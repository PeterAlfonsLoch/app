#pragma once


class var;


namespace gen
{


   namespace international
   {


      extern UINT g_uiACP;
      enum ECodePage
      {
         CodePageShiftJIS = 932,
         CodePageLatin1 = 1252,
#ifdef WINDOWS
         CodePageUtf8 = CP_UTF8,
         CodePageAnsi = CP_ACP,
         CodePageOem = CP_OEMCP,
#else
         CodePageUtf8 = 65001,
         CodePageAnsi = 10,
         CodePageOem = 11,
#endif
      };


       bool CLASS_DECL_ca UnicodeToMultiByte(UINT uiCodePage, char * lpsz, strsize nCount, const wchar_t * lpcsz);
       bool CLASS_DECL_ca UnicodeToMultiByte(UINT uiCodePage, char * lpsz, strsize iBuffer, const wchar_t * lpcsz, strsize iCount);
       strsize   CLASS_DECL_ca UnicodeToMultiByteCount(UINT uiCodePage, const wchar_t * lpcsz);
       strsize   CLASS_DECL_ca UnicodeToMultiByteCount(UINT uiCodePage, const wchar_t * lpcsz, strsize iCount);
       bool CLASS_DECL_ca UnicodeToMultiByte(UINT uiCodePage, string & str, const wchar_t * lpcsz);
       bool CLASS_DECL_ca UnicodeToMultiByte(UINT uiCodePage, string & str, const wchar_t * lpcsz, strsize iCount);
       string CLASS_DECL_ca UnicodeToMultiByte(UINT uiCodePage, const wchar_t * lpcsz);

       bool CLASS_DECL_ca MultiByteToUnicode(UINT uiCodePage, wchar_t * lpwsz, strsize iBuffer, const char  * lpcsz, strsize iCount);
       bool CLASS_DECL_ca MultiByteToUnicode(UINT uiCodePage, wchar_t * lpwsz, strsize nCount, const char * lpcsz);
       CLASS_DECL_ca wstring MultiByteToUnicode(UINT uiCodePage, const char * lpcsz, strsize nCount);
       CLASS_DECL_ca wstring MultiByteToUnicode(UINT uiCodePage, const string & str);
       strsize  CLASS_DECL_ca MultiByteToUnicodeCount(UINT uiCodePage, const char * lpcsz);
       strsize  CLASS_DECL_ca MultiByteToUnicodeCount(UINT uiCodePage, const char * lpcsz, strsize iCount);
       CLASS_DECL_ca wstring MultiByteToUnicode(UINT uiCodePage, const char * lpcsz);

       bool CLASS_DECL_ca MultiByteToMultiByte(UINT uiCodePageDest, string & str, UINT uiCodePageSrc, const char * lpcsz);
       bool CLASS_DECL_ca MultiByteToMultiByte(UINT uiCodePageDest, string & str, UINT uiCodePageSrc, const char * lpcsz, strsize nCount);
       bool CLASS_DECL_ca MultiByteToMultiByte(UINT uiCodePageDest, char * lpsz, strsize nCount, UINT uiCodePageSrc, const char * lpcsz);

       bool CLASS_DECL_ca multibyte_to_utf8(UINT uiCodePageSrc, string & str, const char * lpcsz);
       bool CLASS_DECL_ca multibyte_to_utf8(UINT uiCodePageSrc, string & str, const char * lpcsz, strsize nCount);
       strsize   CLASS_DECL_ca Utf8ToMultiByteCount(UINT uiCodePage, const char * lpcsz);

       bool CLASS_DECL_ca MultiByteToOEM(UINT uiCodePage, string & str, const char * lpcsz);
       bool CLASS_DECL_ca MultiByteToOEM(UINT uiCodePage, string & str, const char * lpcsz, strsize nCount);

       bool CLASS_DECL_ca OEMToMultiByte(UINT uiCodePage, string & str, const char * lpcsz);
       bool CLASS_DECL_ca OEMToMultiByte(UINT uiCodePage, string & str, const char * lpcsz, strsize nCount);

       bool CLASS_DECL_ca utf8_to_multibyte(UINT uiCodePage, string & str, const char * lpcsz);
       bool CLASS_DECL_ca utf8_to_multibyte(UINT uiCodePage, string & str, const char * lpcsz, strsize nCount);
       bool CLASS_DECL_ca utf8_to_multibyte(UINT uiCodePageSrc, char * lpsz, strsize nCount, const char * lpcsz);

       bool CLASS_DECL_ca OemToUtf8(string & str, const char * lpcsz);
       bool CLASS_DECL_ca OemToUtf8(string & str, const char * lpcsz, strsize nCount);

       bool CLASS_DECL_ca unicode_to_utf8(string & str, const wchar_t * lpcsz);
       CLASS_DECL_ca wstring utf8_to_unicode(const char * lpcsz);
       CLASS_DECL_ca wstring utf8_to_unicode(const string & str);
       CLASS_DECL_ca wstring utf8_to_unicode(const var & var);
       CLASS_DECL_ca wstring utf8_to_unicode(const char * lpcsz, strsize iCount);
       bool CLASS_DECL_ca unicode_to_utf8(string & str, const wchar_t * lpcsz, strsize iCount);
       string CLASS_DECL_ca unicode_to_utf8(const wchar_t * lpcsz);

