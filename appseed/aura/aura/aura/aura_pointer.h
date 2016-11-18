#pragma once

template < typename T >
class pointer
{
public:

   T * m_p;

   pointer()
   {
      
      m_p = NULL;

   }

   pointer(T * p)
   {

      m_p = p;

   }

   ~pointer()
   {

      destroy();

   }

   void destroy()
   {

      if(m_p != NULL)
      {

         try
         {

            delete m_p;

         }
         catch(...)
         {

         }


         m_p = NULL;

      }

   }

   T * detach()
   {
      
      T * p = m_p;
      
      m_p = NULL;
      
      return p;

   }

   T * release()
   {

      return detach();

   }

   T * get()
   {

      return m_p;

   }

   T * get() const
   {

      return m_p;

   }

   operator T *()
   {
      
      return m_p;

   }

   operator T *() const
   {
      
      return m_p;

   }

   T & operator *()
   {
      return*m_p;
   }

   const T & operator *() const
   {
      return*m_p;
   }

   void reset(T * p)
   {

      if(p == m_p)
         return;

      destroy();

      m_p = p;

   }


   pointer & operator = (T * p)
   {
      
      reset(p);

      return *this;

   }

   T * operator ->()
   {

      return m_p;

   }

   const T * operator ->() const
   {

      return m_p;

   }

};



#define ap(x) ::pointer < x >