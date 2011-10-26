#include "StdAfx.h"
#ifdef WINDOWS
#include <ShellAPI.h>
#endif

#ifdef LINUX
#include <stdlib.h>
#include <stdio.h>

char *
strtok_r(char *s1, const char *s2, char **lasts)
{
  char *ret;

  if (s1 == NULL)
    s1 = *lasts;
  while(*s1 && strchr_dup(s2, *s1))
    ++s1;
  if(*s1 == '\0')
    return NULL;
  ret = s1;
  while(*s1 && !strchr_dup(s2, *s1))
    ++s1;
  if(*s1)
    *s1++ = '\0';
  *lasts = s1;
  return ret;
}

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
         pArg = strtok_r(cmd_line, " ", &pPtr);
         while( pArg != NULL )
         {
            argv[argc] = pArg;
            argc++;
            if( argc >= 1024 )
               break;
            pArg = strtok_r(NULL, " ", &pPtr);
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

#endif

void call_sync(const char * path, const char * param)
{

   SHELLEXECUTEINFOA infoa;

   memset_dup(&infoa, 0, sizeof(infoa));

   infoa.cbSize = sizeof(infoa);
   infoa.lpFile = path;
   infoa.lpParameters = param;

   execute_sync(&infoa);

}



void execute_sync(SHELLEXECUTEINFOA * pinfoa)
{

   pinfoa->fMask |= SEE_MASK_NOCLOSEPROCESS | SEE_MASK_NOASYNC | SEE_MASK_FLAG_NO_UI;

   ::ShellExecuteExA(pinfoa);

   DWORD dwExitCode;
   int i = 1;
   while(true)
   {
      if(!GetExitCodeProcess(pinfoa->hProcess, &dwExitCode))
         break;
      if(dwExitCode != STILL_ACTIVE)
         break;
      Sleep(84);
      i++;
   }

}



