/**
  ****************************(C) COPYRIGHT 2016 DJI****************************
  * @file       pid.c/h
  * @brief      pid实现函数，包括初始化，PID计算函数，
  * @note
  * @history
  *  Version    Date            Author          Modification
  *  V1.0.0     Dec-26-2018     RM              1. 完成
  *
  @verbatim
  ==============================================================================

  ==============================================================================
  @endverbatim
  ****************************(C) COPYRIGHT 2016 DJI****************************
  */
#ifndef PID_H
#define PID_H
#include "main.h"
#include "struct_typedef.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef fp32
//typedef float fp32;
#endif
	
enum PID_MODE { PID_POSITION = 0, PID_DELTA };

typedef struct pid_type {
    uint8_t mode;
    // PID 三参数
    fp32 Kp;
    fp32 Ki;
    fp32 Kd;

    fp32 max_out;   //最大输出
    fp32 max_iout;  //最大积分输出

    fp32 set;
    fp32 fdb;

    fp32 out;
    fp32 Pout;
    fp32 Iout;
    fp32 Dout;
    fp32 Dbuf[3];   //微分项 0最新 1上一次 2上上次
    fp32 error[3];  //误差项 0最新 1上一次 2上上次

} pid_type_t;

void pid_init(pid_type_t *pid, uint8_t mode, const fp32 PID[5]);
fp32 pid_calc(pid_type_t *pid, fp32 ref, fp32 set);
void pid_clear(pid_type_t *pid);


#ifdef __cplusplus
}
#endif

#endif
