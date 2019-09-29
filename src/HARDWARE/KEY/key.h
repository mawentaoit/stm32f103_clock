#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"

 

typedef struct {
	int Key_Value; //哪个按键按下项
	int choice;//游标选择项
	int stat; 
	/*按键状态项对标时钟状态项
	普通模式或修改时间模式*/
}_KeyStat;

extern _KeyStat KeyStat;//全局变量


#define KEY0  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5)//读取按键0
#define KEY1  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15)//读取按键1
#define WK_UP   GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)//读取按键2 



#define KEY0_PRES	1		//KEY0  
#define KEY1_PRES	2		//KEY1 
#define WKUP_PRES	3		//WK_UP  

void KEY_Init(void);//IO初始化
u8 KEY_Scan(u8 mode);  	//按键扫描函数		

void Key_Stat_Init(void);
#endif
