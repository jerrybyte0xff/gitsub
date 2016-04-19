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
     u8 keyno;
  	 LEDInit();
	 delay_init(168);
	 GPIO_KEY_Config();
	 while(1)
	 {
	 	keyno = ReadKeyDown();
		if (keyno)
		{
			Led_Turn_on(keyno - 1);
		}

	
	  
	 }
}

/*********************************************END OF FILE**********************/

