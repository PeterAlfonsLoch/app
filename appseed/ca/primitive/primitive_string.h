#pragma once


#ifdef LINUX
#undef __USE_MISC
#include <strings.h>
#endif


CLASS_DECL_ca string_manager * __get_string_manager();


class string;
class istring;


class CLASS_DECL_ca string_interface
{
public:


   // the string returned by get_string should be valid
   // during all lifetime of an derived object of
   // string_interface
   virtual strsize get_length() const;

   virtual void get_string(char * psz) const;

   virtual void set_string(const char * psz);

   string_interface & operator = (const string_interface & str);

   string_interface & operator = (const char * psz);

};




class CLASS_DECL_ca string_composite :
   public string_interface
{
public:
   inline string_composite() : m_pstring(NULL), m_pinterface(NULL) {}
   inline string_composite(const string_composite & str) : m_pstring(str.m_pstring), m_pinterface(str.m_pinterface) {}
   inline string_composite(string & str) : m_pstring(&str), m_pinterface(NULL) {}
   inline string_composite(const string & str) : m_pstring((string *) &str), m_pinterface(NULL) {}
   inline string_composite(const string * pstr) : m_pstring(const_cast < string *  > (pstr)) , m_pinterface(NULL) {}
   inline string_composite(string_interface & strinterface) : m_pinterface(&strinterface), m_pstring(NULL) {}
   inline string_composite(const string_interface & strinterface) : m_pinterface(const_cast < string_interface * > (&strinterface)) , m_pstring(NULL) {}
   virtual strsize get_length() const;
   virtual void get_string(char * psz) const;
   virtual void set_string(const char * psz);
   virtual void set_string(string & str) { m_pstring = &str; m_pinterface = NULL; }
   virtual void set_string(const string & str) { m_pstring = (string *) &str; m_pinterface = NULL; }
   virtual void set_string(const string * pstr) const;
   string_composite & operator = (const string & str);

private:
   string * m_pstring;
   string_interface * m_pinterface;
};


CLASS_DECL_ca int64_t strtoi(const char * psz);

CLASS_DECL_ca int64_t strtoi(const wchar_t * psz);


inline UINT _gen_GetConversionACP()
{
#ifdef WINDOWS
   return CP_UTF8;
#else
   return 0;
#endif
}






#ifndef _AFX
#define ___FUNCNAME(_Name) _Name
#endif

//#pragma push_macro("new")
#undef new

/////////////////////////////////////////////////////////////////////////////
// Naming conventions:
//    The term "length" can be confusing when dealing with ANSI, Unicode, and
//    MBCS character sets, so this file will use the following naming
//    conventions to differentiate between the different meanings of
//    "length":
//
//    'byte Length' - Length of a buffer in bytes, regardless of character
//       size
//    'Char Length' - Number of distinct characters in string.  For wide-
//       character strings, this is equivalent to half the 'byte Length'.
//       For ANSI strings, this is equivalent to the 'byte Length'.  For MBCS
//       strings, 'Char Length' counts a lead-byte/trail-byte combination
//       as one character.
//    'Length' - When neither of the above terms is used, 'Length' refers to
//       length in XCHARs, which is equal to 'byte Length'/sizeof(XCHAR).
/////////////////////////////////////////////////////////////////////////////


#define IMPLEMENT_CONST_STRING_PTR(stringype, value, name) const const_fixed_string<stringype, sizeof(value)/sizeof(stringype::XCHAR)> _init##name ={    {NULL,      sizeof(value)/sizeof(stringype::XCHAR)-1,    sizeof(value)/sizeof(stringype::XCHAR)-1,    -1},         value   };   const stringype::XCHAR* const _value##name = _init##name.m_achData;   extern const stringype* const name = CONST_STRING_PTR(stringype, name);
#define DECLARE_CONST_STRING_PTR(stringype, name) extern const stringype* const name;
#define CONST_STRING_PTR(stringype, name) reinterpret_cast<const stringype* const>(&_value##name)


class crt_char_traits :
   public char_traits_base
{
public:

   static char*         __cdecl  CharNext(const char* p ) throw();
   static int           __cdecl  IsDigit(const char * pch ) throw();
   static int           __cdecl  IsSpace(const char * pch ) throw();
   static int           __cdecl  StringCompare(const char * pszA,const char * pszB ) throw();
   static int           __cdecl  StringCompareIgnore(const char * pszA,const char * pszB ) throw();
   static int           __cdecl  StringCollate(const char * pszA,const char * pszB ) throw();
   static int           __cdecl  StringCollateIgnore(const char * pszA,const char * pszB ) throw();
   static const char *  __cdecl  StringFindString(const char * pszBlock,const char * pszMatch ) throw();
   static char *        __cdecl  StringFindString(char * pszBlock,const char * pszMatch ) throw();
   static const char *  __cdecl  StringFindChar(const char * pszBlock,char chMatch ) throw();
   static const char *  __cdecl  StringFindCharRev(const char * psz,char ch, strsize iStart ) throw();
   static const char *  __cdecl  StringFindStrRev(const char * psz,const char * pszFind, strsize iStart ) throw();
   static const char *  __cdecl  StringScanSet(const char * pszBlock,const char * pszMatch ) throw();
   static strsize       __cdecl  StringSpanIncluding(const char * pszBlock,const char * pszSet ) throw();
   static strsize       __cdecl  StringSpanExcluding(const char * pszBlock,const char * pszSet ) throw();
   static char *        __cdecl  StringUppercase( char * psz ) throw();
   static char *        __cdecl  StringLowercase( char * psz ) throw();
   static char *        __cdecl  StringUppercase(char * psz,size_t size ) throw();
   static char *        __cdecl  StringLowercase(char * psz,size_t size ) throw();
   static char *        __cdecl  StringReverse( char * psz ) throw();
   static strsize       __cdecl  GetFormattedLength(const char * pszFormat, va_list args ) throw();
   static strsize       __cdecl  Format(char * pszBuffer,const char * pszFormat, va_list args ) throw();
   static strsize       __cdecl  Format(char * pszBuffer,size_t nlength,const char * pszFormat, va_list args ) throw();
   static strsize       __cdecl  GetcharLength(const char * pszSrc ) throw();
   static strsize       __cdecl  GetcharLength(const char * pszSrc, strsize nLength ) throw();
   static strsize       __cdecl  GetcharLength(const wchar_t * pszSource ) throw();
   static strsize       __cdecl  GetcharLength(const wchar_t * pszSource, strsize nLength ) throw();
   static void          __cdecl  ConvertTochar(char * pszDest,strsize nDestLength, const char * pszSrc, strsize nSrcLength = -1 ) throw();
   static void          __cdecl  ConvertTochar(char * pszDest,strsize nDestLength, const wchar_t * pszSrc,strsize nSrcLength = -1) throw();
   static void                   ConvertToOem(char* pstrString) RELEASENOTHROW;
   static void                   ConvertToAnsi(char* pstrString) RELEASENOTHROW;
   static void                   ConvertToOem(char* pstrString,size_t size);
   static void                   ConvertToAnsi(char* pstrString,size_t size);
   static void          __cdecl  FloodCharacters(char ch,strsize nLength, char* pch ) throw();

#ifdef WINDOWS

   static BSTR          __cdecl  AllocSysString( const char* pchData, strsize nDataLength ) throw();
   static bool          __cdecl  ReAllocSysString( const char* pchData,BSTR* pbstr,strsize nDataLength ) throw();

#endif

   static DWORD         __cdecl  FormatMessage(DWORD dwFlags, LPCVOID pSource, DWORD dwMessageID,DWORD dwLanguageID, char * pszBuffer, DWORD nSize, va_list* pArguments ) throw();
   static DWORD         __cdecl  format_message(DWORD dwFlags, LPCVOID pSource, DWORD dwMessageID,DWORD dwLanguageID, char * pszBuffer, DWORD nSize, va_list* pArguments ) throw();
   static strsize       __cdecl  SafeStringLen( const char * psz ) throw();
   static strsize       __cdecl  SafeStringLen( const wchar_t * psz ) throw();
   static strsize       __cdecl  GetCharLen(const wchar_t* pch ) throw();
   static strsize       __cdecl  GetCharLen(const char* pch ) throw();
   static DWORD         __cdecl  GetEnvironmentVariable(const char * pszVar, char * pszBuffer,DWORD dwSize ) throw();

};
























