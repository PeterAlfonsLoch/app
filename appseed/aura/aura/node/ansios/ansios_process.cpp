#include "framework.h"
#include "ansios.h"


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
#include <pthread.h>
extern char * const * environ;
#endif


CLASS_DECL_AURA void process_get_os_priority(int32_t * piOsPolicy, sched_param * pparam, int32_t iCa2Priority);


namespace ansios
{


   process::process(::aura::application * papp):
      element(papp),
      ::process::process(papp)
   {

   }

   process::~process()
   {

   }


   bool process::create_child_process(const char * pszCmdLine,bool bPiped,const char * pszDir,int32_t iCa2Priority)
   {

      if(!::process::process::create_child_process(pszCmdLine,bPiped,pszDir,iCa2Priority))
         return false;

      stringa straParam;

      ptr_array < char > argv;

      straParam.explode_command_line(pszCmdLine, &argv);

      //char * argv[] ={(char *)pszCmdLine,0};
#if defined(LINUX) || defined(APPLEOS)

      posix_spawnattr_t attr;

      posix_spawnattr_init(&attr);


#ifdef LINUX

      if(iCa2Priority != (int32_t) ::multithreading::priority_none)
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

         pipe * ppipeOut = m_pipe.m_sppipeOut.cast < pipe >();

         posix_spawn_file_actions_adddup2(&actions, ppipeOut->m_fd[1],STDOUT_FILENO);

         posix_spawn_file_actions_adddup2(&actions, ppipeOut->m_fd[1],STDERR_FILENO);

         pipe * ppipeIn = m_pipe.m_sppipeIn.cast < pipe >();

         posix_spawn_file_actions_adddup2(&actions, ppipeIn->m_fd[0],STDIN_FILENO);

      }


      int status = posix_spawn(&m_iPid,argv[0],&actions,&attr,(char * const *)argv.get_data(),environ);


#ifdef APPLEOS

      if(iCa2Priority != (int32_t) ::multithreading::priority_none)
      {

         int32_t iOsPriority = process_get_os_priority(iCa2Priority);

         setpriority(PRIO_PROCESS,m_iPid,iOsPriority);

      }

#endif

      return status == 0;

#else

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
         dup2(m_pipe.m_sppipeOut.cast < pipe >()->m_fd[1],STDOUT_FILENO);
         dup2(m_pipe.m_sppipeOut.cast < pipe >()->m_fd[1],STDERR_FILENO);
         dup2(m_pipe.m_sppipeIn.cast < pipe >()->m_fd[0],STDIN_FILENO);
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

   int32_t process::synch_elevated(const char * pszCmdLineParam,int iShow,const ::duration & durationTimeOut,bool * pbTimeOut)
   {

      string pszCmdLine = "/usr/bin/gksu " + string(pszCmdLineParam);

      stringa straParam;

      ptr_array < char > argv;

      straParam.explode_command_line(pszCmdLine, &argv);

      //char * argv[] ={(char *)pszCmdLine,0};
#if defined(LINUX) || defined(APPLEOS)

      posix_spawnattr_t attr;

      posix_spawnattr_init(&attr);


      posix_spawn_file_actions_t actions;

      posix_spawn_file_actions_init(&actions);


      int status = posix_spawn(&m_iPid,argv[0],&actions,&attr,(char * const *)argv.get_data(),environ);

      //int status = posix_spawn(&m_iPid,argv[0],NULL,NULL,(char * const *)argv.get_data(),environ);


#ifdef APPLEOS

      if(iCa2Priority != (int32_t) ::multithreading::priority_none)
      {

         int32_t iOsPriority = process_get_os_priority(iCa2Priority);

         setpriority(PRIO_PROCESS,m_iPid,iOsPriority);

      }

#endif

    DWORD dwStart = get_tick_count();

        while(!has_exited() && get_tick_count() - dwStart < durationTimeOut.get_total_milliseconds())
        {
            Sleep(84);
        }
        DWORD dwExitCode = 0;
        if(!has_exited(&dwExitCode))
        {
        if(pbTimeOut != NULL)
        {
        *pbTimeOut = true;
        }
        }

      return dwExitCode;

#else

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
         dup2(m_pipe.m_sppipeOut.cast < pipe >()->m_fd[1],STDOUT_FILENO);
         dup2(m_pipe.m_sppipeOut.cast < pipe >()->m_fd[1],STDERR_FILENO);
         dup2(m_pipe.m_sppipeIn.cast < pipe >()->m_fd[0],STDIN_FILENO);
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

} // namespace ansios




