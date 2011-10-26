#pragma once

#include "definition.h"
#include "exception.h"

#ifdef LINUX
#include <stdlib.h>
#endif



namespace _template
{

   inline errno_t AtlCrtErrorCheck(errno_t nError)
   {
      switch(nError)
      {
      case ENOMEM:
         AfxThrowMemoryException();
         break;
      case EINVAL:
      case ERANGE:
         AfxThrowInvalidArgException();
         break;
      case 0:
#if defined(_WINDOWS)
      case STRUNCATE:
#endif
         break;
      default:
         throw -1;
         break;
      }
      return nError;
   }

   /////////////////////////////////////////////////////////////////////////////
   // Secure (checked) CRT functions

   namespace checked
   {

   #if _SECURE_ATL

   #ifdef _AFX
   #define ATLMFC_CRT_ERRORCHECK(expr) AFX_CRT_ERRORCHECK(expr)
   #else
   #define ATLMFC_CRT_ERRORCHECK(expr) ATL_CRT_ERRORCHECK(expr)
   #endif

   inline void __cdecl memcpy_s(void *_S1, size_t _S1max, const void *_S2, size_t _N)
   {
#ifdef _WINDOWS
      ATLMFC_CRT_ERRORCHECK(::memcpy_s(_S1, _S1max, _S2, _N));
#else
      memcpy(_S1, _S2, _N);
#endif
   }

   inline void __cdecl wmemcpy_s(wchar_t *_S1, size_t _N1, const wchar_t *_S2, size_t _N)
   {
#ifdef _WINDOWS
      ATLMFC_CRT_ERRORCHECK(::wmemcpy_s(_S1, _N1, _S2, _N));
#else
      memcpy(_S1, _S2, _N * sizeof(wchar_t));
#endif
   }

   inline void __cdecl memmove_s(void *_S1, size_t _S1max, const void *_S2, size_t _N)
   {
#ifdef _WINDOWS
      ATLMFC_CRT_ERRORCHECK(::memmove_s(_S1, _S1max, _S2, _N));
#else
      memmove(_S1, _S2, _N);
#endif
   }

   inline void __cdecl strcpy_s(char *_S1, size_t _S1max, const char *_S2)
   {
#ifdef _WINDOWS
      ATLMFC_CRT_ERRORCHECK(::strcpy_s(_S1, _S1max, _S2));
#else
      strcpy(_S1, _S2);
#endif
   }

   inline void __cdecl wcscpy_s(wchar_t *_S1, size_t _S1max, const wchar_t *_S2)
   {
#ifdef _WINDOWS
      ATLMFC_CRT_ERRORCHECK(::wcscpy_s(_S1, _S1max, _S2));
#else
      wcscpy_dup(_S1, _S2);
#endif
   }

   inline errno_t __cdecl strncpy_s(char *_Dest, size_t _SizeInChars, const char *_Source, size_t _Count)
   {
#ifdef _WINDOWS
      return ATLMFC_CRT_ERRORCHECK(::strncpy_s(_Dest, _SizeInChars, _Source,_Count));
#else
      strncpy(_Dest, _Source, _Count);
#endif
   }

   inline errno_t __cdecl wcsncpy_s(wchar_t *_Dest, size_t _SizeInChars, const wchar_t *_Source, size_t _Count)
   {
#ifdef _WINDOWS
      return ATLMFC_CRT_ERRORCHECK(::wcsncpy_s(_Dest, _SizeInChars, _Source,_Count));
#else
      wcsncpy(_Dest, _Source, _Count);
#endif
   }

   inline void __cdecl strcat_s(char * _Dst, size_t _SizeInChars, const char * _Src)
   {
#ifdef _WINDOWS
      ATLMFC_CRT_ERRORCHECK(::strcat_s(_Dst, _SizeInChars, _Src));
#else
      strcat(_Dst, _Src);
#endif
   }

