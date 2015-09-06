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
	 delay_init(168);
	 //GPIO_KEY_Config();
	 uart_init(115200);
	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	 ILI9806E_Initializtion();
	 LCD_SSD1963_init();
/********************show image**********************/
	 	printf("\n\r  ("__DATE__ " - " __TIME__ ")\n");
	LCD_SSD1963_clear(RED);
	LCD_SSD1963_putstring(20,20,"hello world",BLACK,BLUE);
	
#if 0
	 	LCD_SSD1963_clear(GREEN);
	 	delay_ms(5000);

	 	LCD_SSD1963_drawrectangle(200, 200, 400, 400,1,RED);

	(void) LCD_SSD1963_putstring(20,20,"hello world",BLACK,BLUE);

	LCD_SSD1963_getpoint(0, 0, &temp);
	
	printf("\n\r site:0-0:[%x]",temp);
	
	LCD_SSD1963_getpoint(10, 10, &temp);
	
	printf("\n\r site:10-10:[%x]",temp);
	
	LCD_SSD1963_getpoint(100, 100, &temp);
	
	printf("\n\r site:100-100:[%x]",temp);
	
	LCD_SSD1963_getpoint(200, 200, &temp);
	
	printf("\n\r site:200-200:[%x]",temp);
	
	LCD_SSD1963_getpoint(400, 400, &temp);
	
	printf("\n\r site:400-400:[%x]",temp);
	
	LCD_SSD1963_getpoint(0, 0, &temp);
	
	printf("\n\r site:0-0:[%x]",temp);
	
	LCD_SSD1963_getpoint(10, 10, &temp);
	
	printf("\n\r site:10-10:[%x]",temp);
	
	LCD_SSD1963_getpoint(100, 100, &temp);
	
	printf("\n\r site:100-100:[%x]",temp);
	
	LCD_SSD1963_getpoint(200, 200, &temp);
	
	printf("\n\r site:200-200:[%x]",temp);
	
	LCD_SSD1963_getpoint(400, 400, &temp);
	
	printf("\n\r site:400-400:[%x]",temp);
	#endif
#if 0
	LCD_SSD1963_clear(RED);
	delay_ms(5000);
	LCD_SSD1963_clear(WHITE);
	delay_ms(5000);
	LCD_SSD1963_clear(YELLOW);
	delay_ms(5000);
	LCD_SSD1963_clear(BLUE);
	delay_ms(5000);
	LCD_SSD1963_clear(BLACK);
	delay_ms(5000);
	LCD_SSD1963_clear(BROWN);
	delay_ms(5000);
	LCD_SSD1963_clear(GRAY);
	delay_ms(5000);
	LCD_SSD1963_clear(YELLOW);
	
#endif
	
	//LCD_DrawPicture(0,0,400,400,gImage_baozi);
//(void) LCD_SSD1963_putstring(20,20,"hello world",BLACK,BLUE);
	while(1);
	 
}

/*********************************************END OF FILE**********************/

