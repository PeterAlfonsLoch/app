#pragma once

// While full_pointer deletes the pointer each time 
// the reference is changed or the full_pointer 
// is destroyed, raw_pointer just hold the pointer.

class CLASS_DECL_ca2 raw_pointer : 
   virtual public ::ca2::object
{
public:

   raw_pointer(sp(::ca2::application) papp);
   raw_pointer(const raw_pointer & holder);
   raw_pointer(sp(::ca2::ca2) pboject);

   template < class T >
   T * ca2 ()
   {
      return dynamic_cast < T * > (m_pca);
   }

   template < class T >
   T * const ca2 () const
   {
      return dynamic_cast < T * const > (m_pca);
   }

   template < class T >
   operator T *()
   {
      return dynamic_cast < T * > (m_pca);
   }

   template < class T >
   operator T * const() const
   {
      return dynamic_cast < T * const > (m_pca);
   }


   sp(::ca2::ca2) m_pca;


};

