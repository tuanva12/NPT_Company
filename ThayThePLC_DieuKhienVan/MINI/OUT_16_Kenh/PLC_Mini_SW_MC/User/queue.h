#ifndef __QUEUE_H
#define __QUEUE_H
#include "stm32f1xx_hal.h"
#include "stdbool.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define SREC_MAX_BYTE_OF_LINE                    70
#define SIZE_QUEUE                               6
/*******************************************************************************
 * API
 ******************************************************************************/
/*!
 * @brief init queue
 *
 * @param
 *
 * @return
 */
void queue_init(void);

/*!
 * @brief check queue full
 *
 * @param
 *
 * @return true if queue is full and else
 */
bool queue_isFull(void);

/*!
 * @brief check queue empty
 *
 * @param
 *
 * @return true if queue is empty and else
 */
bool queue_isEmpty(void);

/*!
 * @brief get element of queue is un used for put data next
 *
 * @param
 *
 * @return
 */
void queue_getUnuseElement(uint8_t **outBuff);

/*!
 * @brief put queue when had data need put
 *
 * @param
 *
 * @return
 */
void queue_put(void);

/*!
 * @brief ghet data of queue for process data
 *
 * @param
 *
 * @return
 */
void queue_getData(uint8_t **outBuff);

/*!
 * @brief get queue after read data of element queue
 *
 * @param
 *
 * @return
 */
void queue_get(void);






#endif


