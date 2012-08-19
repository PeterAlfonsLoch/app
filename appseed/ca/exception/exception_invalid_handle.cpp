#include "framework.h"


invalid_handle_exception::invalid_handle_exception()
   : os_exception()
{

}

invalid_handle_exception::invalid_handle_exception(const char * pszMessage)
   : os_exception(pszMessage)
{

}

invalid_handle_exception::invalid_handle_exception(bool bAutoDelete, UINT nResourceID)
   : os_exception(bAutoDelete) 
{
   m_nResourceID = nResourceID; 
}

invalid_handle_exception::~invalid_handle_exception()
{

}
