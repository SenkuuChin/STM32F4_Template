#include "BSP/key/key.h"
#include "delay_helper.h"


#define KEY_USE_INTERRUPT               0

void Key_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;                          /* GPIO配置参数存储变量 */
    KEY0_GPIO_CLK_ENABLE();                                     /* KEY0时钟使能 */
    KEY1_GPIO_CLK_ENABLE();                                     /* KEY1时钟使能 */
    KEY2_GPIO_CLK_ENABLE();                                     /* KEY2时钟使能 */

    GPIO_InitStructure.Pin = KEY0_GPIO_PIN;                       /* KEY0引脚 */
    GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
    GPIO_InitStructure.Pull = GPIO_PULLUP;                        /* 上拉 */
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;              /* 高速 */
    HAL_GPIO_Init(KEY0_GPIO_PORT, &GPIO_InitStructure);           /* KEY0引脚模式设置,上拉输入 */

    GPIO_InitStructure.Pin = KEY1_GPIO_PIN;                       /* KEY1引脚 */
    GPIO_InitStructure.Mode = GPIO_MODE_INPUT;                    /* 输入 */
    GPIO_InitStructure.Pull = GPIO_PULLUP;                        /* 上拉 */
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;              /* 高速 */
    HAL_GPIO_Init(KEY1_GPIO_PORT, &GPIO_InitStructure);           /* KEY1引脚模式设置,上拉输入 */

    GPIO_InitStructure.Pin = KEY2_GPIO_PIN;                       /* KEY2引脚 */
    #if KEY_USE_INTERRUPT
    GPIO_InitStructure.Mode = GPIO_MODE_IT_FALLING;
    #else
    GPIO_InitStructure.Mode = GPIO_MODE_INPUT;                    /* 输入 */
    #endif
    GPIO_InitStructure.Pull = GPIO_PULLUP;                        /* 上拉 */
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;              /* 高速 */
    HAL_GPIO_Init(KEY2_GPIO_PORT, &GPIO_InitStructure);           /* KEY2引脚模式设置,上拉输入 */

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
    static uint8_t key_up = 1;  /* 按键按松开标志 */
    KEY_PRESS_STATE keyval = NO_KEY_PRESS;

    if (mode) key_up = 1;       /* 支持连按 */

    if (key_up && (KEY0 == 0 || KEY1 == 0 || KEY2 == 0))    /* 按键松开标志为1, 且有任意一个按键按下了 */
    {
        #if SYS_FREERTOS_ENABLE
        vTaskDelay(10);
        #else
        Delay_Ms(10);           /* 去抖动 */
        #endif
        key_up = 0;

        if (KEY0 == 0)  keyval = KEY0_PRESSED;

        if (KEY1 == 0)  keyval = KEY1_PRESSED;

        if (KEY2 == 0)  keyval = KEY2_PRESSED;
    }
    else if (KEY0 == 1 && KEY1 == 1 && KEY2 == 1)           /* 没有任何按键按下, 标记按键松开 */
    {
        key_up = 1;
    }

    return keyval;                                          /* 返回键值 */
}

