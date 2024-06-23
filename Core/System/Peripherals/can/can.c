#include "Peripherals/can/can.h"
#include "global_conf.h"
#if SYS_SRAM_MANAGE_ENABLE
#include "sram_helper.h"
#endif

#if CAN1_ENABLE
CANManager_TypeDef g_CAN1_Manager = { 0 };
#if !SYS_SRAM_MANAGE_ENABLE
uint8_t CAN1_Data[8] = { 0 };
#endif
__weak HandleResult CAN1_Initialise(void)
{
    HandleResult result = OK;
    g_CAN1_Manager.Handle.Instance = CAN1;
    g_CAN1_Manager.Handle.Init.Prescaler = 6;
    g_CAN1_Manager.Handle.Init.Mode = CAN_MODE_NORMAL;
    g_CAN1_Manager.Handle.Init.SyncJumpWidth = CAN_SJW_1TQ;
    g_CAN1_Manager.Handle.Init.TimeSeg1 = CAN_BS1_7TQ;
    g_CAN1_Manager.Handle.Init.TimeSeg2 = CAN_BS2_6TQ;
    g_CAN1_Manager.Handle.Init.TimeTriggeredMode = DISABLE;
    g_CAN1_Manager.Handle.Init.AutoBusOff = DISABLE;
    g_CAN1_Manager.Handle.Init.AutoWakeUp = DISABLE;
    g_CAN1_Manager.Handle.Init.AutoRetransmission = DISABLE; // �����Զ��ش�
    g_CAN1_Manager.Handle.Init.ReceiveFifoLocked = DISABLE;
    g_CAN1_Manager.Handle.Init.TransmitFifoPriority = DISABLE;

    SYSTEM_ASSERT(HAL_CAN_Init(&g_CAN1_Manager.Handle), result);
    #if SYS_SRAM_MANAGE_ENABLE
    SRAMHelper.Malloc(SRAM_INTERNAL, sizeof(uint8_t) * 8);
    #else
    g_CAN1_Manager.Data = CAN1_Data;
    #endif

    __HAL_CAN_ENABLE_IT(&g_CAN1_Manager.Handle, CAN_IT_RX_FIFO0_MSG_PENDING);

    CAN_FilterTypeDef sFilterConfig = { 0 };
    /* ����CAN������ */
    // CAN1 ʹ�� 0~13 �� BankID��CAN2ʹ�� 14 ~ 27 ��BankID
    sFilterConfig.FilterBank = 0;
    sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
    sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
    sFilterConfig.FilterIdHigh = 0x0000;
    sFilterConfig.FilterIdLow = 0x0000;
    sFilterConfig.FilterMaskIdHigh = 0x0000;
    sFilterConfig.FilterMaskIdLow = 0x0000;
    sFilterConfig.FilterFIFOAssignment = CAN_FILTER_FIFO0;
    sFilterConfig.FilterActivation = CAN_FILTER_ENABLE;
    // ָ��CAN2����ʼBankID��14
    sFilterConfig.SlaveStartFilterBank = 14;

    /* ���������� */
    SYSTEM_ASSERT(HAL_CAN_ConfigFilter(&g_CAN1_Manager.Handle, &sFilterConfig), result);

    SYSTEM_ASSERT(HAL_CAN_Start(&g_CAN1_Manager.Handle), result);
    g_CAN1_Manager.Instance = TRUE;
    return result;
}
#endif

#if CAN2_ENABLE
CANManager_TypeDef g_CAN2_Manager = { 0 };
#if !SYS_SRAM_MANAGE_ENABLE
uint8_t CAN2_Data[8] = { 0 };
#endif

__weak HandleResult CAN2_Initialise(void)
{
    HandleResult result = OK;
    g_CAN2_Manager.Handle.Instance = CAN2;
    g_CAN2_Manager.Handle.Init.Prescaler = 6;
    g_CAN2_Manager.Handle.Init.Mode = CAN_MODE_NORMAL;
    g_CAN2_Manager.Handle.Init.SyncJumpWidth = CAN_SJW_1TQ;
    g_CAN2_Manager.Handle.Init.TimeSeg1 = CAN_BS1_7TQ;
    g_CAN2_Manager.Handle.Init.TimeSeg2 = CAN_BS2_6TQ;
    g_CAN2_Manager.Handle.Init.TimeTriggeredMode = DISABLE;
    g_CAN2_Manager.Handle.Init.AutoBusOff = DISABLE;
    g_CAN2_Manager.Handle.Init.AutoWakeUp = DISABLE;
    g_CAN2_Manager.Handle.Init.AutoRetransmission = DISABLE; // �����Զ��ش�
    g_CAN2_Manager.Handle.Init.ReceiveFifoLocked = DISABLE;
    g_CAN2_Manager.Handle.Init.TransmitFifoPriority = DISABLE;

    SYSTEM_ASSERT(HAL_CAN_Init(&g_CAN2_Manager.Handle), result);
    #if SYS_SRAM_MANAGE_ENABLE
    SRAMHelper.Malloc(SRAM_INTERNAL, sizeof(uint8_t) * 8);
    #else
    g_CAN2_Manager.Data = CAN2_Data;
    #endif

    __HAL_CAN_ENABLE_IT(&g_CAN2_Manager.Handle, CAN_IT_RX_FIFO0_MSG_PENDING);

    CAN_FilterTypeDef sFilterConfig = { 0 };
    /* ����CAN������ */
    // CAN1 ʹ�� 0~13 �� BankID��CAN2ʹ�� 14 ~ 27 ��BankID
    sFilterConfig.FilterBank = 14;
    sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
    sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
    sFilterConfig.FilterIdHigh = 0x0000;
    sFilterConfig.FilterIdLow = 0x0000;
    sFilterConfig.FilterMaskIdHigh = 0x0000;
    sFilterConfig.FilterMaskIdLow = 0x0000;
    sFilterConfig.FilterFIFOAssignment = CAN_FILTER_FIFO0;
    sFilterConfig.FilterActivation = CAN_FILTER_ENABLE;
    // ָ��CAN2����ʼBankID��14
    sFilterConfig.SlaveStartFilterBank = 14;

    /* ���������� */
    SYSTEM_ASSERT(HAL_CAN_ConfigFilter(&g_CAN2_Manager.Handle, &sFilterConfig), result);

    SYSTEM_ASSERT(HAL_CAN_Start(&g_CAN2_Manager.Handle), result);
    g_CAN2_Manager.Instance = TRUE;
    return result;
}
#endif

void CAN_Initialise(void)
{
    #if CAN1_ENABLE
    CAN1_Initialise();
    #endif
    #if CAN2_ENABLE
    CAN2_Initialise();
    #endif
}
