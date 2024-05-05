#include "global_conf.h"
#include "timer_conf.h"


#if TIMER3_ENABLE
extern TIM_HandleTypeDef g_GeneralTimer3Handle;
void TIM3_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&g_GeneralTimer3Handle);
}
#endif

#if TIMER6_ENABLE
extern TIM_HandleTypeDef g_BasicTimer6Handle;
void TIM6_DAC_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&g_BasicTimer6Handle);
}
#endif

#if TIMER7_ENABLE
extern TIM_HandleTypeDef g_BasicTimer7Handle;
void TIM7_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&g_BasicTimer7Handle);
}
#endif

#if TIMER8_ENABLE
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
uint32_t timeOverFlowFlag = 0;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM1)
    {
        #if TIMER1_ENABLE
        timeOverFlowFlag |= TIMER1_TIMEOUT;
        #endif
    }
    
    #if TIMER2_ENABLE
    else if (htim->Instance == TIM2)
    {
        timeOverFlowFlag |= TIMER2_TIMEOUT; // 把第2位置一 代表该定时器溢出
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
        timeOverFlowFlag |= TIMER3_TIMEOUT;
    }
    #endif
    
    #if TIMER4_ENABLE
    else if (htim->Instance == TIM4)
    {
        timeOverFlowFlag |= TIMER4_TIMEOUT; // 把第4位置一 代表该定时器溢出
    }
    #endif
    #if TIMER5_ENABLE
    else if (htim->Instance == TIM5)
    {
        timeOverFlowFlag |= TIMER5_TIMEOUT; // 把第5位置一 代表该定时器溢出
    }
    #endif
    #if TIMER6_ENABLE
    else if (htim->Instance == TIM6)
    {
        timeOverFlowFlag |= TIMER6_TIMEOUT; // 把第6位置一 代表该定时器溢出
    }
    #endif
    #if BASIC_TIMER7_ENABLE
    else if (htim->Instance == TIM7)
    {
        timeOverFlowFlag |= TIMER7_TIMEOUT;
    }
    #endif
    #if TIMER8_ENABLE
    else if (htim->Instance == TIM8)
    {
        timeOverFlowFlag |= TIMER8_TIMEOUT; // 把第8位置一 代表该定时器溢出
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

