#pragma once

#undef new


template<class KEY, class VALUE >
class simple_map :
   virtual public ::simple_obj
{
public:
   class pair
   {
   public:
      const KEY m_key;
      VALUE m_value;
      pair(const KEY & key) : m_key(key) {}
   };

   class assoc : public pair
   {
   public:
      friend class simple_map<KEY,VALUE>;
      assoc* pNext;
      UINT nHashValue;  // needed for efficient iteration
      assoc(const KEY & key) : pair(key) {}
   };

   void construct(count nBlockSize = 10);
   simple_map(count nBlockSize = 10);
   //template < pair pairs[]>
   simple_map(pair pairs[]);

   count get_count() const;

   // Lookup
   bool Lookup(KEY & key, VALUE& rValue) const;
   const pair *PLookup(KEY & key) const;
   pair *PLookup(KEY & key);


   VALUE * pget(KEY & key);

// Operations
   // Lookup and add if not there
   VALUE& operator[](KEY & key);

   // add a new (key, value) pair
   void set_at(KEY key, VALUE newValue);

   // removing existing (key, ?) pair
   bool remove_key(KEY key);
   void remove_all();

   // iterating all (key, value) pairs
   POSITION get_start_position() const;

   const pair *PGetFirstAssoc() const;
   pair *PGetFirstAssoc();

   void get_next_assoc(POSITION& rNextPosition, KEY& rKey, VALUE& rValue) const;

   const pair *PGetNextAssoc(const pair *pAssocRet) const;
   pair *PGetNextAssoc(const pair *pAssocRet);

   // advanced features for derived classes
   UINT GetHashTableSize() const;
   void InitHashTable(UINT hashSize, bool bAllocNow = TRUE);


   void clear();


   VALUE get(KEY & argkey, VALUE & valueDefault);

// Implementation
protected:
   assoc** m_pHashTable;
   UINT m_nHashTableSize;
   count m_nCount;
   assoc* m_pFreeList;
   count m_nBlockSize;

   assoc* NewAssoc(KEY & key);
   void FreeAssoc(assoc*);
   assoc* GetAssocAt(KEY &, UINT&, UINT&) const;

public:
   virtual ~simple_map();

};


template<class KEY,  class VALUE>
inline count simple_map< KEY,  VALUE >::get_count() const
   { return m_nCount; }


template<class KEY,  class VALUE>
inline void simple_map< KEY,  VALUE >::set_at(KEY key, VALUE newValue)
   { (*this)[key] = newValue; }

template<class KEY,  class VALUE>
inline POSITION simple_map< KEY,  VALUE >::get_start_position() const
   { return (m_nCount == 0) ? NULL : BEFORE_START_POSITION; }

template<class KEY,  class VALUE>
const typename simple_map< KEY,  VALUE >::pair* simple_map< KEY,  VALUE >::PGetFirstAssoc() const
{
   if(m_nCount == 0) return NULL;

   assoc* pAssocRet = (assoc*)BEFORE_START_POSITION;

   // find the first association
   for (UINT nBucket = 0; nBucket < m_nHashTableSize; nBucket++)
      if ((pAssocRet = m_pHashTable[nBucket]) != NULL)
         break;

   return pAssocRet;
}

template<class KEY,  class VALUE>
typename simple_map< KEY,  VALUE >::pair* simple_map< KEY,  VALUE >::PGetFirstAssoc()
{
   if(m_nCount == 0) return NULL;

   assoc* pAssocRet = (assoc*)BEFORE_START_POSITION;

   // find the first association
   for (UINT nBucket = 0; nBucket < m_nHashTableSize; nBucket++)
      if ((pAssocRet = m_pHashTable[nBucket]) != NULL)
         break;
   return pAssocRet;
}

template<class KEY,  class VALUE>
inline UINT simple_map< KEY,  VALUE >::GetHashTableSize() const
   { return m_nHashTableSize; }

