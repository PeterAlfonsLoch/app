#pragma once


#undef new



template <class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH = ::ca::hash < ARG_KEY > , class EQUALS = ::ca::equals_type_arg_type < KEY, ARG_KEY > >
class map :
   virtual public ::ca::object
{
public:


   typedef KEY                                  BASE_KEY;
   typedef ARG_KEY                              BASE_ARG_KEY;
   typedef VALUE                                BASE_VALUE;
   typedef ARG_VALUE                            BASE_ARG_VALUE;
   typedef HASH                                 BASE_HASH;
   typedef EQUALS                               BASE_EQUALS;
   
   typedef ::map_association < KEY, VALUE >     assoc;
   typedef typename assoc::pair                 pair;




   class iterator
   {
   public:


      pair *                     m_ppair;
      map *                      m_pmap;


      iterator()
      {
         m_ppair  = ::null();
         m_pmap   = ::null();
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
         if(m_ppair != ::null() && m_pmap != ::null())
            m_ppair = m_pmap->PGetNextAssoc(m_ppair);
         return *this;
      }

      iterator operator ++ (int32_t)
      {
         if(m_ppair != ::null() && m_pmap != ::null())
            m_ppair = m_pmap->PGetNextAssoc(m_ppair);
         return *this;
      }

      bool operator == (const iterator & it) const
      {
         if(this == &it)
            return true;
         if(m_ppair == ::null() && it.m_ppair == ::null() && it.m_pmap == ::null())
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
         m_ppair  = ::null();
         m_pmap   = ::null();
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
         if(m_ppair != ::null() && m_pmap != ::null())
            m_ppair = m_pmap->PGetNextAssoc(m_ppair);
         return *this;
      }

      const_iterator operator ++ (int32_t)
      {
         if(m_ppair != ::null() && m_pmap != ::null())
            m_ppair = m_pmap->PGetNextAssoc(m_ppair);
         return *this;
      }

      bool operator == (const const_iterator & it) const
      {
         if(this == &it)
            return true;
         if(m_ppair == ::null() && it.m_ppair == ::null() && it.m_pmap == ::null())
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
      return iterator(::null(), this);
   }

   void construct(::count nBlockSize = 10);
   map(::count nBlockSize = 10);
   map(pair pairs[], int32_t iCount);

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

   const assoc *PGetFirstAssoc() const;
   assoc *PGetFirstAssoc();

   void get_next_assoc(POSITION& rNextPosition, KEY& rKey, VALUE& rValue) const;

   const assoc *PGetNextAssoc(const pair *passocRet) const;
   assoc *PGetNextAssoc(const pair *passocRet);

   // advanced features for derived classes
   UINT GetHashTableSize() const;
   void InitHashTable(UINT hashSize, bool bAllocNow = TRUE);


   VALUE get(ARG_KEY argkey, ARG_VALUE valueDefault);


   pair * next(pair * & ppair)
   {
      if(ppair == ::null())
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
      if(ppair == ::null())
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
      pair * ppair = ::null();
      while(map.next(ppair) != ::null())
      {
         set_at(ppair->m_element1, ppair->m_element2);
      }
   }


   // Implementation
protected:
   assoc **          m_ppassocHash;
   UINT              m_nHashTableSize;
   ::count           m_nCount;
   assoc *           m_passocFree;
   assoc *           m_passocHead;
   struct ::plex *   m_pplex;
   ::count           m_nBlockSize;

   assoc * new_assoc(ARG_KEY key);
   void free_assoc(assoc * passoc);
   assoc * get_assoc_at(ARG_KEY, UINT&, UINT&) const;

public:
   virtual ~map();
   //   void Serialize(CArchive&);
   void dump(dump_context &) const;
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
inline ::count map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS>::count() const
{ return m_nCount; }

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS >
inline ::count map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS>::size() const
{ return m_nCount; }

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS >
inline bool map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS>::is_empty() const
{ return m_nCount == 0; }

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS >
inline void map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS>::set_at(ARG_KEY key, ARG_VALUE newValue)
{ (*this)[key] = newValue; }

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS >
inline POSITION map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS>::get_start_position() const
{ return (m_nCount == 0) ? ::null() : BEFORE_START_POSITION; }

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS >
const typename map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS>::assoc* map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS>::PGetFirstAssoc() const
{

   return m_passocHead;

}

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS >
typename map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS>::assoc* map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS>::PGetFirstAssoc()
{

   return m_passocHead;

}

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS >
inline UINT map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS>::GetHashTableSize() const
{ 

   return m_nHashTableSize; 

}

/////////////////////////////////////////////////////////////////////////////
// map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS> out-of-line functions
template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS >
void map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS>::construct(::count nBlockSize)
{
   ASSERT(nBlockSize > 0);

   m_ppassocHash     = ::null();
   m_nHashTableSize  = 17;  // default size
   m_nCount          = 0;
   m_passocFree      = ::null();
   m_pplex           = ::null();
   m_nBlockSize      = nBlockSize;
   m_passocHead      = ::null();
}

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS >
map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS>::map(::count nBlockSize)
{
   construct(nBlockSize);
}

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS >
map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS>::map(pair pairs[], int32_t iCount)
{
   construct();
   for(int32_t i = 0; i < iCount; i++)
   {
      set_at(pairs[i].m_element1, pairs[i].m_element2);
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

   if (m_ppassocHash != ::null())
   {
      // free hash table
      delete[] m_ppassocHash;
      m_ppassocHash = ::null();
   }

   if (bAllocNow)
   {
      m_ppassocHash = new assoc * [nHashSize];
      ENSURE(m_ppassocHash != ::null());
      memset(m_ppassocHash, 0, sizeof(assoc*) * nHashSize);
   }

   m_nHashTableSize = nHashSize;

}

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS >
void map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS>::remove_all()
{

   ASSERT_VALID(this);

   if(m_passocHead != ::null())
   {
      // destroy elements (values and keys)

      assoc * passoc;

      for (passoc = m_passocHead; passoc != ::null(); passoc = passoc->m_pnext)
      {
         
         passoc->assoc::~assoc();

      }

   }

   // free hash table
   delete[] m_ppassocHash;
   m_ppassocHash = ::null();

   m_nCount = 0;
   m_passocFree = ::null();
   m_pplex->FreeDataChain();
   m_pplex = ::null();
   m_passocHead = ::null();
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
typename map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS>::assoc *
   map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS>::new_assoc(ARG_KEY key)
{

   if(m_passocFree == ::null())
   {
      // add another block
      plex * newBlock = plex::create(m_pplex, m_nBlockSize, sizeof(map::assoc));
      // chain them into free list
      map::assoc* passoc = (map::assoc*) newBlock->data();
      // free in reverse order to make it easier to debug
      index i = m_nBlockSize - 1;
      for (passoc = &passoc[i]; i >= 0; i--, passoc--)
      {
         passoc->m_pnext = m_passocFree;
         m_passocFree = passoc;

      }
   }

   ENSURE(m_passocFree != ::null());  // we must have something

   map::assoc* passoc = m_passocFree;

   m_passocFree  = m_passocFree->m_pnext;

   ZEROP(passoc);

   if(m_passocHead != ::null())
   {

      m_passocHead->m_pprev   = passoc;

   }

   passoc->m_pnext            = m_passocHead;
   
   m_passocHead               = passoc;

   m_passocHead->m_pprev      = ::null();

   m_nCount++;
   
   ASSERT(m_nCount > 0);  // make sure we don't overflow

   ::new(passoc) assoc(key);

   return passoc;

}

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS >
void map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS>::free_assoc(assoc * passoc)
{

   assoc * pnext = passoc->m_pnext;

   if(passoc->m_pnext != ::null())
   {

      passoc->m_pnext->m_pprev = passoc->m_pprev;

   }

   if(passoc->m_pprev != ::null())
   {

      passoc->m_pprev->m_pnext = passoc->m_pnext;

   }

   if(m_passocHead == passoc)
   {

      m_passocHead = pnext;

      if(m_passocHead != NULL)
      {

         m_passocHead->m_pprev = ::null();

      }

   }

   passoc->assoc::~assoc();

   passoc->m_pnext = m_passocFree;

   m_passocFree = passoc;

   m_nCount--;
   
   ASSERT(m_nCount >= 0);  // make sure we don't underflow

   // if no more elements, cleanup completely
   if (m_nCount == 0)
      remove_all();

}

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS >
typename map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS>::assoc*
   map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS>::get_assoc_at(ARG_KEY key, UINT& nHashBucket, UINT& nHashValue) const
   // find association (or return ::null())
{
   
   nHashValue = HASH::HashKey((ARG_KEY) key);

   nHashBucket = nHashValue % m_nHashTableSize;

   if (m_ppassocHash == ::null())
      return ::null();

   // see if it exists
   assoc* passoc;

   for (passoc = m_ppassocHash[nHashBucket]; passoc != ::null(); passoc = passoc->m_pnextHash)
   {

      if(EQUALS::CompareElements(&passoc->m_element1, key))
         return passoc;

   }

   return ::null();

}

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS >
bool map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS>::Lookup(ARG_KEY key, VALUE& rValue) const
{
   //ASSERT_VALID(this);

   UINT nHashBucket, nHashValue;

   assoc* passoc = get_assoc_at(key, nHashBucket, nHashValue);
   
   if (passoc == ::null())
      return FALSE;  // not in map

   rValue = passoc->m_element2;

   return TRUE;

}

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS >
const typename map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS>::pair* map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS>::PLookup(ARG_KEY key) const
{
   //ASSERT_VALID(this);

   UINT nHashBucket, nHashValue;
   assoc* passoc = get_assoc_at(key, nHashBucket, nHashValue);
   return passoc;
}

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS >
typename map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS>::pair* map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS>::PLookup(ARG_KEY key)
{
   //ASSERT_VALID(this);

   UINT nHashBucket, nHashValue;
   assoc* passoc = get_assoc_at(key, nHashBucket, nHashValue);
   return passoc;
}

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS >
VALUE * map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS>::pget(ARG_KEY key)
{
   pair * p = PLookup(key);
   if(p)
      return &p->m_element2;
   else
      return ::null();
}

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS >
VALUE& map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS>::operator[](ARG_KEY key)
{
   
   ASSERT_VALID(this);

   UINT nHashBucket, nHashValue;

   assoc * passoc;

   if ((passoc = get_assoc_at(key, nHashBucket, nHashValue)) == ::null())
   {

      if (m_ppassocHash == ::null())
         InitHashTable(m_nHashTableSize);

      ENSURE(m_ppassocHash);

      passoc = new_assoc(key);

      passoc->m_pnextHash        = m_ppassocHash[nHashBucket];

      m_ppassocHash[nHashBucket] = passoc;

   }

   return passoc->m_element2;  // return new reference

}

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS >
bool map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS>::remove_key(ARG_KEY key)
   // remove key - return TRUE if removed
{
   ASSERT_VALID(this);

   if (m_ppassocHash == ::null())
      return false;  // nothing in the table

   UINT nHashValue;
   assoc** ppAssocPrev;
   nHashValue = HASH::HashKey(key);
   ppAssocPrev = &m_ppassocHash[nHashValue%m_nHashTableSize];

   assoc* passoc;
   for (passoc = *ppAssocPrev; passoc != ::null(); passoc = passoc->m_pnextHash)
   {
      if(EQUALS::CompareElements(&passoc->m_element1, key))
      {
         // remove it
         *ppAssocPrev = passoc->m_pnextHash;  // remove from list
         free_assoc(passoc);
         return true;
      }
      ppAssocPrev = &passoc->m_pnextHash;
   }
   return false;  // not found
}

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS >
inline ::count map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS>::count(const KEY & key) const
{

   return this->PLookup(key) != ::null() ? 1 : 0;

}

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS >
bool map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS>::has(const KEY & key) const
{

   return this->PLookup(key) != ::null() ? 1 : 0;

}

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS >
bool map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS>::contains(const KEY & key) const
{

   return this->PLookup(key) != ::null() ? 1 : 0;

}

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS >
::count map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS>::erase(const KEY & key)
{

   return remove_key(key) ? 1 : 0;

}

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS >
void map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS>::erase(iterator it)
{

   remove_key(it->m_element1);

}

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS >
void map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS>::get_next_assoc(POSITION& rNextPosition,
                                                                         KEY& rKey, VALUE& rValue) const
{
   ASSERT_VALID(this);
   ENSURE(m_ppassocHash != ::null());  // never call on is_empty map

   assoc* passocRet = (assoc*)rNextPosition;
   ENSURE(passocRet != ::null());

   if (passocRet == (assoc*) BEFORE_START_POSITION)
   {
      passocRet = m_passocHead;
      if(passocRet == ::null())
         throw error_exception(get_app(), "map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS>::get_next_assoc : must find something");
   }

   rNextPosition = (POSITION) passocRet->m_pnext;

   // fill in return data
   rKey = passocRet->m_element1;
   rValue = passocRet->m_element2;
}

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS >
const typename map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS>::assoc*
   map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS>::PGetNextAssoc(const typename map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS>::pair* pPairRet) const
{
   ASSERT_VALID(this);

   assoc* passocRet = (assoc*)pPairRet;

   ASSERT(m_ppassocHash != ::null());  // never call on is_empty map
   ASSERT(passocRet != ::null());

   if(m_ppassocHash == ::null() || passocRet == ::null())
      return ::null();

   ASSERT(passocRet != (assoc*)BEFORE_START_POSITION);

   return passocRet->m_pnext;

}

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS >
typename map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS>::assoc*
   map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS>::PGetNextAssoc(const typename map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS>::pair* pPairRet)
{
   ASSERT_VALID(this);

   assoc* passocRet = (assoc*)pPairRet;

   ASSERT(m_ppassocHash != ::null());  // never call on is_empty map
   ASSERT(passocRet != ::null());

   if(m_ppassocHash == ::null() || passocRet == ::null())
      return ::null();

   ASSERT(passocRet != (assoc*)BEFORE_START_POSITION);

   return passocRet->m_pnext;

}

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS >
VALUE map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS> ::
   get(ARG_KEY argkey, ARG_VALUE valueDefault)
{
   pair * ppair = PLookup(argkey);
   if(ppair == ::null())
      return valueDefault;
   else
      return ppair->m_element2;
}

/*
template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS >
void map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS>::Serialize(CArchive& ar)
{
ASSERT_VALID(this);

::ca::object::Serialize(ar);

if (ar.IsStoring())
{
ar.WriteCount(m_nCount);
if (m_nCount == 0)
return;  // nothing more to do

ASSERT(m_ppassocHash != ::null());
for (UINT nHash = 0; nHash < m_nHashTableSize; nHash++)
{
assoc* passoc;
for (passoc = m_ppassocHash[nHash]; passoc != ::null();
passoc = passoc->pNext)
{
KEY* pKey;
VALUE* pValue;
//
// in some cases the & operator might be overloaded, and we cannot use it to
// obtain the address of a given object.  We then use the following trick to
// get the address
//
pKey = reinterpret_cast< KEY* >( &reinterpret_cast< int32_t& >( const_cast< KEY& > ( static_cast< const KEY& >( passoc->key ) ) ) );
pValue = reinterpret_cast< VALUE* >( &reinterpret_cast< int32_t& >( static_cast< VALUE& >( passoc->value ) ) );
SerializeElements<KEY>(ar, pKey, 1);
SerializeElements<VALUE>(ar, pValue, 1);
}
}
}
else
{
uint_ptr nNewCount = ar.ReadCount();
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
   ::ca::object::dump(dumpcontext);

   dumpcontext << "with " << m_nCount << " elements";
   if (dumpcontext.GetDepth() > 0)
   {
      // Dump in format "[key] -> value"

      const pair * ppair = PGetFirstAssoc();
      while (ppair != ::null())
      {
         ppair = PGetNextAssoc(ppair);
         dumpcontext << "\n\t[";
         dump_elements<KEY>(dumpcontext, &ppair->m_element1, 1);
         dumpcontext << "] = ";
         dump_elements<VALUE>(dumpcontext, &ppair->m_element2, 1);
      }
   }

   dumpcontext << "\n";
}

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS >
void map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS>::assert_valid() const
{
   ::ca::object::assert_valid();

   ASSERT(m_nHashTableSize > 0);
   ASSERT(m_nCount == 0 || m_ppassocHash != ::null());
   // non-is_empty map should have hash table
}

template < class KEY, class VALUE >
class std_map :
   virtual public map < KEY, const KEY & , VALUE, const VALUE & >
{
public:

};




#define new DEBUG_NEW


#define ptrptr(T1, T2) map < T1 *, T1 *, T2 *, T2 * >

