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

#define FLASH_USER_START_PAGE62_ADDR 0x0800F800 //Page 62
#define FLASH_USER_START_PAGE63_ADDR 0x0800FC00 //Page 63


void FLASH_Erase_Sector(uint32_t Address);

void FLASH_Erase_Multi_Sector(uint32_t Address,uint8_t NumSector);

void FLASH_Write_HalfWord(uint32_t Address, uint8_t* data);
void FLASH_WriteBytes(uint32_t address, uint8_t *data, uint16_t size);


void FLASH_ReadBytes(uint32_t address, uint8_t *data, uint16_t size);



#endif
