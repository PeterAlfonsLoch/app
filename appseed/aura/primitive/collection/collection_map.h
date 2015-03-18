#pragma once

template < typename PAIR >
class map_dynamic_hash_table
{
public:

   typedef map_association < PAIR >  assoc;

   assoc **          m_ppassocHash;
   UINT              m_nHashTableSize;

   map_dynamic_hash_table()
   {

      m_ppassocHash = NULL;
      m_nHashTableSize = 17;

   }

   UINT GetHashTableSize() const { return m_nHashTableSize; }


   void InitHashTable(UINT nHashSize,bool bAllocNow = TRUE)
   {

      if(m_ppassocHash != NULL)
      {
         // free hash table
         delete[] m_ppassocHash;
         m_ppassocHash = NULL;
      }

      if(bAllocNow)
      {
         m_ppassocHash = new assoc *[nHashSize];
         ENSURE(m_ppassocHash != NULL);
         memset(m_ppassocHash,0,sizeof(assoc*) * nHashSize);
      }

      m_nHashTableSize = nHashSize;

   }

   void remove_all()
   {
      if(m_ppassocHash != NULL)
      {

         // free hash table
         delete[] m_ppassocHash;
         m_ppassocHash = NULL;

      }

   }


};

template < int m_nHashTableSize,typename PAIR >
class map_fixed_hash_table
{
public:


   typedef map_association < PAIR > assoc;


   assoc *           m_ppassocHash[m_nHashTableSize];

   map_fixed_hash_table()
   {
      zero(m_ppassocHash,sizeof(m_ppassocHash));
   }


   UINT GetHashTableSize() const { return m_nHashTableSize; }
   void InitHashTable(UINT hashSize,bool bAllocNow = TRUE) {  }

   void remove_all()
   {
      zero(m_ppassocHash,sizeof(m_ppassocHash));
   }

};


