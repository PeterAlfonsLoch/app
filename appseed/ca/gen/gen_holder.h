#pragma once




// ph - pointer holder
#define ph(holding_type) ::gen::holder < holding_type >
#define pha(holding_type) ::gen::holder_array < holding_type >
#define phm(key, arg_key, holding_type) ::gen::holder_map < key, arg_key, holding_type >


namespace gen
{
   template < class T >
   class holder_array;

   template < typename KEY,  typename ARG_KEY, class T >
   class holder_map;

   template < class T >
   class holder :
      virtual public ::radix::object
   {
   protected:
      friend class holder_array < T >;

      ::ca::ca * m_pca;
      T * m_p;


   public:

      virtual void on_delete(::ca::ca * pca)
      {
         if(m_pca == pca)
         {
            m_pca = NULL;
         }
         if(m_pca == NULL)
         {
            m_p = NULL;
         }
      }


      holder()
      {
         m_p = NULL;
         m_pca = NULL;
      }

      holder(T * p)
      {
         m_p = NULL;
         m_pca = NULL;
         set_p(p);
      }

      virtual ~holder();

      void set_p(T * p);

      holder & operator = (T * p)
      {
         set_p(p);
         return *this;
      }


      holder & operator = (const holder & h)
      {
         if(this == &h)
            return *this;
         set_p(h.m_p);
         return *this;
      }

      operator T *()
      {
         return m_p;
      }

      T * operator ->()
      {
         return m_p;
      }

      operator T *() const
      {
         return m_p;
      }

      T * operator ->() const
      {
         return m_p;
      }

      T * get_p()
      {
         return m_p;
      }

      T * get_p() const
      {
         return m_p;
      }

      ::ca::ca * get_pca()
      {
         return m_pca;
      }

      ::ca::ca * get_pca() const
      {
         return m_pca;
      }

   };

   template < class T >
   class holder_array :
      virtual public ::radix::object
   {
   public:


      raw_array < T * > m_ptra;
      raw_array < ::ca::ca * > m_captra;


      holder_array()
      {
      }

      holder_array(const holder_array & a);

      virtual ~holder_array()
      {
         remove_all();
      }

      virtual void on_delete(::ca::ca * pca)
      {
         remove(pca, true);
      }

      virtual void on_delete(T * p)
      {
         UNREFERENCED_PARAMETER(p);
      }

      virtual count remove_all();

      count set_size(count c)
      {
         if(c > this->get_size())
            throw "This array can only be clipped or mantained in size. The array will not grow.";

         while(this->get_size() > c)
         {
            remove_last();
         }

         return this->get_size();
      }

      virtual index remove_at(index iRemove, count count = 1);

      index add(T * p)
      {
         return add_unique(p);
      }

      index add_unique(T * p);

      index insert_at(index i, T * p);

      index set_at(index i, T * p);


      index find(T * p)
      {
         for(index i = 0; i < m_ptra.get_size(); i++)
         {
            if(m_ptra[i] == p)
            {
               return i;
            }
         }
         return -1;
      }

      bool is_empty() const
      {
         return m_ptra.is_empty();
      }

      T * get_at(index i)
      {
         return m_ptra[i];
      }

      T * get_at(index i) const
      {
         return m_ptra[i];
      }

      bool contains(T * p)
      {
         return find(p) >= 0;
      }

      T * operator[](index i)
      {
         return m_ptra[i];
      }

      T * operator[](index i) const
      {
         return m_ptra[i];
      }

      T * element_at(index i)
      {
         return m_ptra[i];
      }

      T * element_at(index i) const
      {
         return m_ptra[i];
      }

      count get_upper_bound(index i = 0) const
      {
         return m_ptra.get_upper_bound(i);
      }

      T * last_element(index i = 0)
      {
         return m_ptra[get_upper_bound(i)];
      }

      T * last_element(index i = 0) const
      {
         return m_ptra[get_upper_bound(i)];
      }

      T * first_element(index i = 0)
      {
         return m_ptra[i];
      }

      T * first_element(index i = 0) const
      {
         return m_ptra[i];
      }

      index remove_last()
      {
         return remove_at(get_upper_bound());
      }

      template < class ARRAY >
      void get_array(ARRAY & a)
      {
         for(index i = 0; i < m_ptra.get_count(); i++)
         {
            a.add(m_ptra[i]);
         }
      }

      count get_size() const
      {
         return m_ptra.get_size();
      }

      count get_count() const
      {
         return m_ptra.get_count();
      }

      count remove(T * p, bool bCallNativeArrayBaseTypeOnDelete = false);

      holder_array & operator = (const holder_array & a);

      bool has_elements(count countMinimum = 1)
      {
         return this->get_count() >= countMinimum;
      }

   protected:
      count remove(::ca::ca * pca, bool bCallNativeArrayBaseTypeOnDelete = false)
      {
         count count = 0;
         for(index i = 0; i < m_captra.get_size(); )
         {
            if(m_captra[i] == pca)
            {
               m_captra.remove_at(i);
               if(bCallNativeArrayBaseTypeOnDelete)
               {
                  try
                  {
                     on_delete(m_ptra.element_at(i));
                  }
                  catch(...)
                  {
                  }
               }
               m_ptra.remove_at(i);
               count++;
            }
            else
            {
               i++;
            }
         }
         return count;
      }

   };


