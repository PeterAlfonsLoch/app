#include "framework.h"


const int string::npos = -1;

strsize string_interface::get_length() const
{
   return 0;
}

void string_interface::get_string(char * psz) const
{
   *psz = '\0';
}

void string_interface::set_string(const string & str, ::action::context actioncontext)
{
   UNREFERENCED_PARAMETER(str);
   UNREFERENCED_PARAMETER(actioncontext);
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
      set_string(sz, ::action::source::op(::action::source_assign));
   }
   else
   {
      char * psz = new char[iLen + 1];
      str.get_string(psz);
      set_string(psz, ::action::source::op(::action::source_assign));
      delete [] psz;
   }
   return *this;
}

string_interface & string_interface::operator = (const char * psz)
{
   set_string(psz, ::action::source::op(::action::source_assign));
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
      string_trait::ConvertTochar( (char*)buffcharChar.get_data(), ncharCharLen+1, pszCh, 1 );
      //allocate enough characters in string and flood (replicate) with the (converted character)*nLength
      char * pszBuffer = GetBuffer( nLength*ncharCharLen );
      if (ncharCharLen == 1)
      {
         //Optimization for a common case - wide char translates to 1 ansi/wide char.
         string_trait::FloodCharacters( ((const char *)buffcharChar)[0], nLength, pszBuffer );

      } else
      {
         char* p=pszBuffer;
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

string::string(const wchar_t* pch,strsize nLength ) :
   simple_string( string_trait::GetDefaultManager() )
{
   ASSERT( nLength >= 0 );
   if( nLength > 0 )
   {
      ASSERT(__is_valid_address( pch, nLength*sizeof( wchar_t ), FALSE ) );
      if(pch == NULL)
         throw invalid_argument_exception(get_thread_app());

      strsize nDestLength = string_trait::GetcharLength( pch, nLength );
      char * pszBuffer = GetBuffer( nDestLength );
      string_trait::ConvertTochar( pszBuffer, nDestLength, pch, nLength );
      ReleaseBufferSetLength( nDestLength );
   }
}

string::string(const wchar_t* pch,strsize nLength,string_manager * pstringmanager ) :
   simple_string( pstringmanager )
{
   ASSERT( nLength >= 0 );
   if( nLength > 0 )
   {
      ASSERT( __is_valid_address( pch, nLength*sizeof( wchar_t ), FALSE ) );
      if(pch == NULL)
         throw invalid_argument_exception(get_thread_app());

      strsize nDestLength = string_trait::GetcharLength( pch, nLength );
      char * pszBuffer = GetBuffer( nDestLength );
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
//   TRACE(::axis::trace::category_String, 0, _T( "fixed_string_manager::allocate() spilling to heap.  %d chars (fixed size = %d chars)\n" ), nActualChars, nFixedChars );
::OutputDebugStringA("fixed_string_log::OnAllocateSpill");
}

void fixed_string_log::OnReallocateSpill(strsize nActualChars,strsize nFixedChars,const string_data* pData ) throw()
{
()nActualChars;
()nFixedChars;
()pData;
//   TRACE(::axis::trace::category_String, 0, _T( "fixed_string_manager::Reallocate() spilling to heap.  %d chars (fixed size = %d chars)\n" ), nActualChars, nFixedChars );
::OutputDebugStringA("fixed_string_log::OnReallocateSpill");
}

*/


char* __cdecl crt_char_traits::CharNext(const char* p ) throw()
{
   return const_cast< char* >( ::str::utf8_inc(p) );
}



int32_t __cdecl crt_char_traits::IsDigit(const char * pch ) throw()
{
   return ::str::ch::is_digit(pch) ? 1 : 0;
}

int32_t __cdecl crt_char_traits::IsSpace(const char * pch ) throw()
{
   return ::str::ch::is_whitespace( pch ) ? 1 : 0;
}



int32_t __cdecl crt_char_traits::StringCollate(const char * pszA,const char * pszB ) throw()
{
   return strcmp( reinterpret_cast< const  char* >( pszA ), reinterpret_cast< const  char* >( pszB ) );
}

int32_t __cdecl crt_char_traits::StringCollateIgnore(const char * pszA,const char * pszB ) throw()
{
   return stricmp_dup( reinterpret_cast< const  char* >( pszA ), reinterpret_cast< const  char* >( pszB ) );
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
return _mbscmp( reinterpret_cast< const uchar* >( pszA ), reinterpret_cast< const uchar* >( pszB ) );
}

strsize __cdecl crt_char_traits::StringCompareIgnore(const char * pszA,const char * pszB ) throw()
{
return _mbsicmp( reinterpret_cast< const uchar* >( pszA ), reinterpret_cast< const uchar* >( pszB ) );
}

strsize __cdecl crt_char_traits::StringCollate(const char * pszA,const char * pszB ) throw()
{
return _mbscoll( reinterpret_cast< const uchar* >( pszA ), reinterpret_cast< const uchar* >( pszB ) );
}

strsize __cdecl crt_char_traits::StringCollateIgnore(const char * pszA,const char * pszB ) throw()
{
return _mbsicoll( reinterpret_cast< const uchar* >( pszA ), reinterpret_cast< const uchar* >( pszB ) );
}

const char * __cdecl crt_char_traits::StringFindString(const char * pszBlock,const char * pszMatch ) throw()
{
return reinterpret_cast< const char * >( _mbsstr( reinterpret_cast< const uchar* >( pszBlock ),
reinterpret_cast< const uchar* >( pszMatch ) ) );
}

char * __cdecl crt_char_traits::StringFindString(char * pszBlock,const char * pszMatch ) throw()
{
return( const_cast< char * >( StringFindString( const_cast< const char * >( pszBlock ), pszMatch ) ) );
}

const char * __cdecl crt_char_traits::StringFindChar(const char * pszBlock,char chMatch ) throw()
{
return reinterpret_cast< const char * >( _mbschr( reinterpret_cast< const uchar* >( pszBlock ), (uchar)chMatch ) );
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
   //      return reinterpret_cast< const char * >( _mbsrchr( reinterpret_cast< const uchar* >( &psz[iStart] ), (uchar)ch ) );
}


const char * __cdecl crt_char_traits::StringFindStrRev(const char * psz,const char * pszFind, strsize iStart ) throw()
{
   strsize iLen = strsize(strlen(psz));
   strsize iLenFind = strsize(strlen(pszFind));
   if(iStart < 0 )
      iStart = iLen + iStart;
   if(iLenFind > iLen)
      return NULL;
   iStart = MIN(iStart, iLen - iLenFind);
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
#ifdef WINDOWSEX
   return reinterpret_cast< const char * >( _mbspbrk( reinterpret_cast< const uchar* >( pszBlock ), reinterpret_cast< const uchar* >( pszMatch ) ) );
#else
   return reinterpret_cast< const char * >( strpbrk( reinterpret_cast< const char* >( pszBlock ), reinterpret_cast< const char* >( pszMatch ) ) );
#endif
   /*while(*pszMatch != '\0')
   {
      string strUtf8Char = ::str::get_utf8_char(pszMatch);
      const char * psz = strstr(pszBlock, strUtf8Char);
      if(psz != NULL)
         return psz;
      pszMatch = ::str::utf8_inc(pszMatch);
   }
   return NULL;*/
   //return reinterpret_cast< const char * >( _mbspbrk( reinterpret_cast< const uchar* >( pszBlock ),
   // reinterpret_cast< const uchar* >( pszMatch ) ) );
}

strsize __cdecl crt_char_traits::StringSpanIncluding(const char * pszBlock,const char * pszSet ) throw()
{
   if(pszSet == NULL || pszBlock == NULL)
      return 0;
   const char * psz = pszBlock;
   const char * pszLast = NULL;
   while((psz = StringScanSet(psz, pszSet)) != NULL)
   {
      pszLast = psz;
      psz++;
   }
   if(pszLast == NULL)
      return 0;
   else
      return pszBlock - pszLast + ::str::get_utf8_char(pszLast).get_length();
   //return (strsize)_mbsspn( reinterpret_cast< const uchar* >( pszBlock ), reinterpret_cast< const uchar* >( pszSet ) );
}

strsize __cdecl crt_char_traits::StringSpanExcluding(const char * pszBlock,const char * pszSet ) throw()
{
   //   return (strsize)_mbscspn( reinterpret_cast< const uchar* >( pszBlock ), reinterpret_cast< const uchar* >( pszSet ) );
   if(pszSet == NULL || pszBlock == NULL)
      return 0;
   const char * psz = StringScanSet(pszBlock, pszSet);
   if(psz == NULL)
      return strlen(pszBlock);
   else
      return psz - pszBlock;

}

#ifdef WINDOWS
_INSECURE_DEPRECATE("You must pass an output size to crt_char_traits::StringUppercase")
#endif
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
      strFinal += ::str::ch::to_upper_case(p);
      p = (char *) ::str::utf8_inc(p);
   }
   strcpy(p, strFinal);
   return psz;


   //   return reinterpret_cast< char * >(( reinterpret_cast< uchar* >( psz ) ) );
#pragma warning (pop)
}

#if defined(WINDOWS)
_INSECURE_DEPRECATE("You must pass an output size to crt_char_traits::StringLowercase")
#endif
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
      strFinal += ::str::ch::to_lower_case(p);
      p = (char *) ::str::utf8_inc(p);
   }
   strcpy(p, strFinal);
   return psz;

   //   return reinterpret_cast< char * >( _mbslwr( reinterpret_cast< uchar* >( psz ) ) );
