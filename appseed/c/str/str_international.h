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
         CodePageOem = 11,
#endif
      };


       bool CLASS_DECL_c UnicodeToMultiByte(UINT uiCodePage, char * lpsz, strsize nCount, const wchar_t * lpcsz);
       bool CLASS_DECL_c UnicodeToMultiByte(UINT uiCodePage, char * lpsz, strsize iBuffer, const wchar_t * lpcsz, strsize iCount);
       strsize   CLASS_DECL_c UnicodeToMultiByteCount(UINT uiCodePage, const wchar_t * lpcsz);
       strsize   CLASS_DECL_c UnicodeToMultiByteCount(UINT uiCodePage, const wchar_t * lpcsz, strsize iCount);
       bool CLASS_DECL_c UnicodeToMultiByte(UINT uiCodePage, string & str, const wchar_t * lpcsz);
       bool CLASS_DECL_c UnicodeToMultiByte(UINT uiCodePage, string & str, const wchar_t * lpcsz, strsize iCount);
       string CLASS_DECL_c UnicodeToMultiByte(UINT uiCodePage, const wchar_t * lpcsz);

       bool CLASS_DECL_c MultiByteToUnicode(UINT uiCodePage, wchar_t * lpwsz, strsize iBuffer, const char  * lpcsz, strsize iCount);
       bool CLASS_DECL_c MultiByteToUnicode(UINT uiCodePage, wchar_t * lpwsz, strsize nCount, const char * lpcsz);
       CLASS_DECL_c wstring MultiByteToUnicode(UINT uiCodePage, const char * lpcsz, strsize nCount);
       CLASS_DECL_c wstring MultiByteToUnicode(UINT uiCodePage, const string & str);
       strsize  CLASS_DECL_c MultiByteToUnicodeCount(UINT uiCodePage, const char * lpcsz);
       strsize  CLASS_DECL_c MultiByteToUnicodeCount(UINT uiCodePage, const char * lpcsz, strsize iCount);
       CLASS_DECL_c wstring MultiByteToUnicode(UINT uiCodePage, const char * lpcsz);

       bool CLASS_DECL_c MultiByteToMultiByte(UINT uiCodePageDest, string & str, UINT uiCodePageSrc, const char * lpcsz);
       bool CLASS_DECL_c MultiByteToMultiByte(UINT uiCodePageDest, string & str, UINT uiCodePageSrc, const char * lpcsz, strsize nCount);
       bool CLASS_DECL_c MultiByteToMultiByte(UINT uiCodePageDest, char * lpsz, strsize nCount, UINT uiCodePageSrc, const char * lpcsz);

       bool CLASS_DECL_c multibyte_to_utf8(UINT uiCodePageSrc, string & str, const char * lpcsz);
       bool CLASS_DECL_c multibyte_to_utf8(UINT uiCodePageSrc, string & str, const char * lpcsz, strsize nCount);
       strsize   CLASS_DECL_c Utf8ToMultiByteCount(UINT uiCodePage, const char * lpcsz);

       //bool CLASS_DECL_c MultiByteToOEM(UINT uiCodePage, string & str, const char * lpcsz);
       //bool CLASS_DECL_c MultiByteToOEM(UINT uiCodePage, string & str, const char * lpcsz, strsize nCount);

       //bool CLASS_DECL_c OEMToMultiByte(UINT uiCodePage, string & str, const char * lpcsz);
       //bool CLASS_DECL_c OEMToMultiByte(UINT uiCodePage, string & str, const char * lpcsz, strsize nCount);

       bool CLASS_DECL_c utf8_to_multibyte(UINT uiCodePage, string & str, const char * lpcsz);
       bool CLASS_DECL_c utf8_to_multibyte(UINT uiCodePage, string & str, const char * lpcsz, strsize nCount);
       bool CLASS_DECL_c utf8_to_multibyte(UINT uiCodePageSrc, char * lpsz, strsize nCount, const char * lpcsz);

       //bool CLASS_DECL_c OemToUtf8(string & str, const char * lpcsz);
       //bool CLASS_DECL_c OemToUtf8(string & str, const char * lpcsz, strsize nCount);

       bool CLASS_DECL_c unicode_to_utf8(string & str, const wchar_t * lpcsz);
       CLASS_DECL_c wstring utf8_to_unicode(const char * lpcsz);
       CLASS_DECL_c wstring utf8_to_unicode(const string & str);
       CLASS_DECL_c wstring utf8_to_unicode(const var & var);
       CLASS_DECL_c wstring utf8_to_unicode(const char * lpcsz, strsize iCount);
       bool CLASS_DECL_c unicode_to_utf8(string & str, const wchar_t * lpcsz, strsize iCount);
       string CLASS_DECL_c unicode_to_utf8(const wchar_t * lpcsz);

