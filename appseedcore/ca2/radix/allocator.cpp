#include "StdAfx.h"


#include "common.h"
#include "allocate.h"


#pragma comment(lib, "advapi32.lib")
#pragma warning(disable : 4711)   // function selected for automatic inline expansion

bool allocator::Init(const CHAR *pszFileName, DWORD dwMaxSize)
{
   // We're relying on syncronization provided by the startup code (CRT DllMain/WinMain)
   close();

   ATLASSERT(!m_hMap && !m_pBufferStart);

   HANDLE hThreadToken = NULL;
   try
   {
      if( !(GetVersion()&0x80000000) )
      {
         // If we're being loaded while impersonating a different client,
         // we need to revert to self before we open the shared primitive::memory section
         BOOL bOpen = OpenThreadToken(GetCurrentThread(), TOKEN_IMPERSONATE|TOKEN_DUPLICATE, TRUE, &hThreadToken);
         if( !bOpen || hThreadToken != NULL )
         {
            if( !RevertToSelf() )
            {
               CloseHandle(hThreadToken);
               hThreadToken = NULL;
               throw 0;
            }
         }
      }

      // Use a NULL SECURITY_ATTRIBUTES structure to get the default DACL.
      m_hMap = CreateFileMappingA(INVALID_HANDLE_VALUE, NULL,
         PAGE_READWRITE | SEC_RESERVE, 0, dwMaxSize, pszFileName);
      if(!m_hMap)
      {
         throw 0;
      }

      DWORD dwErr = ::GetLastError();

      m_pBufferStart = (BYTE *)
         MapViewOfFile(m_hMap, FILE_MAP_ALL_ACCESS, 0, 0, 0);
      if(!m_pBufferStart)
      {
         throw 0;
      }

      SYSTEM_INFO si;
      GetSystemInfo(&si);

      if(dwErr == ERROR_ALREADY_EXISTS)
      {
         m_pProcess = reinterpret_cast<trace_process *>(m_pBufferStart);

         // Looks like it's already mapped into this process space.
         // Let's do some checking...
         if(( m_pProcess==NULL ) || ( m_pProcess->Base()==NULL ) ||
            ( 0 != memcmp(m_pBufferStart, m_pProcess->Base(), m_pProcess->m_dwFrontAlloc )))
         {
            // something's not right
            throw 0;
         }

         // sure looks valid
         m_pProcess->IncRef();
         m_pProcess = static_cast<trace_process *>(m_pProcess->Base());

         UnmapViewOfFile(m_pBufferStart);
         m_pBufferStart = reinterpret_cast<BYTE *>(m_pProcess);
      }
      else
      {
         // This is just in case sizeof(trace_process) is
         // ever > dwPageSize (doubtful that could ever
         // happen, but it's easy enough to avoid here)
         DWORD dwCurrAlloc = si.dwPageSize;
         while(dwCurrAlloc < sizeof(trace_process))
         {
            dwCurrAlloc += si.dwPageSize;
         }

         if(!VirtualAlloc(m_pBufferStart, dwCurrAlloc, MEM_COMMIT, PAGE_READWRITE))
         {
            throw 0;
         }

#undef new
         m_pProcess = new(m_pBufferStart) trace_process(dwMaxSize);
#define new DEBUG_NEW
         m_pProcess->m_dwFrontAlloc = dwCurrAlloc;
         m_pProcess->m_dwCurrFront = sizeof(trace_process);
      }
      m_dwPageSize = si.dwPageSize;
      m_bValid = true;
   }
   catch(...)
   {
      if( hThreadToken != NULL )
      {
         // Go back to impersonating whomever we were impersonating
         BOOL bSuccess;
         bSuccess = SetThreadToken(NULL, hThreadToken);
         ATLASSERT( bSuccess );
         CloseHandle( hThreadToken );
      }

      if(!m_bValid)
      {
         if(m_pBufferStart)
         {
            UnmapViewOfFile(m_pBufferStart);
            m_pBufferStart = NULL;
         }

         if(m_hMap)
         {
            CloseHandle(m_hMap);
            m_hMap = NULL;
         }
      }
   }
   return m_bValid;
}

