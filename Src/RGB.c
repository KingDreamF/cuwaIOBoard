#include "RGB.h"



/*
@funtion:发送8位数据，高位先发送，
由于5050led灯的时序要在ns，所以使用汇编空转
	0:0.4us的高电平，0.85us的低电平
	1:0.8us的高电平，0.45us的低电平
@data：准备发送的数据
@return：NULL
*/
static void Send_8bits(uint8_t data) 
{    
  	uint8_t a; 
	for(a=0;a<8;a++) 
	{      
		RGBL_1;  
		if(data & 0x80)  
		{       
		  asm("nop");asm("nop");asm("nop");
		  asm("nop");asm("nop");asm("nop");    
		  asm("nop");asm("nop");asm("nop");
		  asm("nop");asm("nop");asm("nop");
		  asm("nop");asm("nop");asm("nop");
		  asm("nop");asm("nop");asm("nop");
		  asm("nop");asm("nop");asm("nop");
		  asm("nop");asm("nop");asm("nop");
		  asm("nop");asm("nop");asm("nop");
		  asm("nop");asm("nop");asm("nop");
		  asm("nop");asm("nop");asm("nop");
		  asm("nop");asm("nop");asm("nop");
		  data=data<<1;       
		  RGBL_0;
		  asm("nop");asm("nop");asm("nop");
		}
		else
		{
			asm("nop");asm("nop");asm("nop");
			asm("nop");asm("nop");asm("nop");
			data=data<<1;
			RGBL_0;       
			asm("nop");asm("nop");asm("nop");
			asm("nop");asm("nop");asm("nop");    
			asm("nop");asm("nop");asm("nop");
			asm("nop");asm("nop");asm("nop");
			asm("nop");asm("nop");asm("nop");
			asm("nop");asm("nop");asm("nop");
			asm("nop");asm("nop");asm("nop");
			asm("nop");asm("nop");asm("nop");
			asm("nop");asm("nop");asm("nop");
			asm("nop");asm("nop");asm("nop");
			asm("nop");asm("nop");asm("nop");
			asm("nop");asm("nop");asm("nop");
		
		}
	}
	
}
/*
@funtion:一帧数据传输以rst开始并且以rst结束
@return：NULL
*/
static void rst() 
{   
	uint16_t i;  
	RGBL_0; 
	for(i=0;i<1000;i++);
}

/*
@funtion:发送一帧RGB值
	由于串联了两个灯，所以一帧发送两个RGB值。
	5050LED驱动发送颜色顺序是G-R-B，所以做了一下调整
	参数顺序是R-G-B
@data1:红色
@data2:绿色
@data3:蓝色
b-r-g
@return：NULL
*/


static void Send_RGB_24bits(uint8_t data1,uint8_t data2,uint8_t data3) 
{   
//  if(dataDiff(data1,data2,data3)==0)
//  {
//  //	return;
//  }
  	rst();

	Send_8bits(data3);
	Send_8bits(data1);
	Send_8bits(data2);
	
	Send_8bits(data1);
	Send_8bits(data2);  
	Send_8bits(data3);
	 
	rst();
	
	//if(data2>0 ||data1>0||data3>0)
	//printf("r:%d	g:%d	b:%d\n",(int)data2,(int)data1,(int)data3);
} 

Color color_rgb;
uint32_t last_color =0;
float g_light =0;
uint8_t time =1;
/*
funtion:设置RGB灯的闪烁频率，颜色，亮度


*/
void setRGBArgument(uint32_t hz, uint32_t color,uint32_t light)
{
  	if(light>=100)
	  g_light=1.0;
	else if(light<=0)
	{
		g_light=0.0;
	}
  	g_light = light/100.0;
	
//	color_rgb.start_r = (last_color>>16&0xff)*g_light;
//	color_rgb.start_g = (last_color>>8&0xff)*g_light;
//	color_rgb.start_b = (last_color&0xff)*g_light;

	color_rgb.end_r = (color>>16&0xff)*g_light;
	color_rgb.end_g = (color>>8&0xff)*g_light;
	color_rgb.end_b = (color&0xff)*g_light;

//	color_rgb.step_r = (color_rgb.start_r - color_rgb.end_r)/(float)time/10;
//	color_rgb.step_g = (color_rgb.start_g - color_rgb.end_g)/(float)time/10;
//	color_rgb.step_b = (color_rgb.start_b - color_rgb.end_b)/(float)time/10;
//
//
//	color_rgb.track = time;
//
//	color_rgb.start_time = HAL_GetTick();
	
	last_color = color;
	  
}


