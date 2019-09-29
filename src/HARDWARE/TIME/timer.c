#include "timer.h"
#include "usart.h"
#include "sys.h"
#include "clock.h"
#include "key.h"


void TIM3_Init(u16 arr,u16 psc)
{  
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	
	TIM_TimeBaseStructure.TIM_Period = arr; 
	TIM_TimeBaseStructure.TIM_Prescaler =psc;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); 

	TIM_ITConfig(TIM3,TIM_IT_Update, ENABLE);
	
	
	NVIC_InitStructure.NVIC_IRQChannel =TIM3_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //��ʼ��NVIC�Ĵ���

	TIM_Cmd(TIM3, ENABLE);  //ʹ��TIM1
   
}

 

//��ʱ������������ʱ����
void TIM3_IRQHandler(void)
{ 
	 if(TIM_GetITStatus(TIM3,TIM_IT_Update)!=RESET)//�ж��Ƿ����˸���(���)�ж�
	 {
		 
		 if (KeyStat.stat == COMMON_STATE) {        //���������״̬����������ʾ������
						tosettime.sec++; //�����˽ṹ����£����ǣ��п�������������60�����ԣ�����ͳһ��ʱ�����
						update_to_time();  //����ʱ��
						show_num_time();//չʾ����ʱ��
						calendar_circle_clock_showtime(120,120,200,8,tosettime.hour,tosettime.min,tosettime.sec); //չʾ�ӱ�ʱ��
					}
						TIM_ClearITPendingBit(TIM3, TIM_IT_Update); //����жϱ�־λ
					
    }
}
