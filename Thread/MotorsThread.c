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