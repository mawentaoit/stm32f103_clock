#include "sys.h"
#include "base.h"
#include "math.h"
#include "clock.h"
#include "lcd.h"
#include "key.h"
#include "delay.h"

void Clock_Init(int year, int month, int day, u8 hour, u8 min, u8 sec){
		settime(year, month, day, hour, min, sec);  //����ʱ��
		calendar_circle_clock_drawpanel(120,120,200,8);  //�̻�����
		calendar_circle_clock_showtime(120,120,200,8,tosettime.hour,tosettime.min,tosettime.sec);  //�̻�ָ��
		show_num_time();  //չʾ����ʱ��
}



/*����ʱ�����õ�һϵ�в����ڴ����*/

void settime(int year, int month, int day, u8 hour, u8 min, u8 sec){
int i=0;	
int const temp[12] =  {31,28,31,30,31,30,31,31,30,31,30,31};
	tosettime.hour = hour;
	tosettime.min = min;
	tosettime.sec = sec;
	tosettime.day = day;
	tosettime.month = month;
	tosettime.year = year;

	for (i=0; i<=12; i++) {
		tosettime.MONTH[i] = temp[i];
	}
	if((tosettime.year%4==0&&tosettime.year%100!=0)||(tosettime.year%400==0))   //����
		{
			tosettime.MONTH[1]=29; 
		}else tosettime.MONTH[1]=28; 
}


//��ʾ����ʱ��
void show_num_time(void) {
	POINT_COLOR = BLACK;
	LCD_ShowNum(50,240,tosettime.year,4,24);
	LCD_ShowString(100,240,5,24,24,"/");
	LCD_ShowNum(115,240,tosettime.month,2,24);
	LCD_ShowString(145,240,5,24,24,"/");
	LCD_ShowNum(160,240,tosettime.day,2,24);
	
	LCD_ShowNum(50,280,tosettime.hour,2,24);
	LCD_ShowString(75,280,5,24,24,"/");
	LCD_ShowNum(90,280,tosettime.min,2,24);
	LCD_ShowString(115,280,5,24,24,"/");
	LCD_ShowNum(130,280,tosettime.sec,2,24);
}


