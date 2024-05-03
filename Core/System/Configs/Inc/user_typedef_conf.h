#ifndef __MY_USER_TYPEDEF_CONF_H__
    #define __MY_USER_TYPEDEF_CONF_H__
    #ifdef __cplusplus
    extern "C" {
    #endif
    #include "general_conf.h"
    typedef struct
    {
        Bool Instance;
        CAN_HandleTypeDef Handle;
        CAN_TxHeaderTypeDef TxHeader;
        CAN_RxHeaderTypeDef RxHeader;
        uint8_t* Data;
        __IO uint8_t Status;
    } CANManager_TypeDef;
    #ifdef __cplusplus
    }
    #endif
#endif
