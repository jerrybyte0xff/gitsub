/*****************************************************************************
 * @file    ssd1963_driver.c
 * @brief   Function abstraction layer file of the ssd1963 driver.
 * @author  Jerry
 * @date    2015.09.07
*****************************************************************************/
/*****************************************************************************
 *        @(#)Copyright (C) Kywoo Beijing .
*****************************************************************************/



/*****************************************************************************
 *   Include
*****************************************************************************/
#include "ssd1963_driver.h"
#include "ascii1608.h"
#include "usart.h"	

#define LCD_24BIT_MODE


/*===============================================================================
 *	INTERNAL FUNCTION 
 *===============================================================================*/
static void LCD_SSD1963_Pins_Config(void);
static void LCD_SSD1963_windowmax(u32 xsta,u32 ysta,u32 xend,u32 yend);
/*===============================================================================
 *	PROCESS FUNCTION
 *===============================================================================*/
 
 
 /*************************************************************************//**
 * @brief		SSD1963 Write Data Process
 *
 * @param[in]	u16 color
 *
 * @retval		void
 *
 * @outline		1.MCU Write 16 bit Data(Color) To SSD1963 .<BR>
 *
 * @date        2015.09.06 New Creation
 * @version     2015.09.06 Jerry New Creation
 *
 ****************************************************************************/
void LCD_SSD1963_write_data(u16 color)
{  
		//while (LCD_TEARREAD);
		LCD_RD_H
		LCD_RS_H
		LCD_CS_L
		LCD_DATAPORT(color)	
		LCD_WR_L	
		LCD_WR_H
	  	LCD_CS_H
}

/*************************************************************************//**
 * @brief		SSD1963 Write Parameter Process
 *
 * @param[in]	u16 parameter
 *
 * @retval		void
 *
 * @outline		1.MCU Write 8 bit Parameter To SSD1963 .<BR>
 *
 * @date        2015.09.06 New Creation
 * @version     2015.09.06 Jerry New Creation
 *
 ****************************************************************************/
void LCD_SSD1963_write_parameter(u16 parameter)   
{  
		LCD_RD_H
		LCD_RS_H
		LCD_CS_L
	    LCD_DATAPORT(parameter & 0xff)	//
		LCD_WR_L
		//LCD_DATAPORT(parameter&0xff)	 
		LCD_WR_H
		LCD_CS_H
}	

/*************************************************************************//**
 * @brief		SSD1963 Write Data Process
 *
 * @param[in]	u16 parameter
 *
 * @retval		void
 *
* @outline		1.MCU Write 8 bit parameter To SSD1963 .<BR>
 *
 * @date        2015.09.06 New Creation
 * @version     2015.09.06 Jerry New Creation
 *
 ****************************************************************************/
 void LCD_SSD1963_write_command(u16 command)	 
{	  
		LCD_RD_H
		LCD_RS_L
		LCD_CS_L
		LCD_DATAPORT(command & 0xff)
		LCD_WR_L
		//LCD_DATAPORT(command&0xff)
		LCD_WR_H
		LCD_CS_H
}

/*************************************************************************//**
 * @brief		SSD1963 Read Parameter Process
 *
 * @param[in]	u32 *p_parameter
 *
 * @retval		void
 *
 * @outline		1.MCU Read 16 bit Parameter From SSD1963 .<BR>
 *
 * @date        2015.09.06 New Creation
 * @version     2015.09.06 Jerry New Creation
 *
 ****************************************************************************/
 void LCD_SSD1963_read_parameter(u32 *p_parameter)
{  
	
		LCD_RS_H
		LCD_WR_H
		LCD_RD_L
		LCD_CS_L
		*p_parameter = LCD_DATAREAD	
		LCD_RD_H
		LCD_CS_H
}	
	


/*************************************************************************//**
 * @brief		Clear the LCD With The  Single Color Process
 *
 * @param[in]	u16 color:Color value defined in ssd1963_driver.h.r
 *
 * @retval		void
 *
 * @outline		1.Set The X Position .<BR>
 *              2.Set The Y Position .<BR>
 *              3.Draw Colors .<BR>
 *
 * @date        2015.09.06 New Creation
 * @version     2015.09.06 Jerry New Creation
 *
 ****************************************************************************/
