#include "framework.h"




id::id(int_ptr i)
{
   operator = (::base::system::id(i));
}

id::id(uint_ptr ui)
{
   operator = (::base::system::id(ui));
}

#if defined(_LP64) || defined(_AMD64_)
id::id(int32_t i)
{
   operator = (::base::system::id(i));
}

id::id(uint32_t ui)
{
   operator = (::base::system::id(ui));
}
#endif

id::id(const string & str)
{
   operator = (::base::system::id((const char * ) str));
}

id::id(const string_interface & str)
{
   operator = (::base::system::id(string(str)));
}

id & id::operator = (const char * psz)
{
   operator = (::base::system::id(psz));
   return *this;
}

id & id::operator = (const string & str)
{
   operator = (::base::system::id(str));
   return *this;
}

id & id::operator = (const string_interface & str)
{
   operator = (::base::system::id(string(str)));
   return *this;
}


