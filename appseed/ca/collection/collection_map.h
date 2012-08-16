#pragma once


#undef new


namespace collection
{


   template <class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH = gen::hash < ARG_KEY > , class EQUALS = gen::equals_type_arg_type < KEY, ARG_KEY > >
   class map :
      virtual public ::radix::object
   {
   public:

      typedef KEY          BASE_KEY;
      typedef ARG_KEY      BASE_ARG_KEY;
      typedef VALUE        BASE_VALUE;
      typedef ARG_VALUE    BASE_ARG_VALUE;
      typedef HASH         BASE_HASH;
      typedef EQUALS       BASE_EQUALS;


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
         friend class map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS>;
         assoc* pNext;
         UINT nHashValue;  // needed for efficient iteration
         assoc(const KEY & key) : pair(key) {}
      };


      class iterator
      {
      public:


         pair *   m_ppair;
         map *    m_pmap;


         iterator()
         {
            m_ppair  = NULL;
            m_pmap   = NULL;
         }

         iterator(const iterator & iterator)
         {
            m_ppair  = iterator.m_ppair;
            m_pmap   = iterator.m_pmap;
         }

         iterator(pair * ppair, map * pmap)
         {
            m_ppair  = ppair;
            m_pmap   = pmap;
         }

         pair * operator -> ()
         {
            return m_ppair;
         }

         const pair * operator -> () const
         {
            return m_ppair;
         }


         iterator & operator ++ ()
         {
            if(m_ppair != NULL && m_pmap != NULL)
               m_ppair = m_pmap->PGetNextAssoc(m_ppair);
            return *this;
         }

         iterator operator ++ (int)
         {
            if(m_ppair != NULL && m_pmap != NULL)
               m_ppair = m_pmap->PGetNextAssoc(m_ppair);
            return *this;
         }

         bool operator == (const iterator & it) const
         {
            if(this == &it)
               return true;
            if(m_ppair == NULL && it.m_ppair == NULL && it.m_pmap == NULL)
               return true;
            if(m_pmap != it.m_pmap)
               return false;
            return m_ppair == it.m_ppair;
         }

         bool operator != (const iterator & it) const
         {
            return !operator == (it);
         }

         iterator & operator = (const iterator & it)
         {
            if(this != &it)
            {
               m_pmap         = it.m_pmap;
               m_ppair        = it.m_ppair;
            }
            return *this;
         }

      };


      class const_iterator
      {
      public:


         pair *   m_ppair;
         map *    m_pmap;


         const_iterator()
         {
            m_ppair  = NULL;
            m_pmap   = NULL;
         }

         const_iterator(const iterator & iterator)
         {
            m_ppair  = iterator.m_ppair;
            m_pmap   = iterator.m_pmap;
         }

         const_iterator(const const_iterator & const_iterator)
         {
            m_ppair  = const_iterator.m_ppair;
            m_pmap   = const_iterator.m_pmap;
         }

         const_iterator(pair * ppair, map * pmap)
         {
            m_ppair  = ppair;
            m_pmap   = pmap;
         }

         const pair * operator -> () const
         {
            return m_ppair;
         }


         const_iterator & operator ++ ()
         {
            if(m_ppair != NULL && m_pmap != NULL)
               m_ppair = m_pmap->PGetNextAssoc(m_ppair);
            return *this;
         }

         const_iterator operator ++ (int)
         {
            if(m_ppair != NULL && m_pmap != NULL)
               m_ppair = m_pmap->PGetNextAssoc(m_ppair);
            return *this;
         }

         bool operator == (const const_iterator & it) const
         {
            if(this == &it)
               return true;
            if(m_ppair == NULL && it.m_ppair == NULL && it.m_pmap == NULL)
               return true;
            if(m_pmap != it.m_pmap)
               return false;
            return m_ppair == it.m_ppair;
         }

         bool operator != (const const_iterator & it) const
         {
            return !operator == (it);
         }

