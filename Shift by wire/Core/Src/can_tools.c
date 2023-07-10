#include "can_tools.h"
#include "cmsis_os.h"
#include "GolfShift.h"
#define CAN_TX_BUFFER_SIZE 20


typedef_CanMsg Canbuffer[CAN_TX_BUFFER_SIZE];
CAN_TxHeaderTypeDef pHeader;
uint8_t indx = 0;
typedef_CAN_Bridge CAN_Bridge_MSG;

extern QueueHandle_t myQueue01Handle;
extern QueueHandle_t myQueue02Handle;

struct {
    CAN_Error_Struct Can1;
    CAN_Error_Struct Can2;
} myErrorFlag;

void CAN_FilterConfig(void)
{
    CAN_FilterTypeDef  sFilterConfig;
    sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
    sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
    sFilterConfig.FilterIdHigh = (uint32_t)0;
    sFilterConfig.FilterIdLow = (uint32_t)0;
    sFilterConfig.FilterMaskIdHigh = (uint32_t)0;
    sFilterConfig.FilterMaskIdLow = (uint32_t)0;
    sFilterConfig.FilterFIFOAssignment = CAN_FilterFIFO0;
    sFilterConfig.FilterActivation = CAN_FILTER_ENABLE;
    sFilterConfig.FilterBank = 0;
		sFilterConfig.SlaveStartFilterBank = 13;

    // ### Configurate CAN 1 ###
    if(HAL_CAN_ConfigFilter(&hcan1, &sFilterConfig) != HAL_OK)
    {

        myErrorFlag.Can1.ConfigFilter = true;
        Error_Handler();
    }

    if(HAL_CAN_Start(&hcan1) != HAL_OK)
    {
        myErrorFlag.Can1.Start = true;
        Error_Handler();
    }

    if(HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING | CAN_IT_TX_MAILBOX_EMPTY) != HAL_OK)
    {
        myErrorFlag.Can1.Act_Notif = true;
        Error_Handler();
    }



    // ### Configurate CAN 2 ###
		sFilterConfig.FilterBank = 13;
    if(HAL_CAN_ConfigFilter(&hcan2, &sFilterConfig) != HAL_OK)
    {
        /* Filter configuration Error */
        myErrorFlag.Can2.ConfigFilter = true;
        Error_Handler();
    }

    if(HAL_CAN_Start(&hcan2) != HAL_OK)
    {
        myErrorFlag.Can2.Start = true;
        Error_Handler();
    }
    
    if(HAL_CAN_ActivateNotification(&hcan2, CAN_IT_RX_FIFO0_MSG_PENDING | CAN_IT_TX_MAILBOX_EMPTY | CAN_IT_RX_FIFO1_MSG_PENDING) != HAL_OK)
    {
        myErrorFlag.Can2.Act_Notif = true;
        Error_Handler();
    }

}

void HAL_CAN_TxMailbox0CompleteCallback(CAN_HandleTypeDef *hcan)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(hcan);
    uint32_t p1TxMailbox;
    int i;
    for(i= 0; i<CAN_TX_BUFFER_SIZE; i++)
    {
        if(Canbuffer[i].Tr == 1)
        {
            if(Canbuffer[i].hcan == hcan)
            {
                if(HAL_CAN_AddTxMessage(Canbuffer[i].hcan, &Canbuffer[i].pHeader, Canbuffer[i].data, &p1TxMailbox) == HAL_OK)
                {
                    Canbuffer[i].Tr = 0;
                    break;
                }
            }
        }

    }


}
void HAL_CAN_TxMailbox1CompleteCallback(CAN_HandleTypeDef *hcan)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(hcan);
    uint32_t p1TxMailbox;
    int i;
    for(i= 0; i<CAN_TX_BUFFER_SIZE; i++)
    {
        if(Canbuffer[i].Tr == 1)
        {
            if(Canbuffer[i].hcan == hcan)
            {
                if(HAL_CAN_AddTxMessage(Canbuffer[i].hcan, &Canbuffer[i].pHeader, Canbuffer[i].data, &p1TxMailbox) == HAL_OK)
                {
                    Canbuffer[i].Tr = 0;
                    break;
                }
            }
        }

    }

}

void HAL_CAN_TxMailbox2CompleteCallback(CAN_HandleTypeDef *hcan)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(hcan);
    uint32_t p1TxMailbox;
    int i;
    for(i= 0; i<CAN_TX_BUFFER_SIZE; i++)
    {
        if(Canbuffer[i].Tr == 1)
        {
            if(Canbuffer[i].hcan == hcan)
            {
                if(HAL_CAN_AddTxMessage(Canbuffer[i].hcan, &Canbuffer[i].pHeader, Canbuffer[i].data, &p1TxMailbox) == HAL_OK)
                {
                    Canbuffer[i].Tr = 0;
                    break;
                }
            }
        }

    }

}




