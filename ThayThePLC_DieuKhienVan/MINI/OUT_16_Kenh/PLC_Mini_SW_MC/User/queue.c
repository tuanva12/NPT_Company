#include "queue.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define MAX_QUEUE_SIZE                    4

typedef struct
{
    uint8_t data[35];
}queue_data_struct_t;

typedef struct
{
    uint8_t getIndex;
    uint8_t putIndex;
    uint8_t size;
    queue_data_struct_t element[MAX_QUEUE_SIZE];
}queue_struct_t;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
queue_struct_t s_queueList;
/*******************************************************************************
 * Code
 ******************************************************************************/
/* init queue */
void queue_init(void)
{
    s_queueList.getIndex = 0;
    s_queueList.putIndex = 0;
    s_queueList.size = 0;
}
/* check queue full */
bool queue_isFull(void)
{
    bool retVal = false;
    if (MAX_QUEUE_SIZE == s_queueList.size)
    {
        retVal = true;
    }
    return retVal;
}
/* check queue empty */
bool queue_isEmpty(void)
{
    bool retVal = false;
    if (0 == s_queueList.size)
    {
        retVal = true;
    }
    return retVal;
}
/* put queue when had data need put */
void queue_put(void)
{
    s_queueList.putIndex++;
    s_queueList.size++;
}
/* get element of queue is un used for put data next */
void queue_getUnuseElement(uint8_t **outBuff)
{
    uint8_t putIndex = s_queueList.putIndex % MAX_QUEUE_SIZE;

    if (!queue_isFull())
    {
        *outBuff = (uint8_t *)&s_queueList.element[putIndex];
    }
}
/* get queue after read data of element queue */
void queue_get(void)
{
    s_queueList.getIndex++;
    s_queueList.size--;
}
/* ghet data of queue for process data */
void queue_getData(uint8_t **outBuff)
{
    uint8_t getIndex = s_queueList.getIndex % MAX_QUEUE_SIZE;
    if (!queue_isEmpty())
    {
        *outBuff = (uint8_t *)&s_queueList.element[getIndex];
    }
}




