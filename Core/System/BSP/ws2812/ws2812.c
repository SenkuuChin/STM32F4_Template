#include "BSP/ws2812/ws2812.h"
#include "general_conf.h"
#include "color_helper.h"
#include "delay_helper.h"


void WS2812_Init(void)
{
    WS2812_CLK_ENABLE();
    GPIO_InitTypeDef GPIO_InitStructure = { 0 };
    GPIO_InitStructure.Pin = WS2812_PIN;
    GPIO_InitStructure.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStructure.Pull = GPIO_NOPULL;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(WS2812_PORT, &GPIO_InitStructure);
}

__IO uint8_t LED_Buffer[LED_BUFFER_SIZE] = { 0 };
Bool TransimitSuccessFlag = TRUE;
extern TIM_HandleTypeDef g_GeneralTimer3Handle;

#if !WS2812_USE_ORIGINAL
void SetLedColor(uint8_t index, uint8_t RED, uint8_t GREEN, uint8_t BLUE)
{
    uint8_t tempBuffer[24] = {0};
    uint8_t i;

    for (i = 0; i < 8; ++i) // GREEN data
        tempBuffer[i] = ((GREEN << i) & 0x80 ) ? WS2812_1 : WS2812_0;

    for (i = 0; i < 8; ++i) // RED
        tempBuffer[8 + i] = ((RED << i) & 0x80 ) ? WS2812_1 : WS2812_0;

    for (i = 0; i < 8; ++i) // BLUE
        tempBuffer[16 + i] = ((BLUE << i) & 0x80 ) ? WS2812_1 : WS2812_0;

    for (i = 0; i < 24; ++i)
        LED_Buffer[index * 24 + i] = tempBuffer[i];
}

void SetWholeColor(uint8_t red, uint8_t green, uint8_t blue)
{
    uint32_t index;

    for (index = 0; index < LED_NUMBER; ++index)
    {
        SetLedColor(index, red, green, blue);
    }
    LED_Buffer[LED_BUFFER_SIZE - 1] = WS2812_RESET;
}

void WS2812_ResetColorData(void)
{
    RESET_ARRAY(LED_Buffer, LED_BUFFER_SIZE);
}


void WS2812_Update(void)
{
    HAL_TIM_PWM_Stop_DMA(&g_GeneralTimer3Handle, TIM_CHANNEL_3);
    HAL_TIM_PWM_Start_DMA(&g_GeneralTimer3Handle, TIM_CHANNEL_3, (uint32_t *)&LED_Buffer, LED_BUFFER_SIZE);
}

/* 纯色 */
uint16_t led_red_color[3] = { 0, 100, 100 };
uint16_t led_orange_color[3] = { 24, 100, 100 };
uint16_t led_yellow_color[3] = { 60, 100, 100 };
uint16_t led_green_color[3] = { 120, 100, 100 };
uint16_t led_cyan_color[3] = { 202, 100, 78 };
uint16_t led_blue_color[3] = { 240, 100, 100 };
uint16_t led_purple_color[3] = { 273, 100, 100 };
uint16_t led_white_color[3] = { 0, 0, 100 };

/* 单色 */
uint16_t led_405_color[3] = { 300, 100, 100 };
uint16_t led_488_color[3] = { 240, 100, 100 };
uint16_t led_561_color[3] = { 120, 100, 100 };
uint16_t led_637_color[3] = { 0, 100, 100 };

uint8_t custom_rgb[3] = { 0 };

/* 双色 */
// uint16_t led_488_561_color = 
Bool switchFlag = FALSE;
uint16_t currentH = 0, currentS = 0, currentV = 100;
void WS2812_BreathLED(unsigned short* orgColor, unsigned short *colorValue, unsigned short delayTime, unsigned char *outSigal)
{
    uint8_t r, g, b;
    #if 1
    if (!TransimitSuccessFlag)
    {
        return;
    }
    TransimitSuccessFlag = FALSE;
    HSV2RGB(colorValue[0], colorValue[1], colorValue[2], &r, &g, &b);
    if ((!switchFlag && --colorValue[2] <= 0) || colorValue[2] > 100)
    {
        switchFlag = TRUE;
        *outSigal = 1;
    }
    else if (switchFlag && ++colorValue[2] >= orgColor[2])
    {
        switchFlag = FALSE;
        // *outSigal = 1;
    }
    SetWholeColor(r, g, b);
    #endif
    WS2812_Update();
    Delay_Ms(delayTime);
}

