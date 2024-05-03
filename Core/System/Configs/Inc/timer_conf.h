#ifndef __MY_TIMER_CONF_H__
    #define __MY_TIMER_CONF_H__
    /* !!下列选项中，是ENABLE的，1为启用，0为禁用 */
    /* 时间间隔 = (分频系数 / 定时器时钟频率) × 定时器周期 */

    /* 高级控制定时器1 */
    #define TIMER1_PRESCALER                167
    // 计数模式
    #define TIMER1_COUNTER_MODE             TIM_COUNTERMODE_UP
    // 周期（TIM1为16位）
    #define TIMER1_ARR                      999
    #define TIMER1_AUTORELOADPRELOAD        TIM_AUTORELOAD_PRELOAD_DISABLE
    // 是否启用模式
    #define TIMER1_PWM_MODE_ENABLE          1
    // 是否启用翻转模式
    #define TIMER1_OC_MODE_ENABLE           0
    // 无论是PWM模式还是翻转模式，都需要指定OCMode
    #define TIMER1_OCMODE                   TIM_OCMODE_PWM1
    // 占空比（脉冲）
    #define TIMER1_PULSE                    (TIMER1_ARR + 1)
    // 极性
    #define TIMER1_OCPOLARITY               TIM_OCPOLARITY_HIGH
    // 通道开启
    #define TIMER1_CHANNEL1_ENABLE          1

    #define TIMER1_CHANNEL2_ENABLE          0

    #define TIMER1_CHANNEL3_ENABLE          0

    #define TIMER1_CHANNEL4_ENABLE          1
    // 是否自动开启
    #define TIMER1_PWM_MODE_AUTO_START      1

    /* 定时器2 */
    // 预分频器，按实际需要修改此分频器值
    #define TIMER2_PRESCALER                4
    // 计数模式
    #define TIMER2_COUNTER_MODE             TIM_COUNTERMODE_UP
    // 周期（TIM2为32位）
    #define TIMER2_ARR                      0xFFFFFFFF - 1
    #define TIMER2_AUTORELOADPRELOAD        TIM_AUTORELOAD_PRELOAD_DISABLE
    // 是否启用模式
    #define TIMER2_PWM_MODE_ENABLE          1
    // 是否启用翻转模式
    #define TIMER2_OC_MODE_ENABLE           0
    // 无论是PWM模式还是翻转模式，都需要指定OCMode
    #define TIMER2_OCMODE                   TIM_OCMODE_PWM1
    // 占空比（脉冲）
    #define TIMER2_PULSE                    ((TIMER2_ARR + 1) / 2)
    // 极性
    #define TIMER2_OCPOLARITY               TIM_OCPOLARITY_HIGH
    // 通道开启
    #define TIMER2_CHANNEL1_ENABLE          0

    #define TIMER2_CHANNEL2_ENABLE          1

    #define TIMER2_CHANNEL3_ENABLE          0

    #define TIMER2_CHANNEL4_ENABLE          0
    // 是否自动开启
    #define TIMER2_PWM_MODE_AUTO_START      0

    /* 定时器3 */
    #define GENERAL_TIMER3_ENCODER_ENABLE   1
    // 计数模式
    #define TIMER3_COUNTER_MODE             TIM_COUNTERMODE_UP
    // 周期（TIM1为16位）
    #define TIMER3_ARR                      0xFFFF - 1

    /* 定时器4 */
    #define TIMER4_PRESCALER                8399
    #define TIMER4_COUNTER_MODE             TIM_COUNTERMODE_UP
    #define TIMER4_ARR                      999
    #define TIMER4_AUTORELOADPRELOAD        TIM_AUTORELOAD_PRELOAD_DISABLE

    /* 基础定时器6 */
    #define TIMER6_PRESCALER                83
    // 计数模式
    #define TIMER6_COUNTER_MODE             TIM_COUNTERMODE_UP
    // 周期（TIM1为16位）
    #define TIMER6_ARR                      999
    #define TIMER6_AUTORELOADPRELOAD        TIM_AUTORELOAD_PRELOAD_DISABLE

    /* 基础定时器7 */
    #define TIMER7_PRESCALER                8399
    // 计数模式
    #define TIMER7_COUNTER_MODE             TIM_COUNTERMODE_UP
    // 周期（TIM1为16位）
    #define TIMER7_ARR                      9999
    #define TIMER7_AUTORELOADPRELOAD        TIM_AUTORELOAD_PRELOAD_DISABLE

    // 预分频器，按实际需要修改此分频器值
    #define TIMER8_PRESCALER                167
    // 计数模式
    #define TIMER8_COUNTER_MODE             TIM_COUNTERMODE_UP
    // 周期（TIM8为16位）
    #define TIMER8_ARR                      0xFFFF - 1
    #define TIMER8_AUTORELOADPRELOAD        TIM_AUTORELOAD_PRELOAD_DISABLE
    // 是否启用模式
    #define TIMER8_PWM_MODE_ENABLE          0
    // 是否启用翻转模式
    #define TIMER8_OC_MODE_ENABLE           1
    // 无论是PWM模式还是翻转模式，都需要指定OCMode
    #define TIMER8_OCMODE                   TIM_OCMODE_PWM1
    // 占空比（脉冲）
    #define TIMER8_PULSE                    ((TIMER8_ARR + 1) / 2)
    // 极性
    #define TIMER8_OCPOLARITY               TIM_OCPOLARITY_HIGH
    // 通道开启
    #define TIMER8_CHANNEL1_ENABLE          1

    #define TIMER8_CHANNEL2_ENABLE          0

    #define TIMER2_CHANNEL3_ENABLE          0

    #define TIMER2_CHANNEL4_ENABLE          0
    // 是否自动开启
    #define TIMER8_PWM_MODE_AUTO_START      0
#endif
