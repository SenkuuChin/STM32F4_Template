#ifndef __MY_YH_PID_HELPER_H__
    #define __MY_YH_PID_HELPER_H__
    typedef unsigned char YH_PID_UPPER_UINT8;
    typedef unsigned short YH_PID_UPPER_UINT16;
    typedef unsigned int YH_PID_UPPER_UINT32;
    typedef enum
    {
        YH_PID_CHANNEL_1 = 1,
        YH_PID_CHANNEL_2,
        YH_PID_CHANNEL_3,
        YH_PID_CHANNEL_4,
        YH_PID_CHANNEL_5,
    } YHPIDChannelEnum_TypeDef;
    typedef enum
    {
        // 设置上位机通道的目标值
        YH_PID_UPPER_TARGET_SET = 1,
        // 设置上位机通道的实际值
        YH_PID_UPPER_ACTUAL_SET,
        // 设置上位机的 PID 值
        YH_PID_UPPER_PID_SET,
        // 设置上位机的启动指令(同步上位机的按钮状态)
        YH_PID_UPPER_START_SYNC,
        // 设置上位机的停止指令(同步上位机的按钮状态)
        YH_PID_UPPER_STOP_SYNC,
        // 设置上位机周期
        YH_PID_UPPER_CYCLE_SET
    } YHPIDToUpperCommandEnum_TypeDef;
    typedef enum
    {
        // 设置下位机的PID
        YH_COMMAND_PID_SET = 0x10,
        // 设置下位机的目标值
        YH_COMMAND_TARGET_SET,
        // 运行指令
        YH_COMMAND_START,
        // 停止指令
        YH_COMMAND_STOP,
        // 重启系统指令
        YH_COMMAND_RESTART_SYSTEM,
        // 设置周期指令
        YH_COMMAND_CYCLE_SET
    } YHPIDFromUpperCommandEnum_TypeDef;
    
    typedef struct 
    {
        float kp, ki, kd;
        int targetVal;
        unsigned int cycleVal;
        YHPIDFromUpperCommandEnum_TypeDef command;
    } YH_PIDUpperReceivedInfo_TypeDef, *YH_PIDUpperReceivedInfoPtr_TypeDef;
    
    void YH_UpperCommandAnalysis(YH_PIDUpperReceivedInfoPtr_TypeDef receivedStore,
                                    YH_PID_UPPER_UINT8* data, YH_PID_UPPER_UINT16 size);
#endif
