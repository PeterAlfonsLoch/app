#include "framework.h"

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
      thread.Begin();
      while(!thread.m_process.has_exited())
      {
         Sleep(100);
      }
      thread.m_evReady.wait();
      return thread.m_strRead;
   }

   DWORD process::retry(const char * pszCmdLine, DWORD dwTimeout, int iShow)
   {

      class on_retry onretry;

      onretry.m_dwTimeout     = dwTimeout;
      onretry.m_dwStartTime   = ::GetTickCount();

      const char * pszEnd = NULL;

      vsstring strBin = consume_param(pszCmdLine, &pszEnd);

      DWORD dwExitCode = call_sync(strBin, pszEnd, NULL, iShow, -1, 484, &process::s_on_retry, (dword_ptr) &onretry);

      return dwExitCode;

   }

   int process::s_on_retry(int iTry, dword_ptr dwParam)
   {
      
      UNREFERENCED_PARAMETER(iTry);

      class on_retry * ponretry = (on_retry *) dwParam;

      return ponretry->m_dwTimeout == 0 || ::GetTickCount() - ponretry->m_dwStartTime < ponretry->m_dwTimeout;

   }

   DWORD process::synch(const char * pszCmdLine, int iShow)
   {
      return retry(pszCmdLine, 0, iShow);
   }

   bool process::launch(const char * pszCmdLine, int iShow)
   {

      const char * pszEnd = NULL;
      
      vsstring strBin = consume_param(pszCmdLine, &pszEnd);

      int iOk = call_async(strBin, pszEnd, NULL, iShow);

      return iOk != 0;

   }

   process::process_thread::process_thread(::ca::application * papp) :
      ca(papp),
      thread(papp),
      simple_thread(papp),
      m_evReady(FALSE, TRUE)
   {
   }
   int process::process_thread::run()
   {
      while(!m_process.has_exited())
      {
         m_strRead += m_process.m_pipe.m_pipeOut.read();
         Sleep(100);
      }
      int iRetry = 50;
      string strRead;
      while(iRetry > 0)
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