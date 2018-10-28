/*****************************************************************************
*Ten Tep          :     user_gpio.c
*Ngay             :     24/12/2015
*Tac Gia          :     MCA Team
*Cong Ty          :     MCA
*Webside          :     mca.vn
*Phien Ban        :     V1.0
*Tom Tat          :     Dinh nghia cac ham cau hinh GPIO trong STM8
******************************************************************************/

#include "user_control.h"
#if (__USER_CONTROL_H!=24122016)  
#error "Include Sai #File user_control.h"
#endif
extern Status,adc_value;
void ADC_map(adc_value)
{
  if(adc_value<10)Status=0;
  else if(10 <=adc_value<100)Status=1;
  else if(100<=adc_value<200)Status=2;
  else if(200<=adc_value<300)Status=3;
  else if(300<=adc_value<400)Status=4;
  else if(400<=adc_value<500)Status=5;
  else if(500<=adc_value<600)Status=6;
  else if(600<=adc_value<700)Status=7;
  else if(700<=adc_value<800)Status=8;
  else if(800<=adc_value<900)Status=9;
  else if(900<=adc_value<1000)Status=10;
}

/*------------------------------KET THUC FILE-------------------------------
_________________________________MCA Team__________________________________*/