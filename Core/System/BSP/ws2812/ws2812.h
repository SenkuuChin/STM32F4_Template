#ifndef __MY_BSP_WS2812_H__
	#define __MY_BSP_WS2812_H__
	#define WS2812_PORT					GPIOB
	#define WS2812_PIN					GPIO_PIN_0
	#define WS2812_CLK_ENABLE()			do { __HAL_RCC_GPIOB_CLK_ENABLE(); } while (0)

	#define TIMER_PERIOD				90							// 定时器周期
	#define LED_NUMBER					(40)						// 灯珠数目
	#define LED_DATA_SIZE				(LED_NUMBER * 24)			// 每个灯珠需要发送24bit数据
	#define LED_BUFFER_SIZE				LED_DATA_SIZE + 1			// 最后一个 RESET 数据
	
	#define WS2812_CUSTOM_PERIOD		0
	#define WS2812_USE_ORIGINAL			0
	#if !WS2812_CUSTOM_PERIOD
	#define WS2812_0					(TIMER_PERIOD / 3)			// 0码占 1/3 
	#define WS2812_1					(TIMER_PERIOD * 2 / 3)		// 1码占 2/3
	#else
	#define WS2812_0					25
	#define WS2812_1					50
	#endif
	#define WS2812_RESET				(0)
	
	#if !WS2812_USE_ORIGINAL
	#define RED_EFFECT_ENABLE			(1 << 0)
	#define ORANGE_EFFECT_ENABLE		(1 << 1)
	#define YELLOW_EFFECT_ENABLE		(1 << 2)
	#define GREEN_EFFECT_ENABLE			(1 << 3)
	#define CYAN_EFFECT_ENABLE			(1 << 4)
	#define BLUE_EFFECT_ENABLE			(1 << 5)
	#define PURPLE_EFFECT_ENABLE		(1 << 6)
	#define WHITE_EFFECT_ENABLE			(1 << 7)
	typedef enum
	{
		BREATH_COLOR_CIRCULAR = 0,
		BREATH_RED,
		BREATH_ORGANGE,
		BREATH_YELLOW,
		BREATH_GREEN,
		BREATH_CYAN,
		BREATH_BLUE,
		BREATH_PURPLE,
		BREATH_WHITE,
		BREATH_RED_GREEN,
		BREATH_RED_BLUE,
		BREATH_RED_PURPLE,
		BREATH_GREEN_BLUE,
		BREATH_GREEN_PURPLE,
		BREATH_BLUE_PURPLE,
		BREATH_RED_GREEN_BLUE,
		BREATH_RED_GREEN_PURPLE,
		BREATH_RED_BLUE_PURPLE,
		BREATH_GREEN_BLUE_PURPLE,
		BREATH_RED_GREEN_BLUE_PLUPLE,
		BLINK_RED,
		BLINK_ORANGE,
		BLINK_YELLOW,
		BLINK_GREEN,
		BLINK_CYAN,
		BLINK_BLUE,
		BLINK_PURPLE,
		BLINK_WHITE,
		LIGHT_RED,
		LIGHT_ORANGE,
		LIGHT_YELLOW,
		LIGHT_GREEN,
		LIGHT_CYAN,
		LIGHT_BLUE,
		LIGHT_PURPLE,
		LIGHT_WHITE,
		LED_CUSTOM = 0xAF
	} WS2812_DisplayMode_Typedef;
	
	typedef enum
	{
		WS2812_EFFECT_BREATH = 0,
		WS2812_EFFECT_LIGHT,
		WS2812_EFFECT_FLASH
	} WS2812_EffectMode_Typedef;
	
	void SetLedColor (unsigned char index, unsigned char red, unsigned char green, unsigned char blue);
	void SetWholeColor (unsigned char red, unsigned char green, unsigned char blue);
	void WS2812_ResetColorData(void);
	
	void WS2812_Update(void);
	
	void WS2812_Display(void);
	#else
	void WS2812_send(unsigned char (*color)[3], unsigned short len);
	void BreathARGB(int delay_time_ms,unsigned char levels,unsigned char (*color_max)[3],unsigned short len);
	void BlinkARGB(int delay_on_time_ms,int delay_off_time_ms,unsigned char (*color_max)[3],unsigned short len);
	#endif
	void WS2812_Init(void);
#endif