template <class KEY,class ARG_KEY,class VALUE,class ARG_VALUE = const VALUE &,class HASH = ::comparison::hash < ARG_KEY >,class EQUALS = ::comparison::equals_type_arg_type < KEY,ARG_KEY >,class PAIR = pair < KEY,VALUE >,typename HASH_TABLE = map_dynamic_hash_table < PAIR > >
class map :
   virtual public ::object
{
public:


   typedef KEY                                     AXIS_KEY;
   typedef ARG_KEY                                 AXIS_ARG_KEY;
   typedef VALUE                                   AXIS_VALUE;
   typedef ARG_VALUE                               AXIS_ARG_VALUE;
   typedef HASH                                    AXIS_HASH;
   typedef EQUALS                                  AXIS_EQUALS;

   typedef ::map_association < PAIR >              assoc;
   typedef typename assoc::pair                    pair;

   HASH_TABLE                                      m_hashtable;


   class iterator
   {
   public:


      typedef pair TYPE;


      pair *                     m_ppair;
      map *                      m_pmap;


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

      pair * operator -> () const
      {
         return m_ppair;
      }

      pair & operator * ()
      {
         return *m_ppair;
      }

      pair & operator * () const
      {
         return *m_ppair;
      }

      iterator & operator ++ ()
      {
         if(m_ppair != NULL && m_pmap != NULL)
            m_ppair = m_pmap->PGetNextAssoc(m_ppair);
         return *this;
      }

      iterator operator ++ (int32_t)
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

      typedef pair TYPE;


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

      pair & operator * ()
      {
         return *m_ppair;
      }

      pair & operator * () const
      {
         return *m_ppair;
      }


      const_iterator & operator ++ ()
      {
         if(m_ppair != NULL && m_pmap != NULL)
            m_ppair = m_pmap->PGetNextAssoc(m_ppair);
         return *this;
      }

      const_iterator operator ++ (int32_t)
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

   const_iterator begin() const
   {
      return const_iterator(((map *) this)->PGetFirstAssoc(), (map *) this);
   }


   const_iterator end() const
   {
      return const_iterator(NULL, (map *) this);
   }

   void construct(::count nBlockSize = 10);
   map(::aura::application * papp = NULL, ::count nBlockSize = 10);
   map(pair pairs[], int32_t iCount);

   ::count get_count() const;
   ::count get_size() const;
   ::count size() const;
   ::count count() const;
   bool is_empty() const;
   bool empty() const;

   // Lookup
   bool Lookup(ARG_KEY key, VALUE& rValue) const;
   const pair *PLookup(ARG_KEY key) const;
   pair *PLookup(ARG_KEY key);


   VALUE * pget(ARG_KEY key);

   // Operations
   // Lookup and add if not there
   VALUE& operator[](ARG_KEY key);

   assoc * get_assoc(ARG_KEY key);
   assoc * get_assoc(ARG_KEY key) const { return ((map *) this)->get_assoc(key);  }

   // add a new (key, value) pair
   assoc * set_at(ARG_KEY key, ARG_VALUE newValue);

   // removing existing (key, ?) pair
   bool remove_key(ARG_KEY key);
   inline bool remove_assoc(assoc * passoc);
   void erase(iterator it);
   ::count erase(const KEY & key);
   // the following funtion is available in a sort_map
   //void erase ( iterator first, iterator last );
   void remove_all();
   void clear();
   void Empty();


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
   UINT GetHashTableSize() const { return m_hashtable.GetHashTableSize();  }
   void InitHashTable(UINT hashSize,bool bAllocNow = TRUE);


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
         set_at(ppair->m_element1, ppair->m_element2);
      }
   }

   iterator find (ARG_KEY key);
   const_iterator find (ARG_KEY key) const;

   // Implementation
   ::count           m_nCount;
   assoc *           m_passocFree;
   assoc *           m_passocHead;
   struct ::plex *   m_pplex;
   ::count           m_nBlockSize;

   assoc * new_assoc(ARG_KEY key);
   void free_assoc(assoc * passoc);
   assoc * get_assoc_at(ARG_KEY, UINT&, UINT&) const;

   virtual ~map();
   //   void Serialize(CArchive&);
   void dump(dump_context &) const;
   void assert_valid() const;

   template < class ARRAY >
   bool remove_key_array(ARRAY a)
   {

      for(index i = 0; i < a.get_count(); i++)
      {

         remove_key(a[i]);

      }

   }

   template < class ARRAY >
   bool remove_assoc_array(ARRAY a)
   {

      for(index i = 0; i < a.get_count(); i++)
      {

         remove_assoc(a[i]);

      }

   }

   virtual void on_after_read() {}

   range < iterator > elements() { return range < iterator >(begin(),end()); }
   const_range < const_iterator > elements() const { return const_range < const_iterator >(begin(),end()); }

   PAIR & element_at(::index iIndex) { return elements().element_at(iIndex); }


};

/////////////////////////////////////////////////////////////////////////////
// map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS, PAIR, HASH_TABLE> inline functions


template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS, class PAIR, class HASH_TABLE >
inline ::count map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS, PAIR, HASH_TABLE>::get_count() const
{ return m_nCount; }

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS, class PAIR, class HASH_TABLE >
inline ::count map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS, PAIR, HASH_TABLE>::get_size() const
{ return m_nCount; }

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS, class PAIR, class HASH_TABLE >
inline ::count map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS, PAIR, HASH_TABLE>::count() const
{ return m_nCount; }

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS, class PAIR, class HASH_TABLE >
inline ::count map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS, PAIR, HASH_TABLE>::size() const
{ return m_nCount; }

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS, class PAIR, class HASH_TABLE >
inline bool map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS, PAIR, HASH_TABLE>::is_empty() const
{ return m_nCount == 0; }

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS, class PAIR, class HASH_TABLE >
inline bool map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS, PAIR, HASH_TABLE>::empty() const
{ return m_nCount == 0; }


template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS, class PAIR, class HASH_TABLE >
inline typename map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS, PAIR, HASH_TABLE>::assoc * map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS, PAIR, HASH_TABLE>::set_at(ARG_KEY key,ARG_VALUE newValue)
{

   assoc * passoc = get_assoc(key);

   passoc->m_element2 = newValue;

   return passoc;

}


