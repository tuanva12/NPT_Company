/*****************************************************************************
*Ten Tep          :     user_delay.c
*Ngay             :     28/06/2014
*Tac Gia          :     MCA Team
*Cong Ty          :     MCA
*Webside          :     mca.vn
*Phien Ban        :     V1.0
*Tom Tat          :     Dinh nghia cac ham tao delay trong STM8
******************************************************************************/

#include "stepper.h"
extern uint8_t dir;
extern uint8_t state;
extern uint8_t mode;
extern uint32_t dem;
/*******************************************************************************
Noi Dung    :   Ham tao tre us.
Tham Bien   :   x: Thoi gian tre.
Tra Ve      :   Khong.
*******************************************************************************/
void phase_out (uint8_t byte)
{
  (byte & 0x01) ? (BIB= HIGH) : (BIB= LOW);
  (byte & 0x02) ? (BIA= HIGH) : (BIA= LOW);
  (byte & 0x04) ? (AIB= HIGH) : (AIB= LOW);
  (byte & 0x08) ? (AIA= HIGH) : (AIA= LOW);
}

void state_machine (void){
  switch (state) {
  case 0:
    {
      phase_out(0x08); //0b00001000
      if (mode) 
      {if (dir){state=1;} else {state = 7;}} else {if (dir){state=2;} else {state = 6;}}
      break;
    }
  case 1:
    {
      phase_out(0x0A);//0b00001010
      if (dir){state=2;} else {state = 0;}
      break;
    }
  case 2:
    {
      phase_out(0X02);  //0b00000010
      if (mode) {if (dir){state=3;} else {state = 1;}} else {if (dir){state=4;} else {state = 0;}}
      break;
    }
  case 3:
    {
      phase_out(0x06); //0b00000110
      if (dir){state=4;} else {state = 2;}
      break;
    }
  case 4:
    {
      phase_out(0x04);//0b00000100
      if (mode) {if (dir){state=5;} else {state = 3;}} else {if (dir){state=6;} else {state = 2;}}
      break;
    }
  case 5:
    {
      phase_out(0x05);//0b00000101
      if(dir){state=6;} else {state = 4;}
      break;
    }
  case 6:
    {
      phase_out(0x01);//0b00000001
      if(mode) {if(dir){state=7;} else {state = 5;}} else {if (dir){state=0;} else {state = 4;}}
      break;
    }
  case 7:
    {
      phase_out(0x09);//0b00001001
      if (dir){state=0;} else {state = 6;}
      break;
    }
  default:
    state = 0;
  }
}
  
  /*------------------------------KET THUC FILE-------------------------------
  _________________________________MCA Team__________________________________*/ 
  