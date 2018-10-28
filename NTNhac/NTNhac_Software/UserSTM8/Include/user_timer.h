/*****************************************************************************
  *Ten Tep          :     user_timer.h
  *Ngay             :     08/01/2017
  *Tac Gia          :     MCA team
  *Cong Ty          :     MCA
  *Webside          :     mca.vn
  *Phien Ban        :     V1.0
  *Tom Tat          :     Dinh nghia cac Timer trong stm8s
  ******************************************************************************/
#ifndef _USER_TIMER_H_
#define _USER_TIMER_H_

#include "main.h"
#include "stm8s_tim1.h"
#include "stm8s_tim2.h"
#include "stm8s_tim3.h"
#include "stm8s_tim4.h"

#define CHANNEL1    1
#define CHANNEL2    2
#define CHANNEL3    3
#define CHANNEL4    4

void TIM1_Init_Configuration();
//void TIM1_PWM(unsigned long int Period, unsigned char Duty);
void TIM1_PWM_Set_Freq(uint32_t Freq);
void TIM1_PWM_Set_Duty(uint8_t Duty, uint8_t Channel);
void TIM2_Configuration();
void TIM3_Configuration();
void TIM4_Configuration();

#endif
/*------------------------------KET THUC FILE-------------------------------
 _________________________________MCA Team__________________________________*/ 


