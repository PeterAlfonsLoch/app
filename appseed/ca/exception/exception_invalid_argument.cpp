#include "framework.h"


invalid_argument_exception::invalid_argument_exception()
   : simple_exception()
{
   m_nResourceID = 0; 
}

invalid_argument_exception::invalid_argument_exception(const char * pszMessage)
   : simple_exception(pszMessage)
{
   m_nResourceID = 0; 
}

invalid_argument_exception::invalid_argument_exception(bool bAutoDelete)
   : simple_exception(bAutoDelete) 
{
   m_nResourceID = 0; 
}

invalid_argument_exception::invalid_argument_exception(bool bAutoDelete, UINT nResourceID)
   : simple_exception(bAutoDelete) 
{
   m_nResourceID = nResourceID; 
}

invalid_argument_exception::~invalid_argument_exception()
{

}
