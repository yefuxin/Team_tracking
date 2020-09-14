#ifndef __TYPEDEFS_H
#define __TYPEDEFS_H

#include <stdbool.h>
#include <stdint.h>

#pragma anon_unions

/* 陀螺仪 */
typedef struct {
		float x;                 //浮点数X轴方向向量
		float y;                 //浮点数Y轴方向向量
		float z;                 //浮点数Z轴方向向量
}Vector_t;

typedef struct {
	float Roll;                 //ROLL轴方向
	float Pitch;                //PITCH轴方向
	float Yaw;                  //YAW轴方向
}Eular_t;

typedef struct{
	Vector_t Gyro;               //陀螺仪数据          
	Eular_t  EularDate;          //欧拉角数据     
	float lastYaw;               //上一次YAW轴数据    
	float totalYaw;
	int16_t turnCount;
	
	uint8_t ImuDevStatus;
	uint8_t ImuInfoUpdateFlag;
	uint16_t ImuInfoUpdateFrame;
	uint8_t ImuOffLineFlag;
}GY_IMU_t;

/* PID参数 */
typedef struct{
	float Target; 			        //设定目标值
	float Measured; 				    //测量值
	float err; 						      //本次偏差值
	float err_last; 				    //上一次偏差
	float err_beforeLast; 			//上上次偏差
	float Kp, Ki, Kd;				    //Kp, Ki, Kd控制系数
	float pwm; 						      //pwm输出
	uint32_t MaxOutput;				  //输出限幅
  uint32_t IntegralLimit;			//积分限幅 
}incrementalpid_t;

typedef struct{
	float Target; 					    //设定目标值
	float Measured; 				    //测量值
	float err; 						      //本次偏差值
	float err_last; 				    //上一次偏差
	float integral_err; 			  //所有偏差之和
	float Kp, Ki, Kd;				    //Kp, Ki, Kd控制系数
	float pwm; 						      //pwm输出
	uint32_t MaxOutput;				  //输出限幅
  uint32_t IntegralLimit;			//积分限幅 
}positionpid_t;


/* 底盘电机 */
typedef struct{
	uint16_t realAngle;			    //读回来的机械角度
	int16_t  realSpeed;			    //读回来的速度
	int16_t  realCurrent;		    //读回来的实际电流
	uint8_t  temperture;        //读回来的电机温度
	int16_t  targetCurrent;			//目标电流
	int16_t  targetSpeed;			  //目标速度
	uint16_t targetAngle;			  //目标角度
	int16_t  outCurrent;				//输出电流
	incrementalpid_t pid;		    //电机pid
	uint8_t  M3508InfoUpdateFlag;		  //信息读取更新标志
	uint16_t M3508InfoUpdateFrame;	  //帧率
	uint8_t  M3508OffLineFlag;		    //设备离线标志
}M3508s_t;

/* 云台电机 */
typedef struct{
	
	uint16_t realAngle;			//读回来的机械角度
	int16_t realSpeed;			//读回来的速度
	int16_t realTorque;			//读回来的实际转矩
	int16_t realTemperature;   //读回来的温度
	
	int16_t targetCurrent;		      //目标电流	
	int16_t targetAngle;		      //目标角度
	int32_t last_targetAngle;		
	int32_t targetSpeed;			    //目标速度
	int16_t outCurrent;				    //输出电流
  int16_t inneroutCurrent;
	
	uint16_t lastAngle;		          //上次的角度
	int16_t  turnCount;			        //转过的圈数
	int32_t totalAngle;			        //累积总共角度
	
	positionpid_t Attitude_pid;			  //云台yaw轴姿态pid
  positionpid_t Speed_pid;	
	
	uint8_t  M6020InfoUpdateFlag;		//信息读取更新标志
	uint16_t M6020InfoUpdateFrame;	//帧率
	uint8_t  M6020OffLineFlag;		  //设备离线标志

}M6020s_t;