   template < class KEY, class ARG_KEY, class T >
   class holder_map :
      virtual public ::radix::object
   {
   public:


      typedef ::collection::map < KEY, ARG_KEY, T *, T * > key_map;
      typedef ::collection::map < ::ca::ca *, ::ca::ca *, KEY, ARG_KEY > ca_map;

      key_map        m_keymap;
      ca_map         m_camap;




      virtual void on_delete(::ca::ca * pca)
      {
         remove(pca);
      }

      void set_at(ARG_KEY key, T * p)
      {
         ::ca::ca * pca = dynamic_cast < ::ca::ca * > (p);
         if(pca == NULL)
            return;
         if(pca->m_papp == NULL)
            return;
         if(pca->m_papp->m_psystem == NULL)
            return;
         m_papp = pca->m_papp;
         m_keymap.set_at(key, p);
         m_camap.set_at(pca, key);
      }

      T * operator[](ARG_KEY key)
      {
         return get_value(key);
      }

      const T * operator[](ARG_KEY key) const
      {
         return get_value(key);
      }

      T * get_value(ARG_KEY key)
      {
         typename key_map::pair * ppair = m_keymap.PLookup(key);
         if(ppair == NULL)
            return NULL;
         return ppair->m_value;
      }

      void remove_key(ARG_KEY key)
      {
         typename key_map::pair * ppair = m_keymap.PLookup(key);
         if(ppair == NULL)
            return;
         remove(dynamic_cast < ::ca::ca * > (ppair->m_value));
         m_keymap.remove_key(key);
      }

      void remove(::ca::ca * pca)
      {
          typename ca_map::pair * ppair = m_camap.PLookup(pca);
         if(ppair == NULL)
            return;
         m_keymap.remove_key(ppair->m_value);
         m_camap.remove_key(pca);
      }
   };

 }// namespace gen