uint8_t a =0xff,step=10;
void test()
{
	Send_RGB_24bits(a,0x00,0x00);
	if(a<=1)
	  step = 2;
	else if(a>=0xff)
	  step=-2;
	
	a+=step;
	
}
void test2()
{
	Send_RGB_24bits(color_rgb.end_r,color_rgb.end_g,color_rgb.end_b);
}

















#if 0
Color color_rgb;

//kalman kalman_r,kalman_g,kalman_b;
uint32_t cur_time;
static int hz =  200,dir =1;
float breath = 0;
int index = 0;
uint8_t g_light =100;
/*
颜色初始化颜色结构体。
*/
static void color_init(uint32_t start_color, uint32_t end_color, uint32_t time)
{
	color_rgb.start_r = (start_color>>16&0xff)*g_light;
	color_rgb.start_g = (start_color>>8&0xff)*g_light;
	color_rgb.start_b = (start_color&0xff)*g_light;

	color_rgb.end_r = (end_color>>16&0xff)*g_light;
	color_rgb.end_g = (end_color>>8&0xff)*g_light;
	color_rgb.end_b = (end_color&0xff)*g_light;

	color_rgb.step_r = (color_rgb.start_r - color_rgb.end_r)/(float)time/10;
	color_rgb.step_g = (color_rgb.start_g - color_rgb.end_g)/(float)time/10;
	color_rgb.step_b = (color_rgb.start_b - color_rgb.end_b)/(float)time/10;

	// kalman_init(&kalman_r, 1.0f,1.0f ,0.5f,100.0f);
	// kalman_init(&kalman_g, 1.0f,1.0f ,0.5f,100.0f);
	// kalman_init(&kalman_b, 1.0f,1.0f ,0.5f,100.0f);

	color_rgb.track = time;

	color_rgb.start_time = HAL_GetTick();
	

}

//呼吸方式
static void breathHZ()
{
	if(dir)
	{
		if(hz<200)
		  hz++;
		else
		  dir =0;
	}else
	{
	  if(hz >10)
		hz--;
	  else
		dir =1;
	}
	//breath  = kalman_calc(&m_kalman_breath,hz);
	breath = breath/255 ;
	//printf("breath:%f	hz:%d\n",breath1,hz);
}

