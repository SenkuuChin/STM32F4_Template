#include "general_conf.h"
#include "serial_gpio_conf.h"
#include "can_gpio_conf.h"
#include "timer_gpio_conf.h"


void HAL_MspInit(void)
{
    __HAL_RCC_SYSCFG_CLK_ENABLE();
    __HAL_RCC_PWR_CLK_ENABLE();
}

void HAL_CAN_MspInit(CAN_HandleTypeDef *hcan)
{
    GPIO_InitTypeDef GPIO_InitStructure = { 0 };
    if (CAN1 == hcan->Instance)
    {
        #if CAN1_ENABLE
        CAN1_RX_GPIO_CLK_ENABLE();
        CAN1_TX_GPIO_CLK_ENABLE();
        __HAL_RCC_CAN1_CLK_ENABLE();

        GPIO_InitStructure.Pin = CAN1_TX_GPIO_PIN;
        GPIO_InitStructure.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStructure.Pull = GPIO_PULLUP;
        GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
        GPIO_InitStructure.Alternate = GPIO_AF9_CAN1;
        HAL_GPIO_Init(CAN1_TX_GPIO_PORT, &GPIO_InitStructure);
        

        GPIO_InitStructure.Pin = CAN1_RX_GPIO_PIN;

        HAL_GPIO_Init(CAN1_RX_GPIO_PORT, &GPIO_InitStructure);
        
        HAL_NVIC_EnableIRQ(CAN1_RX0_IRQn);
        HAL_NVIC_SetPriority(CAN1_RX0_IRQn, 
                            SYS_DEFAULT_COMMINICATE_M_PRIORITY,
                            SYS_DEFAULT_COMMINICATE_S_PRIORITY);
        #endif
    }
    #if CAN2_ENABLE
    else if (CAN2 == hcan->Instance)
    {
        
    }
    #endif
}

