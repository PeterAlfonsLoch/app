#include "framework.h"

#ifdef WINDOWS

#include <winnls.h>

#endif

namespace gen
{


   namespace international
   {


      bool UnicodeToMultiByte(UINT uiCodePage, char * lpstrMultiByte, strsize nCount, const wchar_t * lpcsz)
      {
         return WideCharToMultiByte(uiCodePage, 0, lpcsz, -1, lpstrMultiByte, (int) nCount, NULL, NULL) != FALSE;
      }

      bool UnicodeToMultiByte(UINT uiCodePage, char * lpstrMultiByte, strsize iMultiByteCount, const wchar_t * lpcsz, strsize iCount)
      {
         return WideCharToMultiByte(uiCodePage, 0, lpcsz, (int) iCount, lpstrMultiByte, (int) iMultiByteCount, NULL, NULL) != FALSE;
      }

      bool UnicodeToMultiByte(UINT uiCodePage, string &str, const wchar_t * lpcsz)
      {
         strsize iCount = UnicodeToMultiByteCount(uiCodePage, lpcsz);
         LPSTR lpsz = str.GetBuffer(iCount);
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

      bool UnicodeToMultiByte(UINT uiCodePage, string &str, const wchar_t * lpcsz, strsize iCount)
      {
         strsize iMultiByteCount = UnicodeToMultiByteCount(uiCodePage, lpcsz, iCount);
         LPSTR lpsz = str.GetBuffer(iCount);
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

      bool unicode_to_utf8(string & str, const wchar_t * lpcsz, strsize iCount)
      {
         return UnicodeToMultiByte(CodePageUtf8, str, lpcsz, iCount);
      }

      strsize UnicodeToMultiByteCount(UINT uiCodePage, const wchar_t * lpcsz)
      {
         return WideCharToMultiByte(uiCodePage, 0, lpcsz, -1, NULL, 0, NULL, NULL);
      }

      strsize UnicodeToMultiByteCount(UINT uiCodePage, const wchar_t * lpcsz, strsize iCount)
      {
         return WideCharToMultiByte(uiCodePage, 0, lpcsz, (int) iCount, NULL, 0, NULL, NULL);
      }

      strsize Utf8ToMultiByteCount(UINT uiCodePage, const char * lpcsz)
      {
         return WideCharToMultiByte(uiCodePage, 0, MultiByteToUnicode(uiCodePage, lpcsz), -1, NULL, 0, NULL, NULL);
      }

      bool MultiByteToUnicode(UINT uiCodePage, wchar_t * lpwsz, strsize iBuffer, const char * lpcsz, strsize iCount)
      {
         if(lpwsz == NULL)
         {
            if(iBuffer > 0)
               return false;
            else if(lpcsz != NULL)
               return false;
            else if(iCount > 0)
               return false;
            else
               return true;
         }
         return MultiByteToWideChar(uiCodePage, 0, lpcsz, (int) iCount, lpwsz, (int) iBuffer) != 0;
      }

      bool MultiByteToUnicode(UINT uiCodePage, wchar_t * lpwsz, strsize iBuffer, const char * lpcsz)
      {
         return MultiByteToUnicode(uiCodePage, lpwsz, iBuffer, lpcsz, -1);
      }

      strsize MultiByteToUnicodeCount(UINT uiCodePage, const char * lpcsz, strsize iCount)
      {
         return MultiByteToWideChar(uiCodePage, 0, lpcsz, (int) iCount, NULL, 0);
      }

      strsize MultiByteToUnicodeCount(UINT uiCodePage, const char * lpcsz)
      {
         return MultiByteToUnicodeCount(uiCodePage, lpcsz, -1);
      }

      wstring MultiByteToUnicode(UINT uiCodePage, const char * lpcsz)
      {
         return MultiByteToUnicode(uiCodePage, lpcsz, -1).detach();
      }

      wstring MultiByteToUnicode(UINT uiCodePage, const char * lpcsz, strsize nCount)
      {
         strsize iBuffer = MultiByteToUnicodeCount(uiCodePage, lpcsz, nCount);
         if(iBuffer == ERROR_NO_UNICODE_TRANSLATION)
         {
            return L"";
         }
         else if(iBuffer == 0)
         {
            return L"";
         }
         wstring wstr;
         wstr.alloc(iBuffer + 1);
         if(MultiByteToUnicode(uiCodePage, wstr, iBuffer, lpcsz, nCount))
         {
            wstr.set_length(iBuffer);
            return wstr.detach();
         }
         return L"";
      }

      wstring MultiByteToUnicode(UINT uiCodePage, const string & str)
      {
         if(str.length() <= 0)
            return L"";
         strsize iBuffer = MultiByteToUnicodeCount(uiCodePage, str, (strsize) str.get_length());
         if(iBuffer == ERROR_NO_UNICODE_TRANSLATION)
         {
            return L"";
         }
         else if(iBuffer == 0)
         {
            return L"";
         }
         wstring wstr;
         wstr.alloc(iBuffer + 1);
         if(MultiByteToUnicode(uiCodePage, wstr, iBuffer, str, (strsize) str.get_length()))
         {
            wstr.set_length(iBuffer);
            return wstr.detach();
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

      bool MultiByteToMultiByte(UINT uiCodePageDst, char * lpsz, strsize nCount, UINT uiCodePageSrc, const char * lpcsz)
      {
         return UnicodeToMultiByte(uiCodePageDst, lpsz, nCount, MultiByteToUnicode(uiCodePageSrc, lpcsz));
      }

      bool MultiByteToMultiByte(UINT uiCodePageDst, string & str, UINT uiCodePageSrc, const char * lpcsz, strsize nCount)
      {
         return UnicodeToMultiByte(uiCodePageDst, str, MultiByteToUnicode(uiCodePageSrc, lpcsz, nCount));
      }

      //bool MultiByteToOEM(UINT uiCodePage, string & str, const char * lpcsz)
      //{
      //   return MultiByteToMultiByte(::GetOEMCP(), str, uiCodePage, lpcsz);
      //}

      //bool MultiByteToOEM(UINT uiCodePage, string & str, const char * lpcsz, strsize nCount)
      //{
      //   return MultiByteToMultiByte(::GetOEMCP(), str, uiCodePage, lpcsz, nCount);
      //}

      //bool OEMToMultiByte(UINT uiCodePage, string & str, const char * lpcsz)
      //{
      //   return MultiByteToMultiByte(uiCodePage, str, ::GetOEMCP(), lpcsz);
      //}

      //bool OEMToMultiByte(UINT uiCodePage, string & str, const char * lpcsz, strsize nCount)
      //{
      //   return MultiByteToMultiByte(uiCodePage, str, ::GetOEMCP(), lpcsz, nCount);
      //}

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

      bool MultiByteToMultiByte(UINT uiCodePageDst, primitive::memory & str, UINT uiCodePageSrc, const char * lpcsz, strsize nCount)
      {
         return UnicodeToMultiByte(uiCodePageDst, str, MultiByteToUnicode(uiCodePageSrc, lpcsz, nCount));
      }

      bool UnicodeToMultiByte(UINT uiCodePage, primitive::memory & memstorage, const wchar_t * lpcsz)
      {
         memstorage.allocate(UnicodeToMultiByteCount(uiCodePage, lpcsz));
         return UnicodeToMultiByte(uiCodePage, (char *) memstorage.get_data(), (strsize) memstorage.get_size(), lpcsz);
      }

      //bool OEMToMultiByte(UINT uiCodePage, primitive::memory & str, const char * lpcsz)
      //{
      //   return MultiByteToMultiByte(uiCodePage, str, ::GetOEMCP(), lpcsz);
      //}

      //bool OEMToMultiByte(UINT uiCodePage, primitive::memory & str, const char * lpcsz, strsize nCount)
      //{
      //   return MultiByteToMultiByte(uiCodePage, str, ::GetOEMCP(), lpcsz, nCount);
      //}

      ///////////////////////////////////////////////////////////////
      // ACP ( GetACP() function) conversion
      ///////////////////////////////////////////////////////////////

      string UnicodeToMultiByte(UINT uiCodePage, const wchar_t * lpcsz)
      {
         string str;
         UnicodeToMultiByte(uiCodePage, str, lpcsz);
         return str;
      }

      bool UnicodeToACP(string & str, const wchar_t * lpcsz)
      {
         return UnicodeToMultiByte(g_uiACP, str, lpcsz);
      }

      bool UnicodeToACP(char * lpstrUnicode, strsize nCount, const wchar_t * lpcsz)
      {
         return UnicodeToMultiByte(g_uiACP, lpstrUnicode, nCount, lpcsz);
      }


      string UnicodeToACP(const wchar_t * lpcsz)
      {
         return UnicodeToMultiByte(CP_ACP, lpcsz);
      }


      bool ACPToUnicode(wchar_t * lpstrUnicode, strsize nCount, const char * lpcsz)
      {
         return MultiByteToUnicode(g_uiACP, lpstrUnicode, nCount, lpcsz);
      }

      wstring  ACPToUnicode(const char * lpcsz)
      {
         return MultiByteToUnicode(g_uiACP, lpcsz).detach();
      }

      wstring  ACPToUnicode(const char * lpcsz, strsize iSize)
      {
         return MultiByteToUnicode(g_uiACP, lpcsz, iSize).detach();
      }

      ///////////////////////////////////////////////////////////////
      // OEM ( GetOEM() function) conversion
      ///////////////////////////////////////////////////////////////

      bool UnicodeToOEM(string & str, const wchar_t * lpcsz)
      {
         return UnicodeToMultiByte(CodePageOem, str, lpcsz);
      }

      bool UnicodeToOEM(char * lpstrUnicode, strsize nCount, const wchar_t * lpcsz)
      {
         return UnicodeToMultiByte(CodePageOem, lpstrUnicode, nCount, lpcsz);
      }



      bool OEMToUnicode(wchar_t * lpstrUnicode, strsize nCount, const char * lpcsz)
      {
         return MultiByteToUnicode(CodePageOem, lpstrUnicode, nCount, lpcsz);
      }

      wstring OEMToUnicode(const char * lpcsz)
      {
         return MultiByteToUnicode(CodePageOem, lpcsz).detach();
      }

      bool unicode_to_utf8(string & str, const wchar_t * lpcsz)
      {
         return UnicodeToMultiByte(CodePageUtf8, str, lpcsz);
      }

      wstring utf8_to_unicode(const char * lpcsz)
      {
         return MultiByteToUnicode(CodePageUtf8, lpcsz).detach();
      }

      wstring utf8_to_unicode(const string & str)
      {
         return MultiByteToUnicode(CodePageUtf8, str).detach();
      }

      wstring utf8_to_unicode(const var & var)
      {
         return MultiByteToUnicode(CodePageUtf8, (const string &) var).detach();
      }

      strsize utf8_to_unicode_count(const char * lpcsz, strsize count)
      {
         return MultiByteToUnicodeCount(CodePageUtf8, lpcsz, (strsize) count);
      }

      strsize utf8_to_unicode_count(const string & str)
      {
         return MultiByteToUnicodeCount(CodePageUtf8, str, (strsize) str.get_length());
      }

      /*string UnicodeToACP(const wchar_t * lpcsz)
      {
         string str;
         UnicodeToMultiByte(g_uiACP, str, lpcsz);
         return str;
      }

      string ACPToUnicode(const char * lpcsz)
      {
         string str;
         MultiByteToUnicode(g_uiACP, str, lpcsz);
         return str;
      }
      */


      bool AcpToUtf8(string & str, const char * lpcsz)
      {
         return MultiByteToMultiByte(CodePageUtf8, str, CodePageAnsi, lpcsz);
      }

      bool Utf8ToAcp(string & str, const char * lpcsz)
      {
         return MultiByteToMultiByte(CodePageAnsi, str, CodePageUtf8, lpcsz);
      }


      bool multibyte_to_utf8(UINT uiCodePageSrc, string & str, const char * lpcsz)
      {
         return MultiByteToMultiByte(CP_UTF8, str, uiCodePageSrc, lpcsz);
      }

      bool multibyte_to_utf8(UINT uiCodePageSrc, string & str, const char * lpcsz, strsize nCount)
      {
         return MultiByteToMultiByte(CP_UTF8, str, uiCodePageSrc, lpcsz, nCount);
      }


      bool OemToUtf8(string & str, const char * lpcsz)
      {
         return MultiByteToMultiByte(CP_UTF8, str, CP_OEMCP, lpcsz);
      }

      bool OemToUtf8(string & str, const char * lpcsz, strsize nCount)
      {
         return MultiByteToMultiByte(CP_UTF8, str, CP_OEMCP, lpcsz, nCount);
      }

      wstring utf8_to_unicode(const char * lpcsz, strsize iCount)
      {
         return MultiByteToUnicode(CP_UTF8, lpcsz, (strsize) iCount).detach();
      }

      bool utf8_to_unicode(wchar_t * lpwsz, strsize iBuffer, const char * lpcsz, strsize iCount)
      {
         return MultiByteToUnicode(CP_UTF8, lpwsz, (strsize) iBuffer, lpcsz, (strsize) iCount);
      }

      bool utf8_to_unicode(wchar_t * lpwsz, strsize iBuffer, const char * lpcsz)
      {
         return utf8_to_unicode(lpwsz, (strsize) iBuffer, lpcsz, -1);
      }

      bool utf8_to_multibyte(UINT uiCodePage, string & str, const char * lpcsz)
      {
         return MultiByteToMultiByte(CodePageUtf8, str, uiCodePage, lpcsz);
      }

      bool utf8_to_multibyte(UINT uiCodePage, string & str, const char * lpcsz, strsize nCount)
      {
         return MultiByteToMultiByte(CodePageUtf8, str, uiCodePage, lpcsz, nCount);
      }

      bool utf8_to_multibyte(UINT uiCodePage, char * lpsz, strsize nCount, const char * lpcsz)
      {
         return MultiByteToMultiByte(CodePageUtf8, lpsz, nCount, uiCodePage, lpcsz);
      }


      //bool AcpToUtf8(LPTSTR lpstrUnicode, strsize nCount, const char * lpcsz)
      //{
      //   return MultiByteToMultiByte(CP_UTF8, lpstrUnicode, nCount, g_uiACP, lpcsz);
      //}

      //bool AcpToUtf8(string & str, const char * lpcsz, strsize iSize)
      //{
      //   return MultiByteToMultiByte(CP_UTF8, str, g_uiACP, lpcsz, iSize);
      //}


   } // namespace international


} // namespace gen


