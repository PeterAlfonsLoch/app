#pragma once


namespace ca
{


   template < class T >
   class aaa_scoped_ptr
   {
   public:


      T * m_p;


      aaa_scoped_ptr()
      {
         m_p = NULL;
      }

      aaa_scoped_ptr(int_ptr i) 
      {
         operator = ((T *) i);
      }

      aaa_scoped_ptr(T * p) 
      {
         operator = (p);
      }

      ~aaa_scoped_ptr()
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

      aaa_scoped_ptr & operator = (T * p)
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


} // namespace ca



