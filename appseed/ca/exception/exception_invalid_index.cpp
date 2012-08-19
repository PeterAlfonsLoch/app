#include "framework.h"


invalid_index_exception::invalid_index_exception()
   : invalid_argument_exception()
{

}

invalid_index_exception::invalid_index_exception(const char * pszMessage)
   : invalid_argument_exception(pszMessage)
{

}

invalid_index_exception::invalid_index_exception(bool bAutoDelete, UINT nResourceID)
   : invalid_argument_exception(bAutoDelete) 
{
   m_nResourceID = nResourceID; 
}

invalid_index_exception::~invalid_index_exception()
{

}