class string_trait :
   public crt_char_traits // iterator
{
public:

   CLASS_DECL_ca static string_manager * GetDefaultManager() throw()
   {
      static string_manager * s_pdefaultManager = __get_string_manager();
      return s_pdefaultManager;
   }

};


class fixed_alloc_array;





class CLASS_DECL_ca string :
   public simple_string
#if defined(LINUX)
   , public string_format_printer
#endif
{
public:

   operator class string_composite ();
   operator class string_composite const () const;
   operator PCXSTR() const throw();
   PCXSTR c_str() const throw();
   void construct() throw();
   inline string() throw();
   explicit string( string_manager * pstringmanager ) throw();
   static void __cdecl Construct( string* pstring );

   string(const id & id);
   string(const var & var);
   string(const char * pszSrc);
   string(const string & strSrc);
   string(const unsigned char * pszSrc);
   //   string(char * pszSrc);
   string(unsigned char * pszSrc);
   string(wchar_t * pszSrc);
   string(const wchar_t * pszSrc);
   string(const string_interface & str);
   string(const vsstring & str);
   string(const istring & istr);
   string(const char * pszSrc,string_manager * pstringmanager );
   string(const wchar_t * pszSrc,string_manager * pstringmanager );



   string(const unsigned char* pszSrc, string_manager * pstringmanager);
   explicit string(char ch, strsize nLength = 1);
   string(strsize nLength, char ch);
   string(wchar_t ch, strsize nLength = 1 );
   string(const XCHAR* pch, strsize nLength);
   string(const XCHAR* pch, strsize nLength, string_manager * pstringmanager );
   string(const YCHAR* pch, strsize nLength);
   string(const YCHAR* pch, strsize nLength, string_manager * pstringmanager );
   ~string() throw();



   // Assignment operators
   string& operator=(const string_interface & str );
   string& operator=(string strSrc );
   string& operator=(const id & id);
   string& operator=(const var & var);
   template <bool bMFCDLL>
   string& operator=(const simple_string& strSrc);
   string& operator=(const vsstring & strSrc);
   string& operator=(PCXSTR pszSrc);
   string& operator=(PCYSTR pszSrc);
   string& operator=(const unsigned char* pszSrc );
   string& operator=(char ch );
   string& operator=(const Platform::String ^ & str);
   string& operator=(wchar_t ch );
   string& operator+=(const simple_string& str );
   string& operator+=(PCXSTR pszSrc );
   template< strsize t_nSize >
   string& operator+=(const static_string<t_nSize >& strSrc );
   string& operator+=(PCYSTR pszSrc );
   string& operator+=(char ch );
   string& operator+=(unsigned char ch );
   string& operator+=(wchar_t ch );

   // Override from base class
   string_manager * GetManager() const throw();


   string & assign(const string & str);
   string & assign(const string & str, strsize pos, strsize n);
   string & assign(const char * s, strsize n);
   string & assign(const char * s);
   string & assign(strsize n, char c);
   string & assign(int64_t n, int64_t c);
   string & assign(int n, int c);
   string & assign(unsigned int n, unsigned int c);
   string & assign(uint64 n, uint64 c);
   template <class InputIterator>
   string & assign (InputIterator first, InputIterator last);

   // Comparison
   int Compare(PCXSTR psz ) const;
   int CompareNoCase(PCXSTR psz) const RELEASENOTHROW;



   int Collate(PCXSTR psz ) const RELEASENOTHROW;
   int CollateNoCase(PCXSTR psz ) const RELEASENOTHROW;

   int compare(PCXSTR psz ) const;
   int compare_no_case(PCXSTR psz ) const throw();
   int collate(PCXSTR psz ) const throw();
   int collate_no_case(PCXSTR psz ) const throw();

   int compare(strsize iStart, strsize iCount, PCXSTR psz ) const;
   int compare_no_case(strsize iStart, strsize iCount, PCXSTR psz ) const;
   int collate(strsize iStart, strsize iCount, PCXSTR psz ) const;
   int collate_no_case(strsize iStart, strsize iCount, PCXSTR psz ) const;

   int compare(strsize iStart, strsize iCount, PCXSTR psz, strsize iStart2, strsize iCount2) const;
   int compare_no_case(strsize iStart, strsize iCount, PCXSTR psz, strsize iStart2, strsize iCount2) const;
   int collate(strsize iStart, strsize iCount, PCXSTR psz, strsize iStart2, strsize iCount2) const;
   int collate_no_case(strsize iStart, strsize iCount, PCXSTR psz, strsize iStart2, strsize iCount2) const;

   bool contains(char ch, strsize start = 0, strsize count = -1);
   bool contains(wchar_t wch, strsize start = 0, strsize count = -1);
   bool contains(int i, strsize start = 0, strsize count = -1); // utf8 char index
   bool contains(const char * psz, strsize start = 0, strsize count = -1);
   bool contains(const string & str, strsize start = 0, strsize count = -1);

   bool contains_ci(char ch, strsize start = 0, strsize count = -1);
   bool contains_ci(wchar_t wch, strsize start = 0, strsize count = -1);
   bool contains_ci(int i, strsize start = 0, strsize count = -1); // utf8 char index
   bool contains_ci(const char * psz, strsize start = 0, strsize count = -1);
   bool contains_ci(const string & str, strsize start = 0, strsize count = -1);

   bool contains_wci(char ch, strsize start = 0, strsize count = -1);
   bool contains_wci(wchar_t wch, strsize start = 0, strsize count = -1);
   bool contains_wci(int i, strsize start = 0, strsize count = -1); // utf8 char index
   bool contains_wci(const char * psz, strsize start = 0, strsize count = -1);
   bool contains_wci(const string & str, strsize start = 0, strsize count = -1);
   // Advanced manipulation


   void reserve(strsize res_arg = 0);

   // Delete 'nCount' characters, starting at index 'iIndex'
   strsize Delete(strsize iIndex, strsize nCount = 1);
   strsize remove(strsize iIndex, strsize nCount = 1);

   string & erase(strsize start = 0, strsize count = -1);


   // Insert character 'ch' before index 'iIndex'
   strsize Insert(strsize iIndex,XCHAR ch );

   // Insert string 'psz' before index 'iIndex'
   strsize Insert(strsize iIndex,PCXSTR psz );

   // replace all occurrences of character 'chOld' with character 'chNew'
   strsize replace(XCHAR chOld,XCHAR chNew, strsize iStart = 0);

   // replace all occurrences of string 'pszOld' with string 'pszNew'
   strsize replace(PCXSTR pszOld,PCXSTR pszNew, strsize iStart = 0);

   string & replace(strsize iStart, strsize nCount, const char * psz);

   // remove all occurrences of character 'chRemove'
   strsize remove(XCHAR chRemove );

   string Tokenize(PCXSTR pszTokens, strsize& iStart ) const;
   // find routines

   // find the first occurrence of character 'ch', starting at index 'iStart'
   strsize find(XCHAR ch, strsize start = 0, strsize count = -1) const RELEASENOTHROW;
   strsize find_ci(XCHAR ch, strsize start = 0, strsize count = -1) const RELEASENOTHROW;

   // look for a specific sub-string

   // find the first occurrence of string 'pszSub', starting at index 'iStart'
   strsize find(PCXSTR pszSub, strsize start = 0, strsize count = -1) const RELEASENOTHROW;
   strsize find_w(PCXSTR pszSub, strsize start = 0, strsize count = -1) const RELEASENOTHROW;
   strsize find_ci(PCXSTR pszSub, strsize start = 0, strsize count = -1) const RELEASENOTHROW;
   strsize find_wci(PCXSTR pszSub, strsize start = 0, strsize count = -1) const RELEASENOTHROW;

   // find the first occurrence of any of the characters in string 'pszCharSet'
   strsize FindOneOf(PCXSTR pszCharSet, strsize iStart = 0, strsize n = -1 ) const RELEASENOTHROW;

   strsize find_first_in(const string & str, strsize pos = 0) const RELEASENOTHROW;
   strsize find_first_in(const char * s, strsize pos, strsize n) const RELEASENOTHROW;
   strsize find_first_in(const char * s, strsize pos = 0) const RELEASENOTHROW;
   strsize find_first_in(char c, strsize pos = 0) const RELEASENOTHROW;

   strsize find_first_not_in(const string & str, strsize pos = 0) const RELEASENOTHROW;
   strsize find_first_not_in(const char * s, strsize pos, strsize n) const RELEASENOTHROW;
   strsize find_first_not_in(const char * s, strsize pos = 0) const RELEASENOTHROW;
   strsize find_first_not_in(char c, strsize pos = 0) const RELEASENOTHROW;

   strsize find_last_not_in(const string & str, strsize pos = -1) const RELEASENOTHROW;
   strsize find_last_not_in(const char * s, strsize pos, strsize n) const RELEASENOTHROW;
   strsize find_last_not_in(const char * s, strsize pos = -1) const RELEASENOTHROW;
   strsize find_last_not_in(char c, strsize pos = -1) const RELEASENOTHROW;

   strsize find_last_in(const string & str, strsize pos = -1) const RELEASENOTHROW;
   strsize find_last_in(const char * s, strsize pos, strsize n) const RELEASENOTHROW;
   strsize find_last_in(const char * s, strsize pos = -1) const RELEASENOTHROW;
   strsize find_last_in(char c, strsize pos = -1) const RELEASENOTHROW;

   strsize find_first_of(const string & str, strsize pos = 0) const RELEASENOTHROW;
   strsize find_first_of(const char * s, strsize pos, strsize n) const RELEASENOTHROW;
   strsize find_first_of(const char * s, strsize pos = 0) const RELEASENOTHROW;
   strsize find_first_of(char c, strsize pos = 0) const RELEASENOTHROW;

   strsize find_first_not_of(const string & str, strsize pos = 0) const RELEASENOTHROW;
   strsize find_first_not_of(const char * s, strsize pos, strsize n) const RELEASENOTHROW;
   strsize find_first_not_of(const char * s, strsize pos = 0) const RELEASENOTHROW;
   strsize find_first_not_of(char c, strsize pos = 0) const RELEASENOTHROW;

   strsize find_last_not_of(const string & str, strsize pos = -1) const RELEASENOTHROW;
   strsize find_last_not_of(const char * s, strsize pos, strsize n) const RELEASENOTHROW;
   strsize find_last_not_of(const char * s, strsize pos = -1) const RELEASENOTHROW;
   strsize find_last_not_of(char c, strsize pos = -1) const RELEASENOTHROW;

   strsize find_last_of(const string & str, strsize pos = -1) const RELEASENOTHROW;
   strsize find_last_of(const char * s, strsize pos, strsize n) const RELEASENOTHROW;
   strsize find_last_of(const char * s, strsize pos = -1) const RELEASENOTHROW;
   strsize find_last_of(char c, strsize pos = -1) const RELEASENOTHROW;

   // find the last occurrence of character 'ch'
   strsize reverse_find(XCHAR ch, strsize iStart = -1 ) const RELEASENOTHROW;

   // find the last occurrence of character 'ch'
   strsize reverse_find( PCXSTR ch, strsize iStart = -1 ) const RELEASENOTHROW;


   char last_char() const;

   // manipulation

   // Convert the string to uppercase
   string& make_upper();

   // Convert the string to lowercase
   string& make_lower();

   // Reverse the string
   string& MakeReverse();

   // Convert the string to uppercase
   string uppered() const;

   // Convert the string to lowercase
   string lowered() const;

   // Convert the string to lowercase
   string reversed() const;

   // trimming

   // remove all trailing whitespace
   string& trim_right();

   // remove all leading whitespace
   string& trim_left();

   // remove all leading and trailing whitespace
   string& trim();

   // remove all leading and trailing occurrences of character 'chTarget'
   string& trim(XCHAR chTarget );

   // remove all leading and trailing occurrences of any of the characters in the string 'pszTargets'
   string& trim(PCXSTR pszTargets );

   // trimming anything (either side)

   // remove all trailing occurrences of character 'chTarget'
   string& trim_right(XCHAR chTarget );

   // remove all trailing occurrences of any of the characters in string 'pszTargets'
   string& trim_right(PCXSTR pszTargets );

   // remove all leading occurrences of character 'chTarget'
   string& trim_left(XCHAR chTarget );

   // remove all leading occurrences of any of the characters in string 'pszTargets'
   string& trim_left(PCXSTR pszTargets );


   // remove all trailing whitespace
   string right_trimmed() const;

   // remove all leading whitespace
   string left_trimmed() const;

   // remove all leading and trailing whitespace
   string trimmed() const;

   // remove all leading and trailing occurrences of character 'chTarget'
   string trimmed(XCHAR chTarget) const;

   // remove all leading and trailing occurrences of any of the characters in the string 'pszTargets'
   string trimmed(PCXSTR pszTargets) const;

   // trimming anything (either side)

   // remove all trailing occurrences of character 'chTarget'
   string right_trimmed(XCHAR chTarget) const;

   // remove all trailing occurrences of any of the characters in string 'pszTargets'
   string right_trimmed(PCXSTR pszTargets) const;

   // remove all leading occurrences of character 'chTarget'
   string left_trimmed(XCHAR chTarget) const;

   // remove all leading occurrences of any of the characters in string 'pszTargets'
   string left_trimmed(PCXSTR pszTargets) const;


   // Convert the string to the OEM character set
   void AnsiToOem();

   // Convert the string to the ANSI character set
   void OemToAnsi();

   // Very simple sub-string extraction

   // Return the substring starting at index 'iFirst'
   string Mid(strsize iFirst ) const;

   string substr(strsize iFirst) const;

   // Return the substring starting at index 'iFirst', with length 'nCount'
   string Mid(strsize iFirst,strsize nCount ) const;

   string substr(strsize iFirst, strsize nCount) const;

   string utf8_substr(strsize iFirst) const;

   string utf8_substr(strsize iFirst, strsize nCount) const;

   ::count utf8_get_length() const;

   inline ::count utf8_length() const;

   void clear();

   strsize length() const;

   // Return the substring consisting of the rightmost 'nCount' characters
   string Right(strsize nCount ) const;

   // Return the substring consisting of the leftmost 'nCount' characters
   string Left(strsize nCount ) const;

   // Return the substring consisting of the leftmost characters in the set 'pszCharSet'
   string SpanIncluding(PCXSTR pszCharSet ) const;

   // Return the substring consisting of the leftmost characters not in the set 'pszCharSet'
   string SpanExcluding(PCXSTR pszCharSet ) const;

   // Format data using format string 'pszFormat'
#ifdef WINDOWS

   void __cdecl Format(PCXSTR pszFormat, ... );

#else




   void FormatPrinter(void * , const char * s)
   {

      *this = s;

   }


   void Format(const char * s)
   {

      string_format format(this, &string::FormatPrinter, NULL);

      format.printf(s);

   }

   template<typename T, typename... Args>
   void Format(const char *s, const T & value, Args... args)
   {

      string_format format(this, &string::FormatPrinter, NULL);

      format.printf(s, value, args...);

   }

#endif


   // append formatted data using format string 'pszFormat'
   void __cdecl AppendFormat(PCXSTR pszFormat, ... );

   void AppendFormatV(PCXSTR pszFormat, va_list args );

   void FormatV(PCXSTR pszFormat, va_list args );

   void __cdecl FormatMessage(PCXSTR pszFormat, ... );

   void __cdecl format_message(PCXSTR pszFormat, ... );

   // Format a message using format string 'pszFormat' and va_list
   void FormatMessageV(PCXSTR pszFormat, va_list* pArgList );

#ifdef WINDOWS

   // OLE BSTR support

   // allocate a BSTR containing a copy of the string
   BSTR AllocSysString() const;

   BSTR SetSysString(BSTR* pbstr ) const;

#endif

   // Set the string to the value of environment var 'pszVar'
   bool GetEnvironmentVariable(PCXSTR pszVar);

   // Set the string to the value of environment var 'pszVar'
   bool getenv(PCXSTR pszVar);

   // Load the string from resource 'nID'
   bool load_string(::ca::application * papp, id id);

   // Load the string from resource 'nID' in module 'hInstance'
   /*    bool load_string(HINSTANCE hInstance,strsize nID )
   {
   const STRINGRESOURCEIMAGE* pImage = gen_GetStringResourceImage( hInstance, nID );
   if( pImage == NULL )
   {
   return( FALSE );
   }

   strsize nLength = str_traits::GetcharLength( pImage->achString, pImage->nLength );
   PXSTR pszBuffer = GetBuffer( nLength );
   str_traits::ConvertTochar( pszBuffer, nLength, pImage->achString, pImage->nLength );
   ReleaseBufferSetLength( nLength );

   return( TRUE );
   }*/

   // Load the string from resource 'nID' in module 'hInstance', using language 'wLanguageID'
   /*bool load_string(HINSTANCE hInstance,strsize nID,WORD wLanguageID )
   {
   const STRINGRESOURCEIMAGE* pImage = gen_GetStringResourceImage( hInstance, nID, wLanguageID );
   if( pImage == NULL )
   {
   return( FALSE );
   }

   strsize nLength = str_traits::GetcharLength( pImage->achString, pImage->nLength );
   PXSTR pszBuffer = GetBuffer( nLength );
   str_traits::ConvertTochar( pszBuffer, nLength, pImage->achString, pImage->nLength );
   ReleaseBufferSetLength( nLength );

   return( TRUE );
   }*/

   friend string CLASS_DECL_ca operator+(const string & str1,const string & str2 );
   friend string CLASS_DECL_ca operator+(const string & str1,PCXSTR psz2 );
   friend string CLASS_DECL_ca operator+(PCXSTR psz1,const string & str2 );
   friend string CLASS_DECL_ca operator+(const string & str1,wchar_t ch2 );
   friend string CLASS_DECL_ca operator+(wchar_t ch1,const string & str2 );
   friend string CLASS_DECL_ca operator+(const string & str1,char ch2 );
   friend string CLASS_DECL_ca operator+(char ch1,const string & str2 );
   friend string CLASS_DECL_ca operator+(const string & str1,int ch2 );
   friend string CLASS_DECL_ca operator+(int ch1,const string & str2 );
   friend string CLASS_DECL_ca operator+(const string & str1,int64_t ch2 );
   friend string CLASS_DECL_ca operator+(int64_t ch1,const string & str2 );
   friend string CLASS_DECL_ca operator+(const var & var, const char * psz);
   friend string CLASS_DECL_ca operator+(const char * psz, const var & var);
   friend string CLASS_DECL_ca operator+(const var & var, const string & str);
   friend string CLASS_DECL_ca operator+(const string & str, const var & var);



   friend bool CLASS_DECL_ca operator==(const string & str1,const string_interface & str2 );
   friend bool CLASS_DECL_ca operator==(const string_interface & str1,const string & str2 );
   friend bool CLASS_DECL_ca operator==(const string & str1,const string & str2 ) throw();
   friend bool CLASS_DECL_ca operator==(const string & str1,PCXSTR psz2 ) throw();
   friend bool CLASS_DECL_ca operator==(PCXSTR psz1,const string & str2 ) throw();
   friend bool CLASS_DECL_ca operator==(const string & str1,PCYSTR psz2 ) THROWS;
   friend bool CLASS_DECL_ca operator==(PCYSTR psz1,const string & str2 ) THROWS;
   friend bool CLASS_DECL_ca operator==(const string & str1, int i);
   friend bool CLASS_DECL_ca operator==(int i, const string & str1);
   //   friend bool CLASS_DECL_ca operator==(const string & str1, int i);
   //   friend bool CLASS_DECL_ca operator==(int i, const string & str1);
   friend bool CLASS_DECL_ca operator!=(const string & str1,const string & str2 ) throw();
   friend bool CLASS_DECL_ca operator!=(const string & str1,PCXSTR psz2 ) throw();
   friend bool CLASS_DECL_ca operator!=(PCXSTR psz1,const string & str2 ) throw();
   friend bool CLASS_DECL_ca operator!=(const string & str1,PCYSTR psz2 ) THROWS;
   friend bool CLASS_DECL_ca operator!=(PCYSTR psz1,const string & str2 ) THROWS;
   friend bool CLASS_DECL_ca operator!=(const string & str1, int i);
   friend bool CLASS_DECL_ca operator!=(int i, const string & str1);
   friend bool CLASS_DECL_ca operator<(const string & str1,const string & str2 ) throw();
   friend bool CLASS_DECL_ca operator<(const string & str1,PCXSTR psz2 ) throw();
   friend bool CLASS_DECL_ca operator<(PCXSTR psz1,const string & str2 ) throw();
   friend bool CLASS_DECL_ca operator<(const string & str1, int i);
   friend bool CLASS_DECL_ca operator<(int i, const string & str1);
   friend bool CLASS_DECL_ca operator>(const string & str1,const string & str2 ) throw();
   friend bool CLASS_DECL_ca operator>(const string & str1,PCXSTR psz2 ) throw();
   friend bool CLASS_DECL_ca operator>(PCXSTR psz1,const string & str2 ) throw();
   friend bool CLASS_DECL_ca operator>(const string & str1, int i);
   friend bool CLASS_DECL_ca operator>(int i, const string & str1);
   friend bool CLASS_DECL_ca operator<=(const string & str1,const string & str2 ) throw();
   friend bool CLASS_DECL_ca operator<=(const string & str1,PCXSTR psz2 ) throw();
   friend bool CLASS_DECL_ca operator<=(PCXSTR psz1,const string & str2 ) throw();
   friend bool CLASS_DECL_ca operator<=(const string & str1, int i);
   friend bool CLASS_DECL_ca operator<=(int i, const string & str1);
   friend bool CLASS_DECL_ca operator>=(const string & str1,const string & str2 ) throw();
   friend bool CLASS_DECL_ca operator>=(const string & str1,PCXSTR psz2 ) throw();
   friend bool CLASS_DECL_ca operator>=(PCXSTR psz1,const string & str2 ) throw();
   friend bool CLASS_DECL_ca operator>=(const string & str1, int i);
   friend bool CLASS_DECL_ca operator>=(int i, const string & str1);
   friend bool CLASS_DECL_ca operator==(XCHAR ch1,const string & str2 ) throw();
   friend bool CLASS_DECL_ca operator==(const string & str1,XCHAR ch2 ) throw();
   friend bool CLASS_DECL_ca operator!=(XCHAR ch1,const string & str2 ) throw();
   friend bool CLASS_DECL_ca operator!=(const string & str1,XCHAR ch2 ) throw();

   typedef strsize size_type;


   inline static string empty_string()
   {
      return string();
   }

};


