//#include "framework.h"
//#include <dirent.h>

//using namespace std;

int32_t get_process_pid(const char * procNameParam)
{

   string procName(procNameParam);

   int32_t pid = -1;

   // Open the /proc directory
   DIR *dp = opendir("/proc");
   if (dp != NULL)
   {
      // Enumerate all entries in directory until process found
      struct dirent *dirp;
      while (pid < 0 && (dirp = readdir(dp)))
      {
         // Skip non-numeric entries
         int32_t id = atoi(dirp->d_name);
         if (id > 0)
         {
            // Read contents of virtual /proc/{pid}/cmdline file
            string cmdPath = string("/proc/") + dirp->d_name + "/cmdline";
            FILE * cmdFile = fopen(cmdPath, "rb");
            string cmdLine;
            fgets(cmdLine.GetBufferSetLength(1024 * 256), 1024 * 256, cmdFile);
            cmdLine.ReleaseBuffer();
            if(cmdLine.has_char())
            {
               // Keep first cmdline item which contains the program path
               strsize pos = cmdLine.find('\0');
               if(pos >= 0)
                  cmdLine = cmdLine.substr(0, pos);
               // Keep program name only, removing the path
               pos = cmdLine.reverse_find('/');
               if (pos >= 0)
                  cmdLine = cmdLine.substr(pos + 1);
               // Compare against requested process name
               if (procName == cmdLine)
               pid = id;
            }
            fclose(cmdFile);
         }
      }
   }

   closedir(dp);

   return pid;

}




string module_path_from_pid(unsigned int iPid)
{

   int iSize = 1024 * 8;

   hstring path(iSize);
   char * systemPath = NULL;
   char * candidateDir = NULL;

   string str;
   str = "/proc/" + ::str::from(iPid) + "/exe";

   /* the easiest case: we are in linux */
   ssize_t s = readlink(str,path,iSize);

   if(s == -1)
   {
      return "";
   }

   path[s] = '\0';

   return path;

}



int_array module_path_get_pid(const char * pszPath)
{

   int_array ia;

   ::file::patha stra;

   ::dir::ls_dir(stra,"/proc/");

   for(auto & strPid : stra)
   {

      int iPid = atoi(strPid.title());

      if(iPid > 0)
      {

         string strPath =module_path_from_pid(iPid);

         if(strPath == pszPath)
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

   ::dir::ls_dir(stra,"/proc/");

   string str(psz);

   str = "app=" + str;

   string strApp(psz);

   strApp.replace("-","_");

   strApp.replace("/","_");

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

      ch = (char)mem.get_data()[i];

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



