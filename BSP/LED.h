#ifndef __LED_H
#define __LED_H

#include "user_common.h"

void LED_GPIO_Config(void);
void User_LED_Eight(void);

/* ֱ�Ӳ����Ĵ����ķ�������IO */
#define	digitalHi(p,i)		 {p->BSRR=i;}	 //���Ϊ�ߵ�ƽ		
#define digitalLo(p,i)		 {p->BRR=i;}	 //����͵�ƽ
#define digitalToggle(p,i) {p->ODR ^=i;} //�����ת״̬


/* �������IO�ĺ� */
#define LED1_TOGGLE		 digitalToggle(GPIOE,GPIO_Pin_7)
#define LED1_OFF		   digitalHi(GPIOE,GPIO_Pin_7)
#define LED1_ON			   digitalLo(GPIOE,GPIO_Pin_7)



#endif /*__GPIO_H*/