template< strsize t_nSize >
string& string::operator+=(const static_string<t_nSize >& strSrc )
{
   simple_string::operator+=( strSrc );

   return( *this );
}

template <bool bMFCDLL>
string& string::operator=(const simple_string& strSrc )
{
   simple_string::operator=( strSrc );

   return( *this );
}

template < class InputIterator >
string & string::assign ( InputIterator first, InputIterator last )
{
   Empty();
   for(InputIterator it = first; it <= last; it++)
   {
      *this += *it;
   }
}



inline strsize string::find_first_in(const string & str, strsize pos) const
{
   return find_first_of(str, pos);
}

inline strsize string::find_first_in(const char * s, strsize pos, strsize n) const
{
   return find_first_of(s, pos, n);
}

inline strsize string::find_first_in(const char * s, strsize pos) const
{
   return find_first_of(s, pos);
}

inline strsize string::find_first_in(char c, strsize pos) const
{
   return find_first_of(c, pos);
}

inline strsize string::find_first_not_in(const string & str, strsize pos) const
{
   return find_first_not_of(str, pos);
}

inline strsize string::find_first_not_in(const char * s, strsize pos, strsize n) const
{
   return find_first_not_of(s, pos, n);
}

inline strsize string::find_first_not_in(const char * s, strsize pos) const
{
   return find_first_not_of(s, pos);
}

