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


       bool CLASS_DECL_ACE UnicodeToMultiByte(UINT uiCodePage, char * lpsz, strsize nCount, const unichar * lpcsz);
       bool CLASS_DECL_ACE UnicodeToMultiByte(UINT uiCodePage, char * lpsz, strsize iBuffer, const unichar * lpcsz, strsize iCount);
       strsize   CLASS_DECL_ACE UnicodeToMultiByteCount(UINT uiCodePage, const unichar * lpcsz);
       strsize   CLASS_DECL_ACE UnicodeToMultiByteCount(UINT uiCodePage, const unichar * lpcsz, strsize iCount);
       bool CLASS_DECL_ACE UnicodeToMultiByte(UINT uiCodePage, string & str, const unichar * lpcsz);
       bool CLASS_DECL_ACE UnicodeToMultiByte(UINT uiCodePage, string & str, const unichar * lpcsz, strsize iCount);
       string CLASS_DECL_ACE UnicodeToMultiByte(UINT uiCodePage, const unichar * lpcsz);

       bool CLASS_DECL_ACE MultiByteToUnicode(UINT uiCodePage, unichar * lpwsz, strsize iBuffer, const char  * lpcsz, strsize iCount);
       bool CLASS_DECL_ACE MultiByteToUnicode(UINT uiCodePage, unichar * lpwsz, strsize nCount, const char * lpcsz);
       CLASS_DECL_ACE wstring MultiByteToUnicode(UINT uiCodePage, const char * lpcsz, strsize nCount);
       CLASS_DECL_ACE wstring MultiByteToUnicode(UINT uiCodePage, const string & str);
       strsize  CLASS_DECL_ACE MultiByteToUnicodeCount(UINT uiCodePage, const char * lpcsz);
       strsize  CLASS_DECL_ACE MultiByteToUnicodeCount(UINT uiCodePage, const char * lpcsz, strsize iCount);
       CLASS_DECL_ACE wstring MultiByteToUnicode(UINT uiCodePage, const char * lpcsz);

       bool CLASS_DECL_ACE MultiByteToMultiByte(UINT uiCodePageDest, string & str, UINT uiCodePageSrc, const char * lpcsz);
       bool CLASS_DECL_ACE MultiByteToMultiByte(UINT uiCodePageDest, string & str, UINT uiCodePageSrc, const char * lpcsz, strsize nCount);
       bool CLASS_DECL_ACE MultiByteToMultiByte(UINT uiCodePageDest, char * lpsz, strsize nCount, UINT uiCodePageSrc, const char * lpcsz);

       bool CLASS_DECL_ACE multibyte_to_utf8(UINT uiCodePageSrc, string & str, const char * lpcsz);
       bool CLASS_DECL_ACE multibyte_to_utf8(UINT uiCodePageSrc, string & str, const char * lpcsz, strsize nCount);
       strsize   CLASS_DECL_ACE Utf8ToMultiByteCount(UINT uiCodePage, const char * lpcsz);

       //bool CLASS_DECL_ACE MultiByteToOEM(UINT uiCodePage, string & str, const char * lpcsz);
       //bool CLASS_DECL_ACE MultiByteToOEM(UINT uiCodePage, string & str, const char * lpcsz, strsize nCount);

       //bool CLASS_DECL_ACE OEMToMultiByte(UINT uiCodePage, string & str, const char * lpcsz);
       //bool CLASS_DECL_ACE OEMToMultiByte(UINT uiCodePage, string & str, const char * lpcsz, strsize nCount);

       bool CLASS_DECL_ACE utf8_to_multibyte(UINT uiCodePage, string & str, const char * lpcsz);
       bool CLASS_DECL_ACE utf8_to_multibyte(UINT uiCodePage, string & str, const char * lpcsz, strsize nCount);
       bool CLASS_DECL_ACE utf8_to_multibyte(UINT uiCodePageSrc, char * lpsz, strsize nCount, const char * lpcsz);

       //bool CLASS_DECL_ACE OemToUtf8(string & str, const char * lpcsz);
       //bool CLASS_DECL_ACE OemToUtf8(string & str, const char * lpcsz, strsize nCount);

       bool CLASS_DECL_ACE unicode_to_utf8(string & str, const unichar * lpcsz);
       CLASS_DECL_ACE wstring utf8_to_unicode(const string & str);
       CLASS_DECL_ACE wstring utf8_to_unicode(const char * lpcsz, strsize iCount);
       bool CLASS_DECL_ACE unicode_to_utf8(string & str, const unichar * lpcsz, strsize iCount);
       string CLASS_DECL_ACE unicode_to_utf8(const unichar * lpcsz);

