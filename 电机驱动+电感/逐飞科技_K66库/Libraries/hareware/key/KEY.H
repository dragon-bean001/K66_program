#ifndef _KEY_H
#define _KEY_H
#include "headfile.h"
#define get_key  gpio_get(D1)*2+gpio_get(D0)*1+gpio_get(D2)*4   //获取按键情况

extern uint8 key_interrupt_flag;//按键中断标志位
extern uint8 key_value_last;//上一个键值
extern uint8 key_value;//当前键值

void Key_init(void);//按键初始化
void Key_select(void);//按键判断函数
#endif


