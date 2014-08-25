#include "framework.h"


namespace windows
{


   process::process(sp():
      
      m_pipe(true)
   {

      memset(&m_pi,0,sizeof(PROCESS_INFORMATION));

      memset(&m_si,0,sizeof(STARTUPINFO));

   }


   process::~process()
   {

      if(m_pi.hProcess != INVALID_HANDLE_VALUE && m_pi.hProcess != NULL)
      {

         CloseHandle(m_pi.hProcess);

      }

      if(m_pi.hThread != INVALID_HANDLE_VALUE && m_pi.hThread != NULL)
      {

         CloseHandle(m_pi.hThread);

      }

   }


   bool process::create_child_process(const char * pszCmdLine,bool bPiped,const char * pszDir,int32_t iCa2Priority)
   {


      if(!::aura::process::create_child_process(pszCmdLine,bPiped,pszDir,iCa2Priority))
         return false;

      string szCmdline = pszCmdLine;

      bool bSuccess = false;

      // set up members of the STARTUPINFO structure.
      // This structure specifies the STDIN and STDOUT handles for redirection.

      m_si.cb = sizeof(STARTUPINFO);
      if(bPiped)
      {
         m_si.hStdError = m_pipe.m_pipeOut.m_hWrite;
         m_si.hStdOutput = m_pipe.m_pipeOut.m_hWrite;
         m_si.hStdInput = m_pipe.m_pipeIn.m_hRead;
         m_si.dwFlags |= STARTF_USESTDHANDLES;

      }
      /* STARTUPINFO si;
      PROCESS_INFORMATION pi;
      memset(&si, 0, sizeof(si));
      memset(&pi, 0, sizeof(pi));
      si.cb = sizeof(si);
      si.dwFlags = STARTF_USESHOWWINDOW;
      si.wShowWindow = SW_HIDE; */
      //         if(!::CreateProcess(NULL, (LPTSTR) (const char *) System.dir().appdata("production\\build.bat"), NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi))
      m_si.dwFlags |= STARTF_USESHOWWINDOW;
      m_si.wShowWindow = SW_HIDE;


      DWORD dwPriorityClass = ::get_os_priority_class(iCa2Priority);


      // create the child process.


      if(::str::ends_ci(szCmdline,".bat"))
      {
         string strCmd;

         strCmd = "";
         strCmd += szCmdline;
         strCmd += "";

         wstring wstr = strCmd;

         bSuccess = CreateProcessW(NULL,
            (wchar_t *)(const wchar_t *)wstr,     // command line
            NULL,          // process security attributes
            NULL,          // primary thread security attributes
            TRUE,          // handles are inherited
            CREATE_NEW_CONSOLE | CREATE_UNICODE_ENVIRONMENT | dwPriorityClass,             // creation flags
            NULL,          // use parent's environment
            wstring(pszDir),
            &m_si,  // STARTUPINFO pointer
            &m_pi) != FALSE;  // receives PROCESS_INFORMATION
      }
      else
      {
         bSuccess = CreateProcessW(NULL,
            (wchar_t *)(const wchar_t *)wstring(szCmdline),     // command line
            NULL,          // process security attributes
            NULL,          // primary thread security attributes
            TRUE,          // handles are inherited
            CREATE_NEW_CONSOLE | dwPriorityClass,             // creation flags
            NULL,          // use parent's environment
            wstring(pszDir),
            &m_si,  // STARTUPINFO pointer
            &m_pi) != FALSE;  // receives PROCESS_INFORMATION
      }
      // If an error occurs, exit the application.
      if(! bSuccess)
         return false;
      else
      {
         // close handles to the child process and its primary thread.
         // Some applications might keep these handles to monitor the status
         // of the child process, for example.

         //CloseHandle(m_pi.hProcess);
         //CloseHandle(m_pi.hThread);
      }

      return true;

   }


   bool process::write(const char * psz)
   {
      return m_pipe.m_pipeIn.write(psz);
   }

   string process::read(bool bUntilExit)
   {
      UNREFERENCED_PARAMETER(bUntilExit);
      return m_pipe.m_pipeOut.read();
   }

   uint32_t process::wait_until_exit(int32_t iWaitMax)
   {
      uint32_t dwExitCode = 0;
      uint32_t dwStartTime = ::get_tick_count();
      int32_t i = 1;
      while(true)
      {
         if(has_exited(&dwExitCode))
            break;
         if(iWaitMax >= 0 && get_tick_count() > dwStartTime + iWaitMax)
            break;
         Sleep(100);
         i++;
      }
      return dwExitCode;
   }

   bool process::has_exited(uint32_t * puiExitCode)
   {


      DWORD dwExitCode;
      bool bExited;


      if(!GetExitCodeProcess(m_pi.hProcess,&dwExitCode))
      {

         bExited = true;

      }
      else
      {

         if(dwExitCode == STILL_ACTIVE)
         {

            bExited = false;

         }
         else
         {

            bExited = true;

         }

      }

      if(puiExitCode != NULL)
      {

         *puiExitCode = dwExitCode;
      }

      return bExited;

   }


} // namespace windows











