#include "install_spaboot.h"


const char * calc_id();


int spaboot_start()
{

   int iRetry = 0;
   while(iRetry < 5)
   {
      update_spa_installed();
      if(is_spa_installed())
      {  
         break;
      }
      call_self_privileged_sync("-install_spaboot");
      iRetry++;
   }
   if(!is_spa_installed())
   {  
      return 1;
   }

   iRetry = 0;
   while(iRetry < 5)
   {
      update_spa_updated();
      if(is_spa_updated())
      {  
         break;
      }
      call_self_privileged_sync("-install_spaboot");
      iRetry++;
   }
   if(!is_spa_updated())
   {  
      return 1;
   }

   const char * id = calc_id();
   if(id == NULL)
      id = "install_spaboot";

   iRetry = 0;
   while(iRetry < 5)
   {
      update_ca2_installed();
      if(is_ca2_installed())
      {  
         break;
      }
      starter_start(id);
      iRetry++;
   }
   if(!is_ca2_installed())
   {  
      return 1;
   }

   iRetry = 0;
   while(iRetry < 5)
   {
      update_ca2_updated();
      if(is_ca2_updated())
      {  
         break;
      }
      starter_start(id);
      iRetry++;
   }
   if(!is_ca2_updated())
   {  
      return 1;
   }

   if(stricmp_dup(id, "install_spaboot"))
   {
      cube_run(id);
   }



   return 0;

}




const char * calc_id()
{

   char szModulePath[MAX_PATH * 3];
   ::GetModuleFileNameA((HINSTANCE) NULL, szModulePath, sizeof(szModulePath));
   return read_resource_as_string_dup(::GetModuleHandleA(szModulePath), 1984, "CGCL");

}
