#include "framework.h"


os_exception::os_exception()
   : simple_exception()
{
   m_nResourceID = 0; 
}

os_exception::os_exception(const char * pszMessage)
   : simple_exception(pszMessage)
{
   m_nResourceID = 0; 
}

os_exception::os_exception(bool bAutoDelete)
   : simple_exception(bAutoDelete) 
{
   m_nResourceID = 0; 
}


os_exception::os_exception(bool bAutoDelete, UINT nResourceID)
   : simple_exception(bAutoDelete) 
{
   m_nResourceID = nResourceID; 
}

os_exception::~os_exception()
{

}
