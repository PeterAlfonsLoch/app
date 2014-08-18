#pragma once





template <class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE = ::comparison::binary < KEY > >
class sort_map :
   virtual public ::object
{
public:


   typedef KEY          AXIS_KEY;
   typedef ARG_KEY      AXIS_ARG_KEY;
   typedef VALUE        AXIS_VALUE;
   typedef ARG_VALUE    AXIS_ARG_VALUE;
   typedef COMPARE      AXIS_COMPARE;


   class pair
   {
   public:
      const KEY   m_element1;
      VALUE       m_element2;
      pair(const KEY & key) : m_element1(key) {}
   };



   class iterator
   {
   public:


      pair *         m_ppair;
      sort_map *     m_pmap;


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

      iterator(pair * ppair, sort_map * pmap)
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


      const pair *         m_ppair;
      const sort_map *     m_pmap;


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

      const_iterator(const const_iterator & iterator)
      {
         m_ppair  = iterator.m_ppair;
         m_pmap   = iterator.m_pmap;
      }

      const_iterator(const pair * ppair, const sort_map * pmap)
      {
         m_ppair  = ppair;
         m_pmap   = pmap;
      }

      const pair * operator -> ()
      {
         return m_ppair;
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

      const_iterator & operator = (const iterator & it)
      {
         m_pmap         = it.m_pmap;
         m_ppair        = it.m_ppair;
         return *this;
      }

   };

   comparable_array < pair *, pair * >   m_ptra;





   sort_map(::count nBlockSize = 10);
   sort_map(pair pairs[], int32_t iCount, ::count nBlockSize = 10);
   virtual ~sort_map();



   void construct(::count nBlockSize = 10);


   void dump(dump_context &) const;
   void assert_valid() const;


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
      return const_iterator(PGetFirstAssoc(), this);
   }


   const_iterator end() const
   {
      return const_iterator(NULL, this);
   }

   iterator lower_bound (ARG_KEY k);
   const_iterator lower_bound (ARG_KEY k) const;
   iterator upper_bound (ARG_KEY k);
   const_iterator upper_bound (ARG_KEY k) const;

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
   VALUE & operator[](ARG_KEY key);

   // add a new (key, value) pair
   void set_at(ARG_KEY key, ARG_VALUE newValue);

   // removing existing (key, ?) pair
   bool remove_key(ARG_KEY key);
   void erase(iterator it);
   ::count erase(const KEY & key);
   void erase ( iterator first, iterator last );
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

   const pair *PGetNextAssoc(const pair *passocRet) const;
   pair *PGetNextAssoc(const pair *passocRet);

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


   void set(sort_map & sort_map)
   {
      pair * ppair = NULL;
      while(sort_map.next(ppair) != NULL)
      {
         set_at(ppair->m_element1, ppair->m_element2);
      }
   }


   index    find_pair(pair * ppair) const;
   bool     find_key(ARG_KEY key, index & i) const;

   iterator find(ARG_KEY key);
   const_iterator find(ARG_KEY key) const;

   index    add_pair(ARG_KEY key, ARG_VALUE value);

};

/////////////////////////////////////////////////////////////////////////////
// sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE > inline functions



template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE >
inline ::count sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::get_count() const
{ return m_ptra.get_count(); }

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE >
inline ::count sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::get_size() const
{ return m_ptra.get_count(); }

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE >
inline ::count sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::count() const
{ return m_ptra.get_count(); }

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE >
inline ::count sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::size() const
{ return m_ptra.get_count(); }

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE >
inline bool sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::is_empty() const
{ return m_ptra.get_count() == 0; }

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE >
inline void sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::set_at(ARG_KEY key, ARG_VALUE newValue)
{  add_pair(key, newValue); }

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE >
inline POSITION sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::get_start_position() const
{ return (m_ptra.get_count() == 0) ? NULL : BEFORE_START_POSITION; }

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE >
const typename sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::pair* sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::PGetFirstAssoc() const
{

   ASSERT_VALID(this);

   if(m_ptra.get_count() <= 0)
      return NULL;

   return m_ptra[0];

}

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE >
typename sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::pair* sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::PGetFirstAssoc()
{

   if(m_ptra.get_count() <= 0)
      return NULL;

   return m_ptra[0];

}


