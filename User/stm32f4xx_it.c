/**
  ******************************************************************************
  * @file    Project/STM32F4xx_StdPeriph_Templates/stm32f4xx_it.c 
  * @author  MCD Application Team
  * @version V1.8.0
  * @date    04-November-2016
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2016 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_it.h"
#include "user_common.h"


#define KEY_ACC_TIME     500  //ms

extern uint8_t CeShiBuff[USART2_BUFFLEN+2]; 	//接收buff
extern uint8_t HX711_data[HX711_Buff+2]; 	
/** @addtogroup Template_Project
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/



/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{}

/**
  * @brief  This function handles PendSV_Handler exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
   /**/
}

void CAN1_RX0_IRQHandler(void){
	//接收中断
	if(CAN_GetITStatus(CAN1, CAN_IT_FMP0)){
		CanRxMsg RxMessage;	
		CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);
		M3508_getInfo(RxMessage);	
		M6020_getInfo(RxMessage);
		/*printf("id %x, data %x, T%x, IL%x, IH%x, SL%x, SH%x, AL%x, AH%x\n", RxMessage.StdId, RxMessage.Data[7],
																				RxMessage.Data[6],
																				RxMessage.Data[5],
																				RxMessage.Data[4],
																				RxMessage.Data[3],
																				RxMessage.Data[2],
																				RxMessage.Data[1],
																				RxMessage.Data[0]);*/
		CAN_ClearITPendingBit(CAN1, CAN_IT_FMP0);
	}
	
}

void CAN2_RX0_IRQHandler(void){
	//接收中断
	if(CAN_GetITStatus(CAN2, CAN_IT_FMP0)){
		CanRxMsg RxMessage;	
		CAN_Receive(CAN2, CAN_FIFO0, &RxMessage);
//		M6020_getInfo(RxMessage);
		GY6050_getCloundInfo(RxMessage);
		CAN_ClearITPendingBit(CAN2, CAN_IT_FMP0);
	}
	
}

/**
  * @brief  USART1中断服务函数，DR遥控器
  * @param  None
  * @retval None
  */
//void USART1_IRQHandler(void){
//	
//	if(USART_GetITStatus(USART1, USART_IT_IDLE) != RESET)
//	{
//		//关闭DMA
//		DMA_Cmd(USART1_RX_DMA_STREAM, DISABLE);
//		
//		//printf("%d\n",DMA_GetCurrDataCounter(USART1_RX_DMA_STREAM));
//		//获取DMAbuff剩余大小，是否匹配
//		if (DMA_GetCurrDataCounter(USART1_RX_DMA_STREAM) == 2)
//		{
//			//printf("%s\n", DR16_rxBuff);
//			
//			DR16_dataProcess(DR16_rxBuff);
//		}
//		
//		//设置传输数据长度，+2保证安全
//        DMA_SetCurrDataCounter(USART1_RX_DMA_STREAM,DR16_DBUS_PACKSIZE+2);
//		//打开DMA
//		DMA_Cmd(USART1_RX_DMA_STREAM, ENABLE);
//		
//		
//		//清除空闲中断标志位
//		(void)USART1->DR;
//		(void)USART1->SR;
//		//串口空闲中断标志位并不能通过下面的函数清除
//		//USART_ClearITPendingBit(USART1, USART_IT_IDLE);
//	}
//}



#if USART_FLAG == 1
void USART1_IRQHandler(void){
	
	if(USART_GetITStatus(USART1, USART_IT_IDLE) != RESET)
	{
		//关闭DMA
		DMA_Cmd(USART1_RX_DMA_STREAM, DISABLE);
 		
		printf("%s",CeShiBuff);
		//memset(CeShiBuff, 0, sizeof CeShiBuff); 
	
		//设置传输数据长度，+2保证安全
    DMA_SetCurrDataCounter(USART1_RX_DMA_STREAM,CESHI_1+2)  ;
		//打开DMA
		DMA_Cmd(USART1_RX_DMA_STREAM, ENABLE);
		
		
		//清除空闲中断标志位
		(void)USART1->DR;
		(void)USART1->SR;
		//串口空闲中断标志位并不能通过下面的函数清除
		//USART_ClearITPendingBit(USART1, USART_IT_IDLE);
	}
}

