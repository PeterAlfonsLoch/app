#pragma once


class var;


namespace ca
{


   namespace international
   {


//      extern UINT g_uiACP;
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


       bool CLASS_DECL_ca2 UnicodeToMultiByte(UINT uiCodePage, char * lpsz, strsize nCount, const wchar_t * lpcsz);
       bool CLASS_DECL_ca2 UnicodeToMultiByte(UINT uiCodePage, char * lpsz, strsize iBuffer, const wchar_t * lpcsz, strsize iCount);
       strsize   CLASS_DECL_ca2 UnicodeToMultiByteCount(UINT uiCodePage, const wchar_t * lpcsz);
       strsize   CLASS_DECL_ca2 UnicodeToMultiByteCount(UINT uiCodePage, const wchar_t * lpcsz, strsize iCount);
       bool CLASS_DECL_ca2 UnicodeToMultiByte(UINT uiCodePage, string & str, const wchar_t * lpcsz);
       bool CLASS_DECL_ca2 UnicodeToMultiByte(UINT uiCodePage, string & str, const wchar_t * lpcsz, strsize iCount);
       string CLASS_DECL_ca2 UnicodeToMultiByte(UINT uiCodePage, const wchar_t * lpcsz);

       bool CLASS_DECL_ca2 MultiByteToUnicode(UINT uiCodePage, wchar_t * lpwsz, strsize iBuffer, const char  * lpcsz, strsize iCount);
       bool CLASS_DECL_ca2 MultiByteToUnicode(UINT uiCodePage, wchar_t * lpwsz, strsize nCount, const char * lpcsz);
       CLASS_DECL_ca2 wstring MultiByteToUnicode(UINT uiCodePage, const char * lpcsz, strsize nCount);
       CLASS_DECL_ca2 wstring MultiByteToUnicode(UINT uiCodePage, const string & str);
       strsize  CLASS_DECL_ca2 MultiByteToUnicodeCount(UINT uiCodePage, const char * lpcsz);
       strsize  CLASS_DECL_ca2 MultiByteToUnicodeCount(UINT uiCodePage, const char * lpcsz, strsize iCount);
       CLASS_DECL_ca2 wstring MultiByteToUnicode(UINT uiCodePage, const char * lpcsz);

       bool CLASS_DECL_ca2 MultiByteToMultiByte(UINT uiCodePageDest, string & str, UINT uiCodePageSrc, const char * lpcsz);
       bool CLASS_DECL_ca2 MultiByteToMultiByte(UINT uiCodePageDest, string & str, UINT uiCodePageSrc, const char * lpcsz, strsize nCount);
       bool CLASS_DECL_ca2 MultiByteToMultiByte(UINT uiCodePageDest, char * lpsz, strsize nCount, UINT uiCodePageSrc, const char * lpcsz);

       bool CLASS_DECL_ca2 multibyte_to_utf8(UINT uiCodePageSrc, string & str, const char * lpcsz);
       bool CLASS_DECL_ca2 multibyte_to_utf8(UINT uiCodePageSrc, string & str, const char * lpcsz, strsize nCount);
       strsize   CLASS_DECL_ca2 Utf8ToMultiByteCount(UINT uiCodePage, const char * lpcsz);

       //bool CLASS_DECL_ca2 MultiByteToOEM(UINT uiCodePage, string & str, const char * lpcsz);
       //bool CLASS_DECL_ca2 MultiByteToOEM(UINT uiCodePage, string & str, const char * lpcsz, strsize nCount);

       //bool CLASS_DECL_ca2 OEMToMultiByte(UINT uiCodePage, string & str, const char * lpcsz);
       //bool CLASS_DECL_ca2 OEMToMultiByte(UINT uiCodePage, string & str, const char * lpcsz, strsize nCount);

       bool CLASS_DECL_ca2 utf8_to_multibyte(UINT uiCodePage, string & str, const char * lpcsz);
       bool CLASS_DECL_ca2 utf8_to_multibyte(UINT uiCodePage, string & str, const char * lpcsz, strsize nCount);
       bool CLASS_DECL_ca2 utf8_to_multibyte(UINT uiCodePageSrc, char * lpsz, strsize nCount, const char * lpcsz);

       //bool CLASS_DECL_ca2 OemToUtf8(string & str, const char * lpcsz);
       //bool CLASS_DECL_ca2 OemToUtf8(string & str, const char * lpcsz, strsize nCount);

