/**
  ******************************************************************************
  * @file    ssd1963_driver.h
  * @brief   Header file of the ssd1963 driver.
  * @author  Liyuepeng(Treblemoon) from ICEC-SAST of HEU
  * @version V6.0
  * @date    5-April-2013
  * @note    This driver use GPIO to simulate the 8080 interface with 8-bit or 16-bit Pixel 
  *          data.
  ******************************************************************************
  */
  
  
  
  
#ifndef __SSD1963_DRIVER_H__
#define __SSD1963_DRIVER_H__

#include "delay.h"
#include "stm32f10x.h"  
#include <math.h>


//16-bit DataPort (565 format)
#define LCD_DATAPORT(DATA)     GPIO_Write(GPIOE, DATA);

/* LCD Control pins */
#define LCD_Pin_WR      GPIO_Pin_13
#define LCD_PORT_WR     GPIOB
#define LCD_CLK_WR      RCC_APB2Periph_GPIOB

#define LCD_Pin_RS      GPIO_Pin_11
#define LCD_PORT_RS     GPIOB
#define LCD_CLK_RS      RCC_APB2Periph_GPIOB

#define LCD_Pin_RD      GPIO_Pin_12
#define LCD_PORT_RD     GPIOB
#define LCD_CLK_RD      RCC_APB2Periph_GPIOB


#define LCD_WR_H  GPIO_SetBits(LCD_PORT_WR, LCD_Pin_WR);
#define LCD_WR_L  GPIO_ResetBits(LCD_PORT_WR, LCD_Pin_WR);
 

#define LCD_RS_H  GPIO_SetBits(LCD_PORT_RS, LCD_Pin_RS);
#define LCD_RS_L  GPIO_ResetBits(LCD_PORT_RS, LCD_Pin_RS);
/** @defgroup 16-bit (565 format) color value.
  * @{
  */

//16-bit (565 format) color value
#define WHITE   0xFFFF
#define BLACK   0x0000	  
#define BLUE    0x001F  
#define RED     0xF800
#define MAGENTA 0xF81F
#define GREEN   0x07E0
#define CYAN    0x7FFF
#define YELLOW  0xFFE0
#define BROWN   0XBC40  
#define GRAY    0X8430  

  	
#define RGB(r,g,b) (u16)( (r/0x08 << 11) | (g/0x08<< 6) | b/0x08 )
  	
  	
  	
  	
#define  HDP  470    //Horizontal Display Period
#define  HT   480   //Horizontal Total
#define  HPS  51     //LLINE Pulse Start Position
#define  LPS  3      //	Horizontal Display Period Start Position
#define  HPW  8      //	LLINE Pulse Width


#define  VDP  864	 //Vertical Display Period
#define  VT   854    //Vertical Total
#define  VPS  24	 //	LFRAME Pulse Start Position
#define  FPS  23	 //Vertical Display Period Start Positio
#define  VPW  3 	 // LFRAME Pulse Width

/** @defgroup Exported functions.
  * @{
  */

extern void LCD_SSD1963_clear(u32 color);
extern void LCD_SSD1963_init(void);
extern void LCD_SSD1963_drawpoint(u32 xpos, u32 ypos, u32 color);
extern s8 LCD_SSD1963_putchar(u32 xpos,u32 ypos,u8 asc2num,u32 pencolor,u32 backcolor);
extern s8 LCD_SSD1963_putstring(u32 xpos,u32 ypos,const char* p,u32 pencolor,u32 backcolor);
extern void LCD_SSD1963_drawline(u32 xsta,u32 ysta,u32 xend,u32 yend,u32 color);
extern void LCD_SSD1963_drawrectangle(u32 xsta, u32 ysta, u32 xend, u32 yend,u8 if_fill, u32 color);
extern void LCD_SSD1963_drawcircle(u32 x0, u32 y0, u32 r,u8 if_fill, u32 color);
#endif


