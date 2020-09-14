#ifndef __M6020_H
#define __M6020_H

#include "user_common.h"

#define M6020_SENDID		0x1FF
#define M6020_SENDID_READID_START	0x205
#define M6020_SENDID_READID_END	0x207

extern M6020s_t M6020s[3];
extern M6020s_t M6020s_Yaw;//IDΪ1
extern M6020s_t M6020s_Pitch;//2

void M6020_setCurrent(int16_t iq1, int16_t iq2, int16_t iq3);
void M6020_getInfo(CanRxMsg RxMessage);
void M6020_setTargetAngle(M6020Name_e motorName, int32_t angle);


#endif 

