#pragma once


class string_manager;


struct CLASS_DECL_c string_data
{
   string_manager * pstringmanager;  // string manager for this string_data
   strsize nDataLength;  // Length of currently used data in XCHARs (not including terminating NULL)
   strsize nAllocLength;  // Length of allocated data in XCHARs (not including terminating NULL)
   long nRefs;     // Reference count: negative == locked
   // char data[nAllocLength+1]  // A string_data is always followed in primitive::memory by the actual array of character data

   inline char * data() NOTHROW;
   inline void AddRef() RELEASENOTHROW;
   inline bool IsLocked() const NOTHROW;
   inline bool IsShared() const NOTHROW;
   inline void lock() RELEASENOTHROW;
   inline void Release() RELEASENOTHROW;
   inline void unlock() RELEASENOTHROW;
};




class CLASS_DECL_c nil_string_data :
   public string_data
{
public:


   nil_string_data() NOTHROW
   {
      pstringmanager = NULL;
      nRefs = 2;  // Never gets freed by string_manager
      nDataLength = 0;
      nAllocLength = 0;
      achNil[0] = 0;
      achNil[1] = 0;
   }

   void SetManager(string_manager * pMgr ) NOTHROW
   {
//      ASSERT( pstringmanager == NULL );
      pstringmanager = pMgr;
   }



public:


   wchar_t achNil[2];


};











class string_manager
{
protected:


   fixed_alloc_array * m_palloca;

   nil_string_data  m_nil;


public:


   string_manager();


   inline string_data * allocate(strsize nChars, int32_t nCharSize);
   inline void Free(string_data * pData);
   inline string_data * Reallocate(string_data * pData, strsize nChars, int32_t nCharSize);
   inline string_data * GetNilString() ;
   inline string_manager * Clone() { return this; }

};


inline string_data * string_manager::allocate(strsize nChars, int32_t nCharSize )
{
   size_t nTotalSize;
   string_data * pData;
   size_t nDataBytes;

//   ASSERT(nCharSize > 0);
   
   if(nChars < 0)
   {
//      ASSERT(FALSE);
      return NULL;
   }
   
   nDataBytes = (nChars+1)*nCharSize;
   nTotalSize = sizeof( string_data  )+nDataBytes;
   
   //bool bEnable = __enable_memory_tracking(FALSE);
   
   try
   {
      pData = (string_data *) m_palloca->alloc(nTotalSize);
//      pData = (string_data *) ca2_alloc(nTotalSize);
   }
   catch(...)
   {
      return NULL;
   }

   //__enable_memory_tracking(bEnable);

   if (pData == NULL)
      return NULL;
   pData->pstringmanager = this;
   pData->nRefs = 1;
   pData->nAllocLength = nChars;
   pData->nDataLength = 0;

   return pData;
}

inline void string_manager::Free(string_data * pData)
{
   size_t nTotalSize = sizeof( string_data  ) + pData->nAllocLength + 1;
   m_palloca->free(pData, nTotalSize);
   //ca2_free(pData, 0);
}

inline string_data * string_manager::Reallocate(string_data * pOldData, strsize nChars, int32_t nCharSize)
{
   string_data * pNewData = NULL;
   size_t nNewTotalSize;
   size_t nNewDataBytes;
   size_t nOldTotalSize;
   size_t nOldDataBytes;
   
//   ASSERT(nCharSize > 0);
   
   if(nChars < 0)
   {
//      ASSERT(FALSE);
      return NULL;
   }
   
   nNewDataBytes = (nChars+1)*nCharSize;
   nNewTotalSize = sizeof( string_data  )+nNewDataBytes;
   nOldDataBytes = (pOldData->nAllocLength+1)*nCharSize;
   nOldTotalSize = sizeof( string_data  ) + nOldDataBytes;
   
   //bool bEnable = __enable_memory_tracking(FALSE);
   
   try
   {

      pNewData = (string_data *) m_palloca->realloc(pOldData, nOldTotalSize, nNewTotalSize);
      //pNewData = (string_data *) ca2_realloc(pOldData, nNewTotalSize, 0, NULL, 0);

   }
   catch(...)
   {
   }

   //__enable_memory_tracking(bEnable);


   if(pNewData == NULL)
   {
      return NULL;
   }

   pNewData->nAllocLength = nChars;

   return pNewData;
}