void LCD_SSD1963_clear(u32 color)
{
 	/*-------------------------------*
	 * Variable Declaration
	 *-------------------------------*/
	u16 l = (VDP+1),w;
	
	/*-------------------------------*
	 * Process
	 *-------------------------------*/
	/*  Set The X Position   */
	LCD_SSD1963_write_command(0x002A);	
	LCD_SSD1963_write_parameter(0);	    
	LCD_SSD1963_write_parameter(0);
	LCD_SSD1963_write_parameter(HDP / 256);	    
	LCD_SSD1963_write_parameter(HDP % 256);

	/*  Set The Y Position  */
	LCD_SSD1963_write_command(0x002B);	
	LCD_SSD1963_write_parameter(0);	    
	LCD_SSD1963_write_parameter(0);
	LCD_SSD1963_write_parameter(VDP / 256);	    
	LCD_SSD1963_write_parameter(VDP % 256);
	
	

	// LCD_SSD1963_write_command(0x002C);	
	LCD_SSD1963_write_command(0x002C);	
	printf("before draw\n");
	

	/* Draw Colors */
	while(l--)		 
	{
		for(w = 0; w < (HDP+1); w++) 
		{ 	

			LCD_SSD1963_write_data(color);
		}
		
		
	}
	printf(" draw done\n");
	
}


/*************************************************************************//**
 * @brief		Config SSD1963 Data Pins As Output
 *
 * @param[in]	void
 *
 * @retval		void
 *
 * @outline		1.Config SSD1963 DataPins As Output .<BR>
 *
 * @date        2015.09.06 New Creation
 * @version     2015.09.06 Jerry New Creation
 *
 ****************************************************************************/
void LCD_SSD1963_DataPins_Config_Out(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/* Data */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

}

/*************************************************************************//**
 * @brief		Config SSD1963 Data Pins As Intput
 *
 * @param[in]	void
 *
 * @retval		void
 *
 * @outline		1.Config SSD1963 DataPins As Output .<BR>
 *
 * @date        2015.09.06 New Creation
 * @version     2015.09.06 Jerry New Creation
 *
 ****************************************************************************/
void LCD_SSD1963_DataPins_Config_In(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/* Data */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

}

 /*************************************************************************//**
 * @brief		Init the LCD
 *
 * @param[in]	void
 *
 * @retval		void
 *
 * @outline		1.Initialize the SSD1963 .<BR>
 *
 * @date        2015.09.06 New Creation
 * @version     2015.09.06 Jerry New Creation
 *
 ****************************************************************************/
