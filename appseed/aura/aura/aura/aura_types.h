#pragma once


typedef unsigned char      byte;
typedef unsigned char      uchar;
typedef unsigned int       dword;
typedef int                int_bool;


#ifdef __cplusplus
template < typename TARGET, typename SOURCE >
TARGET throw_cast(SOURCE src)
{
   return (TARGET) src;
}
#endif



#define WINBOOL int_bool

