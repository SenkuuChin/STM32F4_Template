#include "Peripherals/uart/uart.h"
#include "serial_helper.h"

#define RECEIVED_DATA_USE_MACRO             0
#if RECEIVED_DATA_USE_MACRO
#define RECEIVED_DATA_HANDLE(SERIAL) do { \
    if ((SERIAL.receiveFinishFlag & 0x02) != 0) \
        { \
            return; \
        } \
        if (SERIAL.receiveFinishFlag & 0x01) \
        { \
            if (SERIAL.tempData != '\n') \
            { \
                SERIAL.receiveFinishFlag = 0; \
            } \
            else \
            { \
                SERIAL.receiveFinishFlag |= 0x02; \
                SERIAL.data[SERIAL.length] = '\0'; \
            } \
        } \
        else if (SERIAL.tempData == '\r') \
        { \
            SERIAL.receiveFinishFlag |= 0x01; \
        } \
        else if (SERIAL.length < SERIAL_DATA_LENGTH - 1) \
        { \
            SERIAL.data[SERIAL.length] = SERIAL.tempData; \
            ++SERIAL.length; \
        } \
        else \
        { \
            SERIAL.receiveFinishFlag = 0; \
        } \
    } while (0)
#else
void ReceiveHandler(SerialTypeDef* serialNo)
{
    if ((serialNo->receiveFinishFlag & 0x02) != 0)
    {
        return; 
    }
    if (serialNo->receiveFinishFlag & 0x01)
    {
        if (serialNo->tempData != '\n')
        {
            serialNo->receiveFinishFlag = 0;
        }
        else
        {
            serialNo->receiveFinishFlag |= 0x02;
            serialNo->data[serialNo->length] = '\0';
        }
    }
    else if (serialNo->tempData == '\r')
    {
        serialNo->receiveFinishFlag |= 0x01;
    }
    else if (serialNo->length < SERIAL_DATA_LENGTH - 1)
    {
        serialNo->data[serialNo->length++] = serialNo->tempData;
    }
    else
    {
        serialNo->receiveFinishFlag = 0;
        serialNo->length = 0;
    }
}
#endif
#if SYS_COMMAND_CONTROL_ENABLE
extern void Command_Scan(void);
#endif

__IO Bool UART_TransmitSuccessFlag = FALSE;

#if SYS_RT_THREAD_ENABLE
extern rt_mq_t data_mq;
#endif

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART1)
    {
        #if SERIAL_COM1_ENABLE
            #if RECEIVED_DATA_USE_MACRO
                RECEIVED_DATA_HANDLE(SerialNo1);
            #else
                ReceiveHandler(&SerialNo1);
            #endif
            #if SYS_COMMAND_CONTROL_ENABLE
                #if COMMAND_DEFAULT_SERIAL == Serial1
                    Command_Scan();
                #endif
            #endif
        #endif
    }
    #if SERIAL_COM6_ENABLE
    else if (USART6 == huart->Instance)
    {
            #if RECEIVED_DATA_USE_MACRO
                RECEIVED_DATA_HANDLE(SerialNo6);
            #else
                ReceiveHandler(&SerialNo6);
            #endif
            #if COMMAND_DEFAULT_SERIAL == Serial6
                Command_Scan();
            #endif
    }
    #endif
}

// 用于接收不定长数据，配合DMA
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
    // 进入该函数说明触发了空闲中断，一帧数据已经完毕
    if (huart->Instance == USART1)
    {
        #if SERIAL_COM1_ENABLE
            #if SERIAL_COM1_DMA_ENABLE
            
                // HAL_UART_Transmit_DMA(huart, (uint8_t *)SerialNo1.data, Size);
                #if SYS_RT_THREAD_ENABLE
                HandleResult result = OK;
                rt_err_t rtRet = RT_EOK;
                rtRet = rt_mq_send(data_mq,     /* 写入（发送）队列的ID(句柄) */
                                SerialNo1.data, /* 写入（发送）的数据 */
                                Size);          /* 数据的长度 */
                if (rtRet != RT_EOK)
                {
                    uint8_t errorInfo[] = "Push to quene faild!\r\n";
                    HAL_UART_Transmit_DMA(huart, errorInfo, sizeof(errorInfo) - 1);
                }
                #endif
            #endif
        #endif
    }
    #if SERIAL_COM2_ENABLE
    else if (huart->Instance == USART2)
    {
        #if SERIAL_COM2_DMA_ENABLE
            
        #endif
    }
    #endif
    #if SERIAL_COM3_ENABLE
    else if (huart->Instance == USART3)
    {
        #if SERIAL_COM3_DMA_ENABLE
            
        #endif
    }
    #endif
    #if SERIAL_COM4_ENABLE
    else if (huart->Instance == UART4)
    {
        #if SERIAL_COM4_DMA_ENABLE
            
        #endif
    }
    #endif
    #if SERIAL_COM5_ENABLE
    else if (huart->Instance == UART5)
    {
        #if SERIAL_COM5_DMA_ENABLE
            
        #endif
    }
    #endif
    #if SERIAL_COM6_ENABLE
    else if (huart->Instance == USART6)
    {
        #if SERIAL_COM6_DMA_ENABLE
            
        #endif
    }
    #endif
}

