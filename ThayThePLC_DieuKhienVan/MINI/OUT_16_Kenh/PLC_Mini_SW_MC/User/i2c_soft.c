/*

	I2C

*/

#include "i2c_soft.h"


/*******************************************************************************
Noi Dung    :   Khoi tao giao thuc I2C
Tham Bien   :   Khong.
Tra Ve      :   Khong.
********************************************************************************/

void I2CSOFT_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Pin = SDA_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(SDA_PORT, &GPIO_InitStruct);

    I2CSOFT_SCL=1;
    i2c_delay();
    I2CSOFT_SDAOUT=1;
    i2c_delay();
}

/*******************************************************************************
Noi Dung    :   Gui lenh Start I2C (Keo chan SDA xuong 0 khi SCL o muc 1).
Tham Bien   :   Khong.
Tra Ve      :   Khong.
********************************************************************************/

void I2CSOFT_Start(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Pin = SDA_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(SDA_PORT, &GPIO_InitStruct);


    I2CSOFT_SDAOUT=1; 
    I2CSOFT_SCL=1; 
    i2c_delay();
    I2CSOFT_SDAOUT=0; 
    i2c_delay();
    I2CSOFT_SCL=0;
    i2c_delay();
}

/*******************************************************************************
Noi Dung    :   Gui lenh Stop I2C (Keo chan SDA len muc 1 khi SCL o muc 1).
Tham Bien   :   Khong.
Tra Ve      :   Khong.
********************************************************************************/

void I2CSOFT_Stop(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Pin = SDA_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(SDA_PORT, &GPIO_InitStruct);


    I2CSOFT_SDAOUT=0;
    I2CSOFT_SCL=1;
    i2c_delay();
    I2CSOFT_SDAOUT=1;
    i2c_delay();
    I2CSOFT_SCL=0;
    i2c_delay();
}

/*******************************************************************************
Noi Dung    :   Viet du lieu len Bus I2C.
Tham Bien   :   Data: Gia tri du lieu.
Tra Ve      :   Bit Ack.
********************************************************************************/ 

uint8_t I2CSOFT_WriteData(uint8_t Data)
{
    uint8_t i;
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Pin = SDA_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(SDA_PORT, &GPIO_InitStruct);


    for(i=0;i<8;i++)
    {
        if(Data&0x80)
            I2CSOFT_SDAOUT=1;
        else
            I2CSOFT_SDAOUT=0;
        Data<<=1;   
        I2CSOFT_SCL=1;
        i2c_delay();
        I2CSOFT_SCL=0;
        i2c_delay(); 
    }
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(SDA_PORT, &GPIO_InitStruct);

    I2CSOFT_SCL=1;
    i2c_delay();
    i=I2CSOFT_SDAIN;
    i2c_delay();
    I2CSOFT_SCL=0;
    i2c_delay();
    return i;
}

/*******************************************************************************
Noi Dung    :   Lay du lieu tren Bus I2C.
Tham Bien   :   Ack: gia tri Bit Ack phan hoi khi doc het du lieu, 
Tra Ve      :   Gia tri du lieu.
********************************************************************************/

uint8_t I2CSOFT_ReadData(uint8_t Ack)
{
    uint8_t I2C_Data=0,i;
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Pin = SDA_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(SDA_PORT, &GPIO_InitStruct);

    for(i=0;i<8;i++)
    {         
        I2CSOFT_SCL=1; 
        i2c_delay();         
        I2C_Data<<=1;
        if(I2CSOFT_SDAIN)I2C_Data|=1;
        i2c_delay();
        I2CSOFT_SCL=0;
    }

    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(SDA_PORT, &GPIO_InitStruct);

    I2CSOFT_SCL=1;
    i2c_delay();
    I2CSOFT_SDAOUT=Ack;
    i2c_delay();
    I2CSOFT_SCL=0;
    return I2C_Data;
}