template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS, class PAIR, class HASH_TABLE >
inline POSITION map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS, PAIR, HASH_TABLE>::get_start_position() const
{ return (m_nCount == 0) ? NULL : BEFORE_START_POSITION; }

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS, class PAIR, class HASH_TABLE >
const typename map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS, PAIR, HASH_TABLE>::assoc* map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS, PAIR, HASH_TABLE>::PGetFirstAssoc() const
{

   return m_passocHead;

}

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS, class PAIR, class HASH_TABLE >
typename map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS, PAIR, HASH_TABLE>::assoc* map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS, PAIR, HASH_TABLE>::PGetFirstAssoc()
{

   return m_passocHead;

}

//template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS, class PAIR, class HASH_TABLE >
//inline UINT map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS, PAIR, HASH_TABLE>::GetHashTableSize() const
//{
//
//   return m_nHashTableSize;
//
//}

/////////////////////////////////////////////////////////////////////////////
// map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS, PAIR, HASH_TABLE> out-of-line functions
template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS, class PAIR, class HASH_TABLE >
void map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS, PAIR, HASH_TABLE>::construct(::count nBlockSize)
{
   ASSERT(nBlockSize > 0);

   //m_ppassocHash     = NULL;
   //m_nHashTableSize  = 17;  // default size
   m_nCount          = 0;
   m_passocFree      = NULL;
   m_pplex           = NULL;
   m_nBlockSize      = nBlockSize;
   m_passocHead      = NULL;
}

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS, class PAIR, class HASH_TABLE >
map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS, PAIR, HASH_TABLE>::map(::aura::application * papp, ::count nBlockSize) :
   object(papp)
{
   construct(nBlockSize);
}

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS, class PAIR, class HASH_TABLE >
map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS, PAIR, HASH_TABLE>::map(pair pairs[], int32_t iCount)
{
   construct();
   for(int32_t i = 0; i < iCount; i++)
   {
      set_at(pairs[i].m_element1, pairs[i].m_element2);
   }
}


