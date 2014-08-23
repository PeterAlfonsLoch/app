#include "framework.h"
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <string.h>


extern thread_pointer < os_thread > t_posthread;
//extern CLASS_DECL_THREAD HTHREAD currentThread;


int create_process(const char * _cmd_line, int * pprocessId)
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

CLASS_DECL_AXIS int call_async(
                            const char * pszPath, 
                            const char * pszParam, 
                            const char * pszDir,
                            int iShow)
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
    
    return 0;
    
}

CLASS_DECL_AXIS DWORD call_sync(
                             const char * pszPath, 
                             const char * pszParam, 
                             const char * pszDir,
                             int iShow,
                             int iRetry, 
                             int iSleep, 
                             int (* pfnOnRetry)(int iTry, uint_ptr dwParam),
                             uint_ptr dwParam)
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
    
    
   while(true)
   {
   
      if(kill(processId, 0) == -1 && errno == ESRCH) // No process can be found corresponding to processId
         break;
   
      sleep(1);
      
   }
   
   return 0;
   
}








CLASS_DECL_AXIS bool main_initialize()
{
   
//   initialize_primitive_heap();
   
//   if(!os_initialize())
  //    return false;
   
   set_thread_ptr("t_posthread", new os_thread(NULL, NULL));
   
   t_posthread->m_bRun = true;
   
//   currentThread = new hthread;
   
   return true;
   
}


CLASS_DECL_AXIS bool main_finalize()
{
   
   bool bOk = true;
   
//   if(!os_finalize())
  //    bOk = false;
   
   if(t_posthread != NULL)
   {
      
      try
      {
         
         delete t_posthread;
         
      }
      catch(...)
      {
         
      }
      
      t_posthread = NULL;
      
   }
   
//   os_thread::stop_all((1984 + 1977) * 49);
   
//   finalize_primitive_trace();
   
   return bOk;
   
}




bool os_initialize()
{
   
//   if(!initialize_primitive_trace())
  //    return false;
   
   
   return TRUE;
   
}


bool os_finalize()
{
   
//   finalize_primitive_trace();
   
   return true;
   
}