#pragma once

// While full_pointer deletes the pointer each time 
// the reference is changed or the full_pointer 
// is destroyed, raw_pointer just hold the pointer.

class CLASS_DECL_ca raw_pointer : 
   virtual public ::radix::object
{
public:

   raw_pointer(::ca::application * papp);
   raw_pointer(const raw_pointer & holder);
   raw_pointer(::ca::ca * pboject);

   template < class T >
   T * ca2 ()
   {
      return dynamic_cast < T * > (m_pobject);
   }

   template < class T >
   T * const ca2 () const
   {
      return dynamic_cast < T * const > (m_pobject);
   }

   template < class T >
   operator T *()
   {
      return dynamic_cast < T * > (m_pobject);
   }

   template < class T >
   operator T * const() const
   {
      return dynamic_cast < T * const > (m_pobject);
   }


   ::ca::ca * m_pca;


};

