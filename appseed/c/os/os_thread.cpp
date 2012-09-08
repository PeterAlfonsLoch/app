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


DWORD WINAPI thread_layer::proc(LPVOID lp)
{

   thread_layer * player = (thread_layer *) lp;

   return player->run();

}
