#include "StdAfx.h"

#undef new


CMapWordToPtr::CMapWordToPtr(INT_PTR nBlockSize)
{
   ASSERT(nBlockSize > 0);
   if (nBlockSize <= 0)
      nBlockSize = 10;   // default size

   m_pHashTable = NULL;
   m_nHashTableSize = 17;  // default size
   m_nCount = 0;
   m_pFreeList = NULL;
   m_pBlocks = NULL;
   m_nBlockSize = nBlockSize;
}

inline UINT CMapWordToPtr::HashKey(WORD key) const
{
   // default identity hash - works for most primitive values
   return ((DWORD)key) >> 4;
}

void CMapWordToPtr::InitHashTable(
   UINT nHashSize, BOOL bAllocNow)
//
// Used to force allocation of a hash table or to override the default
//   hash table size of (which is fairly small)
{
   ASSERT_VALID(this);
   ASSERT(m_nCount == 0);
   ASSERT(nHashSize > 0);
   if (nHashSize == 0)
      nHashSize = 17;   // default value

   if (m_pHashTable != NULL)
   {
      // free hash table
      delete[] m_pHashTable;
      m_pHashTable = NULL;
   }

   if (bAllocNow)
   {
      m_pHashTable = new assoc* [nHashSize];
      memset(m_pHashTable, 0, sizeof(assoc*) * nHashSize);
   }
   m_nHashTableSize = nHashSize;
}

void CMapWordToPtr::remove_all()
{
   ASSERT_VALID(this);



   if (m_pHashTable != NULL)
   {
      // free hash table
      delete[] m_pHashTable;
      m_pHashTable = NULL;
   }

   m_nCount = 0;
   m_pFreeList = NULL;
   m_pBlocks->FreeDataChain();
   m_pBlocks = NULL;
}

CMapWordToPtr::~CMapWordToPtr()
{
   remove_all();
   ASSERT(m_nCount == 0);
}

/////////////////////////////////////////////////////////////////////////////
// Assoc helpers
// same as list implementation except we store assoc's not node's
//    and assoc's are singly linked all the time

CMapWordToPtr::assoc*
CMapWordToPtr::NewAssoc()
{
   if (m_pFreeList == NULL)
   {
      // add another block
      plex* newBlock = plex::create(m_pBlocks, m_nBlockSize, sizeof(CMapWordToPtr::assoc));
      // chain them into free list
      CMapWordToPtr::assoc* pAssoc = (CMapWordToPtr::assoc*) newBlock->data();
      // free in reverse order to make it easier to debug
      pAssoc += m_nBlockSize - 1;
      for (INT_PTR i = m_nBlockSize-1; i >= 0; i--, pAssoc--)
      {
         pAssoc->pNext = m_pFreeList;
         m_pFreeList = pAssoc;
      }
   }
   ASSERT(m_pFreeList != NULL);  // we must have something

   CMapWordToPtr::assoc* pAssoc = m_pFreeList;
   m_pFreeList = m_pFreeList->pNext;
   m_nCount++;
   ASSERT(m_nCount > 0);  // make sure we don't overflow


   pAssoc->key = 0;




   pAssoc->value = 0;

   return pAssoc;
}

void CMapWordToPtr::FreeAssoc(CMapWordToPtr::assoc* pAssoc)
{

   pAssoc->pNext = m_pFreeList;
   m_pFreeList = pAssoc;
   m_nCount--;
   ASSERT(m_nCount >= 0);  // make sure we don't underflow

   // if no more elements, cleanup completely
   if (m_nCount == 0)
      remove_all();
}

CMapWordToPtr::assoc*
CMapWordToPtr::GetAssocAt(WORD key, UINT& nHashBucket, UINT& nHashValue) const
// find association (or return NULL)
{
   nHashValue = HashKey(key);
   nHashBucket = nHashValue % m_nHashTableSize;

   if (m_pHashTable == NULL)
      return NULL;

   // see if it exists
   assoc* pAssoc;
   for (pAssoc = m_pHashTable[nHashBucket]; pAssoc != NULL; pAssoc = pAssoc->pNext)
   {

      if (pAssoc->key == key)
         return pAssoc;

   }
   return NULL;
}



/////////////////////////////////////////////////////////////////////////////

