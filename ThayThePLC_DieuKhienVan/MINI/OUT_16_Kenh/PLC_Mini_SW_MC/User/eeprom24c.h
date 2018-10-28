


#ifndef __EEPROM24C_H
#define __EEPROM24C_H
#include "main.h"

#define IS_WRITE    0xA0
#define IS_READ     0xA1




void ee24c_write_byte(uint16_t add, uint8_t data);

void current_read_byte(uint8_t *data);





#endif