inline string_data * string_manager::GetNilString() 
{
   m_nil.AddRef();
   return &m_nil;
}







































namespace ca2
{
   namespace str
   {
      CLASS_DECL_c inline void copy(char * pszDest, const char * pszSrc) { strcpy(pszDest, pszSrc); }
      CLASS_DECL_c inline void copy(wchar_t * pszDest, const wchar_t * pszSrc) { wcscpy_dup(pszDest, pszSrc); }
   } // namespace str
} // namespace ca2



/*namespace ca2
{

   namespace international
   {

      CLASS_DECL_c strsize          UnicodeToMultiByteCount(UINT uiCodePage, const wchar_t * lpcsz);
      CLASS_DECL_c bool         UnicodeToMultiByte(UINT uiCodePage, char * lpstrMultiByte, strsize nCount, const wchar_t * lpcsz);
      CLASS_DECL_c const char * UnicodeToMultiByte(UINT uiCodePage, const wchar_t * lpcsz);
      CLASS_DECL_c
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

/*      class CLASS_DECL_c string_manager
      {
   public:
      // allocate a new string_data
      virtual string_data * allocate(strsize nAllocLength, int32_t nCharSize) = 0;
      // Free an existing string_data
      virtual void Free(string_data * pData) = 0;
      // Change the size of an existing string_data
      virtual string_data * Reallocate(string_data * pData, strsize nAllocLength, int32_t nCharSize ) = 0;
      // get the string_data for a Nil string
      virtual string_data * GetNilString() = 0;
      virtual string_manager* Clone() = 0;
      };*/

#if defined(LINUX) || defined(MACOS) || defined(ANDROID)
   #define _gen_InterlockedIncrement(ptr) __sync_add_and_fetch(ptr, 1)
   #define _gen_InterlockedDecrement(ptr) __sync_sub_and_fetch(ptr, 1)
#else
   #ifdef _M_IX86
      #ifndef _M_CEE
         #define _gen_InterlockedIncrement _InterlockedIncrement
         #define _gen_InterlockedDecrement _InterlockedDecrement
      #else
         #define _gen_InterlockedIncrement InterlockedIncrement
         #define _gen_InterlockedDecrement InterlockedDecrement
         /* managed code must use the non-intrinsics */
         #ifdef InterlockedIncrement
            #undef InterlockedIncrement
         #endif
         #ifdef InterlockedDecrement
            #undef InterlockedDecrement
         #endif
      #endif  // !_M_CEE
   #else
      #define _gen_InterlockedIncrement InterlockedIncrement
      #define _gen_InterlockedDecrement InterlockedDecrement
   #endif  // _M_IX86_
#endif // ! LINUX
















template< const strsize t_nSize >
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

   static strsize __cdecl get_length()
   {
      return (t_nSize/sizeof( char ))-1;
   }

private:
const char* m_psz;

private:
static_string( const static_string& str ) NOTHROW;
static_string& operator=( const static_string& str ) NOTHROW;
};








#define _ST( psz ) ::ca2::static_string< char, sizeof( _T( psz ) ) >( _T( psz ) )
#define _SA( psz ) ::ca2::static_string< char, sizeof( psz ) >( psz )
#define _SW( psz ) ::ca2::static_string< wchar_t, sizeof( L##psz ) >( L##psz )
#define _SO( psz ) _SW( psz )

class CLASS_DECL_c char_traits_base
{
public:
};



























      class string_buffer;


class CLASS_DECL_c simple_string
{
public:


   explicit simple_string(string_manager * pstringmanager )
   {
      construct(pstringmanager);
   }

   void construct(string_manager * pstringmanager)
   {
      ENSURE( pstringmanager != NULL );
      string_data * pData = pstringmanager->GetNilString();
      attach( pData );
   }

