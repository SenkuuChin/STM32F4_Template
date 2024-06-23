#include "Peripherals/uart/uart.h"


void DMA2_Stream2_IRQHandler(void)
{
#if SERIAL_COM1_RX_DMA_ENABLE
    HAL_DMA_IRQHandler(&SerialNo1.DMA_Rx_Handle);
#endif
}

void DMA2_Stream7_IRQHandler(void)
{
#if SERIAL_COM1_TX_DMA_ENABLE
    HAL_DMA_IRQHandler(&SerialNo1.DMA_Tx_Handle);
#endif
}
