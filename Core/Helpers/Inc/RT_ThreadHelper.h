#ifndef __MY_RT_THREAD_HELPER_H__
    #define __MY_RT_THREAD_HELPER_H__
    #ifdef __cplusplus
    extern "C" {
    #endif
    #include "rtthread.h"
    rt_thread_t RTOSThreadCreate(const char *name,
                             void (*entry)(void *parameter),
                             void       *parameter,
                             rt_uint32_t stack_size,
                             rt_uint8_t  priority,
                             rt_uint32_t tick);
    rt_err_t RTOSThreadClose(rt_thread_t thread);
    #ifdef __cplusplus
    }
    #endif
#endif
