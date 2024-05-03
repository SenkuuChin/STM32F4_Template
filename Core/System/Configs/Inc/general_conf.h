#ifndef __MY_GENERAL_CONF_H__
    #define __MY_GENERAL_CONF_H__
    #ifdef __cplusplus
    extern "C" {
    #endif
    #include "base_conf.h"
    #include "func_conf.h"
    #include "stm32f4xx_hal.h"
    #if SYS_FREERTOS_ENABLE
    #include "FreeRTOS.h"
    #include "task.h"
    #include "queue.h"
    #include "semphr.h"
    #include "event_groups.h"
    #elif SYS_RT_THREAD_ENABLE
    #include "rtthread.h"
    #endif
    #ifdef __cplusplus
    }
    #endif
#endif
