#include"key.h"
#include "delay.h" 

void GPIO_KEY_Config(void)
{
 /*remember init the delay in main*/
  GPIO_InitTypeDef GPIO_InitStructure;

  /* Configure KEY1 Button */
  RCC_APB2PeriphClockCmd(RCC_KEY1, ENABLE);

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_InitStructure.GPIO_Pin = GPIO_KEY1;
  GPIO_Init(GPIO_KEY1_PORT, &GPIO_InitStructure);

  /* Configure KEY2 Button */
  RCC_APB2PeriphClockCmd(RCC_KEY2, ENABLE);

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_InitStructure.GPIO_Pin = GPIO_KEY2;
  GPIO_Init(GPIO_KEY2_PORT, &GPIO_InitStructure);

  /* Configure KEY3 Button */
  RCC_APB2PeriphClockCmd(RCC_KEY3, ENABLE);

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_InitStructure.GPIO_Pin = GPIO_KEY3;
  GPIO_Init(GPIO_KEY3_PORT, &GPIO_InitStructure);  

  /* Configure KEY4 Button */
  RCC_APB2PeriphClockCmd(RCC_KEY4, ENABLE);

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_InitStructure.GPIO_Pin = GPIO_KEY4;
  GPIO_Init(GPIO_KEY4_PORT, &GPIO_InitStructure);

}

u8 ReadKeyDown(void)
{
  /* 1 key is pressed */
  if(!GPIO_ReadInputDataBit(GPIO_KEY1_PORT, GPIO_KEY1))
  {
    delay_ms(5);
	if(!GPIO_ReadInputDataBit(GPIO_KEY1_PORT, GPIO_KEY1))
	return KEY1; 
  }	
  /* 2 key is pressed */
  if(!GPIO_ReadInputDataBit(GPIO_KEY2_PORT, GPIO_KEY2))
  {
  	delay_ms(5);
	if(!GPIO_ReadInputDataBit(GPIO_KEY2_PORT, GPIO_KEY2))
    return KEY2; 
  }
  /* 3 key is pressed */
  if(!GPIO_ReadInputDataBit(GPIO_KEY3_PORT, GPIO_KEY3))
  {
  	delay_ms(5);
	if(!GPIO_ReadInputDataBit(GPIO_KEY3_PORT, GPIO_KEY3))
    return KEY3; 
  }
  /* 4 key is pressed */
  if(!GPIO_ReadInputDataBit(GPIO_KEY4_PORT, GPIO_KEY4))
  {
    
	delay_ms(5);
	if(!GPIO_ReadInputDataBit(GPIO_KEY4_PORT, GPIO_KEY4))
	return KEY4; 
  }

  /* No key is pressed */
  else 
  {
    return NOKEY;
  }
  return NOKEY;
}


