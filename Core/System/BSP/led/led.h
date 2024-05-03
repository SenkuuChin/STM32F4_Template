#ifndef __MY_BSP_LED_H__
    #ifdef __cplusplus
    extern "C" {
    #endif
    #define LED0_GPIO_PORT                  GPIOE
    #define LED0_GPIO_PIN                   GPIO_PIN_0
    #define LED0_GPIO_CLK_ENABLE()          do { __HAL_RCC_GPIOE_CLK_ENABLE(); }while(0)             /* LED1使能 */

    #define LED1_GPIO_PORT                  GPIOE
    #define LED1_GPIO_PIN                   GPIO_PIN_1
    #define LED1_GPIO_CLK_ENABLE()          do { __HAL_RCC_GPIOE_CLK_ENABLE(); }while(0)             /* LED2使能 */

    #define LED0_SET(LEVEL)                 do { HAL_GPIO_WritePin(LED0_GPIO_PORT, LED0_GPIO_PIN, LEVEL ? GPIO_PIN_SET : GPIO_PIN_RESET); } while (0)
    #define LED0_TOGGLE()                   do { HAL_GPIO_TogglePin(LED0_GPIO_PORT, LED0_GPIO_PIN); } while (0)

    #define LED1_SET(LEVEL)                 do { HAL_GPIO_WritePin(LED1_GPIO_PORT, LED1_GPIO_PIN, LEVEL ? GPIO_PIN_SET : GPIO_PIN_RESET); } while (0)
    #define LED1_TOGGLE()                   do { HAL_GPIO_TogglePin(LED1_GPIO_PORT, LED1_GPIO_PIN); } while (0)
    void LED_Init(void);
    #ifdef __cplusplus
    }
    #endif
#endif
