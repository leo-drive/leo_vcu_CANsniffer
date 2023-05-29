#ifndef __CAN_TOOLS_H
#define __CAN_TOOLS_H

#include "main.h"
#include "stdint.h"



#define true 	1
#define false 0

#define CAN1_Buffer_size 40
#define CAN2_Buffer_size 150

#define ShiftCommand_ID 0x123456

typedef struct 
{
	CAN_HandleTypeDef *hcan;
	CAN_TxHeaderTypeDef pHeader;
	uint8_t data[8];
	uint8_t Tr;
	
}typedef_CanMsg;

typedef struct{
	uint8_t Act_Notif;
	uint8_t Init;
	uint8_t Start;
	uint8_t ConfigFilter;
	struct{
		uint8_t noProperId;
		uint8_t noValidDLC;
	}Send;
	uint8_t Receive;
}CAN_Error_Struct;

extern CAN_HandleTypeDef hcan1;
extern CAN_HandleTypeDef hcan2;

void CAN_FilterConfig(void);
void CAN_GetMessage(CAN_HandleTypeDef *hcan);
void CAN_SendMessage(CAN_HandleTypeDef *hcan,uint32_t ID,uint32_t dlc, uint8_t *data);
uint8_t StoreCANID(uint32_t ID, uint8_t Port);

typedef struct{
	
	uint32_t ID;
	uint8_t Data[8];
	uint8_t DLC;
	uint8_t cnt;
	
}CANRX_MSG;

typedef struct{
	
	CANRX_MSG CAN1_MSG[CAN1_Buffer_size];
	CANRX_MSG CAN2_MSG[CAN2_Buffer_size];
	
}typedef_CAN_Bridge;







#endif


