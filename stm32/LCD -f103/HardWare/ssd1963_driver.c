/**
  ******************************************************************************
  * @file    ssd1963_driver.c
  * @brief   Function abstraction layer file of the ssd1963 driver.
  * @author  Liyuepeng(Treblemoon) from ICEC-SAST of HEU
  * @version V6.0
  * @date    5-April-2013
  * @note    This driver use GPIO to simulate the 8080 interface with 8-bit or 16-bit Pixel 
  *          data.
  ******************************************************************************
  */


#include "ssd1963_driver.h"

#include "ascii1608.h"
#include "usart.h"	


static void LCD_SSD1963_write_data(u16 color)
{  
		LCD_RS_H
		LCD_WR_L
		LCD_DATAPORT(color)		
		LCD_WR_H
}	  


static void LCD_SSD1963_write_parameter(u16 parameter)   
{  
	
		LCD_RS_H
		LCD_WR_L
		LCD_DATAPORT(parameter&0xff)	 
		LCD_WR_H
}	
static void LCD_SSD1963_write_command(u16 command)	 
{	  
		LCD_RS_L
		LCD_WR_L
		LCD_DATAPORT(command&0xff)
		LCD_WR_H
  
}

static void LCD_SSD1963_read_parameter(u16 *p_parameter)   
{  
	
		LCD_WR_H
		LCD_RS_L
		*p_parameter = LCD_DATAREAD	 
		LCD_RS_H
}	
	

/**
  * @brief  Clear the LCD.
  * @param  color:Color value defined in ssd1963_driver.h.
  * @retval None.
  */

void LCD_SSD1963_clear(u32 color)
{
  
	 u16 l = VDP+1,w;

	/*  X  */
		LCD_SSD1963_write_command(0X002A);	
		LCD_SSD1963_write_parameter(0);	    
		LCD_SSD1963_write_parameter(0);
		LCD_SSD1963_write_parameter(HDP>>8);	    
		LCD_SSD1963_write_parameter(HDP);

	/*  Y  */
		LCD_SSD1963_write_command(0X002B);	
		LCD_SSD1963_write_parameter(0);	    
		LCD_SSD1963_write_parameter(0);
		LCD_SSD1963_write_parameter(VDP>>8);	    
		LCD_SSD1963_write_parameter(VDP);

	    LCD_SSD1963_write_command(0X002C);	
	printf("before draw\n");
	while(l--)		 
	{
		for(w = 0; w < HDP+1; w++) 
		{ 	

			LCD_SSD1963_write_data(color);

		}
		
	}
	printf(" draw done\n");
	
}


static void LCD_SSD1963_Pins_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/* Data */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	/* R Data */
	GPIO_InitStructure.GPIO_Pin = LCD_SSD1963_Pin_CS || 
	                              LCD_SSD1963_Pin_RS || 
	                              LCD_SSD1963_Pin_RD || 
	                              LCD_SSD1963_Pin_WR ;
	                              
	GPIO_Init(GPIOB, &GPIO_InitStructure);

}


static void LCD_SSD1963_DataPins_Config_Out(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/* Data */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

}

static void LCD_SSD1963_DataPins_Config_In(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/* Data */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

}


/**
  * @brief  Init the LCD.
  * @param  None.
  * @retval None.
  */
