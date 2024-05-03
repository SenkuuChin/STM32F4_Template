#ifndef __MY_COLOR_HELPER_H__
    #define __MY_COLOR_HELPER_H__
    #ifdef __cplusplus
    extern "C" {
    #endif
    void HSV2RGB(unsigned short h, unsigned short s, unsigned short v, 
                 unsigned char *r, unsigned char *g, unsigned char *b);
    void RGB2HSV(unsigned char r, unsigned char g, unsigned char b, 
                 float *h, float *s, float *v);
    #ifdef __cplusplus
    }
    #endif
#endif
