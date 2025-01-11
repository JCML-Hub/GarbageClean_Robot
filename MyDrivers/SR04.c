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
  	
}

void SR04_Read(void){
  
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
  rt_interrupt_enter();
  if(HAL_GPIO_ReadPin(GPIOB,GPIO_Pin)==GPIO_PIN_RESET){
    switch (GPIO_Pin)
    {
      case Echo1_Pin: hsr04[FRONT_LEFT].distance = (uwTick-hsr04[FRONT_LEFT].tickLast)*0.174;break;
      case Echo2_Pin: hsr04[FRONT_RIGHT].distance = (uwTick-hsr04[FRONT_RIGHT].tickLast)*0.174;break;
      case Echo3_Pin: hsr04[LEFT].distance = (uwTick-hsr04[LEFT].tickLast)*0.174;break;
      case Echo4_Pin: hsr04[RIGHT].distance = (uwTick-hsr04[RIGHT].tickLast)*0.174;break;
      default:break;
    }
  }else{
    switch (GPIO_Pin)
    {
      case Echo1_Pin: hsr04[FRONT_LEFT].tickLast = uwTick;break;
      case Echo2_Pin: hsr04[FRONT_RIGHT].tickLast = uwTick;break;
      case Echo3_Pin: hsr04[LEFT].tickLast = uwTick;break;
      case Echo4_Pin: hsr04[RIGHT].tickLast = uwTick;break;
      default:break;
    }
  }
  rt_interrupt_leave();
}


