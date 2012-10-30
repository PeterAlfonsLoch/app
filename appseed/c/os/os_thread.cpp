#include "framework.h"



thread_layer::thread_layer()
{

   m_iSleepiness     = 49;
   m_iResult         = 0;

}


void thread_layer::begin()
{

   start_thread(&::thread_layer::proc, this);

}


