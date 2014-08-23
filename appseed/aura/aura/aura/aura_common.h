#pragma once


#if defined(LINUX) || defined(APPLEOS)
#include <wchar.h>
#endif


namespace aura
{


   inline void __cdecl memcpy_s(void *_S1, size_t _S1max, const void *_S2, size_t N)
   {
#ifdef WINDOWS
      C_RUNTIME_ERROR_CHECK(::memcpy_s(_S1, _S1max, _S2, N));
#else
      memcpy(_S1, _S2, N);
#endif
   }

   inline void __cdecl wmemcpy_s(wchar_t *_S1, size_t _N1, const wchar_t *_S2, size_t N)
   {
#ifdef WINDOWS
      C_RUNTIME_ERROR_CHECK(::wmemcpy_s(_S1, _N1, _S2, N));
#else
      memcpy(_S1, _S2, N * sizeof(wchar_t));
#endif
   }

   inline void __cdecl memmove_s(void *_S1, size_t _S1max, const void *_S2, size_t N)
   {
#ifdef WINDOWS
      C_RUNTIME_ERROR_CHECK(::memmove_s(_S1, _S1max, _S2, N));
#else
      memmove(_S1, _S2, N);
#endif
   }

   inline void __cdecl strcpy_s(char *_S1, size_t _S1max, const char *_S2)
   {
#ifdef WINDOWS
      C_RUNTIME_ERROR_CHECK(::strcpy_s(_S1, _S1max, _S2));
#else
      strcpy(_S1, _S2);
#endif
   }

   inline void __cdecl wcscpy_s(wchar_t *_S1, size_t _S1max, const wchar_t *_S2)
   {
#ifdef WINDOWS
      C_RUNTIME_ERROR_CHECK(::wcscpy_s(_S1, _S1max, _S2));
#else
      wcscpy_dup(_S1, _S2);
#endif
   }

   inline errno_t __cdecl strncpy_s(char *_Dest, size_t _SizeInChars, const char *_Source, size_t _Count)
   {
#ifdef WINDOWS
      return C_RUNTIME_ERROR_CHECK(::strncpy_s(_Dest, _SizeInChars, _Source,_Count));
#else
      strncpy(_Dest, _Source, _Count);
      return errno;
#endif
   }

   inline errno_t __cdecl wcsncpy_s(wchar_t *_Dest, size_t _SizeInChars, const wchar_t *_Source, size_t _Count)
   {
#ifdef WINDOWS
       return C_RUNTIME_ERROR_CHECK(::wcsncpy_s(_Dest, _SizeInChars, _Source,_Count));
#elif defined ANDROID || defined APPLE_IOS
      wcsncpy_dup(_Dest, _Source, _Count);
       return errno;
#else
       wcsncpy(_Dest, _Source, _Count);
       return errno;
#endif
   }

   inline void __cdecl strcat_s(char * _Dst, size_t _SizeInChars, const char * _Src)
   {
#ifdef WINDOWS
      C_RUNTIME_ERROR_CHECK(::strcat_s(_Dst, _SizeInChars, _Src));
#else
      strcat(_Dst, _Src);
#endif
   }

   inline void __cdecl wcscat_s(wchar_t * _Dst, size_t _SizeInChars, const wchar_t * _Src)
   {
#ifdef WINDOWS
      C_RUNTIME_ERROR_CHECK(::wcscat_s(_Dst, _SizeInChars, _Src));
#else
      wcscat_dup(_Dst, _Src);
#endif
   }

   inline void __cdecl strlwr_s(char * Str, size_t _SizeInChars)
   {
#ifdef WINDOWS
      C_RUNTIME_ERROR_CHECK(::_strlwr_s(Str, _SizeInChars));
#elif defined(ANDROID) || defined(APPLEOS)
      to_lower(Str);
#else
      strlwr(Str);
#endif
   }

   inline void __cdecl wcslwr_s(wchar_t * Str, size_t _SizeInChars)
   {
#ifdef WINDOWS
      C_RUNTIME_ERROR_CHECK(::_wcslwr_s(Str, _SizeInChars));
#else
      C_RUNTIME_ERROR_CHECK(::wcslwr_s_dup(Str, _SizeInChars));
#endif
   }

   inline void __cdecl strupr_s(char * Str, size_t _SizeInChars)
   {
#ifdef WINDOWS
      C_RUNTIME_ERROR_CHECK(::_strupr_s(Str, _SizeInChars));
#elif defined(ANDROID) || defined(APPLEOS)
      to_upper(Str);
#else
      strupr(Str);
#endif
   }

