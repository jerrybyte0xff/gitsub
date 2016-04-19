#ifndef __LED_H
#define __LED_H

#include "stm32f10x.h"

/* Private macro -------------------------------------------------------------*/
#define RCC_GPIO_LED                                 RCC_APB2Periph_GPIOD
#define GPIO_LED_PORT                                GPIOD    
#define GPIO_LED1                                    GPIO_Pin_2    
#define GPIO_LED2                                    GPIO_Pin_3    
#define GPIO_LED3                                    GPIO_Pin_4    
#define GPIO_LED4                                    GPIO_Pin_7
#define GPIO_LED_ALL                                 GPIO_LED1 |GPIO_LED2 |GPIO_LED3 |GPIO_LED4 


extern void LEDInit(void);
extern void Led_Turn_on_all(void);
extern void Led_Turn_on_1(void);
extern void Led_Turn_on_2(void);
extern void Led_Turn_on_3(void);
extern void Led_Turn_on_4(void);
extern void Led_Turn_on(u8 led);
extern void Led_Turn_off_all(void);
#endif