template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS, class PAIR, class HASH_TABLE >
void map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS, PAIR, HASH_TABLE>::remove_all()
{

   ASSERT_VALID(this);

   if(m_passocHead != NULL)
   {
      // destroy elements (values and keys)

      assoc * passoc;

      for (passoc = m_passocHead; passoc != NULL; passoc = passoc->m_pnext)
      {

         passoc->assoc::~assoc();

      }

   }

   m_hashtable.remove_all();

   m_nCount = 0;
   m_passocFree = NULL;

   if(m_pplex != NULL)
   {

      m_pplex->FreeDataChain();
      m_pplex = NULL;

   }

   m_passocHead = NULL;
}

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS, class PAIR, class HASH_TABLE >
inline void map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS, PAIR, HASH_TABLE>::clear()
{
   remove_all();
}

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS, class PAIR, class HASH_TABLE >
inline void map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS, PAIR, HASH_TABLE>::Empty()
{
   clear();
}

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS, class PAIR, class HASH_TABLE >
map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS, PAIR, HASH_TABLE>::~map()
{
   remove_all();
   ASSERT(m_nCount == 0);
}

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS, class PAIR, class HASH_TABLE >
typename map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS, PAIR, HASH_TABLE>::assoc *
   map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS, PAIR, HASH_TABLE>::new_assoc(ARG_KEY key)
{

   if(m_passocFree == NULL)
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

   ENSURE(m_passocFree != NULL);  // we must have something

   map::assoc* passoc = m_passocFree;

   m_passocFree  = m_passocFree->m_pnext;

   ZEROP(passoc);

   if(m_passocHead != NULL)
   {

      m_passocHead->m_pprev   = passoc;

   }

   passoc->m_pnext            = m_passocHead;

   m_passocHead               = passoc;

   m_passocHead->m_pprev      = NULL;

   m_nCount++;

   ASSERT(m_nCount > 0);  // make sure we don't overflow

   ::new(passoc) assoc(key);

   return passoc;

}

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS, class PAIR, class HASH_TABLE >
void map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS, PAIR, HASH_TABLE>::free_assoc(assoc * passoc)
{

   assoc * pnext = passoc->m_pnext;

   if(passoc->m_pnext != NULL)
   {

      passoc->m_pnext->m_pprev = passoc->m_pprev;

   }

   if(passoc->m_pprev != NULL)
   {

      passoc->m_pprev->m_pnext = passoc->m_pnext;

   }

   if(m_passocHead == passoc)
   {

      m_passocHead = pnext;

      if(m_passocHead != NULL)
      {

         m_passocHead->m_pprev = NULL;

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

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS, class PAIR, class HASH_TABLE >
typename map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS, PAIR, HASH_TABLE>::assoc *
   map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS, PAIR, HASH_TABLE>::get_assoc_at(ARG_KEY key, UINT& nHashBucket, UINT& nHashValue) const
   // find association (or return NULL)
{

   nHashValue = HASH::HashKey((ARG_KEY) key);

   nHashBucket = nHashValue % m_hashtable.GetHashTableSize();

   if(get_count() <= 0)
      return NULL;

   // see if it exists
   assoc * passoc;

   for(passoc = m_hashtable.m_ppassocHash[nHashBucket]; passoc != NULL; passoc = passoc->m_pnextHash)
   {

      if(EQUALS::CompareElements(&passoc->m_element1, key))
         return passoc;

   }

   return NULL;

}

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS, class PAIR, class HASH_TABLE >
bool map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS, PAIR, HASH_TABLE>::Lookup(ARG_KEY key, VALUE& rValue) const
{
   //ASSERT_VALID(this);

   UINT nHashBucket, nHashValue;

   assoc* passoc = get_assoc_at(key, nHashBucket, nHashValue);

   if (passoc == NULL)
      return FALSE;  // not in map

   rValue = passoc->m_element2;

   return TRUE;

}

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS, class PAIR, class HASH_TABLE >
typename map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS, PAIR, HASH_TABLE>::iterator map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS, PAIR, HASH_TABLE>::find (ARG_KEY key)
{
   return iterator(PLookup(key), this);
}

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS, class PAIR, class HASH_TABLE >
typename map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS, PAIR, HASH_TABLE>::const_iterator map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS, PAIR, HASH_TABLE>::find (ARG_KEY key) const
{
   return const_iterator((pair *) PLookup(key), (map *) this);
}


template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS, class PAIR, class HASH_TABLE >
const typename map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS, PAIR, HASH_TABLE>::pair* map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS, PAIR, HASH_TABLE>::PLookup(ARG_KEY key) const
{
   //ASSERT_VALID(this);

   UINT nHashBucket, nHashValue;
   assoc* passoc = get_assoc_at(key, nHashBucket, nHashValue);
   return passoc;
}

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS, class PAIR, class HASH_TABLE >
typename map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS, PAIR, HASH_TABLE>::pair* map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS, PAIR, HASH_TABLE>::PLookup(ARG_KEY key)
{
   //ASSERT_VALID(this);

   UINT nHashBucket, nHashValue;
   assoc* passoc = get_assoc_at(key, nHashBucket, nHashValue);
   return passoc;
}

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS, class PAIR, class HASH_TABLE >
VALUE * map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS, PAIR, HASH_TABLE>::pget(ARG_KEY key)
{
   pair * p = PLookup(key);
   if(p)
      return &p->m_element2;
   else
      return NULL;
}

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS, class PAIR, class HASH_TABLE >
typename map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS, PAIR, HASH_TABLE>::assoc * map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS, PAIR, HASH_TABLE>::get_assoc(ARG_KEY key)
{

   ASSERT_VALID(this);

   UINT nHashBucket,nHashValue;

   assoc * passoc;

   if((passoc = get_assoc_at(key,nHashBucket,nHashValue)) == NULL)
   {

      if(m_hashtable.m_ppassocHash == NULL)
         InitHashTable(m_hashtable.GetHashTableSize());

      ENSURE(m_hashtable.m_ppassocHash);

      passoc = new_assoc(key);

      if(m_hashtable.m_ppassocHash[nHashBucket] != NULL)
      {
         m_hashtable.m_ppassocHash[nHashBucket]->m_ppprevHash = &passoc->m_pnextHash;
      }

      passoc->m_pnextHash        = m_hashtable.m_ppassocHash[nHashBucket];

      m_hashtable.m_ppassocHash[nHashBucket] = passoc;

      passoc->m_ppprevHash       = &m_hashtable.m_ppassocHash[nHashBucket];

   }

   return passoc;

}


template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS, class PAIR, class HASH_TABLE >
VALUE& map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS, PAIR, HASH_TABLE>::operator[](ARG_KEY key)
{

   return get_assoc(key)->m_element2;  // return new reference

}

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS, class PAIR, class HASH_TABLE >
bool map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS, PAIR, HASH_TABLE>::remove_key(ARG_KEY key)
   // remove key - return TRUE if removed
{
   ASSERT_VALID(this);

   if (get_count() <= 0)
      return false;  // nothing in the table

   UINT nHashValue;
   nHashValue = HASH::HashKey(key);
   assoc * passoc = m_hashtable.m_ppassocHash[nHashValue%m_hashtable.GetHashTableSize()];
   for(; passoc != NULL; passoc = passoc->m_pnextHash)
   {
      if(EQUALS::CompareElements(&passoc->m_element1, key))
      {
         remove_assoc(passoc);
         return true;
      }
   }
   return false;  // not found
}

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS, class PAIR, class HASH_TABLE >
inline bool map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS, PAIR, HASH_TABLE>::remove_assoc(assoc * passoc)
   // remove key - return TRUE if removed
{
   if(passoc->m_pnextHash != NULL)
   {
      passoc->m_pnextHash->m_ppprevHash = passoc->m_ppprevHash;
   }
   *passoc->m_ppprevHash = passoc->m_pnextHash;
   free_assoc(passoc);
   return true;
}


template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS, class PAIR, class HASH_TABLE >
inline ::count map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS, PAIR, HASH_TABLE>::count(const KEY & key) const
{

   return this->PLookup(key) != NULL ? 1 : 0;

}

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS, class PAIR, class HASH_TABLE >
bool map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS, PAIR, HASH_TABLE>::has(const KEY & key) const
{

   return this->PLookup(key) != NULL ? 1 : 0;

}

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS, class PAIR, class HASH_TABLE >
bool map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS, PAIR, HASH_TABLE>::contains(const KEY & key) const
{

   return this->PLookup(key) != NULL ? 1 : 0;

}

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS, class PAIR, class HASH_TABLE >
::count map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS, PAIR, HASH_TABLE>::erase(const KEY & key)
{

   return remove_key(key) ? 1 : 0;

}

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS, class PAIR, class HASH_TABLE >
void map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS, PAIR, HASH_TABLE>::erase(iterator it)
{

   remove_key(it->m_element1);

}

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS, class PAIR, class HASH_TABLE >
void map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS, PAIR, HASH_TABLE>::get_next_assoc(POSITION& rNextPosition,
                                                                         KEY& rKey, VALUE& rValue) const
{
   ASSERT_VALID(this);
   if(m_hashtable.m_ppassocHash == NULL)
   {
      printf("map::get_next_assoc m_ppassocHash == NULL");
   }
   ENSURE(m_hashtable.m_ppassocHash != NULL);  // never call on is_empty map

   assoc* passocRet = (assoc*)rNextPosition;
   ENSURE(passocRet != NULL);

   if (passocRet == (assoc*) BEFORE_START_POSITION)
   {
      passocRet = m_passocHead;
      if(passocRet == NULL)
         throw error_exception(get_app(), "map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS, PAIR, HASH_TABLE>::get_next_assoc : must find something");
   }

   rNextPosition = (POSITION) passocRet->m_pnext;

   // fill in return data
   rKey = passocRet->m_element1;
   rValue = passocRet->m_element2;
}

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS, class PAIR, class HASH_TABLE >
const typename map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS, PAIR, HASH_TABLE>::assoc*
   map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS, PAIR, HASH_TABLE>::PGetNextAssoc(const typename map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS, PAIR, HASH_TABLE>::pair* pPairRet) const
{
   ASSERT_VALID(this);

   assoc* passocRet = (assoc*)pPairRet;

   ASSERT(m_hashtable.m_ppassocHash != NULL);  // never call on is_empty map
   ASSERT(passocRet != NULL);

   ASSERT(passocRet != (assoc*)BEFORE_START_POSITION);

   return passocRet->m_pnext;

}

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS, class PAIR, class HASH_TABLE >
typename map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS, PAIR, HASH_TABLE>::assoc*
   map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS, PAIR, HASH_TABLE>::PGetNextAssoc(const typename map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS, PAIR, HASH_TABLE>::pair* pPairRet)
{
   ASSERT_VALID(this);

   assoc* passocRet = (assoc*)pPairRet;

   ASSERT(m_hashtable.m_ppassocHash != NULL);  // never call on is_empty map
   ASSERT(passocRet != NULL);

   ASSERT(passocRet != (assoc*)BEFORE_START_POSITION);

   return passocRet->m_pnext;

}

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS, class PAIR, class HASH_TABLE >
VALUE map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS, PAIR, HASH_TABLE> ::
   get(ARG_KEY argkey, ARG_VALUE valueDefault)
{
   pair * ppair = PLookup(argkey);
   if(ppair == NULL)
      return valueDefault;
   else
      return ppair->m_element2;
}

/*
template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS, class PAIR, class HASH_TABLE >
void map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS, PAIR, HASH_TABLE>::Serialize(CArchive& ar)
{
ASSERT_VALID(this);

object::Serialize(ar);

if (ar.IsStoring())
{
ar.WriteCount(m_nCount);
if (m_nCount == 0)
return;  // nothing more to do

ASSERT(m_ppassocHash != NULL);
for (UINT nHash = 0; nHash < m_nHashTableSize; nHash++)
{
assoc* passoc;
for (passoc = m_ppassocHash[nHash]; passoc != NULL;
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

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS, class PAIR, class HASH_TABLE >
void map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS, PAIR, HASH_TABLE>::dump(dump_context & dumpcontext) const
{
   object::dump(dumpcontext);

   dumpcontext << "with " << m_nCount << " elements";
   if (dumpcontext.GetDepth() > 0)
   {
      // Dump in format "[key] -> value"

      const pair * ppair = PGetFirstAssoc();
      while (ppair != NULL)
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

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class HASH, class EQUALS, class PAIR, class HASH_TABLE >
void map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS, PAIR, HASH_TABLE>::assert_valid() const
{
   object::assert_valid();

   ASSERT(GetHashTableSize() > 0);
   ASSERT(m_nCount == 0 || m_hashtable.m_ppassocHash != NULL);
   // non-is_empty map should have hash table
}







#define ptrptr(T1, T2) map < T1 *, T1 *, T2 *, T2 * >



template <class KEY,class ARG_KEY,class VALUE,class ARG_VALUE,class HASH = ::comparison::hash < ARG_KEY >,class EQUALS = ::comparison::equals_type_arg_type < KEY,ARG_KEY >,class PAIR = pair < KEY,VALUE >,class HASH_TABLE = map_dynamic_hash_table < map_association < PAIR > > >
::file::ostream & operator << (::file::ostream & os,const map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS, PAIR, HASH_TABLE> & a)
{
   ::file::map::write(os,a);
   return os;
}

template <class KEY,class ARG_KEY,class VALUE,class ARG_VALUE,class HASH = ::comparison::hash < ARG_KEY >,class EQUALS = ::comparison::equals_type_arg_type < KEY,ARG_KEY >,class PAIR = pair < KEY,VALUE >,class HASH_TABLE = map_dynamic_hash_table < map_association < PAIR > > >
::file::istream & operator >> (::file::istream & is,map < KEY, ARG_KEY, VALUE, ARG_VALUE, HASH, EQUALS, PAIR, HASH_TABLE> & a)
{
   ::file::map::read(is,a);
   return is;
}