         const_iterator & operator = (const const_iterator & it)
         {
            if(this != &it)
            {
               m_pmap         = it.m_pmap;
               m_ppair        = it.m_ppair;
            }
            return *this;
         }

      };



      iterator begin()
      {
         return iterator(PGetFirstAssoc(), this);
      }


      iterator end()
      {
         return iterator(NULL, this);
      }

      void construct(::count nBlockSize = 10);
      map(::count nBlockSize = 10);
      map(pair pairs[], int iCount);

      ::count get_count() const;
      ::count get_size() const;
      ::count size() const;
      ::count count() const;
      bool is_empty() const;

      // Lookup
      bool Lookup(ARG_KEY key, VALUE& rValue) const;
      const pair *PLookup(ARG_KEY key) const;
      pair *PLookup(ARG_KEY key);


      VALUE * pget(ARG_KEY key);

   // Operations
      // Lookup and add if not there
      VALUE& operator[](ARG_KEY key);

      // add a new (key, value) pair
      void set_at(ARG_KEY key, ARG_VALUE newValue);

      // removing existing (key, ?) pair
      bool remove_key(ARG_KEY key);
      void erase(iterator it);
      ::count erase(const KEY & key);
      // the following funtion is available in a sort_map
      //void erase ( iterator first, iterator last );
      void remove_all();
      void clear();
      

      ::count count(const KEY & t) const;
      bool has(const KEY & t) const;
      bool contains(const KEY & t) const;

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


      VALUE get(ARG_KEY argkey, ARG_VALUE valueDefault);


      pair * next(pair * & ppair)
      {
         if(ppair == NULL)
         {
            ppair = PGetFirstAssoc();
         }
         else
         {
            ppair = PGetNextAssoc(ppair);
         }
         return ppair;
      }

      const pair * next(const pair * & ppair) const
      {
         if(ppair == NULL)
         {
            ppair = PGetFirstAssoc();
         }
         else
         {
            ppair = PGetNextAssoc(ppair);
         }
         return ppair;
      }


      void set(map & map)
      {
         pair * ppair = NULL;
         while(map.next(ppair) != NULL)
         {
            set_at(ppair->m_key, ppair->m_value);
         }
      }


   // Implementation
   protected:
      assoc** m_pHashTable;
      UINT m_nHashTableSize;
      ::count m_nCount;
      assoc* m_pFreeList;
      struct ::plex* m_pBlocks;
      ::count m_nBlockSize;

      assoc* NewAssoc(ARG_KEY key);
      void FreeAssoc(assoc*);
      assoc* GetAssocAt(ARG_KEY, UINT&, UINT&) const;