#pragma warning (pop)
}

char * __cdecl crt_char_traits::StringUppercase(char * psz,size_t size ) throw()
{

   ::axis::strupr_s(psz, size);

   return psz;

}

char * __cdecl crt_char_traits::StringLowercase(char * psz,size_t size ) throw()
{

   ::axis::strlwr_s(psz, size);

   return psz;

}

char * __cdecl crt_char_traits::StringReverse( char * psz ) throw()
{
   if(psz == NULL)
      return NULL;
   string strRev;
   char * p = psz + strlen(psz);
   while((p = (char*) ::str::utf8_dec(psz, p))!= NULL)
   {
      strRev += ::str::get_utf8_char(p);
   }
   strcpy(psz, strRev);
   return psz;
   //return reinterpret_cast< char * >( _mbsrev( reinterpret_cast< uchar* >( psz ) ) );
}

strsize __cdecl crt_char_traits::GetFormattedLength(const char * pszFormat, va_list args ) throw()
{

#ifdef WINDOWS

   return _vscprintf(pszFormat, args);

#else

   return vsnprintf(NULL, 0, pszFormat, args);

#endif

}

strsize __cdecl crt_char_traits::Format(char * pszBuffer,const char * pszFormat, va_list args ) throw()
{

   return vsprintf(pszBuffer, pszFormat, args);

}

strsize __cdecl crt_char_traits::Format(char * pszBuffer,size_t nlength,const char * pszFormat, va_list args ) throw()
{

#ifdef WINDOWS

   return vsprintf_s(pszBuffer, nlength, pszFormat, args);

#else

   return vsnprintf(pszBuffer, nlength, pszFormat, args);

#endif

}

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
   return ::WideCharToMultiByte( _gen_GetConversionACP(), 0, pszSource, (int32_t) nLength, NULL, 0, NULL, NULL );
}

void __cdecl crt_char_traits::ConvertTochar(char * pszDest,strsize nDestLength, const char * pszSrc, strsize nSrcLength) throw()
{
   if (nSrcLength == -1) { nSrcLength=1 + GetcharLength(pszSrc); }
   // nLen is in XCHARs
   ::axis::memcpy_s( pszDest, nDestLength*sizeof( char ),
      pszSrc, nSrcLength*sizeof( char ) );
}

void __cdecl crt_char_traits::ConvertTochar(char * pszDest,strsize nDestLength, const wchar_t * pszSrc,strsize nSrcLength) throw()
{
   // nLen is in XCHARs
   ::WideCharToMultiByte( _gen_GetConversionACP(), 0, pszSrc, (int32_t) nSrcLength, pszDest, (int32_t) nDestLength, NULL, NULL );
}

void crt_char_traits::ConvertToOem(char* pstrString) RELEASENOTHROW
{
#ifdef WINDOWSEX
   bool fSuccess=::CharToOemA(pstrString, pstrString) != 0;
   // old version can't report error
   ASSERT(fSuccess);
#endif
}

void crt_char_traits::ConvertToAnsi(char* pstrString) RELEASENOTHROW
{
#ifdef WINDOWSEX
   bool fSuccess=::OemToCharA(pstrString, pstrString) != 0;
   // old version can't report error
   ASSERT(fSuccess);
#endif
}

void __cdecl crt_char_traits::FloodCharacters(char ch,strsize nLength, char* pch ) throw()
{
   // nLength is in XCHARs
   memset( pch, ch, nLength );
}

#ifdef WINDOWS

BSTR __cdecl crt_char_traits::AllocSysString( const char* pchData, strsize nDataLength ) throw()
{

   strsize nLen = ::MultiByteToWideChar( _gen_GetConversionACP(), 0, pchData, (int32_t) nDataLength, NULL, 0 );

   BSTR bstr = ::SysAllocStringLen( NULL, (UINT) nLen );

   if( bstr != NULL )
   {
      ::MultiByteToWideChar( _gen_GetConversionACP(), 0, pchData, (int32_t) nDataLength, bstr, (int32_t) nLen);
   }

   return bstr;

}

bool __cdecl crt_char_traits::ReAllocSysString( const char* pchData,BSTR* pbstr,strsize nDataLength ) throw()
{

   strsize nLen = ::MultiByteToWideChar( _gen_GetConversionACP(), 0, pchData, (int32_t) nDataLength, NULL, 0 );

   bool bSuccess = ::SysReAllocStringLen( pbstr, NULL, (UINT) nLen ) != 0;

   if( bSuccess )
   {
      ::MultiByteToWideChar( _gen_GetConversionACP(), 0, pchData, (int32_t) nDataLength, *pbstr, (int32_t) nLen );
   }

   return bSuccess;

}

#endif