void LCD_SSD1963_init(void)
{
	/*-------------------------------*
	 * Variable Declaration
	 *-------------------------------*/
	u32 read_temp;
	
	/*-------------------------------*
	 * Initialize
	 *-------------------------------*/
	read_temp = 0;
	
	
	LCD_SSD1963_Pins_Config();
	delay_ms(50);
	//LCD_CS_L
	/*-------------------------------*
	 * Process
	 *-------------------------------*/
	
#if 0 
	 /* Software Reset */
	LCD_SSD1963_write_command(0x0001);  
	delay_ms(100);
	printf("Software Reset \n");
	
	LCD_SSD1963_write_command(0x002b);	
	LCD_SSD1963_write_parameter(0);
#endif
	
	/* Set PLL MN */
	LCD_SSD1963_write_command(0x00E2);		//PLL = In *N / M
	LCD_SSD1963_write_parameter(0x0023);    //N = 36, M = 3
	LCD_SSD1963_write_parameter(0x0002);							 
	LCD_SSD1963_write_parameter(0x0004);
	
	printf("Set PLL MN Success \n");

    /* Set PLL */
	LCD_SSD1963_write_command(0x00E0);  
	LCD_SSD1963_write_parameter(0x0001);  /* PLL enable  */
	delay_ms(100);	      
	LCD_SSD1963_write_command(0x00E0);	  /* Lock PLL   */
	LCD_SSD1963_write_parameter(0x0003);
	delay_ms(10);
	LCD_SSD1963_write_command(0x0001);

	delay_ms(100);

	/* Set LSHIFT Frequency */
#if 0
	LCD_SSD1963_write_command(0x00E6);	  
	LCD_SSD1963_write_parameter(0x0004);
	LCD_SSD1963_write_parameter(0x0000);
	LCD_SSD1963_write_parameter(0x0000);
	printf("Set LSHIFT Frequency \n");

#endif
#if 1
	LCD_SSD1963_write_command(0x00E6);	  
	LCD_SSD1963_write_parameter(0x0002);
	LCD_SSD1963_write_parameter(0x0047);
	LCD_SSD1963_write_parameter(0x00BE);
	printf("Set LSHIFT Frequency \n");
#endif	
	
 	/* Set LCD Mode */
	LCD_SSD1963_write_command(0x00B0);	      	  
//#ifdef LCD_24BIT_MODE
#if 1
	LCD_SSD1963_write_parameter(0x0024);
//#else
	//LCD_SSD1963_write_parameter(0x0004);
#endif
	LCD_SSD1963_write_parameter(0x0000);
	LCD_SSD1963_write_parameter(HDP / 256);  /*Set the horizontal panel size*/
	LCD_SSD1963_write_parameter(HDP % 256);
	LCD_SSD1963_write_parameter(VDP / 256);  /*Set the horizontal panel size*/
	LCD_SSD1963_write_parameter(VDP % 256);
	LCD_SSD1963_write_parameter(0x0000);
	
	/* Get LCD Mode */
	LCD_SSD1963_write_command(0x00B1);
	LCD_SSD1963_DataPins_Config_In();
	LCD_SSD1963_read_parameter(&read_temp);
	printf("Get LCD Mode[%d]\n",read_temp);
	LCD_SSD1963_read_parameter(&read_temp);
	printf("Get LCD Mode[%d]\n",read_temp);
	LCD_SSD1963_read_parameter(&read_temp);
	printf("Get LCD Mode[%d]\n",read_temp);
	LCD_SSD1963_read_parameter(&read_temp);
	printf("Get LCD Mode[%d]\n",read_temp);
	LCD_SSD1963_read_parameter(&read_temp);
	printf("Get LCD Mode[%d]\n",read_temp);
	LCD_SSD1963_read_parameter(&read_temp);
	printf("Get LCD Mode[%d]\n",read_temp);
	LCD_SSD1963_read_parameter(&read_temp);
	printf("Get LCD Mode[%d]\n",read_temp);
	LCD_SSD1963_DataPins_Config_Out();
	
	

    /* Set Horizontal Period */
	LCD_SSD1963_write_command(0x00B4);	         
	LCD_SSD1963_write_parameter(((HT>>8)&0X00FF));  //Set HT
	LCD_SSD1963_write_parameter((HT&0X00FF));
	LCD_SSD1963_write_parameter((HPS>>8)&0X00FF);  //Set HPS
	LCD_SSD1963_write_parameter((HPS&0X00FF));
	LCD_SSD1963_write_parameter( HPW);	            //Set HPW
	LCD_SSD1963_write_parameter(((LPS>>8)&0X00FF));  //SetLPS
	LCD_SSD1963_write_parameter((LPS&0X00FF));
	LCD_SSD1963_write_parameter(0x0000);

 	/*Set Vertical Period */
	LCD_SSD1963_write_command(0x00B6);	           //VSYNC
	LCD_SSD1963_write_parameter(((VT>>8)&0X00FF));   //Set VT
	LCD_SSD1963_write_parameter((VT&0X00FF));
	LCD_SSD1963_write_parameter(((VPS>>8)&0X00FF));  //Set VPS
	LCD_SSD1963_write_parameter((VPS&0X00FF));
	LCD_SSD1963_write_parameter((VPW));		     //Set VPW
	LCD_SSD1963_write_parameter(((FPS>>8)&0X00FF));  //Set FPS
	LCD_SSD1963_write_parameter((FPS&0X00FF));

 	
		/*  X  */
	LCD_SSD1963_write_command(0x002A);	
	LCD_SSD1963_write_parameter(0);	    
	LCD_SSD1963_write_parameter(0);
	LCD_SSD1963_write_parameter(HDP>>8);	    
	LCD_SSD1963_write_parameter(HDP&0x00ff);

	

	/*  Y  */
	LCD_SSD1963_write_command(0x002B);	
	LCD_SSD1963_write_parameter(0);	    
	LCD_SSD1963_write_parameter(0);
	LCD_SSD1963_write_parameter(VDP>>8);	     
	LCD_SSD1963_write_parameter(VDP&0x00ff);
	
	
	/* set address_mode */
	LCD_SSD1963_write_command(0x36);
    LCD_SSD1963_write_parameter(0x00);     
	delay_ms(100);
	
	/* Pixel Data Interface 565 */
	LCD_SSD1963_write_command(0x000C);    

	//LCD_SSD1963_write_parameter(0x0060);
	LCD_SSD1963_write_parameter(0x0050);
	
	
	/* Pixel Data Interface 565 */
	LCD_SSD1963_write_command(0x00F0);    

	LCD_SSD1963_write_parameter(0x0003);
	
	
	/* Pixel Data Interface 565 */
	LCD_SSD1963_write_command(0x003A);    

	LCD_SSD1963_write_parameter(0x0050);

	
	/* set_tear_on */
	LCD_SSD1963_write_command(0x0035); 
	LCD_SSD1963_write_parameter(0x0001);
	
	/* enter_normal_mode The whole display area is used for image display. */
	//LCD_SSD1963_write_command(13);
	
	/* Set Display On */
	LCD_SSD1963_write_command(0x0029);        //display on

	delay_ms(100);
	
	//LCD_SSD1963_clear(WHITE);

}


