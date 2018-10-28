/*****************************************************************************
  *Ten Tep          :     user_delay.h
  *Ngay             :     28/06/2014
  *Tac Gia          :     MCA Team
  *Cong Ty          :     MCA
  *Webside          :     mca.vn
  *Phien Ban        :     V1.0
  *Tom Tat          :     Dinh nghia cac ham tao delay trong STM8
  ******************************************************************************/

#ifndef __USER_DELAY_H
#define __USER_DELAY_H    28062014

#include "main.h"

/*******************************************************************************
Noi Dung    :   Ham tao tre us.
Tham Bien   :   x: Thoi gian tre.
Tra Ve      :   Khong.
*******************************************************************************/

void delay_us(uint16_t x);

/*******************************************************************************
Noi Dung    :   Ham tao tre ms.
Tham Bien   :   x: Thoi gian tre.
Tra Ve      :   Khong.
*******************************************************************************/

void delay_ms(uint16_t x);

#endif

/*------------------------------KET THUC FILE-------------------------------
 _________________________________MCA Team__________________________________*/ 