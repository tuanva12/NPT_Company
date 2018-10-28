/*

	I2C

*/



#ifndef __I2C_SOFT_H
#define __I2C_SOFT_H
#include "main.h"

#define SDA_PIN         GPIO_PIN_4
#define SDA_PORT        GPIOA

#define I2CSOFT_SDAOUT  PORTA_4
#define I2CSOFT_SDAIN   PINA_4

#define I2CSOFT_SCL     PORTA_5




#define i2c_delay()   __NOP();__NOP();__NOP();__NOP();__NOP();__NOP()



void I2CSOFT_Init(void);

/*******************************************************************************
Noi Dung    :   Gui lenh Start I2C (Keo chan SDA xuong 0 khi SCL o muc 1).
Tham Bien   :   Khong.
Tra Ve      :   Khong.
********************************************************************************/

void I2CSOFT_Start(void);
/*******************************************************************************
Noi Dung    :   Gui lenh Stop I2C (Keo chan SDA len muc 1 khi SCL o muc 1).
Tham Bien   :   Khong.
Tra Ve      :   Khong.
********************************************************************************/

void I2CSOFT_Stop(void);

/*******************************************************************************
Noi Dung    :   Viet du lieu len Bus I2C.
Tham Bien   :   Data: Gia tri du lieu.
Tra Ve      :   Bit Ack.
********************************************************************************/ 

uint8_t I2CSOFT_WriteData(uint8_t Data);

/*******************************************************************************
Noi Dung    :   Lay du lieu tren Bus I2C.
Tham Bien   :   Ack: gia tri Bit Ack phan hoi khi doc het du lieu, 
Tra Ve      :   Gia tri du lieu.
********************************************************************************/

uint8_t I2CSOFT_ReadData(uint8_t Ack);



#endif





