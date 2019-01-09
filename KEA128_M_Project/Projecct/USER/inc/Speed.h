#ifndef _Speed_h
#define _Speed_h

void Speed_Init(void);
int Speed_Count_ForB(int Count);
int Speed_Count_Out(void);
int SpeedPWM_PID_Out(int SetCount);
void Motor_Init(void);
void Motor_Out(int value);
#endif