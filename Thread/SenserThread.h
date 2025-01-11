//
// Created by mulai on 2024/12/17.
//

#ifndef __SENSERTHREAD_H_
#define __SENSERTHREAD_H_

#include "rtthread.h"
#include "gpio.h"


enum KEYSTATE{
    KeyPushed=1,
    KeyReleased,
    KeyShortPress,
    KeyLongPress,
    KeyNone
};


void BuzzerBeep(void);
void LED_Blink(void);
rt_bool_t KeyScan(void);
void Myprintf(const char *format, ...);
void SenserThread_entry(void *parameter);
#endif