uint32_t __cdecl crt_char_traits::FormatMessage(uint32_t dwFlags, LPCVOID pSource, uint32_t dwMessageID,uint32_t dwLanguageID, char * pszBuffer, uint32_t nSize, va_list* pArguments ) throw()
{

#ifdef WINDOWS

   return ::FormatMessageA( dwFlags, pSource, dwMessageID, dwLanguageID,pszBuffer, nSize, pArguments );

#else

   return 0;

#endif



}

uint32_t __cdecl crt_char_traits::format_message(uint32_t dwFlags, LPCVOID pSource, uint32_t dwMessageID,uint32_t dwLanguageID, char * pszBuffer, uint32_t nSize, va_list* pArguments ) throw()
{

#ifdef WINDOWS

   return FormatMessage(dwFlags, pSource, dwMessageID, dwLanguageID, pszBuffer, nSize, pArguments);

#else

   return 0;

#endif

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
   return  ::str::get_utf8_char(pch).get_length();
}

uint32_t __cdecl crt_char_traits::GetEnvironmentVariable(const char * pszVar, char * pszBuffer,uint32_t dwSize )
{

#ifdef METROWIN

   throw todo(get_thread_app());

#elif defined(WINDOWSEX)

   return ::GetEnvironmentVariableA(pszVar, pszBuffer, dwSize);

#else

   return (uint32_t) strlen(strncpy(pszBuffer, getenv(pszVar), dwSize));

#endif

}


void crt_char_traits::ConvertToAnsi(char* pstrString,size_t size)
{

#ifdef WINDOWSEX

   if(size>UINT_MAX)
   {
      // API only allows uint32_t size
      throw invalid_argument_exception(get_thread_app());
   }
   uint32_t dwSize=static_cast<uint32_t>(size);
   bool fSuccess=::OemToCharBuffA(pstrString, pstrString, dwSize) != 0;
   if(!fSuccess)
   {
      throw last_error_exception(get_thread_app());
   }

#endif

}


void crt_char_traits::ConvertToOem(char* pstrString,size_t size)
{

#ifdef WINDOWSEX

   if(size>UINT_MAX)
   {
      // API only allows uint32_t size
      throw invalid_argument_exception(get_thread_app());
   }
   uint32_t dwSize=static_cast<uint32_t>(size);
   bool fSuccess=::CharToOemBuffA(pstrString, pstrString, dwSize) != 0;
   if(!fSuccess)
   {
      throw last_error_exception(get_thread_app());
   }

#endif

}






string::operator class string_composite ()
{
   class string_composite composite;
   composite.set_string(*this, ::action::source::op(::action::source_cast));
   return composite;
}

string::operator class string_composite const () const
{

   return string_composite(*this);

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
#define new AXIS_NEW

// copy constructor
string::string(const string & strSrc) :
   simple_string( strSrc, string_trait::GetDefaultManager() )
{
}

string::string(const char * pszSrc) :
   simple_string( string_trait::GetDefaultManager() )
{
   //if(!CheckImplicitLoad(pszSrc))
   //{
   // nDestLength is in XCHARs
   *this = pszSrc;
   //      }
}


string::string(char * pszSrc) :
   simple_string( string_trait::GetDefaultManager() )
{
   //if(!CheckImplicitLoad(pszSrc))
   //{
   // nDestLength is in XCHARs
   *this = (const char *) pszSrc;
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


string::string(const wchar_t* pszSrc ) :
   simple_string( string_trait::GetDefaultManager() )
{
   //      if( !CheckImplicitLoad( pszSrc ) )
   //      {
   *this = pszSrc;
   //      }
}


/*string::string(const string & str ) :
   simple_string( string_trait::GetDefaultManager() )
{

   *this = str.m_psz;

}*/


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

#ifdef METROWIN

string::string(Platform::Object ^ o) :
   simple_string(string_trait::GetDefaultManager())
{
   //      if( !CheckImplicitLoad( pszSrc ) )
   //      {
   *this = o->ToString()->Begin();
   //      }
}

string::string(Platform::Object ^ o, string_manager * pstringmanager) :
   simple_string(pstringmanager)
{
   //      if( !CheckImplicitLoad( pszSrc ) )
   //      {
   *this = o->ToString()->Begin();
   //      }
}

#endif

string::string( const uchar* pszSrc ) :
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

string::string(uchar* pszSrc ) :
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

string::string(const uchar* pszSrc,string_manager * pstringmanager ) :
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
      char * pszBuffer = GetBuffer( nLength );
      string_trait::FloodCharacters( char( ch ), nLength, pszBuffer );
      ReleaseBufferSetLength( nLength );
   }
}

string::string(strsize nLength, char ch) :
   simple_string( string_trait::GetDefaultManager() )
{
   ASSERT( nLength >= 0 );
   if( nLength > 0 )
   {
      char * pszBuffer = GetBuffer( nLength );
      string_trait::FloodCharacters( char( ch ), nLength, pszBuffer );
      ReleaseBufferSetLength( nLength );
   }

}


string::string(const char* pch,strsize nLength ) :
   simple_string( pch, nLength, string_trait::GetDefaultManager() )
{
}

string::string(const char* pch,strsize nLength,string_manager * pstringmanager ) :
   simple_string( pch, nLength, pstringmanager )
{
}

string::~string() throw()
{
}

string& string::operator=(const string_interface & str )
{
   simple_string::operator=(string(str));

   return *this;
}

/*
string& string::operator=(string strSrc )
{
   simple_string::operator=( strSrc );

   return *this;
}
*/

string& string::operator=(const char * pszSrc )
{
   simple_string::operator=( pszSrc );

   return *this;
}

string& string::operator=(const string & str)
{
   simple_string::operator=( str.c_str() );

   return *this;
}

string& string::operator=(const wchar_t * pszSrc )
{
   // nDestLength is in XCHARs
   strsize nDestLength = (pszSrc != NULL) ? string_trait::GetcharLength( pszSrc ) : 0;
   if( nDestLength > 0 )
   {
      char * pszBuffer = GetBuffer( nDestLength );
      string_trait::ConvertTochar( pszBuffer, nDestLength, pszSrc);
      ReleaseBufferSetLength( nDestLength );
   }
   else
   {
      Empty();
   }

   return *this;
}

string& string::operator=(const uchar* pszSrc )
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

   return *this;
}

string& string::operator+=(const char * pszSrc )
{
   simple_string::operator+=( pszSrc );

   return *this;
}
string& string::operator+=(const wchar_t * pszSrc )
{
   string str( pszSrc, GetManager() );

   return( operator+=( str ) );
}


string & string::operator+=(char ch )
{

   append_char((char) ch );

   return *this;

}


string & string::operator+=(uchar ch )
{

   append_char((char) ch );

   return *this;

}


string & string::operator+=(wchar_t ch )
{

   append_char((char) ch );

   return *this;

}

// Override from axis class
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

string & string::assign(strsize n, char ca)
{
   return operator = (string(ca, n));
}

string & string::assign(int32_t n, int32_t ca)
{
   return assign((uint64_t) n, (uint64_t) ca);
}

string & string::assign(int64_t n, int64_t ca)
{
   return assign((uint64_t) n, (uint64_t) ca);
}

string & string::assign(uint32_t n, uint32_t ca)
{
   return assign((uint64_t) n, (uint64_t) ca);
}

