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
     u8 ledcount;
  	 LEDInit();
	 delay_init(168);
	 while(1)
	  {
	    delay_ms (200);
	    Led_Turn_on_all();
	    delay_ms (200);
		Led_Turn_off_all();
		delay_ms (200);
		for (ledcount = 0; ledcount < 4; ledcount++)
		{
			Led_Turn_on(ledcount);
			delay_ms (200);
		}
		Led_Turn_off_all();
	  
	  }
}

/*********************************************END OF FILE**********************/

