/*******************************************************************************
  *Ten Tep         :     flash.h
  *Ngay            :     07/09/2016
  *Tac Gia         :     linh.mta
  *Phien Ban       :     V1.0
  *Tom Tat         :
  *
  *
  *
  *****************************************************************************/
#ifndef __FLASH_H
#define __FLASH_H
#include "stm32f1xx_hal.h"

#define FLASH_USER_START_PAGE62_ADDR 0x08058D00 //Page 62
#define FLASH_USER_START_PAGE63_ADDR 0x0805FFF0 //Page 63

uint8_t FLASH_WriteBytes(uint32_t address, uint8_t *data, uint16_t size);
void FLASH_ReadBytes(uint32_t address, uint8_t *data, uint16_t size);


#endif
