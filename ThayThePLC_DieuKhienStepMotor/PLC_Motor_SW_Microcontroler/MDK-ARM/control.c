/*


 _______________________________________________
| DIR | ENB | DIR | ENB | DIR | ENB | DIR | ENB |
|_____|_____|_____|_____|_____|_____|_____|_____|

*/
#include "control.h"
#include "fatfs.h"
#include "effect.h"
#include "flash.h"
/********************************Define*****************************************/
#define MAX_BYTE_DATA                100


#define ADD_TIME_DELAY
#define FLASH_TIME_DELAY_ADDR        0x08058D00
#define FLASH_NUM_PULSE_ADDR         0x0805FFF0

/****************************** variable ***************************************/
FATFS fatfs;
FIL  myfile;
FRESULT fresult;
UINT br;

static uint8_t byte_init[5];                /* save byte init*/

uint8_t byte_data[MAX_BYTE_DATA];           /* save data eff*/
uint8_t byte_data_previous[MAX_BYTE_DATA];  /* save data eff*/
uint8_t Data_Show[MAX_BYTE_DATA * 2];       /* Chua du lieu se show ra module */

static uint8_t file_name[20];               /* save file name*/
static uint8_t ctr_byte_chanel;             /* S? byte c?n d? luu data out ra các module, chieu ngang*/
static uint16_t ctr_long_data_eff;          /* chieu dai cua hieu ung */
static uint8_t   ctr_repeat;                /* So lan lap lai cua mot hieu ung */

uint8_t chanel_current = 0;



uint8_t  Delay_put_pulse = 100;                /* Thoi gian delay can cho viec ban xung */
uint16_t Num_pulse = 20;                      /* S? xung c?n b?n d? d?ng co bu?c di dúng v? trí */

uint8_t USB_Buff_Data[20];                    /* Du lieu nhan duoc tu cong USB */
uint8_t Update_USB = 0;                      /* C? báo có d? ki?u du?c nh?n t? USB */



/*******************************FUNCTION****************************************/


/* Hàm chuy?n d?i 4 bit d?y ch?a d? li?u nh?n du?c thành byte c?n d? b?n ra module */
uint8_t Convest_Byte_High(uint8_t Data_Previous,uint8_t Data_Now);
/* Hàm chuy?n d?i 4 bit sau ch?a d? li?u nh?n du?c thành byte c?n d? b?n ra module */
uint8_t Convest_Byte_Low(uint8_t Data_Previous,uint8_t Data_Now);
/*Ban xung dieu khien ra*/
void Put_pulse(void);

/*********************************CODE******************************************/

void read_byte_init()
{
    f_read(&myfile,byte_init,4,&br);

    __NOP();__NOP();__NOP();__NOP();

    ctr_byte_chanel = byte_init[0];
    ctr_repeat = byte_init[1];
    ctr_long_data_eff = ((((uint16_t)byte_init[2])<<8)|(uint16_t)byte_init[3]);

    eff_init(ctr_byte_chanel,ctr_long_data_eff,ctr_repeat);
}


void read_data_eff(void)
{
    f_read(&myfile,byte_data,ctr_byte_chanel,&br);
}



