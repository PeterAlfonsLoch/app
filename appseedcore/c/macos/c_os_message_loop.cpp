#include "StdAfx.h"


class sys_message_queue
{
public:


   simple_event                     m_event;
   simple_mutex                     m_mutex;
   simple_array < MSG * >           m_msgptra;


   BOOL GetMessage(MSG * pmsg);


};

class sys_thread
{
public:


   pthread_t                        m_pthread;
   sys_message_queue                m_messagequeue;


   sys_thread(pthread_t pthread);


   BOOL GetMessage(MSG * pmsg);


};

class sys_thread_pool
{
public:


   simple_mutex                     m_mutex;
   simple_array < sys_thread * >    m_threadptra;


   sys_thread * get_current();
   sys_thread * get(pthread_t pthread);


};

static sys_thread_pool * g_psysthreadpool;

BOOL GetMessage(MSG * pmsg)
{

   return TRUE;
}

BOOL TranslateMessage(MSG * pmsg)
{

   return TRUE;
}

BOOL DispatchMessage(MSG * pmsg)
{

   return TRUE;
}


void _c_simple_message_loop()
{


   MSG msg;
	while(GetMessage(&msg))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}



}

BOOL sys_message_queue::GetMessage(MSG * pmsg)
{
   mutex_lock lockMutex(&m_mutex, false);
   event_wait waitEvent(&m_event, false);
   while(true)
   {
      lockMutex.lock();
      if(m_msgptra.get_count() <= 0)
      {
         lockMutex.unlock();
         waitEvent.wait();
      }
      else
      {
         *pmsg = *m_msgptra[0];
         m_msgptra.remove_at(0);
         if(pmsg->message == 0xffff)
         {
            return FALSE;
         }
         else
         {
            return TRUE;
         }

      }
   }
}


sys_thread::sys_thread(pthread_t pthread) :
   m_pthread(pthread)
{
}

BOOL sys_thread::GetMessage(MSG * pmsg)
{
      return m_messagequeue.GetMessage(pmsg);
}







sys_thread * sys_thread_pool::get_current()
{
   return get(pthread_self());
}

sys_thread * sys_thread_pool::get(pthread_t pthread)
{


   mutex_lock lockMutex(&m_mutex, false);


   for(int i = 0; i < m_threadptra.get_count(); i++)
   {
      if(m_threadptra[i]->m_pthread == pthread)
         return m_threadptra[i];

   }

   m_threadptra.add(new sys_thread(pthread));

   return m_threadptra[m_threadptra.get_count() - 1];
}
