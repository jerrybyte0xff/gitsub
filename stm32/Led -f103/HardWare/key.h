#ifndef __KEY_H
#define __KEY_H

#include "stm32f10x.h"

/* KEY 04  */
#define RCC_KEY1                                    RCC_APB2Periph_GPIOC
#define GPIO_KEY1_PORT                              GPIOC    
#define GPIO_KEY1                                   GPIO_Pin_4

#define RCC_KEY2                                    RCC_APB2Periph_GPIOB
#define GPIO_KEY2_PORT                              GPIOB   
#define GPIO_KEY2                                   GPIO_Pin_10

#define RCC_KEY3                                    RCC_APB2Periph_GPIOC
#define GPIO_KEY3_PORT                              GPIOC    
#define GPIO_KEY3                                   GPIO_Pin_13 

#define RCC_KEY4                                    RCC_APB2Periph_GPIOA
#define GPIO_KEY4_PORT                              GPIOA    
#define GPIO_KEY4                                   GPIO_Pin_0 

#define GPIO_KEY_ANTI_TAMP                          GPIO_KEY3
#define GPIO_KEY_WEAK_UP                            GPIO_KEY4

/* Values magic to the Board keys */
#define  NOKEY  0
#define  KEY1   1
#define  KEY2   2
#define  KEY3   3
#define  KEY4   4



extern void GPIO_KEY_Config(void);
extern u8 ReadKeyDown(void);



#endif
