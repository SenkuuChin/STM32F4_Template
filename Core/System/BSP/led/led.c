#include "BSP/led/led.h"
#include "general_conf.h"

void LED_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = { 0 };

    LED0_GPIO_CLK_ENABLE();                                     /* LED1ʱ��ʹ�� */
    LED1_GPIO_CLK_ENABLE();                                     /* LED2ʱ��ʹ�� */

    GPIO_InitStructure.Pin = LED0_GPIO_PIN;                     /* LED1���� */
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;              /* ������� */
    GPIO_InitStructure.Pull = GPIO_PULLUP;                      /* ���� */
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;            /* ���� */
    HAL_GPIO_Init(LED0_GPIO_PORT, &GPIO_InitStructure);         /* ��ʼ��LED1���� */

    GPIO_InitStructure.Pin = LED1_GPIO_PIN;                     /* LED2���� */
    HAL_GPIO_Init(LED1_GPIO_PORT, &GPIO_InitStructure);         /* ��ʼ��LED2���� */

    LED0_SET(HIGH_LEVEL);                                       /* �ر� LED0 */
    LED1_SET(HIGH_LEVEL);                                       /* �ر� LED1 */
}

