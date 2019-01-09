#include <stdint.h>
#include "SKEAZ1284.h"


//-------------------------------------------------------------------------------------------------------------------
//  KEA128_CLOCK Ϊ 0  �ں�Ƶ�� 40M  ����Ƶ��20M   ��ʱ��Ƶ��40M
//  KEA128_CLOCK Ϊ 1  �ں�Ƶ�� 80M  ����Ƶ��40M   ��ʱ��Ƶ��80M
//-------------------------------------------------------------------------------------------------------------------
#define KEA128_CLOCK    0



void disable_wdog(void)
{
    /* WDOG->TOVAL: TOVAL=0xE803 */
    WDOG->TOVAL = WDOG_TOVAL_TOVAL(0xE803); /* Timeout value */
    /* WDOG->CS2: WIN=0,FLG=0,??=0,PRES=0,??=0,??=0,CLK=1 */
    WDOG->CS2 = WDOG_CS2_CLK(0x01);       /* 1-kHz clock source */
    /* WDOG->CS1: EN=0,INT=0,UPDATE=1,TST=0,DBG=0,WAIT=1,STOP=1 */
    WDOG->CS1 = WDOG_CS1_UPDATE_MASK |
                WDOG_CS1_TST(0x00) |
                WDOG_CS1_WAIT_MASK |
                WDOG_CS1_STOP_MASK;
}

void Start (void) 
{
    disable_wdog();

    SIM->CLKDIV = SIM_CLKDIV_OUTDIV1(0x00) | SIM_CLKDIV_OUTDIV2_MASK; //����Ԥ��Ƶϵ��
    //�л���PEEģʽ
    ICS->C2 = ICS_C2_BDIV(0x00) | ICS_C2_LP_MASK;
    OSC->CR = OSC_CR_OSCEN_MASK | OSC_CR_OSCOS_MASK | OSC_CR_RANGE_MASK | OSC_CR_HGO_MASK;
    ICS->C1 = ICS_C1_CLKS(0x00) | ICS_C1_RDIV(0x04-KEA128_CLOCK) | ICS_C1_IRCLKEN_MASK;
    while((ICS->S & ICS_S_IREFST_MASK) != 0x00U) {};    //�ȴ��ⲿʱ�ӱ�ѡ��Ϊ��׼ʱ��
    while((ICS->S & ICS_S_LOCK_MASK) == 0x00U){};       //�ȴ�FLL����
    while((ICS->S & 0x0CU) != 0x00U) {};                //�ȴ�ѡ��FLL���
    
    //SIM->SOPT0 |= SIM_SOPT0_CLKOE_MASK;                 //H2�������ʱ��
}
