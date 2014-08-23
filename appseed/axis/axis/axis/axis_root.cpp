#include "framework.h"


root::root()
{

   m_countReference  = 1;
   m_bHeap           = false;
   m_pauraapp        = NULL;

}


root::root(sp(::aura::application) papp)
{

   m_countReference  = 1;
   m_bHeap           = false;
   m_pauraapp        = papp.m_p;

}


root::~root()
{
}


int64_t root::add_ref()
{
   
#ifdef WINDOWS
   return InterlockedIncrement64(&m_countReference);
#else
   return __sync_add_and_fetch(&m_countReference, 1);
#endif

}

int64_t root::dec_ref()
{
#ifdef WINDOWS
   int64_t i = InterlockedDecrement64(&m_countReference);
#else
   int64_t i =  __sync_sub_and_fetch(&m_countReference, 1);
#endif
   return i;
}

int64_t root::release()
{
   int64_t i = dec_ref();
   if(i == 0)
   {
      delete_this();
   }
   return i;
}



void root::delete_this()
{

   // quite verisimple default implementation
   delete this;

}


