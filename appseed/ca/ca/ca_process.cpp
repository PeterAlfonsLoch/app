#include "framework.h"


#ifndef METROWIN


namespace ca
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


} // namespace ca



#endif




#include "framework.h"


#ifndef METROWIN


#ifdef LINUX
#include <sys/wait.h>
#endif


namespace ca
{

   process::process() :
      m_pipe(true)
   {

      m_bPiped = false;

#ifdef WINDOWSEX

      memset(&m_pi, 0, sizeof(PROCESS_INFORMATION));

      memset(&m_si, 0, sizeof(STARTUPINFO));

#endif

   }

   process::~process()
   {

#ifdef WINDOWSEX

      if(m_pi.hProcess != INVALID_HANDLE_VALUE && m_pi.hProcess != NULL)
      {

         CloseHandle(m_pi.hProcess);

      }

      if(m_pi.hThread != INVALID_HANDLE_VALUE && m_pi.hThread != NULL)
      {

         CloseHandle(m_pi.hThread);

      }

#endif

   }


   bool process::create_child_process(const char * pszCmdLine, bool bPiped, const char * pszDir)
   {
      string szCmdline = pszCmdLine;



// Set up members of the PROCESS_INFORMATION structure.



      if(bPiped)
      {
         if(!m_pipe.create(false))
            return false;
      }

      m_bPiped = bPiped;

#ifdef WINDOWSEX


      bool bSuccess = FALSE;


// Set up members of the STARTUPINFO structure.
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


// create the child process.

      bSuccess = CreateProcess(NULL,
         (char *)(const char *) szCmdline,     // command line
         NULL,          // process security attributes
         NULL,          // primary thread security attributes
         TRUE,          // handles are inherited
         CREATE_NEW_CONSOLE,             // creation flags
         NULL,          // use parent's environment
         pszDir,
         &m_si,  // STARTUPINFO pointer
         &m_pi) != FALSE;  // receives PROCESS_INFORMATION

      // If an error occurs, exit the application.
      if ( ! bSuccess )
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

#elif defined(METROWIN)

      throw todo(::ca::get_thread_app());

#else
   char *   exec_path_name;
   char *	cmd_line;

   cmd_line = (char *) ca2_alloc(strlen(pszCmdLine ) + 1 );

   if(cmd_line == NULL)
            return 0;

   strcpy_dup(cmd_line, pszCmdLine);

   if((m_iPid = fork()) == 0)
   {

      if(bPiped)
      {
         dup2(m_pipe.m_pipeOut.m_fd[1] , STDOUT_FILENO);
         dup2(m_pipe.m_pipeOut.m_fd[1] , STDERR_FILENO);
         dup2(m_pipe.m_pipeIn.m_fd[0]  , STDIN_FILENO);
      }


      // child
      char		*pArg, *pPtr;
      char		*argv[1024 + 1];
      int32_t		 argc;
      if( ( pArg = strrchr_dup( exec_path_name, '/' ) ) != NULL )
         pArg++;
      else
         pArg = exec_path_name;
      argv[0] = pArg;
      argc = 1;

      if( cmd_line != NULL && *cmd_line != '\0' )
      {
         pArg = strtok_r_dup(cmd_line, " ", &pPtr);
         while( pArg != NULL )
         {
            argv[argc] = pArg;
            argc++;
            if( argc >= 1024 )
               break;
            pArg = strtok_r_dup(NULL, " ", &pPtr);
         }
      }
      argv[argc] = NULL;

      execv(exec_path_name, argv);
      free(cmd_line);
      exit( -1 );
   }
   else if(m_iPid == -1)
   {
      // in parent, but error
      m_iPid = 0;
      free(cmd_line);
      return 0;
   }
   // in parent, success
   return 1;

#endif
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

#ifdef WINDOWSEX

      DWORD dwExitCode;

      bool bExited;

      if(!GetExitCodeProcess(m_pi.hProcess, &dwExitCode))
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

#elif defined(METROWIN)

      throw todo(::ca::get_thread_app());

#else

      int32_t wpid = waitpid(m_iPid, (int32_t *) puiExitCode, WNOHANG
              #ifdef WCONTINUED
              | WCONTINUED
              #endif
              );

      if(wpid == -1)
      {
         // error has occurred / process unavailable
         return true;
      }

      if(WIFEXITED(*puiExitCode))
      {
         *puiExitCode = WEXITSTATUS(*puiExitCode);
         return true;
      }
      else if(WIFSIGNALED(*puiExitCode))
      {
         *puiExitCode = WTERMSIG(*puiExitCode);
         return true;
      }
      else if(WIFSTOPPED(*puiExitCode))
      {
         *puiExitCode = WSTOPSIG(*puiExitCode);
         return true;
      }
#ifdef WIFCONTINUED
      else if(WIFCONTINUED(*puiExitCode))
      {
         return false;
      }
#endif

      return false;

#endif

   }


} // namespace ca



#endif


