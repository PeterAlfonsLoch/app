#include "framework.h"


small_ipc_channel::small_ipc_channel()
{
   
   m_dwTimeout = (1984 + 1977) * 11;

}



bool small_ipc_channel::open_ab(const char * pszKey, const char * pszModule, launcher * plauncher)
{

   m_vssChannel = pszKey;

   m_rxchannel.m_preceiver = this;

   vsstring strChannelRx = m_vssChannel + "-a";
   vsstring strChannelTx = m_vssChannel + "-b";


   if(!m_rxchannel.create(strChannelRx, pszModule))
   {
      return false;
   }

   if(!small_ipc_tx_channel::open(strChannelTx, plauncher))
   {
      return false;
   }

   return true;

}

bool small_ipc_channel::open_ba(const char * pszKey, const char * pszModule, launcher * plauncher)
{

   m_vssChannel = pszKey;

   m_rxchannel.m_preceiver = this;

   vsstring strChannelRx = m_vssChannel + "-b";
   vsstring strChannelTx = m_vssChannel + "-a";


   if(!m_rxchannel.create(strChannelRx, pszModule))
   {
      return false;
   }

   if(!small_ipc_tx_channel::open(strChannelTx, plauncher))
   {
      return false;
   }

   return true;

}


bool small_ipc_channel::close()
{

   small_ipc_tx_channel::close();

   m_rxchannel.destroy();

   return true;

}

void small_ipc_channel::restart()
{
}



// calls restart if confirm_tx failed
bool small_ipc_channel::ensure_tx(const char * pszMessage, DWORD dwTimeout)
{

   if(dwTimeout == INFINITE)
      dwTimeout = m_dwTimeout;

   if(!send(pszMessage, dwTimeout))
   {

      restart();

      return false;

   }

   return true;

}


bool small_ipc_channel::ensure_tx(int message, void * pdata, int len, DWORD dwTimeout)
{

   if(dwTimeout == INFINITE)
      dwTimeout = m_dwTimeout;

   if(!send(message, pdata, len, dwTimeout))
   {

      restart();

      return false;

   }

   return true;

}