/*************************************************************************//**
 * @brief		Draw A Point In The LCD
 *
 * @param[in]	u32 color:Color value defined in ssd1963_driver.h.
 *				u32 xpos :can be 0 to HDP .
 *				u32 ypos :can be 0 to VDP .
 *
 * @retval		void
 *
 * @outline		1.Draw A Point In The LCD .<BR>
 *
 * @date        2015.09.06 New Creation
 * @version     2015.09.06 Jerry New Creation
 *
 ****************************************************************************/
void LCD_SSD1963_drawpoint(u32 xpos, u32 ypos, u32 color)
{
 	/* Set the Cursor */
	LCD_SSD1963_write_command(0x2A);	
	LCD_SSD1963_write_parameter(xpos / 256);	    
	LCD_SSD1963_write_parameter(xpos % 256);
	LCD_SSD1963_write_parameter(xpos / 256);	    
	LCD_SSD1963_write_parameter(xpos % 256);
	
	LCD_SSD1963_write_command(0x2b);	
	LCD_SSD1963_write_parameter(ypos / 256);	    
	LCD_SSD1963_write_parameter(ypos % 256);
	LCD_SSD1963_write_parameter(ypos / 256);	    
	LCD_SSD1963_write_parameter(ypos % 256);

	/* Write Memory Start */
	LCD_SSD1963_write_command(0x002C);       
	LCD_SSD1963_write_data(color); 
}



/*************************************************************************//**
 * @brief		Get The Point In The LCD
 *
 * @param[in]	u32* color:Color value defined in ssd1963_driver.h.
 *				u32 xpos :can be 0 to HDP .
 *				u32 ypos :can be 0 to VDP .
 *
 * @retval		void
 *
 * @outline		1.Get A Point In The LCD .<BR>
 *
 * @date        2015.09.06 New Creation
 * @version     2015.09.06 Jerry New Creation
 *
 ****************************************************************************/
void LCD_SSD1963_getpoint(u32 xpos, u32 ypos, u32* color)
{
  	/* Set the Cursor */
	LCD_SSD1963_write_command(0x2A);	
	LCD_SSD1963_write_parameter(xpos / 256);	    
	LCD_SSD1963_write_parameter(xpos);
	LCD_SSD1963_write_parameter(xpos % 256);	    
	LCD_SSD1963_write_parameter(xpos);
	
	LCD_SSD1963_write_command(0x2b);	
	LCD_SSD1963_write_parameter(ypos / 256);	    
	LCD_SSD1963_write_parameter(ypos);
	LCD_SSD1963_write_parameter(ypos % 256);	    
	LCD_SSD1963_write_parameter(ypos);

	/* Write Memory Start */
	LCD_SSD1963_write_command(0x002E); 
	LCD_SSD1963_DataPins_Config_In();
	LCD_SSD1963_read_parameter(color); 
	LCD_SSD1963_DataPins_Config_Out();
}
   

 /*************************************************************************//**
 * @brief		Put a 16*8 Character
 *
 * @param[in]	u32* color:Color value defined in ssd1963_driver.h.
 *				u32 xpos :can be 0 to HDP .
 *				u32 ypos :can be 0 to VDP .
 *				u8 asc2num :The Character Value .
 *				u32 backcolor :Color value defined in ssd1963_driver.h.
 *
 * @retval		0
 * @retval		-1
 *
 * @outline		1.Get A Point In The LCD .<BR>
 *
 * @date        2015.09.06 New Creation
 * @version     2015.09.06 Jerry New Creation
 *
 ****************************************************************************/
