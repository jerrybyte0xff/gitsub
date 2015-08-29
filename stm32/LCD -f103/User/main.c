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
     
	 delay_init(168);
	 GPIO_KEY_Config();
	 uart_init(115200);
	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	 ILI9806E_Initializtion();
	 LCD_SSD1963_init();
	 while(1)
	 {
	
//	 	keyno = ReadKeyDown();	
//		printf("\n\r  ("__DATE__ " - " __TIME__ ")");
//     	printf("end");
//		if (keyno)
//		{
//			 Led_Turn_on(keyno - 1);
//			 printf("\r\n\n\n key[%d] pushed",keyno );
//			 printf("\n\r  ("__DATE__ " - " __TIME__ ")");
//
//
//		}
	 	printf("\n\r  ("__DATE__ " - " __TIME__ ")");
	 	LCD_SSD1963_clear(GREEN);
	 	delay_ms(3000);
		LCD_SSD1963_clear(YELLOW);

	
	  
	 }
}

/*********************************************END OF FILE**********************/

