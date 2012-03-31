#pragma once


namespace gen
{


   template < class T >
   class scoped_ptr
   {
   public:


      T * m_p;


      scoped_ptr()
      {
         m_p = NULL;
      }

      scoped_ptr(INT_PTR i) 
      {
         operator = ((T *) i);
      }

      scoped_ptr(T * p) 
      {
         operator = (p);
      }

      ~scoped_ptr()
      {
         if(m_p != NULL)
         {
            delete m_p;
         }
      }

      operator const T * () const
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

      scoped_ptr & operator = (T * p)
      {
         m_p = p;
         return *this;
      }


      T * detach()
      {
         T * p = m_p;
         m_p = NULL;
         return p;
      }

      T * get_p()
      {
         return m_p;
      }


   };


} // namespace gen



