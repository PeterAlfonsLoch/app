#pragma once


#define __uint8_t      uint8_t
#define __uint64_t     uint64_t
#define __uint32_t     uint32_t
#define __uint16_t     uint16_t
#define __int64_t      int64_t
#define __int32_t      int32_t
#define __int16_t      int16_t


typedef uint8_t      __uint8_t;
typedef uint64_t     __uint64_t;
typedef uint32_t     __uint32_t;
typedef uint16_t     __uint16_t;
typedef int64_t      __int64_t;
typedef int32_t      __int32_t;
typedef int16_t      __int16_t;


#define byte            __uint8_t


#ifdef __cplusplus
template < typename TARGET, typename SOURCE >
TARGET throw_cast(SOURCE src)
{
   return (TARGET) src;
}
#endif


typedef DWORD dword;


