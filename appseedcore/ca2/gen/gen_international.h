#pragma once


namespace gen
{
   namespace international
   {
      extern UINT g_uiACP;
      enum ECodePage
      {
         CodePageShiftJIS = 932,
         CodePageLatin1 = 1252,
         CodePageUtf8 = CP_UTF8,
         CodePageAnsi = CP_ACP,
         CodePageOem = CP_OEMCP,
      };


       bool CLASS_DECL_ca UnicodeToMultiByte(UINT uiCodePage, char * lpsz, int nCount, const wchar_t * lpcsz);
       bool CLASS_DECL_ca UnicodeToMultiByte(UINT uiCodePage, char * lpsz, int iBuffer, const wchar_t * lpcsz, int iCount);
       int   CLASS_DECL_ca UnicodeToMultiByteCount(UINT uiCodePage, const wchar_t * lpcsz);
       int   CLASS_DECL_ca UnicodeToMultiByteCount(UINT uiCodePage, const wchar_t * lpcsz, int iCount);
       bool CLASS_DECL_ca UnicodeToMultiByte(UINT uiCodePage, string & str, const wchar_t * lpcsz);
       bool CLASS_DECL_ca UnicodeToMultiByte(UINT uiCodePage, string & str, const wchar_t * lpcsz, int iCount);
       string CLASS_DECL_ca UnicodeToMultiByte(UINT uiCodePage, const wchar_t * lpcsz);

       bool CLASS_DECL_ca MultiByteToUnicode(UINT uiCodePage, wchar_t * lpwsz, int iBuffer, const char  * lpcsz, int iCount);
       bool CLASS_DECL_ca MultiByteToUnicode(UINT uiCodePage, wchar_t * lpwsz, int nCount, const char * lpcsz);
       CLASS_DECL_ca wstring MultiByteToUnicode(UINT uiCodePage, const char * lpcsz, int nCount);
       int  CLASS_DECL_ca MultiByteToUnicodeCount(UINT uiCodePage, const char * lpcsz);
       int  CLASS_DECL_ca MultiByteToUnicodeCount(UINT uiCodePage, const char * lpcsz, int iCount);
       CLASS_DECL_ca wstring MultiByteToUnicode(UINT uiCodePage, const char * lpcsz);

       bool CLASS_DECL_ca MultiByteToMultiByte(UINT uiCodePageDest, string & str, UINT uiCodePageSrc, const char * lpcsz);
       bool CLASS_DECL_ca MultiByteToMultiByte(UINT uiCodePageDest, string & str, UINT uiCodePageSrc, const char * lpcsz, int nCount);
       bool CLASS_DECL_ca MultiByteToMultiByte(UINT uiCodePageDest, char * lpsz, int nCount, UINT uiCodePageSrc, const char * lpcsz);

       bool CLASS_DECL_ca multibyte_to_utf8(UINT uiCodePageSrc, string & str, const char * lpcsz);
       bool CLASS_DECL_ca multibyte_to_utf8(UINT uiCodePageSrc, string & str, const char * lpcsz, int nCount);
       int   CLASS_DECL_ca Utf8ToMultiByteCount(UINT uiCodePage, const char * lpcsz);

       bool CLASS_DECL_ca MultiByteToOEM(UINT uiCodePage, string & str, const char * lpcsz);
       bool CLASS_DECL_ca MultiByteToOEM(UINT uiCodePage, string & str, const char * lpcsz, int nCount);

       bool CLASS_DECL_ca OEMToMultiByte(UINT uiCodePage, string & str, const char * lpcsz);
       bool CLASS_DECL_ca OEMToMultiByte(UINT uiCodePage, string & str, const char * lpcsz, int nCount);

       bool CLASS_DECL_ca utf8_to_multibyte(UINT uiCodePage, string & str, const char * lpcsz);
       bool CLASS_DECL_ca utf8_to_multibyte(UINT uiCodePage, string & str, const char * lpcsz, int nCount);
       bool CLASS_DECL_ca utf8_to_multibyte(UINT uiCodePageSrc, char * lpsz, int nCount, const char * lpcsz);

       bool CLASS_DECL_ca OemToUtf8(string & str, const char * lpcsz);
       bool CLASS_DECL_ca OemToUtf8(string & str, const char * lpcsz, int nCount);

