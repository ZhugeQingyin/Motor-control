#include "headfile.h"

typedef union {
    float fdata;
    unsigned long ldata;
} FloatLongType;

struct KEY
{
    unsigned char Menu;
    unsigned char Menu_Up;
    unsigned char Menu_Dn;
    unsigned char Value_Up;
    unsigned char Value_Dn;
} KEY_Flag;

struct Parameter
{
    float Speed_P;
    float Speed_I;
    float Speed_D;  
    float Speed_VAL;
} Transfer_Data;

struct DATA
{
    int Speed;       // 1
    int Current;     // 2
} Run_Data;


void Transfer_Data_Init(void)
{
    unsigned char temp;
    temp = flash_read(254, 0, unsigned char);
    if (temp == 0xFF)
    {
        Transfer_Data.Speed_P = 0.0f;
        Transfer_Data.Speed_I = 0.0f;
        Transfer_Data.Speed_D = 0.0f;
        Transfer_Data.Speed_VAL = 0.0f;
        WriteFlash();
        temp = 0;
        FLASH_EraseSector(254);
        FLASH_WriteSector(254, (const uint8 *)&temp, 1, 0);
    }
    else
    {
        ReadFlash();
    }
}

float Pass_Parameter(unsigned char Num)
{
    switch (Num)
    {
    case 1:
        return Transfer_Data.Speed_P;
    case 2:
        return Transfer_Data.Speed_I;
    case 3:
        return Transfer_Data.Speed_D;
    case 4:
        return Transfer_Data.Speed_VAL;
    default:
        return 0.0f;
    }
}

void Run_Data_Init(void)
{
    Run_Data.Speed = 0;
    Run_Data.Current = 0;
} 

void Copy_Data(unsigned int Num, int value)
{
    switch (Num)
    {
    case 1:
        Run_Data.Speed = value;
        break;
    case 2:
        Run_Data.Current = value;
        break;
    default:
        break;
    }
}




void Bluetooth(unsigned char mode)
{
    switch(mode)
    {
    case 1:
        Send_1();
        break;
    case 2:
        Send_2();
        break;
    default:
        break;
    }
}

void Send_1(void)
{
    uint8 cmdf[2] = {CMD_WARE, ~CMD_WARE}; //串口调试 使用的前命令
    uint8 cmde[2] = {~CMD_WARE, CMD_WARE}; //串口调试 使用的后命令
    int16 t1 = Run_Data.Speed;
    int16 t2 = Run_Data.Current;

    uint8 byte1[2] = {0};
    uint8 byte2[2] = {0};

    byte1[0] = (unsigned char)t1;
    byte1[1] = (unsigned char)(t1 >> 8);

    byte2[0] = (unsigned char)t2;
    byte2[1] = (unsigned char)(t2 >> 8);

    uart_putbuff(uart1,&cmdf[0],sizeof(cmdf));
    uart_putbuff(uart1,&byte1[0],sizeof(byte1));
    uart_putbuff(uart1,&byte2[0],sizeof(byte2));
    uart_putbuff(uart1,&cmde[0],sizeof(cmde));
    
}

void Send_Data(int value)
{
    uint8 temp_value[3] = {0};
    sprintf((char*)temp_value, "%d", value);
    uart_putbuff(uart1,&temp_value[0],sizeof(temp_value)); 
}

void Send_2(void)
{
    Send_Data(Run_Data.Speed);
    uart_putstr(uart1,"\r\n");
}


void Dial_Switch_Init(void)
{   
    gpio_init(E5,GPI,0);
    gpio_init(B5,GPI,0);
}

void Key_Init(void)
{
    KEY_Flag.Menu = 1;
    KEY_Flag.Menu_Up = 0;
    KEY_Flag.Menu_Dn = 0;
    KEY_Flag.Value_Up = 0;
    KEY_Flag.Value_Dn = 0;
  
    kbi_init(KBI0_P19, IRQ_FALLING_LOW);
    kbi_init(KBI0_P18, IRQ_FALLING_LOW);
    kbi_init(KBI0_P31, IRQ_FALLING_LOW);
    kbi_init(KBI0_P30, IRQ_FALLING_LOW);
    set_irq_priority(KBI0_IRQn, 1);
    enable_irq(KBI0_IRQn);
}

unsigned char Dial_Switch_Read(void)
{
    unsigned char key_0 = 0;
    unsigned char key_1 = 0;
    unsigned char out = 0;
    
    key_0 = gpio_get(E5);
    key_1 = gpio_get(B5);

    out = key_0 | (key_1 << 1);

    return out;
}

//按键中断响应
void Key_Menu_Up(void)
{
    KEY_Flag.Menu_Up = 1;
}

void Key_Menu_Dn(void)
{
    KEY_Flag.Menu_Dn = 1;
}

