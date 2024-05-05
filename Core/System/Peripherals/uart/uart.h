#ifndef __MY_PERIPHERALS_UART_H__
    #define __MY_PERIPHERALS_UART_H__
    #ifdef __cplusplus
    extern "C" {
    #endif
    #include "general_conf.h"
    #include "serial_conf.h"
    
    typedef struct
    {
        uint8_t Instance;                   /* 实例化 */
        __IO uint8_t receiveFinishFlag;     /* 接收数据完成标识位 */
        __IO uint8_t sentFlag;              /* 发送完成标识位 */
        uint8_t tempData;                   /* 缓存数据，每次接收一个字节 */
        uint16_t length;                    /* 接收到的数据长度 */
        DMA_HandleTypeDef DMA_Rx_Handle;
        DMA_HandleTypeDef DMA_Tx_Handle;
        UART_HandleTypeDef handle;
        char* data;                         /* 接收进来最后存储的buffer */
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
