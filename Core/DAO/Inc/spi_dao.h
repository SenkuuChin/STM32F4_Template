#ifndef __MY_SPI_DAO_H__
    #define __MY_SPI_DAO_H__
    #ifdef __cplusplus
    extern "C" {
    #endif
    #include "global_conf.h"
    typedef enum
    {
        SPINo1 = 1,
        SPINo2
    } SPIType;
    void SPI_Read(SPIType whichSPI, uint8_t regAddr, uint8_t *readData, uint16_t readDataLength);
    void SPI_Write(SPIType whichSPI, uint8_t* dat, uint16_t datLength);
    void SPI_WriteWithResponse(SPIType whichSPI, uint8_t* dat, uint8_t* respondContent, uint16_t respondLength);
    #ifdef __cplusplus
    }
    #endif
#endif
