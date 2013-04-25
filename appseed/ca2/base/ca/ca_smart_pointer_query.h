#pragma once


namespace ca
{


   template < class T >
   class smart_pointer_query :
      virtual ::ca::object
   {
   public:


      ::c::smart_pointer < T > * m_psp;

      T * m_p;

      smart_pointer_query(smart_pointer_query && q)
      {

         m_psp    = q.m_psp;

         m_p      = q.m_p;

         q.m_psp  = ::null();

      }

      smart_pointer_query & operator = (smart_pointer_query && q)
      {

         m_psp    = q.m_psp;

         m_p      = q.m_p;

         q.m_psp  = ::null();

      }


      smart_pointer_query(::c::smart_pointer < T > & sp)
      {

         m_psp    = &sp;

         m_p      = ::null();

      }

      virtual ~smart_pointer_query()
      {

         if(m_psp != ::null())
         {

            (*m_psp) = m_p;

         }

      }

      operator T * &()
      {

         return m_p;

      }

   };


} // namespace ca





template < class T >
inline ::ca::smart_pointer_query < T > ca_smart_pointer_query(::c::smart_pointer < T > & sp)
{
   return ::ca::smart_pointer_query < T > (sp);
}


#define spquery(smart_pointer) ::ca_smart_pointer_query(smart_pointer)