inline strsize string::find_first_not_in(char c, strsize pos) const
{
   return find_first_not_of(c, pos);
}

inline strsize string::find_last_not_in(const string & str, strsize pos) const
{
   return find_first_not_of(str, pos);
}

inline strsize string::find_last_not_in(const char * s, strsize pos, strsize n) const
{
   return find_last_not_of(s, pos, n);
}

inline strsize string::find_last_not_in(const char * s, strsize pos) const
{
   return find_last_not_of(s, pos);
}

inline strsize string::find_last_not_in(char c, strsize pos) const
{
   return find_last_not_of(c, pos);
}

inline strsize string::find_last_in(const string & str, strsize pos) const
{
   return find_last_of(str, pos);
}

inline strsize string::find_last_in(const char * s, strsize pos, strsize n) const
{
   return find_last_of(s, pos, n);
}

inline strsize string::find_last_in(const char * s, strsize pos) const
{
   return find_last_of(s, pos);
}

inline strsize string::find_last_in(char c, strsize pos) const
{
   return find_last_of(c, pos);
}

inline strsize string::length() const
{
   return get_length();
}

inline strsize string::utf8_length() const
{
   return utf8_get_length();
}









inline strsize string_composite::get_length() const
{
   if(m_pstring != NULL)
      return m_pstring->get_length();
   else
      return m_pinterface->get_length();
}

