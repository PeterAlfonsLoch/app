#pragma once


#define byte            uint8_t
#define uchar           unsigned char


#ifdef __cplusplus
template < typename TARGET, typename SOURCE >
TARGET throw_cast(SOURCE src)
{
   return (TARGET) src;
}
#endif


typedef uint32_t dword;


