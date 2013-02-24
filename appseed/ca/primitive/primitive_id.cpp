#include "framework.h"



id::id(const char * psz)
{
   operator = (::ca::system::id(psz));
}

id::id(int_ptr i)
{
   operator = (::ca::system::id(i));
}

id::id(uint_ptr ui)
{
   operator = (::ca::system::id(ui));
}

#if defined(_LP64) || defined(_AMD64_)
id::id(int32_t i)
{
   operator = (::ca::system::id(i));
}

id::id(uint32_t ui)
{
   operator = (::ca::system::id(ui));
}
#endif

id::id(const string & str)
{
   operator = (::ca::system::id((const char * ) str));
}

id::id(const string_interface & str)
{
   operator = (::ca::system::id(string(str)));
}

id & id::operator = (const char * psz)
{
   operator = (::ca::system::id(psz));
   return *this;
}

id & id::operator = (const string & str)
{
   operator = (::ca::system::id(str));
   return *this;
}

id & id::operator = (const string_interface & str)
{
   operator = (::ca::system::id(string(str)));
   return *this;
}


