#include "headfile.h"


void Start_Mode(void);

unsigned char Debug = 0;



int main(void)
{
    get_clk();                 //获取时钟频率 必须执行
    FLASH_Init();              //Flash
    Transfer_Data_Init();      //运行参数传递
    uart_Init(uart1,115200);
    Motor_Init();
    Dial_Switch_Init();
    Speed_Init();
    LED_Init();
    OLED_Init();
    Start_Mode();
    adc_init(ADC0_SE6);
    EnableInterrupts;          //开启全局中断
    while(Debug)
    {
        Key_Dis();
    }
    while(1)
    {
        LED_Refresh();
        systick_delay_ms(1);
    }
}

void Start_Mode(void)              //启动模式
{  
    int Start_Mode_Value = Dial_Switch_Read();
    switch (Start_Mode_Value)
    {
    case 0:
        OLED_P6x8Str(121, 7, "0");
        OLED_P8x16Str(0, 0, "Normal Mode");
        pit_init_ms(pit0, 10);               //初始化pit0 周期设置为 X ms
        set_irq_priority(PIT_CH0_IRQn, 3);   //设置pit0优先级 0-3
        enable_irq(PIT_CH0_IRQn);            //开启pit0中断
        break;
    case 1:
        OLED_P6x8Str(121, 7, "1");
        OLED_P8x16Str(0, 0, "Test Mode");
        pit_init_ms(pit1, 10);              //初始化pit0 周期设置为 X ms
        set_irq_priority(PIT_CH1_IRQn, 3);   //设置pit0优先级 0-3
        enable_irq(PIT_CH1_IRQn);            //开启pit0中断
        break;
    case 2:
        OLED_P6x8Str(121, 7, "2");
        ResetFlash();                //重置Flash
        OLED_P8x16Str(0, 0, "Complete Reset");
        OLED_P8x16Str(0, 2, "Please Restart");
        break;
    case 3:
        OLED_P6x8Str(121, 7, "3");//参数调试模式
        Key_Init();
        Debug = 1;
        break;
    default:
        OLED_P8x16Str(0, 0, "Err");
        break;
    }
}