s8 LCD_SSD1963_putchar(u32 xpos,u32 ypos,u8 asc2num,u32 pencolor,u32 backcolor)
{       
	/*-------------------------------*
	 * Variable Declaration
	 *-------------------------------*/
    u8 temp;
    u8 pos,t;
	
	/*-------------------------------*
	 * Initialize
	 *-------------------------------*/
	temp = 0;
	pos = 0;
	t = 0;
	/*-------------------------------*
	 * Process
	 *-------------------------------*/
    if(xpos>(HDP-7)||ypos>(VDP-15)) 
	{
		return -1;
	}

		asc2num=asc2num-' ';                        
	
	for(pos=0;pos<16;pos++)
	{
		 temp=LCD_ascii_1608_table[asc2num][pos];		
		for(t=0;t<8;t++)
	    {                 
	        if(temp&0x01)			        
			{
				LCD_SSD1963_drawpoint(xpos+t,ypos+pos, pencolor);  
			}
			else 
				LCD_SSD1963_drawpoint(xpos+t,ypos+pos, backcolor);	    
	       temp>>=1; 
	    }
	}	
		return 0;
} 



/*************************************************************************//**
 * @brief		Put a string in a row.
 *
 * @param[in]	u32 xpos :can be 0 to HDP .
 *				u32 ypos :can be 0 to VDP .
 *				const char* p :he pointer of the string whitch should end with \0 .
 *				u32 backcolor :Color value defined in ssd1963_driver.h.
 *
 * @retval		0:The string is puted succeeded
 * @retval		-1:xpos of ypos is not expected.
 *
 * @outline		1.Put a string in a row. .<BR>
 *
 * @date        2015.09.06 New Creation
 * @version     2015.09.06 Jerry New Creation
 *
 ****************************************************************************/
s8 LCD_SSD1963_putstring(u32 xpos,u32 ypos,const char* p,u32 pencolor,u32 backcolor)
{         
    while(*p!='\0')
    {       
        if(xpos>(HDP-7)||ypos>(VDP-15)) 
    	{
    		return -1;
    	}
    	
        LCD_SSD1963_putchar(xpos,ypos,*p,pencolor,backcolor);
        xpos+=8;
        p++;
    }  
		return 0;
}

 /*************************************************************************//**
 * @brief		Draw a line.
 *
 * @param[in]	u32 xsta : the start position of X .
 *				u32 ysta : the start position of Y.
 *				u32 xend : the end position of X .
 *				u32 yend : the end position of Y.
 *				u32 color :Color value defined in ssd1963_driver.h.
 *
 * @retval		void
 *
 * @outline		1.Draw a line .<BR>
 *
 * @date        2015.09.06 New Creation
 * @version     2015.09.06 Jerry New Creation
 *
 ****************************************************************************/
void LCD_SSD1963_drawline(u32 xsta,u32 ysta,u32 xend,u32 yend,u32 color)
{
 	
	/*-------------------------------*
	 * Variable Declaration
	 *-------------------------------*/
	 s8 dx,dy,e;
	
	/*-------------------------------*
	 * Initialize
	 *-------------------------------*/
	 dx=xend-xsta; 
	 dy=yend-ysta;
    /*-------------------------------*
	 * Process
	 *-------------------------------*/
	 if(dx>=0)
	 {
		  if(dy >= 0) 
		  {
			   if(dx>=dy) 
			   {
			   		e=dy-dx/2;
			   		while(xsta<=xend)
			   		{
						 LCD_SSD1963_drawpoint(xsta,ysta,color);
						 if(e>0){ysta+=1;e-=dx;} 
						 xsta+=1;
						 e+=dy;
			   		}
			    }
			   else  
			   {
				   	e=dx-dy/2;
				   	while(ysta<=yend)
				   	{
					   	 LCD_SSD1963_drawpoint(xsta,ysta,color);
					   	 if(e>0){xsta+=1;e-=dy;} 
					   	 ysta+=1;
					   	 e+=dx;
			   		}
			   }
		  }
		  else     
		  {
			   dy=-dy;   

			   if(dx>=dy) 
			   {
				    e=dy-dx/2;
				    while(xsta<=xend)
				    {
					     LCD_SSD1963_drawpoint(xsta,ysta,color);
					     if(e>0){ysta-=1;e-=dx;} 
					     xsta+=1;
					     e+=dy;
				    }
			   }
			   else  
			   {
				    e=dx-dy/2;
				    while(ysta>=yend)
				    {
					     LCD_SSD1963_drawpoint(xsta,ysta,color);
					     if(e>0){xsta+=1;e-=dy;} 
					     ysta-=1;
					     e+=dx;
				    }
				}
			} 
	 }
	 else 
	 {
		  dx=-dx; 
		  if(dy >= 0) 
		  {
			   if(dx>=dy) 
			   {
				    e=dy-dx/2;
				    while(xsta>=xend)
				    {
					     LCD_SSD1963_drawpoint(xsta,ysta,color);
					     if(e>0){ysta+=1;e-=dx;} 
					     xsta-=1;
					     e+=dy;
				    }
			   }
			   else  
			   {
			   		e=dx-dy/2;
				    while(ysta<=yend)
				    {
					     LCD_SSD1963_drawpoint(xsta,ysta,color);
					     if(e>0){xsta-=1;e-=dy;} 
					     ysta+=1;
					     e+=dx;
				    }
			    }
		 	}
		  else    
		  {
			   dy=-dy;   

			   if(dx>=dy) 
			   {
				    e=dy-dx/2;
				    while(xsta>=xend)
				    {
					     LCD_SSD1963_drawpoint(xsta,ysta,color);
					     if(e>0){ysta-=1;e-=dx;} 
					     xsta-=1;
					     e+=dy;
				    }
			   }
			   else 
			   {
				    e=dx-dy/2;
				    while(ysta>=yend)
				    {
					     LCD_SSD1963_drawpoint(xsta,ysta,color);
					     if(e>0){xsta-=1;e-=dy;} 
					     ysta-=1;
					     e+=dx;
				    }
			   }
		  } 
	 }
} 



