#include "Peripherals/uart/uart.h"
#if SYS_SRAM_MANAGE_ENABLE
#include "sram_helper.h"
#endif

#if SERIAL_COM1_ENABLE
SerialTypeDef SerialNo1 = { 0 };
#if !SYS_SRAM_MANAGE_ENABLE
char SerialNo1Data[SERIAL_DATA_LENGTH] = { 0 };
#endif

#endif
#if SERIAL_COM2_ENABLE
SerialTypeDef SerialNo2 = { 0 };
#if !SYS_SRAM_MANAGE_ENABLE
char SerialNo2Data[SERIAL_DATA_LENGTH] = { 0 };
#endif
#if SERIAL_COM2_DMA_ENABLE
DMA_HandleTypeDef hdma_usart2_tx;
#endif
#endif
#if SERIAL_COM3_ENABLE
SerialTypeDef SerialNo3 = { 0 };
#if !SYS_SRAM_MANAGE_ENABLE
char SerialNo1Data[SERIAL_DATA_LENGTH] = { 0 };
#endif
#endif
#if SERIAL_COM4_ENABLE
SerialTypeDef SerialNo4 = { 0 };
#if !SYS_SRAM_MANAGE_ENABLE
char SerialNo4Data[SERIAL_DATA_LENGTH] = { 0 };
#endif
#endif
#if SERIAL_COM5_ENABLE
SerialTypeDef SerialNo5 = { 0 };
#if !SYS_SRAM_MANAGE_ENABLE
char SerialNo5Data[SERIAL_DATA_LENGTH] = { 0 };
#endif
#endif
#if SERIAL_COM6_ENABLE
SerialTypeDef SerialNo6 = { 0 };
#if !SYS_SRAM_MANAGE_ENABLE
char SerialNo6Data[SERIAL_DATA_LENGTH] = { 0 };
#endif
#endif