/*       bool CLASS_DECL_ACE AcpToUtf8(string & str, const char * lpcsz);
       bool CLASS_DECL_ACE AcpToUtf8(string & str, const char * lpcsz, strsize iSize);
       bool CLASS_DECL_ACE AcpToUtf8(LPTSTR lpstrUnicode, strsize nCount, const char * lpcsz);

       bool CLASS_DECL_ACE Utf8ToAcp(string & str, const char * lpcsz);

       bool CLASS_DECL_ACE UnicodeToACP(string & str, const unichar * lpcsz);
       string CLASS_DECL_ACE UnicodeToACP(const unichar * lpcsz);
       bool CLASS_DECL_ACE UnicodeToACP(char * lpstrUnicode, strsize nCount, const unichar * lpcsz);
       CLASS_DECL_ACE wstring ACPToUnicode(const char * lpcsz);
       CLASS_DECL_ACE wstring ACPToUnicode(const char * lpcsz, strsize iSize);
       bool CLASS_DECL_ACE ACPToUnicode(unichar * lpstrUnicode, strsize nCount, const char * lpcsz);

       bool CLASS_DECL_ACE UnicodeToOEM(string & str, const unichar * lpcsz);
       bool CLASS_DECL_ACE UnicodeToOEM(char * lpstrUnicode, strsize nCount, const unichar * lpcsz);
       CLASS_DECL_ACE wstring OEMToUnicode(const char * lpcsz);
       bool CLASS_DECL_ACE OEMToUnicode(unichar * lpstrUnicode, strsize nCount, const char * lpcsz);
       */

      ///////////////////////////////////////////////////////////////
      // ACP ( GetACP() function) conversion
      ///////////////////////////////////////////////////////////////

      CLASS_DECL_ACE string UnicodeToMultiByte(UINT uiCodePage, const unichar * lpcsz);
      //CLASS_DECL_ACE bool UnicodeToACP(string & str, const unichar * lpcsz);
      //CLASS_DECL_ACE bool UnicodeToACP(char * lpstrUnicode, strsize nCount, const unichar * lpcsz);
      //CLASS_DECL_ACE string UnicodeToACP(const unichar * lpcsz);
      //CLASS_DECL_ACE bool ACPToUnicode(unichar * lpstrUnicode, strsize nCount, const char * lpcsz);
      //CLASS_DECL_ACE wstring  ACPToUnicode(const char * lpcsz);
      //CLASS_DECL_ACE wstring  ACPToUnicode(const char * lpcsz, strsize iSize);

      ///////////////////////////////////////////////////////////////
      // OEM ( GetOEM() function) conversion
      ///////////////////////////////////////////////////////////////

      //CLASS_DECL_ACE bool UnicodeToOEM(string & str, const unichar * lpcsz);
      //CLASS_DECL_ACE bool UnicodeToOEM(char * lpstrUnicode, strsize nCount, const unichar * lpcsz);
      //CLASS_DECL_ACE bool OEMToUnicode(unichar * lpstrUnicode, strsize nCount, const char * lpcsz);
      //CLASS_DECL_ACE wstring OEMToUnicode(const char * lpcsz);
      CLASS_DECL_ACE bool unicode_to_utf8(string & str, const unichar * lpcsz);
      CLASS_DECL_ACE strsize utf8_to_unicode_count(const char * lpcsz, strsize count = -1);
      CLASS_DECL_ACE strsize utf8_to_unicode_count(const string & str);

      /*
      CLASS_DECL_ACE string UnicodeToACP(const unichar * lpcsz);
      CLASS_DECL_ACE string ACPToUnicode(const char * lpcsz);
      */

      //CLASS_DECL_ACE bool AcpToUtf8(string & str, const char * lpcsz);
      //CLASS_DECL_ACE bool Utf8ToAcp(string & str, const char * lpcsz);
      CLASS_DECL_ACE bool multibyte_to_utf8(UINT uiCodePageSrc, string & str, const char * lpcsz);
      CLASS_DECL_ACE bool multibyte_to_utf8(UINT uiCodePageSrc, string & str, const char * lpcsz, strsize nCount);
      //CLASS_DECL_ACE bool OemToUtf8(string & str, const char * lpcsz);
      //CLASS_DECL_ACE bool OemToUtf8(string & str, const char * lpcsz, strsize nCount);
      CLASS_DECL_ACE wstring utf8_to_unicode(const char * lpcsz, strsize iCount);
      CLASS_DECL_ACE bool utf8_to_unicode(unichar * lpwsz, strsize iBuffer, const char * lpcsz, strsize iCount);
      CLASS_DECL_ACE bool utf8_to_unicode(unichar * lpwsz, strsize iBuffer, const char * lpcsz);
      CLASS_DECL_ACE bool utf8_to_multibyte(UINT uiCodePage, string & str, const char * lpcsz);
      CLASS_DECL_ACE bool utf8_to_multibyte(UINT uiCodePage, string & str, const char * lpcsz, strsize nCount);
      CLASS_DECL_ACE bool utf8_to_multibyte(UINT uiCodePage, char * lpsz, strsize nCount, const char * lpcsz);
      //CLASS_DECL_ACE bool AcpToUtf8(LPTSTR lpstrUnicode, strsize nCount, const char * lpcsz);
      //CLASS_DECL_ACE bool AcpToUtf8(string & str, const char * lpcsz, strsize iSize);


   } // namespace international


} // namespace str

inline wstring u16(const char * psz) { return ::str::international::utf8_to_unicode(psz);  }
inline string u8(const unichar * pwsz) { return ::str::international::unicode_to_utf8(pwsz); }

#if defined(WINDOWS)
#define unitext(text) (::str::international::unicode_to_utf8(L##text))
#else
#define unitext(text) (::str::international::unicode_to_utf8(utf32_to_utf16(L##text)))
#endif


