#ifndef __MY_COMMON_SERIAL_HELPER_H__
    #define __MY_COMMON_SERIAL_HELPER_H__
    #ifdef __cplusplus
    extern "C" {
    #endif
    #include "user_typedef_conf.h"
    
    #define PRINT_TEMP_DATA_LENGTH      1024
    #define PRINT_AUTO_WRAP_ENABLE      1
    typedef enum
    {
        Serial1 = 1,
        Serial2,
        Serial3,
        Serial4,
        Serial5,
        Serial6,
    } SerialType;
    #define DEBUG_INFO_OUT_DEFAULT_SERIAL       Serial1
    #define COMMAND_DEFAULT_SERIAL              Serial1

    #define SerialPrint(serialType, str)                    SerialOutput(serialType, TRUE, FALSE, 0, TRUE, str)
    #define SerialPrint_NoDash(serialType, str)             SerialOutput(serialType, FALSE, FALSE, 0, TRUE, str)
    #define SerialSendData(serialType, str, length)         SerialOutput(serialType, FALSE, TRUE, length, TRUE, str)
    #define SerialPrintf(serialType, str, ...)              SerialOutput(serialType, TRUE, FALSE, 0, FALSE, str, __VA_ARGS__)
    #define SerialPrintf_NoDash(serialType, str, ...)       SerialOutput(serialType, FALSE, FALSE, 0, FALSE, str, __VA_ARGS__)
    
    #define SerialGetDataLenth(serialType, len)             SerialDataGet(serialType, NULL, len, TRUE, FALSE, FALSE)
    #define SerialGetString(serialType, refData)            SerialDataGet(serialType, refData, NULL, FALSE, TRUE, FALSE)
    #define SerialGetDataByLength(serialType, refData, len) SerialDataGet(serialType, refData, len, FALSE, FALSE, FALSE)
    // ʹ�ô˺�������Ҫ��len��ʼ������Ϊ0
    #define SerialGetData(serialType, refData, len)         SerialDataGet(serialType, refData, len, FALSE, FALSE, FALSE)
    #define SerialPrintReceivedData(serialType)             SerialDataGet(serialType, NULL, NULL, FALSE, FALSE, TRUE)

    void Serial_Init(void);
    void SerialOutput(SerialType serialType, uint8_t isNeedDash,
                        uint8_t isSpecifyLength, uint16_t dataLength,
                        uint8_t isOnlyPrint,
                        const char* format, ...);
    
    void SerialDataGet(SerialType serialType, char* refData, uint16_t *refLength,
                        Bool isGetLength, Bool isGetString, Bool isPrintUse);
    #ifdef __cplusplus
    }
    #endif
#endif