string & string::assign(uint64_t n, uint64_t ca)
{
   string strChar = ::str::uni_to_utf8(ca);
   while(n > 0)
   {
      *this += strChar;
   }
   return *this;
}



// Comparison


int32_t string::Collate(const char * psz ) const RELEASENOTHROW
{
   ASSERT( __is_valid_string( psz ) );
   return( string_trait::StringCollate( GetString(), psz ) );
}

int32_t string::CollateNoCase(const char * psz ) const RELEASENOTHROW
{
   ASSERT( __is_valid_string( psz ) );
   return( string_trait::StringCollateIgnore( GetString(), psz ) );
}

int32_t string::compare(const char * psz ) const
{
   return Compare(psz);
}

int32_t string::compare_no_case(const char * psz ) const throw()
{
   return CompareNoCase(psz);
}

int32_t string::collate(const char * psz ) const throw()
{
   return Collate(psz);
}

int32_t string::collate_no_case(const char * psz ) const throw()
{
   return CollateNoCase(psz);
}

int32_t string::compare(strsize iStart, strsize nCount, const char * psz ) const
{
   return substr(iStart, nCount).compare(psz);
}

int32_t string::compare_no_case(strsize iStart, strsize nCount, const char * psz ) const
{
   return substr(iStart, nCount).compare_no_case(psz);
}

int32_t string::collate(strsize iStart, strsize nCount, const char * psz ) const
{
   return substr(iStart, nCount).collate(psz);
}

int32_t string::collate_no_case(strsize iStart, strsize nCount, const char * psz ) const
{
   return substr(iStart, nCount).compare_no_case(psz);
}

int32_t string::compare(strsize iStart, strsize nCount, const char * psz, strsize start2, strsize count2) const
{
   return substr(iStart, nCount).compare(string(psz).substr(start2, count2));
}

int32_t string::compare_no_case(strsize iStart, strsize nCount, const char * psz, strsize start2, strsize count2) const
{
   return substr(iStart, nCount).compare_no_case(string(psz).substr(start2, count2));
}

int32_t string::collate(strsize iStart, strsize nCount, const char * psz, strsize start2, strsize count2) const
{
   return substr(iStart, nCount).collate(string(psz).substr(start2, count2));
}

int32_t string::collate_no_case(strsize iStart, strsize nCount, const char * psz, strsize start2, strsize count2) const
{
   return substr(iStart, nCount).collate_no_case(string(psz).substr(start2, count2));
}


bool string::contains(char ch, strsize iStart, strsize nCount)
{
   return find(ch, iStart, nCount) >= 0;
}

bool string::contains(wchar_t wch, strsize iStart, strsize nCount)
{
   return find_w(::str::uni_to_utf8(wch), iStart, nCount) >= 0;
}

bool string::contains(int32_t i, strsize iStart, strsize nCount) // utf8 char index
{
   return find_w(::str::uni_to_utf8(i), iStart, nCount) >= 0;
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
   return find_wci(::str::uni_to_utf8(wch), iStart, nCount) >= 0;
}

bool string::contains_ci(int32_t i, strsize iStart, strsize nCount) // utf8 char index
{
   return find_wci(::str::uni_to_utf8(i), iStart, nCount) >= 0;
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
   return find_wci(::str::uni_to_utf8(wch), iStart, nCount) >= 0;
}

bool string::contains_wci(int32_t i, strsize iStart, strsize nCount) // utf8 char index
{
   return find_wci(::str::uni_to_utf8(i), iStart, nCount) >= 0;
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

   if( (::core::add_throw(nCount, iIndex)) > nLength )
   {
      nCount = nLength-iIndex;
   }
   if( nCount > 0 )
   {
      strsize nNewLength = nLength-nCount;
      strsize nXCHARsToCopy = nLength-(iIndex+nCount)+1;
      char * pszBuffer = GetBuffer();
      ::axis::memmove_s( pszBuffer+iIndex, nXCHARsToCopy*sizeof( char ),
         pszBuffer+iIndex+nCount, nXCHARsToCopy*sizeof( char ) );
      ReleaseBufferSetLength( nNewLength );
   }

   return( get_length() );
}

strsize string::Insert(strsize iIndex,char ch )
{
   if( iIndex < 0 )
      iIndex = 0;

   if( iIndex > get_length() )
   {
      iIndex = get_length();
   }
   strsize nNewLength = get_length()+1;

   char * pszBuffer = GetBuffer( nNewLength );

   // move existing bytes down
   ::axis::memmove_s( pszBuffer+iIndex+1, (nNewLength-iIndex)*sizeof( char ),
      pszBuffer+iIndex, (nNewLength-iIndex)*sizeof( char ) );
   pszBuffer[iIndex] = ch;

   ReleaseBufferSetLength( nNewLength );

   return( nNewLength );
}

strsize string::Insert(strsize iIndex,const char * psz )
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

      char * pszBuffer = GetBuffer( nNewLength );
      // move existing bytes down
      ::axis::memmove_s( pszBuffer+iIndex+nInsertLength, (nNewLength-iIndex-nInsertLength+1)*sizeof( char ),
         pszBuffer+iIndex, (nNewLength-iIndex-nInsertLength+1)*sizeof( char ) );
      ::axis::memcpy_s( pszBuffer+iIndex, nInsertLength*sizeof( char ),
         psz, nInsertLength*sizeof( char ) );
      ReleaseBufferSetLength( nNewLength );
   }

   return( nNewLength );
}

