/*****************************************************************************
*Ten Tep          :     main.c
*Ngay             :     24/12/2016
*Tac Gia          :     MCA team
*Cong Ty          :     MCA
*Webside          :     mca.vn
*Phien Ban        :     V1.0
*Tom Tat          :     Lap trinh su dung GPIO trong STM8S105C4T6
******************************************************************************/

#include "main.h"
#include "var.h"

#if (__MAIN_H!=24122016)
#error "Include Sai File main.h"
#endif

uint16_t music_on=0; // nhan biet co nhac thi on cong OUT1

uint16_t count = 0;
/***********************************************************************/
#pragma vector = TIM2_OVR_UIF_vector   /* Symbol from I/O */
__interrupt void NGATTIMER2(void)
{
    TIM2_ClearFlag(TIM2_FLAG_UPDATE);
    dem2++;
    ADC1_ConversionConfig(ADC1_CONVERSIONMODE_SINGLE,ADC1_CHANNEL_5,ADC1_ALIGN_RIGHT);
    ADC1_StartConversion();
    adc2 = ADC1_GetConversionValue();
    if(adc2>Value2)
    {
        Value2=adc2;
    }
    if(dem2==50)
    {

        Gtri=Value2;
        //OUT1 = 1;
        if(Gtri > 5)OUT1 = 0;
        dem2=0;
        Value2=0;
    }

    ///////
    count ++;
    if(count == 1000)
    {
        music_on = 0;
        count = 0;
    }
}
#pragma vector = TIM4_OVR_UIF_vector   /* Symbol from I/O */   //xem datasheet phan 7 Interrupt vector mapping de biet vector ngat
__interrupt void NGATTIMER4(void)
{
    TIM4_ClearFlag(TIM4_FLAG_UPDATE);
    dem4++;
    ADC1_ConversionConfig(ADC1_CONVERSIONMODE_SINGLE,ADC1_CHANNEL_6,ADC1_ALIGN_RIGHT);
    ADC1_StartConversion();
    delay = ADC1_GetConversionValue();
    IWDG_ReloadCounter();
}



#pragma vector = 8   /* Symbol from I/O */   //xem datasheet phan 7 Interrupt vector mapping de biet vector ngat
__interrupt void PORT_D(void)
{
    count = 0;
    music_on = 1;
}


void main(void)
{
    /********************************* SYSTEM *************************************/
    CLK_HSICmd(ENABLE);                        // Cho phep su dung nguon Clock HSI
    CLK_SYSCLKConfig(CLK_PRESCALER_HSIDIV1);   // Su dung nguon Clock co F = 16MHz
    /*________________________________ GPIO ___________________________________*/
    GPIO_Configuration();
      EXTI_DeInit();
      EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOD,EXTI_SENSITIVITY_FALL_ONLY);
    /*________________________________ USER ___________________________________*/


    /********************************* TIMER *************************************/
    /*________________________________ TIMER1 ___________________________________*/
    ADC1_Config();

    /*________________________________ TIMER2 ___________________________________*/
    TIM2_Configuration();
    /*________________________________ TIMER3 ___________________________________*/

    /*________________________________ TIMER4 ___________________________________*/
    TIM4_Configuration();

    IWDG_Configuration();
    enableInterrupts();

    while(1)
    {
        delay=delay+10;
        Status=(Gtri)/10;
        switch (Status)
        {
        case 0:
            {
                OUT2=OUT3=OUT4=OUT5=OUT6=OUT7=OUT8=OUT9=OUT10=1;
                if(Gtri < 8)
                {
                    OUT1 = 1;
                }
                break;
            }
        case 1:
            {
                OUT1=0;
                OUT2=OUT3=OUT4=OUT5=OUT6=OUT7=OUT8=OUT9=OUT10=1;
                break;
            }
        case 2:
            {
                OUT1=OUT2=0;
                OUT3=OUT4=OUT5=OUT6=OUT7=OUT8=OUT9=OUT10=1;
                break;
            }
        case 3:
            {
                OUT1=OUT2=OUT3=0;
                OUT4=OUT5=OUT6=OUT7=OUT8=OUT9=OUT10=1;
                break;
            }
        case 4:
            {
                OUT1=OUT2=OUT3=OUT4=0;
                OUT5=OUT6=OUT7=OUT8=OUT9=OUT10=1;
                break;
            }
        case 5:
            {
                OUT1=OUT2=OUT3=OUT4=OUT5=0;
                OUT6=OUT7=OUT8=OUT9=OUT10=1;
                break;
            }
        case 6:
            {
                OUT1=OUT2=OUT3=OUT4=OUT5=OUT6=0;
                OUT7=OUT8=OUT9=OUT10=1;
                break;
            }
        case 7:
            {
                OUT1=OUT2=OUT3=OUT4=OUT5=OUT6=OUT7=0;
                OUT8=OUT9=OUT10=1;
                break;
            }
        case 8:
            {
                OUT1=OUT2=OUT3=OUT4=OUT5=OUT6=OUT7=OUT8=0;
                OUT9=OUT10=1;
                break;
            }
        case 9:
            {
                OUT1=OUT2=OUT3=OUT4=OUT5=OUT6=OUT7=OUT8=OUT9=0;
                OUT10=1;
                break;
            }
        case 10:
            {
                OUT1=OUT2=OUT3=OUT4=OUT5=OUT6=OUT7=OUT8=OUT9=OUT10=0;
                break;
            }
        }
        delay_ms(delay);
    }

}

/*------------------------------KET THUC FILE-------------------------------
_________________________________MCA Team__________________________________*/