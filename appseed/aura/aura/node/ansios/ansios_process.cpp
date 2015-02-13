//#include "framework.h"
//#include "ansios.h"


#if defined(ANDROID)
//#include <sys/wait.h>
//#include <unistd.h>
//#include <pthread.h>
//#include <stdlib.h>
#elif defined(LINUX)
//#include <sys/wait.h>
//#include <unistd.h>
//#include <spawn.h>
extern char **environ;
#elif defined(APPLEOS)
//#include <sys/wait.h>
//#include <unistd.h>
//#include <spawn.h>
//#include <pthread.h>
//#include <stdlib.h>
extern char * const * environ;
#endif

string ca2_module_folder_dup();


CLASS_DECL_AURA void process_get_os_priority(int32_t * piOsPolicy, sched_param * pparam, int32_t iCa2Priority);
namespace ansios
{


   process::process(::aura::application * papp):
      object(papp),
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
      
      ptr_array < char > env;
      
      char * const * e = environ;
      
      string strFallback;
      
#ifdef MACOS
      
      strFallback = ::ca2_module_folder_dup();
      
#endif
      
      if(::str::begins_ci(strFallback, "/Users/"))
      {
      
         index i = 0;
      
         int iPrevious = -1;
      
         const char * psz;
      
         while((psz = environ[i]) != NULL)
         {
            if(i <= iPrevious)
               break;
         
            env.add((char *) psz);
         
            iPrevious = i;
         
            i++;
         
         }
      
#ifdef MACOS
      
         string strCurrent = getenv("DYLD_FALLBACK_LIBRARY_PATH");
      
         if(strCurrent.has_char())
         {
         
            strFallback += ":" + strCurrent;
         
         }
      
         strFallback = string("DYLD_FALLBACK_LIBRARY_PATH=") + strFallback;
      
         env.add((char *) (const char *) strFallback);
              
#endif
      
         env.add(NULL);
         
         e = (char * const *)env.get_data();
         
      }
      
      int status = posix_spawn(&m_iPid,argv[0],&actions,&attr,(char * const *)argv.get_data(),e);

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
      
#if defined(MACOS)
      
      
      string strFallback = ::ca2_module_folder_dup();
      
      string strFolder = strFallback;
      
//      ::dir::eat_end_level(strFolder, 2, NULL);
      
      string strCurrent = getenv("DYLD_FALLBACK_LIBRARY_PATH");
      
      if(strCurrent == strFallback || ::str::ends(strCurrent, ":" + strFallback) || str::begins(strCurrent, strFallback + ":") || strCurrent.contains(":"+strFallback +":"))
      {
         
         strFallback = strCurrent;
         
      }
      else if(strCurrent.has_char())
      {
         
         strFallback += ":" + strCurrent;
         
      }
      
      setenv("DYLD_FALLBACK_LIBRARY_PATH", strFallback, TRUE);
      
      // Create authorization reference
      OSStatus status;
      
      AuthorizationRef authorizationRef;
      
      // AuthorizationCreate and pass NULL as the initial
      // AuthorizationRights set so that the AuthorizationRef gets created
      // successfully, and then later call AuthorizationCopyRights to
      // determine or extend the allowable rights.
      // http://developer.apple.com/qa/qa2001/qa1172.html
      status = AuthorizationCreate(NULL, kAuthorizationEmptyEnvironment, kAuthorizationFlagDefaults, &authorizationRef);
      
      if (status != errAuthorizationSuccess)
      {
         
         TRACE("Error Creating Initial Authorization: %d", status);
         
         return -1;
         
      }
      
      // kAuthorizationRightExecute == "system.privilege.admin"
      AuthorizationItem right = {kAuthorizationRightExecute, 0, NULL, 0};
      AuthorizationRights rights = {1, &right};
      AuthorizationFlags flags = kAuthorizationFlagDefaults |
      kAuthorizationFlagInteractionAllowed |
      kAuthorizationFlagPreAuthorize |
      kAuthorizationFlagExtendRights;
      
      

      // Call AuthorizationCopyRights to determine or extend the allowable rights.
      status = AuthorizationCopyRights(authorizationRef, &rights, NULL, flags, NULL);
      if (status != errAuthorizationSuccess)
      {
         TRACE("Copy Rights Unsuccessful: %d", status);
         return -1;
      }
      
      TRACE("\n\n** %s **\n\n", "This command should work.");


      stringa straParam;
      
      ptr_array < char > argv;
      
      straParam.add("/bin/bash");

      straParam.add("-c");
      
      string strC = "ignit_phase2 () { export DYLD_FALLBACK_LIBRARY_PATH="+strFallback+" ; cd "+strFolder+" ; "+string(pszCmdLineParam)+" ; } ; ignit_phase2 ;";
//            string strC = "export DYLD_FALLBACK_LIBRARY_PATH="+strFallback;
      
      straParam.add(strC);
      
      for(index i = 0; i < straParam.get_count(); i++)
      {
         
         argv.add((char *)(const char *)straParam[i]);
         
      }
      
      argv.add(NULL);
      

      
      char *tool = (char * )argv[0];
      char **args = (char **) &argv.get_data()[1];
      FILE *pipe = NULL;
      
//      int uid = getuid();
      
      
      
//      int i = setuid(0);
      
