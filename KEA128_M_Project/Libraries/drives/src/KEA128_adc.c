#include "KEA128_adc.h"




//-------------------------------------------------------------------------------------------------------------------
//  @brief      ADC初始化
//  @param      adcn_ch         选择ADC通道
//  @return     void
//  @since      v2.0
//  Sample usage:               adc_init(ADC0_SE8);
//-------------------------------------------------------------------------------------------------------------------
void adc_init(ADCn_Ch adcn_ch)
{
    SIM->SCGC |= SIM_SCGC_ADC_MASK;         //开启ADC时钟
    
    ADC->APCTL1 |= 1<<adcn_ch;              //使能ADC引脚
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      ADC采集
//  @param      adcn_ch         选择ADC通道
//  @param      bit             选择精度ADC_8bit
//  @return     void
//  @since      v2.0
//  Sample usage:               uint16 dat = adc_once(ADC0_SE8,ADC_12bit);//采集ADC0_SE8电压，精度12位
//-------------------------------------------------------------------------------------------------------------------
uint16 adc_once(ADCn_Ch adcn_ch, ADC_nbit bit)
{
    uint16 result;
    ADC->SC3 = (0
                | ADC_SC3_ADIV(0)           //分频系数
                | ADC_SC3_MODE(bit)         //分辨率
                | ADC_SC3_ADICLK(0)         //使用总线时钟最为ADC得时钟源
                );
        
    
    ADC->SC2 = ADC_SC2_REFSEL(0);           //基准电压选择

    ADC->SC1 = ADC_SC1_ADCH(adcn_ch);       //启动转换
    
    while(!(ADC->SC1 & ADC_SC1_COCO_MASK)); //等待转换完成
    result = ADC->R;
    return (result & ADC_R_ADR_MASK);       //返回结果
    
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ADC停止采集
//  @param      adcn_ch         选择ADC通道
//  @param      bit             选择精度ADC_8bit
//  @return     void
//  @since      v2.0
//  Sample usage:               adc_stop(adc0);
//-------------------------------------------------------------------------------------------------------------------
void adc_stop(void)
{
    ADC->SC1 = ADC_SC1_ADCH(0xFF); 
}
