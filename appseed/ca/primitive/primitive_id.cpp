#include "framework.h"



id::id(const char * psz)
{
   operator = (::gen::system::id(psz));
}

id::id(int_ptr i)
{
   operator = (::gen::system::id(i));
}

id::id(uint_ptr ui)
{
   operator = (::gen::system::id(ui));
}

#if defined(_LP64) || defined(_AMD64_)
id::id(int32_t i)
{
   operator = (::gen::system::id(i));
}

id::id(uint32_t ui)
{
   operator = (::gen::system::id(ui));
}
#endif

id::id(const string & str)
{
   operator = (::gen::system::id((const char * ) str));
}

id::id(const string_interface & str)
{
   operator = (::gen::system::id(string(str)));
}

id & id::operator = (const char * psz)
{
   operator = (::gen::system::id(psz));
   return *this;
}

id & id::operator = (const string & str)
{
   operator = (::gen::system::id(str));
   return *this;
}

id & id::operator = (const string_interface & str)
{
   operator = (::gen::system::id(string(str)));
   return *this;
}