       bool CLASS_DECL_ca unicode_to_utf8(string & str, const wchar_t * lpcsz);
       CLASS_DECL_ca wstring utf8_to_unicode(const char * lpcsz);
       CLASS_DECL_ca wstring utf8_to_unicode(const char * lpcsz, int iCount);
       bool CLASS_DECL_ca unicode_to_utf8(string & str, const wchar_t * lpcsz, int iCount);
       string CLASS_DECL_ca unicode_to_utf8(const wchar_t * lpcsz);

       bool CLASS_DECL_ca AcpToUtf8(string & str, const char * lpcsz);
       bool CLASS_DECL_ca AcpToUtf8(string & str, const char * lpcsz, int iSize);
       bool CLASS_DECL_ca AcpToUtf8(LPTSTR lpstrUnicode, int nCount, const char * lpcsz);

       bool CLASS_DECL_ca Utf8ToAcp(string & str, const char * lpcsz);

       bool CLASS_DECL_ca UnicodeToACP(string & str, const wchar_t * lpcsz);
       string CLASS_DECL_ca UnicodeToACP(const wchar_t * lpcsz);
       bool CLASS_DECL_ca UnicodeToACP(char * lpstrUnicode, int nCount, const wchar_t * lpcsz);
       CLASS_DECL_ca wstring ACPToUnicode(const char * lpcsz);
       CLASS_DECL_ca wstring ACPToUnicode(const char * lpcsz, int iSize);
       bool CLASS_DECL_ca ACPToUnicode(wchar_t * lpstrUnicode, int nCount, const char * lpcsz);
      
       bool CLASS_DECL_ca UnicodeToOEM(string & str, const wchar_t * lpcsz);
       bool CLASS_DECL_ca UnicodeToOEM(char * lpstrUnicode, int nCount, const wchar_t * lpcsz);
       CLASS_DECL_ca wstring OEMToUnicode(const char * lpcsz);
       bool CLASS_DECL_ca OEMToUnicode(wchar_t * lpstrUnicode, int nCount, const char * lpcsz);


      ///////////////////////////////////////////////////////////////
      // ACP ( GetACP() function) conversion
      ///////////////////////////////////////////////////////////////

      inline string UnicodeToMultiByte(UINT uiCodePage, const wchar_t * lpcsz)
      {
         string str;
         UnicodeToMultiByte(uiCodePage, str, lpcsz);
         return str;
      }

      inline bool UnicodeToACP(string & str, const wchar_t * lpcsz)
      {
         return UnicodeToMultiByte(g_uiACP, str, lpcsz);
      }

      inline bool UnicodeToACP(char * lpstrUnicode, int nCount, const wchar_t * lpcsz)
      {
         return UnicodeToMultiByte(g_uiACP, lpstrUnicode, nCount, lpcsz);
      }


      inline string UnicodeToACP(const wchar_t * lpcsz)
      {
         return UnicodeToMultiByte(CP_ACP, lpcsz);
      }


      inline bool ACPToUnicode(wchar_t * lpstrUnicode, int nCount, const char * lpcsz)
      {
         return MultiByteToUnicode(g_uiACP, lpstrUnicode, nCount, lpcsz);
      }

      inline wstring  ACPToUnicode(const char * lpcsz)
      {
         return MultiByteToUnicode(g_uiACP, lpcsz);
      }

      inline wstring  ACPToUnicode(const char * lpcsz, int iSize)
      {
         return MultiByteToUnicode(g_uiACP, lpcsz, iSize);
      }

      ///////////////////////////////////////////////////////////////
      // OEM ( GetOEM() function) conversion
      ///////////////////////////////////////////////////////////////

      inline bool UnicodeToOEM(string & str, const wchar_t * lpcsz)
      {
         return UnicodeToMultiByte(CodePageOem, str, lpcsz);
      }

      inline bool UnicodeToOEM(char * lpstrUnicode, int nCount, const wchar_t * lpcsz)
      {
         return UnicodeToMultiByte(CodePageOem, lpstrUnicode, nCount, lpcsz);
      }



      inline bool OEMToUnicode(wchar_t * lpstrUnicode, int nCount, const char * lpcsz)
      {
         return MultiByteToUnicode(CodePageOem, lpstrUnicode, nCount, lpcsz);
      }

