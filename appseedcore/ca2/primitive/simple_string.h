#pragma once

namespace gen
{
   namespace str
   {
      CLASS_DECL_ca inline void copy(char * pszDest, const char * pszSrc) { strcpy(pszDest, pszSrc); }
      CLASS_DECL_ca inline void copy(wchar_t * pszDest, const wchar_t * pszSrc) { wcscpy(pszDest, pszSrc); }
   } // namespace str
} // namespace gen


#include "template/definition.h"
#include "template/core.h"
//#include "template/trace.h"
#include "template/exception.h"

CLASS_DECL_ca void throw_error_exception(const char * psz);

/*namespace gen
{

   namespace international
   {
      
      CLASS_DECL_ca int          UnicodeToMultiByteCount(UINT uiCodePage, const wchar_t * lpcsz);
      CLASS_DECL_ca bool         UnicodeToMultiByte(UINT uiCodePage, char * lpstrMultiByte, int nCount, const wchar_t * lpcsz);
      CLASS_DECL_ca const char * UnicodeToMultiByte(UINT uiCodePage, const wchar_t * lpcsz);
      CLASS_DECL_ca 
      inline const char * _001GetUtf8(const char * psz)
      {
         return _strdup(psz);
      }
      inline const char * _001GetUtf8(const wchar_t * psz)
      {
         return UnicodeToMultiByte(CP_UTF8, psz); 
      }
   }
}*/


extern "C"
{
   LONG __cdecl _InterlockedIncrement( LONG volatile * pn );
   LONG __cdecl _InterlockedDecrement( LONG volatile * pn );
};
   
#pragma intrinsic( _InterlockedIncrement )
#pragma intrinsic( _InterlockedDecrement )
   
      struct string_data;
      
      class CLASS_DECL_ca string_manager_interface
      {
   public:
      // allocate a new string_data
      virtual string_data * allocate( int nAllocLength, int nCharSize ) = 0;
      // Free an existing string_data
      virtual void Free( string_data * pData ) = 0;
      // Change the size of an existing string_data
      virtual string_data * Reallocate( string_data * pData, int nAllocLength, int nCharSize ) = 0;
      // get the string_data for a Nil string
      virtual string_data * GetNilString() = 0;
      virtual string_manager_interface* Clone() = 0;
      };
      
#ifdef _M_IX86
#ifndef _M_CEE
#define _AtlInterlockedIncrement _InterlockedIncrement
#define _AtlInterlockedDecrement _InterlockedDecrement
#else
#define _AtlInterlockedIncrement InterlockedIncrement
#define _AtlInterlockedDecrement InterlockedDecrement
      /* managed code must use the non-intrinsics */
#ifdef InterlockedIncrement
#undef InterlockedIncrement
#endif
#ifdef InterlockedDecrement
#undef InterlockedDecrement
#endif
#endif  // !_M_CEE
#else
#define _AtlInterlockedIncrement InterlockedIncrement
#define _AtlInterlockedDecrement InterlockedDecrement
#endif  // _M_IX86_
      
      struct CLASS_DECL_ca string_data
      {
         string_manager_interface * pstringmanager;  // string manager for this string_data
         int nDataLength;  // Length of currently used data in XCHARs (not including terminating null)
         int nAllocLength;  // Length of allocated data in XCHARs (not including terminating null)
         long nRefs;     // Reference count: negative == locked
         // XCHAR data[nAllocLength+1]  // A string_data is always followed in primitive::memory by the actual base_array of character data
         
         char * data() NOTHROW
         {
            return reinterpret_cast < char *> (this+1);
         }
         
         void AddRef() NOTHROW
         {
            ATLASSERT(nRefs > 0);
            _AtlInterlockedIncrement(&nRefs);
         }
         bool IsLocked() const NOTHROW
         {
            return nRefs < 0;
         }
         bool IsShared() const NOTHROW
         {
            return( nRefs > 1 ); 
         }
         void Lock() NOTHROW
         {
            ATLASSERT( nRefs <= 1 );
            nRefs--;  // Locked buffers can't be shared, so no interlocked operation necessary
            if( nRefs == 0 )
            {
               nRefs = -1;
            }
         }
         void Release() NOTHROW
         {
            ATLASSERT( nRefs != 0 );
            
            if( _AtlInterlockedDecrement( &nRefs ) <= 0 )
            {
               pstringmanager->Free( this );
            }
         }
         void Unlock() NOTHROW
         {
            ATLASSERT( IsLocked() );
            
            if(IsLocked())
            {
               nRefs++;  // Locked buffers can't be shared, so no interlocked operation necessary
               if( nRefs == 0 )
               {
                  nRefs = 1;
               }
            }
         }
      };
      










   class CLASS_DECL_ca nil_string_data :
      public string_data
      {
   public:
      nil_string_data() NOTHROW
      {
         pstringmanager = NULL;
         nRefs = 2;  // Never gets freed by string_manager_interface
         nDataLength = 0;
         nAllocLength = 0;
         achNil[0] = 0;
         achNil[1] = 0;
      }
      
      void SetManager(string_manager_interface * pMgr ) NOTHROW
      {
         ATLASSERT( pstringmanager == NULL );
         pstringmanager = pMgr;
      }
      
      
      
   public:
      wchar_t achNil[2];
      };
      














      template< const int t_nSize >
         class static_string
      {
   public:
      static_string(const char* psz ) :
         m_psz( psz )
         {
         }
         
         operator const char*() const
         {
            return m_psz;
         }
         
         static int __cdecl get_length() 
         {
            return (t_nSize/sizeof( char ))-1;
         }
         
   private:
      const char* m_psz;
      
   private:
      static_string( const static_string& str ) NOTHROW;
      static_string& operator=( const static_string& str ) NOTHROW;
      };
   







