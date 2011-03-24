#pragma once



#include "ex1/ex1_request_interface.h"



#define SCAST_PTR(tcast, pcasted, pcasting) tcast * pcasted = dynamic_cast < tcast * > (pcasting);
#define SCAST_REF(tcast, rcasted, pcasting) tcast & rcasted = *(dynamic_cast < tcast * > (pcasting));

namespace gen
{

   template < class TYPE >
   bool is_null(TYPE * p)
   {
      return (((int) p) < sizeof(TYPE));
   }

   class CLASS_DECL_ca ptri :
      virtual public ::ex1::request_interface
   {
   public:
      ptri(void);
      ptri(const ptri & o);
      virtual ~ptri(void);

      ptri & operator = (const ptri & o);
   };

   template <class t>
   inline void delptr(t *& p)
   {
      if(p != NULL)
      {
         delete p;
         p = NULL;
      }
   }

   template < class TYPE >
   class scoped_ptr
   {
   public:
      TYPE * m_ptr;
      inline scoped_ptr(INT_PTR i) : m_ptr((TYPE *) i) {};
      inline scoped_ptr(TYPE * ptr) : m_ptr(ptr) {};
      inline TYPE * operator ->() {return m_ptr; };
      inline ~scoped_ptr() {delptr(m_ptr);};
   };

}



