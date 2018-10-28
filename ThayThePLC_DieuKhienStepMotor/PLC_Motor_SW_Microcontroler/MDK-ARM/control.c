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
static uint8_t ctr_byte_chanel;             /* Số byte cần để lưu data out ra các module, chieu ngang*/
static uint16_t ctr_long_data_eff;          /* chieu dai cua hieu ung */
static uint8_t   ctr_repeat;                /* So lan lap lai cua mot hieu ung */

uint8_t chanel_current = 0;
uint8_t Delay_put_pulse = 0;                /* Thoi gian delay can cho viec ban xung */
uint8_t Num_pulse = 0;                      /* Số xung cần bắn để động cơ bước đi đúng vị trí */

/*******************************FUNCTION****************************************/


/* Hàm chuyển đổi 4 bit đầy chủa dữ liệu nhận được thành byte cần để bắn ra module */
uint8_t Convest_Byte_High(uint8_t Data_Previous,uint8_t Data_Now);
/* Hàm chuyển đổi 4 bit sau chủa dữ liệu nhận được thành byte cần để bắn ra module */
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
        
        if(chanel_current != 0)       /* Neu co in put đầu vào mới đọc memorycard và chạy chương trình*/
        {
            sprintf((char*)file_name,"eff%d.bin",chanel_current);          /* Lấy tên file để bắt đầu đọc */

            fresult = f_open(&myfile,(char*)file_name,FA_READ);            /* opent file */
            if(fresult == FR_OK)
            {
                read_byte_init();    // khoi tao cac gia tri ban dau cua file hieu ung
                while((input_chanel() == chanel_current) && (ctr_long_data_eff >0))
                {
                    fresult = f_read(&myfile,byte_data,ctr_byte_chanel,&br);             /* read data*/

                    delay_count = (((uint16_t)byte_data[0])<<8|((uint16_t)byte_data[1]));    /* Chuyển đổi giá trị delay được lưu trữ trong 2 byte đầu của mảng */
                    shadow_data();                          /* đẩy các byte trước đi xa, tránh bị trùng khi nó nhiều module*/

                    /* Chuyển đổi từ dữ liệu đọc được trong memorycard sang dữ liệu cần bắn ra module */
                    for(index = 0;index < ctr_byte_chanel ;index++)
                    {
                        Data_Show[index*2]     = Convest_Byte_High(byte_data_previous[index+2],byte_data[index+2]);
                        Data_Show[index*2 + 1] = Convest_Byte_Low(byte_data_previous[index+2],byte_data[index+2]);
                    }

                    /* Dẩy dữ liệu ra các module */
                    for(index = 0;index <= (ctr_byte_chanel * 2);index++)
                    {
                        CD4094_InByte(Data_Show[(ctr_byte_chanel * 2) - index]);
                    }
                    CD4094_Latch();                                       /* Chốt dữ liệu */
                    /* Bắt đầu bắn xung ra chân pulse */
                    Put_pulse();
                    /* Kết thúc bắn xung */
                    HAL_Delay(delay_count);                                /* delay step epp*/

                    /* copy dữ liệu đọc được cho lần so sánh sau. */
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




/* Hàm chuyển đổi 4 bit đầy chủa dữ liệu nhận được thành byte cần để bắn ra module */
uint8_t Convest_Byte_High(uint8_t Data_Previous,uint8_t Data_Now)
{
    uint8_t Data_Result = 0x00;
    /* Chuyển đổi trạng thái cho chân direction, trạng thái của chân này luôn thay đổi theo trạng thái dữ liệu đọc được*/
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
    /* Chuyển đổi trạng thái cho chân ennable, trạng thái của chân này sẽ được bật nếu trạng thái bít tương ứng của lần trước và lần sau khác nhau */
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
/* Hàm chuyển đổi 4 bit sau chủa dữ liệu nhận được thành byte cần để bắn ra module */
uint8_t Convest_Byte_Low(uint8_t Data_Previous,uint8_t Data_Now)
{
    uint8_t Data_Result = 0x00;
    /* Chuyển đổi trạng thái cho chân direction */
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
    /* Chuyển đổi trạng thái cho chân ennable */
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
    HAL_GPIO_TogglePin(LED_BLINK_GPIO_Port,LED_BLINK_Pin);
    HAL_Delay(50);
    HAL_GPIO_TogglePin(LED_BLINK_GPIO_Port,LED_BLINK_Pin);
    HAL_Delay(50);
    HAL_GPIO_TogglePin(LED_BLINK_GPIO_Port,LED_BLINK_Pin);
    HAL_Delay(50);
    HAL_GPIO_TogglePin(LED_BLINK_GPIO_Port,LED_BLINK_Pin);
    HAL_Delay(50);
    HAL_GPIO_TogglePin(LED_BLINK_GPIO_Port,LED_BLINK_Pin);
    HAL_Delay(50);
    HAL_GPIO_TogglePin(LED_BLINK_GPIO_Port,LED_BLINK_Pin);
    HAL_Delay(50);
    HAL_GPIO_TogglePin(LED_BLINK_GPIO_Port,LED_BLINK_Pin);
    HAL_Delay(50);
    HAL_GPIO_TogglePin(LED_BLINK_GPIO_Port,LED_BLINK_Pin);
    HAL_Delay(50);
}





/* Ham duoc goi trong chuong trinh chinh */
void control(void)
{
   if(BSP_SD_Init() == MSD_OK);
    {
        fresult = f_mount(&fatfs,"",1);
        if(fresult ==FR_OK)
        {

            control_main_eff();

        }
    }
}