/////////////////////////////////////////////////////////////////////////////
// simple_map< KEY,  VALUE > out-of-line functions
template<class KEY,  class VALUE>
void simple_map< KEY,  VALUE >::construct(count nBlockSize)
{
   m_pHashTable = NULL;
   m_nHashTableSize = 17;  // default size
   m_nCount = 0;
   m_pFreeList = NULL;
   m_nBlockSize = nBlockSize;
}

template<class KEY,  class VALUE>
simple_map< KEY,  VALUE >::simple_map(count nBlockSize)
{
   construct(nBlockSize);
}

template<class KEY,  class VALUE>
simple_map< KEY,  VALUE >::simple_map(pair pairs[])
{
   construct();
   int32_t iCount = sizeof(pairs) / sizeof(pair);
   for(int32_t i = 0; i < iCount; i++)
   {
      set_at(pairs[i].m_key, pairs[i].m_value);
   }
}

template<class KEY,  class VALUE>
void simple_map< KEY,  VALUE >::InitHashTable(
   UINT nHashSize, bool bAllocNow)
//
// Used to force allocation of a hash table or to override the default
//   hash table size of (which is fairly small)
{

   if (m_pHashTable != NULL)
   {
      // free hash table
      delete[] m_pHashTable;
      m_pHashTable = NULL;
   }

   if (bAllocNow)
   {
      m_pHashTable = new assoc* [nHashSize];
      memset_dup(m_pHashTable, 0, sizeof(assoc*) * nHashSize);
   }
   m_nHashTableSize = nHashSize;
}

template<class KEY,  class VALUE>
void simple_map< KEY,  VALUE >::clear()
{
   remove_all();
}


template<class KEY,  class VALUE>
void simple_map< KEY,  VALUE >::remove_all()
{
   if (m_pHashTable != NULL)
   {
      // destroy elements (values and keys)
      for (UINT nHash = 0; nHash < m_nHashTableSize; nHash++)
      {
         assoc* pAssoc;
         for (pAssoc = m_pHashTable[nHash]; pAssoc != NULL;
            pAssoc = pAssoc->pNext)
         {
            pAssoc->assoc::~assoc();
            //DestructElements<VALUE>(&pAssoc->value, 1);
            //DestructElements<KEY>((KEY*)&pAssoc->key, 1);
         }
      }
   }

   // free hash table
   delete[] m_pHashTable;
   m_pHashTable = NULL;

   m_nCount = 0;
   m_pFreeList = NULL;
}

template<class KEY,  class VALUE>
simple_map< KEY,  VALUE >::~simple_map()
{
   remove_all();
}

template<class KEY,  class VALUE>
typename simple_map< KEY,  VALUE >::assoc*
simple_map< KEY,  VALUE >::NewAssoc(KEY & key)
{
   if (m_pFreeList == NULL)
   {
      // chain them into free list
      typename simple_map::assoc* pAssoc = (typename simple_map::assoc *) _ca_alloc(m_nBlockSize * sizeof(simple_map::assoc));
      // free in reverse order to make it easier to debug
      pAssoc += m_nBlockSize - 1;
      for (index i = m_nBlockSize-1; i >= 0; i--, pAssoc--)
      {
         pAssoc->pNext = m_pFreeList;
         m_pFreeList = pAssoc;
      }
   }

   typename simple_map::assoc* pAssoc = m_pFreeList;

   // zero the primitive::memory
   typename simple_map::assoc* pTemp = pAssoc->pNext;
   memset_dup( pAssoc, 0, sizeof(simple_map::assoc) );
   pAssoc->pNext = pTemp;

   m_pFreeList = m_pFreeList->pNext;
   m_nCount++;
   ::new(pAssoc) assoc(key);
   return pAssoc;
}

template<class KEY,  class VALUE>
void simple_map< KEY,  VALUE >::FreeAssoc(assoc* pAssoc)
{
   pAssoc->assoc::~assoc();
   pAssoc->pNext = m_pFreeList;
   m_pFreeList = pAssoc;
   m_nCount--;

   // if no more elements, cleanup completely
   if (m_nCount == 0)
      remove_all();
}

