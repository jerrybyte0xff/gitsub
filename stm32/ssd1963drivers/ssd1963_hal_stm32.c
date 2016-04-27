/**  ******************************************************************************  * @file    ssd1963_hal_stm32.c  * @brief   Hardware layer of the ssd1963 driver.  * @author  Liyuepeng(Treblemoon) from ICEC-SAST of HEU  * @version V6.0  * @date    5-April-2013  * @note    This hardware layer file is based on STM32F10x   *          Standard Peripherals Library V3.5.0.  ******************************************************************************   * @hardware description  *   	The CONF pin is connected to VDDIO,so the MCU  *		interface is configure in 8080 mode.  *		Because we only write and no chip select,  *		we connected RS to VDDIO and CS to GND.  *		We also connected REST to VDDIO.  *     Attention:
  *     1,You can select 8-bit of 16-bit Pixel data 
  *        by if or not define PIXELDATA_8BIT in ssd1963_hal_stm32.h:
  *        8-bit :A0-A7 of ssd1963 should be connected to PIN_0-PIN_7 of MCU.
  *		     16-bit:A0-15 of ssd1963 should be connected to PIN_0-PIN_15 of MCU.
  *     2,You can select if configure mcu in lcd_init() in ssd1963_driver.c
  *        by if of not define CONFIGMCUFROMDRIVER in ssd1963_hal_stm32.h. 
  *        The configuration  function is in ssd1963_hal_stm32.c
  ****************************************************************************** 
  */#include "ssd1963_hal_stm32.h" 


/**
  * @brief  Configures the clocks and GPIO ports for driving ssd1963.
  * @param  None
  * @retval None
  */	
void rcc_and_gpio_configuration(void)
{

	GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD, ENABLE);

  
  GPIO_InitStructure.GPIO_Pin = 0x00ff;//P0~P7
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14|GPIO_Pin_15;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

}/**  * @brief  Millisecond delay  * @param  nms:The ms to delay for.  * @retval None.  */void delay_ms(unsigned int nms){	unsigned int i,j;	for(i = 0;i<nms;++i)		for(j=0;j<1800;j++);}


