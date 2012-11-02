#include "framework.h"


wait_result::wait_result(unsigned long value, count objectCount)
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
			m_iWaitResult = Abandon0-((int)value-WAIT_ABANDONED_0);
		else if (/*value>=WAIT_OBJECT_0 &&*/ value<=(WAIT_OBJECT_0 + objectCount - 1))
			m_iWaitResult = Event0+((int)value-WAIT_OBJECT_0);
		break;
	}		

}