void LCD_SSD1963_init(void)
{
	u16 read_temp;

	LCD_SSD1963_Pins_Config();
	delay_ms(50);
	LCD_CS_L
		
	/* Set PLL MN */
	LCD_SSD1963_write_command(0x00E2);		//PLL = In *N / M
	LCD_SSD1963_write_parameter(0x0024);    //N = 36, M = 3
	LCD_SSD1963_write_parameter(0x0003);							 
	LCD_SSD1963_write_parameter(0x0004);
	
	printf("Set PLL MN Success \n");

    /* Set PLL */
	LCD_SSD1963_write_command(0x00E0);  
	LCD_SSD1963_write_parameter(0x0001);  /* PLL enable  */
	delay_ms(100);	      
	LCD_SSD1963_write_command(0x00E0);	  /* Lock PLL   */
	LCD_SSD1963_write_parameter(0x0003);
	delay_ms(100);

   /* Software Reset */
	LCD_SSD1963_write_command(0x0001);  
	delay_ms(100);
	printf("Software Reset \n");
	

	/* Set LSHIFT Frequency */
	LCD_SSD1963_write_command(0x00E6);	  
	LCD_SSD1963_write_parameter(0x0003);
	LCD_SSD1963_write_parameter(0x0055);
	LCD_SSD1963_write_parameter(0x0055);
	printf("Set LSHIFT Frequency \n");

 	/* Set LCD Mode */
	LCD_SSD1963_write_command(0x00B0);	      	  
	LCD_SSD1963_write_parameter(0x0000);
	LCD_SSD1963_write_parameter(0x0000);
	LCD_SSD1963_write_parameter(HDP>>8);  /*Set the horizontal panel size*/
	LCD_SSD1963_write_parameter(HDP);
	LCD_SSD1963_write_parameter(VDP>>8);  /*Set the horizontal panel size*/
	LCD_SSD1963_write_parameter(VDP);
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
	LCD_SSD1963_write_parameter(HT>>8);  //Set HT
	LCD_SSD1963_write_parameter(HT);
	LCD_SSD1963_write_parameter(HPS>>8);  //Set HPS
	LCD_SSD1963_write_parameter(HPS);
	LCD_SSD1963_write_parameter(HPW);			         //Set HPW
	LCD_SSD1963_write_parameter(LPS>>8);  //Set HPS
	LCD_SSD1963_write_parameter(LPS);
	LCD_SSD1963_write_parameter(0x0000);

 	/*Set Vertical Period */
	LCD_SSD1963_write_command(0x00B6);	           //VSYNC
	LCD_SSD1963_write_parameter(VT>>8);   //Set VT
	LCD_SSD1963_write_parameter(VT);
	LCD_SSD1963_write_parameter(VPS>>8);  //Set VPS
	LCD_SSD1963_write_parameter(VPS);
	LCD_SSD1963_write_parameter(VPW);			         //Set VPW
	LCD_SSD1963_write_parameter((FPS>>8));  //Set FPS
	LCD_SSD1963_write_parameter(FPS);

 	/* Set GPIO Value */
	LCD_SSD1963_write_command(0x00BA);     
	LCD_SSD1963_write_parameter(0x0005);     //GPIO[3:0] out 1
		
	/* Set GPIO Configuration */
	LCD_SSD1963_write_command(0x00B8);    
	LCD_SSD1963_write_parameter(0x0007);    //GPIO3=input, GPIO[2:0]=output
	LCD_SSD1963_write_parameter(0x0001);    //GPIO0 normal


	/* Set Address Mode *///under search
	LCD_SSD1963_write_command(0x0036);      
	LCD_SSD1963_write_parameter(0x0008);

	/* Pixel Data Interface */
	LCD_SSD1963_write_command(0x00F0);    

	LCD_SSD1963_write_parameter(0x0003);
	delay_ms(100);

	/* Set Display On */
	LCD_SSD1963_write_command(0x0029);        //display on

	/* Set PWM Configuration */
	LCD_SSD1963_write_command(0x00BE);        //set PWM for B/L
	LCD_SSD1963_write_command(0x0006);
	LCD_SSD1963_write_parameter(0x0080);
	LCD_SSD1963_write_parameter(0x0001);
	LCD_SSD1963_write_parameter(0x00f0);
	LCD_SSD1963_write_parameter(0x0000);
	LCD_SSD1963_write_parameter(0x0000);

 	/* Set DBC Configuration */
	LCD_SSD1963_write_command(0x00d0);
	LCD_SSD1963_write_parameter(0x000d);
		
	LCD_SSD1963_clear(BLACK);

}

/* @brief  Draw a point.
 *@param  xpos can be 0 to HDP and ypos can be 0 to VDP.
        color:Color value defined in ssd1963_driver.h.
 *@retval None.
	*/