__weak void UART_Init(void)
{
    #if SERIAL_COM1_ENABLE
        SerialNo1.handle.Instance = USART1;
        SerialNo1.handle.Init.BaudRate = SERIAL_COM1_BAUDRATE;
        SerialNo1.handle.Init.WordLength = UART_WORDLENGTH_8B;
        SerialNo1.handle.Init.StopBits = UART_STOPBITS_1;
        SerialNo1.handle.Init.Parity = UART_PARITY_NONE;
        SerialNo1.handle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
        SerialNo1.handle.Init.Mode = UART_MODE_TX_RX;
        HAL_UART_Init(&SerialNo1.handle);
        #if SYS_SRAM_MANAGE_ENABLE
        SerialNo1.data = SRAMHelper.Malloc(SRAM_INTERNAL, sizeof(char) * SERIAL_DATA_LENGTH);
        #else
        SerialNo1.data = SerialNo1Data;
        #endif
        #if SERIAL_COM1_DMA_ENABLE
        
        // 由于DMA传输需要检查是否完成上一次传输才发送下一次，与传统的发送没有区别，所以发送上还是使用传统的
        SerialNo1.DMA_Tx_Handle.Instance = SERIAL_COM1_DMA_TX_INSTANCE;
        SerialNo1.DMA_Tx_Handle.Init.Channel = SERIAL_COM1_DMA_TX_CHANNEL;
        SerialNo1.DMA_Tx_Handle.Init.Direction = DMA_MEMORY_TO_PERIPH;
        SerialNo1.DMA_Tx_Handle.Init.PeriphInc = DMA_PINC_DISABLE;
        SerialNo1.DMA_Tx_Handle.Init.MemInc = DMA_MINC_ENABLE;
        SerialNo1.DMA_Tx_Handle.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
        SerialNo1.DMA_Tx_Handle.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
        SerialNo1.DMA_Tx_Handle.Init.Mode = DMA_NORMAL;
        SerialNo1.DMA_Tx_Handle.Init.Priority = DMA_PRIORITY_VERY_HIGH;
        SerialNo1.DMA_Tx_Handle.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
        HAL_DMA_Init(&SerialNo1.DMA_Tx_Handle);
        __HAL_LINKDMA(&SerialNo1.handle, hdmatx, SerialNo1.DMA_Tx_Handle);
        
        SerialNo1.DMA_Rx_Handle.Instance = SERIAL_COM1_DMA_RX_INSTANCE;
        SerialNo1.DMA_Rx_Handle.Init.Channel = SERIAL_COM1_DMA_RX_CHANNEL;
        SerialNo1.DMA_Rx_Handle.Init.Direction = DMA_PERIPH_TO_MEMORY;
        SerialNo1.DMA_Rx_Handle.Init.PeriphInc = DMA_PINC_DISABLE;
        SerialNo1.DMA_Rx_Handle.Init.MemInc = DMA_MINC_ENABLE;
        SerialNo1.DMA_Rx_Handle.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
        SerialNo1.DMA_Rx_Handle.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
        SerialNo1.DMA_Rx_Handle.Init.Mode = DMA_NORMAL;
        SerialNo1.DMA_Rx_Handle.Init.Priority = DMA_PRIORITY_VERY_HIGH;
        SerialNo1.DMA_Rx_Handle.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
        HAL_DMA_Init(&SerialNo1.DMA_Rx_Handle);
        __HAL_LINKDMA(&SerialNo1.handle, hdmarx, SerialNo1.DMA_Rx_Handle);
        
        // 空闲中断，接收引脚需要配置为上拉
        // __HAL_UART_ENABLE_IT(&SerialNo1.handle, UART_IT_IDLE);
        // HAL_UART_Receive_DMA(&SerialNo1.handle, (uint8_t *)SerialNo1.data, SERIAL_DATA_LENGTH);
        // 最后的参数是一次性能接收的最大长度
        HAL_UARTEx_ReceiveToIdle_DMA(&SerialNo1.handle, (uint8_t *)SerialNo1.data, SERIAL_DATA_LENGTH);
        // 关闭串口传输过半中断
        // __HAL_DMA_DISABLE_IT(&SerialNo1.DMA_Rx_Handle, DMA_IT_HT);
        #else
        HAL_UART_Receive_IT(&SerialNo1.handle, &SerialNo1.tempData, 1);
        #endif
        
        SerialNo1.Instance = INITIALIZED;
    #endif

    #if SERIAL_COM2_ENABLE
        SerialNo2.handle.Instance = USART2;
        SerialNo2.handle.Init.BaudRate = SERIAL_COM2_BAUDRATE;
        SerialNo2.handle.Init.WordLength = UART_WORDLENGTH_8B;
        SerialNo2.handle.Init.StopBits = UART_STOPBITS_1;
        SerialNo2.handle.Init.Parity = UART_PARITY_NONE;
        SerialNo2.handle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
        SerialNo2.handle.Init.Mode = UART_MODE_TX_RX;
        HAL_UART_Init(&SerialNo2.handle);
        HAL_UART_Receive_IT(&SerialNo2.handle, &SerialNo2.tempData, 1);
        #if SYS_SRAM_MANAGE_ENABLE
        SerialNo2.data = SRAMHelper.Malloc(SRAM_INTERNAL, sizeof(char) * SERIAL_DATA_LENGTH);
        #else
        SerialNo2.data = SerialNo2Data;
        #endif
        SerialNo2.Instance = INITIALIZED;
        #if SERIAL_COM2_DMA_ENABLE

        hdma_usart2_tx.Instance = DMA1_Stream6;
        hdma_usart2_tx.Init.Channel = DMA_CHANNEL_4;
        hdma_usart2_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
        hdma_usart2_tx.Init.PeriphInc = DMA_PINC_DISABLE;
        hdma_usart2_tx.Init.MemInc = DMA_MINC_ENABLE;
        hdma_usart2_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
        hdma_usart2_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
        hdma_usart2_tx.Init.Mode = DMA_NORMAL;
        hdma_usart2_tx.Init.Priority = DMA_PRIORITY_LOW;

        HAL_DMA_Init(&hdma_usart2_tx);
//      HAL_NVIC_SetPriority(DMA1_Stream6_IRQn, 0, 0);
//      HAL_NVIC_EnableIRQ(DMA1_Stream6_IRQn);
        __HAL_LINKDMA(&SerialNo2.handle, hdmatx, hdma_usart2_tx);
        
        
        #endif
    #endif

    #if SERIAL_COM3_ENABLE
        SerialNo3.handle.Instance = USART3;
        SerialNo3.handle.Init.BaudRate = SERIAL_COM3_BAUDRATE;
        SerialNo3.handle.Init.WordLength = UART_WORDLENGTH_8B;
        SerialNo3.handle.Init.StopBits = UART_STOPBITS_1;
        SerialNo3.handle.Init.Parity = UART_PARITY_NONE;
        SerialNo3.handle.Init.Mode = UART_MODE_TX_RX;
        HAL_UART_Init(&SerialNo3.handle);
        #if SYS_SRAM_MANAGE_ENABLE
        SerialNo3.data = SRAMHelper.Malloc(SRAM_INTERNAL, sizeof(char) * SERIAL_DATA_LENGTH);
        #else
        SerialNo3.data = SerialNo3Data;
        #endif
        HAL_UART_Receive_IT(&SerialNo3.handle, &SerialNo3.tempData, 1);
        
        SerialNo3.Instance = INITIALIZED;
    #endif
    
    #if SERIAL_COM4_ENABLE
        SerialNo4.handle.Instance = UART4;
        SerialNo4.handle.Init.BaudRate = SERIAL_COM4_BAUDRATE;
        SerialNo4.handle.Init.WordLength = UART_WORDLENGTH_8B;
        SerialNo4.handle.Init.StopBits = UART_STOPBITS_1;
        SerialNo4.handle.Init.Parity = UART_PARITY_NONE;
        SerialNo4.handle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
        SerialNo4.handle.Init.Mode = UART_MODE_TX_RX;
        HAL_UART_Init(&SerialNo4.handle);
        #if SYS_SRAM_MANAGE_ENABLE
        SerialNo4.data = SRAMHelper.Malloc(SRAM_INTERNAL, sizeof(char) * SERIAL_DATA_LENGTH);
        #else
        SerialNo4.data = SerialNo4Data;
        #endif
        HAL_UART_Receive_IT(&SerialNo4.handle, &SerialNo4.temp_data, 1);
        
    #endif
    
    #if SERIAL_COM5_ENABLE
        SerialNo5.handle.Instance = USART5;
        SerialNo5.handle.Init.BaudRate = SERIAL_COM5_BAUDRATE;
        SerialNo5.handle.Init.WordLength = UART_WORDLENGTH_8B;
        SerialNo5.handle.Init.StopBits = UART_STOPBITS_1;
        SerialNo5.handle.Init.Parity = UART_PARITY_NONE;
        SerialNo5.handle.Init.Mode = UART_MODE_TX_RX;
        HAL_UART_Init(&SerialNo5.handle);
        #if SYS_SRAM_MANAGE_ENABLE
        SerialNo5.data = SRAMHelper.Malloc(SRAM_INTERNAL, sizeof(char) * SERIAL_DATA_LENGTH);
        #else
        SerialNo5.data = SerialNo5Data;
        #endif
        HAL_UART_Receive_IT(&SerialNo5.handle, &SerialNo5.tempData, 1);
        SerialNo5.Instance = INITIALIZED;
    #endif
    #if SERIAL_COM6_ENABLE
        SerialNo6.handle.Instance = USART6;
        SerialNo6.handle.Init.BaudRate = SERIAL_COM6_BAUDRATE;
        SerialNo6.handle.Init.WordLength = UART_WORDLENGTH_8B;
        SerialNo6.handle.Init.StopBits = UART_STOPBITS_1;
        SerialNo6.handle.Init.Parity = UART_PARITY_NONE;
        SerialNo6.handle.Init.Mode = UART_MODE_TX_RX;
        HAL_UART_Init(&SerialNo6.handle);
        #if SYS_SRAM_MANAGE_ENABLE
        SerialNo6.data = SRAMHelper.Malloc(SRAM_INTERNAL, sizeof(char) * SERIAL_DATA_LENGTH);
        #else
        SerialNo6.data = SerialNo6Data;
        #endif
        HAL_UART_Receive_IT(&SerialNo6.handle, &SerialNo6.tempData, 1);
        SerialNo6.Instance = INITIALIZED;
    #endif
}
