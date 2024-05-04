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
    
    #define COPY_DATA_TO(orgArr, desArr, start, end)     do { \
        uint32_t _i_, _j_; \
        for (_i_ = start, _j_ = 0; _i_ < end; ++_i_, ++_j_) \
        { \
            desArr[_i_] = orgArr[_j_]; \
        } \
    } while (0)
    
    #define LIMIT(x, max, min)                  ((x < max ) ? ((x > min ) ? x : min) : max)
    #define MAX(a, b, c)                        (a > b ? a : b > c ? b : c)
    #define MIN(a, b, c)                        (a < b ? a : b < c ? b : c)

    #ifdef __cplusplus
    }
    #endif
#endif
