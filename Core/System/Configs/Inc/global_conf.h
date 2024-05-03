#ifndef __MY_GLOBAL_CONF_H__
    #define __MY_GLOBAL_CONF_H__
    #ifdef __cplusplus
    extern "C" {
    #endif
    #include "serial_helper.h"
    #if SYS_SHOW_DEBUG_INFO_ENABLE
    #define SYSTEM_ASSERT(__FUNC__, RES) do { \
            if (__FUNC__ != HAL_OK) \
            { \
                SerialPrintf(DEBUG_INFO_OUT_DEFAULT_SERIAL, \
                    "Funtion: %s error! File: %s , Line: %d", __FUNCTION__, __FILE__, __LINE__); \
                RES = NOT_OK; \
            } \
        } while(0)
    #else
    #define SYSTEM_ASSERT(__FUNC__, RES) do { \
        if (__FUNC__ != HAL_OK) \
        { \
            RES = NOT_OK; \
        } \
    } while(0)
    #endif

    #if SYS_SHOW_DEBUG_INFO_ENABLE
    #define SYSTEM_ASSERT_EXPRESS(__EXPRESS__, RES) do { \
            if (__EXPRESS__) \
            { \
                SerialPrintf(DEBUG_INFO_OUT_DEFAULT_SERIAL, \
                    "Funtion: %s error! File: %s , Line: %d", __FUNCTION__, __FILE__, __LINE__); \
                RES = NOT_OK; \
            } \
        } while(0)
    #else
    #define SYSTEM_ASSERT_EXPRESS(__EXPRESS__, RES) do { \
        if (__EXPRESS__) \
        { \
            RES = NOT_OK; \
        } \
    } while(0)
    #endif
    #ifdef __cplusplus
    }
    #endif
#endif
