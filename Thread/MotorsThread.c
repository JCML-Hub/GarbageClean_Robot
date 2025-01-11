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
#include "rtthread.h"

Motor_t Motor[4];


//传感器数据接收线程
void MotorsThread_entry(void *parameter){
  //HAL_TIM_IC_Start_IT(&htim3,TIM_CHANNEL_1);
  while(1)
  {
    //数据接收

    rt_thread_delay(200);
  }
}

void GetEncode(void){
  // Motor[0].Encoder = (int16_t)(TIM3->CCR1);
  // Motor[1].Encoder = (int16_t)(TIM3->CCR2);
  // Motor[2].Encoder = (int16_t)(TIM3->CCR3);
  // Motor[3].Encoder = (int16_t)(TIM3->CCR4);
}

// void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim){
//   uint32_t temp;  
//   rt_interrupt_enter();

//   if(htim->Instance->CCER == State_Rising){//???
//     __HAL_TIM_SET_COUNTER(&htim3,0);//?????
//     switch (htim->Channel){//?????????
//       case HAL_TIM_ACTIVE_CHANNEL_1:
//         hsr04[FRONT_RIGHT].tick = htim3.Instance->CCR1;//?????????
//         hsr04[FRONT_RIGHT].state = Rising;
//         break;
//       case HAL_TIM_ACTIVE_CHANNEL_2: 

//         hsr04[FRONT_LEFT].state = Rising;
//         break;
//       case HAL_TIM_ACTIVE_CHANNEL_3: 
//         hsr04[RIGHT].state = Rising;
//         break;
//       case HAL_TIM_ACTIVE_CHANNEL_4: 
//         hsr04[LEFT].state = Rising;
//         break;
//       default:break;
//     }
//     __HAL_TIM_SET_CAPTUREPOLARITY(&htim3, htim->Channel,TIM_INPUTCHANNELPOLARITY_FALLING);//??????????
//   }else if(htim->Instance->CCER == State_Falling){//???
//     temp = HAL_TIM_ReadCapturedValue(&htim3,htim->Channel)+1;
//     __HAL_TIM_SET_CAPTUREPOLARITY(&htim3, htim->Channel,TIM_INPUTCHANNELPOLARITY_RISING);//??????????
//     switch (htim->Channel){//?????????
//       case HAL_TIM_ACTIVE_CHANNEL_1: 
//         hsr04[FRONT_RIGHT].distance = (float)(htim3.Instance->CCR1 - hsr04[FRONT_RIGHT].tick) * 0.01724f;
//         hsr04[FRONT_RIGHT].tick = 0;
//         hsr04[FRONT_RIGHT].state = Falling;
//         break;
//       case HAL_TIM_ACTIVE_CHANNEL_2: 
//         hsr04[FRONT_LEFT].distance = (float)temp * 0.01724f;
//         hsr04[FRONT_LEFT].state = Falling;
//         break;
//       case HAL_TIM_ACTIVE_CHANNEL_3: 
//         hsr04[RIGHT].distance = (float)temp * 0.01724f;
//         hsr04[RIGHT].state = Falling;
//         break;
//       case HAL_TIM_ACTIVE_CHANNEL_4: 
//         hsr04[LEFT].distance = (float)temp * 0.01724f;
//         hsr04[LEFT].state = Falling;
//         break;
//       default:break;
//     }
//   }
// 	rt_interrupt_leave();
// }