#elif USART_FLAG == 2
uint16_t DMA_Counter = 0;
int aoligei = 0;
void USART2_IRQHandler(void){
	
	if(USART_GetITStatus(USART2, USART_IT_IDLE) != RESET)
	{
		//关闭DMA
		DMA_Cmd(USART2_RX_DMA_STREAM, DISABLE);
		//设置传输数据长度，+2保证安全
    DMA_SetCurrDataCounter(USART2_RX_DMA_STREAM,HX711_Buff+2)  ;
		//打开DMA
		DMA_Cmd(USART2_RX_DMA_STREAM, ENABLE);
		
		
		//清除空闲中断标志位
		(void)USART2->DR;
		(void)USART2->SR;
		//串口空闲中断标志位并不能通过下面的函数清除
		//USART_ClearITPendingBit(USART1, USART_IT_IDLE);
	}
}

#elif USART_FLAG == 3
void USART3_IRQHandler(void){
	
	if(USART_GetITStatus(USART3, USART_IT_IDLE) != RESET)
	{
		//关闭DMA
		DMA_Cmd(USART3_RX_DMA_STREAM, DISABLE);
 		
		printf("%s",CeShiBuff);
		//memset(CeShiBuff, 0, sizeof CeShiBuff); 
	
		//设置传输数据长度，+2保证安全
    DMA_SetCurrDataCounter(USART3_RX_DMA_STREAM,CESHI_1+2)  ;
		//打开DMA
		DMA_Cmd(USART3_RX_DMA_STREAM, ENABLE);
		
		
		//清除空闲中断标志位
		(void)USART3->DR;
		(void)USART3->SR;
		//串口空闲中断标志位并不能通过下面的函数清除
		//USART_ClearITPendingBit(USART1, USART_IT_IDLE);
	}
}

#elif USART_FLAG == 6
void USART6_IRQHandler(void){
	
	if(USART_GetITStatus(USART6, USART_IT_IDLE) != RESET)
	{
		//关闭DMA
		DMA_Cmd(USART6_RX_DMA_STREAM, DISABLE);
 		
		printf("%s\n",CeShiBuff);
		//memset(CeShiBuff, 0, sizeof CeShiBuff); 
	
		//设置传输数据长度，+2保证安全
    DMA_SetCurrDataCounter(USART6_RX_DMA_STREAM,CESHI_1+2)  ;
		//打开DMA
		DMA_Cmd(USART6_RX_DMA_STREAM, ENABLE);
		
		
		//清除空闲中断标志位
		(void)USART6->DR;
		(void)USART6->SR;
		//串口空闲中断标志位并不能通过下面的函数清除
		//USART_ClearITPendingBit(USART1, USART_IT_IDLE);
	}
}

#elif USART_FLAG == 7
void UART7_IRQHandler(void){
	
	if(USART_GetITStatus(UART7, USART_IT_IDLE) != RESET)
	{
		//关闭DMA
		DMA_Cmd(UART7_RX_DMA_STREAM, DISABLE);
 		
		printf("%s",CeShiBuff);
//		printf("111");
		//memset(CeShiBuff, 0, sizeof CeShiBuff); 
	
		//设置传输数据长度，+2保证安全
    DMA_SetCurrDataCounter(UART7_RX_DMA_STREAM,CESHI_1+2)  ;
		//打开DMA
		DMA_Cmd(UART7_RX_DMA_STREAM, ENABLE);
		
		
		//清除空闲中断标志位
		(void)UART7->DR;
		(void)UART7->SR;
		//串口空闲中断标志位并不能通过下面的函数清除
		//USART_ClearITPendingBit(USART1, USART_IT_IDLE);
	}
}

#elif USART_FLAG == 8
void UART8_IRQHandler(void){
	
	if(USART_GetITStatus(UART8, USART_IT_IDLE) != RESET)
	{
		//关闭DMA
		DMA_Cmd(UART8_RX_DMA_STREAM, DISABLE);
 		
		printf("%s",CeShiBuff);
//		printf("111");
		//memset(CeShiBuff, 0, sizeof CeShiBuff); 
	
		//设置传输数据长度，+2保证安全
    DMA_SetCurrDataCounter(UART8_RX_DMA_STREAM,CESHI_1+2)  ;
		//打开DMA
		DMA_Cmd(UART8_RX_DMA_STREAM, ENABLE);
		
		
		//清除空闲中断标志位
		(void)UART8->DR;
		(void)UART8->SR;
		//串口空闲中断标志位并不能通过下面的函数清除
		//USART_ClearITPendingBit(USART1, USART_IT_IDLE);
	}
}
#endif

