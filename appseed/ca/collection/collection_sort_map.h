#pragma once


#undef new


namespace collection
{


   template <class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE = gen::compare < KEY > >
   class sort_map :
      virtual public ::gen::object
   {
   public:


      typedef KEY          BASE_KEY;
      typedef ARG_KEY      BASE_ARG_KEY;
      typedef VALUE        BASE_VALUE;
      typedef ARG_VALUE    BASE_ARG_VALUE;
      typedef COMPARE      BASE_COMPARE;


      class pair
      {
      public:
         const KEY m_key;
         VALUE m_value;
         pair(const KEY & key) : m_key(key) {}
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

      const pair *PGetNextAssoc(const pair *pAssocRet) const;
      pair *PGetNextAssoc(const pair *pAssocRet);

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
            set_at(ppair->m_key, ppair->m_value);
         }
      }


      index    find_pair(pair * ppair) const;
      bool     find_key(ARG_KEY key, index & i) const;

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
   inline count sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::count() const
   { return m_ptra.get_count(); }

   template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE >
   inline count sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::size() const
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

         set_at(pairs[i].m_key, pairs[i].m_value);

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

      pair * pAssoc = PLookup(key);

      if (pAssoc == NULL)
         return false;

      rValue = pAssoc->m_value;

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
         return &p->m_value;
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

      return ppair->m_value;  // return new reference

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

         iCompare = BASE_COMPARE::CompareElements(&m_ptra[i]->m_key, &key);

         if(iCompare == 0)
            return true;
         else if(iCompare > 0)
            hi = i;
         else
            lo = i;

      }

      for(i = 0; i < hi; i++)
      {

         if(BASE_COMPARE::CompareElements(&m_ptra[i]->m_key, &key) == 0)
            return true;

      }

      for(; i >= 0; i--)
      {

         if(BASE_COMPARE::CompareElements(&m_ptra[i]->m_key, &key) < 0)
            break;

      }

      i++;

      return false;

   }

   template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE >
   index sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::add_pair(ARG_KEY key, ARG_VALUE newValue)
   {

      index i;

      if(!find_key(key, i))
      {

         m_ptra.insert_at(i, new pair(key));

      }

      m_ptra[i]->m_value = newValue;

      return i;

   }




   template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE >
   ::count sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::erase(const KEY & key)
   {

      return remove_key(key) ? 1 : 0;

   }

   template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE >
   void sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::erase(iterator it)
   {

      remove_key(it->m_key);

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
         iFirst = m_ptra.find(first.m_ppair);

      if(iFirst < 0)
         return;

      if(last.m_ppair == NULL)
         iFirst = 0;
      else
         iFirst = m_ptra.find(first.m_ppair);

      if(iFirst < 0)
         return;



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
      rKey           = m_ptra[iRet - 1]->m_key;
      rValue         = m_ptra[iRet - 1]->m_value;

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

      index iRet = (index) find_pair(pPairRet);

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
         return ppair->m_value;
   }


   template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE >
   void sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::dump(dump_context & dumpcontext) const
   {
      ::gen::object::dump(dumpcontext);

      dumpcontext << "with " << m_ptra.get_count() << " elements";
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

   template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE >
   void sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE >::assert_valid() const
   {

      ::gen::object::assert_valid();

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
   sort_attrib_map < type_map > & sort_attrib_map < type_map >::operator = (const sort_attrib_map & attribmap)
   {

      if(this != &attribmap)
      {

         this->remove_all();

         typename type_map::pair * ppair;

         for(index i = 0; i < attribmap.m_ptra.get_count(); i++)
         {

            ppair      = new typename type_map::pair(attribmap.m_ptra[i]->m_key);

            ppair->m_value    = attribmap.m_ptra[i]->m_value;

            this->m_ptra.add(ppair);

         }

      }

      return *this;

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

         if(attribmap.m_ptra[i]->m_key       != this->m_ptra[i]->m_key
         || attribmap.m_ptra[i]->m_value     != this->m_ptra[i]->m_value)
         {

            return false;

         }

      }

      return true;

   }


   template < class VALUE, class ARG_VALUE = const VALUE &, class COMPARE = gen::compare < string > >
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
   sort_string_map < VALUE, ARG_VALUE, COMPARE >::sort_string_map(const sort_string_map & sort_map) :
      sort_attrib_map < ::collection::sort_map < string, const string &, VALUE, ARG_VALUE, COMPARE > > (sort_map)
   {
   }

   template < class VALUE, class ARG_VALUE, class COMPARE >
   sort_string_map < VALUE, ARG_VALUE, COMPARE > & sort_string_map < VALUE, ARG_VALUE, COMPARE >::operator = (const sort_string_map & sort_map)
   {

      if(this != &sort_map)
      {

         sort_attrib_map < ::collection::sort_map < string, const string &, VALUE, ARG_VALUE, COMPARE > >::operator = (sort_map);

      }

      return *this;

   }

   template < class VALUE, class ARG_VALUE = const VALUE &, class COMPARE = gen::strid_compare  >
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
   sort_strid_map < VALUE, ARG_VALUE, COMPARE >::sort_strid_map(const sort_strid_map & sort_map) :
      sort_attrib_map < ::collection::sort_map < id, const id &, VALUE, ARG_VALUE > > (sort_map)
   {
   }

   template < class VALUE, class ARG_VALUE, class COMPARE >
   sort_strid_map < VALUE, ARG_VALUE, COMPARE > & sort_strid_map < VALUE, ARG_VALUE, COMPARE >::operator = (const sort_strid_map & sort_map)
   {

      if(this != &sort_map)
      {
         sort_attrib_map < ::collection::sort_map < id, const id &, VALUE, ARG_VALUE > >::operator = (sort_map);
      }

      return *this;

   }

   template < class VALUE, class ARG_VALUE = const VALUE &, class COMPARE = gen::compare < int32_t > >
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
   sort_int_map < VALUE, ARG_VALUE, COMPARE >::sort_int_map(const sort_int_map & sort_map) :
      sort_attrib_map < ::collection::sort_map < int32_t, int32_t, VALUE, ARG_VALUE, COMPARE > > (sort_map)
   {
   }

   template < class VALUE, class ARG_VALUE, class COMPARE >
   sort_int_map < VALUE, ARG_VALUE, COMPARE > & sort_int_map < VALUE, ARG_VALUE, COMPARE >::operator = (const sort_int_map & sort_map)
   {

      if(this != &sort_map)
      {
         sort_attrib_map < ::collection::sort_map < int32_t, int32_t, VALUE, ARG_VALUE, COMPARE > >::operator = (sort_map);
      }

      return *this;

   }

   typedef CLASS_DECL_ca sort_attrib_map < sort_map < int32_t, int32_t, int32_t, int32_t > > sort_int_to_int;
   typedef CLASS_DECL_ca sort_attrib_map < sort_map < int32_t, int32_t, string, const string & > > sort_int_to_string;
   typedef CLASS_DECL_ca ::collection::sort_string_map < void *, void * > sort_string_to_ptr;

   template < class T >
   class CLASS_DECL_ca sort_string_to_pointer :
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


   typedef CLASS_DECL_ca ::collection::sort_string_map < int_ptr, int_ptr > sort_string_to_intptr;


} // namespace collection


typedef CLASS_DECL_ca ::collection::sort_string_map < string, const string & > sort_string_to_string_map;


#define new DEBUG_NEW
