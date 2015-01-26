//#include "framework.h"




id::id(int_ptr i)
{
   m_all ={};


   operator = (i);
}

id::id(uint_ptr ui)
{
   m_all ={};

   operator = ((int_ptr)ui);
}

#if defined(_LP64) || defined(_AMD64_)
id::id(int32_t i)
{
   m_all = {};

   operator = (i);
}

id::id(uint32_t ui)
{
   m_all ={};

   operator = ((int_ptr)ui);
}
#endif

id::id(const string & str)
{
   m_all ={};

   operator = (::aura::system::id((const char *)str));
}

id::id(const string_interface & str)
{
   m_all ={};

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