//void UART7_IRQHandler(void){
//	
//	if(USART_GetITStatus(UART7, USART_IT_IDLE) != RESET)
//	{
//		//关闭DMA
//		DMA_Cmd(UART7_RX_DMA_STREAM, DISABLE);
// 		
//		printf("%s",CeShiBuff);
////		printf("111");
//		//memset(CeShiBuff, 0, sizeof CeShiBuff); 
//	
//		//设置传输数据长度，+2保证安全
//    DMA_SetCurrDataCounter(UART7_RX_DMA_STREAM,CESHI_1+2)  ;
//		//打开DMA
//		DMA_Cmd(UART7_RX_DMA_STREAM, ENABLE);
//		
//		
//		//清除空闲中断标志位
//		(void)UART7->DR;
//		(void)UART7->SR;
//		//串口空闲中断标志位并不能通过下面的函数清除
//		//USART_ClearITPendingBit(USART1, USART_IT_IDLE);
//	}
//}

void TIM6_DAC_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET) 
	{	
	
//		float Temp_Chassis_Vx=0.0f,Temp_Chassis_Vy=0.0f,Temp_Chassis_VOmega=0.0f;
////		float Temp_Cloud_Vx = 0.0f,Temp_Cloud_Vy = 0.0f;
//		switch(ControlStatus.ControlLeft)
//		{
//			case ControlMode_ByRC:
//						Temp_Chassis_Vx = dr16_rocker_L.x*15.0f;
//						Temp_Chassis_Vy = dr16_rocker_L.y*15.0f;
//						Temp_Chassis_VOmega = dr16_rocker_R.x*15.0f;
//					Temp_Cloud_Vy = dr16_rocker_R.y*1;
//					Temp_Cloud_Vx = dr16_rocker_R.y*1;
//						
//						Chassis_processing(Temp_Chassis_Vx, Temp_Chassis_Vy, Temp_Chassis_VOmega, ControlStatus.ControlLeft);
//			 // Temp_Chassis_VOmega = dr16_rocker_R.x*8.0f;
//				break;
//			
//		  case ControlMode_ByPC:

//			 break;
//			
//			
//			case ControlMode_OFF:

//				
//			 break;
//		}
		
//		Pitch_control(Temp_Cloud_Vy,Temp_Cloud_Vx,ControlStatus.ControlLeft);

//		User_LED_Eight();
		
		//测试串口接收信息 -- 以后可以根据接收的信息来循迹
if(CeShiBuff[0]=='S'&CeShiBuff[1]=='1'&CeShiBuff[2]=='E')
{
	GPIO_ResetBits(GPIOG,GPIO_Pin_1);
}
else if(CeShiBuff[0]=='S'&CeShiBuff[1]=='2'&CeShiBuff[2]=='E')
{
	GPIO_ResetBits(GPIOG,GPIO_Pin_2);
}
else if(CeShiBuff[0]=='S'&CeShiBuff[1]=='3'&CeShiBuff[2]=='E')
{
	GPIO_ResetBits(GPIOG,GPIO_Pin_3);
}
else if(CeShiBuff[0]=='S'&CeShiBuff[1]=='4'&CeShiBuff[2]=='E')
{
	GPIO_ResetBits(GPIOG,GPIO_Pin_4);
}
else if(CeShiBuff[0]=='S'&CeShiBuff[1]=='5'&CeShiBuff[2]=='E')
{
	GPIO_ResetBits(GPIOG,GPIO_Pin_5);
}
else if(CeShiBuff[0]=='S'&CeShiBuff[1]=='6'&CeShiBuff[2]=='E')
{
	GPIO_ResetBits(GPIOG,GPIO_Pin_6);
}
else if(CeShiBuff[0]=='S'&CeShiBuff[1]=='7'&CeShiBuff[2]=='E')
{
	GPIO_ResetBits(GPIOG,GPIO_Pin_7);
}
		
		TIM_ClearITPendingBit(TIM6 , TIM_IT_Update);  		 
	}		 	
}


/******************************************************************************/
/*                 STM32F4xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f4xx.s).                                               */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