BOOL CMapWordToPtr::Lookup(WORD key, void *& rValue) const
{
   ASSERT_VALID(this);

   UINT nHashBucket, nHashValue;
   assoc* pAssoc = GetAssocAt(key, nHashBucket, nHashValue);
   if (pAssoc == NULL)
      return FALSE;  // not in ::collection::map

   rValue = pAssoc->value;
   return TRUE;
}

void *& CMapWordToPtr::operator[](WORD key)
{
   ASSERT_VALID(this);

   UINT nHashBucket, nHashValue;
   assoc* pAssoc;
   if ((pAssoc = GetAssocAt(key, nHashBucket, nHashValue)) == NULL)
   {
      if (m_pHashTable == NULL)
         InitHashTable(m_nHashTableSize);

      // it doesn't exist, add a new Association
      pAssoc = NewAssoc();

      pAssoc->key = key;
      // 'pAssoc->value' is a constructed object, nothing more

      // put into hash table
      pAssoc->pNext = m_pHashTable[nHashBucket];
      m_pHashTable[nHashBucket] = pAssoc;
   }
   return pAssoc->value;  // return new reference
}


BOOL CMapWordToPtr::RemoveKey(WORD key)
// remove key - return TRUE if removed
{
   ASSERT_VALID(this);

   if (m_pHashTable == NULL)
      return FALSE;  // nothing in the table

   assoc** ppAssocPrev;
   ppAssocPrev = &m_pHashTable[HashKey(key) % m_nHashTableSize];

   assoc* pAssoc;
   for (pAssoc = *ppAssocPrev; pAssoc != NULL; pAssoc = pAssoc->pNext)
   {
      if (pAssoc->key == key)
      {
         // remove it
         *ppAssocPrev = pAssoc->pNext;  // remove from list
         FreeAssoc(pAssoc);
         return TRUE;
      }
      ppAssocPrev = &pAssoc->pNext;
   }
   return FALSE;  // not found
}


/////////////////////////////////////////////////////////////////////////////
// Iterating

void CMapWordToPtr::get_next_assoc(POSITION& rNextPosition,
   WORD& rKey, void *& rValue) const
{
   ASSERT_VALID(this);
   ASSERT(m_pHashTable != NULL);  // never call on is_empty ::collection::map

   assoc* pAssocRet = (assoc*)rNextPosition;
   ASSERT(pAssocRet != NULL);
   if (pAssocRet == NULL)
      return;

   if (pAssocRet == (assoc*) BEFORE_START_POSITION)
   {
      // find the first association
      for (UINT nBucket = 0; nBucket < m_nHashTableSize; nBucket++)
      {
         if ((pAssocRet = m_pHashTable[nBucket]) != NULL)
         {
            break;
         }
      }
      ENSURE(pAssocRet != NULL);  // must find something
   }

   // find next association
   ASSERT(fx_is_valid_address(pAssocRet, sizeof(assoc)));
   assoc* pAssocNext;
   if ((pAssocNext = pAssocRet->pNext) == NULL)
   {
      // go to next bucket

      for (UINT nBucket = (HashKey(pAssocRet->key) % m_nHashTableSize) + 1;

        nBucket < m_nHashTableSize; nBucket++)
         if ((pAssocNext = m_pHashTable[nBucket]) != NULL)
            break;
   }

   rNextPosition = (POSITION) pAssocNext;

   // fill in return data
   rKey = pAssocRet->key;
   rValue = pAssocRet->value;
}


/////////////////////////////////////////////////////////////////////////////
// Diagnostics

#ifdef _DEBUG
void CMapWordToPtr::dump(dump_context & dumpcontext) const
{
   ::radix::object::dump(dumpcontext);

   dumpcontext << "with " << LONGLONG(m_nCount) << " elements";
   if (dumpcontext.GetDepth() > 0)
   {
      // dump in format "[key] -> value"
      WORD key;
      void * val;

      POSITION pos = get_start_position();
      while (pos != NULL)
      {
         get_next_assoc(pos, key, val);
         dumpcontext << "\n\t[" << key << "] = " << val;
      }
   }

   dumpcontext << "\n";
}

void CMapWordToPtr::assert_valid() const
{
   ::radix::object::assert_valid();

   ASSERT(m_nHashTableSize > 0);
   ASSERT(m_nCount == 0 || m_pHashTable != NULL);
      // non-is_empty ::collection::map should have hash table
}
#endif //_DEBUG



// IMPLEMENT_DYNAMIC(CMapWordToPtr, ::radix::object)

/////////////////////////////////////////////////////////////////////////////
