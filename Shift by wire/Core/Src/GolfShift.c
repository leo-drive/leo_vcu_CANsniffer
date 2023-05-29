
#include "GolfShift.h"
#include "stdint.h"




uint8_t ShiftControl(uint8_t CurrentShift, uint8_t DesiredShift, uint8_t *SwitchMove, uint8_t *SwitchRelated)
{
	static uint32_t cnt = 0;
	
	if(CurrentShift > 5 || DesiredShift > 5 || DesiredShift <= 1)
		return InvalidShift;
	
	
	if(*SwitchMove != 180)
	{
		return Intervention;
	}
	
	if(CurrentShift == DesiredShift)
	{
		cnt = 0;
		return NoChange;
	}
	
	
	if(cnt++ > 100)
	{
		return TimeoutError;
	}
	
		switch (CurrentShift)
		{
			case P:
				switch (DesiredShift)
        {
					case P:
						break;
        	case R:
						*SwitchMove		 = 105;
						*SwitchRelated = 98;
        		break;
        	case N:
						*SwitchMove		 = 105;
						*SwitchRelated = 98;
        		break;
					case D:
						*SwitchMove		 = 150;
						*SwitchRelated = 82;
						break;
					case S:
						*SwitchMove		 = 150;
						*SwitchRelated = 82;
						break;
        	default:
        		break;
        }
				break;
			case R:
				switch (DesiredShift)
        {
        	case P:
        		break;
					case R:
						break;
        	case N:
						*SwitchMove		 = 150;
						*SwitchRelated = 98;
        		break;
					case D:
						*SwitchMove		 = 150;
						*SwitchRelated = 98;
						break;
					case S:
						*SwitchMove		 = 150;
						*SwitchRelated = 98;
						break;
        	default:
        		break;
        }
				break;
			case N:
				switch (DesiredShift)
        {
        	case P:
        		break;
        	case R:
						*SwitchMove		 = 105;
						*SwitchRelated = 114;
        		break;
					case N:
						break;
					case D:
						*SwitchMove		 = 150;
						*SwitchRelated = 82;
						break;
					case S:
						*SwitchMove		 = 150;
						*SwitchRelated = 82;
						break;
        	default:
        		break;
        }
				break;
			case D:
				switch (DesiredShift)
        {
					case P:
						break;
        	case R:
						*SwitchMove		 = 105;
						*SwitchRelated = 98;
        		break;
        	case N:
						*SwitchMove		 = 105;
						*SwitchRelated = 98;
        		break;
					case D:
						break;
					case S:
						*SwitchMove		 = 150;
						*SwitchRelated = 194;
						break;
        	default:
        		break;
        }
				break;
			case S:
				switch (DesiredShift)
        {
					case P:
						break;
        	case R:
						*SwitchMove		 = 105;
						*SwitchRelated = 98;
        		break;
        	case N:
						*SwitchMove		 = 105;
						*SwitchRelated = 98;
        		break;
					case D:
						break;
					case S:
						break;
        	default:
        		break;
        }
				break;
			default:
				break;
		}

	return ChangeRequied;
}


