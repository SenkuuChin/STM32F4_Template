#include "serial_helper.h"
#include <stdio.h>
#include "Peripherals/uart/uart.h"
#include <stdarg.h>
#if SYS_SRAM_MANAGE_ENABLE
#include "sram_helper.h"
#endif
#if SYS_STRING_HELPER_ENABLE
#include "string_helper.h"
#else
#include <string.h>
#endif




#define SERIAL_SEND(SERIAL, LENGTH, DATA) do { \
    uint16_t i; \
    for (i = 0; i < LENGTH; ++i) \
    { \
        while ((SERIAL->SR & 0x40) == 0); \
        SERIAL->DR = *DATA; \
        DATA++; \
    } \
} while (0)

#define SERIAL_AUTO_WRAP_FUNC(SERIAL) do { \
    while ((SERIAL->SR & 0x40) == 0); \
    SERIAL->DR = '\r'; \
    while ((SERIAL->SR & 0x40) == 0); \
    SERIAL->DR = '\n'; \
} while (0)

#ifdef __ARMCC_VERSION
    FILE __stdout;
    #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#else
    #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#endif


#if (__ARMCC_VERSION >= 6010050)					/* 使用AC6编译器时 */
__asm(".global __use_no_semihosting\n\t");			/* 声明不使用半主机模式 */
__asm(".global __ARM_use_no_argv \n\t");			/* AC6下需要声明main函数为无参数格式，否则部分例程可能出现半主机模式 */

#else
/* 使用AC5编译器时, 要在这里定义__FILE 和 不使用半主机模式 */
#pragma import(__use_no_semihosting)

struct __FILE
{
    int handle;
    /* Whatever you require here. If the only file you are using is */
    /* standard output using printf() for debugging, no file handling */
    /* is required. */
};
#endif

PUTCHAR_PROTOTYPE
{
    HAL_UART_Transmit(&SerialNo1.handle, (uint8_t *)&ch, 1, 0xFFFF);
    return ch;
}

void Serial_Init(void)
{
    #if SERIAL_SYNC_ENABLE
    USART_Init();
    #endif
    UART_Init();
}

__IO uint8_t serialLock = NULL;
void SerialOutput(SerialType serialType, uint8_t isNeedDash,
    uint8_t isSpecifyLength, uint16_t dataLength,
    uint8_t isOnlyPrint,
    const char* format, ...)
{
    #if SYS_FREERTOS_ENABLE
    taskENTER_CRITICAL();
    #elif SYS_RT_THREAD_ENABLE
    /* 进入临界段 */
    rt_enter_critical();
    #endif
/* 定义一个发送缓冲区，存放格式化后的数据 */
    char *buffer = NULL, *str = NULL;
    #if SYS_SRAM_MANAGE_ENABLE
    buffer = SRAMHelper.Malloc(SRAM_INTERNAL, PRINT_TEMP_DATA_LENGTH);
    #else
    buffer = (char*)malloc(sizeof(char) * PRINT_TEMP_DATA_LENGTH);
    #endif
    uint16_t length = 0;
    va_list args;
    if (isSpecifyLength == FALSE)
    {
        if (isOnlyPrint == FALSE)
        {
            
            va_start(args, format);

            vsnprintf(buffer, PRINT_TEMP_DATA_LENGTH, format, args);
        }
        else
        {
            COPY_DATA(format, buffer, 0, strlen(format));
        }
        #if SYS_STRING_HELPER_ENABLE
        length = my_StrGetLength(buffer);
        #else
        length = strlen(buffer);
        #endif
    }
    else
    {
        length = dataLength;
        COPY_DATA(format, buffer, 0, length);
    }
    
    if (isNeedDash == TRUE)
    {
        if (length > (PRINT_TEMP_DATA_LENGTH - 2))
        {
            /* 若长度大于最大值，则等于最大值 */
            length = PRINT_TEMP_DATA_LENGTH;
            buffer[length - 1] = '\n';
            buffer[length - 2] = '\r';
        }
        else
        {
            buffer[length] = '\r';
            buffer[length + 1] = '\n';
            length += 2;
        }
    }
    else if (length > PRINT_TEMP_DATA_LENGTH)
    {
        /* 若长度大于最大值，则等于最大值 */
        length = PRINT_TEMP_DATA_LENGTH;
    }
    str = buffer;
    switch (serialType)
    {
        case Serial1:
            #if SERIAL_COM1_ENABLE
            SERIAL_SEND(USART1, length, str);
            #endif
            break;
        case Serial2:
            #if SERIAL_COM2_ENABLE
            SERIAL_SEND(USART2, length, str);
            #endif
            break;
        case Serial3:
            #if SERIAL_COM3_ENABLE
            SERIAL_SEND(USART3, length, str);
            #endif
            break;
        case Serial4:
            #if SERIAL_COM4_ENABLE
            SERIAL_SEND(UART4, length, str);
            #endif
            break;
        case Serial5:
            #if SERIAL_COM5_ENABLE
            SERIAL_SEND(UART5, length, str);
            #endif
            break;
        case Serial6:
            #if SERIAL_COM6_ENABLE
            SERIAL_SEND(USART6, length, str);
            #endif
            break;
        default:
            break;
    }
    // 不指定长度，并且是有格式化的(不是纯打印的)
    if (isSpecifyLength == FALSE && isOnlyPrint == FALSE)
    {
        va_end(args);
    }
    #if SYS_SRAM_MANAGE_ENABLE
    SRAMHelper.Free(SRAM_INTERNAL, buffer);
    #else
    free(buffer);
    #endif
    str = NULL;
    buffer = NULL;
    serialLock = NULL;
    #if SYS_FREERTOS_ENABLE
    taskEXIT_CRITICAL();
    #elif SYS_RT_THREAD_ENABLE
    /* 退出临界段 */
    rt_exit_critical();
    #endif
}

