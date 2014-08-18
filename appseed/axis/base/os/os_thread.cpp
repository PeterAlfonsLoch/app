#include "framework.h"



thread_layer::thread_layer()
{

   m_iSleepiness     = 49;
   m_iResult         = 0;
   m_hthread         = NULL;
   m_nId             = 0;
   m_bRun            = true;

}


void thread_layer::begin()
{

   m_hthread = create_thread(NULL, 0, &::thread_layer::proc, this, 0, &m_nId);

}



