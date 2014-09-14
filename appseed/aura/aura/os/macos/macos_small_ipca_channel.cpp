#include "framework.h"
#include <sys/ipc.h>
#include <sys/msg.h>
#include <pthread.h>


small_ipc_channel_base::small_ipc_channel_base()
{
   m_key = 0;
   m_iQueue = -1;
}

small_ipc_channel_base::~small_ipc_channel_base()
{
}



bool small_ipc_tx_channel::open(const char * pszKey, launcher * plauncher)
{
   
   if(m_iQueue >= 0)
      close();
   
   m_key = ftok(".", 'c');
   
   if(m_key == 0)
      return false;
   
   if((m_iQueue = msgget(m_key, 0660)) == -1)
   {
      return false;
   }
   
   m_strKey = pszKey;
   
   return true;
   
}

bool small_ipc_tx_channel::close()
{
   
   if(m_iQueue < 0)
      return true;
   
   m_iQueue = -1;
   
   m_strKey = "";
   
   return true;
   
}


bool small_ipc_tx_channel::send(const char * pszMessage, DWORD dwTimeout)
{
   
   ::count c = strlen_dup(pszMessage);
   
   ::count cSend;
   
   data_struct data;
   data.mtype        = 15111984;
   data.request      = 0x80000000;
   data.size         = (int)strlen_dup(pszMessage);
   
   ::count cPos = 0;
   
   while(c > 0)
   {
      
      cSend = MIN(c, 511);
   
      memcpy(data.data, &pszMessage[cPos], MIN(c, 511));
   
      c -= cSend;
      
      cPos += cSend;
      
      if(c > 0)
         data.size = 512;
      else
         data.size = (int) cSend;
      
      /* The length is essentially the size of the structure minus sizeof(mtype) */
      int length = sizeof(data_struct) - sizeof(long);
   
      int result;
   
      if((result = msgsnd(m_iQueue, &data, length, 0)) == -1)
      {
         return false;
      }
      
   }
   
   return true;
   
}


bool small_ipc_tx_channel::send(int message, void * pdata, int len, DWORD dwTimeout)
{
   
   if(message == 0x80000000)
      return false;
   
   
   if(!is_tx_ok())
      return false;
   
   const char * pszMessage = (const char *) pdata;
   
   ::count c = len;
   
   ::count cSend;
   
   data_struct data;
   data.mtype        = 15111984;
   data.request      = 0x80000000;
   data.size         = (int)strlen_dup(pszMessage);
   
   ::count cPos = 0;
   
   while(c > 0)
   {
      
      cSend = MIN(c, 511);
      
      memcpy(data.data, &pszMessage[cPos], MIN(c, 511));
      
      c -= cSend;
      
      cPos += cSend;
      
      if(c > 0)
         data.size = 512;
      else
         data.size = (int) cSend;
      
      /* The length is essentially the size of the structure minus sizeof(mtype) */
      int length = sizeof(data_struct) - sizeof(long);
      
      int result;
      
      if((result = msgsnd(m_iQueue, &data, length, 0)) == -1)
      {
         return false;
      }
      
   }
   
   return true;
   
}



bool small_ipc_tx_channel::is_tx_ok()
{
   
   return m_iQueue != -1;

}




small_ipc_rx_channel::small_ipc_rx_channel()
{

   m_preceiver    = NULL;

}


small_ipc_rx_channel::~small_ipc_rx_channel()
{

}



bool small_ipc_rx_channel::create(const char * pszKey)
{
   m_key = ftok(".", 'c');
   
   if(m_key == 0)
      return false;
   
   if((m_iQueue = msgget(m_key, IPC_CREAT | IPC_EXCL | 0660 )) == -1)
   {
      return false;
   }
   
   return true;
}


bool small_ipc_rx_channel::destroy()
{
   
   int iRetry = 23;
   while(m_bRunning && iRetry > 0)
   {
      m_bRun = false;
      Sleep(1000);
      iRetry--;
   }
   
   if(m_iQueue < 0)
      return true;
   
   if(msgctl( m_iQueue, IPC_RMID, 0) == -1)
   {
      return false;
   }
   
   m_iQueue = -1;
   
   return true;
   
}

bool small_ipc_rx_channel::start_receiving()
{
   
   m_bRunning = true;
   
   m_bRun = true;
   
   if(pthread_create(&m_thread, NULL, &small_ipc_rx_channel::receive_proc, this) != 0)
   {
      
      m_bRunning = false;
      
      m_bRun = false;
      
      return false;
      
   }
   
   return true;
   
}