//��Բ��ָ�����
//x,y:�������ĵ�
//size:���̴�С(ֱ��)
//d:���̷ָ�,���ӵĸ߶�
void calendar_circle_clock_drawpanel(u16 x,u16 y,u16 size,u16 d)
{
	u16 r=size/2;//�õ��뾶 
	u16 sx=x-r;
	u16 sy=y-r;
	u16 px0,px1;
	u16 py0,py1; 
	u16 i; 
	
	
	gui_draw_arcrectangle(x-r-12,y-r-12,2*r+24,2*r+24,r/6,1,0x0000,0x0000);
	gui_fill_circle(x,y,r,WHITE);		//����Ȧ
	//gui_fill_circle(x,y,r-4,BLACK);		//����Ȧ


	for(i=0;i<60;i++)//�����Ӹ�
	{ 
		px0=sx+r+(r-4)*sin((pi/30)*i); 
		py0=sy+r-(r-4)*cos((pi/30)*i); 
		px1=sx+r+(r-d)*sin((pi/30)*i); 
		py1=sy+r-(r-d)*cos((pi/30)*i);  
		gui_draw_bline1(px0,py0,px1,py1,0,0x7497);		
	}
	for(i=0;i<12;i++)//��Сʱ��
	{ 
		px0=sx+r+(r-5)*sin((pi/6)*i); 
		py0=sy+r-(r-5)*cos((pi/6)*i); 
		px1=sx+r+(r-d)*sin((pi/6)*i); 
		py1=sy+r-(r-d)*cos((pi/6)*i);  
		gui_draw_bline1(px0,py0,px1,py1,2,0x78EF);		
	}
	for(i=0;i<4;i++)//��3Сʱ��
	{ 
		px0=sx+r+(r-5)*sin((pi/2)*i); 
		py0=sy+r-(r-5)*cos((pi/2)*i); 
		px1=sx+r+(r-d-3)*sin((pi/2)*i); 
		py1=sy+r-(r-d-3)*cos((pi/2)*i);
		
		if ( i == 0 ) {
					LCD_ShowNum(px1-5,py1+5,12,2,16);
		} else if ( i == 1) {
								LCD_ShowNum(px1-20,py1-10,i*3,2,16);
		} else if ( i == 2 ) {
								LCD_ShowNum(px1-10,py1-20,i*3,2,16);
		} else {
							LCD_ShowNum(px1,py1-10,i*3,2,16);		
		}

		gui_draw_bline1(px0,py0,px1,py1,2,YELLOW);		
	}
	gui_fill_circle(x,y,d/2,0xb222);		//������Ȧ
}
//��ʾʱ��
//x,y:�������ĵ�
//size:���̴�С(ֱ��)
//d:���̷ָ�,���ӵĸ߶�
//hour:ʱ��
//min:����
//sec:����
void calendar_circle_clock_showtime(u16 x,u16 y,u16 size,u16 d,u8 hour,u8 min,u8 sec)
{
	static u8 oldhour=0;	//���һ�ν���ú�����ʱ������Ϣ
	static u8 oldmin=0;
	static u8 oldsec=0;
	float temp;
	u16 r=size/2;//�õ��뾶 
	u16 sx=x-r;
	u16 sy=y-r;
	u16 px0,px1;
	u16 py0,py1;  
	u8 r1; 
	if(hour>11)hour-=12;
///////////////////////////////////////////////
	//���Сʱ
	r1=d/2+4;
	//�����һ�ε�����
	temp=(float)oldmin/60;
	temp+=oldhour;
	px0=sx+r+(r-3*d-40)*sin((pi/6)*temp); 
	py0=sy+r-(r-3*d-40)*cos((pi/6)*temp); 
	px1=sx+r+r1*sin((pi/6)*temp); 
	py1=sy+r-r1*cos((pi/6)*temp); 
	gui_draw_bline1(px0,py0,px1,py1,2,WHITE);
	//�������
	r1=d/2+3;
	temp=(float)oldsec/60;
	temp+=oldmin;
	//�����һ�ε�����
	px0=sx+r+(r-2*d-30)*sin((pi/30)*temp); 
	py0=sy+r-(r-2*d-30)*cos((pi/30)*temp); 
	px1=sx+r+r1*sin((pi/30)*temp); 
	py1=sy+r-r1*cos((pi/30)*temp); 
	gui_draw_bline1(px0,py0,px1,py1,1,WHITE); 
	//������� 
	r1=d/2+3;
	//�����һ�ε�����
	px0=sx+r+(r-d-25)*sin((pi/30)*oldsec); 
	py0=sy+r-(r-d-25)*cos((pi/30)*oldsec); 
	px1=sx+r+r1*sin((pi/30)*oldsec); 
	py1=sy+r-r1*cos((pi/30)*oldsec); 
	gui_draw_bline1(px0,py0,px1,py1,0,WHITE); 
///////////////////////////////////////////////
	//��ʾСʱ 
	r1=d/2+4; 
	//��ʾ�µ�ʱ��
	temp=(float)min/60;
	temp+=hour;
	px0=sx+r+(r-3*d-40)*sin((pi/6)*temp); 
	py0=sy+r-(r-3*d-40)*cos((pi/6)*temp); 
	px1=sx+r+r1*sin((pi/6)*temp); 
	py1=sy+r-r1*cos((pi/6)*temp); 
	gui_draw_bline1(px0,py0,px1,py1,2,0x0000); 
	//��ʾ���� 
	r1=d/2+3; 
	temp=(float)sec/60;
	temp+=min;
	//��ʾ�µķ���
	px0=sx+r+(r-2*d-30)*sin((pi/30)*temp); 
	py0=sy+r-(r-2*d-30)*cos((pi/30)*temp); 
	px1=sx+r+r1*sin((pi/30)*temp); 
	py1=sy+r-r1*cos((pi/30)*temp); 
	gui_draw_bline1(px0,py0,px1,py1,1,0x0000); 	
	//��ʾ����  
	r1=d/2+3;
	//��ʾ�µ�����
	px0=sx+r+(r-d-25)*sin((pi/30)*sec); 
	py0=sy+r-(r-d-25)*cos((pi/30)*sec); 
	px1=sx+r+r1*sin((pi/30)*sec); 
	py1=sy+r-r1*cos((pi/30)*sec); 
	gui_draw_bline1(px0,py0,px1,py1,0,0x0000); 
	oldhour=hour;	//����ʱ
	oldmin=min;		//�����
	oldsec=sec;		//������
}	   