/* main */
void control_main_eff(void)
{
    static uint16_t delay_count = 0;
    uint16_t index;

    for(index = 0;index < MAX_BYTE_DATA;index++)
    {
        byte_data_previous[index] = 0x00;
    }
    sprintf((char*)file_name,"eff1.bin");
    while(1)
    {
        HAL_Delay(20);
        HAL_GPIO_TogglePin(LED_BLINK_GPIO_Port,LED_BLINK_Pin);

        if(input_chanel() != chanel_current)// neu co su thay doi kenh dau vao
        {
            chanel_current = input_chanel();
        }

        if(chanel_current != 0)       /* Neu co in put d?u vào m?i d?c memorycard và ch?y chuong trình*/
        {
            sprintf((char*)file_name,"eff%d.bin",chanel_current);          /* L?y tên file d? b?t d?u d?c */

            fresult = f_open(&myfile,(char*)file_name,FA_READ);            /* opent file */
            if(fresult == FR_OK)
            {
                read_byte_init();    // khoi tao cac gia tri ban dau cua file hieu ung
                while((input_chanel() == chanel_current) && (ctr_long_data_eff >0))
                {
                    fresult = f_read(&myfile,byte_data,ctr_byte_chanel,&br);             /* read data*/

                    delay_count = (((uint16_t)byte_data[0])<<8|((uint16_t)byte_data[1]));    /* Chuy?n d?i giá tr? delay du?c luu tr? trong 2 byte d?u c?a m?ng */
                    shadow_data();                                                      /* d?y các byte tru?c di xa, tránh b? trùng khi nó nhi?u module*/

                    /* Chuy?n d?i t? d? li?u d?c du?c trong memorycard sang d? li?u c?n b?n ra module */
                    for(index = 0;index < ctr_byte_chanel ;index++)
                    {
                        Data_Show[index*2]     = Convest_Byte_High(byte_data_previous[index+2],byte_data[index+2]);
                        Data_Show[index*2 + 1] = Convest_Byte_Low(byte_data_previous[index+2],byte_data[index+2]);
                    }

                    /* D?y d? li?u ra các module */
                    for(index = 0;index <= (ctr_byte_chanel * 2);index++)
                    {
                        CD4094_InByte(Data_Show[(ctr_byte_chanel * 2) - index]);
                    }
                    CD4094_Latch();                                       /* Ch?t d? li?u */
                    /* B?t d?u b?n xung ra chân pulse */
                    Put_pulse();
                    /* K?t thúc b?n xung */
                    HAL_Delay(delay_count);                                /* delay step epp*/

                    /* copy d? li?u d?c du?c cho l?n so sánh sau. */
                    for(index = 0;index < (ctr_byte_chanel + 2);index++)
                    {
                        byte_data_previous[index] = byte_data[index];
                    }
                    /*  */
                    ctr_long_data_eff--;
                }
            }
            f_close(&myfile);   /* close file */
        }
        else /* end show eff*/
        {
            shadow_data();
            CD4094_Latch();
        }

    }
}




/* Hàm chuy?n d?i 4 bit d?y ch?a d? li?u nh?n du?c thành byte c?n d? b?n ra module */
uint8_t Convest_Byte_High(uint8_t Data_Previous,uint8_t Data_Now)
{
    uint8_t Data_Result = 0x00;
    /* Chuy?n d?i tr?ng thái cho chân direction, tr?ng thái c?a chân này luôn thay d?i theo tr?ng thái d? li?u d?c du?c*/
    if((Data_Now & 0x80)!=0)
    {
        Data_Result |= 0x40;
    }
    if((Data_Now & 0x40)!=0)
    {
        Data_Result |= 0x10;
    }
    if((Data_Now & 0x20)!=0)
    {
        Data_Result |= 0x04;
    }
    if((Data_Now & 0x10)!=0)
    {
        Data_Result |= 0x01;
    }
    /* Chuy?n d?i tr?ng thái cho chân ennable, tr?ng thái c?a chân này s? du?c b?t n?u tr?ng thái bít tuong ?ng c?a l?n tru?c và l?n sau khác nhau */
    if((Data_Now & 0x80) != (Data_Previous & 0x80))
    {
        Data_Result |= 0x80;
    }
    if((Data_Now & 0x40) != (Data_Previous & 0x40))
    {
        Data_Result |= 0x20;
    }
    if((Data_Now & 0x20) != (Data_Previous & 0x20))
    {
        Data_Result |= 0x08;
    }
    if((Data_Now & 0x10) != (Data_Previous & 0x10))
    {
        Data_Result |= 0x02;
    }

    /* Return value*/
    return Data_Result;
}
/* Hàm chuy?n d?i 4 bit sau ch?a d? li?u nh?n du?c thành byte c?n d? b?n ra module */
uint8_t Convest_Byte_Low(uint8_t Data_Previous,uint8_t Data_Now)
{
    uint8_t Data_Result = 0x00;
    /* Chuy?n d?i tr?ng thái cho chân direction */
    if((Data_Now & 0x08)!=0)
    {
        Data_Result |= 0x40;
    }
    if((Data_Now & 0x04)!=0)
    {
        Data_Result |= 0x10;
    }
    if((Data_Now & 0x02)!=0)
    {
        Data_Result |= 0x04;
    }
    if((Data_Now & 0x01)!=0)
    {
        Data_Result |= 0x01;
    }
    /* Chuy?n d?i tr?ng thái cho chân ennable */
    if((Data_Now & 0x08) != (Data_Previous & 0x08))
    {
        Data_Result |= 0x80;
    }
    if((Data_Now & 0x04) != (Data_Previous & 0x04))
    {
        Data_Result |= 0x20;
    }
    if((Data_Now & 0x02) != (Data_Previous & 0x02))
    {
        Data_Result |= 0x08;
    }
    if((Data_Now & 0x01) != (Data_Previous & 0x01))
    {
        Data_Result |= 0x02;
    }

    /* Return value*/
    return Data_Result;
}



