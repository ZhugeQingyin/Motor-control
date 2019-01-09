#include "KEA128_gpio.h"


static FGPIO_Type * const GPIOX[] = FGPIO_BASES;


//-------------------------------------------------------------------------------------------------------------------
//  @brief      gpio 初始化
//  @param      ptx_n           选择的引脚   
//  @param      ddr             引脚方向    GPI：输入 GPO：输出
//  @param      dat             引脚输出数据（如果设置为输出）
//  @return     void
//  @since      v2.0
//  Sample usage:               gpio_init(A5,GPO,0);   //初始化A5为gpio模式，设置为输出模式，初始化输出低电平
//-------------------------------------------------------------------------------------------------------------------
void gpio_init(PTX_n ptx_n, GPIO_MOD ddr, uint8 dat)
{
    vuint8 ptx,ptn;
    uint32 temp;
    
    ptx = PTX(ptx_n);//记录模块号    //A,B......
    ptn = PTn(ptx_n);//记录引脚号    //0,1,2,3......
    
    if(GPI == ddr)
    {
        temp = GPIOX[ptx]->PIDR;
        temp &= ~((uint32)1<<ptn);
        GPIOX[ptx]->PIDR = temp;    //取消输入禁用
        
        temp = GPIOX[ptx]->PDDR;    
        temp &= ~((uint32)1<<ptn);
        GPIOX[ptx]->PDDR = temp;    //设置为输入模式
    }
    else
    {
        temp = GPIOX[ptx]->PIDR;
        temp |= ((uint32)1<<ptn);
        GPIOX[ptx]->PIDR = temp;    //输入禁用
        
        temp = GPIOX[ptx]->PDDR;    
        temp |= ((uint32)1<<ptn);
        GPIOX[ptx]->PDDR = temp;    //设置为输出模式
        
        temp = GPIOX[ptx]->PDOR;    
        temp &= ~((uint32)1<<ptn);
        temp |=  (uint32)dat<<ptn;
        GPIOX[ptx]->PDOR = temp;    //设置端口状态
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      设置引脚方向
//  @param      ptx_n           选择的引脚   
//  @param      ddr             引脚方向    GPI：输入 GPO：输出
//  @return     void
//  @since      v2.0
//  Sample usage:               gpio_ddr(A5,GPO);   //设置A5为输出模式
//-------------------------------------------------------------------------------------------------------------------
void gpio_ddr(PTX_n ptx_n, GPIO_MOD ddr)
{
    vuint8 ptx,ptn;
    uint32 temp;
    
    ptx = PTX(ptx_n);//记录模块号    //A,B......
    ptn = PTn(ptx_n);//记录引脚号    //0,1,2,3......
    
    if(GPI == ddr)
    {
        temp = GPIOX[ptx]->PIDR;
        temp &= ~((uint32)1<<ptn);
        GPIOX[ptx]->PIDR = temp;    //取消输入禁用
        
        temp = GPIOX[ptx]->PDDR;    
        temp &= ~((uint32)1<<ptn);
        GPIOX[ptx]->PDDR = temp;    //设置为输入模式
    }
    else
    {
        temp = GPIOX[ptx]->PIDR;
        temp |= ((uint32)1<<ptn);
        GPIOX[ptx]->PIDR = temp;    //输入禁用
        
        temp = GPIOX[ptx]->PDDR;    
        temp |= ((uint32)1<<ptn);
        GPIOX[ptx]->PDDR = temp;    //设置为输出模式
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      读取引脚状态
//  @param      ptx_n           选择的引脚   
//  @return     管脚的状态      1为高电平，0为低电平
//  @since      v2.0
//  Sample usage:               uint8 status = gpio_get(A5);   //读取A5为状态
//-------------------------------------------------------------------------------------------------------------------
uint8 gpio_get(PTX_n ptx_n)
{
    vuint8 ptx,ptn;
    uint32 temp;
    
    ptx = PTX(ptx_n);//记录模块号    //A,B......
    ptn = PTn(ptx_n);//记录引脚号    //0,1,2,3......
    
    //设置端口状态
    temp = GPIOX[ptx]->PDIR;
    return ( (temp >> ptn) & 0x1 );
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      设置引脚状态
//  @param      ptx_n           选择的引脚   
//  @param      dat             1为高电平，0为低电平
//  @return     void
//  @since      v2.0
//  Sample usage:               gpio_set(A5,0);   //设置A5为低电平
//-------------------------------------------------------------------------------------------------------------------
void gpio_set(PTX_n ptx_n, uint8 dat)
{
    vuint8 ptx,ptn;
    uint32 temp;
    
    ptx = PTX(ptx_n);//记录模块号    //A,B......
    ptn = PTn(ptx_n);//记录引脚号    //0,1,2,3......
    
    //设置端口状态
    temp = GPIOX[ptx]->PDOR;    
    temp &= ~((uint32)1<<ptn);
    temp |=  (uint32)dat<<ptn;
    GPIOX[ptx]->PDOR = temp;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      翻转引脚状态
//  @param      ptx_n           选择的引脚   
//  @return     void
//  @since      v2.0
//  Sample usage:               gpio_turn(A5);   //翻转A5
//-------------------------------------------------------------------------------------------------------------------
void gpio_turn(PTX_n ptx_n)
{
    vuint8 ptx,ptn;
    uint32 temp;
    
    ptx = PTX(ptx_n);//记录模块号    //A,B......
    ptn = PTn(ptx_n);//记录引脚号    //0,1,2,3......
    
    //设置端口状态
    temp = GPIOX[ptx]->PTOR;
    temp |= (uint32)(1<<ptn);
    GPIOX[ptx]->PTOR = temp;
}

