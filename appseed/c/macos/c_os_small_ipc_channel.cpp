#include "StdAfx.h"
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


bool small_ipc_tx_channel::send(const char * pszMessage)
{

   data_struct data;
   data.mtype        = 15111984;
   data.request      = 1;
   data.size         = strlen_dup(pszMessage);
   if(data.size > 512)
      return false;

   /* The length is essentially the size of the structure minus sizeof(mtype) */
   int length = sizeof(data_struct) - sizeof(long);

   int result;

   if((result = msgsnd(m_iQueue, &data, length, 0)) == -1)
   {
      return false;
   }

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

      int     result, length;

      data_struct data;

      /* The length is essentially the size of the structure minus sizeof(mtype) */
      length = sizeof(data_struct) - sizeof(long);

      if((result = msgrcv(m_iQueue, &data, length, 15111984,  0)) == -1)
      {
         return (void *) -1;
      }

      on_receive(vsstring(data.data, data.size));

   }

   m_bRunning = false;

   return NULL;

}


void * small_ipc_rx_channel::on_receive(const char * psz)
{
   if(m_preceiver != NULL)
   {
       m_preceiver->on_receive(psz);
   }
    return NULL;
}