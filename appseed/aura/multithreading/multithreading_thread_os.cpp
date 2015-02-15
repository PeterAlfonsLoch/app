//#include "framework.h"

//void _on_os_hthread_end();
//
//mutex * hthread::s_pmutex = NULL;
//ptr_array < hthread  > * hthread::s_pptra = NULL;
//thread_pointer < hthread >  t_phthread;
//
//hthread::hthread(uint32_t(* pfn)(void *),void * pv)
//{
//
//   m_pthread = NULL;
//
//   // former hthread (ANOTHER HTHREAD Threading Layer Policy Lawyer... etc... Can you believe it?)
//   {
//
//      m_pevent = new event(NULL,false,true);
//
//      //m_pthread = NULL;
//
//   }
//
//   //thread_layer::thread_layer()
//   {
//
//      m_iSleepiness     = 49;
//      m_iResult         = 0;
//      //m_hthread         = NULL;
//      m_nId             = 0;
//      m_bRun            = true;
//
//   }
//
//
//   m_pfn    = pfn;
//   m_pv     = pv;
//   m_bRun   = true;
//
//
//   synch_lock ml(&*s_pmutex);
//
//   s_pptra->add(this);
//
//}
//
//
//
//hthread::~hthread()
//{
//
//   synch_lock ml(s_pmutex);
//
//   for(index i = s_pptra->get_count() - 1; i >= 0; i--)
//   {
//
//      if(s_pptra->element_at(i) == this)
//      {
//
//         s_pptra->remove_at(i);
//
//      }
//
//   }
//
//}
//
//
//bool hthread::begin(LPSECURITY_ATTRIBUTES lpsa,uint32_t cbStack,uint32_t uiFlags,uint32_t * lpuiId,uint32_t(* pfn)(void *),void * pv)
//{
//
//   if(pfn != NULL)
//   {
//
//      m_pfn = pfn;
//
//      m_pv = pv;
//
//   }
//
//   DWORD uiId = 0;
//
//
//   if(!::CreateThread(lpsa,cbStack,&hthread::thread_proc,(void *)this,uiFlags,&uiId))
//   {
//
//      return false;
//
//
//   }
//
//   try
//   {
//
//      if(lpuiId != NULL)
//      {
//
//         *lpuiId = uiId;
//
//      }
//
//   }
//   catch(...)
//   {
//
//   }
//
//   return true;
//
//}
//
//hthread * hthread::get()
//{
//
//   return t_phthread;
//
//}
//
//void hthread::set(hthread * posthread)
//{
//
//   t_phthread = posthread;
//
//}
//
//bool hthread::get_run()
//{
//
//   return get()->m_bRun;
//
//}
//
//void hthread::stop_all(uint32_t millisMaxWait)
//{
//
//   millisMaxWait = millisMaxWait;
//
//   uint32_t start = get_tick_count();
//
//   while(get_tick_count() - start < millisMaxWait)
//   {
//
//      {
//
//         synch_lock ml(s_pmutex);
//
//         for(int i = 0; i < s_pptra->get_count(); i++)
//         {
//
//            s_pptra->element_at(i)->m_bRun = false;
//
//         }
//
//         if(s_pptra->get_count() <= 0)
//         {
//
//            break;
//
//         }
//
//      }
//
//      Sleep(184);
//
//   }
//
//
//}
//
//#ifdef WINDOWS
//
//DWORD WINAPI hthread::thread_proc(LPVOID lpparameter)
//{
//   return (DWORD)proc(lpparameter);
//}
//#else
//void * WINAPI hthread::thread_proc(LPVOID lpparameter)
//{
//   return (void *)proc(lpparameter);
//}
//#endif
//
//unsigned int hthread::proc(LPVOID lpparameter)
//{
//
//   hthread * phthread = (hthread *)lpparameter;
//
//   uint32_t uiRet;
//
////   player->m_hthread       = ::get_current_thread();
//
//  // player->m_nId           = ::get_current_thread_id();
//
//   try
//   {
//
//      keep_threading_count keepthreadingcount;
//
//      phthread->m_nId           = ::get_current_thread_id();
//
//      t_phthread = phthread;
//
//      uiRet = phthread->run();
//
//      t_phthread = NULL;
//
//   }
//   catch(...)
//   {
//
//      uiRet = 0x66666666;
//
//   }
//
//   phthread->release();
//
//   _on_os_hthread_end();
//
//   return uiRet;
//
//}
//
//
//int32_t hthread::run()
//{
//
//   m_iResult = 0;
//
//   if(m_pfn == NULL)
//   {
//
//      MESSAGE msg;
//
//      while(m_bRun)
//      {
//
//         if(m_bRun && !PeekMessage(&msg,NULL,0,0xffffffffu,TRUE))
//         {
//
//            if(m_bRun && !on_idle())
//            {
//
//               Sleep(m_iSleepiness);
//
//            }
//
//
//            continue;
//
//         }
//
//         if(msg.message == WM_QUIT)
//            break;
//
//         TranslateMessage(&msg);
//
//         DispatchMessage(&msg);
//
//      }
//
//   }
//   else
//   {
//
//      attach_thread_input_to_main_thread(true);
//
//
//
//      try
//      {
//
//         m_iResult = m_pfn(m_pv);
//
//      }
//      catch(...)
//      {
//
//         m_iResult = 0x67676767;
//
//      }
//
//   }
//
//
//   return m_iResult;
//
//}
//
//
//
///*hthread::hthread(uint32_t (* pfn)(void *), void * pv)
//{
//
//m_pfn    = pfn;
//m_pv     = pv;
//
//}*/
//
//
//bool hthread::on_idle()
//{
//
//   return false;
//
//}
//
//
//void hthread::wait_thread(uint32_t dwMillis)
//{
//
//   ::WaitForSingleObjectEx(this,dwMillis,FALSE);
//
//}
//
//
//
//HTHREAD create_thread(LPSECURITY_ATTRIBUTES lpsa,uint32_t cbStack,uint32_t(* pfn)(void *),void * pv,uint32_t uiFlags,uint32_t * lpuiId)
//{
//
//   hthread * phthread;
//
//   try
//   {
//
//      phthread = new hthread(pfn,pv);
//
//   }
//   catch(...)
//   {
//
//      return NULL;
//
//   }
//
//   try
//   {
//
//      if(!phthread->begin())
//      {
//
//         try
//         {
//
//            delete phthread;
//
//         }
//         catch(...)
//         {
//
//         }
//
//         return NULL;
//
//      }
//
//   }
//   catch(...)
//   {
//
//   }
//
//   return phthread;
//
//}
//
//
//
//static HTHREAD g_hMainThread = NULL;
//static UINT g_uiMainThread = -1;
//
//CLASS_DECL_AURA void set_main_thread(HTHREAD hThread)
//{
//
//   g_hMainThread = hThread;
//
//}
//
//CLASS_DECL_AURA void set_main_thread_id(UINT uiThread)
//{
//
//   g_uiMainThread = uiThread;
//
//}
//
//
//CLASS_DECL_AURA HTHREAD get_main_thread()
//{
//   return g_hMainThread;
//
//}
//CLASS_DECL_AURA UINT   get_main_thread_id()
//{
//   return g_uiMainThread;
//}


