#include "system_service.h"
#if SYS_FREERTOS_ENABLE
#include "FreeRTOS_Demo.h"
#elif SYS_RT_THREAD_ENABLE
#include "RT_Thread_App.h"
#endif
#include "BSP/led/led.h"

#if SYS_RT_THREAD_ENABLE
__IO uint8_t SystemInitialized = FALSE;
#endif
extern __IO uint32_t timeOverFlowFlag;

__IO uint16_t timeCounter = 0;

int main(void)
{
    #if !SYS_RT_THREAD_ENABLE
    SystemInitialise();
    #endif
    #if SYS_RT_THREAD_ENABLE
    SystemInitialized = TRUE;
    #endif
    #if SYS_FREERTOS_ENABLE || SYS_RT_THREAD_ENABLE
    App.exec();
    #else
    while (TRUE)
    {
        if (timeOverFlowFlag & (TIMER6_TIMEOUT))
        {
            timeOverFlowFlag &= ~TIMER6_TIMEOUT;
            if (++timeCounter >= 500)
            {
                timeCounter = 0;
                LED0_TOGGLE();
            }
        }
    }
    #endif
    return 0;
}
