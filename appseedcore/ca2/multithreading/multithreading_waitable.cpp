/**
* \brief	Platform independent waitables
* \author	Thomas Hoefer
*/
// from sector8J on 2011-08-09
#include "StdAfx.h"




///  \brief		destructor
waitable::~waitable()
{

}

///  \brief		abstract function to initialize a waiting action without a timeout
void waitable::wait()
{
   wait(duration::infinite());
}

	///  \brief		abstract function to initialize a waiting action with a timeout
	///  \param		duration time period to wait for item
	///  \return	waiting action result as wait_result
//	virtual wait_result wait(const duration & duration ) = 0;




// forward declaration
//class event_base;

/// This class represents a virtual interface for a callback method for WaitableItems in a
/// event_collection.

waitable_callback::~waitable_callback()
{
}

	/// called on signalization of a event_base
	/// \param signaling event_base
//	virtual void callback(const event_base& waitItem) = 0;
//};


///  \brief		pauses waitable for specified time
///  \param		duration sleeping time of waitable
/*CLASS_DECL_ca void sleep(const duration & duration)
{
   Sleep((DWORD)duration.total_milliseconds());
}*/

CLASS_DECL_ca void sleep(const duration & duration)
{ 
   ::Sleep(static_cast<DWORD>(duration.total_milliseconds())); 
}
