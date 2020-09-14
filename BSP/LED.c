/**
  ******************************************************************************
  * @file    LED.c
  * @author  Hare
  * @version V1.0
  * @date    
  * @brief   LED应用函数接口
  ******************************************************************************
  */
  
  
#include "LED.h"

extern uint8_t LED_Cycle;

void LED_GPIO_Config(void)
{

	GPIO_InitTypeDef GPIO_InitStruct;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG|RCC_AHB1Periph_GPIOE|RCC_AHB1Periph_GPIOF,ENABLE);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;	
	GPIO_InitStruct.GPIO_Speed = GPIO_Low_Speed;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;	

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
	GPIO_Init(GPIOE, &GPIO_InitStruct);	
	GPIO_SetBits(GPIOE,GPIO_Pin_9);
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
	GPIO_Init(GPIOE, &GPIO_InitStruct);	
	GPIO_SetBits(GPIOE,GPIO_Pin_10);
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11;
	GPIO_Init(GPIOE, &GPIO_InitStruct);	
	GPIO_SetBits(GPIOE,GPIO_Pin_11);
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12;
	GPIO_Init(GPIOE, &GPIO_InitStruct);	
	GPIO_SetBits(GPIOE,GPIO_Pin_12);
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13;
	GPIO_Init(GPIOE, &GPIO_InitStruct);	
	GPIO_SetBits(GPIOE,GPIO_Pin_13);
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_14;
	GPIO_Init(GPIOE, &GPIO_InitStruct);	
	GPIO_SetBits(GPIOE,GPIO_Pin_14);
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15;
	GPIO_Init(GPIOE, &GPIO_InitStruct);	
	GPIO_SetBits(GPIOE,GPIO_Pin_15);
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;
	GPIO_Init(GPIOE, &GPIO_InitStruct);	
	GPIO_ResetBits(GPIOF,GPIO_Pin_7);
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;
	GPIO_Init(GPIOG, &GPIO_InitStruct);	
	GPIO_SetBits(GPIOG,GPIO_Pin_2);	
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
	GPIO_Init(GPIOG, &GPIO_InitStruct);	
	GPIO_SetBits(GPIOG,GPIO_Pin_3);
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4;
	GPIO_Init(GPIOG, &GPIO_InitStruct);	
	GPIO_SetBits(GPIOG,GPIO_Pin_4);
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;
	GPIO_Init(GPIOG, &GPIO_InitStruct);	
	GPIO_SetBits(GPIOG,GPIO_Pin_5);
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
	GPIO_Init(GPIOG, &GPIO_InitStruct);	
	GPIO_SetBits(GPIOG,GPIO_Pin_6);
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;
	GPIO_Init(GPIOG, &GPIO_InitStruct);	
	GPIO_SetBits(GPIOG,GPIO_Pin_7);
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8;
	GPIO_Init(GPIOG, &GPIO_InitStruct);	
	GPIO_SetBits(GPIOG,GPIO_Pin_8);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;
	GPIO_Init(GPIOG, &GPIO_InitStruct);	
	GPIO_SetBits(GPIOG,GPIO_Pin_1);
}


void User_LED_Eight(void)
{
	if (LED_Cycle >= 70)
	{
		LED_Cycle = 1;
	}
	else
	{
		LED_Cycle++;
	}
	
	switch (LED_Cycle)
	{
	  case 10:GPIO_ToggleBits(GPIOG, GPIO_Pin_1);break;
	  case 20:GPIO_ToggleBits(GPIOG, GPIO_Pin_2); break;
	  case 30:GPIO_ToggleBits(GPIOG, GPIO_Pin_3); break;
	  case 40:GPIO_ToggleBits(GPIOG, GPIO_Pin_4); break;
	  case 50:GPIO_ToggleBits(GPIOG, GPIO_Pin_5); break;
	  case 60:GPIO_ToggleBits(GPIOG, GPIO_Pin_6); break;
	  case 70:GPIO_ToggleBits(GPIOG, GPIO_Pin_7); break;
	  case 80:GPIO_ToggleBits(GPIOG, GPIO_Pin_8); break;
	
//	  case 10:GPIO_ToggleBits(GPIOE, GPIO_Pin_9);break;
//	  case 20:GPIO_ToggleBits(GPIOE, GPIO_Pin_10); break;
//	  case 30:GPIO_ToggleBits(GPIOE, GPIO_Pin_11); break;
//	  case 40:GPIO_ToggleBits(GPIOE, GPIO_Pin_12); break;
//	  case 50:GPIO_ToggleBits(GPIOE, GPIO_Pin_13); break;
//	  case 60:GPIO_ToggleBits(GPIOE, GPIO_Pin_14); break;
//	  case 70:GPIO_ToggleBits(GPIOE, GPIO_Pin_15); break;
//	  case 80:GPIO_ToggleBits(GPIOE, GPIO_Pin_8); break;		
	}
}