   inline void __cdecl wcscat_s(wchar_t * _Dst, size_t _SizeInChars, const wchar_t * _Src)
   {
#ifdef _WINDOWS
      ATLMFC_CRT_ERRORCHECK(::wcscat_s(_Dst, _SizeInChars, _Src));
#else
      wcscat_dup(_Dst, _Src);
#endif
   }

   inline void __cdecl strlwr_s(char * _Str, size_t _SizeInChars)
   {
#ifdef _WINDOWS
      ATLMFC_CRT_ERRORCHECK(::_strlwr_s(_Str, _SizeInChars));
#else
      strlwr(_Str);
#endif
   }

   inline void __cdecl wcslwr_s(wchar_t * _Str, size_t _SizeInChars)
   {
#ifdef _WINDOWS
      ATLMFC_CRT_ERRORCHECK(::_wcslwr_s(_Str, _SizeInChars));
#else
      wcslwr(_Str);
#endif
   }

   inline void __cdecl strupr_s(char * _Str, size_t _SizeInChars)
   {
#ifdef _WINDOWS
      ATLMFC_CRT_ERRORCHECK(::_strupr_s(_Str, _SizeInChars));
#else
      strupr(_Str);
#endif
   }

   inline void __cdecl wcsupr_s(wchar_t * _Str, size_t _SizeInChars)
   {
#ifdef _WINDOWS
      ATLMFC_CRT_ERRORCHECK(::_wcsupr_s(_Str, _SizeInChars));
#else
      wcsupr(_Str);
#endif
   }

   inline void __cdecl itoa_s(int _Val, char *_Buf, size_t _SizeInChars, int _Radix)
   {
#ifdef _WINDOWS
      ATLMFC_CRT_ERRORCHECK(::_itoa_s(_Val, _Buf, _SizeInChars, _Radix));
#else
      itoa(_Val, _Buf, _Radix);
#endif
   }

   inline void __cdecl ltoa_s(long _Val, char *_Buf, size_t _SizeInChars, int _Radix)
   {
#ifdef _WINDOWS
      ATLMFC_CRT_ERRORCHECK(::_ltoa_s(_Val, _Buf, _SizeInChars, _Radix));
#else
      ltoa(_Val, _Buf, _Radix);
#endif
   }

   inline void __cdecl ultoa_s(unsigned long _Val, char *_Buf, size_t _SizeInChars, int _Radix)
   {
#ifdef _WINDOWS
      ATLMFC_CRT_ERRORCHECK(::_ultoa_s(_Val, _Buf, _SizeInChars, _Radix));
#else
      ultoa(_Val, _Buf, _Radix);
#endif
   }

   inline void __cdecl ultow_s(unsigned long _Val, wchar_t *_Buf, size_t _SizeInChars, int _Radix)
   {
#ifdef _WINDOWS
      ATLMFC_CRT_ERRORCHECK(::_ultow_s(_Val, _Buf, _SizeInChars, _Radix));
#else
      ultow(_Val, _Buf, _Radix);
#endif
   }

   inline void __cdecl i64toa_s(__int64 _Val, char *_Buf, size_t _SizeInChars, int _Radix)
   {
#ifdef _WINDOWS
      ATLMFC_CRT_ERRORCHECK(::_i64toa_s(_Val, _Buf, _SizeInChars, _Radix));
#else
      i64toa(_Val, _Buf, _Radix);
#endif
   }

   inline void __cdecl i64tow_s(__int64 _Val, wchar_t *_Buf, size_t _SizeInChars, int _Radix)
   {
#ifdef _WINDOWS
      ATLMFC_CRT_ERRORCHECK(::_i64tow_s(_Val, _Buf, _SizeInChars, _Radix));
#else
      i64tow(_Val, _Buf, _Radix);
#endif
   }

