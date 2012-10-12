// sprintf.cpp

// based on:
// LIBCTINY - Matt Pietrek 2001
// MSDN Magazine, January 2001

// 08/12/06 (mv)

#include "framework.h"

#define EOF     (-1)

// Force the linker to include USER32.LIB
#pragma comment(linker, "/defaultlib:user32.lib")

int sprintf_dup(char *buffer, const char *format, ...)
{
    int retValue;
    va_list argptr;

    va_start(argptr, format);
    retValue = vsprintf_dup(buffer, format, argptr);
    va_end(argptr);

    return retValue;
}

int snprintf_dup(char *dest, size_t n, const char *fmt, ...)
{
	n;

	va_list args;
	va_start(args, fmt);
	int retValue = vsprintf_dup(dest, fmt, args);
	va_end(args);
	return retValue;
}

int vsnprintf_dup(char *dest, size_t n, const char *fmt, va_list args)
{
	n;
	return vsprintf_dup(dest, fmt, args);
}

int vsprintf_dup(char *dest, const char *fmt, va_list args)
{
   #ifdef WINDOWSEX
	int retValue = wvsprintfA(dest, fmt, args);
   #elif defined(MERDE_WINDOWS)
	int retValue = vsprintf(dest, fmt, args);
	#else
	int retValue = vsprintf(dest, fmt, args);
	#endif
   return retValue;
}













int swnprintf_dup(wchar_t *dest, size_t n, const wchar_t *fmt, ...)
{

	va_list args;
	va_start(args, fmt);
	int retValue = vswprintf_dup(dest, n, fmt, args);
	va_end(args);
	return retValue;

}


int vswprintf_dup(wchar_t *dest, size_t n, const wchar_t *fmt, va_list args)
{

#ifdef WINDOWSEX
	int retValue = wvsprintfW(dest, fmt, args);
#elif defined(MERDE_WINDOWS)
   int retValue = vswprintf_s(dest, n, fmt, args);
#else
	int retValue = vswprintf(dest, n, fmt, args);
#endif
   return retValue;

}
