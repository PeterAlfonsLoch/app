#include "framework.h"

os_history::os_history(::ca::application * papp) :
   ca(papp),
   ::ca::history(papp)
{
}
         
   
bool os_history::hist(const char * psz)
{
   ::ShellExecute(NULL, "open", psz, "", "", SW_SHOWNORMAL);
   return true;
}