   simple_string(const simple_string & strSrc, string_manager * pstringmanager  )
   {
      if(&strSrc == NULL)
      {
         ENSURE( pstringmanager != NULL );

         string_data* pData = pstringmanager->allocate( 0, sizeof( char ) );
         if( pData == NULL )
         {
            ThrowMemoryException();
         }
         attach( pData );
         set_length( 0 );
         return;
      }
      string_data* pSrcData = strSrc.get_data();
      string_data* pNewData = CloneData( pSrcData );
      attach( pNewData );
   }

   simple_string(const char * pszSrc,string_manager * pstringmanager )
   {
      ENSURE( pstringmanager != NULL );

      strsize nLength = StringLength( pszSrc );
      string_data* pData = pstringmanager->allocate( nLength, sizeof( char ) );
      if( pData == NULL )
      {
         ThrowMemoryException();
      }
      attach( pData );
      set_length( nLength );
#if _SECURE_TEMPLATE
      CopyChars( m_pszData, nLength, pszSrc, nLength );
#else
      CopyChars( m_pszData, pszSrc, nLength );
#endif
   }
   simple_string(const char* pchSrc,strsize nLength,string_manager * pstringmanager )
   {
      ENSURE( pstringmanager != NULL );

      if(pchSrc == NULL && nLength != 0)
         throw invalid_argument_exception(::ca2::get_thread_app());

      if(nLength < 0)
         nLength = (strsize) strlen(pchSrc);

      string_data * pData = pstringmanager->allocate( nLength, sizeof( char ) );
      if( pData == NULL )
      {
         ThrowMemoryException();
      }
      attach( pData );
      set_length( nLength );
#if _SECURE_TEMPLATE
      CopyChars( m_pszData, nLength, pchSrc, nLength );
#else
      CopyChars( m_pszData, pchSrc, nLength );
#endif
   }
   ~simple_string() NOTHROW
   {
      if(m_pszData != NULL)
      {
         string_data * pData = get_data();
         pData->Release();
      }
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
            attach( pNewData );
         }
      }

      return *this;
   }


   simple_string& operator=(const char * pszSrc )
   {
      SetString( pszSrc );

      return *this;
   }

   simple_string& operator+=(const simple_string& strSrc )
   {
      append( strSrc );

      return *this;
   }

   simple_string& operator+=(const char * pszSrc )
   {
      append( pszSrc );

      return *this;
   }
   template< strsize t_nSize >
      simple_string& operator+=(const static_string< t_nSize >& strSrc )
   {
      append( static_cast<const char *>(strSrc), strSrc.get_length() );

      return *this;
   }


   simple_string& operator+=(char ch )
   {

      append_char(ch );

      return *this;

   }


   simple_string& operator+=(uchar ch )
   {

      append_char( char( ch ) );

      return *this;

   }


   simple_string& operator+=(wchar_t ch )
   {

      append_char( char( ch ) );

      return *this;

   }


   const char & operator [](strsize iChar ) const
   {
      
      //ASSERT( (iChar >= 0) && (iChar <= get_length()) );  // Indexing the '\0' is OK

      if( (iChar < 0) || (iChar > get_length()) )
         throw invalid_argument_exception(::ca2::get_thread_app());

      return m_pszData[iChar];

   }

   // non error at
   char s_at(strsize iChar) const
   {

      if((iChar < 0) || (iChar > get_length()))
         return '\0';

      return m_pszData[iChar];

   }

   inline operator const char *() const NOTHROW
   {
      return( m_pszData );
   }

#ifdef METROWIN
   inline operator Platform::String ^() const
   {
      return ref new Platform::String(wstring(*this));
   }
