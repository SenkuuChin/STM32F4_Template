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

/* 定义线程控制块 */
ALIGN(RT_ALIGN_SIZE)
rt_thread_t AppThreadStart = RT_NULL;
ALIGN(RT_ALIGN_SIZE)
rt_thread_t LED1_Thread = RT_NULL;
ALIGN(RT_ALIGN_SIZE)
rt_thread_t AnoCommandPhraseThread = RT_NULL;
// 野火PID上位机线程
ALIGN(RT_ALIGN_SIZE)
rt_thread_t YHCommandThread = RT_NULL;
// 野火上位机解析
YH_PIDUpperReceivedInfo_TypeDef YH_UpperInfo = { 0 };

// 事件
rt_event_t timerTimeoutEvent = RT_NULL;
// 消息队列，配合命令数据使用
rt_mq_t commandData_mq = RT_NULL;

void LED1_ThreadEntry(void *parameter)
{
    rt_uint32_t recved;
    rt_err_t result = RT_EOK;
    while (TRUE)
    {
        /* 等待接收事件标志 */
        result = rt_event_recv(timerTimeoutEvent,               /* 事件对象句柄 */
                    TIMER6_TIMEOUT,                             /* 接收线程感兴趣的事件 */
                    RT_EVENT_FLAG_AND | RT_EVENT_FLAG_CLEAR,    /* 接收选项 */
                    RT_WAITING_FOREVER,                         /* 指定超时事件,一直等 */
                    &recved);                                   /* 指向接收到的事件 */
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
        /* 队列读取（接收），等待时间为一直等待 */
        uwRet = rt_mq_recv(commandData_mq,          /* 读取（接收）队列的ID(句柄) */
                            outData,                /* 读取（接收）的数据保存位置 */
                            sizeof(outData),        /* 读取（接收）的数据的长度 */
                            RT_WAITING_FOREVER);    /* 等待时间：一直等 */
                            
        if (uwRet != RT_EOK)
        {
            rt_kprintf("数据接收出错,错误代码: 0x%lx\n",uwRet);
            continue;
        }
        #if SELECT_UPPER == USE_ANO_UPPER
        if (!AnoCheckData(outData))
        {
            SerialPrint(DEBUG_INFO_OUT_DEFAULT_SERIAL, "数据校验错误！");
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
    /* 创建一个事件 */
    timerTimeoutEvent = rt_event_create("test_event",   /* 事件标志组名字 */
                            RT_IPC_FLAG_PRIO);          /* 事件模式 FIFO(0x00)*/
    SYSTEM_ASSERT_EXPRESS(timerTimeoutEvent == RT_NULL, result);
    /* 创建消息队列 */
    commandData_mq = rt_mq_create("data_mq",    /* 消息队列名字 */
                            50,                 /* 消息的最大长度 */
                            50,                 /* 消息队列的最大容量 */
                            RT_IPC_FLAG_FIFO);  /* 队列模式 FIFO(0x00)*/
    
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
