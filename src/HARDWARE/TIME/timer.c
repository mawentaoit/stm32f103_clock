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
	
	
	NVIC_InitStructure.NVIC_IRQChannel =TIM3_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器

	TIM_Cmd(TIM3, ENABLE);  //使能TIM1
   
}

 

//定时器，产生秒钟时间间隔
void TIM3_IRQHandler(void)
{ 
	 if(TIM_GetITStatus(TIM3,TIM_IT_Update)!=RESET)//判断是否发生了更新(溢出)中断
	 {
		 
		 if (KeyStat.stat == COMMON_STATE) {        //如果是正常状态，就正常显示，否则
						tosettime.sec++; //进行了结构体更新，但是，有可能秒数超过了60，所以，进行统一的时间更新
						update_to_time();  //更新时间
						show_num_time();//展示数字时间
						calendar_circle_clock_showtime(120,120,200,8,tosettime.hour,tosettime.min,tosettime.sec); //展示钟表时间
					}
						TIM_ClearITPendingBit(TIM3, TIM_IT_Update); //清除中断标志位
					
    }
}
