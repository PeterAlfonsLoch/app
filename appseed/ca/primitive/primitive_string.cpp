#include "framework.h"


strsize string_interface::get_length() const
{
   return 0;
}

void string_interface::get_string(char * psz) const
{
   *psz = '\0';
}

void string_interface::set_string(const char * psz)
{
   UNREFERENCED_PARAMETER(psz);
}

string_interface & string_interface::operator = (const string_interface & str)
{
   if(&str == this)
      return *this;
   char sz[256];
   strsize iLen = str.get_length();
   if(iLen < ((sizeof(sz) / sizeof(char)) - sizeof(char)))
   {
      str.get_string(sz);
      set_string(sz);
   }
   else
   {
      char * psz = new char[iLen + 1];
      str.get_string(psz);
      set_string(psz);
      delete [] psz;
   }
   return *this;
}

string_interface & string_interface::operator = (const char * psz)
{
   set_string(psz);
   return *this;
}


void string_composite::set_string(const string * pstr) const
{
   string_composite * pThis = const_cast < string_composite * > (this);
   pThis->m_pstring = const_cast < string *  > (pstr);
   pThis->m_pinterface = NULL;
}

string_composite & string_composite::operator = (const string & str)
{
   *m_pstring = str;
   m_pinterface = NULL;
   return *this;
}



string::string(wchar_t ch,strsize nLength) :
   simple_string( string_trait::GetDefaultManager() )
{
   ASSERT( nLength >= 0 );
   if( nLength > 0 )
   {
      //Convert ch to the char
      wchar_t pszCh[2] = { ch , 0 };
      strsize ncharCharLen = 1;

      if(ch != L'\0')
      {
         ncharCharLen = string_trait::GetcharLength(pszCh);
      }

      primitive::memory buffcharChar;
      buffcharChar.allocate(ncharCharLen+1);
      string_trait::ConvertTochar( (XCHAR*)buffcharChar.get_data(), ncharCharLen+1, pszCh, 1 );
      //allocate enough characters in string and flood (replicate) with the (converted character)*nLength
      PXSTR pszBuffer = GetBuffer( nLength*ncharCharLen );
      if (ncharCharLen == 1)
      {
         //Optimization for a common case - wide char translates to 1 ansi/wide char.
         string_trait::FloodCharacters( ((const char *)buffcharChar)[0], nLength, pszBuffer );

      } else
      {
         XCHAR* p=pszBuffer;
         for (strsize i=0 ; i < nLength ;++i)
         {
            for (strsize j=0 ; j < ncharCharLen ;++j)
            {
               *p = ((char *)buffcharChar)[j];
               ++p;
            }
         }
      }
      ReleaseBufferSetLength( nLength*ncharCharLen );
   }
}

string::string(const YCHAR* pch,strsize nLength ) :
   simple_string( string_trait::GetDefaultManager() )
{
   ASSERT( nLength >= 0 );
   if( nLength > 0 )
   {
      ASSERT(__is_valid_address( pch, nLength*sizeof( YCHAR ), FALSE ) );
      if(pch == NULL)
         throw invalid_argument_exception();

      strsize nDestLength = string_trait::GetcharLength( pch, nLength );
      PXSTR pszBuffer = GetBuffer( nDestLength );
      string_trait::ConvertTochar( pszBuffer, nDestLength, pch, nLength );
      ReleaseBufferSetLength( nDestLength );
   }
}

string::string(const YCHAR* pch,strsize nLength,string_manager * pstringmanager ) :
   simple_string( pstringmanager )
{
   ASSERT( nLength >= 0 );
   if( nLength > 0 )
   {
      ASSERT( __is_valid_address( pch, nLength*sizeof( YCHAR ), FALSE ) );
      if(pch == NULL)
         throw invalid_argument_exception();

      strsize nDestLength = string_trait::GetcharLength( pch, nLength );
      PXSTR pszBuffer = GetBuffer( nDestLength );
      string_trait::ConvertTochar( pszBuffer, nDestLength, pch, nLength );
      ReleaseBufferSetLength( nDestLength );
   }
}


/*

void fixed_string_log::OnAllocateSpill(strsize nActualChars,strsize nFixedChars,const string_data* pData ) throw()
{
()nActualChars;
()nFixedChars;
()pData;
//   TRACE(gen::trace::category_String, 0, _T( "fixed_string_manager::allocate() spilling to heap.  %d chars (fixed size = %d chars)\n" ), nActualChars, nFixedChars );
::OutputDebugStringA("fixed_string_log::OnAllocateSpill");
}

void fixed_string_log::OnReallocateSpill(strsize nActualChars,strsize nFixedChars,const string_data* pData ) throw()
{
()nActualChars;
()nFixedChars;
()pData;
//   TRACE(gen::trace::category_String, 0, _T( "fixed_string_manager::Reallocate() spilling to heap.  %d chars (fixed size = %d chars)\n" ), nActualChars, nFixedChars );
::OutputDebugStringA("fixed_string_log::OnReallocateSpill");
}

*/


char* __cdecl crt_char_traits::CharNext(const char* p ) throw()
{
   return const_cast< char* >( gen::str::utf8_inc(p) );
}



int __cdecl crt_char_traits::IsDigit(const char * pch ) throw()
{
   return gen::ch::is_digit(pch) ? 1 : 0;
}

int __cdecl crt_char_traits::IsSpace(const char * pch ) throw()
{
   return gen::ch::is_whitespace( pch ) ? 1 : 0;
}



int __cdecl crt_char_traits::StringCollate(const char * pszA,const char * pszB ) throw()
{
   return strcmp( reinterpret_cast< const  char* >( pszA ), reinterpret_cast< const  char* >( pszB ) );
}

int __cdecl crt_char_traits::StringCollateIgnore(const char * pszA,const char * pszB ) throw()
{
   return _stricmp( reinterpret_cast< const  char* >( pszA ), reinterpret_cast< const  char* >( pszB ) );
}

const char * __cdecl crt_char_traits::StringFindString(const char * pszBlock,const char * pszMatch ) throw()
{
   return reinterpret_cast< const char * >( strstr( reinterpret_cast< const  char* >( pszBlock ),
      reinterpret_cast< const  char* >( pszMatch ) ) );
}

char * __cdecl crt_char_traits::StringFindString(char * pszBlock,const char * pszMatch ) throw()
{
   return( const_cast< char * >( StringFindString( const_cast< const char * >( pszBlock ), pszMatch ) ) );
}

const char * __cdecl crt_char_traits::StringFindChar(const char * pszBlock,char chMatch ) throw()
{
   return reinterpret_cast< const char * >( strchr( reinterpret_cast< const  char* >( pszBlock ), ( char)chMatch ) );
}

/*
strsize __cdecl crt_char_traits::StringCompare(const char * pszA,const char * pszB ) throw()
{
return _mbscmp( reinterpret_cast< const unsigned char* >( pszA ), reinterpret_cast< const unsigned char* >( pszB ) );
}

strsize __cdecl crt_char_traits::StringCompareIgnore(const char * pszA,const char * pszB ) throw()
{
return _mbsicmp( reinterpret_cast< const unsigned char* >( pszA ), reinterpret_cast< const unsigned char* >( pszB ) );
}

strsize __cdecl crt_char_traits::StringCollate(const char * pszA,const char * pszB ) throw()
{
return _mbscoll( reinterpret_cast< const unsigned char* >( pszA ), reinterpret_cast< const unsigned char* >( pszB ) );
}

strsize __cdecl crt_char_traits::StringCollateIgnore(const char * pszA,const char * pszB ) throw()
{
return _mbsicoll( reinterpret_cast< const unsigned char* >( pszA ), reinterpret_cast< const unsigned char* >( pszB ) );
}

const char * __cdecl crt_char_traits::StringFindString(const char * pszBlock,const char * pszMatch ) throw()
{
return reinterpret_cast< const char * >( _mbsstr( reinterpret_cast< const unsigned char* >( pszBlock ),
reinterpret_cast< const unsigned char* >( pszMatch ) ) );
}

char * __cdecl crt_char_traits::StringFindString(char * pszBlock,const char * pszMatch ) throw()
{
return( const_cast< char * >( StringFindString( const_cast< const char * >( pszBlock ), pszMatch ) ) );
}

const char * __cdecl crt_char_traits::StringFindChar(const char * pszBlock,char chMatch ) throw()
{
return reinterpret_cast< const char * >( _mbschr( reinterpret_cast< const unsigned char* >( pszBlock ), (unsigned char)chMatch ) );
}
*/
const char * __cdecl crt_char_traits::StringFindCharRev(const char * psz,char ch, strsize iStart ) throw()
{
   if(iStart < 0)
      iStart = (strsize)(strlen(psz) + iStart);
   if(iStart < 0)
      return NULL;
   while(iStart >= 0)
   {
      if(psz[iStart] == ch)
         return &psz[iStart];
      iStart--;
   }
   return NULL;
   //      return reinterpret_cast< const char * >( _mbsrchr( reinterpret_cast< const unsigned char* >( &psz[iStart] ), (unsigned char)ch ) );
}