template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE >
void sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::construct(::count nBlockSize)
{

   UNREFERENCED_PARAMETER(nBlockSize);

}

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE >
sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::sort_map(::count nBlockSize)
{

   construct(nBlockSize);

}

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE >
sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::sort_map(pair pairs[], int32_t iCount, ::count nBlockSize)
{

   construct(nBlockSize);

   for(int32_t i = 0; i < iCount; i++)
   {

      set_at(pairs[i].m_element1, pairs[i].m_element2);

   }

}


template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE >
void sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::remove_all()
{

   ASSERT_VALID(this);

   for(index i = 0; i < m_ptra.get_count(); i++)
   {

      delete m_ptra[i];

   }

   m_ptra.remove_all();

}

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE >
inline void sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::clear()
{

   remove_all();

}

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE >
sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::~sort_map()
{

   remove_all();

}



template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE >
bool sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::Lookup(ARG_KEY key, VALUE& rValue) const
{

   pair * passoc = PLookup(key);

   if (passoc == NULL)
      return false;

   rValue = passoc->m_element2;

   return TRUE;

}

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE >
const typename sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::pair* sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::PLookup(ARG_KEY key) const
{

   index i;

   if(!find_key(key, i))
      return NULL;

   return m_ptra[i];

}

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE >
typename sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::pair* sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::PLookup(ARG_KEY key)
{

   index i;

   if(!find_key(key, i))
      return NULL;

   return m_ptra[i];

}

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE >
VALUE * sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::pget(ARG_KEY key)
{

   pair * p = PLookup(key);

   if(p)
      return &p->m_element2;
   else
      return NULL;

}

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE >
VALUE& sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::operator[](ARG_KEY key)
{

   ASSERT_VALID(this);

   pair * ppair = PLookup(key);

   if(ppair == NULL)
   {

      add_pair(key, VALUE());

      ppair = PLookup(key);

      ASSERT(ppair != NULL);

   }

   return ppair->m_element2;  // return new reference

}

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE >
bool sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::remove_key(ARG_KEY key)
   // remove key - return TRUE if removed
{

   ASSERT_VALID(this);

   index i;

   if(!find_key(key, i))
      return false;  // nothing in the table

   delete m_ptra[i];

   m_ptra.remove_at(i);

   return true;

}

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE >
::index sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::find_pair(pair * ppair) const
{

   if(ppair == NULL)
      return m_ptra.get_size();

   if(ppair == (pair *) (uint_ptr) -1)
      return 0;

   return m_ptra.find_first(ppair);


}

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE >
typename sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::iterator sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::find(ARG_KEY key)
{

   index i;

   if(!find_key(key, i))
      return end();

   return iterator(m_ptra[i], this);

}

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE >
typename sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::const_iterator sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::find(ARG_KEY key) const
{

   index i;

   if(!find_key(key, i))
      return end();

   return const_iterator(m_ptra[i], this);

}


template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE >
bool sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::find_key(ARG_KEY key, index & i) const
{

   index lo = 0;
   index hi = m_ptra.get_upper_bound();
   int_ptr iCompare;

   while(true)
   {

      if(lo + 3 > hi)
         break;

      i = (hi + lo) / 2;

      iCompare = AXIS_COMPARE::CompareElements(&m_ptra[i]->m_element1, &key);

      if(iCompare == 0)
         return true;
      else if(iCompare > 0)
         hi = i;
      else
         lo = i;

   }

   for(i = 0; i < hi; i++)
   {

      if(AXIS_COMPARE::CompareElements(&m_ptra[i]->m_element1, &key) == 0)
         return true;

   }

   for(; i >= 0; i--)
   {

      if(AXIS_COMPARE::CompareElements(&m_ptra[i]->m_element1, &key) < 0)
         break;

   }

   i++;

   return false;

}


