#ifndef __MY_PERIPHERALS_UART_H__
    #define __MY_PERIPHERALS_UART_H__
    #ifdef __cplusplus
    extern "C" {
    #endif
    #include "general_conf.h"
    #include "serial_conf.h"
    
    typedef struct
    {
        uint8_t Instance;                   /* ʵ���� */
        __IO uint8_t receiveFinishFlag;     /* ����������ɱ�ʶλ */
        __IO uint8_t sentFlag;              /* ������ɱ�ʶλ */
        uint8_t tempData;                   /* �������ݣ�ÿ�ν���һ���ֽ� */
        uint16_t length;                    /* ���յ������ݳ��� */
        DMA_HandleTypeDef DMA_Rx_Handle;
        DMA_HandleTypeDef DMA_Tx_Handle;
        UART_HandleTypeDef handle;
        char* data;                         /* ���ս������洢��buffer */
    } SerialTypeDef, *SerialTypeDefPtr;
    
    #if SERIAL_COM1_ENABLE
    extern SerialTypeDef SerialNo1;
    #endif
    
    #if SERIAL_COM2_ENABLE
    
    #if SERIAL_COM2_DMA_ENABLE
    
    #endif
    extern SerialTypeDef SerialNo2;
    #endif
    
    #if SERIAL_COM3_ENABLE
    
    extern SerialTypeDef SerialNo3;
    #endif
    
    #if SERIAL_COM4_ENABLE
    
    extern SerialTypeDef SerialNo4;
    #endif
    
    #if SERIAL_COM5_ENABLE
    
    extern TSerialTypeDef SerialNo5;
    #endif

    #if SERIAL_COM6_ENABLE
    
    extern SerialTypeDef SerialNo6;
    #endif
    void UART_Init(void);
    #ifdef __cplusplus
    }
    #endif
#endif