/*
	颜色渐变过程

*/
#define HZ_TIME(a) ( a == BREATH ? 20 : 20 )
static void colorChange(uint8_t model)
{
  	
	if(HAL_GetTick() - color_rgb.start_time > HZ_TIME(model))
	{
		if(model == BREATH)
		{
			if(index < 4)
 	  			breathHZ();
		}else if(model == NORMAL)
			breath = 1;
			

	  	color_rgb.start_time = HAL_GetTick();
	  	//red
	  	if(color_rgb.step_r > 0)
	  	{
			if(color_rgb.start_r >= color_rgb.end_r + color_rgb.step_r)
			{
				color_rgb.start_r-= color_rgb.step_r;
			}else
				color_rgb.start_r = color_rgb.end_r;
	  	}
	  	else if(color_rgb.step_r < 0)
	  	{
	  		if(color_rgb.start_r <= color_rgb.end_r - color_rgb.step_r)
			{
				color_rgb.start_r -= color_rgb.step_r;
			}else
				color_rgb.start_r = color_rgb.end_r;	
	  	}
	  	//float red = kalman_calc(&kalman_r,color_rgb.start_r*g_light)*breath;


	  	//green
	  	if(color_rgb.step_g > 0)
	  	{
			if(color_rgb.start_g >= color_rgb.end_g + color_rgb.step_g)
			{
				color_rgb.start_g -= color_rgb.step_g;
			}else
				color_rgb.start_g = color_rgb.end_g;
	  	}
	  	else if(color_rgb.step_g < 0)
	  	{
	  		if(color_rgb.start_g <= color_rgb.end_g - color_rgb.step_g)
			{
				color_rgb.start_g -= color_rgb.step_g;
			}else
				color_rgb.start_g = color_rgb.end_g;	
	  	}
	  	//float green = kalman_calc(&kalman_g,color_rgb.start_g*g_light)*breath;


	  	//blue
	  	if(color_rgb.step_b > 0)
	  	{
			if(color_rgb.start_b >= color_rgb.end_b + color_rgb.step_b)
			{
				color_rgb.start_b -= color_rgb.step_b;
			}else
				color_rgb.start_b = color_rgb.end_b;
	  	}
	  	else if(color_rgb.step_b < 0)
	  	{
	  		if(color_rgb.start_b <= color_rgb.end_b - color_rgb.step_b)
			{
				color_rgb.start_b -= color_rgb.step_b;
			}else
				color_rgb.start_b = color_rgb.end_b;	
	  	}
		
		//float blue = kalman_calc(&kalman_b,color_rgb.start_b*g_light)*breath;
		//Send_2811_24bits((uint8_t)red,(uint8_t)green,(uint8_t)blue);
		Send_RGB_24bits((uint8_t)color_rgb.start_r,(uint8_t)color_rgb.start_g,(uint8_t)color_rgb.start_b);
		//printf("r:%f	g:%f	b:%f	%f\n",red,green,blue,breath);
	}
}


//检查颜色渐变是否结束
static int  checkEnd(int value)
{
  	
	if((abs(color_rgb.start_r - color_rgb.end_r) < 0.1)
		&& (abs(color_rgb.start_g - color_rgb.end_g) < 0.1)
		&& (abs(color_rgb.start_b - color_rgb.end_b) < 0.1))
	{
		color_rgb.flage &= ~0x01;
		if(index <= value)
			index ++;
	}
	return index;	
}
//设置开始颜色和结束颜色值
static void colorSet(uint32_t start_color, uint32_t end_color, uint32_t time)
{
	if(( color_rgb.flage & 0x01 ) == 0)
	{
		color_init(start_color,end_color,time);
		color_rgb.flage |= 0x01;
	}
}
/*
	@funtion：颜色两种颜色交替
	@parameter:循环次数
*/
void calmingW(int value)
{
	if(index < value)
	{
		switch(index % 2)//颜色交替
		{
			case 0:
				colorSet(GreenBlue,BlueGreen,30);
				break;
			case 1:
				colorSet(BlueGreen,GreenBlue,30);
				break;
		};
	}
	else if(index == value) //模式结束后熄灭
	{
		if((index % 2) == 0)
			colorSet(BlueGreen,0,30);
	 	if((index % 2) == 1)
			colorSet(GreenBlue,0,30);
	}
		
	colorChange(NORMAL);
	index = checkEnd(value);
}
void strengthenW()
{
	
	switch(index)
	{
		case 0:
			colorSet(YellowGreen,Green,TIME_LEN);
			break;
		case 1:
			colorSet(Green,GreenBlue,TIME_LEN);
			break;
		case 2:
			colorSet(GreenBlue,BlueGreen,TIME_LEN);
			break;
		case 3:
			colorSet(BlueGreen,Blue,TIME_LEN);
			break;
		case 4:
			colorSet(Blue,0,30);
			break;
	};
	//breathChange();
	colorChange(BREATH);
	index = checkEnd(4);
}
#endif