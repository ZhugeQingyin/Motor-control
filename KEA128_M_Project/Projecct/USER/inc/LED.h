#ifndef _LED_h
#define _LED_h
//LED类IO初始化
void LED_Init(void);
//数码管
void LED_Single_Disp(unsigned char value);
void LED_Disp(int value);
void LED_Refresh(void);
//LED灯
void LED_Light(unsigned char number, unsigned char value);

#endif