const char * __cdecl crt_char_traits::StringFindStrRev(const char * psz,const char * pszFind, strsize iStart ) throw()
{
   strsize iLen = strsize(strlen(psz));
   strsize iLenFind = strsize(strlen(pszFind));
   if(iStart < 0 )
      iStart = iLen + iStart;
   if(iLenFind > iLen)
      return NULL;
   iStart = min(iStart, iLen - iLenFind);
   while(iStart >= 0)
   {
      if(strncmp(&psz[iStart], pszFind, iLenFind) == 0)
         return &psz[iStart];
      iStart--;
   }
   return NULL;
}


const char * __cdecl crt_char_traits::StringScanSet(const char * pszBlock,const char * pszMatch ) throw()
{
   if(pszMatch == NULL || pszBlock == NULL || *pszBlock == '\0')
      return NULL;
   while(*pszMatch != '\0')
   {
      string strUtf8Char = gen::str::utf8_char(pszMatch);
      const char * psz = strstr(pszBlock, strUtf8Char);
      if(psz != NULL)
         return psz;
      pszMatch = gen::str::utf8_inc(pszMatch);
   }
   return NULL;
   //return reinterpret_cast< const char * >( _mbspbrk( reinterpret_cast< const unsigned char* >( pszBlock ),
   // reinterpret_cast< const unsigned char* >( pszMatch ) ) );
}

strsize __cdecl crt_char_traits::StringSpanIncluding(const char * pszBlock,const char * pszSet ) throw()
{
   if(pszSet == NULL || pszBlock == NULL)
      return 0;
   const char * psz = pszBlock;
   const char * pszLast = NULL;
   while((psz == StringScanSet(psz, pszSet)) != NULL)
   {
      pszLast = psz;
      psz++;
   }
   if(pszLast == NULL)
      return 0;
   else
      return pszBlock - pszLast + gen::str::utf8_char(pszLast).get_length();
   //return (strsize)_mbsspn( reinterpret_cast< const unsigned char* >( pszBlock ), reinterpret_cast< const unsigned char* >( pszSet ) );
}

strsize __cdecl crt_char_traits::StringSpanExcluding(const char * pszBlock,const char * pszSet ) throw()
{
   //   return (strsize)_mbscspn( reinterpret_cast< const unsigned char* >( pszBlock ), reinterpret_cast< const unsigned char* >( pszSet ) );
   if(pszSet == NULL || pszBlock == NULL)
      return 0;
   const char * psz = StringScanSet(pszBlock, pszSet);
   if(psz == NULL)
      return strlen(pszBlock);
   else
      return psz - pszBlock;

}

_INSECURE_DEPRECATE("You must pass an output size to crt_char_traits::StringUppercase")
   char * __cdecl crt_char_traits::StringUppercase( char * psz ) throw()
{
#pragma warning (push)
#pragma warning(disable : 4996)
   if(psz == NULL)
      return NULL;
   char * p = psz;
   string strFinal;
   while(*p)
   {
      strFinal += gen::ch::to_upper_case(p);
      p = (char *) gen::str::utf8_inc(p);
   }
   strcpy(p, strFinal);
   return psz;


   //   return reinterpret_cast< char * >(( reinterpret_cast< unsigned char* >( psz ) ) );
#pragma warning (pop)
}

_INSECURE_DEPRECATE("You must pass an output size to crt_char_traits::StringLowercase")
   char * __cdecl crt_char_traits::StringLowercase( char * psz ) throw()
{
#pragma warning (push)
#pragma warning(disable : 4996)
   if(psz == NULL)
      return NULL;
   char * p = psz;
   string strFinal;
   while(*p)
   {
      strFinal += gen::ch::to_lower_case(p);
      p = (char *) gen::str::utf8_inc(p);
   }
   strcpy(p, strFinal);
   return psz;

   //   return reinterpret_cast< char * >( _mbslwr( reinterpret_cast< unsigned char* >( psz ) ) );
#pragma warning (pop)
}

char * __cdecl crt_char_traits::StringUppercase(char * psz,size_t size ) throw()
{
   
   ::gen::strupr_s(psz, size);

   return psz;
   
}

char * __cdecl crt_char_traits::StringLowercase(char * psz,size_t size ) throw()
{

   ::gen::strlwr_s(psz, size);

   return psz;
   
}

char * __cdecl crt_char_traits::StringReverse( char * psz ) throw()
{
   if(psz == NULL)
      return NULL;
   string strRev;
   char * p = psz + strlen(psz);
   while((p = (char*) gen::str::utf8_dec(psz, p))!= NULL)
   {
      strRev += gen::str::utf8_char(p);
   }
   strcpy(psz, strRev);
   return psz;
   //return reinterpret_cast< char * >( _mbsrev( reinterpret_cast< unsigned char* >( psz ) ) );
}

#ifdef WINDOWS

strsize __cdecl crt_char_traits::GetFormattedLength(const char * pszFormat, va_list args ) throw()
{
   return _vscprintf( pszFormat, args );
}

#endif


strsize __cdecl crt_char_traits::Format(char * pszBuffer,const char * pszFormat, va_list args ) throw()
{
   return vsprintf( pszBuffer, pszFormat, args );

}

#if _SECURE_TEMPLATE
strsize __cdecl crt_char_traits::Format(char * pszBuffer,size_t nlength,const char * pszFormat, va_list args ) throw()
{
   return vsprintf_s( pszBuffer, nlength, pszFormat, args );
}
#endif

strsize __cdecl crt_char_traits::GetcharLength(const char * pszSrc ) throw()
{
   // Returns required buffer length in XCHARs
   return strsize( strlen( pszSrc ) );
}

strsize __cdecl crt_char_traits::GetcharLength(const char * pszSrc, strsize nLength ) throw()
{
   (void)pszSrc;
   // Returns required buffer length in XCHARs
   return nLength;
}

strsize __cdecl crt_char_traits::GetcharLength(const wchar_t * pszSource ) throw()
{
   // Returns required buffer length in XCHARs
   return ::WideCharToMultiByte( _gen_GetConversionACP(), 0, pszSource, -1, NULL, 0, NULL, NULL )-1;
}

strsize __cdecl crt_char_traits::GetcharLength(const wchar_t * pszSource, strsize nLength ) throw()
{
   // Returns required buffer length in XCHARs
   return ::WideCharToMultiByte( _gen_GetConversionACP(), 0, pszSource, (int) nLength, NULL, 0, NULL, NULL );
}

void __cdecl crt_char_traits::ConvertTochar(char * pszDest,strsize nDestLength, const char * pszSrc, strsize nSrcLength) throw()
{
   if (nSrcLength == -1) { nSrcLength=1 + GetcharLength(pszSrc); }
   // nLen is in XCHARs
   ::gen::memcpy_s( pszDest, nDestLength*sizeof( char ),
      pszSrc, nSrcLength*sizeof( char ) );
}

void __cdecl crt_char_traits::ConvertTochar(char * pszDest,strsize nDestLength, const wchar_t * pszSrc,strsize nSrcLength) throw()
{
   // nLen is in XCHARs
   ::WideCharToMultiByte( _gen_GetConversionACP(), 0, pszSrc, (int) nSrcLength, pszDest, (int) nDestLength, NULL, NULL );
}

void crt_char_traits::ConvertToOem(char* pstrString) RELEASENOTHROW
{
   bool fSuccess=::CharToOemA(pstrString, pstrString) != 0;
   // old version can't report error
   ASSERT(fSuccess);
}

void crt_char_traits::ConvertToAnsi(char* pstrString) RELEASENOTHROW
{
   bool fSuccess=::OemToCharA(pstrString, pstrString) != 0;
   // old version can't report error
   ASSERT(fSuccess);
}

void __cdecl crt_char_traits::FloodCharacters(char ch,strsize nLength, char* pch ) throw()
{
   // nLength is in XCHARs
   memset( pch, ch, nLength );
}

BSTR __cdecl crt_char_traits::AllocSysString( const char* pchData, strsize nDataLength ) throw()
{

   strsize nLen = ::MultiByteToWideChar( _gen_GetConversionACP(), 0, pchData, (int) nDataLength, NULL, NULL );

   BSTR bstr = ::SysAllocStringLen( NULL, (UINT) nLen );

   if( bstr != NULL )
   {
      ::MultiByteToWideChar( _gen_GetConversionACP(), 0, pchData, (int) nDataLength, bstr, (int) nLen);
   }

   return bstr;

}

bool __cdecl crt_char_traits::ReAllocSysString( const char* pchData,BSTR* pbstr,strsize nDataLength ) throw()
{

   strsize nLen = ::MultiByteToWideChar( _gen_GetConversionACP(), 0, pchData, (int) nDataLength, NULL, NULL );

   bool bSuccess = ::SysReAllocStringLen( pbstr, NULL, (UINT) nLen ) != 0;

   if( bSuccess )
   {
      ::MultiByteToWideChar( _gen_GetConversionACP(), 0, pchData, (int) nDataLength, *pbstr, (int) nLen );
   }

   return bSuccess;

}

