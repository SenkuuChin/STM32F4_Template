#ifndef __MY_COMMON_DELAY_HELPER_H__
    #define __MY_COMMON_DELAY_HELPER_H__
    #ifdef __cplusplus
    extern "C" {
    #endif
    #include "global_conf.h"
    void Delay_Us(uint32_t nus);
    void Delay_Ms(uint16_t nms);
    void Delay_Init(uint16_t);
    #if SYS_RT_THREAD_ENABLE
    #define GET_CPU_ClkFreq()       HAL_RCC_GetSysClockFreq()
    #define SysClockFreq            165000000U
    /* Ϊ����ʹ�ã�����ʱ�����ڲ�����CPU_TS_TmrInit������ʼ��ʱ����Ĵ�����
        ����ÿ�ε��ú��������ʼ��һ�顣
        �ѱ���ֵ����Ϊ0��Ȼ����main����������ʱ����CPU_TS_TmrInit�ɱ���ÿ�ζ���ʼ��
    */

    #define CPU_TS_INIT_IN_DELAY_FUNCTION   0
    
    #endif
    #ifdef __cplusplus
    }
    #endif
#endif
