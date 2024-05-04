#include "Peripherals/timer/timer.h"
#include "timer_conf.h"
#include "global_conf.h"


#if TIMER1_ENABLE
#endif

#if TIMER2_ENABLE
#endif

#if TIMER3_ENABLE
TIM_HandleTypeDef g_GeneralTimer3Handle = { 0 };
#if GENERAL_TIMER3_ENCODER_ENABLE
TIM_Encoder_InitTypeDef g_GeneralTimer3_Encoder_Handle = { 0 };
#endif
void GeneralTimer3_StartConter(void)
{
    if (g_GeneralTimer3Handle.State != HAL_TIM_STATE_READY)
    {
        return;
    }
    HAL_TIM_Base_Start_IT(&g_GeneralTimer3Handle);
}
void GeneralTimer3_Stop(void)
{
    if (g_GeneralTimer3Handle.State == HAL_TIM_STATE_READY
        || g_GeneralTimer3Handle.State == HAL_TIM_STATE_RESET)
    {
        return;
    }
    HAL_TIM_Base_Stop_IT(&g_GeneralTimer3Handle);
}
void GeneralTimer3_ResetCounter(void)
{
    if (g_GeneralTimer3Handle.State == HAL_TIM_STATE_READY
        || g_GeneralTimer3Handle.State == HAL_TIM_STATE_RESET)
    {
        return;
    }
    __HAL_TIM_SET_COUNTER(&g_GeneralTimer3Handle, 0);
}
void GeneralTimer3_Init(void)
{
    if (g_GeneralTimer3Handle.Instance == TIM3)
    {
        return;
    }
    g_GeneralTimer3Handle.Instance = TIM3;
    g_GeneralTimer3Handle.Init.Prescaler = 0;
    g_GeneralTimer3Handle.Init.CounterMode = TIMER3_COUNTER_MODE;
    g_GeneralTimer3Handle.Init.Period = TIMER3_ARR;
    g_GeneralTimer3Handle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;

    #if GENERAL_TIMER3_ENCODER_ENABLE
    // ������ģʽ��T1��T2����⣬�ı�Ƶ
    g_GeneralTimer3_Encoder_Handle.EncoderMode = TIM_ENCODERMODE_TI12;
    // IC1���뼫�ԣ��Ƿ���
    g_GeneralTimer3_Encoder_Handle.IC1Polarity = TIM_ICPOLARITY_RISING;
    // ����ͨ��ѡ��
    g_GeneralTimer3_Encoder_Handle.IC1Selection = TIM_ICSELECTION_DIRECTTI;
    // IC1����Ƶ
    g_GeneralTimer3_Encoder_Handle.IC1Prescaler = TIM_ICPSC_DIV1;
    // IC1�˲�����10
    g_GeneralTimer3_Encoder_Handle.IC1Filter = 10;

    // IC2���뼫�ԣ�������
    g_GeneralTimer3_Encoder_Handle.IC2Polarity = TIM_ICPOLARITY_RISING;
    // ����ͨ��ѡ��
    g_GeneralTimer3_Encoder_Handle.IC2Selection = TIM_ICSELECTION_DIRECTTI;
    // IC2����Ƶ
    g_GeneralTimer3_Encoder_Handle.IC2Prescaler = TIM_ICPSC_DIV1;
    // IC2�˲�����10
    g_GeneralTimer3_Encoder_Handle.IC2Filter = 10;

    HAL_TIM_Encoder_Init(&g_GeneralTimer3Handle, &g_GeneralTimer3_Encoder_Handle);

    // ����������
    HAL_TIM_Encoder_Start(&g_GeneralTimer3Handle, TIM_CHANNEL_1);
    HAL_TIM_Encoder_Start(&g_GeneralTimer3Handle, TIM_CHANNEL_2);
    // ��������������ж�
    __HAL_TIM_CLEAR_FLAG(&g_GeneralTimer3Handle, TIM_IT_UPDATE);
    __HAL_TIM_ENABLE_IT(&g_GeneralTimer3Handle, TIM_IT_UPDATE);
    #endif
}
#endif

#if TIMER4_ENABLE
#endif

#if TIMER5_ENABLE
#endif