template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE >
typename sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::iterator sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::lower_bound (ARG_KEY k)
{

   index i = 0;

   find_key(k, i);

   if(i <= 0 || i >= m_ptra.get_size())
      return end();
   else
      return iterator(m_ptra[i], this);

}

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE >
typename sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::const_iterator sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::lower_bound (ARG_KEY k) const
{

   index i = 0;

   find_key(k, i);

   if(i <= 0 || i >= m_ptra.get_size())
      return end();
   else
      return const_iterator(m_ptra[i], this);

}

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE >
typename sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::iterator sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::upper_bound (ARG_KEY k)
{

   index i = 0;

   if(find_key(k, i))
   {
      i++;
   }

   if(i <= 0 || i >= m_ptra.get_size())
      return end();
   else
      return iterator(m_ptra[i], this);

}

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE >
typename sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::const_iterator sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::upper_bound (ARG_KEY k) const
{

   index i = 0;

   if(find_key(k, i))
   {
      i++;
   }

   if(i <= 0 || i >= m_ptra.get_size())
      return end();
   else
      return const_iterator(m_ptra[i], this);

}


template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE >
::count sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::erase(const KEY & key)
{

   return remove_key(key) ? 1 : 0;

}

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE >
void sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::erase(iterator it)
{

   remove_key(it->m_element1);

}

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE >
::count sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::count(const KEY & key) const
{

   return this->PLookup(key) != NULL ? 1 : 0;

}

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE >
bool sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::has(const KEY & key) const
{

   return this->PLookup(key) != NULL;

}

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE >
bool sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::contains(const KEY & key) const
{

   return this->PLookup(key) != NULL;

}

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE >
void sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::erase(iterator first, iterator last)
{

   if(first.m_pmap != this || last.m_pmap != this)
      return;

   index iFirst;

   if(first.m_ppair == (pair *) (uint_ptr) (-1))
      iFirst = 0;
   else
      iFirst = m_ptra.find_first(first.m_ppair);

   if(iFirst < 0)
      return;

   index iLast;

   if(last.m_ppair == NULL)
      iLast = m_ptra.get_size();
   else
      iLast = m_ptra.find_first(first.m_ppair);

   if(iLast < 0)
      return;

   while(iLast-- > iFirst)
      delete m_ptra.pop();

}


template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE >
void sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::get_next_assoc(POSITION& rNextPosition, KEY& rKey, VALUE& rValue) const
{

   ASSERT_VALID(this);

   ENSURE(m_ptra.get_count() > 0);  // never call on is_empty sort_map

   index iRet = (index) rNextPosition;

   if (iRet == (index) BEFORE_START_POSITION)
   {
      iRet = 1;
   }

   // find next association
   index iNext = iRet + 1;
   if(iNext > m_ptra.get_count())
   {

   }

   rNextPosition  = (POSITION) iNext;

   // fill in return data
   rKey           = m_ptra[iRet - 1]->m_element1;
   rValue         = m_ptra[iRet - 1]->m_element2;

}

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE >
const typename sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::pair*
   sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::PGetNextAssoc(const typename sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::pair* pPairRet) const
{

   ASSERT_VALID(this);

   ENSURE(m_ptra.get_count() > 0);  // never call on is_empty sort_map

   index iRet = (index) find_pair(const_cast < pair * > (pPairRet));

   // find next association
   iRet++;

   if(iRet >= m_ptra.get_count())
   {

      return NULL;

   }

   return m_ptra[iRet];

}

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE >
typename sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::pair*
   sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::PGetNextAssoc(const typename sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::pair* pPairRet)
{

   ASSERT_VALID(this);

   ENSURE(m_ptra.get_count() > 0);  // never call on is_empty sort_map

   index iRet = (index) find_pair((pair *) pPairRet);

   // find next association
   iRet++;

   if(iRet >= m_ptra.get_count())
   {

      return NULL;

   }

   return m_ptra[iRet];

}

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE >
VALUE sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE > ::
   get(ARG_KEY argkey, ARG_VALUE valueDefault)
{
   pair * ppair = PLookup(argkey);
   if(ppair == NULL)
      return valueDefault;
   else
      return ppair->m_element2;
}


