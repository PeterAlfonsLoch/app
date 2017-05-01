#include "framework.h"


void ns_app_run()
;
void ns_shared_application(int argc, char *argv[]);

void ns_app_terminate();
//extern thread_pointer < os_thread > t_posthread;

int32_t raw_main_command_line(const char * pszCommandLine, int argc, char *argv[]);



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


void osx_init_workspace_rect();

CLASS_DECL_AURA bool __node_axis_pre_init()
{

   osx_init_workspace_rect();
   
   return true;

}



CLASS_DECL_AURA bool __node_axis_pos_init()
{
   
   
   return true;
   
}





CLASS_DECL_AURA bool __node_axis_pre_term()
{
  
//   if(t_posthread != NULL)
//   {
//      
//      try
//      {
//         
//         delete t_posthread;
//         
//      }
//      catch(...)
//      {
//         
//      }
//      
//      t_posthread = NULL;
//      
//   }
   
   return true;
   
}



CLASS_DECL_AURA bool __node_axis_pos_term()
{
   


   return true;
   
}

const char * g_pszCommandLine = NULL;




int32_t axis_main_command_line(const char * pszParams, int argc, char *argv[])
{
   
   
   pid_t processid;
   
   string strCommandLine;
   
   strCommandLine = argv[0];
   
   if(strCommandLine.find(' ') >= 0)
   {
      
      strCommandLine = "\"" + strCommandLine + "\"";
      
   }
   
   string strP = pszParams;

   strsize iFind = strP.find(':');
   
   if(iFind == 0)
   {
   }
   else
   {
      int iQuote;
      while(iFind > 0)
      {
      
      iQuote = 0;
      const char * psz = &strP[iFind];
      for(; psz >= strP.c_str(); psz = ::str::utf8_dec(strP, psz))
{
         if(*psz == '\"')
         {
            iQuote++;
         }
      }
      
      if(iQuote % 2 == 0)
      {
         break;
         
      }
         iFind = strP.find(':', iFind + 1);
         
      }
      

      
   }
   
   
   string str1;
   
   string str2;
   
   if(iFind >= 0)
   {
      
      str1 = strP.Left(iFind);
      
      if(str1.has_char())
      {
         
         str1 = " " + str1 + " ";
         
      }
      
      str2 = strP.Mid(iFind + 1);
      
      if(str2.has_char())
      {
         
         str2 = " " + str2 + " ";
         
      }
      
   }
   
   string strA;
   
   string strB;
   
   processid = getpid();
   
   printf("%d\n", processid);
   
   string strAddUp;
   
   bool bColon = false;
   
   bool bOverride = false;
   
   for(index i = 1; i < argc; i++)
   {
      
      if(strcmp(argv[i], ":") == 0)
      {
         
         bColon = true;
         
      }
      else
      {
         if(!bColon)
         {
         
            if(argv[i][0] == '-')
            {
            
               bColon = true;
            
            }
            
         }
         
         if(!bColon)
         {
            
            //if(strstr(argv[i], " ") != 0)
            {
               
               strA += " \"" + string(argv[i]) + "\"";
               
            }
//            else
//            {
//            
//               strA += string(" ") + argv[i];
//               
//            }
            
         }
         else
         {
            
            if(::str::begins_ci(argv[i], "app="))
            {
               
               bOverride = true;
               
            }

            strB += string(" ") + argv[i];
            
         }
         
      }
      
   }
   
   if(bOverride)
   {
      
      str2.replace_ci("app=", "fallback_app=");
      
   }
   
   strCommandLine += str1 + strA + " : " + str2 + strB;

   return raw_main_command_line(strCommandLine, argc, argv);

}

int32_t raw_main_command_line(const char * pszCommandLine, int argc, char *argv[])
{

   
   setlocale(LC_ALL,"");
   
   g_pszCommandLine = strdup_dup(pszCommandLine);
   
   ns_shared_application(argc, argv);
   
   ns_app_run();
   
   delete ::aura::system::g_p;
   
   return 0;
   
}








int32_t run_system()
{
   
   return   __run_system_command_line(g_pszCommandLine);
   
}


void macos_on_app_activate()
{
   
   ::aura::system::g_p->on_setting_changed(::aura::setting_app_activation);
   
}