// 接收一半时的中断，一般关闭，除非是要乒乓缓存的才需要开启
void HAL_UART_RxHalfCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART1)
    {
        #if SERIAL_COM1_ENABLE
            #if SERIAL_COM1_DMA_ENABLE
                
            #endif
        #endif
    }
    #if SERIAL_COM2_ENABLE
    else if (huart->Instance == USART2)
    {
        #if SERIAL_COM2_DMA_ENABLE
            
        #endif
    }
    #endif
    #if SERIAL_COM3_ENABLE
    else if (huart->Instance == USART3)
    {
        #if SERIAL_COM3_DMA_ENABLE
            
        #endif
    }
    #endif
    #if SERIAL_COM4_ENABLE
    else if (huart->Instance == UART4)
    {
        #if SERIAL_COM4_DMA_ENABLE
            
        #endif
    }
    #endif
    #if SERIAL_COM5_ENABLE
    else if (huart->Instance == UART5)
    {
        #if SERIAL_COM5_DMA_ENABLE
            
        #endif
    }
    #endif
    #if SERIAL_COM6_ENABLE
    else if (huart->Instance == USART6)
    {
        #if SERIAL_COM6_DMA_ENABLE
            
        #endif
    }
    #endif
    
}

void USART_DMA_IRQHandler(UART_HandleTypeDef* huart)
{
    if (huart->Instance == USART1)
    {
        #if SERIAL_COM1_ENABLE
        if (__HAL_UART_GET_FLAG(huart, UART_FLAG_IDLE) == RESET)
        {
            return;
        }
        // 清除空闲中断
        __HAL_UART_CLEAR_IDLEFLAG(huart);
        
        // 处理当前数据的偏移
        #endif
    }
    #if SERIAL_COM2_ENABLE
    else if (huart->Instance == USART2)
    {
        if (__HAL_UART_GET_FLAG(huart, UART_FLAG_IDLE) == RESET)
        {
            return;
        }
        // 清除空闲中断
        __HAL_UART_CLEAR_IDLEFLAG(huart);
        
        // 处理当前数据的偏移
    }
    #endif
    #if SERIAL_COM3_ENABLE
    else if (huart->Instance == USART3)
    {
        if (__HAL_UART_GET_FLAG(huart, UART_FLAG_IDLE) == RESET)
        {
            return;
        }
        // 清除空闲中断
        __HAL_UART_CLEAR_IDLEFLAG(huart);
        
        // 处理当前数据的偏移
    }
    #endif
    #if SERIAL_COM4_ENABLE
    else if (huart->Instance == UART4)
    {
        if (__HAL_UART_GET_FLAG(huart, UART_FLAG_IDLE) == RESET)
        {
            return;
        }
        // 清除空闲中断
        __HAL_UART_CLEAR_IDLEFLAG(huart);
        
        // 处理当前数据的偏移
    }
    #endif
    #if SERIAL_COM5_ENABLE
    else if (huart->Instance == UART5)
    {
        if (__HAL_UART_GET_FLAG(huart, UART_FLAG_IDLE) == RESET)
        {
            return;
        }
        // 清除空闲中断
        __HAL_UART_CLEAR_IDLEFLAG(huart);
        
        // 处理当前数据的偏移
    }
    #endif
    #if SERIAL_COM6_ENABLE
    else if (huart->Instance == USART6)
    {
        if (__HAL_UART_GET_FLAG(huart, UART_FLAG_IDLE) == RESET)
        {
            return;
        }
        // 清除空闲中断
        __HAL_UART_CLEAR_IDLEFLAG(huart);
        
        // 处理当前数据的偏移
    }
    #endif
}

#if SERIAL_COM1_ENABLE
void USART1_IRQHandler(void)
{
    #if !SERIAL_COM1_DMA_ENABLE
    uint32_t timeout = 0;
    uint32_t maxDelay = 0x1FFFF;
    #endif
    
    #if SERIAL_COM1_DMA_ENABLE
    // USART_DMA_IRQHandler(&SerialNo1.handle);
    #endif
    HAL_UART_IRQHandler(&SerialNo1.handle); 

    #if !SERIAL_COM1_DMA_ENABLE
    timeout = 0;
    while(HAL_UART_GetState(&SerialNo1.handle) != HAL_UART_STATE_READY)
    {
        if(++timeout > maxDelay)
        {
            break;
        }
    }

    timeout = 0;

    while(HAL_UART_Receive_IT(&SerialNo1.handle, &SerialNo1.tempData, 1) != HAL_OK)
    {
        if(++timeout > maxDelay)
        {
            break;
        }
    }
    #else
    HAL_UARTEx_ReceiveToIdle_DMA(&SerialNo1.handle, (uint8_t *)SerialNo1.data, SERIAL_DATA_LENGTH);
    #endif
}
#endif

