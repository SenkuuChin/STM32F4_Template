#include "BSP/key/key.h"
#include "delay_helper.h"


#define KEY_USE_INTERRUPT               0

void Key_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;                          /* GPIO���ò����洢���� */
    KEY0_GPIO_CLK_ENABLE();                                     /* KEY0ʱ��ʹ�� */
    KEY1_GPIO_CLK_ENABLE();                                     /* KEY1ʱ��ʹ�� */
    KEY2_GPIO_CLK_ENABLE();                                     /* KEY2ʱ��ʹ�� */

    GPIO_InitStructure.Pin = KEY0_GPIO_PIN;                       /* KEY0���� */
    GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
    GPIO_InitStructure.Pull = GPIO_PULLUP;                        /* ���� */
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;              /* ���� */
    HAL_GPIO_Init(KEY0_GPIO_PORT, &GPIO_InitStructure);           /* KEY0����ģʽ����,�������� */

    GPIO_InitStructure.Pin = KEY1_GPIO_PIN;                       /* KEY1���� */
    GPIO_InitStructure.Mode = GPIO_MODE_INPUT;                    /* ���� */
    GPIO_InitStructure.Pull = GPIO_PULLUP;                        /* ���� */
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;              /* ���� */
    HAL_GPIO_Init(KEY1_GPIO_PORT, &GPIO_InitStructure);           /* KEY1����ģʽ����,�������� */

    GPIO_InitStructure.Pin = KEY2_GPIO_PIN;                       /* KEY2���� */
    #if KEY_USE_INTERRUPT
    GPIO_InitStructure.Mode = GPIO_MODE_IT_FALLING;
    #else
    GPIO_InitStructure.Mode = GPIO_MODE_INPUT;                    /* ���� */
    #endif
    GPIO_InitStructure.Pull = GPIO_PULLUP;                        /* ���� */
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;              /* ���� */
    HAL_GPIO_Init(KEY2_GPIO_PORT, &GPIO_InitStructure);           /* KEY2����ģʽ����,�������� */

    #if KEY_USE_INTERRUPT
    //	HAL_NVIC_SetPriority(EXTI2_IRQn, 5, 0);
    //	HAL_NVIC_EnableIRQ(EXTI2_IRQn);

    HAL_NVIC_SetPriority(EXTI3_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(EXTI3_IRQn);

    HAL_NVIC_SetPriority(EXTI4_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(EXTI4_IRQn);
    #endif
}

KEY_PRESS_STATE Key_Scan(uint8_t mode)
{
    static uint8_t key_up = 1;  /* �������ɿ���־ */
    KEY_PRESS_STATE keyval = NO_KEY_PRESS;

    if (mode) key_up = 1;       /* ֧������ */

    if (key_up && (KEY0 == 0 || KEY1 == 0 || KEY2 == 0))    /* �����ɿ���־Ϊ1, ��������һ������������ */
    {
        #if SYS_FREERTOS_ENABLE
        vTaskDelay(10);
        #else
        Delay_Ms(10);           /* ȥ���� */
        #endif
        key_up = 0;

        if (KEY0 == 0)  keyval = KEY0_PRESSED;

        if (KEY1 == 0)  keyval = KEY1_PRESSED;

        if (KEY2 == 0)  keyval = KEY2_PRESSED;
    }
    else if (KEY0 == 1 && KEY1 == 1 && KEY2 == 1)           /* û���κΰ�������, ��ǰ����ɿ� */
    {
        key_up = 1;
    }

    return keyval;                                          /* ���ؼ�ֵ */
}

