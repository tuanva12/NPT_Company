/*


*/

#ifndef __CONTROL_H
#define __CONTROL_H     05042018
#include "main.h"
#include "cd4094.h"

#define MAX_MODULE_OUT_PUT    4
#define MAX_CHANE_OUT_PUT     (uint8_t)(MAX_MODULE_OUT_PUT*8)

#define MAX_LENGH_DATA_OUT    500

#define SECTER_PER_CHANEL              ((uint8_t)2)

// Dia chi luu du lieu vao Flash
#define ADD_DATA_FLASH_START           ((uint32_t)0x08000000)

#define ADD_DATA_EFF_CHANEL_1          ((uint32_t)(ADD_DATA_FLASH_START + (30 * 1024)))
#define ADD_DATA_EFF_CHANEL_2          ((uint32_t)(ADD_DATA_EFF_CHANEL_1 + (SECTER_PER_CHANEL * 1024)))
#define ADD_DATA_EFF_CHANEL_3          ((uint32_t)(ADD_DATA_EFF_CHANEL_2 + (SECTER_PER_CHANEL * 1024)))
#define ADD_DATA_EFF_CHANEL_4          ((uint32_t)(ADD_DATA_EFF_CHANEL_3 + (SECTER_PER_CHANEL * 1024)))







//#define ADD_DATA_EFF_CHANEL_1          ((uint32_t)0x0800E000)
//#define ADD_DATA_EFF_CHANEL_2          ((uint32_t)0x0800E800)
//#define ADD_DATA_EFF_CHANEL_3          ((uint32_t)0x0800F000)
//#define ADD_DATA_EFF_CHANEL_4          ((uint32_t)0x0800F800)



void Read_data_edd(void);
/* write data to flash */
void Ctrl_Write_Data(void);
// ham chay hieu ung
void run_step_epp (void);

void Ctrl_Run_Effect(void);
#endif