#endif

   void append(const char * pszSrc )
   {
      append( pszSrc, StringLength( pszSrc ) );
   }
   void append(const char * pszSrc,strsize nLength )
   {
      // See comment in SetString() about why we do this
      uint_ptr nOffset = pszSrc-GetString();

      strsize nOldLength = get_length();
      if (nOldLength < 0)
      {
         // protects from underflow
         nOldLength = 0;
      }
      strsize nNewLength = nOldLength+nLength;
      char * pszBuffer = GetBuffer( nNewLength );
      if( nOffset <= (uint_ptr) nOldLength )
      {
         pszSrc = pszBuffer+nOffset;
         // No need to call CopyCharsOverlapped, since the destination is
         // beyond the end of the original buffer
      }
#if _SECURE_TEMPLATE
      CopyChars( pszBuffer+nOldLength, nLength, pszSrc, nLength );
#else
      CopyChars( pszBuffer+nOldLength, pszSrc, nLength );
#endif
      ReleaseBufferSetLength( nNewLength );
   }
   
   void append_char(char ch)
   {

      strsize nOldLength = get_length();
      
      strsize nNewLength = nOldLength+1;
      
      char * pszBuffer = GetBuffer( nNewLength );
      
      pszBuffer[nOldLength] = ch;
      
      ReleaseBufferSetLength( nNewLength );

   }

   void append(strsize i, char ch)
   {

      if(i <= 0)
         return;

      strsize nOldLength = get_length();
      
      strsize nNewLength = nOldLength+1;
      
      char * pszBuffer = GetBuffer( nNewLength );
      
      memset(&pszBuffer[nOldLength], (int) ch, i);
      
      ReleaseBufferSetLength( nNewLength );

   }

   void append(const simple_string& strSrc )
   {
      
      append( strSrc.GetString(), strSrc.get_length() );

   }

   void Empty() NOTHROW
   {

      string_data * pOldData = get_data();

      string_manager * pstringmanager = pOldData->pstringmanager;

      if(pOldData->nDataLength == 0)
         return;

      if(pOldData->IsLocked())
      {
         // Don't reallocate a locked buffer that's shrinking
         set_length(0);
      }
      else
      {
         
         pOldData->Release();
         string_data* pNewData = pstringmanager->GetNilString();
         attach( pNewData );

      }

   }
   void free_extra()
   {
      string_data* pOldData = get_data();
      strsize nLength = pOldData->nDataLength;
      string_manager* pstringmanager = pOldData->pstringmanager;
      if( pOldData->nAllocLength == nLength )
      {
         return;
      }

      if( !pOldData->IsLocked() )  // Don't reallocate a locked buffer that's shrinking
      {
         string_data* pNewData = pstringmanager->allocate( nLength, sizeof( char ) );
         if( pNewData == NULL )
         {
            set_length( nLength );
            return;
         }

#if _SECURE_TEMPLATE
         CopyChars( char *( pNewData->data() ), nLength, const char *( pOldData->data() ), nLength );
#else
         CopyChars( (char *)( pNewData->data() ), (const char *)( pOldData->data() ), nLength );
#endif

         pOldData->Release();
         attach( pNewData );
         set_length( nLength );
      }
   }

   strsize GetAllocLength() const NOTHROW
   {
      return( get_data()->nAllocLength );
   }
   char get_at(strsize iChar ) const
   {
      ASSERT( (iChar >= 0) && (iChar <= get_length()) );  // Indexing the '\0' is OK
      if( (iChar < 0) || (iChar > get_length()) )
         throw invalid_argument_exception(::ca2::get_thread_app());

      return( m_pszData[iChar] );
   }
   char * GetBuffer()
   {
      string_data* pData = get_data();
      if( pData->IsShared() )
      {
         Fork( pData->nDataLength );
      }

      return( m_pszData );
   }
   char * GetBuffer(strsize nMinBufferLength )
   {
      return( PrepareWrite( nMinBufferLength ) );
   }
   char * GetBufferSetLength(strsize nLength )
   {
      char * pszBuffer = GetBuffer( nLength );
      set_length( nLength );

      return( pszBuffer );
   }
   strsize get_length() const NOTHROW
   {
      return( get_data()->nDataLength );
   }
   strsize size() const NOTHROW
   {
      return( get_data()->nDataLength );
   }
   void get_string(char * psz) const NOTHROW
   {
      ::strcpy(psz, (const char *) *this);
   }
   void set_string(const char * psz) NOTHROW
   {
      SetString(psz);
   }
   string_manager * GetManager() const NOTHROW
   {
      string_manager * pstringmanager = get_data()->pstringmanager;
      return pstringmanager ? pstringmanager->Clone() : NULL;
   }

   const char * GetString() const NOTHROW
   {
      return( m_pszData );
   }

   bool is_empty() const NOTHROW
   {
      return( get_length() == 0 );
   }

   bool empty() const NOTHROW
   {
      return( get_length() == 0 );
   }

   bool has_char() const NOTHROW
   {
      return (get_length() > 0);
   }

   char * LockBuffer()
   {
      string_data* pData = get_data();
      if( pData->IsShared() )
      {
         Fork( pData->nDataLength );
         pData = get_data();  // Do it again, because the fork might have changed it
      }
      pData->lock();

      return( m_pszData );
   }
   void UnlockBuffer() NOTHROW
   {
      string_data* pData = get_data();
      pData->unlock();
   }
   void Preallocate(strsize nLength )
   {
      PrepareWrite( nLength );
   }
   void ReleaseBuffer(strsize nNewLength = -1 )
   {
      if( nNewLength == -1 )
      {
         nNewLength = StringLength( m_pszData );
      }
      set_length( nNewLength );
   }
   void ReleaseBufferSetLength(strsize nNewLength )
   {
      ASSERT( nNewLength >= 0 );
      set_length( nNewLength );
   }
   void Truncate(strsize nNewLength )
   {
      ASSERT( nNewLength <= get_length() );
      GetBuffer( nNewLength );
      ReleaseBufferSetLength( nNewLength );
   }
   void set_at(strsize iChar,char ch )
   {
      ASSERT( (iChar >= 0) && (iChar < get_length()) );

      if( (iChar < 0) || (iChar >= get_length()) )
         throw invalid_argument_exception(::ca2::get_thread_app());

      strsize nLength = get_length();
      char * pszBuffer = GetBuffer();
      pszBuffer[iChar] = ch;
      ReleaseBufferSetLength( nLength );

   }
   void SetManager(string_manager * pstringmanager )
   {
      ASSERT( is_empty() );

      string_data * pData = get_data();
      pData->Release();
      pData = pstringmanager->GetNilString();
      attach( pData );
   }
   void SetString(const char * pszSrc )
   {
      SetString( pszSrc, StringLength( pszSrc ) );
   }
   void SetString(const char * pszSrc,strsize nLength )
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
            throw invalid_argument_exception(::ca2::get_thread_app());

         uint_ptr nOldLength = (uint_ptr) get_length();
         uint_ptr nOffset = (uint_ptr) (pszSrc - GetString());
         // If 0 <= nOffset <= nOldLength, then pszSrc points into our
         // buffer

         char * pszBuffer = GetBuffer( nLength );
         if( nOffset <= nOldLength )
         {
#if _SECURE_TEMPLATE
            CopyCharsOverlapped( pszBuffer, nLength,
               pszBuffer+nOffset, nLength );
#else
            CopyCharsOverlapped( pszBuffer, pszBuffer+nOffset, nLength );
#endif
         }
         else
         {
#if _SECURE_TEMPLATE
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
      const char * psz2 )
   {
      simple_string s( str1.GetManager() );

      Concatenate( s, str1, str1.get_length(), psz2, StringLength( psz2 ) );

      return( s );
   }

   friend simple_string operator+(
      const char * psz1,
      const simple_string& str2 )
   {
      simple_string s( str2.GetManager() );

      Concatenate( s, psz1, StringLength( psz1 ), str2, str2.get_length() );

      return( s );
   }

   static void __cdecl CopyChars(char* pchDest,const char* pchSrc,strsize nChars ) NOTHROW
   {
      memcpy(pchDest, pchSrc, nChars * sizeof(char));
   }

