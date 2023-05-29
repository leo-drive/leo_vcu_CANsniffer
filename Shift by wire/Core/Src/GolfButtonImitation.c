

#include "GolfButtonImitation.h"
#include "main.h"
#include "cmsis_os.h"

void vHandBrakePull(void)
{
	HAL_GPIO_WritePin(HB_PULL_GPIO_Port,HB_PULL_Pin,GPIO_PIN_SET);
	osDelay(20);
	HAL_GPIO_WritePin(HB_PULL_GPIO_Port,HB_PULL_Pin,GPIO_PIN_RESET);
	
}


void vHandBrakePush(void)
{
	HAL_GPIO_WritePin(HB_PUSH_GPIO_Port,HB_PUSH_Pin,GPIO_PIN_SET);
	osDelay(20);
	HAL_GPIO_WritePin(HB_PUSH_GPIO_Port,HB_PUSH_Pin,GPIO_PIN_RESET);
	
}

void vParkBrake(void)
{
	
	
	
	HAL_GPIO_WritePin(RELAY_COIL_GPIO_Port,RELAY_COIL_Pin,GPIO_PIN_RESET);//imitate pressed Park button 
	osDelay(20);//wait a bit
	HAL_GPIO_WritePin(RELAY_COIL_GPIO_Port,RELAY_COIL_Pin,GPIO_PIN_SET);// release button
	//osDelay(1000);
}



void vStartStop(void)
{
	/* StartStop Button has two pins Which are active when grounded*/
	HAL_GPIO_WritePin(LS_SWITCH_1_GPIO_Port,LS_SWITCH_1_Pin,GPIO_PIN_SET);
	osDelay(1);
	HAL_GPIO_WritePin(LS_SWITCH_2_GPIO_Port,LS_SWITCH_2_Pin,GPIO_PIN_SET);
	osDelay(20);
	HAL_GPIO_WritePin(LS_SWITCH_1_GPIO_Port,LS_SWITCH_1_Pin,GPIO_PIN_RESET);
	osDelay(1);
	HAL_GPIO_WritePin(LS_SWITCH_2_GPIO_Port,LS_SWITCH_2_Pin,GPIO_PIN_RESET);
}






