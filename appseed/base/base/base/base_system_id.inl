#pragma once


inline id ::base::system::id(const class var & var)
{
   return ::id((const char *) (class var &) var);
}

inline id ::base::system::id(const property & prop)
{
   return ::id((const string &) (property &) prop);
}


inline id ::base::system::id(const std_type_info & info)
{
#ifdef WINDOWS
   return (*s_pidspace)(info.name());
#else
   return (*s_pidspace)(info.name());
#endif
}

inline id ::base::system::id(const char * psz)
{
   return (*s_pidspace)(psz);
}

inline id ::base::system::id(const string & str)
{
   return (*s_pidspace)(str);
}

inline id ::base::system::id(int64_t i)
{
   return (*s_pidspace)(i);
}

inline id_space & ::base::system::id()
{
   return (*s_pidspace);
}



inline id::id(const char * psz)
{
   operator = (::base::system::id(psz));
}

#if defined(_LP64) || defined(_AMD64_)
inline id & id::operator = (int32_t i)
{
   return operator = (::base::system::id(::str::from(i)));
}
#endif

inline id & id::operator = (int_ptr i)
{
   return operator = (::base::system::id(::str::from(i)));
}




