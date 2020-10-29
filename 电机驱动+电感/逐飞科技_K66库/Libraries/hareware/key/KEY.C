#include "headfile.h"

void Key_init(void)//按键初始化
{
	port_init (D1, IRQ_EITHER | PF | ALT1 | PULLUP );	//初始化 D1 管脚，下降沿触发中断，带无源滤波器，复用功能为GPIO并设置为输入 ，上拉电阻
	port_init (D2, IRQ_EITHER | PF | ALT1 | PULLUP );
	port_init (D3, IRQ_EITHER | PF | ALT1 | PULLUP );
	set_irq_priority(PORTD_IRQn,2);						//设置优先级
	enable_irq(PORTD_IRQn);								//打开PORTD中断开关
	EnableInterrupts;									//打开总的中断开关

	Key_value=NONE;
	Screen_num=1;
	Key_interrupt_flag=0;//按键中断标志位，在多个文件传递
}
