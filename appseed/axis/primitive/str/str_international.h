#pragma once


class var;


namespace str
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
         CodePageOem = 11
#endif
      };


       bool CLASS_DECL_AXIS UnicodeToMultiByte(UINT uiCodePage, char * lpsz, strsize nCount, const wchar_t * lpcsz);
       bool CLASS_DECL_AXIS UnicodeToMultiByte(UINT uiCodePage, char * lpsz, strsize iBuffer, const wchar_t * lpcsz, strsize iCount);
       strsize   CLASS_DECL_AXIS UnicodeToMultiByteCount(UINT uiCodePage, const wchar_t * lpcsz);
       strsize   CLASS_DECL_AXIS UnicodeToMultiByteCount(UINT uiCodePage, const wchar_t * lpcsz, strsize iCount);
       bool CLASS_DECL_AXIS UnicodeToMultiByte(UINT uiCodePage, string & str, const wchar_t * lpcsz);
       bool CLASS_DECL_AXIS UnicodeToMultiByte(UINT uiCodePage, string & str, const wchar_t * lpcsz, strsize iCount);
       string CLASS_DECL_AXIS UnicodeToMultiByte(UINT uiCodePage, const wchar_t * lpcsz);

       bool CLASS_DECL_AXIS MultiByteToUnicode(UINT uiCodePage, wchar_t * lpwsz, strsize iBuffer, const char  * lpcsz, strsize iCount);
       bool CLASS_DECL_AXIS MultiByteToUnicode(UINT uiCodePage, wchar_t * lpwsz, strsize nCount, const char * lpcsz);
       CLASS_DECL_AXIS wstring MultiByteToUnicode(UINT uiCodePage, const char * lpcsz, strsize nCount);
       CLASS_DECL_AXIS wstring MultiByteToUnicode(UINT uiCodePage, const string & str);
       strsize  CLASS_DECL_AXIS MultiByteToUnicodeCount(UINT uiCodePage, const char * lpcsz);
       strsize  CLASS_DECL_AXIS MultiByteToUnicodeCount(UINT uiCodePage, const char * lpcsz, strsize iCount);
       CLASS_DECL_AXIS wstring MultiByteToUnicode(UINT uiCodePage, const char * lpcsz);

       bool CLASS_DECL_AXIS MultiByteToMultiByte(UINT uiCodePageDest, string & str, UINT uiCodePageSrc, const char * lpcsz);
       bool CLASS_DECL_AXIS MultiByteToMultiByte(UINT uiCodePageDest, string & str, UINT uiCodePageSrc, const char * lpcsz, strsize nCount);
       bool CLASS_DECL_AXIS MultiByteToMultiByte(UINT uiCodePageDest, char * lpsz, strsize nCount, UINT uiCodePageSrc, const char * lpcsz);

       bool CLASS_DECL_AXIS multibyte_to_utf8(UINT uiCodePageSrc, string & str, const char * lpcsz);
       bool CLASS_DECL_AXIS multibyte_to_utf8(UINT uiCodePageSrc, string & str, const char * lpcsz, strsize nCount);
       strsize   CLASS_DECL_AXIS Utf8ToMultiByteCount(UINT uiCodePage, const char * lpcsz);

       //bool CLASS_DECL_AXIS MultiByteToOEM(UINT uiCodePage, string & str, const char * lpcsz);
       //bool CLASS_DECL_AXIS MultiByteToOEM(UINT uiCodePage, string & str, const char * lpcsz, strsize nCount);

       //bool CLASS_DECL_AXIS OEMToMultiByte(UINT uiCodePage, string & str, const char * lpcsz);
       //bool CLASS_DECL_AXIS OEMToMultiByte(UINT uiCodePage, string & str, const char * lpcsz, strsize nCount);

       bool CLASS_DECL_AXIS utf8_to_multibyte(UINT uiCodePage, string & str, const char * lpcsz);
       bool CLASS_DECL_AXIS utf8_to_multibyte(UINT uiCodePage, string & str, const char * lpcsz, strsize nCount);
       bool CLASS_DECL_AXIS utf8_to_multibyte(UINT uiCodePageSrc, char * lpsz, strsize nCount, const char * lpcsz);

       //bool CLASS_DECL_AXIS OemToUtf8(string & str, const char * lpcsz);
       //bool CLASS_DECL_AXIS OemToUtf8(string & str, const char * lpcsz, strsize nCount);

       bool CLASS_DECL_AXIS unicode_to_utf8(string & str, const wchar_t * lpcsz);
       CLASS_DECL_AXIS wstring utf8_to_unicode(const char * lpcsz);
       CLASS_DECL_AXIS wstring utf8_to_unicode(const string & str);
       CLASS_DECL_AXIS wstring utf8_to_unicode(const var & var);
       CLASS_DECL_AXIS wstring utf8_to_unicode(const char * lpcsz, strsize iCount);
       bool CLASS_DECL_AXIS unicode_to_utf8(string & str, const wchar_t * lpcsz, strsize iCount);
       string CLASS_DECL_AXIS unicode_to_utf8(const wchar_t * lpcsz);