DWORD __cdecl crt_char_traits::FormatMessage(DWORD dwFlags, LPCVOID pSource,
                                             DWORD dwMessageID,DWORD dwLanguageID, char * pszBuffer,
                                             DWORD nSize, va_list* pArguments ) throw()
{
   return ::FormatMessageA( dwFlags, pSource, dwMessageID, dwLanguageID,
      pszBuffer, nSize, pArguments );
}

DWORD __cdecl crt_char_traits::format_message(DWORD dwFlags, LPCVOID pSource,
                                              DWORD dwMessageID,DWORD dwLanguageID, char * pszBuffer,
                                              DWORD nSize, va_list* pArguments ) throw()
{
   return FormatMessage(dwFlags, pSource, dwMessageID, dwLanguageID, pszBuffer, nSize, pArguments);
}

strsize __cdecl crt_char_traits::SafeStringLen( const char * psz ) throw()
{
   // returns length in bytes
   return (psz != NULL) ? strsize( strlen( psz ) ) : 0;
}

strsize __cdecl crt_char_traits::SafeStringLen( const wchar_t * psz ) throw()
{
   // returns length in wchar_ts
   return (psz != NULL) ? strsize( wcslen( psz ) ) : 0;
}

strsize __cdecl crt_char_traits::GetCharLen(const wchar_t* pch ) throw()
{
   (void)pch;
   // returns char length
   return 1;
}

strsize __cdecl crt_char_traits::GetCharLen(const char* pch ) throw()
{
   // returns char length
   return  gen::str::utf8_char(pch).get_length();
}

DWORD __cdecl crt_char_traits::GetEnvironmentVariable(const char * pszVar,
                                                      char * pszBuffer,DWORD dwSize ) throw()
{
   return ::GetEnvironmentVariableA( pszVar, pszBuffer, dwSize );
}

void crt_char_traits::ConvertToAnsi(char* pstrString,size_t size)
{
   if(size>UINT_MAX)
   {
      // API only allows DWORD size
      throw invalid_argument_exception();
   }
   DWORD dwSize=static_cast<DWORD>(size);
   bool fSuccess=::OemToCharBuffA(pstrString, pstrString, dwSize) != 0;
   if(!fSuccess)
   {
      throw last_error_exception();
   }
}
void crt_char_traits::ConvertToOem(char* pstrString,size_t size)
{
   if(size>UINT_MAX)
   {
      // API only allows DWORD size
      throw invalid_argument_exception();
   }
   DWORD dwSize=static_cast<DWORD>(size);
   bool fSuccess=::CharToOemBuffA(pstrString, pstrString, dwSize) != 0;
   if(!fSuccess)
   {
      throw last_error_exception();
   }
}






string::operator class string_composite ()
{
   class string_composite composite;
   composite.set_string(*this);
   return composite;
}

string::operator class string_composite const () const
{
   class string_composite composite;
   composite.set_string(this);
   return composite;
}


void string::construct() throw()
{
   simple_string::construct( string_trait::GetDefaultManager());
}


string::string( string_manager * pstringmanager ) throw() :
   simple_string( pstringmanager )
{
}

#undef new
void __cdecl string::Construct(class string * pstring)
{
   new (pstring) class string;
}
#define new DEBUG_NEW

// copy constructor
string::string(const string & strSrc ) :
   simple_string( strSrc, string_trait::GetDefaultManager() )
{
}

string::string(const XCHAR* pszSrc ) :
   simple_string( string_trait::GetDefaultManager() )
{
   //      if( !CheckImplicitLoad( pszSrc ) )
   //      {
   // nDestLength is in XCHARs
   *this = pszSrc;
   //      }
}

string::string(const char * pszSrc,string_manager * pstringmanager ) :
   simple_string( pstringmanager )
{
   //      if( !CheckImplicitLoad( pszSrc ) )
   //      {
   // nDestLength is in XCHARs
   *this = pszSrc;
   //      }
}

string::string(const YCHAR* pszSrc ) :
   simple_string( string_trait::GetDefaultManager() )
{
   //      if( !CheckImplicitLoad( pszSrc ) )
   //      {
   *this = pszSrc;
   //      }
}


string::string(const vsstring & str ) :
   simple_string( string_trait::GetDefaultManager() )
{

   *this = str.m_psz;

}


string::string(const id & id ) :
   simple_string( string_trait::GetDefaultManager() )
{

   *this = *id.m_pstr;

}


string::string(const var & var) :
   simple_string( string_trait::GetDefaultManager() )
{

   *this = var.get_string();

}


string::string( const string_interface & str ) :
   simple_string( string_trait::GetDefaultManager() )
{
   char sz[256];
   strsize iLen = str.get_length();
   if(iLen < ((sizeof(sz) / sizeof(sz[0])) - sizeof(sz[0])))
   {
      str.get_string(sz);
      *this = sz;
   }
   else
   {
      char * psz = (char *) malloc(sizeof(char) * (iLen + 1));
      str.get_string(psz);
      *this = psz;
      free(psz);
   }
}


string::string(const wchar_t * pszSrc,string_manager * pstringmanager ) :
   simple_string( pstringmanager )
{
   //      if( !CheckImplicitLoad( pszSrc ) )
   //      {
   *this = pszSrc;
   //      }
}

string::string( const unsigned char* pszSrc ) :
   simple_string( string_trait::GetDefaultManager() )
{
   *this = reinterpret_cast< const char* >( pszSrc );
}

/*CSTRING_EXPLICIT string::string(char* pszSrc ) :
simple_string( string_trait::GetDefaultManager() )
{
const char *psz = reinterpret_cast< const char* >( pszSrc );
//      if (!CheckImplicitLoad( psz ))
//    {
*this = psz;
//  }
}*/

string::string(unsigned char* pszSrc ) :
   simple_string( string_trait::GetDefaultManager() )
{
   const char *psz = reinterpret_cast< const char* >( pszSrc );
   //      if (!CheckImplicitLoad( psz ))
   //    {
   *this = psz;
   //  }
}

string::string(wchar_t* pszSrc ) :
   simple_string( string_trait::GetDefaultManager() )
{
   const wchar_t *psz = reinterpret_cast< const wchar_t* >( pszSrc );
   //if (!CheckImplicitLoad( psz ))
   {
      *this = psz;
   }
}

string::string(const istring & istr) :
   simple_string( string_trait::GetDefaultManager() )
{
   *this = (const char *) istr;
}

string::string(const unsigned char* pszSrc,string_manager * pstringmanager ) :
   simple_string( pstringmanager )
{
   *this = reinterpret_cast< const char* >( pszSrc );
}

string::string(char ch,strsize nLength) :
   simple_string( string_trait::GetDefaultManager() )
{
   ASSERT( nLength >= 0 );
   if( nLength > 0 )
   {
      PXSTR pszBuffer = GetBuffer( nLength );
      string_trait::FloodCharacters( XCHAR( ch ), nLength, pszBuffer );
      ReleaseBufferSetLength( nLength );
   }
}

string::string(strsize nLength, char ch) :
   simple_string( string_trait::GetDefaultManager() )
{
   ASSERT( nLength >= 0 );
   if( nLength > 0 )
   {
      PXSTR pszBuffer = GetBuffer( nLength );
      string_trait::FloodCharacters( XCHAR( ch ), nLength, pszBuffer );
      ReleaseBufferSetLength( nLength );
   }

}


string::string(const XCHAR* pch,strsize nLength ) :
   simple_string( pch, nLength, string_trait::GetDefaultManager() )
{
}

string::string(const XCHAR* pch,strsize nLength,string_manager * pstringmanager ) :
   simple_string( pch, nLength, pstringmanager )
{
}

string::~string() throw()
{
}

string& string::operator=(const string_interface & str )
{
   simple_string::operator=(string(str));

   return( *this );
}

string& string::operator=(string strSrc )
{
   simple_string::operator=( strSrc );

   return( *this );
}


string& string::operator=(PCXSTR pszSrc )
{
   simple_string::operator=( pszSrc );

   return( *this );
}

string& string::operator=(const vsstring & str)
{
   simple_string::operator=( str.m_psz );

   return( *this );
}

string & string::operator = (const class id & id)
{

   simple_string::operator = (id.str());

   return( *this );

}

string& string::operator=(PCYSTR pszSrc )
{
   // nDestLength is in XCHARs
   strsize nDestLength = (pszSrc != NULL) ? string_trait::GetcharLength( pszSrc ) : 0;
   if( nDestLength > 0 )
   {
      PXSTR pszBuffer = GetBuffer( nDestLength );
      string_trait::ConvertTochar( pszBuffer, nDestLength, pszSrc);
      ReleaseBufferSetLength( nDestLength );
   }
   else
   {
      Empty();
   }

   return( *this );
}

string& string::operator=(const unsigned char* pszSrc )
{
   return( operator=( reinterpret_cast< const char* >( pszSrc ) ) );
}