template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE >
void sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::dump(dump_context & dumpcontext) const
{
   object::dump(dumpcontext);

   dumpcontext << "with " << m_ptra.get_count() << " elements";
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

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE >
void sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::assert_valid() const
{

   object::assert_valid();

}



template < class type_map >
class sort_attrib_map :
   virtual public type_map
{
public:


   sort_attrib_map(int_ptr nBlockSize = 10);
   sort_attrib_map(const sort_attrib_map & sort_map);

   sort_attrib_map & operator = (const sort_attrib_map & sort_map);

   bool operator == (const sort_attrib_map & sort_map) const;


};


template < class type_map >
sort_attrib_map < type_map >::sort_attrib_map(int_ptr nBlockSize) :
   type_map(nBlockSize)
{
}

template < class type_map >
sort_attrib_map < type_map >::sort_attrib_map(const sort_attrib_map & attribmap)
{
   operator = (attribmap);
}


template < class type_map >
bool sort_attrib_map < type_map >::operator == (const sort_attrib_map & attribmap) const
{

   if(this == &attribmap)
      return true;

   if(this->m_ptra.get_size() != attribmap.get_size())
      return false;

   for(index i = 0; i < attribmap.m_ptra.get_count(); i++)
   {

      if(attribmap.m_ptra[i]->m_element1       != this->m_ptra[i]->m_element1
         || attribmap.m_ptra[i]->m_element2     != this->m_ptra[i]->m_element2)
      {

         return false;

      }

   }

   return true;

}


template < class VALUE, class ARG_VALUE = const VALUE &, class COMPARE = ::comparison::binary < string > >
class sort_string_map :
   virtual public sort_attrib_map < sort_map < string, const string &, VALUE, ARG_VALUE, COMPARE > >
{
public:


   sort_string_map(::count nBlockSize = 10);
   sort_string_map(const sort_string_map & sort_map);


   sort_string_map & operator = (const sort_string_map & sort_map);


};

template < class VALUE, class ARG_VALUE, class COMPARE >
sort_string_map < VALUE, ARG_VALUE, COMPARE >::sort_string_map(::count nBlockSize) :
   sort_map < string, const string &, VALUE, ARG_VALUE, COMPARE > (nBlockSize)
{
}

template < class VALUE, class ARG_VALUE, class COMPARE >
sort_string_map < VALUE, ARG_VALUE, COMPARE >::sort_string_map(const sort_string_map & sortmap) :
   sort_attrib_map < sort_map < string, const string &, VALUE, ARG_VALUE, COMPARE > > (sortmap)
{
}

template < class VALUE, class ARG_VALUE, class COMPARE >
sort_string_map < VALUE, ARG_VALUE, COMPARE > & sort_string_map < VALUE, ARG_VALUE, COMPARE >::operator = (const sort_string_map & sortmap)
{

   if(this != &sortmap)
   {

      sort_attrib_map < sort_map < string, const string &, VALUE, ARG_VALUE, COMPARE > >::operator = (sortmap);

   }

   return *this;

}

template < class VALUE, class ARG_VALUE = const VALUE &, class COMPARE = ::comparison::strid_binary  >
class sort_strid_map :
   virtual public sort_attrib_map < sort_map < id, const id &, VALUE, ARG_VALUE, COMPARE > >
{
public:

   sort_strid_map(::count nBlockSize = 256);
   sort_strid_map(const sort_strid_map & sort_map);


   sort_strid_map & operator = (const sort_strid_map & sort_map);


};


template < class VALUE, class ARG_VALUE, class COMPARE >
sort_strid_map < VALUE, ARG_VALUE, COMPARE >::sort_strid_map(::count nBlockSize) :
   sort_attrib_map < sort_map < id, const id &, VALUE, ARG_VALUE, COMPARE > > (nBlockSize)
{
}


template < class VALUE, class ARG_VALUE, class COMPARE >
sort_strid_map < VALUE, ARG_VALUE, COMPARE >::sort_strid_map(const sort_strid_map & sortmap) :
   sort_attrib_map < sort_map < id, const id &, VALUE, ARG_VALUE > > (sortmap)
{
}

template < class VALUE, class ARG_VALUE, class COMPARE >
sort_strid_map < VALUE, ARG_VALUE, COMPARE > & sort_strid_map < VALUE, ARG_VALUE, COMPARE >::operator = (const sort_strid_map & sortmap)
{

   if(this != &sortmap)
   {
      sort_attrib_map < sort_map < id, const id &, VALUE, ARG_VALUE > >::operator = (sortmap);
   }

   return *this;

}

template < class VALUE, class ARG_VALUE = const VALUE &, class COMPARE = ::comparison::binary < int32_t > >
class sort_int_map :
   virtual public sort_attrib_map < sort_map < int32_t, int32_t, VALUE, ARG_VALUE, COMPARE > >
{
public:

   sort_int_map(::count nBlockSize = 10);
   sort_int_map(const sort_int_map & sort_map);


   sort_int_map & operator = (const sort_int_map & sort_map);

};

template < class VALUE, class ARG_VALUE, class COMPARE >
sort_int_map < VALUE, ARG_VALUE, COMPARE >::sort_int_map(::count nBlockSize) :
   sort_map < int32_t, int32_t, VALUE, ARG_VALUE, COMPARE > (nBlockSize)
{
}

template < class VALUE, class ARG_VALUE, class COMPARE >
sort_int_map < VALUE, ARG_VALUE, COMPARE >::sort_int_map(const sort_int_map & sortmap) :
   sort_attrib_map < sort_map < int32_t, int32_t, VALUE, ARG_VALUE, COMPARE > > (sortmap)
{
}

template < class VALUE, class ARG_VALUE, class COMPARE >
sort_int_map < VALUE, ARG_VALUE, COMPARE > & sort_int_map < VALUE, ARG_VALUE, COMPARE >::operator = (const sort_int_map & sortmap)
{

   if(this != &sortmap)
   {
      sort_attrib_map < sort_map < int32_t, int32_t, VALUE, ARG_VALUE, COMPARE > >::operator = (sortmap);
   }

   return *this;

}

typedef CLASS_DECL_AXIS sort_attrib_map < sort_map < int32_t, int32_t, int32_t, int32_t > > sort_int_to_int;
typedef CLASS_DECL_AXIS sort_attrib_map < sort_map < int32_t, int32_t, string, const string & > > sort_int_to_string;
typedef CLASS_DECL_AXIS sort_string_map < void *, void * > sort_string_to_ptr;

template < class T >
class CLASS_DECL_AXIS sort_string_to_pointer :
   virtual public string_to_ptr
{
public:

   class pair
   {
   public:
      const string m_element1;
      T * m_element2;
   };

   bool Lookup(string key, T * & rValue) const
   {
      return string_to_ptr::Lookup(key, rValue);
   }
   const pair *PLookup(string key) const
   {
      return reinterpret_cast < const sort_string_to_pointer::pair * > (string_to_ptr::PLookup(key));
   }
   pair *PLookup(string key)
   {
      return reinterpret_cast < sort_string_to_pointer::pair * > (string_to_ptr::PLookup(key));
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


typedef CLASS_DECL_AXIS sort_string_map < int_ptr, int_ptr > sort_string_to_intptr;

typedef CLASS_DECL_AXIS sort_string_map < string, const string & > sort_string_to_string_map;



