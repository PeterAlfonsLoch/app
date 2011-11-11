#include "StdAfx.h"
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <errno.h>


int create_process(const char * _cmd_line, int * pprocessId)
{
   char *   exec_path_name;
   char *	cmd_line;

   cmd_line = (char *) ca2_alloc(strlen(_cmd_line ) + 1 );

   if(cmd_line == NULL)
            return 0;

   strcpy_dup(cmd_line, _cmd_line);

   if((*pprocessId = fork()) == 0)
   {
      // child
      char		*pArg, *pPtr;
      char		*argv[1024 + 1];
      int		 argc;
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

void call_sync(const char * path, const char * param)
{

   vsstring strCmdLine;

   strCmdLine = path;
   if(strlen_dup(param) > 0)
   {
      strCmdLine +=  " ";
      strCmdLine += param;
   }

   int processId;

   if(!create_process(strCmdLine, &processId))
      return;


   while(true)
   {

      if(kill(processId, 0) == -1 && errno == ESRCH) // No process can be found corresponding to processId
         break;
      sleep(1);
   }

}



