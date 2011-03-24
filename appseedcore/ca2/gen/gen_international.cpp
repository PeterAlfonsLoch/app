#include "StdAfx.h"
#include <winnls.h>

namespace gen
{

   namespace international
   {

      UINT       g_uiACP = GetACP();

      bool UnicodeToMultiByte(UINT uiCodePage, char * lpstrMultiByte, int nCount, const wchar_t * lpcsz)
      {
         return WideCharToMultiByte(uiCodePage, 0, lpcsz, -1, lpstrMultiByte, nCount, NULL, NULL) != FALSE;
      }

      bool UnicodeToMultiByte(UINT uiCodePage, char * lpstrMultiByte, int iMultiByteCount, const wchar_t * lpcsz, int iCount)
      {
         return WideCharToMultiByte(uiCodePage, 0, lpcsz, iCount, lpstrMultiByte, iMultiByteCount, NULL, NULL) != FALSE;
      }

      bool UnicodeToMultiByte(UINT uiCodePage, string &str, const wchar_t * lpcsz)
      {
         int iCount = UnicodeToMultiByteCount(uiCodePage, lpcsz);
         LPTSTR lpsz = str.GetBuffer(iCount);
         if(UnicodeToMultiByte(uiCodePage, lpsz, iCount, lpcsz))
         {
            str.ReleaseBufferSetLength(iCount - 1);
            return true;
         }
         else
         {
            str.ReleaseBufferSetLength(0);
            str.Empty();
            return false;
         }
         return true;
      }

      bool UnicodeToMultiByte(UINT uiCodePage, string &str, const wchar_t * lpcsz, int iCount)
      {
         int iMultiByteCount = UnicodeToMultiByteCount(uiCodePage, lpcsz, iCount);
         LPTSTR lpsz = str.GetBuffer(iCount);
         if(UnicodeToMultiByte(uiCodePage, lpsz, iMultiByteCount, lpcsz, iCount))
         {
            str.ReleaseBufferSetLength(iCount - 1);
            return true;
         }
         else
         {
            str.ReleaseBufferSetLength(0);
            str.Empty();
            return false;
         }
      }

      bool unicode_to_utf8(string & str, const wchar_t * lpcsz, int iCount)
      {
         return UnicodeToMultiByte(CodePageUtf8, str, lpcsz, iCount);
      }

      int UnicodeToMultiByteCount(UINT uiCodePage, const wchar_t * lpcsz)
      {
         return WideCharToMultiByte(uiCodePage, 0, lpcsz, -1, NULL, 0, NULL, NULL);
      }

      int UnicodeToMultiByteCount(UINT uiCodePage, const wchar_t * lpcsz, int iCount)
      {
         return WideCharToMultiByte(uiCodePage, 0, lpcsz, iCount, NULL, 0, NULL, NULL);
      }

      int Utf8ToMultiByteCount(UINT uiCodePage, const char * lpcsz)
      {
         return WideCharToMultiByte(uiCodePage, 0, MultiByteToUnicode(uiCodePage, lpcsz), -1, NULL, 0, NULL, NULL);
      }

      bool MultiByteToUnicode(UINT uiCodePage, wchar_t * lpwsz, int iBuffer, const char * lpcsz, int iCount)
      {
         return MultiByteToWideChar(uiCodePage, 0, lpcsz, iCount, lpwsz, iBuffer) != 0;
      }

      bool MultiByteToUnicode(UINT uiCodePage, wchar_t * lpwsz, int iBuffer, const char * lpcsz)
      {
         return MultiByteToUnicode(uiCodePage, lpwsz, iBuffer, lpcsz, -1);
      }

      int MultiByteToUnicodeCount(UINT uiCodePage, const char * lpcsz, int iCount)
      {
         return MultiByteToWideChar(uiCodePage, 0, lpcsz, iCount, NULL, 0);
      }

      int MultiByteToUnicodeCount(UINT uiCodePage, const char * lpcsz)
      {
         return MultiByteToUnicodeCount(uiCodePage, lpcsz, -1);
      }

      wstring MultiByteToUnicode(UINT uiCodePage, const char * lpcsz)
      {
         return MultiByteToUnicode(uiCodePage, lpcsz, -1);
      }