#if TIMER6_ENABLE
TIM_HandleTypeDef g_BasicTimer6Handle = { 0 };
void BasicTimer6_StartConter(void)
{
    if (g_BasicTimer6Handle.State != HAL_TIM_STATE_READY)
    {
        return;
    }
    HAL_TIM_Base_Start_IT(&g_BasicTimer6Handle);
}
void BasicTimer6_Stop(void)
{
    if (g_BasicTimer6Handle.State == HAL_TIM_STATE_READY
        || g_BasicTimer6Handle.State == HAL_TIM_STATE_RESET)
    {
        return;
    }
    HAL_TIM_Base_Stop_IT(&g_BasicTimer6Handle);
}
void BasicTimer6_ResetCounter(void)
{
    if (g_BasicTimer6Handle.State == HAL_TIM_STATE_READY
        || g_BasicTimer6Handle.State == HAL_TIM_STATE_RESET)
    {
        return;
    }
    __HAL_TIM_SET_COUNTER(&g_BasicTimer6Handle, 0);
}
void BasicTimer6_Init(void)
{
    if (g_BasicTimer6Handle.Instance == TIM6)
    {
        return;
    }
    // ���ι�����TIM6��ʱ 1msһ������
    g_BasicTimer6Handle.Instance = TIM6;
    g_BasicTimer6Handle.Init.Prescaler = TIMER6_PRESCALER;
    g_BasicTimer6Handle.Init.CounterMode = TIMER6_COUNTER_MODE;
    g_BasicTimer6Handle.Init.Period = TIMER6_ARR;
    g_BasicTimer6Handle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    HAL_TIM_Base_Init(&g_BasicTimer6Handle);

    HAL_TIM_Base_Start_IT(&g_BasicTimer6Handle);
    __HAL_TIM_CLEAR_IT(&g_BasicTimer6Handle, TIM_IT_UPDATE);
}
#endif

#if TIMER7_ENABLE
TIM_HandleTypeDef g_BasicTimer7Handle = { 0 };
void BasicTimer7_StartConter(void)
{
    if (g_BasicTimer7Handle.State != HAL_TIM_STATE_READY)
    {
        return;
    }
    HAL_TIM_Base_Start_IT(&g_BasicTimer7Handle);
}
void BasicTimer7_Stop(void)
{
    if (g_BasicTimer7Handle.State == HAL_TIM_STATE_READY || g_BasicTimer7Handle.State == HAL_TIM_STATE_RESET)
    {
        return;
    }
    HAL_TIM_Base_Stop_IT(&g_BasicTimer6Handle);
}
void BasicTimer7_ResetCounter(void)
{
    if (g_BasicTimer7Handle.State == HAL_TIM_STATE_READY || g_BasicTimer7Handle.State == HAL_TIM_STATE_RESET)
    {
        return;
    }
    __HAL_TIM_SET_COUNTER(&g_BasicTimer6Handle, 0);
}
void BasicTimer7_Init(void)
{
    if (g_BasicTimer7Handle.State == HAL_TIM_STATE_RESET)
    {
        return;
    }
    // ���ι�����TIM7��ʱ 1000msһ������
    g_BasicTimer7Handle.Instance = TIM7;                        /* ��ʱ��7 */
    g_BasicTimer7Handle.Init.Prescaler = TIMER7_PRESCALER;      /* ����Ԥ��Ƶ��  */
    g_BasicTimer7Handle.Init.CounterMode = TIMER7_COUNTER_MODE; /* ���ϼ����� */
    g_BasicTimer7Handle.Init.Period = TIMER7_ARR;               /* �Զ�װ��ֵ */
    HAL_TIM_Base_Init(&g_BasicTimer7Handle);
    HAL_TIM_Base_Start_IT(&g_BasicTimer7Handle);
}
#endif