string& string::operator=(char ch )
{
   char ach[2] = { ch, 0 };

   return( operator=( ach ) );
}

string& string::operator=(wchar_t ch )
{
   wchar_t ach[2] = { ch, 0 };

   return( operator=( ach ) );
}

string& string::operator+=(const simple_string& str )
{
   append( str, str.get_length() );

   return( *this );
}

string& string::operator+=(PCXSTR pszSrc )
{
   simple_string::operator+=( pszSrc );

   return( *this );
}
string& string::operator+=(PCYSTR pszSrc )
{
   string str( pszSrc, GetManager() );

   return( operator+=( str ) );
}

string& string::operator+=(char ch )
{
   AppendChar((XCHAR)  ch );

   return( *this );
}

string& string::operator+=(unsigned char ch )
{
   AppendChar((XCHAR)  ch );

   return( *this );
}

string& string::operator+=(wchar_t ch )
{
   AppendChar((XCHAR) ch );

   return( *this );
}

// Override from base class
string_manager * string::GetManager() const throw()
{
   string_manager * pstringmanager = simple_string::GetManager();
   if(pstringmanager) { return pstringmanager; }

   pstringmanager = string_trait::GetDefaultManager();
   return pstringmanager->Clone();
}

string & string::assign (const string & str)
{
   return operator = (str);
}

string & string::assign(const string & str, strsize pos, strsize n)
{
   return operator = (str.substr(pos, n));
}

string & string::assign(const char* s, strsize n)
{
   return operator = (string(s, n));
}

string & string::assign(const char * s)
{
   return operator = (s);
}

string & string::assign(strsize n, char c)
{
   return operator = (string(c, n));
}

string & string::assign(int n, int c)
{
   return assign((uint64) n, (uint64) c);
}

string & string::assign(int64_t n, int64_t c)
{
   return assign((uint64) n, (uint64) c);
}

string & string::assign(unsigned int n, unsigned int c)
{
   return assign((uint64) n, (uint64) c);
}

string & string::assign(uint64 n, uint64 c)
{
   string strChar = gen::str::uni_to_utf8(c);
   while(n > 0)
   {
      *this += strChar;
   }
   return *this;
}



// Comparison


int string::Collate(PCXSTR psz ) const RELEASENOTHROW
{
   ASSERT( __is_valid_string( psz ) );
   return( string_trait::StringCollate( GetString(), psz ) );
}

int string::CollateNoCase(PCXSTR psz ) const RELEASENOTHROW
{
   ASSERT( __is_valid_string( psz ) );
   return( string_trait::StringCollateIgnore( GetString(), psz ) );
}

int string::compare(PCXSTR psz ) const
{
   return Compare(psz);
}

int string::compare_no_case(PCXSTR psz ) const throw()
{
   return CompareNoCase(psz);
}

int string::collate(PCXSTR psz ) const throw()
{
   return Collate(psz);
}

int string::collate_no_case(PCXSTR psz ) const throw()
{
   return CollateNoCase(psz);
}

int string::compare(strsize iStart, strsize nCount, PCXSTR psz ) const
{
   return substr(iStart, nCount).compare(psz);
}

int string::compare_no_case(strsize iStart, strsize nCount, PCXSTR psz ) const
{
   return substr(iStart, nCount).compare_no_case(psz);
}

int string::collate(strsize iStart, strsize nCount, PCXSTR psz ) const
{
   return substr(iStart, nCount).collate(psz);
}

int string::collate_no_case(strsize iStart, strsize nCount, PCXSTR psz ) const
{
   return substr(iStart, nCount).compare_no_case(psz);
}

int string::compare(strsize iStart, strsize nCount, PCXSTR psz, strsize start2, strsize count2) const
{
   return substr(iStart, nCount).compare(string(psz).substr(start2, count2));
}

int string::compare_no_case(strsize iStart, strsize nCount, PCXSTR psz, strsize start2, strsize count2) const
{
   return substr(iStart, nCount).compare_no_case(string(psz).substr(start2, count2));
}

int string::collate(strsize iStart, strsize nCount, PCXSTR psz, strsize start2, strsize count2) const
{
   return substr(iStart, nCount).collate(string(psz).substr(start2, count2));
}

int string::collate_no_case(strsize iStart, strsize nCount, PCXSTR psz, strsize start2, strsize count2) const
{
   return substr(iStart, nCount).collate_no_case(string(psz).substr(start2, count2));
}


bool string::contains(char ch, strsize iStart, strsize nCount)
{
   return find(ch, iStart, nCount) >= 0;
}

bool string::contains(wchar_t wch, strsize iStart, strsize nCount)
{
   return find_w(gen::str::uni_to_utf8(wch), iStart, nCount) >= 0;
}

bool string::contains(int i, strsize iStart, strsize nCount) // utf8 char index
{
   return find_w(gen::str::uni_to_utf8(i), iStart, nCount) >= 0;
}

bool string::contains(const char * psz, strsize iStart, strsize nCount)
{
   return find(psz, iStart, nCount) >= 0;
}

bool string::contains(const string & str, strsize iStart, strsize nCount)
{
   return find(str, iStart, nCount) >= 0;
}

bool string::contains_ci(char ch, strsize iStart, strsize nCount)
{
   return find_ci(ch, iStart, nCount) >= 0;
}

bool string::contains_ci(wchar_t wch, strsize iStart, strsize nCount)
{
   return find_wci(gen::str::uni_to_utf8(wch), iStart, nCount) >= 0;
}

bool string::contains_ci(int i, strsize iStart, strsize nCount) // utf8 char index
{
   return find_wci(gen::str::uni_to_utf8(i), iStart, nCount) >= 0;
}

bool string::contains_ci(const char * psz, strsize iStart, strsize nCount)
{
   return find_ci(psz, iStart, nCount) >= 0;
}

bool string::contains_ci(const string & str, strsize iStart, strsize nCount)
{
   return find_ci(str, iStart, nCount) >= 0;
}

bool string::contains_wci(wchar_t wch, strsize iStart, strsize nCount)
{
   return find_wci(gen::str::uni_to_utf8(wch), iStart, nCount) >= 0;
}

bool string::contains_wci(int i, strsize iStart, strsize nCount) // utf8 char index
{
   return find_wci(gen::str::uni_to_utf8(i), iStart, nCount) >= 0;
}

bool string::contains_wci(const char * psz, strsize iStart, strsize nCount)
{
   return find_wci(psz, iStart, nCount) >= 0;
}

bool string::contains_wci(const string & str, strsize iStart, strsize nCount)
{
   return find_wci(str, iStart, nCount) >= 0;
}


string & string::erase(strsize iStart, strsize strsize)
{
   if( iStart < 0 )
      strsize = 0;

   if( strsize < 0 )
      strsize = get_length();

   Delete(iStart, strsize);

   return *this;
}

strsize string::Delete(strsize iIndex,strsize nCount)
{
   strsize nLength = get_length();

   if( iIndex < 0 )
      iIndex = 0;

   if(nCount < 0)
      nCount = nLength;

   if(nCount + iIndex > nLength)
      nCount = nLength - iIndex;

   if(nCount < 0)
      return get_length();

   if( (::gen::add_throw(nCount, iIndex)) > nLength )
   {
      nCount = nLength-iIndex;
   }
   if( nCount > 0 )
   {
      strsize nNewLength = nLength-nCount;
      strsize nXCHARsToCopy = nLength-(iIndex+nCount)+1;
      PXSTR pszBuffer = GetBuffer();
      ::gen::memmove_s( pszBuffer+iIndex, nXCHARsToCopy*sizeof( XCHAR ),
         pszBuffer+iIndex+nCount, nXCHARsToCopy*sizeof( XCHAR ) );
      ReleaseBufferSetLength( nNewLength );
   }

   return( get_length() );
}

strsize string::Insert(strsize iIndex,XCHAR ch )
{
   if( iIndex < 0 )
      iIndex = 0;

   if( iIndex > get_length() )
   {
      iIndex = get_length();
   }
   strsize nNewLength = get_length()+1;

   PXSTR pszBuffer = GetBuffer( nNewLength );

   // move existing bytes down
   ::gen::memmove_s( pszBuffer+iIndex+1, (nNewLength-iIndex)*sizeof( XCHAR ),
      pszBuffer+iIndex, (nNewLength-iIndex)*sizeof( XCHAR ) );
   pszBuffer[iIndex] = ch;

   ReleaseBufferSetLength( nNewLength );

   return( nNewLength );
}