#if SERIAL_COM2_ENABLE
void USART2_IRQHandler(void)
{
    uint32_t timeout = 0;
    uint32_t maxDelay = 0x1FFFF;

    HAL_UART_IRQHandler(&SerialNo2.handle); 

    timeout = 0;
    while(HAL_UART_GetState(&SerialNo2.handle) != HAL_UART_STATE_READY)
    {
        if(++timeout > maxDelay)
        {
            break;
        }
    }

    timeout = 0;

    while(HAL_UART_Receive_IT(&SerialNo2.handle, &SerialNo2.tempData, 1) != HAL_OK)
    {
        if(++timeout > maxDelay)
        {
            break;
        }
    }
}
#endif

#if SERIAL_COM3_ENABLE
void USART3_IRQHandler(void)
{
    uint32_t timeout = 0;
    uint32_t maxDelay = 0x1FFFF;

    HAL_UART_IRQHandler(&SerialNo3.handle); 

    timeout = 0;
    while(HAL_UART_GetState(&SerialNo3.handle) != HAL_UART_STATE_READY)
    {
        if(++timeout > maxDelay)
        {
            break;
        }
    }

    timeout = 0;

    while(HAL_UART_Receive_IT(&SerialNo3.handle, &SerialNo3.tempData, 1) != HAL_OK)
    {
        if(++timeout > maxDelay)
        {
            break;
        }
    }
}
#endif

#if SERIAL_COM6_ENABLE
void USART6_IRQHandler(void)
{
    uint32_t timeout = 0;
    uint32_t maxDelay = 0x1FFFF;

    HAL_UART_IRQHandler(&SerialNo6.handle); 

    timeout = 0;
    while(HAL_UART_GetState(&SerialNo6.handle) != HAL_UART_STATE_READY)
    {
        if(++timeout > maxDelay)
        {
            break;
        }
    }

    timeout = 0;

    while(HAL_UART_Receive_IT(&SerialNo6.handle, &SerialNo6.tempData, 1) != HAL_OK)
    {
        if(++timeout > maxDelay)
        {
            break;
        }
    }
}
#endif

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART1)
    {
        #if SERIAL_COM1_ENABLE
            #if SERIAL_COM1_DMA_ENABLE
                UART_TransmitSuccessFlag = TRUE;
            #endif
        #endif
    }
    #if SERIAL_COM2_ENABLE
    else if (huart->Instance == USART2)
    {
        #if SERIAL_COM2_DMA_ENABLE
            
        #endif
    }
    #endif
    #if SERIAL_COM3_ENABLE
    else if (huart->Instance == USART3)
    {
        #if SERIAL_COM3_DMA_ENABLE
            
        #endif
    }
    #endif
    #if SERIAL_COM4_ENABLE
    else if (huart->Instance == UART4)
    {
        #if SERIAL_COM4_DMA_ENABLE
            
        #endif
    }
    #endif
    #if SERIAL_COM5_ENABLE
    else if (huart->Instance == UART5)
    {
        #if SERIAL_COM5_DMA_ENABLE
            
        #endif
    }
    #endif
    #if SERIAL_COM6_ENABLE
    else if (huart->Instance == USART6)
    {
        #if SERIAL_COM6_DMA_ENABLE
            
        #endif
    }
    #endif
}


void HAL_UART_ErrorCallback(UART_HandleTypeDef * huart)
{
    if (huart->Instance == USART1)
    {
        #if SERIAL_COM1_ENABLE
            #if SERIAL_COM1_DMA_ENABLE
                HAL_UART_Receive_DMA(&SerialNo1.handle, (uint8_t *)SerialNo1.data, SERIAL_DATA_LENGTH);
            #endif
        #endif
    }
    #if SERIAL_COM2_ENABLE
    else if (huart->Instance == USART2)
    {
        #if SERIAL_COM2_DMA_ENABLE
            
        #endif
    }
    #endif
    #if SERIAL_COM3_ENABLE
    else if (huart->Instance == USART3)
    {
        #if SERIAL_COM3_DMA_ENABLE
            
        #endif
    }
    #endif
    #if SERIAL_COM4_ENABLE
    else if (huart->Instance == UART4)
    {
        #if SERIAL_COM4_DMA_ENABLE
            
        #endif
    }
    #endif
    #if SERIAL_COM5_ENABLE
    else if (huart->Instance == UART5)
    {
        #if SERIAL_COM5_DMA_ENABLE
            
        #endif
    }
    #endif
    #if SERIAL_COM6_ENABLE
    else if (huart->Instance == USART6)
    {
        #if SERIAL_COM6_DMA_ENABLE
            
        #endif
    }
    #endif
}
