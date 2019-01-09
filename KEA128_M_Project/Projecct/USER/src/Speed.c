#include "headfile.h"


struct PID
{
    float SetValue;
    float ActualValue;
    float Err;
    float LastErr;
    float P, I, D;
    double integral;
    double integral_max;
    double Output;
    double LastOutput;
} SpeedPWM_PID;

void Speed_Init(void)
{
    ftm_count_init(ftm1);
    gpio_init(H6, GPI, 0);
    SpeedPWM_PID.SetValue = 0.0f;
    SpeedPWM_PID.ActualValue = 0.0f;
    SpeedPWM_PID.Err = 0.0f;
    SpeedPWM_PID.LastErr = 0.0f;
    SpeedPWM_PID.LastOutput = 0.0f;

    SpeedPWM_PID.P = 100.0f;
    SpeedPWM_PID.I = 5.5f;
    SpeedPWM_PID.D = 0.0f;
    
//    SpeedPWM_PID.P = Pass_Parameter(1);
//    SpeedPWM_PID.I = Pass_Parameter(2);
//    SpeedPWM_PID.D = Pass_Parameter(3);

    SpeedPWM_PID.integral = 0.0f;
    SpeedPWM_PID.integral_max = 400 * 30;
}



int SpeedPWM_PID_Out(int SetCount)
{
    int Count = 0;
    Count = Speed_Count_Out();
    LED_Disp(Count);
    Copy_Data(Num_Speed,Count);
              
    SpeedPWM_PID.ActualValue = Count;
    SpeedPWM_PID.SetValue = SetCount;
    SpeedPWM_PID.Err = SpeedPWM_PID.SetValue - SpeedPWM_PID.ActualValue;
    
//    /*误差低通滤波*/
//    SpeedPWM_PID.LastErr *= 0.7f;
//    SpeedPWM_PID.Err *= 0.3f;
//    SpeedPWM_PID.Err += SpeedPWM_PID.LastErr;
//    SpeedPWM_PID.LastErr = SpeedPWM_PID.Err;
    
    SpeedPWM_PID.integral += SpeedPWM_PID.Err;

    if (fabs(SpeedPWM_PID.integral) > SpeedPWM_PID.integral_max)
    {
        if (SpeedPWM_PID.integral > 0)
        {
            SpeedPWM_PID.integral = SpeedPWM_PID.integral_max;
        }
        else if (SpeedPWM_PID.integral < 0)
        {
            SpeedPWM_PID.integral = -SpeedPWM_PID.integral_max;
        }
    }

    SpeedPWM_PID.Output = SpeedPWM_PID.P * SpeedPWM_PID.Err + SpeedPWM_PID.I * SpeedPWM_PID.integral + SpeedPWM_PID.D * (SpeedPWM_PID.Err - SpeedPWM_PID.LastErr);
    
    SpeedPWM_PID.LastOutput = SpeedPWM_PID.Output;
    return (int)(SpeedPWM_PID.Output);
}


int Speed_Count_ForB(int Count)
{
    char ForB = 0;
    ForB = gpio_get(H6);
    ForB = ForB ? -1 : 1;
    Count *= ForB;
    return Count;
}

int Speed_Count_Out(void)
{
    int Count = 0.0f;
    Count = ftm_count_get(ftm1);
    Count = Speed_Count_ForB(Count);
    ftm_count_clean(ftm1);
    return Count;
}

//电机PWM输出初始化
void Motor_Init(void)
{
    ftm_pwm_init(ftm2, ftm_ch0, 10 * 1000, 0);
    ftm_pwm_init(ftm2, ftm_ch1, 10 * 1000, 0);
}

void Motor_Out(int value)
{
    if (value >= 0)
    {
        ftm_pwm_duty(ftm2, ftm_ch0, value);
        ftm_pwm_duty(ftm2, ftm_ch1, 0);
    }
    else if(value < 0)
    {
        value *= -1;
        ftm_pwm_duty(ftm2, ftm_ch0, 0);
        ftm_pwm_duty(ftm2, ftm_ch1, value);
    }
}

