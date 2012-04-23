#include "StdAfx.h"



id::id(const char * psz)
{
   operator = (::radix::system::id(psz));
}

id::id(int i)
{
   operator = (::radix::system::id(i));
}

id::id(unsigned int ui)
{
   operator = (::radix::system::id(ui));
}

id::id(int64_t i)
{
   operator = (::radix::system::id(i));
}

id::id(uint64_t ui)
{
   operator = (::radix::system::id(ui));
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