   inline void __cdecl ui64toa_s(uint64_t _Val, char *_Buf, size_t _SizeInChars, int _Radix)
   {
#ifdef _WINDOWS
      ATLMFC_CRT_ERRORCHECK(::_ui64toa_s(_Val, _Buf, _SizeInChars, _Radix));
#else
      ui64toa(_Val, _Buf, _Radix);
#endif
   }

   inline void __cdecl ui64tow_s(uint64_t _Val, wchar_t *_Buf, size_t _SizeInChars, int _Radix)
   {
#ifdef _WINDOWS
      ATLMFC_CRT_ERRORCHECK(::_ui64tow_s(_Val, _Buf, _SizeInChars, _Radix));
#else
      ui64tow(_Val, _Buf, _Radix);
#endif
   }

   inline void __cdecl gcvt_s(char *_Buffer, size_t _SizeInChars, double _Value, int _Ndec)
   {
#ifdef _WINDOWS
      ATLMFC_CRT_ERRORCHECK(::_gcvt_s(_Buffer, _SizeInChars, _Value, _Ndec));
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
      ATLMFC_CRT_ERRORCHECK(::_tsplitpath_s(_Path, _Drive, _Drive_len, _Dir, _Dir_len, _Fname, _Fname_len, _Ext, _Ext_len));
   }

   inline void __cdecl tmakepath_s(char *_Path, size_t _SizeInChars, const char *_Drive,
      const char *_Dir, const char *_Fname, const char *_Ext)
   {
      ATLMFC_CRT_ERRORCHECK(::_tmakepath_s(_Path, _SizeInChars, _Drive, _Dir, _Fname, _Ext));
   }*/

   inline size_t __cdecl strnlen(const char *_Str, size_t _Maxsize)
   {
#ifdef _WINDOWS
      return ::strnlen(_Str, _Maxsize);
#else
      return ::strlen(_Str);
#endif
   }

   inline size_t __cdecl wcsnlen(const wchar_t *_Wcs, size_t _Maxsize)
   {
#ifdef _WINDOWS
      return ::wcsnlen(_Wcs, _Maxsize);
#else
      return ::wcslen_dup(_Wcs);
#endif
   }

   CLASS_DECL_ca int get_errno();
   CLASS_DECL_ca void set_errno(int _Value);

   #else // !_SECURE_ATL

   #define ATLMFC_CRT_ERRORCHECK(expr) do { expr; } while (0)

   inline void __cdecl memcpy_s(void *_S1, size_t _S1max, const void *_S2, size_t _N)
   {
      (_S1max);
      memcpy(_S1, _S2, _N);
   }

   inline void __cdecl wmemcpy_s(wchar_t *_S1, size_t _N1, const wchar_t *_S2, size_t _N)
   {
      (_N1);
      ::wmemcpy_dup(_S1, _S2, _N);
   }

   inline void __cdecl memmove_s(void *_S1, size_t _S1max, const void *_S2, size_t _N)
   {
      (_S1max);
      memmove(_S1, _S2, _N);
   }

   inline void __cdecl strcpy_s(char *_S1, size_t _S1max, const char *_S2)
   {
      (_S1max);
      ::strcpy(_S1, _S2);
   }

   inline void __cdecl wcscpy_s(wchar_t *_S1, size_t _S1max, const wchar_t *_S2)
   {
      (_S1max);
      ::wcscpy_dup(_S1, _S2);
   }

   inline void __cdecl tcscpy_s(char * _Dst, size_t _SizeInChars, const char * _Src)
   {
      (_SizeInChars);
      ::strcpy_dup(_Dst, _Src);
   }

   /* ensure that strncpy_s null-terminate the dest string */
   inline errno_t __cdecl strncpy_s(char *_Dest, size_t _SizeInChars, const char *_Source,size_t _Count)
   {
      if (_Count == _TRUNCATE)
      {
         _Count = _SizeInChars - 1;
      }
      while (_Count > 0 && *_Source != 0)
      {
         *_Dest++ = *_Source++;
         --_Count;
      }
      *_Dest = 0;

      return (*_Source!=0) ? STRUNCATE : 0;
   }

