// printf.cpp

// based on:
// LIBCTINY - Matt Pietrek 2001
// MSDN Magazine, January 2001

// 08/12/06 (mv)

#include "framework.h"
#include <wchar.h>
#include <stdarg.h>



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

#if defined(LINUX) || defined(APPLEOS) || defined(ANDROID) || defined(SOLARIS)

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

#if defined(LINUX) || defined(APPLEOS) || defined(ANDROID) || defined(SOLARIS)

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


#ifdef APPLEOS

mutex * g_pmutexCvt = NULL;

int32_t ecvt_r(double d, int i, int *__restrict pi1, int *__restrict pi2, char * sz, size_t size) /* LEGACY */
{

   synch_lock ml(g_pmutexCvt);

   char * psz = ecvt(d, i, pi1, pi2);

   if(psz == NULL)
      return -1;

   if(strlen(psz) > (size - 1))
      return -1;

   strcpy(sz, psz);

   return 0;

}

int32_t fcvt_r(double d, int i, int *__restrict pi1, int *__restrict pi2, char * sz, size_t size) /* LEGACY */
{

   synch_lock ml(g_pmutexCvt);

   char * psz = fcvt(d, i, pi1, pi2);

   if(psz == NULL)
      return -1;

   if(strlen(psz) > (size - 1))
      return -1;

   strcpy(sz, psz);

   return 0;

}

#endif
