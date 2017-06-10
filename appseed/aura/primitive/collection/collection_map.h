#pragma once


#include "collection_iterable.h"


template < typename PAIR >
class map_dynamic_hash_table
{
public:

   typedef map_association < PAIR >  assoc;

   assoc *           m_assocHash17[17];
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

      if(m_ppassocHash != NULL && m_ppassocHash != m_assocHash17)
      {
         // free hash table
         delete[] m_ppassocHash;
         m_ppassocHash = NULL;
      }

      if(bAllocNow)
      {

         if (nHashSize == 17)
         {

            m_ppassocHash = m_assocHash17;

         }
         else
         {
         
            m_ppassocHash = new assoc *[nHashSize];
            
            ENSURE(m_ppassocHash != NULL);

         }

         memset(m_ppassocHash,0,sizeof(assoc*) * nHashSize);

      }

      m_nHashTableSize = nHashSize;

   }

   void remove_all()
   {
      if(m_ppassocHash != NULL && m_ppassocHash != m_assocHash17)
      {

         // free hash table
         delete[] m_ppassocHash;

      }

      m_ppassocHash = NULL;

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


template <class KEY,class ARG_KEY,class VALUE,class ARG_VALUE = const VALUE &, class PAIR = pair < KEY, VALUE, ARG_KEY, ARG_VALUE >, typename HASH = ::comparison::hash, typename EQUALS = ::comparison::equals >
class map_data :
   virtual public ::object
{
public:

   typedef map_dynamic_hash_table < PAIR >         HASH_TABLE;
   typedef KEY                                     BASE_KEY;
   typedef ARG_KEY                                 BASE_ARG_KEY;
   typedef VALUE                                   BASE_VALUE;
   typedef ARG_VALUE                               BASE_ARG_VALUE;
   typedef PAIR                                    BASE_TYPE;
   typedef BASE_TYPE                               TYPE;

   typedef ::map_association < PAIR >              assoc;
   typedef typename assoc::pair                    pair;

   typedef map_iterator < PAIR >                   iterator;
   typedef const_map_iterator < PAIR >             const_iterator;

   HASH_TABLE                                      m_hashtable;

   ::count                                         m_nCount;
   assoc *                                         m_passocFree;
   assoc *                                         m_passocHead;
   assoc *                                         m_passocTail;
   struct ::plex *                                 m_pplex;
   ::count                                         m_nBlockSize;


   map_data(::aura::application * papp = NULL, ::count nBlockSize = 10);
   map_data(const PAIR * ppairs, ::count count);
   map_data(const map_data & m);
   virtual ~map_data();


   void construct(::count nBlockSize = 10);


   ::count get_count() const;
   ::count get_size() const;
   ::count size() const;
   ::count count() const;
   bool is_empty() const;
   bool empty() const;


   iterator lower_bound()
   {

      return NULL;

   }

   iterator begin()
   {
      return iterator(m_passocHead);
   }


   iterator end()
   {
      return iterator(NULL);
   }


   iterator upper_bound()
   {

      return iterator(m_passocTail);

   }


   const_iterator lower_bound() const
   {

      return const_iterator(NULL);

   }

   const_iterator begin() const
   {

      return const_iterator(m_passocHead);

   }


   const_iterator end() const
   {

      return const_iterator(NULL);

   }


   const_iterator upper_bound() const
   {

      return const_iterator(m_passocTail);

   }


   void iprepare_first_last(index & first, index & last) const
   {

      if (first < 0)
      {

         first = m_nCount <= 0 ? 0 : m_nCount + (first % m_nCount) + 1;

      }

      if (last < 0)
      {

         last = m_nCount <= 0 ? 0 : m_nCount + (last % m_nCount) + 1;

      }

   }


   void riprepare_first_last(index & first, index & last) const
   {

      if (first < 0)
      {

         first = m_nCount <= 0 ? 0 : m_nCount + (first % m_nCount);

      }

      if (last < 0)
      {

         last = m_nCount <= 0 ? 0 : m_nCount + (last % m_nCount);

      }

   }


   void iprepare_first_count(index & first, ::count & count) const
   {

      if (first < 0)
      {

         first = m_nCount <= 0 ? 0 : m_nCount + (first % m_nCount) + 1;

      }

      if (count < 0)
      {

         count = m_nCount <= 0 ? 0 : (m_nCount + (count % m_nCount) + 1);

      }
      else
      {

         count += first;

      }

   }


   void prepare_first_last(iterator & first, iterator & last) const
   {

      if (first.is_null())
      {

         first = m_passocHead;

      }

   }

   void prepare_first_last(const_iterator & first, const_iterator & last) const
   {

      if (first.is_null())
      {

         first = m_passocHead;

      }

   }

   void rprepare_first_last(iterator & first, iterator & last) const
   {

      if (first.is_null())
      {

         first = m_passocTail;

      }

   }

   void rprepare_first_last(const_iterator & first, const_iterator & last) const
   {

      if (first.is_null())
      {

         first = m_passocTail;

      }

   }


   bool valid_iter(iterator current, iterator end) const
   {

      return current != end;

   }

   bool valid_iter(const_iterator current, const_iterator end) const
   {

      return current != end;

   }

   bool rvalid_iter(iterator current, iterator end) const
   {

      return current != end;

   }

   bool rvalid_iter(const_iterator current, const_iterator end) const
   {

      return current != end;

   }




   //Lookup
   bool lookup(ARG_KEY key, VALUE& rValue) const;

   iterator find_first(ARG_KEY key);
   const_iterator find_first(ARG_KEY key) const;

   iterator find_first_key(ARG_KEY key);
   const_iterator find_first_key(ARG_KEY key) const;

   VALUE * pget(ARG_KEY key);

    //Operations
    //Lookup and add if not there
   VALUE& operator[](ARG_KEY key);
   const VALUE& operator[](ARG_KEY key) const;

   assoc * get_assoc(ARG_KEY key);
   assoc * get_assoc(ARG_KEY key) const { return ((map_data *) this)->get_assoc(key);  }

    //add a new (key, value) pair
   assoc * set_at(ARG_KEY key, ARG_VALUE newValue);
   iterator add(const TYPE & t);

    //removing existing (key, ?) pair
   bool remove_key(ARG_KEY key);
   inline bool remove_assoc(assoc * passoc);

   void remove(PAIR & pair);

   void erase(iterator & it);
   void erase(iterator & it, iterator last);
   void erase_count(iterator & it, ::count c);

   void remove_at(index first);
   void remove_at(index first, ::count c);

   iterator index_iterator(index i);
   const_iterator index_iterator(index i) const;
   
    //the following funtion is available in a sort_map
   //void erase ( iterator first, iterator last );
   void remove_all();
   void clear();
   void Empty();


   ::count count(const KEY & t) const;
   bool has(const KEY & t) const;
   bool contains(const KEY & t) const;


    //iterating all (key, value) pairs
   // POSITION get_start_position() const;

   //const assoc *PGetFirstAssoc() const;
   //assoc *PGetFirstAssoc();

   //void get_next_assoc(POSITION& rNextPosition, KEY& rKey, VALUE& rValue) const;

   //const assoc *PGetNextAssoc(const pair *passocRet) const;
   //assoc *PGetNextAssoc(const pair *passocRet);

    //advanced features for derived classes
   UINT GetHashTableSize() const { return m_hashtable.GetHashTableSize();  }
   void InitHashTable(UINT hashSize,bool bAllocNow = TRUE);


   VALUE get(ARG_KEY argkey, ARG_VALUE valueDefault);


   //pair * next(pair * & ppair)
   //{
   //   if(ppair == NULL)
   //   {
   //      ppair = PGetFirstAssoc();
   //   }
   //   else
   //   {
   //      ppair = PGetNextAssoc(ppair);
   //   }
   //   return ppair;
   //}

   //const pair * next(const pair * & ppair) const
   //{
   //   if(ppair == NULL)
   //   {
   //      ppair = PGetFirstAssoc();
   //   }
   //   else
   //   {
   //      ppair = PGetNextAssoc(ppair);
   //   }
   //   return ppair;
   //}


   void set(map_data & map_data)
   {
      
      for(auto & item : map_data)
      {

         set_at(item.m_element1, item.m_element2);

      }

   }

   TYPE & first() { return *begin(); }
   const TYPE & first() const { return *begin(); }
   TYPE & last() { return *upper_bound(); }
   const TYPE & last() const { return *upper_bound(); }


   iterator find (ARG_KEY key);
   const_iterator find (ARG_KEY key) const;

   assoc * new_assoc(ARG_KEY key);
   void free_assoc(assoc * passoc);
   assoc * get_assoc_at(ARG_KEY, UINT&, UINT&) const;

//      void Serialize(CArchive&);
   void dump(dump_context &) const;
   void assert_valid() const;

   template < class ARRAY >
   bool remove_key_array(ARRAY a)
   {

      bool bRemoved = false;

      for(index i = 0; i < a.get_count(); i++)
      {

         bRemoved |= remove_key(a[i]);

      }

      return bRemoved;

   }

   template < class ARRAY >
   ::count remove_assoc_array(ARRAY a)
   {

      ::count countRemoved = 0;

      for(index i = 0; i < a.get_count(); i++)
      {

         if(remove_assoc(a[i]))
         {

            countRemoved++;

         }

      }

      return countRemoved;

   }

   virtual void on_after_read() {}

   range < iterator > elements() { return range < iterator >(begin(),end()); }
   const_range < const_iterator > elements() const { return const_range < const_iterator >(begin(),end()); }

   PAIR & element_at(::index iIndex) { return elements().element_at(iIndex); }

   template < typename PRED >
   typename assoc * pred_find(PRED pred)
   {

      auto p = this->begin();

      while (p != end())
      {

         if (pred(*p))
         {

            return p;

         }

         p++;

      }

      return NULL;

   }


   void remove_first()
   {

      ::iter::remove_first(*this);

   }


   void remove_last()
   {

      ::iter::remove_last(*this);

   }


   TYPE pop_first()
   {

      TYPE t = first();

      remove_first();

      return t;

   }


   TYPE pop_last()
   {

      TYPE t = last();

      remove_last();

      return t;

   }

};


template <class KEY, class ARG_KEY, class VALUE, class ARG_VALUE = const VALUE &, class PAIR = pair < KEY, VALUE, ARG_KEY, ARG_VALUE >, typename HASH = ::comparisontest::hash, typename EQUALS = ::comparisontest::equals >
class maptest :
   virtual public iterable < map_data < KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR, HASH, EQUALS > >
{
public:

   typedef iterable < map_data < KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR, HASH, EQUALS > > ITERABLE;
   typedef typename ITERABLE::iterator iterator;

   maptest(::aura::application * papp = NULL, ::count nBlockSize = 10);
   maptest(const PAIR * pairs, ::count count);
   maptest(const maptest & m);

};


template <class KEY, class ARG_KEY, class VALUE, class ARG_VALUE = const VALUE &, class PAIR = pair < KEY, VALUE, ARG_KEY, ARG_VALUE >, typename HASH = ::comparisonok::hash, typename EQUALS = ::comparisonok::equals >
class map :
   virtual public iterable < map_data < KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR, HASH, EQUALS > >
{
public:

   typedef iterable < map_data < KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR, HASH, EQUALS > > ITERABLE;
   typedef typename ITERABLE::iterator iterator;

   map(::aura::application * papp = NULL, ::count nBlockSize = 10);
   map(const PAIR * pairs, ::count count);
   map(const map & m);

};

template <class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class PAIR, typename HASH, typename EQUALS >
maptest<KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR, HASH, EQUALS>::maptest(::aura::application * papp, ::count nBlockSize) :
::object(papp)
{

   ASSERT(nBlockSize > 0);
   m_nBlockSize = nBlockSize;

}


template <class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class PAIR, typename HASH, typename EQUALS >
maptest<KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR, HASH, EQUALS>::maptest(const PAIR * pdata, ::count count)
{
   
   ::iter::add_data(*this, pdata, count);

}


template <class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class PAIR, typename HASH, typename EQUALS >
maptest<KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR, HASH, EQUALS>::maptest(const maptest & m)
{


}


template <class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class PAIR, typename HASH, typename EQUALS >
map<KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR, HASH, EQUALS>::map(::aura::application * papp, ::count nBlockSize) :
   ::object(papp)
{

   ASSERT(nBlockSize > 0);
   m_nBlockSize = nBlockSize;

}


template <class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class PAIR, typename HASH, typename EQUALS >
map<KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR, HASH, EQUALS>::map(const PAIR * pdata, ::count count)
{

   ::iter::add_data(*this, pdata, count);

}


template <class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class PAIR, typename HASH, typename EQUALS >
map<KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR, HASH, EQUALS>::map(const map & m)
{


}

//
// SVN 17305
//
//template <class KEY,class ARG_KEY,class VALUE,class ARG_VALUE = const VALUE &,class HASH = ::comparison::hash < ARG_KEY >,class EQUALS = ::comparison::equals_type_arg_type < KEY,ARG_KEY >,class PAIR = pair < KEY,VALUE >,typename HASH_TABLE = map_dynamic_hash_table < PAIR > >
//class theora_map :
//   virtual public ::object
//{
//public:
//
//
//   typedef KEY                                     AXIS_KEY;
//   typedef ARG_KEY                                 AXIS_ARG_KEY;
//   typedef VALUE                                   AXIS_VALUE;
//   typedef ARG_VALUE                               AXIS_ARG_VALUE;
//   typedef HASH                                    AXIS_HASH;
//   typedef EQUALS                                  AXIS_EQUALS;
//
//   typedef ::map_association < PAIR >              assoc;
//   typedef typename assoc::pair                    pair;
//
//   HASH_TABLE                                      m_hashtable;
//
//
//   class iterator
//   {
//   public:
//
//
//      typedef pair TYPE;
//
//
//      pair *                     m_ppair;
//      map_data *                      m_pmap;
//
//
//      iterator()
//      {
//         m_ppair  = NULL;
//         m_pmap   = NULL;
//      }
//
//      iterator(const iterator & iterator)
//      {
//         m_ppair  = iterator.m_ppair;
//         m_pmap   = iterator.m_pmap;
//      }
//
//      iterator(pair * ppair, map_data * pmap)
//      {
//         m_ppair  = ppair;
//         m_pmap   = pmap;
//      }
//
//      pair * operator -> ()
//      {
//         return m_ppair;
//      }
//
//      pair * operator -> () const
//      {
//         return m_ppair;
//      }
//
//      pair & operator * ()
//      {
//         return *m_ppair;
//      }
//
//      pair & operator * () const
//      {
//         return *m_ppair;
//      }
//
//      iterator & operator ++ ()
//      {
//         if(m_ppair != NULL && m_pmap != NULL)
//            m_ppair = m_pmap->PGetNextAssoc(m_ppair);
//         return *this;
//      }
//
//      iterator operator ++ (int32_t)
//      {
//         if(m_ppair != NULL && m_pmap != NULL)
//            m_ppair = m_pmap->PGetNextAssoc(m_ppair);
//         return *this;
//      }
//
//      bool operator == (const iterator & it) const
//      {
//         if(this == &it)
//            return true;
//         if(m_ppair == NULL && it.m_ppair == NULL && it.m_pmap == NULL)
//            return true;
//         if(m_pmap != it.m_pmap)
//            return false;
//         return m_ppair == it.m_ppair;
//      }
//
//      bool operator != (const iterator & it) const
//      {
//         return !operator == (it);
//      }
//
//      iterator & operator = (const iterator & it)
//      {
//         if(this != &it)
//         {
//            m_pmap         = it.m_pmap;
//            m_ppair        = it.m_ppair;
//         }
//         return *this;
//      }
//
//   };
//
//
//   class const_iterator
//   {
//   public:
//
//      typedef pair TYPE;
//
//
//      pair *   m_ppair;
//      map_data *    m_pmap;
//
//
//      const_iterator()
//      {
//         m_ppair  = NULL;
//         m_pmap   = NULL;
//      }
//
//      const_iterator(const iterator & iterator)
//      {
//         m_ppair  = iterator.m_ppair;
//         m_pmap   = iterator.m_pmap;
//      }
//
//      const_iterator(const const_iterator & const_iterator)
//      {
//         m_ppair  = const_iterator.m_ppair;
//         m_pmap   = const_iterator.m_pmap;
//      }
//
//      const_iterator(pair * ppair, map_data * pmap)
//      {
//         m_ppair  = ppair;
//         m_pmap   = pmap;
//      }
//
//      const pair * operator -> () const
//      {
//         return m_ppair;
//      }
//
//      pair & operator * ()
//      {
//         return *m_ppair;
//      }
//
//      pair & operator * () const
//      {
//         return *m_ppair;
//      }
//
//
//      const_iterator & operator ++ ()
//      {
//         if(m_ppair != NULL && m_pmap != NULL)
//            m_ppair = m_pmap->PGetNextAssoc(m_ppair);
//         return *this;
//      }
//
//      const_iterator operator ++ (int32_t)
//      {
//         if(m_ppair != NULL && m_pmap != NULL)
//            m_ppair = m_pmap->PGetNextAssoc(m_ppair);
//         return *this;
//      }
//
//      bool operator == (const const_iterator & it) const
//      {
//         if(this == &it)
//            return true;
//         if(m_ppair == NULL && it.m_ppair == NULL && it.m_pmap == NULL)
//            return true;
//         if(m_pmap != it.m_pmap)
//            return false;
//         return m_ppair == it.m_ppair;
//      }
//
//      bool operator != (const const_iterator & it) const
//      {
//         return !operator == (it);
//      }
//
//      const_iterator & operator = (const const_iterator & it)
//      {
//         if(this != &it)
//         {
//            m_pmap         = it.m_pmap;
//            m_ppair        = it.m_ppair;
//         }
//         return *this;
//      }
//
//   };
//
//
//
//   iterator begin()
//   {
//      return iterator(PGetFirstAssoc(), this);
//   }
//
//
//   iterator end()
//   {
//      return iterator(NULL, this);
//   }
//
//   const_iterator begin() const
//   {
//      return const_iterator(((map_data *) this)->PGetFirstAssoc(), (map_data *) this);
//   }
//
//
//   const_iterator end() const
//   {
//      return const_iterator(NULL, (map_data *) this);
//   }
//
//   void construct(::count nBlockSize = 10);
//   map_data(::aura::application * papp = NULL, ::count nBlockSize = 10);
//   map_data(pair pairs[], int32_t iCount);
//   map_data(const map_data & m);
//
//   ::count get_count() const;
//   ::count get_size() const;
//   ::count size() const;
//   ::count count() const;
//   bool is_empty() const;
//   bool empty() const;
//
//    Lookup
//   bool Lookup(ARG_KEY key, VALUE& rValue) const;
//   const pair *PLookup(ARG_KEY key) const;
//   pair *PLookup(ARG_KEY key);
//
//
//   VALUE * pget(ARG_KEY key);
//
//    Operations
//    Lookup and add if not there
//   VALUE& operator[](ARG_KEY key);
//
//   assoc * get_assoc(ARG_KEY key);
//   assoc * get_assoc(ARG_KEY key) const { return ((map_data *) this)->get_assoc(key);  }
//
//    add a new (key, value) pair
//   assoc * set_at(ARG_KEY key, ARG_VALUE newValue);
//
//    removing existing (key, ?) pair
//   bool remove_key(ARG_KEY key);
//   inline bool remove_assoc(assoc * passoc);
//   void erase(iterator it);
//   ::count erase(const KEY & key);
//    the following funtion is available in a sort_map
//   void erase ( iterator first, iterator last );
//   void remove_all();
//   void clear();
//   void Empty();
//
//
//   ::count count(const KEY & t) const;
//   bool has(const KEY & t) const;
//   bool contains(const KEY & t) const;
//
//    iterating all (key, value) pairs
//   POSITION get_start_position() const;
//
//   const assoc *PGetFirstAssoc() const;
//   assoc *PGetFirstAssoc();
//
//   void get_next_assoc(POSITION& rNextPosition, KEY& rKey, VALUE& rValue) const;
//
//   const assoc *PGetNextAssoc(const pair *passocRet) const;
//   assoc *PGetNextAssoc(const pair *passocRet);
//
//    advanced features for derived classes
//   UINT GetHashTableSize() const { return m_hashtable.GetHashTableSize();  }
//   void InitHashTable(UINT hashSize,bool bAllocNow = TRUE);
//
//
//   VALUE get(ARG_KEY argkey, ARG_VALUE valueDefault);
//
//
//   pair * next(pair * & ppair)
//   {
//      if(ppair == NULL)
//      {
//         ppair = PGetFirstAssoc();
//      }
//      else
//      {
//         ppair = PGetNextAssoc(ppair);
//      }
//      return ppair;
//   }
//
//   const pair * next(const pair * & ppair) const
//   {
//      if(ppair == NULL)
//      {
//         ppair = PGetFirstAssoc();
//      }
//      else
//      {
//         ppair = PGetNextAssoc(ppair);
//      }
//      return ppair;
//   }
//
//
//   void set(map_data & map_data)
//   {
//      pair * ppair = NULL;
//      while(map_data.next(ppair) != NULL)
//      {
//         set_at(ppair->m_element1, ppair->m_element2);
//      }
//   }
//
//   iterator find (ARG_KEY key);
//   const_iterator find (ARG_KEY key) const;
//
//    Implementation
//   ::count           m_nCount;
//   assoc *           m_passocFree;
//   assoc *           m_passocHead;
//   struct ::plex *   m_pplex;
//   ::count           m_nBlockSize;
//
//   assoc * new_assoc(ARG_KEY key);
//   void free_assoc(assoc * passoc);
//   assoc * get_assoc_at(ARG_KEY, UINT&, UINT&) const;
//
//   virtual ~map_data();
//      void Serialize(CArchive&);
//   void dump(dump_context &) const;
//   void assert_valid() const;
//
//   template < class ARRAY >
//   bool remove_key_array(ARRAY a)
//   {
//
//      bool bRemoved = false;
//
//      for(index i = 0; i < a.get_count(); i++)
//      {
//
//         bRemoved |= remove_key(a[i]);
//
//      }
//
//      return bRemoved;
//
//   }
//
//   template < class ARRAY >
//   ::count remove_assoc_array(ARRAY a)
//   {
//
//      ::count countRemoved = 0;
//
//      for(index i = 0; i < a.get_count(); i++)
//      {
//
//         if(remove_assoc(a[i]))
//         {
//
//            countRemoved++;
//
//         }
//
//      }
//
//      return countRemoved;
//
//   }
//
//   virtual void on_after_read() {}
//
//   range < iterator > elements() { return range < iterator >(begin(),end()); }
//   const_range < const_iterator > elements() const { return const_range < const_iterator >(begin(),end()); }
//
//   PAIR & element_at(::index iIndex) { return elements().element_at(iIndex); }
//
//
//};

/////////////////////////////////////////////////////////////////////////////
// map_data <KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR, HASH, EQUALS> inline functions


template <class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class PAIR, typename HASH, typename EQUALS >
inline ::count map_data <KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR, HASH, EQUALS>::get_count() const
{ return m_nCount; }

template <class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class PAIR, typename HASH, typename EQUALS >
inline ::count map_data <KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR, HASH, EQUALS>::get_size() const
{ return m_nCount; }

template <class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class PAIR, typename HASH, typename EQUALS >
inline ::count map_data <KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR, HASH, EQUALS>::count() const
{ return m_nCount; }

template <class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class PAIR, typename HASH, typename EQUALS >
inline ::count map_data <KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR, HASH, EQUALS>::size() const
{ return m_nCount; }

template <class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class PAIR, typename HASH, typename EQUALS >
inline bool map_data <KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR, HASH, EQUALS>::is_empty() const
{ return m_nCount == 0; }

template <class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class PAIR, typename HASH, typename EQUALS >
inline bool map_data <KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR, HASH, EQUALS>::empty() const
{ return m_nCount == 0; }


template <class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class PAIR, typename HASH, typename EQUALS >
inline typename map_data <KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR, HASH, EQUALS>::assoc * map_data <KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR, HASH, EQUALS>::set_at(ARG_KEY key,ARG_VALUE newValue)
{

   assoc * passoc = get_assoc(key);

   passoc->m_element2 = newValue;

   return passoc;

}


template <class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class PAIR, typename HASH, typename EQUALS >
inline typename map_data <KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR, HASH, EQUALS>::iterator map_data <KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR, HASH, EQUALS>::add(const TYPE & pair)
{

   return set_at(pair.m_element1, pair.m_element2);

}


//template <class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class PAIR, typename HASH, typename EQUALS >
//inline POSITION map_data <KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR, HASH, EQUALS>::get_start_position() const
//{ return (m_nCount == 0) ? NULL : BEFORE_START_POSITION; }
//
//template <class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class PAIR, typename HASH, typename EQUALS >
//const typename map_data <KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR, HASH, EQUALS>::assoc* map_data <KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR, HASH, EQUALS>::PGetFirstAssoc() const
//{
//
//   return m_passocHead;
//
//}
//
//template <class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class PAIR, typename HASH, typename EQUALS >
//typename map_data <KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR, HASH, EQUALS>::assoc* map_data <KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR, HASH, EQUALS>::PGetFirstAssoc()
//{
//
//   return m_passocHead;
//
//}

//template <class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class PAIR, typename HASH, typename EQUALS >
//inline UINT map_data <KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR, HASH, EQUALS>::GetHashTableSize() const
//{
//
//   return m_nHashTableSize;
//
//}

/////////////////////////////////////////////////////////////////////////////
// map_data <KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR, HASH, EQUALS> out-of-line functions
template <class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class PAIR, typename HASH, typename EQUALS >
void map_data <KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR, HASH, EQUALS>::construct(::count nBlockSize)
{
   ASSERT(nBlockSize > 0);

   //m_ppassocHash     = NULL;
   //m_nHashTableSize  = 17;  // default size
   m_nCount          = 0;
   m_passocFree      = NULL;
   m_pplex           = NULL;
   m_nBlockSize      = nBlockSize;
   m_passocHead      = NULL;
   m_passocTail      = NULL;

}


template <class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class PAIR, typename HASH, typename EQUALS >
map_data <KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR, HASH, EQUALS>::map_data(::aura::application * papp, ::count nBlockSize) :
   object(papp)
{
   construct(nBlockSize);
}


template <class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class PAIR, typename HASH, typename EQUALS >
map_data <KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR, HASH, EQUALS>::map_data(const PAIR * pdata, ::count count)
{
   
   construct();

   ::iter::add_data(*this, pdata, count);

}


template <class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class PAIR, typename HASH, typename EQUALS >
map_data <KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR, HASH, EQUALS>::map_data(const map_data & m)
{
   
   construct();

   ::iter::copy_iter(*this, m);
   
}


template <class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class PAIR, typename HASH, typename EQUALS >
void map_data <KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR, HASH, EQUALS>::remove_all()
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
   m_passocTail = NULL;

}

