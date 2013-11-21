#include "framework.h"


HANDLE g_hmutexBoot = NULL;

int32_t installer(const char * param);


int32_t ca2_cube_install(const char * pszCommandLine, bool bBackground)
{

   wait_until_mutex_does_not_exist("Global\\::ca::fontopus::ca2_spa::7807e510-5579-11dd-ae16-0800200c7784");


   char * szParameters = (char *) memory_alloc(strlen_dup(pszCommandLine) + 256);
   strcpy_dup(szParameters, "synch_spaadmin:");
   strcat_dup(szParameters, "starter_start:");
   strcat_dup(szParameters, pszCommandLine);
   if(bBackground)
   {
      strcat_dup(szParameters, " background");
   }

   installer(szParameters);

   memory_free_dbg(szParameters, 0);

   return 0;
}




int32_t start_ca2_cube_install(const char * pszCommandLine, bool bBackground)
{

   wait_until_mutex_does_not_exist("Global\\::ca::fontopus::ca2_spa::7807e510-5579-11dd-ae16-0800200c7784");


   char * szParameters = (char *) memory_alloc(strlen_dup(pszCommandLine) + 256);
   strcpy_dup(szParameters, "spaadmin:");
   strcat_dup(szParameters, "starter_start:");
   strcat_dup(szParameters, pszCommandLine);
   if(bBackground)
   {
      strcat_dup(szParameters, " background");
   }

   installer(szParameters);

   memory_free_dbg(szParameters, 0);

   return 0;
}




