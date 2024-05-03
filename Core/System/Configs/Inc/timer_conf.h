#ifndef __MY_TIMER_CONF_H__
    #define __MY_TIMER_CONF_H__
    /* !!����ѡ���У���ENABLE�ģ�1Ϊ���ã�0Ϊ���� */
    /* ʱ���� = (��Ƶϵ�� / ��ʱ��ʱ��Ƶ��) �� ��ʱ������ */

    /* �߼����ƶ�ʱ��1 */
    #define TIMER1_PRESCALER                167
    // ����ģʽ
    #define TIMER1_COUNTER_MODE             TIM_COUNTERMODE_UP
    // ���ڣ�TIM1Ϊ16λ��
    #define TIMER1_ARR                      999
    #define TIMER1_AUTORELOADPRELOAD        TIM_AUTORELOAD_PRELOAD_DISABLE
    // �Ƿ�����ģʽ
    #define TIMER1_PWM_MODE_ENABLE          1
    // �Ƿ����÷�תģʽ
    #define TIMER1_OC_MODE_ENABLE           0
    // ������PWMģʽ���Ƿ�תģʽ������Ҫָ��OCMode
    #define TIMER1_OCMODE                   TIM_OCMODE_PWM1
    // ռ�ձȣ����壩
    #define TIMER1_PULSE                    (TIMER1_ARR + 1)
    // ����
    #define TIMER1_OCPOLARITY               TIM_OCPOLARITY_HIGH
    // ͨ������
    #define TIMER1_CHANNEL1_ENABLE          1

    #define TIMER1_CHANNEL2_ENABLE          0

    #define TIMER1_CHANNEL3_ENABLE          0

    #define TIMER1_CHANNEL4_ENABLE          1
    // �Ƿ��Զ�����
    #define TIMER1_PWM_MODE_AUTO_START      1

    /* ��ʱ��2 */
    // Ԥ��Ƶ������ʵ����Ҫ�޸Ĵ˷�Ƶ��ֵ
    #define TIMER2_PRESCALER                4
    // ����ģʽ
    #define TIMER2_COUNTER_MODE             TIM_COUNTERMODE_UP
    // ���ڣ�TIM2Ϊ32λ��
    #define TIMER2_ARR                      0xFFFFFFFF - 1
    #define TIMER2_AUTORELOADPRELOAD        TIM_AUTORELOAD_PRELOAD_DISABLE
    // �Ƿ�����ģʽ
    #define TIMER2_PWM_MODE_ENABLE          1
    // �Ƿ����÷�תģʽ
    #define TIMER2_OC_MODE_ENABLE           0
    // ������PWMģʽ���Ƿ�תģʽ������Ҫָ��OCMode
    #define TIMER2_OCMODE                   TIM_OCMODE_PWM1
    // ռ�ձȣ����壩
    #define TIMER2_PULSE                    ((TIMER2_ARR + 1) / 2)
    // ����
    #define TIMER2_OCPOLARITY               TIM_OCPOLARITY_HIGH
    // ͨ������
    #define TIMER2_CHANNEL1_ENABLE          0

    #define TIMER2_CHANNEL2_ENABLE          1

    #define TIMER2_CHANNEL3_ENABLE          0

    #define TIMER2_CHANNEL4_ENABLE          0
    // �Ƿ��Զ�����
    #define TIMER2_PWM_MODE_AUTO_START      0

    /* ��ʱ��3 */
    #define GENERAL_TIMER3_ENCODER_ENABLE   1
    // ����ģʽ
    #define TIMER3_COUNTER_MODE             TIM_COUNTERMODE_UP
    // ���ڣ�TIM1Ϊ16λ��
    #define TIMER3_ARR                      0xFFFF - 1

    /* ��ʱ��4 */
    #define TIMER4_PRESCALER                8399
    #define TIMER4_COUNTER_MODE             TIM_COUNTERMODE_UP
    #define TIMER4_ARR                      999
    #define TIMER4_AUTORELOADPRELOAD        TIM_AUTORELOAD_PRELOAD_DISABLE

    /* ������ʱ��6 */
    #define TIMER6_PRESCALER                83
    // ����ģʽ
    #define TIMER6_COUNTER_MODE             TIM_COUNTERMODE_UP
    // ���ڣ�TIM1Ϊ16λ��
    #define TIMER6_ARR                      999
    #define TIMER6_AUTORELOADPRELOAD        TIM_AUTORELOAD_PRELOAD_DISABLE

    /* ������ʱ��7 */
    #define TIMER7_PRESCALER                8399
    // ����ģʽ
    #define TIMER7_COUNTER_MODE             TIM_COUNTERMODE_UP
    // ���ڣ�TIM1Ϊ16λ��
    #define TIMER7_ARR                      9999
    #define TIMER7_AUTORELOADPRELOAD        TIM_AUTORELOAD_PRELOAD_DISABLE

    // Ԥ��Ƶ������ʵ����Ҫ�޸Ĵ˷�Ƶ��ֵ
    #define TIMER8_PRESCALER                167
    // ����ģʽ
    #define TIMER8_COUNTER_MODE             TIM_COUNTERMODE_UP
    // ���ڣ�TIM8Ϊ16λ��
    #define TIMER8_ARR                      0xFFFF - 1
    #define TIMER8_AUTORELOADPRELOAD        TIM_AUTORELOAD_PRELOAD_DISABLE
    // �Ƿ�����ģʽ
    #define TIMER8_PWM_MODE_ENABLE          0
    // �Ƿ����÷�תģʽ
    #define TIMER8_OC_MODE_ENABLE           1
    // ������PWMģʽ���Ƿ�תģʽ������Ҫָ��OCMode
    #define TIMER8_OCMODE                   TIM_OCMODE_PWM1
    // ռ�ձȣ����壩
    #define TIMER8_PULSE                    ((TIMER8_ARR + 1) / 2)
    // ����
    #define TIMER8_OCPOLARITY               TIM_OCPOLARITY_HIGH
    // ͨ������
    #define TIMER8_CHANNEL1_ENABLE          1

    #define TIMER8_CHANNEL2_ENABLE          0

    #define TIMER2_CHANNEL3_ENABLE          0

    #define TIMER2_CHANNEL4_ENABLE          0
    // �Ƿ��Զ�����
    #define TIMER8_PWM_MODE_AUTO_START      0
#endif
