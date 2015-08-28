 /******************************************************************************
  * @file    ILI9806E.c
  * @author  jerry 
  * @version V1.0
  * @date    2015/08/24
  * @brief   LCD Driver program
  ******************************************************************************/
  
 #include "ili9806e.h"


/*******************************************************************************
* Function Name  : LCD_DB_AS_OutPut
* Description    : config MCU LCD_DB pins AS OutPut
* Input          : None
* Output         : None
* Return         : None.
*******************************************************************************/
void LCD_DB_AS_OutPut(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/* G&&B Data */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	/* R Data */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 ||  GPIO_Pin_9 || 
	                              GPIO_Pin_10 || 
	                              GPIO_Pin_11 || 
	                              GPIO_Pin_12 || 
	                              GPIO_Pin_13 || 
	                              GPIO_Pin_14 || 
	                              GPIO_Pin_15;
	                              
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	
} 
/*******************************************************************************
* Function Name  : LCD_Pins_Config
* Description    : Configures LCD Pins
                   Push-Pull mode.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_Pins_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(LCD_CLK_CS | RCC_APB2Periph_GPIOE |
                         LCD_CLK_SDA, ENABLE);

	/* Data Pin Config */
	LCD_DB_AS_OutPut();
	
	/*LCD_Pin_CS & RES */
	GPIO_InitStructure.GPIO_Pin = LCD_Pin_CS | LCD_Pin_RES;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(LCD_PORT_CS, &GPIO_InitStructure);

	/*LCD_Pin_SCL */
	GPIO_InitStructure.GPIO_Pin = LCD_Pin_SCL;
	GPIO_Init(LCD_PORT_SCL, &GPIO_InitStructure);

	/*LCD_Pin_SDA */
	GPIO_InitStructure.GPIO_Pin = LCD_Pin_SDA;
	GPIO_Init(LCD_PORT_SDA, &GPIO_InitStructure);
  
	LCD_SETCS
	LCD_SETSCL
	LCD_SETSDA
}


/*******************************************************************************
* Function Name  : LCD Write Control Command
* Description    : Writes command  to the  LCD 
* Input          : - LCD_CommandValue: The Command Value.
* Output         : None
* Return         : None
* author         : jerry
*******************************************************************************/
void LCD_WriteCtrlCommand(u8 LCD_CommandValue)
{
	/************************************
	Variables Define
	************************************/
	u8 u8_DataCount;
	
	
	u8_DataCount = 0;
	/************************************
	Function 
	************************************/
	/*  Control pins Set Low */
	LCD_CLRSCL
	LCD_CLRSDA
	LCD_SETCS
	LCD_CLRCS
	
	/*  SCL Set High */
	delay_us(1);
	LCD_SETSCL
	delay_us(1);
	
	/*  Write Data */
	for (u8_DataCount = 0; u8_DataCount < 8; u8_DataCount++)
	{
		LCD_CLRSCL
		if (LCD_CommandValue & 0x80)
		{
			LCD_SETSDA
		}
		else
		{
			LCD_CLRSDA
		}
		delay_us(1);
		LCD_SETSCL
		delay_us(1);
		u8_DataCount = u8_DataCount << 1;
	}
	LCD_SETCS


}

/*******************************************************************************
* Function Name  : LCD Write Control Data
* Description    : Writes data  to the  LCD 
* Input          : - LCD_CommandData: The Control Data.
* Output         : None
* Return         : None
* author         : jerry
*******************************************************************************/
void LCD_WriteCtrlData(u8 LCD_CtrlData)
{
	/************************************
	Variables Define
	************************************/
	u8 u8_DataCount;
	
	
	u8_DataCount = 0;
	/************************************
	Function 
	************************************/
	/*  Control pins Set Low */
	LCD_CLRSCL
	LCD_SETSDA
	LCD_SETCS
	LCD_CLRCS
	
	/*  SCL Set High */
	delay_us(1);
	LCD_SETSCL
	delay_us(1);
	
	/*  Write Data */
	for (u8_DataCount = 0; u8_DataCount < 8; u8_DataCount++)
	{
		LCD_CLRSCL
		if (LCD_CtrlData & 0x80)
		{
			LCD_SETSDA
		}
		else
		{
			LCD_CLRSDA
		}
		delay_us(1);
		LCD_SETSCL
		delay_us(1);
		LCD_CtrlData = LCD_CtrlData << 1;
	}
	LCD_SETCS


}

