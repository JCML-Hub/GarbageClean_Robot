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




//传感器数据接收线程
void MotorsThread_entry(void *parameter){

  while(1)
  {
    //数据接收

    rt_thread_delay(200);
  }
}