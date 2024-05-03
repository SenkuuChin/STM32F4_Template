#include "Peripherals/peripheral_index.h"
#include "serial_helper.h"
#if SYS_CAN_ENABEL
#include "Peripherals/can/can.h"
#endif
#if SYS_TIMER_ENABLE
#include "Peripherals/timer/timer.h"
#endif

void PeripheralInitialize(void)
{
    #if SYS_SERIAL_ENABLE
        Serial_Init();
    #endif
    #if SYS_CAN_ENABEL
        CAN_Initialise();
    #endif
    #if SYS_TIMER_ENABLE
    Timer_Initialise();
    #endif

    #if SYS_SERIAL_ENABLE
        SerialPrint(DEBUG_INFO_OUT_DEFAULT_SERIAL, "Connected successfully!");
    #endif
}


