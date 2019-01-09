#include "isr.h"

#define PWMOut_Max 7000


void PIT_CH0_IRQHandler(void)
{
    PIT_FlAG_CLR(pit0);
    //int Speed_Set = (int)Pass_Parameter(4);
    int Speed_Set = 150;
    int PWM_Out = 0;
    PWM_Out = SpeedPWM_PID_Out(Speed_Set);
    PWM_Out = fabs(PWM_Out) > PWMOut_Max ? PWM_Out > 0 ? PWMOut_Max : -PWMOut_Max : PWM_Out;
    Motor_Out(PWM_Out);
    //Bluetooth(2);
}

void PIT_CH1_IRQHandler(void)
{
    PIT_FlAG_CLR(pit1);
    int ADC_value = 0;
//    static int PWM_Out = 0;
//    static unsigned char Out_flag = 0;
//    int Count = Speed_Count_Out();
//    
//    if(PWM_Out > 5000)
//    {
//        Out_flag = 1;
//    }
//    else if(PWM_Out < -5000)
//    {
//        Out_flag = 0;
//    } 
//    if(Out_flag == 0)
//    {
//        PWM_Out += 10;
//    }
//    else if(Out_flag == 1)
//    {
//        PWM_Out -= 10;
//    }
//    LED_Disp(Count);
    for(int i = 0; i < 10; i++)
    {
        ADC_value += adc_once(ADC0_SE6,ADC_12bit);
    }
    ADC_value *= 0.1571;
    
    LED_Disp(ADC_value);
    
    Motor_Out(-4000);
}

void KBI0_IRQHandler(void)
{
    volatile unsigned long int flag = 0;
    flag = READ_KBI0_FLAG;
    switch (flag)
    {
    case K5:
        Key_Menu_Up();
        break;
    case K3:
        Key_Menu_Dn();
        break;
    case K2:
        Key_Value_Up();
        break;
    case K1:
        Key_Value_Dn();
        break;
    default:
        break;
    }
    CLEAN_KBI0_FLAG;
}



/*
中断函数名称，用于设置对应功能的中断函数
Sample usage:当前启用了周期定时器 通道0得中断
void PIT_CH0_IRQHandler(void)
{
    ;
}
记得进入中断后清除标志位

void IRQ_IRQHandler(void)
{
    CLEAR_IRQ_FLAG;
    
}


void KBI0_IRQHandler(void)
{
    CLEAN_KBI0_FLAG;
    
}



void PIT_CH0_IRQHandler(void)
{
    PIT_FlAG_CLR(pit0);
    
}


FTMRE_IRQHandler      
PMC_IRQHandler        
IRQ_IRQHandler        
I2C0_IRQHandler       
I2C1_IRQHandler       
SPI0_IRQHandler       
SPI1_IRQHandler       
UART0_IRQHandler 
UART1_IRQHandler 
UART2_IRQHandler 
ADC0_IRQHandler       
ACMP0_IRQHandler      
FTM0_IRQHandler       
FTM1_IRQHandler       
FTM2_IRQHandler       
RTC_IRQHandler        
ACMP1_IRQHandler      
PIT_CH0_IRQHandler    
PIT_CH1_IRQHandler    
KBI0_IRQHandler       
KBI1_IRQHandler       
Reserved26_IRQHandler 
ICS_IRQHandler        
WDG_IRQHandler        
PWT_IRQHandler        
MSCAN_Rx_IRQHandler   
MSCAN_Tx_IRQHandler   
*/



