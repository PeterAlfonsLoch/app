#include "framework_cpp.h"


namespace ca
{
   
   ca::ca()
   {

      m_countReference  = 1;
      m_bHeap           = false;

   }

   ca::~ca()
   {
   }


   int64_t ca::add_ref()
   {
         #ifdef WINDOWS
      return InterlockedIncrement64(&m_countReference);
      #else
      return __sync_add_and_fetch(&m_countReference, 1);
      #endif
   }

   int64_t ca::dec_ref()
   {
      #ifdef WINDOWS
      int64_t i = InterlockedDecrement64(&m_countReference);
      #else
      int64_t i =  __sync_sub_and_fetch(&m_countReference, 1);
      #endif
      return i;
   }

   int64_t ca::release()
   {
      int64_t i = dec_ref();
      if(i == 0)
      {
         delete_this();
      }
      return i;
   }



  void ca::delete_this()
  {

     // quite verisimple default implementation
     delete this;

  }


  
} // namespace ca



