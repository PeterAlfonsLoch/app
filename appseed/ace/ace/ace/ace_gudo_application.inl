#pragma once


namespace ace
{


   template < class AXIS >
   void gudo < AXIS > ::gudo_get()
   {

      Application.gudo_get(m_strKey,*this);

   }


   template < class AXIS >
   void gudo < AXIS > ::gudo_set()
   {

      Application.gudo_set(m_strKey,*this);

   }


} // namespace ace







