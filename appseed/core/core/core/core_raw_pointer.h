#pragma once

// While full_pointer deletes the pointer each time
// the reference is changed or the full_pointer
// is destroyed, raw_pointer just hold the pointer.

class CLASS_DECL_CORE raw_pointer :
   virtual public ::object
{
public:

   raw_pointer(::core::applicationsp papp);
   raw_pointer(const raw_pointer & holder);
   raw_pointer(sp(element) pboject);

   template < class T >
   T * core ()
   {
      return dynamic_cast < T * > (m_pca);
   }

   template < class T >
   T * const core () const
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


   sp(element) m_pca;


};