bool allocator::open(const CHAR *pszFileName)
{
   close();

   __try
   {
      m_hMap = OpenFileMappingA(FILE_MAP_WRITE, FALSE, pszFileName);
      if(!m_hMap)
         __leave;

      m_pBufferStart = (BYTE *)
         MapViewOfFile(m_hMap, FILE_MAP_ALL_ACCESS, 0, 0, 0);
      if(!m_pBufferStart)
         __leave;

      m_pProcess = reinterpret_cast<trace_process *>(m_pBufferStart);
      m_pProcess->IncRef();

      SYSTEM_INFO si;
      GetSystemInfo(&si);
      m_dwPageSize = si.dwPageSize;

      m_bValid = true;
   }
   __finally
   {
      if(!m_bValid)
      {
         if(m_pBufferStart)
         {
            UnmapViewOfFile(m_pBufferStart);
            m_pBufferStart = NULL;
         }
         if(m_hMap)
         {
            CloseHandle(m_hMap);
            m_hMap = NULL;
         }

         m_pProcess = NULL;
      }
   }
   return m_bValid;
}

void allocator::close(bool bForceUnmap)
{
   if(m_bValid)
   {
      if(m_pProcess->DecRef() == 0 || bForceUnmap)
         UnmapViewOfFile(m_pBufferStart);
      m_pBufferStart = NULL;

      CloseHandle(m_hMap);
      m_hMap = NULL;

      m_bValid = false;
   }
}

trace_module *allocator::GetModule(int iModule) const
{
   if( iModule == -1 )
   {
      return NULL;
   }
        int modcnt = m_pProcess->ModuleCount();
   ATLASSERT(iModule < modcnt);
   if(iModule >=0 && iModule < modcnt)
   {
      BYTE *pb = reinterpret_cast<BYTE *>(m_pProcess) + sizeof(trace_process);
      return reinterpret_cast<trace_module *>(pb) + iModule;
   }
   else
      return NULL;
}

/*
trace_category *allocator::GetCategory(unsigned nModule, unsigned nCategory) const
{
   ATLASSERT(nModule < m_pProcess->ModuleCount());

   if(nModule < m_pProcess->ModuleCount())
   {
      BYTE *pb = reinterpret_cast<BYTE *>(m_pProcess) + sizeof(trace_process);
      trace_module *pModule = reinterpret_cast<trace_module *>(pb) + nModule;

      if(IsValidCategoryIndex(pModule->m_nFirstCategory))
      {
         unsigned nOldIndex, nIndex = pModule->m_nFirstCategory;
         trace_category *pCategory;
         do
         {
            pCategory = GetCategoryByIndex(nIndex);
            if(pCategory->m_nCategory == nCategory)
               return pCategory;

            nOldIndex = nIndex;
            nIndex = pCategory->m_nNext;
         }
         while(nOldIndex != nIndex);
      }
   }
   return NULL;
}
*/

/*
bool allocator::IsValidCategoryIndex(unsigned nIndex) const
{
   return nIndex < m_pProcess->CategoryCount();
}
*/

trace_category *allocator::GetCategory(int iCategory) const
{
   if(iCategory == m_pProcess->CategoryCount())
      return NULL;

   ATLASSERT((iCategory < m_pProcess->CategoryCount()) || (iCategory == -1));
   trace_category *pCategory = NULL;
   if(iCategory >= 0)
   {
      BYTE *pb = reinterpret_cast<BYTE *>(m_pProcess) + m_pProcess->MaxSize();
      pCategory = reinterpret_cast<trace_category *>(pb) - iCategory - 1;
   }
   return pCategory;
}

int allocator::GetCategoryCount(int iModule) const
{
   UINT nCategories = 0;
   trace_module* pModule = GetModule(iModule);
   ATLASSERT(pModule != NULL);
   if(pModule != NULL)
   {
      nCategories = GetCategoryCount( *pModule );
   }

   return nCategories;
}

