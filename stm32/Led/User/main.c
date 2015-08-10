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




/* Private macro -------------------------------------------------------------*/
#define RCC_GPIO_LED                                 RCC_APB2Periph_GPIOD
#define GPIO_LED_PORT                                GPIOD    
#define GPIO_LED1                                    GPIO_Pin_2    
#define GPIO_LED2                                    GPIO_Pin_3    
#define GPIO_LED3                                    GPIO_Pin_4    
#define GPIO_LED4                                    GPIO_Pin_7
#define GPIO_LED_ALL                                 GPIO_LED1 |GPIO_LED2 |GPIO_LED3 |GPIO_LED4 


void LEDInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	/* Enable GPIOB, GPIOC and AFIO clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD , ENABLE);  //RCC_APB2Periph_AFIO
	
	/* LEDs pins configuration */
	GPIO_InitStructure.GPIO_Pin = GPIO_LED_ALL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIO_LED_PORT, &GPIO_InitStructure);
}




int main(void)
{
  	 LEDInit();
	 delay_init(336);
	 while(1)
	  {
	    delay_ms (1000);
	    GPIO_ResetBits(GPIO_LED_PORT, GPIO_LED_ALL);
	    delay_ms (1000);
		GPIO_SetBits(GPIO_LED_PORT, GPIO_LED_ALL);
	  
	  }
	  /* add your code here ^_^. */
}

/*********************************************END OF FILE**********************/

