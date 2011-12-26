#include "StdAfx.h"



id::id(const char * psz)
{
   operator = (::radix::system::id(psz));
}

#ifdef _AMD64_
id::id(int i)
{
   operator = (::radix::system::id(i));
}
#endif

id::id(unsigned int user)
{
   operator = (::radix::system::id((index)user));
}

id::id(index i)
{
   operator = (::radix::system::id(i));
}

id::id(const string & str)
{
   operator = (::radix::system::id((const char * ) str));
}

id::id(const string_interface & str)
{
   operator = (::radix::system::id(string(str)));
}

id & id::operator = (const char * psz)
{
   operator = (::radix::system::id(psz));
   return *this;
}

id & id::operator = (const string & str)
{
   operator = (::radix::system::id(str));
   return *this;
}

id & id::operator = (const string_interface & str)
{
   operator = (::radix::system::id(string(str)));
   return *this;
}


string id::str()
{
   if(m_chType == IDTYPE_TYPE_TEXT)
      return m_psz;
   else if(m_chType == IDTYPE_TYPE_NUMBER)
   {
      string str;
      str.Format("%d", m_ui);
      return str;
   }
   else
      return "";
 }
