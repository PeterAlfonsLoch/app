#pragma once

// object ptr
// template for using a pointer in more object way,
// safer from allocation point of ::view


template < class T >
class pointer_object
{
public:


   bool  m_bOwn;
   T *   m_ptr;



   pointer_object(T * ptr = NULL)
   {
      m_bOwn = true;
      m_ptr = ptr;
   }

   ~pointer_object()
   {
      if(m_ptr != NULL && m_bOwn)
      {
         delete m_ptr;
      }
   }

   pointer_object & operator = (T * ptr)
   {
      if(m_ptr != ptr)
      {
         if(m_ptr != NULL && m_bOwn)
            delete m_ptr;
         m_bOwn = true;
         m_ptr = ptr;
      }
      return *this;
   }

   pointer_object & operator = (const pointer_object & ptr)
   {
      if(m_ptr != ptr.m_ptr)
      {
         if(m_ptr != NULL && m_bOwn)
            delete m_ptr;
         m_ptr = ptr.m_ptr;
         m_bOwn = ptr.m_bOwn;
         const_cast < pointer_object & > (ptr).m_bOwn = false;
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

   T * detach()
   {
      T * p = m_ptr;
      m_ptr = NULL;
      return p;
   }

};
