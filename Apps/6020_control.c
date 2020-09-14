#include "6020_control.h"
#include "user_code.h"

//float Temp_Chassis_Vx = 0.0f, Temp_Chassis_Vy = 0.0f, Temp_Chassis_VOmega = 0.0f;
//float Temp_Cloud_Vx = 0.0f, Temp_Cloud_Vy = 0.0f;
Cloud_t Cloud;
/**
  * @brief  ��̨��ʼ�������ò�������λ��̨
  * @param  None
  * @retval None
  */
void Cloud_Init(void){
	
	M6020s[0].turnCount = 0;
	M6020s[1].turnCount = 0;
	M6020s[2].turnCount = 0;
	
	Cloud.LpfAttFactor = 0.1f;
	
	//��������ʱ�̻�е�Ƕȵ�Yaw���Pitch��
	//Cloud.targetYawRaw = Cloud.targetYawLPF = M6020s[2].totalAngle;
//	Cloud.targetPitchRaw = Cloud.targetPitchLPF = M6020s[1].totalAngle;
//  Cloud.targetPitchRaw = Cloud.targetPitchLPF = Cloud_Pitch_Center;
	
		/************************************��е�Ƕ�PID***********************************/	
	//���û�е�Ƕ�ģʽYaw��PID
//  PositionPID_paraReset(&M6020s[2].Attitude_pid, 0.25f, 0.0f, 0.0f,25000, 500);
//	PositionPID_paraReset(&M6020s[2].Speed_pid, 1500.0f, 0.0f, 80.0f,  25000, 500);
//  PositionPID_paraReset(&M6020s[0].Attitude_pid, 0.2f, 0.0f, 0.0f,   25000, 500);
//  PositionPID_paraReset(&M6020s[0].Speed_pid, 380.0f, 0.0f, 0.0f,   25000, 500);
	
	PositionPID_paraReset(&M6020s[1].Attitude_pid, 5.0f, 0.0f, 0.0f,   28000, 800);
  PositionPID_paraReset(&M6020s[1].Speed_pid, 1.0f, 0.0f, 0.0f,   25000, 3000);
		

	
//	IncrementalPID_paraReset(&M6020s[1].Speed_pid, 2.5f, 0.8f, 0.0f, 8000, 1000);
	
//	//��������ʱ�������ǽǶȵ�Yaw���Pitch��
//	Cloud.IMUtargetYawRaw = Cloud.IMUtargetYawLPF = GY_6050[0].totalYaw;

//	M6020_setTargetAngle(M6020_YAW, Cloud.targetYawRaw);
//	M6020_setTargetAngle(M6020_PITCH_Right, Cloud.targetPitchRaw);
	
	//���ø���ģʽYaw��PID
/************************************������PID***********************************/	
//	PositionPID_paraReset(&Cloud.YawAttitude_pid, -350.0f, 0.0f, -200.0f, 0.0f, 0.0f, 0.0f, 8000,1000);
//	PositionPID_paraReset(&Cloud.YawSpeed_pid, 7.0f, 0.0f, 18.0f, 0.0f, 0.0f, 0.0f, 29000, 1000);
	
//	PositionPID_paraReset(&Cloud.PitchAttitude_pid, 18.0f, 0.0f, 10.0f, 0.0f, 0.0f, 0.0f,29000, 200);
//	PositionPID_paraReset(&Cloud.PitchSpeed_pid, 2.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,29000, 200);

	
}	


void Pitch_control(float temp_targetyaw, float delta_pitch,uint8_t mode)
{
	Cloud.targetPitchRaw = M6020s_Yaw.totalAngle;
	

		if((mode == ControlMode_OFF)||(dr16_data.DR16OffLineFlag)){
		Cloud.targetPitchLPF = 2500;
		M6020_setCurrent(0, 0, 0);
		return;
	}
	
	Cloud.targetPitchRaw += delta_pitch;
	
	//��̨�޷�begin
	if(Cloud.targetPitchRaw > Cloud_Pitch_Max){
		Cloud.targetPitchRaw = Cloud_Pitch_Max;
	}
	if(Cloud.targetPitchRaw < Cloud_Pitch_Min) {
		Cloud.targetPitchRaw = Cloud_Pitch_Min;
	}

	//��̨�޷�end

	//ƽ������begin
	Filter_IIRLPF(&Cloud.targetPitchRaw, &Cloud.targetPitchLPF, 0.1);
	//ƽ������end
	
	M6020_setTargetAngle(M6020_PITCH_Left, Cloud.targetPitchLPF);
	
			//PITCH��PID	
	M6020s[1].inneroutCurrent = Position_PID(&M6020s[1].Attitude_pid, Cloud.targetPitchLPF, M6020s[1].totalAngle);
	M6020s[1].outCurrent = Position_PID(&M6020s[1].Speed_pid, M6020s[1].inneroutCurrent, M6020s[1].realSpeed);
//  M6020s[1].outCurrent = -M6020s[0].outCurrent;
	
		  //���־λ
		M6020s[0].M6020InfoUpdateFlag = 0;				
		M6020s[1].M6020InfoUpdateFlag = 0;				
		M6020s[2].M6020InfoUpdateFlag = 0;		


		//�趨�������ֵ

    M6020_setCurrent(0,M6020s[1].outCurrent,0);
}



//void RC_control(float Temp_Cloud_Vx,float Temp_Cloud_Vy)
//{
//		M6020s[1].outCurrent = Incremental_PID(&M6020s[1].pid, M6020s[1].targetSpeed, M6020s[1].realSpeed);
//}
//{
//	//����
//	Temp_Chassis_Vx = dr16_rocker_L.x * 15.0f;
//	Temp_Chassis_Vy = dr16_rocker_L.y * 15.0f;
//	//Temp_Chassis_VOmega = dr16_rocker_R.x * 10.0f;

//	//��̨
//	Temp_Cloud_Vy = dr16_rocker_R.y / 10.0f;
//	Temp_Cloud_Vx = dr16_rocker_R.x / 250.0f;

//	//ң��
//	if (ControlStatus.ControlRight == ControlMode_High)
//	{
//		M6020_setCurrent(0, 0, 0);
//	}

//	else if (ControlStatus.ControlRight == ControlMode_Mid)
//	{
//		M6020_setCurrent(0, 10000, 0);
//		Chassis_processing(Temp_Chassis_Vx, Temp_Chassis_Vy, Temp_Chassis_VOmega, ControlStatus.ControlLeft);
//		M3508s[i].outCurrent = Incremental_PID(&M3508s[i].pid, M3508s[i].targetSpeed, M3508s[i].realSpeed);

//	}
//}



