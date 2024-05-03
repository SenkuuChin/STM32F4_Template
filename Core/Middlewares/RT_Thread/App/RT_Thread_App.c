#include "global_conf.h"
#include "RT_Thread_App.h"
#include "RT_ThreadHelper.h"
#include "BSP/led/led.h"



/* 定义线程控制块 */
ALIGN(RT_ALIGN_SIZE)
rt_thread_t AppThreadStart = RT_NULL;
ALIGN(RT_ALIGN_SIZE)
rt_thread_t LED1_Thread = RT_NULL;

rt_event_t timerTimeoutEvent = RT_NULL;

void LED1_ThreadEntry(void *parameter)
{
    rt_uint32_t recved;
    while (1)
    {
        /* 等待接收事件标志 */
        recved = rt_event_recv(timerTimeoutEvent,  /* 事件对象句柄 */
                    TIMER1_TIMEOUT | TIMER6_TIMEOUT,/* 接收线程感兴趣的事件 */
                    RT_EVENT_FLAG_AND | RT_EVENT_FLAG_CLEAR,/* 接收选项 */
                    RT_WAITING_FOREVER,/* 指定超时事件,一直等 */
                    &recved);    /* 指向接收到的事件 */
        if (recved == TIMER6_TIMEOUT)
        {
            LED0_TOGGLE();
        }
        
        // rt_thread_delay(500);
    }
}

void AppThreadStartEntry(void *arg)
{
    LED1_Thread = RTOSThreadCreate("LED1_Thread",
                                   LED1_ThreadEntry,
                                   RT_NULL,
                                   128,
                                   3,
                                   20);
    // 线程 1 阻塞时，线程2创建
    // rt_thread_startup(LED1_Thread);
    /* 当线程创建完成，关闭起始线程 */
    // rt_thread_delete(AppThreadStart);
    RTOSThreadClose(AppThreadStart);
}

void App_Run(void)
{
    HandleResult result = OK;
    AppThreadStart = RTOSThreadCreate("AppThreadStart",
                                   AppThreadStartEntry,
                                   RT_NULL,
                                   256,
                                   2,
                                   20);
    
    SYSTEM_ASSERT_EXPRESS(AppThreadStart == RT_NULL, result);
    /* 创建一个事件 */
    timerTimeoutEvent = rt_event_create("test_event",/* 事件标志组名字 */
                            RT_IPC_FLAG_PRIO); /* 事件模式 FIFO(0x00)*/
    SYSTEM_ASSERT_EXPRESS(timerTimeoutEvent == RT_NULL, result);
    // rt_thread_startup(AppThreadStart);
}

App_TypeDef App = { App_Run };
