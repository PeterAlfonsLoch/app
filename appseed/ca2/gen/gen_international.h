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
#ifdef _WINDOWS
         CodePageUtf8 = CP_UTF8,
         CodePageAnsi = CP_ACP,
         CodePageOem = CP_OEMCP,
#else
         CodePageUtf8 = 65001,
         CodePageAnsi = 10,
         CodePageOem = 11,
#endif
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

      CLASS_DECL_ca string UnicodeToMultiByte(UINT uiCodePage, const wchar_t * lpcsz);
      CLASS_DECL_ca bool UnicodeToACP(string & str, const wchar_t * lpcsz);
      CLASS_DECL_ca bool UnicodeToACP(char * lpstrUnicode, int nCount, const wchar_t * lpcsz);
      CLASS_DECL_ca string UnicodeToACP(const wchar_t * lpcsz);
      CLASS_DECL_ca bool ACPToUnicode(wchar_t * lpstrUnicode, int nCount, const char * lpcsz);
      CLASS_DECL_ca wstring  ACPToUnicode(const char * lpcsz);
      CLASS_DECL_ca wstring  ACPToUnicode(const char * lpcsz, int iSize);

      ///////////////////////////////////////////////////////////////
      // OEM ( GetOEM() function) conversion
      ///////////////////////////////////////////////////////////////

      CLASS_DECL_ca bool UnicodeToOEM(string & str, const wchar_t * lpcsz);
      CLASS_DECL_ca bool UnicodeToOEM(char * lpstrUnicode, int nCount, const wchar_t * lpcsz);
      CLASS_DECL_ca bool OEMToUnicode(wchar_t * lpstrUnicode, int nCount, const char * lpcsz);
      CLASS_DECL_ca wstring OEMToUnicode(const char * lpcsz);
      CLASS_DECL_ca bool unicode_to_utf8(string & str, const wchar_t * lpcsz);
      CLASS_DECL_ca wstring utf8_to_unicode(const char * lpcsz);
      CLASS_DECL_ca int utf8_to_unicode_count(const char * lpcsz);

      /*
      CLASS_DECL_ca string UnicodeToACP(const wchar_t * lpcsz);
      CLASS_DECL_ca string ACPToUnicode(const char * lpcsz);
      */

      CLASS_DECL_ca bool AcpToUtf8(string & str, const char * lpcsz);
      CLASS_DECL_ca bool Utf8ToAcp(string & str, const char * lpcsz);
      CLASS_DECL_ca bool multibyte_to_utf8(UINT uiCodePageSrc, string & str, const char * lpcsz);
      CLASS_DECL_ca bool multibyte_to_utf8(UINT uiCodePageSrc, string & str, const char * lpcsz, int nCount);
      CLASS_DECL_ca bool OemToUtf8(string & str, const char * lpcsz);
      CLASS_DECL_ca bool OemToUtf8(string & str, const char * lpcsz, int nCount);
      CLASS_DECL_ca wstring utf8_to_unicode(const char * lpcsz, int iCount);
      CLASS_DECL_ca bool utf8_to_unicode(wchar_t * lpwsz, int iBuffer, const char * lpcsz, int iCount);
      CLASS_DECL_ca bool utf8_to_unicode(wchar_t * lpwsz, int iBuffer, const char * lpcsz);
      CLASS_DECL_ca bool utf8_to_multibyte(UINT uiCodePage, string & str, const char * lpcsz);
      CLASS_DECL_ca bool utf8_to_multibyte(UINT uiCodePage, string & str, const char * lpcsz, int nCount);
      CLASS_DECL_ca bool utf8_to_multibyte(UINT uiCodePage, char * lpsz, int nCount, const char * lpcsz);
      CLASS_DECL_ca bool AcpToUtf8(LPTSTR lpstrUnicode, int nCount, const char * lpcsz);
      CLASS_DECL_ca bool AcpToUtf8(string & str, const char * lpcsz, int iSize);


   } // namespace international

} // namespace gen

#define unitext(text) (::gen::international::unicode_to_utf8(L##text))
