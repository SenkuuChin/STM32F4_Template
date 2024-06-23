#ifndef __SK_FUNC_CONF_H__
    #define __SK_FUNC_CONF_H__
    /* 系统功能配置区 */
    /* Configure System function Area */
    // 配置是否启用SRAM管理
    #define SYS_SRAM_MANAGE_ENABLE              1
    #define SYS_STRING_HELPER_ENABLE            0
    #define SYS_CAN_ENABLE                      0
    #define SYS_SERIAL_ENABLE                   1
    // RTOS 启用选择
    #define SYS_FREERTOS_ENABLE                 0
    #define SYS_RT_THREAD_ENABLE                1
    #define SYS_UCOS_ENABLE                     0
    // 是否显示Debug的信息
    #define SYS_SHOW_DEBUG_INFO_ENABLE          1
    #if SYS_SHOW_DEBUG_INFO_ENABLE & !SYS_SERIAL_ENABLE
        #error For showing DEBUG info you should ENABLE <Serial> !!!
    #endif
    #define SYS_COMMAND_CONTROL_ENABLE          0
    #if SYS_COMMAND_CONTROL_ENABLE & (!SYS_SERIAL_ENABLE & !SYS_CAN_ENABLE)
        #error For using COMMAND you should ENBALE <Serial> or <CAN> !!!
    #endif
    #define SYS_IWDG_ENABLE                     0
    #define SYS_CAN_ENABEL                      1
    #define SYS_TIMER_ENABLE                    1
    #define SYS_I2C_ENABLE                      0
    #define SYS_SPI_ENABLE                      0
    #define SYS_I2C_USE_HARDWARE                1
    #define SYS_SD_ENABLE                       0
    #define SYS_ETHERNET_ENABLE                 0
    #define SYS_WWDG_ENABLE                     0
    // 默认通信优先级。M 代表主优先级 S代表子优先级
    // 除非有需要则在具体代码调整，否则默认统一
    #define SYS_DEFAULT_COMMINICATE_M_PRIORITY  2
    #define SYS_DEFAULT_COMMINICATE_S_PRIORITY  0
    /* Debug 方式选择 */
    /* pick Debug method */
    #define JTAG_ENABLE                         1
    #define SERIAL_WIRE_ENABLE                  0
    #if JTAG_ENABLE & SERIAL_WIRE_ENABLE
        #error Debug method is only one can be selected for JTAG and SERIAL WIRE
    #endif
    /* 外设区域 */
    /* Peripherals Area */
    // 串口 Serial. 注意: 有些芯片上是没有这么多串口的，开启有的即可。
    //              Note: Some chip does not has such many serial COMs. Just ENABLE the serial which the chip own.
    #define SERIAL_COM1_ENABLE                  1
    #define SERIAL_COM2_ENABLE                  0
    #define SERIAL_COM3_ENABLE                  0
    #define SERIAL_COM4_ENABLE                  0
    #define SERIAL_COM5_ENABLE                  0
    #define SERIAL_COM6_ENABLE                  0

    #if SERIAL_COM1_ENABLE
    #define SERIAL_COM1_DMA_ENABLE              1
    #define SERIAL_COM1_TX_DMA_ENABLE           0
    #define SERIAL_COM1_RX_DMA_ENABLE           1
    #endif
    #if SERIAL_COM2_ENABLE
    #define SERIAL_COM2_DMA_ENABLE              1
    #define SERIAL_COM2_TX_DMA_ENABLE           0
    #define SERIAL_COM2_RX_DMA_ENABLE           1
    #endif
    #if SERIAL_COM3_ENABLE
    #define SERIAL_COM3_DMA_ENABLE              1
    #define SERIAL_COM3_TX_DMA_ENABLE           0
    #define SERIAL_COM3_RX_DMA_ENABLE           1
    #endif
    #if SERIAL_COM4_ENABLE
    #define SERIAL_COM4_DMA_ENABLE              1
    #define SERIAL_COM4_TX_DMA_ENABLE           0
    #define SERIAL_COM4_RX_DMA_ENABLE           1
    #endif
    #if SERIAL_COM5_ENABLE
    #define SERIAL_COM5_DMA_ENABLE              1
    #define SERIAL_COM5_TX_DMA_ENABLE           0
    #define SERIAL_COM5_RX_DMA_ENABLE           1
    #endif
    #if SERIAL_COM6_ENABLE
    #define SERIAL_COM6_DMA_ENABLE              1
    #define SERIAL_COM6_TX_DMA_ENABLE           0
    #define SERIAL_COM6_RX_DMA_ENABLE           1
    #endif
    
    // CAN
    #define CAN1_ENABLE                         1
    #define CAN2_ENABLE                         0
    // I2C
    #define I2C1_ENABLE                         0
    #define I2C2_ENABLE                         0
    // SPI
    #define SPI1_ENABLE                         0
    #define SPI2_ENBALE                         0
    // Timer
    #define TIMER1_ENABLE                       0
    #define TIMER2_ENABLE                       0
    #define TIMER3_ENABLE                       0
    #define TIMER4_ENABLE                       0
    #define TIMER5_ENABLE                       0
    #define TIMER6_ENABLE                       1
    #define TIMER7_ENABLE                       0
    #define TIMER8_ENABLE                       0
    #define TIMER9_ENABLE                       0
    #define TIMER10_ENABLE                      0
    /* 自定义区域 */
    /* Custom Area */
#endif
