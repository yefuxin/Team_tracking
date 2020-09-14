#ifndef __6020_CONTROL_H
#define __6020_CONTROL_H

#include "user_common.h"

#define Cloud_Pitch_Max			6000.0f
#define Cloud_Pitch_Min			2500.0f
#define Cloud_Pitch_Center	2100.0f

#define M6020_AngleToDEG(ang)	ang/22.75f
#define Cloud_Pitch_delta		(Cloud_Pitch_Max - Cloud_Pitch_Min)

void Cloud_Init(void);
void Pitch_control(float temp_targetyaw, float delta_pitch,uint8_t mode);


extern Cloud_t Cloud;
#endif 
