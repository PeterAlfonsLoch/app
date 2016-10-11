#include "framework.h"
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <string.h>


int32_t create_process(const char * _cmd_line, int32_t * pprocessId)
{
   
   char *   exec_path_name;
   
   char *	cmd_line;
   
   char *	cmd_line2;
   
   cmd_line = strdup(_cmd_line);
   
   if(cmd_line == NULL)
   {
      
      return 0;
      
   }
   
   char *      pArg;
   
   char *      pPtr = NULL;
   
   char *      argv[1024 + 1];
   
   int32_t		argc = 0;
   
   char * p;
   
   char * psz = cmd_line;
   
   enum e_state
   {
      
      state_initial,
      
      state_quote,
      
      state_non_space,
      
   };
   
   e_state e = state_initial;
   
   char quote;
   
   while(psz != NULL && *psz != '\0')
   {
      
      if(e == state_initial)
      {
         
         if(*psz == ' ')
         {
            
            psz = (char *) ::str::utf8_inc(psz);
            
         }
         else if(*psz == '\"')
         {
            
            quote = '\"';
            
            psz = (char *) ::str::utf8_inc(psz);
            
            argv[argc++] = psz;
            
            e = state_quote;
            
         }
         else if(*psz == '\'')
         {
            
            quote = '\'';
            
            psz = (char *) ::str::utf8_inc(psz);
            
            argv[argc++] = psz;
            
            e = state_quote;
            
         }
         else
         {
            
            argv[argc++] = psz;
            
            psz = (char *) ::str::utf8_inc(psz);
            
            e = state_non_space;
            
         }
         
      }
      else if(e == state_quote)
      {
         
         if(*psz == quote)
         {
            
            p = (char *) ::str::utf8_inc(psz);
            
            *psz = '\0';
            
            psz = p;
            
            e = state_initial;
            
         }
         else
         {
            
            psz = (char *) ::str::utf8_inc(psz);
            
         }
         
      }
      else
      {
         
         if(*psz == ' ')
         {
            
            p = (char *) ::str::utf8_inc(psz);
            
            *psz = '\0';
            
            psz = p;
            
            e = state_initial;
            
         }
         else
         {
            
            psz = (char *) ::str::utf8_inc(psz);
            
         }
         
      }
      
   }
   
   argv[argc] = NULL;
   
   
   pid_t pid;
   
   //   char *argv[] = {"ls", (char *) 0};
   
   int status;
   
   //puts("Testing posix_spawn");
   
   //fflush(NULL);
   
   status = posix_spawn(&pid, argv[0], NULL, NULL, argv, environ);
   
   free(cmd_line);
   
   if (status == 0)
   {
      
      return 1;
      
      //    printf("Child id: %i\n", pid);
      //    fflush(NULL);
      //    if (waitpid(pid, &status, 0) != -1) {
      //      printf("Child exited with status %i\n", status);
      //    } else {
      //      perror("waitpid");
      //    }
   }
   else
   {
      
      return 0;
      
      //printf("posix_spawn: %s\n", strerror(status));
      
   }
   
}



int create_process2(const char * _cmd_line, int * pprocessId)
{
   char *   exec_path_name;
   char *	cmd_line;

   cmd_line = (char *) memory_alloc(strlen(_cmd_line ) + 1 );

   if(cmd_line == NULL)
            return 0;

   strcpy_dup(cmd_line, _cmd_line);

   if((*pprocessId = fork()) == 0)
   {
      // child
      char		*pArg, *pPtr;
      char		*argv[1024 + 1];
      int		 argc;
      exec_path_name = cmd_line;
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
   else if(*pprocessId == -1)
   {
      // in parent, but error
      *pprocessId = 0;
      free(cmd_line);
      return 0;
   }
   // in parent, success
   return 1;
}

CLASS_DECL_AURA int call_async(
                            const char * pszPath, 
                            const char * pszParam, 
                            const char * pszDir,
                            int iShow,
                               bool bPrivileged,
                               unsigned int * puiPid)
{
   
   string strCmdLine;
    
    strCmdLine = pszPath;
    if(strlen_dup(pszParam) > 0)
    {
        strCmdLine +=  " ";
        strCmdLine += pszParam;
    }
    
    int processId;
    
    if(!create_process(strCmdLine, &processId))
        return -1;
   
   
   if(puiPid != NULL)
   {
      
      *puiPid = processId;
      
   }
   
    
    return 0;
    
}

CLASS_DECL_AURA DWORD call_sync(
                             const char * pszPath, 
                             const char * pszParam, 
                             const char * pszDir,
                             int iShow,
                             int iRetry, 
                             int iSleep, 
                             int (* pfnOnRetry)(int iTry, uint_ptr dwParam),
                             uint_ptr dwParam,
                             unsigned int * puiPid)
{

   string strCmdLine;
    
   strCmdLine = pszPath;
   
   if(strlen_dup(pszParam) > 0)
   {
   
      strCmdLine +=  " ";
      strCmdLine += pszParam;
   }
    
   int processId;
    
   if(!create_process(strCmdLine, &processId))
      return -1;
   
   
   if(puiPid != NULL)
   {
      
      *puiPid = processId;
      
   }
    
    
   while(true)
   {
   
      if(kill(processId, 0) == -1 && errno == ESRCH) // No process can be found corresponding to processId
         break;
   
      sleep(1);
      
   }
   
   return 0;
   
}








