#pragma once


CLASS_DECL_BASE string_manager * __get_string_manager();
CLASS_DECL_BASE int64_t strtoi(const char * psz);
CLASS_DECL_BASE int64_t strtoi(const wchar_t * psz);


inline UINT _gen_GetConversionACP()
{
   return CP_UTF8;
}




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
//    'char Length' - Number of distinct characters in string.  For wide-
//       character strings, this is equivalent to half the 'byte Length'.
//       For ANSI strings, this is equivalent to the 'byte Length'.  For MBCS
//       strings, 'char Length' counts a lead-byte/trail-byte combination
//       as one character.
//    'Length' - When neither of the above terms is used, 'Length' refers to
//       length in XCHARs, which is equal to 'byte Length'/sizeof(char).
/////////////////////////////////////////////////////////////////////////////


#define IMPLEMENT_CONST_STRING_PTR(stringype, value, name) const const_fixed_string<stringype, sizeof(value)/sizeof(stringype::char)> _init##name ={    {NULL,      sizeof(value)/sizeof(stringype::char)-1,    sizeof(value)/sizeof(stringype::char)-1,    -1},         value   };   const stringype::char* const _value##name = _init##name.m_achData;   extern const stringype* const name = CONST_STRING_PTR(stringype, name);
#define DECLARE_CONST_STRING_PTR(stringype, name) extern const stringype* const name;
#define CONST_STRING_PTR(stringype, name) reinterpret_cast<const stringype* const>(&_value##name)


class crt_char_traits :
   public char_traits_base
{
public:

   static char*         __cdecl  CharNext(const char* p ) throw();
   static int32_t           __cdecl  IsDigit(const char * pch ) throw();
   static int32_t           __cdecl  IsSpace(const char * pch ) throw();
   static int32_t           __cdecl  StringCompare(const char * pszA,const char * pszB ) throw();
   static int32_t           __cdecl  StringCompareIgnore(const char * pszA,const char * pszB ) throw();
   static int32_t           __cdecl  StringCollate(const char * pszA,const char * pszB ) throw();
   static int32_t           __cdecl  StringCollateIgnore(const char * pszA,const char * pszB ) throw();
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

   static uint32_t         __cdecl  FormatMessage(uint32_t dwFlags, LPCVOID pSource, uint32_t dwMessageID,uint32_t dwLanguageID, char * pszBuffer, uint32_t nSize, va_list* pArguments ) throw();
   static uint32_t         __cdecl  format_message(uint32_t dwFlags, LPCVOID pSource, uint32_t dwMessageID,uint32_t dwLanguageID, char * pszBuffer, uint32_t nSize, va_list* pArguments ) throw();
   static strsize       __cdecl  SafeStringLen( const char * psz ) throw();
   static strsize       __cdecl  SafeStringLen( const wchar_t * psz ) throw();
   static strsize       __cdecl  GetCharLen(const wchar_t* pch ) throw();
   static strsize       __cdecl  GetCharLen(const char* pch ) throw();
   static uint32_t         __cdecl  GetEnvironmentVariable(const char * pszVar, char * pszBuffer, uint32_t dwSize);

};
























class string_trait :
   public crt_char_traits // iterator
{
public:

   CLASS_DECL_BASE static string_manager * GetDefaultManager() throw()
   {
      static string_manager * s_pdefaultManager = __get_string_manager();
      return s_pdefaultManager;
   }

};


class fixed_alloc_array;





class CLASS_DECL_BASE string :
   public simple_string
#if defined(LINUX)
   , public string_format_printer
