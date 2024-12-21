//
// Created by mulai on 2024/12/17.
//

#ifndef __MOTORSTHREAD_H_
#define __MOTORSTHREAD_H_

#define MOTOR_PROPLE_A  0   //�ƽ����A
#define MOTOR_PROPLE_B  1   //�ƽ����B
#define MOTOR_DRIVER    2   //���̵��
#define MOTOR_SLICE     3   //�и���

enum MotorState {
    Forward=1,
    Reversal,
    Stop
};

typedef struct {
    enum MotorState State;//���״̬
    int Speed;  //����ٶ�  0-100
    // int16_t Encode; //��������ֵ
}Motor_t;

extern Motor_t Motor[];

void MotorsThread_entry(void *parameter);
#endif
