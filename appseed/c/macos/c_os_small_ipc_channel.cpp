#include "framework.h"
#include <sys/ipc.h>
#include <sys/msg.h>

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

   data_struct data;
   data.mtype        = 15111984;
   data.request      = 0;
    int iPos = 0;
    int iSize = strlen_dup(pszMessage);
    
    do
    {
  
        data.size         = min(iSize, 512);
 
        /* The length is essentially the size of the structure minus sizeof(mtype) */
        int length = sizeof(data_struct) - sizeof(long);

        int result;

        if((result = msgsnd(m_iQueue, &data, length, 0)) == -1)
        {
            return false;
        }
        iSize -= data.size;
        if(iSize <= 0)
            break;
}
while(true);

   return true;
}


small_ipc_rx_channel::small_ipc_rx_channel()
{
    m_preceiver = NULL;
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
      sleep(1);
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

      simple_memory mem;
       
      do
      {
       
         if((result = msgrcv(m_iQueue, &data, length, 15111984, 0)) == -1)
         {
         
            return (void *) -1;
            
         }
       
         mem.write(data.data, data.size);
      
       
         if(data.size < 512)
            break;
         
      }
      while(true);
       
       
      if(data.request == 0)
      {
         
         on_receive(this, mem.str());
         
      }
      else
      {
         
         on_receive(this, data.request, mem.m_psz, mem.m_iSize);
         
      }

   }

   m_bRunning = false;

   return NULL;

}


void * small_ipc_rx_channel::on_receive(small_ipc_rx_channel * prxchannel, const char * psz)
{
   
   if(m_preceiver != NULL)
   {
      
      m_preceiver->on_receive(prxchannel, psz);
      
   }
   
   return NULL;
   
}

void * small_ipc_rx_channel::on_receive(small_ipc_rx_channel * prxchannel, int message, void * p, int iSize)
{
   
   if(m_preceiver != NULL)
   {
      
      m_preceiver->on_receive(prxchannel, message, p, iSize);
      
   }
   
   return NULL;
   
}

void * small_ipc_rx_channel::on_post(small_ipc_rx_channel * prxchannel, int a, int b)
{
   
   if(m_preceiver != NULL)
   {
      
      m_preceiver->on_post(prxchannel, a, b);
      
   }
   
   return NULL;
   
}



bool small_ipc_channel::open_ab(const char * pszKey, launcher * plauncher)
{
   
   m_vssChannel = pszKey;
   
   m_rxchannel.m_preceiver = this;
   
   vsstring strChannelRx = m_vssChannel + "-a";
   vsstring strChannelTx = m_vssChannel + "-b";
   
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
   
   vsstring strChannelRx = m_vssChannel + "-b";
   vsstring strChannelTx = m_vssChannel + "-a";
   
   
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