#endif
{
public:


   template < typename T >
   friend inline string to_string(T o);


   operator class string_composite ();
   operator class string_composite const () const;
   operator const char *() const throw();
   const char * c_str() const throw();
   const char * data() const throw();

   void construct() throw();
   inline string() throw();
   explicit string( string_manager * pstringmanager ) throw();
   static void __cdecl Construct( string* pstring );

   string(const char * pszSrc);
   string(const uchar * pszSrc);
   string(char * pszSrc);
   string(uchar * pszSrc);
   string(wchar_t * pszSrc);
   string(const wchar_t * pszSrc);
   string(const string & strSrc);
   string(const istring & istr);
   string(const string_interface & str);

   inline string(const id & id);
   inline string(const var & var);
   inline string(const property & prop);

   template < typename T >
   inline explicit string(T o) :
      simple_string(string_trait::GetDefaultManager())
   {

      *this = to_string(o);

   }


#if defined(METROWIN) && defined(__cplusplus_winrt)
   string(Platform::Object ^ o);
#endif
   string(const char * pszSrc,string_manager * pstringmanager );
   string(const wchar_t * pszSrc,string_manager * pstringmanager );



   string(const uchar* pszSrc, string_manager * pstringmanager);
   explicit string(char ch, strsize nLength = 1);
   string(strsize nLength, char ch);
   string(wchar_t ch, strsize nLength = 1 );
   string(const char* pch, strsize nLength);
   string(const char* pch, strsize nLength, string_manager * pstringmanager );
   string(const wchar_t* pch, strsize nLength);
   string(const wchar_t* pch, strsize nLength, string_manager * pstringmanager);
#if defined(METROWIN) && defined(__cplusplus_winrt)
   string(Platform::Object ^ o, string_manager * pstringmanager);
#endif
   ~string() throw();



   inline string & operator = (const id & str);
   inline string & operator = (const var & var);
   inline string & operator = (const property & prop);

   string & operator = (const string_interface & str );
   //string & operator = (string strSrc);
   string & operator = (const simple_string & strSrc);
   string & operator = (const string & strSrc);
   string & operator = (const char * pszSrc);
   string & operator = (const wchar_t * pszSrc);
   string & operator = (const uchar* pszSrc);
   string & operator = (char ch);
#if defined(METROWIN) && defined(__cplusplus_winrt)
   string & operator = (const Platform::String ^ & str);
#endif
   string & operator = (wchar_t ch);

   // Assignment operators
   template < typename T >
   inline string & operator = (T o);

   string& operator+=(const simple_string& str );
   string& operator+=(const char * pszSrc );
   template< strsize t_nSize >
   string& operator+=(const static_string<t_nSize >& strSrc );
   string& operator+=(const wchar_t * pszSrc );
   string& operator+=(char ch );
   string& operator+=(uchar ch );
   string& operator+=(wchar_t ch );

   // Override from base class
   string_manager * GetManager() const throw();


   string & assign(const string & str);
   string & assign(const string & str, strsize pos, strsize n);
   string & assign(const char * s, strsize n);
   string & assign(const char * s);
   string & assign(strsize n, char ca);
   string & assign(int64_t n, int64_t ca);
   string & assign(int32_t n, int32_t ca);
   string & assign(uint32_t n, uint32_t ca);
   string & assign(uint64_t n, uint64_t ca);
   template <class InputIterator>
   string & assign (InputIterator first, InputIterator last);

   // Comparison
   int32_t Compare(const char * psz ) const;
   int32_t CompareNoCase(const char * psz) const RELEASENOTHROW;



   int32_t Collate(const char * psz ) const RELEASENOTHROW;
   int32_t CollateNoCase(const char * psz ) const RELEASENOTHROW;

   int32_t compare(const char * psz ) const;
   int32_t compare_no_case(const char * psz ) const throw();
   int32_t collate(const char * psz ) const throw();
   int32_t collate_no_case(const char * psz ) const throw();

   int32_t compare(strsize iStart, strsize iCount, const char * psz ) const;
   int32_t compare_no_case(strsize iStart, strsize iCount, const char * psz ) const;
   int32_t collate(strsize iStart, strsize iCount, const char * psz ) const;
   int32_t collate_no_case(strsize iStart, strsize iCount, const char * psz ) const;

   int32_t compare(strsize iStart, strsize iCount, const char * psz, strsize iStart2, strsize iCount2) const;
   int32_t compare_no_case(strsize iStart, strsize iCount, const char * psz, strsize iStart2, strsize iCount2) const;
   int32_t collate(strsize iStart, strsize iCount, const char * psz, strsize iStart2, strsize iCount2) const;
   int32_t collate_no_case(strsize iStart, strsize iCount, const char * psz, strsize iStart2, strsize iCount2) const;

   bool contains(char ch, strsize start = 0, strsize count = -1);
   bool contains(wchar_t wch, strsize start = 0, strsize count = -1);
   bool contains(int32_t i, strsize start = 0, strsize count = -1); // utf8 char index
   bool contains(const char * psz, strsize start = 0, strsize count = -1);
   bool contains(const string & str, strsize start = 0, strsize count = -1);

   bool contains_ci(char ch, strsize start = 0, strsize count = -1);
   bool contains_ci(wchar_t wch, strsize start = 0, strsize count = -1);
   bool contains_ci(int32_t i, strsize start = 0, strsize count = -1); // utf8 char index
   bool contains_ci(const char * psz, strsize start = 0, strsize count = -1);
   bool contains_ci(const string & str, strsize start = 0, strsize count = -1);

   bool contains_wci(char ch, strsize start = 0, strsize count = -1);
   bool contains_wci(wchar_t wch, strsize start = 0, strsize count = -1);
   bool contains_wci(int32_t i, strsize start = 0, strsize count = -1); // utf8 char index
   bool contains_wci(const char * psz, strsize start = 0, strsize count = -1);
   bool contains_wci(const string & str, strsize start = 0, strsize count = -1);
   // Advanced manipulation


   void reserve(strsize res_arg = 0);

   // Delete 'nCount' characters, starting at index 'iIndex'
   strsize Delete(strsize iIndex, strsize nCount = 1);
   strsize remove(strsize iIndex, strsize nCount = 1);

   string & erase(strsize start = 0, strsize count = -1);


   // Insert character 'ch' before index 'iIndex'
   strsize Insert(strsize iIndex,char ch );

   // Insert string 'psz' before index 'iIndex'
   strsize Insert(strsize iIndex,const char * psz );

   // replace all occurrences of character 'chOld' with character 'chNew'
   strsize replace(char chOld,char chNew, strsize iStart = 0);

   // replace all occurrences of string 'pszOld' with string 'pszNew'
   strsize replace(const char * pszOld,const char * pszNew, strsize iStart = 0);

   strsize replace_ci(const char * pszOld,const char * pszNew, strsize iStart = 0);

   string & replace(strsize iStart, strsize nCount, const char * psz);

   // remove all occurrences of character 'chRemove'
   strsize remove(char chRemove );

   string Tokenize(const char * pszTokens, strsize& iStart ) const;
   // find routines

   // find the first occurrence of character 'ch', starting at index 'iStart'
   strsize find(char ch, strsize start = 0, strsize count = -1) const RELEASENOTHROW;
   strsize find_ci(char ch, strsize start = 0, strsize count = -1) const RELEASENOTHROW;

   // look for a specific sub-string

   // find the first occurrence of string 'pszSub', starting at index 'iStart'
   strsize find(const char * pszSub,strsize start = 0,strsize count = -1,const char ** pszTail = NULL) const RELEASENOTHROW;
   strsize find_w(const char * pszSub,strsize start = 0,strsize count = -1,const char ** pszTail = NULL) const RELEASENOTHROW;
   strsize find_ci(const char * pszSub,strsize start = 0,strsize count = -1,const char ** pszTail = NULL) const RELEASENOTHROW;
   strsize find_wci(const char * pszSub, strsize start = 0, strsize count = -1, const char ** pszTail = NULL) const RELEASENOTHROW;

   // find the first occurrence of string 'pszSub', starting at index 'iStart', if found returns the index of first character after the end of the found string
   strsize find_tail(const char * pszSub,strsize start = 0,strsize count = -1) const RELEASENOTHROW;
   strsize find_w_tail(const char * pszSub,strsize start = 0,strsize count = -1) const RELEASENOTHROW;
   strsize find_ci_tail(const char * pszSub,strsize start = 0,strsize count = -1) const RELEASENOTHROW;
   strsize find_wci_tail(const char * pszSub,strsize start = 0,strsize count = -1) const RELEASENOTHROW;

   // find the first occurrence of any of the characters in string 'pszCharSet'
   strsize FindOneOf(const char * pszCharSet, strsize iStart = 0, strsize n = -1 ) const RELEASENOTHROW;

   strsize find_first_in(const string & str, strsize pos = 0) const RELEASENOTHROW;
   strsize find_first_in(const char * s, strsize pos, strsize n) const RELEASENOTHROW;
   strsize find_first_in(const char * s, strsize pos = 0) const RELEASENOTHROW;
   strsize find_first_in(char ca, strsize pos = 0) const RELEASENOTHROW;

   strsize find_first_not_in(const string & str, strsize pos = 0) const RELEASENOTHROW;
   strsize find_first_not_in(const char * s, strsize pos, strsize n) const RELEASENOTHROW;
   strsize find_first_not_in(const char * s, strsize pos = 0) const RELEASENOTHROW;
   strsize find_first_not_in(char ca, strsize pos = 0) const RELEASENOTHROW;

   strsize find_last_not_in(const string & str, strsize pos = -1) const RELEASENOTHROW;
   strsize find_last_not_in(const char * s, strsize pos, strsize n) const RELEASENOTHROW;
   strsize find_last_not_in(const char * s, strsize pos = -1) const RELEASENOTHROW;
   strsize find_last_not_in(char ca, strsize pos = -1) const RELEASENOTHROW;

   strsize find_last_in(const string & str, strsize pos = -1) const RELEASENOTHROW;
   strsize find_last_in(const char * s, strsize pos, strsize n) const RELEASENOTHROW;
   strsize find_last_in(const char * s, strsize pos = -1) const RELEASENOTHROW;
   strsize find_last_in(char ca, strsize pos = -1) const RELEASENOTHROW;

   strsize find_first_of(const string & str, strsize pos = 0) const RELEASENOTHROW;
   strsize find_first_of(const char * s, strsize pos, strsize n) const RELEASENOTHROW;
   strsize find_first_of(const char * s, strsize pos = 0) const RELEASENOTHROW;
   strsize find_first_of(char ca, strsize pos = 0) const RELEASENOTHROW;

   strsize find_first_not_of(const string & str, strsize pos = 0) const RELEASENOTHROW;
   strsize find_first_not_of(const char * s, strsize pos, strsize n) const RELEASENOTHROW;
   strsize find_first_not_of(const char * s, strsize pos = 0) const RELEASENOTHROW;
   strsize find_first_not_of(char ca, strsize pos = 0) const RELEASENOTHROW;

   strsize find_last_not_of(const string & str, strsize pos = -1) const RELEASENOTHROW;
   strsize find_last_not_of(const char * s, strsize pos, strsize n) const RELEASENOTHROW;
   strsize find_last_not_of(const char * s, strsize pos = -1) const RELEASENOTHROW;
   strsize find_last_not_of(char ca, strsize pos = -1) const RELEASENOTHROW;

   strsize find_last_of(const string & str, strsize pos = -1) const RELEASENOTHROW;
   strsize find_last_of(const char * s, strsize pos, strsize n) const RELEASENOTHROW;
   strsize find_last_of(const char * s, strsize pos = -1) const RELEASENOTHROW;
   strsize find_last_of(char ca, strsize pos = -1) const RELEASENOTHROW;

   // find the last occurrence of character 'ch'
   strsize reverse_find(char ch, strsize iStart = -1 ) const RELEASENOTHROW;

   // find the last occurrence of character 'ch'
   strsize reverse_find( const char * ch, strsize iStart = -1 ) const RELEASENOTHROW;


   inline bool ends_ci(const string & strSuffixCandidate);


   bool begins_ci(const char * s) const;


   char last_char() const;

   // manipulation

   // Convert the string to uppercase
   string& make_upper();

   // Convert the string to lowercase
   string& make_lower();

   // Reverse the string
   string& MakeReverse();

   string lower() const;

   string upper() const;


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
   string& trim(char chTarget );

   // remove all leading and trailing occurrences of any of the characters in the string 'pszTargets'
   string& trim(const char * pszTargets );

   // trimming anything (either side)

   // remove all trailing occurrences of character 'chTarget'
   string& trim_right(char chTarget );

   // remove all trailing occurrences of any of the characters in string 'pszTargets'
   string& trim_right(const char * pszTargets );

   // remove all leading occurrences of character 'chTarget'
   string& trim_left(char chTarget );

   // remove all leading occurrences of any of the characters in string 'pszTargets'
   string& trim_left(const char * pszTargets );


   // remove all trailing whitespace
   string right_trimmed() const;

   // remove all leading whitespace
   string left_trimmed() const;

   // remove all leading and trailing whitespace
   string trimmed() const;

   // remove all leading and trailing occurrences of character 'chTarget'
   string trimmed(char chTarget) const;

   // remove all leading and trailing occurrences of any of the characters in the string 'pszTargets'
   string trimmed(const char * pszTargets) const;

   // trimming anything (either side)

   // remove all trailing occurrences of character 'chTarget'
   string right_trimmed(char chTarget) const;

   // remove all trailing occurrences of any of the characters in string 'pszTargets'
   string right_trimmed(const char * pszTargets) const;

   // remove all leading occurrences of character 'chTarget'
   string left_trimmed(char chTarget) const;

   // remove all leading occurrences of any of the characters in string 'pszTargets'
   string left_trimmed(const char * pszTargets) const;


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
   string SpanIncluding(const char * pszCharSet ) const;

   // Return the substring consisting of the leftmost characters not in the set 'pszCharSet'
   string SpanExcluding(const char * pszCharSet ) const;

   // Format data using format string 'pszFormat'
#ifdef VARIADIC_TEMPLATE

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


#else


   void __cdecl Format(const char * pszFormat, ... );



#endif


   // append formatted data using format string 'pszFormat'
   void __cdecl AppendFormat(const char * pszFormat, ... );

   void AppendFormatV(const char * pszFormat, va_list args );

   void FormatV(const char * pszFormat, va_list args );

   void __cdecl FormatMessage(const char * pszFormat, ... );

   void __cdecl format_message(const char * pszFormat, ... );

   // Format a message using format string 'pszFormat' and va_list
   void FormatMessageV(const char * pszFormat, va_list* pArgList );

#ifdef WINDOWS

   // OLE BSTR support

   // allocate a BSTR containing a copy of the string
   BSTR AllocSysString() const;

   BSTR SetSysString(BSTR* pbstr ) const;

#endif

   // set the string to the value of environment var 'pszVar'
   bool GetEnvironmentVariable(const char * pszVar);

   // set the string to the value of environment var 'pszVar'
   bool getenv(const char * pszVar);

   // Load the string from resource 'nID'
   bool load_string(sp(::base::application) papp, id id);

   // Load the string from resource 'nID' in module 'hInstance'
   /*    bool load_string(HINSTANCE hInstance,strsize nID )
   {
   const STRINGRESOURCEIMAGE* pImage = gen_GetStringResourceImage( hInstance, nID );
   if( pImage == NULL )
   {
   return( FALSE );
   }

   strsize nLength = str_traits::GetcharLength( pImage->achString, pImage->nLength );
   char * pszBuffer = GetBuffer( nLength );
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
   char * pszBuffer = GetBuffer( nLength );
   str_traits::ConvertTochar( pszBuffer, nLength, pImage->achString, pImage->nLength );
   ReleaseBufferSetLength( nLength );

   return( TRUE );
   }*/

   void resize (strsize n)
   {
      resize(n, '\0');
   }

   void resize (strsize n, char c)
   {

      strsize nOldSize = length();

      if(n < nOldSize)
      {
         Truncate(n);
      }
      else
      {
         LPSTR lpsz = GetBufferSetLength(n);
         memset(&lpsz[nOldSize], c, n - nOldSize);
         ReleaseBuffer(n);
      }

   }


   friend string CLASS_DECL_BASE operator+(const string & str1,const string & str2 );
   friend string CLASS_DECL_BASE operator+(const string & str1,const char * psz2 );
   friend string CLASS_DECL_BASE operator+(const char * psz1,const string & str2 );
   friend string CLASS_DECL_BASE operator+(const string & str1,wchar_t ch2 );
   friend string CLASS_DECL_BASE operator+(wchar_t ch1,const string & str2 );
   friend string CLASS_DECL_BASE operator+(const string & str1,char ch2 );
   friend string CLASS_DECL_BASE operator+(char ch1,const string & str2 );
   friend string CLASS_DECL_BASE operator+(const string & str1,int32_t ch2 );
   friend string CLASS_DECL_BASE operator+(int32_t ch1,const string & str2 );
   friend string CLASS_DECL_BASE operator+(const string & str1,int64_t ch2 );
   friend string CLASS_DECL_BASE operator+(int64_t ch1,const string & str2 );
   friend string CLASS_DECL_BASE operator+(const var & var, const char * psz);
   friend string CLASS_DECL_BASE operator+(const char * psz, const var & var);
   friend string CLASS_DECL_BASE operator+(const var & var, const string & str);
   friend string CLASS_DECL_BASE operator+(const string & str, const var & var);



   bool operator==(const string_interface & str) const;
   bool operator==(const string & str) const;
   bool operator==(const char * psz2) const;
   bool operator==(const wchar_t * psz2) const;
   bool operator==(char psz2) const;
   bool operator==(wchar_t psz2) const;
   bool operator==(int32_t i) const;

   bool operator>(const string_interface & str) const;
   bool operator>(const string & str) const;
   bool operator>(const char * psz2) const;
   bool operator>(const wchar_t * psz2) const;
   bool operator>(char psz2) const;
   bool operator>(wchar_t psz2) const;
   bool operator>(int32_t i) const;

   bool operator<(const string_interface & str) const;
   bool operator<(const string & str) const;
   bool operator<(const char * psz2) const;
   bool operator<(const wchar_t * psz2) const;
   bool operator<(char psz2) const;
   bool operator<(wchar_t psz2) const;
   bool operator<(int32_t i) const;

   inline bool operator!=(const string_interface & str)   const { return !operator ==(str); }
   inline bool operator!=(const string & str )            const { return !operator ==(str); }
   inline bool operator!=(const char * psz)                     const { return !operator ==(psz); }
   inline bool operator!=(const wchar_t * psz)                     const { return !operator ==(psz); }
   inline bool operator!=(char ch)                       const { return !operator ==(ch);  }
   inline bool operator!=(wchar_t ch)                       const { return !operator ==(ch);  }
   inline bool operator!=(int32_t i)                      const { return !operator ==(i);  }

   inline bool operator>=(const string_interface & str)   const { return !operator <(str); }
   inline bool operator>=(const string & str )            const { return !operator <(str); }
   inline bool operator>=(const char * psz)                     const { return !operator <(psz); }
   inline bool operator>=(const wchar_t * psz)                     const { return !operator <(psz); }
   inline bool operator>=(char ch)                       const { return !operator <(ch);  }
   inline bool operator>=(wchar_t ch)                       const { return !operator <(ch);  }
   inline bool operator>=(int32_t i)                      const { return !operator <(i);  }

   inline bool operator<=(const string_interface & str)   const { return !operator >(str); }
   inline bool operator<=(const string & str )            const { return !operator >(str); }
   inline bool operator<=(const char * psz)                     const { return !operator >(psz); }
   inline bool operator<=(const wchar_t * psz)                     const { return !operator >(psz); }
   inline bool operator<=(char ch)                       const { return !operator >(ch);  }
   inline bool operator<=(wchar_t ch)                       const { return !operator >(ch);  }
   inline bool operator<=(int32_t i)                      const { return !operator >(i);  }


   typedef strsize size_type;


   inline static string empty_string()
   {
      return string();
   }



#if defined(METROWIN) && defined(__cplusplus_winrt)
inline operator Platform::String ^() const
{
   return ref new Platform::String(wstring(*this));
}
inline operator Platform::String ^()
{
   return ref new Platform::String(wstring(*this));
}
#endif



};


