#include "can_dao.h"

#define CAN_RECEIVED_USE_CUSTOM                         0

#if CAN1_ENABLE
extern CANManager_TypeDef g_CAN1_Manager;
#endif
#if CAN2_ENABLE
extern CANManager_TypeDef g_CAN2_Manager;
#endif

#if CAN_RECEIVED_USE_CUSTOM
static uint8_t CAN_GetMsg(CANManager_TypeDef* canType, uint32_t id, uint8_t *buf)
{
    if (HAL_CAN_GetRxFifoFillLevel(&canType->Handle, CAN_RX_FIFO0) == 0)
    {
        // 没有接收到数据则直接返回
        return 0;
    }

    if (HAL_CAN_GetRxMessage(&canType->Handle, \
        CAN_RX_FIFO0, &canType->RxHeader, buf) != HAL_OK)
    {
        RESET_ARRAY(buf, 8);
        return 0;
    }

    // 获取指定ID的数据 注：必须先接收信息才能判断ID，否则没有任何数据
    if (canType->RxHeader.StdId != id || \
        canType->RxHeader.IDE != CAN_ID_STD || \
        canType->RxHeader.RTR != CAN_RTR_DATA)
    {
        // 获取的数据不正确则清空buffer
        RESET_ARRAY(buf, 8);
        return 0;
    }

    return canType->RxHeader.DLC;
}
#else

#endif

void CAN1_RX0_IRQHandler(void)
{
    #if CAN_RECEIVED_USE_CUSTOM
    if (CAN_GetMsg(&g_CAN1_Manager, 0x01, g_CAN1_Manager.Data) != 0)
    {
        
    }
    #else
    HAL_CAN_IRQHandler(&g_CAN1_Manager.Handle);
    #endif
}
