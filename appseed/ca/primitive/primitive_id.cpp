#include "framework.h"



id::id(const char * psz)
{
   operator = (::radix::system::id(psz));
}

id::id(int_ptr i)
{
   operator = (::radix::system::id(i));
}

id::id(uint_ptr ui)
{
   operator = (::radix::system::id(ui));
}

#if defined(_LP64) || defined(_AMD64_)
id::id(int32_t i)
{
   operator = (::radix::system::id(i));
}

id::id(unsigned int32_t ui)
{
   operator = (::radix::system::id(ui));
}
#endif

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