template <class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class PAIR, typename HASH, typename EQUALS >
inline void map_data <KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR, HASH, EQUALS>::clear()
{
   remove_all();
}

template <class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class PAIR, typename HASH, typename EQUALS >
inline void map_data <KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR, HASH, EQUALS>::Empty()
{
   clear();
}

template <class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class PAIR, typename HASH, typename EQUALS >
map_data <KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR, HASH, EQUALS>::~map_data()
{
   remove_all();
   ASSERT(m_nCount == 0);
}

template <class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class PAIR, typename HASH, typename EQUALS >
typename map_data <KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR, HASH, EQUALS>::assoc *
   map_data <KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR, HASH, EQUALS>::new_assoc(ARG_KEY key)
{

   if(m_passocFree == NULL)
   {
      // add another block
      plex * newBlock = plex::create(m_pplex, m_nBlockSize, sizeof(map_data::assoc));
      // chain them into free list
      map_data::assoc* passoc = (map_data::assoc*) newBlock->data();
      // free in reverse order to make it easier to debug
      index i = m_nBlockSize - 1;
      for (passoc = &passoc[i]; i >= 0; i--, passoc--)
      {
         passoc->m_pnext = m_passocFree;
         m_passocFree = passoc;

      }
   }

   ENSURE(m_passocFree != NULL);  // we must have something

   typename map_data <KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR, HASH, EQUALS>::assoc * passoc = m_passocFree;

   if (m_passocTail == NULL)
   {

      m_passocTail = passoc;

   }


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

   ::new(passoc) typename map_data <KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR, HASH, EQUALS>::assoc(key);

   return passoc;

}

