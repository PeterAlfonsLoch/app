#include <sys/types.h>
#include <sys/param.h>
#define user user_struct
#include <sys/user.h>
#include <sys/sysctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <libproc.h>


extern int strncmp_dup(const char * sz1, const char * sz2, int_ptr iLen);

///************************************************************************
// *
// * Returns the pid of the process name which is given as the function
// * argument.
// * In case no process found with the given name -1 will be returned.
// *
// *************************************************************************/
///*=======================================================================*/
//int get_process_pid(const char * csProcessName)
//{
///*=======================================================================*/
//
//        struct kinfo_proc *sProcesses = NULL, *sNewProcesses;
//        pid_t  iCurrentPid;
//        int    aiNames[4];
//        size_t iNamesLength;
//        int    i, iRetCode, iNumProcs;
//        size_t iSize;
//
//        iSize = 0;
//        aiNames[0] = CTL_KERN;
//        aiNames[1] = KERN_PROC;
//        aiNames[2] = KERN_PROC_ALL;
//        aiNames[3] = 0;
//        iNamesLength = 3;
//
//        iRetCode = sysctl(aiNames, (u_int) iNamesLength, NULL, &iSize, NULL, 0);
//
//        /*
//         * Allocate memory and populate info in the  processes structure
//         */
//
//        do {
//                iSize += iSize / 10;
//                sNewProcesses = (struct kinfo_proc *) realloc(sProcesses, iSize);
//
//                if (sNewProcesses == 0) {
//                        if (sProcesses)
//                                free(sProcesses);
//                                throw "could not reallocate memory";
//                }
//                sProcesses = sNewProcesses;
//                iRetCode = sysctl(aiNames, (u_int) iNamesLength, sProcesses, &iSize, NULL, 0);
//        } while (iRetCode == -1 && errno == ENOMEM);
//
//        iNumProcs = (int) (iSize / sizeof(struct kinfo_proc));
//      /*
//         * Search for the given process name and return its pid.
//         */
//
//        for (i = 0; i < iNumProcs; i++) {
//                iCurrentPid = sProcesses[i].kp_proc.p_pid;
//                if( strncmp_dup(csProcessName, sProcesses[i].kp_proc.p_comm, MAXCOMLEN) == 0 ) {
//                        free(sProcesses);
//                        return iCurrentPid;
//                }
//        }
//
//        /*
//         * Clean up and return -1 because the given proc name was not found
//         */
//
//        free(sProcesses);
//        return (-1);
//} /* end of getProcessId() */
//

// http://stackoverflow.com/questions/3018054/retrieve-names-of-running-processes
// http://stackoverflow.com/users/115730/dave-delong
// http://stackoverflow.com/users/237188/v%C3%A1clav-slav%C3%ADk
// https://github.com/vslavik/

int_array get_pids()
{
   
   int_array pids;
   
   array < pid_t > pida;
   
   int numberOfProcesses = proc_listpids(PROC_ALL_PIDS, 0, NULL, 0);
   
   pida.set_size(numberOfProcesses);
   
   proc_listpids(PROC_ALL_PIDS, 0, pids, sizeof(pids));
   
   for(auto pid : pida)
   {
      if(pid == 0)
      {
         
         continue;
      
      }
      
      pids.add(pid);
      
   }
   
   return pids;
   
}


int_array module_path_get_pid(const char * csProcessName)
{
   
   int_array iaPid;
   
   int_array pids = get_pids();
   
   string strPath;
   
   for(auto iCurrentPid : pids)
   {
      
      strPath = module_path_from_pid(iCurrentPid);
      
      if(strPath.CompareNoCase(csProcessName) == 0 )
      {
         
         iaPid.add(iCurrentPid);
         
      }
      
   }
   
   return iaPid;
   
}

// https://astojanov.wordpress.com/2011/11/16/mac-os-x-resolve-absolute-path-using-process-pid/


string module_path_from_pid(unsigned int uiPid)
{
   

   pid_t pid = uiPid;
   
   int ret;

   char pathbuf[PROC_PIDPATHINFO_MAXSIZE];

   ret = proc_pidpath (pid, pathbuf, sizeof(pathbuf));
   
   if ( ret <= 0 )
   {
      
      fprintf(stderr, "PID %d: proc_pidpath ();\n", pid);
      
      fprintf(stderr,	"    %s\n", strerror(errno));
      
      return "";
      
   }
   else
   {
   
      return pathbuf;
      
   }
   
}



int_array app_get_pid(const char * psz)
{
   
   int_array ia;
   
   int_array pids = get_pids();
   
   string str(psz);
   
   str = "app=" + str;
   
   string strApp(psz);
   
   strApp.replace("-", "_");
   
   strApp.replace("/", "_");
   
   for(auto pid : pids)
   {
      
      if(pid <= 0)
      {
         
         continue;
         
      }
      
      ::file::path path = module_path_from_pid(pid);
         
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
   
   return ia;
   
}



// http://stackoverflow.com/questions/31500821/get-process-cmdline-in-mac-os-from-another-c-based-executable
// http://stackoverflow.com/users/823872/dan

#define SHOW_ZOMBIES 0

string get_cmdline(unsigned int uiPid)
{
   
   struct proc_taskallinfo info = {};
   
   int ret = proc_pidinfo((pid_t) uiPid, PROC_PIDTASKALLINFO, SHOW_ZOMBIES, &info, sizeof(struct proc_taskallinfo));
   
   return info.pbsd.pbi_comm;
   
}


stringa cmdline_from_pid(unsigned int uiPid)
{

   string strCmdLine = get_cmdline(uiPid);
   
   stringa stra;
   
   string strArg;
   
   const char * psz = strCmdLine;
   
   string strChar;
   
   while(*psz != '\0')
   {
      
      strChar = ::str::get_utf8_char(psz);
      
      if(strChar.is_empty())
      {
         
         break;
         
      }
      
      psz += strChar.get_length();
      
      if(strChar == "\"")
      {
         
         while(*psz != '\0')
         {
            
            strChar = ::str::get_utf8_char(psz);
            
            if(strChar.is_empty())
            {
               
               goto end;
               
            }
            else if(strChar == "\"")
            {
               
               break;
               
            }
            
            psz += strChar.get_length();
            
            
            if(strChar == "\\")
            {
               
               strChar = ::str::get_utf8_char(psz);
               
               if(strChar.is_empty())
               {
                  
                  goto end;
                  
               }

               psz += strChar.get_length();

               if(strChar == "n")
               {
                  
                  strArg += "\n";
                  
               }
               else
               {
                  
                  strArg += strChar;
                  
               }
               
            }
            else
            {
            
               strArg += strChar;
               
            }
            
         }
         
         stra.add(strArg);
         
         strArg.Empty();
         
      }
      else if(strChar == " ")
      {
         
         stra.add(strArg);
         
         strArg.Empty();
         
      }
      else if(strChar == "\\")
      {
         
         strChar = ::str::get_utf8_char(psz);
         
         if(strChar.is_empty())
         {
            
            goto end;
            
         }
         
         psz += strChar.get_length();
         
         if(strChar == "n")
         {
            
            strArg += "\n";
            
         }
         else
         {
            
            strArg += strChar;
            
         }
         
      }
      else
      {
         
         strArg += strChar;
         
      }
      
      
   }
   
end:
   
   if(strArg.has_char())
   {
      
      stra.add(strArg);
      
   }

   return stra;

}


