// sprintf.cpp

// based on:
// LIBCTINY - Matt Pietrek 2001
// MSDN Magazine, January 2001

// 08/12/06 (mv)

//#include "framework.h"
//#include <stdarg.h>

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
	UNREFERENCED_PARAMETER(n);

	va_list args;
	va_start(args, fmt);
	int32_t retValue = vsprintf_dup(dest, fmt, args);
	va_end(args);
	return retValue;
}

int32_t vsnprintf_dup(char *dest, size_t n, const char *fmt, va_list args)
{
	UNREFERENCED_PARAMETER(n);
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













int32_t swnprintf_dup(unichar *dest, size_t n, const unichar *fmt, ...)
{

	va_list args;
	va_start(args, fmt);
	int32_t retValue = vswprintf_dup(dest, n, fmt, args);
	va_end(args);
	return retValue;

}


int32_t vswprintf_dup(unichar *dest, size_t n, const unichar *fmt, va_list args)
{

#ifdef WINDOWSEX
	int32_t retValue = wvsprintfW(dest, fmt, args);
#elif defined(METROWIN)
   int32_t retValue = vswprintf_s(dest, n, fmt, args);
#elif defined(APPLEOS) || defined LINUX
   unichar32 * vdest = (unichar32 *) memory_alloc(n * sizeof(unichar32));
   unichar32 * v = utf16_to_utf32(fmt);
   int32_t retValue = vswprintf(vdest, n, v, args);
   memory_free(v);
   utf32_to_utf16(dest, vdest, n);
   memory_free(vdest);
   return retValue;
#else
	int32_t retValue = vswprintf(dest, n, fmt, args);
#endif
   return retValue;

}
