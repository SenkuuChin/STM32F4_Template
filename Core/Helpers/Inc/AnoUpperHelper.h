#ifndef __MY_ANO_UPPER_HELPER__
    #define __MY_ANO_UPPER_HELPER__
    #include "global_conf.h"
    #define ANO_UPPER_ADDR              0xFE
    
    typedef enum
    {
        // ���Դ���������
        INERTIAL_SENSOR_DATA = 1,
        // ���̡��¶ȴ���������
        COMPASS_TEMPERATURE_SENSOR_DATA,
        // �ɿ���̬��ŷ���Ǹ�ʽ
        EULER_ANGLE_ATTITUDE_FORMAT,
        // �ɿ���̬����Ԫ����ʽ
        QUATERNION_ATTITUDE_FORMAT,
        // �߶�����
        HEIGHT_DATA,
        // ����ģʽ
        RUNNING_MODE,
        // �ٶ�����
        SPEED_DATA,
        // λ��ƫ������
        LOCATION_OFFSET_DATA,
        // ���ٹ���
        WIND_SPEED_ESTIMATION,
        // Ŀ����̬����
        TARGET_ATTITUDE_DATA,
        // Ŀ���ٶ�����
        TARGET_SPEED_DATA,
        // �غ���Ϣ
        RETURN_INFO,
        // ��ѹ��������
        VOLTAGE_CURRENT_DATA,
        // ���ģ�鹤��״̬
        EXTERNAL_MODULES_WORKING_STATUS,
        // RGB ������Ϣ���
        RGB_BRIGHTNESS_INFO_OUTPUT
    } FlightControlFuncID_TypeDef;                  /* �ɿ������Ϣ������ID */
    
    
    typedef enum
    {
        // PWM ������
        PWM_CONTROL_VARIABLE = 0x20,
        // ��̬������
        ATTITUDE_CONTROL_VARIABLE,
    } FltCtrlContrlVariableOutputFuncID_TypeDef;    /* �ɿؿ���������� */
    
    typedef enum
    {
        // GPS����������
        GPS_SENSOR_DATA = 0x30,
        // ԭʼ������Ϣ
        ORIGINAL_OPTICAL_FLOW_INFO,
        // ͨ��λ���ʹ���������
        GENERAL_LOCATION_SENSOR_DATA,
        // ͨ���ٶ��ʹ���������
        GENERAL_SPEED_SENSOR_DATA,
        // ͨ�ò�ഫ��������
        GENERAL_RANGING_SENSOR_DATA,
        // ͨ��ͼ����������Ϣ֡
        GENERAL_IMAGE_FEATURE_POINT_INFO_FRAME
    } FltCtrlReceivedInfoFuncID_TypeDef;            /* �ɿؽ�����Ϣ�� */
    
    typedef enum
    {
        // ң��������
        REMOTE_CONTROL_DATA = 0x40,
        // ʵʱ����֡
        REAL_TIME_CONTROL_FRAME
    } FltCtrlReceivedCMDFuncID_TypeDef; /* �ɿؽ��տ���ָ���� */
    
    typedef enum
    {
        // ������������
        ANONY_OPTICAL_FLOW_DATA = 0x51,
        
    } OpticalFlowInfoFuncID_TypeDef; /* ������Ϣ�� */
    
    typedef enum
    {
        // �����ȡ
        WAYPOINT_GET = 0x60,
        // ����д�롢�����ȡ����
        WAYPOINT_GET_RETURN
        
    } GPSWaypointRWFuncID_TypeDef; /* GPS�����д֡ */
    
    typedef enum
    {
        // CMD ����֡
        CMD_FRAME = 0xC0,
        // CMD ����֡
        CMD_FUNC_FRAME,
        // CMD ������Ϣ֡
        CMD_INFO_FRAME,
        
    } FuncCMDFuncID_TypeDef; /* ���ܴ�����֡ */
    
    typedef enum
    {
        // ��������
        PARA_CMD = 0xE0,
        // ����д�롢����ֵ��ȡ����
        PARA_GET_RETURN,
        // ������Ϣ����
        PARA_INFO_RETRUN,
        // �豸��Ϣ����
        DEVICE_INFO_RETURN,
        
    } ParameterRWFuncID_TypeDef; /* ������д��֡ */
    
    
    typedef enum
    {
        // LOG��Ϣ���-�ַ���
        LOG_OUTPUT_STR = 0xA0,
        // LOG��Ϣ���-�ַ��� + ����
        LOG_OUTPUT_STR_NUM,
        // ͼ������
        IMAGE_DATA = 0xB0,
        // ����IP����������(��ʽ1)
        BASE_IP_DATA_1,
        // ����IP����������(��ʽ2)
        BASE_IP_DATA_2,
        // ��������
        SPEICAL_DATA = 0xFB
    } OtherFuncID_TypeDef; /* ����֡ */
    
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
    
    /* �ϴ�ʹ�õĺ��� */
    #define ANO_UPLOAD_FUNC                 SerialSendDataByDMA
#endif
