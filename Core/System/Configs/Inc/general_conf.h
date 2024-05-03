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
    #define TIMER1_TIMEOUT          (1 << 0)
    #define TIMER2_TIMEOUT          (1 << 1)
    #define TIMER3_TIMEOUT          (1 << 2)
    #define TIMER4_TIMEOUT          (1 << 3)
    #define TIMER5_TIMEOUT          (1 << 4)
    #define TIMER6_TIMEOUT          (1 << 5)
    #define TIMER7_TIMEOUT          (1 << 6)
    #define TIMER8_TIMEOUT          (1 << 7)
    #define TIMER9_TIMEOUT          (1 << 8)
    #define TIMER10_TIMEOUT         (1 << 9)
    #define TIMER11_TIMEOUT         (1 << 10)
    #define TIMER12_TIMEOUT         (1 << 11)
    #define TIMER13_TIMEOUT         (1 << 12)
    #define TIMER14_TIMEOUT         (1 << 13)
    #define TIMER15_TIMEOUT         (1 << 14)
    #define TIMER16_TIMEOUT         (1 << 15)
    #define TIMER17_TIMEOUT         (1 << 16)
    #define TIMER18_TIMEOUT         (1 << 17)
    #define TIMER19_TIMEOUT         (1 << 18)
    #define TIMER20_TIMEOUT         (1 << 19)
    #ifdef __cplusplus
    }
    #endif
#endif
