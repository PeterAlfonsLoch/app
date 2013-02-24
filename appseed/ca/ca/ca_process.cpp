#include "framework.h"


#ifndef METROWIN


namespace ca2
{

   process::process()
   {
   }

   process::~process()
   {
   }

   var process::get_output(const char * pszCmdLine)
   {
      process_thread thread(get_app());
      if(!thread.m_process.create_child_process(pszCmdLine, true))
         return false;
      thread.begin();
      while(!thread.m_process.has_exited())
      {
         Sleep(100);
      }
      thread.m_evReady.wait();
      return thread.m_strRead;
   }

   uint32_t process::retry(const char * pszCmdLine, uint32_t dwTimeout, int32_t iShow)
   {

      class on_retry onretry;

      onretry.m_dwTimeout     = dwTimeout;
      onretry.m_dwStartTime   = ::get_tick_count();

      const char * pszEnd = NULL;

      vsstring strBin = consume_param(pszCmdLine, &pszEnd);



#ifdef METROWIN

      throw todo(get_app());

#else

      uint32_t dwExitCode = call_sync(strBin, pszEnd, NULL, iShow, -1, 484, &process::s_on_retry, (uint_ptr) &onretry);

      return dwExitCode;

#endif

      

   }

   int32_t process::s_on_retry(int32_t iTry, uint_ptr dwParam)
   {
      
      UNREFERENCED_PARAMETER(iTry);

      class on_retry * ponretry = (on_retry *) dwParam;

      return ponretry->m_dwTimeout == 0 || ::get_tick_count() - ponretry->m_dwStartTime < ponretry->m_dwTimeout;

   }

   uint32_t process::synch(const char * pszCmdLine, int32_t iShow)
   {
      return retry(pszCmdLine, 0, iShow);
   }

   bool process::launch(const char * pszCmdLine, int32_t iShow)
   {

      const char * pszEnd = NULL;
      
      vsstring strBin = consume_param(pszCmdLine, &pszEnd);

#ifndef METROWIN

      int32_t iOk = call_async(strBin, pszEnd, NULL, iShow);

      return iOk != 0;

#else

      throw todo(get_app());

#endif

   }

   process::process_thread::process_thread(::ca::application * papp) :
      ca(papp),
      thread(papp),
      simple_thread(papp),
      m_evReady(papp)
   {
   }

   int32_t process::process_thread::run()
   {
      while(!m_process.has_exited())
      {
         m_strRead += m_process.m_pipe.m_pipeOut.read();
         Sleep(100);
      }
      int32_t iRetry = 50;
      string strRead;
      while(iRetry > 0 && m_bRun)
      {
         strRead = m_process.m_pipe.m_pipeOut.read();
         if(strRead.is_empty())
         {
            iRetry--;
         }
         else
         {
            m_strRead += strRead;
            strRead.Empty();
         }
         Sleep(100);
      }
      m_evReady.SetEvent();
      return 0;
   }


} // namespace ca2



#endif


