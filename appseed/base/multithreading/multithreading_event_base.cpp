/**
* \brief	Platform independent waitables (windows version)
* \author	Thomas Hoefer
*/
#include "framework.h"


event_base::event_base(int_ptr item)
   : m_object(item), m_bOwn(true)
{

}

event_base::~event_base()
{
#ifdef WINDOWS
   if(m_bOwn && (HANDLE)m_object != INVALID_HANDLE_VALUE && m_object != 0)
		::CloseHandle((HANDLE) m_object);
#endif
};


void event_base::set_item(int_ptr item)
{

#ifdef WINDOWS
   if(m_bOwn && (HANDLE)m_object != INVALID_HANDLE_VALUE && m_object != 0)
      ::CloseHandle((HANDLE) m_object);
#endif

   m_object = item;
	m_bOwn = true;

}

void event_base::release_ownership()
{
   m_bOwn = false;
}

int_ptr event_base::item() const
{
   return m_object;
}

void * event_base::get_os_data() const
{
   return (void *) m_object;
}


void event_base::init_wait ()
{
}

void event_base::exit_wait ()
{
}

