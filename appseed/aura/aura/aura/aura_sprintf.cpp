// sprintf.cpp

// based on:
// LIBCTINY - Matt Pietrek 2001
// MSDN Magazine, January 2001

// 08/12/06 (mv)

#include "framework.h"
#include <stdarg.h>

#define EOF     (-1)


int32_t sprintf_dup(char *buffer, const char *format, ...)
{
    int32_t retValue;
    va_list argptr;

    va_start(argptr, format);
    retValue = vsprintf_dup(buffer, format, argptr);
    va_end(argptr);

    return retValue;
}

int32_t snprintf_dup(char *dest, size_t n, const char *fmt, ...)
{
	n;

	va_list args;
	va_start(args, fmt);
	int32_t retValue = vsprintf_dup(dest, fmt, args);
	va_end(args);
	return retValue;
}

int32_t vsnprintf_dup(char *dest, size_t n, const char *fmt, va_list args)
{
	n;
	return vsprintf_dup(dest, fmt, args);
}

int32_t vsprintf_dup(char *dest, const char *fmt, va_list args)
{
   #ifdef WINDOWSEX
	int32_t retValue = wvsprintfA(dest, fmt, args);
   #elif defined(METROWIN)
	int32_t retValue = vsprintf(dest, fmt, args);
	#else
	int32_t retValue = vsprintf(dest, fmt, args);
	#endif
   return retValue;
}













int32_t swnprintf_dup(wchar_t *dest, size_t n, const wchar_t *fmt, ...)
{

	va_list args;
	va_start(args, fmt);
	int32_t retValue = vswprintf_dup(dest, n, fmt, args);
	va_end(args);
	return retValue;

}


int32_t vswprintf_dup(wchar_t *dest, size_t n, const wchar_t *fmt, va_list args)
{

#ifdef WINDOWSEX
	int32_t retValue = wvsprintfW(dest, fmt, args);
#elif defined(METROWIN)
   int32_t retValue = vswprintf_s(dest, n, fmt, args);
#else
	int32_t retValue = vswprintf(dest, n, fmt, args);
#endif
   return retValue;

}
