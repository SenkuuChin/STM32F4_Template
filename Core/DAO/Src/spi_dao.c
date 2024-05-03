#include "spi_dao.h"
#include "Peripherals/spi/spi.h"

#if SPI1_ENABLE
extern SPI_HandleTypeDef hspi2;
#endif
#if SPI2_ENBALE
extern SPI_HandleTypeDef hspi2;
#endif

void SPI_Read(SPIType whichSPI,
    uint8_t regAddr, uint8_t *readData, uint16_t readDataLength)
{
    #if !SPI_HARDWARE_MODE_ENABLE
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
    #endif

    switch (whichSPI)
    {
        case SPINo1:
            #if SPI1_ENABLE
            HAL_SPI_TransmitReceive(&hspi1, &regAddr, readData, readDataLength, 1000);
            #endif
            break;
        case SPINo2:
            #if SPI2_ENABLE
            HAL_SPI_TransmitReceive(&hspi2, &regAddr, readData, readDataLength, 1000);
            #endif
            break;
    }
    #if !SPI_HARDWARE_MODE_ENABLE
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
    #endif
}

void SPI_Write(SPIType whichSPI, uint8_t* dat, uint16_t datLength)
{
    #if !SPI_HARDWARE_MODE_ENABLE
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
    #endif

    switch (whichSPI)
    {
        case SPINo1:
            #if SPI1_ENABLE
            HAL_SPI_Transmit(&hspi1, dat, datLength, 1000);
            #endif
            break;
        case SPINo2:
            #if SPI2_ENABLE
            HAL_SPI_Transmit(&hspi2, dat, datLength, 1000);
            #endif
            break;
    }

    #if !SPI_HARDWARE_MODE_ENABLE
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
    #endif
}

void SPI_WriteWithResponse(SPIType whichSPI, uint8_t* dat,
    uint8_t* respondContent, uint16_t respondLength)
{
    #if !SPI_HARDWARE_MODE_ENABLE
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
    #endif
    switch (whichSPI)
    {
        case SPINo1:
            #if SPI1_ENABLE
            HAL_SPI_TransmitReceive(&hspi1, dat, respondContent, respondLength, 1000);
            #endif
            break;
        case SPINo2:
            #if SPI2_ENABLE
            HAL_SPI_TransmitReceive(&hspi2, dat, respondContent, respondLength, 1000);
            #endif
            break;
    }

    #if !SPI_HARDWARE_MODE_ENABLE
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
    #endif
    #if SYS_SHOW_DEBUG_INFO_ENABLE
    SerialSendData(DEBUG_INFO_OUT_DEFAULT_SERIAL, (char *)respondContent, respondLength);
    #endif
}

