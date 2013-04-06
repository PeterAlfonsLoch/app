#include "framework.h"


os_history::os_history(sp(::ca::application) papp) :
   ca(papp),
   ::ca::history(papp)
{
}


bool os_history::hist(const char * psz)
{

#if !defined(METROWIN)

   simple_shell_launcher launcher(::ca::null(), "open", psz, "", "", SW_SHOWNORMAL);

   launcher.execute();

#endif

   return true;

}