/*************************************************************************//**
 * @brief		 Draw a Rectangle On Lcd.
 *
 * @param[in]	u32 xsta : the start position of
 *				u32 ysta : the start position of
 *				u32 xend : the end position of X
 *				u32 yend : the end position of Y.
 *				u8 if_fill : 1:fill all 
 *                           else: not fill
 *				u32 color : Color value defined in ssd1963_driver.h..
 *
 * @retval		void
 *
 * @outline		1.Draw a Rectangle On Lcd .<BR>
 *
 * @date        2015.09.06 New Creation
 * @version     2015.09.06 Jerry New Creation
 *
 ****************************************************************************/
void LCD_SSD1963_drawrectangle(u32 xsta, u32 ysta, u32 xend, u32 yend,u8 if_fill, u32 color)
{
    u32 n;
	if(if_fill==1)
	{

		LCD_SSD1963_windowmax(xsta, ysta, xend, yend); 
		LCD_SSD1963_write_command(0x002C);      	   	   
		n=(u32)(yend-ysta+1)*(xend-xsta+1);    
		while(n--){LCD_SSD1963_write_data(color);} 
	}
	LCD_SSD1963_drawline(xsta, ysta, xend, ysta, color);
	LCD_SSD1963_drawline(xsta, ysta, xsta, yend, color);
	LCD_SSD1963_drawline(xsta, yend, xend, yend, color);
	LCD_SSD1963_drawline(xend, ysta, xend, yend, color);
} 


/*************************************************************************//**
 * @brief		 Draw a Circle On Lcd.
 *
 * @param[in]	u32 x0 : the origin position of X .
 *				u32 y0 : the origin position of Y.
 *				u32 r  : the radius .
 *				u8 if_fill : 1:fill all 
 *                           else: not fill
 *				u32 color : Color value defined in ssd1963_driver.h..
 *
 * @retval		void
 *
 * @outline		1.Draw a Circle On Lcd .<BR>
 *
 * @date        2015.09.06 New Creation
 * @version     2015.09.06 Jerry New Creation
 *
 ****************************************************************************/
