#ifndef _CLOCK__H
#define _CLOCK__H
#include "sys.h"
#include "math.h"
#define pi	3.1415926535897932384626433832795 



typedef struct {
	 int hour;	//���һ�ν���ú�����ʱ������Ϣ
	 int min;
	 int sec;
	int year;
	int month;
	int day;
	int MONTH[12];
}_tosettime;
extern _tosettime tosettime;



#define CHANGE_TIME_STATE  1   //�޸�ʱ��״̬����Ϊ1
#define COMMON_STATE       0		//���޸�ʱ��״̬����Ϊ0



#define NO_FILICKER_AT_ALL -1     //ȫ������˸״̬
#define YEAR_FILICKER   0  //�����˸
#define MONTH_FILICKER  1   //�·���˸
#define DAY_FILICKER    2   //�����˸
#define HOUR_FILICKER   3   //Сʱ��˸
#define MINUTE_FILICKER 4   //������˸
#define SECOND_FILICKER 5   //������˸


//�ӱ������
void Clock_Init(int year, int month, int day, u8 hour, u8 min, u8 sec);
//��ʱ���������
void update_to_time(void);

//��ʾ����ʱ��
void show_num_time(void);
//�̻�����
void calendar_circle_clock_drawpanel(u16 x,u16 y,u16 size,u16 d);


//����ʱ��
void settime(int year, int month, int day, u8 hour, u8 min, u8 sec);

//�̻�ָ��
void calendar_circle_clock_showtime(u16 x,u16 y,u16 size,u16 d,u8 hour,u8 min,u8 sec);

//����ʱ��
void deal_change_time(void);

//�ƶ�ָ��




#endif