void * small_ipc_rx_channel::receive_proc(void * param)
{
   
   small_ipc_rx_channel * pchannel = (small_ipc_rx_channel *) param;
   
   return pchannel->receive();
   
}

void small_ipc_rx_channel::receiver::on_receive(small_ipc_rx_channel * prxchannel, const char * pszMessage)
{
}

void small_ipc_rx_channel::receiver::on_receive(small_ipc_rx_channel * prxchannel, int message, void * pdata, int len)
{
}

void small_ipc_rx_channel::receiver::on_post(small_ipc_rx_channel * prxchannel, int64_t a, int64_t b)
{
}



void * small_ipc_rx_channel::on_receive(small_ipc_rx_channel * prxchannel, const char * pszMessage)
{
   
   if(m_preceiver != NULL)
   {
      m_preceiver->on_receive(prxchannel, pszMessage);
   }
   
   // ODOW - on date of writing : return ignored by this windows implementation
   
   return NULL;
   
}

void * small_ipc_rx_channel::on_receive(small_ipc_rx_channel * prxchannel, int message, void * pdata, int len)
{
   
   if(m_preceiver != NULL)
   {
      m_preceiver->on_receive(prxchannel, message, pdata, len);
   }
   
   // ODOW - on date of writing : return ignored by this windows implementation
   
   return NULL;
   
}


void * small_ipc_rx_channel::on_post(small_ipc_rx_channel * prxchannel, int64_t a, int64_t b)
{
   
   if(m_preceiver != NULL)
   {
      m_preceiver->on_post(prxchannel, a, b);
   }
   
   // ODOW - on date of writing : return ignored by this windows implementation
   
   return NULL;
   
}



bool small_ipc_rx_channel::on_idle()
{
   
   return false;
   
}


bool small_ipc_rx_channel::is_rx_ok()
{
   
   return m_iQueue != -1;
}



void * small_ipc_rx_channel::receive()
{
   
   while(m_bRun)
   {
      
      m_bRunning = true;
      
      ssize_t  result;
      
      int length;
      
      data_struct data;
      
      /* The length is essentially the size of the structure minus sizeof(mtype) */
      length = sizeof(data_struct) - sizeof(long);
      
      ::primitive::memory mem;
      
      do
      {
         
         if((result = msgrcv(m_iQueue, &data, length, 15111984, IPC_NOWAIT)) == -1)
         {
            
            if(errno == ENOMSG)
            {
               if(!on_idle())
               {
                  Sleep(84 * 1000);
               }
            }
            else
            {
               return (void *) -1;
            }
            
         }
         
         mem.append(data.data, data.size);
         
         
         if(data.size < 512)
            break;
         
      }
      while(true);
      
      
      if(data.request == 0)
      {
         
         on_receive(this, mem.to_string());
         
      }
      else
      {
         
         on_receive(this, data.request, mem.get_data(), (int) mem.get_size());
         
      }
      
   }
   
   m_bRunning = false;
   
   return NULL;
   
}



bool small_ipc_channel::open_ab(const char * pszKey, launcher * plauncher)
{
   
   m_vssChannel = pszKey;
   
   m_rxchannel.m_preceiver = this;
   
   string strChannelRx = m_vssChannel + "-a";
   string strChannelTx = m_vssChannel + "-b";
   
   
   if(!m_rxchannel.create(strChannelRx))
   {
      return false;
   }
   
   if(!small_ipc_tx_channel::open(strChannelTx, plauncher))
   {
      return false;
   }
   
   return true;
   
}

bool small_ipc_channel::open_ba(const char * pszKey, launcher * plauncher)
{
   
   m_vssChannel = pszKey;
   
   m_rxchannel.m_preceiver = this;
   
   string strChannelRx = m_vssChannel + "-b";
   string strChannelTx = m_vssChannel + "-a";
   
   
   if(!m_rxchannel.create(strChannelRx))
   {
      return false;
   }
   
   if(!small_ipc_tx_channel::open(strChannelTx, plauncher))
   {
      return false;
   }
   
   return true;
   
}


bool small_ipc_channel::is_rx_tx_ok()
{
   
   return m_rxchannel.is_rx_ok() && is_tx_ok();
   
}

