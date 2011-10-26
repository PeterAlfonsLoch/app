#include "StdAfx.h"

CLASS_DECL_____ bool send_short_message_to_installer(const char * psz, bool bLaunch);
CLASS_DECL_____ void installer_call_sync(const char * path, const char * param);

CLASS_DECL_____ char * szSpabootInstall = NULL;


int installer(const char * param)
{

   installer_call_sync(szSpabootInstall, param);

   return 0;

}




void installer_call_sync(const char * path, const char * param)
{

   bool bLaunch;

   if(stricmp_dup(param, "exit") == 0
   || stricmp_dup(param, "quit") == 0)
   {
      bLaunch = false;
   }
   else
   {
      bLaunch = true;
   }

   send_short_message_to_installer(param, bLaunch);

}





CLASS_DECL_____ bool send_short_message_to_installer(const char * psz, bool bLaunch)
{
   
   small_ipc_tx_channel txchannel;
   
   spa::installer::launcher launcher;

   if(!txchannel.open("ca2/fontopus/ccvotagus/spaboot_install", bLaunch ? &launcher : NULL)) 
      return false;

   txchannel.send(psz);

   return true;

}


void send_spaboot_install_response(const char * param)
{

   small_ipc_tx_channel txchannel;
   
   spa::installer::launcher launcher;

   if(!txchannel.open("ca2/fontopus/ccvotagus/spaboot_install_callback")) 
      return;

   txchannel.send(param);

}
