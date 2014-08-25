#include "framework.h"


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




namespace ansios
{


   process::process(sp(::aura::application) papp):
      element(papp),
      ::process::process(papp)
   {

   }

   process::~process()
   {

   }


   bool process::create_child_process(const char * pszCmdLine,bool bPiped,const char * pszDir,int32_t iCa2Priority)
   {

      if(!::aura::process::create_child_process(pszCmdLine,bPiped,pszDir,iCa2Priority))
         return false;

      string szCmdline = pszCmdLine;

      char * argv[] ={(char *)pszCmdLine,0};

      posix_spawnattr_t attr;

      posix_spawnattr_init(&attr);

#ifdef LINUX

      if(iCa2Priority != (int32_t) ::aura::scheduling_priority_none)
      {

         int32_t iPolicy = SCHED_OTHER;

         sched_param schedparam;

         schedparam.sched_priority = 0;

         process_get_os_priority(&iPolicy,&schedparam,iCa2Priority);

         posix_spawnattr_setschedpolicy(&attr,iPolicy);

         posix_spawnattr_setschedparam(&attr,&schedparam);

      }

#endif

      posix_spawn_file_actions_t actions;

      posix_spawn_file_actions_init(&actions);

      if(bPiped)
      {

         pipe * ppipeOut = m_pipe.m_sppipeOut.cast < ::ansios::pipe >();

         posix_spawn_file_actions_adddup2(&actions, ppipeOut->m_fd[1],STDOUT_FILENO);

         posix_spawn_file_actions_adddup2(&actions, ppipeOut->m_fd[1],STDERR_FILENO);

         pipe * ppipeIn = m_pipe.m_sppipeIn.cast < ::ansios::pipe >();

         posix_spawn_file_actions_adddup2(&actions, m_pipe.m_sppipeOut.cast < ::ansions::pipe >()->m_fd[0],STDIN_FILENO);

      }


      int status = posix_spawn(&m_iPid,pszCmdLine,&actions,&attr,argv,environ);

#ifdef APPLEOS

      if(iCa2Priority != (int32_t) ::aura::scheduling_priority_none)
      {

         int32_t iOsPriority = process_get_os_priority(iCa2Priority);

         setpriority(PRIO_PROCESS,m_iPid,iOsPriority);

      }

#endif

//#ifdef LINUX


      posix_spawn_file_actions_destroy(&actions);

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


      int32_t iExitCode;
      //      bool bExited;

      int32_t wpid = waitpid(m_iPid,&iExitCode,
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



   }


} // namespace ansios