template < typename T >
inline string to_string(T o)
{

   return o.to_string();

}




template < typename T >
inline string & string::operator = (T o)
{

   return operator =(to_string(o));

}


template< strsize t_nSize >
string& string::operator+=(const static_string<t_nSize >& strSrc )
{
   simple_string::operator+=( strSrc );

   return *this;
}

inline string & string::operator=(const simple_string& strSrc )
{
   simple_string::operator=( strSrc );

   return *this;
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



inline strsize string::find_first_in(const string & str, strsize pos) const RELEASENOTHROW
{
   return find_first_of(str, pos);
}

inline strsize string::find_first_in(const char * s, strsize pos, strsize n) const RELEASENOTHROW
{
   return find_first_of(s, pos, n);
}

inline strsize string::find_first_in(const char * s, strsize pos) const RELEASENOTHROW
{
   return find_first_of(s, pos);
}

inline strsize string::find_first_in(char ca, strsize pos) const RELEASENOTHROW
{
   return find_first_of(ca, pos);
}

inline strsize string::find_first_not_in(const string & str, strsize pos) const RELEASENOTHROW
{
   return find_first_not_of(str, pos);
}

inline strsize string::find_first_not_in(const char * s, strsize pos, strsize n) const RELEASENOTHROW
{
   return find_first_not_of(s, pos, n);
}

inline strsize string::find_first_not_in(const char * s, strsize pos) const RELEASENOTHROW
{
   return find_first_not_of(s, pos);
}

inline strsize string::find_first_not_in(char ca, strsize pos) const RELEASENOTHROW
{
   return find_first_not_of(ca, pos);
}

inline strsize string::find_last_not_in(const string & str, strsize pos) const RELEASENOTHROW
{
   return find_first_not_of(str, pos);
}

inline strsize string::find_last_not_in(const char * s, strsize pos, strsize n) const RELEASENOTHROW
{
   return find_last_not_of(s, pos, n);
}

inline strsize string::find_last_not_in(const char * s, strsize pos) const RELEASENOTHROW
{
   return find_last_not_of(s, pos);
}

inline strsize string::find_last_not_in(char ca, strsize pos) const RELEASENOTHROW
{
   return find_last_not_of(ca, pos);
}

inline strsize string::find_last_in(const string & str, strsize pos) const RELEASENOTHROW
{
   return find_last_of(str, pos);
}

inline strsize string::find_last_in(const char * s, strsize pos, strsize n) const RELEASENOTHROW
{
   return find_last_of(s, pos, n);
}

inline strsize string::find_last_in(const char * s, strsize pos) const RELEASENOTHROW
{
   return find_last_of(s, pos);
}

inline strsize string::find_last_in(char ca, strsize pos) const RELEASENOTHROW
{
   return find_last_of(ca, pos);
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

inline void string_composite::set_string(const string & str, ::action::context actioncontext)
{
   if(m_pstring != NULL)
      m_pstring->set_string(str);
   else
      m_pinterface->set_string(str, actioncontext);
}

class CLASS_DECL_BASE const_empty_string :
   public string_interface
{
public:
   strsize get_length() const;
   void get_string(char * pszstr) const;
   void set_string(const string & str, ::action::context actioncontext);
};




namespace str
{

   extern CLASS_DECL_BASE const_empty_string g_strEmpty;

   CLASS_DECL_BASE string_interface & empty_string();

}


#define BAD_WCHAR ((wchar_t)(0xFFFF))

/// macro - number of elements in array
#define ARRAY_SIZE(a) (sizeof(a)/sizeof(*(a)))

#include "base/primitive/str/x/x_charcategory.h"
#include "base/primitive/primitive_bit.h"
#include "base/primitive/collection/collection_bit_array.h"


inline bool id::operator == (const string & str) const
{
   return m_pstr == NULL ? false : m_pstr->compare(str) == 0;
}
inline bool id::operator != (const string & str) const
{
   return m_pstr == NULL ? true : m_pstr->compare(str) != 0;
}
inline bool id::operator < (const string & str) const
{
   return m_pstr == NULL ? true : m_pstr->compare(str) < 0;
}
inline bool id::operator <= (const string & str) const
{
   return m_pstr == NULL ? true : m_pstr->compare(str) <= 0;
}
inline bool id::operator > (const string & str) const
{
   return m_pstr == NULL ? false : m_pstr->compare(str) > 0;
}
inline bool id::operator >= (const string & str) const
{
   return m_pstr == NULL ? false : m_pstr->compare(str) >= 0;
}


inline bool id::operator == (const string_interface & str) const
{
   return m_pstr == NULL ? false : m_pstr->compare(string(str)) == 0;
}
inline bool id::operator != (const string_interface & str) const
{
   return m_pstr == NULL ? true : m_pstr->compare(string(str)) != 0;
}
inline bool id::operator < (const string_interface & str) const
{
   return m_pstr == NULL ? true : m_pstr->compare(string(str)) < 0;
}
inline bool id::operator <= (const string_interface & str) const
{
   return m_pstr == NULL ? true : m_pstr->compare(string(str)) <= 0;
}
inline bool id::operator > (const string_interface & str) const
{
   return m_pstr == NULL ? false : m_pstr->compare(string(str)) > 0;
}
inline bool id::operator >= (const string_interface & str) const
{
   return m_pstr == NULL ? false : m_pstr->compare(string(str)) >= 0;
}


inline char string::last_char() const
{
   return operator[] (get_length() - 1);
}



























inline string::string(const id & id) :
   simple_string(string_trait::GetDefaultManager())
{

   operator = (id.to_string());

}

inline string & string::operator = (const id & id)
{

   return operator = (id.to_string());

}

inline id::operator const char *() const
{
   return m_pstr == NULL ? NULL : (const char *) *m_pstr;
}

inline string id::to_string() const
{
    return m_pstr == NULL ? string() : *m_pstr;
}
























inline bool id::is_empty() const
{
   return is_null() || m_pstr->is_empty();
}



inline CLASS_DECL_BASE int_ptr id_strcmp(const id * pid1, const id * pid2)
{
   return pid1->m_pstr->Compare(*pid2->m_pstr);
}

inline void id::raw_set(const string * pstr)
{
   m_pstr = pstr;
}

inline string id::str() const
{
   return m_pstr == NULL ? string() : *m_pstr;
}

inline   string::string() throw() :
simple_string( string_trait::GetDefaultManager() )
{
}





inline int32_t __cdecl crt_char_traits::StringCompare(const char * pszA,const char * pszB ) throw()
{

   return strcmp( reinterpret_cast< const  char* >( pszA ), reinterpret_cast< const  char* >( pszB ) );

}


inline int32_t __cdecl crt_char_traits::StringCompareIgnore(const char * pszA,const char * pszB ) throw()
{

   return stricmp_dup(reinterpret_cast< const  char* >( pszA ), reinterpret_cast< const  char* >( pszB ) );

}




inline int32_t string::Compare(const char * psz ) const
{
   //ENSURE( __is_valid_string( psz ) );
   return( string_trait::StringCompare( GetString(), psz ) );
}

inline int32_t string::CompareNoCase(const char * psz ) const RELEASENOTHROW
{
   //ASSERT( __is_valid_string( psz ) );
   return( string_trait::StringCompareIgnore( GetString(), psz ) );
}


inline   string CLASS_DECL_BASE operator+(const string & str1,const string & str2 )
{
   string strResult( str1.GetManager() );

   string::Concatenate( strResult, str1, str1.get_length(), str2, str2.get_length() );

   return( strResult );
}

inline   string CLASS_DECL_BASE operator+(const string & str1,const char * psz2 )
{
   string strResult( str1.GetManager() );

   string::Concatenate( strResult, str1, str1.get_length(), psz2, string::StringLength( psz2 ) );

   return( strResult );
}

inline   string CLASS_DECL_BASE operator+(const char * psz1,const string & str2 )
{
   string strResult( str2.GetManager() );

   string::Concatenate( strResult, psz1, string::StringLength( psz1 ), str2, str2.get_length() );

   return( strResult );
}

inline   string CLASS_DECL_BASE operator+(const string & str1,wchar_t ch2 )
{
   string strResult( str1.GetManager() );
   char chTemp = char( ch2 );

   string::Concatenate( strResult, str1, str1.get_length(), &chTemp, 1 );

   return( strResult );
}

inline   string CLASS_DECL_BASE operator+(const string & str1,char ch2 )
{
   string strResult( str1.GetManager() );
   char chTemp = char( ch2 );

   string::Concatenate( strResult, str1, str1.get_length(), &chTemp, 1 );

   return( strResult );
}

inline   string CLASS_DECL_BASE operator+(wchar_t ch1,const string & str2 )
{
   string strResult( str2.GetManager() );
   char chTemp = char( ch1 );

   string::Concatenate( strResult, &chTemp, 1, str2, str2.get_length() );

   return( strResult );
}

inline   string CLASS_DECL_BASE operator+(char ch1,const string & str2 )
{
   string strResult( str2.GetManager() );
   char chTemp = char( ch1 );

   string::Concatenate( strResult, &chTemp, 1, str2, str2.get_length() );

   return( strResult );
}


inline   string CLASS_DECL_BASE operator+ (const string & str1, int32_t i2)
{

   string strResult( str1.GetManager() );

   strResult = str1 + ::str::from(i2);

   return strResult;
}

inline   string CLASS_DECL_BASE operator+ (int32_t i1, const string & str2)
{

   string strResult( str2.GetManager() );

   strResult = ::str::from(i1) + str2;

   return strResult;
}

inline   string CLASS_DECL_BASE operator+ (const string & str1, int64_t i2)
{

   string strResult( str1.GetManager() );

   strResult = str1 + ::str::from(i2);

   return strResult;
}

inline   string CLASS_DECL_BASE operator+ (int64_t i1, const string & str2)
{

   string strResult( str2.GetManager() );

   strResult = ::str::from(i1) + str2;

   return strResult;
}



inline bool string::operator==(const string & str) const
{

   return get_length() == str.get_length() && Compare(str.m_pszData) == 0;

}


inline bool string::operator==(const string_interface & str) const
{

   return get_length() == str.get_length() && operator == (string(str));

}


inline bool string::operator==(const char * psz) const
{

   return strcmp(m_pszData, psz) == 0;

}


inline bool string::operator==(const wchar_t * psz) const
{

   return operator == (string(psz));

}


inline bool string::operator==(char ch) const
{

   return get_length() == 1 && operator[](0) == ch;

}


inline bool string::operator==(wchar_t ch) const
{

   return operator==(string(ch));

}


inline bool string::operator==(int32_t i) const
{

   return strtoi(*this) == i;

}


inline bool string::operator<(const string & str) const
{

   return Compare(str) < 0;

}

inline bool string::operator<(const string_interface & str) const
{

   return operator < (string(str));

}


inline bool string::operator<(const char * psz) const
{

   return operator < (string(psz));

}


inline bool string::operator<(const wchar_t * psz) const
{

   return operator < (string(psz));

}


inline bool string::operator<(char ch) const
{

   return operator < (string(ch)) ;

}


inline bool string::operator<(wchar_t ch) const
{

   return operator < (string(ch));

}


inline bool string::operator<(int32_t i) const
{

   return strtoi(*this) < i;

}


inline bool string::operator>(const string & str) const
{

   return Compare(str) > 0 ;

}


inline bool string::operator>(const string_interface & str) const
{

   return operator > (string(str));

}


inline bool string::operator>(const char * psz) const
{

   return operator > (string(psz));

}


inline bool string::operator>(const wchar_t * psz) const
{

   return operator > (string(psz));

}


inline bool string::operator>(char ch) const
{

   return operator > (string(ch));

}


inline bool string::operator>(wchar_t ch) const
{

   return operator > (string(ch));

}


inline bool string::operator>(int32_t i) const
{

   return strtoi(*this) > i;

}





inline string::operator const char *() const throw()
{
   return simple_string::operator const char *();
}


inline const char * string::c_str() const throw()
{
   return simple_string::operator const char *();
}

inline const char * string::data() const throw()
{
   return simple_string::operator const char *();
}

inline strsize string::remove(strsize iIndex,strsize nCount)
{
   return Delete(iIndex, nCount);
}


inline bool CLASS_DECL_BASE operator==(const string_interface & str1   , const string & str2)  { return str2 == str1; }
inline bool CLASS_DECL_BASE operator==(const char *  psz                     , const string & str )  { return str  == psz ; }
inline bool CLASS_DECL_BASE operator==(const wchar_t *  psz                     , const string & str )  { return str  == psz ; }
inline bool CLASS_DECL_BASE operator==(char   ch                      , const string & str )  { return str  == ch  ; }
inline bool CLASS_DECL_BASE operator==(wchar_t   ch                      , const string & str )  { return str  == ch  ; }
inline bool CLASS_DECL_BASE operator==(int32_t i                       , const string & str )  { return str  == i   ; }

inline bool CLASS_DECL_BASE operator>(const string_interface & str1   , const string & str2 )   { return str2 < str1; }
inline bool CLASS_DECL_BASE operator>(const char * psz                      , const string & str  )   { return str  < psz ; }
inline bool CLASS_DECL_BASE operator>(const wchar_t * psz                      , const string & str  )   { return str  < psz ; }
inline bool CLASS_DECL_BASE operator>(char ch                        , const string & str  )   { return str  < ch  ; }
inline bool CLASS_DECL_BASE operator>(wchar_t ch                        , const string & str  )   { return str  < ch  ; }
inline bool CLASS_DECL_BASE operator>(int32_t i                       , const string & str  )   { return str  < i   ; }

inline bool CLASS_DECL_BASE operator<(const string_interface & str1   , const string & str2 )   { return str2 > str1; }
inline bool CLASS_DECL_BASE operator<(const char * psz                      , const string & str  )   { return str  > psz ; }
inline bool CLASS_DECL_BASE operator<(const wchar_t * psz                      , const string & str  )   { return str  > psz ; }
inline bool CLASS_DECL_BASE operator<(char ch                        , const string & str  )   { return str  > ch  ; }
inline bool CLASS_DECL_BASE operator<(wchar_t ch                        , const string & str  )   { return str  > ch  ; }
inline bool CLASS_DECL_BASE operator<(int32_t i                       , const string & str  )   { return str  > i   ; }

inline bool CLASS_DECL_BASE operator!=(const string_interface & str1,const string & str2)  { return !::operator==(str1, str2); }
inline bool CLASS_DECL_BASE operator!=(const char * psz,const string & str)                      { return !::operator==(psz, str); }
inline bool CLASS_DECL_BASE operator!=(const wchar_t * psz,const string & str)                      { return !::operator==(psz, str); }
inline bool CLASS_DECL_BASE operator!=(char ch,const string & str)                        { return !::operator==(ch, str); }
inline bool CLASS_DECL_BASE operator!=(wchar_t ch,const string & str)                        { return !::operator==(ch, str); }
inline bool CLASS_DECL_BASE operator!=(int32_t i, const string & str)                      { return !::operator==(i, str); }

inline bool CLASS_DECL_BASE operator>=(const string_interface & str1,const string & str2)  { return !::operator<(str1, str2); }
inline bool CLASS_DECL_BASE operator>=(const char * psz,const string & str)                      { return !::operator<(psz, str); }
inline bool CLASS_DECL_BASE operator>=(const wchar_t * psz,const string & str)                      { return !::operator<(psz, str); }
inline bool CLASS_DECL_BASE operator>=(char ch,const string & str)                        { return !::operator<(ch, str); }
inline bool CLASS_DECL_BASE operator>=(wchar_t ch,const string & str)                        { return !::operator<(ch, str); }
inline bool CLASS_DECL_BASE operator>=(int32_t i, const string & str)                      { return !::operator<(i, str); }

inline bool CLASS_DECL_BASE operator<=(const string_interface & str1,const string & str2)  { return !::operator>(str1, str2); }
inline bool CLASS_DECL_BASE operator<=(const char * psz,const string & str)                      { return !::operator>(psz, str); }
inline bool CLASS_DECL_BASE operator<=(const wchar_t * psz,const string & str)                      { return !::operator>(psz, str); }
inline bool CLASS_DECL_BASE operator<=(char ch,const string & str)                        { return !::operator>(ch, str); }
inline bool CLASS_DECL_BASE operator<=(wchar_t ch,const string & str)                        { return !::operator>(ch, str); }
inline bool CLASS_DECL_BASE operator<=(int32_t i, const string & str)                      { return !::operator>(i, str); }




template < >
inline string to_string(const char * psz)
{

   return string(psz);

}

template < >
inline string to_string(char * psz)
{

   return string(psz);

}

template < >
inline string to_string(unsigned char * psz)
{

   return string(psz);

}

template < >
inline string to_string(const char ch)
{

   return string((char) ch);

}

template < >
inline string to_string(const wchar_t * pwsz)
{

   return string(pwsz);

}

template < >
inline string to_string(wchar_t * pwsz)
{

   return string(pwsz);

}

template < >
inline string to_string(string_composite ca)
{

   string str;

   ca.get_string(str.GetBufferSetLength(ca.get_length()));

   str.ReleaseBuffer(ca.get_length());

   return str;

}


template < >
inline string to_string(verisimple_wstring wstr)
{

   return string((const wchar_t *) wstr);

}


#if defined(METROWIN) && defined(__cplusplus_winrt)


template < >
inline string to_string(Platform::String ^ str)
{

   return (const wchar_t *) wstring(begin(str));

}


#endif


template < >
inline string to_string(const in_addr * addr)
{

   return to_vsstring(addr);

}


template < >
inline string to_string(const in6_addr * addr)
{

   return to_vsstring(addr);

}

inline string  & operator += (string & str, const ::id & id)
{

   str += id.str();

   return str;

}


inline bool id::operator == (const char * psz) const
{
   return m_pstr == NULL ? psz == NULL : m_pstr->compare(psz) == 0;
}
inline bool id::operator != (const char * psz) const
{
   return m_pstr == NULL ? psz != NULL : m_pstr->compare(psz) != 0;
}
inline bool id::operator < (const char * psz) const
{
   return m_pstr == NULL ? psz != NULL : m_pstr->compare(psz) < 0;
}
inline bool id::operator <= (const char * psz) const
{
   return m_pstr == NULL ? true : m_pstr->compare(psz) <= 0;
}
inline bool id::operator > (const char * psz) const
{
   return m_pstr == NULL ? false : m_pstr->compare(psz) > 0;
}
inline bool id::operator >= (const char * psz) const
{
   return m_pstr == NULL ? psz == NULL : m_pstr->compare(psz) >= 0;
}


#if defined(_LP64) || defined(_AMD64_)

inline bool id::operator == (int32_t i) const
{
   return m_pstr == NULL ? i == 0 : atoi(*m_pstr) == i;
}
inline bool id::operator != (int32_t i) const
{
   return m_pstr == NULL ? i != 0 : (i == 0 ? (m_pstr->length() != 1 || m_pstr->m_pszData[0] != '0') : atoi(*m_pstr) != i);
}
inline bool id::operator < (int32_t i) const
{
   return m_pstr == NULL ? i != 0 : atoi(*m_pstr) < i;
}
inline bool id::operator <= (int32_t i) const
{
   return m_pstr == NULL ? true : atoi(*m_pstr) <= i;
}
inline bool id::operator > (int32_t i) const
{
   return m_pstr == NULL ? false : atoi(*m_pstr) > i;
}
inline bool id::operator >= (int32_t i) const
{
   return m_pstr == NULL ? i != 0 : atoi(*m_pstr) >= i;;
}

#endif


inline bool id::operator == (int_ptr i) const
{
   return m_pstr == NULL ? i == 0 : atoi(*m_pstr) == i;
}
inline bool id::operator != (int_ptr i) const
{
   return m_pstr == NULL ? i != 0 : (i == 0 ? (m_pstr->length() != 1 || m_pstr->m_pszData[0] != '0') : atoi(*m_pstr) != i);
}
inline bool id::operator < (int_ptr i) const
{
   return m_pstr == NULL ? i != 0 : atoi(*m_pstr) < i;
}
inline bool id::operator <= (int_ptr i) const
{
   return m_pstr == NULL ? true : atoi(*m_pstr) <= i;
}
inline bool id::operator > (int_ptr i) const
{
   return m_pstr == NULL ? false : atoi(*m_pstr) > i;
}
inline bool id::operator >= (int_ptr i) const
{
   return m_pstr == NULL ? i != 0 : atoi(*m_pstr) >= i;;
}


inline id::operator int64_t () const
{
   if(m_pstr == NULL)
      return 0x8000000000000000ll;
   const char * pszEnd = NULL;
   int64_t iResult = atoi_dup(*m_pstr, &pszEnd);
   if(pszEnd != NULL && pszEnd > m_pstr->c_str() && *pszEnd == '\0')
      return iResult;
   return 0x8000000000000000ll;
}

//inline id::operator int_ptr()
//{
//   if(is_number())
//      return m_i;
//   else
//      return 0;
//}

inline bool id::is_null() const
{
   return m_pstr == NULL;
}

inline bool id::has_char() const
{
   return !is_empty();
}

inline void id::Empty()
{
   m_pstr = NULL;
}

inline void id::clear()
{
   m_pstr = NULL;
}



namespace str
{

   inline CLASS_DECL_BASE bool ends_eat(string & str, const char * lpcszSuffix)
   {

      strsize iLen = strlen(lpcszSuffix);

      if(iLen > str.length())
         return false;

      if(strncmp(&str[str.length() - iLen], lpcszSuffix, iLen) != 0)
         return false;

      str.Truncate(str.length() - iLen);

      return true;

   }

} // namespace str


inline CLASS_DECL_BASE string operator + (const id & id, const char * psz)
{

   return id.to_string() + psz;

}

inline CLASS_DECL_BASE string operator + (const char * psz, const id & id)
{

   return psz + id.to_string();

}


inline CLASS_DECL_BASE string operator + (const string & str, const id & id)
{

   return str + id.to_string();

}


inline int_ptr id::compare_ci(const char * psz)
{
   if(m_pstr == NULL)
   {
      if(psz == NULL)
         return 0;
      else
         return -1;
   }
   else if(psz == NULL)
   {
      return 1;
   }
   else
   {
      return m_pstr->compare_no_case(psz);
   }
}



inline string string::lower() const
{

   return string(*this).make_lower();

}

inline string string::upper() const
{

   return string(*this).make_lower();

}

