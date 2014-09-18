   inline void simple_string::construct(string_manager * pstringmanager)
   {
      ENSURE( pstringmanager != NULL );
      string_data * pData = pstringmanager->GetNilString();
      attach( pData );
   }

   inline simple_string::simple_string(const simple_string & strSrc, string_manager * pstringmanager  )
   {
      if(&strSrc == NULL)
      {
         ENSURE( pstringmanager != NULL );

         string_data* pData = pstringmanager->allocate( 0, sizeof( char ) );
         if( pData == NULL )
         {
            throw_memory_exception();
         }
         attach( pData );
         set_length( 0 );
         return;
      }
      string_data* pSrcData = strSrc.get_data();
      string_data* pNewData = CloneData( pSrcData );
      attach( pNewData );
   }

   inline simple_string::simple_string(const char * pszSrc,string_manager * pstringmanager )
   {
      ENSURE( pstringmanager != NULL );

      strsize nLength = StringLength( pszSrc );
      string_data* pData = pstringmanager->allocate( nLength, sizeof( char ) );
      if( pData == NULL )
      {
         throw_memory_exception();
      }
      attach( pData );
      set_length( nLength );
#if _SECURE_TEMPLATE
      CopyChars( m_pszData, nLength, pszSrc, nLength );
#else
      CopyChars( m_pszData, pszSrc, nLength );
#endif
   }
   inline simple_string::simple_string(const char* pchSrc,strsize nLength,string_manager * pstringmanager )
   {
      ENSURE( pstringmanager != NULL );

      if(pchSrc == NULL && nLength != 0)
         throw invalid_argument_exception(get_thread_app());

      if(nLength < 0)
         nLength = (strsize) strlen(pchSrc);

      string_data * pData = pstringmanager->allocate( nLength, sizeof( char ) );
      if( pData == NULL )
      {
         throw_memory_exception();
      }
      attach( pData );
      set_length( nLength );
#if _SECURE_TEMPLATE
      CopyChars( m_pszData, nLength, pchSrc, nLength );
#else
      CopyChars( m_pszData, pchSrc, nLength );
#endif
   }

      inline const char & simple_string::operator [](strsize iChar ) const
   {
      
      //ASSERT( (iChar >= 0) && (iChar <= get_length()) );  // Indexing the '\0' is OK

      if( (iChar < 0) || (iChar > get_length()) )
         throw invalid_argument_exception(get_thread_app());

      return m_pszData[iChar];

   }
   inline char simple_string::get_at(strsize iChar ) const
   {
      ASSERT( (iChar >= 0) && (iChar <= get_length()) );  // Indexing the '\0' is OK
      if( (iChar < 0) || (iChar > get_length()) )
         throw invalid_argument_exception(get_thread_app());

      return( m_pszData[iChar] );
   }


   inline   void simple_string::set_at(strsize iChar,char ch )
   {
      ASSERT( (iChar >= 0) && (iChar < get_length()) );

      if( (iChar < 0) || (iChar >= get_length()) )
         throw invalid_argument_exception(get_thread_app());

      strsize nLength = get_length();
      char * pszBuffer = GetBuffer();
      pszBuffer[iChar] = ch;
      ReleaseBufferSetLength( nLength );

   }


   inline void simple_string::SetString(const char * pszSrc,strsize nLength )
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
            throw invalid_argument_exception(get_thread_app());

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


      inline void throw_error_exception(const char * psz)
      {
         throw error_exception(get_thread_app(), psz);
      }

   inline void string_buffer::set_length(strsize nLength )
   {
      ASSERT( nLength >= 0 );
      ASSERT( nLength <= m_nBufferLength );

      if( nLength < 0 )
         throw invalid_argument_exception(get_thread_app());

      m_nLength = nLength;
   }



   inline void simple_string::ReleaseBufferSetLength(strsize nNewLength )
   {
      ASSERT( nNewLength >= 0 );
      set_length( nNewLength );
   }
   inline void simple_string::Truncate(strsize nNewLength )
   {
      ASSERT( nNewLength <= get_length() );
      GetBuffer( nNewLength );
      ReleaseBufferSetLength( nNewLength );
   }

   inline void simple_string::SetManager(string_manager * pstringmanager )
   {
      ASSERT( is_empty() );

      string_data * pData = get_data();
      pData->Release();
      pData = pstringmanager->GetNilString();
      attach( pData );
   }
   inline void simple_string::Reallocate(strsize nLength )
   {
      string_data* pOldData = get_data();
      ASSERT( pOldData->nAllocLength < nLength );
      string_manager * pstringmanager = pOldData->pstringmanager;
      if ( pOldData->nAllocLength >= nLength || nLength <= 0)
      {
         throw_memory_exception();
         return;
      }
      string_data* pNewData = pstringmanager->Reallocate( pOldData, nLength, sizeof( char ) );
      if( pNewData == NULL )
      {
         throw_memory_exception();
      }
      attach( pNewData );
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

   _gen_InterlockedDecrement( &nRefs );
   if(nRefs <= 0 )
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
      

inline strsize string::replace_ci(const char * pszOld,const char * pszNew, strsize iStart)
{
   *this = ::str::replace_ci(pszOld, pszNew, *this, iStart);
   return get_length();
}


DECLSPEC_NO_RETURN inline void __cdecl throw_memory_exception()
{
   throw memory_exception(get_thread_app());
}

inline bool string::ends_ci(const string & strSuffixCandidate)
{
   return ::str::ends_ci(*this, strSuffixCandidate);
}











template < class BASE >
strsize stdstring::copy(typename BASE::value_type * s,strsize len,strsize pos) const
{

   strsize thislen = get_length();

   if(pos < 0)
   {

      pos = thislen + pos + 1;

   }

   if(pos < 0)
   {

      len += pos;

      pos = 0;

   }

   if(pos >= thislen)
   {

      return 0;

   }

   len = MIN(len,thislen - pos);

   if(len <= 0)
   {

      return 0;

   }

   memcpy(s,operator const char *() + (pos * sizeof(typename BASE::value_type)),(len * sizeof(typename BASE::value_type)));

   return len;

}


