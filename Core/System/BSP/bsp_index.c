#include "BSP/bsp_index.h"
#include "BSP/key/key.h"
#include "BSP/led/led.h"


void BSP_Initialze(void)
{
    Key_Init();
    LED_Init();
}

