#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"

 

typedef struct {
	int Key_Value; //�ĸ�����������
	int choice;//�α�ѡ����
	int stat; 
	/*����״̬��Ա�ʱ��״̬��
	��ͨģʽ���޸�ʱ��ģʽ*/
}_KeyStat;

extern _KeyStat KeyStat;//ȫ�ֱ���


#define KEY0  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5)//��ȡ����0
#define KEY1  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15)//��ȡ����1
#define WK_UP   GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)//��ȡ����2 



#define KEY0_PRES	1		//KEY0  
#define KEY1_PRES	2		//KEY1 
#define WKUP_PRES	3		//WK_UP  

void KEY_Init(void);//IO��ʼ��
u8 KEY_Scan(u8 mode);  	//����ɨ�躯��		

void Key_Stat_Init(void);
#endif
