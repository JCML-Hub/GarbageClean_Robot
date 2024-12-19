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
#ifndef INC_SR04_H_
#define INC_SR04_H_

#include "main.h"
#define State_Rising	0x00000001
#define State_Falling	0x00000003

#define FRONT_LEFT 0
#define FRONT_RIGHT 1
#define LEFT        2
#define RIGHT       3

enum HSR04_STATE{
    Falling=1,
    Rising
};


typedef struct{
    enum HSR04_STATE state;
    float distance;
    uint32_t tick;
}HSR04_Node_t;


extern HSR04_Node_t hsr04[];

void SR04_Init(void);

#endif /* INC_INA219_H_ */
