#include "Peripherals/uart/uart.h"


void DMA2_Stream2_IRQHandler(void)
{
    HAL_DMA_IRQHandler(&SerialNo1.DMA_Rx_Handle);
}

void DMA2_Stream7_IRQHandler(void)
{
    HAL_DMA_IRQHandler(&SerialNo1.DMA_Tx_Handle);
}