void CAN_SendMessage(CAN_HandleTypeDef *hcan,uint32_t ID,uint32_t DLC, uint8_t *data)
{
    uint32_t pTxMailbox;

    if(IS_CAN_STDID(ID))
    {
        pHeader.IDE = CAN_ID_STD;
        pHeader.StdId = ID;
    }
    else if (IS_CAN_EXTID(ID))
    {
        pHeader.IDE = CAN_ID_EXT;
        pHeader.ExtId = ID;
    }
    else
    {
        if (hcan == &hcan1) {
            myErrorFlag.Can1.Send.noProperId = true;
        }
        else if (hcan == &hcan2) {
            myErrorFlag.Can2.Send.noProperId = true;
        }
    }

    if (DLC <= 8)
    {
        pHeader.DLC = DLC;
    }
    else
    {
        if (hcan == &hcan1) {
            myErrorFlag.Can1.Send.noValidDLC = true;
        }
        else if (hcan == &hcan2) {
            myErrorFlag.Can2.Send.noValidDLC = true;
        }
    }

    if(HAL_CAN_GetTxMailboxesFreeLevel(hcan) != 0)// check mailboxes
    {
        HAL_CAN_AddTxMessage(hcan, &pHeader, data, &pTxMailbox);
    }
    else //store data
    {
        if(Canbuffer[indx].Tr == 1)
            indx++;
        if(indx >= (CAN_TX_BUFFER_SIZE -1) )
            indx = 0;

        Canbuffer[indx].hcan = hcan;
        Canbuffer[indx].pHeader = pHeader;
        for(int i = 0; i<8; i++)
        {
            Canbuffer[indx].data[i] = *data++;
        }
        Canbuffer[indx].Tr = 1;
    }
}



void CAN_GetMessage(CAN_HandleTypeDef *hcan) {
    CAN_RxHeaderTypeDef myRxHeader;
    uint8_t CAN_Rx_Buffer[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    HAL_CAN_GetRxMessage(hcan, CAN_FilterFIFO0, &myRxHeader, CAN_Rx_Buffer);
    uint32_t ID;
    if(hcan == &hcan1)
    {
			if(myRxHeader.StdId == 0)// if recieved message id is 0x343, add this message into queue
				{
					BaseType_t pxHigherPriorityTaskWoken = pdFALSE; 
					xQueueSendToBackFromISR( myQueue01Handle, (typedef_343h*)CAN_Rx_Buffer, &pxHigherPriorityTaskWoken );
				}
			else
			{
				
        if (myRxHeader.IDE == CAN_ID_STD)
        {
            CAN_SendMessage(&hcan2,myRxHeader.StdId,myRxHeader.DLC, CAN_Rx_Buffer);
            StoreCANID(myRxHeader.StdId, 1);
            ID = myRxHeader.StdId;
        }
        else if (myRxHeader.IDE == CAN_ID_EXT)
        {
            CAN_SendMessage(&hcan2,myRxHeader.ExtId,myRxHeader.DLC, CAN_Rx_Buffer);
            ID = myRxHeader.ExtId;
            StoreCANID(myRxHeader.ExtId, 1);
        }

        for(int i = 0; i<CAN1_Buffer_size; i++)
        {
            if(CAN_Bridge_MSG.CAN1_MSG[i].ID == ID || CAN_Bridge_MSG.CAN1_MSG[i].ID == 0x00)
            {
				CAN_Bridge_MSG.CAN1_MSG[i].DLC = myRxHeader.DLC;
                CAN_Bridge_MSG.CAN1_MSG[i].ID = ID;
                CAN_Bridge_MSG.CAN1_MSG[i].cnt++;
                for(int j = 0; j<8; j++)
                {
                    CAN_Bridge_MSG.CAN1_MSG[i].Data[j] = CAN_Rx_Buffer[j];
                }
                break;
            }

        }
			}

    }

    else if(hcan == &hcan2)
    {
				if(myRxHeader.StdId == 0x343)// if recieved message id is ShiftCommand_ID, add this message into queue
				{
					BaseType_t pxHigherPriorityTaskWoken = pdFALSE; 
					xQueueSendToBackFromISR( myQueue02Handle, CAN_Rx_Buffer, &pxHigherPriorityTaskWoken );
				}
				else if(myRxHeader.StdId == 0x191)// if recieved message id is ShiftCommand_ID, add this message into queue
				{
					BaseType_t pxHigherPriorityTaskWoken = pdFALSE;
					xQueueSendToBackFromISR( myQueue01Handle, CAN_Rx_Buffer, &pxHigherPriorityTaskWoken );
				}
				else
				{
					if (myRxHeader.IDE == CAN_ID_STD)
					{
							CAN_SendMessage(&hcan1,myRxHeader.StdId,myRxHeader.DLC, CAN_Rx_Buffer);
							ID = myRxHeader.StdId;
							StoreCANID(myRxHeader.StdId, 2);
					}
					else if (myRxHeader.IDE == CAN_ID_EXT)
					{
							CAN_SendMessage(&hcan1,myRxHeader.ExtId,myRxHeader.DLC, CAN_Rx_Buffer);
							ID = myRxHeader.ExtId;
							StoreCANID(myRxHeader.ExtId, 2);
					}


				}
				for(int i = 0; i<CAN2_Buffer_size; i++)
					{
							if(CAN_Bridge_MSG.CAN2_MSG[i].ID == ID || CAN_Bridge_MSG.CAN2_MSG[i].ID == 0x00)
							{
									CAN_Bridge_MSG.CAN2_MSG[i].DLC = myRxHeader.DLC;
									CAN_Bridge_MSG.CAN2_MSG[i].ID = ID;
									CAN_Bridge_MSG.CAN2_MSG[i].cnt++;
								
									for(int j = 0; j<8; j++)
									{
											CAN_Bridge_MSG.CAN2_MSG[i].Data[j] = CAN_Rx_Buffer[j];
									}
									break;
							}

					}

    }


}

uint32_t IDlist1[250],IDlist2[250];
uint8_t StoreCANID(uint32_t ID, uint8_t Port)
{
	static uint16_t index1=0,index2=0;
	if(Port == 1)
	{
		for(int i=0;i<250;i++)
		{
			if(IDlist1[i]==ID)
				return 0;
		}
		IDlist1[index1++] = ID;

	}
	if(Port == 2)
	{
		for(int i=0;i<250;i++)
		{
			if(IDlist2[i]==ID)
				return 0;
		}
		IDlist2[index2++] = ID;

	}


	return 1;
}

