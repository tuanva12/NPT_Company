/*****************************************************************************
  *Ten Tep          :     user_uart1.c
  *Ngay             :     27/01/2016
  *Tac Gia          :     MCA Team
  *Cong Ty          :     MCA
  *Webside          :     MCA.vn
  *Phien Ban        :     V1.0
  *Tom Tat          :     Dinh nghia cac ham cau hinh UART1 trong STM8F003
  ******************************************************************************/

#include "user_adc.h"
#if (__USER_ADC_H!=11022017)  
    #error "Include Sai #File user_adc.h"
#endif


/*******************************************************************************
Noi Dung    :   Cau hinh ADC1.
Tham Bien   :   Khong.
Tra Ve      :   Khong.
*******************************************************************************/
void ADC1_Config(void)
{
    ADC1_DeInit();
    ADC1_ConversionConfig(ADC1_CONVERSIONMODE_SINGLE,ADC1_CHANNEL_5,ADC1_ALIGN_RIGHT);
//    ADC1_DataBufferCmd(DISABLE);
    ADC1_PrescalerConfig(ADC1_PRESSEL_FCPU_D2);
//    ADC1_ITConfig(ADC1_IT_EOCIE,ENABLE); //NGAT ADC
    ADC1_Cmd(ENABLE);
}
/*------------------------------KET THUC FILE-------------------------------
 _________________________________MCA Temp_________________________________*/