/*
template < class DERIVED > class pointer;
template < class DERIVED  > class pointer_array;

// A pointer class add to its derived classes
// the ability to have pointer class features.
// One of the features is to notify the pointer
// object pointer arrays (listeners) when the
// pointer object is deleted.
template < class DERIVED >
class pointer
{
public:
   DERIVED * m_p;
   base_array < DERIVED ** , DERIVED ** > m_deriveda;
   comparable_array < pointer_array < DERIVED > *, pointer_array < DERIVED > * > m_listenera;

   pointer();
   virtual ~pointer();

   DERIVED * derived();
   const DERIVED * derived() const;

   void pointer_clear_references();

   void add_reference(DERIVED * & pderived);
   void add_listener(pointer_array < DERIVED > * plistener);
   void remove_listener(pointer_array < DERIVED > * plistener);

   operator DERIVED * ();
   operator const DERIVED * () const;

};

template < class DERIVED >
pointer < DERIVED >::operator DERIVED * ()
{
   return dynamic_cast < DERIVED * > (this);
}

template < class DERIVED >
pointer < DERIVED >::operator const DERIVED * () const
{
   return dynamic_cast < const DERIVED * > (this);
}

template < class DERIVED >
pointer < DERIVED >::pointer()
{
   m_p            = NULL;

}

template < class DERIVED >
pointer < DERIVED >::~pointer()
{
   pointer_clear_references();
}

template < class DERIVED >
void pointer < DERIVED >::pointer_clear_references()
{
   try
   {
      int32_t i;
      for(i = 0; i < m_deriveda.get_size() ; i++)
      {
         *m_deriveda.element_at(i) = NULL;
      }
      comparable_array < pointer_array < DERIVED > *, pointer_array < DERIVED > * >
         listenera = m_listenera;
      for(i = 0; i < listenera.get_size() ; i++)
      {
         try
         {
          listenera.element_at(i)->remove(this);
         }
         catch(...)
         {
         }
         try
         {
            listenera.element_at(i)->OnPointerClear(m_p);
         }
         catch(...)
         {
         }
      }
   }
   catch(...)
   {
      return;
   }
}

template < class DERIVED >
DERIVED * pointer < DERIVED >::derived()
{
   return dynamic_cast < DERIVED * > ( this );
}

template < class DERIVED >
const DERIVED * pointer < DERIVED >::derived() const
{
   return dynamic_cast < const DERIVED * > ( this );
}

template < class DERIVED >
void pointer < DERIVED >::add_reference(DERIVED * & pderived)
{
   if(pderived != NULL
      && ((pointer<DERIVED> *) pderived) == this)
   {
      m_deriveda.add(&pderived);
   }
}

template < class DERIVED >
void pointer < DERIVED >::
add_listener(pointer_array<DERIVED > * plistener)
{
   ASSERT(plistener != NULL);
   if(plistener != NULL)
   {
      m_listenera.add_unique(plistener);
   }
}

template < class DERIVED >
void pointer < DERIVED >::
remove_listener(pointer_array<DERIVED > * plistener)
{
   ASSERT(plistener != NULL);
   if(plistener != NULL)
   {
      m_listenera.remove(plistener);
   }
}








namespace gen
{

   template < class DERIVED >
   static void add_reference(DERIVED * & lpderived)
   {
      pointer<DERIVED> * lppi = dynamic_cast<pointer<DERIVED> *>(lpderived);
      ASSERT(lppi != NULL);
      if(lppi != NULL)
      {
         lppi->add_reference(lpderived);
      }
   }

} // namespace gen








template < class DERIVED >
class pointer_array :
   virtual public comparable_array < pointer < DERIVED > *, pointer < DERIVED > * >
{
public:
   pointer_array();
   pointer_array(const pointer_array & a);
   virtual ~pointer_array();
   virtual void OnPointerClear(DERIVED * p);

   virtual index add(pointer < DERIVED > * p);
   virtual void set_at(int32_t iIndex, pointer < DERIVED > * p);
   virtual count remove(pointer < DERIVED > * p);

   virtual void remove_all();


   virtual DERIVED * derived_at(index idx);
   virtual const DERIVED * derived_at(index idx) const;


   void get_array(raw_array < DERIVED * > & a);
   void get_array(comparable_array < DERIVED * > & a);

   pointer_array & operator = (const pointer_array & a);

};


template < class DERIVED >
void pointer_array < DERIVED >::get_array(raw_array < DERIVED * > & a)
{
   for(int32_t i = 0; i < this->get_count(); i++)
   {
      a.add(derived_at(i));
   }
}

template < class DERIVED >
void pointer_array < DERIVED >::get_array(comparable_array < DERIVED * > & a)
{
   for(int32_t i = 0; i < this->get_count(); i++)
   {
      a.add(derived_at(i));
   }
}

template < class DERIVED >
pointer_array < DERIVED >::
pointer_array()
{
}

template < class DERIVED >
pointer_array < DERIVED >::
pointer_array(const pointer_array & a)
{
   operator = (a);
}

template < class DERIVED >
pointer_array < DERIVED >::
~pointer_array()
{
   remove_all();
}

template < class DERIVED >
void pointer_array < DERIVED >::
remove_all()
{
   for(int32_t i = 0; i < this->get_size(); i++)
   {
      this->element_at(i)->remove_listener(this);
   }
   comparable_array < pointer < DERIVED > *, pointer < DERIVED > * >::remove_all();
}

template < class DERIVED >
void pointer_array < DERIVED >::
OnPointerClear(DERIVED * p)
{
   remove(dynamic_cast < pointer < DERIVED > * > (p));
}

template < class DERIVED >
index pointer_array < DERIVED >::
add(pointer < DERIVED > * p)
{
   ASSERT(p != NULL);
   if(p != NULL)
   {
      if(p->m_p == NULL)
         p->m_p = dynamic_cast < DERIVED * >(p);
      index idx = comparable_array < pointer < DERIVED > *, pointer < DERIVED > * >::add(p);
      p->add_listener(this);
      return idx;
   }
   return -1;
}

template < class DERIVED >
void pointer_array < DERIVED >::
set_at(int32_t iIndex, pointer < DERIVED > * p)
{
   if(p != NULL)
   {
      if(p->m_p == NULL)
         p->m_p = dynamic_cast < DERIVED * >(p);
      p->add_listener(this);
      comparable_array < pointer < DERIVED > *, pointer < DERIVED > * >::set_at(iIndex, p);
   }
}


template < class DERIVED >
count pointer_array < DERIVED >::
remove(pointer < DERIVED > * p)
{
   if(p != NULL)
   {
      count cnt = comparable_array < pointer < DERIVED > *, pointer < DERIVED > * >::remove(p);
      p->remove_listener(this);
      return cnt;
   }
   return 0;
}

template < class DERIVED >
DERIVED * pointer_array < DERIVED >::
derived_at(index idx)
{
   return this->element_at(idx)->derived();
}

template < class DERIVED >
const DERIVED * pointer_array < DERIVED >::
derived_at(index idx) const
{
   return this->element_at(idx)->derived();
}

template < class DERIVED >
pointer_array < DERIVED > &
pointer_array < DERIVED >::
operator = (const pointer_array & a)
{
   if(this != &a)
   {
      set_app(a.get_app());
      for(int32_t i = 0; i < a.get_size(); i++)
      {
         add(a.element_at(i));
      }
   }
   return *this;
}


*/
