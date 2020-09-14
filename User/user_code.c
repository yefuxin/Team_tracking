#include "user_code.h"


uint8_t LED_Cycle = 1;
uint8_t CeShiBuff[CESHI_1+2]; 	//Ω” ’buff

void Init(void){

	LED_GPIO_Config();
//	HX711_Init();
#if USART_FLAG == 1 
	USART1_QuickInit(115200);
	USART1_RXDMA_Config((uint32_t)CeShiBuff, CESHI_1+2);
#elif USART_FLAG == 2
	USART2_QuickInit(115200);
	USART2_RXDMA_Config((uint32_t)HX711_data, HX711_Buff+2);
#elif USART_FLAG == 3
	USART3_QuickInit(115200);
	USART3_RXDMA_Config((uint32_t)CeShiBuff, CESHI_1+2);
#elif USART_FLAG == 6
	USART6_QuickInit(115200);
	USART6_RXDMA_Config((uint32_t)CeShiBuff, CESHI_1+2);
#elif USART_FLAG == 7
	USART7_QuickInit(115200);
	USART7_RXDMA_Config((uint32_t)CeShiBuff, CESHI_1+2);
#elif USART_FLAG == 8
	USART8_QuickInit(115200);
	USART8_RXDMA_Config((uint32_t)CeShiBuff, CESHI_1+2);
#endif
//	printf("≤‚ ‘¿˝≥Ã!!!\n");
	Usart_SendString(USART6,"S1E");
	
	TIM6_CounterMode(89, 9999);
	
	

}


void Test(void)
{ 

	
}


