#include "FreeRTOS_Demo.h"
#include "delay_helper.h"
#include "BSP/key/key.h"
#include "BSP/led/led.h"


/* START_TASK ���� ����
 * ����: ������ �������ȼ� ��ջ��С ��������
 */
#define START_TASK_PRIO 1                   /* �������ȼ� */
#define START_STK_SIZE 128                  /* �����ջ��С */
TaskHandle_t StartTask_Handler;             /* ������ */

/* TASK1 ���� ����
 * ����: ������ �������ȼ� ��ջ��С ��������
 */
#define TASK1_PRIO 3                        /* �������ȼ� */
#define TASK1_STK_SIZE 128                  /* �����ջ��С */
TaskHandle_t Task1Task_Handler;             /* ������ */

/* TASK2 ���� ����
 * ����: ������ �������ȼ� ��ջ��С ��������
 */
#define TASK2_PRIO 3                        /* �������ȼ� */
#define TASK2_STK_SIZE 128                  /* �����ջ��С */
TaskHandle_t Task2Task_Handler;             /* ������ */

/* TASK3 ���� ����
 * ����: ������ �������ȼ� ��ջ��С ��������
 */
#define TASK3_PRIO 3                        /* �������ȼ� */
#define TASK3_STK_SIZE 128                  /* �����ջ��С */
TaskHandle_t Task3Task_Handler;             /* ������ */

/* TASK4 ���� ����
 * ����: ������ �������ȼ� ��ջ��С ��������
 */
#define TASK4_PRIO 5                        /* �������ȼ� */
#define TASK4_STK_SIZE 128                  /* �����ջ��С */
TaskHandle_t Task4Task_Handler;             /* ������ */

// FreeRTOS �У����ȼ�����Խ���֤�������ȼ�Խ�ߡ�STM32�ж����ȼ��� ����ԽС���ȼ�Խ�ߡ�

EventGroupHandle_t Event_Handle = NULL;

// ��Ϣ���У���Ͻ���ָ����ʹ��
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
        /* xEventGroupWaitBits ��������˵��
         * xEventGroup���¼�����������һ��֮ǰͨ�� xEventGroupCreate �������¼��顣
         * uxBitsToWaitFor������һ��λ���룬ָ�������ڼ���ִ��ǰ�ȴ����õ�λ��
         * xClearOnExit������������Ϊ pdTRUE����������ʱ��������� uxBitsToWaitFor �����õ�λ�����Ϊ pdFALSE���򲻻�ı���Щλ��
         * xWaitForAllBits������������Ϊ pdTRUE�������ȴ�����ָ����λ�������á����Ϊ pdFALSE������������κ�ָ����λ������ʱ���ء�
         * xTicksToWait���ȴ��¼�λ�����õ����ʱ�䣬�Խ�������ticks����ʾ���������Ϊ portMAX_DELAY��������������ڵȴ���ֱ�������λ�����á�
         * �ȴ��¼���־ 0 ���¼���־ 1
         * ����ɹ��ȴ������¼���־ 0 �� 1���������¼���־ 0 �� 1
         * �ȴ��ķ�ʽΪ�߼��룬���¼���־ 0 �� 1 ��Ҫ��ͬʱ����
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
    taskENTER_CRITICAL();           /* �����ٽ���(�ر�FreeRTOS����������ж�) */
                                    /* vTaskSuspendAll���������������ֻ��ֹ������л����ǲ���ر��ж� */
    /* ��������1 */
    xTaskCreate((TaskFunction_t)Task1,
                (const char*   )"Task1",
                (uint16_t      )TASK1_STK_SIZE,
                (void*         )NULL,
                (UBaseType_t   )TASK1_PRIO,
                (TaskHandle_t* )&Task1Task_Handler);
    /* ��������2 */
    xTaskCreate((TaskFunction_t)Task2,
                (const char*   )"Task2",
                (uint16_t      )TASK2_STK_SIZE,
                (void*         )NULL,
                (UBaseType_t   )TASK2_PRIO,
                (TaskHandle_t* )&Task2Task_Handler);
    /* ��������3 */
    xTaskCreate((TaskFunction_t)Task3,
                (const char*   )"Task3",
                (uint16_t      )TASK3_STK_SIZE,
                (void*         )NULL,
                (UBaseType_t   )TASK3_PRIO,
                (TaskHandle_t* )&Task3Task_Handler);
    vTaskDelete(StartTask_Handler); /* ɾ����ʼ���� */
    taskEXIT_CRITICAL();            /* �˳��ٽ��� */
}

void App_Run(void)
{
    HandleResult result = OK;
    Event_Handle = xEventGroupCreate();
    SYSTEM_ASSERT_EXPRESS(Event_Handle == NULL, result);
    // ����һ��������100��ÿ����Ϣ�����30�Ķ���
    commandQueue = xQueueCreate(100, sizeof(char) * 30);
    SYSTEM_ASSERT_EXPRESS(commandQueue == NULL, result);
    xTaskCreate((TaskFunction_t)StartTask,              /* ������ */
                (const char*   )"StartTask",            /* �������� */
                (uint16_t      )START_STK_SIZE,         /* �����ջ��С����Ϊ��λ�� */
                (void*         )NULL,                   /* ������������Ĳ��� */
                (UBaseType_t   )START_TASK_PRIO,        /* �������ȼ� */
                (TaskHandle_t* )&StartTask_Handler);    /* ������ */
    vTaskStartScheduler();
}

App_TypeDef App = { App_Run };
