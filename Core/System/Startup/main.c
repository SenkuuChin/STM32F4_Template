#include "system_service.h"
#if SYS_FREERTOS_ENABLE
#include "FreeRTOS_Demo.h"
#endif

int main(void)
{
    SystemInitialise();
    #if SYS_FREERTOS_ENABLE
    App.exec();
    #else
    while (true)
    {
        
    }
    #endif
    return 0;
}