void update_to_time(void){
		if (KeyStat.stat == COMMON_STATE)    //���޸�ʱ��״̬
			{
				if((tosettime.year%4==0&&tosettime.year%100!=0)||(tosettime.year%400==0))   //����
				{
					tosettime.MONTH[1]=29; 
				}else tosettime.MONTH[1]=28; 
				
				if (tosettime.sec > 59)
					{
						tosettime.sec = 0;
						tosettime.min ++;	
					}
				if (tosettime.min > 59)
					{
						tosettime.min = 0;
						tosettime.hour ++;
					}
				if (tosettime.hour > 23)
					{
						tosettime.hour = 0;
						tosettime.day++;
					}
				if(tosettime.day > tosettime.MONTH[tosettime.month-1])
					{
						tosettime.day = 1;
						tosettime.month++;
					}		
				if(tosettime.month > 12)
					{
						tosettime.month = 1;
						tosettime.year++;
					}
			}
			
		else 
			{      //�޸�ʱ��״̬
				if((tosettime.year%4==0&&tosettime.year%100!=0)||(tosettime.year%400==0))   //����
				{
					tosettime.MONTH[1]=29; 
				}else tosettime.MONTH[1]=28; 
				
				if (tosettime.sec < 0)tosettime.sec = 59;
				if (tosettime.min < 0)tosettime.min = 59;
				if (tosettime.hour < 0)tosettime.hour = 23;
				if (tosettime.day < 1)tosettime.day = tosettime.MONTH[tosettime.month-1];
				if (tosettime.month < 1)tosettime.month = 12;
							
				if (tosettime.sec > 59)tosettime.sec = 0;							
				if (tosettime.min > 59)tosettime.min = 0;
				if (tosettime.hour > 23)tosettime.hour = 0;
				if(tosettime.month > 12)tosettime.month = 1;
				if(tosettime.day > tosettime.MONTH[tosettime.month-1])tosettime.day = 1;
			}	
			
}


void deal_change_time(void){
	
	//��ѡ����ѡ�������˸
	if(KeyStat.stat == CHANGE_TIME_STATE) {
	
		if(KeyStat.choice == YEAR_FILICKER) {
			POINT_COLOR = WHITE;
			LCD_ShowNum(50,240,tosettime.year,4,24);
			POINT_COLOR = BLACK;
		}
		if (KeyStat.choice == MONTH_FILICKER) {
			POINT_COLOR = WHITE;
			LCD_ShowNum(115,240,tosettime.month,2,24);
			POINT_COLOR = BLACK;			
		}
		if (KeyStat.choice == DAY_FILICKER) {
				POINT_COLOR = WHITE;
			LCD_ShowNum(160,240,tosettime.day,2,24);
			POINT_COLOR = BLACK;			
		} 
		if (KeyStat.choice == HOUR_FILICKER) {
			POINT_COLOR = WHITE;
			LCD_ShowNum(50,280,tosettime.hour,2,24);
			POINT_COLOR = BLACK;			
		}
		if (KeyStat.choice == MINUTE_FILICKER) {
			POINT_COLOR = WHITE;
			LCD_ShowNum(90,280,tosettime.min,2,24);
			POINT_COLOR = BLACK;			
		}
		if (KeyStat.choice == SECOND_FILICKER) {
			POINT_COLOR = WHITE;
			LCD_ShowNum(130,280,tosettime.sec,2,24);
			POINT_COLOR = BLACK;			
		}
		delay_ms(400);
	} 
	
	
	if (KeyStat.Key_Value == KEY0_PRES) { //�������KEY0,��˵�������˵���ʱ��״̬
			KeyStat.Key_Value = 0;
			if (KeyStat.choice == YEAR_FILICKER) {
				tosettime.year++;
				//����ͳһ��ʱ�����
				update_to_time();
			}
			if (KeyStat.choice == MONTH_FILICKER) {
				tosettime.month++;
				update_to_time();
			}
			if (KeyStat.choice == DAY_FILICKER) {
				tosettime.day ++;
				update_to_time();
			}
			if (KeyStat.choice == HOUR_FILICKER){
				tosettime.hour ++;
				update_to_time();
			}
			if (KeyStat.choice == MINUTE_FILICKER) {
				tosettime.min ++;
				update_to_time();
			}
			if (KeyStat.choice == SECOND_FILICKER){
				tosettime.sec ++;
				update_to_time();
			}
	} else if (KeyStat.Key_Value == KEY1_PRES) {
		KeyStat.Key_Value = 0;
		switch(KeyStat.choice){
			case 0: tosettime.year--;
			update_to_time();
			break;
			case 1: tosettime.month--;
			update_to_time();
			break;
			case 2: tosettime.day--;
			update_to_time();
			break;
			case 3: tosettime.hour--;
			update_to_time();
			break;
			case 4: tosettime.min--;
			update_to_time();
			break;
			case 5: tosettime.sec--;
			update_to_time();
			break;	
		}
		
	}
	

	
	//����ʱ�Ӹ���
	show_num_time();
	calendar_circle_clock_showtime(120,120,200,8,tosettime.hour,tosettime.min,tosettime.sec);
	delay_ms(400);
}

