/**
  ******************************************************************************
  * File Name          : main.h
  * Description        : This file contains the common defines of the application
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2018 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H
  /* Includes ------------------------------------------------------------------*/

/* USER CODE BEGIN Includes */

#include "stm32f1xx_hal.h"
#include "DEF_STM32.h"



/* USER CODE END Includes */

/* Private define ------------------------------------------------------------*/

#define BUTTOM_Pin GPIO_PIN_1
#define BUTTOM_GPIO_Port GPIOA
#define IN_1_Pin GPIO_PIN_14
#define IN_1_GPIO_Port GPIOB
#define IN_2_Pin GPIO_PIN_15
#define IN_2_GPIO_Port GPIOB
#define IN_3_Pin GPIO_PIN_8
#define IN_3_GPIO_Port GPIOA
#define IN_4_Pin GPIO_PIN_9
#define IN_4_GPIO_Port GPIOA
#define RESET_USB_Pin GPIO_PIN_10
#define RESET_USB_GPIO_Port GPIOA
#define OUT_FET_Pin GPIO_PIN_15
#define OUT_FET_GPIO_Port GPIOA
#define CD_STB_Pin GPIO_PIN_3
#define CD_STB_GPIO_Port GPIOB
#define CD_DATA_Pin GPIO_PIN_4
#define CD_DATA_GPIO_Port GPIOB
#define CD_CLK_Pin GPIO_PIN_5
#define CD_CLK_GPIO_Port GPIOB
#define LED_Pin GPIO_PIN_7
#define LED_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

#define     CD4094_DATA   PORTB_4
#define     CD4094_CLK    PORTB_5
#define     CD4094_STROBE PORTB_3

#define BUTTON_PRESS()           (HAL_GPIO_ReadPin(BUTTOM_GPIO_Port,BUTTOM_Pin) == GPIO_PIN_RESET)
#define Enable_USB()             HAL_GPIO_WritePin(RESET_USB_GPIO_Port,RESET_USB_Pin,GPIO_PIN_RESET);
#define Disable_USB()            HAL_GPIO_WritePin(RESET_USB_GPIO_Port,RESET_USB_Pin,GPIO_PIN_SET);



#define IN_1 PINB_14
#define IN_2 PINB_15
#define IN_3 PINA_8
#define IN_4 PINA_9

#define LED   PORTB_7


/* USER CODE END Private defines */

void _Error_Handler(char *, int);

#define Error_Handler() _Error_Handler(__FILE__, __LINE__)

/**
  * @}
  */ 

/**
  * @}
*/ 

#endif /* __MAIN_H */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
