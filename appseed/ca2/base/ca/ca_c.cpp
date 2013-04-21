#include "framework.h"


namespace ca
{
   
   c::c()
   {

      m_countReference = 1;

   }

   c::~c()
   {
   }


   int64_t c::add_ref()
   {
         #ifdef WINDOWS
      return InterlockedIncrement64(&m_countReference);
      #else
      return __sync_add_and_fetch(&m_countReference, 1);
      #endif
   }


   int64_t c::release()
   {
         #ifdef WINDOWS
      int64_t i = InterlockedDecrement64(&m_countReference);
      #else
      int64_t i =  __sync_sub_and_fetch(&m_countReference, 1);
      #endif
      if(i == 0)
      {
         delete_this();
      }
      return i;
   }



  void c::delete_this()
  {

     // quite verisimple default implementation
     delete this;

  }


  
} // namespace ca