/*       bool CLASS_DECL_AXIS AcpToUtf8(string & str, const char * lpcsz);
       bool CLASS_DECL_AXIS AcpToUtf8(string & str, const char * lpcsz, strsize iSize);
       bool CLASS_DECL_AXIS AcpToUtf8(LPTSTR lpstrUnicode, strsize nCount, const char * lpcsz);

       bool CLASS_DECL_AXIS Utf8ToAcp(string & str, const char * lpcsz);

       bool CLASS_DECL_AXIS UnicodeToACP(string & str, const wchar_t * lpcsz);
       string CLASS_DECL_AXIS UnicodeToACP(const wchar_t * lpcsz);
       bool CLASS_DECL_AXIS UnicodeToACP(char * lpstrUnicode, strsize nCount, const wchar_t * lpcsz);
       CLASS_DECL_AXIS wstring ACPToUnicode(const char * lpcsz);
       CLASS_DECL_AXIS wstring ACPToUnicode(const char * lpcsz, strsize iSize);
       bool CLASS_DECL_AXIS ACPToUnicode(wchar_t * lpstrUnicode, strsize nCount, const char * lpcsz);

       bool CLASS_DECL_AXIS UnicodeToOEM(string & str, const wchar_t * lpcsz);
       bool CLASS_DECL_AXIS UnicodeToOEM(char * lpstrUnicode, strsize nCount, const wchar_t * lpcsz);
       CLASS_DECL_AXIS wstring OEMToUnicode(const char * lpcsz);
       bool CLASS_DECL_AXIS OEMToUnicode(wchar_t * lpstrUnicode, strsize nCount, const char * lpcsz);
       */

      ///////////////////////////////////////////////////////////////
      // ACP ( GetACP() function) conversion
      ///////////////////////////////////////////////////////////////

      CLASS_DECL_AXIS string UnicodeToMultiByte(UINT uiCodePage, const wchar_t * lpcsz);
      //CLASS_DECL_AXIS bool UnicodeToACP(string & str, const wchar_t * lpcsz);
      //CLASS_DECL_AXIS bool UnicodeToACP(char * lpstrUnicode, strsize nCount, const wchar_t * lpcsz);
      //CLASS_DECL_AXIS string UnicodeToACP(const wchar_t * lpcsz);
      //CLASS_DECL_AXIS bool ACPToUnicode(wchar_t * lpstrUnicode, strsize nCount, const char * lpcsz);
      //CLASS_DECL_AXIS wstring  ACPToUnicode(const char * lpcsz);
      //CLASS_DECL_AXIS wstring  ACPToUnicode(const char * lpcsz, strsize iSize);

      ///////////////////////////////////////////////////////////////
      // OEM ( GetOEM() function) conversion
      ///////////////////////////////////////////////////////////////

      //CLASS_DECL_AXIS bool UnicodeToOEM(string & str, const wchar_t * lpcsz);
      //CLASS_DECL_AXIS bool UnicodeToOEM(char * lpstrUnicode, strsize nCount, const wchar_t * lpcsz);
      //CLASS_DECL_AXIS bool OEMToUnicode(wchar_t * lpstrUnicode, strsize nCount, const char * lpcsz);
      //CLASS_DECL_AXIS wstring OEMToUnicode(const char * lpcsz);
      CLASS_DECL_AXIS bool unicode_to_utf8(string & str, const wchar_t * lpcsz);
      CLASS_DECL_AXIS wstring utf8_to_unicode(const char * lpcsz);
      CLASS_DECL_AXIS strsize utf8_to_unicode_count(const char * lpcsz, strsize count = -1);
      CLASS_DECL_AXIS strsize utf8_to_unicode_count(const string & str);

      /*
      CLASS_DECL_AXIS string UnicodeToACP(const wchar_t * lpcsz);
      CLASS_DECL_AXIS string ACPToUnicode(const char * lpcsz);
      */

      //CLASS_DECL_AXIS bool AcpToUtf8(string & str, const char * lpcsz);
      //CLASS_DECL_AXIS bool Utf8ToAcp(string & str, const char * lpcsz);
      CLASS_DECL_AXIS bool multibyte_to_utf8(UINT uiCodePageSrc, string & str, const char * lpcsz);
      CLASS_DECL_AXIS bool multibyte_to_utf8(UINT uiCodePageSrc, string & str, const char * lpcsz, strsize nCount);
      //CLASS_DECL_AXIS bool OemToUtf8(string & str, const char * lpcsz);
      //CLASS_DECL_AXIS bool OemToUtf8(string & str, const char * lpcsz, strsize nCount);
      CLASS_DECL_AXIS wstring utf8_to_unicode(const char * lpcsz, strsize iCount);
      CLASS_DECL_AXIS bool utf8_to_unicode(wchar_t * lpwsz, strsize iBuffer, const char * lpcsz, strsize iCount);
      CLASS_DECL_AXIS bool utf8_to_unicode(wchar_t * lpwsz, strsize iBuffer, const char * lpcsz);
      CLASS_DECL_AXIS bool utf8_to_multibyte(UINT uiCodePage, string & str, const char * lpcsz);
      CLASS_DECL_AXIS bool utf8_to_multibyte(UINT uiCodePage, string & str, const char * lpcsz, strsize nCount);
      CLASS_DECL_AXIS bool utf8_to_multibyte(UINT uiCodePage, char * lpsz, strsize nCount, const char * lpcsz);
      //CLASS_DECL_AXIS bool AcpToUtf8(LPTSTR lpstrUnicode, strsize nCount, const char * lpcsz);
      //CLASS_DECL_AXIS bool AcpToUtf8(string & str, const char * lpcsz, strsize iSize);


   } // namespace international


} // namespace str


#define unitext(text) (::str::international::unicode_to_utf8(L##text))


