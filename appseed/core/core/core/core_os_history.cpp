//#include "framework.h"


os_history::os_history(::aura::application * papp) :
   object(papp),
   ::core::history(papp)
{
}


bool os_history::hist(const char * psz)
{

#if !defined(METROWIN)

   simple_shell_launcher launcher(NULL, "open", psz, "", "", SW_SHOWNORMAL);

   launcher.execute();

#endif

   return true;

}


