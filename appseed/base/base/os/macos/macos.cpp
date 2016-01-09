#include "framework.h"


string & get_command_line_string()
{
   static string g_strCommandLine;
   return g_strCommandLine;
}

wstring & get_command_line_wstring()
{
   static wstring g_wstrCommandLine;
   return g_wstrCommandLine;
}


void SetCommandLineA(const char * psz)
{

   get_command_line_string()     = psz;
   get_command_line_wstring()    = psz;

}

void SetCommandLineW(const unichar * pwsz)
{

   get_command_line_string()     = pwsz;
      get_command_line_wstring()     = pwsz;

}


LPSTR GetCommandLineA()
{

   return (LPSTR) (LPCSTR) get_command_line_string();

}

LPWSTR GetCommandLineW()
{

   return (LPWSTR) (LPCWSTR)    get_command_line_wstring() ;

}




void output_debug_string(const char * psz)
{

   OutputDebugString(psz);

}




CLASS_DECL_AURA bool __node_base_pre_init()
{

   
   return true;

}



CLASS_DECL_AURA bool __node_base_pos_init()
{
   
   
   return true;
   
}


CLASS_DECL_AURA bool __node_base_pre_term()
{
  
   return true;
   
}



CLASS_DECL_AURA bool __node_base_pos_term()
{
   


   return true;
   
}


const char * g_pszCommandLine = NULL;

int32_t run_system()
{
return   __run_system_command_line(g_pszCommandLine);
}

int32_t base_main_command_line(const char * pszParams, int argc, char *argv[])
{
   
   pid_t processid;
   
   string strCommandLine;
   
   strCommandLine = "app ";
   
   strCommandLine += pszParams;
   
   processid=getpid();
   
   printf("%d\n", processid);
   
   string strAddUp;
   
   for(index i = 0; i < argc; i++)
   {
      
      if(strcmp(argv[i], "install") == 0)
      {
         
         strAddUp += " install";
         
      }
      else if(strcmp(argv[i], "uninstall") == 0)
      {
         
         strAddUp += " uninstall";
         
      }
      
   }
   
   strCommandLine += strAddUp;
   
   setlocale(LC_ALL,"");
   
   g_pszCommandLine = strdup_dup(strCommandLine);
   
   ns_shared_application(argc, argv);
   
   
//   __run_system_command_line(pszCommandLine);
   
   ns_app_run();
   
   return 0;
   
   
}
