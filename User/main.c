#include "user_code.h"

/*RM STM32F427||Hx模板 */
HX711 HX711_t;
float values = 0.0f;
float Weight = 0.0f;
uint8_t HX711_data[HX711_Buff+2]; 
float original_value = 0.0f;
float net_weight = 0.0f;
float net_Lpweight = 0.0f;
#define HX711_LpfAttFactor     0.4f



int main(void)
{
     Init();
//		 original_value = Get_Weight();
	/* 在这里添加你自己的程序 */
	while(1)
	{
//	 printf("nmsl\n");
//	 Get_NetWeight(20);
//   ANO_Send_Data_V3(original_value,Weight,net_weight,net_Lpweight);
	}

}

void HX711_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	//SCK
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;	
	GPIO_InitStruct.GPIO_Speed = GPIO_Low_Speed;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;		
	GPIO_Init(GPIOB, &GPIO_InitStruct);       
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	
	//DOUT
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
//	GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStruct.GPIO_Speed = GPIO_Low_Speed;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;		
	GPIO_Init(GPIOB, &GPIO_InitStruct);
}


int HX711_GetInfo(void)
{

	int buffer = 0;
	while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1));
	delay_us(1);
	GPIO_ResetBits(GPIOB,GPIO_Pin_0);
//	while(!GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1))
// ;
		for(uint16_t i=0;i <24;i++)
		{
			delay_us(1);
			GPIO_SetBits(GPIOB,GPIO_Pin_0);
		  buffer = buffer<<1;
			delay_us(1);
			GPIO_ResetBits(GPIOB,GPIO_Pin_0);
		 if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1))
		 buffer++;
		 delay_us(1);
    }
	 GPIO_SetBits(GPIOB,GPIO_Pin_0);
	 buffer = buffer ^ 0x800000;
	 delay_us(1);
	 GPIO_ResetBits(GPIOB,GPIO_Pin_0);
	 delay_us(1);
	 return buffer;
}


int HX711_Average_Value(uint8_t times)
{
    int sum = 0;
    for (int i = 0; i < times; i++)
    {
        sum += HX711_GetInfo();
    }

    return sum / times;
}


long Get_Weight(void)
{
	Weight = HX711_Average_Value(10);
  return Weight;
}

float Get_NetWeight(uint8_t times)
{
//	delay_ms(400);
	values = HX711_Average_Value(times);
	net_weight = values - original_value;
	net_weight = (net_weight/GapValue);
	Filter_IIRLPF(&net_weight,&net_Lpweight,HX711_LpfAttFactor);
	return net_weight;
	
}