void LCD_SSD1963_drawpoint(u32 xpos, u32 ypos, u32 color)
{
 	/* Set the Cursor */
	LCD_SSD1963_write_command(0x2A);	
	LCD_SSD1963_write_parameter(xpos>>8);	    
	LCD_SSD1963_write_parameter(xpos);
	LCD_SSD1963_write_parameter(HDP>>8);	    
	LCD_SSD1963_write_parameter(HDP);
	
	LCD_SSD1963_write_command(0x2b);	
	LCD_SSD1963_write_parameter(ypos>>8);	    
	LCD_SSD1963_write_parameter(ypos);
	LCD_SSD1963_write_parameter(VDP>>8);	    
	LCD_SSD1963_write_parameter(VDP);

	/* Write Memory Start */
	LCD_SSD1963_write_command(0x002C);       
	LCD_SSD1963_write_data(color); 
}

/**
  * @brief  Put a 16*8 character.
  * @param  xpos can be 0 to HDP-7 and ypos can be 0 to VDP-15.
  *         asc2num:The ascii value of the character.
  *         pencolor of backcolor:Color value defined in ssd1963_driver.h.
  * @retval -1:xpos of ypos is not Expected.
  *          0:The char is puted succeeded.
  */
s8 LCD_SSD1963_putchar(u32 xpos,u32 ypos,u8 asc2num,u32 pencolor,u32 backcolor)
{       

    u8 temp;
    u8 pos,t;
	
    if(xpos>(HDP-7)||ypos>(VDP-15)) return -1;		    

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


/**
  * @brief  Put a string in a row.
  * @param  xpos can be 0 to HDP-7 and ypos can be 0 to VDP-15.
  *         *p is the pointer of the string whitch should end with 0.
  *         pencolor or backcolor:Color value defined in ssd1963_driver.h.
  * @retval -1:xpos of ypos is not expected.
  *          0:The string is puted succeeded.
  */
s8 LCD_SSD1963_putstring(u32 xpos,u32 ypos,const char* p,u32 pencolor,u32 backcolor)
{         
    while(*p!='\0')
    {       
        if(xpos>(HDP-7)||ypos>(VDP-15)) return -1;
        LCD_SSD1963_putchar(xpos,ypos,*p,pencolor,backcolor);
        xpos+=8;
        p++;
    }  
		return 0;
}

/**
  * @brief  Draw a line.
  * @param  xsta,ysta is the start position and
  *         xend,yend is the end position.
  *         color:Color value defined in ssd1963_driver.h.
  * @retval None.
  */
void LCD_SSD1963_drawline(u32 xsta,u32 ysta,u32 xend,u32 yend,u32 color)
{
 
		
 s8 dx,dy,e;
 dx=xend-xsta; 
 dy=yend-ysta;
    
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

/**
  * @brief  Set a window for fillling in lcd.
  * @param  xsta,ysta is the upper-left start position and
  *         xend,yend is the lower-right end position.
  * @retval None.
  */
static void LCD_SSD1963_windowmax(u32 xsta,u32 ysta,u32 xend,u32 yend) 
{	
	LCD_SSD1963_write_command(0X002A);
	LCD_SSD1963_write_parameter(xsta>>8);
	LCD_SSD1963_write_parameter(xsta);
	LCD_SSD1963_write_parameter(xend>>8);
	LCD_SSD1963_write_parameter(xend);
		
	LCD_SSD1963_write_command(0X002B);	
	LCD_SSD1963_write_parameter(ysta>>8);	
	LCD_SSD1963_write_parameter(ysta);
	LCD_SSD1963_write_parameter(yend>>8);	
	LCD_SSD1963_write_parameter(yend);			
}
/**
  * @brief  Draw a rectangle.
  * @param  xsta,ysta is the upper-left start position and
  *         xend,yend is the lower-right end position.
  *         if_fill:   1:fill all 
  *                   else: not fill
  *         color:Color value defined in ssd1963_driver.h.
  * @retval None.
  */
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

/**
  * @brief  Draw a circle.
  * @param  x0,y0 is the origin position.
  *         r is radius.
  *         if_fill:   1:fill all 
  *                    else: not fill
  *         color:Color value defined in ssd1963_driver.h.
  * @retval None.
  */
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


