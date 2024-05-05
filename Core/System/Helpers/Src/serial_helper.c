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


#if (__ARMCC_VERSION >= 6010050)					/* ʹ��AC6������ʱ */
__asm(".global __use_no_semihosting\n\t");			/* ������ʹ�ð�����ģʽ */
__asm(".global __ARM_use_no_argv \n\t");			/* AC6����Ҫ����main����Ϊ�޲�����ʽ�����򲿷����̿��ܳ��ְ�����ģʽ */

#else
/* ʹ��AC5������ʱ, Ҫ�����ﶨ��__FILE �� ��ʹ�ð�����ģʽ */
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
#if SYS_RT_THREAD_ENABLE
extern __IO uint8_t SystemInitialized;
#endif

void SerialOutput(SerialType serialType, uint8_t isNeedDash,
    uint8_t isSpecifyLength, uint16_t dataLength,
    uint8_t isOnlyPrint, uint8_t needCriticalZone,
    const char* format, ...)
{
    // ��Ҫ�����ٽ�������
    if (needCriticalZone)
    {
        #if SYS_FREERTOS_ENABLE
        taskENTER_CRITICAL();
        #elif SYS_RT_THREAD_ENABLE
        /* �����ٽ�� */
        rt_enter_critical();
        #endif
    }
/* ����һ�����ͻ���������Ÿ�ʽ��������� */
    char *str = NULL;
    #if SYS_SRAM_MANAGE_ENABLE
    char *buffer = SRAMHelper.Malloc(SRAM_INTERNAL, PRINT_TEMP_DATA_LENGTH);
    #else
    char buffer[PRINT_TEMP_DATA_LENGTH] = { 0 };
    #endif
    RESET_ARRAY(buffer, PRINT_TEMP_DATA_LENGTH);
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
            /* �����ȴ������ֵ����������ֵ */
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
        /* �����ȴ������ֵ����������ֵ */
        length = PRINT_TEMP_DATA_LENGTH;
    }
    str = buffer;
    switch (serialType)
    {
        case Serial1:
            #if SERIAL_COM1_ENABLE
                if (needCriticalZone)
                {
                    SERIAL_SEND(USART1, length, str);
                }
                else
                {
                    #if SERIAL_COM1_DMA_ENABLE
                    #if SYS_RT_THREAD_ENABLE
                    // RT Thread ��������������ʽ��һ������һ�δ�ӡ��ʱ��ϵͳ��û������ʼ����ϣ��жϵȲ��ᱻ���ã�������Ҫ��һ����
                    if (SystemInitialized)
                    {
                    #endif
                        HAL_UART_Transmit_DMA(&SerialNo1.handle, (uint8_t *)str, length);
                        // �ȴ�TX��DMA�Ĵ�����ɡ�F407IGT6 ��USART1��DMA��Stream7������ʹ�� DMA_FLAG_TCIF3_7
                        // ������ɻص������жϣ����Դ��ڴ�����ʹ���ٽ���, �����ʹ������ĵȴ����������ͻᵼ����������
                        #else
                        // �жϴ��䷽ʽҲ��Ҫ�жϿ���
                        // HAL_UART_Transmit_IT(&SerialNo1.handle, (uint8_t *)str, length);
                        #endif
                        // �ȴ��������
                        while (!SerialNo1.sentFlag);
                    #if SYS_RT_THREAD_ENABLE
                    }
                    else
                    {
                        SERIAL_SEND(USART1, length, str);
                    }
                    #endif
                }
                SerialNo1.sentFlag = FALSE;
            #endif
            break;
        case Serial2:
            
            #if SERIAL_COM2_ENABLE
            if (needCriticalZone)
            {
                SERIAL_SEND(USART2, length, str);
            }
            else
            {
                #if SERIAL_COM2_DMA_ENABLE
                #if SYS_RT_THREAD_ENABLE
                // RT Thread ��������������ʽ��һ������һ�δ�ӡ��ʱ��ϵͳ��û������ʼ����ϣ��жϵȲ��ᱻ���ã�������Ҫ��һ����
                if (SystemInitialized)
                {
                #endif
                    HAL_UART_Transmit_DMA(&SerialNo2.handle, (uint8_t *)str, length);
                    // ������ɻص������жϣ����Դ��ڴ�����ʹ���ٽ���, �����ʹ������ĵȴ����������ͻᵼ����������
                #else
                    // �жϴ��䷽ʽҲ��Ҫ�жϿ���
                    // HAL_UART_Transmit_IT(&SerialNo2.handle, (uint8_t *)str, length);
                #endif
                    // �ȴ��������
                    while (!SerialNo2.sentFlag);
                #if SYS_RT_THREAD_ENABLE
                }
                else
                {
                    SERIAL_SEND(USART2, length, str);
                }
                #endif
            }
            SerialNo2.sentFlag = FALSE;
            #endif
            break;
        case Serial3:
            #if SERIAL_COM3_ENABLE
            if (needCriticalZone)
            {
                SERIAL_SEND(USART3, length, str);
            }
            else
            {
                #if SERIAL_COM3_DMA_ENABLE
                #if SYS_RT_THREAD_ENABLE
                // RT Thread ��������������ʽ��һ������һ�δ�ӡ��ʱ��ϵͳ��û������ʼ����ϣ��жϵȲ��ᱻ���ã�������Ҫ��һ����
                if (SystemInitialized)
                {
                #endif
                    HAL_UART_Transmit_DMA(&SerialNo3.handle, (uint8_t *)str, length);
                    // ������ɻص������жϣ����Դ��ڴ�����ʹ���ٽ���, �����ʹ������ĵȴ����������ͻᵼ����������
                #else
                    // �жϴ��䷽ʽҲ��Ҫ�жϿ���
                    // HAL_UART_Transmit_IT(&SerialNo3.handle, (uint8_t *)str, length);
                #endif
                    // �ȴ��������
                    while (!SerialNo3.sentFlag);
                #if SYS_RT_THREAD_ENABLE
                }
                else
                {
                    SERIAL_SEND(USART3, length, str);
                }
                #endif
            }
            SerialNo3.sentFlag = FALSE;
            #endif
            break;
        case Serial4:
            #if SERIAL_COM4_ENABLE
            if (needCriticalZone)
            {
                SERIAL_SEND(UART4, length, str);
            }
            else
            {
                #if SERIAL_COM4_DMA_ENABLE
                #if SYS_RT_THREAD_ENABLE
                // RT Thread ��������������ʽ��һ������һ�δ�ӡ��ʱ��ϵͳ��û������ʼ����ϣ��жϵȲ��ᱻ���ã�������Ҫ��һ����
                if (SystemInitialized)
                {
                #endif
                    HAL_UART_Transmit_DMA(&SerialNo4.handle, (uint8_t *)str, length);
                    // ������ɻص������жϣ����Դ��ڴ�����ʹ���ٽ���, �����ʹ������ĵȴ����������ͻᵼ����������
                #else
                    // �жϴ��䷽ʽҲ��Ҫ�жϿ���
                    // HAL_UART_Transmit_IT(&SerialNo4.handle, (uint8_t *)str, length);
                #endif
                    // �ȴ��������
                    while (!SerialNo4.sentFlag);
                #if SYS_RT_THREAD_ENABLE
                }
                else
                {
                    SERIAL_SEND(UART4, length, str);
                }
                #endif
            }
            SerialNo4.sentFlag = FALSE;
            #endif
            break;
        case Serial5:
            #if SERIAL_COM5_ENABLE
            if (needCriticalZone)
            {
                SERIAL_SEND(UART5, length, str);
            }
            else
            {
                #if SERIAL_COM5_DMA_ENABLE
                #if SYS_RT_THREAD_ENABLE
                // RT Thread ��������������ʽ��һ������һ�δ�ӡ��ʱ��ϵͳ��û������ʼ����ϣ��жϵȲ��ᱻ���ã�������Ҫ��һ����
                if (SystemInitialized)
                {
                #endif
                    HAL_UART_Transmit_DMA(&SerialNo5.handle, (uint8_t *)str, length);
                    // ������ɻص������жϣ����Դ��ڴ�����ʹ���ٽ���, �����ʹ������ĵȴ����������ͻᵼ����������
                #else
                    // �жϴ��䷽ʽҲ��Ҫ�жϿ���
                    // HAL_UART_Transmit_IT(&SerialNo5.handle, (uint8_t *)str, length);
                #endif
                    // �ȴ��������
                    while (!SerialNo5.sentFlag);
                #if SYS_RT_THREAD_ENABLE
                }
                else
                {
                    SERIAL_SEND(UART5, length, str);
                }
                #endif
            }
            SerialNo5.sentFlag = FALSE;
            #endif
            break;
        case Serial6:
            #if SERIAL_COM6_ENABLE
            if (needCriticalZone)
            {
                SERIAL_SEND(USART6, length, str);
            }
            else
            {
                #if SERIAL_COM6_DMA_ENABLE
                #if SYS_RT_THREAD_ENABLE
                // RT Thread ��������������ʽ��һ������һ�δ�ӡ��ʱ��ϵͳ��û������ʼ����ϣ��жϵȲ��ᱻ���ã�������Ҫ��һ����
                if (SystemInitialized)
                {
                #endif
                    HAL_UART_Transmit_DMA(&SerialNo6.handle, (uint8_t *)str, length);
                    // ������ɻص������жϣ����Դ��ڴ�����ʹ���ٽ���, �����ʹ������ĵȴ����������ͻᵼ����������
                #else
                    // �жϴ��䷽ʽҲ��Ҫ�жϿ���
                    // HAL_UART_Transmit_IT(&SerialNo6.handle, (uint8_t *)str, length);
                #endif
                    // �ȴ��������
                    while (!SerialNo6.sentFlag);
                #if SYS_RT_THREAD_ENABLE
                }
                else
                {
                    SERIAL_SEND(USART6, length, str);
                }
                #endif
            }
            SerialNo6.sentFlag = FALSE;
            #endif
            break;
        default:
            break;
    }
    // ��ָ�����ȣ��������и�ʽ����(���Ǵ���ӡ��)
    if (isSpecifyLength == FALSE && isOnlyPrint == FALSE)
    {
        va_end(args);
    }
    #if SYS_SRAM_MANAGE_ENABLE
    SRAMHelper.Free(SRAM_INTERNAL, buffer);
    buffer = NULL;
    #else
    #endif
    str = NULL;
    serialLock = NULL;
    if (needCriticalZone)
    {
        #if SYS_FREERTOS_ENABLE
        taskEXIT_CRITICAL();
        #elif SYS_RT_THREAD_ENABLE
        /* �˳��ٽ�� */
        rt_exit_critical();
        #endif
    }
}


