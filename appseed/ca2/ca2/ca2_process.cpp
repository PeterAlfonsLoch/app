#include "StdAfx.h"

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
      LPSTR lpCommand = _strdup(pszCmdLine);

      STARTUPINFO si;
      memset(&si, 0, sizeof(si));
      si.cb = sizeof(si);
      if(iShow >= 0)
      {
         si.dwFlags = STARTF_USESHOWWINDOW;
         si.wShowWindow = (WORD) iShow;
      }
      PROCESS_INFORMATION pi;

      memset(&pi, 0, sizeof(pi));
         
      if(!::CreateProcess(NULL, lpCommand, 
                         NULL, NULL, FALSE, 0, NULL, NULL,
                         &si, &pi))
      {
         free(lpCommand);
         throw misc_exception("failed to create process");
      }
      DWORD dwStartTime = ::GetTickCount();
      //DWORD dwStartError = ::GetLastError();
      free(lpCommand);
      DWORD dwExitCode;
      int iRetry = 0;
      while(true)
      {
         if(!GetExitCodeProcess(pi.hProcess, &dwExitCode))
            break;
         if(dwExitCode != STILL_ACTIVE)
            break;
         iRetry++;
         Sleep(484);
         if(dwTimeout > 0 && ::GetTickCount() - dwStartTime > dwTimeout)
         {
            break;
         }
      }
      ::CloseHandle(pi.hProcess);
      ::CloseHandle(pi.hThread);
      return dwExitCode;
   }

   DWORD process::synch(const char * pszCmdLine, int iShow)
   {
      return retry(pszCmdLine, 0, iShow);
   }

   bool process::launch(const char * pszCmdLine, int iShow)
   {
      UNREFERENCED_PARAMETER(iShow);
      try
      {
      }
      catch(const char *)
      {
      }
      LPSTR lpCommand = _strdup(pszCmdLine);

      STARTUPINFO si;
      memset(&si, 0, sizeof(si));
      si.cb = sizeof(si);
      si.dwFlags = STARTF_USESHOWWINDOW;
      si.wShowWindow = SW_HIDE;
      PROCESS_INFORMATION pi;

      memset(&pi, 0, sizeof(pi));
         
      if(!::CreateProcess(NULL, lpCommand, 
                         NULL, NULL, FALSE, 0, NULL, NULL,
                         &si, &pi))
      {
         free(lpCommand);
         return false;
      }
      free(lpCommand);
      ::CloseHandle(pi.hProcess);
      ::CloseHandle(pi.hThread);
      return true;
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