/**
  ************************************* Copyright ******************************
  *                 (C) Copyright 2023,--,China, CUIT.
  *                            All Rights Reserved
  *                     By(JCML)
  * FileName   : CommunicateThread.c
  * Version    : v1.0
  * Author     : JCML
  * Date       : 2024/12/17
  * Description: 用于通信的线程，与外部的芯片或者传感器进行通信
******************************************************************************
 */
#include "CommunicateThread.h"
#include "main.h"
#include "rtthread.h"




//传感器数据接收线程
void CommunicateThread_entry(void *parameter){

  while(1)
  {
    //数据接收

    rt_thread_delay(200);
  }
}