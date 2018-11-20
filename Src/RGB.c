#include "RGB.h"



/*
@funtion:����8λ���ݣ���λ�ȷ��ͣ�
����5050led�Ƶ�ʱ��Ҫ��ns������ʹ�û���ת
	0:0.4us�ĸߵ�ƽ��0.85us�ĵ͵�ƽ
	1:0.8us�ĸߵ�ƽ��0.45us�ĵ͵�ƽ
@data��׼�����͵�����
@return��NULL
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
@funtion:һ֡���ݴ�����rst��ʼ������rst����
@return��NULL
*/
static void rst() 
{   
	uint16_t i;  
	RGBL_0; 
	for(i=0;i<1000;i++);
}

/*
@funtion:����һ֡RGBֵ
	���ڴ����������ƣ�����һ֡��������RGBֵ��
	5050LED����������ɫ˳����G-R-B����������һ�µ���
	����˳����R-G-B
@data1:��ɫ
@data2:��ɫ
@data3:��ɫ
b-r-g
@return��NULL
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
funtion:����RGB�Ƶ���˸Ƶ�ʣ���ɫ������


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
��ɫ��ʼ����ɫ�ṹ�塣
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

//������ʽ
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
	��ɫ�������

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


//�����ɫ�����Ƿ����
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
//���ÿ�ʼ��ɫ�ͽ�����ɫֵ
static void colorSet(uint32_t start_color, uint32_t end_color, uint32_t time)
{
	if(( color_rgb.flage & 0x01 ) == 0)
	{
		color_init(start_color,end_color,time);
		color_rgb.flage |= 0x01;
	}
}
/*
	@funtion����ɫ������ɫ����
	@parameter:ѭ������
*/
void calmingW(int value)
{
	if(index < value)
	{
		switch(index % 2)//��ɫ����
		{
			case 0:
				colorSet(GreenBlue,BlueGreen,30);
				break;
			case 1:
				colorSet(BlueGreen,GreenBlue,30);
				break;
		};
	}
	else if(index == value) //ģʽ������Ϩ��
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