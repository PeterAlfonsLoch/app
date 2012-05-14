#include "framework.h"

#include "elements.h"  // used for special creation

#undef new

base_string_to_string_map::base_string_to_string_map(INT_PTR nBlockSize)
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

void base_string_to_string_map::InitHashTable(
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

void base_string_to_string_map::remove_all()
{
   ASSERT_VALID(this);

   if (m_pHashTable != NULL)
   {
      // destroy elements
      for (UINT nHash = 0; nHash < m_nHashTableSize; nHash++)
      {
         assoc* pAssoc;
         for (pAssoc = m_pHashTable[nHash]; pAssoc != NULL;
           pAssoc = pAssoc->pNext)
         {
            pAssoc->~assoc();
            //DestructElement((string*)&pAssoc->key);  // free up string data
            //DestructElement(&pAssoc->value);

         }
      }

      // free hash table
      delete [] m_pHashTable;
      m_pHashTable = NULL;
   }

   m_nCount = 0;
   m_pFreeList = NULL;
   m_pBlocks->FreeDataChain();
   m_pBlocks = NULL;
}

base_string_to_string_map::~base_string_to_string_map()
{
   remove_all();
   ASSERT(m_nCount == 0);
}

/////////////////////////////////////////////////////////////////////////////
// Assoc helpers
// same as list implementation except we store assoc's not node's
//    and assoc's are singly linked all the time

base_string_to_string_map::assoc*
base_string_to_string_map::NewAssoc(const string & key)
{
   if (m_pFreeList == NULL)
   {
      // add another block
      plex* newBlock = plex::create(m_pBlocks, m_nBlockSize,
                     sizeof(base_string_to_string_map::assoc));
      // chain them into free list
      base_string_to_string_map::assoc* pAssoc =
            (base_string_to_string_map::assoc*) newBlock->data();
      // free in reverse order to make it easier to debug
      pAssoc += m_nBlockSize - 1;
      for (INT_PTR i = m_nBlockSize-1; i >= 0; i--, pAssoc--)
      {
         pAssoc->pNext = m_pFreeList;
         m_pFreeList = pAssoc;
      }
   }
   ASSERT(m_pFreeList != NULL);  // we must have something

   base_string_to_string_map::assoc* pAssoc = m_pFreeList;
   m_pFreeList = m_pFreeList->pNext;
   m_nCount++;
   ASSERT(m_nCount > 0);  // make sure we don't overflow
   ::new(pAssoc) assoc(key);

   return pAssoc;
}

void base_string_to_string_map::FreeAssoc(base_string_to_string_map::assoc* pAssoc)
{
   pAssoc->~assoc();
//   DestructElement((string*)&pAssoc->key);  // free up string data
//   DestructElement(&pAssoc->value);

   pAssoc->pNext = m_pFreeList;
   m_pFreeList = pAssoc;
   m_nCount--;
   ASSERT(m_nCount >= 0);  // make sure we don't underflow

   // if no more elements, cleanup completely
   if (m_nCount == 0)
      remove_all();
}

base_string_to_string_map::assoc*
base_string_to_string_map::GetAssocAt(const string & key, UINT& nHashBucket, UINT& nHashValue) const
// find association (or return NULL)
{
   nHashValue = gen::hash < BASE_ARG_KEY >::HashKey(key);
   nHashBucket = nHashValue % m_nHashTableSize;

   if (m_pHashTable == NULL)
      return NULL;

   // see if it exists
   assoc* pAssoc;
   for (pAssoc = m_pHashTable[nHashBucket]; pAssoc != NULL; pAssoc = pAssoc->pNext)
   {
      if (pAssoc->nHashValue == nHashValue && pAssoc->m_key == key)
         return pAssoc;
   }
   return NULL;
}

/////////////////////////////////////////////////////////////////////////////

const base_string_to_string_map::pair *base_string_to_string_map::PLookup(const string & key) const
{
   ASSERT_VALID(this);

   UINT nHashBucket, nHashValue;
   assoc* pAssoc = GetAssocAt(key, nHashBucket, nHashValue);
   return pAssoc;
}

base_string_to_string_map::pair *base_string_to_string_map::PLookup(const string & key)
{
   ASSERT_VALID(this);

   UINT nHashBucket, nHashValue;
   assoc* pAssoc = GetAssocAt(key, nHashBucket, nHashValue);
   return pAssoc;
}

BOOL base_string_to_string_map::Lookup(const string & key, string & rValue) const
{
   ASSERT_VALID(this);

   UINT nHashBucket, nHashValue;
   assoc* pAssoc = GetAssocAt(key, nHashBucket, nHashValue);
   if (pAssoc == NULL)
      return FALSE;  // not in ::collection::map

   rValue = pAssoc->m_value;
   return TRUE;
}

BOOL base_string_to_string_map::LookupKey(const string & key, string & rKey) const
{
   ASSERT_VALID(this);

   UINT nHashBucket, nHashValue;
   assoc* pAssoc = GetAssocAt(key, nHashBucket, nHashValue);
   if (pAssoc == NULL)
      return FALSE;  // not in ::collection::map

   rKey = pAssoc->m_key;
   return TRUE;
}

string & base_string_to_string_map::operator[](const string & key)
{
   ASSERT_VALID(this);

   UINT nHashBucket, nHashValue;
   assoc* pAssoc;
   if ((pAssoc = GetAssocAt(key, nHashBucket, nHashValue)) == NULL)
   {
      if (m_pHashTable == NULL)
         InitHashTable(m_nHashTableSize);

      // it doesn't exist, add a new Association
      pAssoc = NewAssoc(key);
      pAssoc->nHashValue = nHashValue;
      // 'pAssoc->value' is a constructed object, nothing more

      // put into hash table
      pAssoc->pNext = m_pHashTable[nHashBucket];
      m_pHashTable[nHashBucket] = pAssoc;
   }
   return pAssoc->m_value;  // return new reference
}


BOOL base_string_to_string_map::RemoveKey(const string & key)
// remove key - return TRUE if removed
{
   ASSERT_VALID(this);

   if (m_pHashTable == NULL)
      return FALSE;  // nothing in the table

   assoc** ppAssocPrev;
   UINT nHashValue;
   nHashValue = gen::hash < BASE_ARG_KEY >::HashKey(key);
   ppAssocPrev = &m_pHashTable[nHashValue%m_nHashTableSize];

   assoc* pAssoc;
   for (pAssoc = *ppAssocPrev; pAssoc != NULL; pAssoc = pAssoc->pNext)
   {
      if ((pAssoc->nHashValue == nHashValue) && (pAssoc->m_key == key))
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

const base_string_to_string_map::pair *base_string_to_string_map::PGetFirstAssoc() const
{
   ASSERT_VALID(this);
   ASSERT(m_pHashTable != NULL);  // never call on is_empty ::collection::map

   if( m_nCount == 0 ) return NULL;

   assoc* pAssocRet = NULL;

   // find the first association
   for (UINT nBucket = 0; nBucket < m_nHashTableSize; nBucket++)
      if ((pAssocRet = m_pHashTable[nBucket]) != NULL)
         break;
   ASSERT(pAssocRet != NULL);  // must find something

   return pAssocRet;
}

base_string_to_string_map::pair *base_string_to_string_map::PGetFirstAssoc()
{
   ASSERT_VALID(this);
   ASSERT(m_pHashTable != NULL);  // never call on is_empty ::collection::map

   if( m_nCount == 0 ) return NULL;

   assoc* pAssocRet = NULL;

   // find the first association
   for (UINT nBucket = 0; nBucket < m_nHashTableSize; nBucket++)
      if ((pAssocRet = m_pHashTable[nBucket]) != NULL)
         break;
   ASSERT(pAssocRet != NULL);  // must find something

   return pAssocRet;
}

void base_string_to_string_map::get_next_assoc(POSITION& rNextPosition,
   string & rKey, string & rValue) const
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
   ASSERT(__is_valid_address(pAssocRet, sizeof(assoc)));
   assoc* pAssocNext;
   if ((pAssocNext = pAssocRet->pNext) == NULL)
   {
      // go to next bucket
      for (UINT nBucket = (pAssocRet->nHashValue % m_nHashTableSize) + 1;
        nBucket < m_nHashTableSize; nBucket++)
         if ((pAssocNext = m_pHashTable[nBucket]) != NULL)
            break;
   }

   rNextPosition = (POSITION) pAssocNext;

   // fill in return data
   rKey = pAssocRet->m_key;
   rValue = pAssocRet->m_value;
}

const base_string_to_string_map::pair *base_string_to_string_map::PGetNextAssoc(const pair *pAssoc) const
{
   ASSERT_VALID(this);
   ASSERT(m_pHashTable != NULL);  // never call on is_empty ::collection::map

   assoc* pAssocRet = (assoc*)pAssoc;
   ASSERT(pAssocRet != NULL);

   if(m_pHashTable == NULL || pAssocRet == NULL)
      return NULL;

   ASSERT(pAssocRet != (assoc*)BEFORE_START_POSITION );

   // find next association
   ASSERT(__is_valid_address(pAssocRet, sizeof(assoc)));
   assoc* pAssocNext;
   if ((pAssocNext = pAssocRet->pNext) == NULL)
   {
      // go to next bucket
      for (UINT nBucket = (pAssocRet->nHashValue % m_nHashTableSize) + 1;
        nBucket < m_nHashTableSize; nBucket++)
         if ((pAssocNext = m_pHashTable[nBucket]) != NULL)
            break;
   }

   return pAssocNext;
}

base_string_to_string_map::pair *base_string_to_string_map::PGetNextAssoc(const pair *pAssoc)
{
   ASSERT_VALID(this);
   ASSERT(m_pHashTable != NULL);  // never call on is_empty ::collection::map

   assoc* pAssocRet = (assoc*)pAssoc;
   ASSERT(pAssocRet != NULL);

   if(m_pHashTable == NULL || pAssocRet == NULL)
      return NULL;

   ASSERT(pAssocRet != (assoc*)BEFORE_START_POSITION );

   // find next association
   ASSERT(__is_valid_address(pAssocRet, sizeof(assoc)));
   assoc* pAssocNext;
   if ((pAssocNext = pAssocRet->pNext) == NULL)
   {
      // go to next bucket
      for (UINT nBucket = (pAssocRet->nHashValue % m_nHashTableSize) + 1;
        nBucket < m_nHashTableSize; nBucket++)
         if ((pAssocNext = m_pHashTable[nBucket]) != NULL)
            break;
   }

   return pAssocNext;
}


/////////////////////////////////////////////////////////////////////////////
// Serialization

/*void base_string_to_string_map::Serialize(CArchive& ar)
{
   ASSERT_VALID(this);

   ::radix::object::Serialize(ar);

   if (ar.IsStoring())
   {
      ar.WriteCount(m_nCount);
      if (m_nCount == 0)
         return;  // nothing more to do

      ASSERT(m_pHashTable != NULL);
      for (UINT nHash = 0; nHash < m_nHashTableSize; nHash++)
      {
         assoc* pAssoc;
         for (pAssoc = m_pHashTable[nHash]; pAssoc != NULL;
           pAssoc = pAssoc->pNext)
         {
            ar << pAssoc->key;
            ar << pAssoc->value;
         }
      }
   }
   else
   {
      DWORD_PTR nNewCount = ar.ReadCount();
      string newKey;
      string newValue;
      while (nNewCount--)
      {
         ar >> newKey;
         ar >> newValue;
         set_at(newKey, newValue);
      }
   }
}*/

/////////////////////////////////////////////////////////////////////////////
// Diagnostics

void base_string_to_string_map::dump(dump_context & dumpcontext) const
{
   ::radix::object::dump(dumpcontext);

   dumpcontext << "with " << LONGLONG(m_nCount) << " elements";
   if (dumpcontext.GetDepth() > 0)
   {
      // dump in format "[key] -> value"
      string key;
      string val;

      POSITION pos = get_start_position();
      while (pos != NULL)
      {
         get_next_assoc(pos, key, val);
         dumpcontext << "\n\t[" << key << "] = " << val;
      }
   }

   dumpcontext << "\n";
}

void base_string_to_string_map::assert_valid() const
{
   ::radix::object::assert_valid();

   ASSERT(m_nHashTableSize > 0);
   ASSERT(m_nCount == 0 || m_pHashTable != NULL);
      // non-is_empty ::collection::map should have hash table
}



void base_string_to_string_map::_001ReplaceVars(string & str)
{
   if(this->get_count() == 0)
      return;
   pair * ppair = PGetFirstAssoc();
   string strFind;
   string strReplace;
   while(ppair != NULL)
   {
      strFind.Format("{$%s}", ppair->m_key);
      strReplace = ppair->m_value;
      str.replace(strFind, strReplace);
      ppair = PGetNextAssoc(ppair);
   }
}




string_to_string_map::string_to_string_map(INT_PTR nBlockSize) :
   base_string_to_string_map(nBlockSize)
{
   
}


string_to_string_map::string_to_string_map(const string_to_string_map & map) :
   base_string_to_string_map(dynamic_cast < const base_string_to_string_map & > (map))
{
   
}


string_to_string_map::~string_to_string_map()
{
}



string_to_string_map & string_to_string_map::operator = (const string_to_string_map & map)
{

   if(this != &map)
   {

      base_string_to_string_map::m_nBlockSize = map.base_string_to_string_map::m_nBlockSize;
      attrib_map < base_string_to_string_map >::operator = (map);

   }

   return *this;

}
