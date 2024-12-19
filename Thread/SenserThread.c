/**
  ************************************* Copyright ******************************
  *                 (C) Copyright 2023,--,China, CUIT.
  *                            All Rights Reserved
  *                     By(JCML)
  * FileName   : SenserThread.c
  * Version    : v1.0
  * Author     : JCML
  * Date       : 2024/12/17
  * Description: 传感器数据接收线程
******************************************************************************
 */
#include "SenserThread.h"
#include "main.h"
#include "rtthread.h"
#include "INA219.h"
#include "i2c.h"
#include "usart.h"

INA219_t ina219;
enum KEYSTATE{
    KeyPushed=1,
    KeyReleased,
    KeyShortPress,
    KeyLongPress,
    KeyNone
};

uint8_t KeyState=0;
uint16_t Keytime=0;

/**
 * @brief    传感器数据接收线程
 * @param  parameter 线程参数
 * @return void
 */
void SenserThread_entry(void *parameter){
  //BuzzerBeep();
  if (INA219_Init(&ina219,&hi2c1, 0x80)){
    rt_kprintf("INA219 Init OK!\r\n");
  }
  while(1)
  {
    //数据接收
    INA219_ReadALL(&ina219);
    rt_thread_delay(100);
    //rt_kprintf("voltage:%f %f %f\r\n", ina219.Voltage,ina219.Current,ina219.Power);
    // rt_kprintf("vbus:%f,currunt:%f,power:%f\r\n", ina219.voltage,ina219.current,ina219.power);
    LED_Blink();
    if(KeyScan()==RT_TRUE){
      KeyState=KeyNone;
      rt_kprintf("KeyShortPress\r\n");
    }
  }
}

/**
 * @brief  蜂鸣器简单响一下
 * @param  void
 * @return void
 */
void BuzzerBeep(void){
  HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin, GPIO_PIN_SET);
  rt_thread_delay(100);
  HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin, GPIO_PIN_RESET);
}
/**
 * @brief  一闪一闪亮晶晶
 * @param  void
 * @return void
 */
void LED_Blink(void){
  static rt_bool_t led_flag = RT_FALSE;
  if(led_flag){
    HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);led_flag=RT_FALSE;
  }else{
    HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);led_flag=RT_TRUE;
  }
}


/**
 * @brief  按键扫描函数
 * @param  void
 * @return 是否按下
 */
rt_bool_t KeyScan(void){
  if(HAL_GPIO_ReadPin(Key_GPIO_Port,Key_Pin)==GPIO_PIN_RESET){
    rt_thread_mdelay(20);
    if(HAL_GPIO_ReadPin(Key_GPIO_Port,Key_Pin)==GPIO_PIN_RESET){
      while (HAL_GPIO_ReadPin(Key_GPIO_Port,Key_Pin)==GPIO_PIN_RESET){//等待抬起
        rt_thread_mdelay(1);
      }  
     return RT_TRUE;     
    }
  }
  return RT_FALSE;
}
