#pragma once


namespace base
{


   template < class BASE >
   void gudo < BASE > ::gudo_get()
   {

      Application.gudo_get(m_strKey,*this);

   }


   template < class BASE >
   void gudo < BASE > ::gudo_set()
   {

      Application.gudo_set(m_strKey,*this);

   }


} // namespace base







