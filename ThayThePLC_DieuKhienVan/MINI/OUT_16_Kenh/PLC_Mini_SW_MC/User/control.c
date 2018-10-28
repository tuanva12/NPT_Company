/*
    file chuong trinh dieu khien hieu ung

*/

#include "control.h"
#include "flash.h"
#include "queue.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
 
 /*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
static uint8_t  s_Module = 0;
static uint16_t s_Lenght = 0;
/*******************************************************************************
 * Code
 ******************************************************************************/

/* Check input for select effect */
uint8_t Ctrl_Check_Input(void)
{
    if(IN_1 == 0) return 1;
    if(IN_2 == 0) return 2;
    if(IN_3 == 0) return 3;
    if(IN_4 == 0) return 4;
    return 0;
}

/* write data to flash */
void Ctrl_Write_Data(void)
{
    uint8_t chanel = 0;
    uint32_t Address;
    uint8_t* ptr_data;
    uint8_t index = 0;
    while(1)
    {
        chanel = Ctrl_Check_Input();
        if(chanel == 0)
        {
            HAL_GPIO_TogglePin(LED_GPIO_Port,LED_Pin);
            HAL_Delay(50);
        }
        else
        {
            switch (chanel)
            {
                case 1:
                {
                    Address = ADD_DATA_EFF_CHANEL_1;
                    break;
                }
                case 2:
                {
                    Address = ADD_DATA_EFF_CHANEL_2;
                    break;
                }
                case 3:
                {
                    Address = ADD_DATA_EFF_CHANEL_3;
                    break;
                }
                case 4:
                {
                    Address = ADD_DATA_EFF_CHANEL_4;
                    break;
                }
            }

            if ((!queue_isEmpty()) && (chanel != 0))/* check is queue empty */
            {
                LED = 1;           /* turn off led status */
                FLASH_Erase_Multi_Sector(Address,SECTER_PER_CHANEL);      /* erase data */
                while(1)
                {
                    if (!queue_isEmpty())/* check is queue empty */
                    {
                        queue_getData((uint8_t **)&ptr_data);     /* read data from queue */
                        queue_get();                              /* get queue */
                        /* start write flash */
                        for(index = 0; index < 32 ;index += 2)
                        {
                            FLASH_Write_HalfWord(Address,(ptr_data + index));
                            Address += 2;
                        }
                    }
                }
            }
        }
    }
}


/* Read header data */
void Ctrl_Read_Header(uint8_t* add)
{
    s_Module = add[0];
    s_Lenght = (((uint16_t)add[1])<<8) | ((uint16_t)add[2]);
}
/* Show led */
void Ctrl_Show(__IO uint8_t* data)
{
    uint16_t delay;
    uint8_t i;
    delay = (((uint16_t)(data[0])<<8) | (uint16_t)data[1]);
    for(i = 0;i <10;i++)
    {
        CD4094_InByte(0x00);
    }
    for(i = s_Module;i >= 2;i--)
    {
        CD4094_InByte(data[i]);
    }
    CD4094_Latch();
    HAL_Delay(delay);
}


/* RUN EFF */
void Ctrl_Run_Effect(void)
{
    uint32_t Address;
    uint8_t chanel_current = 0;

    while(1)
    {
        chanel_current = Ctrl_Check_Input();
        switch (chanel_current)
        {
            case 1:
            {
                Address = ADD_DATA_EFF_CHANEL_1;
                break;
            }
            case 2:
            {
                Address = ADD_DATA_EFF_CHANEL_2;
                break;
            }
            case 3:
            {
                Address = ADD_DATA_EFF_CHANEL_3;
                break;
            }
            case 4:
            {
                Address = ADD_DATA_EFF_CHANEL_4;
                break;
            }
        }
        if(Ctrl_Check_Input() != 0)
        {
            Ctrl_Read_Header((uint8_t*)Address);
            Address += 3;
            while((Ctrl_Check_Input() == chanel_current) && (s_Lenght > 0))
            {
                Ctrl_Show((__IO uint8_t*)Address);
                Address += s_Module;
                s_Lenght--;
            }

            CD4094_InByte(0x00);
            CD4094_InByte(0x00);
            CD4094_InByte(0x00);
            CD4094_InByte(0x00);
            CD4094_InByte(0x00);
            CD4094_InByte(0x00);
            CD4094_InByte(0x00);
            CD4094_InByte(0x00);
            CD4094_InByte(0x00);
            CD4094_Latch();

        }
    }
}


















