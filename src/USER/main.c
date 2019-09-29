#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "base.h"
#include "math.h"
#include "timer.h"
#include "clock.h"
#include "exti.h"
#include "key.h"



_KeyStat KeyStat;  //全局变量，KeyStat的状态
_tosettime tosettime;  //时间结构体,记录了时间这个对象

 
int main(void)
{	

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	delay_init();
	LCD_Init();
	gui_init();
	KEY_Init();
	EXTIX_Init();
	TIM3_Init(9999,7200-1);
	Clock_Init(2019,6,12,9,30,30);
	while(1){
		deal_change_time();
	};
 }
