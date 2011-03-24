#pragma once


#include "template/base.h"

#include "radix/fixed_alloc.h"


CLASS_DECL_ca string_manager_interface * AfxGetStringManager();

#if core_level_1
CLASS_DECL_ca int __cdecl _vscprintf(const char * pszFormat, va_list args );
#endif


class string;



class CLASS_DECL_ca string_interface
{
public:


   // the string returned by get_string should be valid
   // during all lifetime of an derived object of
   // string_interface
   virtual int get_length() const;

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
   virtual int get_length() const;
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


CLASS_DECL_ca int strtoi(const char * psz);

CLASS_DECL_ca int strtoi(const wchar_t * psz);


inline int _AtlGetConversionACP()
{
   return CP_UTF8;
}




#include "simple_string.h"

#ifdef _ATL_CSTRING_EXPLICIT_CONSTRUCTORS
#define CSTRING_EXPLICIT explicit
#else
#define CSTRING_EXPLICIT
#endif

#ifndef _AFX
#define _AFX_FUNCNAME(_Name) _Name
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
   static int           __cdecl  IsDigit(char ch ) throw();
   static int           __cdecl  IsSpace(char ch ) throw();
   static int           __cdecl  StringCompare(const char * pszA,const char * pszB ) throw();
   static int           __cdecl  StringCompareIgnore(const char * pszA,const char * pszB ) throw();
   static int           __cdecl  StringCollate(const char * pszA,const char * pszB ) throw();
   static int           __cdecl  StringCollateIgnore(const char * pszA,const char * pszB ) throw();
   static const char *  __cdecl  StringFindString(const char * pszBlock,const char * pszMatch ) throw();
   static char *        __cdecl  StringFindString(char * pszBlock,const char * pszMatch ) throw();
   static const char *  __cdecl  StringFindChar(const char * pszBlock,char chMatch ) throw();
   static const char *  __cdecl  StringFindCharRev(const char * psz,char ch, int iStart ) throw();
   static const char *  __cdecl  StringFindStrRev(const char * psz,const char * pszFind, int iStart ) throw();
   static const char *  __cdecl  StringScanSet(const char * pszBlock,const char * pszMatch ) throw();
   static int           __cdecl  StringSpanIncluding(const char * pszBlock,const char * pszSet ) throw();
   static int           __cdecl  StringSpanExcluding(const char * pszBlock,const char * pszSet ) throw();
   static char *        __cdecl  StringUppercase( char * psz ) throw();
   static char *        __cdecl  StringLowercase( char * psz ) throw();
   static char *        __cdecl  StringUppercase(char * psz,size_t size ) throw();
   static char *        __cdecl  StringLowercase(char * psz,size_t size ) throw();
   static char *        __cdecl  StringReverse( char * psz ) throw();
   static int           __cdecl  GetFormattedLength(const char * pszFormat, va_list args ) throw();
   static int           __cdecl  Format(char * pszBuffer,const char * pszFormat, va_list args ) throw();
#if _SECURE_ATL
   static int           __cdecl  Format(char * pszBuffer,size_t nlength,const char * pszFormat, va_list args ) throw();
#endif
   static int           __cdecl  GetcharLength(const char * pszSrc ) throw();
   static int           __cdecl  GetcharLength(const char * pszSrc, int nLength ) throw();
   static int           __cdecl  GetcharLength(const wchar_t * pszSource ) throw();
   static int           __cdecl  GetcharLength(const wchar_t * pszSource, int nLength ) throw();
   static void          __cdecl  ConvertTochar(char * pszDest,int nDestLength, const char * pszSrc, int nSrcLength = -1 ) throw();
   static void          __cdecl  ConvertTochar(char * pszDest,int nDestLength, const wchar_t * pszSrc,int nSrcLength = -1) throw();
   static void                   ConvertToOem(char* pstrString) throw();
   static void                   ConvertToAnsi(char* pstrString) throw();
   static void                   ConvertToOem(char* pstrString,size_t size);
   static void                   ConvertToAnsi(char* pstrString,size_t size);
   static void          __cdecl  FloodCharacters(char ch,int nLength, char* pch ) throw();
   static BSTR          __cdecl  AllocSysString( const char* pchData, int nDataLength ) throw();
   static BOOL          __cdecl  ReAllocSysString( const char* pchData,BSTR* pbstr,int nDataLength ) throw();
   static DWORD         __cdecl  FormatMessage(DWORD dwFlags, LPCVOID pSource, DWORD dwMessageID,DWORD dwLanguageID, char * pszBuffer, DWORD nSize, va_list* pArguments ) throw();
   static DWORD         __cdecl  format_message(DWORD dwFlags, LPCVOID pSource, DWORD dwMessageID,DWORD dwLanguageID, char * pszBuffer, DWORD nSize, va_list* pArguments ) throw();
   static int           __cdecl  SafeStringLen( const char * psz ) throw();
   static int           __cdecl  SafeStringLen( const wchar_t * psz ) throw();
   static int           __cdecl  GetCharLen(const wchar_t* pch ) throw();
   static int           __cdecl  GetCharLen(const char* pch ) throw();
   static DWORD         __cdecl  GetEnvironmentVariable(const char * pszVar, char * pszBuffer,DWORD dwSize ) throw();

};
























