#include "Peripherals/spi/spi.h"
#include "global_conf.h"
#include "spi_conf.h"

#if SPI1_ENABLE
SPI_HandleTypeDef hspi1 = { 0 };
HandleResult SPI1_Init(void)
{
    HandleResult result = OK;
    hspi1.Instance = SPI1;
    hspi1.Init.Mode = SPI_MODE_MASTER;
    hspi1.Init.Direction = SPI_DIRECTION_2LINES;
    hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
    hspi1.Init.CLKPolarity = SPI_POLARITY_HIGH;
    hspi1.Init.CLKPhase = SPI_PHASE_2EDGE;
    #if SPI_HARDWARE_MODE_ENABLE
    // 配置为硬件输出，NSS引脚自动拉低、拉高
    hspi1.Init.NSS = SPI_NSS_HARD_OUTPUT;
    #else
    // 配置为软件输出，NSS引脚需要手动拉低、拉高
    hspi1.Init.NSS = SPI_NSS_SOFT;
    #endif
    // APB1 外设时钟是 42MHz，16分频后，SPI2 波特率就是 42 / 16 = 2.625MBits/s
    hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
    hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
    hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
    hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    #if SPI_HARDWARE_MODE_ENABLE
    hspi1.Init.CRCPolynomial = 7;
    #else
    hspi1.Init.CRCPolynomial = 10;
    #endif
    SYSTEM_ASSERT(HAL_SPI_Init(&hspi1), result);
}
#endif

#if SPI2_ENABLE
SPI_HandleTypeDef hspi2 = { 0 };
HandleResult SPI2_Init(void)
{
    HandleResult result = OK;
    hspi2.Instance = SPI2;
    hspi2.Init.Mode = SPI_MODE_MASTER;
    hspi2.Init.Direction = SPI_DIRECTION_2LINES;
    hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
    hspi2.Init.CLKPolarity = SPI_POLARITY_HIGH;
    hspi2.Init.CLKPhase = SPI_PHASE_2EDGE;
    #if SPI_HARDWARE_MODE_ENABLE
    // 配置为硬件输出，NSS引脚自动拉低、拉高
    hspi2.Init.NSS = SPI_NSS_HARD_OUTPUT;
    #else
    // 配置为软件输出，NSS引脚需要手动拉低、拉高
    hspi2.Init.NSS = SPI_NSS_SOFT;
    #endif
    // APB1 外设时钟是 42MHz，16分频后，SPI2 波特率就是 42 / 16 = 2.625MBits/s
    hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
    hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
    hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
    hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    #if SPI_HARDWARE_MODE_ENABLE
    hspi2.Init.CRCPolynomial = 7;
    #else
    hspi2.Init.CRCPolynomial = 10;
    #endif
    SYSTEM_ASSERT(HAL_SPI_Init(&hspi2), result);
}
#endif

void SPI_Initialise(void)
{
    #if SPI1_ENBALE
    SPI1_Init();
    #endif
    #if SPI2_ENBALE
    SPI2_Init();
    #endif
}