inline void string_composite::get_string(char * psz) const
{
   if(m_pstring != NULL)
      m_pstring->get_string(psz);
   else
      m_pinterface->get_string(psz);
}

inline void string_composite::set_string(const char * psz)
{
   if(m_pstring != NULL)
      m_pstring->set_string(psz);
   else
      m_pinterface->set_string(psz);
}

class CLASS_DECL_ca const_empty_string :
   public string_interface
{
public:
   strsize get_length() const;
   void get_string(char * pszstr) const;
   void set_string(const char * psz);
};




namespace gen
{
   extern CLASS_DECL_ca const_empty_string g_strEmpty;
   CLASS_DECL_ca string_interface & empty_string();
}

#define BAD_WCHAR ((wchar_t)(0xFFFF))

/// macro - number of elements in array
#define ARRAY_SIZE(a) (sizeof(a)/sizeof(*(a)))

#include "x/x_charcategory.h"
#include "gen/gen_bit.h"
#include "collection/collection_bit_array.h"

#include "gen/gen_ch.h"
#include "gen/gen_ch_class.h"
#include "gen/gen_international.h"
#include "gen/gen_str.h"

inline bool id::operator == (const string & str) const
{
   return !id_cmp(this, str);
}
inline bool id::operator != (const string & str) const
{
   return id_cmp(this, str) != 0;
}
inline bool id::operator < (const string & str) const
{
   return id_cmp(this, str) < 0;
}
inline bool id::operator <= (const string & str) const
{
   return id_cmp(this, str) <= 0;
}
inline bool id::operator > (const string & str) const
{
   return id_cmp(this, str) > 0;
}
inline bool id::operator >= (const string & str) const
{
   return id_cmp(this, str) >= 0;
}


