#include "framework.h"


invalid_argument_exception::invalid_argument_exception()
   : simple_exception()
{

}

invalid_argument_exception::invalid_argument_exception(const char * pszMessage)
   : simple_exception(pszMessage)
{

}

invalid_argument_exception::invalid_argument_exception(BOOL bAutoDelete, UINT nResourceID)
   : simple_exception(bAutoDelete) 
{
   m_nResourceID = nResourceID; 
}

invalid_argument_exception::~invalid_argument_exception()
{

}
