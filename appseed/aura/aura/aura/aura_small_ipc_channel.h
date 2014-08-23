#pragma once

#ifdef APPLEOS
typedef int32_t key_t;
#elif defined(LINUX)
typedef __key_t key_t;
#elif defined(ANDROID)
#else
//#include "ca_mutex.h"
#endif


class CLASS_DECL_AURA small_ipc_channel_base
{
public:

#ifdef WINDOWS
   oswindow        m_oswindow;
#else
   key_t   m_key;
   int32_t      m_iQueue;

   struct data_struct
   {
      long     mtype;          /* Message type */
      int32_t      request;        /* Work request number */
      int32_t      size;
      char     data[512];
   } msg;
#endif
   string m_strKey;


   small_ipc_channel_base();
   virtual ~small_ipc_channel_base();


};




class CLASS_DECL_AURA small_ipc_tx_channel :
   virtual public  small_ipc_channel_base
{
public:


   bool open(const char * pszKey, launcher * plauncher = NULL);
   bool close();


   bool send(const char * pszMessage, uint32_t dwTimeout);
   bool send(int32_t message, void * pdata, int32_t len, uint32_t dwTimeout);


   bool is_tx_ok();

};




class CLASS_DECL_AURA small_ipc_rx_channel :
   virtual public  small_ipc_channel_base
{
public:

   class CLASS_DECL_AURA receiver
   {
   public:

      virtual void on_receive(small_ipc_rx_channel * prxchannel, const char * pszMessage);
      virtual void on_receive(small_ipc_rx_channel * prxchannel, int32_t message, void * pdata, int32_t len);
      virtual void on_post(small_ipc_rx_channel * prxchannel, int64_t a, int64_t b);

   };

   receiver *        m_preceiver;

#ifdef WINDOWS
   string          m_strWindowProcModule;
#else
   bool              m_bRunning;
   bool              m_bRun;
   pthread_t         m_thread;
#endif


   small_ipc_rx_channel();
   virtual ~small_ipc_rx_channel();


#ifdef WINDOWS
   bool create(const char * pszKey, const char * pszWindowProcModule);
#else
   bool create(const char * pszKey);
#endif
   bool destroy();


   virtual void * on_receive(small_ipc_rx_channel * prxchannel, const char * pszMessage);
   virtual void * on_receive(small_ipc_rx_channel * prxchannel, int32_t message, void * pdata, int32_t len);
   virtual void * on_post(small_ipc_rx_channel * prxchannel, int64_t a, int64_t b);


   virtual bool on_idle();

#ifdef WINDOWS
   ATOM register_class(HINSTANCE hInstance);
   static LRESULT CALLBACK s_message_queue_proc(oswindow oswindow, UINT message, WPARAM wParam, LPARAM lParam);
   LRESULT message_queue_proc(UINT message, WPARAM wParam, LPARAM lParam);
#else
   bool start_receiving();
#ifndef SOLARIS
   static void * receive_proc(void * param);
#endif
   void * receive();
#endif

   bool is_rx_ok();

};




class CLASS_DECL_AURA small_ipc_channel :
   virtual public small_ipc_tx_channel,
   virtual public small_ipc_rx_channel::receiver
{
public:


   small_ipc_rx_channel       m_rxchannel;
   string                   m_vssChannel;
   uint32_t                      m_dwTimeout;


   small_ipc_channel();

#ifdef WINDOWS
   bool open_ab(const char * pszKey, const char * pszModule, launcher * plauncher = NULL);
   bool open_ba(const char * pszKey, const char * pszModule, launcher * plauncher = NULL);
#else
   bool open_ab(const char * pszKey, launcher * plauncher = NULL);
   bool open_ba(const char * pszKey, launcher * plauncher = NULL);
#endif
   bool close();

   virtual void restart_small_ipc_channel();

   bool ensure_tx(const char * pszMessage, uint32_t dwTimeout = INFINITE);
   bool ensure_tx(int32_t message, void * pdata, int32_t len, uint32_t dwTimeout = INFINITE);


   bool is_rx_tx_ok();


};

