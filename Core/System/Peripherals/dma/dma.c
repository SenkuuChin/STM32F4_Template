#include "Peripherals/dma/dma.h"
#include "general_conf.h"


void DMA_Init(void)
{
    __HAL_RCC_DMA2_CLK_ENABLE();
    
    HAL_NVIC_SetPriority(DMA2_Stream2_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(DMA2_Stream2_IRQn);
    HAL_NVIC_SetPriority(DMA2_Stream7_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(DMA2_Stream7_IRQn);
}
