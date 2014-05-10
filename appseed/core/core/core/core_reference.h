#pragma once

template < class DERIVED > class reference;
template < class DERIVED > class reference_array;

// A pointer class add to its derived classes
// the ability to have pointer class features.
// One of the features is to notify the pointer
// object pointer arrays (listeners) when the
// pointer object is deleted.
template < class DERIVED >
class reference :
   public pointer < DERIVED >
{
public:
   int32_t      m_iRefCount;

   reference();
   virtual ~reference();

   virtual void add_ref();
   virtual void release();
   virtual void on_add_ref();
   virtual void on_release();
   virtual void on_final_release();


};




template < class DERIVED >
reference < DERIVED >::reference()
{
   m_iRefCount    = 0;
}

template < class DERIVED >
reference < DERIVED >::~reference()
{
}



template < class DERIVED >
void reference < DERIVED >::
add_ref()
{
   m_iRefCount++;
   on_add_ref();
}

template < class DERIVED >
void reference < DERIVED >::
release()
{
   ASSERT(m_iRefCount > 0);
   if(m_iRefCount > 0)
   {
      m_iRefCount--;
      on_release();
      if(m_iRefCount == 0)
      {
         on_final_release();
         delete this;
      }
   }
}

template < class DERIVED >
void reference < DERIVED >::
on_add_ref()
{
}

template < class DERIVED >
void reference < DERIVED >::
on_release()
{
}

template < class DERIVED >
void reference < DERIVED >::
on_final_release()
{
}




namespace core
{

   template <class DERIVED >
   inline void add_ref(DERIVED * & pref)
   {
      if(pref != NULL)
      {
         pref->add_ref();
      }
   }

   template <class DERIVED >
   inline void release(DERIVED * & pref)
   {
      if(pref != NULL)
      {
         pref->release();
         pref = NULL;
      }
   }
} // namespace core








template < class DERIVED >
class reference_array :
   public pointer_array < DERIVED >
{
public:
   virtual ~reference_array();

   virtual index add(reference < DERIVED > * p);
   virtual void set_at(int32_t iIndex, reference < DERIVED > * p);
   virtual ::count remove(reference < DERIVED > * p);

   virtual void remove_all();

   virtual reference < DERIVED > * reference_at(index idx);
   virtual const reference < DERIVED > * reference_at(index idx) const;

};

template < class DERIVED >
reference_array < DERIVED >::
~reference_array()
{
   remove_all();
}

template < class DERIVED >
void reference_array < DERIVED >::
remove_all()
{
   int32_t i;
   for(i = 0; i < this->get_size(); i++)
   {
      this->element_at(i)->remove_listener(this);
   }
   for(i = 0; i < this->get_size(); i++)
   {
      reference_at(i)->release();
   }
   comparable_array < pointer < DERIVED > *, pointer < DERIVED > * >::remove_all();
}

template < class DERIVED >
index reference_array < DERIVED >::
add(reference < DERIVED > * p)
{
   ASSERT(p != NULL);
   if(p != NULL)
   {
      index idx = pointer_array < DERIVED >::add(p);
      p->add_ref();
      return idx;
   }
   return -1;
}

template < class DERIVED >
void reference_array < DERIVED >::
set_at(int32_t iIndex, reference < DERIVED > * p)
{
   ASSERT(p != NULL);
   if(p != NULL)
   {
      p->add_ref();
      pointer_array < DERIVED >::set_at(iIndex, p);
   }
}


template < class DERIVED >
::count reference_array < DERIVED >::
remove(reference < DERIVED > * p)
{
   ASSERT(p != NULL);
   if(p != NULL)
   {
      ::count cnt = pointer_array < DERIVED >::remove(p);
      p->release();
      return cnt;
   }
   return 0;
}


template < class DERIVED >
reference < DERIVED > *
reference_array < DERIVED >::
reference_at(index idx)
{
   return dynamic_cast < reference < DERIVED > * > (this->element_at(idx));
}

template < class DERIVED >
const reference < DERIVED > *
reference_array < DERIVED >::
reference_at(index idx) const
{
   return dynamic_cast < const reference < DERIVED > * > (this->element_at(idx));
}

