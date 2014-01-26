#pragma once


template < class T >
class smart_pointer_query :
   virtual object
{
public:


   smart_pointer < T > * m_psp;

   T * m_p;

#if defined(MOVE_SEMANTICS)

   smart_pointer_query(smart_pointer_query && q)
   {

      m_psp    = q.m_psp;

      m_p      = q.m_p;

      q.m_psp  = NULL;

   }

   smart_pointer_query & operator = (smart_pointer_query && q)
   {

      m_psp    = q.m_psp;

      m_p      = q.m_p;

      q.m_psp  = NULL;

   }

   smart_pointer_query(smart_pointer < T > & sp)
   {

      m_psp    = &sp;

      m_p      = NULL;

   }

#else

   smart_pointer_query(smart_pointer < T > & sp)
   {

      m_psp    = &sp;

      m_p      = NULL;

   }

#endif


   virtual ~smart_pointer_query()
   {

      if(m_psp != NULL)
      {

         (*m_psp) = m_p;

      }

   }

   operator T * &()
   {

      return m_p;

   }

};





#if defined(MOVE_SEMANTICS)

template < class T >
inline smart_pointer_query < T > ca_smart_pointer_query(smart_pointer < T > & sp)
{
   return smart_pointer_query < T > (sp);
}

#else

template < class T >
inline smart_pointer_query < T > ca_smart_pointer_query(smart_pointer < T > & sp)
{
   return sp;
}

#endif

#define spquery(sp) ::ca_smart_pointer_query(sp)