#ifndef __MY_FREERTOS_DEMO_H__
    #define __MY_FREERTOS_DEMO_H__
    #ifdef __cplusplus
    extern "C" {
    #endif
    typedef struct
    {
        void (*exec)(void);
    } App_TypeDef;
    extern App_TypeDef App;
    #ifdef __cplusplus
    }
    #endif
#endif
