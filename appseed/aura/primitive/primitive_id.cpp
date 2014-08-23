#include "framework.h"




id::id(int_ptr i)
{
   operator = (::aura::system::id(i));
}

id::id(uint_ptr ui)
{
   operator = (::aura::system::id(ui));
}

#if defined(_LP64) || defined(_AMD64_)
id::id(int32_t i)
{
   operator = (::aura::system::id(i));
}

id::id(uint32_t ui)
{
   operator = (::aura::system::id(ui));
}
#endif

id::id(const string & str)
{
   operator = (::aura::system::id((const char * ) str));
}

id::id(const string_interface & str)
{
   operator = (::aura::system::id(string(str)));
}

id & id::operator = (const char * psz)
{
   operator = (::aura::system::id(psz));
   return *this;
}

id & id::operator = (const string & str)
{
   operator = (::aura::system::id(str));
   return *this;
}

id & id::operator = (const string_interface & str)
{
   operator = (::aura::system::id(string(str)));
   return *this;
}


