/**
  ************************************* Copyright ******************************
  *                 (C) Copyright 2023,--,China, CUIT.
  *                            All Rights Reserved
  *                     By(JCML)
  * FileName   : SR04.c
  * Version    : v1.0
  * Author     : JCML
  * Date       : 2024/12/19
  * Description: SR04³¬Éù²¨Ä£¿éÇý¶¯
******************************************************************************
 */
#ifndef __SR04_H_
#define __SR04_H_

#include "main.h"
#include "rtthread.h"


#define FRONT_LEFT 0
#define FRONT_RIGHT 1
#define LEFT        2
#define RIGHT       3



typedef struct{
    rt_bool_t flag;
    float distance;
    uint32_t tickLast;
}HSR04_Node_t;

volatile extern HSR04_Node_t hsr04[];

void SR04_Init(void);
void SR04_Read_Callback(uint16_t GPIO_Pin);
void SR04_Read(float *distance);
#endif /* INC_INA219_H_ */