#if TIMER8_ENABLE
TIM_HandleTypeDef g_AdvancedTimer8Handle = { 0 };
#if TIMER8_OC_MODE_ENABLE
TIM_OC_InitTypeDef g_AdvancedTimer8OCHandle = { 0 };
#endif
void AdvanceTimer8_StartConter(void)
{
    if (g_AdvancedTimer8Handle.State != HAL_TIM_STATE_READY)
    {
        return;
    }
    HAL_TIM_Base_Start_IT(&g_AdvancedTimer8Handle);
}
void AdvanceTimer8_Stop(void)
{
    if (g_AdvancedTimer8Handle.State == HAL_TIM_STATE_READY
        || g_AdvancedTimer8Handle.State == HAL_TIM_STATE_RESET)
    {
        return;
    }
    HAL_TIM_Base_Stop_IT(&g_BasicTimer6Handle);
}
void AdvanceTimer8_ResetCounter(void)
{
    if (g_AdvancedTimer8Handle.State == HAL_TIM_STATE_READY
        || g_AdvancedTimer8Handle.State == HAL_TIM_STATE_RESET)
    {
        return;
    }
    __HAL_TIM_SET_COUNTER(&g_AdvancedTimer8Handle, 0);
}
void AdvanceTimer8_Init(void)
{
    if (g_AdvancedTimer8Handle.State == HAL_TIM_STATE_RESET)
    {
        return;
    }
    g_AdvancedTimer8Handle.Instance = TIM8;                                     /* ��ʱ��8 */
    g_AdvancedTimer8Handle.Init.Prescaler = TIMER8_PRESCALER;                   /* ��ʱ����Ƶ */
    g_AdvancedTimer8Handle.Init.CounterMode = TIMER8_COUNTER_MODE;              /* ���ϼ���ģʽ */
    g_AdvancedTimer8Handle.Init.Period = TIMER8_ARR;                            /* �Զ���װ��ֵ */
    g_AdvancedTimer8Handle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;         /* ��Ƶ���� */
    g_AdvancedTimer8Handle.Init.AutoReloadPreload = TIMER8_AUTORELOADPRELOAD;
    g_AdvancedTimer8Handle.Init.RepetitionCounter = TIMER8_PWM_MODE_AUTO_START; /* ��ʼʱ������*/
    #if TIMER8_OC_MODE_ENABLE
    HAL_TIM_OC_Init(&g_AdvancedTimer8Handle);                                   /* ��ʼ���������ģʽ */
    g_AdvancedTimer8OCHandle.OCMode = TIM_OCMODE_TOGGLE;                        /* ��תģʽ */
    g_AdvancedTimer8OCHandle.Pulse = 0;
    g_AdvancedTimer8OCHandle.OCPolarity = TIMER8_OCPOLARITY;                    /* ����Ƚϼ���Ϊ�� */
    g_AdvancedTimer8OCHandle.OCNPolarity = TIM_OCNPOLARITY_LOW;
    g_AdvancedTimer8OCHandle.OCFastMode = TIM_OCFAST_DISABLE;
    g_AdvancedTimer8OCHandle.OCIdleState = TIM_OCIDLESTATE_RESET;
    g_AdvancedTimer8OCHandle.OCNIdleState = TIM_OCNIDLESTATE_RESET;

    #if TIMER8_CHANNEL1_ENABLE
    HAL_TIM_OC_ConfigChannel(&g_AdvancedTimer8Handle, &g_AdvancedTimer8OCHandle, TIM_CHANNEL_1); /* ����TIM8ͨ��1 */
    #endif
    #if TIMER8_CHANNEL2_ENABLE
    HAL_TIM_OC_ConfigChannel(&g_AdvancedTimer8Handle, &g_AdvancedTimer8OCHandle, TIM_CHANNEL_2); /* ����TIM8ͨ��2 */
    #endif
    #if TIMER8_CHANNEL3_ENABLE
    HAL_TIM_OC_ConfigChannel(&g_AdvancedTimer8Handle, &g_AdvancedTimer8OCHandle, TIM_CHANNEL_3); /* ����TIM8ͨ��3 */
    #endif
    #if TIMER8_CHANNEL4_ENABLE
    HAL_TIM_OC_ConfigChannel(&g_AdvancedTimer8Handle, &g_AdvancedTimer8OCHandle, TIM_CHANNEL_4); /* ����TIM8ͨ��4 */
    #endif
    #endif
    HAL_TIM_Base_Start(&g_AdvancedTimer8Handle);
#endif

#if TIMER9_ENABLE
#endif

#if TIMER10_ENABLE
#endif

__weak void Timer_Initialise(void)
{
    #if TIMER3_ENABLE
    GeneralTimer3_Init();
    #endif
    #if TIMER6_ENABLE
    BasicTimer6_Init();
    #endif
    
    #if TIMER7_ENABLE
    BasicTimer7_Init();
    #endif
    
    #if TIMER8_ENABLE
    AdvanceTimer8_Init();
    #endif
}



__weak void ConfigureTimeForRunTimeStats(void)
{
    // ȡ����ѡ���ĸ���ʱ����ΪFreeRTOSͳ��ʹ�õĽ��ļ�����
    #if TIMER3_ENABLE
    GeneralTimer3_StartConter();               /* ������ʱ�� */
    #endif
}
