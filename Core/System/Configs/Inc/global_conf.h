#ifndef __MY_GLOBAL_CONF_H__
    #define __MY_GLOBAL_CONF_H__
    #ifdef __cplusplus
    extern "C" {
    #endif
    #include "serial_helper.h"
    #define RESET_ARRAY(arr, len)               do { \
        uint32_t _i_; \
        for (_i_ = 0; _i_ < len; ++_i_) \
        { \
            arr[_i_] = 0; \
        } \
    } while (0)
    #define SET_ARRAY(arr, len, val)            do { \
        uint32_t _i_; \
        for (_i_ = 0; _i_ < len; ++_i_) \
        { \
            arr[_i_] = val; \
        } \
    } while (0)
    #define COPY_DATA(orgArr, desArr, start, end)     do { \
        uint32_t _i_; \
        for (_i_ = start; _i_ < end; ++_i_) \
        { \
            desArr[_i_] = orgArr[_i_]; \
        } \
    } while (0)
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
    #ifdef __cplusplus
    }
    #endif
#endif