void SerialDataGet(SerialType serialType, char* refData, uint16_t *refLength,
                    Bool isGetLength, Bool isGetString, Bool isPrintUse)
{
    #if SYS_FREERTOS_ENABLE
    taskENTER_CRITICAL();
    #elif SYS_RT_THREAD_ENABLE
    /* �����ٽ�� */
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
            // ֻΪ��ȡ������Ϣ
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
            // �������Ϊ0֤������Ҫ��ȡȫ�����ڳ�������
            else if (*refLength == NULL)
            {
                *refLength = SerialNo1.length;
                // COPY_DATA(SerialNo1.data, refData, SerialNo1.length);
            }
            // �����Ҫ�ĳ��ȴ����˱����ĳ���
            else if (*refLength > SerialNo1.length)
            {
                break;
            }
            // ��ָ������ȥ��ȡ
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
            // ֻΪ��ȡ������Ϣ
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
            // �������Ϊ0֤������Ҫ��ȡȫ�����ڳ�������
            else if (*refLength == NULL)
            {
                *refLength = SerialNo2.length;
                // COPY_DATA(SerialNo1.data, refData, SerialNo1.length);
            }
            // �����Ҫ�ĳ��ȴ����˱����ĳ���
            else if (*refLength > SerialNo2.length)
            {
                break;
            }
            // ��ָ������ȥ��ȡ
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
            // ֻΪ��ȡ������Ϣ
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
            // �������Ϊ0֤������Ҫ��ȡȫ�����ڳ�������
            else if (*refLength == NULL)
            {
                *refLength = SerialNo3.length;
                // COPY_DATA(SerialNo3.data, refData, SerialNo3.length);
            }
            // �����Ҫ�ĳ��ȴ����˱����ĳ���
            else if (*refLength > SerialNo3.length)
            {
                break;
            }
            // ��ָ������ȥ��ȡ
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
            // ֻΪ��ȡ������Ϣ
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
            // �������Ϊ0֤������Ҫ��ȡȫ�����ڳ�������
            else if (*refLength == NULL)
            {
                *refLength = SerialNo4.length;
                // COPY_DATA(SerialNo4.data, refData, SerialNo4.length);
            }
            // �����Ҫ�ĳ��ȴ����˱����ĳ���
            else if (*refLength > SerialNo4.length)
            {
                break;
            }
            // ��ָ������ȥ��ȡ
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
            // ֻΪ��ȡ������Ϣ
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
            // �������Ϊ0֤������Ҫ��ȡȫ�����ڳ�������
            else if (*refLength == NULL)
            {
                *refLength = SerialNo5.length;
                // COPY_DATA(SerialNo5.data, refData, SerialNo5.length);
            }
            // �����Ҫ�ĳ��ȴ����˱����ĳ���
            else if (*refLength > SerialNo5.length)
            {
                break;
            }
            // ��ָ������ȥ��ȡ
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
            // ֻΪ��ȡ������Ϣ
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
            // �������Ϊ0֤������Ҫ��ȡȫ�����ڳ�������
            else if (*refLength == NULL)
            {
                *refLength = SerialNo6.length;
                // COPY_DATA(SerialNo6.data, refData, SerialNo6.length);
            }
            // �����Ҫ�ĳ��ȴ����˱����ĳ���
            else if (*refLength > SerialNo6.length)
            {
                break;
            }
            // ��ָ������ȥ��ȡ
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
    /* �˳��ٽ�� */
    rt_exit_critical();
    #endif
}
