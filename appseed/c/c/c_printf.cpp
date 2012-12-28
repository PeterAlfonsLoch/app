// printf.cpp

// based on:
// LIBCTINY - Matt Pietrek 2001
// MSDN Magazine, January 2001

// 08/12/06 (mv)

#include "framework.h"
#include <stdarg.h>
#include <wchar.h>

// Force the linker to include USER32.LIB
#pragma comment(linker, "/defaultlib:user32.lib")


int32_t printf_dup(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    int32_t ret = vprintf_dup(format, args);
    va_end(args);

	return ret;
}

int32_t wprintf_dup(const wchar_t *format, ...)
{
	va_list args;
	va_start(args, format);
	int32_t ret = vwprintf_dup(format, args);
	va_end(args);

	return ret;
}



int32_t vprintf_dup(const char *format, va_list args)
{

#if defined(LINUX) || defined(MACOS)

    return vprintf(format, args);

#elif defined(METROWIN)

    return vprintf(format, args);

#else

	char szBuff[1024];

	int32_t retValue = wvsprintfA(szBuff, format, args);

	fwrite_dup(szBuff, retValue, 1, stdout_dup);

	return retValue;

#endif

}


int32_t vwprintf_dup(const wchar_t *format, va_list args)
{

#if defined(LINUX) || defined(MACOS)

    return vwprintf(format, args);

#elif defined(METROWIN)

    return vwprintf(format, args);

#else
	wchar_t buf[1024];
	int32_t ret = wvsprintfW(buf, format, args);

	char ansibuf[1024];
	WideCharToMultiByte(CP_ACP, 0, buf, -1, ansibuf, sizeof(ansibuf), 0, 0);
	fwrite_dup(ansibuf, ret, 1, stdout_dup);

	return ret;

#endif

}
