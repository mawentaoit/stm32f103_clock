#ifndef _BASEH_H
#define _BASEH_H

#include <string.h>
#include <sys.h>
#include <lcd.h>
//GUI-�ײ��װ,Ϊ��ʹ�ϲ�Ӧ�ø��ӱ�ݡ�
//V1.0

//��ҪLCD�����ṩ�ĸ��ײ㺯��
//1,���㺯��
//2,���㺯��
//3,��ɫ��亯��
//4,��ɫ��亯��

typedef struct 
{
	u16 back_color;  //����ɫ
	u16(*read_point) (u16,u16);  //���㺯��
	void(*draw_point) (u16,u16,u16); //���㺯��
	void(*fill) (u16,u16,u16,u16,u16);  //��亯��,Ҳ���ǻ��ߺ���
	void(*colorfill) (u16,u16,u16,u16,u16*);  //��ɫ��亯��
	u8 tbfsize;  
	u8 tbheight;
	u16 lcdwidth;
	u16 lcdheight;
}_gui_phy;
extern _gui_phy gui_phy;


u16 gui_color_chg(u32 rgb);

u16 gui_alpha_blend565(u16 src,u16 dst,u8 alpha);						//alpha blending
long long gui_pow(u8 m,u8 n);			
void gui_init(void);
void gui_draw_bigpoint(u16 x0,u16 y0,u16 color);						//�����
void gui_draw_line(u16 x0,u16 y0,u16 x1,u16 y1,u16 color);				//��������
void gui_draw_bline(u16 x1, u16 y1, u16 x2, u16 y2,u8 size,u16 color);	//��һ������
void gui_draw_bline1(u16 x0,u16 y0,u16 x1,u16 y1,u8 size,u16 color);	//��һ������,����1
void gui_draw_rectangle(u16 x0,u16 y0,u16 width,u16 height,u16 color);	//������
void gui_draw_arcrectangle(u16 x,u16 y,u16 width,u16 height,u8 r,u8 mode,u16 upcolor,u16 downcolor);//��Բ�Ǿ���
void gui_draw_vline(u16 x0,u16 y0,u16 len,u16 color);								//����ֱ��
void gui_draw_hline(u16 x0,u16 y0,u16 len,u16 color);								//��ˮƽ��
void gui_fill_colorblock(u16 x0,u16 y0,u16 width,u16 height,u16* ctbl,u8 mode);		//�����ɫ��
void gui_smooth_color(u32 srgb,u32 ergb,u16*cbuf,u16 len);							//��ɫƽ������
void gui_draw_smooth_rectangle(u16 x,u16 y,u16 width,u16 height,u32 srgb,u32 ergb);	//����ɫƽ�����ɵľ���/����
void gui_fill_rectangle(u16 x0,u16 y0,u16 width,u16 height,u16 color);				//�������
void gui_fill_circle(u16 x0,u16 y0,u16 r,u16 color);
void gui_draw_ellipse(u16 x0, u16 y0, u16 rx, u16 ry,u16 color);
void gui_fill_ellipse(u16 x0,u16 y0,u16 rx,u16 ry,u16 color);
void gui_draw_argrec(u16 x0,u16 y0,u16 width,u16 height,u16 color);
void gui_show_strmid(u16 x,u16 y,u16 width,u16 height,u16 color,u8 size,u8 *str);
void gui_show_ptchar(u16 x,u16 y,u16 xend,u16 yend,u16 offset,u16 color,u16 size,u8 chr,u8 mode);
void gui_show_ptstr(u16 x,u16 y,u16 xend,u16 yend,u16 offset,u16 color,u8 size,u8 *str,u8 mode);
void gui_show_ptstrwhiterim(u16 x,u16 y,u16 xend,u16 yend,u16 offset,u16 color,u16 rimcolor,u8 size,u8 *str);//��Ч��ʾ�ַ���
void gui_draw_icos(u16 x,u16 y,u8 size,u8 index);
void gui_draw_icosalpha(u16 x,u16 y,u8 size,u8 index);
void gui_show_num(u16 x,u16 y,u8 len,u16 color,u8 size,long long num,u8 mode);
u8* gui_num2str(u8*str,u32 num);//������תΪ�ַ���
void gui_draw_arc(u16 sx,u16 sy,u16 ex,u16 ey,u16 rx,u16 ry,u16 r,u16 color,u8 mode);
u32 gui_get_stringline(u8*str,u16 linelenth,u8 font);
void gui_show_string(u8*str,u16 x,u16 y,u16 width,u16 height,u8 font,u16 fcolor);
u16 gui_string_forwardgbk_count(u8 *str,u16 pos);
#endif



