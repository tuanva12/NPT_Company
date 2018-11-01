/*******************************************************************************
  *Ten Tep         :     flash.c
  *Ngay            :     07/09/2016
  *Tac Gia         :     linh.mta
  *Phien Ban       :     V1.0
  *Tom Tat         :
  *
  *
  *
  *****************************************************************************/
#include "flash.h"
/**
*@brief : Write bytes to Flash
*/
uint8_t FLASH_WriteBytes(uint32_t address, uint8_t *data, uint16_t size)
{
    uint16_t i;
    FLASH_EraseInitTypeDef eraseInit;
    uint32_t pageError;
    //Unlock
    HAL_FLASH_Unlock();
    //Erase Pages
    eraseInit.TypeErase = FLASH_TYPEERASE_PAGES;
    eraseInit.PageAddress = address;
    eraseInit.NbPages = 1;
    HAL_FLASHEx_Erase(&eraseInit,&pageError);
    //Write data to Flash
    if(size%2==0)
    {
        for(i=0; i<(size/2); i++)
        {
            HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD,(uint32_t) (address+i*2),((uint64_t)data[i*2+1]<<8)|data[i*2]);
        }
    }
    else
    {
        for(i=0; i<(size/2)+1; i++)
        {
            HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD,(uint32_t) (address+i*2),((uint16_t)data[i*2+1]<<8)|data[i*2]);
        }
    }
    HAL_FLASH_Lock();
}
/**
*@brief : Read bytes from Flash
*/
void FLASH_ReadBytes(uint32_t address, uint8_t *data, uint16_t size)
{
    uint16_t i;
    /*Read data from Flash*/
    for(i=0; i<size; i++)
    {
        data[i] = *(__IO uint8_t*)(address+i);
    }
}
