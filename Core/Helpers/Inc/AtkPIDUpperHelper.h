#ifndef __MY_ATK_PID_UPPER_HELPER_H__
    #define __MY_ATK_PID_UPPER_HELPER_H__
    typedef enum
    {
        ATK_TO_UPPER_TYPE_FAULT = 0x0F,
        ATK_TO_UPPER_TYPE_MOTOR_STATUS = 0x10,
        ATK_TO_UPPER_TYPE_SPEED_VAL,
        ATK_TO_UPPER_TYPE_ENCODER_POSITION_VAL,
        ATK_TO_UPPER_TYPE_VOLTAGE_VAL,
        ATK_TO_UPPER_TYPE_CURRENT_VAL,
        ATK_TO_UPPER_TYPE_TEMPERATURE_VAL,
        ATK_TO_UPPER_TYPE_TOTAL_MILEAGE,
        ATK_TO_UPPER_TYPE_BACK_EMF,
        ATK_TO_UPPER_TYPE_MOTOR_TYPE,
        ATK_TO_UPPER_TYPE_TORQUE_VAL,
        ATK_TO_UPPER_TYPE_POWER,
        /* 0x1B ~ 0x1F 保留 */
        ATK_TO_UPPER_TYPE_USER_PID_1 = 0x20,
        ATK_TO_UPPER_TYPE_USER_PID_2,
        ATK_TO_UPPER_TYPE_USER_PID_3,
        ATK_TO_UPPER_TYPE_USER_PID_4,
        ATK_TO_UPPER_TYPE_USER_PID_5,
        ATK_TO_UPPER_TYPE_USER_PID_6,
        ATK_TO_UPPER_TYPE_USER_PID_7,
        ATK_TO_UPPER_TYPE_USER_PID_8,
        ATK_TO_UPPER_TYPE_USER_PID_9,
        ATK_TO_UPPER_TYPE_USER_PID_10,
        /* 0x2A ~ 0x2F 保留 */
        ATK_TO_UPPER_TYPE_WAVE_DATA = 0x30,
        /* 0x50 ~ 0x6F 用户自定义变量 */
    } SendToUpperType_TypeDef;          /* 发送给上位机的数据类型 */
    
    typedef enum
    {
        /* 0x10 ~ 0x18 保留 */
        ATK_FROM_UPPER_TYPE_ALL_PARAMETER_GET = 0x19,
        /* 0x1A ~ 0x20 保留 */
        ATK_FROM_UPPER_TYPE_CONTROL_CMD = 0x21,
        ATK_FROM_UPPER_TYPE_CONTROL_MODE,
        ATK_FROM_UPPER_TYPE_SPEED_SET,
        ATK_FROM_UPPER_TYPE_TURQUE_SET,
        ATK_FROM_UPPER_TYPE_VF_VOLTAGE_SET,
        ATK_FROM_UPPER_TYPE_VF_IF_FREQUENCY_SET,
        ATK_FROM_UPPER_TYPE_IF_CURRENT_SET,
        ATK_FROM_UPPER_TYPE_DQ_CURRENT_D_SET,
        ATK_FROM_UPPER_TYPE_DQ_CURRENT_Q_SET,
        /* 0x2A ~ 0x30 保留 */
        ATK_FROM_UPPER_TYPE_USER_PID_1_SET,
        ATK_FROM_UPPER_TYPE_USER_PID_2_SET,
        ATK_FROM_UPPER_TYPE_USER_PID_3_SET,
        ATK_FROM_UPPER_TYPE_USER_PID_4_SET,
        ATK_FROM_UPPER_TYPE_USER_PID_5_SET,
        ATK_FROM_UPPER_TYPE_USER_PID_6_SET,
        ATK_FROM_UPPER_TYPE_USER_PID_7_SET,
        ATK_FROM_UPPER_TYPE_USER_PID_8_SET,
        ATK_FROM_UPPER_TYPE_USER_PID_9_SET,
        ATK_FROM_UPPER_TYPE_USER_PID_10_SET,
        /* 0x3B ~ 0x4F 保留 */
        /* 0x50 ~ 0x6F 用户自定义变量 */
    }ReceivedFromUpperType_TypeDef;     /* 上位机发送下来的数据类型 */
    
    
    typedef enum
    {
        ATK_FAULT_TYPE_ENCODER_HALL_ERROR = 1,
        ATK_FAULT_TYPE_EXCESSIVE_SPEED,
        ATK_FAULT_TYPE_DRIVER_BOARD_OVERHEATED = 0x04,
        ATK_FAULT_TYPE_MOTOR_OVERHEATED = 0x08,
        ATK_FAULT_TYPE_DRIVER_BOARD_OVERVOLTAGED = 0x10,
        ATK_FAULT_TYPE_DRIVER_BOARD_UNDERVOLTAGED = 0x20,
        ATK_FAULT_TYPE_DRIVER_BOARD_OVERCURRENT = 0x40,
        ATK_FAULT_TYPE_UNKNOWN_ERROR = 0x80,
    } SendToUpperFaultType_TypeDef;
    
    typedef enum
    {
        ATK_MOTOR_STATUS_IDEL = 0,
        ATK_MOTOR_STATUS_RUNNING,
        ATK_MOTOR_STATUS_ERROR,
        ATK_MOTOR_STATUS_STALLED,
        ATK_MOTOR_STATUS_BRAKE
    } SendToUpperMotorStatusType_TypeDef;
    
    typedef enum
    {
        ATK_MOTOR_TYPE_BDC = 0x10,
        ATK_MOTOR_TYPE_BLDC,
        // 永磁同步电机
        ATK_MOTOR_TYPE_PMSM,
        ATK_MOTOR_TYPE_STEP_MOTOR,
        // 伺服电机
        ATK_MOTOR_TYPE_SERVO_MOTOR,
        // Variable-frequency Drive 变频器(三相交流异步电机)
        ATK_MOTOR_TYPE_VFD,
        // 舵机
        ATK_MOTOR_TYPE_SERVO
    } SendToUpperMotorType_TypeDef;
    
    typedef enum
    {
        ATK_CONTROL_TYPE_STOPPAGE = 1,
        ATK_CONTROL_TYPE_RUNNING,
        ATK_CONTROL_TYPE_BRAKE
    } ReceivedFromUpperControlType_TypeDef;
    
    typedef enum
    {
        ATK_CONTROL_MODE_RPM = 1,
        ATK_CONTROL_MODE_TURQUE,
        ATK_CONTROL_MODE_IF,
        ATK_CONTROL_MODE_VF,
        ATK_CONTROL_MODE_DQ
    } ReceivedFromUpperControlMode_TypeDef;
#endif