       bool CLASS_DECL_ca2 unicode_to_utf8(string & str, const wchar_t * lpcsz);
       CLASS_DECL_ca2 wstring utf8_to_unicode(const char * lpcsz);
       CLASS_DECL_ca2 wstring utf8_to_unicode(const string & str);
       CLASS_DECL_ca2 wstring utf8_to_unicode(const var & var);
       CLASS_DECL_ca2 wstring utf8_to_unicode(const char * lpcsz, strsize iCount);
       bool CLASS_DECL_ca2 unicode_to_utf8(string & str, const wchar_t * lpcsz, strsize iCount);
       string CLASS_DECL_ca2 unicode_to_utf8(const wchar_t * lpcsz);

/*       bool CLASS_DECL_ca2 AcpToUtf8(string & str, const char * lpcsz);
       bool CLASS_DECL_ca2 AcpToUtf8(string & str, const char * lpcsz, strsize iSize);
       bool CLASS_DECL_ca2 AcpToUtf8(LPTSTR lpstrUnicode, strsize nCount, const char * lpcsz);

       bool CLASS_DECL_ca2 Utf8ToAcp(string & str, const char * lpcsz);

       bool CLASS_DECL_ca2 UnicodeToACP(string & str, const wchar_t * lpcsz);
       string CLASS_DECL_ca2 UnicodeToACP(const wchar_t * lpcsz);
       bool CLASS_DECL_ca2 UnicodeToACP(char * lpstrUnicode, strsize nCount, const wchar_t * lpcsz);
       CLASS_DECL_ca2 wstring ACPToUnicode(const char * lpcsz);
       CLASS_DECL_ca2 wstring ACPToUnicode(const char * lpcsz, strsize iSize);
       bool CLASS_DECL_ca2 ACPToUnicode(wchar_t * lpstrUnicode, strsize nCount, const char * lpcsz);

       bool CLASS_DECL_ca2 UnicodeToOEM(string & str, const wchar_t * lpcsz);
       bool CLASS_DECL_ca2 UnicodeToOEM(char * lpstrUnicode, strsize nCount, const wchar_t * lpcsz);
       CLASS_DECL_ca2 wstring OEMToUnicode(const char * lpcsz);
       bool CLASS_DECL_ca2 OEMToUnicode(wchar_t * lpstrUnicode, strsize nCount, const char * lpcsz);
       */

      ///////////////////////////////////////////////////////////////
      // ACP ( GetACP() function) conversion
      ///////////////////////////////////////////////////////////////

      CLASS_DECL_ca2 string UnicodeToMultiByte(UINT uiCodePage, const wchar_t * lpcsz);
      //CLASS_DECL_ca2 bool UnicodeToACP(string & str, const wchar_t * lpcsz);
      //CLASS_DECL_ca2 bool UnicodeToACP(char * lpstrUnicode, strsize nCount, const wchar_t * lpcsz);
      //CLASS_DECL_ca2 string UnicodeToACP(const wchar_t * lpcsz);
      //CLASS_DECL_ca2 bool ACPToUnicode(wchar_t * lpstrUnicode, strsize nCount, const char * lpcsz);
      //CLASS_DECL_ca2 wstring  ACPToUnicode(const char * lpcsz);
      //CLASS_DECL_ca2 wstring  ACPToUnicode(const char * lpcsz, strsize iSize);

      ///////////////////////////////////////////////////////////////
      // OEM ( GetOEM() function) conversion
      ///////////////////////////////////////////////////////////////

      //CLASS_DECL_ca2 bool UnicodeToOEM(string & str, const wchar_t * lpcsz);
      //CLASS_DECL_ca2 bool UnicodeToOEM(char * lpstrUnicode, strsize nCount, const wchar_t * lpcsz);
      //CLASS_DECL_ca2 bool OEMToUnicode(wchar_t * lpstrUnicode, strsize nCount, const char * lpcsz);
      //CLASS_DECL_ca2 wstring OEMToUnicode(const char * lpcsz);
      CLASS_DECL_ca2 bool unicode_to_utf8(string & str, const wchar_t * lpcsz);
      CLASS_DECL_ca2 wstring utf8_to_unicode(const char * lpcsz);
      CLASS_DECL_ca2 strsize utf8_to_unicode_count(const char * lpcsz, strsize count = -1);
      CLASS_DECL_ca2 strsize utf8_to_unicode_count(const string & str);

      /*
      CLASS_DECL_ca2 string UnicodeToACP(const wchar_t * lpcsz);
      CLASS_DECL_ca2 string ACPToUnicode(const char * lpcsz);
      */

      //CLASS_DECL_ca2 bool AcpToUtf8(string & str, const char * lpcsz);
      //CLASS_DECL_ca2 bool Utf8ToAcp(string & str, const char * lpcsz);
      CLASS_DECL_ca2 bool multibyte_to_utf8(UINT uiCodePageSrc, string & str, const char * lpcsz);
      CLASS_DECL_ca2 bool multibyte_to_utf8(UINT uiCodePageSrc, string & str, const char * lpcsz, strsize nCount);
      //CLASS_DECL_ca2 bool OemToUtf8(string & str, const char * lpcsz);
      //CLASS_DECL_ca2 bool OemToUtf8(string & str, const char * lpcsz, strsize nCount);
      CLASS_DECL_ca2 wstring utf8_to_unicode(const char * lpcsz, strsize iCount);
      CLASS_DECL_ca2 bool utf8_to_unicode(wchar_t * lpwsz, strsize iBuffer, const char * lpcsz, strsize iCount);
      CLASS_DECL_ca2 bool utf8_to_unicode(wchar_t * lpwsz, strsize iBuffer, const char * lpcsz);
      CLASS_DECL_ca2 bool utf8_to_multibyte(UINT uiCodePage, string & str, const char * lpcsz);
      CLASS_DECL_ca2 bool utf8_to_multibyte(UINT uiCodePage, string & str, const char * lpcsz, strsize nCount);
      CLASS_DECL_ca2 bool utf8_to_multibyte(UINT uiCodePage, char * lpsz, strsize nCount, const char * lpcsz);
      //CLASS_DECL_ca2 bool AcpToUtf8(LPTSTR lpstrUnicode, strsize nCount, const char * lpcsz);
      //CLASS_DECL_ca2 bool AcpToUtf8(string & str, const char * lpcsz, strsize iSize);


   } // namespace international


} // namespace ca


#define unitext(text) (::ca::international::unicode_to_utf8(L##text))
