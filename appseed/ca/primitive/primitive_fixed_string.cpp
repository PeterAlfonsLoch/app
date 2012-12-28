#include "framework.h"


/*


fixed_string_log_interface * fixed_string_manager::s_pLog = NULL;


fixed_string_manager::fixed_string_manager(string_data * pData,int32_t nChars, string_manager * pMgr) throw() :
   m_pData( pData ),
   m_pMgr( pMgr )
{
   m_pData->nRefs = -1;
   m_pData->nDataLength = 0;
   m_pData->nAllocLength = nChars;
   m_pData->pstringmanager = this;
   *(wchar_t*)( m_pData->data() ) = 0;
}
fixed_string_manager::~fixed_string_manager() throw()
{
}

// string_manager
string_data  * fixed_string_manager::allocate(strsize nChars, int32_t nCharSize ) throw()
{
   ASSUME( m_pData->nRefs == -1 );
   ASSUME( m_pData->nDataLength == 0 );
   if( nChars > m_pData->nAllocLength )
   {
      if( s_pLog != NULL )
      {
         s_pLog->OnAllocateSpill( nChars, m_pData->nAllocLength, m_pData );
      }
      string_data * pData = m_pMgr->allocate( nChars, nCharSize );
      if( pData != NULL )
      {
         pData->pstringmanager = this;
         pData->nRefs = -1;  // Locked
      }

      return pData;
   }

   m_pData->nRefs = -1;  // Locked
   m_pData->nDataLength = 0;
   m_pData->pstringmanager = this;

   return m_pData;
}
void fixed_string_manager::Free( string_data  * pData ) throw()
{
   ASSERT( pData->nRefs <= 0 );
   if( pData != m_pData )
   {
      // Must have been allocated from the backup manager
      pData->pstringmanager = m_pMgr;
      m_pMgr->Free( pData );
   }

   // Always make sure the fixed buffer is ready to be used as the nil string.
   m_pData->nRefs = -1;
   m_pData->nDataLength = 0;
   *static_cast< char* >( m_pData->data() ) = 0;
}

string_data * fixed_string_manager::Reallocate( string_data * pData, strsize nChars, int32_t nCharSize ) throw()
{
   string_data * pNewData;

   ASSERT( pData->nRefs < 0 );
   if( pData != m_pData )
   {
      pData->pstringmanager = m_pMgr;
      pNewData = m_pMgr->Reallocate( pData, nChars, nCharSize );
      if( pNewData == NULL )
      {
         pData->pstringmanager = this;
      }
      else
      {
         pNewData->pstringmanager = this;
      }
   }
   else
   {
      if( nChars > pData->nAllocLength )
      {
         if( s_pLog != NULL )
         {
            s_pLog->OnReallocateSpill( nChars, pData->nAllocLength, pData );
         }
         pNewData = m_pMgr->allocate( nChars, nCharSize );
         if( pNewData == NULL )
         {
            return NULL;
         }

         // copy the string data
               ::gen::memcpy_s( pNewData->data(), nChars*nCharSize,
            pData->data(), (pData->nAllocLength+1)*nCharSize );
         pNewData->nRefs = pData->nRefs;  // Locked
         pNewData->pstringmanager = this;
         pNewData->nDataLength = pData->nDataLength;
      }
      else
      {
         // Don't do anything if the buffer is already big enough.
         pNewData = pData;
      }
   }

   return pNewData;
}
string_data * fixed_string_manager::GetNilString() throw()
{
   ASSUME( m_pData->nRefs == -1 );
   ASSUME( m_pData->nDataLength == 0 );

   return m_pData;
}
string_manager* fixed_string_manager::Clone() throw()
{
   return m_pMgr;
}

string_manager* fixed_string_manager::GetBackupManager() const throw()
{
   return m_pMgr;
}




   
fixed_string_log::fixed_string_log() throw()
{
   fixed_string_manager::s_pLog = this;
}
fixed_string_log::~fixed_string_log() throw()
{
   fixed_string_manager::s_pLog = NULL;
}




*/



