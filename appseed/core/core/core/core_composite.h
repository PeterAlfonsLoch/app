#pragma once


#undef new


namespace core
{

   template < class TYPE >
   inline TYPE * alloc()
   {
      return new TYPE();
   }

   template < class TYPE >
   inline TYPE * alloc(const TYPE & t)
   {
      return new TYPE(t);
   }

   // strict or simple delete
   template < class TYPE >
   inline void _sdel(TYPE * pt)
   {
      delete pt;
   }

   // strict or simple delete
   template < class TYPE >
   inline void sdel(TYPE * & pt)
   {
      if(pt != NULL)
      {
         TYPE * ptCopy = pt;
         pt = NULL;
         _sdel(ptCopy);
      }
   }

   // delete
   template < class TYPE >
   inline void del(TYPE * & pt)
   {
      if(pt != NULL)
      {
         TYPE * ptCopy = pt;
         pt = NULL;
         ptCopy->delete_this();
      }
   }

   template < class TYPE >
   class composite
   {
   public:
      inline composite();
      inline composite(TYPE & t);

      inline operator TYPE();
      inline operator TYPE &();
      inline operator const TYPE &() const;

//      TYPE & operator = (const TYPE &);
      inline composite<TYPE> & operator = (const TYPE &);
      inline composite<TYPE> & operator = (const composite<TYPE> &);
   protected:
      TYPE * m_pptr;
   public:
      virtual ~composite();
   };


   template < class TYPE >
   composite<TYPE>::composite()
   {
      m_pptr = ::core::alloc<TYPE>();
   }

   template < class TYPE >
   composite<TYPE>::composite(TYPE & t)
   {
      m_pptr = ::core::alloc<TYPE>();
   }

   template < class TYPE >
   composite<TYPE>::~composite()
   {
      del<TYPE>(m_pptr);
      m_pptr = NULL;
   }

   template < class TYPE >
   inline composite<TYPE>::operator TYPE()
   {
      return *m_pptr;
   }

   template < class TYPE >
   inline composite<TYPE>::operator TYPE &()
   {
      return *m_pptr;
   }

   template < class TYPE >
   inline composite<TYPE>::operator const TYPE &() const
   {
      return *m_pptr;
   }
   /*template < class TYPE >
   TYPE & composite<TYPE>::operator = (const TYPE & t)
   {
      *m_pptr = t;
      return *this;
   }*/

   template < class TYPE >
   inline composite<TYPE> & composite<TYPE>::operator = (const composite<TYPE> & t)
   {
      *m_pptr = *t.m_pptr;
      return *this;
   }

   template < class TYPE >
   inline composite<TYPE> & composite<TYPE>::operator = (const TYPE & t)
   {
      *m_pptr  = t;
      return *this;
   }



} // namespace core


#define new AXIS_NEW
