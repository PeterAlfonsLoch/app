#pragma once

#include "definition.h"
#include "exception.h"




namespace _template
{

   inline errno_t AtlCrtErrorCheck(errno_t nError)
   {
      switch(nError)
      {
      case ENOMEM:
         AtlThrow(E_OUTOFMEMORY);
         break;
      case EINVAL:
      case ERANGE:
         AtlThrow(E_INVALIDARG);
         break;
      case 0:
#if !defined(VC6)
      case STRUNCATE:
#endif
         break;
      default:
         AtlThrow(E_FAIL);
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
      ATLMFC_CRT_ERRORCHECK(::memcpy_s(_S1, _S1max, _S2, _N));
   }

   inline void __cdecl wmemcpy_s(wchar_t *_S1, size_t _N1, const wchar_t *_S2, size_t _N)
   {
      ATLMFC_CRT_ERRORCHECK(::wmemcpy_s(_S1, _N1, _S2, _N));
   }

   inline void __cdecl memmove_s(void *_S1, size_t _S1max, const void *_S2, size_t _N)
   {
      ATLMFC_CRT_ERRORCHECK(::memmove_s(_S1, _S1max, _S2, _N));
   }

   inline void __cdecl strcpy_s(char *_S1, size_t _S1max, const char *_S2)
   {
      ATLMFC_CRT_ERRORCHECK(::strcpy_s(_S1, _S1max, _S2));
   }

   inline void __cdecl wcscpy_s(wchar_t *_S1, size_t _S1max, const wchar_t *_S2)
   {
      ATLMFC_CRT_ERRORCHECK(::wcscpy_s(_S1, _S1max, _S2));
   }

   inline void __cdecl tcscpy_s(char * _Dst, size_t _SizeInChars, const char * _Src)
   {
      ATLMFC_CRT_ERRORCHECK(::_tcscpy_s(_Dst, _SizeInChars, _Src));
   }

   inline errno_t __cdecl strncpy_s(char *_Dest, size_t _SizeInChars, const char *_Source, size_t _Count)
   {
      return ATLMFC_CRT_ERRORCHECK(::strncpy_s(_Dest, _SizeInChars, _Source,_Count));
   }

   inline errno_t __cdecl wcsncpy_s(wchar_t *_Dest, size_t _SizeInChars, const wchar_t *_Source, size_t _Count)
   {
      return ATLMFC_CRT_ERRORCHECK(::wcsncpy_s(_Dest, _SizeInChars, _Source,_Count));
   }

   inline errno_t __cdecl tcsncpy_s(char *_Dest, size_t _SizeInChars, const char *_Source, size_t _Count)
   {
      return ATLMFC_CRT_ERRORCHECK(::_tcsncpy_s(_Dest, _SizeInChars, _Source,_Count));
   }

   inline void __cdecl strcat_s(char * _Dst, size_t _SizeInChars, const char * _Src)
   {
      ATLMFC_CRT_ERRORCHECK(::strcat_s(_Dst, _SizeInChars, _Src));
   }

   inline void __cdecl wcscat_s(wchar_t * _Dst, size_t _SizeInChars, const wchar_t * _Src)
   {
      ATLMFC_CRT_ERRORCHECK(::wcscat_s(_Dst, _SizeInChars, _Src));
   }

   inline void __cdecl tcscat_s(char * _Dst, size_t _SizeInChars, const char * _Src)
   {
      ATLMFC_CRT_ERRORCHECK(::_tcscat_s(_Dst, _SizeInChars, _Src));
   }

   inline void __cdecl strlwr_s(char * _Str, size_t _SizeInChars)
   {
      ATLMFC_CRT_ERRORCHECK(::_strlwr_s(_Str, _SizeInChars));
   }

   inline void __cdecl wcslwr_s(wchar_t * _Str, size_t _SizeInChars)
   {
      ATLMFC_CRT_ERRORCHECK(::_wcslwr_s(_Str, _SizeInChars));
   }

   inline void __cdecl mbslwr_s(unsigned char * _Str, size_t _SizeInChars)
   {
      ATLMFC_CRT_ERRORCHECK(::_mbslwr_s(_Str, _SizeInChars));
   }

   inline void __cdecl tcslwr_s(char * _Str, size_t _SizeInChars)
   {
      ATLMFC_CRT_ERRORCHECK(::_tcslwr_s(_Str, _SizeInChars));
   }

   inline void __cdecl strupr_s(char * _Str, size_t _SizeInChars)
   {
      ATLMFC_CRT_ERRORCHECK(::_strupr_s(_Str, _SizeInChars));
   }

   inline void __cdecl wcsupr_s(wchar_t * _Str, size_t _SizeInChars)
   {
      ATLMFC_CRT_ERRORCHECK(::_wcsupr_s(_Str, _SizeInChars));
   }

   inline void __cdecl mbsupr_s(unsigned char * _Str, size_t _SizeInChars)
   {
      ATLMFC_CRT_ERRORCHECK(::_mbsupr_s(_Str, _SizeInChars));
   }

   inline void __cdecl tcsupr_s(char * _Str, size_t _SizeInChars)
   {
      ATLMFC_CRT_ERRORCHECK(::_tcsupr_s(_Str, _SizeInChars));
   }

   inline void __cdecl itoa_s(int _Val, char *_Buf, size_t _SizeInChars, int _Radix)
   {
      ATLMFC_CRT_ERRORCHECK(::_itoa_s(_Val, _Buf, _SizeInChars, _Radix));
   }

   inline void __cdecl itot_s(int _Val, char *_Buf, size_t _SizeInChars, int _Radix)
   {
      ATLMFC_CRT_ERRORCHECK(::_itot_s(_Val, _Buf, _SizeInChars, _Radix));
   }

   inline void __cdecl ltoa_s(long _Val, char *_Buf, size_t _SizeInChars, int _Radix)
   {
      ATLMFC_CRT_ERRORCHECK(::_ltoa_s(_Val, _Buf, _SizeInChars, _Radix));
   }

   inline void __cdecl ltot_s(long _Val, char *_Buf, size_t _SizeInChars, int _Radix)
   {
      ATLMFC_CRT_ERRORCHECK(::_ltot_s(_Val, _Buf, _SizeInChars, _Radix));
   }

   inline void __cdecl ultoa_s(unsigned long _Val, char *_Buf, size_t _SizeInChars, int _Radix)
   {
      ATLMFC_CRT_ERRORCHECK(::_ultoa_s(_Val, _Buf, _SizeInChars, _Radix));
   }

   inline void __cdecl ultow_s(unsigned long _Val, wchar_t *_Buf, size_t _SizeInChars, int _Radix)
   {
      ATLMFC_CRT_ERRORCHECK(::_ultow_s(_Val, _Buf, _SizeInChars, _Radix));
   }

   inline void __cdecl ultot_s(unsigned long _Val, char *_Buf, size_t _SizeInChars, int _Radix)
   {
      ATLMFC_CRT_ERRORCHECK(::_ultot_s(_Val, _Buf, _SizeInChars, _Radix));
   }

   inline void __cdecl i64toa_s(__int64 _Val, char *_Buf, size_t _SizeInChars, int _Radix)
   {
      ATLMFC_CRT_ERRORCHECK(::_i64toa_s(_Val, _Buf, _SizeInChars, _Radix));
   }

   inline void __cdecl i64tow_s(__int64 _Val, wchar_t *_Buf, size_t _SizeInChars, int _Radix)
   {
      ATLMFC_CRT_ERRORCHECK(::_i64tow_s(_Val, _Buf, _SizeInChars, _Radix));
   }

   inline void __cdecl ui64toa_s(unsigned __int64 _Val, char *_Buf, size_t _SizeInChars, int _Radix)
   {
      ATLMFC_CRT_ERRORCHECK(::_ui64toa_s(_Val, _Buf, _SizeInChars, _Radix));
   }

   inline void __cdecl ui64tow_s(unsigned __int64 _Val, wchar_t *_Buf, size_t _SizeInChars, int _Radix)
   {
      ATLMFC_CRT_ERRORCHECK(::_ui64tow_s(_Val, _Buf, _SizeInChars, _Radix));
   }

   inline void __cdecl gcvt_s(char *_Buffer, size_t _SizeInChars, double _Value, int _Ndec)
   {
      ATLMFC_CRT_ERRORCHECK(::_gcvt_s(_Buffer, _SizeInChars, _Value, _Ndec));
   }

   inline void __cdecl tsplitpath_s(const char *_Path, char *_Drive, size_t _Drive_len,
      char *_Dir, size_t _Dir_len,
      __out_ecount_z_opt(_Fname_len) char *_Fname, size_t _Fname_len,
      char *_Ext, size_t _Ext_len)
   {
      ATLMFC_CRT_ERRORCHECK(::_tsplitpath_s(_Path, _Drive, _Drive_len, _Dir, _Dir_len, _Fname, _Fname_len, _Ext, _Ext_len));
   }

   inline void __cdecl tmakepath_s(char *_Path, size_t _SizeInChars, const char *_Drive,
      const char *_Dir, const char *_Fname, const char *_Ext)
   {
      ATLMFC_CRT_ERRORCHECK(::_tmakepath_s(_Path, _SizeInChars, _Drive, _Dir, _Fname, _Ext));
   }

   inline size_t __cdecl strnlen(const char *_Str, size_t _Maxsize)
   {
      return ::strnlen(_Str, _Maxsize);
   }

   inline size_t __cdecl wcsnlen(const wchar_t *_Wcs, size_t _Maxsize)
   {
      return ::wcsnlen(_Wcs, _Maxsize);
   }

   inline size_t __cdecl tcsnlen(const char *_Str, size_t _Maxsize)
   {
      return ::_tcsnlen(_Str, _Maxsize);
   }

   inline int get_errno()
   {
      int nErrNo;
      ATLMFC_CRT_ERRORCHECK(::_get_errno(&nErrNo));
      return nErrNo;
   }

   inline void set_errno(int _Value)
   {
      ATLMFC_CRT_ERRORCHECK(::_set_errno(_Value));
   }

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
      ::wmemcpy(_S1, _S2, _N);
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
      ::wcscpy(_S1, _S2);
   }

