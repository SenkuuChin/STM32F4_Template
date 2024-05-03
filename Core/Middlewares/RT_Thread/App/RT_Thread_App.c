#include "global_conf.h"
#include "RT_Thread_App.h"
#include "RT_ThreadHelper.h"
#include "BSP/led/led.h"



/* �����߳̿��ƿ� */
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
        /* �ȴ������¼���־ */
        recved = rt_event_recv(timerTimeoutEvent,  /* �¼������� */
                    TIMER1_TIMEOUT | TIMER6_TIMEOUT,/* �����̸߳���Ȥ���¼� */
                    RT_EVENT_FLAG_AND | RT_EVENT_FLAG_CLEAR,/* ����ѡ�� */
                    RT_WAITING_FOREVER,/* ָ����ʱ�¼�,һֱ�� */
                    &recved);    /* ָ����յ����¼� */
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
    // �߳� 1 ����ʱ���߳�2����
    // rt_thread_startup(LED1_Thread);
    /* ���̴߳�����ɣ��ر���ʼ�߳� */
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
    /* ����һ���¼� */
    timerTimeoutEvent = rt_event_create("test_event",/* �¼���־������ */
                            RT_IPC_FLAG_PRIO); /* �¼�ģʽ FIFO(0x00)*/
    SYSTEM_ASSERT_EXPRESS(timerTimeoutEvent == RT_NULL, result);
    // rt_thread_startup(AppThreadStart);
}

App_TypeDef App = { App_Run };
