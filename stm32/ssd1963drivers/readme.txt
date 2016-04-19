/**
  ******************************************************************************
  * @name    ssd1963 drivers
  * @author  Liyuepeng(Treblemoon) from ICEC-SAST of HEU
  * @version V6.0
  * @date    5-April-2013
  ****************************************************************************** 
  */
These are ssd1963 drivers from Liyuepeng(Treblemoon).
 
@hardware description
All hardware-related code is in the hardware layer files(ssd1963_hal_stm32.c/h).
The CONF pin is connected to VDDIO,so the MCU
interface is configure in 8080 mode.
Because we only write and no chip select,
we connected RS to VDDIO and CS to GND.
We also connected REST to VDDIO.
Attention:
  1,You can select 8-bit of 16-bit Pixel data 
    by if or not define PIXELDATA_8BIT in ssd1963_hal_stm32.h:
      8-bit :A0-A7 of ssd1963 should be connected to PIN_0-PIN_7 of MCU.
      16-bit:A0-15 of ssd1963 should be connected to PIN_0-PIN_15 of MCU.
  2,You can select if configure mcu in lcd_init() in ssd1963_driver.c
    by if of not define CONFIGMCUFROMDRIVER in ssd1963_hal_stm32.h. 
    The configuration  function is in ssd1963_hal_stm32.c

@files description	
ssd1963_driver.c is function abstraction layer file.
ssd1963_driver.h header file of the driver.
ascii1608.h contain the 16*8 pixels ASCII table.
ssd1963_hal_stm32.c and ssd1963_hal_stm32.h are the hardware layer files

Note:
When you use this driver,you should include the ssd1963_driver.h in your code and add ssd1963_hal_stm32.c and ssd1963_driver.c in your project.
And when you transplant the driver to other platform just change the hardware layer files.