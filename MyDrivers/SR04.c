/**
  ************************************* Copyright ******************************
  *                 (C) Copyright 2023,--,China, CUIT.
  *                            All Rights Reserved
  *                     By(JCML)
  * FileName   : SR04.c
  * Version    : v1.0
  * Author     : JCML
  * Date       : 2024/12/19
  * Description: SR04???????
******************************************************************************
 */
#include "main.h"
#include "SR04.h"
#include "tim.h"
#include "rtthread.h"

HSR04_Node_t hsr04[4];


void SR04_Init(void){
  	HAL_TIM_IC_Start_IT(&htim3,TIM_CHANNEL_1);//??????
}

void SR04_Read(void){
  
}
//todo:??????????????????????????????????????
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim){
  uint32_t temp;  
  rt_interrupt_enter();

  if(htim->Instance->CCER == State_Rising){//???
    __HAL_TIM_SET_COUNTER(&htim3,0);//?????
    switch (htim->Channel){//?????????
      case HAL_TIM_ACTIVE_CHANNEL_1:
        hsr04[FRONT_RIGHT].tick = htim3.Instance->CCR1;//?????????
        hsr04[FRONT_RIGHT].state = Rising;
        break;
      case HAL_TIM_ACTIVE_CHANNEL_2: 

        hsr04[FRONT_LEFT].state = Rising;
        break;
      case HAL_TIM_ACTIVE_CHANNEL_3: 
        hsr04[RIGHT].state = Rising;
        break;
      case HAL_TIM_ACTIVE_CHANNEL_4: 
        hsr04[LEFT].state = Rising;
        break;
      default:break;
    }
    __HAL_TIM_SET_CAPTUREPOLARITY(&htim3, htim->Channel,TIM_INPUTCHANNELPOLARITY_FALLING);//??????????
  }else if(htim->Instance->CCER == State_Falling){//???
    temp = HAL_TIM_ReadCapturedValue(&htim3,htim->Channel)+1;
    __HAL_TIM_SET_CAPTUREPOLARITY(&htim3, htim->Channel,TIM_INPUTCHANNELPOLARITY_RISING);//??????????
    switch (htim->Channel){//?????????
      case HAL_TIM_ACTIVE_CHANNEL_1: 
        hsr04[FRONT_RIGHT].distance = (float)(htim3.Instance->CCR1 - hsr04[FRONT_RIGHT].tick) * 0.01724f;
        hsr04[FRONT_RIGHT].tick = 0;
        hsr04[FRONT_RIGHT].state = Falling;
        break;
      case HAL_TIM_ACTIVE_CHANNEL_2: 
        hsr04[FRONT_LEFT].distance = (float)temp * 0.01724f;
        hsr04[FRONT_LEFT].state = Falling;
        break;
      case HAL_TIM_ACTIVE_CHANNEL_3: 
        hsr04[RIGHT].distance = (float)temp * 0.01724f;
        hsr04[RIGHT].state = Falling;
        break;
      case HAL_TIM_ACTIVE_CHANNEL_4: 
        hsr04[LEFT].distance = (float)temp * 0.01724f;
        hsr04[LEFT].state = Falling;
        break;
      default:break;
    }
  }
	rt_interrupt_leave();
}
