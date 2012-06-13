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

bool small_ipc_channel::confirm_tx(const char * pszMessage, DWORD dwTimeout)
{
   
   m_rxchannel.prepare_wait();
   
   send(pszMessage);

   if(dwTimeout == INFINITE)
      dwTimeout = m_dwTimeout;
   
   return m_rxchannel.wait(dwTimeout);

}


bool small_ipc_channel::confirm_tx(int message, void * pdata, int len, DWORD dwTimeout)
{
   
   m_rxchannel.prepare_wait(message);
   
   send(message, pdata, len);

   if(dwTimeout == INFINITE)
      dwTimeout = m_dwTimeout;

   return m_rxchannel.wait(message, dwTimeout);

}




// calls restart if confirm_tx failed
bool small_ipc_channel::ensure_tx(const char * pszMessage, DWORD dwTimeout)
{

   if(!confirm_tx(pszMessage, dwTimeout))
   {

      restart();

      return false;

   }

   return true;

}


bool small_ipc_channel::ensure_tx(int message, void * pdata, int len, DWORD dwTimeout)
{

   if(!confirm_tx(message, pdata, len, dwTimeout))
   {

      restart();

      return false;

   }

   return true;

}