/*Ban xung dieu khien ra*/
void Put_pulse(void)
{
    uint16_t index;
    for(index = 0;index < Num_pulse;index++)
    {
        HAL_GPIO_TogglePin(OUT_PULS_GPIO_Port,OUT_PULS_Pin);
        HAL_Delay(Delay_put_pulse);
        HAL_GPIO_TogglePin(OUT_PULS_GPIO_Port,OUT_PULS_Pin);
        HAL_Delay(Delay_put_pulse);
    }
    HAL_GPIO_WritePin(OUT_PULS_GPIO_Port,OUT_PULS_Pin,GPIO_PIN_RESET);
}

/*Ban xung dieu khien ra mac dinh*/
void Put_pulse_default(void)
{
    uint16_t index;
    for(index = 0;index < Num_pulse;index++)
    {
        HAL_GPIO_TogglePin(OUT_PULS_GPIO_Port,OUT_PULS_Pin);
        HAL_Delay(1);
        HAL_GPIO_TogglePin(OUT_PULS_GPIO_Port,OUT_PULS_Pin);
        HAL_Delay(1);
    }
    HAL_GPIO_WritePin(OUT_PULS_GPIO_Port,OUT_PULS_Pin,GPIO_PIN_RESET);
}



/* Ham duoc goi trong chuong trinh chinh */
void control(void)
{
    uint8_t index;

    Delay_put_pulse = *(__IO uint8_t*)(FLASH_TIME_DELAY_ADDR);
    Num_pulse       = *(__IO uint16_t*)(FLASH_NUM_PULSE_ADDR);

/* Dieu chinh dong co ve vi tri ban dau */
    for(index = 0;index < MAX_BYTE_DATA;index ++)
    {
        CD4094_InByte(0x55);
    }
    CD4094_Latch();
    Put_pulse();

/* Bat dau doc memorycard. */
   if(BSP_SD_Init() == MSD_OK);
    {
        fresult = f_mount(&fatfs,"",1);
        if(fresult ==FR_OK)
        {
            control_main_eff();
        }
    }

/* Neu khong doc duoc the nho thi vao che do cai dat */
    HAL_GPIO_WritePin(RESET_USB_GPIO_Port,RESET_USB_Pin,GPIO_PIN_RESET);    /* Enable USB */
    while(1)
    {
        if(Update_USB == 1)
        {
            Update_USB = 0;

            /* Start analysis data received from USB port */
            if((USB_Buff_Data[0] == 'V') && (USB_Buff_Data[1] == 'A') && (USB_Buff_Data[2] == 'T'))
            {
                if((USB_Buff_Data[4] == 'T') && (USB_Buff_Data[5] == 'E') && (USB_Buff_Data[6] == 'S') && (USB_Buff_Data[7] == 'T'))
                {
                    /* Che do test dong co */
                    shadow_data();
                    CD4094_InByte(0xFF);
                    CD4094_Latch();
                    Put_pulse_default();

                    shadow_data();
                    CD4094_InByte(0x55);
                    CD4094_Latch();
                    Put_pulse_default();
                }
                else
                {
                    if((USB_Buff_Data[4] == 'S') && (USB_Buff_Data[5] == 'T') && (USB_Buff_Data[6] == 'E') && (USB_Buff_Data[7] == 'P'))
                    {
                        /* Ghi vao so buoc */
                        FLASH_WriteBytes(FLASH_NUM_PULSE_ADDR,&USB_Buff_Data[8],2);
                        Num_pulse       = *(__IO uint16_t*)(FLASH_NUM_PULSE_ADDR);
                    }
                    else
                    {
                        if((USB_Buff_Data[4] == 'D') && (USB_Buff_Data[5] == 'E') && (USB_Buff_Data[6] == 'L') && (USB_Buff_Data[7] == 'Y'))
                        {
                            /* Ghi vao thoi gian delay */
                            FLASH_WriteBytes(FLASH_TIME_DELAY_ADDR,&USB_Buff_Data[8],1);
                            Delay_put_pulse = *(__IO uint8_t*)(FLASH_TIME_DELAY_ADDR);
                        }
                    }
                }
            }
        }
        HAL_Delay(10);
    }
}








