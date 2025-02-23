//
// Created by mulai on 2024/12/17.
//

#ifndef __MOTORSTHREAD_H_
#define __MOTORSTHREAD_H_

#include "main.h"
#include "rtthread.h"

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

typedef struct {
    enum MotorState State;//电机状态
    int Speed;  //电机速度  0-1000
    float Encode; //编码器数值
    int16_t Pwm;
}Motor_t;

// 全局变量存储四个通道的捕获数据
typedef struct {
    uint32_t last_capture[4];  // 各通道上一次捕获值
    uint32_t period[4];        // 各通道周期值（单位us）
    uint16_t overflow_cnt[4];  // 各通道溢出计数器
    rt_bool_t flag[4];          // 各通道捕获标志
} pwm_data_t;


extern volatile pwm_data_t pwm_data;
extern Motor_t Motor[];
extern volatile uint32_t tick;

uint8_t Get2POwer(uint16_t num);
void MotorsThread_entry(void *parameter);
void Encoder_Read(void);
void Motor_Read_Callback(uint16_t GPIO_Pin);

void MotorControl(float M1,float M2,float M3,float M4);
#endif
