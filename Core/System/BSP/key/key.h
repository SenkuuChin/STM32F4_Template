#ifndef __MY_BSP_KEY_H__
    #ifdef __cplusplus
    extern "C" {
    #endif
    #define KEY0_GPIO_PORT                  GPIOE
    #define KEY0_GPIO_PIN                   GPIO_PIN_2
    #define KEY0_GPIO_CLK_ENABLE()          do { __HAL_RCC_GPIOE_CLK_ENABLE(); } while(0)   /* PE��ʱ��ʹ�� */

    #define KEY1_GPIO_PORT                  GPIOE
    #define KEY1_GPIO_PIN                   GPIO_PIN_3
    #define KEY1_GPIO_CLK_ENABLE()          do { __HAL_RCC_GPIOE_CLK_ENABLE(); } while(0)   /* PE��ʱ��ʹ�� */

    #define KEY2_GPIO_PORT                  GPIOE
    #define KEY2_GPIO_PIN                   GPIO_PIN_4
    #define KEY2_GPIO_CLK_ENABLE()          do { __HAL_RCC_GPIOE_CLK_ENABLE(); } while(0)   /* PE��ʱ��ʹ�� */

    #define KEY0                            HAL_GPIO_ReadPin(KEY0_GPIO_PORT, KEY0_GPIO_PIN)     /* ��ȡKEY0���� */
    #define KEY1                            HAL_GPIO_ReadPin(KEY1_GPIO_PORT, KEY1_GPIO_PIN)     /* ��ȡKEY1���� */
    #define KEY2                            HAL_GPIO_ReadPin(KEY2_GPIO_PORT, KEY2_GPIO_PIN)     /* ��ȡKEY2���� */
    typedef enum
    {
        NO_KEY_PRESS = 0,
        KEY0_PRESSED,                   /* KEY0���� */
        KEY1_PRESSED,                   /* KEY1���� */
        KEY2_PRESSED,                   /* KEY2���� */
    } KEY_PRESS_STATE;
    void Key_Init(void);
    KEY_PRESS_STATE Key_Scan(unsigned char mode);
    #ifdef __cplusplus
    }
    #endif
#endif
