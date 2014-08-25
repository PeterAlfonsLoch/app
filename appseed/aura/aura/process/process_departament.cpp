#include "framework.h"


namespace process
{


   departament::departament(sp(::aura::application) papp):
      element(papp),
      ::aura::departament(papp)
   {

   }


   departament::~departament()
   {

   }


   var departament::get_output(const char * pszCmdLine)
   {

      string strRead;

      manual_reset_event evReady(get_app());

      evReady.ResetEvent();

      process_thread * pthread = new process_thread(get_app(),&strRead,&evReady);

      pthread->m_bAutoDelete = true;

      if(!pthread->m_spprocess.create_child_process(pszCmdLine,true))
         return false;

      pthread->begin();

      evReady.wait();

      return strRead;

   }


   uint32_t departament::retry(const char * pszCmdLine,uint32_t dwTimeout,int32_t iShow)
   {

      class on_retry onretry;

      onretry.m_dwTimeout     = dwTimeout;
      onretry.m_dwStartTime   = ::get_tick_count();

      const char * pszEnd = NULL;

      string strBin = consume_param(pszCmdLine,&pszEnd);



#ifdef METROWIN

      throw todo(get_app());

#else

      uint32_t dwExitCode = call_sync(strBin,pszEnd,NULL,iShow,-1,484,&departament::s_on_retry,(uint_ptr)&onretry);

      return dwExitCode;

#endif



   }

   int32_t departament::s_on_retry(int32_t iTry,uint_ptr dwParam)
   {

      UNREFERENCED_PARAMETER(iTry);

      class on_retry * ponretry = (on_retry *)dwParam;

      return ponretry->m_dwTimeout == 0 || ::get_tick_count() - ponretry->m_dwStartTime < ponretry->m_dwTimeout;

   }

   uint32_t departament::synch(const char * pszCmdLine,int32_t iShow)
   {
      return retry(pszCmdLine,0,iShow);
   }

   bool departament::launch(const char * pszCmdLine,int32_t iShow)
   {

      const char * pszEnd = NULL;

      string strBin = consume_param(pszCmdLine,&pszEnd);

#ifndef METROWIN

      int32_t iOk = call_async(strBin,pszEnd,NULL,iShow);

      return iOk != 0;

#else

      throw todo(get_app());

#endif

   }

   departament::process_thread::process_thread(sp(::aura::application) papp,string * pstrRead,manual_reset_event * pevReady):
      element(papp),
      thread(papp),
      simple_thread(papp),
      m_spprocess(allocer()),
      m_pstrRead(pstrRead),
      m_pevReady(pevReady)
   {
   }


   int32_t departament::process_thread::run()
   {

      string strRead;

      while(!m_spprocess->has_exited())
      {

         strRead = m_spprocess->m_pipe.m_pipeOut.read();

         if(m_pstrRead != NULL)
         {

            *m_pstrRead += strRead;

         }

         Sleep(100);

      }

      while(get_run())
      {
         strRead = m_process.m_pipe.m_pipeOut.read();
         if(strRead.is_empty())
         {
            break;
         }
         else
         {
            if(m_pstrRead != NULL)
            {
               *m_pstrRead += strRead;
            }
         }
      }
      if(m_pevReady != NULL)
      {
         m_pevReady->SetEvent();
      }
      return 0;
   }


} // namespace process