   public:
      virtual ~map();
   //   void Serialize(CArchive&);
      void dump(dump_context&) const;
      void assert_valid() const;
   };

   /////////////////////////////////////////////////////////////////////////////
   // map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS> inline functions



   template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS >
   inline ::count map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS>::get_count() const
      { return m_nCount; }

   template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS >
   inline ::count map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS>::get_size() const
      { return m_nCount; }

   template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS >
   inline count map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS>::count() const
      { return m_nCount; }

   template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS >
   inline count map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS>::size() const
      { return m_nCount; }

   template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS >
   inline bool map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS>::is_empty() const
      { return m_nCount == 0; }

   template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS >
   inline void map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS>::set_at(ARG_KEY key, ARG_VALUE newValue)
      { (*this)[key] = newValue; }

   template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS >
   inline POSITION map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS>::get_start_position() const
      { return (m_nCount == 0) ? NULL : BEFORE_START_POSITION; }

   template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS >
   const typename map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS>::pair* map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS>::PGetFirstAssoc() const
   {
      ASSERT_VALID(this);
      if(m_nCount == 0) return NULL;

      ASSERT(m_pHashTable != NULL);  // never call on is_empty map

      assoc* pAssocRet = (assoc*)BEFORE_START_POSITION;

      // find the first association
      for (UINT nBucket = 0; nBucket < m_nHashTableSize; nBucket++)
         if ((pAssocRet = m_pHashTable[nBucket]) != NULL)
            break;
      ASSERT(pAssocRet != NULL);  // must find something

      return pAssocRet;
   }

   template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS >
   typename map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS>::pair* map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS>::PGetFirstAssoc()
   {
      ASSERT_VALID(this);
      if(m_nCount == 0) return NULL;

      ASSERT(m_pHashTable != NULL);  // never call on is_empty map

      assoc* pAssocRet = (assoc*)BEFORE_START_POSITION;

      // find the first association
      for (UINT nBucket = 0; nBucket < m_nHashTableSize; nBucket++)
         if ((pAssocRet = m_pHashTable[nBucket]) != NULL)
            break;
      ASSERT(pAssocRet != NULL);  // must find something

      return pAssocRet;
   }

   template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS >
   inline UINT map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS>::GetHashTableSize() const
      { return m_nHashTableSize; }

   /////////////////////////////////////////////////////////////////////////////
   // map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS> out-of-line functions
   template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS >
   void map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS>::construct(::count nBlockSize)
   {
      ASSERT(nBlockSize > 0);

      m_pHashTable = NULL;
      m_nHashTableSize = 17;  // default size
      m_nCount = 0;
      m_pFreeList = NULL;
      m_pBlocks = NULL;
      m_nBlockSize = nBlockSize;
   }

   template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS >
   map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS>::map(::count nBlockSize)
   {
      construct(nBlockSize);
   }

   template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS >
   map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS>::map(pair pairs[], int iCount)
   {
      construct();
      for(int i = 0; i < iCount; i++)
      {
         set_at(pairs[i].m_key, pairs[i].m_value);
      }
   }

   template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS >
   void map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS>::InitHashTable(
      UINT nHashSize, bool bAllocNow)
   //
   // Used to force allocation of a hash table or to override the default
   //   hash table size of (which is fairly small)
   {
      ASSERT_VALID(this);
      ASSERT(m_nCount == 0);
      ASSERT(nHashSize > 0);

      if (m_pHashTable != NULL)
      {
         // free hash table
         delete[] m_pHashTable;
         m_pHashTable = NULL;
      }

      if (bAllocNow)
      {
         m_pHashTable = new assoc* [nHashSize];
         ENSURE(m_pHashTable != NULL);
         memset(m_pHashTable, 0, sizeof(assoc*) * nHashSize);
      }
      m_nHashTableSize = nHashSize;
   }

   template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS >
   void map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS>::remove_all()
   {
      ASSERT_VALID(this);

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
      m_pBlocks->FreeDataChain();
      m_pBlocks = NULL;
   }

   template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS >
   inline void map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS>::clear()
   {
      remove_all();
   }

   template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS >
   map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS>::~map()
   {
      remove_all();
      ASSERT(m_nCount == 0);
   }

   template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS >
   typename map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS>::assoc*
   map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS>::NewAssoc(ARG_KEY key)
   {
      if (m_pFreeList == NULL)
      {
         // add another block
         plex* newBlock = plex::create(m_pBlocks, m_nBlockSize, sizeof(map::assoc));
         // chain them into free list
         map::assoc* pAssoc = (map::assoc*) newBlock->data();
         // free in reverse order to make it easier to debug
         pAssoc += m_nBlockSize - 1;
         for (index i = m_nBlockSize-1; i >= 0; i--, pAssoc--)
         {
            pAssoc->pNext = m_pFreeList;
            m_pFreeList = pAssoc;
         }
      }
      ENSURE(m_pFreeList != NULL);  // we must have something

      map::assoc* pAssoc = m_pFreeList;

      // zero the primitive::memory
      map::assoc* pTemp = pAssoc->pNext;
      memset( pAssoc, 0, sizeof(map::assoc) );
      pAssoc->pNext = pTemp;

      m_pFreeList = m_pFreeList->pNext;
      m_nCount++;
      ASSERT(m_nCount > 0);  // make sure we don't overflow
   #if !core_level_1
      ::new(pAssoc) assoc(key);
   #else
      ConstructElements < KEY > (&pAssoc->m_key, 1);
      pAssoc->m_key = key;
      ConstructElements < VALUE > (&pAssoc->m_value, 1);
   #endif
      return pAssoc;
   }

   template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS >
   void map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS>::FreeAssoc(assoc* pAssoc)
   {
   #if !core_level_1
      pAssoc->assoc::~assoc();
   #else
      DestructElements<VALUE>(&pAssoc->m_value, 1);
      DestructElements<KEY>(&pAssoc->m_key, 1);
   #endif
      pAssoc->pNext = m_pFreeList;
      m_pFreeList = pAssoc;
      m_nCount--;
      ASSERT(m_nCount >= 0);  // make sure we don't underflow

      // if no more elements, cleanup completely
      if (m_nCount == 0)
         remove_all();
   }

   template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS >
   typename map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS>::assoc*
   map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS>::GetAssocAt(ARG_KEY key, UINT& nHashBucket, UINT& nHashValue) const
   // find association (or return NULL)
   {
      nHashValue = HASH::HashKey((ARG_KEY) key);
      nHashBucket = nHashValue % m_nHashTableSize;

      if (m_pHashTable == NULL)
         return NULL;

      // see if it exists
      assoc* pAssoc;
      for (pAssoc = m_pHashTable[nHashBucket]; pAssoc != NULL; pAssoc = pAssoc->pNext)
      {
         if (pAssoc->nHashValue == nHashValue && EQUALS::CompareElements(&pAssoc->m_key, key))
            return pAssoc;
      }
      return NULL;
   }

   template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS >
   bool map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS>::Lookup(ARG_KEY key, VALUE& rValue) const
   {
      //ASSERT_VALID(this);

      UINT nHashBucket, nHashValue;
      assoc* pAssoc = GetAssocAt(key, nHashBucket, nHashValue);
      if (pAssoc == NULL)
         return FALSE;  // not in map

      rValue = pAssoc->m_value;
      return TRUE;
   }

   template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS >
   const typename map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS>::pair* map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS>::PLookup(ARG_KEY key) const
   {
      //ASSERT_VALID(this);

      UINT nHashBucket, nHashValue;
      assoc* pAssoc = GetAssocAt(key, nHashBucket, nHashValue);
      return pAssoc;
   }

   template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS >
   typename map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS>::pair* map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS>::PLookup(ARG_KEY key)
   {
      //ASSERT_VALID(this);

      UINT nHashBucket, nHashValue;
      assoc* pAssoc = GetAssocAt(key, nHashBucket, nHashValue);
      return pAssoc;
   }

   template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS >
   VALUE * map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS>::pget(ARG_KEY key)
   {
      pair * p = PLookup(key);
      if(p)
         return &p->m_value;
      else
         return NULL;
   }

   template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS >
   VALUE& map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS>::operator[](ARG_KEY key)
   {
      ASSERT_VALID(this);

      UINT nHashBucket, nHashValue;
      assoc* pAssoc;
      if ((pAssoc = GetAssocAt(key, nHashBucket, nHashValue)) == NULL)
      {
         if (m_pHashTable == NULL)
            InitHashTable(m_nHashTableSize);

         ENSURE(m_pHashTable);
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

   template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS >
   bool map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS>::remove_key(ARG_KEY key)
   // remove key - return TRUE if removed
   {
      ASSERT_VALID(this);

      if (m_pHashTable == NULL)
         return FALSE;  // nothing in the table

      UINT nHashValue;
      assoc** ppAssocPrev;
      nHashValue = HASH::HashKey(key);
      ppAssocPrev = &m_pHashTable[nHashValue%m_nHashTableSize];

      assoc* pAssoc;
      for (pAssoc = *ppAssocPrev; pAssoc != NULL; pAssoc = pAssoc->pNext)
      {
         if ((pAssoc->nHashValue == nHashValue) && EQUALS::CompareElements(&pAssoc->m_key, key))
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

   template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS >
   inline ::count map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS>::count(const KEY & key) const
   {

      return this->PLookup(key) != NULL ? 1 : 0;

   }

   template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS >
   bool map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS>::has(const KEY & key) const
   {

      return this->PLookup(key) != NULL ? 1 : 0;

   }

   template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS >
   bool map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS>::contains(const KEY & key) const
   {

      return this->PLookup(key) != NULL ? 1 : 0;

   }

   template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS >
   ::count map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS>::erase(const KEY & key)
   {

      return remove_key(key) ? 1 : 0;

   }

   template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS >
   void map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS>::erase(iterator it)
   {

      remove_key(it->m_key);

   }

   template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS >
   void map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS>::get_next_assoc(POSITION& rNextPosition,
      KEY& rKey, VALUE& rValue) const
   {
      ASSERT_VALID(this);
      ENSURE(m_pHashTable != NULL);  // never call on is_empty map

      assoc* pAssocRet = (assoc*)rNextPosition;
      ENSURE(pAssocRet != NULL);

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
            throw error_exception("map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS>::get_next_assoc : must find something");
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

   template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS >
   const typename map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS>::pair*
   map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS>::PGetNextAssoc(const typename map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS>::pair* pPairRet) const
   {
      ASSERT_VALID(this);

      assoc* pAssocRet = (assoc*)pPairRet;

      ASSERT(m_pHashTable != NULL);  // never call on is_empty map
      ASSERT(pAssocRet != NULL);

      if(m_pHashTable == NULL || pAssocRet == NULL)
         return NULL;

      ASSERT(pAssocRet != (assoc*)BEFORE_START_POSITION);

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

   template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS >
   typename map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS>::pair*
   map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS>::PGetNextAssoc(const typename map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS>::pair* pPairRet)
   {
      ASSERT_VALID(this);

      assoc* pAssocRet = (assoc*)pPairRet;

      ASSERT(m_pHashTable != NULL);  // never call on is_empty map
      ASSERT(pAssocRet != NULL);

      if(m_pHashTable == NULL || pAssocRet == NULL)
         return NULL;

      ASSERT(pAssocRet != (assoc*)BEFORE_START_POSITION);

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

      template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS >
      VALUE map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS> ::
         get(ARG_KEY argkey, ARG_VALUE valueDefault)
      {
         pair * ppair = PLookup(argkey);
         if(ppair == NULL)
            return valueDefault;
         else
            return ppair->m_value;
      }

   /*
   template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS >
   void map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS>::Serialize(CArchive& ar)
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
               KEY* pKey;
               VALUE* pValue;
               //
               // in some cases the & operator might be overloaded, and we cannot use it to
               // obtain the address of a given object.  We then use the following trick to
               // get the address
               //
               pKey = reinterpret_cast< KEY* >( &reinterpret_cast< int& >( const_cast< KEY& > ( static_cast< const KEY& >( pAssoc->key ) ) ) );
               pValue = reinterpret_cast< VALUE* >( &reinterpret_cast< int& >( static_cast< VALUE& >( pAssoc->value ) ) );
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

   template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS >
   void map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS>::dump(dump_context & dumpcontext) const
   {
      ::radix::object::dump(dumpcontext);

      dumpcontext << "with " << m_nCount << " elements";
      if (dumpcontext.GetDepth() > 0)
      {
         // Dump in format "[key] -> value"

         const pair * ppair = PGetFirstAssoc();
         while (ppair != NULL)
         {
            ppair = PGetNextAssoc(ppair);
            dumpcontext << "\n\t[";
            dump_elements<KEY>(dumpcontext, &ppair->m_key, 1);
            dumpcontext << "] = ";
            dump_elements<VALUE>(dumpcontext, &ppair->m_value, 1);
         }
      }

      dumpcontext << "\n";
   }

   template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS >
   void map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS>::assert_valid() const
   {
      ::radix::object::assert_valid();

      ASSERT(m_nHashTableSize > 0);
      ASSERT(m_nCount == 0 || m_pHashTable != NULL);
         // non-is_empty map should have hash table
   }



   template < class type_map >
   class attrib_map :
      virtual public type_map
   {
   public:


      attrib_map(int_ptr nBlockSize = 10);
      attrib_map(const attrib_map & map);

      attrib_map & operator = (const attrib_map & map);


   };


   template < class type_map >
   attrib_map < type_map >::attrib_map(int_ptr nBlockSize) :
      type_map(nBlockSize)
   {
   }

   template < class type_map >
   attrib_map < type_map >::attrib_map(const attrib_map & attribmap)
   {
      operator = (attribmap);
   }

   template < class type_map >
   attrib_map < type_map > & attrib_map < type_map >::operator = (const attrib_map & attribmap)
   {

      if(this != &attribmap)
      {
         this->remove_all();
         type_map::m_nBlockSize = attribmap.type_map::m_nBlockSize;
         const typename type_map::pair * ppair = attribmap.PGetFirstAssoc();
         while(ppair != NULL)
         {
            this->set_at(ppair->m_key, ppair->m_value);
            ppair  = attribmap.PGetNextAssoc(ppair);
         }
      }

      return *this;

   }


   template < class VALUE, class ARG_VALUE = const VALUE &, class HASH = gen::hash < const string & > , class EQUALS = gen::equals_type_arg_type < string, const string & > >
   class string_map :
      virtual public attrib_map < map < string, const string &, VALUE, ARG_VALUE, HASH, EQUALS > >
   {
   public:
      
      
      string_map(::count nBlockSize = 10);
      string_map(const string_map & map);


      string_map & operator = (const string_map & map);


   };

   template < class VALUE, class ARG_VALUE, class HASH, class EQUALS >
   string_map < VALUE, ARG_VALUE, HASH, EQUALS >::string_map(::count nBlockSize) :
      map < string, const string &, VALUE, ARG_VALUE, HASH, EQUALS > (nBlockSize)
   {
   }

   template < class VALUE, class ARG_VALUE, class HASH, class EQUALS >
   string_map < VALUE, ARG_VALUE, HASH, EQUALS >::string_map(const string_map & map) :
      attrib_map < ::collection::map < string, const string &, VALUE, ARG_VALUE, HASH, EQUALS > > (map)
   {
   }

   template < class VALUE, class ARG_VALUE, class HASH, class EQUALS >
   string_map < VALUE, ARG_VALUE, HASH, EQUALS > & string_map < VALUE, ARG_VALUE, HASH, EQUALS >::operator = (const string_map & map)
   {
      
      if(this != &map)
      {
         attrib_map < ::collection::map < string, const string &, VALUE, ARG_VALUE, HASH, EQUALS > >::operator = (map);
      }

      return *this;

   }

   template < class VALUE, class ARG_VALUE = const VALUE &, class HASH = gen::strid_hash, class EQUALS = gen::strid_equals  >
   class strid_map :
      virtual public attrib_map < map < id, const id &, VALUE, ARG_VALUE, HASH, EQUALS > >
   {
   public:
     
      strid_map(::count nBlockSize = 256);
      strid_map(const strid_map & map);


      strid_map & operator = (const strid_map & map);


   };


   template < class VALUE, class ARG_VALUE, class HASH, class EQUALS >
   strid_map < VALUE, ARG_VALUE, HASH, EQUALS >::strid_map(::count nBlockSize) :
      map < id, const id &, VALUE, ARG_VALUE, HASH, EQUALS > (nBlockSize)
   {
   }


   template < class VALUE, class ARG_VALUE, class HASH, class EQUALS >
   strid_map < VALUE, ARG_VALUE, HASH, EQUALS >::strid_map(const strid_map & map) :
      attrib_map < ::collection::map < id, const id &, VALUE, ARG_VALUE, HASH, EQUALS > > (map)
   {
   }

   template < class VALUE, class ARG_VALUE, class HASH, class EQUALS >
   strid_map < VALUE, ARG_VALUE, HASH, EQUALS > & strid_map < VALUE, ARG_VALUE, HASH, EQUALS >::operator = (const strid_map & map)
   {
      
      if(this != &map)
      {
         attrib_map < ::collection::map < id, const id &, VALUE, ARG_VALUE, HASH, EQUALS > >::operator = (map);
      }

      return *this;

   }

   template < class VALUE, class ARG_VALUE = const VALUE &, class HASH = gen::hash < int > , class EQUALS = gen::equals_type_arg_type < int, int > >
   class int_map :
      virtual public attrib_map < map < int, int, VALUE, ARG_VALUE, HASH, EQUALS > >
   {
   public:

      int_map(::count nBlockSize = 10);
      int_map(const int_map & map);


      int_map & operator = (const int_map & map);

   };

   template < class VALUE, class ARG_VALUE, class HASH, class EQUALS >
   int_map < VALUE, ARG_VALUE, HASH, EQUALS >::int_map(::count nBlockSize) :
      map < int, int, VALUE, ARG_VALUE, HASH, EQUALS > (nBlockSize)
   {
   }

   template < class VALUE, class ARG_VALUE, class HASH, class EQUALS >
   int_map < VALUE, ARG_VALUE, HASH, EQUALS >::int_map(const int_map & map) :
      attrib_map < ::collection::map < int, int, VALUE, ARG_VALUE, HASH, EQUALS > > (map)
   {
   }

   template < class VALUE, class ARG_VALUE, class HASH, class EQUALS >
   int_map < VALUE, ARG_VALUE, HASH, EQUALS > & int_map < VALUE, ARG_VALUE, HASH, EQUALS >::operator = (const int_map & map)
   {
      
      if(this != &map)
      {
         attrib_map < ::collection::map < int, int, VALUE, ARG_VALUE, HASH, EQUALS > >::operator = (map);
      }

      return *this;

   }

   typedef CLASS_DECL_ca attrib_map < map < int, int, int, int > > int_to_int;
   typedef CLASS_DECL_ca attrib_map < map < int, int, string, const string & > > int_to_string;
   typedef CLASS_DECL_ca ::collection::string_map < void *, void * > string_to_ptr;

   template < class T >
   class CLASS_DECL_ca string_to_pointer :
      virtual public string_to_ptr
   {
   public:

      class pair
      {
      public:
         const string m_key;
         T * m_value;
      };

      bool Lookup(string key, T * & rValue) const
      {
         return string_to_ptr::Lookup(key, rValue);
      }
      const pair *PLookup(string key) const
      {
         return reinterpret_cast < const string_to_pointer::pair * > (string_to_ptr::PLookup(key));
      }
      pair *PLookup(string key)
      {
         return reinterpret_cast < string_to_pointer::pair * > (string_to_ptr::PLookup(key));
      }


      T ** pget(string key)
      {
         return (T**) string_to_ptr::pget(key);
      }
      T * get(string key)
      {
         T ** p = (T **) string_to_ptr::pget(key);
         if(p == NULL)
            return NULL;
         else
            return (T*) *p;
      }

   // Operations
      // Lookup and add if not there
      T * & operator[](string key)
      {
         return (T * &) string_to_ptr::operator[](key);
      }


      pair * PGetFirstAssoc()
      {
         return (pair *) string_to_ptr::PGetFirstAssoc();
      }

      pair * PGetNextAssoc(pair * & rPpair)
      {
         return (pair *) string_to_ptr::PGetNextAssoc((string_to_ptr::pair * &) rPpair);
      }

   };


   typedef CLASS_DECL_ca ::collection::string_map < int_ptr, int_ptr > string_to_intptr;


} // namespace collection

template < class KEY, class VALUE >
class std_map :
   virtual public ::collection::map < KEY, const KEY & , VALUE, const VALUE & >
{
public:

};


#define new DEBUG_NEW
