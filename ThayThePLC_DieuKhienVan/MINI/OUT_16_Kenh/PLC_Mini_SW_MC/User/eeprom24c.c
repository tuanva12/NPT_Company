


#include "eeprom24c.h"
#include "i2c_soft.h"
void ee24c_write_add(uint16_t address)
{
  I2CSOFT_WriteData((uint8_t)(address>>8));
  I2CSOFT_WriteData((uint8_t)address);
}


void ee24c_write_byte(uint16_t add, uint8_t data)
{
  I2CSOFT_Start();
  I2CSOFT_WriteData(IS_WRITE);
  ee24c_write_add(add);
  I2CSOFT_WriteData(data);
  I2CSOFT_Stop();
}


void current_read_byte(uint8_t *data)
{
  I2CSOFT_Start();
  I2CSOFT_WriteData(IS_READ);
  *data = I2CSOFT_ReadData(1);
}



