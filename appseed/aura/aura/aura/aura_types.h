#pragma once


typedef uint8_t      byte;
typedef uint8_t      uchar;
typedef uint32_t     dword;
typedef int          int_bool;


#ifdef __cplusplus
template < typename TARGET, typename SOURCE >
TARGET throw_cast(SOURCE src)
{
   return (TARGET) src;
}
#endif



#define WINBOOL int_bool