inline bool id::operator == (const string_interface & str) const
{
   return !id_cmp(this, string(str));
}
inline bool id::operator != (const string_interface & str) const
{
   return id_cmp(this, string(str)) != 0;
}
inline bool id::operator < (const string_interface & str) const
{
   return id_cmp(this, string(str)) < 0;
}
inline bool id::operator <= (const string_interface & str) const
{
   return id_cmp(this, string(str)) <= 0;
}
inline bool id::operator > (const string_interface & str) const
{
   return id_cmp(this, string(str)) > 0;
}
inline bool id::operator >= (const string_interface & str) const
{
   return id_cmp(this, string(str)) >= 0;
}


inline char string::last_char() const
{
   return operator[] (get_length() - 1);
}



inline id::operator const char *() const
{
   return m_pstr == NULL ? NULL : (const char *) *m_pstr;
}

inline bool id::is_empty() const
{
   return is_null() || (is_text() && (m_pstr == NULL || m_pstr->is_empty()));
}

inline CLASS_DECL_ca int_ptr id_cmp(const id * pid, const string & str)
{
   if(pid->is_null())
   {
      if(str.is_empty())
      {
         return 0;
      }
      else
      {
         return -1;
      }
   }
   else if(pid->is_text())
   {
      if(str.is_empty())
      {
         return 1;
      }
      else if(id_is_text(str))
      {
         return pid->m_pstr->Compare(str);
      }
      else
      {
         return 1;
      }
   }
   else // if(pid->is_number())
   {
      if(str.is_empty())
      {
         return 1;
      }
      else if(id_is_text(str))
      {
         return 1;
      }
      else
      {
         return pid->m_i - gen::str::to_int_ptr(str);
      }
   }
}

inline CLASS_DECL_ca int_ptr id_cmp(const id * pid, const char * psz)
{
   if(pid->is_null())
   {
      if(psz == NULL ||*psz == '\0')
      {
         return 0;
      }
      else
      {
         return -1;
      }
   }
   else if(pid->is_text())
   {
      if(psz == NULL ||*psz == '\0')
      {
         return 1;
      }
      else if(id_is_text(psz))
      {
         return pid->m_pstr->Compare(psz);
      }
      else
      {
         return 1;
      }
   }
   else // if(pid->is_number())
   {
      if(psz == NULL ||*psz == '\0')
      {
         return 1;
      }
      else if(id_is_text(psz))
      {
         return 1;
      }
      else
      {
         return pid->m_i - gen::str::to_int_ptr(psz);
      }
   }
}

