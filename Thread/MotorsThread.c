/**
  ************************************* Copyright ******************************
  *                 (C) Copyright 2023,--,China, CUIT.
  *                            All Rights Reserved
  *                     By(JCML)
  * FileName   : MotorsThread.c
  * Version    : v1.0
  * Author     : JCML
  * Date       : 2024/12/17
  * Description: 电机控制线程
******************************************************************************
 */
#include "MotorsThread.h"
#include "main.h"
#include "tim.h"
#include "rtthread.h"
#include "algorithm.h"
#include "pid.h"

Motor_t Motor[4];
volatile pwm_data_t pwm_data;
pid_type_t motorSpeedPID[4];
first_order_filter_type_t filter[4];
const fp32 PID_Param[5] = {2.5f, 0.0f, 0.0f, 50.0f, 50.0f};


volatile uint32_t tick = 0;

//传感器数据接收线程
void MotorsThread_entry(void *parameter){
  HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_4);
  HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_2);
  HAL_GPIO_WritePin(M1CCW_GPIO_Port,M1CCW_Pin,GPIO_PIN_SET);
  HAL_GPIO_WritePin(M2CCW_GPIO_Port,M2CCW_Pin,GPIO_PIN_SET);
  HAL_GPIO_WritePin(M3CCW_GPIO_Port,M3CCW_Pin,GPIO_PIN_SET);
  HAL_GPIO_WritePin(M4CCW_GPIO_Port,M4CCW_Pin,GPIO_PIN_SET);

  HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_1);
  HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_2);
  HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_3);
  HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_4);
  HAL_TIM_Base_Start_IT(&htim3);


  first_order_filter_init(&filter[0], 0.05f, 0.5f);
  first_order_filter_init(&filter[1], 0.05f, 0.5f);
  first_order_filter_init(&filter[2], 0.05f, 0.5f);
  first_order_filter_init(&filter[3], 0.05f, 0.5f);
  pid_init(&motorSpeedPID[0], PID_POSITION, PID_Param);
  pid_init(&motorSpeedPID[1], PID_POSITION, PID_Param);
  pid_init(&motorSpeedPID[2], PID_POSITION, PID_Param);
  pid_init(&motorSpeedPID[3], PID_POSITION, PID_Param);
  rt_kprintf("Motor Thread Init OK!\r\n");  
  while(1)
  { 
    //数据接收
    Encoder_Read();
    for(uint8_t i=0;i<4;i++){
      first_order_filter_calc(&filter[i], Motor[i].Encode);
      pid_calc(&motorSpeedPID[i], filter[i].out, 30.0f);
    }
    //MotorControl(motorSpeedPID[0].out,motorSpeedPID[1].out,motorSpeedPID[2].out,motorSpeedPID[3].out);

    //rt_kprintf("%.2f,%.2f\n",Motor[2].Encode,filter[2].out);
    rt_thread_delay(40);
  }
}

void Encoder_Read(void){
  static uint32_t Tick = 0;
  for(int i=0;i<4;i++){
    if(pwm_data.flag[i] == RT_TRUE){
      Motor[i].Encode = 100000.0f/pwm_data.period[i];//换算成频率
      Tick = uwTick;
      pwm_data.flag[i] = RT_FALSE;
    }
    if(uwTick-Tick > 40){//如果超过100ms没有更新，则置为0---->掉线检测
      Motor[i].Encode = 0.0f;
    }
  }
}

//电机控制
void MotorControl(float M1,float M2,float M3,float M4){
  if(M1>0){HAL_GPIO_WritePin(M1CCW_GPIO_Port,M1CCW_Pin,GPIO_PIN_SET);TIM1->CCR1 = M1;
  }else{HAL_GPIO_WritePin(M1CCW_GPIO_Port,M1CCW_Pin,GPIO_PIN_RESET);TIM1->CCR1 = -M1;}

  if(M2>0){HAL_GPIO_WritePin(M2CCW_GPIO_Port,M2CCW_Pin,GPIO_PIN_SET);TIM1->CCR4 = M2;
  }else{HAL_GPIO_WritePin(M2CCW_GPIO_Port,M2CCW_Pin,GPIO_PIN_RESET);TIM1->CCR4 = -M2;} 

  if(M3>0){HAL_GPIO_WritePin(M3CCW_GPIO_Port,M3CCW_Pin,GPIO_PIN_SET);TIM4->CCR1 = M3;
  }else{HAL_GPIO_WritePin(M3CCW_GPIO_Port,M3CCW_Pin,GPIO_PIN_RESET);TIM4->CCR1 = -M3;}

  if(M4>0){HAL_GPIO_WritePin(M4CCW_GPIO_Port,M4CCW_Pin,GPIO_PIN_SET);TIM4->CCR2 = M4;
  }else{HAL_GPIO_WritePin(M4CCW_GPIO_Port,M4CCW_Pin,GPIO_PIN_RESET);TIM4->CCR2 = -M4;}
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
  uint32_t current_capture;
    if(htim->Instance == TIM3){
        uint8_t ch = (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1) ? 0 :
                    (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2) ? 1 :
                    (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_3) ? 2 : 3;
        current_capture = HAL_TIM_ReadCapturedValue(htim, ch*4);
        if(pwm_data.last_capture[ch] != 0)
        {
            if(current_capture > pwm_data.last_capture[ch]){
              pwm_data.period[ch] = (65535 * pwm_data.overflow_cnt[ch]) + current_capture - pwm_data.last_capture[ch];
                //rt_kprintf("int:%d,%d,%d,%d\n",ch,pwm_data.period[ch],current_capture,pwm_data.last_capture[ch]);
              pwm_data.flag[ch] = RT_TRUE;
            }
        }
        
        // 更新捕获值和溢出计数器
        pwm_data.last_capture[ch] = current_capture;
        pwm_data.overflow_cnt[ch] = 0;
    }
}


