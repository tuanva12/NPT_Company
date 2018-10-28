/*****************************************************************************
  *Ten Tep          :     user_timer.c
  *Ngay             :     08/01/2017
  *Tac Gia          :     MCA team
  *Cong Ty          :     MCA
  *Webside          :     mca.vn
  *Phien Ban        :     V1.0
  *Tom Tat          :     Dinh nghia cac Timer trong stm8s
  ******************************************************************************/
#include "user_timer.h"

static uint32_t Count;
/*________________________________ TIMER1 ___________________________________*/ 
void TIM1_Init_Configuration()
{
    //TIM1_DeInit();
    CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER1,ENABLE);    // Cho phep su dung nguon clock cho Timer1
    TIM1_TimeBaseInit(15,TIM1_COUNTERMODE_UP,0,0);              // Khoi tao timer 1
    //TIM1_ARRPreloadConfig(DISABLE);
    TIM1_OC1Init(TIM1_OCMODE_PWM1,TIM1_OUTPUTSTATE_ENABLE,
                 TIM1_OUTPUTNSTATE_DISABLE,0,TIM1_OCPOLARITY_HIGH,
                 TIM1_OCNPOLARITY_LOW,TIM1_OCIDLESTATE_SET,TIM1_OCNIDLESTATE_SET);
    TIM1_OC2Init(TIM1_OCMODE_PWM1,TIM1_OUTPUTSTATE_ENABLE,
                 TIM1_OUTPUTNSTATE_DISABLE,0,TIM1_OCPOLARITY_HIGH,
                 TIM1_OCNPOLARITY_LOW,TIM1_OCIDLESTATE_SET,TIM1_OCNIDLESTATE_SET);
    //TIM1_PWMIConfig(TIM1_CHANNEL_1,TIM1_ICPOLARITY_RISING,TIM1_ICSELECTION_DIRECTTI,TIM1_ICPSC_DIV1,0x00);
    //TIM1_ITConfig(TIM1_IT_UPDATE,ENABLE);                     // Chon su kien ngat update 
    TIM1_Cmd(ENABLE);                                           // cho phep chay Timer1
    TIM1_CtrlPWMOutputs(ENABLE);
}

void TIM1_PWM_Set_Freq(uint32_t Freq)
{
    Count = (1000000/Freq);         // Tinh toan gia tri nap cho thanh ghi ARR
    TIM1->ARRH = Count/256;         // Nap 8 byte cao cua bien Count vao thanh ghi ARRH
    TIM1->ARRL = Count%256;         // Nap 8 byte thap cua bien count vao thanh ghi ARRL
    TIM1_SetCompare1(Count/2);      // Cai Duty mac dinh la 50%
    TIM1_SetCompare2(Count/2);      // Cai Duty mac dinh la 50%
}

void TIM1_PWM_Set_Duty(uint8_t Duty, uint8_t Channel)
{
    uint32_t  Counter_Duty;
    
    Counter_Duty = ((uint32_t) Duty * Count/100);       // Tinh toan Duty
    switch (Channel)
    {
        case 1:                                         // Select channel 1
            TIM1_SetCompare1(Counter_Duty);             // Nap gia tri Duty vua tinh toan vao thanh ghi CCR1
            break;
        case 2: 
            TIM1_SetCompare2(Counter_Duty);             // Nap gia tri Duty vua tinh toan vao thanh ghi CCR1
            break;
        case 3: 
            TIM1_SetCompare3(Counter_Duty);             // Nap gia tri Duty vua tinh toan vao thanh ghi CCR1
            break;
        case 4: 
            TIM1_SetCompare4(Counter_Duty);             // Nap gia tri Duty vua tinh toan vao thanh ghi CCR1
            break;
    }
}

/*________________________________ TIMER2 ___________________________________*/
void TIM2_Configuration()
{
    CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER2,ENABLE);// Cho phep su dung nguon clock cho Timer2
    TIM2_ARRPreloadConfig(ENABLE);                          // Bat che do Autoreload
    TIM2_TimeBaseInit(TIM2_PRESCALER_16,100);             // Bo chia 16, thoi gian 0.1ms
    TIM2_ITConfig(TIM2_IT_UPDATE,ENABLE);                   // Chon su kien ngat update
    TIM2_Cmd(ENABLE);                                       // cho phep chay Timer2
}
/*________________________________ TIMER3 ___________________________________*/ 
void TIM3_Configuration()
{
    CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER3,ENABLE);// Cho phep su dung nguon clock cho Timer3
    TIM3_ARRPreloadConfig(ENABLE);                          // Bat che do Autoreload
    TIM3_TimeBaseInit(TIM3_PRESCALER_16, 100);            // Bo chia timer 16, thoi gia  0.1ms
    TIM3_ITConfig(TIM3_IT_UPDATE,ENABLE);                   // Chon su kien ngat update
    TIM3_Cmd(ENABLE);                                       // cho phep chay Timer3
}
/*________________________________ TIMER4 ___________________________________*/ 
void TIM4_Configuration()
{
    CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER4,ENABLE);// Cho phep su dung nguon clock cho Timer4
    TIM4_ARRPreloadConfig(ENABLE);                          // Bat che do Autoreload
    TIM4_TimeBaseInit(TIM4_PRESCALER_128, 125);             // Bo chia timer 128, thoi gia  1ms
    TIM4_ITConfig(TIM4_IT_UPDATE,ENABLE);                   // Chon su kien ngat update
    TIM4_Cmd(ENABLE);                                       // cho phep chay Timer4
}
