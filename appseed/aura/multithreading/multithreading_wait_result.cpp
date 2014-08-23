#include "framework.h"


wait_result::wait_result(uint32_t value, ::count objectCount)
{
	switch ( value )
   {
	case WAIT_FAILED:	
		m_iWaitResult = Failure;
		break;

	case WAIT_TIMEOUT:	
		m_iWaitResult = Timeout;
		break;

	default:
		if (value>=WAIT_ABANDONED_0 && value<=(WAIT_ABANDONED_0 + objectCount - 1))
			m_iWaitResult = Abandon0-((int32_t)value-WAIT_ABANDONED_0);
		else if (/*value>=WAIT_OBJECT_0 &&*/ value<=(WAIT_OBJECT_0 + objectCount - 1))
			m_iWaitResult = Event0+((int32_t)value-WAIT_OBJECT_0);
		break;
	}		

}