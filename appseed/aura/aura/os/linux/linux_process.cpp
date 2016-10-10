//#include "framework.h"

//#include <signal.h>
//#include <unistd.h>


CLASS_DECL_AURA void dll_processes(uint_array & dwa, stringa & straProcesses, const char * pszDll)
{

   UNREFERENCED_PARAMETER(dwa);
   UNREFERENCED_PARAMETER(straProcesses);
   UNREFERENCED_PARAMETER(pszDll);

}






//extern thread_pointer < hthread > t_hthread;

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

            psz = ::str::utf8_inc(psz);

         }
         else if(*psz == '\"')
         {

            quote = '\"';

            psz = ::str::utf8_inc(psz);

            argv[argc++] = psz;

            e = state_quote;

         }
         else if(*psz == '\'')
         {

            quote = '\'';

            psz = ::str::utf8_inc(psz);

            argv[argc++] = psz;

            e = state_quote;

         }
         else
         {

            argv[argc++] = psz;

            psz = ::str::utf8_inc(psz);

            e = state_non_space;

         }

      }
      else if(e == state_quote)
      {

         if(*psz == quote)
         {

            p = ::str::utf8_inc(psz);

            *psz = '\0';

            psz = p;

            e = state_initial;

         }
         else
         {

            psz = ::str::utf8_inc(psz);

         }

      }
      else
      {

         if(*psz == ' ')
         {

            p = ::str::utf8_inc(psz);

            *psz = '\0';

            psz = p;

            e = state_initial;

         }
         else
         {

            psz = ::str::utf8_inc(psz);

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


int32_t create_process2(const char * _cmd_line, int32_t * pprocessId)
{

   char *   exec_path_name;

   char *	cmd_line;

   char *	cmd_line2;

   cmd_line = strdup(_cmd_line);

   if(cmd_line == NULL)
   {

      return 0;

   }

   cmd_line2 = strdup(_cmd_line);

   if(cmd_line2 == NULL)
   {

      free(cmd_line);

      return 0;

   }

   strcpy_dup(cmd_line, _cmd_line);

   strcpy_dup(cmd_line2, _cmd_line);

   const char * pszEnv = getenv("LD_LIBRARY_PATH");

   if((*pprocessId = fork()) == 0)
   {

      char *      pArg;

      char *      pPtr = NULL;

      char *      argv[1024 + 1];

      int32_t		argc = 0;

      char * p;

      setenv("LD_LIBRARY_PATH", pszEnv, 1);

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

               psz = ::str::utf8_inc(psz);

            }
            else if(*psz == '\"')
            {

               quote = '\"';

               psz = ::str::utf8_inc(psz);

               argv[argc++] = psz;

               e = state_quote;

            }
            else if(*psz == '\'')
            {

               quote = '\'';

               psz = ::str::utf8_inc(psz);

               argv[argc++] = psz;

               e = state_quote;

            }
            else
            {

               argv[argc++] = psz;

               psz = ::str::utf8_inc(psz);

               e = state_non_space;

            }

         }
         else if(e == state_quote)
         {

            if(*psz == quote)
            {

               p = ::str::utf8_inc(psz);

               *psz = '\0';

               psz = p;

               e = state_initial;

            }
            else
            {

               psz = ::str::utf8_inc(psz);

            }

         }
         else
         {

            if(*psz == ' ')
            {

               p = ::str::utf8_inc(psz);

               *psz = '\0';

               psz = p;

               e = state_initial;

            }
            else
            {

               psz = ::str::utf8_inc(psz);

            }

         }

      }

      argv[argc] = NULL;

      execv(argv[0], argv);

      int status = 0;

      wait(&status);

      free(cmd_line);

      free(cmd_line2);

      exit(status);

   }
   else if(*pprocessId == -1)
   {

      // in parent, but error

      *pprocessId = 0;

      free(cmd_line);

      free(cmd_line2);

      return 0;

   }

   // in parent, success
   return 1;

}

CLASS_DECL_AURA int32_t call_async(
                            const char * pszPath,
                            const char * pszParam,
                            const char * pszDir,
                            int32_t iShow,
		            bool bPrivileged,
		            unsigned int * puiPid = NULL)
{
    string strCmdLine;

    strCmdLine = pszPath;
    if(strlen_dup(pszParam) > 0)
    {
        strCmdLine +=  " ";
        strCmdLine += pszParam;
    }

    int32_t processId;

    if(!create_process(strCmdLine, &processId))
    {

        if(puiPid != NULL)
        {

            *puiPid = -1;

        }

        return -1;

    }

    if(puiPid != NULL)
    {

        *puiPid = processId;

    }

    return 0;

}

