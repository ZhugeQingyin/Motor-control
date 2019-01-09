#ifndef _Interaction_h
#define _Interaction_h

#define K5 0xFFF7FFFF 
#define K3 0xFFFBFFFF 
#define K2 0x7FFFFFFF 
#define K1 0xBFFFFFFF

#define CMD_WARE 3

#define Num_Speed 1
#define Num_Current 2

void Key_Init(void);
void Dial_Switch_Init(void);
unsigned char Dial_Switch_Read(void);
void Key_Menu_Up(void);
void Key_Menu_Dn(void);
void Key_Value_Up(void);
void Key_Value_Dn(void);
char Key_value_UpDn(void);
void Key_Dis(void);

void Float_to_Byte(float f, unsigned char byte[]);
void Byte_to_Float(float *f, unsigned char byte[]);
void ReadFlash(void);
void WriteFlash(void);
void ResetFlash(void);

void Transfer_Data_Init(void);
void Copy_Data(unsigned int Num, int value);
float Pass_Parameter(unsigned char Num);


void Send_Data(int value);
void Send_1(void);
void Send_2(void);
void Bluetooth(unsigned char mode);

#endif
