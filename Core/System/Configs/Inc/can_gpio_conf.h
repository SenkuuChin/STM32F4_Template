#ifndef __MY_CAN_GPIO_CONF_H__
    #define __MY_CAN_GPIO_CONF_H__
    #define CAN1_RX_GPIO_PORT               GPIOB
    #define CAN1_RX_GPIO_PIN                GPIO_PIN_8
    #define CAN1_RX_GPIO_CLK_ENABLE()       do { __HAL_RCC_GPIOB_CLK_ENABLE(); } while (0)

    #define CAN1_TX_GPIO_PORT               GPIOB
    #define CAN1_TX_GPIO_PIN                GPIO_PIN_9
    #define CAN1_TX_GPIO_CLK_ENABLE()       do { __HAL_RCC_GPIOB_CLK_ENABLE(); } while (0)
#endif