  //    if(i != 0)
    //  {
      //   TRACE("Failed to setuid: %d", i);
        // return -1;
      //}
      
      
      /*
      stringa straParam;
      
      ptr_array < char > argv;
      
      
      straParam.explode_command_line(pszCmdLineParam, &argv);
      
      posix_spawnattr_t attr;
      
      posix_spawnattr_init(&attr);
      
      
      posix_spawn_file_actions_t actions;
      
      posix_spawn_file_actions_init(&actions);
      
      
      status = posix_spawn(&m_iPid,argv[0],&actions,&attr,(char * const *)argv.get_data(),environ);
      
      //int status = posix_spawn(&m_iPid,argv[0],NULL,NULL,(char * const *)argv.get_data(),environ);
      
      printf("synch_elevated : posix_spawn return status %d", status);
      
      
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
      */
      
//      setuid(uid);
      
      status = AuthorizationExecuteWithPrivileges(authorizationRef, tool, kAuthorizationFlagDefaults, args, &pipe);
      if (status != errAuthorizationSuccess)
      {
         TRACE("AuthorizationExecuteWithPrivileges Error: %d", status);
         return -1;
      }

      /*

      straParam.remove_all();
      argv.remove_all();
      straParam.explode_command_line(pszCmdLineParam, &argv);
      
      tool = (char * )argv[0];
      args = (char **) &argv.get_data()[1];
      pipe = NULL;


      status = AuthorizationExecuteWithPrivileges(authorizationRef, tool, kAuthorizationFlagDefaults, args, &pipe);
      if (status != errAuthorizationSuccess)
      {
         TRACE("AuthorizationExecuteWithPrivileges Error: %d", status);
         return -1;
      }
       
       */
      
      DWORD dwExitCode = 0;

      
      if(pipe != NULL)
      {
         
         int pptp_pid = 0;

         fscanf(pipe, "%d", &pptp_pid);
         
//         pid_t pptp_pid = 0;
         
  //       fread(&pptp_pid,sizeof(pptp_pid),1,pipe); // get pid
         
         m_iPid = pptp_pid;
         
         DWORD dwStart = get_tick_count();
         
         while(!has_exited() && get_tick_count() - dwStart < durationTimeOut.get_total_milliseconds())
         {
            Sleep(84);
         }
         if(!has_exited(&dwExitCode))
         {
            if(pbTimeOut != NULL)
            {
               *pbTimeOut = true;
            }
         }
      
/*         char c;
      
         int iRead;
      
         string strRead;
      
         while(true)
         {
            iRead = fread(&c,1,1, pipe);
            if(iRead == 1)
            {
               strRead += c;
            }
            else if(ferror(pipe))
            {
               TRACE("Error reading from file");
               break;
            }
            else
            {
            }
         }
         
         fclose(pipe);
      
         TRACE0(strRead);*/
         
         
      }
      
      // The only way to guarantee that a credential acquired when you
      // request a right is not shared with other authorization instances is
      // to destroy the credential.  To do so, call the AuthorizationFree
      // function with the flag kAuthorizationFlagDestroyRights.
      // http://developer.apple.com/documentation/Security/Conceptual/authorization_concepts/02authconcepts/chapter_2_section_7.html
      status = AuthorizationFree(authorizationRef, kAuthorizationFlagDestroyRights);

      if (status != errAuthorizationSuccess)
      {
         TRACE("AuthorizationFree Error: %d", status);
      }

      return dwExitCode;
#else
      
       stringa straParam;
       
       ptr_array < char > argv;
       
#ifdef MACOS
    
       straParam.add("/usr/bin/osascript");
       straParam.add("-e");
       straParam.add("'do shell script \"" + string(pszCmdLineParam) + "\" with administrator privileges'");
       
       argv.add((char *) (const char *) straParam[0]);
       argv.add((char *) (const char *) straParam[1]);
       argv.add((char *) (const char *) straParam[2]);
       argv.add(NULL);
       
#else

      string pszCmdLine = "/usr/bin/gksu " + string(pszCmdLineParam);

      straParam.explode_command_line(pszCmdLine, &argv);
       
#endif


      //char * argv[] ={(char *)pszCmdLine,0};
#if defined(LINUX) || defined(APPLEOS)

      posix_spawnattr_t attr;

      posix_spawnattr_init(&attr);


      posix_spawn_file_actions_t actions;

      posix_spawn_file_actions_init(&actions);


      int status = posix_spawn(&m_iPid,argv[0],&actions,&attr,(char * const *)argv.get_data(),environ);

      //int status = posix_spawn(&m_iPid,argv[0],NULL,NULL,(char * const *)argv.get_data(),environ);
       
       printf("synch_elevated : posix_spawn return status %d", status);


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

      //if(bPiped)
      //{
      //   dup2(m_pipe.m_sppipeOut.cast < pipe >()->m_fd[1],STDOUT_FILENO);
      //   dup2(m_pipe.m_sppipeOut.cast < pipe >()->m_fd[1],STDERR_FILENO);
      //   dup2(m_pipe.m_sppipeIn.cast < pipe >()->m_fd[0],STDIN_FILENO);
      //}


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
      
#endif

   }

} // namespace ansios