      inline wstring OEMToUnicode(const char * lpcsz)
      {
         return MultiByteToUnicode(CodePageOem, lpcsz);
      }

      inline bool unicode_to_utf8(string & str, const wchar_t * lpcsz)
      {
         return UnicodeToMultiByte(CodePageUtf8, str, lpcsz);
      }

      inline wstring utf8_to_unicode(const char * lpcsz)
      {
         return MultiByteToUnicode(CodePageUtf8, lpcsz);
      }

      inline int utf8_to_unicode_count(const char * lpcsz)
      {
         return MultiByteToUnicodeCount(CodePageUtf8, lpcsz);
      }

      /*inline string UnicodeToACP(const wchar_t * lpcsz)
      {
         string str;
         UnicodeToMultiByte(g_uiACP, str, lpcsz);
         return str;
      }

      inline string ACPToUnicode(const char * lpcsz)
      {
         string str;
         MultiByteToUnicode(g_uiACP, str, lpcsz);
         return str;
      }
      */


      inline bool AcpToUtf8(string & str, const char * lpcsz)
      {
         return MultiByteToMultiByte(CodePageUtf8, str, CodePageAnsi, lpcsz);
      }

      inline bool Utf8ToAcp(string & str, const char * lpcsz)
      {
         return MultiByteToMultiByte(CodePageAnsi, str, CodePageUtf8, lpcsz);
      }


      inline bool multibyte_to_utf8(UINT uiCodePageSrc, string & str, const char * lpcsz)
      {
         return MultiByteToMultiByte(CP_UTF8, str, uiCodePageSrc, lpcsz);
      }

      inline bool multibyte_to_utf8(UINT uiCodePageSrc, string & str, const char * lpcsz, int nCount)
      {
         return MultiByteToMultiByte(CP_UTF8, str, uiCodePageSrc, lpcsz, nCount);
      }


      inline bool OemToUtf8(string & str, const char * lpcsz)
      {
         return MultiByteToMultiByte(CP_UTF8, str, CP_OEMCP, lpcsz);
      }

      inline bool OemToUtf8(string & str, const char * lpcsz, int nCount)
      {
         return MultiByteToMultiByte(CP_UTF8, str, CP_OEMCP, lpcsz, nCount);
      }

      inline wstring utf8_to_unicode(const char * lpcsz, int iCount)
      {
         return MultiByteToUnicode(CP_UTF8, lpcsz, iCount);
      }

      inline bool utf8_to_unicode(wchar_t * lpwsz, int iBuffer, const char * lpcsz, int iCount)
      {
         return MultiByteToUnicode(CP_UTF8, lpwsz, iBuffer, lpcsz, iCount);
      }

      inline bool utf8_to_unicode(wchar_t * lpwsz, int iBuffer, const char * lpcsz)
      {
         return utf8_to_unicode(lpwsz, iBuffer, lpcsz, -1);
      }

      inline bool utf8_to_multibyte(UINT uiCodePage, string & str, const char * lpcsz)
      {
         return MultiByteToMultiByte(CodePageUtf8, str, uiCodePage, lpcsz);
      }

      inline bool utf8_to_multibyte(UINT uiCodePage, string & str, const char * lpcsz, int nCount)
      {
         return MultiByteToMultiByte(CodePageUtf8, str, uiCodePage, lpcsz, nCount);
      }

      inline bool utf8_to_multibyte(UINT uiCodePage, char * lpsz, int nCount, const char * lpcsz)
      {
         return MultiByteToMultiByte(CodePageUtf8, lpsz, nCount, uiCodePage, lpcsz);
      }


      inline bool AcpToUtf8(LPTSTR lpstrUnicode, int nCount, const char * lpcsz)
      {
         return MultiByteToMultiByte(CP_UTF8, lpstrUnicode, nCount, g_uiACP, lpcsz);
      }

      inline bool AcpToUtf8(string & str, const char * lpcsz, int iSize)
      {
         return MultiByteToMultiByte(CP_UTF8, str, g_uiACP, lpcsz, iSize);
      }


   } // namespace international

} // namespace gen

#define unitext(text) (::gen::international::unicode_to_utf8(L##text))