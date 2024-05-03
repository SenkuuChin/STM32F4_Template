#ifndef __MY_BSP_KEY_H__
    #ifdef __cplusplus
    extern "C" {
    #endif
    #define KEY0_GPIO_PORT                  GPIOE
    #define KEY0_GPIO_PIN                   GPIO_PIN_2
    #define KEY0_GPIO_CLK_ENABLE()          do { __HAL_RCC_GPIOE_CLK_ENABLE(); } while(0)   /* PE口时钟使能 */

    #define KEY1_GPIO_PORT                  GPIOE
    #define KEY1_GPIO_PIN                   GPIO_PIN_3
    #define KEY1_GPIO_CLK_ENABLE()          do { __HAL_RCC_GPIOE_CLK_ENABLE(); } while(0)   /* PE口时钟使能 */

    #define KEY2_GPIO_PORT                  GPIOE
    #define KEY2_GPIO_PIN                   GPIO_PIN_4
    #define KEY2_GPIO_CLK_ENABLE()          do { __HAL_RCC_GPIOE_CLK_ENABLE(); } while(0)   /* PE口时钟使能 */

    #define KEY0                            HAL_GPIO_ReadPin(KEY0_GPIO_PORT, KEY0_GPIO_PIN)     /* 读取KEY0引脚 */
    #define KEY1                            HAL_GPIO_ReadPin(KEY1_GPIO_PORT, KEY1_GPIO_PIN)     /* 读取KEY1引脚 */
    #define KEY2                            HAL_GPIO_ReadPin(KEY2_GPIO_PORT, KEY2_GPIO_PIN)     /* 读取KEY2引脚 */
    typedef enum
    {
        NO_KEY_PRESS = 0,
        KEY0_PRESSED,                   /* KEY0按下 */
        KEY1_PRESSED,                   /* KEY1按下 */
        KEY2_PRESSED,                   /* KEY2按下 */
    } KEY_PRESS_STATE;
    void Key_Init(void);
    KEY_PRESS_STATE Key_Scan(unsigned char mode);
    #ifdef __cplusplus
    }
    #endif
#endif
