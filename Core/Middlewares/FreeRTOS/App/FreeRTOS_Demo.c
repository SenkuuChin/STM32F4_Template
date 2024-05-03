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
#define TASK1_PRIO 2                        /* 任务优先级 */
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
#define TASK3_PRIO 4                        /* 任务优先级 */
#define TASK3_STK_SIZE 128                  /* 任务堆栈大小 */
TaskHandle_t Task3Task_Handler;             /* 任务句柄 */

/* TASK4 任务 配置
 * 包括: 任务句柄 任务优先级 堆栈大小 创建任务
 */
#define TASK4_PRIO 5                        /* 任务优先级 */
#define TASK4_STK_SIZE 128                  /* 任务堆栈大小 */
TaskHandle_t Task4Task_Handler;             /* 任务句柄 */

// FreeRTOS 中，优先级数字越大的证明其优先级越高。STM32中断优先级是 数字越小优先级越高。

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
        vTaskDelay(10);
    }
}

void Task2(void *pvParameters)
{
    while (TRUE)
    {
        SerialPrintReceivedData(DEBUG_INFO_OUT_DEFAULT_SERIAL);
        vTaskDelay(10);
    }
}

void Task3(void *pvParameters)
{
    while (TRUE)
    {
        LED0_TOGGLE();
        vTaskDelay(500);
        LED0_TOGGLE();
        LED1_TOGGLE();
        vTaskDelay(500);
        LED1_TOGGLE();
        vTaskDelay(500);
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
    xTaskCreate((TaskFunction_t)StartTask,              /* 任务函数 */
                (const char*   )"StartTask",            /* 任务名称 */
                (uint16_t      )START_STK_SIZE,         /* 任务堆栈大小（字为单位） */
                (void*         )NULL,                   /* 传入给任务函数的参数 */
                (UBaseType_t   )START_TASK_PRIO,        /* 任务优先级 */
                (TaskHandle_t* )&StartTask_Handler);    /* 任务句柄 */
    vTaskStartScheduler();
}

App_TypeDef App = { App_Run };
