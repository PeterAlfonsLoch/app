#pragma once

#if defined(LINUX)

inline string string::format_spec::format(int i)
{

   return gen::str::itoa(i);

}


inline string string::format_spec::format(const char * psz)
{

   return psz;

}

#endif