#define _ST( psz ) _template::static_string< char, sizeof( _T( psz ) ) >( _T( psz ) )
#define _SA( psz ) _template::static_string< char, sizeof( psz ) >( psz )
#define _SW( psz ) _template::static_string< wchar_t, sizeof( L##psz ) >( L##psz )
#define _SO( psz ) _SW( psz )
      
   class CLASS_DECL_ca char_traits_base
   {
   public:
      typedef char XCHAR;
      typedef char * PXSTR;
      typedef const char * PCXSTR;
      typedef wchar_t YCHAR;
      typedef wchar_t * PYSTR;
      typedef const wchar_t * PCYSTR;
   };
      
      
      
























      class string_buffer;


      class CLASS_DECL_ca simple_string
      {
   public:
      typedef char_traits_base::XCHAR XCHAR;
      typedef char_traits_base::PXSTR PXSTR;
      typedef char_traits_base::PCXSTR PCXSTR;
      typedef char_traits_base::YCHAR YCHAR;
      typedef char_traits_base::PYSTR PYSTR;
      typedef char_traits_base::PCYSTR PCYSTR;
      
   public:
      explicit simple_string(string_manager_interface * pstringmanager )
      {
         construct(pstringmanager);
      }
      
      void construct(string_manager_interface * pstringmanager)
      {
         ATLENSURE( pstringmanager != NULL );
         string_data * pData = pstringmanager->GetNilString();
         Attach( pData );
      }
      
      simple_string(const simple_string & strSrc )
      {
         string_data* pSrcData = strSrc.get_data();
         string_data* pNewData = CloneData( pSrcData );
         Attach( pNewData );
      }
      
      simple_string(PCXSTR pszSrc,string_manager_interface * pstringmanager )
      {
         ATLENSURE( pstringmanager != NULL );
         
         int nLength = StringLength( pszSrc );
         string_data* pData = pstringmanager->allocate( nLength, sizeof( XCHAR ) );
         if( pData == NULL )
         {
            ThrowMemoryException();
         }
         Attach( pData );
         SetLength( nLength );
#if _SECURE_ATL
         CopyChars( m_pszData, nLength, pszSrc, nLength );
#else
         CopyChars( m_pszData, pszSrc, nLength );
#endif
      }
      simple_string(const XCHAR* pchSrc,int nLength,string_manager_interface * pstringmanager )
      {
         ATLENSURE( pstringmanager != NULL );
         
         if(pchSrc == NULL && nLength != 0)
            AtlThrow(E_INVALIDARG);
         
         string_data * pData = pstringmanager->allocate( nLength, sizeof( XCHAR ) );
         if( pData == NULL )
         {
            ThrowMemoryException();
         }
         Attach( pData );
         SetLength( nLength );
#if _SECURE_ATL
         CopyChars( m_pszData, nLength, pchSrc, nLength );
#else
         CopyChars( m_pszData, pchSrc, nLength );
#endif
      }
      ~simple_string() NOTHROW
      {
         string_data * pData = get_data();
         pData->Release();
      }
      
      operator simple_string&()
      {
         return *(simple_string*)this;
      }
      
      simple_string& operator=(const simple_string& strSrc )
      {
         string_data * pSrcData = strSrc.get_data();
         string_data * pOldData = get_data();
         if( pSrcData != pOldData)
         {
            if( pOldData->IsLocked() || pSrcData->pstringmanager != pOldData->pstringmanager )
            {
               SetString( strSrc.GetString(), strSrc.get_length() );
            }
            else
            {
               string_data * pNewData = CloneData( pSrcData );
               pOldData->Release();
               Attach( pNewData );
            }
         }
         
         return( *this );
      }
      
      
      simple_string& operator=(PCXSTR pszSrc )
      {
         SetString( pszSrc );
         
         return( *this );
      }
      
      simple_string& operator+=(const simple_string& strSrc )
      {
         append( strSrc );
         
         return( *this );
      }
      
      simple_string& operator+=(PCXSTR pszSrc )
      {
         append( pszSrc );
         
         return( *this );
      }
      template< int t_nSize >
         simple_string& operator+=(const static_string< t_nSize >& strSrc )
      {
         append( static_cast<const XCHAR *>(strSrc), strSrc.get_length() );
         
         return( *this );
      }
      simple_string& operator+=(char ch )
      {
         AppendChar(ch );
         
         return( *this );
      }
      
      simple_string& operator+=(unsigned char ch )
      {
         AppendChar( XCHAR( ch ) );
         
         return( *this );
      }
      
      simple_string& operator+=(wchar_t ch )
      {
         AppendChar( XCHAR( ch ) );
         
         return( *this );
      }
      
      XCHAR operator[](int iChar ) const
      {
         ATLASSERT( (iChar >= 0) && (iChar <= get_length()) );  // Indexing the '\0' is OK
         
         if( (iChar < 0) || (iChar > get_length()) )
            AtlThrow(E_INVALIDARG);
         
         return( m_pszData[iChar] );
      }
      
      operator PCXSTR() const NOTHROW
      {
         return( m_pszData );
      }
      
      void append(PCXSTR pszSrc )
      {
         append( pszSrc, StringLength( pszSrc ) );
      }
      void append(PCXSTR pszSrc,int nLength )
      {
         // See comment in SetString() about why we do this
         UINT_PTR nOffset = pszSrc-GetString();
         
         UINT nOldLength = get_length();
         if (nOldLength < 0)
         {
            // protects from underflow
            nOldLength = 0;
         }
         int nNewLength = nOldLength+nLength;
         PXSTR pszBuffer = GetBuffer( nNewLength );
         if( nOffset <= nOldLength )
         {
            pszSrc = pszBuffer+nOffset;
            // No need to call CopyCharsOverlapped, since the destination is
            // beyond the end of the original buffer
         }
#if _SECURE_ATL
         CopyChars( pszBuffer+nOldLength, nLength, pszSrc, nLength );
#else
         CopyChars( pszBuffer+nOldLength, pszSrc, nLength );
#endif
         ReleaseBufferSetLength( nNewLength );
      }
      void AppendChar(XCHAR ch )
      {
         UINT nOldLength = get_length();
         int nNewLength = nOldLength+1;
         PXSTR pszBuffer = GetBuffer( nNewLength );
         pszBuffer[nOldLength] = ch;
         ReleaseBufferSetLength( nNewLength );
      }
      void append(const simple_string& strSrc )
      {
         append( strSrc.GetString(), strSrc.get_length() );
      }   
      void Empty() NOTHROW
      {
         string_data * pOldData = get_data();
         string_manager_interface * pstringmanager = pOldData->pstringmanager;
         if( pOldData->nDataLength == 0 )
         {
            return;
         }
         
         if( pOldData->IsLocked() )
         {
            // Don't reallocate a locked buffer that's shrinking
            SetLength( 0 );
         }
         else
         {
            pOldData->Release();
            string_data* pNewData = pstringmanager->GetNilString();
            Attach( pNewData );
         }
      }
      void free_extra()
      {
         string_data* pOldData = get_data();
         int nLength = pOldData->nDataLength;
         string_manager_interface* pstringmanager = pOldData->pstringmanager;
         if( pOldData->nAllocLength == nLength )
         {
            return;
         }
         
         if( !pOldData->IsLocked() )  // Don't reallocate a locked buffer that's shrinking
         {
            string_data* pNewData = pstringmanager->allocate( nLength, sizeof( XCHAR ) );
            if( pNewData == NULL )
            {
               SetLength( nLength );
               return;
            }
            
#if _SECURE_ATL
            CopyChars( PXSTR( pNewData->data() ), nLength, 
               PCXSTR( pOldData->data() ), nLength );
#else
            CopyChars( PXSTR( pNewData->data() ), PCXSTR( pOldData->data() ), nLength );
#endif
            
            pOldData->Release();
            Attach( pNewData );
            SetLength( nLength );
         }
      }
      
      int GetAllocLength() const NOTHROW
      {
         return( get_data()->nAllocLength );
      }
      XCHAR get_at(int iChar ) const
      {
         ATLASSERT( (iChar >= 0) && (iChar <= get_length()) );  // Indexing the '\0' is OK
         if( (iChar < 0) || (iChar > get_length()) )
            AtlThrow(E_INVALIDARG);      
         
         return( m_pszData[iChar] );
      }
      PXSTR GetBuffer()
      {
         string_data* pData = get_data();
         if( pData->IsShared() )
         {
            Fork( pData->nDataLength );
         }
         
         return( m_pszData );
      }
      PXSTR GetBuffer(int nMinBufferLength )
      {
         return( PrepareWrite( nMinBufferLength ) );
      }
      PXSTR GetBufferSetLength(int nLength )
      {
         PXSTR pszBuffer = GetBuffer( nLength );
         SetLength( nLength );
         
         return( pszBuffer );
      }
      int get_length() const NOTHROW
      {
         return( get_data()->nDataLength );
      }
      void get_string(char * psz) const NOTHROW
      {
         gen::str::copy(psz, (const char *) *this);
      }
      void set_string(const char * psz) NOTHROW
      {
         SetString(psz);
      }
      string_manager_interface * GetManager() const NOTHROW
      {
         string_manager_interface * pstringmanager = get_data()->pstringmanager;
         return pstringmanager ? pstringmanager->Clone() : NULL;
      }
      
      PCXSTR GetString() const NOTHROW
      {
         return( m_pszData );
      }
      
      bool is_empty() const NOTHROW
      {
         return( get_length() == 0 );
      }
      
      bool has_char() const NOTHROW
      {
         return (get_length() > 0);
      }
      
      PXSTR LockBuffer()
      {
         string_data* pData = get_data();
         if( pData->IsShared() )
         {
            Fork( pData->nDataLength );
            pData = get_data();  // Do it again, because the fork might have changed it
         }
         pData->Lock();
         
         return( m_pszData );
      }
      void UnlockBuffer() NOTHROW
      {
         string_data* pData = get_data();
         pData->Unlock();
      }
      void Preallocate(int nLength )
      {
         PrepareWrite( nLength );
      }
      void ReleaseBuffer(int nNewLength = -1 )
      {
         if( nNewLength == -1 )
         {
            nNewLength = StringLength( m_pszData );
         }
         SetLength( nNewLength );
      }
      void ReleaseBufferSetLength(int nNewLength )
      {
         ATLASSERT( nNewLength >= 0 );
         SetLength( nNewLength );
      }
      void Truncate(int nNewLength )
      {
         ATLASSERT( nNewLength <= get_length() );
         GetBuffer( nNewLength );
         ReleaseBufferSetLength( nNewLength );
      }
      void set_at(int iChar,XCHAR ch )
      {
         ATLASSERT( (iChar >= 0) && (iChar < get_length()) );
         
         if( (iChar < 0) || (iChar >= get_length()) )
            AtlThrow(E_INVALIDARG);      
         
         int nLength = get_length();
         PXSTR pszBuffer = GetBuffer();
         pszBuffer[iChar] = ch;
         ReleaseBufferSetLength( nLength );
         
      }
      void SetManager(string_manager_interface * pstringmanager )
      {
         ATLASSERT( is_empty() );
         
         string_data * pData = get_data();
         pData->Release();
         pData = pstringmanager->GetNilString();
         Attach( pData );
      }
      void SetString(PCXSTR pszSrc )
      {
         SetString( pszSrc, StringLength( pszSrc ) );
      }
      void SetString(PCXSTR pszSrc,int nLength )
      {
         if( nLength == 0 )
         {
            Empty();
         }
         else
         {
            // It is possible that pszSrc points to a location inside of our 
            // buffer.  GetBuffer() might change m_pszData if (1) the buffer 
            // is shared or (2) the buffer is too small to hold the new 
            // string.  We detect this aliasing, and modify pszSrc to point
            // into the newly allocated buffer instead.
            
            if(pszSrc == NULL)
               AtlThrow(E_INVALIDARG);         
            
            UINT nOldLength = get_length();
            UINT_PTR nOffset = pszSrc-GetString();
            // If 0 <= nOffset <= nOldLength, then pszSrc points into our 
            // buffer
            
            PXSTR pszBuffer = GetBuffer( nLength );
            if( nOffset <= nOldLength )
            {
#if _SECURE_ATL
               CopyCharsOverlapped( pszBuffer, nLength, 
                  pszBuffer+nOffset, nLength );
#else
               CopyCharsOverlapped( pszBuffer, pszBuffer+nOffset, nLength );
#endif
            }
            else
            {
#if _SECURE_ATL
               CopyChars( pszBuffer, nLength, pszSrc, nLength );
#else
               CopyChars( pszBuffer, pszSrc, nLength );
#endif
            }
            ReleaseBufferSetLength( nLength );
         }
      }
      
   public:
      friend simple_string operator+(
         const simple_string& str1,
         const simple_string& str2 )
      {
         simple_string s( str1.GetManager() );
         
         Concatenate( s, str1, str1.get_length(), str2, str2.get_length() );
         
         return( s );
      }
      
      friend simple_string operator+(
         const simple_string& str1,
         PCXSTR psz2 )
      {
         simple_string s( str1.GetManager() );
         
         Concatenate( s, str1, str1.get_length(), psz2, StringLength( psz2 ) );
         
         return( s );
      }
      
      friend simple_string operator+(
         PCXSTR psz1,
         const simple_string& str2 )
      {
         simple_string s( str2.GetManager() );
         
         Concatenate( s, psz1, StringLength( psz1 ), str2, str2.get_length() );
         
         return( s );
      }
      
      static void __cdecl CopyChars(XCHAR* pchDest,const XCHAR* pchSrc,int nChars ) NOTHROW
      {
         memcpy(pchDest, pchSrc, nChars * sizeof(XCHAR));
      }

#if _SECURE_ATL
      static void __cdecl CopyChars(XCHAR* pchDest,size_t nDestLen,const XCHAR* pchSrc,int nChars ) NOTHROW
      {
         memcpy_s(pchDest, nDestLen * sizeof(XCHAR), pchSrc, nChars * sizeof(XCHAR));
      }
#endif
      
      static void __cdecl CopyCharsOverlapped(XCHAR* pchDest,const XCHAR* pchSrc,int nChars ) NOTHROW
      {
         memmove( pchDest, pchSrc, nChars*sizeof( XCHAR ) );
      }

#if _SECURE_ATL
      static void __cdecl CopyCharsOverlapped(XCHAR* pchDest,size_t nDestLen,const XCHAR* pchSrc,int nChars ) NOTHROW
      {
         memmove_s(pchDest, nDestLen * sizeof(XCHAR), pchSrc, nChars * sizeof(XCHAR));
      }
#endif

      ATL_NOINLINE static int __cdecl StringLength(PCXSTR psz ) NOTHROW
      {
         int nLength = 0;
         if( psz != NULL )
         {
            const XCHAR* pch = psz;
            while( *pch != 0 )
            {
               nLength++;
               pch++;
            }
         }
         
         return( nLength );
      }
      
   protected:
      static void __cdecl Concatenate(simple_string& strResult, PCXSTR psz1,int nLength1, PCXSTR psz2,int nLength2 )
      {
         int nNewLength = nLength1+nLength2;
         PXSTR pszBuffer = strResult.GetBuffer( nNewLength );
#if _SECURE_ATL
         CopyChars( pszBuffer, nLength1, psz1, nLength1 );
         CopyChars( pszBuffer+nLength1, nLength2, psz2, nLength2 );
#else
         CopyChars( pszBuffer, psz1, nLength1 );
         CopyChars( pszBuffer+nLength1, psz2, nLength2 );
#endif
         strResult.ReleaseBufferSetLength( nNewLength );
      }

      ATL_NOINLINE __declspec( noreturn ) static void __cdecl ThrowMemoryException()
      {
         AtlThrow( E_OUTOFMEMORY );
      }
      
      // Implementation
   private:
      void Attach(string_data * pData ) NOTHROW
      {
         m_pszData = static_cast< PXSTR >( pData->data() );
      }
      ATL_NOINLINE void Fork(int nLength )
      {
         string_data* pOldData = get_data();
         int nOldLength = pOldData->nDataLength;
         string_data* pNewData = pOldData->pstringmanager->Clone()->allocate( nLength, sizeof( XCHAR ) );
         if( pNewData == NULL )
         {
            ThrowMemoryException();
         }
         int nCharsToCopy = ((nOldLength < nLength) ? nOldLength : nLength)+1;  // copy '\0'
#if _SECURE_ATL
         CopyChars( PXSTR( pNewData->data() ), nCharsToCopy, 
            PCXSTR( pOldData->data() ), nCharsToCopy );
#else
         CopyChars( PXSTR( pNewData->data() ), PCXSTR( pOldData->data() ), nCharsToCopy );
#endif
         pNewData->nDataLength = nOldLength;
         pOldData->Release();
         Attach( pNewData );
      }
      string_data * get_data() const NOTHROW
      {
         return( reinterpret_cast< string_data * >( m_pszData )-1 );
      }
      PXSTR PrepareWrite(int nLength )
      {
         string_data * pOldData = get_data();
         int nShared = 1-pOldData->nRefs;  // nShared < 0 means true, >= 0 means false
         int nTooShort = pOldData->nAllocLength-nLength;  // nTooShort < 0 means true, >= 0 means false
         if( (nShared|nTooShort) < 0 )  // If either sign bit is set (i.e. either is less than zero), we need to copy data
         {
            PrepareWrite2( nLength );
         }
         
         return( m_pszData );
      }
      ATL_NOINLINE void PrepareWrite2(int nLength )
      {
         string_data * pOldData = get_data();
         if( pOldData->nDataLength > nLength )
         {
            nLength = pOldData->nDataLength;
         }
         if( pOldData->IsShared() )
         {
            Fork( nLength );
         }
         else if( pOldData->nAllocLength < nLength )
         {
            // Grow exponentially, until we hit 1K.
            int nNewLength = pOldData->nAllocLength;
            if( nNewLength > 1024 )
            {
               nNewLength += 1024;
            }
            else
            {
               nNewLength *= 2;
            }
            if( nNewLength < nLength )
            {
               nNewLength = nLength;
            }
            Reallocate( nNewLength );
         }
      }
      ATL_NOINLINE void Reallocate(int nLength )
      {
         string_data* pOldData = get_data();
         ATLASSERT( pOldData->nAllocLength < nLength );
         string_manager_interface * pstringmanager = pOldData->pstringmanager;
         if ( pOldData->nAllocLength >= nLength || nLength <= 0)
         {
            ThrowMemoryException();
            return;
         }
         string_data* pNewData = pstringmanager->Reallocate( pOldData, nLength, sizeof( XCHAR ) );
         if( pNewData == NULL )
         {
            ThrowMemoryException();
         }
         Attach( pNewData );
      }
      
      void SetLength(int nLength )
      {

         if(nLength < 0 )
            throw_error_exception("simple_string::SetLength nLength < 0");
         if(nLength > get_data()->nAllocLength)
            throw_error_exception("simple_string::SetLength nLength > get_data()->nAllocLength");
         
         get_data()->nDataLength = nLength;
         m_pszData[nLength] = 0;

      }
      
      static string_data * __cdecl CloneData(string_data * pData )
      {
         string_data * pNewData = NULL;
         
         string_manager_interface * pNewStringMgr = pData->pstringmanager->Clone();
         if( !pData->IsLocked() && (pNewStringMgr == pData->pstringmanager) )
         {
            pNewData = pData;
            pNewData->AddRef();
         }
         else
         {
            pNewData = pNewStringMgr->allocate( pData->nDataLength, sizeof( XCHAR ) );
            if( pNewData == NULL )
            {
               ThrowMemoryException();
            }
            pNewData->nDataLength = pData->nDataLength;
#if _SECURE_ATL
            CopyChars( PXSTR( pNewData->data() ), pData->nDataLength+1,
               PCXSTR( pData->data() ), pData->nDataLength+1 );  // copy '\0'
#else
            CopyChars( PXSTR( pNewData->data() ), PCXSTR( pData->data() ), pData->nDataLength+1 );  // copy '\0'
#endif
         }
         
         return( pNewData );
      }
      
   public :
      typedef string_buffer CStrBuf;
   private:
      PXSTR m_pszData;
      
      friend class simple_string;
   };
   
   class CLASS_DECL_ca string_buffer
   {
   public:
      
      enum
      {
         AUTO_LENGTH = 0x01,  // Automatically determine the new length of the string at release.  The string must be null-terminated.
            SET_LENGTH = 0x02,  // Set the length of the string object at GetBuffer time
      };
      
      typedef simple_string StringType;
      typedef StringType::XCHAR XCHAR;
      typedef StringType::PXSTR PXSTR;
      typedef StringType::PCXSTR PCXSTR;
      
      
   public:
      explicit string_buffer(StringType& str ) THROWS :
      m_str( str ),
         m_pszBuffer( NULL ),
#ifdef _DEBUG
         m_nBufferLength( str.get_length() ),
#endif
         m_nLength( str.get_length() )
      {
         m_pszBuffer = m_str.GetBuffer();
      }
      
      string_buffer(StringType& str,int nMinLength,DWORD dwFlags = AUTO_LENGTH ) THROWS :
      m_str( str ),
         m_pszBuffer( NULL ),
#ifdef _DEBUG
         m_nBufferLength( nMinLength ),
#endif
         m_nLength( (dwFlags&AUTO_LENGTH) ? -1 : nMinLength )
      {
         if( dwFlags&SET_LENGTH )
         {
            m_pszBuffer = m_str.GetBufferSetLength( nMinLength );
         }
         else
         {
            m_pszBuffer = m_str.GetBuffer( nMinLength );
         }
      }
      
      ~string_buffer()
      {
         m_str.ReleaseBuffer( m_nLength );
      }
      
      operator PXSTR() NOTHROW
      {
         return( m_pszBuffer );
      }
      operator PCXSTR() const NOTHROW
      {
         return( m_pszBuffer );
      }
      
      void SetLength(int nLength )
      {
         ATLASSERT( nLength >= 0 );      
         ATLASSERT( nLength <= m_nBufferLength );
         
         if( nLength < 0 )
            AtlThrow(E_INVALIDARG);
         
         m_nLength = nLength;
      }
      
      // Implementation
   private:
      StringType& m_str;
      PXSTR m_pszBuffer;
      int m_nLength;
#ifdef _DEBUG
      int m_nBufferLength;
#endif
      
      // Private copy constructor and copy assignment operator to prevent accidental use
   private:
      string_buffer( const string_buffer& ) NOTHROW;
      string_buffer& operator=( const string_buffer& ) NOTHROW;
   };
   
class string;

class CLASS_DECL_ca verisimple_wstring
{
public:
   
   wchar_t * m_pwsz;

   verisimple_wstring();
   verisimple_wstring(const wchar_t * pwsz);
   verisimple_wstring(const verisimple_wstring & wstr);
   ~verisimple_wstring();


   verisimple_wstring & operator = (const verisimple_wstring & wstr);
   verisimple_wstring & operator = (const wchar_t * pwsz);


   inline operator const wchar_t * () { return m_pwsz; }


   wchar_t * alloc(int iCount);
   count get_length();

};


typedef verisimple_wstring wstring;


class CLASS_DECL_ca wstringtou :
   public wstring
{
public:
   
   string * m_pstringUtf8;

   wstringtou(string & str, int iAllocCount);
   ~wstringtou();

   inline operator const wchar_t * () { return m_pwsz; }
   inline operator wchar_t * () { return m_pwsz; }

};
