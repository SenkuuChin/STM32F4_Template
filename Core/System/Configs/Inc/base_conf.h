#ifndef __MY_BASE_CONF_H__
    #define __MY_BASE_CONF_H__
    #ifdef __cplusplus
    extern "C" {
    #endif
    #include <stdint.h>
    #ifndef __cplusplus
    #define true            1
    #define false           0
    #endif
    #define nullptr         ((void *)0)
    #define NULLPTR         nullptr
    #define NULL            0
    #define INITIALIZED     1
    #define UNINITIAL       0

    #define TO_STRING(data) #data
    #define COMBINE_STRING(str1, str2) str1##str2
    typedef enum
    {
        LOW_LEVEL = 0,
        HIGH_LEVEL
    } ElectricLevel;
    typedef enum
    {
        OK = 0,
        NOT_OK,
        NO_INSTANCE,
        INSTANCE_EXIST,
        INIT_SUCCESS
    } HandleResult;
    typedef enum
    {
        FALSE = 0,
        TRUE
    } Bool;
    #ifdef __cplusplus
    }
    #endif
#endif