uint8_t signal = 0;
uint8_t currentMode = BREATH_COLOR_CIRCULAR;
#define BREATH_DELAY_TIME			15

void WS2812_BreathEffect(unsigned char mode, unsigned char effectMode, unsigned char colorEnable)
{
    uint16_t colorType[3] = { 0 };
    
    if (currentMode != mode)
    {
        return;
    }
    
    if (colorEnable & RED_EFFECT_ENABLE)
    {
        signal = 0;
        COPY_DATA(led_red_color, colorType, 0, 3);
        colorType[2] = currentV;
        
        while (effectMode == WS2812_EFFECT_BREATH && signal == 0)
        {
            WS2812_BreathLED(led_red_color, colorType, BREATH_DELAY_TIME, &signal);
        }
    }
    
    if (currentMode != mode)
    {
        return;
    }
    
    if (colorEnable & ORANGE_EFFECT_ENABLE)
    {
        currentV = colorType[2];
        signal = 0;
        COPY_DATA(led_orange_color, colorType, 0, 3);
        colorType[2] = currentV;
        while (effectMode == WS2812_EFFECT_BREATH && signal == 0)
        {
            WS2812_BreathLED(led_orange_color, colorType, BREATH_DELAY_TIME, &signal);
        }
    }
    
    if (currentMode != mode)
    {
        return;
    }
    
    if (colorEnable & YELLOW_EFFECT_ENABLE)
    {
        signal = 0;
        currentV = colorType[2];
        COPY_DATA(led_yellow_color, colorType, 0, 3);
        colorType[2] = currentV;
        while (effectMode == WS2812_EFFECT_BREATH && signal == 0)
        {
            WS2812_BreathLED(led_yellow_color, colorType, BREATH_DELAY_TIME, &signal);
        }
    }
    
    if (currentMode != mode)
    {
        return;
    }
    
    if (colorEnable & GREEN_EFFECT_ENABLE)
    {
        signal = 0;
        currentV = colorType[2];
        COPY_DATA(led_green_color, colorType, 0, 3);
        colorType[2] = currentV;
        while (effectMode == WS2812_EFFECT_BREATH && signal == 0)
        {
            WS2812_BreathLED(led_green_color, colorType, BREATH_DELAY_TIME, &signal);
        }
    }
    
    if (currentMode != mode)
    {
        return;
    }
    
    if (colorEnable & CYAN_EFFECT_ENABLE)
    {
        signal = 0;
        currentV = colorType[2];
        COPY_DATA(led_cyan_color, colorType, 0, 3);
        colorType[2] = currentV;
        while (effectMode == WS2812_EFFECT_BREATH && signal == 0)
        {
            WS2812_BreathLED(led_cyan_color, colorType, BREATH_DELAY_TIME, &signal);
        }
    }
    
    if (currentMode != mode)
    {
        return;
    }
    
    if (colorEnable & BLUE_EFFECT_ENABLE)
    {
        signal = 0;
        currentV = colorType[2];
        COPY_DATA(led_blue_color, colorType, 0, 3);
        colorType[2] = currentV;
        while (effectMode == WS2812_EFFECT_BREATH && signal == 0)
        {
            WS2812_BreathLED(led_blue_color, colorType, BREATH_DELAY_TIME, &signal);
        }
    }
    
    if (currentMode != mode)
    {
        return;
    }
    
    if (colorEnable & PURPLE_EFFECT_ENABLE)
    {
        signal = 0;
        currentV = colorType[2];
        COPY_DATA(led_purple_color, colorType, 0, 3);
        colorType[2] = currentV;
        while (effectMode == WS2812_EFFECT_BREATH && signal == 0)
        {
            WS2812_BreathLED(led_purple_color, colorType, BREATH_DELAY_TIME, &signal);
        }
        currentV = colorType[2];
    }
    
    if (currentMode != mode)
    {
        return;
    }
    
    if (colorEnable & WHITE_EFFECT_ENABLE)
    {
        signal = 0;
        currentV = colorType[2];
        COPY_DATA(led_white_color, colorType, 0, 3);
        colorType[2] = currentV;
        while (effectMode == WS2812_EFFECT_BREATH && signal == 0)
        {
            WS2812_BreathLED(led_white_color, colorType, BREATH_DELAY_TIME, &signal);
        }
        currentV = colorType[2];
    }
}



