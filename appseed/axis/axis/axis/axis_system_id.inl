#pragma once


namespace axis
{


   inline id system::id(const std_type_info & info)
   {
#ifdef WINDOWS
      return (*s_pidspace)(info.name());
#else
      return (*s_pidspace)(info.name());
#endif
   }

   inline id system::id(const char * psz)
   {
      return (*s_pidspace)(psz);
   }

   inline id system::id(const string & str)
   {
      return (*s_pidspace)(str);
   }

   inline id system::id(int64_t i)
   {
      return (*s_pidspace)(i);
   }

   inline id_space & system::id()
   {
      return (*s_pidspace);
   }


} //namespace axis



inline id::id(const char * psz)
{
   operator = (::axis::system::id(psz));
}

#if defined(_LP64) || defined(_AMD64_)
inline id & id::operator = (int32_t i)
{
   return operator = (::axis::system::id(::str::from(i)));
}
#endif

inline id & id::operator = (int_ptr i)
{
   return operator = (::axis::system::id(::str::from(i)));
}




