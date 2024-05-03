#include "color_helper.h"


void HSV2RGB(unsigned short h, unsigned short s, unsigned short v,
             unsigned char *r, unsigned char *g, unsigned char *b)
{
    // R,G,B from 0-255, H from 0-360, S,V from 0-100
    int i;
    float RGB_min, RGB_max;
    RGB_max = v * 2.55F;
    RGB_min = RGB_max*(100 - s) / 100.0F;

    i = h / 60;
    int difs = h % 60; // factorial part of h

                       // RGB adjustment amount by hue 
    float RGB_Adj = (RGB_max - RGB_min)*difs / 60.0f;

    switch (i)
    {
        case 0:
            *r = RGB_max;
            *g = RGB_min + RGB_Adj;
            *b = RGB_min;
            break;
        case 1:
            *r = RGB_max - RGB_Adj;
            *g = RGB_max;
            *b = RGB_min;
            break;
        case 2:
            *r = RGB_min;
            *g = RGB_max;
            *b = RGB_min + RGB_Adj;
            break;
        case 3:
            *r = RGB_min;
            *g = RGB_max - RGB_Adj;
            *b = RGB_max;
            break;
        case 4:
            *r = RGB_min + RGB_Adj;
            *g = RGB_min;
            *b = RGB_max;
            break;
        default:		// case 5:
            *r = RGB_max;
            *g = RGB_min;
            *b = RGB_max - RGB_Adj;
            break;
    }
}


void RGB2HSV(unsigned char r, unsigned char g, unsigned char b,
             float *h, float *s, float *v)
{
    float red, green ,blue;
    float cmax, cmin, delta;

    red = (float)r / 255;
    green = (float)g / 255;
    blue = (float)b / 255;

    cmax = (red > green ? red : green > blue ? green : blue);
    cmin = (red < green ? red : green < blue ? green : blue);
    delta = cmax - cmin;

    /* H */
    if(delta != 0)
    {
        if(cmax == red)
        {
                *h= green >= blue ? 60 * ((green - blue) / delta): 60 * ((green - blue) / delta) + 360;
        }
        else if(cmax == green)
        {
          *h = 60 * ((blue - red) / delta + 2);
        }
        else if(cmax == blue) 
        {
          *h = 60 * ((red - green) / delta + 4);
        }
    }
    else
    {
        *h = 0;
    }
    /* S */
    *s=cmax?delta / cmax:0;
    /* V */
    *v = cmax;
}