void WS2812_FlashEffect(unsigned char mode, unsigned char colorEnable, unsigned short delayTime)
{
    uint8_t R = 0, G = 0, B = 0;
    if (colorEnable & RED_EFFECT_ENABLE)
    {
        HSV2RGB(led_red_color[0], led_red_color[1], led_red_color[2], &R, &G, &B);
        SetWholeColor(R, G, B);
    }
    else if (colorEnable & ORANGE_EFFECT_ENABLE)
    {
        HSV2RGB(led_orange_color[0], led_orange_color[1], led_orange_color[2], &R, &G, &B);
        SetWholeColor(R, G, B);
    }
    else if (colorEnable & YELLOW_EFFECT_ENABLE)
    {
        HSV2RGB(led_yellow_color[0], led_yellow_color[1], led_yellow_color[2], &R, &G, &B);
        SetWholeColor(R, G, B);
    }
    else if (colorEnable & GREEN_EFFECT_ENABLE)
    {
        HSV2RGB(led_green_color[0], led_green_color[1], led_green_color[2], &R, &G, &B);
        SetWholeColor(R, G, B);
    }
    else if (colorEnable & CYAN_EFFECT_ENABLE)
    {
        HSV2RGB(led_cyan_color[0], led_cyan_color[1], led_cyan_color[2], &R, &G, &B);
        SetWholeColor(R, G, B);
    }
    else if (colorEnable & BLUE_EFFECT_ENABLE)
    {
        HSV2RGB(led_blue_color[0], led_blue_color[1], led_blue_color[2], &R, &G, &B);
        SetWholeColor(R, G, B);
    }
    else if (colorEnable & PURPLE_EFFECT_ENABLE)
    {
        HSV2RGB(led_purple_color[0], led_purple_color[1], led_purple_color[2], &R, &G, &B);
        SetWholeColor(R, G, B);
    }
    else if (colorEnable & WHITE_EFFECT_ENABLE)
    {
        HSV2RGB(led_white_color[0], led_white_color[1], led_white_color[2], &R, &G, &B);
        SetWholeColor(R, G, B);
    }
    WS2812_Update();
    
    if (mode != WS2812_EFFECT_FLASH)
    {
        Delay_Ms(1);
        return;
    }
    Delay_Ms(delayTime);
    SetWholeColor(0, 0, 0);
    WS2812_Update();
    Delay_Ms(delayTime);
}
#define WS2812_LightEffect(colorEnable)                 WS2812_FlashEffect(WS2812_EFFECT_LIGHT, colorEnable, 0)


