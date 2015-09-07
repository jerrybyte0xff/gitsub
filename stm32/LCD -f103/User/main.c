/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-08-10
  * @brief   Test LED
  ******************************************************************************
  */
  
#include "stm32f10x.h"
#include "delay.h"
#include "led.h"
#include "key.h"
#include "usart.h"	
#include "ili9806e.h"
#include "ssd1963_driver.h"

  /**************************************************************
* @file    main.c
* @author  liuznchang			
* @version V1.0
* @date    14:41 2015/7/9
* @brief   Led Test
*************************************************************/


int main(void)
{
	//u32 temp = 0;
	u16 i,ii;
	delay_init(168);
	uart_init(115200);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	ILI9806E_Initializtion();
	LCD_SSD1963_init();
	

/********************show image**********************/
	while(1)
	{
		/*
		delay_ms(500);		 
		LCD_SSD1963_write_command(0x002c);
		
		for(ii=0;ii<480;ii++)
		{
			LCD_SSD1963_write_data(0xffff);
			
		}
			
		for(i=0;i<800;i++)
		{
			LCD_SSD1963_write_data(0xffff);
			for(ii=0;ii<478;ii++)
			{
		  		LCD_SSD1963_write_data(0x0000);
			}
			LCD_SSD1963_write_data(0xffff);
		}
		for(i=0;i<480;i++)
		{
			LCD_SSD1963_write_data(0xffff);


		}
		
		*/
		delay_ms(5000);	
		LCD_SSD1963_drawrectangle(0, 0, 800, 800,1,RED);
		delay_ms(5000);
		
		LCD_SSD1963_clear(BLUE);
		delay_ms(5000);		
		LCD_SSD1963_putstring(100,100,"hello world",BLACK,RED);
		delay_ms(5000);	
		LCD_SSD1963_drawrectangle(200, 200, 400, 400,1,RED);
		
		delay_ms(5000);	
		 
		/*
		LCD_SSD1963_write_command(0x002C);	
		
		for(i = 0; i < 400; i++) 	 
		{
			for(ii = 0; ii < (HDP+1); ii++) 
			{ 	

				LCD_SSD1963_write_data(GREEN);
			}
			
			
		}
		*/
	}
	
	

}

/*********************************************END OF FILE**********************/