strsize string::replace(char chOld,char chNew, strsize iStart )
{
   strsize nCount = 0;

   // int16_t-circuit the nop case
   if( chOld != chNew )
   {
      // otherwise modify each character that matches in the string
      bool bCopied = false;
      char * pszBuffer = const_cast< char * >( GetString() + iStart);  // We don't actually write to pszBuffer until we've called GetBuffer().

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

strsize string::replace(const char * pszOld, const char * pszNew, strsize iStart)
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
      const char * pszStart = GetString() + iStart;
//      const char * pszEnd = pszStart+get_length();
      const char * pszTarget;
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

      char * pszBuffer = GetBuffer( __max( nNewLength, nOldLength ) );

      char * pszStart = pszBuffer + iStart;
      char * pszEnd = pszBuffer+nOldLength;

      // loop again to actually do the work
      while( pszStart < pszEnd )
      {
         char * pszTarget;
         while( (pszTarget = string_trait::StringFindString( pszStart, pszOld ) ) != NULL )
         {
            strsize nBalance = nOldLength-strsize(pszTarget-pszBuffer+nSourceLen);
            ::axis::memmove_s( pszTarget+nReplacementLen, nBalance*sizeof( char ),
               pszTarget+nSourceLen, nBalance*sizeof( char ) );
            ::axis::memcpy_s( pszTarget, nReplacementLen*sizeof( char ),
               pszNew, nReplacementLen*sizeof( char ) );
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

string & string::replace(strsize iStart,strsize nCount,const char * psz, strsize nSubLen)
{
   if(nCount < 0)
   {
      return operator = (Left(iStart) + string(psz,nSubLen));
   }
   else
   {
      return operator = (Left(iStart) + string(psz,nSubLen) + Mid(nCount));
   }
}

strsize string::remove(char chRemove )
{
   strsize nLength = get_length();
   char * pszBuffer = GetBuffer( nLength );

   char * pszSource = pszBuffer;
   char * pszDest = pszBuffer;
   char * pszEnd = pszBuffer+nLength;

   while( pszSource < pszEnd )
   {
      char * pszNewSource = pszSource + 1;
      if(*pszSource != chRemove)
      {
         // copy the source to the destination.  Remember to copy all bytes of an MBCS character
         // copy the source to the destination.  Remember to copy all bytes of an MBCS character
         size_t NewSourceGap = (pszNewSource-pszSource);
         char * pszNewDest = pszDest + NewSourceGap;
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

string string::Tokenize(const char * pszTokens, strsize& iStart ) const
{
   ASSERT( iStart >= 0 );

   if(iStart < 0)
      throw invalid_argument_exception(get_thread_app());

   if( (pszTokens == NULL) || (*pszTokens == (char)0) )
   {
      if (iStart < get_length())
      {
         return( string( GetString()+iStart, GetManager() ) );
      }
   }
   else
   {
      const char * pszPlace = GetString()+iStart;
      const char * pszEnd = GetString()+get_length();
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
   iStart = npos;

   return( string( GetManager() ) );
}

// find routines

// find the first occurrence of character 'ch', starting at strsize 'iStart'
strsize string::find(char ch,strsize iStart, strsize nCount) const RELEASENOTHROW
{
   // iStart is in XCHARs
   ASSERT( iStart >= 0 );

   // nLength is in XCHARs
   strsize nLength = get_length();
   if( iStart < 0 || iStart >= nLength)
   {
      return npos;
   }

   if(nCount < 0)
      nCount = nLength;

   if(nCount + iStart > nLength)
      nCount = nLength - iStart;

   if(nCount < 0)
      return npos;

   const char * psz = GetString() + iStart;
   for(int32_t i = 0; i < nCount; i++)
   {
      if(psz[i] == ch)
      {
         return iStart + i;
      }
   }
   return npos;
}

// find the first occurrence of character 'ch', starting at strsize 'iStart'
strsize string::find_ci(char ch,strsize iStart, strsize nCount) const RELEASENOTHROW
{
   // iStart is in XCHARs
   ASSERT( iStart >= 0 );

   // nLength is in XCHARs
   strsize nLength = get_length();
   if( iStart < 0 || iStart >= nLength)
   {
      return( npos );
   }

   if(nCount < 0)
      nCount = nLength;

   if(nCount + iStart > nLength)
      nCount = nLength - iStart;

   if(nCount < 0)
      return npos;

   const char * psz = GetString() + iStart;
   for(int32_t i = 0; i < nCount; i++)
   {
      if(tolower(psz[i]) == tolower(ch))
      {
         return iStart + i;
      }
   }
   return npos;
}

strsize string::find_first_of(char ch,strsize iStart) const RELEASENOTHROW
{
   return find(ch, iStart);
}
// look for a specific sub-string

// find the first occurrence of string 'pszSub', starting at strsize 'iStart'
strsize string::find(const char * pszSub,strsize iStart, strsize nCount, const char ** pszTail) const RELEASENOTHROW
{
   // iStart is in XCHARs
   ASSERT( iStart >= 0 );
   ASSERT( __is_valid_string( pszSub ) );

   if(pszSub == NULL)
   {
      return( npos );
   }
   // nLength is in XCHARs
   strsize nLength = get_length();
   if( iStart < 0 || iStart > nLength )
   {
      return( npos );
   }

   strsize nLength2 = strlen(pszSub);

   if(nCount < 0)
      nCount = nLength;

   if(nCount + iStart + nLength2 > nLength)
      nCount = nLength  - iStart - nLength2;

   if(nCount < 0)
      return npos;

   const char * psz = GetString() + iStart;
   for(int32_t i = 0; i <= nCount; i++)
   {
      bool bFound = true;
      int32_t j;
      for(j = 0; j < nLength2; j++)
      {
         if(psz[j] != pszSub[j])
         {
            bFound = false;
            break;
         }
      }
      if(bFound && j == nLength2)
      {
         if(pszTail)
            *pszTail = &psz[j];
         return i + iStart;
      }
      psz++;
   }
   return npos;
}

// find the first occurrence of string 'pszSub', starting at strsize 'iStart'
strsize string::find_ci(const char * pszSub,strsize iStart,strsize nCount,const char ** pszTail) const RELEASENOTHROW
{
   // iStart is in XCHARs
   ASSERT( iStart >= 0 );
   ASSERT( __is_valid_string( pszSub ) );

   if(pszSub == NULL)
   {
      return( npos );
   }
   // nLength is in XCHARs
   strsize nLength = get_length();
   if( iStart < 0 || iStart > nLength )
   {
      return( npos );
   }

   strsize nLength2 = strlen(pszSub);

   if(nCount < 0)
      nCount = nLength;

   if(nCount + iStart + nLength2 > nLength)
      nCount = nLength  - iStart - nLength2;

   if(nCount < 0)
      return npos;

   int32_t j;

   const char * psz = GetString() + iStart;
   for(int32_t i = 0; i <= nCount; i++)
   {
      bool bFound = true;
      for(j = 0; j < nLength2; j++)
      {
         if(tolower(psz[j]) != tolower(pszSub[j]))
         {
            bFound = false;
            break;
         }
      }
      if(bFound)
      {
         if(pszTail)
            *pszTail = &psz[j];
         return i + iStart;
      }
      psz++;
   }
   return npos;
}

// find the first occurrence of string 'pszSub', starting at strsize 'iStart'
strsize string::find_w(const char * pszSub,strsize iStart,strsize nCount,const char ** pszTail) const RELEASENOTHROW
{
   // iStart is in XCHARs
   ASSERT( iStart >= 0 );
   ASSERT( __is_valid_string( pszSub ) );

   if(pszSub == NULL)
   {
      return( npos );
   }

   if(iStart < 0)
      return npos;

   const char * psz = GetString() + iStart;

   if(*psz == '\0')
      return npos;
   while(*psz != '\0' && (psz - GetString() - iStart) < nCount)
   {
      bool bFound = true;
      const char * psz2 = psz;
      const char * pszSub2 = pszSub;
      while(*psz2 != '\0' && *pszSub2 != '\0')
      {
         if(::str::get_utf8_char(psz2) != ::str::get_utf8_char(pszSub2))
         {
            bFound = false;
            break;
         }
         psz2 = ::str::utf8_inc(psz2);
         pszSub2 = ::str::utf8_inc(pszSub2);
      }
      if(bFound)
      {
         if(*pszSub2 == '\0')
         {
            if(pszTail)
               *pszTail = psz2;
            return psz - GetString();
         }
         else
         {
            return npos;
         }
      }
      psz++;
   }
   return npos;
}

// find the first occurrence of string 'pszSub', starting at strsize 'iStart'
strsize string::find_wci(const char * pszSub,strsize iStart,strsize nCount,const char ** pszTail) const RELEASENOTHROW
{
   // iStart is in XCHARs
   ASSERT( iStart >= 0 );
   ASSERT( __is_valid_string( pszSub ) );

   if(pszSub == NULL)
   {
      return( npos );
   }

   if(iStart < 0)
      return npos;

   const char * psz = GetString() + iStart;

   if(*psz == '\0')
      return npos;
   while(*psz != '\0' && (psz - GetString() - iStart) < nCount)
   {
      bool bFound = true;
      const char * psz2 = psz;
      const char * pszSub2 = pszSub;
      while(*psz2 != '\0' && *pszSub2 != '\0')
      {
         if(::str::ch::to_lower_case(psz2) != ::str::ch::to_lower_case(pszSub2))
         {
            bFound = false;
            break;
         }
         psz2 = ::str::utf8_inc(psz2);
         pszSub2 = ::str::utf8_inc(pszSub2);
      }
      if(bFound)
      {
         if(*pszSub2 == '\0')
         {
            if(pszTail)
               *pszTail = psz2;
            return psz - GetString();
         }
         else
         {
            return npos;
         }
      }
      psz++;
   }
   return npos;
}


strsize string::find_tail(const char * pszSub,strsize start,strsize count) const RELEASENOTHROW
{

   const char * pszTail = NULL;

   if(find(pszSub,start,count,&pszTail) < 0)
      return npos;

   return pszTail - m_pszData;

}


strsize string::find_w_tail(const char * pszSub,strsize start,strsize count) const RELEASENOTHROW
{

   const char * pszTail = NULL;

   if(find_w(pszSub,start,count,&pszTail) < 0)
      return npos;

   return pszTail - m_pszData;

}


strsize string::find_ci_tail(const char * pszSub,strsize start,strsize count) const RELEASENOTHROW
{

   const char * pszTail = NULL;

   if(find_ci(pszSub,start,count,&pszTail) < 0)
      return npos;

   return pszTail - m_pszData;

}


strsize string::find_wci_tail(const char * pszSub,strsize start,strsize count) const RELEASENOTHROW
{

   const char * pszTail = NULL;

   if(find_wci(pszSub,start,count,&pszTail) < 0)
      return npos;

   return pszTail - m_pszData;

}


// find the first occurrence of any of the characters in string 'pszCharSet'
strsize string::FindOneOf(const char * pszCharSet, strsize iStart, strsize n) const RELEASENOTHROW
{
   string strCharSet(pszCharSet, n);
   // iStart is in XCHARs
   ASSERT( iStart >= 0 );

   // nLength is in XCHARs
   strsize nLength = get_length();
   if( iStart < 0 || iStart >= nLength)
   {
      return( npos );
   }
   const char * psz = string_trait::StringScanSet( &GetString()[iStart], strCharSet );
   return( (psz == NULL) ? npos : strsize( psz-GetString() ) );
}

strsize string::find_first_of(const char * pszCharSet, strsize iStart) const RELEASENOTHROW
{
   return FindOneOf(pszCharSet, iStart, npos);
}

strsize string::find_first_of(const char * pszCharSet, strsize iStart, strsize n) const RELEASENOTHROW
{
   return FindOneOf(pszCharSet, iStart, n);
}

strsize string::find_first_of(const string & strCharSet, strsize pos) const RELEASENOTHROW
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

strsize string::find_first_not_of(char ca, strsize pos) const
{
   strsize nLength = get_length();

   if(pos < 0 || pos >= nLength)
      return npos;
   const char * psz = &GetString()[pos];
   while(*psz != '\0' && *psz == ca)
   {
      psz++;
   }
   if(*psz == '\0')
      return npos;
   else
      return psz - GetString();
}

strsize string::find_first_not_of(const char* s, strsize pos, strsize n ) const
{
   string strChars(s, n);

   strsize nLength = get_length();

   if(pos < 0 || pos >= nLength)
      return npos;
   const char * psz = &GetString()[pos];
   while(*psz != '\0' && strChars.contains(*psz))
   {
      psz++;
   }
   if(*psz == '\0')
      return npos;
   else
      return psz - GetString();
}


// find the first occurrence of any of the characters in string 'pszCharSet'
strsize string::find_last_of(char ca, strsize pos) const RELEASENOTHROW
{
   strsize nLength = get_length();
   // nLength is in XCHARs
   if(pos < 0)
      pos = nLength - 1;
   if(pos < 0 || pos >= nLength)
   {
      return( npos );
   }
   const char * psz = GetString();
   while(pos >= 0 && psz[pos] != ca)
   {
      pos--;
   }
   return pos;
}

strsize string::find_last_of(const char * pszCharSet, strsize iStart) const RELEASENOTHROW
{
   return find_last_of(pszCharSet, iStart, npos);
}

strsize string::find_last_of(const char * pszCharSet, strsize pos, strsize n) const RELEASENOTHROW
{
   strsize nLength = get_length();
   // nLength is in XCHARs
   if(pos < 0)
      pos = nLength - 1;
   if(pos < 0 || pos >= nLength)
   {
      return( npos );
   }
   string strChars(pszCharSet, n);
   const char * psz = GetString();
   while(pos >= 0 && !strChars.contains(psz[pos]))
   {
      pos--;
   }
   return pos;
}

strsize string::find_last_of(const string & strCharSet, strsize pos) const RELEASENOTHROW
{
   return find_last_of(strCharSet, pos, strCharSet.get_length());
}


// find the first occurrence of any of the characters in string 'pszCharSet'
strsize string::find_last_not_of(char ca, strsize pos) const RELEASENOTHROW
{
   strsize nLength = get_length();
   // nLength is in XCHARs
   if(pos < 0)
      pos = nLength - 1;
   if(pos < 0 || pos >= nLength)
   {
      return( npos );
   }
   const char * psz = GetString();
   while(pos >= 0 && psz[pos] == ca)
   {
      pos--;
   }
   return pos;
}

strsize string::find_last_not_of(const char * pszCharSet, strsize iStart) const RELEASENOTHROW
{
   return find_last_not_of(pszCharSet, iStart, npos);
}

strsize string::find_last_not_of(const char * pszCharSet, strsize pos, strsize n) const RELEASENOTHROW
{
   strsize nLength = get_length();
   // nLength is in XCHARs
   if(pos < 0)
      pos = nLength - 1;
   if(pos < 0 || pos >= nLength)
   {
      return( npos );
   }
   string strChars(pszCharSet, n);
   const char * psz = GetString();
   while(pos >= 0 && strChars.contains(psz[pos]))
   {
      pos--;
   }
   return pos;
}

strsize string::find_last_not_of(const string & strCharSet, strsize pos) const RELEASENOTHROW
{
   return find_last_not_of(strCharSet, pos, strCharSet.get_length());
}


// find the last occurrence of character 'ch'
strsize string::reverse_find(char ch, strsize iStart) const RELEASENOTHROW
{
   // find last single character
   const char * psz = string_trait::StringFindCharRev( GetString(), ch, iStart );

   // return npos if not found, distance from beginning otherwise
   return( (psz == NULL) ? npos : strsize( psz-GetString() ) );
}

// find the last occurrence of character 'ch'
strsize string::reverse_find( const char * ch, strsize iStart) const RELEASENOTHROW
{
   // find last single character
   const char * psz = string_trait::StringFindStrRev( GetString(), ch, iStart );

   // return npos if not found, distance from beginning otherwise
   return( (psz == NULL) ? npos : strsize( psz-GetString() ) );
}

// manipulation

// Convert the string to uppercase
string& string::make_upper()
{
   strsize nLength = get_length();
   char * pszBuffer = GetBuffer( nLength );
   string_trait::StringUppercase( pszBuffer, nLength+1 );
   ReleaseBufferSetLength( nLength );

   return *this;
}

// Convert the string to lowercase
string& string::make_lower()
{
   strsize nLength = get_length();
   char * pszBuffer = GetBuffer( nLength );
   string_trait::StringLowercase( pszBuffer, nLength+1 );
   ReleaseBufferSetLength( nLength );

   return *this;
}

// Reverse the string
string& string::MakeReverse()
{
   strsize nLength = get_length();
   char * pszBuffer = GetBuffer( nLength );
   string_trait::StringReverse( pszBuffer );
   ReleaseBufferSetLength( nLength );

   return *this;
}

// trimming

// remove all trailing whitespace
string& string::trim_right()
{

   const char * pszLast = NULL;
   const char * pszMax = GetString() + get_length();
   const char * psz = pszMax;

   if(psz != NULL)
   {
      while(true)
      {
         psz = ::str::utf8_dec(GetString(), psz);
         if(psz < GetString())
            break;
         if(!string_trait::IsSpace(psz))
         {
            pszLast = ::str::__utf8_inc(psz);
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

   return *this;

}

// remove all leading whitespace
string& string::trim_left()
{
   // find first non-space character

   const char * psz = GetString();

   while( string_trait::IsSpace( psz ) )
   {
      psz = string_trait::CharNext( psz );
   }

   if( psz != GetString() )
   {
      // fix up data and length
      strsize iFirst = strsize( psz-GetString() );
      char * pszBuffer = GetBuffer( get_length() );
      psz = pszBuffer+iFirst;
      strsize nDataLength = get_length()-iFirst;
      ::axis::memmove_s( pszBuffer, (nDataLength+1)*sizeof( char ),
         psz, (nDataLength+1)*sizeof( char ) );
      ReleaseBufferSetLength( nDataLength );
   }

   return *this;
}

// remove all leading and trailing whitespace
string& string::trim()
{
   return( trim_right().trim_left() );
}

// remove all leading and trailing occurrences of character 'chTarget'
string& string::trim(char chTarget )
{
   return( trim_right( chTarget ).trim_left( chTarget ) );
}

// remove all leading and trailing occurrences of any of the characters in the string 'pszTargets'
string& string::trim(const char * pszTargets )
{
   return( trim_right( pszTargets ).trim_left( pszTargets ) );
}

// trimming anything (either side)

// remove all trailing occurrences of character 'chTarget'
string& string::trim_right(char chTarget )
{
   // find beginning of trailing matches
   // by starting at beginning (DBCS aware)

   const char * psz = GetString();
   const char * pszLast = NULL;

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

   return *this;
}

// remove all trailing occurrences of any of the characters in string 'pszTargets'
string& string::trim_right(const char * pszTargets )
{
   // if we're not trimming anything, we're not doing any work
   if( (pszTargets == NULL) || (*pszTargets == 0) )
   {
      return *this;
   }

   // find beginning of trailing matches
   // by starting at beginning (DBCS aware)

   const char * psz = GetString();
   const char * pszLast = NULL;

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

   return *this;
}

// remove all leading occurrences of character 'chTarget'
string& string::trim_left(char chTarget )
{
   // find first non-matching character
   const char * psz = GetString();

   while( chTarget == *psz )
   {
      psz = string_trait::CharNext( psz );
   }

   if( psz != GetString() )
   {
      // fix up data and length
      strsize iFirst = strsize( psz-GetString() );
      char * pszBuffer = GetBuffer( get_length() );
      psz = pszBuffer+iFirst;
      strsize nDataLength = get_length()-iFirst;
      ::axis::memmove_s( pszBuffer, (nDataLength+1)*sizeof( char ),
         psz, (nDataLength+1)*sizeof( char ) );
      ReleaseBufferSetLength( nDataLength );
   }

   return *this;
}

// remove all leading occurrences of any of the characters in string 'pszTargets'
string& string::trim_left(const char * pszTargets )
{
   // if we're not trimming anything, we're not doing any work
   if( (pszTargets == NULL) || (*pszTargets == 0) )
   {
      return *this;
   }

   const char * psz = GetString();
   while( (*psz != 0) && (string_trait::StringFindChar( pszTargets, *psz ) != NULL) )
   {
      psz = string_trait::CharNext( psz );
   }

   if( psz != GetString() )
   {
      // fix up data and length
      strsize iFirst = strsize( psz-GetString() );
      char * pszBuffer = GetBuffer( get_length() );
      psz = pszBuffer+iFirst;
      strsize nDataLength = get_length()-iFirst;
      ::axis::memmove_s( pszBuffer, (nDataLength+1)*sizeof( char ),
         psz, (nDataLength+1)*sizeof( char ) );
      ReleaseBufferSetLength( nDataLength );
   }

   return *this;
}


// remove all trailing whitespace
string string::right_trimmed() const
{

   string str(*this);

   str.trim_right();

   return str;

}


// remove all leading whitespace
string string::left_trimmed() const
{

   string str(*this);

   str.trim_left();

   return str;

}


// remove all leading and trailing whitespace
string string::trimmed() const
{

   string str(*this);

   str.trim();

   return str;

}


// remove all leading and trailing occurrences of character 'chTarget'
string string::trimmed(char chTarget) const
{

   string str(*this);

   str.trim(chTarget);

   return str;

}


// remove all leading and trailing occurrences of any of the characters in the string 'pszTargets'
string string::trimmed(const char * pszTargets) const
{

   string str(*this);

   str.trim(pszTargets);

   return str;

}


// trimming anything (either side)

// remove all trailing occurrences of character 'chTarget'
string string::right_trimmed(char chTarget) const
{

   string str(*this);

   str.trim_right(chTarget);

   return str;

}


// remove all trailing occurrences of any of the characters in string 'pszTargets'
string string::right_trimmed(const char * pszTargets) const
{

   string str(*this);

   str.trim_right(pszTargets);

   return str;

}


// remove all leading occurrences of character 'chTarget'
string string::left_trimmed(char chTarget) const
{

   string str(*this);

   str.trim_left(chTarget);

   return str;

}


// remove all leading occurrences of any of the characters in string 'pszTargets'
string string::left_trimmed(const char * pszTargets) const
{

   string str(*this);

   str.trim_left(pszTargets);

   return str;

}


// Convert the string to the OEM character set
void string::AnsiToOem()
{
   strsize nLength = get_length();
   char * pszBuffer = GetBuffer( nLength );
   string_trait::ConvertToOem( pszBuffer, nLength+1 );
   ReleaseBufferSetLength( nLength );
}

// Convert the string to the ANSI character set
void string::OemToAnsi()
{
   strsize nLength = get_length();
   char * pszBuffer = GetBuffer( nLength );
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

   if( (::core::add_throw(iFirst,nCount)) > get_length() )
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
      return *this;
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
      return *this;
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
      return *this;
   }

   return( string( GetString(), nCount, GetManager() ) );
}

// Return the substring consisting of the leftmost characters in the set 'pszCharSet'
string string::SpanIncluding(const char * pszCharSet ) const
{
   ASSERT( __is_valid_string( pszCharSet ) );
   if(pszCharSet == NULL)
      throw invalid_argument_exception(get_thread_app());

   return( Left( string_trait::StringSpanIncluding( GetString(), pszCharSet ) ) );
}

// Return the substring consisting of the leftmost characters not in the set 'pszCharSet'
string string::SpanExcluding(const char * pszCharSet ) const
{
   ASSERT( __is_valid_string( pszCharSet ) );
   if(pszCharSet == NULL)
      throw invalid_argument_exception(get_thread_app());

   return( Left( string_trait::StringSpanExcluding( GetString(), pszCharSet ) ) );
}

void string::AppendFormatV(const char * pszFormat, va_list args )
{

   ASSERT( __is_valid_string( pszFormat ) );

   strsize nCurrentLength = get_length();

   strsize nAppendLength = string_trait::GetFormattedLength( pszFormat, args );

   char * pszBuffer = GetBuffer( nCurrentLength+nAppendLength );
#if _SECURE_TEMPLATE
   string_trait::Format( pszBuffer+nCurrentLength,
      nAppendLength+1, pszFormat, args );
#else
   string_trait::Format( pszBuffer+nCurrentLength, pszFormat, args );
#endif
   ReleaseBufferSetLength( nCurrentLength+nAppendLength );


}

void string::FormatV(const char * pszFormat, va_list args )
{

   ASSERT( __is_valid_string( pszFormat ) );

   if(pszFormat == NULL)
      throw invalid_argument_exception(get_thread_app());

  strsize nLength = string_trait::GetFormattedLength( pszFormat, args );
   char * pszBuffer = GetBuffer( nLength );
#if _SECURE_TEMPLATE
   string_trait::Format( pszBuffer, nLength+1, pszFormat, args );
#else
   string_trait::Format( pszBuffer, pszFormat, args );
#endif
   ReleaseBufferSetLength( nLength );

}

// Format a message using format string 'pszFormat' and va_list
void string::FormatMessageV(const char * pszFormat, va_list* pArgList )
{

#ifdef WINDOWSEX

   // format message into temporary buffer pszTemp

   char * pszTemp;

   uint32_t dwResult = string_trait::FormatMessage( FORMAT_MESSAGE_FROM_STRING | FORMAT_MESSAGE_ALLOCATE_BUFFER, pszFormat, 0, 0, reinterpret_cast< char * >( &pszTemp ), 0, pArgList );

   if(dwResult == 0)
   {

      throw_memory_exception();

   }

   *this = pszTemp;

   LocalFree(pszTemp);

#else


   FormatV(pszFormat, *pArgList);

#endif

}

#ifdef WINDOWS

// OLE BSTR support

// allocate a BSTR containing a copy of the string
BSTR string::AllocSysString() const
{
   BSTR bstrResult = string_trait::AllocSysString( GetString(), get_length() );
   if( bstrResult == NULL )
   {
      throw_memory_exception();
   }
   return( bstrResult );
}

BSTR string::SetSysString(BSTR* pbstr ) const
{
   ASSERT( __is_valid_address( pbstr, sizeof( BSTR ) ) );

   if( !string_trait::ReAllocSysString( GetString(), pbstr,
      get_length() ) )
   {
      throw_memory_exception();
   }
   ASSERT( *pbstr != NULL );
   return( *pbstr );
}

#endif

// set the string to the value of environment var 'pszVar'
bool string::GetEnvironmentVariable(const char * pszVar )
{

   uint32_t nLength = string_trait::GetEnvironmentVariable( pszVar, NULL, 0 );
   bool bRetVal = FALSE;

   if( nLength == 0 )
   {
      Empty();
   }
   else
   {
      char * pszBuffer = GetBuffer( nLength );
      string_trait::GetEnvironmentVariable( pszVar, pszBuffer, nLength );
      ReleaseBuffer();
      bRetVal = TRUE;
   }

   return( bRetVal );

}

bool string::getenv(const char * pszVar)
{

   return GetEnvironmentVariable(pszVar);

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
char * pszBuffer = GetBuffer( nLength );
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
char * pszBuffer = GetBuffer( nLength );
string_trait::ConvertTochar( pszBuffer, nLength, pImage->achString, pImage->nLength );
ReleaseBufferSetLength( nLength );

return( TRUE );
}*/


#ifndef _CSTRING_BUFFER_SIZE
#define _CSTRING_BUFFER_SIZE(_CStringObj) ((_CStringObj).GetAllocLength() + 1)
#endif

#ifdef WINDOWS

void __cdecl string::Format(const char * pszFormat, ... )
{
   ASSERT( __is_valid_string( pszFormat ) );

   va_list argList;
   va_start( argList, pszFormat );
   FormatV( pszFormat, argList );
   va_end( argList );
}


// append formatted data using format string 'pszFormat'
void __cdecl string::AppendFormat(const char * pszFormat, ... )
{
   ASSERT( __is_valid_string( pszFormat ) );

   va_list argList;
   va_start( argList, pszFormat );

   AppendFormatV( pszFormat, argList );

   va_end( argList );
}

// Format a message using format string 'pszFormat'
void __cdecl string::format_message(const char * pszFormat, ... )
{
   if(pszFormat == NULL)
      throw invalid_argument_exception(get_thread_app());

   va_list argList;
   va_start( argList, pszFormat );

   FormatMessageV( pszFormat, &argList );

   va_end( argList );
}

#endif

bool string::load_string(sp(::axis::application) papp, id id)
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


string string::utf8_substr(strsize iFirst) const
{

   return utf8_substr(iFirst, npos);

}

string string::utf8_substr(strsize iFirst, strsize nCount) const
{

   const char * pchStart = *this;

   if(pchStart == NULL)
      return "";

   ::count iUtf8Len = utf8_get_length();

   if(iFirst < 0 )
      iFirst = iUtf8Len + iFirst;

   if(nCount < 0)
      nCount = iUtf8Len - iFirst + nCount + 1;

   if(iFirst + nCount > iUtf8Len)
      nCount = iUtf8Len - iFirst;

   if(nCount <= 0)
      return "";

   ::count ca = 0;

   while(ca < iFirst && *pchStart != '\0')
   {

      pchStart = ::str::__utf8_inc(pchStart);

      ca++;

   }

   if(*pchStart ==  '\0')
      return "";

   const char * pchEnd = pchStart;

   ca = 0;

   while(ca < nCount && *pchEnd != '\0')
   {

      pchEnd = ::str::__utf8_inc(pchEnd);

      ca++;

   }

   return string(pchStart, pchEnd - pchStart);


}

::count string::utf8_get_length() const
{

   const char * pch = *this;

   if(pch == NULL)
      return 0;

   ::count ca = 0;

   while(*pch != '\0')
   {

      pch = ::str::__utf8_inc(pch);

      ca++;

   }

   return ca;

}



bool string::begins_ci(const char * s) const
{
   return ::str::begins_ci(*this, s);
}
