#include "framework.h"


#ifndef METROWIN

#if defined(ANDROID)
#include <sys/wait.h>
#include <unistd.h>
#elif defined(LINUX)
#include <sys/wait.h>
#include <unistd.h>
#include <spawn.h>
extern char **environ;
#elif defined(APPLEOS)
#include <sys/wait.h>
#include <unistd.h>
#include <spawn.h>
extern char * const * environ;
#endif




namespace core
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


   bool process::create_child_process(const char * pszCmdLine, bool bPiped, const char * pszDir, int32_t iCa2Priority)
   {


      string szCmdline = pszCmdLine;

      // set up members of the PROCESS_INFORMATION structure.

      if(bPiped)
      {
         if(!m_pipe.create(false))
            return false;
      }

      m_bPiped = bPiped;

#ifdef WINDOWSEX


      bool bSuccess = FALSE;


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


      if(::str::ends_ci(szCmdline, ".bat"))
      {
         string strCmd;

         strCmd = "";
         strCmd += szCmdline;
         strCmd += "";

         wstring wstr = strCmd;

      bSuccess = CreateProcessW(NULL,
         (wchar_t *)(const wchar_t *) wstr,     // command line
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
         (wchar_t *)(const wchar_t *) wstring(szCmdline),     // command line
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

      throw todo(get_thread_app());

#elif defined(ANDROID)

      throw todo(get_thread_app());

#else

      char * argv[] = {(char *) pszCmdLine, 0};

      posix_spawnattr_t attr;

      posix_spawnattr_init(&attr);

#ifdef LINUX

      if(iCa2Priority != (int32_t) ::aura::scheduling_priority_none)
      {

         int32_t iPolicy = SCHED_OTHER;

         sched_param schedparam;

         schedparam.sched_priority = 0;

         process_get_os_priority(&iPolicy, &schedparam, iCa2Priority);

         posix_spawnattr_setschedpolicy(&attr, iPolicy);

         posix_spawnattr_setschedparam(&attr, &schedparam);

      }

#endif

      int status = posix_spawn(&m_iPid, pszCmdLine, NULL, &attr, argv, environ);

#ifdef APPLEOS

      if(iCa2Priority != (int32_t) ::aura::scheduling_priority_none)
      {

         int32_t iOsPriority = process_get_os_priority(iCa2Priority);

         setpriority(PRIO_PROCESS, m_iPid, iOsPriority);

      }

#endif

      posix_spawnattr_destroy(&attr);




      return status == 0;

      /*
      char *	cmd_line;

      cmd_line = (char *) memory_alloc(strlen(pszCmdLine ) + 1 );

      if(cmd_line == NULL)
      return 0;

      strcpy_dup(cmd_line, pszCmdLine);

      char *   exec_path_name = cmd_line;

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
      return 1;*/


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

      throw todo(get_thread_app());

#else
      int32_t iExitCode;
      //      bool bExited;

      int32_t wpid = waitpid(m_iPid, &iExitCode,
         0
#ifdef WNOHANG
         | WNOHANG
#endif
#ifdef WCONTINUED
         | WCONTINUED
#endif
         );

      if(wpid == -1)
         return true;

      if(WIFEXITED(iExitCode))
      {
         if(puiExitCode != NULL)
         {
            *puiExitCode = WEXITSTATUS(iExitCode);

         }
         return false;
      }
      else if(WIFSIGNALED(iExitCode))
      {
         if(puiExitCode != NULL)
         {
            *puiExitCode = WTERMSIG(iExitCode);
         }
         return false;
      }
      else if(WIFSTOPPED(iExitCode))
      {
         if(puiExitCode != NULL)
         {
            *puiExitCode = WSTOPSIG(iExitCode);
         }
         return false;
      }
#ifdef WIFCONTINUED
      else if(WIFCONTINUED(iExitCode))
      {
         return false;
      }
#endif

      return false;



#endif


   }


} // namespace core



#endif


