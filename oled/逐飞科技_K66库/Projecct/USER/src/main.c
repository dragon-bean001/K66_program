/********************************************
逐飞科技 总钻风-摄像头  历程
Designed by Fly Sir
软件版本:V1.1
最后更新:2016年5月3日
相关信息参考下列地址：
淘宝店：https://seekfree.taobao.com/
------------------------------------
软件版本： IAR 7.2 or MDK 5.17
目标核心： MK60DN512VLL10
============================================
MT9V032接线定义：
------------------------------------ 
    模块管脚            单片机管脚
    SDA(51的RX)         PTC17
    SCL(51的TX)         PTC16
	场中断(VSY)         PTC6
    像素中断(PCLK)      PTC18
    数据口(D0-D7)       PTC8-PTC15 

    串口  
    波特率 115200 
    数据位 8 
    校验位 无
    停止位 1位
    流控   无
	串口连接注意事项：切勿使用蓝牙等无线串口连接
    RX                  PTD3
    TX                  PTD2
============================================

分辨率是                188*120
摄像头参数设置可以到    SEEKFREE-->h_file-->SEEKFREE_MT9V032.h

总钻风-摄像头测试步骤：
1.下载程序到开发板
2.插上串口线或者USB转TTL
3.接好MT9V032模块接线
4.通电在TFT液晶上即可观看    
*********************************************/  
#include "headfile.h"



uint16 dat;
int main(void)
{
   uint8 a[10]={1}; 
	 uint32 b;
	get_clk();//上电后必须运行一次这个函数，获取各个频率信息，便于后面各个模块的参数设置
	OLED_Init();
	
	adc_init(ADC1_SE12);

	 while(1)
	 {
		 b= adc_once(ADC1_SE12,ADC_12bit);
		OLED_Print_Num(16,0,13);
		 systick_delay_ms(100);
		OLED_P6x8Str(8,6,(uint8 *)"voltage");	
		 systick_delay_ms(100);
	 }
	



}

