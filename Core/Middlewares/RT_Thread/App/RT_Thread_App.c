#include "global_conf.h"
#include "RT_Thread_App.h"
#include "RT_ThreadHelper.h"
#include "BSP/led/led.h"
#include "AnoUpperHelper.h"
#include "YHPIDUpperHelper.h"

#define USE_YH_UPPER            1
#define USE_ATK_UPPER           2
#define USE_ANO_UPPER           3

#define SELECT_UPPER            USE_YH_UPPER

/* �����߳̿��ƿ� */
ALIGN(RT_ALIGN_SIZE)
rt_thread_t AppThreadStart = RT_NULL;
ALIGN(RT_ALIGN_SIZE)
rt_thread_t LED1_Thread = RT_NULL;
ALIGN(RT_ALIGN_SIZE)
rt_thread_t AnoCommandPhraseThread = RT_NULL;
// Ұ��PID��λ���߳�
ALIGN(RT_ALIGN_SIZE)
rt_thread_t YHCommandThread = RT_NULL;
// Ұ����λ������
YH_PIDUpperReceivedInfo_TypeDef YH_UpperInfo = { 0 };

// �¼�
rt_event_t timerTimeoutEvent = RT_NULL;
// ��Ϣ���У������������ʹ��
rt_mq_t commandData_mq = RT_NULL;

void LED1_ThreadEntry(void *parameter)
{
    rt_uint32_t recved;
    rt_err_t result = RT_EOK;
    while (TRUE)
    {
        /* �ȴ������¼���־ */
        result = rt_event_recv(timerTimeoutEvent,               /* �¼������� */
                    TIMER6_TIMEOUT,                             /* �����̸߳���Ȥ���¼� */
                    RT_EVENT_FLAG_AND | RT_EVENT_FLAG_CLEAR,    /* ����ѡ�� */
                    RT_WAITING_FOREVER,                         /* ָ����ʱ�¼�,һֱ�� */
                    &recved);                                   /* ָ����յ����¼� */
        if (recved == TIMER6_TIMEOUT)
        {
            LED0_TOGGLE();
            // AnoAssistantLogPrintf(LOG_COLOR_GREEN, (uint8_t *)"Data is %d", recved);
            // AnoAssistantLog(LOG_COLOR_RED, (uint8_t *)"Log ok!");
        }
    }
}


void AnoCommandPhraseThreadEntry(void *parameter)
{
    rt_err_t uwRet = RT_EOK;
    uint8_t outData[50] = { 0 };
    while (TRUE)
    {
        /* ���ж�ȡ�����գ����ȴ�ʱ��Ϊһֱ�ȴ� */
        uwRet = rt_mq_recv(commandData_mq,          /* ��ȡ�����գ����е�ID(���) */
                            outData,                /* ��ȡ�����գ������ݱ���λ�� */
                            sizeof(outData),        /* ��ȡ�����գ������ݵĳ��� */
                            RT_WAITING_FOREVER);    /* �ȴ�ʱ�䣺һֱ�� */
                            
        if (uwRet != RT_EOK)
        {
            rt_kprintf("���ݽ��ճ���,�������: 0x%lx\n",uwRet);
            continue;
        }
        #if SELECT_UPPER == USE_ANO_UPPER
        if (!AnoCheckData(outData))
        {
            SerialPrint(DEBUG_INFO_OUT_DEFAULT_SERIAL, "����У�����");
            continue;
        }
        switch (outData[3])
        {
            case PARA_CMD:
                if (outData[6] == NULL)
                {
                    AnoAssistDeviceInfoGet();
                }
                break;
            default:
                break;
        }
        #elif SELECT_UPPER == USE_ATK_UPPER
        
        #elif SELECT_UPPER == USE_YH_UPPER
        
        YH_UpperCommandAnalysis(&YH_UpperInfo, outData, sizeof(outData));
        #endif
    }
}

#if SELECT_UPPER == USE_YH_UPPER
void YHCommandThreadEntry(void *parameter)
{
    while (TRUE)
    {
        
    }
}
#endif

void AppThreadStartEntry(void *arg)
{
    HandleResult result = OK;
    LED1_Thread = RTOSThreadCreate("LED1_Thread",
                                   LED1_ThreadEntry,
                                   RT_NULL,
                                   512,
                                   3,
                                   20);
    SYSTEM_ASSERT_EXPRESS(LED1_Thread == RT_NULL, result);
    AnoCommandPhraseThread = RTOSThreadCreate("AnoCommandPhraseThread",
                                   AnoCommandPhraseThreadEntry,
                                   RT_NULL,
                                   512,
                                   3,
                                   20);
    SYSTEM_ASSERT_EXPRESS(AnoCommandPhraseThread == RT_NULL, result);
    #if SELECT_UPPER == USE_ATK_UPPER
    YHCommandThread = RTOSThreadCreate("YHCommandThread",
                                   YHCommandThreadEntry,
                                   RT_NULL,
                                   512,
                                   3,
                                   20);
    SYSTEM_ASSERT_EXPRESS(YHCommandThread == RT_NULL, result);
    #endif
    RTOSThreadClose(AppThreadStart);
}

void App_Run(void)
{
    HandleResult result = OK;
    /* ����һ���¼� */
    timerTimeoutEvent = rt_event_create("test_event",   /* �¼���־������ */
                            RT_IPC_FLAG_PRIO);          /* �¼�ģʽ FIFO(0x00)*/
    SYSTEM_ASSERT_EXPRESS(timerTimeoutEvent == RT_NULL, result);
    /* ������Ϣ���� */
    commandData_mq = rt_mq_create("data_mq",    /* ��Ϣ�������� */
                            50,                 /* ��Ϣ����󳤶� */
                            50,                 /* ��Ϣ���е�������� */
                            RT_IPC_FLAG_FIFO);  /* ����ģʽ FIFO(0x00)*/
    
    SYSTEM_ASSERT_EXPRESS(commandData_mq == RT_NULL, result);
    
    AppThreadStart = RTOSThreadCreate("AppThreadStart",
                                   AppThreadStartEntry,
                                   RT_NULL,
                                   512,
                                   2,
                                   20);
    
    
    SYSTEM_ASSERT_EXPRESS(AppThreadStart == RT_NULL, result);
}

App_TypeDef App = { App_Run };
