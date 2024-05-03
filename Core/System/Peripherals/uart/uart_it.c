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

#if SERIAL_COM1_ENABLE
void USART1_IRQHandler(void)
{
    uint32_t timeout = 0;
    uint32_t maxDelay = 0x1FFFF;

    HAL_UART_IRQHandler(&SerialNo1.handle); 

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
