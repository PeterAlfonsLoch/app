#pragma once

// While raw_pointer just hold the pointer,
// full_pointer deletes the pointer each time 
// the reference is changed or the full_pointer 
// is destroyed.
// And full_pointer requires that the pointer
// is derived from pointer template.
/*template < class T > 
class full_pointer : 
   virtual public ::gen::object,
   virtual public pointer_array < T >
{
public:

   full_pointer();
   full_pointer(::ca::application * papp);
   full_pointer(const full_pointer & holder);
   full_pointer(T * pboject);
   virtual ~full_pointer();

   T * ca2 ()
   {
      return dynamic_cast < T * > (m_pobject);
   }

   T * const ca2 () const
   {
      return dynamic_cast < T * const > (m_pobject);
   }

   operator T *()
   {
      return dynamic_cast < T * > (m_pobject);
   }

   operator T * const() const
   {
      return dynamic_cast < T * const > (m_pobject);
   }

   full_pointer & operator = (T * pobject);

   virtual void set_pointer(T * pobject);

   virtual void OnPointerClear(T * p);

   T * detach();

protected:
   T * m_pobject;
};


template < class T > 
full_pointer < T >::full_pointer()
{
   m_pobject = NULL;
}

template < class T >
full_pointer < T >::full_pointer(::ca::application * papp) :
   ::ca::ca(get_app())
{
   m_pobject = NULL;
}

template < class T >
full_pointer < T >::full_pointer(const full_pointer & holder) :
   ::ca::ca(holder.get_app())
{
   m_pobject = NULL;
   set_pointer(holder.m_pobject);
}

template < class T >
full_pointer < T >::full_pointer(T * pobject) :
   ::ca::ca(pobject != NULL ? pobject->get_app() : NULL)
{
   m_pobject = NULL;
   set_pointer(pobject);
}

template < class T >
full_pointer < T >::~full_pointer()
{
   if(m_pobject != NULL)
   {
      remove(m_pobject);
      delete m_pobject;
   }
}

template < class T >
full_pointer < T > & full_pointer < T >::operator = (T * pobject)
{
   set_pointer(pobject);
   return *this;
}

template < class T >
void full_pointer < T >::set_pointer(T * pobject)
{
   if(pobject != m_pobject)
   {
      if(m_pobject != NULL)
      {
         remove(m_pobject);
         delete m_pobject;
      }
      m_pobject = pobject;
      add(m_pobject);
   }
}

template < class T >
void full_pointer < T >::OnPointerClear(T * p)
{
   if(m_pobject == p)
   {
      m_pobject = NULL;
   }
}

template < class T >
T * full_pointer < T >::detach()
{
   T * p = m_pobject;
   remove(p);
   m_pobject = NULL;
   return p;
}
*/