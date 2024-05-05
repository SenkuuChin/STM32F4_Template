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

#if SYS_FREERTOS_ENABLE
extern EventGroupHandle_t Event_Handle;
#elif SYS_RT_THREAD_ENABLE

#endif
uint16_t timer6Counter = 0;
int32_t encode_count_time = 0;
uint16_t timeOverFlowFlag = 0;
uint32_t FreeRTOSRunTimeTicks = 0;          /* FreeRTOSʱ��ͳ�����õĽ��ļ����� */
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
        timeOverFlowFlag |= TIMER2_TIMEOUT; // �ѵ�2λ��һ ����ö�ʱ�����
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
        timeOverFlowFlag |= TIMER4_TIMEOUT; // �ѵ�4λ��һ ����ö�ʱ�����
    }
    #endif
    #if TIMER5_ENABLE
    else if (htim->Instance == TIM5)
    {
        timeOverFlowFlag |= TIMER5_TIMEOUT; // �ѵ�5λ��һ ����ö�ʱ�����
    }
    #endif
    #if TIMER6_ENABLE
    else if (htim->Instance == TIM6)
    {
        timeOverFlowFlag |= TIMER6_TIMEOUT; // �ѵ�6λ��һ ����ö�ʱ�����
        if (++timer6Counter >= 500)
        {
            timer6Counter = 0;
            #if SYS_FREERTOS_ENABLE
                BaseType_t xHigherPriorityTaskWoken = pdFALSE;
                // �ж���ʹ�� FreeRTOS �ĺ���������Ҫ�� FreeRTOS������жϷ�Χ�ڣ���
                // ���ڻ���� configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY ������жϺ�(�� FreeRTOSConfig.h �ж���)
                xEventGroupSetBitsFromISR((EventGroupHandle_t )Event_Handle,
                                            (EventBits_t )TIMER6_TIMEOUT, &xHigherPriorityTaskWoken);
                // ����Ƿ���Ҫ�����������л�
                portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
            #elif SYS_RT_THREAD_ENABLE
            #endif
        }
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
        timeOverFlowFlag |= TIMER8_TIMEOUT; // �ѵ�8λ��һ ����ö�ʱ�����
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

