/**
  ************************************* Copyright ******************************
  *                 (C) Copyright 2023,--,China, CUIT.
  *                            All Rights Reserved
  *                     By(JCML)
  * FileName   : MotorsThread.c
  * Version    : v1.0
  * Author     : JCML
  * Date       : 2024/12/17
  * Description: ��������߳�
******************************************************************************
 */
#include "MotorsThread.h"
#include "main.h"
#include "rtthread.h"




//���������ݽ����߳�
void MotorsThread_entry(void *parameter){

  while(1)
  {
    //���ݽ���

    rt_thread_delay(200);
  }
}