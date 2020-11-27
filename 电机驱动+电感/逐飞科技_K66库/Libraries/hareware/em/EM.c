#include "EM.h"

#define smoothing_num 4 //����5��
uint16 EM_left[smoothing_num+1];//�����洢��������5��ֵ
uint16 EM_mid[smoothing_num+1];
uint16 EM_right[smoothing_num+1];
uint16 EM_left_value;
uint16 EM_right_value;
uint16 EM_mid_value;
float ELE_Angle_max_out=200;
float EM_error=0.0f;
float EM_last_error=0.0f;
float PWM_Direction=0;
PID_t ELE_PID_Direction;//��е�PID����

void EM_get()
{
	EM_right[smoothing_num] =adc_once(ADC1_SE12, ADC_16bit);  //��
	EM_left[smoothing_num]=adc_once(ADC1_SE10, ADC_16bit);  //��
	EM_mid[smoothing_num]=  adc_once(ADC1_SE13, ADC_16bit);//��
}
	
void EM_store()
{
	int i;
	for( i=0;i<smoothing_num;i++)//�����˲�����n����������
	{
		EM_right[i]=EM_right[i+1];
		EM_left[i]=EM_left[i+1];
		EM_mid[i]=EM_mid[i+1];//��ֵ���󻬶�������ֵ�������ұ�
	}
	EM_get();//���ڻ�ȡ����ֵ����ȡ���������ұ�
	
	
	//����е����ֵ��Ȩƽ������
	EM_right_value=(EM_right[0]*0.05f+EM_right[1]*0.05f+EM_right[2]*0.1f+EM_right[3]*0.1f+EM_right[4]*0.8f)*100.0f/EM_right_max;
	
	EM_left_value=(EM_left[0]*0.05f+EM_left[1]*0.05f+EM_left[2]*0.1f+EM_left[3]*0.1f+EM_left[4]*0.8f)*100.0f/EM_left_max;
	
	EM_mid_value=(EM_mid[0]*0.05f+EM_mid[1]*0.05f+EM_mid[2]*0.1f+EM_mid[3]*0.1f+EM_mid[4]*0.8f)*100.0f/EM_mid_max;

	   
		
		 OLED_Print_Num1(5,1,EM_left_value);
		 OLED_Print_Num1(5,3,EM_mid_value);
		 OLED_Print_Num1(5,5,EM_right_value);
		 OLED_Print_Num1(60,1,PWM_Direction);//x=40����Էֿ���
		 OLED_Print_float(60,5,ELE_PID_Direction.KpPos);
	   OLED_Print_float(60,7,ELE_PID_Direction.KdPos); 
}

void EM_init()
{
	adc_init(ADC1_SE10);
	adc_init(ADC1_SE12);
	adc_init(ADC1_SE13);
	
	EM_store();//��ȡһ��

}

void EM_dectect()
{
	EM_get();
	EM_store();
	EM_error=(EM_left_value -EM_right_value)*100/(EM_left_value+EM_right_value);//���ƫ�����
	PWM_Direction=PID_Direction_Pos_Neg(&ELE_PID_Direction,EM_error);
	if(PWM_Direction>ELE_Angle_max_out)
	{
		PWM_Direction=ELE_Angle_max_out;
	}
	else
		if(PWM_Direction<-ELE_Angle_max_out)
			PWM_Direction=-ELE_Angle_max_out;
	if(EM_left_value<EM_right_value&&PWM_Direction<-50)//��ƫ��PWM_DirectionС��0
	{
		Motor12_speed(1500-PWM_Direction,0);
		Motor34_speed(0,1500+PWM_Direction);
	}
	
	else if(EM_left_value>EM_right_value&&PWM_Direction>50)//��ƫ��PWM_Direction����0
	{
		Motor34_speed(1500+PWM_Direction,0);
		Motor12_speed(0,1500-PWM_Direction);
	}
	else
	{
		Motor34_speed(1500,0);
		Motor12_speed(1500,0);
	}

}
	
float PID_Direction_Pos_Neg(PID_t * pid,float newE_k)
{
	float temp;
	pid->E_k_1 = pid->E_k;
	pid->E_k = newE_k;
			

	pid->Kp_OUT = pid->KpPos  * newE_k ;
	pid->Kd_OUT = pid->KdPos  * (newE_k - pid->E_k_1);	//����D���ž���
	
	temp=pid->Kp_OUT+ pid->Kd_OUT;	//����D���ž���
	pid->PID_out=temp;

	return temp;			
}
