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

volatile HSR04_Node_t hsr04[4];
uint32_t Tick = 0;

void SR04_Read(float *distance){
  for(int i=0;i<4;i++){
    if(hsr04[i].flag == RT_TRUE){
      distance[i] = hsr04[i].distance;
      Tick = uwTick;
      hsr04[i].flag = RT_FALSE;
    }
    if(uwTick-Tick > 250){//如果超过250ms没有更新，则置为0---->掉线检测
      distance[i] = 0;
    }
  }
}

void SR04_Read_Callback(uint16_t GPIO_Pin){
  if(HAL_GPIO_ReadPin(GPIOB,GPIO_Pin)==GPIO_PIN_RESET){
    switch (GPIO_Pin)
    {
      case Echo1_Pin: {
        hsr04[FRONT_LEFT].distance = (uwTick-hsr04[FRONT_LEFT].tickLast)*0.174;
        hsr04[FRONT_LEFT].flag = RT_TRUE;//可读
        break;
      }
      case Echo2_Pin: {
        hsr04[FRONT_RIGHT].distance = (uwTick-hsr04[FRONT_RIGHT].tickLast)*0.174;
        hsr04[FRONT_RIGHT].flag = RT_TRUE;//可读
        break;
      }
      case Echo3_Pin: {
        
        hsr04[LEFT].distance = (uwTick-hsr04[LEFT].tickLast)*0.174;
        hsr04[LEFT].flag = RT_TRUE;//可读
        break;
      }
      case Echo4_Pin: {
        hsr04[RIGHT].distance = (uwTick-hsr04[RIGHT].tickLast)*0.174;
        hsr04[RIGHT].flag = RT_TRUE;//可读
        break;
      }
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
}