   inline void __cdecl wcsupr_s(wchar_t * Str, size_t _SizeInChars)
   {
#ifdef WINDOWS
      C_RUNTIME_ERROR_CHECK(::_wcsupr_s(Str, _SizeInChars));
#else
      C_RUNTIME_ERROR_CHECK(::wcsupr_s_dup(Str, _SizeInChars));
#endif
   }

   inline void __cdecl itoa_s(int32_t _Val, char *_Buf, size_t _SizeInChars, int32_t _Radix)
   {
#ifdef WINDOWS
      C_RUNTIME_ERROR_CHECK(::_itoa_s(_Val, _Buf, _SizeInChars, _Radix));
#else
      itoa_dup(_Buf, _Val, _Radix);
#endif
   }

   inline void __cdecl i64toa_s(int64_t _Val, char *_Buf, size_t _SizeInChars, int32_t _Radix)
   {
#ifdef WINDOWS
      C_RUNTIME_ERROR_CHECK(::_i64toa_s(_Val, _Buf, _SizeInChars, _Radix));
#else
      ltoa_dup(_Buf, _Val, _Radix);
#endif
   }

   inline void __cdecl i64tow_s(int64_t _Val, wchar_t *_Buf, size_t _SizeInChars, int32_t _Radix)
   {
#ifdef WINDOWS
      C_RUNTIME_ERROR_CHECK(::_i64tow_s(_Val, _Buf, _SizeInChars, _Radix));
#else
      ltow_dup(_Buf, _Val, _Radix);
#endif
   }

   inline void __cdecl ui64toa_s(uint64_t _Val, char *_Buf, size_t _SizeInChars, int32_t _Radix)
   {
#ifdef WINDOWS
      C_RUNTIME_ERROR_CHECK(::_ui64toa_s(_Val, _Buf, _SizeInChars, _Radix));
#else
     ltoa_dup(_Buf, _Val, _Radix);
#endif
   }

   inline void __cdecl ui64tow_s(uint64_t _Val, wchar_t *_Buf, size_t _SizeInChars, int32_t _Radix)
   {
#ifdef WINDOWS
      C_RUNTIME_ERROR_CHECK(::_ui64tow_s(_Val, _Buf, _SizeInChars, _Radix));
#else
      ltow_dup(_Buf, _Val, _Radix);
#endif
   }

   inline void __cdecl gcvt_s(char *_Buffer, size_t _SizeInChars, double _Value, int32_t _Ndec)
   {
#ifdef WINDOWS
      C_RUNTIME_ERROR_CHECK(::_gcvt_s(_Buffer, _SizeInChars, _Value, _Ndec));
#elif defined(ANDROID)
      //_gcvt(_Value, _Ndec, _Buffer);
#else
      gcvt(_Value, _Ndec, _Buffer);
#endif
   }

/*
   inline void __cdecl tsplitpath_s(
      const char *_Path,
      char *_Drive, size_t _Drive_len,
      char *_Dir, size_t _Dir_len,
      char *_Fname, size_t _Fname_len,
      char *_Ext, size_t _Ext_len)
   {
      C_RUNTIME_ERROR_CHECK(::_tsplitpath_s(_Path, _Drive, _Drive_len, _Dir, _Dir_len, _Fname, _Fname_len, _Ext, _Ext_len));
   }

   inline void __cdecl tmakepath_s(char *_Path, size_t _SizeInChars, const char *_Drive,
      const char *_Dir, const char *_Fname, const char *_Ext)
   {
      C_RUNTIME_ERROR_CHECK(::_tmakepath_s(_Path, _SizeInChars, _Drive, _Dir, _Fname, _Ext));
   }*/

   inline size_t __cdecl strnlen(const char *_Str, size_t _Maxsize)
   {
#ifdef WINDOWS
      return ::strnlen(_Str, _Maxsize);
#else
      return ::strlen(_Str);
#endif
   }

   inline size_t __cdecl wcsnlen(const wchar_t *_Wcs, size_t _Maxsize)
   {
#ifdef WINDOWS
      return ::wcsnlen(_Wcs, _Maxsize);
#else
      return ::wcslen_dup(_Wcs);
#endif
   }

   CLASS_DECL_AURA int32_t get_errno();
   CLASS_DECL_AURA void set_errno(int32_t _Value);



} // namespace core