strsize string::Insert(strsize iIndex,PCXSTR psz )
{
   if( iIndex < 0 )
      iIndex = 0;

   if( iIndex > get_length() )
   {
      iIndex = get_length();
   }

   // nInsertLength and nNewLength are in XCHARs
   strsize nInsertLength = string_trait::SafeStringLen( psz );
   strsize nNewLength = get_length();
   if( nInsertLength > 0 )
   {
      nNewLength += nInsertLength;

      PXSTR pszBuffer = GetBuffer( nNewLength );
      // move existing bytes down
      ::gen::memmove_s( pszBuffer+iIndex+nInsertLength, (nNewLength-iIndex-nInsertLength+1)*sizeof( XCHAR ),
         pszBuffer+iIndex, (nNewLength-iIndex-nInsertLength+1)*sizeof( XCHAR ) );
      ::gen::memcpy_s( pszBuffer+iIndex, nInsertLength*sizeof( XCHAR ),
         psz, nInsertLength*sizeof( XCHAR ) );
      ReleaseBufferSetLength( nNewLength );
   }

   return( nNewLength );
}

strsize string::replace(XCHAR chOld,XCHAR chNew, strsize iStart )
{
   strsize nCount = 0;

   // short-circuit the nop case
   if( chOld != chNew )
   {
      // otherwise modify each character that matches in the string
      bool bCopied = false;
      PXSTR pszBuffer = const_cast< PXSTR >( GetString() + iStart);  // We don't actually write to pszBuffer until we've called GetBuffer().

      strsize nLength = get_length();
      strsize iChar = 0;
      while( iChar < nLength )
      {
         // replace instances of the specified character only
         if( pszBuffer[iChar] == chOld )
         {
            if( !bCopied )
            {
               bCopied = true;
               pszBuffer = GetBuffer( nLength );
            }
            pszBuffer[iChar] = chNew;
            nCount++;
         }
         iChar = strsize( (pszBuffer+iChar + 1 )-pszBuffer );
      }
      if( bCopied )
      {
         ReleaseBufferSetLength( nLength );
      }
   }

   return( nCount );
}

strsize string::replace(PCXSTR pszOld, PCXSTR pszNew, strsize iStart)
{
   // can't have is_empty or NULL lpszOld

   // nSourceLen is in XCHARs
   strsize nSourceLen = string_trait::SafeStringLen( pszOld );
   if( nSourceLen == 0 )
      return( 0 );
   // nReplacementLen is in XCHARs
   strsize nReplacementLen = string_trait::SafeStringLen( pszNew );

   // loop once to figure out the size of the result string
   strsize nCount = 0;
   {
      PCXSTR pszStart = GetString() + iStart;
      PCXSTR pszEnd = pszStart+get_length();
      PCXSTR pszTarget;
      while( (pszTarget = string_trait::StringFindString( pszStart, pszOld ) ) != NULL)
      {
         nCount++;
         pszStart = pszTarget+nSourceLen;
      }
   }

   // if any changes were made, make them
   if( nCount > 0 )
   {
      // if the buffer is too small, just
      //   allocate a new buffer (slow but sure)
      strsize nOldLength = get_length();
      strsize nNewLength = nOldLength+(nReplacementLen-nSourceLen)*nCount;

      PXSTR pszBuffer = GetBuffer( __max( nNewLength, nOldLength ) );

      PXSTR pszStart = pszBuffer + iStart;
      PXSTR pszEnd = pszBuffer+nOldLength;

      // loop again to actually do the work
      while( pszStart < pszEnd )
      {
         PXSTR pszTarget;
         while( (pszTarget = string_trait::StringFindString( pszStart, pszOld ) ) != NULL )
         {
            strsize nBalance = nOldLength-strsize(pszTarget-pszBuffer+nSourceLen);
            ::gen::memmove_s( pszTarget+nReplacementLen, nBalance*sizeof( XCHAR ),
               pszTarget+nSourceLen, nBalance*sizeof( XCHAR ) );
            ::gen::memcpy_s( pszTarget, nReplacementLen*sizeof( XCHAR ),
               pszNew, nReplacementLen*sizeof( XCHAR ) );
            pszStart = pszTarget+nReplacementLen;
            pszTarget[nReplacementLen+nBalance] = 0;
            nOldLength += (nReplacementLen-nSourceLen);
         }
         pszStart += string_trait::SafeStringLen( pszStart )+1;
      }
      ASSERT( pszBuffer[nNewLength] == 0 );
      ReleaseBufferSetLength( nNewLength );
   }

   return( nCount );
}

string & string::replace(strsize iStart, strsize nCount, const char * psz)
{
   if(nCount < 0)
   {
      return operator = (Left(iStart) + psz);
   }
   else
   {
      return operator = (Left(iStart) + psz + Mid(nCount));
   }
}

strsize string::remove(XCHAR chRemove )
{
   strsize nLength = get_length();
   PXSTR pszBuffer = GetBuffer( nLength );

   PXSTR pszSource = pszBuffer;
   PXSTR pszDest = pszBuffer;
   PXSTR pszEnd = pszBuffer+nLength;

   while( pszSource < pszEnd )
   {
      PXSTR pszNewSource = pszSource + 1;
      if(*pszSource != chRemove)
      {
         // copy the source to the destination.  Remember to copy all bytes of an MBCS character
         // copy the source to the destination.  Remember to copy all bytes of an MBCS character
         size_t NewSourceGap = (pszNewSource-pszSource);
         PXSTR pszNewDest = pszDest + NewSourceGap;
         size_t i = 0;
         for (i = 0;  pszDest != pszNewDest && i < NewSourceGap; i++)
         {
            *pszDest = *pszSource;
            pszSource++;
            pszDest++;
         }
      }
      pszSource = pszNewSource;
   }
   *pszDest = 0;
   strsize nCount = strsize( pszSource-pszDest );
   ReleaseBufferSetLength( nLength-nCount );

   return( nCount );
}

string string::Tokenize(PCXSTR pszTokens, strsize& iStart ) const
{
   ASSERT( iStart >= 0 );

   if(iStart < 0)
      throw invalid_argument_exception();

   if( (pszTokens == NULL) || (*pszTokens == (XCHAR)0) )
   {
      if (iStart < get_length())
      {
         return( string( GetString()+iStart, GetManager() ) );
      }
   }
   else
   {
      PCXSTR pszPlace = GetString()+iStart;
      PCXSTR pszEnd = GetString()+get_length();
      if( pszPlace < pszEnd )
      {
         strsize nIncluding = string_trait::StringSpanIncluding( pszPlace,
            pszTokens );

         if( (pszPlace+nIncluding) < pszEnd )
         {
            pszPlace += nIncluding;
            strsize nExcluding = string_trait::StringSpanExcluding( pszPlace, pszTokens );

            strsize iFrom = iStart+nIncluding;
            strsize nUntil = nExcluding;
            iStart = iFrom+nUntil+1;

            return( Mid( iFrom, nUntil ) );
         }
      }
   }

   // return is_empty string, done tokenizing
   iStart = -1;

   return( string( GetManager() ) );
}

// find routines

// find the first occurrence of character 'ch', starting at strsize 'iStart'
strsize string::find(XCHAR ch,strsize iStart, strsize nCount) const RELEASENOTHROW
{
   // iStart is in XCHARs
   ASSERT( iStart >= 0 );

   // nLength is in XCHARs
   strsize nLength = get_length();
   if( iStart < 0 || iStart >= nLength)
   {
      return( -1 );
   }

   if(nCount < 0)
      nCount = nLength;

   if(nCount + iStart > nLength)
      nCount = nLength - iStart;

   if(nCount < 0)
      return -1;

   PCXSTR psz = GetString() + iStart;
   for(int i = 0; i < nCount; i++)
   {
      if(psz[i] == ch)
      {
         return iStart + i;
      }
   }
   return -1;
}

// find the first occurrence of character 'ch', starting at strsize 'iStart'
strsize string::find_ci(XCHAR ch,strsize iStart, strsize nCount) const RELEASENOTHROW
{
   // iStart is in XCHARs
   ASSERT( iStart >= 0 );

   // nLength is in XCHARs
   strsize nLength = get_length();
   if( iStart < 0 || iStart >= nLength)
   {
      return( -1 );
   }

   if(nCount < 0)
      nCount = nLength;

   if(nCount + iStart > nLength)
      nCount = nLength - iStart;

   if(nCount < 0)
      return -1;

   PCXSTR psz = GetString() + iStart;
   for(int i = 0; i < nCount; i++)
   {
      if(tolower(psz[i]) == tolower(ch))
      {
         return iStart + i;
      }
   }
   return -1;
}

strsize string::find_first_of(XCHAR ch,strsize iStart) const throw()
{
   return find(ch, iStart);
}
// look for a specific sub-string

// find the first occurrence of string 'pszSub', starting at strsize 'iStart'
strsize string::find(PCXSTR pszSub,strsize iStart, strsize nCount) const RELEASENOTHROW
{
   // iStart is in XCHARs
   ASSERT( iStart >= 0 );
   ASSERT( __is_valid_string( pszSub ) );

   if(pszSub == NULL)
   {
      return( -1 );
   }
   // nLength is in XCHARs
   strsize nLength = get_length();
   if( iStart < 0 || iStart > nLength )
   {
      return( -1 );
   }

   strsize nLength2 = strlen(pszSub);

   if(nCount < 0)
      nCount = nLength;

   if(nCount + iStart + nLength2 > nLength)
      nCount = nLength  - iStart - nLength2;

   if(nCount < 0)
      return -1;

   PCXSTR psz = GetString() + iStart;
   for(int i = 0; i <= nCount; i++)
   {
      bool bFound = true;
      int j;
      for(j = 0; j < nLength2; j++)
      {
         if(psz[j] != pszSub[j])
         {
            bFound = false;
            break;
         }
      }
      if(bFound && j == nLength2)
         return i + iStart;
      psz++;
   }
   return -1;
}

