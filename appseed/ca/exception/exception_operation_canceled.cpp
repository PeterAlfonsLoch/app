#include "framework.h"


operation_canceled_exception::operation_canceled_exception()
   : simple_exception()
{
   m_nResourceID = 0; 
}

operation_canceled_exception::operation_canceled_exception(const char * pszMessage)
   : simple_exception(pszMessage)
{
   m_nResourceID = 0; 
}

operation_canceled_exception::operation_canceled_exception(bool bAutoDelete)
   : simple_exception(bAutoDelete) 
{
   m_nResourceID = 0; 
}

operation_canceled_exception::operation_canceled_exception(bool bAutoDelete, UINT nResourceID)
   : simple_exception(bAutoDelete) 
{
   m_nResourceID = nResourceID; 
}

operation_canceled_exception::~operation_canceled_exception()
{

}
