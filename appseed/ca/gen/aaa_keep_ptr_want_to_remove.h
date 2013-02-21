#pragma once

template < class T >
class keep_ptr
{
public:
   T ** m_pp;
   keep_ptr(T ** pp)
   {
      m_pp = pp;
   }
   ~keep_ptr()
   {
      if(m_pp != NULL && *m_pp != NULL)
         delete *m_pp;
   }
   T * get()
   {
      T * p = *m_pp;
      m_pp = NULL;
      return p;
   }
};

