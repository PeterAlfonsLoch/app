#include "framework.h"



thread_layer::thread_layer()
{

   m_iSleepiness     = 49;
   m_iResult         = 0;
   m_hthread         = ::null();
   m_nId             = 0;

}


void thread_layer::begin()
{

   m_hthread = create_thread(::null(), 0, &::thread_layer::proc, this, 0, &m_nId);

}