void WS2812_Display(void)
{
    switch (currentMode)
    {
        case BREATH_COLOR_CIRCULAR:
            WS2812_BreathEffect(BREATH_COLOR_CIRCULAR, WS2812_EFFECT_BREATH, RED_EFFECT_ENABLE | ORANGE_EFFECT_ENABLE | YELLOW_EFFECT_ENABLE
                                | GREEN_EFFECT_ENABLE | CYAN_EFFECT_ENABLE | BLUE_EFFECT_ENABLE | PURPLE_EFFECT_ENABLE);
            break;
        case BREATH_RED:
            WS2812_BreathEffect(BREATH_RED, WS2812_EFFECT_BREATH, RED_EFFECT_ENABLE);
            break;
        case BREATH_ORGANGE:
            WS2812_BreathEffect(BREATH_ORGANGE, WS2812_EFFECT_BREATH, ORANGE_EFFECT_ENABLE);
            break;
        case BREATH_YELLOW:
            WS2812_BreathEffect(BREATH_YELLOW, WS2812_EFFECT_BREATH, YELLOW_EFFECT_ENABLE);
            break;
        case BREATH_GREEN:
            WS2812_BreathEffect(BREATH_GREEN, WS2812_EFFECT_BREATH, GREEN_EFFECT_ENABLE);
            break;
        case BREATH_CYAN:
            WS2812_BreathEffect(BREATH_CYAN, WS2812_EFFECT_BREATH, CYAN_EFFECT_ENABLE);
            break;
        case BREATH_BLUE:
            WS2812_BreathEffect(BREATH_BLUE, WS2812_EFFECT_BREATH, BLUE_EFFECT_ENABLE);
            break;
        case BREATH_PURPLE:
            WS2812_BreathEffect(BREATH_PURPLE, WS2812_EFFECT_BREATH, PURPLE_EFFECT_ENABLE);
            break;
        case BREATH_WHITE:
            WS2812_BreathEffect(BREATH_WHITE, WS2812_EFFECT_BREATH, WHITE_EFFECT_ENABLE);
            break;
        case BREATH_RED_GREEN:
            WS2812_BreathEffect(BREATH_RED_GREEN, WS2812_EFFECT_BREATH, RED_EFFECT_ENABLE | GREEN_EFFECT_ENABLE);
            break;

        case BREATH_RED_BLUE:
            WS2812_BreathEffect(BREATH_RED_BLUE, WS2812_EFFECT_BREATH, RED_EFFECT_ENABLE | BLUE_EFFECT_ENABLE);
            break;
        
        case BREATH_RED_PURPLE:
            WS2812_BreathEffect(BREATH_RED_PURPLE, WS2812_EFFECT_BREATH, RED_EFFECT_ENABLE | PURPLE_EFFECT_ENABLE);
            break;

        case BREATH_GREEN_BLUE:
            WS2812_BreathEffect(BREATH_GREEN_BLUE, WS2812_EFFECT_BREATH, GREEN_EFFECT_ENABLE | BLUE_EFFECT_ENABLE);
            break;
        
        case BREATH_GREEN_PURPLE:
            WS2812_BreathEffect(BREATH_GREEN_PURPLE, WS2812_EFFECT_BREATH, GREEN_EFFECT_ENABLE | PURPLE_EFFECT_ENABLE);
            break;

        case BREATH_BLUE_PURPLE:
            WS2812_BreathEffect(BREATH_BLUE_PURPLE, WS2812_EFFECT_BREATH, BLUE_EFFECT_ENABLE | PURPLE_EFFECT_ENABLE);
        break;

        case BREATH_RED_GREEN_BLUE:
            WS2812_BreathEffect(BREATH_RED_GREEN_BLUE, WS2812_EFFECT_BREATH, RED_EFFECT_ENABLE | GREEN_EFFECT_ENABLE | BLUE_EFFECT_ENABLE);
        break;

        case BREATH_RED_GREEN_PURPLE:
            WS2812_BreathEffect(BREATH_RED_GREEN_PURPLE, WS2812_EFFECT_BREATH, RED_EFFECT_ENABLE | GREEN_EFFECT_ENABLE | PURPLE_EFFECT_ENABLE);
            break;
        
        case BREATH_RED_BLUE_PURPLE:
            WS2812_BreathEffect(BREATH_RED_BLUE_PURPLE, WS2812_EFFECT_BREATH, RED_EFFECT_ENABLE | BLUE_EFFECT_ENABLE | PURPLE_EFFECT_ENABLE);
            break;

        case BREATH_GREEN_BLUE_PURPLE:
            WS2812_BreathEffect(BREATH_GREEN_BLUE_PURPLE, WS2812_EFFECT_BREATH, GREEN_EFFECT_ENABLE | BLUE_EFFECT_ENABLE | PURPLE_EFFECT_ENABLE);
            break;

        case BREATH_RED_GREEN_BLUE_PLUPLE:
            WS2812_BreathEffect(BREATH_RED_GREEN_BLUE_PLUPLE, WS2812_EFFECT_BREATH, RED_EFFECT_ENABLE | GREEN_EFFECT_ENABLE | BLUE_EFFECT_ENABLE | PURPLE_EFFECT_ENABLE);
            break;

        case BLINK_RED:
            WS2812_FlashEffect(WS2812_EFFECT_FLASH, RED_EFFECT_ENABLE, 100);
            break;
        
        case BLINK_ORANGE:
            WS2812_FlashEffect(WS2812_EFFECT_FLASH, ORANGE_EFFECT_ENABLE, 100);
            break;
        
        case BLINK_YELLOW:
            WS2812_FlashEffect(WS2812_EFFECT_FLASH, YELLOW_EFFECT_ENABLE, 100);
            break;

        case BLINK_GREEN:
            WS2812_FlashEffect(WS2812_EFFECT_FLASH, GREEN_EFFECT_ENABLE, 100);
            break;

        case BLINK_CYAN:
            WS2812_FlashEffect(WS2812_EFFECT_FLASH, CYAN_EFFECT_ENABLE, 100);
            break;

        case BLINK_BLUE:
            WS2812_FlashEffect(WS2812_EFFECT_FLASH, BLUE_EFFECT_ENABLE, 100);
            break;

        case BLINK_PURPLE:
            WS2812_FlashEffect(WS2812_EFFECT_FLASH, PURPLE_EFFECT_ENABLE, 100);
            break;

        case BLINK_WHITE:
            WS2812_FlashEffect(WS2812_EFFECT_FLASH, WHITE_EFFECT_ENABLE, 100);
            break;
        
        case LIGHT_RED:
            WS2812_LightEffect(RED_EFFECT_ENABLE);
            break;
        
        case LIGHT_ORANGE:
            WS2812_LightEffect(ORANGE_EFFECT_ENABLE);
            break;
        
        case LIGHT_YELLOW:
            WS2812_LightEffect(YELLOW_EFFECT_ENABLE);
            break;

        case LIGHT_GREEN:
            WS2812_LightEffect(GREEN_EFFECT_ENABLE);
            break;

        case LIGHT_CYAN:
            WS2812_LightEffect(CYAN_EFFECT_ENABLE);
            break;

        case LIGHT_BLUE:
            WS2812_LightEffect(BLUE_EFFECT_ENABLE);
            break;

        case LIGHT_PURPLE:
            WS2812_LightEffect(PURPLE_EFFECT_ENABLE);
            break;

        case LIGHT_WHITE:
            WS2812_LightEffect(WHITE_EFFECT_ENABLE);
            break;
        case LED_CUSTOM:
            SetWholeColor(custom_rgb[0], custom_rgb[1], custom_rgb[2]);
            WS2812_Update();
            Delay_Ms(1);
            break;
    }
}
#else
void WS2812_send(uint8_t (*color)[3], uint16_t len)
{
    uint8_t i;
    uint8_t j;
    uint16_t memaddr;
    uint16_t buffersize;
    buffersize = (len*24)+43;	// number of bytes needed is #LEDs * 24 bytes + 42 trailing bytes
    memaddr = 0;				// reset buffer memory index
    j=0;

    while (len)
    {	
        for(i=0; i<8; i++) // GREEN data
        {
            LED_Buffer[memaddr] = ((color[j][1]<<i) & 0x0080) ? WS2812_1:WS2812_0;
            memaddr++;
        }
        for(i=0; i<8; i++) // RED
        {
                LED_Buffer[memaddr] = ((color[j][0]<<i) & 0x0080) ? WS2812_1:WS2812_0;
                memaddr++;
        }
        for(i=0; i<8; i++) // BLUE
        {
                LED_Buffer[memaddr] = ((color[j][2]<<i) & 0x0080) ? WS2812_1:WS2812_0;
                memaddr++;
        }
        len--;
        j++;
    }
//===================================================================//	
//bug：最后一个周期波形不知道为什么全是高电平，故增加一个波形
    LED_Buffer[memaddr] = ((color[j-1][2]<<8) & 0x0080) ? WS2812_1:WS2812_0;
//===================================================================//	
      memaddr++;	
        while(memaddr < buffersize)
        {
            LED_Buffer[memaddr] = 0;
            memaddr++;
        }

        TransimitSuccessFlag = FALSE;
        HAL_TIM_PWM_Start_DMA(&g_GeneralTimer3Handle, TIM_CHANNEL_3, (uint32_t *)&LED_Buffer, LED_BUFFER_SIZE);
        while(!TransimitSuccessFlag);	// wait until transfer complete
        HAL_TIM_PWM_Stop_DMA(&g_GeneralTimer3Handle, TIM_CHANNEL_3);
}