   inline void __cdecl tcscpy_s(char * _Dst, size_t _SizeInChars, const char * _Src)
   {
      (_SizeInChars);
      ::_tcscpy(_Dst, _Src);
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
      ::_tcsncpy(_Dest,_Source,_Count);
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
      ::wcscat(_Dst, _Src);
   }

   inline void __cdecl tcscat_s(char * _Dst, size_t _SizeInChars, const char * _Src)
   {
      (_SizeInChars);
      ::_tcscat(_Dst, _Src);
   }

   inline void __cdecl strlwr_s(char * _Str, size_t _SizeInChars)
   {
      (_SizeInChars);
      ::_strlwr(_Str);
   }

   inline void __cdecl wcslwr_s(wchar_t * _Str, size_t _SizeInChars)
   {
      (_SizeInChars);
      ::_wcslwr(_Str);
   }

   inline void __cdecl mbslwr_s(unsigned char * _Str, size_t _SizeInChars)
   {
      (_SizeInChars);
      ::_mbslwr(_Str);
   }

   inline void __cdecl tcslwr_s(char * _Str, size_t _SizeInChars)
   {
      (_SizeInChars);
      ::_tcslwr(_Str);
   }

   inline void __cdecl itoa_s(int _Val, char *_Buf, size_t _SizeInChars, int _Radix)
   {
      (_SizeInChars);
#if defined(VC6) || defined(VC71)
      ::itoa(_Val, _Buf, _Radix);
#else
      ::_itoa_s(_Val, _Buf, _SizeInChars, _Radix);
#endif
   }

