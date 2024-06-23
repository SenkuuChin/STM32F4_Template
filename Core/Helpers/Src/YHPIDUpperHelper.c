#include "YHPIDUpperHelper.h"
#include "serial_helper.h"


void YH_PIDUpperTargetSet(YHPIDChannelEnum_TypeDef channel, int targetVal)
{
    uint8_t data[15] = { 0 };
    data[0] = 0x53;
    data[1] = 0x5A;
    data[2] = 0x48;
    data[3] = 0x59;
    data[4] = channel;
    
//    switch (command)
//    {
//        case YH_PID_UPPER_TARGET_SET:
//            break;
//        case YH_PID_UPPER_ACTUAL_SET:
//            break;
//        case YH_PID_UPPER_PID_SET:
//            break;
//        case YH_PID_UPPER_START_SYNC:
//            break;
//        case YH_PID_UPPER_STOP_SYNC:
//            break;
//        case YH_PID_UPPER_CYCLE_SET:
//            break;
//        default:
//            break;
//    }
    
    data[5] = 0x0F;
    data[9] = YH_PID_UPPER_TARGET_SET;
    data[10] = targetVal;
    data[11] = targetVal >> 8;
    data[12] = targetVal >> 16;
    data[13] = targetVal >> 24;
    data[14] = 0;
}

void YH_PIDUpperActualSet(YHPIDChannelEnum_TypeDef channel, int actualVal)
{
    uint8_t data[15] = { 0 };
    data[0] = 0x53;
    data[1] = 0x5A;
    data[2] = 0x48;
    data[3] = 0x59;
    data[4] = channel;
    data[5] = 0x0F;
    data[9] = YH_PID_UPPER_ACTUAL_SET;
    data[10] = actualVal;
    data[11] = actualVal >> 8;
    data[12] = actualVal >> 16;
    data[13] = actualVal >> 24;
    data[14] = 0;
}

void YH_PIDUpperPIDSet(YHPIDChannelEnum_TypeDef channel, float kp, float ki, float kd)
{
    uint8_t data[23] = { 0 };
    data[0] = 0x53;
    data[1] = 0x5A;
    data[2] = 0x48;
    data[3] = 0x59;
    data[4] = channel;
    data[5] = 0x17;
    data[9] = YH_PID_UPPER_PID_SET;
    data[10] = kp;
    data[11] = (int)kp >> 8;
    data[12] = (int)kp >> 16;
    data[13] = (int)kp >> 24;
    
    data[14] = (int)ki;
    data[15] = (int)ki >> 8;
    data[16] = (int)ki >> 16;
    data[17] = (int)ki >> 24;
    
    data[18] = kd;
    data[19] = (int)kd >> 8;
    data[20] = (int)kd >> 16;
    data[21] = (int)kd >> 24;
    
    data[22] = 0;
}

void YH_UpperCommandAnalysis(YH_PIDUpperReceivedInfoPtr_TypeDef receivedStore,
    YH_PID_UPPER_UINT8* data, YH_PID_UPPER_UINT16 size)
{
    if (size < 0x0B)
    {
        // 最小的包要有 11 长度
        return;
    }
    unsigned int headFrame = (data[0] | data[1] << 8 | data[2] << 16 | data[3] << 24);
    if (headFrame != 0x59485A53)
    {
        // 校验帧头失败
        return;
    }
    // 暂时不管通道值，只用一个通道
    receivedStore->command = data[9];
    float my = ((float)(data[10] << 26 | data[11] << 16 | data[12] << 8 | data[13]));
    switch (data[9])
    {
        case YH_COMMAND_PID_SET:
            
            receivedStore->kp = ((float)(data[10] | data[11] << 8 | data[12] << 16 | data[13] << 26));
            receivedStore->ki = ((float)(data[14] | data[15] << 8 | data[16] << 16 | data[17] << 26));
            receivedStore->kd = ((float)(data[18] | data[19] << 8 | data[20] << 16 | data[21] << 26));
            break;
        case YH_COMMAND_TARGET_SET:
            receivedStore->targetVal = ((int)(data[10] | data[11] << 8 | data[12] << 16 | data[13] << 26));
            break;
        case YH_COMMAND_START:
            break;
        case YH_COMMAND_STOP:
            break;
        case YH_COMMAND_RESTART_SYSTEM:
            break;
        case YH_COMMAND_CYCLE_SET:
            receivedStore->cycleVal = ((unsigned int)(data[10] | data[11] >> 8 | data[12] >> 16 | data[13] >> 26));
            break;
        default:
            break;
    }
}