/*       bool CLASS_DECL_c AcpToUtf8(string & str, const char * lpcsz);
       bool CLASS_DECL_c AcpToUtf8(string & str, const char * lpcsz, strsize iSize);
       bool CLASS_DECL_c AcpToUtf8(LPTSTR lpstrUnicode, strsize nCount, const char * lpcsz);

       bool CLASS_DECL_c Utf8ToAcp(string & str, const char * lpcsz);

       bool CLASS_DECL_c UnicodeToACP(string & str, const wchar_t * lpcsz);
       string CLASS_DECL_c UnicodeToACP(const wchar_t * lpcsz);
       bool CLASS_DECL_c UnicodeToACP(char * lpstrUnicode, strsize nCount, const wchar_t * lpcsz);
       CLASS_DECL_c wstring ACPToUnicode(const char * lpcsz);
       CLASS_DECL_c wstring ACPToUnicode(const char * lpcsz, strsize iSize);
       bool CLASS_DECL_c ACPToUnicode(wchar_t * lpstrUnicode, strsize nCount, const char * lpcsz);

       bool CLASS_DECL_c UnicodeToOEM(string & str, const wchar_t * lpcsz);
       bool CLASS_DECL_c UnicodeToOEM(char * lpstrUnicode, strsize nCount, const wchar_t * lpcsz);
       CLASS_DECL_c wstring OEMToUnicode(const char * lpcsz);
       bool CLASS_DECL_c OEMToUnicode(wchar_t * lpstrUnicode, strsize nCount, const char * lpcsz);
       */

      ///////////////////////////////////////////////////////////////
      // ACP ( GetACP() function) conversion
      ///////////////////////////////////////////////////////////////

      CLASS_DECL_c string UnicodeToMultiByte(UINT uiCodePage, const wchar_t * lpcsz);
      //CLASS_DECL_c bool UnicodeToACP(string & str, const wchar_t * lpcsz);
      //CLASS_DECL_c bool UnicodeToACP(char * lpstrUnicode, strsize nCount, const wchar_t * lpcsz);
      //CLASS_DECL_c string UnicodeToACP(const wchar_t * lpcsz);
      //CLASS_DECL_c bool ACPToUnicode(wchar_t * lpstrUnicode, strsize nCount, const char * lpcsz);
      //CLASS_DECL_c wstring  ACPToUnicode(const char * lpcsz);
      //CLASS_DECL_c wstring  ACPToUnicode(const char * lpcsz, strsize iSize);

      ///////////////////////////////////////////////////////////////
      // OEM ( GetOEM() function) conversion
      ///////////////////////////////////////////////////////////////

      //CLASS_DECL_c bool UnicodeToOEM(string & str, const wchar_t * lpcsz);
      //CLASS_DECL_c bool UnicodeToOEM(char * lpstrUnicode, strsize nCount, const wchar_t * lpcsz);
      //CLASS_DECL_c bool OEMToUnicode(wchar_t * lpstrUnicode, strsize nCount, const char * lpcsz);
      //CLASS_DECL_c wstring OEMToUnicode(const char * lpcsz);
      CLASS_DECL_c bool unicode_to_utf8(string & str, const wchar_t * lpcsz);
      CLASS_DECL_c wstring utf8_to_unicode(const char * lpcsz);
      CLASS_DECL_c strsize utf8_to_unicode_count(const char * lpcsz, strsize count = -1);
      CLASS_DECL_c strsize utf8_to_unicode_count(const string & str);

      /*
      CLASS_DECL_c string UnicodeToACP(const wchar_t * lpcsz);
      CLASS_DECL_c string ACPToUnicode(const char * lpcsz);
      */

      //CLASS_DECL_c bool AcpToUtf8(string & str, const char * lpcsz);
      //CLASS_DECL_c bool Utf8ToAcp(string & str, const char * lpcsz);
      CLASS_DECL_c bool multibyte_to_utf8(UINT uiCodePageSrc, string & str, const char * lpcsz);
      CLASS_DECL_c bool multibyte_to_utf8(UINT uiCodePageSrc, string & str, const char * lpcsz, strsize nCount);
      //CLASS_DECL_c bool OemToUtf8(string & str, const char * lpcsz);
      //CLASS_DECL_c bool OemToUtf8(string & str, const char * lpcsz, strsize nCount);
      CLASS_DECL_c wstring utf8_to_unicode(const char * lpcsz, strsize iCount);
      CLASS_DECL_c bool utf8_to_unicode(wchar_t * lpwsz, strsize iBuffer, const char * lpcsz, strsize iCount);
      CLASS_DECL_c bool utf8_to_unicode(wchar_t * lpwsz, strsize iBuffer, const char * lpcsz);
      CLASS_DECL_c bool utf8_to_multibyte(UINT uiCodePage, string & str, const char * lpcsz);
      CLASS_DECL_c bool utf8_to_multibyte(UINT uiCodePage, string & str, const char * lpcsz, strsize nCount);
      CLASS_DECL_c bool utf8_to_multibyte(UINT uiCodePage, char * lpsz, strsize nCount, const char * lpcsz);
      //CLASS_DECL_c bool AcpToUtf8(LPTSTR lpstrUnicode, strsize nCount, const char * lpcsz);
      //CLASS_DECL_c bool AcpToUtf8(string & str, const char * lpcsz, strsize iSize);


   } // namespace international


} // namespace str


#define unitext(text) (::str::international::unicode_to_utf8(L##text))


