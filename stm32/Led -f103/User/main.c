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


/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
  /**************************************************************
* @file    main.c
* @author  liuznchang			
* @version V1.0
* @date    14:41 2015/7/9
* @brief   Led Test
*************************************************************/


int main(void)
{
      u16 height;
	 delay_init(168);
	 GPIO_KEY_Config();
	 uart_init(115200);
	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	 ILI9806E_Initializtion();
	 while(1)
	 {
		for (height = 0; height < Lcd_Height; height++)
		{
			  Lcd_Fill_Disp(Red_262k); 

		}
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

	
	  
	 }
}

/*********************************************END OF FILE**********************/

