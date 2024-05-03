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
    /* 为方便使用，在延时函数内部调用CPU_TS_TmrInit函数初始化时间戳寄存器，
        这样每次调用函数都会初始化一遍。
        把本宏值设置为0，然后在main函数刚运行时调用CPU_TS_TmrInit可避免每次都初始化
    */

    #define CPU_TS_INIT_IN_DELAY_FUNCTION   0
    
    #endif
    #ifdef __cplusplus
    }
    #endif
#endif
