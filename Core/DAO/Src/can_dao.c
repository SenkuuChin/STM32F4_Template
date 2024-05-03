#include "can_dao.h"


#if CAN1_ENABLE
extern CANManager_TypeDef g_CAN1_Manager;
#endif
#if CAN2_ENABLE
extern CANManager_TypeDef g_CAN2_Manager;
#endif


HandleResult CAN_SendMsg(uint8_t* msg, uint16_t length)
{
    if (length > 8)
    {
        length = 8;
    }
    HandleResult res = OK;
    uint32_t TxMailbox = 0;
    g_CAN1_Manager.TxHeader.StdId = 0x01;
    g_CAN1_Manager.TxHeader.ExtId = 0x00;
    g_CAN1_Manager.TxHeader.RTR = CAN_RTR_DATA;
    g_CAN1_Manager.TxHeader.IDE = CAN_ID_STD;
    g_CAN1_Manager.TxHeader.DLC = length;
    g_CAN1_Manager.TxHeader.TransmitGlobalTime = DISABLE;
    SYSTEM_ASSERT(HAL_CAN_AddTxMessage(&g_CAN1_Manager.Handle, &g_CAN1_Manager.TxHeader, msg, &TxMailbox), res);
    return res;
}
