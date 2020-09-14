// PID.h

#ifndef __PID_H
#define __PID_H


#include "user_common.h"


void PositionPID_paraReset(positionpid_t *pid_t, float kp, float ki, float kd, uint32_t MaxOutput, uint32_t IntegralLimit);
void PositionPID_setPara(positionpid_t *pid_t, float kp, float ki, float kd);
float Position_PID(positionpid_t *pid_t, float target, float measured);

void IncrementalPID_paraReset(incrementalpid_t *pid_t, float kp, float ki, float kd, uint32_t MaxOutput, uint32_t IntegralLimit);
void IncrementalPID_setPara(incrementalpid_t *pid_t, float kp, float ki, float kd);
float Incremental_PID(incrementalpid_t *pid_t, float target, float measured);

float Pitch_Position_PID(positionpid_t *pid_t, float target, float measured);
#endif