template<class KEY,  class VALUE>
typename simple_map< KEY,  VALUE >::assoc*
simple_map< KEY,  VALUE >::GetAssocAt(KEY & key, UINT& nHashBucket, UINT& nHashValue) const
// find association (or return NULL)
{
   nHashValue = simple_HashKey<KEY>(key);
   nHashBucket = nHashValue % m_nHashTableSize;

   if (m_pHashTable == NULL)
      return NULL;

   // see if it exists
   assoc* pAssoc;
   for (pAssoc = m_pHashTable[nHashBucket]; pAssoc != NULL; pAssoc = pAssoc->pNext)
   {
      if (pAssoc->nHashValue == nHashValue && simple_CompareElements(&pAssoc->m_key, &key))
         return pAssoc;
   }
   return NULL;
}

template<class KEY,  class VALUE>
bool simple_map< KEY,  VALUE >::Lookup(KEY & key, VALUE& rValue) const
{
   UINT nHashBucket, nHashValue;
   assoc* pAssoc = GetAssocAt(key, nHashBucket, nHashValue);
   if (pAssoc == NULL)
      return FALSE;  // not in simple_map

   rValue = pAssoc->m_value;
   return TRUE;
}

template<class KEY,  class VALUE>
const typename simple_map< KEY,  VALUE >::pair* simple_map< KEY,  VALUE >::PLookup(KEY & key) const
{


   UINT nHashBucket, nHashValue;
   assoc* pAssoc = GetAssocAt(key, nHashBucket, nHashValue);
   return pAssoc;
}

template<class KEY,  class VALUE>
typename simple_map< KEY,  VALUE >::pair* simple_map< KEY,  VALUE >::PLookup(KEY & key)
{
   UINT nHashBucket, nHashValue;
   assoc* pAssoc = GetAssocAt(key, nHashBucket, nHashValue);
   return pAssoc;
}

template<class KEY,  class VALUE>
VALUE * simple_map< KEY,  VALUE >::pget(KEY & key)
{
   pair * p = PLookup(key);
   if(p)
      return &p->m_value;
   else
      return NULL;
}

template<class KEY,  class VALUE>
VALUE& simple_map< KEY,  VALUE >::operator[](KEY & key)
{

   UINT nHashBucket, nHashValue;
   assoc* pAssoc;
   if ((pAssoc = GetAssocAt(key, nHashBucket, nHashValue)) == NULL)
   {
      if (m_pHashTable == NULL)
         InitHashTable(m_nHashTableSize);

      // it doesn't exist, add a new Association
      pAssoc = NewAssoc(key);
      pAssoc->nHashValue = nHashValue;
      //'pAssoc->value' is a constructed object, nothing more

      // put into hash table
      pAssoc->pNext = m_pHashTable[nHashBucket];
      m_pHashTable[nHashBucket] = pAssoc;
   }
   return pAssoc->m_value;  // return new reference
}

