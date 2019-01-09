#include "headfile.h"

unsigned char LED_Buffer[4] = {0};

void LED_Init(void)
{
    //数码管
    gpio_init(E0, GPO, 1);
    gpio_init(E1, GPO, 1);
    gpio_init(G0, GPO, 1);
    gpio_init(G1, GPO, 1);
    gpio_init(G2, GPO, 1);
    gpio_init(G3, GPO, 1);
    gpio_init(E2, GPO, 1);
    gpio_init(E3, GPO, 1);
    gpio_init(C6, GPO, 1);
    gpio_init(C7, GPO, 1);
    gpio_init(A0, GPO, 1);
    gpio_init(A1, GPO, 1);
    //LED_Light
    gpio_init(I4, GPO, 1);
    gpio_init(H1, GPO, 1);
    gpio_init(H0, GPO, 1);
    gpio_init(E6, GPO, 1);
}

void LED_Single_Disp(unsigned char value)
{
    switch (value)
    {
    case 0: //0
    {
        gpio_set(E0, 0);
        gpio_set(G0, 0);
        gpio_set(E2, 0);
        gpio_set(G2, 0);
        gpio_set(G1, 0);
        gpio_set(E1, 0);
        gpio_set(E3, 1);
        gpio_set(G3, 1);
        break;
    }
    case 1: //1
    {
        gpio_set(E0, 1);
        gpio_set(G0, 0);
        gpio_set(E2, 0);
        gpio_set(G2, 1);
        gpio_set(G1, 1);
        gpio_set(E1, 1);
        gpio_set(E3, 1);
        gpio_set(G3, 1);
        break;
    }
    case 2: //2
    {
        gpio_set(E0, 0);
        gpio_set(G0, 0);
        gpio_set(E2, 1);
        gpio_set(G2, 0);
        gpio_set(G1, 0);
        gpio_set(E1, 1);
        gpio_set(E3, 0);
        gpio_set(G3, 1);
        break;
    }
    case 3: //3
    {
        gpio_set(E0, 0);
        gpio_set(G0, 0);
        gpio_set(E2, 0);
        gpio_set(G2, 0);
        gpio_set(G1, 1);
        gpio_set(E1, 1);
        gpio_set(E3, 0);
        gpio_set(G3, 1);
        break;
    }
    case 4: //4
    {
        gpio_set(E0, 1);
        gpio_set(G0, 0);
        gpio_set(E2, 0);
        gpio_set(G2, 1);
        gpio_set(G1, 1);
        gpio_set(E1, 0);
        gpio_set(E3, 0);
        gpio_set(G3, 1);
        break;
    }
    case 5: //5
    {
        gpio_set(E0, 0);
        gpio_set(G0, 1);
        gpio_set(E2, 0);
        gpio_set(G2, 0);
        gpio_set(G1, 1);
        gpio_set(E1, 0);
        gpio_set(E3, 0);
        gpio_set(G3, 1);
        break;
    }
    case 6: //6
    {
        gpio_set(E0, 0);
        gpio_set(G0, 1);
        gpio_set(E2, 0);
        gpio_set(G2, 0);
        gpio_set(G1, 0);
        gpio_set(E1, 0);
        gpio_set(E3, 0);
        gpio_set(G3, 1);
        break;
    }
    case 7: //7
    {
        gpio_set(E0, 0);
        gpio_set(G0, 0);
        gpio_set(E2, 0);
        gpio_set(G2, 1);
        gpio_set(G1, 1);
        gpio_set(E1, 1);
        gpio_set(E3, 1);
        gpio_set(G3, 1);
        break;
    }
    case 8: //8
    {
        gpio_set(E0, 0);
        gpio_set(G0, 0);
        gpio_set(E2, 0);
        gpio_set(G2, 0);
        gpio_set(G1, 0);
        gpio_set(E1, 0);
        gpio_set(E3, 0);
        gpio_set(G3, 1);
        break;
    }
    case 9: //9
    {
        gpio_set(E0, 0);
        gpio_set(G0, 0);
        gpio_set(E2, 0);
        gpio_set(G2, 0);
        gpio_set(G1, 1);
        gpio_set(E1, 0);
        gpio_set(E3, 0);
        gpio_set(G3, 1);
        break;
    }
    case 10: // -
    {
        gpio_set(E0, 1);
        gpio_set(G0, 1);
        gpio_set(E2, 1);
        gpio_set(G2, 1);
        gpio_set(G1, 1);
        gpio_set(E1, 1);
        gpio_set(E3, 0);
        gpio_set(G3, 1);
        break;
    }
    case 11: //OFF
    {
        gpio_set(E0, 1);
        gpio_set(G0, 1);
        gpio_set(E2, 1);
        gpio_set(G2, 1);
        gpio_set(G1, 1);
        gpio_set(E1, 1);
        gpio_set(E3, 1);
        gpio_set(G3, 1);
        break;
    }
    default:
        break;
    }
}

void LED_Disp(int value)
{
    if (value > 9999 || value < -999)
    {
        LED_Buffer[0] = LED_Buffer[1] = LED_Buffer[2] = LED_Buffer[3] = 10;
    }
    else
    {
        if (value >= 0)
        {
            LED_Buffer[0] = value / 1000;
            value %= 1000;
            LED_Buffer[1] = value / 100;
            value %= 100;
            LED_Buffer[2] = value / 10;
            value %= 10;
            LED_Buffer[3] = value;
        }
        else
        {
            value *= -1;
            LED_Buffer[0] = 10;
            LED_Buffer[1] = value / 100;
            value %= 100;
            LED_Buffer[2] = value / 10;
            value %= 10;
            LED_Buffer[3] = value;
        }
    }
}

void LED_Refresh(void)
{
    static unsigned char bit = 1;
    switch (bit)
    {
    case 1:
        LED_Single_Disp(11);
        gpio_set(A0, 0);
        gpio_set(C7, 1);
        gpio_set(C6, 1);
        gpio_set(A1, 1);
        LED_Single_Disp(LED_Buffer[0]);
        bit++;
        break;
    case 2:
        LED_Single_Disp(11);
        gpio_set(A0, 1);
        gpio_set(C7, 0);
        gpio_set(C6, 1);
        gpio_set(A1, 1);
        LED_Single_Disp(LED_Buffer[1]);
        bit++;
        break;
    case 3:
        LED_Single_Disp(11);
        gpio_set(A0, 1);
        gpio_set(C7, 1);
        gpio_set(C6, 0);
        gpio_set(A1, 1);
        LED_Single_Disp(LED_Buffer[2]);
        bit++;
        break;
    case 4:
        LED_Single_Disp(11);
        gpio_set(A0, 1);
        gpio_set(C7, 1);
        gpio_set(C6, 1);
        gpio_set(A1, 0);
        LED_Single_Disp(LED_Buffer[3]);
        bit = 1;
        break;
    default:
        bit = 1;
        break;
    }
}

void LED_Light(unsigned char number, unsigned char value)
{
    switch (number)
    {
    case 1:
        if (value == 0)
            GPIOC_PSOR |= 1 << 4;
        else
            GPIOC_PCOR |= 1 << 4;
        break;
    case 2:
        if (value == 0)
            GPIOB_PSOR |= 1 << 25;
        else
            GPIOB_PCOR |= 1 << 25;
        break;
    case 3:
        if (value == 0)
            GPIOB_PSOR |= 1 << 24;
        else
            GPIOB_PCOR |= 1 << 24;
        break;
    case 4:
        if (value == 0)
            GPIOB_PSOR |= 1 << 6;
        else
            GPIOB_PCOR |= 1 << 6;
        break;
    default:
        break;
    }
}