/* 底盘运动 */
typedef struct{
	float targetXRaw;		//底盘x轴原始数据
	float targetYRaw;		//底盘y轴原始数据
	float targetZRaw;		//底盘z轴原始数据
	float LpfAttFactor;		//底盘滤波系数
	float targetXLPF;		//底盘x轴滤波后数据
	float targetYLPF;		//底盘y轴滤波后数据
	float targetZLPF;		//底盘z轴滤波后数据
	float speedLimit;		//底盘速度限制
	float FollowtargetYawRaw;	//底盘目标Yaw轴跟随云台原始数据
	float FollowtargetYawLPF;	//底盘Yaw轴跟随云台滤波后数据
	positionpid_t FollowYawAttitude_pid;		//底盘Yaw轴跟随云台pid
	uint8_t mode;								//底盘控制模式
	uint8_t swingFlag;							//扭腰标志位
	float swingSpeed;					//扭腰速度
	uint8_t PowerOverflowFlag;					//超功率标志位
}Chassis_t;


/* 遥控 */
typedef struct {
	struct{
		int16_t ch0;   //通道
		int16_t ch1;
		int16_t ch2;
		int16_t ch3;
		uint8_t s_left;
		uint8_t s_right;
	}rc;
	
	struct{
		int16_t x;
		int16_t y;
		int16_t z;
	
		uint8_t keyLeft;
		uint8_t keyRight;
		
	}mouse;
	
	union {
		uint16_t key_code;
		struct{
			bool press_W:1;
			bool press_S:1;
			bool press_A:1;
			bool press_D:1;
			bool press_Shift:1;
			bool press_Ctrl:1;
			bool press_Q:1;
			bool press_E:1;
			
			bool press_R:1;
			bool press_F:1;
			bool press_G:1;
			bool press_Z:1;
			bool press_X:1;
			bool press_C:1;
			bool press_V:1;
			bool press_B:1;
		};
	}keyBoard;
	
	uint16_t DR16InfoUpdateFrame;	//帧率
	uint8_t DR16OffLineFlag;		//设备离线标志
}DR16_DBUS_DATA_t;


typedef enum{
	ControlMode_ByRC = 3,
	ControlMode_ByPC = 1,
	ControlMode_OFF = 2,
}ControlMode_e;

typedef enum{
	ControlMode_Mid = 3,
	ControlMode_High = 1,
	ControlMode_Low = 2,
}Mode_e;

typedef enum{
	SpecialMode_Normal = 0,
	SpecialMode_BigSymbol = 2,	//大符模式
	SpecialMode_UPBridge = 3,	//上桥模式
	SpecialMode_Supply = 4, 	//补给站模式
}SpecialMode_t;

typedef struct{
	uint8_t ControlLeft;
	uint8_t ControlRight;			//特殊模式
}ControlStatus_t;



typedef struct {
	float x;
	float y;
	float radian;
	float degrees;
	float distance;
}rocker_t;

/* 云台运动 */
typedef struct{
	float LpfAttFactor;			//云台滤波系数

	float targetYawRaw;			//云台目标yaw轴原始数据
	float last_targetYawRaw;
	float targetPitchRaw;		//云台目标pitch轴原始数据
	float IMUtargetYawRaw;		//云台目标yaw轴原始数据	
	float IMUtargetPitchRaw;	//云台目标pitch轴原始数据
	
	float targetYawLPF;			//云台yaw轴滤波后数据
	float targetPitchLPF;		//云台pitch轴滤波后数据
	float IMUtargetYawLPF;		//云台yaw轴滤波后数据
  float last_IMUtargetYawLPF;		//云台yaw轴滤波后数据
	float IMUtargetPitchLPF;	//云台pitch轴滤波后数据
	
	float IMUYawAngleMax;		//云台IMU最大角度(右)
	float IMUYawAngleMin;		//云台IMU最小角度(左)
	float IMUPitchAngleMax;		//云台IMU最大角度(下)
	float IMUPitchAngleMin;		//云台IMU最小角度(上)
	
	positionpid_t YawAttitude_pid;			//云台yaw轴姿态pid
	positionpid_t YawSpeed_pid;			//云台yaw轴速度pid
	positionpid_t PitchAttitude_pid;			//云台roll轴姿态pid
	positionpid_t PitchSpeed_pid;			//云台roll轴姿态pid
	
	uint8_t Mode;						//云台控制模式
}Cloud_t;

typedef enum{
  M6020_PITCH_Right = 0,
	M6020_PITCH_Left,
	M6020_YAW,	
}M6020Name_e;


typedef void TIM_SetComparex_f(TIM_TypeDef* TIMx, uint32_t Compare);


#endif /* __TYPEDEFS_H */