template<class KEY,  class VALUE>
bool simple_map< KEY,  VALUE >::remove_key(KEY key)
// remove key - return TRUE if removed
{
   if (m_pHashTable == NULL)
      return FALSE;  // nothing in the table

   UINT nHashValue;
   assoc** ppAssocPrev;
   nHashValue = simple_HashKey<KEY>(key);
   ppAssocPrev = &m_pHashTable[nHashValue%m_nHashTableSize];

   assoc* pAssoc;
   for (pAssoc = *ppAssocPrev; pAssoc != NULL; pAssoc = pAssoc->pNext)
   {
      if ((pAssoc->nHashValue == nHashValue) && simple_CompareElements(&pAssoc->m_key, &key))
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

template<class KEY,  class VALUE>
void simple_map< KEY,  VALUE >::get_next_assoc(POSITION& rNextPosition,
   KEY& rKey, VALUE& rValue) const
{

   assoc* pAssocRet = (assoc*)rNextPosition;

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
      if(pAssocRet == NULL)
      {
         rNextPosition = NULL;
         return;
      }
   }

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

template<class KEY,  class VALUE>
const typename simple_map< KEY,  VALUE >::pair*
simple_map< KEY,  VALUE >::PGetNextAssoc(const typename simple_map< KEY,  VALUE >::pair* pPairRet) const
{
   assoc* pAssocRet = (assoc*)pPairRet;

   if(m_pHashTable == NULL || pAssocRet == NULL)
      return NULL;

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

template<class KEY,  class VALUE>
typename simple_map< KEY,  VALUE >::pair*
simple_map< KEY,  VALUE >::PGetNextAssoc(const typename simple_map< KEY,  VALUE >::pair* pPairRet)
{
   assoc* pAssocRet = (assoc*)pPairRet;

   if(m_pHashTable == NULL || pAssocRet == NULL)
      return NULL;

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

   template < class KEY, class VALUE >
   VALUE simple_map < KEY,  VALUE > ::
      get(KEY & argkey, VALUE & valueDefault)
   {
      pair * ppair = PLookup(argkey);
      if(ppair == NULL)
         return valueDefault;
      else
         return ppair->m_value;
   }

/*
template<class KEY,  class VALUE>
void simple_map< KEY,  VALUE >::Serialize(CArchive& ar)
{
   ::radix::object::Serialize(ar);

   if (ar.IsStoring())
   {
      ar.WriteCount(m_nCount);
      if (m_nCount == 0)
         return;  // nothing more to do

      for (UINT nHash = 0; nHash < m_nHashTableSize; nHash++)
      {
         assoc* pAssoc;
         for (pAssoc = m_pHashTable[nHash]; pAssoc != NULL;
            pAssoc = pAssoc->pNext)
         {
            KEY* pKey;
            VALUE* pValue;
            //
            // in some cases the & operator might be overloaded, and we cannot use it to
            // obtain the address of a given object.  We then use the following trick to
            // get the address
            //
            pKey = reinterpret_cast< KEY* >( &reinterpret_cast< int32_t& >( const_cast< KEY& > ( static_cast< const KEY& >( pAssoc->key ) ) ) );
            pValue = reinterpret_cast< VALUE* >( &reinterpret_cast< int32_t& >( static_cast< VALUE& >( pAssoc->value ) ) );
            SerializeElements<KEY>(ar, pKey, 1);
            SerializeElements<VALUE>(ar, pValue, 1);
         }
      }
   }
   else
   {
      dword_ptr nNewCount = ar.ReadCount();
      while (nNewCount--)
      {
         KEY newKey[1];
         VALUE newValue[1];
         SerializeElements<KEY>(ar, newKey, 1);
         SerializeElements<VALUE>(ar, newValue, 1);
         set_at(newKey[0], newValue[0]);
      }
   }
}
*/


































template < class VALUE >
class simple_string_map :
   virtual public ::simple_obj
{
public:
   class pair
   {
   public:
      const vsstring m_vsstring;
      VALUE m_value;
      pair(const vsstring & str) : m_vsstring(str) {}
   };

   class assoc : public pair
   {
   public:
      assoc* pNext;
      UINT nHashValue;  // needed for efficient iteration
      assoc(const vsstring &  str) : pair(str) {}
   };

   void construct(count nBlockSize = 10);
   simple_string_map(count nBlockSize = 10);
   //template < pair pairs[]>
   simple_string_map(pair pairs[]);

   count get_count() const;

   // Lookup
   bool Lookup(vsstring &  str, VALUE& rValue) const;
   const pair *PLookup(vsstring &  str) const;
   pair *PLookup(vsstring &  str);


   VALUE * pget(vsstring &  str);

   // Operations
   // Lookup and add if not there
   VALUE& operator[](vsstring &  str);
   VALUE& operator[](const char * psz);

   // add a new (vsstring, value) pair
   void set_at(vsstring str, VALUE newValue);

   // removing existing (vsstring, ?) pair
   bool remove_vsstring(vsstring  str);
   void remove_all();

   // iterating all (vsstring, value) pairs
   POSITION get_start_position() const;

   const pair *PGetFirstAssoc() const;
   pair *PGetFirstAssoc();

   void get_next_assoc(POSITION& rNextPosition, vsstring& rvsstring, VALUE& rValue) const;

   const pair *PGetNextAssoc(const pair *pAssocRet) const;
   pair *PGetNextAssoc(const pair *pAssocRet);

   // advanced features for derived classes
   UINT GetHashTableSize() const;
   void InitHashTable(UINT hashSize, bool bAllocNow = TRUE);


   VALUE get(vsstring & argvsstring, VALUE & valueDefault);

// Implementation
protected:
   assoc** m_pHashTable;
   UINT m_nHashTableSize;
   count m_nCount;
   assoc* m_pFreeList;
   count m_nBlockSize;

   assoc* NewAssoc(vsstring & str);
   void FreeAssoc(assoc*);
   assoc* GetAssocAt(vsstring &, UINT&, UINT&) const;

public:
   virtual ~simple_string_map();

};


template < class VALUE>
inline count simple_string_map < VALUE >::get_count() const
   { return m_nCount; }


template < class VALUE>
inline void simple_string_map < VALUE >::set_at(vsstring vsstring, VALUE newValue)
   { (*this)[vsstring] = newValue; }

template < class VALUE>
inline POSITION simple_string_map < VALUE >::get_start_position() const
   { return (m_nCount == 0) ? NULL : BEFORE_START_POSITION; }

template < class VALUE>
const typename simple_string_map < VALUE >::pair* simple_string_map < VALUE >::PGetFirstAssoc() const
{
   if(m_nCount == 0) return NULL;

   assoc* pAssocRet = (assoc*)BEFORE_START_POSITION;

   // find the first association
   for (UINT nBucket = 0; nBucket < m_nHashTableSize; nBucket++)
      if ((pAssocRet = m_pHashTable[nBucket]) != NULL)
         break;

   return pAssocRet;
}

template < class VALUE>
typename simple_string_map < VALUE >::pair* simple_string_map < VALUE >::PGetFirstAssoc()
{
   if(m_nCount == 0) return NULL;

   assoc* pAssocRet = (assoc*)BEFORE_START_POSITION;

   // find the first association
   for (UINT nBucket = 0; nBucket < m_nHashTableSize; nBucket++)
      if ((pAssocRet = m_pHashTable[nBucket]) != NULL)
         break;
   return pAssocRet;
}

template < class VALUE>
inline UINT simple_string_map < VALUE >::GetHashTableSize() const
   { return m_nHashTableSize; }

/////////////////////////////////////////////////////////////////////////////
// simple_string_map < VALUE > out-of-line functions
template < class VALUE>
void simple_string_map < VALUE >::construct(count nBlockSize)
{
   m_pHashTable = NULL;
   m_nHashTableSize = 17;  // default size
   m_nCount = 0;
   m_pFreeList = NULL;
   m_nBlockSize = nBlockSize;
}

template < class VALUE>
simple_string_map < VALUE >::simple_string_map(count nBlockSize)
{
   construct(nBlockSize);
}

template < class VALUE>
simple_string_map < VALUE >::simple_string_map(pair pairs[])
{
   construct();
   int32_t iCount = sizeof(pairs) / sizeof(pair);
   for(int32_t i = 0; i < iCount; i++)
   {
      set_at(pairs[i].m_vsstring, pairs[i].m_value);
   }
}

template < class VALUE>
void simple_string_map < VALUE >::InitHashTable(
   UINT nHashSize, bool bAllocNow)
//
// Used to force allocation of a hash table or to override the default
//   hash table size of (which is fairly small)
{

   if (m_pHashTable != NULL)
   {
      // free hash table
      delete[] m_pHashTable;
      m_pHashTable = NULL;
   }

   if (bAllocNow)
   {
      m_pHashTable = new assoc* [nHashSize];
      memset_dup(m_pHashTable, 0, sizeof(assoc*) * nHashSize);
   }
   m_nHashTableSize = nHashSize;
}

template < class VALUE>
void simple_string_map < VALUE >::remove_all()
{
   if (m_pHashTable != NULL)
   {
      // destroy elements (values and vsstrings)
      for (UINT nHash = 0; nHash < m_nHashTableSize; nHash++)
      {
         assoc* pAssoc;
         for (pAssoc = m_pHashTable[nHash]; pAssoc != NULL;
            pAssoc = pAssoc->pNext)
         {
            pAssoc->assoc::~assoc();
            //DestructElements<VALUE>(&pAssoc->value, 1);
            //DestructElements<vsstring>((vsstring*)&pAssoc->vsstring, 1);
         }
      }
   }

   // free hash table
   delete[] m_pHashTable;
   m_pHashTable = NULL;

   m_nCount = 0;
   m_pFreeList = NULL;
}

template < class VALUE>
simple_string_map < VALUE >::~simple_string_map()
{
   remove_all();
}

template < class VALUE>
typename simple_string_map < VALUE >::assoc*
simple_string_map < VALUE >::NewAssoc(vsstring & vsstring)
{
   if (m_pFreeList == NULL)
   {
      // chain them into free list
      typename simple_string_map::assoc* pAssoc = (typename simple_string_map::assoc *) _ca_alloc(m_nBlockSize * sizeof(typename simple_string_map::assoc));
      // free in reverse order to make it easier to debug
      pAssoc += m_nBlockSize - 1;
      for (index i = m_nBlockSize-1; i >= 0; i--, pAssoc--)
      {
         pAssoc->pNext = m_pFreeList;
         m_pFreeList = pAssoc;
      }
   }

   typename simple_string_map::assoc* pAssoc = m_pFreeList;

   // zero the primitive::memory
   typename simple_string_map::assoc* pTemp = pAssoc->pNext;
   memset_dup( pAssoc, 0, sizeof(typename simple_string_map::assoc) );
   pAssoc->pNext = pTemp;

   m_pFreeList = m_pFreeList->pNext;
   m_nCount++;
   ::new(pAssoc) assoc(vsstring);
   return pAssoc;
}

template < class VALUE>
void simple_string_map < VALUE >::FreeAssoc(assoc* pAssoc)
{
   pAssoc->assoc::~assoc();
   pAssoc->pNext = m_pFreeList;
   m_pFreeList = pAssoc;
   m_nCount--;

   // if no more elements, cleanup completely
   if (m_nCount == 0)
      remove_all();
}

template < class VALUE>
typename simple_string_map < VALUE >::assoc*
simple_string_map < VALUE >::GetAssocAt(vsstring & str, UINT& nHashBucket, UINT& nHashValue) const
// find association (or return NULL)
{
   nHashValue = simple_HashKey < > (str);
   nHashBucket = nHashValue % m_nHashTableSize;

   if (m_pHashTable == NULL)
      return NULL;

   // see if it exists
   assoc* pAssoc;
   for (pAssoc = m_pHashTable[nHashBucket]; pAssoc != NULL; pAssoc = pAssoc->pNext)
   {
      if (pAssoc->nHashValue == nHashValue && simple_CompareElements(&pAssoc->m_vsstring, &str))
         return pAssoc;
   }
   return NULL;
}

template < class VALUE>
bool simple_string_map < VALUE >::Lookup(vsstring & str, VALUE& rValue) const
{
   UINT nHashBucket, nHashValue;
   assoc* pAssoc = GetAssocAt(str, nHashBucket, nHashValue);
   if (pAssoc == NULL)
      return FALSE;  // not in simple_string_map

   rValue = pAssoc->m_value;
   return TRUE;
}

template < class VALUE>
const typename simple_string_map < VALUE >::pair* simple_string_map < VALUE >::PLookup(vsstring & str) const
{


   UINT nHashBucket, nHashValue;
   assoc* pAssoc = GetAssocAt(str, nHashBucket, nHashValue);
   return pAssoc;
}

template < class VALUE>
typename simple_string_map < VALUE >::pair* simple_string_map < VALUE >::PLookup(vsstring & str)
{
   UINT nHashBucket, nHashValue;
   assoc* pAssoc = GetAssocAt(str, nHashBucket, nHashValue);
   return pAssoc;
}

template < class VALUE>
VALUE * simple_string_map < VALUE >::pget(vsstring & str)
{
   pair * p = PLookup(str);
   if(p)
      return &p->m_value;
   else
      return NULL;
}

template < class VALUE>
VALUE& simple_string_map < VALUE >::operator[](vsstring & str)
{

   UINT nHashBucket, nHashValue;
   assoc* pAssoc;
   if ((pAssoc = GetAssocAt(str, nHashBucket, nHashValue)) == NULL)
   {
      if (m_pHashTable == NULL)
         InitHashTable(m_nHashTableSize);

      // it doesn't exist, add a new Association
      pAssoc = NewAssoc(str);
      pAssoc->nHashValue = nHashValue;
      //'pAssoc->value' is a constructed object, nothing more

      // put into hash table
      pAssoc->pNext = m_pHashTable[nHashBucket];
      m_pHashTable[nHashBucket] = pAssoc;
   }
   return pAssoc->m_value;  // return new reference
}

template < class VALUE>
VALUE& simple_string_map < VALUE >::operator[](const char * psz)
{
   vsstring str(psz);
   return operator[](str);
}

template < class VALUE>
bool simple_string_map < VALUE >::remove_vsstring(vsstring str)
// remove vsstring - return TRUE if removed
{
   if (m_pHashTable == NULL)
      return FALSE;  // nothing in the table

   UINT nHashValue;
   assoc** ppAssocPrev;
   nHashValue = simple_HashKey <> (str);
   ppAssocPrev = &m_pHashTable[nHashValue%m_nHashTableSize];

   assoc* pAssoc;
   for (pAssoc = *ppAssocPrev; pAssoc != NULL; pAssoc = pAssoc->pNext)
   {
      if ((pAssoc->nHashValue == nHashValue) && simple_CompareElements(&pAssoc->m_vsstring, &str))
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

template < class VALUE>
void simple_string_map < VALUE >::get_next_assoc(POSITION& rNextPosition, vsstring & rStr, VALUE& rValue) const
{

   assoc* pAssocRet = (assoc*)rNextPosition;

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
      if(pAssocRet == NULL)
      {
         rNextPosition = NULL;
         return;
      }
   }

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
   rStr= pAssocRet->m_vsstring;
   rValue = pAssocRet->m_value;
}

template < class VALUE>
const typename simple_string_map < VALUE >::pair*
simple_string_map < VALUE >::PGetNextAssoc(const typename simple_string_map < VALUE >::pair* pPairRet) const
{
   assoc* pAssocRet = (assoc*)pPairRet;

   if(m_pHashTable == NULL || pAssocRet == NULL)
      return NULL;

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

template < class VALUE>
typename simple_string_map < VALUE >::pair*
simple_string_map < VALUE >::PGetNextAssoc(const typename simple_string_map < VALUE >::pair* pPairRet)
{
   assoc* pAssocRet = (assoc*)pPairRet;

   if(m_pHashTable == NULL || pAssocRet == NULL)
      return NULL;

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

   template < class VALUE >
   VALUE simple_string_map < VALUE > ::get(vsstring & rStr, VALUE & valueDefault)
   {
      pair * ppair = PLookup(rStr);
      if(ppair == NULL)
         return valueDefault;
      else
         return ppair->m_value;
   }

/*
template < class VALUE>
void simple_string_map < VALUE >::Serialize(CArchive& ar)
{
   ::radix::object::Serialize(ar);

   if (ar.IsStoring())
   {
      ar.WriteCount(m_nCount);
      if (m_nCount == 0)
         return;  // nothing more to do

      for (UINT nHash = 0; nHash < m_nHashTableSize; nHash++)
      {
         assoc* pAssoc;
         for (pAssoc = m_pHashTable[nHash]; pAssoc != NULL;
            pAssoc = pAssoc->pNext)
         {
            vsstring* pvsstring;
            VALUE* pValue;
            //
            // in some cases the & operator might be overloaded, and we cannot use it to
            // obtain the address of a given object.  We then use the following trick to
            // get the address
            //
            pvsstring = reinterpret_cast< vsstring* >( &reinterpret_cast< int32_t& >( const_cast< vsstring& > ( static_cast< const vsstring& >( pAssoc->vsstring ) ) ) );
            pValue = reinterpret_cast< VALUE* >( &reinterpret_cast< int32_t& >( static_cast< VALUE& >( pAssoc->value ) ) );
            SerializeElements<vsstring>(ar, pvsstring, 1);
            SerializeElements<VALUE>(ar, pValue, 1);
         }
      }
   }
   else
   {
      dword_ptr nNewCount = ar.ReadCount();
      while (nNewCount--)
      {
         vsstring newvsstring[1];
         VALUE newValue[1];
         SerializeElements<vsstring>(ar, newvsstring, 1);
         SerializeElements<VALUE>(ar, newValue, 1);
         set_at(newvsstring[0], newValue[0]);
      }
   }
}
*/



template < class VALUE >
class simple_string_attrib_map :
   virtual public simple_string_map < VALUE >
{
public:
   simple_string_attrib_map();
   simple_string_attrib_map(const simple_string_attrib_map & simple_map);

   simple_string_attrib_map & operator = (const simple_string_attrib_map & simple_map);
};

template < class VALUE >
simple_string_attrib_map < VALUE >::simple_string_attrib_map()
{
}

template < class VALUE >
simple_string_attrib_map < VALUE >::simple_string_attrib_map(const simple_string_attrib_map & attribmap)
{
   operator = (attribmap);
}

template < class VALUE >
simple_string_attrib_map < VALUE > & simple_string_attrib_map < VALUE >::operator = (const simple_string_attrib_map & attribmap)
{
   if(this != &attribmap)
   {
      simple_string_map < VALUE > ::remove_all();
      const typename simple_string_map < VALUE > ::pair * ppair = attribmap.PGetFirstAssoc();
      while(ppair != NULL)
      {
         set_at(ppair->m_key, ppair->m_value);
         ppair  = attribmap.PGetNextAssoc(ppair);
      }
   }
   return *this;
}














































template<class KEY,  class VALUE>
class simple_attrib_map :
   virtual public simple_map < KEY, VALUE >
{
public:
   simple_attrib_map();
   simple_attrib_map(const simple_attrib_map & simple_map);

   simple_attrib_map & operator = (const simple_attrib_map & simple_map);
};

template<class KEY,  class VALUE>
simple_attrib_map< KEY,  VALUE >::simple_attrib_map()
{
}

template<class KEY,  class VALUE>
simple_attrib_map< KEY,  VALUE >::simple_attrib_map(const simple_attrib_map & attribmap)
{
   operator = (attribmap);
}

template<class KEY,  class VALUE>
simple_attrib_map< KEY,  VALUE > & simple_attrib_map< KEY,  VALUE >::operator = (const simple_attrib_map & attribmap)
{
   if(this != &attribmap)
   {
      simple_map < KEY, VALUE > ::remove_all();
      const typename simple_map < KEY, VALUE > ::pair * ppair = attribmap.PGetFirstAssoc();
      while(ppair != NULL)
      {
         set_at(ppair->m_key, ppair->m_value);
         ppair  = attribmap.PGetNextAssoc(ppair);
      }
   }
   return *this;
}


class CLASS_DECL_c simple_int_to_string :
   virtual public simple_attrib_map < int32_t, vsstring >
{
public:
};


class CLASS_DECL_c simple_string_to_pointer :
   virtual public simple_string_map < void * >
{
public:
};


class CLASS_DECL_c simple_string_to_intptr :
   virtual public simple_string_map < int_ptr >
{
public:
};

class CLASS_DECL_c simple_string_to_string :
   virtual public simple_string_map < vsstring >
{
public:
};
