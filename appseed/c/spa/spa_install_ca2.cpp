#include "StdAfx.h"


HANDLE g_hmutexBoot = NULL;

int installer(const char * param);


int APIENTRY ca2_cube_install(const char * pszCommandLine, bool bBackground)
{

   wait_until_mutex_does_not_exist("Global\\ca2::fontopus::ccvotagus_ca2_spa::7807e510-5579-11dd-ae16-0800200c7784");


   char * szParameters = (char *) ca2_alloc(strlen_dup(pszCommandLine) + 256);
   strcpy_dup(szParameters, "synch_spaadmin:");
   strcat_dup(szParameters, "starter_start:");
   strcat_dup(szParameters, pszCommandLine);
   if(bBackground)
   {
      strcat_dup(szParameters, " background");
   }

   installer(szParameters);

   ca2_free(szParameters);

   return 0;
}




int APIENTRY start_ca2_cube_install(const char * pszCommandLine, bool bBackground)
{

   wait_until_mutex_does_not_exist("Global\\ca2::fontopus::ccvotagus_ca2_spa::7807e510-5579-11dd-ae16-0800200c7784");


   char * szParameters = (char *) ca2_alloc(strlen_dup(pszCommandLine) + 256);
   strcpy_dup(szParameters, "spaadmin:");
   strcat_dup(szParameters, "starter_start:");
   strcat_dup(szParameters, pszCommandLine);
   if(bBackground)
   {
      strcat_dup(szParameters, " background");
   }

   installer(szParameters);

   ca2_free(szParameters);

   return 0;
}




