#include "framework.h"
#include "windows.h"



namespace windows
{


   process::process(sp(::aura::application) papp):
      element(papp),
      ::process::process(papp)
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


      if(!::process::process::create_child_process(pszCmdLine,bPiped,pszDir,iCa2Priority))
         return false;

      string szCmdline = pszCmdLine;

      bool bSuccess = false;

      m_si.cb = sizeof(STARTUPINFO);

      if(bPiped)
      {

         pipe * ppipeOut      = m_pipe.m_sppipeOut.cast < pipe >();

         m_si.hStdError       = ppipeOut->m_hWrite;

         m_si.hStdOutput      = ppipeOut->m_hWrite;

         pipe * ppipeIn       = m_pipe.m_sppipeIn.cast < pipe >();

         m_si.hStdInput       = ppipeIn->m_hRead;

         m_si.dwFlags         |= STARTF_USESTDHANDLES;

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


   int32_t process::synch_elevated(const char * pszCmdLine,int iShow,const ::duration & durationTimeOut,bool * pbTimeOut)
   {

      DWORD dwExitCode = 0;

      HANDLE h = NULL;

      ::str::parse parse(pszCmdLine,"= ");

      parse.EnableQuote(true);

      string strPath;

      if(parse.getrestlen())
      {
         parse.getword(strPath);
      }

      string strParam;

      parse.getrest(strParam);

      if(VistaTools::RunElevated(NULL,strPath,strParam,NULL,&h))
      {
         
         dwExitCode = 0;

      }
      else
      {
         return -1;

      }

      bool bTimedOut = true;

      DWORD dwStart = ::get_tick_count();

      DWORD dwTimeOut = durationTimeOut.get_total_milliseconds();

      while(::get_tick_count() - dwStart < dwTimeOut)
      {

         if(!::GetExitCodeProcess(h,&dwExitCode))
            break;

         if(dwExitCode != STILL_ACTIVE)
         {

            bTimedOut = false;

            break;

         }

         Sleep(84);

      }

      ::CloseHandle(h);

      if(pbTimeOut != NULL)
      {

         *pbTimeOut = bTimedOut;

      }

      return dwExitCode;

   }


} // namespace windows