// find the first occurrence of string 'pszSub', starting at strsize 'iStart'
strsize string::find_ci(PCXSTR pszSub,strsize iStart, strsize nCount) const RELEASENOTHROW
{
   // iStart is in XCHARs
   ASSERT( iStart >= 0 );
   ASSERT( __is_valid_string( pszSub ) );

   if(pszSub == NULL)
   {
      return( -1 );
   }
   // nLength is in XCHARs
   strsize nLength = get_length();
   if( iStart < 0 || iStart > nLength )
   {
      return( -1 );
   }

   strsize nLength2 = strlen(pszSub);

   if(nCount < 0)
      nCount = nLength;

   if(nCount + iStart + nLength2 > nLength)
      nCount = nLength  - iStart - nLength2;

   if(nCount < 0)
      return -1;

   PCXSTR psz = GetString() + iStart;
   for(int i = 0; i <= nCount; i++)
   {
      bool bFound = true;
      for(int j = 0; j < nLength2; j++)
      {
         if(tolower(psz[j]) != tolower(pszSub[j]))
         {
            bFound = false;
            break;
         }
      }
      if(bFound)
         return i + iStart;
      psz++;
   }
   return -1;
}

// find the first occurrence of string 'pszSub', starting at strsize 'iStart'
strsize string::find_w(PCXSTR pszSub,strsize iStart, strsize nCount) const RELEASENOTHROW
{
   // iStart is in XCHARs
   ASSERT( iStart >= 0 );
   ASSERT( __is_valid_string( pszSub ) );

   if(pszSub == NULL)
   {
      return( -1 );
   }

   if(iStart < 0)
      return -1;

   PCXSTR psz = GetString() + iStart;

   if(*psz == '\0')
      return -1;
   while(*psz != '\0' && (psz - GetString() - iStart) < nCount)
   {
      bool bFound = true;
      const char * psz2 = psz;
      const char * pszSub2 = pszSub;
      while(*psz2 != '\0' && *pszSub2 != '\0')
      {
         if(gen::str::utf8_char(psz2) != gen::str::utf8_char(pszSub2))
         {
            bFound = false;
            break;
         }
         psz2 = gen::str::utf8_inc(psz2);
         pszSub2 = gen::str::utf8_inc(pszSub2);
      }
      if(bFound)
      {
         if(*pszSub2 == '\0')
         {
            return psz - GetString();
         }
         else
         {
            return -1;
         }
      }
      psz++;
   }
   return -1;
}

// find the first occurrence of string 'pszSub', starting at strsize 'iStart'
strsize string::find_wci(PCXSTR pszSub,strsize iStart, strsize nCount) const RELEASENOTHROW
{
   // iStart is in XCHARs
   ASSERT( iStart >= 0 );
   ASSERT( __is_valid_string( pszSub ) );

   if(pszSub == NULL)
   {
      return( -1 );
   }

   if(iStart < 0)
      return -1;

   PCXSTR psz = GetString() + iStart;

   if(*psz == '\0')
      return -1;
   while(*psz != '\0' && (psz - GetString() - iStart) < nCount)
   {
      bool bFound = true;
      const char * psz2 = psz;
      const char * pszSub2 = pszSub;
      while(*psz2 != '\0' && *pszSub2 != '\0')
      {
         if(gen::ch::to_lower_case(psz2) != gen::ch::to_lower_case(pszSub2))
         {
            bFound = false;
            break;
         }
         psz2 = gen::str::utf8_inc(psz2);
         pszSub2 = gen::str::utf8_inc(pszSub2);
      }
      if(bFound)
      {
         if(*pszSub2 == '\0')
         {
            return psz - GetString();
         }
         else
         {
            return -1;
         }
      }
      psz++;
   }
   return -1;
}

// find the first occurrence of any of the characters in string 'pszCharSet'
strsize string::FindOneOf(PCXSTR pszCharSet, strsize iStart, strsize n) const RELEASENOTHROW
{
   string strCharSet(pszCharSet, n);
   // iStart is in XCHARs
   ASSERT( iStart >= 0 );

   // nLength is in XCHARs
   strsize nLength = get_length();
   if( iStart < 0 || iStart >= nLength)
   {
      return( -1 );
   }
   PCXSTR psz = string_trait::StringScanSet( &GetString()[iStart], strCharSet );
   return( (psz == NULL) ? -1 : strsize( psz-GetString() ) );
}

strsize string::find_first_of(PCXSTR pszCharSet, strsize iStart) const throw()
{
   return FindOneOf(pszCharSet, iStart, -1);
}

strsize string::find_first_of(PCXSTR pszCharSet, strsize iStart, strsize n) const throw()
{
   return FindOneOf(pszCharSet, iStart, n);
}

strsize string::find_first_of(const string & strCharSet, strsize pos) const throw()
{
   return FindOneOf(strCharSet, pos, strCharSet.get_length());
}

strsize string::find_first_not_of(const string& str, strsize pos) const
{
   return find_first_not_of(str, pos, str.get_length());
}

strsize string::find_first_not_of(const char* s, strsize pos) const
{
   return find_first_not_of(s, pos, strlen(s));
}

strsize string::find_first_not_of(char c, strsize pos) const
{
   strsize nLength = get_length();

   if(pos < 0 || pos >= nLength)
      return -1;
   const char * psz = &GetString()[pos];
   while(*psz != '\0' && *psz == c)
   {
      psz++;
   }
   if(*psz == '\0')
      return -1;
   else
      return psz - GetString();
}

strsize string::find_first_not_of(const char* s, strsize pos, strsize n ) const
{
   string strChars(s, n);

   strsize nLength = get_length();

   if(pos < 0 || pos >= nLength)
      return -1;
   const char * psz = &GetString()[pos];
   while(*psz != '\0' && strChars.contains(*psz))
   {
      psz++;
   }
   if(*psz == '\0')
      return -1;
   else
      return psz - GetString();
}


// find the first occurrence of any of the characters in string 'pszCharSet'
strsize string::find_last_of(char c, strsize pos) const throw()
{
   strsize nLength = get_length();
   // nLength is in XCHARs
   if(pos < 0)
      pos = nLength - 1;
   if(pos < 0 || pos >= nLength)
   {
      return( -1 );
   }
   PCXSTR psz = GetString();
   while(pos >= 0 && psz[pos] != c)
   {
      pos--;
   }
   return pos;
}

strsize string::find_last_of(PCXSTR pszCharSet, strsize iStart) const throw()
{
   return find_last_of(pszCharSet, iStart, -1);
}

strsize string::find_last_of(PCXSTR pszCharSet, strsize pos, strsize n) const throw()
{
   strsize nLength = get_length();
   // nLength is in XCHARs
   if(pos < 0)
      pos = nLength - 1;
   if(pos < 0 || pos >= nLength)
   {
      return( -1 );
   }
   string strChars(pszCharSet, n);
   PCXSTR psz = GetString();
   while(pos >= 0 && !strChars.contains(psz[pos]))
   {
      pos--;
   }
   return pos;
}

strsize string::find_last_of(const string & strCharSet, strsize pos) const throw()
{
   return find_last_of(strCharSet, pos, strCharSet.get_length());
}


// find the first occurrence of any of the characters in string 'pszCharSet'
strsize string::find_last_not_of(char c, strsize pos) const throw()
{
   strsize nLength = get_length();
   // nLength is in XCHARs
   if(pos < 0)
      pos = nLength - 1;
   if(pos < 0 || pos >= nLength)
   {
      return( -1 );
   }
   PCXSTR psz = GetString();
   while(pos >= 0 && psz[pos] == c)
   {
      pos--;
   }
   return pos;
}

strsize string::find_last_not_of(PCXSTR pszCharSet, strsize iStart) const throw()
{
   return find_last_not_of(pszCharSet, iStart, -1);
}

strsize string::find_last_not_of(PCXSTR pszCharSet, strsize pos, strsize n) const throw()
{
   strsize nLength = get_length();
   // nLength is in XCHARs
   if(pos < 0)
      pos = nLength - 1;
   if(pos < 0 || pos >= nLength)
   {
      return( -1 );
   }
   string strChars(pszCharSet, n);
   PCXSTR psz = GetString();
   while(pos >= 0 && strChars.contains(psz[pos]))
   {
      pos--;
   }
   return pos;
}

strsize string::find_last_not_of(const string & strCharSet, strsize pos) const throw()
{
   return find_last_not_of(strCharSet, pos, strCharSet.get_length());
}


