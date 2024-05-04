#include "AnoUpperHelper.h"
#include "my_version.h"
#include "sram_helper.h"
#include <string.h>
#include <stdarg.h>
#include <stdio.h>

/*
 * 匿名上位机帮助类
 * 适配匿名助手、匿名上位机
 * Author: ShinKunChin
 * 注：该文件严重依赖串口
 *
*/

void AnoCheckCalc(uint8_t* inData)
{
    uint8_t sumcheck = 0;
    uint8_t addcheck = 0;
    uint16_t flen = inData[4] + inData[5] * 256;
    for (uint16_t i = 0; i < (flen + 6); ++i)
    {
        sumcheck += inData[i];      // 从帧头开始，对每一字节进行求和，直到 DATA 区结束
        addcheck += sumcheck;       // 每一字节的求和操作，进行一次 sumcheck 的累加
    }
    // 将计算出来的校验数据写入数据帧
    inData[flen + 6] = sumcheck;
    inData[flen + 7] = addcheck;
}

// 接收数据后的校验
Bool AnoCheckData(uint8_t* inData)
{
    uint8_t sumcheck = 0;
    uint8_t addcheck = 0;
    uint16_t flen = inData[4] + inData[5] * 256;
    for(uint16_t i=0; i < (flen+6); ++i)
    {
        sumcheck += inData[i];      // 从帧头开始，对每一字节进行求和，直到 DATA 区结束
        addcheck += sumcheck;       // 每一字节的求和操作，进行一次 sumcheck 的累加
    }
    // 如果计算出的 sumcheck 和 addcheck 和接收到的 check 数据相等，代表校验通过，反之数据有误
    if(sumcheck == inData[flen + 6] && addcheck == inData[flen + 7])
        return TRUE; //校验通过
    else
        return FALSE; //校验失败
}

void AnoAssistDeviceInfoGet(void)
{
    // 根据手册，名字长度最大不能超过20
    uint8_t data[15 + 20 + 2] = { 0 };
    uint8_t nameLength = strlen(deviceInfo.deviceName);
    nameLength = nameLength > 20 ? 20 : nameLength;
    
    // 得到数据部分的长度(-6是去帧头, -2 是去校验帧)
    uint16_t dataLength = 15 - 6 + nameLength;
    
    /* 帧头 */
    data[0] = 0xAB;
    // 板子的ID，1-199 可以定义，其它是预留
    data[1] = deviceInfo.deviceID;
    // 目标机器的ID，也就是上位机ID，固定 0xFE
    data[2] = ANO_UPPER_ADDR;
    // 功能码ID
    data[3] = DEVICE_INFO_RETURN;
    // 数据长度
    data[4] = dataLength;
    data[5] = dataLength >> 8;
    
    /* 数据 */
    data[6] = deviceInfo.deviceID;
    data[7] = deviceInfo.hardwareVersion;
    data[8] = deviceInfo.hardwareVersion >> 8;
    data[9] = deviceInfo.softwareVersion;
    data[10] = deviceInfo.softwareVersion >> 8;
    data[11] = deviceInfo.blVersion;
    data[12] = deviceInfo.blVersion >> 8;
    data[13] = deviceInfo.communicationProtocolVersion;
    data[14] = deviceInfo.communicationProtocolVersion >> 8;
    COPY_DATA_TO(deviceInfo.deviceName, data, 15, 15 + nameLength);
    
    /* 校验 */
    AnoCheckCalc(data);
    
    SerialSendDataDMA(COMMAND_DEFAULT_SERIAL, data, dataLength + 6 + 2);
}

void AnoAssistantLogOutput(Bool withNum, Bool needPrint,
    LogColor_TypeDef color, int32_t num,
    uint8_t* str,
    ...
    )
{
    char* buffer = NULL;
    uint16_t strLength = 0;
    uint8_t* data = NULL;
    data = SRAMHelper.Malloc(SRAM_INTERNAL, sizeof(uint8_t) * strLength + sizeof(int32_t) + 2);
    if (data == NULL)
    {
        SRAMHelper.Free(SRAM_INTERNAL, data);
        return;
    }
    
    if (needPrint)
    {
        buffer = SRAMHelper.Malloc(SRAM_INTERNAL, PRINT_TEMP_DATA_LENGTH);
        if (buffer == NULL)
        {
            SRAMHelper.Free(SRAM_INTERNAL, buffer);
            return;
        }
        va_list args;
        va_start(args, str);
        vsnprintf(buffer, PRINT_TEMP_DATA_LENGTH, (const char*)str, args);
        strLength = strlen(buffer);
    }
    else
    {
        strLength = strlen((char *)str);
    }
    
    /* 帧头 */
    data[0] = 0xAB;
    data[1] = deviceInfo.deviceID;
    data[2] = ANO_UPPER_ADDR;
    
    if (withNum)
    {
        data[3] = LOG_OUTPUT_STR_NUM;
        // 数据长度
        strLength += 4;    // 多一个 int32 四个字节
        data[4] = strLength;
        data[5] = strLength >> 8;
        
        data[6] = num;
        data[7] = num >> 8;
        data[8] = num >> 16;
        data[9] = num >> 24;
        COPY_DATA_TO(str, data, 10, 10 + strLength + 6);
    }
    else
    {
        data[3] = LOG_OUTPUT_STR;
        strLength += 1; // color 数据
        data[4] = strLength;
        data[5] = strLength >> 8;
        data[6] = color;
        if (needPrint)
        {
            COPY_DATA_TO(buffer, data, 7, 7 + strLength + 6);
        }
        else
        {
            COPY_DATA_TO(str, data, 7, 7 + strLength + 6);
        }
    }
    AnoCheckCalc(data);
    SerialSendDataDMA(COMMAND_DEFAULT_SERIAL, data, data[4] + (data[5] * 256) + 6 + 2);
    if (needPrint || buffer != NULL)
    {
        SRAMHelper.Free(SRAM_INTERNAL, buffer);
        buffer = NULL;
    }
    SRAMHelper.Free(SRAM_INTERNAL, data);
}

