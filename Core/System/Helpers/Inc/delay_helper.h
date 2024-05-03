#ifndef __MY_COMMON_DELAY_HELPER_H__
    #define __MY_COMMON_DELAY_HELPER_H__
    #ifdef __cplusplus
    extern "C" {
    #endif
    #include "global_conf.h"
    void Delay_Us(uint32_t nus);
    void Delay_Ms(uint16_t nms);
    void Delay_Init(uint16_t);
    
    #ifdef __cplusplus
    }
    #endif
#endif
