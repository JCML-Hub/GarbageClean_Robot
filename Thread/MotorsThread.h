//
// Created by mulai on 2024/12/17.
//

#ifndef __MOTORSTHREAD_H_
#define __MOTORSTHREAD_H_

#include "main.h"

#define MOTOR_PROPLE_A  0   //推进电机A
#define MOTOR_PROPLE_B  1   //推进电机B
#define MOTOR_DRIVER    2   //拨盘电机
#define MOTOR_SLICE     3   //切割电机
#define State_Rising	0x00000001
#define State_Falling	0x00000003

#define CONTSTART   0
#define CONTEND     1

enum MotorState {
    Forward=1,
    Reversal,
    Stop
};

typedef struct {
    uint64_t StartCNT;
    uint64_t EndCNT;
}Encoder_t;

typedef struct mypwm{
    uint32_t firstrisingcnt;
    uint32_t secondrisingcnt;
    uint32_t fallingcnt;
    uint32_t validcnt; //有效计数值对应于脉宽
    float freq;
    float duty;
    uint16_t updatetimes;
    uint8_t state;
} pwms;

typedef struct {
    enum MotorState State;//电机状态
    int Speed;  //电机速度  0-1000
    uint16_t Encode; //编码器数值
    int16_t Pwm;
}Motor_t;

extern Motor_t Motor[];
extern uint32_t TimeCount;
extern pwms mpwms[];

uint8_t Get2POwer(uint16_t num);
void MotorsThread_entry(void *parameter);
#endif
