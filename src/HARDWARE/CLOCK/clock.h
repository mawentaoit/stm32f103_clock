#ifndef _CLOCK__H
#define _CLOCK__H
#include "sys.h"
#include "math.h"
#define pi	3.1415926535897932384626433832795 



typedef struct {
	 int hour;	//最近一次进入该函数的时分秒信息
	 int min;
	 int sec;
	int year;
	int month;
	int day;
	int MONTH[12];
}_tosettime;
extern _tosettime tosettime;



#define CHANGE_TIME_STATE  1   //修改时间状态设置为1
#define COMMON_STATE       0		//不修改时间状态设置为0



#define NO_FILICKER_AT_ALL -1     //全部不闪烁状态
#define YEAR_FILICKER   0  //年份闪烁
#define MONTH_FILICKER  1   //月份闪烁
#define DAY_FILICKER    2   //天份闪烁
#define HOUR_FILICKER   3   //小时闪烁
#define MINUTE_FILICKER 4   //分钟闪烁
#define SECOND_FILICKER 5   //秒钟闪烁


//钟表出世法
void Clock_Init(int year, int month, int day, u8 hour, u8 min, u8 sec);
//对时间进行限制
void update_to_time(void);

//显示数字时间
void show_num_time(void);
//刻画表盘
void calendar_circle_clock_drawpanel(u16 x,u16 y,u16 size,u16 d);


//设置时间
void settime(int year, int month, int day, u8 hour, u8 min, u8 sec);

//刻画指针
void calendar_circle_clock_showtime(u16 x,u16 y,u16 size,u16 d,u8 hour,u8 min,u8 sec);

//处理时间
void deal_change_time(void);

//移动指针




#endif



