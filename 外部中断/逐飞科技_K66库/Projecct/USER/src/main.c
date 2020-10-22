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
    get_clk();//上电后必须运行一次这个函数，获取各个频率信息，便于后面各个模块的参数设置
	  gpio_init(D15,GPO,1);
  //相关的库函数在 MK60DN10_ftm.c 里面
	//MK60DN共有三个FTM模块FTM0、FTM1、FTM2，每一个模块只能产生一个频率的PWM，意味着一个模块下所有的通道频率必须一致，
	//三个模块就只能产生三种不同频率的PWM。同一个模块不同通道占空比可以不一样。
	ftm_pwm_init(ftm0,ftm_ch0,50,1950);//初始化ftm0模块，0通道为50HZ，占空比为百分之50，默认精度为1000 引脚对应查看MK60DN10_port_cfg.h
	//while(1)
	//{
		ftm_pwm_duty(ftm0,ftm_ch0,1000);
	//}
   while(1)
	 {
	 }
		//ftm_pwm_duty(ftm0,ftm_ch0,1950);//设置ftm0模块，0通道占空比为百分之10，占空比 = 100/FTM0_PRECISON;
	
}

//uint8  data1[8] = {1,2,3,4,5,6,7,8};
//uint16 data2 = 60000;
//uint32 data3 = 600051;
//
//uint8  data11[8];
//uint16 data22; 
//uint32 data33;
//
//int main(void)
//{
//	get_clk();//上电后必须运行一次这个函数，获取各个频率信息，便于后面各个模块的参数设置
//	
//	//相关的库函数在 MK60DN10_flash.c 里面
//	FLASH_Init();			//初始化flash模块
//	FLASH_EraseSector(10);	//擦除扇区
//	FLASH_WriteSector(10,(const uint8 *)data1,8,0);		
//	FLASH_WriteSector(10,(const uint8 *)&data2,8,8);
//	FLASH_WriteSector(10,(const uint8 *)&data3,8,16);
//    for(;;)
//	{
//		//读取保存的data1数组数据
//		data11[0] = flash_read(10,0,uint8);	
//		data11[1] = flash_read(10,1,uint8);
//		data11[2] = flash_read(10,2,uint8);
//		data11[3] = flash_read(10,3,uint8);
//        data11[4] = flash_read(10,4,uint8);
//        data11[5] = flash_read(10,5,uint8);
//        data11[6] = flash_read(10,6,uint8);
//        data11[7] = flash_read(10,7,uint8);
//		
//		//读取保存的data2数组数据
//		data22 = flash_read(10,8,uint16);
//		
//		//读取保存的data3变量数据
//		data33 = flash_read(10,16,uint32);
//	}
//}


