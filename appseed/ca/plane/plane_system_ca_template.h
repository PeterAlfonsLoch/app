#pragma once


namespace ca
{
 

   template < class T >
   void smart_pointer <T>::create(::ca::application * papp)
   {
      if(get_app() == NULL)
         set_app(papp);
      if(m_p != NULL)
         gen::release(m_p);
      m_p = dynamic_cast < T * > (Sys(papp).alloc(papp, Sys(papp->m_psystem).template type_info < T > ()));
   }

   template < class T >
   T * smart_pointer <T>::clone() const   
   {
      if(m_p == NULL)
         return NULL;
      if(m_p->get_app() == NULL)
         return NULL;
      return dynamic_cast < T * > (Sys(m_p->m_papp).clone(m_p));
   }

   template < class T >
   void smart_pointer <T>::destroy()
   {
      if(m_p != NULL)
      {
         m_p->delete_this();
         m_p = NULL;
      }
   }


} // namespace ca


