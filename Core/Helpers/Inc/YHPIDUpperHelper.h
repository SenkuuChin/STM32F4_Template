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
        // ������λ��ͨ����Ŀ��ֵ
        YH_PID_UPPER_TARGET_SET = 1,
        // ������λ��ͨ����ʵ��ֵ
        YH_PID_UPPER_ACTUAL_SET,
        // ������λ���� PID ֵ
        YH_PID_UPPER_PID_SET,
        // ������λ��������ָ��(ͬ����λ���İ�ť״̬)
        YH_PID_UPPER_START_SYNC,
        // ������λ����ָֹͣ��(ͬ����λ���İ�ť״̬)
        YH_PID_UPPER_STOP_SYNC,
        // ������λ������
        YH_PID_UPPER_CYCLE_SET
    } YHPIDToUpperCommandEnum_TypeDef;
    typedef enum
    {
        // ������λ����PID
        YH_COMMAND_PID_SET = 0x10,
        // ������λ����Ŀ��ֵ
        YH_COMMAND_TARGET_SET,
        // ����ָ��
        YH_COMMAND_START,
        // ָֹͣ��
        YH_COMMAND_STOP,
        // ����ϵͳָ��
        YH_COMMAND_RESTART_SYSTEM,
        // ��������ָ��
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
