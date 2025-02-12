#ifndef __ALGORITHM_H
#define __ALGORITHM_H

#include "stdint.h"
#include "struct_typedef.h"

#ifdef __cplusplus
extern "C" {
#endif

#define GET_BIT(reg, bit) (((reg) >> bit) & 0x01)

/* 角度边界处理 */
#define BOUNDARY_PROCESS(var, ref, exp, max)  \
    if ((ref) - (exp) >= (max / 2)) {         \
        var = (ref)-max;                      \
    } else if ((ref) - (exp) <= -(max / 2)) { \
        var = (ref) + max;                    \
    } else {                                  \
        var = (ref);                          \
    }

typedef struct {
    fp32 input;         //输入数据
    fp32 out;           //输出数据
    fp32 min_value;     //限幅最小值
    fp32 max_value;     //限幅最大值
    fp32 frame_period;  //时间间隔
} ramp_function_source_t;

typedef struct {
    fp32 input;         //输入数据
    fp32 out;           //滤波输出的数据
    fp32 num;           //滤波参数
    fp32 frame_period;  //滤波的时间间隔 单位 s
} first_order_filter_type_t;

typedef struct {
    fp32 Kp;
    fp32 value[2];  //误差项 0最新 1上一次
} feedforward_type_t;

void ramp_init(ramp_function_source_t *ramp_source_type);
void ramp_calc(ramp_function_source_t *ramp_source_type, fp32 input, fp32 step);
void first_order_filter_init(first_order_filter_type_t *first_order_filter_type, fp32 frame_period, const fp32 num);
void first_order_filter_calc(first_order_filter_type_t *first_order_filter_type, fp32 input);
void feedforward_init(feedforward_type_t *handle, fp32 parameter);
fp32 feedforward_calc(feedforward_type_t *handle, fp32 set);

#ifdef __cplusplus
}
#endif

#endif
