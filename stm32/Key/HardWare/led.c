#include "led.h"



void LEDInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	/* Enable GPIOB, GPIOC and AFIO clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);  //RCC_APB2Periph_AFIO
	
	/* LEDs pins configuration */
	GPIO_InitStructure.GPIO_Pin = GPIO_LED_ALL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIO_LED_PORT, &GPIO_InitStructure);
}

void Led_Turn_on_all(void)
{
	/* Turn On All LEDs */
    GPIO_ResetBits(GPIO_LED_PORT, GPIO_LED_ALL);
}

void Led_Turn_on_1(void)
{
	/* Turn On LED1 */
    GPIO_ResetBits(GPIO_LED_PORT, GPIO_LED1);
}

void Led_Turn_on_2(void)
{
	/* Turn On LED2 */
    GPIO_ResetBits(GPIO_LED_PORT, GPIO_LED2 );
}

void Led_Turn_on_3(void)
{
	/* Turn On LED3 */
    GPIO_ResetBits(GPIO_LED_PORT, GPIO_LED3);
}


void Led_Turn_on_4(void)
{
	/* Turn On LED3 */
    GPIO_ResetBits(GPIO_LED_PORT, GPIO_LED4);
}

void Led_Turn_off_all(void)
{
	/* Turn Off All LEDs */
    GPIO_SetBits(GPIO_LED_PORT, GPIO_LED_ALL);
}

void Led_Turn_on(u8 led)
{
    Led_Turn_off_all();

	/* Turn Off Select LED */
    switch(led)
    {
        case 0:
          Led_Turn_on_1();
          break;

        case 1:
          Led_Turn_on_2();
          break;

        case 2:
          Led_Turn_on_3();
          break;

        case 3:
          Led_Turn_on_4();
          break;
          
        default:
          Led_Turn_off_all();
          break;
    }
}
