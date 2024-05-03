#if !SYS_RT_THREAD_ENABLE
#include "system_service.h"
#endif
#if SYS_FREERTOS_ENABLE
#include "FreeRTOS_Demo.h"
#elif SYS_RT_THREAD_ENABLE
#include "RT_Thread_App.h"
#endif

int main(void)
{
    #if !SYS_RT_THREAD_ENABLE
    SystemInitialise();
    #endif
    #if SYS_FREERTOS_ENABLE || SYS_RT_THREAD_ENABLE
    App.exec();
    #else
    while (true)
    {
        
    }
    #endif
    return 0;
}
