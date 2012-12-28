#include "framework.h"


#ifndef METROWIN


#ifdef LINUX
#include <sys/wait.h>
#endif


namespace gen
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

   DWORD process::wait_until_exit(int32_t iWaitMax)
   {
      DWORD dwExitCode = 0;
      DWORD dwStartTime = ::get_tick_count();
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

   bool process::has_exited(DWORD * pdwExitCode)
   {
      DWORD dwExitCode;
      if(pdwExitCode == NULL)
         pdwExitCode = &dwExitCode;

#ifdef WINDOWSEX

      if(!GetExitCodeProcess(m_pi.hProcess, pdwExitCode))
         return true;
      if(*pdwExitCode == STILL_ACTIVE)
         return false;
      return true;

#elif defined(METROWIN)

      throw todo(::ca::get_thread_app());

#else

      int32_t wpid = waitpid(m_iPid, (int32_t *) pdwExitCode, WNOHANG
              #ifdef WCONTINUED
              | WCONTINUED
              #endif
              );

      if(wpid == -1)
      {
         // error has occurred / process unavailable
         return true;
      }

      if(WIFEXITED(*pdwExitCode))
      {
         *pdwExitCode = WEXITSTATUS(*pdwExitCode);
         return true;
      }
      else if(WIFSIGNALED(*pdwExitCode))
      {
         *pdwExitCode = WTERMSIG(*pdwExitCode);
         return true;
      }
      else if(WIFSTOPPED(*pdwExitCode))
      {
         *pdwExitCode = WSTOPSIG(*pdwExitCode);
         return true;
      }
#ifdef WIFCONTINUED
      else if(WIFCONTINUED(*pdwExitCode))
      {
         return false;
      }
#endif

      return false;

#endif

   }


} // namespace gen



#endif


