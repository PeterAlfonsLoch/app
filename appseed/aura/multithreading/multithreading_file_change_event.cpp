#include "framework.h"


#ifdef WINDOWSEX

///  \brief		constructor with passed path to file
///  \param		path the file to watch
///  \param		watchsubtree if true, the function monitors the directory tree
///				rooted at the specified directory, if it is false,
///				it monitors only the specified directory
///  \param		filter filter conditions that satisfy a change notification wait
///				can take values described by enum filter
file_change_event::file_change_event(sp(::aura::application) papp, const char * path, bool watchsubtree, uint32_t filter) :
	event_base((int_ptr) ::FindFirstChangeNotificationW(::str::international::utf8_to_unicode(path), watchsubtree, filter) )
{
	if (item() == 0)
		throw runtime_error(papp, "file_change_event: failed to create event");
}

///  \brief		destructor
file_change_event::~file_change_event()
{
}


bool file_change_event::lock(const duration & durationTimeout)
{
   uint32_t dwRet = ::WaitForSingleObject((HANDLE) item(), durationTimeout.os_lock_duration());
   if (dwRet == WAIT_OBJECT_0 || dwRet == WAIT_ABANDONED)
      return true;
   else
      return false;
}

bool file_change_event::unlock()
{
   next();
   return true;
}

///  \brief		waits for an file notification forever
void file_change_event::wait ()
{
	if ( ::WaitForSingleObject((HANDLE) item(), INFINITE) != WAIT_OBJECT_0 )
		throw runtime_error(get_app(), "::core::pal::file_change_event::wait: failure");
}

///  \brief		waits for an file notification for a specified time
///  \param		duration time period to wait for an file notification
///  \return	waiting action result as wait_result
wait_result file_change_event::wait (const duration & duration)
{
   return wait_result((uint32_t) ::WaitForSingleObject((HANDLE)item(),duration.os_lock_duration()));
}

///  \brief		requests that the operating system signal a change
///				notification handle the next time it detects an appropriate
///				change
bool file_change_event::next ()
{ 
   return ::FindNextChangeNotification((HANDLE)item()) != FALSE;

}

///  \brief		stops change notification handle monitoring
void file_change_event::close ()
{
   ::FindCloseChangeNotification((HANDLE)item());
}




#endif


