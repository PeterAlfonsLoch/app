#pragma once

#define core_level 1

#define WINVER 0x0400

#define VC_EXTRALEAN



//vc6 retro compatibility

// throw()
#define NOTHROW
// throw(...) 
#define THROWS 

typedef long __time64_t;


typedef int socklen_t;

typedef unsigned long DWORD;
typedef unsigned long ULONG;
typedef long LONG;

typedef DWORD DWORD_PTR;
typedef ULONG ULONG_PTR;
typedef LONG LONG_PTR;

typedef int errno_t;
typedef unsigned int size_t;

class type_info;

typedef type_info std_type_info;

#define _SECURE_ATL 0


#define _TRUNCATE 0xffffffff
#define STRUNCATE 0xffffffff
