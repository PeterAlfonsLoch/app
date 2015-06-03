//#include "framework.h"


small_ipc_channel::small_ipc_channel()
{
   
   m_dwTimeout = (5000) * 11;

}





bool small_ipc_channel::close()
{

   small_ipc_tx_channel::close();

   m_rxchannel.destroy();

   return true;

}

void small_ipc_channel::restart_small_ipc_channel()
{
}



// calls restart if confirm_tx failed
bool small_ipc_channel::ensure_tx(const char * pszMessage, unsigned int dwTimeout)
{

   //if(dwTimeout == INFINITE)
   //   dwTimeout = m_dwTimeout;

   if(!send(pszMessage, dwTimeout))
   {

      restart_small_ipc_channel();

      return false;

   }

   return true;

}


bool small_ipc_channel::ensure_tx(int message, void * pdata, int len, unsigned int dwTimeout)
{

   //if(dwTimeout == INFINITE)
   //   dwTimeout = m_dwTimeout;

   if(message == WM_APP + WM_USER)
   {

      if(!is_tx_ok())
      {
      
         restart_small_ipc_channel();

         return false;

      }

   }
   else if(!send(message, pdata, len, dwTimeout))
   {

      restart_small_ipc_channel();

      return false;

   }

   return true;

}


namespace small_ipc_channel
{

   string app_install(string strPlatform = "")
   {

      if(strPlatform.is_empty())
      {

         strPlatform = process_platform_dir_name();

      }
      
      return "::ca2::fontopus::ca2_spaboot_install_" + strPlatform + "::7807e510-5579-11dd-ae16-0800200c7784"

   }



}