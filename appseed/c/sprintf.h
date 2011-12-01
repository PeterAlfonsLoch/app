#pragma once



CLASS_DECL_c int sprintf_dup(char *buffer, const char *format, ...);
CLASS_DECL_c int _snprintf_dup(char *dest, size_t n, const char *fmt, ...);
CLASS_DECL_c int vsnprintf_dup(char *dest, size_t n, const char *fmt, va_list args);
CLASS_DECL_c int vsprintf_dup(char *dest, const char *fmt, va_list args);

CLASS_DECL_c int swnprintf_dup(wchar_t *dest, size_t n, const wchar_t *fmt, ...);
CLASS_DECL_c int vswprintf_dup(wchar_t *dest, size_t n, const wchar_t *fmt, va_list args);
