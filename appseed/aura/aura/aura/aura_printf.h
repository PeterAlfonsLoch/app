// printf.cpp

// based on:
// LIBCTINY - Matt Pietrek 2001
// MSDN Magazine, January 2001

// 08/12/06 (mv)

#pragma once

CLASS_DECL_AURA int32_t printf_dup(const char *format, ...);
CLASS_DECL_AURA int32_t wprintf_dup(const wchar_t *format, ...);
CLASS_DECL_AURA int32_t vprintf_dup(const char *format, va_list args);
CLASS_DECL_AURA int32_t vwprintf_dup(const wchar_t *format, va_list args);

#ifdef APPLEOS
int32_t ecvt_r(double, int, int *__restrict, int *__restrict, char * sz, size_t size); /* LEGACY */
int32_t fcvt_r(double, int, int *__restrict, int *__restrict, char * sz, size_t size); /* LEGACY */
#endif