void Key_Value_Up(void)
{
    KEY_Flag.Value_Up = 1;
}

void Key_Value_Dn(void)
{
    KEY_Flag.Value_Dn = 1;
}

//按键加减实现
char Key_value_UpDn(void)
{
    if (KEY_Flag.Value_Up == 1)
    {
        KEY_Flag.Value_Up = 0;
        return 1;
    }
    if (KEY_Flag.Value_Dn == 1)
    {
        KEY_Flag.Value_Dn = 0;
        return -1;
    }
    return 0;
}

//调试界面
void Key_Dis(void)
{
    if (KEY_Flag.Menu_Up == 1)
    {
        if (KEY_Flag.Menu <= 4)
        {
            KEY_Flag.Menu++;
        }
        KEY_Flag.Menu_Up = 0;
    }
    if (KEY_Flag.Menu_Dn == 1)
    {
        if (KEY_Flag.Menu > 1)
        {
            KEY_Flag.Menu--;
        }
        KEY_Flag.Menu_Dn = 0;
    }
    
    switch (KEY_Flag.Menu)
    {
    case 1:
        OLED_P8x16Str(0, 0, "Speed_P  ");
        OLED_Print_Num(0, 2, (unsigned int)Transfer_Data.Speed_P);
        Transfer_Data.Speed_P += (1.0f * Key_value_UpDn());
        break;
    case 2:
        OLED_P8x16Str(0, 0, "Speed_I  ");
        OLED_Print_Num(0, 2, (unsigned int)Transfer_Data.Speed_I);
        Transfer_Data.Speed_I += (1.0f * Key_value_UpDn());
        break;
    case 3:
        OLED_P8x16Str(0, 0, "Speed_D  ");
        OLED_Print_Num(0, 2, (unsigned int)Transfer_Data.Speed_D);
        Transfer_Data.Speed_D += (1.0f * Key_value_UpDn());
        break;
    case 4:
        OLED_P8x16Str(0, 0, "Speed_VAL");
        OLED_Print_Num(0, 2, (unsigned int)Transfer_Data.Speed_VAL);
        Transfer_Data.Speed_VAL += (0.01f * Key_value_UpDn());
        break;
    default:
        WriteFlash();
        KEY_Flag.Menu = 1;
        break;
    }
}    





//将浮点数f转化为4个字节数据存放在byte[4]中
void Float_to_Byte(float f, unsigned char byte[]) 
{
    FloatLongType fl;
    fl.fdata = f;
    byte[0] = (unsigned char)fl.ldata;
    byte[1] = (unsigned char)(fl.ldata >> 8);
    byte[2] = (unsigned char)(fl.ldata >> 16);
    byte[3] = (unsigned char)(fl.ldata >> 24);
}

//将4个字节数据byte[4]转化为浮点数存放在*f中
void Byte_to_Float(float *f, unsigned char byte[]) 
{
    FloatLongType fl;
    fl.ldata = 0;
    fl.ldata = byte[3];
    fl.ldata = (fl.ldata << 8) | byte[2];
    fl.ldata = (fl.ldata << 8) | byte[1];
    fl.ldata = (fl.ldata << 8) | byte[0];
    *f = fl.fdata;
}

//写Flash
void WriteFlash(void)
{
    unsigned char Data_Flash[16] = {0};
    unsigned char Temp[4] = {0};

    Float_to_Byte(Transfer_Data.Speed_P, Temp);
    for (unsigned char i = 0; i < 4; i++)
    {
        Data_Flash[0 + i] = Temp[i];
    }

    Float_to_Byte(Transfer_Data.Speed_I, Temp);
    for (unsigned char i = 0; i < 4; i++)
    {
        Data_Flash[4 + i] = Temp[i];
    }

    Float_to_Byte(Transfer_Data.Speed_D, Temp);
    for (unsigned char i = 0; i < 4; i++)
    {
        Data_Flash[8 + i] = Temp[i];
    }

    Float_to_Byte(Transfer_Data.Speed_VAL, Temp);
    for (unsigned char i = 0; i < 4; i++)
    {
        Data_Flash[12 + i] = Temp[i];
    }

    FLASH_EraseSector(255);
    FLASH_WriteSector(255, (const uint8 *)Data_Flash, 16, 0);
}

//读Flash
void ReadFlash(void)
{
    Transfer_Data.Speed_P = flash_read(255, 0, float);
    Transfer_Data.Speed_I = flash_read(255, 4, float);
    Transfer_Data.Speed_D = flash_read(255, 8, float);
    Transfer_Data.Speed_VAL = flash_read(255, 12, float);
}

//重置Flash
void ResetFlash(void)
{
    unsigned char temp = 0xFF;
    FLASH_EraseSector(254);
    FLASH_WriteSector(254, (const uint8 *)&temp, 1, 0);
}
