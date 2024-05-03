#ifndef __MY_CAN_DAO_H__
    #define __MY_CAN_DAO_H__
    #ifdef __cplusplus
    extern "C" {
    #endif
    #include "global_conf.h"
    HandleResult CAN_SendMsg(uint8_t* msg, uint16_t length);
    #ifdef __cplusplus
    }
    #endif
#endif
