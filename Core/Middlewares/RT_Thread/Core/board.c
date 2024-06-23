/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-07-24     Tanek        the first version
 * 2018-11-12     Ernest Chen  modify copyright
 */
 
#include <stdint.h>
/* RT-Thread���ͷ�ļ� */
#include <rthw.h>
#include <rtthread.h>
/* ������Ӳ�����ͷ�ļ� */
#include "board.h"

#if 0
#define _SCB_BASE       (0xE000E010UL)
#define _SYSTICK_CTRL   (*(rt_uint32_t *)(_SCB_BASE + 0x0))
#define _SYSTICK_LOAD   (*(rt_uint32_t *)(_SCB_BASE + 0x4))
#define _SYSTICK_VAL    (*(rt_uint32_t *)(_SCB_BASE + 0x8))
#define _SYSTICK_CALIB  (*(rt_uint32_t *)(_SCB_BASE + 0xC))
#define _SYSTICK_PRI    (*(rt_uint8_t  *)(0xE000ED23UL))

/* �ⲿʱ�Ӻͺ������� */
// Updates the variable SystemCoreClock and must be called 
// whenever the core clock is changed during program execution.
extern void SystemCoreClockUpdate(void);

// Holds the system core clock, which is the system clock 
// frequency supplied to the SysTick timer and the processor 
// core clock.
extern uint32_t SystemCoreClock;

/* ϵͳ��ʱ�� SysTick ��ʼ�� */
static uint32_t _SysTick_Config(rt_uint32_t ticks)
{
    if ((ticks - 1) > 0xFFFFFF)
    {
        return 1;
    }
    
    _SYSTICK_LOAD = ticks - 1; 
    _SYSTICK_PRI = 0xFF;
    _SYSTICK_VAL  = 0;
    _SYSTICK_CTRL = 0x07;  
    
    return 0;
}
#endif

#if defined(RT_USING_USER_MAIN) && defined(RT_USING_HEAP)
/* ���ڲ� SRAM �������һ���־�̬�ڴ�����Ϊ rtt �Ķѿռ䣬��������Ϊ 4KB */
#define RT_HEAP_SIZE 1024 * 4
static uint32_t rt_heap[RT_HEAP_SIZE];     // heap default size: 4K(1024 * 4)
RT_WEAK void *rt_heap_begin_get(void)
{
    return rt_heap;
}

RT_WEAK void *rt_heap_end_get(void)
{
    return rt_heap + RT_HEAP_SIZE;
}
#endif

/** 
* @brief ������Ӳ����ʼ������
* @param ��
* @retval ��
* 
* @attention 
* RTT �ѿ�������صĳ�ʼ������ͳһ�ŵ� board.c �ļ���ʵ�֣�
* ��Ȼ���������Щ����ͳһ�ŵ� main.c �ļ�Ҳ�ǿ��Եġ�
*/
/**
 * This function will initial your board.
 */
void rt_hw_board_init()
{
    #if 0
    /* ����ϵͳʱ�� */
    /* System Clock Update */
    SystemCoreClockUpdate();
    
    /* SysTick ��ʼ�� */
    /* System Tick Configuration */
    _SysTick_Config(SystemCoreClock / RT_TICK_PER_SECOND);
    #endif

    SystemInitialise();
    
    /* ��ʼ��SysTick */
    HAL_SYSTICK_Config(HAL_RCC_GetSysClockFreq() / RT_TICK_PER_SECOND);

    /* Ӳ�� BSP ��ʼ��ͳͳ����������� LED�����ڣ�LCD �� */
    
    /* ���������ʼ������ (use INIT_BOARD_EXPORT()) */
    /* Call components board initial (use INIT_BOARD_EXPORT()) */
#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif

#if defined(RT_USING_USER_MAIN) && defined(RT_USING_HEAP)
    rt_system_heap_init(rt_heap_begin_get(), rt_heap_end_get());
#endif
}


/** 
* @brief SysTick �жϷ�����
* @param ��* @retval ��
* 
* @attention 
* SysTick �жϷ������ڹ̼����ļ� stm32f10x_it.c ��Ҳ�����ˣ�������
* �� board.c ���ֶ���һ�Σ���ô�����ʱ�������ظ�����Ĵ��󣬽��
* �����ǿ��԰� stm32f10x_it.c �е�ע�ͻ���ɾ�����ɡ�
*/
void SysTick_Handler(void)
{
    /* �����ж� */
    /* enter interrupt */
    rt_interrupt_enter();

    /* ����ʱ�� */
    rt_tick_increase();

    /* �뿪�ж� */
    /* leave interrupt */
    rt_interrupt_leave();
}