       bool CLASS_DECL_ca AcpToUtf8(string & str, const char * lpcsz);
       bool CLASS_DECL_ca AcpToUtf8(string & str, const char * lpcsz, strsize iSize);
       bool CLASS_DECL_ca AcpToUtf8(LPTSTR lpstrUnicode, strsize nCount, const char * lpcsz);

       bool CLASS_DECL_ca Utf8ToAcp(string & str, const char * lpcsz);

       bool CLASS_DECL_ca UnicodeToACP(string & str, const wchar_t * lpcsz);
       string CLASS_DECL_ca UnicodeToACP(const wchar_t * lpcsz);
       bool CLASS_DECL_ca UnicodeToACP(char * lpstrUnicode, strsize nCount, const wchar_t * lpcsz);
       CLASS_DECL_ca wstring ACPToUnicode(const char * lpcsz);
       CLASS_DECL_ca wstring ACPToUnicode(const char * lpcsz, strsize iSize);
       bool CLASS_DECL_ca ACPToUnicode(wchar_t * lpstrUnicode, strsize nCount, const char * lpcsz);

       bool CLASS_DECL_ca UnicodeToOEM(string & str, const wchar_t * lpcsz);
       bool CLASS_DECL_ca UnicodeToOEM(char * lpstrUnicode, strsize nCount, const wchar_t * lpcsz);
       CLASS_DECL_ca wstring OEMToUnicode(const char * lpcsz);
       bool CLASS_DECL_ca OEMToUnicode(wchar_t * lpstrUnicode, strsize nCount, const char * lpcsz);


      ///////////////////////////////////////////////////////////////
      // ACP ( GetACP() function) conversion
      ///////////////////////////////////////////////////////////////

      CLASS_DECL_ca string UnicodeToMultiByte(UINT uiCodePage, const wchar_t * lpcsz);
      CLASS_DECL_ca bool UnicodeToACP(string & str, const wchar_t * lpcsz);
      CLASS_DECL_ca bool UnicodeToACP(char * lpstrUnicode, strsize nCount, const wchar_t * lpcsz);
      CLASS_DECL_ca string UnicodeToACP(const wchar_t * lpcsz);
      CLASS_DECL_ca bool ACPToUnicode(wchar_t * lpstrUnicode, strsize nCount, const char * lpcsz);
      CLASS_DECL_ca wstring  ACPToUnicode(const char * lpcsz);
      CLASS_DECL_ca wstring  ACPToUnicode(const char * lpcsz, strsize iSize);

      ///////////////////////////////////////////////////////////////
      // OEM ( GetOEM() function) conversion
      ///////////////////////////////////////////////////////////////

      CLASS_DECL_ca bool UnicodeToOEM(string & str, const wchar_t * lpcsz);
      CLASS_DECL_ca bool UnicodeToOEM(char * lpstrUnicode, strsize nCount, const wchar_t * lpcsz);
      CLASS_DECL_ca bool OEMToUnicode(wchar_t * lpstrUnicode, strsize nCount, const char * lpcsz);
      CLASS_DECL_ca wstring OEMToUnicode(const char * lpcsz);
      CLASS_DECL_ca bool unicode_to_utf8(string & str, const wchar_t * lpcsz);
      CLASS_DECL_ca wstring utf8_to_unicode(const char * lpcsz);
      CLASS_DECL_ca strsize utf8_to_unicode_count(const char * lpcsz, strsize count = -1);
      CLASS_DECL_ca strsize utf8_to_unicode_count(const string & str);

      /*
      CLASS_DECL_ca string UnicodeToACP(const wchar_t * lpcsz);
      CLASS_DECL_ca string ACPToUnicode(const char * lpcsz);
      */

      CLASS_DECL_ca bool AcpToUtf8(string & str, const char * lpcsz);
      CLASS_DECL_ca bool Utf8ToAcp(string & str, const char * lpcsz);
      CLASS_DECL_ca bool multibyte_to_utf8(UINT uiCodePageSrc, string & str, const char * lpcsz);
      CLASS_DECL_ca bool multibyte_to_utf8(UINT uiCodePageSrc, string & str, const char * lpcsz, strsize nCount);
      CLASS_DECL_ca bool OemToUtf8(string & str, const char * lpcsz);
      CLASS_DECL_ca bool OemToUtf8(string & str, const char * lpcsz, strsize nCount);
      CLASS_DECL_ca wstring utf8_to_unicode(const char * lpcsz, strsize iCount);
      CLASS_DECL_ca bool utf8_to_unicode(wchar_t * lpwsz, strsize iBuffer, const char * lpcsz, strsize iCount);
      CLASS_DECL_ca bool utf8_to_unicode(wchar_t * lpwsz, strsize iBuffer, const char * lpcsz);
      CLASS_DECL_ca bool utf8_to_multibyte(UINT uiCodePage, string & str, const char * lpcsz);
      CLASS_DECL_ca bool utf8_to_multibyte(UINT uiCodePage, string & str, const char * lpcsz, strsize nCount);
      CLASS_DECL_ca bool utf8_to_multibyte(UINT uiCodePage, char * lpsz, strsize nCount, const char * lpcsz);
      CLASS_DECL_ca bool AcpToUtf8(LPTSTR lpstrUnicode, strsize nCount, const char * lpcsz);
      CLASS_DECL_ca bool AcpToUtf8(string & str, const char * lpcsz, strsize iSize);


   } // namespace international


} // namespace gen


#define unitext(text) (::gen::international::unicode_to_utf8(L##text))