#define LED_MAX_NUMBER   35
uint8_t  color_off[LED_MAX_NUMBER][3]={{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}};

// 实现ARGB呼吸灯效果
// color_max为每个灯的亮度最大值
// led为灯的个数  ，前提是保证color数组大于灯的个数
void BreathARGB(int delay_time_ms,uint8_t levels,uint8_t (*color_max)[3],uint16_t len)
{
    uint8_t i;
    uint8_t j;
    //亮度临时变化值
    uint8_t color_temp[LED_MAX_NUMBER][3];
    // 每个灯珠的亮度变化步进值
    uint8_t color_delta[LED_MAX_NUMBER][3];
    uint16_t len_temp;
    
    
    // 如果分级为1，那么常亮
    if(levels==1) 
    {
            WS2812_send(color_max,len);
            return;
    }
    else if(levels==0)	// 如果分级为0，那么常灭
    {
            WS2812_send(color_off,len);
            return;
    }
    
    j=0;
    len_temp=len;
    while (len_temp)
    {
        // 计算每个灯珠的亮度变化步进值
        color_delta[j][0]=(uint8_t)(color_max[j][0]/levels);
        color_delta[j][1]=(uint8_t)(color_max[j][1]/levels);
        color_delta[j][2]=(uint8_t)(color_max[j][2]/levels);
        color_temp[j][0]=0;
        color_temp[j][1]=0;
        color_temp[j][2]=0;

        len_temp--;
        j++;
    }
        
    // 呼吸灯效果
    for(i=0;i<levels;i++)
    {	
    
        j=0;
        len_temp=len;
        while (len_temp)
        {
            color_temp[j][0]+=color_delta[j][0];
            color_temp[j][1]+=color_delta[j][1];
            color_temp[j][2]+=color_delta[j][2];
            len_temp--;
            j++;
        }
        WS2812_send(color_temp,len);
        Delay_Ms(delay_time_ms);
    }
    
    
    // 达到最大亮度值
    j=0;
    len_temp=len;
    while (len_temp)
    {
        color_temp[j][0]=color_max[j][0];
        color_temp[j][1]=color_max[j][1];
        color_temp[j][2]=color_max[j][2];
        len_temp--;
        j++;
    }
    
    // 呼吸灯效果
    for(i=0;i<levels;i++)
    {
        j=0;
        len_temp=len;
        while (len_temp)
        {
            color_temp[j][0]-=color_delta[j][0];
            color_temp[j][1]-=color_delta[j][1];
            color_temp[j][2]-=color_delta[j][2];

            len_temp--;
            j++;
        }
        WS2812_send(color_temp,len);
        Delay_Ms(delay_time_ms);
    }
}

// 实现ARGB灯闪烁效果
// color_max为每个灯的亮度最大值
// led为灯的个数  ，前提是保证color数组大于灯的个数
void BlinkARGB(int delay_on_time_ms,int delay_off_time_ms,uint8_t (*color_max)[3],uint16_t len)
{
    WS2812_send(color_max,len);
    Delay_Ms(delay_on_time_ms);
    WS2812_send(color_off,len);
    Delay_Ms(delay_off_time_ms);
}

#endif
