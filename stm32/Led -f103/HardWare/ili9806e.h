 /******************************************************************************
  * @file    ili9806e.h
  * @author  jerry 
  * @version V1.0
  * @date    2015/08/24
  * @brief   LCD Driver program
  ******************************************************************************/

#ifndef __ILI9806E_H__
#define	__ILI9806E_H__

#include "stm32f10x.h"
#include "delay.h"
#include "stm32f10x_gpio.h"



#define  Lcd_Height           854
#define  Lcd_Width            480
#define  TVP                  2
#define  TVB                  2
#define  TVF                  4
#define  THP                  2
#define  THB                  8
#define  THF                  6

#define RGB565_MASK_RED 0xF800
#define RGB565_MASK_GREEN 0x07E0
#define RGB565_MASK_BLUE 0x001F

#define RGB(r,g,b) (unsigned int)( (r/0x08 << 11) | (g/0x08<< 6) | b/0x08 )




#define LCD_SETCS  GPIO_SetBits(LCD_PORT_CS, LCD_Pin_CS);
#define LCD_CLRCS  GPIO_ResetBits(LCD_PORT_CS, LCD_Pin_CS);
 

#define LCD_SETSCL  GPIO_SetBits(LCD_PORT_SCL, LCD_Pin_SCL);
#define LCD_CLRSCL  GPIO_ResetBits(LCD_PORT_SCL, LCD_Pin_SCL);

#define LCD_SETSDA  GPIO_SetBits(LCD_PORT_SDA, LCD_Pin_SDA);
#define LCD_CLRSDA  GPIO_ResetBits(LCD_PORT_SDA, LCD_Pin_SDA);

#define LCD_SETRES  GPIO_SetBits(LCD_PORT_RES, LCD_Pin_RES);
#define LCD_CLRRES  GPIO_ResetBits(LCD_PORT_RES, LCD_Pin_RES);

#define LCD_SETDE  GPIO_SetBits(LCD_PORT_DE, LCD_Pin_DE);
#define LCD_CLRDE  GPIO_ResetBits(LCD_PORT_DE, LCD_Pin_DE);

#define LCD_SETHSYNC  GPIO_SetBits(LCD_PORT_HSYNC, LCD_Pin_HSYNC);
#define LCD_CLRHSYNC  GPIO_ResetBits(LCD_PORT_HSYNC, LCD_Pin_HSYNC);

#define LCD_SETVSYNC  GPIO_SetBits(LCD_PORT_VSYNC, LCD_Pin_VSYNC);
#define LCD_CLRVSYNC  GPIO_ResetBits(LCD_PORT_VSYNC, LCD_Pin_VSYNC);

#define LCD_SETDCLK  GPIO_SetBits(LCD_PORT_DCLK, LCD_Pin_DCLK);
#define LCD_CLRDCLK  GPIO_ResetBits(LCD_PORT_DCLK, LCD_Pin_DCLK);

#define LCD_READDATABIT 	GPIO_ReadOutputDataBit(LCD_PORT_SDA, LCD_Pin_SDA)

#define LCD_Write(LCD_DATA)  GPIO_Write(GPIOE, LCD_DATA)
#define LCD_Read()  GPIO_ReadInputData(GPIOE)

////////////////////////////////////////////////////////////////////////////////////////
/* LCD Control pins */

#define LCD_Pin_CS      GPIO_Pin_1
#define LCD_PORT_CS     GPIOD
#define LCD_CLK_CS      RCC_APB2Periph_GPIOD

#define LCD_Pin_RES      GPIO_Pin_2
#define LCD_PORT_RES     GPIOD
#define LCD_CLK_RES      RCC_APB2Periph_GPIOD

#define LCD_Pin_DE       GPIO_Pin_3
#define LCD_PORT_DE      GPIOD
#define LCD_CLK_DE       RCC_APB2Periph_GPIOD

#define LCD_Pin_HSYNC    GPIO_Pin_4
#define LCD_PORT_HSYNC   GPIOD
#define LCD_CLK_HSYNC    RCC_APB2Periph_GPIOD

#define LCD_Pin_VSYNC    GPIO_Pin_5
#define LCD_PORT_VSYNC   GPIOD
#define LCD_CLK_VSYNC    RCC_APB2Periph_GPIOD

#define LCD_Pin_DCLK     GPIO_Pin_6
#define LCD_PORT_DCLK    GPIOD
#define LCD_CLK_DCLK     RCC_APB2Periph_GPIOD


#define LCD_Pin_SDA      GPIO_Pin_7
#define LCD_PORT_SDA     GPIOB
#define LCD_CLK_SDA      RCC_APB2Periph_GPIOB

#define LCD_Pin_SCL      GPIO_Pin_6
#define LCD_PORT_SCL     GPIOB
#define LCD_CLK_SCL      RCC_APB2Periph_GPIOB



/************************** Color Define *********************************/
#define   Red_262k              0x3F000
#define   Green_262k            0xFC0
#define   Blue_262k             0x3F
#define   White_262k            0x3FFFF
#define   Black_262k            0x0

#define   Black_65k		       0x0000       /* 0,   0,   0 */
#define   Navy_65k		       0x000F       /* 0,   0, 128 */
#define   Dgreen_65k	       0x03E0		/* 0, 128,   0 */
#define   Dcyan_65k		       0x03EF		/* 0, 128, 128 */
#define   Maroon_65k	       0x7800		/* 128,   0,   0 */
#define   Purple_65k	       0x780F		/* 128,   0, 128 */
#define   Olive_65k		       0x7BE0 	    /* 128, 128,   0 */
#define   Lgray_65k		       0xC618	    /* 192, 192, 192 */
#define   Dgray_65k		       0x7BEF		/* 128, 128, 128 */
#define   Blue_65k		       0x001F		/*  0,   0, 255 */
#define   Green_65k		       0x07E0		/*  0, 255,   0 */
#define   Cyan_65k	           0x07FF 		/*  0, 255, 255 */
#define   Red_65k		       0xF800		/*  255,   0,   0 */
#define   Magenta_65k	       0xF81F		/*  255,   0, 255 */
#define   Yellow_65k	       0xFFE0		/*  255, 255, 0   */
#define   White_65k		       0xFFFF       /*  255, 255, 255 */

/***********************************************************************/


void LCD_DB_AS_OutPut(void);
void LCD_Pins_Config(void);
void LCD_WriteCtrlCommand(u8 LCD_CommandValue);
void LCD_WriteCtrlData(u8 LCD_CtrlData);
void LCD_WriteReg(u8 LCD_Reg,u8 LCD_RegValue);
u16 LCD_ReadReg(u8 LCD_CommandValue);
void Lcd_ColorSet(u16 Color);


extern void ILI9806E_Initializtion(void);
extern void Lcd_Fill_Disp(u16 Color);

#endif