#if _SECURE_TEMPLATE
   static void __cdecl CopyChars(char* pchDest,size_t nDestLen,const char* pchSrc,strsize nChars ) NOTHROW
   {
#ifdef WINDOWS
      memcpy_s(pchDest, nDestLen * sizeof(char), pchSrc, nChars * sizeof(char));
#else
      memcpy(pchDest, pchSrc, nChars * sizeof(char));
#endif
   }
#endif

   static void __cdecl CopyCharsOverlapped(char* pchDest,const char* pchSrc,strsize nChars ) NOTHROW
   {
      memmove( pchDest, pchSrc, nChars*sizeof( char ) );
   }

#if _SECURE_TEMPLATE
   static void __cdecl CopyCharsOverlapped(char* pchDest,size_t nDestLen,const char* pchSrc,strsize nChars ) NOTHROW
   {
#ifdef WINDOWS
      memmove_s(pchDest, nDestLen * sizeof(char), pchSrc, nChars * sizeof(char));
#else
      memmove(pchDest, pchSrc, nChars * sizeof(char));
#endif
   }
#endif

   static strsize __cdecl StringLength(const char * psz ) NOTHROW
   {
      strsize nLength = 0;
      if( psz != NULL )
      {
         const char* pch = psz;
         while( *pch != 0 )
         {
            nLength++;
            pch++;
         }
      }

      return( nLength );
   }