class string_trait :
   public crt_char_traits // iterator
{
public:

   CLASS_DECL_ca static string_manager_interface * GetDefaultManager() throw()
   {
      static string_manager_interface * s_pdefaultManager = AfxGetStringManager();
      return s_pdefaultManager;
   }

};


class string_manager :
   public string_manager_interface
{
public:
   string_manager();

public:
   virtual string_data * allocate( int nChars, int nCharSize );
   virtual void Free( string_data * pData );
   virtual string_data * Reallocate( string_data * pData, int nChars, int nCharSize );
   virtual string_data * GetNilString() ;
   virtual string_manager_interface * Clone() ;

protected:
   fixed_alloc_array m_alloca;

   nil_string_data  m_nil;
};



class CLASS_DECL_ca string :
   public simple_string
{
public:

   operator class string_composite ();
   operator class string_composite const () const;
   operator PCXSTR() const throw();
   void construct() throw();
   string() throw();
   explicit string( string_manager_interface * pstringmanager ) throw();
   static void __cdecl Construct( string* pstring );
   string(const string & strSrc );
   operator simple_string&();
   string(const XCHAR* pszSrc);
   string(const char * pszSrc,string_manager_interface * pstringmanager );
   CSTRING_EXPLICIT string(const YCHAR* pszSrc );
   CSTRING_EXPLICIT string( const string_interface & str );
   string(const wchar_t * pszSrc,string_manager_interface * pstringmanager );

   CSTRING_EXPLICIT string( const unsigned char* pszSrc );
//ctors to prevent from oldSyntax template ctor (above) hijack certain types.
//ca2 API dll instantiate all string methods inside the dll and declares dllimport for
//all methods in ::fontopus::user build (see afxstr.h), so need to include the methods in ca2 API dll builds.
#if defined(_ApplicationFrameworkDLL) && defined(_MFC_DLL_BLD) || !defined(__cplusplus_cli) && defined(_MANAGED)

   /*CSTRING_EXPLICIT*/ string(char* pszSrc );
   CSTRING_EXPLICIT string(unsigned char* pszSrc );
   CSTRING_EXPLICIT string(wchar_t* pszSrc );
#endif

   string(const unsigned char* pszSrc,string_manager_interface * pstringmanager );
   CSTRING_EXPLICIT string(char ch,int nLength = 1 );
   string(wchar_t ch,int nLength = 1 );
   string(const XCHAR* pch,int nLength );
   string(const XCHAR* pch,int nLength,string_manager_interface * pstringmanager );
   string(const YCHAR* pch,int nLength );
   string(const YCHAR* pch,int nLength,string_manager_interface * pstringmanager );
   ~string() throw();

   

   // Assignment operators
   string& operator=(const string_interface & str );
   string& operator=(string strSrc );
   template <bool bMFCDLL>
   string& operator=(const simple_string& strSrc );
   string& operator=(PCXSTR pszSrc );
   string& operator=(PCYSTR pszSrc );
   string& operator=(const unsigned char* pszSrc );
   string& operator=(char ch );
   string& operator=(wchar_t ch );
   string& operator+=(const simple_string& str );
   string& operator+=(PCXSTR pszSrc );
   template< int t_nSize >
   string& operator+=(const static_string<t_nSize >& strSrc );
   string& operator+=(PCYSTR pszSrc );
   string& operator+=(char ch );
   string& operator+=(unsigned char ch );
   string& operator+=(wchar_t ch );

   // Override from base class
   string_manager_interface * GetManager() const throw();

   // Comparison
   int Compare(PCXSTR psz ) const;
   int CompareNoCase(PCXSTR psz ) const throw();
   int Collate(PCXSTR psz ) const throw();
   int CollateNoCase(PCXSTR psz ) const throw();

   // Advanced manipulation

   // Delete 'nCount' characters, starting at index 'iIndex'
   int Delete(int iIndex,int nCount = 1 );

   // Insert character 'ch' before index 'iIndex'
   int Insert(int iIndex,XCHAR ch );

   // Insert string 'psz' before index 'iIndex'
   int Insert(int iIndex,PCXSTR psz );

   // replace all occurrences of character 'chOld' with character 'chNew'
   int replace(XCHAR chOld,XCHAR chNew );

   // replace all occurrences of string 'pszOld' with string 'pszNew'
   int replace(PCXSTR pszOld,PCXSTR pszNew );

   // remove all occurrences of character 'chRemove'
   int remove(XCHAR chRemove );

   string Tokenize(PCXSTR pszTokens, int& iStart ) const;
   // find routines

   // find the first occurrence of character 'ch', starting at index 'iStart'
   int find(XCHAR ch,int iStart = 0 ) const throw();

   // look for a specific sub-string

   // find the first occurrence of string 'pszSub', starting at index 'iStart'
   int find(PCXSTR pszSub,int iStart = 0 ) const throw();

   // find the first occurrence of any of the characters in string 'pszCharSet'
   int FindOneOf(PCXSTR pszCharSet ) const throw();

   // find the last occurrence of character 'ch'
   int reverse_find(XCHAR ch, int iStart = -1 ) const throw();

   // find the last occurrence of character 'ch'
   int reverse_find( PCXSTR ch, int iStart = -1 ) const throw();

   // manipulation

   // Convert the string to uppercase
   string& make_upper();

   // Convert the string to lowercase
   string& make_lower();

   // Reverse the string
   string& MakeReverse();

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

   // Convert the string to the OEM character set
   void AnsiToOem();

   // Convert the string to the ANSI character set
   void OemToAnsi();

   // Very simple sub-string extraction

   // Return the substring starting at index 'iFirst'
   string Mid(int iFirst ) const;

   string substr(int iFirst) const;

   // Return the substring starting at index 'iFirst', with length 'nCount'
   string Mid(int iFirst,int nCount ) const;

   string substr(int iFirst, int nCount) const;

   void clear();

   // Return the substring consisting of the rightmost 'nCount' characters
   string Right(int nCount ) const;

   // Return the substring consisting of the leftmost 'nCount' characters
   string Left(int nCount ) const;

   // Return the substring consisting of the leftmost characters in the set 'pszCharSet'
   string SpanIncluding(PCXSTR pszCharSet ) const;

   // Return the substring consisting of the leftmost characters not in the set 'pszCharSet'
   string SpanExcluding(PCXSTR pszCharSet ) const;

   // Format data using format string 'pszFormat'
   void __cdecl Format(PCXSTR pszFormat, ... );

   // append formatted data using format string 'pszFormat'
   void __cdecl AppendFormat(PCXSTR pszFormat, ... );

   void AppendFormatV(PCXSTR pszFormat, va_list args );

   void FormatV(PCXSTR pszFormat, va_list args );

   void __cdecl FormatMessage(PCXSTR pszFormat, ... );

   void __cdecl format_message(PCXSTR pszFormat, ... );

   // Format a message using format string 'pszFormat' and va_list
   void FormatMessageV(PCXSTR pszFormat, va_list* pArgList );

   // OLE BSTR support

   // allocate a BSTR containing a copy of the string
   BSTR AllocSysString() const;

   BSTR SetSysString(BSTR* pbstr ) const;

   // Set the string to the value of environment var 'pszVar'
   BOOL GetEnvironmentVariable(PCXSTR pszVar );

   // Load the string from resource 'nID'
   //BOOL load_string(id id);

   // Load the string from resource 'nID' in module 'hInstance'
/*    BOOL load_string(HINSTANCE hInstance,UINT nID )
   {
      const ATLSTRINGRESOURCEIMAGE* pImage = AtlGetStringResourceImage( hInstance, nID );
      if( pImage == NULL )
      {
         return( FALSE );
      }

      int nLength = str_traits::GetcharLength( pImage->achString, pImage->nLength );
      PXSTR pszBuffer = GetBuffer( nLength );
      str_traits::ConvertTochar( pszBuffer, nLength, pImage->achString, pImage->nLength );
      ReleaseBufferSetLength( nLength );

      return( TRUE );
   }*/

   // Load the string from resource 'nID' in module 'hInstance', using language 'wLanguageID'
    /*BOOL load_string(HINSTANCE hInstance,UINT nID,WORD wLanguageID )
   {
      const ATLSTRINGRESOURCEIMAGE* pImage = AtlGetStringResourceImage( hInstance, nID, wLanguageID );
      if( pImage == NULL )
      {
         return( FALSE );
      }

      int nLength = str_traits::GetcharLength( pImage->achString, pImage->nLength );
      PXSTR pszBuffer = GetBuffer( nLength );
      str_traits::ConvertTochar( pszBuffer, nLength, pImage->achString, pImage->nLength );
      ReleaseBufferSetLength( nLength );

      return( TRUE );
   }*/

   friend string CLASS_DECL_ca operator+(string str1,string str2 );
   friend string CLASS_DECL_ca operator+(string str1,PCXSTR psz2 );
   friend string CLASS_DECL_ca operator+(PCXSTR psz1,string str2 );
   friend string CLASS_DECL_ca operator+(string str1,wchar_t ch2 );
   friend string CLASS_DECL_ca operator+(string str1,char ch2 );
   friend string CLASS_DECL_ca operator+(wchar_t ch1,string str2 );
   friend string CLASS_DECL_ca operator+(char ch1,string str2 );
   friend bool CLASS_DECL_ca operator==(string str1,const string_interface & str2 );
   friend bool CLASS_DECL_ca operator==(const string_interface & str1,string str2 );
   friend bool CLASS_DECL_ca operator==(string str1,string str2 ) throw();
   friend bool CLASS_DECL_ca operator==(string str1,PCXSTR psz2 ) throw();
   friend bool CLASS_DECL_ca operator==(PCXSTR psz1,string str2 ) throw();
   friend bool CLASS_DECL_ca operator==(string str1,PCYSTR psz2 ) THROWS;
   friend bool CLASS_DECL_ca operator==(PCYSTR psz1,string str2 ) THROWS;
   friend bool CLASS_DECL_ca operator==(string str1, int i);
   friend bool CLASS_DECL_ca operator==(int i, string str1);
   friend bool CLASS_DECL_ca operator!=(string str1,string str2 ) throw();
   friend bool CLASS_DECL_ca operator!=(string str1,PCXSTR psz2 ) throw();
   friend bool CLASS_DECL_ca operator!=(PCXSTR psz1,string str2 ) throw();
   friend bool CLASS_DECL_ca operator!=(string str1,PCYSTR psz2 ) THROWS;
   friend bool CLASS_DECL_ca operator!=(PCYSTR psz1,string str2 ) THROWS;
   friend bool CLASS_DECL_ca operator!=(string str1, int i);
   friend bool CLASS_DECL_ca operator!=(int i, string str1);
   friend bool CLASS_DECL_ca operator<(string str1,string str2 ) throw();
   friend bool CLASS_DECL_ca operator<(string str1,PCXSTR psz2 ) throw();
   friend bool CLASS_DECL_ca operator<(PCXSTR psz1,string str2 ) throw();
   friend bool CLASS_DECL_ca operator<(string str1, int i);
   friend bool CLASS_DECL_ca operator<(int i, string str1);
   friend bool CLASS_DECL_ca operator>(string str1,string str2 ) throw();
   friend bool CLASS_DECL_ca operator>(string str1,PCXSTR psz2 ) throw();
   friend bool CLASS_DECL_ca operator>(PCXSTR psz1,string str2 ) throw();
   friend bool CLASS_DECL_ca operator>(string str1, int i);
   friend bool CLASS_DECL_ca operator>(int i, string str1);
   friend bool CLASS_DECL_ca operator<=(string str1,string str2 ) throw();
   friend bool CLASS_DECL_ca operator<=(string str1,PCXSTR psz2 ) throw();
   friend bool CLASS_DECL_ca operator<=(PCXSTR psz1,string str2 ) throw();
   friend bool CLASS_DECL_ca operator<=(string str1, int i);
   friend bool CLASS_DECL_ca operator<=(int i, string str1);
   friend bool CLASS_DECL_ca operator>=(string str1,string str2 ) throw();
   friend bool CLASS_DECL_ca operator>=(string str1,PCXSTR psz2 ) throw();
   friend bool CLASS_DECL_ca operator>=(PCXSTR psz1,string str2 ) throw();
   friend bool CLASS_DECL_ca operator>=(string str1, int i);
   friend bool CLASS_DECL_ca operator>=(int i, string str1);
   friend bool CLASS_DECL_ca operator==(XCHAR ch1,string str2 ) throw();
   friend bool CLASS_DECL_ca operator==(string str1,XCHAR ch2 ) throw();
   friend bool CLASS_DECL_ca operator!=(XCHAR ch1,string str2 ) throw();
   friend bool CLASS_DECL_ca operator!=(string str1,XCHAR ch2 ) throw();


};


template< int t_nSize >
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

inline int string_composite::get_length() const 
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
   int get_length() const;
   void get_string(char * pszstr) const;
   void set_string(const char * psz);
};


#include "fixed_string.h"

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
#include "collection/bit_array.h"

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
