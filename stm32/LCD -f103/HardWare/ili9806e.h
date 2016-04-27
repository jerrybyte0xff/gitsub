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








#define LCD_SETCS  GPIO_SetBits(LCD_PORT_CS, LCD_Pin_CS);
#define LCD_CLRCS  GPIO_ResetBits(LCD_PORT_CS, LCD_Pin_CS);
 

#define LCD_SETSCL  GPIO_SetBits(LCD_PORT_SCL, LCD_Pin_SCL);
#define LCD_CLRSCL  GPIO_ResetBits(LCD_PORT_SCL, LCD_Pin_SCL);

#define LCD_SETSDA  GPIO_SetBits(LCD_PORT_SDA, LCD_Pin_SDA);
#define LCD_CLRSDA  GPIO_ResetBits(LCD_PORT_SDA, LCD_Pin_SDA);

#define LCD_SETRES  GPIO_SetBits(LCD_PORT_RES, LCD_Pin_RES);
#define LCD_CLRRES  GPIO_ResetBits(LCD_PORT_RES, LCD_Pin_RES);


#define LCD_READDATABIT 	GPIO_ReadOutputDataBit(LCD_PORT_SDA, LCD_Pin_SDA)


////////////////////////////////////////////////////////////////////////////////////////
/* LCD Control pins */

#define LCD_Pin_CS      GPIO_Pin_1
#define LCD_PORT_CS     GPIOD
#define LCD_CLK_CS      RCC_APB2Periph_GPIOD

#define LCD_Pin_RES      GPIO_Pin_2
#define LCD_PORT_RES     GPIOD
#define LCD_CLK_RES      RCC_APB2Periph_GPIOD


#define LCD_Pin_SDA      GPIO_Pin_7
#define LCD_PORT_SDA     GPIOB
#define LCD_CLK_SDA      RCC_APB2Periph_GPIOB

#define LCD_Pin_SCL      GPIO_Pin_6
#define LCD_PORT_SCL     GPIOB
#define LCD_CLK_SCL      RCC_APB2Periph_GPIOB




void LCD_DB_AS_OutPut(void);
void LCD_Pins_Config(void);
void LCD_WriteCtrlCommand(u8 LCD_CommandValue);
void LCD_WriteCtrlData(u8 LCD_CtrlData);
void LCD_WriteReg(u8 LCD_Reg,u8 LCD_RegValue);
u16 LCD_ReadReg(u8 LCD_CommandValue);


extern void ILI9806E_Initializtion(void);

#endif