int allocator::GetCategoryCount(const trace_module& rModule) const
{
   UINT nCategories = 0;
   int iCategory = rModule.m_iFirstCategory;
   while( iCategory != -1 )
   {
      trace_category* pCategory = GetCategory( iCategory );
      if( pCategory == NULL )
         break;
      nCategories++;
      iCategory = pCategory->m_iNextCategory;
   }
   return nCategories;
}

int allocator::GetModuleCount() const
{
   ATLASSERT(m_pProcess);
   return m_pProcess->ModuleCount();
}

const ULONG kModuleBatchSize = 10;

bool allocator::FindModule(const WCHAR *pszModulePath, unsigned *pnModule) const
{
   if(pnModule)
      for(int i = 0; i < m_pProcess->ModuleCount(); i++)
         if(0 == _wcsicmp(GetModule(i)->Path(), pszModulePath))
         {
            *pnModule = i;
            return true;
         }

   return false;
}

int allocator::AddModule(HINSTANCE hInst)
{
   trace_process *pProcess = GetProcess();
   ATLASSERT(pProcess);
   int iFoundModule = -1;
   while( iFoundModule == -1 )
   {
      for(int iModule = 0; (iModule < pProcess->ModuleCount()) && (iFoundModule == -1); iModule++)
      {
         trace_module *pModule = GetModule(iModule);
         ATLASSERT(pModule != NULL);
         bool bFound = pModule->TryAllocate();
         if( bFound )
         {
            pModule->Reset(hInst);
            pModule->m_iFirstCategory = -1;
            pModule->MarkValid( pProcess->GetNextCookie() );
            iFoundModule = iModule;
         }
      }
      if( iFoundModule == -1 )
      {
         ULONG nNewAllocSize = kModuleBatchSize*sizeof( trace_module );
         void * pNewModules = reinterpret_cast<BYTE *>(pProcess) + pProcess->m_dwFrontAlloc;
         VirtualAlloc(pNewModules, nNewAllocSize, MEM_COMMIT, PAGE_READWRITE);
         pProcess->m_dwFrontAlloc += nNewAllocSize;
         for( ULONG iNewModule = 0; iNewModule < kModuleBatchSize; iNewModule++ )
         {
            trace_module* pNewModule = static_cast< trace_module* >( pNewModules )+iNewModule;
#undef new
            new( pNewModule ) trace_module;
#define new DEBUG_NEW
         }
         pProcess->IncModuleCount( kModuleBatchSize );
      }
   }

   return iFoundModule;
}

const ULONG kCategoryBatchSize = 10;

int allocator::AddCategory(int iModule, const CHAR *szCategoryName)
{
   int iFoundCategory = -1;
   trace_process *pProcess = GetProcess();
   ATLASSERT(pProcess);
   trace_module *pModule = GetModule(iModule);
   if(pModule)
   {
      pModule->TryAddRef();

      while( iFoundCategory == -1 )
      {
         for(int iCategory = 0; (iCategory < pProcess->CategoryCount()) && (iFoundCategory == -1); iCategory++)
         {
            trace_category *pCategory = GetCategory( iCategory );
            ATLASSERT(pCategory != NULL);
            bool bFound = pCategory->TryAllocate();
            if( bFound )
            {
               pCategory->Reset( szCategoryName, pModule->m_nCookie );
               pCategory->m_iNextCategory = pModule->m_iFirstCategory;
               pCategory->MarkValid( pProcess->GetNextCookie() );
               pModule->m_iFirstCategory = iCategory;
               ::InterlockedIncrement( &pModule->m_nCategories );
               iFoundCategory = iCategory;
            }
         }

         if( iFoundCategory == -1 )
         {
            ULONG nNewAllocSize = kCategoryBatchSize*sizeof( trace_category );
            void * pNewCategories = reinterpret_cast<BYTE *>(pProcess) + pProcess->MaxSize()-pProcess->m_dwBackAlloc-nNewAllocSize;
            VirtualAlloc(pNewCategories, nNewAllocSize, MEM_COMMIT, PAGE_READWRITE);
            pProcess->m_dwBackAlloc += nNewAllocSize;
            for( ULONG iNewCategory = 0; iNewCategory < kCategoryBatchSize; iNewCategory++ )
            {
               trace_category* pNewCategory = static_cast< trace_category* >( pNewCategories )+iNewCategory;
#undef new
               new( pNewCategory ) trace_category;
#define new DEBUG_NEW
            }
            pProcess->IncCategoryCount( kCategoryBatchSize );
         }
      }

      pModule->Release();
   }

   pProcess->m_bLoaded = false;

   return( iFoundCategory );
}

