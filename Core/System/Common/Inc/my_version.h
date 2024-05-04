#ifndef __MY_VERSION_H__
    #define __MY_VERSION_H__
    typedef struct
    {
        unsigned char deviceID;
        short hardwareVersion;
        short softwareVersion;
        short blVersion;
        short communicationProtocolVersion;
        char* deviceName;
    } DeviceInfo_TypeDef;
    
    extern DeviceInfo_TypeDef deviceInfo;
#endif
