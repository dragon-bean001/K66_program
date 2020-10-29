#ifndef _KEY_H
#define _KEY_H
#include "headfile.h"
#define get_key  gpio_get(D2)*2+gpio_get(D1)*1+gpio_get(D3)*4   //获取按键情况

u8 key_value_last;
u8 key_value;

#endif