bool allocator::RemoveModule(int iModule)
{
   trace_module* pModule = GetModule(iModule);
   if(pModule)
   {
      int iCategory = pModule->m_iFirstCategory;
      while( iCategory != -1 )
      {
         trace_category* pCategory = GetCategory( iCategory );
         if( pCategory == NULL )
         {
            pModule->Release();
            return false;
         }
         iCategory = pCategory->m_iNextCategory;
         ::InterlockedDecrement( &pModule->m_nCategories );
         pModule->m_iFirstCategory = iCategory;
         pCategory->Release();
      }

      pModule->Release();
      return true;
   }
   return false;
}

void allocator::CleanUp()
{
   close();
}

void allocator::TakeSnapshot()
{
   if( m_bSnapshot )
   {
      ReleaseSnapshot();
   }

   int nModules = GetModuleCount();
   for( int iModule = 0; iModule < nModules; iModule++ )
   {
      trace_module* pModule = GetModule( iModule );
      bool bValidModule = pModule->TryAddRef();
      if( bValidModule )
      {
         CTraceSnapshot::CModuleInfo module;
         module.m_dwModule = DWORD_PTR( iModule )+1;
         module.m_iFirstCategory = m_snapshot.m_adwCategories.get_size();
         module.m_nCategories = pModule->m_nCategories;

         int iCategory = pModule->m_iFirstCategory;
         bool bCategoriesValid = true;
         int nCategories = 0;
         while( (iCategory != -1) && bCategoriesValid )
         {
            trace_category* pCategory = GetCategory( iCategory );
            bool bValidCategory = pCategory->TryAddRef();
            if( bValidCategory )
            {
               if( pCategory->m_nModuleCookie != pModule->m_nCookie )
               {
                  bValidCategory = false;
                  pCategory->Release();
               }
               else
               {
                  m_snapshot.m_adwCategories.add( DWORD_PTR( iCategory ) );
                  nCategories++;
                  iCategory = pCategory->m_iNextCategory;
               }
            }
            if( !bValidCategory )
            {
               bCategoriesValid = false;
            }
         }
         if( !bCategoriesValid )
         {
            for( int iCategoryIndex = nCategories-1; iCategoryIndex >= 0; iCategoryIndex-- )
            {
               DWORD_PTR dwCategory = m_snapshot.m_adwCategories[module.m_iFirstCategory+iCategoryIndex];
               m_snapshot.m_adwCategories.remove_at( module.m_iFirstCategory+iCategoryIndex );
               GetCategory( int( dwCategory ) )->Release();
            }
            pModule->Release();
         }
         else
         {
            m_snapshot.m_aModules.add( module );
         }
      }
   }

   m_bSnapshot = true;
}

void allocator::ReleaseSnapshot()
{
   if( m_bSnapshot )
   {
      for( int iModule = 0; iModule < m_snapshot.m_aModules.get_size(); iModule++ )
      {
         trace_module *pModule = GetModule( int( m_snapshot.m_aModules[iModule].m_dwModule-1 ) );
         if( pModule != NULL )
            pModule->Release();
      }
      for( int iCategory = 0; iCategory < m_snapshot.m_adwCategories.get_size(); iCategory++ )
      {
         trace_category *pCategory = GetCategory( int( m_snapshot.m_adwCategories[iCategory] ) );
         if( pCategory != NULL )
            pCategory->Release();
      }
      m_bSnapshot = false;
   }
}