void SerialDataGet(SerialType serialType, char* refData, uint16_t *refLength,
                    Bool isGetLength, Bool isGetString, Bool isPrintUse)
{
    #if SYS_FREERTOS_ENABLE
    taskENTER_CRITICAL();
    #elif SYS_RT_THREAD_ENABLE
    /* 进入临界段 */
    rt_enter_critical();
    #endif
    switch (serialType)
    {
        case Serial1:
            #if SERIAL_COM1_ENABLE
            if ((SerialNo1.receiveFinishFlag & 0x02) == FALSE)
            {
                break;
            }
            if (isPrintUse == TRUE)
            {
                SerialSendData(Serial1, SerialNo1.data, SerialNo1.length);
                SerialNo1.receiveFinishFlag = 0;
                SerialNo1.length = 0;
                break;
            }
            // 只为获取长度信息
            else if (isGetLength)
            {
                *refLength = SerialNo1.length;
                break;
            }
            else if (isGetString)
            {
                COPY_DATA(SerialNo1.data, refData, 0, strlen(SerialNo1.data));
                SerialNo1.receiveFinishFlag = 0;
                SerialNo1.length = 0;
                break;
            }
            // 如果长度为0证明它想要获取全部串口长度数据
            else if (*refLength == NULL)
            {
                *refLength = SerialNo1.length;
                // COPY_DATA(SerialNo1.data, refData, SerialNo1.length);
            }
            // 如果想要的长度大于了本来的长度
            else if (*refLength > SerialNo1.length)
            {
                break;
            }
            // 按指定长度去读取
            COPY_DATA(SerialNo1.data, refData, 0, *refLength);
            // refData = SerialNo1.data;
            SerialNo1.receiveFinishFlag = 0;
            SerialNo1.length = 0;
            #endif
            break;
        case Serial2:
            #if SERIAL_COM2_ENABLE
            if ((SerialNo2.receiveFinishFlag & 0x02) == false)
            {
                break;
            }
            if (isPrintUse == TRUE)
            {
                SerialSendData(Serial2, SerialNo2.data, SerialNo2.length);
                SerialNo2.receiveFinishFlag = 0;
                SerialNo2.length = 0;
                break;
            }
            // 只为获取长度信息
            else if (isGetLength)
            {
                *refLength = SerialNo2.length;
                break;
            }
            else if (isGetString)
            {
                COPY_DATA(SerialNo2.data, refData, 0, strlen(SerialNo2.data));
                SerialNo2.receiveFinishFlag = 0;
                SerialNo2.length = 0;
                break;
            }
            // 如果长度为0证明它想要获取全部串口长度数据
            else if (*refLength == NULL)
            {
                *refLength = SerialNo2.length;
                // COPY_DATA(SerialNo1.data, refData, SerialNo1.length);
            }
            // 如果想要的长度大于了本来的长度
            else if (*refLength > SerialNo2.length)
            {
                break;
            }
            // 按指定长度去读取
            COPY_DATA(SerialNo2.data, refData, 0, *refLength);
            SerialNo2.receiveFinishFlag = 0;
            SerialNo2.length = 0;
            // refData = SerialNo2.data;
            #endif
            break;
        case Serial3:
            #if SERIAL_COM3_ENABLE
            if ((SerialNo3.receiveFinishFlag & 0x02) == false)
            {
                break;
            }
            if (isPrintUse == TRUE)
            {
                SerialSendData(Serial3, SerialNo3.data, SerialNo3.length);
                SerialNo3.receiveFinishFlag = 0;
                SerialNo3.length = 0;
                break;
            }
            // 只为获取长度信息
            else if (isGetLength)
            {
                *refLength = SerialNo3.length;
                break;
            }
            else if (isGetString)
            {
                COPY_DATA(SerialNo3.data, refData, 0, strlen(SerialNo3.data));
                SerialNo3.receiveFinishFlag = 0;
                SerialNo3.length = 0;
                break;
            }
            // 如果长度为0证明它想要获取全部串口长度数据
            else if (*refLength == NULL)
            {
                *refLength = SerialNo3.length;
                // COPY_DATA(SerialNo3.data, refData, SerialNo3.length);
            }
            // 如果想要的长度大于了本来的长度
            else if (*refLength > SerialNo3.length)
            {
                break;
            }
            // 按指定长度去读取
            COPY_DATA(SerialNo3.data, refData, 0, *refLength);
            SerialNo3.receiveFinishFlag = 0;
            SerialNo3.length = 0;
            // refData = SerialNo3.data;
            #endif
            break;
        case Serial4:
            #if SERIAL_COM4_ENABLE
            if ((SerialNo4.receiveFinishFlag & 0x02) == false)
            {
                break;
            }
            if (isPrintUse == TRUE)
            {
                SerialSendData(Serial4, SerialNo4.data, SerialNo4.length);
                SerialNo4.receiveFinishFlag = 0;
                SerialNo4.length = 0;
                break;
            }
            // 只为获取长度信息
            else if (isGetLength)
            {
                *refLength = SerialNo4.length;
                break;
            }
            else if (isGetString)
            {
                COPY_DATA(SerialNo4.data, refData, 0, strlen(SerialNo4.data));
                SerialNo4.receiveFinishFlag = 0;
                SerialNo4.length = 0;
                break;
            }
            // 如果长度为0证明它想要获取全部串口长度数据
            else if (*refLength == NULL)
            {
                *refLength = SerialNo4.length;
                // COPY_DATA(SerialNo4.data, refData, SerialNo4.length);
            }
            // 如果想要的长度大于了本来的长度
            else if (*refLength > SerialNo4.length)
            {
                break;
            }
            // 按指定长度去读取
            COPY_DATA(SerialNo4.data, refData, 0, *refLength);
            SerialNo4.receiveFinishFlag = 0;
            SerialNo4.length = 0;
            // refData = SerialNo4.data;
            #endif
            break;
        case Serial5:
            #if SERIAL_COM5_ENABLE
            if ((SerialNo5.receiveFinishFlag & 0x02) == false)
            {
                break;
            }
            if (isPrintUse == TRUE)
            {
                SerialSendData(Serial5, SerialNo5.data, SerialNo5.length);
                SerialNo5.receiveFinishFlag = 0;
                SerialNo5.length = 0;
                break;
            }
            // 只为获取长度信息
            else if (isGetLength)
            {
                *refLength = SerialNo5.length;
                break;
            }
            else if (isGetString)
            {
                COPY_DATA(SerialNo5.data, refData, 0, strlen(SerialNo5.data));
                SerialNo5.receiveFinishFlag = 0;
                SerialNo5.length = 0;
                break;
            }
            // 如果长度为0证明它想要获取全部串口长度数据
            else if (*refLength == NULL)
            {
                *refLength = SerialNo5.length;
                // COPY_DATA(SerialNo5.data, refData, SerialNo5.length);
            }
            // 如果想要的长度大于了本来的长度
            else if (*refLength > SerialNo5.length)
            {
                break;
            }
            // 按指定长度去读取
            COPY_DATA(SerialNo5.data, refData, 0, *refLength);
            SerialNo5.receiveFinishFlag = 0;
            SerialNo5.length = 0;
            // refData = SerialNo5.data;
            #endif
            break;
        case Serial6:
            #if SERIAL_COM6_ENABLE
            if ((SerialNo6.receiveFinishFlag & 0x02) == false)
            {
                break;
            }
            if (isPrintUse == TRUE)
            {
                SerialSendData(Serial6, SerialNo6.data, SerialNo6.length);
                SerialNo6.receiveFinishFlag = 0;
                SerialNo6.length = 0;
                break;
            }
            // 只为获取长度信息
            else if (isGetLength)
            {
                *refLength = SerialNo6.length;
                break;
            }
            else if (isGetString)
            {
                COPY_DATA(SerialNo6.data, refData, 0, strlen(SerialNo6.data));
                SerialNo6.receiveFinishFlag = 0;
                SerialNo6.length = 0;
                break;
            }
            // 如果长度为0证明它想要获取全部串口长度数据
            else if (*refLength == NULL)
            {
                *refLength = SerialNo6.length;
                // COPY_DATA(SerialNo6.data, refData, SerialNo6.length);
            }
            // 如果想要的长度大于了本来的长度
            else if (*refLength > SerialNo6.length)
            {
                break;
            }
            // 按指定长度去读取
            COPY_DATA(SerialNo6.data, refData, 0, *refLength);
            SerialNo6.receiveFinishFlag = 0;
            SerialNo6.length = 0;
            // refData = SerialNo6.data;
            #endif
            break;
        default:
            break;
    }
    #if SYS_FREERTOS_ENABLE
    taskEXIT_CRITICAL();
    #elif SYS_RT_THREAD_ENABLE
    /* 退出临界段 */
    rt_exit_critical();
    #endif
}
