/**
* \brief	Platform independent waitables (windows version)
* \author	Thomas Hoefer
*/
#include "framework.h"


///  \brief		constructor with passed handle
///  \param		item handle of the item (default: INVALID_HANDLE_VALUE)
#ifdef WINDOWS
event_base::event_base(HANDLE item)
   : m_object(item), m_bOwn(true)
{
}
#else
event_base::event_base(int_ptr item)
   : m_object(item), m_bOwn(true)
{
}
#endif

///  \brief		destructor
event_base::~event_base()
{
#ifdef WINDOWS
	if ( m_bOwn && m_object != INVALID_HANDLE_VALUE && m_object != 0 )
		::CloseHandle(m_object);
#endif
};


///  \brief		handle setter
///  \param     item handle to set
#ifdef WINDOWS
void event_base::set_item(HANDLE item)
{
	if ( m_bOwn && m_object != INVALID_HANDLE_VALUE && m_object != 0 )
		::CloseHandle(m_object);
	m_object = item;
	m_bOwn = true;
}
#else
void event_base::set_item(int_ptr item)
{
	m_object = item;
	m_bOwn = true;
}
#endif

///  \brief		resets ownership of the waitable item
void event_base::release_ownership()
{
   m_bOwn = false;
}

///  \brief		handle getter
///  \return    item handle
#ifdef WINDOWS
HANDLE event_base::item() const
{
   return m_object;
}
#else
int_ptr event_base::item() const
{
   return m_object;
}
#endif

int_ptr event_base::get_os_data() const
{
   return (int_ptr) m_object;
}


void event_base::init_wait ()
{
}

void event_base::exit_wait ()
{
}

