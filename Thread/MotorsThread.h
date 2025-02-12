//
// Created by mulai on 2024/12/17.
//

#ifndef __MOTORSTHREAD_H_
#define __MOTORSTHREAD_H_

#include "main.h"

#define MOTOR_PROPLE_A  0   //�ƽ����A
#define MOTOR_PROPLE_B  1   //�ƽ����B
#define MOTOR_DRIVER    2   //���̵��
#define MOTOR_SLICE     3   //�и���
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
    uint32_t validcnt; //��Ч����ֵ��Ӧ������
    float freq;
    float duty;
    uint16_t updatetimes;
    uint8_t state;
} pwms;

typedef struct {
    enum MotorState State;//���״̬
    int Speed;  //����ٶ�  0-1000
    uint16_t Encode; //��������ֵ
    int16_t Pwm;
}Motor_t;

extern Motor_t Motor[];
extern uint32_t TimeCount;
extern pwms mpwms[];

uint8_t Get2POwer(uint16_t num);
void MotorsThread_entry(void *parameter);
#endif
