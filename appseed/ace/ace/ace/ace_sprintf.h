#pragma once



CLASS_DECL_ACE int32_t sprintf_dup(char *buffer, const char *format, ...);
CLASS_DECL_ACE int32_t _snprintf_dup(char *dest, size_t n, const char *fmt, ...);
CLASS_DECL_ACE int32_t vsnprintf_dup(char *dest, size_t n, const char *fmt, va_list args);
CLASS_DECL_ACE int32_t vsprintf_dup(char *dest, const char *fmt, va_list args);

CLASS_DECL_ACE int32_t swnprintf_dup(unichar *dest, size_t n, const unichar *fmt, ...);
CLASS_DECL_ACE int32_t vswprintf_dup(unichar *dest, size_t n, const unichar *fmt, va_list args);
