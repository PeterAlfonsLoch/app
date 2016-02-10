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

   cmd_line = (char *) memory_alloc(strlen(_cmd_line ) + 1 );

   if(cmd_line == NULL)
            return 0;
   cmd_line2 = (char *) memory_alloc(strlen(_cmd_line ) + 1 );

   if(cmd_line2 == NULL)
            return 0;

   strcpy_dup(cmd_line, _cmd_line);

   strcpy_dup(cmd_line2, _cmd_line);

   if((*pprocessId = fork()) == 0)
   {
      // child
      char *      pArg;
      char *      pPtr = NULL;
      char *      argv[1024 + 1];
      int32_t		argc = 0;

      pArg = strtok_r_dup(cmd_line, " ", &pPtr);

      exec_path_name = pArg;

      while(pArg != NULL)
      {

         argv[argc] = pArg;

         argc++;

         if( argc >= 1024 )
         {

            break;

         }

         pArg = strtok_r_dup(NULL, " ", &pPtr);

      }

      argv[argc] = NULL;

      execv(exec_path_name, argv);

      memory_free(cmd_line);

      memory_free(cmd_line2);

      int status = 0;

      wait(&status);

      exit(status);

   }
   else if(*pprocessId == -1)
   {
      // in parent, but error
      *pprocessId = 0;
      memory_free(cmd_line);
      memory_free(cmd_line2);
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
		            bool bPrivileged)
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
        return -1;

    return 0;

}

CLASS_DECL_AURA DWORD call_sync(const char * pszPath, const char * pszParam, const char * pszDir, int32_t iShow, int32_t iRetry, int32_t iSleep, PFNCALLSYNCONRETRY pfnOnRetry, uint_ptr dwParam)
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
        return -1;


    while(true)
    {

        if(kill(processId, 0) == -1 && errno == ESRCH) // No process can be found corresponding to processId
            break;
        sleep(1);
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

   mem.m_strTag = "memory://function=module_path_from_pid";

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



