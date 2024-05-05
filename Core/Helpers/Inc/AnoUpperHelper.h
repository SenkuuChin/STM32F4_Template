#ifndef __MY_ANO_UPPER_HELPER__
    #define __MY_ANO_UPPER_HELPER__
    #include "global_conf.h"
    #define ANO_UPPER_ADDR              0xFE
    
    typedef enum
    {
        // 惯性传感器数据
        INERTIAL_SENSOR_DATA = 1,
        // 罗盘、温度传感器数据
        COMPASS_TEMPERATURE_SENSOR_DATA,
        // 飞控姿态：欧拉角格式
        EULER_ANGLE_ATTITUDE_FORMAT,
        // 飞控姿态：四元数格式
        QUATERNION_ATTITUDE_FORMAT,
        // 高度数据
        HEIGHT_DATA,
        // 运行模式
        RUNNING_MODE,
        // 速度数据
        SPEED_DATA,
        // 位置偏移数据
        LOCATION_OFFSET_DATA,
        // 风速估计
        WIND_SPEED_ESTIMATION,
        // 目标姿态数据
        TARGET_ATTITUDE_DATA,
        // 目标速度数据
        TARGET_SPEED_DATA,
        // 回航信息
        RETURN_INFO,
        // 电压电流数据
        VOLTAGE_CURRENT_DATA,
        // 外接模块工作状态
        EXTERNAL_MODULES_WORKING_STATUS,
        // RGB 亮度信息输出
        RGB_BRIGHTNESS_INFO_OUTPUT
    } FlightControlFuncID_TypeDef;                  /* 飞控相关信息控制类ID */
    
    
    typedef enum
    {
        // PWM 控制量
        PWM_CONTROL_VARIABLE = 0x20,
        // 姿态控制量
        ATTITUDE_CONTROL_VARIABLE,
    } FltCtrlContrlVariableOutputFuncID_TypeDef;    /* 飞控控制量输出类 */
    
    typedef enum
    {
        // GPS传感器数据
        GPS_SENSOR_DATA = 0x30,
        // 原始光流信息
        ORIGINAL_OPTICAL_FLOW_INFO,
        // 通用位置型传感器数据
        GENERAL_LOCATION_SENSOR_DATA,
        // 通用速度型传感器数据
        GENERAL_SPEED_SENSOR_DATA,
        // 通用测距传感器数据
        GENERAL_RANGING_SENSOR_DATA,
        // 通用图像特征点信息帧
        GENERAL_IMAGE_FEATURE_POINT_INFO_FRAME
    } FltCtrlReceivedInfoFuncID_TypeDef;            /* 飞控接收信息类 */
    
    typedef enum
    {
        // 遥控器数据
        REMOTE_CONTROL_DATA = 0x40,
        // 实时控制帧
        REAL_TIME_CONTROL_FRAME
    } FltCtrlReceivedCMDFuncID_TypeDef; /* 飞控接收控制指令类 */
    
    typedef enum
    {
        // 匿名光流数据
        ANONY_OPTICAL_FLOW_DATA = 0x51,
        
    } OpticalFlowInfoFuncID_TypeDef; /* 光流信息类 */
    
    typedef enum
    {
        // 航点读取
        WAYPOINT_GET = 0x60,
        // 航点写入、航点读取返回
        WAYPOINT_GET_RETURN
        
    } GPSWaypointRWFuncID_TypeDef; /* GPS航点读写帧 */
    
    typedef enum
    {
        // CMD 命令帧
        CMD_FRAME = 0xC0,
        // CMD 功能帧
        CMD_FUNC_FRAME,
        // CMD 命令信息帧
        CMD_INFO_FRAME,
        
    } FuncCMDFuncID_TypeDef; /* 功能触发类帧 */
    
    typedef enum
    {
        // 参数命令
        PARA_CMD = 0xE0,
        // 参数写入、参数值读取返回
        PARA_GET_RETURN,
        // 参数信息返回
        PARA_INFO_RETRUN,
        // 设备信息返回
        DEVICE_INFO_RETURN,
        
    } ParameterRWFuncID_TypeDef; /* 参数读写类帧 */
    
    
    typedef enum
    {
        // LOG信息输出-字符串
        LOG_OUTPUT_STR = 0xA0,
        // LOG信息输出-字符串 + 数字
        LOG_OUTPUT_STR_NUM,
        // 图像数据
        IMAGE_DATA = 0xB0,
        // 基于IP组网的数据(格式1)
        BASE_IP_DATA_1,
        // 基于IP组网的数据(格式2)
        BASE_IP_DATA_2,
        // 特殊数据
        SPEICAL_DATA = 0xFB
    } OtherFuncID_TypeDef; /* 其它帧 */
    
    typedef enum
    {
        LOG_COLOR_DEFUALT = 0,
        LOG_COLOR_RED,
        LOG_COLOR_GREEN
    } LogColor_TypeDef;
    
    #define AnoAssistantLog(color, str)             AnoAssistantLogOutput(FALSE, FALSE, color, 0, str)
    #define AnoAssistantLogPrintf(color, str, ...)  AnoAssistantLogOutput(FALSE, TRUE, color, 0, str, __VA_ARGS__)
    #define AnoAssistantLogWithNum(num, str)        AnoAssistantLogOutput(TRUE, FALSE, 0, num, str)
    
    void AnoAssistDeviceInfoGet(void);
    void AnoAssistantLogOutput(Bool withNum, Bool needPrint,
                                LogColor_TypeDef color, int32_t num,
                                uint8_t* str, ...);
    
    Bool AnoCheckData(uint8_t* inData);
    
    /* 上传使用的函数 */
    #define ANO_UPLOAD_FUNC                 SerialSendDataByDMA
#endif