   inline errno_t __cdecl wcsncpy_s(wchar_t *_Dest, size_t _SizeInChars, const wchar_t *_Source, size_t _Count)
   {
      if (_Count == _TRUNCATE)
      {
         _Count = _SizeInChars - 1;
      }
      while (_Count > 0 && *_Source != 0)
      {
         *_Dest++ = *_Source++;
         --_Count;
      }
      *_Dest = 0;

      return (*_Source!=0) ? STRUNCATE : 0;
   }

   inline errno_t __cdecl tcsncpy_s(char *_Dest, size_t _SizeInChars, const char *_Source,size_t _Count)
   {
      if (_Count == _TRUNCATE)
      {
         if(_SizeInChars>0)
         {
            _Count = _SizeInChars - 1;
         }
         else
         {
            _Count =0;
         }
      }

   #pragma warning(push)
#if !defined(VC6) && !defined(VC71)
   #pragma warning(disable: 6535)
#endif
      ::strncpy_dup(_Dest,_Source,_Count);
   #pragma warning(pop)
      if(_SizeInChars>0)
      {
         _Dest[_SizeInChars-1] = 0;
      }

      return (*_Source!=0) ? STRUNCATE : 0;
   }

   inline void __cdecl strcat_s(char * _Dst, size_t _SizeInChars, const char * _Src)
   {
      (_SizeInChars);
      ::strcat(_Dst, _Src);
   }

   inline void __cdecl wcscat_s(wchar_t * _Dst, size_t _SizeInChars, const wchar_t * _Src)
   {
      (_SizeInChars);
      ::wcscat_dup(_Dst, _Src);
   }

   inline void __cdecl tcscat_s(char * _Dst, size_t _SizeInChars, const char * _Src)
   {
      (_SizeInChars);
      ::strcat_dup(_Dst, _Src);
   }

   inline void __cdecl strlwr_s(char * _Str, size_t _SizeInChars)
   {
      (_SizeInChars);
      ::to_lower(_Str);
   }

   /*inline void __cdecl wcslwr_s(wchar_t * _Str, size_t _SizeInChars)
   {
      (_SizeInChars);
      ::_wcslwr(_Str);
   }*/

   /*inline void __cdecl mbslwr_s(unsigned char * _Str, size_t _SizeInChars)
   {
      (_SizeInChars);
      ::_mbslwr(_Str);
   }*/

   /*inline void __cdecl tcslwr_s(char * _Str, size_t _SizeInChars)
   {
      (_SizeInChars);
      ::_tcslwr(_Str);
   }*/

   inline void __cdecl itoa_s(int _Val, char *_Buf, size_t _SizeInChars, int _Radix)
   {
      (_SizeInChars);
#if defined(LINUX)
      ::ltoa_dup(_Val, _Buf, _Radix);
#elif defined(VC6) || defined(VC71)
      ::itoa(_Val, _Buf, _Radix);
#else
      ::_itoa_s(_Val, _Buf, _SizeInChars, _Radix);
#endif
   }

/*   inline void __cdecl itot_s(int _Val, char *_Buf, size_t _SizeInChars, int _Radix)
   {
      (_SizeInChars);
      ::_itot(_Val, _Buf, _Radix);
   }*/

   inline void __cdecl ltoa_s(int64_t _Val, char *_Buf, size_t _SizeInChars, int _Radix)
   {
      (_SizeInChars);
#if defined(LINUX)
      ::ltoa_dup(_Val, _Buf, _Radix);
#else
      ::_ltoa(_Val, _Buf, _Radix);
#endif
   }

/*   inline void __cdecl ltot_s(long _Val, char *_Buf, size_t _SizeInChars, int _Radix)
   {
      (_SizeInChars);
      ::_ltot(_Val, _Buf, _Radix);
   }*/

