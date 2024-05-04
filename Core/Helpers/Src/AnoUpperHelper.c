#include "AnoUpperHelper.h"
#include "my_version.h"

#include <string.h>
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
    
    SerialSendData(COMMAND_DEFAULT_SERIAL, (char *)data, dataLength + 6 + 2);
}

