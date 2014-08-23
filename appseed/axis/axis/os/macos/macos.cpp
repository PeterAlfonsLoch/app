#include "framework.h"


extern thread_pointer < os_thread > t_posthread;


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

void SetCommandLineW(const wchar_t * pwsz)
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




CLASS_DECL_AURA bool __node_aura_pre_init()
{

   
   return true;

}



CLASS_DECL_AURA bool __node_aura_pos_init()
{
   
   t_posthread = new os_thread(NULL, NULL);
   
   t_posthread->m_bRun = true;
   
   return true;
   
}





CLASS_DECL_AURA bool __node_pre_term()
{
  
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
   
   return true;
   
}



CLASS_DECL_AURA bool __node_pos_term()
{
   


   return true;
   
}