inline CLASS_DECL_ca int_ptr id_strcmp(const id * pid1, const id * pid2)
{
   char register chCompare = pid1->m_chType - pid2->m_chType;
   if(chCompare != 0) return chCompare;
   if(pid1->m_chType == IDTYPE_TYPE_TEXT)
      return pid1->m_pstr->Compare(*pid2->m_pstr);
   else
      return pid1->m_i - pid2->m_i;
}

inline void id::raw_set(const string * pstr)
{
   if(pstr == NULL)
   {
      m_chType = IDTYPE_TYPE_NULL;
      m_i = 0;
   }
   else if(id_is_number(pstr->c_str()))
   {
      m_chType = IDTYPE_TYPE_NUMBER;
      m_i = gen::str::to_int_ptr(*pstr);
   }
   else
   {
      m_chType = IDTYPE_TYPE_TEXT;
      m_i = 0;
      m_pstr = pstr;
   }
}

inline string id::str() const
{
   if(m_chType == IDTYPE_TYPE_TEXT)
      return *m_pstr;
   else if(m_chType == IDTYPE_TYPE_NUMBER)
   {
      return gen::str::from(m_i);
   }
   else
      return "";
}

inline   string::string() throw() :
simple_string( string_trait::GetDefaultManager() )
{
}


#include "gen/gen_str2.h"



inline int __cdecl crt_char_traits::StringCompare(const char * pszA,const char * pszB ) throw()
{
   return strcmp( reinterpret_cast< const  char* >( pszA ), reinterpret_cast< const  char* >( pszB ) );
}

inline int __cdecl crt_char_traits::StringCompareIgnore(const char * pszA,const char * pszB ) throw()
{
#ifdef WINDOWS
   return _stricmp( reinterpret_cast< const  char* >( pszA ), reinterpret_cast< const  char* >( pszB ) );
#else
   return strcasecmp( reinterpret_cast< const  char* >( pszA ), reinterpret_cast< const  char* >( pszB ) );
#endif
}




inline int string::Compare(PCXSTR psz ) const
{
   //ENSURE( __is_valid_string( psz ) );
   return( string_trait::StringCompare( GetString(), psz ) );
}

inline int string::CompareNoCase(PCXSTR psz ) const RELEASENOTHROW
{
   //ASSERT( __is_valid_string( psz ) );
   return( string_trait::StringCompareIgnore( GetString(), psz ) );
}


inline bool CLASS_DECL_ca operator ==(const string & str1, const string & str2 ) throw()
{
   return str1.get_length() == str2.get_length() &&
      str1.Compare( str2 ) == 0;
}


inline   string CLASS_DECL_ca operator+(const string & str1,const string & str2 )
{
   string strResult( str1.GetManager() );

   string::Concatenate( strResult, str1, str1.get_length(), str2, str2.get_length() );

   return( strResult );
}

inline   string CLASS_DECL_ca operator+(const string & str1,string::PCXSTR psz2 )
{
   string strResult( str1.GetManager() );

   string::Concatenate( strResult, str1, str1.get_length(), psz2, string::StringLength( psz2 ) );

   return( strResult );
}

inline   string CLASS_DECL_ca operator+(string::PCXSTR psz1,const string & str2 )
{
   string strResult( str2.GetManager() );

   string::Concatenate( strResult, psz1, string::StringLength( psz1 ), str2, str2.get_length() );

   return( strResult );
}

inline   string CLASS_DECL_ca operator+(const string & str1,wchar_t ch2 )
{
   string strResult( str1.GetManager() );
   string::XCHAR chTemp = string::XCHAR( ch2 );

   string::Concatenate( strResult, str1, str1.get_length(), &chTemp, 1 );

   return( strResult );
}

inline   string CLASS_DECL_ca operator+(const string & str1,char ch2 )
{
   string strResult( str1.GetManager() );
   string::XCHAR chTemp = string::XCHAR( ch2 );

   string::Concatenate( strResult, str1, str1.get_length(), &chTemp, 1 );

   return( strResult );
}

inline   string CLASS_DECL_ca operator+(wchar_t ch1,const string & str2 )
{
   string strResult( str2.GetManager() );
   string::XCHAR chTemp = string::XCHAR( ch1 );

   string::Concatenate( strResult, &chTemp, 1, str2, str2.get_length() );

   return( strResult );
}

inline   string CLASS_DECL_ca operator+(char ch1,const string & str2 )
{
   string strResult( str2.GetManager() );
   string::XCHAR chTemp = string::XCHAR( ch1 );

   string::Concatenate( strResult, &chTemp, 1, str2, str2.get_length() );

   return( strResult );
}


inline   string CLASS_DECL_ca operator+ (const string & str1, int i2)
{

   string strResult( str1.GetManager() );

   strResult = str1 + gen::str::from(i2);

   return strResult;
}

inline   string CLASS_DECL_ca operator+ (int i1, const string & str2)
{

   string strResult( str2.GetManager() );

   strResult = gen::str::from(i1) + str2;

   return strResult;
}

inline   string CLASS_DECL_ca operator+ (const string & str1, int64_t i2)
{

   string strResult( str1.GetManager() );

   strResult = str1 + gen::str::from(i2);

   return strResult;
}

inline   string CLASS_DECL_ca operator+ (int64_t i1, const string & str2)
{

   string strResult( str2.GetManager() );

   strResult = gen::str::from(i1) + str2;

   return strResult;
}



inline   bool CLASS_DECL_ca operator==(const string & str1,const string_interface & str2 )
{
   return( str1.Compare(string(str2)) == 0 );
}

inline   bool CLASS_DECL_ca operator==(const string_interface & str1,const string & str2 )
{
   return( str2.Compare(string(str1)) == 0 );
}


inline   bool CLASS_DECL_ca operator==(const string & str1,string::PCXSTR psz2 ) throw()
{
   return( str1.Compare( psz2 ) == 0 );
}

inline   bool CLASS_DECL_ca operator==(string::PCXSTR psz1,const string & str2 ) throw()
{
   return( str2.Compare( psz1 ) == 0 );
}

