#include "framework.h"


simple_exception::simple_exception()
{
}

simple_exception::simple_exception(const char * pszMessage)
{

   m_strMessage = pszMessage;

}

simple_exception::~simple_exception()
{

}

vsstring simple_exception::get_error_message()
{

   return m_strMessage;

}
