//
// Created by mulai on 2024/12/17.
//

#ifndef __MOTORSTHREAD_H_
#define __MOTORSTHREAD_H_

#define MOTOR_PROPLE_A  0   //推进电机A
#define MOTOR_PROPLE_B  1   //推进电机B
#define MOTOR_DRIVER    2   //拨盘电机
#define MOTOR_SLICE     3   //切割电机

enum MotorState {
    Forward=1,
    Reversal,
    Stop
};

typedef struct {
    enum MotorState State;//电机状态
    int Speed;  //电机速度  0-100
    // int16_t Encode; //编码器数值
}Motor_t;

extern Motor_t Motor[];

void MotorsThread_entry(void *parameter);
#endif