void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
    GPIO_InitTypeDef GPIO_InitStructure = { 0 };
    if (huart->Instance == USART1)
    {
        #if SERIAL_COM1_ENABLE
        __HAL_RCC_USART1_CLK_ENABLE();
        SERIAL_COM1_PIN_CLK_ENABLE();
        
        GPIO_InitStructure.Pin = SERIAL_COM1_TX_PIN;
        GPIO_InitStructure.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStructure.Pull = GPIO_PULLUP;
        GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
        GPIO_InitStructure.Alternate = SERIAL_COM1_AF;
        
        HAL_GPIO_Init(SERIAL_COM1_TX_PIN_PORT, &GPIO_InitStructure);
        
        GPIO_InitStructure.Pin = SERIAL_COM1_RX_PIN;
        GPIO_InitStructure.Alternate = SERIAL_COM1_AF;
        HAL_GPIO_Init(SERIAL_COM1_RX_PIN_PORT, &GPIO_InitStructure);
    
        HAL_NVIC_EnableIRQ(USART1_IRQn);
        HAL_NVIC_SetPriority(USART1_IRQn, 
                            SYS_DEFAULT_COMMINICATE_M_PRIORITY,
                            SYS_DEFAULT_COMMINICATE_S_PRIORITY);
        #endif
    }
    #if SERIAL_COM2_ENABLE
    else if(huart->Instance == USART2)
    {
        __HAL_RCC_USART2_CLK_ENABLE();
        SERIAL_COM2_PIN_CLK_ENABLE();

        GPIO_InitStructure.Pin = SERIAL_COM2_TX_PIN;
        GPIO_InitStructure.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStructure.Pull = GPIO_PULLUP;
        GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
        GPIO_InitStructure.Alternate =  SERIAL_COM2_AF;
        HAL_GPIO_Init(SERIAL_COM2_TX_PIN_PORT, &GPIO_InitStructure);

        GPIO_InitStructure.Pin = SERIAL_COM2_RX_PIN;
        HAL_GPIO_Init(SERIAL_COM2_RX_PIN_PORT, &GPIO_InitStructure);

        HAL_NVIC_EnableIRQ(USART2_IRQn);
        HAL_NVIC_SetPriority(USART2_IRQn,
                            SYS_DEFAULT_COMMINICATE_M_PRIORITY,
                            SYS_DEFAULT_COMMINICATE_S_PRIORITY);
    }
    #endif
    #if SERIAL_COM3_ENABLE
    else if(huart->Instance == USART3)
    {
        __HAL_RCC_USART3_CLK_ENABLE();
        SERIAL_COM3_PIN_CLK_ENABLE();

        GPIO_InitStructure.Pin = SERIAL_COM3_TX_PIN;
        GPIO_InitStructure.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStructure.Pull = GPIO_PULLUP;
        GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
        GPIO_InitStructure.Alternate =  SERIAL_COM3_AF;
        HAL_GPIO_Init(SERIAL_COM3_TX_PIN_PORT, &GPIO_InitStructure);

        GPIO_InitStructure.Pin = SERIAL_COM3_RX_PIN;
        HAL_GPIO_Init(SERIAL_COM3_RX_PIN_PORT, &GPIO_InitStructure);

        HAL_NVIC_EnableIRQ(USART3_IRQn);
        HAL_NVIC_SetPriority(USART3_IRQn,
                            SYS_DEFAULT_COMMINICATE_M_PRIORITY,
                            SYS_DEFAULT_COMMINICATE_S_PRIORITY);
    }
    #endif
    #if SERIAL_COM4_ENABLE
    else if(huart->Instance == UART4)
    {
        __HAL_RCC_UART4_CLK_ENABLE();
        SERIAL_COM4_PIN_CLK_ENABLE();

        GPIO_InitStructure.Pin = SERIAL_COM4_TX_PIN;
        GPIO_InitStructure.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStructure.Pull = GPIO_PULLUP;
        GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
        GPIO_InitStructure.Alternate =  SERIAL_COM4_AF;
        HAL_GPIO_Init(SERIAL_COM4_TX_PIN_PORT, &GPIO_InitStructure);

        GPIO_InitStructure.Pin = SERIAL_COM4_RX_PIN;
        HAL_GPIO_Init(SERIAL_COM4_RX_PIN_PORT, &GPIO_InitStructure);

        HAL_NVIC_EnableIRQ(UART4_IRQn);
        HAL_NVIC_SetPriority(UART4_IRQn,
                            SYS_DEFAULT_COMMINICATE_M_PRIORITY,
                            SYS_DEFAULT_COMMINICATE_S_PRIORITY);
    }
    #endif
    #if SERIAL_COM5_ENABLE
    else if(huart->Instance == UART5)
    {
        __HAL_RCC_UART5_CLK_ENABLE();
        SERIAL_COM5_PIN_CLK_ENABLE();

        GPIO_InitStructure.Pin = SERIAL_COM5_TX_PIN;
        GPIO_InitStructure.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStructure.Pull = GPIO_PULLUP;
        GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
        GPIO_InitStructure.Alternate =  SERIAL_COM5_AF;
        HAL_GPIO_Init(SERIAL_COM5_TX_PIN_PORT, &GPIO_InitStructure);

        GPIO_InitStructure.Pin = SERIAL_COM5_RX_PIN;
        HAL_GPIO_Init(SERIAL_COM5_RX_PIN_PORT, &GPIO_InitStructure);

        HAL_NVIC_EnableIRQ(UART5_IRQn);
        HAL_NVIC_SetPriority(UART5_IRQn,
                            SYS_DEFAULT_COMMINICATE_M_PRIORITY,
                            SYS_DEFAULT_COMMINICATE_S_PRIORITY);
    }
    #endif
    #if SERIAL_COM6_ENABLE
    else if(huart->Instance == USART6)
    {
        __HAL_RCC_USART6_CLK_ENABLE();
        SERIAL_COM6_PIN_CLK_ENABLE();

        GPIO_InitStructure.Pin = SERIAL_COM6_TX_PIN;
        GPIO_InitStructure.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStructure.Pull = GPIO_PULLUP;
        GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
        GPIO_InitStructure.Alternate =  SERIAL_COM6_AF;
        HAL_GPIO_Init(SERIAL_COM6_TX_PIN_PORT, &GPIO_InitStructure);

        GPIO_InitStructure.Pin = SERIAL_COM6_RX_PIN;
        HAL_GPIO_Init(SERIAL_COM6_RX_PIN_PORT, &GPIO_InitStructure);

        HAL_NVIC_EnableIRQ(USART6_IRQn);
        HAL_NVIC_SetPriority(USART6_IRQn,
                            SYS_DEFAULT_COMMINICATE_M_PRIORITY,
                            SYS_DEFAULT_COMMINICATE_S_PRIORITY);
    }
    #endif
}