CLASS_DECL_AURA DWORD call_sync(const char * pszPath, const char * pszParam, const char * pszDir, int32_t iShow, int32_t iRetry, int32_t iSleep, PFNCALLSYNCONRETRY pfnOnRetry, uint_ptr dwParam, unsigned int * puiPid)
{

    string strCmdLine;

    strCmdLine = pszPath;
    if(strlen_dup(pszParam) > 0)
    {
        strCmdLine +=  " ";
        strCmdLine += pszParam;
    }

    int32_t processId;

    if(!create_process(strCmdLine, &processId))
    {

        if(puiPid != NULL)
        {

            *puiPid = -1;

        }

        return -1;

    }


    while(true)
    {

        if(kill(processId, 0) == -1 && errno == ESRCH) // No process can be found corresponding to processId
            break;
        sleep(1);
    }

    if(puiPid != NULL)
    {

        *puiPid = processId;

    }

    return 0;

}








string module_path_from_pid(unsigned int iPid)
{

   struct stat sb;

   int iSize;

   string str;

   str = "/proc/" + ::str::from(iPid) + "/exe";

   memory mem;

   ssize_t s;

   bool iTry;

   if(lstat(str, &sb) == -1)
   {

retry:

      iSize = 1024 * 4;

      iTry = 1;

      sb.st_size = iSize - 1;

   }
   else
   {

      iSize = sb.st_size + 1;

      iTry = 0;

   }
#if MEMDLEAK
   mem.m_strTag = "memory://function=module_path_from_pid";
#endif
   mem.allocate(iSize);

   s = readlink (str, mem.get_data(), iSize);

   if(s > sb.st_size)
   {

      if(iTry <= 0)
      {

         goto retry;

      }
      else
      {

         return "";

      }

   }

   mem.get_data()[s] = '\0';

   return (const char *) mem.get_data();

}



int_array module_path_get_pid(const char * pszPath)
{

   int_array ia;

   ::file::patha stra;

	::dir::ls_dir(stra, "/proc/");

   for(auto & strPid : stra)
   {

      int iPid = atoi(strPid.title());

      if(iPid > 0)
      {

         string strPath =module_path_from_pid(iPid);

         if(strPath	 == pszPath)
         {

            ia.add(iPid);

         }

      }

   }

   return ia;

}


int_array app_get_pid(const char * psz)
{

   int_array ia;

   ::file::patha stra;

	::dir::ls_dir(stra, "/proc/");

	string str(psz);

	str = "app=" + str;

	string strApp(psz);

	strApp.replace("-", "_");

	strApp.replace("/", "_");

	for(auto & strPid : stra)
   {

      int iPid = atoi(strPid.title());

      if(iPid > 0)
      {

         ::file::path path = module_path_from_pid(iPid);

         if(path.title() == strApp)
         {

            ia.add(iPid);

         }
         else
         {

            stringa straCmdLine = cmdline_from_pid(iPid);

            string strCmdLine;

            strCmdLine = straCmdLine.implode(" ");

            if(straCmdLine.find_first(str) > 0)
            {

               ia.add(iPid);

            }

         }

      }

   }

   return ia;

}



stringa cmdline_from_pid(unsigned int iPid)
{

   stringa stra;

   string str;

   str = "/proc/" + ::str::from(iPid) + "/cmdline";

   memory mem = file_as_memory_dup(str);

   string strArg;

   char ch;

   for(int i = 0; i < mem.get_size(); i++)
   {

      ch = (char) mem.get_data()[i];

      if(ch == '\0')
      {

         stra.add(strArg);

         strArg.Empty();

      }
      else
      {

         strArg += ch;

      }


   }

   if(strArg.has_char())
   {

      stra.add(strArg);

   }

   return stra;

    /* the easiest case: we are in linux */
//    ssize_t s = readlink (str, path, iSize);

  //  if(s == -1)
    //{
       // return "";
    //}

    //path[s] = '\0';

	//return path;

}