protected:
   static void __cdecl Concatenate(simple_string& strResult, const char * psz1,strsize nLength1, const char * psz2,strsize nLength2 )
   {
      strsize nNewLength = nLength1+nLength2;
      char * pszBuffer = strResult.GetBuffer( nNewLength );
#if _SECURE_TEMPLATE
      CopyChars( pszBuffer, nLength1, psz1, nLength1 );
      CopyChars( pszBuffer+nLength1, nLength2, psz2, nLength2 );
#else
      CopyChars( pszBuffer, psz1, nLength1 );
      CopyChars( pszBuffer+nLength1, psz2, nLength2 );
#endif
      strResult.ReleaseBufferSetLength( nNewLength );
   }

   DECLSPEC_NO_RETURN static void __cdecl ThrowMemoryException()
   {
      throw hresult_exception(::ca2::get_thread_app(), E_OUTOFMEMORY);
   }

   // Implementation
private:
   void attach(string_data * pData ) NOTHROW
   {
      m_pszData = static_cast< char * >( pData->data() );
   }
   void Fork(strsize nLength )
   {
      string_data* pOldData = get_data();
      strsize nOldLength = pOldData->nDataLength;
      string_data* pNewData = pOldData->pstringmanager->Clone()->allocate( nLength, sizeof( char ) );
      if( pNewData == NULL )
      {
         ThrowMemoryException();
      }
      strsize nCharsToCopy = ((nOldLength < nLength) ? nOldLength : nLength)+1;  // copy '\0'
#if _SECURE_TEMPLATE
      CopyChars( char *( pNewData->data() ), nCharsToCopy, const char *( pOldData->data() ), nCharsToCopy );
#else
      CopyChars((char *) ( pNewData->data() ), (const char *) ( pOldData->data() ), nCharsToCopy );
#endif
      pNewData->nDataLength = nOldLength;
      pOldData->Release();
      attach( pNewData );
   }
   string_data * get_data() const NOTHROW
   {
      return( reinterpret_cast< string_data * >( m_pszData )-1 );
   }
   char * PrepareWrite(strsize nLength )
   {
      string_data * pOldData = get_data();
      long nShared = 1-pOldData->nRefs;  // nShared < 0 means true, >= 0 means false
      strsize nTooShort = pOldData->nAllocLength-nLength;  // nTooShort < 0 means true, >= 0 means false
      if( (nShared|nTooShort) < 0 )  // If either sign bit is set (i.e. either is less than zero), we need to copy data
      {
         PrepareWrite2( nLength );
      }

      return( m_pszData );
   }
   void PrepareWrite2(strsize nLength )
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
         strsize nNewLength = pOldData->nAllocLength;
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
   void Reallocate(strsize nLength )
   {
      string_data* pOldData = get_data();
      ASSERT( pOldData->nAllocLength < nLength );
      string_manager * pstringmanager = pOldData->pstringmanager;
      if ( pOldData->nAllocLength >= nLength || nLength <= 0)
      {
         ThrowMemoryException();
         return;
      }
      string_data* pNewData = pstringmanager->Reallocate( pOldData, nLength, sizeof( char ) );
      if( pNewData == NULL )
      {
         ThrowMemoryException();
      }
      attach( pNewData );
   }

   void set_length(strsize nLength )
   {

      if(nLength < 0 )
         throw error_exception(::ca2::get_thread_app(), "simple_string::set_length nLength < 0");
      if(nLength > get_data()->nAllocLength)
         throw error_exception(::ca2::get_thread_app(), "simple_string::set_length nLength > get_data()->nAllocLength");

      get_data()->nDataLength = nLength;
      m_pszData[nLength] = 0;

   }

   static string_data * __cdecl CloneData(string_data * pData )
   {
      string_data * pNewData = NULL;

      string_manager * pNewStringMgr = pData->pstringmanager->Clone();
      if( !pData->IsLocked() && (pNewStringMgr == pData->pstringmanager) )
      {
         pNewData = pData;
         pNewData->AddRef();
      }
      else
      {
         pNewData = pNewStringMgr->allocate( pData->nDataLength, sizeof( char ) );
         if( pNewData == NULL )
         {
            ThrowMemoryException();
         }
         pNewData->nDataLength = pData->nDataLength;
#if _SECURE_TEMPLATE
         CopyChars( char *( pNewData->data() ), pData->nDataLength+1, const char *( pData->data() ), pData->nDataLength+1 );  // copy '\0'
#else
         CopyChars((char *)( pNewData->data() ), (const char *)( pData->data() ), pData->nDataLength+1 );  // copy '\0'
#endif
      }

      return( pNewData );
   }