      wstring MultiByteToUnicode(UINT uiCodePage, const char * lpcsz, int nCount)
      {
         int iBuffer = MultiByteToUnicodeCount(uiCodePage, lpcsz, nCount);
         if(iBuffer == ERROR_NO_UNICODE_TRANSLATION)
         {
            return NULL;
         }
         else if(iBuffer == 0)
         {
            return L"";
         }
         wstring wstr;
         wstr.alloc(iBuffer);
         if(MultiByteToUnicode(uiCodePage, wstr.m_pwsz, iBuffer, lpcsz, nCount))
         {
            return wstr;
         }
         return L"";
      }

      bool MultiByteToMultiByte(UINT uiCodePageDst, string & str, UINT uiCodePageSrc, const char * lpcsz)
      {
         if(uiCodePageDst == uiCodePageSrc)
         {
            str = lpcsz;
            return true;
         }
         else
            return UnicodeToMultiByte(uiCodePageDst, str, MultiByteToUnicode(uiCodePageSrc, lpcsz));
      }

      bool MultiByteToMultiByte(UINT uiCodePageDst, char * lpsz, int nCount, UINT uiCodePageSrc, const char * lpcsz)
      {
         return UnicodeToMultiByte(uiCodePageDst, lpsz, nCount, MultiByteToUnicode(uiCodePageSrc, lpcsz));
      }

      bool MultiByteToMultiByte(UINT uiCodePageDst, string & str, UINT uiCodePageSrc, const char * lpcsz, int nCount)
      {
         return UnicodeToMultiByte(uiCodePageDst, str, MultiByteToUnicode(uiCodePageSrc, lpcsz, nCount));
      }

      bool MultiByteToOEM(UINT uiCodePage, string & str, const char * lpcsz)
      {
         return MultiByteToMultiByte(::GetOEMCP(), str, uiCodePage, lpcsz);
      }

      bool MultiByteToOEM(UINT uiCodePage, string & str, const char * lpcsz, int nCount)
      {
         return MultiByteToMultiByte(::GetOEMCP(), str, uiCodePage, lpcsz, nCount);
      }

      bool OEMToMultiByte(UINT uiCodePage, string & str, const char * lpcsz)
      {
         return MultiByteToMultiByte(uiCodePage, str, ::GetOEMCP(), lpcsz);
      }

      bool OEMToMultiByte(UINT uiCodePage, string & str, const char * lpcsz, int nCount)
      {
         return MultiByteToMultiByte(uiCodePage, str, ::GetOEMCP(), lpcsz, nCount);
      }

      string unicode_to_utf8(const wchar_t * lpcsz)
      {
         string str;
         unicode_to_utf8(str, lpcsz);
         return str;
      }

      bool MultiByteToMultiByte(UINT uiCodePageDst, primitive::memory & str, UINT uiCodePageSrc, const char * lpcsz)
      {
         return UnicodeToMultiByte(uiCodePageDst, str, MultiByteToUnicode(uiCodePageSrc, lpcsz));
      }

      bool MultiByteToMultiByte(UINT uiCodePageDst, primitive::memory & str, UINT uiCodePageSrc, const char * lpcsz, int nCount)
      {
         return UnicodeToMultiByte(uiCodePageDst, str, MultiByteToUnicode(uiCodePageSrc, lpcsz, nCount));
      }

      bool UnicodeToMultiByte(UINT uiCodePage, primitive::memory & memstorage, const wchar_t * lpcsz)
      {
         memstorage.allocate(UnicodeToMultiByteCount(uiCodePage, lpcsz));
         return UnicodeToMultiByte(uiCodePage, (char *) memstorage.GetAllocation(), memstorage.GetStorageSize(), lpcsz);
      }

      bool OEMToMultiByte(UINT uiCodePage, primitive::memory & str, const char * lpcsz)
      {
         return MultiByteToMultiByte(uiCodePage, str, ::GetOEMCP(), lpcsz);
      }

      bool OEMToMultiByte(UINT uiCodePage, primitive::memory & str, const char * lpcsz, int nCount)
      {
         return MultiByteToMultiByte(uiCodePage, str, ::GetOEMCP(), lpcsz, nCount);
      }

   } // namespace international

} // namespace gen