inline   bool CLASS_DECL_ca operator==(const string & str1,string::PCYSTR psz2 ) THROWS
{
   string str2( psz2, str1.GetManager() );

   return( str1 == str2 );
}

inline   bool CLASS_DECL_ca operator==(string::PCYSTR psz1,const string & str2 ) THROWS
{
   string str1( psz1, str2.GetManager() );

   return( str1 == str2 );
}

inline   bool CLASS_DECL_ca operator==(const string & str1, int i)
{
   return strtoi(str1.operator string::PCXSTR()) == i;
}

inline   bool CLASS_DECL_ca operator==(int i, const string & str1)
{
   return strtoi(str1.operator string::PCXSTR()) == i;
}

inline   bool CLASS_DECL_ca operator!=(const string & str1,const string & str2 ) throw()
{
   return( str1.Compare( str2 ) != 0 );
}

inline   bool CLASS_DECL_ca operator!=(const string & str1,string::PCXSTR psz2 ) throw()
{
   return( str1.Compare( psz2 ) != 0 );
}

inline   bool CLASS_DECL_ca operator!=(string::PCXSTR psz1,const string & str2 ) throw()
{
   return( str2.Compare( psz1 ) != 0 );
}

inline   bool CLASS_DECL_ca operator!=(const string & str1,string::PCYSTR psz2 ) THROWS
{
   string str2( psz2, str1.GetManager() );

   return( str1 != str2 );
}

inline   bool CLASS_DECL_ca operator!=(string::PCYSTR psz1,const string & str2 ) THROWS
{
   string str1( psz1, str2.GetManager() );

   return( str1 != str2 );
}

inline   bool CLASS_DECL_ca operator!=(const string & str1, int i)
{
   return strtoi(str1.operator string::PCXSTR()) != i;
}

inline   bool CLASS_DECL_ca operator!=(int i, const string & str1)
{
   return strtoi(str1.operator string::PCXSTR()) != i;
}

inline   bool CLASS_DECL_ca operator<(const string & str1,const string & str2 ) throw()
{
   return( str1.Compare( str2 ) < 0 );
}

inline   bool CLASS_DECL_ca operator<(const string & str1,string::PCXSTR psz2 ) throw()
{
   return( str1.Compare( psz2 ) < 0 );
}

inline   bool CLASS_DECL_ca operator<(string::PCXSTR psz1,const string & str2 ) throw()
{
   return( str2.Compare( psz1 ) > 0 );
}

inline   bool CLASS_DECL_ca operator<(const string & str1, int i)
{
   return strtoi(str1.operator string::PCXSTR()) < i;
}

inline   bool CLASS_DECL_ca operator<(int i, const string & str1)
{
   return i < strtoi(str1.operator string::PCXSTR());
}

inline   bool CLASS_DECL_ca operator>(const string & str1,const string & str2 ) throw()
{
   return( str1.Compare( str2 ) > 0 );
}

inline   bool CLASS_DECL_ca operator>(const string & str1,string::PCXSTR psz2 ) throw()
{
   return( str1.Compare( psz2 ) > 0 );
}


inline   bool CLASS_DECL_ca operator>(string::PCXSTR psz1,const string & str2 ) throw()
{
   return( str2.Compare( psz1 ) < 0 );
}


inline   bool CLASS_DECL_ca operator>(const string & str1, int i)
{
   return strtoi(str1.operator string::PCXSTR()) > i;
}


inline   bool CLASS_DECL_ca operator>(int i, const string & str1)
{
   return i > strtoi(str1.operator string::PCXSTR());
}


inline   bool CLASS_DECL_ca operator<=(const string & str1,const string & str2 ) throw()
{
   return( str1.Compare( str2 ) <= 0 );
}


inline   bool CLASS_DECL_ca operator<=(const string & str1,string::PCXSTR psz2 ) throw()
{
   return( str1.Compare( psz2 ) <= 0 );
}


inline   bool CLASS_DECL_ca operator<=(string::PCXSTR psz1,const string & str2 ) throw()
{
   return( str2.Compare( psz1 ) >= 0 );
}


inline   bool CLASS_DECL_ca operator<=(const string & str1, int i)
{
   return strtoi(str1.operator string::PCXSTR()) <= i;
}


inline bool CLASS_DECL_ca operator<=(int i, const string & str1)
{
   return i <= strtoi(str1.operator string::PCXSTR());
}


inline   bool CLASS_DECL_ca operator>=(const string & str1,const string & str2 ) throw()
{
   return( str1.Compare( str2 ) >= 0 );
}


inline   bool CLASS_DECL_ca operator>=(const string & str1,string::PCXSTR psz2 ) throw()
{
   return( str1.Compare( psz2 ) >= 0 );
}


inline   bool CLASS_DECL_ca operator>=(string::PCXSTR psz1,const string & str2 ) throw()
{
   return( str2.Compare( psz1 ) <= 0 );
}


inline bool CLASS_DECL_ca operator>=(const string & str1, int i)
{
   return strtoi(str1.operator string::PCXSTR()) >= i;
}


inline   bool CLASS_DECL_ca operator>=(int i, const string & str1)
{
   return i >= strtoi(str1.operator string::PCXSTR());
}


inline   bool CLASS_DECL_ca operator==(string::XCHAR ch1,const string & str2 ) throw()
{
   return( (str2.get_length() == 1) && (str2[0] == ch1) );
}


inline   bool CLASS_DECL_ca operator==(const string & str1,string::XCHAR ch2 ) throw()
{
   return( (str1.get_length() == 1) && (str1[0] == ch2) );
}


inline   bool CLASS_DECL_ca operator!=(string::XCHAR ch1,const string & str2 ) throw()
{
   return( (str2.get_length() != 1) || (str2[0] != ch1) );
}


inline   bool CLASS_DECL_ca operator!=(const string & str1,string::XCHAR ch2 ) throw()
{
   return( (str1.get_length() != 1) || (str1[0] != ch2) );
}


inline string::operator PCXSTR() const throw()
{
   return simple_string::operator PCXSTR();
}


inline string::PCXSTR string::c_str() const throw()
{
   return simple_string::operator PCXSTR();
}

inline strsize string::remove(strsize iIndex,strsize nCount)
{
   return Delete(iIndex, nCount);
}

inline string str(Platform::String ^ str)
{
   if(str == nullptr)
      return "";
   return str->Begin();
}
