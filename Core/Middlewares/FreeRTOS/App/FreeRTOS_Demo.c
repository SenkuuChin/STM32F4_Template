#include "FreeRTOS_Demo.h"
#include "delay_helper.h"
#include "BSP/key/key.h"
#include "BSP/led/led.h"


/* START_TASK 任务 配置
 * 包括: 任务句柄 任务优先级 堆栈大小 创建任务
 */
#define START_TASK_PRIO 1                   /* 任务优先级 */
#define START_STK_SIZE 128                  /* 任务堆栈大小 */
TaskHandle_t StartTask_Handler;             /* 任务句柄 */

/* TASK1 任务 配置
 * 包括: 任务句柄 任务优先级 堆栈大小 创建任务
 */
#define TASK1_PRIO 3                        /* 任务优先级 */
#define TASK1_STK_SIZE 128                  /* 任务堆栈大小 */
TaskHandle_t Task1Task_Handler;             /* 任务句柄 */

/* TASK2 任务 配置
 * 包括: 任务句柄 任务优先级 堆栈大小 创建任务
 */
#define TASK2_PRIO 3                        /* 任务优先级 */
#define TASK2_STK_SIZE 128                  /* 任务堆栈大小 */
TaskHandle_t Task2Task_Handler;             /* 任务句柄 */

/* TASK3 任务 配置
 * 包括: 任务句柄 任务优先级 堆栈大小 创建任务
 */
#define TASK3_PRIO 3                        /* 任务优先级 */
#define TASK3_STK_SIZE 128                  /* 任务堆栈大小 */
TaskHandle_t Task3Task_Handler;             /* 任务句柄 */

/* TASK4 任务 配置
 * 包括: 任务句柄 任务优先级 堆栈大小 创建任务
 */
#define TASK4_PRIO 5                        /* 任务优先级 */
#define TASK4_STK_SIZE 128                  /* 任务堆栈大小 */
TaskHandle_t Task4Task_Handler;             /* 任务句柄 */

// FreeRTOS 中，优先级数字越大的证明其优先级越高。STM32中断优先级是 数字越小优先级越高。

EventGroupHandle_t Event_Handle = NULL;

// 消息队列，配合接收指令来使用
QueueHandle_t commandQueue = NULL;

void Task1(void *pvParameters)
{
    KEY_PRESS_STATE key = NO_KEY_PRESS;
    BaseType_t res = pdFAIL;
    while (TRUE)
    {
        key = Key_Scan(0);
        switch (key)
        {
            case KEY0_PRESSED:
                {
                    #if SYS_SHOW_DEBUG_INFO_ENABLE
                    SerialPrint(DEBUG_INFO_OUT_DEFAULT_SERIAL, "Key 0 pressed!");
                    #endif
                }
                break;
            case KEY1_PRESSED:
                {
                    #if SYS_SHOW_DEBUG_INFO_ENABLE
                    SerialPrint(DEBUG_INFO_OUT_DEFAULT_SERIAL, "Key 1 pressed!");
                    #endif
                }
                break;
            case KEY2_PRESSED:
                {
                    #if SYS_SHOW_DEBUG_INFO_ENABLE
                    SerialPrint(DEBUG_INFO_OUT_DEFAULT_SERIAL, "Key 2 pressed!");
                    #endif
                }
                break;
            default:
                break;
        }
        
    }
}

void Task2(void *pvParameters)
{
    uint8_t commandItem[30] = { 0 };
    while (TRUE)
    {
        // SerialPrintReceivedData(DEBUG_INFO_OUT_DEFAULT_SERIAL);
        if (xQueueReceive(commandQueue, commandItem, portMAX_DELAY) == pdPASS)
        {
            SerialSendDataByDMA(DEBUG_INFO_OUT_DEFAULT_SERIAL, (char *)commandItem, 30);
        }
    }
}

void Task3(void *pvParameters)
{
    while (TRUE)
    {
        /* xEventGroupWaitBits 函数参数说明
         * xEventGroup：事件组句柄，这是一个之前通过 xEventGroupCreate 创建的事件组。
         * uxBitsToWaitFor：这是一个位掩码，指定任务在继续执行前等待设置的位。
         * xClearOnExit：如果这个参数为 pdTRUE，函数返回时将会清除在 uxBitsToWaitFor 中设置的位。如果为 pdFALSE，则不会改变这些位。
         * xWaitForAllBits：如果这个参数为 pdTRUE，任务会等待所有指定的位都被设置。如果为 pdFALSE，则任务会在任何指定的位被设置时返回。
         * xTicksToWait：等待事件位被设置的最大时间，以节拍数（ticks）表示。如果设置为 portMAX_DELAY，则任务会无限期等待，直到所需的位被设置。
         * 等待事件标志 0 和事件标志 1
         * 如果成功等待到了事件标志 0 和 1，则清零事件标志 0 和 1
         * 等待的方式为逻辑与，即事件标志 0 和 1 需要被同时设置
         */
        xEventGroupWaitBits((EventGroupHandle_t )Event_Handle,
                            (EventBits_t )TIMER6_TIMEOUT,
                            (BaseType_t )pdTRUE,
                            (BaseType_t )pdFALSE,
                            (TickType_t )portMAX_DELAY);
        LED0_TOGGLE();
    }
}

void StartTask(void *pvParameters)
{
    taskENTER_CRITICAL();           /* 进入临界区(关闭FreeRTOS管理的所有中断) */
                                    /* vTaskSuspendAll（任务调度器）是只禁止任务的切换但是不会关闭中断 */
    /* 创建任务1 */
    xTaskCreate((TaskFunction_t)Task1,
                (const char*   )"Task1",
                (uint16_t      )TASK1_STK_SIZE,
                (void*         )NULL,
                (UBaseType_t   )TASK1_PRIO,
                (TaskHandle_t* )&Task1Task_Handler);
    /* 创建任务2 */
    xTaskCreate((TaskFunction_t)Task2,
                (const char*   )"Task2",
                (uint16_t      )TASK2_STK_SIZE,
                (void*         )NULL,
                (UBaseType_t   )TASK2_PRIO,
                (TaskHandle_t* )&Task2Task_Handler);
    /* 创建任务3 */
    xTaskCreate((TaskFunction_t)Task3,
                (const char*   )"Task3",
                (uint16_t      )TASK3_STK_SIZE,
                (void*         )NULL,
                (UBaseType_t   )TASK3_PRIO,
                (TaskHandle_t* )&Task3Task_Handler);
    vTaskDelete(StartTask_Handler); /* 删除开始任务 */
    taskEXIT_CRITICAL();            /* 退出临界区 */
}

void App_Run(void)
{
    HandleResult result = OK;
    Event_Handle = xEventGroupCreate();
    SYSTEM_ASSERT_EXPRESS(Event_Handle == NULL, result);
    // 创建一个长度是100，每个消息深度是30的队列
    commandQueue = xQueueCreate(100, sizeof(char) * 30);
    SYSTEM_ASSERT_EXPRESS(commandQueue == NULL, result);
    xTaskCreate((TaskFunction_t)StartTask,              /* 任务函数 */
                (const char*   )"StartTask",            /* 任务名称 */
                (uint16_t      )START_STK_SIZE,         /* 任务堆栈大小（字为单位） */
                (void*         )NULL,                   /* 传入给任务函数的参数 */
                (UBaseType_t   )START_TASK_PRIO,        /* 任务优先级 */
                (TaskHandle_t* )&StartTask_Handler);    /* 任务句柄 */
    vTaskStartScheduler();
}

App_TypeDef App = { App_Run };