template <class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class PAIR, typename HASH, typename EQUALS >
void map_data <KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR, HASH, EQUALS>::free_assoc(assoc * passoc)
{

   assoc * pnext = passoc->m_pnext;

   assoc * pprev = passoc->m_pprev;

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

   if (m_passocTail == passoc)
   {

      m_passocTail = pprev;

      if (m_passocTail != NULL)
      {

         m_passocTail->m_pnext = NULL;

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

template <class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class PAIR, typename HASH, typename EQUALS >
typename map_data <KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR, HASH, EQUALS>::assoc *
   map_data <KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR, HASH, EQUALS>::get_assoc_at(ARG_KEY key, UINT& nHashBucket, UINT& nHashValue) const
   // find association (or return NULL)
{

   nHashValue = HASH::run<ARG_KEY>(key);

   nHashBucket = nHashValue % m_hashtable.GetHashTableSize();

   if(get_count() <= 0)
      return NULL;

   // see if it exists
   assoc * passoc;

   for(passoc = m_hashtable.m_ppassocHash[nHashBucket]; passoc != NULL; passoc = passoc->m_pnextHash)
   {

      if(EQUALS::run<ARG_KEY>(passoc->m_element1, key))
         return passoc;

   }

   return NULL;

}

template <class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class PAIR, typename HASH, typename EQUALS >
bool map_data <KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR, HASH, EQUALS>::lookup(ARG_KEY key, VALUE& rValue) const
{
   //ASSERT_VALID(this);

   UINT nHashBucket, nHashValue;

   assoc* passoc = get_assoc_at(key, nHashBucket, nHashValue);

   if (passoc == NULL)
      return FALSE;  // not in map_data

   rValue = passoc->m_element2;

   return TRUE;

}

template <class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class PAIR, typename HASH, typename EQUALS >
typename map_data <KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR, HASH, EQUALS>::iterator map_data <KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR, HASH, EQUALS>::find (ARG_KEY key)
{
   
   return iterator(find_first(key));

}

template <class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class PAIR, typename HASH, typename EQUALS >
typename map_data <KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR, HASH, EQUALS>::const_iterator map_data <KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR, HASH, EQUALS>::find (ARG_KEY key) const
{
   return const_iterator(find_first(key));
}


template <class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class PAIR, typename HASH, typename EQUALS >
typename map_data <KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR, HASH, EQUALS>::const_iterator map_data <KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR, HASH, EQUALS>::find_first(ARG_KEY key) const
{
   //ASSERT_VALID(this);

   UINT nHashBucket, nHashValue;
   assoc* passoc = get_assoc_at(key, nHashBucket, nHashValue);
   return passoc;
}

template <class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class PAIR, typename HASH, typename EQUALS >
typename map_data <KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR, HASH, EQUALS>::iterator map_data <KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR, HASH, EQUALS>::find_first(ARG_KEY key)
{
   //ASSERT_VALID(this);

   UINT nHashBucket, nHashValue;
   assoc* passoc = get_assoc_at(key, nHashBucket, nHashValue);
   return passoc;
}


template <class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class PAIR, typename HASH, typename EQUALS >
typename map_data <KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR, HASH, EQUALS>::const_iterator map_data <KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR, HASH, EQUALS>::find_first_key(ARG_KEY key) const
{

   return find_first(key);

}



template <class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class PAIR, typename HASH, typename EQUALS >
typename map_data <KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR, HASH, EQUALS>::iterator map_data <KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR, HASH, EQUALS>::find_first_key(ARG_KEY key)
{

   return find_first(key);

}


template <class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class PAIR, typename HASH, typename EQUALS >
VALUE * map_data <KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR, HASH, EQUALS>::pget(ARG_KEY key)
{
   
   pair * p = find_first(key);

   if (p)
   {

      return &p->m_element2;

   }

   
   return NULL;

}


template <class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class PAIR, typename HASH, typename EQUALS >
typename map_data <KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR, HASH, EQUALS>::assoc * map_data <KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR, HASH, EQUALS>::get_assoc(ARG_KEY key)
{

   ASSERT_VALID(this);

   UINT nHashBucket,nHashValue;

   assoc * passoc;

   if((passoc = get_assoc_at(key,nHashBucket,nHashValue)) == NULL)
   {

      // not precise (memleak? a watch dog can restart from the last check point... continuable tasks need...) but self-healing(self-recoverable/not-fatal)...
      if(void_ptr_is_null(m_hashtable.m_ppassocHash))
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


template <class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class PAIR, typename HASH, typename EQUALS >
VALUE& map_data <KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR, HASH, EQUALS>::operator[](ARG_KEY key)
{

   return get_assoc(key)->m_element2;  // return new reference

}

template <class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class PAIR, typename HASH, typename EQUALS >
const VALUE & map_data <KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR, HASH, EQUALS>::operator[](ARG_KEY key) const
{

   return get_assoc(key)->m_element2;  // return new reference

}

template <class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class PAIR, typename HASH, typename EQUALS >
bool map_data <KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR, HASH, EQUALS>::remove_key(ARG_KEY key)
   // remove key - return TRUE if removed
{
   
   ASSERT_VALID(this);

   if (get_count() <= 0)
      return false;  // nothing in the table

   UINT nHashValue;
   
   nHashValue = HASH::run<ARG_KEY>(key);

   assoc * passoc = m_hashtable.m_ppassocHash[nHashValue%m_hashtable.GetHashTableSize()];

   for(; passoc != NULL; passoc = passoc->m_pnextHash)
   {

      if(EQUALS::run<ARG_KEY>(passoc->m_element1, key))
      {

         remove_assoc(passoc);

         return true;

      }

   }

   return false;  // not found

}

template <class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class PAIR, typename HASH, typename EQUALS >
inline bool map_data <KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR, HASH, EQUALS>::remove_assoc(assoc * passoc)
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


template <class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class PAIR, typename HASH, typename EQUALS >
inline ::count map_data <KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR, HASH, EQUALS>::count(const KEY & key) const
{

   return this->find_first(key) != this->end() ? 1 : 0;

}

template <class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class PAIR, typename HASH, typename EQUALS >
bool map_data <KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR, HASH, EQUALS>::has(const KEY & key) const
{

   return this->find_first(key) != this->end() ? 1 : 0;

}

template <class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class PAIR, typename HASH, typename EQUALS >
bool map_data <KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR, HASH, EQUALS>::contains(const KEY & key) const
{

   return this->find_first(key) != this->end() ? 1 : 0;

}




//template <class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class PAIR, typename HASH, typename EQUALS >
//::count map_data <KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR, HASH, EQUALS>::erase(const KEY & key)
//{
//
//   return remove_key(key) ? 1 : 0;
//
//}



template <class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class PAIR, typename HASH, typename EQUALS >
void map_data <KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR, HASH, EQUALS>::remove(PAIR & pair)
{

   remove_assoc((map_association < PAIR > *) &pair);

}

template <class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class PAIR, typename HASH, typename EQUALS >
void map_data <KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR, HASH, EQUALS>::erase(iterator & it)
{
   
   iterator itRemove = it;
   it++;
   remove_assoc(it.m_passoc);

}

template <class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class PAIR, typename HASH, typename EQUALS >
void map_data <KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR, HASH, EQUALS>::erase(iterator & it, iterator last)
{

   while (it != end() && it != last)
   {

      erase(it);

   }


}


template <class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class PAIR, typename HASH, typename EQUALS >
void map_data <KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR, HASH, EQUALS>::erase_count(iterator & it, ::count c)
{

   while (c > 0 && it != end())
   {

      erase(it);

      c--;

   }


}


template <class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class PAIR, typename HASH, typename EQUALS >
void map_data <KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR, HASH, EQUALS>::remove_at(index first)
{
   
   auto it = index_iterator(first);
   
   erase(it);

}


template <class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class PAIR, typename HASH, typename EQUALS >
void map_data <KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR, HASH, EQUALS>::remove_at(index first, ::count c)
{
   
   auto it = index_iterator(first);
   
   while (c > 0 && it != end())
   {
      
      erase(it);

      c--;

   }

}


template <class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class PAIR, typename HASH, typename EQUALS >
typename map_data <KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR, HASH, EQUALS>::iterator map_data <KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR, HASH, EQUALS>::index_iterator(index i)
{

   if (i < 0)
   {

      return end();

   }
   
   auto it = begin();
   
   while (i > 0 && it != end())
   {
      
      i--;

      it++;

   }

   return it;

}


template <class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class PAIR, typename HASH, typename EQUALS >
typename map_data <KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR, HASH, EQUALS>::const_iterator map_data <KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR, HASH, EQUALS>::index_iterator(index i) const
{

   if (i < 0)
   {

      return end();

   }

   auto it = begin();

   while (i > 0 && it != end())
   {

      i--;

      i++;

   }

   return it;

}

//template <class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class PAIR, typename HASH, typename EQUALS >
//inline void map_data <KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR, HASH, EQUALS>::remove(iterator & it)
//{
//
//   erase(it);
//
//}



//template <class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class PAIR, typename HASH, typename EQUALS >
//inline void map_data <KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR, HASH, EQUALS>::remove_at(iterator & it)
//{
//
//   remove(it);
//
//}

//template <class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class PAIR, typename HASH, typename EQUALS >
//void map_data <KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR, HASH, EQUALS>::get_next_assoc(POSITION& rNextPosition,
//                                                                         KEY& rKey, VALUE& rValue) const
//{
//   
//   ASSERT_VALID(this);
//   
//   if(m_hashtable.m_ppassocHash == NULL)
//   {
//
//      debug_print("map_data::get_next_assoc m_ppassocHash == NULL");
//
//   }
//
//   ENSURE(m_hashtable.m_ppassocHash != NULL);  // never call on is_empty map_data
//
//   assoc* passocRet = (assoc*)rNextPosition;
//   ENSURE(passocRet != NULL);
//
//   if (passocRet == (assoc*) BEFORE_START_POSITION)
//   {
//      passocRet = m_passocHead;
//      if(passocRet == NULL)
//         throw error_exception(get_app(), "map_data <KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR, HASH, EQUALS>::get_next_assoc : must find something");
//   }
//
//   rNextPosition = (POSITION) passocRet->m_pnext;
//
//   // fill in return data
//   rKey = passocRet->m_element1;
//   rValue = passocRet->m_element2;
//}

//template <class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class PAIR, typename HASH, typename EQUALS >
//const typename map_data <KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR, HASH, EQUALS>::assoc*
//   map_data <KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR, HASH, EQUALS>::PGetNextAssoc(const typename map_data <KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR, HASH, EQUALS>::pair* ppair) const
//{
//
//   return ((assoc *)ppair)->m_pnext;
//
//}

//template <class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class PAIR, typename HASH, typename EQUALS >
//typename map_data <KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR, HASH, EQUALS>::assoc*
//   map_data <KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR, HASH, EQUALS>::PGetNextAssoc(const typename map_data <KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR, HASH, EQUALS>::pair* ppair)
//{
//
//   return ((assoc *)ppair)->m_pnext;
//
//}

template <class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class PAIR, typename HASH, typename EQUALS >
VALUE map_data <KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR, HASH, EQUALS> ::
   get(ARG_KEY argkey, ARG_VALUE valueDefault)
{
   
   auto it = find_first(argkey);

   if (it == end())
   {

      return valueDefault;

   }
   
   return it->m_element2;

}


/*
template <class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class PAIR, typename HASH, typename EQUALS >
void map_data <KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR, HASH, EQUALS>::Serialize(CArchive& ar)
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

template <class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class PAIR, typename HASH, typename EQUALS >
void map_data <KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR, HASH, EQUALS>::dump(dump_context & dumpcontext) const
{
   object::dump(dumpcontext);

   dumpcontext << "with " << m_nCount << " elements";
   if (dumpcontext.GetDepth() > 0)
   {
      // Dump in format "[key] -> value"

      auto it = begin();
      while (it != end())
      {
         dumpcontext << "\n\t[";
         dump_elements<KEY>(dumpcontext, &it->m_element1, 1);
         dumpcontext << "] = ";
         dump_elements<VALUE>(dumpcontext, &it->m_element2, 1);
         it++;
      }
   }

   dumpcontext << "\n";
}

template <class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class PAIR, typename HASH, typename EQUALS >
void map_data <KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR, HASH, EQUALS>::assert_valid() const
{
   object::assert_valid();

   ASSERT(GetHashTableSize() > 0);
   ASSERT(m_nCount == 0 || m_hashtable.m_ppassocHash != NULL);
   // non-is_empty map_data should have hash table
}







#define ptrptr(T1, T2) map_data < T1 *, T1 *, T2 *, T2 * >



template <class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class PAIR, typename HASH, typename EQUALS >
::file::ostream & operator << (::file::ostream & os,const map_data <KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR, HASH, EQUALS> & a)
{
   ::file::map::write(os,a);
   return os;
}

template <class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class PAIR, typename HASH, typename EQUALS >
::file::istream & operator >> (::file::istream & is,map_data <KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR, HASH, EQUALS> & a)
{
   ::file::map::read(is,a);
   return is;
}








//template < class VALUE, class ARG_VALUE = const VALUE & >
//using double_map = map_data < double, double, VALUE, ARG_VALUE >;
//
//using double_to_double = double_map < double, double >;
//



