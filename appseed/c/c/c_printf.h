// printf.cpp

// based on:
// LIBCTINY - Matt Pietrek 2001
// MSDN Magazine, January 2001

// 08/12/06 (mv)

#pragma once

CLASS_DECL_c int32_t printf_dup(const char *format, ...);
CLASS_DECL_c int32_t wprintf_dup(const wchar_t *format, ...);
CLASS_DECL_c int32_t vprintf_dup(const char *format, va_list args);
CLASS_DECL_c int32_t vwprintf_dup(const wchar_t *format, va_list args);

