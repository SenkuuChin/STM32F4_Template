#include "global_conf.h"
#include "timer_conf.h"


#if GENERAL_TIMER3_ENABLE
extern TIM_HandleTypeDef g_GeneralTimer3Handle;
void TIM3_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&g_GeneralTimer3Handle);
}
#endif

#if BASIC_TIMER6_ENABLE
extern TIM_HandleTypeDef g_BasicTimer6Handle;
void TIM6_DAC_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&g_BasicTimer6Handle);
}
#endif

#if BASIC_TIMER7_ENABLE
extern TIM_HandleTypeDef g_BasicTimer7Handle;
void TIM7_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&g_BasicTimer7Handle);
}
#endif

#if ADVANCED_TIMER8_ENABLE
extern TIM_HandleTypeDef g_AdvancedTimer8Handle;
#if TIMER8_OC_MODE_ENABLE
extern TIM_OC_InitTypeDef g_AdvancedTimer8OCHandle;
#endif
void TIM8_CC_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&g_AdvancedTimer8Handle);
}
#endif

int32_t encode_count_time = 0;
uint16_t timeOverFlowFlag = 0;
uint32_t FreeRTOSRunTimeTicks = 0;          /* FreeRTOS时间统计所用的节拍计数器 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM1)
    {
        #if TIMER1_ENABLE
        #endif
    }
    
    #if TIMER2_ENABLE
    else if (htim->Instance == TIM2)
    {
        timeOverFlowFlag |= (1 << 1); // 把第2位置一 代表该定时器溢出
    }
    #endif
    
    #if TIMER3_ENABLE
    else if (htim->Instance == TIM3)
    {
        #if GENERAL_TIMER3_ENCODER_ENABLE
        if(__HAL_TIM_IS_TIM_COUNTING_DOWN(&g_GeneralTimer3Handle))
        {
            --encode_count_time;
        }
        else
        {
            ++encode_count_time;
        }
        #endif
    }
    #endif
    
    #if TIMER4_ENABLE
    else if (htim->Instance == TIM4)
    {
        timeOverFlowFlag |= (1 << 3); // 把第4位置一 代表该定时器溢出
    }
    #endif
    #if TIMER5_ENABLE
    else if (htim->Instance == TIM5)
    {
        timeOverFlowFlag |= (1 << 4); // 把第5位置一 代表该定时器溢出
    }
    #endif
    #if TIMER6_ENABLE
    else if (htim->Instance == TIM6)
    {
        timeOverFlowFlag |= (1 << 5); // 把第6位置一 代表该定时器溢出
    }
    #endif
    #if BASIC_TIMER7_ENABLE
    else if (htim->Instance == TIM7)
    {
        timeOverFlowFlag |= (1 << 6);
    }
    #endif
    #if TIMER8_ENABLE
    else if (htim->Instance == TIM8)
    {
        timeOverFlowFlag |= (1 << 7); // 把第8位置一 代表该定时器溢出
    }
    #endif
}

void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM1)
    {
        
    }
    #if TIMER8_ENABLE
    else if (htim->Instance == TIM8)
    {
        
    }
    #endif
}

