#include "AnoUpperHelper.h"
#include "my_version.h"
#include "sram_helper.h"
#include <string.h>
#include <stdarg.h>
#include <stdio.h>

/*
 * ������λ��������
 * �����������֡�������λ��
 * Author: ShinKunChin
 * ע�����ļ�������������
 *
*/

void AnoCheckCalc(uint8_t* inData)
{
    uint8_t sumcheck = 0;
    uint8_t addcheck = 0;
    uint16_t flen = inData[4] + inData[5] * 256;
    for (uint16_t i = 0; i < (flen + 6); ++i)
    {
        sumcheck += inData[i];      // ��֡ͷ��ʼ����ÿһ�ֽڽ�����ͣ�ֱ�� DATA ������
        addcheck += sumcheck;       // ÿһ�ֽڵ���Ͳ���������һ�� sumcheck ���ۼ�
    }
    // �����������У������д������֡
    inData[flen + 6] = sumcheck;
    inData[flen + 7] = addcheck;
}

// �������ݺ��У��
Bool AnoCheckData(uint8_t* inData)
{
    uint8_t sumcheck = 0;
    uint8_t addcheck = 0;
    uint16_t flen = inData[4] + inData[5] * 256;
    for(uint16_t i=0; i < (flen+6); ++i)
    {
        sumcheck += inData[i];      // ��֡ͷ��ʼ����ÿһ�ֽڽ�����ͣ�ֱ�� DATA ������
        addcheck += sumcheck;       // ÿһ�ֽڵ���Ͳ���������һ�� sumcheck ���ۼ�
    }
    // ���������� sumcheck �� addcheck �ͽ��յ��� check ������ȣ�����У��ͨ������֮��������
    if(sumcheck == inData[flen + 6] && addcheck == inData[flen + 7])
        return TRUE; //У��ͨ��
    else
        return FALSE; //У��ʧ��
}

void AnoAssistDeviceInfoGet(void)
{
    // �����ֲᣬ���ֳ�������ܳ���20
    uint8_t data[15 + 20 + 2] = { 0 };
    uint8_t nameLength = strlen(deviceInfo.deviceName);
    nameLength = nameLength > 20 ? 20 : nameLength;
    
    // �õ����ݲ��ֵĳ���(-6��ȥ֡ͷ, -2 ��ȥУ��֡)
    uint16_t dataLength = 15 - 6 + nameLength;
    
    /* ֡ͷ */
    data[0] = 0xAB;
    // ���ӵ�ID��1-199 ���Զ��壬������Ԥ��
    data[1] = deviceInfo.deviceID;
    // Ŀ�������ID��Ҳ������λ��ID���̶� 0xFE
    data[2] = ANO_UPPER_ADDR;
    // ������ID
    data[3] = DEVICE_INFO_RETURN;
    // ���ݳ���
    data[4] = dataLength;
    data[5] = dataLength >> 8;
    
    /* ���� */
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
    
    /* У�� */
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
    
    /* ֡ͷ */
    data[0] = 0xAB;
    data[1] = deviceInfo.deviceID;
    data[2] = ANO_UPPER_ADDR;
    
    if (withNum)
    {
        data[3] = LOG_OUTPUT_STR_NUM;
        // ���ݳ���
        strLength += 4;    // ��һ�� int32 �ĸ��ֽ�
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
        strLength += 1; // color ����
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

