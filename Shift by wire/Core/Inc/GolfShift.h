#ifndef GOLFSHIFT_H
#define GOLFSHIFT_H
#include "stdint.h"

#define P 1
#define R 2
#define N 3
#define D 4
#define S 5

#define NoChange 				1
#define ChangeRequied		2
#define InvalidShift		4
#define	TimeoutError		8
#define Intervention		16

#define HandBrakepull		1
#define HandBrakepush		2

uint8_t ShiftControl(uint8_t CurrentShift, uint8_t DesiredShift, uint8_t *SwitchMove, uint8_t *SwitchRelated);


typedef struct{
	struct{
		uint8_t Nochange 			:1;
		uint8_t Changerequied :1;
		uint8_t Invalidshift 	:1;
		uint8_t Timeouterror 	:1;
		uint8_t intervention 	:1;
		uint8_t rsv					 	:3;
	}ShiftErr;
	
	
}typedef_Error;


typedef struct{


	int16_t ACCEL_CMD;
	uint8_t randomdata[5];
	uint8_t Checksum;
	
}typedef_343h;

typedef struct{
	
	uint8_t AutonomuosMode;
	float SetSteerAngle;
	uint8_t rsv1;
	uint8_t rsv2;
	uint8_t rsv3;
}typedef_Command;
	
typedef struct{
	struct{
		uint8_t steer_request: 1;
		uint8_t cnt :6;
		uint8_t set_me_X1:1;
	}byte0;
	int16_t STEER_ANGLE_CMD;
	struct{
		uint8_t rsv: 1;
		uint8_t STEER_REQUEST_2 :1;
		uint8_t LKA_ACTIVE:1;
		uint8_t rsv2:1;
		uint8_t SETME_X3 :2;
		uint8_t BIT :1;
		uint8_t rsv3 :1;
	}byte3;
	uint8_t PERCENTAGE;
	uint8_t SETME_X64;
	uint8_t ANGLE;
	uint8_t Checksum;
}typedef_LTA;



#endif

