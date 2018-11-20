#ifndef __RGB__H__
#define __RGB__H__


#include "main.h"

#define PIN_RGBL   GPIO_PIN_7  
#define PIN_RGBR   GPIO_PIN_6  
#define PORT_RGB  GPIOA

//static inline void RGBL_0(void)        { PORT_RGB->BRR = PIN_RGBL; }
//static inline void RGBL_1(void)        { PORT_RGB->BSRR = PIN_RGBL; }
//static inline void RGBR_0(void)        { PORT_RGB->BRR = PIN_RGBR; }
//static inline void RGBR_1(void)        { PORT_RGB->BSRR = PIN_RGBR; }
#define RGBL_0 		(PORT_RGB->BRR = PIN_RGBL)
#define RGBL_1		(PORT_RGB->BSRR = PIN_RGBL)


#define	YellowGreen	 0x2fFF00
#define Green		 0x00FF00
#define	GreenBlue	 0x00FFFF
#define	BlueGreen	 0x00117F
#define	Blue		 0x0000FF

#define	YellowOrange 0xFF8000
#define	Orange		 0xFF6100
#define	OrangeRed	 0xFF4500
#define	Red			 0xff0000
#define Pink		 0xff2010
//#define	YellowGreen	 0x00FF2f
//#define Green		 0x00FF00
//#define	GreenBlue	 0xFFFF00
//#define	BlueGreen	 0x7F1100
//#define	Blue		 0xFF0000
//
//#define	YellowOrange 0x0080FF
//#define	Orange		 0x0061FF
//#define	OrangeRed	 0x0045FF
//#define	Red			 0x0000ff
//#define Pink		 0x1020ff


#define	Purple		 0xF020A0


#define TIME_LEN (360 * 4)


#define NORMAL	1
#define	BREATH	2

typedef struct{
	float start_r;
	float start_g;
	float start_b;
	float end_r;
	float end_g;
	float end_b;
	
	float step_r;
	float step_g;
	float step_b;
	
	uint8_t flage;
	uint32_t track;	
	uint32_t start_time;
}Color;
#endif