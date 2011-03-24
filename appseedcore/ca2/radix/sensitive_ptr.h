#pragma once

template < class T >
class sensitive_ptr
{
public:
   T * m_p;

   sensitive_ptr()
   {
      m_p = NULL;
   }

   sensitive_ptr(T * p) 
   {
      operator = (p);
   }

   ~sensitive_ptr()
   {
      if(m_p != NULL)
      {
         delete m_p;
      }
   }

   operator T *() const
   {
      return m_p;
   }
   operator T * & ()
   {
      return m_p;
   }
   T * operator ->()
   {
      return m_p;
   }

   sensitive_ptr & operator = (T * p)
   {
      m_p = p;
      return *this;
   }


   T * get()
   {
      T * p = m_p;
      m_p = NULL;
      return p;
   }

};