/*******************************************************************************
* Function Name  : LCD_WriteReg
* Description    : Writes to the selected LCD register.
* Input          : - LCD_Reg: address of the selected register.
*                  - LCD_RegValue: value to write to the selected register.
* Output         : None
* Return         : None
* author         : jerry 
*******************************************************************************/
void LCD_WriteReg(u8 LCD_Reg,u8 LCD_RegValue)
{
  	/* Write 16-bit Index, then Write Reg */
	LCD_WriteCtrlCommand(LCD_Reg);
  	/* Write 16-bit Reg */
	LCD_WriteCtrlData(LCD_RegValue);
}

/*******************************************************************************
* Function Name  : LCD_ReadReg
* Description    : Reads the selected LCD Register.
* Input          : None
* Output         : None
* Return         : LCD Register Value.
*******************************************************************************/
u16 LCD_ReadReg(u8 LCD_CommandValue)
{
	/************************************
	Variables Define
	************************************/
	u8 u8_DataCount;
	u8 u8_ReadData;
	u8 u8_ReadTemp;
	
	u8_DataCount = 0;
	u8_ReadData = 0;
	u8_ReadTemp = 0;
	/************************************
	Function 
	************************************/
	/*  Control pins Set Low */
	LCD_CLRSCL
	LCD_SETSDA
	LCD_SETCS
	LCD_CLRCS
	
	/*  SCL Set High */
	delay_us(1);
	LCD_SETSCL
	delay_us(1);
	
	/*  Write Index */
	for (u8_DataCount = 0; u8_DataCount < 8; u8_DataCount++)
	{
		LCD_CLRSCL
		if (LCD_CommandValue & 0x80)
		{
			LCD_SETSDA
		}
		else
		{
			LCD_CLRSDA
		}
		delay_us(1);
		LCD_SETSCL
		delay_us(1);
		u8_DataCount = u8_DataCount << 1;
	}
	
	
	/*  Read Data */
	for (u8_DataCount = 0; u8_DataCount < 8; u8_DataCount++)
	{
		u8_ReadData = (u8_ReadData << 1) & 0xfe;
		LCD_CLRSCL
		u8_ReadTemp = LCD_READDATABIT;
		u8_ReadData = u8_ReadData | u8_ReadTemp;

		delay_us(1);
		LCD_SETSCL
		delay_us(1);
	}
	return u8_ReadData;
}