struct create_thread_data
{
   uint32_t(*m_pfn)(void *);
   void * m_pv;


   create_thread_data(uint32_t(*pfn)(void *), void * pv)
   {
      m_pfn = pfn;
      m_pv = pv;
   }
#ifdef WINDOWS
   static DWORD WINAPI os_thread_proc(void * p)
   {
      return (DWORD)proc(p);
   }
#else
   static void * os_thread_proc(void * p)
   {
      return (void *)(int_ptr) proc(p);
   }
#endif


   static int32_t proc(void * p)
   {
      create_thread_data * pdata = (create_thread_data *)p;

      if(!on_init_thread())
      {

         return -34;

      }

      int32_t iRet = pdata->m_pfn(pdata->m_pv);

      try
      {

         on_term_thread();

      }
      catch(...)
      {
      }


      return iRet;

   }


};


CLASS_DECL_AURA HTHREAD create_thread(LPSECURITY_ATTRIBUTES lpsa,uint_ptr cbStack,uint32_t(*pfn)(void *),void * pv,uint32_t uiFlags,IDTHREAD * puiId)
{

#ifdef WINDOWS

   DWORD dwId = 0;

   HTHREAD  hthread = CreateThread(lpsa,cbStack,&create_thread_data::os_thread_proc,new create_thread_data(pfn,pv),uiFlags,&dwId);

   if(hthread == NULL)
   {
      return NULL;
   }

   try
   {
      if(puiId != NULL)
      {
         *puiId = dwId;
      }
   }
   catch(...)
   {
   }

   return hthread;
#else

   pthread_t thread;

   pthread_attr_t threadAttr;

   pthread_attr_init(&threadAttr);

   if(cbStack > 0)
   {

      pthread_attr_setstacksize(&threadAttr,120 * 1024); // Set the stack size of the thread

   }

   //int iPolicy;

   //sched_param schedparam; // scheduling priority

   //thread_get_os_priority(&iPolicy,&schedparam,nPriority);

   //pthread_attr_setschedpolicy(&threadAttr,iPolicy);

   //pthread_attr_setschedparam(&threadAttr,&schedparam);

   pthread_attr_setdetachstate(&threadAttr,PTHREAD_CREATE_DETACHED); // Set thread to detached state. No need for pthread_join

   pthread_create(&thread,&threadAttr,&create_thread_data::os_thread_proc,(LPVOID)new create_thread_data(pfn,pv)); // Create the thread

   if(puiId != NULL)
   {

    *puiId = thread;

   }

   return thread;


#endif
}




