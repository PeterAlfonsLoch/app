#include "framework.h"


#ifndef METROWIN


namespace ca
{

   process_section::process_section()
   {
   }

   process_section::~process_section()
   {
   }

   var process_section::get_output(const char * pszCmdLine)
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

   uint32_t process_section::retry(const char * pszCmdLine, uint32_t dwTimeout, int32_t iShow)
   {

      class on_retry onretry;

      onretry.m_dwTimeout     = dwTimeout;
      onretry.m_dwStartTime   = ::get_tick_count();

      const char * pszEnd = ::null();

      vsstring strBin = consume_param(pszCmdLine, &pszEnd);



#ifdef METROWIN

      throw todo(get_app());

#else

      uint32_t dwExitCode = call_sync(strBin, pszEnd, ::null(), iShow, -1, 484, &process_section::s_on_retry, (uint_ptr) &onretry);

      return dwExitCode;

#endif



   }

   int32_t process_section::s_on_retry(int32_t iTry, uint_ptr dwParam)
   {

      UNREFERENCED_PARAMETER(iTry);

      class on_retry * ponretry = (on_retry *) dwParam;

      return ponretry->m_dwTimeout == 0 || ::get_tick_count() - ponretry->m_dwStartTime < ponretry->m_dwTimeout;

   }

   uint32_t process_section::synch(const char * pszCmdLine, int32_t iShow)
   {
      return retry(pszCmdLine, 0, iShow);
   }

   bool process_section::launch(const char * pszCmdLine, int32_t iShow)
   {

      const char * pszEnd = ::null();

      vsstring strBin = consume_param(pszCmdLine, &pszEnd);

#ifndef METROWIN

      int32_t iOk = call_async(strBin, pszEnd, ::null(), iShow);

      return iOk != 0;

#else

      throw todo(get_app());

#endif

   }

   process_section::process_thread::process_thread(sp(::ca::application) papp) :
      ca(papp),
      thread(papp),
      simple_thread(papp),
      m_evReady(papp)
   {
   }

   int32_t process_section::process_thread::run()
   {
      while(!m_process.has_exited())
      {
         m_strRead += m_process.m_pipe.m_pipeOut.read();
         Sleep(100);
      }
      int32_t iRetry = 50;
      string strRead;
      while(iRetry > 0 && get_run())
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


} // namespace ca



#endif



