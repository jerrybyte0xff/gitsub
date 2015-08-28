/**
  ******************************************************************************
  * @file    ssd1963_hal_stm32.h
  * @brief   Hardware layer of the ssd1963 driver.
  * @author  Liyuepeng(Treblemoon) from ICEC-SAST of HEU
  * @version V6.0
  * @date    5-April-2013
  * @note    This hardware layer file is based on STM32F10x 
  *          Standard Peripherals Library V3.5.0.
  ****************************************************************************** 
  * @hardware description
  *   	The CONF pin is connected to VDDIO,so the MCU
  *		interface is configure in 8080 mode.
  *		Because we only write and no chip select,
  *		we connected RS to VDDIO and CS to GND.
  *		We also connected REST to VDDIO.
  *     Attention:
  *     1,You can select 8-bit of 16-bit Pixel data 
  *        by if or not define PIXELDATA_8BIT in ssd1963_hal_stm32.h:
  *        8-bit :A0-A7 of ssd1963 should be connected to PIN_0-PIN_7 of MCU.
  *		     16-bit:A0-15 of ssd1963 should be connected to PIN_0-PIN_15 of MCU.
  *     2,You can select if configure mcu in lcd_init() in ssd1963_driver.c
  *        by if of not define CONFIGMCUFROMDRIVER in ssd1963_hal_stm32.h. 
  *        The configuration  function is in ssd1963_hal_stm32.c
  ****************************************************************************** 
  */
  
 
  
#ifndef __SSD1963_HAL_STM32_H__
#define __SSD1963_HAL_STM32_H__




#endif	


#define LCD_WR_H        GPIOD->BSRR = GPIO_Pin_14;
#define LCD_WR_L        GPIOD->BRR = GPIO_Pin_14; 

#define LCD_RS_H        GPIOD->BSRR = GPIO_Pin_15;
#define LCD_RS_L        GPIOD->BRR = GPIO_Pin_15;  





#define  HDP  799    //Horizontal Display Period
#define  HT   1000   //Horizontal Total
#define  HPS  51     //LLINE Pulse Start Position
#define  LPS  3      //	Horizontal Display Period Start Position
#define  HPW  8      //	LLINE Pulse Width


#define  VDP  479	 //Vertical Display Period
#define  VT   530    //Vertical Total
#define  VPS  24	 //	LFRAME Pulse Start Position
#define  FPS  23	 //Vertical Display Period Start Positio
#define  VPW  3 	 // LFRAME Pulse Width

#define DELAYMS(TIME)   delay_ms(TIME);  

#ifdef CONFIGMCUFROMDRIVER
#define CONFIGMCUFORLCD       rcc_and_gpio_configuration();
void rcc_and_gpio_configuration(void);
#endif

void delay_ms(unsigned int nms);



#endif