// find the last occurrence of character 'ch'
strsize string::reverse_find(XCHAR ch, strsize iStart) const throw()
{
   // find last single character
   PCXSTR psz = string_trait::StringFindCharRev( GetString(), ch, iStart );

   // return -1 if not found, distance from beginning otherwise
   return( (psz == NULL) ? -1 : strsize( psz-GetString() ) );
}

// find the last occurrence of character 'ch'
strsize string::reverse_find( PCXSTR ch, strsize iStart) const throw()
{
   // find last single character
   PCXSTR psz = string_trait::StringFindStrRev( GetString(), ch, iStart );

   // return -1 if not found, distance from beginning otherwise
   return( (psz == NULL) ? -1 : strsize( psz-GetString() ) );
}

// manipulation

// Convert the string to uppercase
string& string::make_upper()
{
   strsize nLength = get_length();
   PXSTR pszBuffer = GetBuffer( nLength );
   string_trait::StringUppercase( pszBuffer, nLength+1 );
   ReleaseBufferSetLength( nLength );

   return( *this );
}

// Convert the string to lowercase
string& string::make_lower()
{
   strsize nLength = get_length();
   PXSTR pszBuffer = GetBuffer( nLength );
   string_trait::StringLowercase( pszBuffer, nLength+1 );
   ReleaseBufferSetLength( nLength );

   return( *this );
}

// Reverse the string
string& string::MakeReverse()
{
   strsize nLength = get_length();
   PXSTR pszBuffer = GetBuffer( nLength );
   string_trait::StringReverse( pszBuffer );
   ReleaseBufferSetLength( nLength );

   return( *this );
}

// trimming

// remove all trailing whitespace
string& string::trim_right()
{

   PCXSTR pszLast = NULL;
   PCXSTR pszMax = GetString() + get_length();
   PCXSTR psz = pszMax;

   if(psz != NULL)
   {
      while(true)
      {
         psz = gen::str::utf8_dec(GetString(), psz);
         if(psz < GetString())
            break;
         if(!string_trait::IsSpace(psz))
         {
            pszLast = gen::str::__utf8_inc(psz);
            break;
         }
      }
   }

   if(pszLast != NULL && pszLast < pszMax)
   {

      // truncate at trailing space iStart

      strsize iLast = strsize(pszLast - GetString());

      Truncate( iLast );

   }

   return( *this );

}

// remove all leading whitespace
string& string::trim_left()
{
   // find first non-space character

   PCXSTR psz = GetString();

   while( string_trait::IsSpace( psz ) )
   {
      psz = string_trait::CharNext( psz );
   }

   if( psz != GetString() )
   {
      // fix up data and length
      strsize iFirst = strsize( psz-GetString() );
      PXSTR pszBuffer = GetBuffer( get_length() );
      psz = pszBuffer+iFirst;
      strsize nDataLength = get_length()-iFirst;
      ::gen::memmove_s( pszBuffer, (nDataLength+1)*sizeof( XCHAR ),
         psz, (nDataLength+1)*sizeof( XCHAR ) );
      ReleaseBufferSetLength( nDataLength );
   }

   return( *this );
}

// remove all leading and trailing whitespace
string& string::trim()
{
   return( trim_right().trim_left() );
}

// remove all leading and trailing occurrences of character 'chTarget'
string& string::trim(XCHAR chTarget )
{
   return( trim_right( chTarget ).trim_left( chTarget ) );
}

// remove all leading and trailing occurrences of any of the characters in the string 'pszTargets'
string& string::trim(PCXSTR pszTargets )
{
   return( trim_right( pszTargets ).trim_left( pszTargets ) );
}

// trimming anything (either side)

// remove all trailing occurrences of character 'chTarget'
string& string::trim_right(XCHAR chTarget )
{
   // find beginning of trailing matches
   // by starting at beginning (DBCS aware)

   PCXSTR psz = GetString();
   PCXSTR pszLast = NULL;

   while( *psz != 0 )
   {
      if( *psz == chTarget )
      {
         if( pszLast == NULL )
         {
            pszLast = psz;
         }
      }
      else
      {
         pszLast = NULL;
      }
      psz = string_trait::CharNext( psz );
   }

   if( pszLast != NULL )
   {
      // truncate at left-most matching character
      strsize iLast = strsize( pszLast-GetString() );
      Truncate( iLast );
   }

   return( *this );
}

// remove all trailing occurrences of any of the characters in string 'pszTargets'
string& string::trim_right(PCXSTR pszTargets )
{
   // if we're not trimming anything, we're not doing any work
   if( (pszTargets == NULL) || (*pszTargets == 0) )
   {
      return( *this );
   }

   // find beginning of trailing matches
   // by starting at beginning (DBCS aware)

   PCXSTR psz = GetString();
   PCXSTR pszLast = NULL;

   while( *psz != 0 )
   {
      if( string_trait::StringFindChar( pszTargets, *psz ) != NULL )
      {
         if( pszLast == NULL )
         {
            pszLast = psz;
         }
      }
      else
      {
         pszLast = NULL;
      }
      psz = string_trait::CharNext( psz );
   }

   if( pszLast != NULL )
   {
      // truncate at left-most matching character
      strsize iLast = strsize( pszLast-GetString() );
      Truncate( iLast );
   }

   return( *this );
}

// remove all leading occurrences of character 'chTarget'
string& string::trim_left(XCHAR chTarget )
{
   // find first non-matching character
   PCXSTR psz = GetString();

   while( chTarget == *psz )
   {
      psz = string_trait::CharNext( psz );
   }

   if( psz != GetString() )
   {
      // fix up data and length
      strsize iFirst = strsize( psz-GetString() );
      PXSTR pszBuffer = GetBuffer( get_length() );
      psz = pszBuffer+iFirst;
      strsize nDataLength = get_length()-iFirst;
      ::gen::memmove_s( pszBuffer, (nDataLength+1)*sizeof( XCHAR ),
         psz, (nDataLength+1)*sizeof( XCHAR ) );
      ReleaseBufferSetLength( nDataLength );
   }

   return( *this );
}

// remove all leading occurrences of any of the characters in string 'pszTargets'
string& string::trim_left(PCXSTR pszTargets )
{
   // if we're not trimming anything, we're not doing any work
   if( (pszTargets == NULL) || (*pszTargets == 0) )
   {
      return( *this );
   }

   PCXSTR psz = GetString();
   while( (*psz != 0) && (string_trait::StringFindChar( pszTargets, *psz ) != NULL) )
   {
      psz = string_trait::CharNext( psz );
   }

   if( psz != GetString() )
   {
      // fix up data and length
      strsize iFirst = strsize( psz-GetString() );
      PXSTR pszBuffer = GetBuffer( get_length() );
      psz = pszBuffer+iFirst;
      strsize nDataLength = get_length()-iFirst;
      ::gen::memmove_s( pszBuffer, (nDataLength+1)*sizeof( XCHAR ),
         psz, (nDataLength+1)*sizeof( XCHAR ) );
      ReleaseBufferSetLength( nDataLength );
   }

   return( *this );
}


// remove all trailing whitespace
string string::right_trimmed() const
{

   return string(*this).trim_right();

}


// remove all leading whitespace
string string::left_trimmed() const
{

   return string(*this).trim_left();

}


// remove all leading and trailing whitespace
string string::trimmed() const
{

   return string(*this).trim();

}


// remove all leading and trailing occurrences of character 'chTarget'
string string::trimmed(XCHAR chTarget) const
{

   return string(*this).trim(chTarget);

}


// remove all leading and trailing occurrences of any of the characters in the string 'pszTargets'
string string::trimmed(PCXSTR pszTargets) const
{

   return string(*this).trim(pszTargets);

}


// trimming anything (either side)

// remove all trailing occurrences of character 'chTarget'
string string::right_trimmed(XCHAR chTarget) const
{

   return string(*this).trim_right(chTarget);

}


// remove all trailing occurrences of any of the characters in string 'pszTargets'
string string::right_trimmed(PCXSTR pszTargets) const
{

   return string(*this).trim_right(pszTargets);

}


// remove all leading occurrences of character 'chTarget'
string string::left_trimmed(XCHAR chTarget) const
{

   return string(*this).trim_left(chTarget);

}


// remove all leading occurrences of any of the characters in string 'pszTargets'
string string::left_trimmed(PCXSTR pszTargets) const
{

   return string(*this).trim_left(pszTargets);

}


// Convert the string to the OEM character set
void string::AnsiToOem()
{
   strsize nLength = get_length();
   PXSTR pszBuffer = GetBuffer( nLength );
   string_trait::ConvertToOem( pszBuffer, nLength+1 );
   ReleaseBufferSetLength( nLength );
}

// Convert the string to the ANSI character set
void string::OemToAnsi()
{
   strsize nLength = get_length();
   PXSTR pszBuffer = GetBuffer( nLength );
   string_trait::ConvertToAnsi( pszBuffer, nLength+1 );
   ReleaseBufferSetLength( nLength );
}

