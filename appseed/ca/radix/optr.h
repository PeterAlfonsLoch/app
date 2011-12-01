#pragma once

// object ptr
// template for using a pointer in more object way,
// safer from allocation point of ::view


template < class T >
class optr
{
public:


   bool  m_bOwn;
   T *   m_ptr;



   optr(T * ptr = NULL)
   {
      m_bOwn = true;
      m_ptr = ptr;
   }

   ~optr()
   {
      if(m_ptr != NULL && m_bOwn)
      {
         delete m_ptr;
      }
   }

   optr & operator = (T * ptr)
   {
      if(m_ptr != ptr)
      {
         if(m_ptr != NULL && m_bOwn)
            delete m_ptr;
         m_ptr = ptr;
      }
      return *this;
   }

   optr & operator = (const optr & ptr)
   {
      if(m_ptr != ptr.m_ptr)
      {
         if(m_ptr != NULL && m_bOwn)
            delete m_ptr;
         m_ptr = ptr.m_ptr;
         const_cast < optr & > (ptr).m_bOwn = false;
      }
      return *this;
   }

   operator T *()
   {
      return m_ptr;
   }

   operator T *() const
   {
      return m_ptr;
   }

   T * operator ->()
   {
      return m_ptr;
   }

};
