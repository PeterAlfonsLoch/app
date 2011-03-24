#include "StdAfx.h"


#define ROUND(x,y) (((x)+(y-1))&~(y-1))
#define ROUND4(x) ROUND(x, 4)

string_manager::string_manager()
{
/*   BOOL bEnable = AfxEnableMemoryTracking(FALSE);
   try
   {
      m_alloca.add(new fixed_alloc(ROUND4(32), 1024));
   }
   catch(...)
   {
   }
   try
   {
      m_alloca.add(new fixed_alloc(ROUND4(64), 1024));
   }
   catch(...)
   {
   }
   try
   {
      m_alloca.add(new fixed_alloc(ROUND4(128), 1024));
   }
   catch(...)
   {
   }
   try
   {
      m_alloca.add(new fixed_alloc(ROUND4(256), 1024));
   }
   catch(...)
   {
   }
   try
   {
      m_alloca.add(new fixed_alloc(ROUND4(512), 1024));
   }
   catch(...)
   {
   }
   try
   {
      m_alloca.add(new fixed_alloc(ROUND4(768), 1024));
   }
   catch(...)
   {
   }
   try
   {
      m_alloca.add(new fixed_alloc(ROUND4(1024), 1024));
   }
   catch(...)
   {
   }
   AfxEnableMemoryTracking(bEnable);*/
   
   m_nil.SetManager(this);
}

string_data * string_manager::allocate( int nChars, int nCharSize )
{
   size_t nTotalSize;
   string_data * pData;
   size_t nDataBytes;

   ASSERT(nCharSize > 0);
   
   if(nChars < 0)
   {
      ASSERT(FALSE);
      return NULL;
   }
   
   nDataBytes = (nChars+1)*nCharSize;
   nTotalSize = sizeof( string_data  )+nDataBytes;
   
   //BOOL bEnable = AfxEnableMemoryTracking(FALSE);
   
   try
   {
//      pData = (string_data *) m_alloca.alloc(nTotalSize);
      pData = (string_data *) ca2_alloc(nTotalSize);
   }
   catch(...)
   {
   }

   //AfxEnableMemoryTracking(bEnable);

   if (pData == NULL)
      return NULL;
   pData->pstringmanager = this;
   pData->nRefs = 1;
   pData->nAllocLength = nChars;
   pData->nDataLength = 0;

   return pData;
}

void string_manager::Free( string_data * pData )
{
   //size_t nTotalSize = sizeof( string_data  ) + pData->nAllocLength + 1;
   //m_alloca.free(pData, nTotalSize);
   ca2_free(pData, 0);
}

string_data * string_manager::Reallocate( string_data * pOldData, int nChars, int nCharSize )
{
   string_data * pNewData = NULL;
   size_t nNewTotalSize;
   size_t nNewDataBytes;
   size_t nOldTotalSize;
   size_t nOldDataBytes;
   
   ASSERT(nCharSize > 0);
   
   if(nChars < 0)
   {
      ASSERT(FALSE);
      return NULL;
   }
   
   nNewDataBytes = (nChars+1)*nCharSize;
   nNewTotalSize = sizeof( string_data  )+nNewDataBytes;
   nOldDataBytes = (pOldData->nAllocLength+1)*nCharSize;
   nOldTotalSize = sizeof( string_data  ) + nOldDataBytes;
   
   //BOOL bEnable = AfxEnableMemoryTracking(FALSE);
   
   try
   {

      //pNewData = (string_data *) m_alloca.realloc(pOldData, nOldTotalSize, nNewTotalSize);
      pNewData = (string_data *) ca2_realloc(pOldData, nNewTotalSize, 0, NULL, 0);

   }
   catch(...)
   {
   }

   //AfxEnableMemoryTracking(bEnable);


   if(pNewData == NULL)
   {
      return NULL;
   }

   pNewData->nAllocLength = nChars;

   return pNewData;
}

string_data * string_manager::GetNilString() 
{
   m_nil.AddRef();
   return &m_nil;
}

string_manager_interface * string_manager::Clone() 
{
   return this;
}