/*******************************************************************************
* Function Name  : ILI9806E_Initializtion
* Description    : ILI9806E Initializtion.
* Input          : 
* Output         : None
* Return         : None
* author         : jerry 
*******************************************************************************/
void ILI9806E_Initializtion(void)
{
	
	LCD_Pins_Config();
	
 	LCD_SETRES
	delay_ms(10);
	LCD_CLRRES
	delay_ms(50);
	LCD_SETRES;
	delay_ms(200);
	//***************************************************************//LCD SETING
	LCD_WriteCtrlCommand(0xFF);        // Change to Page 1 CMD 
	LCD_WriteCtrlData(0xFF); 
	LCD_WriteCtrlData(0x98); 
	LCD_WriteCtrlData(0x06); 
	LCD_WriteCtrlData(0x04); 
	LCD_WriteCtrlData(0x01); 
	 
	LCD_WriteCtrlCommand(0x08);        //Output    SDA 
	LCD_WriteCtrlData(0x10); 

	LCD_WriteCtrlCommand(0x20);        //set DE/VSYNC mode  
	LCD_WriteCtrlData(0x00); 	

	LCD_WriteCtrlCommand(0x21);        //DE = 1 Active 
	LCD_WriteCtrlData(0x01); 
	 
	LCD_WriteCtrlCommand(0x30);        //Resolution setting 480 X 800 
	LCD_WriteCtrlData(0x02); 
	 
	LCD_WriteCtrlCommand(0x31);        //Inversion setting 2-dot 
	LCD_WriteCtrlData(0x02); 
	 
	LCD_WriteCtrlCommand(0x3A);      
	//LCD_WriteCtrlData(0x50); //16BIT
	LCD_WriteCtrlData(0x60); //18BIT
	//LCD_WriteCtrlData(0x0E); //16bit
	//LCD_WriteCtrlData(0x1E); //186bit
	//LCD_WriteCtrlData(0x2E); //18bit
	//LCD_WriteCtrlData(0x3E); //24bit
	 
	LCD_WriteCtrlCommand(0x60);       
	LCD_WriteCtrlData(0x07); 
	 
	LCD_WriteCtrlCommand(0x61);        
	LCD_WriteCtrlData(0x06); 
	 
	LCD_WriteCtrlCommand(0x62);      
	LCD_WriteCtrlData(0x06); 
	 
	LCD_WriteCtrlCommand(0x63);      
	LCD_WriteCtrlData(0x04); 

	LCD_WriteCtrlCommand(0x40); //BT  AVDD,AVDD 
	LCD_WriteCtrlData(0x18); //10,14
	 
	LCD_WriteCtrlCommand(0x41);//AVDD・AVEE
	LCD_WriteCtrlData(0x33); //avdd +5.4v,avee-5.2v 55
	 
	LCD_WriteCtrlCommand(0x42);  //VGL ,VGH  SET  
	LCD_WriteCtrlData(0x11); 
	 
	LCD_WriteCtrlCommand(0x43);//Default 
	LCD_WriteCtrlData(0x09); 
	 
	LCD_WriteCtrlCommand(0x44);       
	LCD_WriteCtrlData(0x0C); 

	LCD_WriteCtrlCommand(0x46); //增加    
	LCD_WriteCtrlData(0x55);
	 
	LCD_WriteCtrlCommand(0x47); //增加     
	LCD_WriteCtrlData(0x55); 

	LCD_WriteCtrlCommand(0x45);       
	LCD_WriteCtrlData(0x14); 
	 
	LCD_WriteCtrlCommand(0x50);        //VREG1 
	LCD_WriteCtrlData(0x50); 
	 
	LCD_WriteCtrlCommand(0x51);        //VREG2 
	LCD_WriteCtrlData(0x50); 
	 
	LCD_WriteCtrlCommand(0x52);        //Flicker MSB 
	LCD_WriteCtrlData(0x00); 
	 
	LCD_WriteCtrlCommand(0x53);        //Flicker LSB 
	LCD_WriteCtrlData(0x38); //VCOM

	LCD_WriteCtrlCommand(0xA0);        //Positive Gamma 
	LCD_WriteCtrlData(0x00); 
	LCD_WriteCtrlCommand(0xA1);        // 
	LCD_WriteCtrlData(0x09); 
	LCD_WriteCtrlCommand(0xA2);        // 
	LCD_WriteCtrlData(0x0C); 
	LCD_WriteCtrlCommand(0xA3);        // 
	LCD_WriteCtrlData(0x0F); 
	LCD_WriteCtrlCommand(0xA4);        // 
	LCD_WriteCtrlData(0x06); 
	LCD_WriteCtrlCommand(0xA5);        // 
	LCD_WriteCtrlData(0x09); 
	LCD_WriteCtrlCommand(0xA6);        // 
	LCD_WriteCtrlData(0x07); 
	LCD_WriteCtrlCommand(0xA7);        // 
	LCD_WriteCtrlData(0x16); 
	LCD_WriteCtrlCommand(0xA8);        // 
	LCD_WriteCtrlData(0x06); 
	LCD_WriteCtrlCommand(0xA9);        // 
	LCD_WriteCtrlData(0x09); 
	LCD_WriteCtrlCommand(0xAA);        // 
	LCD_WriteCtrlData(0x11); 
	LCD_WriteCtrlCommand(0xAB);        // 
	LCD_WriteCtrlData(0x06); 
	LCD_WriteCtrlCommand(0xAC);        // 
	LCD_WriteCtrlData(0x0E); 
	LCD_WriteCtrlCommand(0xAD);        // 
	LCD_WriteCtrlData(0x19); 
	LCD_WriteCtrlCommand(0xAE);        // 
	LCD_WriteCtrlData(0x0E); 
	LCD_WriteCtrlCommand(0xAF);        // 
	LCD_WriteCtrlData(0x00); 
	 
	LCD_WriteCtrlCommand(0xC0);        //Negative Gamma 
	LCD_WriteCtrlData(0x00); 
	LCD_WriteCtrlCommand(0xC1);        // 
	LCD_WriteCtrlData(0x09); 
	LCD_WriteCtrlCommand(0xC2);        // 
	LCD_WriteCtrlData(0x0C); 
	LCD_WriteCtrlCommand(0xC3);        // 
	LCD_WriteCtrlData(0x0F); 
	LCD_WriteCtrlCommand(0xC4);        // 
	LCD_WriteCtrlData(0x06); 
	LCD_WriteCtrlCommand(0xC5);        // 
	LCD_WriteCtrlData(0x09); 
	LCD_WriteCtrlCommand(0xC6);        // 
	LCD_WriteCtrlData(0x07); 
	LCD_WriteCtrlCommand(0xC7);        // 
	LCD_WriteCtrlData(0x16); 
	LCD_WriteCtrlCommand(0xC8);        // 
	LCD_WriteCtrlData(0x06); 
	LCD_WriteCtrlCommand(0xC9);        // 
	LCD_WriteCtrlData(0x09); 
	LCD_WriteCtrlCommand(0xCA);        // 
	LCD_WriteCtrlData(0x11); 
	LCD_WriteCtrlCommand(0xCB);        // 
	LCD_WriteCtrlData(0x06); 
	LCD_WriteCtrlCommand(0xCC);        // 
	LCD_WriteCtrlData(0x0E); 
	LCD_WriteCtrlCommand(0xCD);        // 
	LCD_WriteCtrlData(0x19); 
	LCD_WriteCtrlCommand(0xCE);        // 
	LCD_WriteCtrlData(0x0E); 
	LCD_WriteCtrlCommand(0xCF);        // 
	LCD_WriteCtrlData(0x00); 
	 

	LCD_WriteCtrlCommand(0xFF);        // Change to Page 6 CMD for GIP timing   
	LCD_WriteCtrlData(0xFF); 
	LCD_WriteCtrlData(0x98); 
	LCD_WriteCtrlData(0x06); 
	LCD_WriteCtrlData(0x04); 
	LCD_WriteCtrlData(0x06); 

	LCD_WriteCtrlCommand(0x00);        // 
	LCD_WriteCtrlData(0xA0); 
	LCD_WriteCtrlCommand(0x01);        // 
	LCD_WriteCtrlData(0x05); 
	LCD_WriteCtrlCommand(0x02);        // 
	LCD_WriteCtrlData(0x00); 
	LCD_WriteCtrlCommand(0x03);        // 
	LCD_WriteCtrlData(0x00); 
	LCD_WriteCtrlCommand(0x04);        // 
	LCD_WriteCtrlData(0x01); 
	LCD_WriteCtrlCommand(0x05);        // 
	LCD_WriteCtrlData(0x01); 
	LCD_WriteCtrlCommand(0x06);        // 
	LCD_WriteCtrlData(0x88); 
	LCD_WriteCtrlCommand(0x07);        // 
	LCD_WriteCtrlData(0x04); 
	LCD_WriteCtrlCommand(0x08);        // 
	LCD_WriteCtrlData(0x01); 
	LCD_WriteCtrlCommand(0x09);        // 
	LCD_WriteCtrlData(0x90); 
	LCD_WriteCtrlCommand(0x0A);        // 
	LCD_WriteCtrlData(0x04); 
	LCD_WriteCtrlCommand(0x0B);        // 
	LCD_WriteCtrlData(0x01); 
	LCD_WriteCtrlCommand(0x0C);        // 
	LCD_WriteCtrlData(0x01); 
	LCD_WriteCtrlCommand(0x0D);        // 
	LCD_WriteCtrlData(0x01); 
	LCD_WriteCtrlCommand(0x0E);        // 
	LCD_WriteCtrlData(0x00); 
	LCD_WriteCtrlCommand(0x0F);        // 
	LCD_WriteCtrlData(0x00);

	LCD_WriteCtrlCommand(0x10);        // 
	LCD_WriteCtrlData(0x55); 
	LCD_WriteCtrlCommand(0x11);        // 
	LCD_WriteCtrlData(0x50); 
	LCD_WriteCtrlCommand(0x12);        // 
	LCD_WriteCtrlData(0x01); 
	LCD_WriteCtrlCommand(0x13);        // 
	LCD_WriteCtrlData(0x85); 
	LCD_WriteCtrlCommand(0x14);        // 
	LCD_WriteCtrlData(0x85); 
	LCD_WriteCtrlCommand(0x15);        // 
	LCD_WriteCtrlData(0xC0); 
	LCD_WriteCtrlCommand(0x16);        // 
	LCD_WriteCtrlData(0x0B); 
	LCD_WriteCtrlCommand(0x17);        // 
	LCD_WriteCtrlData(0x00); 
	LCD_WriteCtrlCommand(0x18);        // 
	LCD_WriteCtrlData(0x00); 
	LCD_WriteCtrlCommand(0x19);        // 
	LCD_WriteCtrlData(0x00); 
	LCD_WriteCtrlCommand(0x1A);        // 
	LCD_WriteCtrlData(0x00); 
	LCD_WriteCtrlCommand(0x1B);        // 
	LCD_WriteCtrlData(0x00); 
	LCD_WriteCtrlCommand(0x1C);        // 
	LCD_WriteCtrlData(0x00); 
	LCD_WriteCtrlCommand(0x1D);        // 
	LCD_WriteCtrlData(0x00); 

	LCD_WriteCtrlCommand(0x20);        // 
	LCD_WriteCtrlData(0x01); 
	LCD_WriteCtrlCommand(0x21);        // 
	LCD_WriteCtrlData(0x23); 
	LCD_WriteCtrlCommand(0x22);        // 
	LCD_WriteCtrlData(0x45); 
	LCD_WriteCtrlCommand(0x23);        // 
	LCD_WriteCtrlData(0x67); 
	LCD_WriteCtrlCommand(0x24);        // 
	LCD_WriteCtrlData(0x01); 
	LCD_WriteCtrlCommand(0x25);        // 
	LCD_WriteCtrlData(0x23); 
	LCD_WriteCtrlCommand(0x26);        // 
	LCD_WriteCtrlData(0x45); 
	LCD_WriteCtrlCommand(0x27);        // 
	LCD_WriteCtrlData(0x67); 

	LCD_WriteCtrlCommand(0x30);        // 
	LCD_WriteCtrlData(0x02); 
	LCD_WriteCtrlCommand(0x31);        // 
	LCD_WriteCtrlData(0x22); 
	LCD_WriteCtrlCommand(0x32);        // 
	LCD_WriteCtrlData(0x11); 
	LCD_WriteCtrlCommand(0x33);        // 
	LCD_WriteCtrlData(0xAA); 
	LCD_WriteCtrlCommand(0x34);        // 
	LCD_WriteCtrlData(0xBB); 
	LCD_WriteCtrlCommand(0x35);        // 
	LCD_WriteCtrlData(0x66); 
	LCD_WriteCtrlCommand(0x36);        // 
	LCD_WriteCtrlData(0x00); 
	LCD_WriteCtrlCommand(0x37);        // 
	LCD_WriteCtrlData(0x22); 
	LCD_WriteCtrlCommand(0x38);        // 
	LCD_WriteCtrlData(0x22); 
	LCD_WriteCtrlCommand(0x39);        // 
	LCD_WriteCtrlData(0x22); 
	LCD_WriteCtrlCommand(0x3A);        // Interface Pixel Format
	LCD_WriteCtrlData(0x22); 
	LCD_WriteCtrlCommand(0x3B);        // 
	LCD_WriteCtrlData(0x22); 
	LCD_WriteCtrlCommand(0x3C);        // 
	LCD_WriteCtrlData(0x22); 
	LCD_WriteCtrlCommand(0x3D);        // 
	LCD_WriteCtrlData(0x22); 
	LCD_WriteCtrlCommand(0x3E);        // 
	LCD_WriteCtrlData(0x22); 
	LCD_WriteCtrlCommand(0x3F);        // 
	LCD_WriteCtrlData(0x22); 
	LCD_WriteCtrlCommand(0x40);        // 
	LCD_WriteCtrlData(0x22); 
	LCD_WriteCtrlCommand(0x52);        // 
	LCD_WriteCtrlData(0x12); 
	LCD_WriteCtrlCommand(0x53);        // 
	LCD_WriteCtrlData(0x12); 

	LCD_WriteCtrlCommand(0xFF);        // Change to Page 7 CMD for GIP timing   
	LCD_WriteCtrlData(0xFF); 
	LCD_WriteCtrlData(0x98); 
	LCD_WriteCtrlData(0x06); 
	LCD_WriteCtrlData(0x04); 
	LCD_WriteCtrlData(0x07); 
	 
	LCD_WriteCtrlCommand(0x17);        // 
	LCD_WriteCtrlData(0x32); 

	LCD_WriteCtrlCommand(0x02);        // 
	LCD_WriteCtrlData(0x17); 

	LCD_WriteCtrlCommand(0x18);        // 
	LCD_WriteCtrlData(0x1D); 

	LCD_WriteCtrlCommand(0xE1);        // 
	LCD_WriteCtrlData(0x79); 

	LCD_WriteCtrlCommand(0xFF);        // Change to Page 7 CMD for Normal command 
	LCD_WriteCtrlData(0xFF); 
	LCD_WriteCtrlData(0x98); 
	LCD_WriteCtrlData(0x06); 
	LCD_WriteCtrlData(0x04); 
	LCD_WriteCtrlData(0x00); 


	LCD_WriteCtrlCommand(0x11);
	delay_ms(120);
	LCD_WriteCtrlCommand(0x29);
	delay_ms(25);
	LCD_WriteCtrlCommand(0x2C);
	

}
