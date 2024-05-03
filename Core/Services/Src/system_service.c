#include "system_service.h"
#include "system_conf.h"
#if SYS_SRAM_MANAGE_ENABLE
#include "sram_helper.h"
#endif
#include "Peripherals/peripheral_index.h"
#include "BSP/bsp_index.h"


void SystemInitialise(void)
{
    HAL_Init();
    SystemClockConfig(8, 336, 2, 7);
    Delay_Init(168);
    
    #if SYS_SRAM_MANAGE_ENABLE
        SRAMHelper.Init();
    #endif
    PeripheralInitialize();
    BSP_Initialze();
}