   inline void __cdecl itot_s(int _Val, char *_Buf, size_t _SizeInChars, int _Radix)
   {
      (_SizeInChars);
      ::_itot(_Val, _Buf, _Radix);
   }

   inline void __cdecl ltoa_s(long _Val, char *_Buf, size_t _SizeInChars, int _Radix)
   {
      (_SizeInChars);
      ::_ltoa(_Val, _Buf, _Radix);
   }

   inline void __cdecl ltot_s(long _Val, char *_Buf, size_t _SizeInChars, int _Radix)
   {
      (_SizeInChars);
      ::_ltot(_Val, _Buf, _Radix);
   }

   inline void __cdecl ultoa_s(unsigned long _Val, char *_Buf, size_t _SizeInChars, int _Radix)
   {
      (_SizeInChars);
      ::_ultoa(_Val, _Buf, _Radix);
   }

   inline void __cdecl ultow_s(unsigned long _Val, wchar_t *_Buf, size_t _SizeInChars, int _Radix)
   {
      (_SizeInChars);
      ::_ultow(_Val, _Buf, _Radix);
   }

   inline void __cdecl ultot_s(unsigned long _Val, char *_Buf, size_t _SizeInChars, int _Radix)
   {
      (_SizeInChars);
      ::_ultot(_Val, _Buf, _Radix);
   }

   inline void __cdecl i64toa_s(__int64 _Val, char *_Buf, size_t _SizeInChars, int _Radix)
   {
      (_SizeInChars);
      ::_i64toa(_Val, _Buf, _Radix);
   }

   inline void __cdecl i64tow_s(__int64 _Val, wchar_t *_Buf, size_t _SizeInChars, int _Radix)
   {
      (_SizeInChars);
      ::_i64tow(_Val, _Buf, _Radix);
   }

   inline void __cdecl ui64toa_s(unsigned __int64 _Val, char *_Buf, size_t _SizeInChars, int _Radix)
   {
      (_SizeInChars);
      ::_ui64toa(_Val, _Buf, _Radix);
   }

   inline void __cdecl ui64tow_s(unsigned __int64 _Val, wchar_t *_Buf, size_t _SizeInChars, int _Radix)
   {
      (_SizeInChars);
      ::_ui64tow(_Val, _Buf, _Radix);
   }

   inline void __cdecl gcvt_s(char *_Buffer, size_t _SizeInChars, double _Value, int _Ndec)
   {
      (_SizeInChars);
      ::_gcvt(_Value, _Ndec, _Buffer);
   }

   inline void __cdecl tsplitpath_s(const char *_Path, char *_Drive, size_t _Drive_len,
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
   }

   inline size_t __cdecl strnlen(const char *_Str, size_t _Maxsize)
   {
      (_Maxsize);
      return ::strlen(_Str);
   }

   inline size_t __cdecl wcsnlen(const wchar_t *_Wcs, size_t _Maxsize)
   {
      (_Maxsize);
      return ::wcslen(_Wcs);
   }

   inline size_t __cdecl tcsnlen(const char *_Str, size_t _Maxsize)
   {
      (_Maxsize);
      return ::_tcslen(_Str);
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