// Very simple sub-string extraction

// Return the substring starting at strsize 'iFirst'
string string::Mid(strsize iFirst ) const
{
   return( Mid( iFirst, get_length()-iFirst ) );
}

string string::substr(strsize iFirst) const
{
   return Mid(iFirst);
}

// Return the substring starting at strsize 'iFirst', with length 'nCount'
string string::Mid(strsize iFirst,strsize nCount ) const
{
   // nCount is in XCHARs

   // out-of-bounds requests return sensible things

   strsize nLength = get_length();

   if (iFirst < 0)
      iFirst = 0;

   if(nCount < 0)
      nCount = nLength;

   if(nCount + iFirst > nLength)
      nCount = nLength - iFirst;

   if(nCount < 0)
      return "";

   if( (::gen::add_throw(iFirst,nCount)) > get_length() )
   {
      nCount = get_length()-iFirst;
   }
   if( iFirst > get_length() )
   {
      nCount = 0;
   }

   ASSERT( (nCount == 0) || ((iFirst+nCount) <= get_length()) );

   // optimize case of returning entire string
   if( (iFirst == 0) && ((iFirst+nCount) == get_length()) )
   {
      return( *this );
   }

   return( string( GetString()+iFirst, nCount, GetManager() ) );
}

string string::substr(strsize iFirst, strsize nCount) const
{
   return Mid(iFirst, nCount);
}

void string::clear()
{
   Empty();
}

// Return the substring consisting of the rightmost 'nCount' characters
string string::Right(strsize nCount ) const
{
   // nCount is in XCHARs
   if (nCount < 0)
      nCount = 0;

   strsize nLength = get_length();
   if( nCount >= nLength )
   {
      return( *this );
   }

   return( string( GetString()+nLength-nCount, nCount, GetManager() ) );
}

// Return the substring consisting of the leftmost 'nCount' characters
string string::Left(strsize nCount ) const
{
   // nCount is in XCHARs
   if (nCount < 0)
      nCount = 0;

   strsize nLength = get_length();
   if( nCount >= nLength )
   {
      return( *this );
   }

   return( string( GetString(), nCount, GetManager() ) );
}

// Return the substring consisting of the leftmost characters in the set 'pszCharSet'
string string::SpanIncluding(PCXSTR pszCharSet ) const
{
   ASSERT( __is_valid_string( pszCharSet ) );
   if(pszCharSet == NULL)
      throw invalid_argument_exception();

   return( Left( string_trait::StringSpanIncluding( GetString(), pszCharSet ) ) );
}

// Return the substring consisting of the leftmost characters not in the set 'pszCharSet'
string string::SpanExcluding(PCXSTR pszCharSet ) const
{
   ASSERT( __is_valid_string( pszCharSet ) );
   if(pszCharSet == NULL)
      throw invalid_argument_exception();

   return( Left( string_trait::StringSpanExcluding( GetString(), pszCharSet ) ) );
}

void string::AppendFormatV(PCXSTR pszFormat, va_list args )
{
   ASSERT( __is_valid_string( pszFormat ) );

   strsize nCurrentLength = get_length();
   strsize nAppendLength = string_trait::GetFormattedLength( pszFormat, args );
   PXSTR pszBuffer = GetBuffer( nCurrentLength+nAppendLength );
#if _SECURE_TEMPLATE
   string_trait::Format( pszBuffer+nCurrentLength,
      nAppendLength+1, pszFormat, args );
#else
   string_trait::Format( pszBuffer+nCurrentLength, pszFormat, args );
#endif
   ReleaseBufferSetLength( nCurrentLength+nAppendLength );
}

void string::FormatV(PCXSTR pszFormat, va_list args )
{
   ASSERT( __is_valid_string( pszFormat ) );
   if(pszFormat == NULL)
      throw invalid_argument_exception();

   strsize nLength = string_trait::GetFormattedLength( pszFormat, args );
   PXSTR pszBuffer = GetBuffer( nLength );
#if _SECURE_TEMPLATE
   string_trait::Format( pszBuffer, nLength+1, pszFormat, args );
#else
   string_trait::Format( pszBuffer, pszFormat, args );
#endif
   ReleaseBufferSetLength( nLength );
}

// Format a message using format string 'pszFormat' and va_list
void string::FormatMessageV(PCXSTR pszFormat, va_list* pArgList )
{
   // format message into temporary buffer pszTemp
   XCHAR * pszTemp;
   DWORD dwResult = string_trait::FormatMessage( FORMAT_MESSAGE_FROM_STRING|
      FORMAT_MESSAGE_ALLOCATE_BUFFER, pszFormat, 0, 0, reinterpret_cast< PXSTR >( &pszTemp ),
      0, pArgList );
   if( dwResult == 0 )
   {
      ThrowMemoryException();
   }

   *this = pszTemp;
   LocalFree(pszTemp);
}

// OLE BSTR support

// allocate a BSTR containing a copy of the string
BSTR string::AllocSysString() const
{
   BSTR bstrResult = string_trait::AllocSysString( GetString(), get_length() );
   if( bstrResult == NULL )
   {
      ThrowMemoryException();
   }
   return( bstrResult );
}

BSTR string::SetSysString(BSTR* pbstr ) const
{
   ASSERT( __is_valid_address( pbstr, sizeof( BSTR ) ) );

   if( !string_trait::ReAllocSysString( GetString(), pbstr,
      get_length() ) )
   {
      ThrowMemoryException();
   }
   ASSERT( *pbstr != NULL );
   return( *pbstr );
}

// Set the string to the value of environment var 'pszVar'
bool string::GetEnvironmentVariable(PCXSTR pszVar )
{
   ULONG nLength = string_trait::GetEnvironmentVariable( pszVar, NULL, 0 );
   bool bRetVal = FALSE;

   if( nLength == 0 )
   {
      Empty();
   }
   else
   {
      PXSTR pszBuffer = GetBuffer( nLength );
      string_trait::GetEnvironmentVariable( pszVar, pszBuffer, nLength );
      ReleaseBuffer();
      bRetVal = TRUE;
   }

   return( bRetVal );
}



// Load the string from resource 'nID'
//bool load_string(id id);

// Load the string from resource 'nID' in module 'hInstance'
/*    bool load_string(HINSTANCE hInstance,UINT nID )
{
const STRINGRESOURCEIMAGE* pImage = gen_GetStringResourceImage( hInstance, nID );
if( pImage == NULL )
{
return( FALSE );
}

strsize nLength = string_trait::GetcharLength( pImage->achString, pImage->nLength );
PXSTR pszBuffer = GetBuffer( nLength );
string_trait::ConvertTochar( pszBuffer, nLength, pImage->achString, pImage->nLength );
ReleaseBufferSetLength( nLength );

return( TRUE );
}*/

// Load the string from resource 'nID' in module 'hInstance', using language 'wLanguageID'
/*bool load_string(HINSTANCE hInstance,UINT nID,WORD wLanguageID )
{
const STRINGRESOURCEIMAGE* pImage = gen_GetStringResourceImage( hInstance, nID, wLanguageID );
if( pImage == NULL )
{
return( FALSE );
}

strsize nLength = string_trait::GetcharLength( pImage->achString, pImage->nLength );
PXSTR pszBuffer = GetBuffer( nLength );
string_trait::ConvertTochar( pszBuffer, nLength, pImage->achString, pImage->nLength );
ReleaseBufferSetLength( nLength );

return( TRUE );
}*/


#ifndef _CSTRING_BUFFER_SIZE
#define _CSTRING_BUFFER_SIZE(_CStringObj) ((_CStringObj).GetAllocLength() + 1)
#endif

void __cdecl string::Format(PCXSTR pszFormat, ... )
{
   ASSERT( __is_valid_string( pszFormat ) );

   va_list argList;
   va_start( argList, pszFormat );
   FormatV( pszFormat, argList );
   va_end( argList );
}


// append formatted data using format string 'pszFormat'
void __cdecl string::AppendFormat(PCXSTR pszFormat, ... )
{
   ASSERT( __is_valid_string( pszFormat ) );

   va_list argList;
   va_start( argList, pszFormat );

   AppendFormatV( pszFormat, argList );

   va_end( argList );
}

// Format a message using format string 'pszFormat'
void __cdecl string::format_message(PCXSTR pszFormat, ... )
{
   if(pszFormat == NULL)
      throw invalid_argument_exception();

   va_list argList;
   va_start( argList, pszFormat );

   FormatMessageV( pszFormat, &argList );

   va_end( argList );
}



bool string::load_string(::ca::application * papp, id id)
{
   return App(papp).load_string(*this, id);
}


void string::reserve(strsize res_arg)
{
   GetBufferSetLength(res_arg + 1);
}



// Convert the string to uppercase
string string::uppered() const
{

   return string(*this).make_upper();

}

// Convert the string to lowercase
string string::lowered() const
{

   return string(*this).make_lower();

}

// Convert the string to lowercase
string string::reversed() const
{

   return string(*this).MakeReverse();

}
