#include "BSP/led/led.h"
#include "general_conf.h"

void LED_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = { 0 };

    LED0_GPIO_CLK_ENABLE();                                     /* LED1时钟使能 */
    LED1_GPIO_CLK_ENABLE();                                     /* LED2时钟使能 */

    GPIO_InitStructure.Pin = LED0_GPIO_PIN;                     /* LED1引脚 */
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;              /* 推挽输出 */
    GPIO_InitStructure.Pull = GPIO_PULLUP;                      /* 上拉 */
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;            /* 高速 */
    HAL_GPIO_Init(LED0_GPIO_PORT, &GPIO_InitStructure);         /* 初始化LED1引脚 */

    GPIO_InitStructure.Pin = LED1_GPIO_PIN;                     /* LED2引脚 */
    HAL_GPIO_Init(LED1_GPIO_PORT, &GPIO_InitStructure);         /* 初始化LED2引脚 */

    LED0_SET(HIGH_LEVEL);                                       /* 关闭 LED0 */
    LED1_SET(HIGH_LEVEL);                                       /* 关闭 LED1 */
}

