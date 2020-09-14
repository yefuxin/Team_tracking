#include "M6020.h"
M6020s_t M6020s[3];
M6020s_t M6020s_Yaw;//ID为1
M6020s_t M6020s_Pitch;//2

/**
  * @brief  设置M6020电机电流值
  * @param  iqx (x:5) 对应id号电机的电流值，范围-10000~0~10000
  * @retval None
  */
void M6020_setCurrent(int16_t iq1, int16_t iq2, int16_t iq3){

	uint8_t data[8];
	
	data[0] = iq1 >> 8;
	data[1] = iq1;
	data[2] = iq2 >> 8;
	data[3] = iq2;
	data[4] = iq3 >> 8;
	data[5] = iq3;

	CAN_SendData(CAN1, CAN_ID_STD, M6020_SENDID, data);

}

void M6020_getInfo(CanRxMsg RxMessage){
		//报文id确认
		if((RxMessage.StdId < M6020_SENDID_READID_START) || (RxMessage.StdId > M6020_SENDID_READID_END))
			return;
			uint32_t Clound_StdId;
			Clound_StdId = RxMessage.StdId - M6020_SENDID_READID_START;
		
		
			M6020s[Clound_StdId].realAngle = (uint16_t)(RxMessage.Data[0]<<8 | RxMessage.Data[1]);
			M6020s[Clound_StdId].realSpeed = (int16_t)(RxMessage.Data[2]<<8 | RxMessage.Data[3]);
			M6020s[Clound_StdId].realTorque = (int16_t)(RxMessage.Data[4]<<8 | RxMessage.Data[5]);
			M6020s[Clound_StdId].realTemperature = (int16_t)(RxMessage.Data[6]);

			if(M6020s[Clound_StdId].realAngle - M6020s[Clound_StdId].lastAngle < -6000){
				M6020s[Clound_StdId].turnCount++;
			}

			if(M6020s[Clound_StdId].lastAngle - M6020s[Clound_StdId].realAngle < -6000){
				M6020s[Clound_StdId].turnCount--;
			}

			M6020s[Clound_StdId].lastAngle =  M6020s[Clound_StdId].realAngle;

			M6020s[Clound_StdId].totalAngle = M6020s[Clound_StdId].realAngle + (8192*M6020s[Clound_StdId].turnCount);
			M6020s[Clound_StdId].M6020InfoUpdateFrame++;
			M6020s[Clound_StdId].M6020InfoUpdateFlag = 1;		
		}

/**
  * @brief  设定M6020电机的目标角度
  * @param  motorName 	电机名字 @ref M6623Name_e
  *			angle		电流值，范围 0~8191 由于设置0和8191会导致电机振荡，要做个限幅
  * @retval None
  */
void M6020_setTargetAngle(M6020Name_e motorName, int32_t angle){
	M6020s[motorName].targetAngle = angle;
}
