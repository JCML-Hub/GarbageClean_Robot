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

uint32_t TimeCount=0;
Motor_t Motor[4];
pwms mpwms[4];
first_order_filter_type_t filter[4];

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

  TIM1->CCR1 = 20;
  TIM1->CCR4 = 25;
  TIM4->CCR1 = 25;
  TIM4->CCR2 = 25;

  HAL_TIM_Base_Start_IT(&htim3);
  HAL_TIM_IC_Start_IT(&htim3,TIM_CHANNEL_1);
  HAL_TIM_IC_Start_IT(&htim3,TIM_CHANNEL_2);
  HAL_TIM_IC_Start_IT(&htim3,TIM_CHANNEL_3);
  HAL_TIM_IC_Start_IT(&htim3,TIM_CHANNEL_4);

  first_order_filter_init(&filter[0],0.1f,0.5f);
  first_order_filter_init(&filter[1],0.1f,0.5f);
  first_order_filter_init(&filter[2],0.1f,0.5f);
  first_order_filter_init(&filter[3],0.1f,0.5f);
  rt_kprintf("Motor Thread Init OK!\r\n");  
  while(1)
  {
    //数据接收
    for(uint8_t i=0;i<4;i++)
    {
      first_order_filter_calc(&filter[i],Motor[i].Encode);
    }

    rt_kprintf("%f,%d\r\n",filter[3].out,Motor[3].Encode);
    rt_thread_delay(20);
  }
}


void Inputcapturehandle(pwms * cpwm,uint32_t cnt,TIM_HandleTypeDef *htim,uint32_t ch){
  uint32_t temp = 0;
  switch(cpwm->state)
  {   
    case 0:{     //测量上升沿
      //开启下次为下降沿采样
      __HAL_TIM_SET_CAPTUREPOLARITY(htim, ch, TIM_INPUTCHANNELPOLARITY_FALLING); 
      cpwm->updatetimes = 0;//溢出计数值置为0
      cpwm->firstrisingcnt =cnt;//捕获第一次计数值
      cpwm->state = 1;//更新状态
      break;
    }
    case 1:{    //测量下降沿
      //开启下一次为上升沿采样
      __HAL_TIM_SET_CAPTUREPOLARITY(htim, ch, TIM_INPUTCHANNELPOLARITY_RISING);      
      cpwm->fallingcnt = cnt;//捕获下降沿的计数值
      //计算有效计数值(考虑溢出)
      cpwm->validcnt =  (cpwm->updatetimes * htim->Instance->ARR)+ cpwm->fallingcnt-cpwm->firstrisingcnt;    
      cpwm->updatetimes  =0;  //溢出计数置为0
      cpwm->state = 2;//更新下一状态       
      break;     
    }
    case 2: { //再次测量上升沿
      cpwm->updatetimes = 0;//溢出计数值置为0
      cpwm->state = 0;//更新状态  
    }   
    break;  
  }      
}


void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
  if(htim->Instance ==  TIM3)
  {
    if(htim->Channel ==  HAL_TIM_ACTIVE_CHANNEL_1){
      Inputcapturehandle(&mpwms[0],TIM3->CCR1,htim,TIM_CHANNEL_1);   
      Motor[0].Encode = mpwms[0].validcnt;
  }
  else if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2){//进入到自己的中断回调函数中执行
      Inputcapturehandle(&mpwms[1],TIM3->CCR2,htim,TIM_CHANNEL_2);
      Motor[1].Encode = mpwms[1].validcnt;
  }
    if(htim->Channel ==  HAL_TIM_ACTIVE_CHANNEL_3){
        Inputcapturehandle(&mpwms[2],TIM3->CCR3,htim,TIM_CHANNEL_3);   
        Motor[2].Encode = mpwms[2].validcnt;
    }
    else if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_4){//进入到自己的中断回调函数中执行
        Inputcapturehandle(&mpwms[3],TIM3->CCR4,htim,TIM_CHANNEL_4);
        Motor[3].Encode = mpwms[3].validcnt;
    }
  }
}
/*获取2的指数*/
uint8_t Get2POwer(uint16_t num){
  uint8_t i = 0;
  while(num){
    num = num>>1;
    i++;
  }
  return i-1;
}
