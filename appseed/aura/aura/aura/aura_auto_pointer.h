#pragma once

template < typename T >
class auto_pointer
{
public:

   T * m_p;

   auto_pointer()
   {
      
      m_p = NULL;

   }

   auto_pointer(T * p)
   {

      m_p = p;

   }

   ~auto_pointer()
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

   const T * get() const
   {

      return m_p;

   }

   operator T *()
   {
      
      return m_p;

   }

   operator const T *() const
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


   auto_pointer & operator = (T * p)
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



