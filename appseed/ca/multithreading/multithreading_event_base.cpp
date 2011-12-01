/**
* \brief	Platform independent waitables (windows version)
* \author	Thomas Hoefer
*/
#include "StdAfx.h"


///  \brief		constructor with passed handle
///  \param		item handle of the item (default: INVALID_HANDLE_VALUE)
event_base::event_base( HANDLE item)
   : m_object(item), m_bOwn(true)
{
}

///  \brief		destructor
event_base::~event_base()
{
	if ( m_bOwn && m_object != INVALID_HANDLE_VALUE && m_object != 0 )
		::CloseHandle(m_object);
};


///  \brief		handle setter
///  \param     item handle to set
void event_base::set_item( HANDLE item )
{
	if ( m_bOwn && m_object != INVALID_HANDLE_VALUE && m_object != 0 )
		::CloseHandle(m_object);
	m_object = item;
	m_bOwn = true;
}

///  \brief		resets ownership of the waitable item
void event_base::release_ownership()
{ 
   m_bOwn = false; 
}

///  \brief		handle getter
///  \return    item handle
HANDLE event_base::item() const
{ 
   return m_object; 
}

HANDLE event_base::get_os_data() const
{ 
   return m_object; 
}

void event_base::init_wait ()
{
}

void event_base::exit_wait ()
{
}