public :
   typedef string_buffer CStrBuf;
public:
   char * m_pszData;

};

class CLASS_DECL_c string_buffer
{
public:

   enum
   {
      AUTO_LENGTH = 0x01,  // Automatically determine the new length of the string at release.  The string must be NULL-terminated.
         SET_LENGTH = 0x02,  // set the length of the string object at GetBuffer time
   };

public:
   explicit string_buffer(simple_string& str ) THROWS :
   m_str( str ),
      m_pszBuffer( NULL ),
#ifdef DEBUG
      m_nBufferLength( str.get_length() ),
#endif
      m_nLength( str.get_length() )
   {
      m_pszBuffer = m_str.GetBuffer();
   }

   string_buffer(simple_string & str,strsize nMinLength,uint32_t dwFlags = AUTO_LENGTH ) THROWS :
   m_str( str ),
      m_pszBuffer( NULL ),
#ifdef DEBUG
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

   operator char *() NOTHROW
   {
      return( m_pszBuffer );
   }
   operator const char *() const NOTHROW
   {
      return( m_pszBuffer );
   }

   void set_length(strsize nLength )
   {
      ASSERT( nLength >= 0 );
      ASSERT( nLength <= m_nBufferLength );

      if( nLength < 0 )
         throw invalid_argument_exception(::ca2::get_thread_app());

      m_nLength = nLength;
   }

   // Implementation
private:
   simple_string & m_str;
   char * m_pszBuffer;
   strsize m_nLength;
#ifdef DEBUG
   strsize m_nBufferLength;
#endif

   // Private copy constructor and copy assignment operator to prevent accidental use
private:
   string_buffer( const string_buffer& ) NOTHROW;
   string_buffer& operator=( const string_buffer& ) NOTHROW;
};

///////////////////////////////////////////
// string_data inlining

inline char * string_data::data() NOTHROW
{
   return reinterpret_cast < char *> (this+1);
}

inline void string_data::AddRef() RELEASENOTHROW
{
   ASSERT(nRefs > 0);
   _gen_InterlockedIncrement(&nRefs);
}
inline bool string_data::IsLocked() const NOTHROW
{
   return nRefs < 0;
}
inline bool string_data::IsShared() const NOTHROW
{
   return( nRefs > 1 );
}
inline void string_data::lock() RELEASENOTHROW
{
   ASSERT( nRefs <= 1 );
   nRefs--;  // Locked buffers can't be shared, so no interlocked operation necessary
   if( nRefs == 0 )
   {
      nRefs = -1;
   }
}
inline void string_data::Release() RELEASENOTHROW
{
   ASSERT( nRefs != 0 );

   if( _gen_InterlockedDecrement( &nRefs ) <= 0 )
   {
      pstringmanager->Free( this );
   }
}
inline void string_data::unlock() RELEASENOTHROW
{
   ASSERT( IsLocked() );

   if(IsLocked())
   {
      nRefs++;  // Locked buffers can't be shared, so no interlocked operation necessary
      if( nRefs == 0 )
      {
         nRefs = 1;
      }
   }
}
      




class string;