   inline void __cdecl ultoa_s(unsigned long _Val, char *_Buf, size_t _SizeInChars, int _Radix)
   {
      (_SizeInChars);
#if defined(LINUX)
      ::ultoa_dup(_Val, _Buf, _Radix);
#else
      ::_ultoa(_Val, _Buf, _Radix);
#endif
   }

/*   inline void __cdecl ultow_s(unsigned long _Val, wchar_t *_Buf, size_t _SizeInChars, int _Radix)
   {
      (_SizeInChars);
      ::_ultow(_Val, _Buf, _Radix);
   }

   inline void __cdecl ultot_s(unsigned long _Val, char *_Buf, size_t _SizeInChars, int _Radix)
   {
      (_SizeInChars);
      ::_ultot(_Val, _Buf, _Radix);
   }*/

   inline void __cdecl i64toa_s(int64_t _Val, char *_Buf, size_t _SizeInChars, int _Radix)
   {
      (_SizeInChars);
#if defined(LINUX)
l        ::ltoa_dup(_Val, _Buf, _Radix);
#else
        ::_i64toa(_Val, _Buf, _Radix);
#endif
   }

/*   inline void __cdecl i64tow_s(__int64 _Val, wchar_t *_Buf, size_t _SizeInChars, int _Radix)
   {
      (_SizeInChars);
      ::_i64tow(_Val, _Buf, _Radix);
   }*/

   inline void __cdecl ui64toa_s(uint64_t _Val, char *_Buf, size_t _SizeInChars, int _Radix)
   {
      (_SizeInChars);
#if defined(LINUX)
      ::ultoa_dup(_Val, _Buf, _Radix);
#else
        ::_ui64toa(_Val, _Buf, _Radix);
#endif
   }

/*   inline void __cdecl ui64tow_s(uint64_t _Val, wchar_t *_Buf, size_t _SizeInChars, int _Radix)
   {
      (_SizeInChars);
      ::_ui64tow(_Val, _Buf, _Radix);
   }*/

   inline void __cdecl gcvt_s(char *_Buffer, size_t _SizeInChars, double _Value, int _Ndec)
   {
      (_SizeInChars);
#if defined(LINUX)
      ::gcvt(_Value, _Ndec, _Buffer);
#else
      ::_gcvt(_Value, _Ndec, _Buffer);
#endif
   }

/*   inline void __cdecl tsplitpath_s(const char *_Path, char *_Drive, size_t _Drive_len,
      char *_Dir, size_t _Dir_len,
      char *_Fname, size_t _Fname_len,
      char *_Ext, size_t _Ext_len)
   {
      (_Drive_len, _Dir_len, _Fname_len, _Ext_len);
      ::_tsplitpath(_Path, _Drive, _Dir, _Fname, _Ext);
   }

   inline void __cdecl tmakepath_s(char *_Path, size_t _SizeInChars, const char *_Drive,
      const char *_Dir, const char *_Fname, const char *_Ext)
   {
      (_SizeInChars);
      ::_tmakepath(_Path, _Drive, _Dir, _Fname, _Ext);
   }*/

   inline size_t __cdecl strnlen(const char *_Str, size_t _Maxsize)
   {
      (_Maxsize);
      return ::strlen(_Str);
   }

   inline size_t __cdecl wcsnlen(const wchar_t *_Wcs, size_t _Maxsize)
   {
      (_Maxsize);
      return ::wcslen_dup(_Wcs);
   }

   inline size_t __cdecl tcsnlen(const char *_Str, size_t _Maxsize)
   {
      (_Maxsize);
      return ::strlen_dup(_Str);
   }

   inline int get_errno()
   {
      return errno;
   }

   inline void set_errno(int _Value)
   {
      errno = _Value;
   }

   #endif // _SECURE_ATL

   } // namespace checked

} // namespace _template