void LCD_SSD1963_drawcircle(u32 x0, u32 y0, u32 r,u8 if_fill, u32 color)
{
	u32 a=0,b=r;
	s32 di=3-(r<<1);
		         
	while(a<=b)
	{
		LCD_SSD1963_drawpoint(x0-b, y0-a, color);
		LCD_SSD1963_drawpoint(x0+b, y0-a, color); 	
		LCD_SSD1963_drawpoint(x0-a, y0+b, color); 
		LCD_SSD1963_drawpoint(x0-a, y0-b, color);    
		LCD_SSD1963_drawpoint(x0+b, y0+a, color);    
		LCD_SSD1963_drawpoint(x0+a, y0-b, color); 
		LCD_SSD1963_drawpoint(x0+a, y0+b, color);  
		LCD_SSD1963_drawpoint(x0-b, y0+a, color); 
		if(if_fill==1)
		{   
			LCD_SSD1963_drawline(x0-b,y0-a,x0,y0,color);	
		    LCD_SSD1963_drawline(x0,y0,x0+b,y0-a,color);	
			LCD_SSD1963_drawline(x0-a,y0+b,x0,y0,color);
		    LCD_SSD1963_drawline(x0-a,y0-b,x0,y0,color);	
		    LCD_SSD1963_drawline(x0+b,y0+a,x0,y0,color);	
		    LCD_SSD1963_drawline(x0+a,y0-b,x0,y0,color);	
		    LCD_SSD1963_drawline(x0+a,y0+b,x0,y0,color);	
			LCD_SSD1963_drawline(x0-b,y0+a,x0,y0,color);
		}
		a++;

		/* Bresenham */     
		if(di<0)
			di +=4*a+6;	  
		else
		{
			di+=10+4*(a-b);   
			b--;
		} 
	}
	
} 



 /*************************************************************************//**
 * @brief		 Draw a Picture On Lcd.
 *
 * @param[in]	u32 StartX : the start position of X .
 *				u32 StartY : the start position of Y.
 *				u32 Xend : the end position of X .
 *				u32 Yend : the end position of Y.
 *				u8 *pic :  the Address  of Picture.
 *
 * @retval		void
 *
 * @outline		1.Draw a Picture On Lcd .<BR>
 *
 * @date        2015.09.06 New Creation
 * @version     2015.09.06 Jerry New Creation
 *
 ****************************************************************************/
void LCD_DrawPicture(u16 StartX,u16 StartY,u16 Xend,u16 Yend,const u8 *pic)

{
	/*-------------------------------*
	 * Variable Declaration
	 *-------------------------------*/
	u16 i=0,j=0;

	const u8 *bitmap = pic;
	
	/*-------------------------------*
	 * Process
	 *-------------------------------*/
	for(j=0; j<Yend-StartY; j++)

	{

		for(i=0; i<Xend-StartX; i++)

		LCD_SSD1963_drawpoint(StartX+i, StartY+j, *bitmap++);
	}


}

/*===============================================================================
 *	INTERNAL FUNCTION 
 *===============================================================================*/
 /*************************************************************************//**
 * @brief		Set a window for fillling in lcd.
 *
 * @param[in]	u32 xsta : the start position of X .
 *				u32 ysta : the start position of Y.
 *				u32 xend : the end position of X .
 *				u32 yend : the end position of Y.
 *
 * @retval		void
 *
 * @outline		1.Set a window for fillling in lcd .<BR>
 *
 * @date        2015.09.06 New Creation
 * @version     2015.09.06 Jerry New Creation
 *
 ****************************************************************************/
static void LCD_SSD1963_windowmax(u32 xsta,u32 ysta,u32 xend,u32 yend) 
{	
	LCD_SSD1963_write_command(0x002A);
	LCD_SSD1963_write_parameter(xsta>>8);
	LCD_SSD1963_write_parameter(xsta);
	LCD_SSD1963_write_parameter(xend>>8);
	LCD_SSD1963_write_parameter(xend);
		
	LCD_SSD1963_write_command(0x002B);	
	LCD_SSD1963_write_parameter(ysta>>8);	
	LCD_SSD1963_write_parameter(ysta);
	LCD_SSD1963_write_parameter(yend>>8);	
	LCD_SSD1963_write_parameter(yend);			
}
 
/*************************************************************************//**
 * @brief		 SSD1963 Pins Config.
 *
 * @param[in]	void
 * @retval		void
 *
 * @outline		1. SSD1963 Pins Config .<BR>
 *
 * @date        2015.09.06 New Creation
 * @version     2015.09.06 Jerry New Creation
 *
 ****************************************************************************/
static void LCD_SSD1963_Pins_Config(void)
{
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOE, ENABLE);

	/* Data */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	/* R Data */
	GPIO_InitStructure.GPIO_Pin = LCD_SSD1963_Pin_CS | 
	                              LCD_SSD1963_Pin_RS |
	                              LCD_SSD1963_Pin_RD | 
	                              LCD_SSD1963_Pin_WR ;
	                              
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	TESTIO_H
	
	printf("LCD_SSD1963_Pins_Config Success\n");

}
