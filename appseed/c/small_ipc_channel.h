#pragma once

#ifdef MACOS
#include <pthread.h>
typedef int key_t;
#elif defined(LINUX) 
typedef __key_t key_t;
#include <pthread.h>
#else
#include "simple_mutex.h"
#endif


class CLASS_DECL_c small_ipc_channel_base
{
public:

#ifdef WINDOWS
   HWND        m_hwnd;
#else
   key_t   m_key;
   int      m_iQueue;

   struct data_struct
   {
      long     mtype;          /* Message type */
      int      request;        /* Work request number */
      int      size;
      char     data[512];
   } msg;
#endif
   vsstring m_strKey;


   small_ipc_channel_base();
   virtual ~small_ipc_channel_base();


};




class CLASS_DECL_c small_ipc_tx_channel :
   virtual public  small_ipc_channel_base
{
public:


   bool open(const char * pszKey, launcher * plauncher = NULL);
   bool close();


   bool send(const char * pszMessage);


};




class CLASS_DECL_c small_ipc_rx_channel :
   virtual public  small_ipc_channel_base
{
public:

   class CLASS_DECL_c receiver
   {
   public:

      virtual void on_receive(const char * pszMessage);

   };

   receiver *        m_preceiver;
#ifdef WINDOWS
   vsstring          m_strWindowProcModule;
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


   virtual void * on_receive(const char * pszMessage);


#ifdef WINDOWS
   ATOM register_class(HINSTANCE hInstance);
   static LRESULT CALLBACK s_message_window_proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
   LRESULT message_window_proc(UINT message, WPARAM wParam, LPARAM lParam);
#else
   bool start_receiving();
   static void * receive_proc(void * param);
   void * receive();
#endif

};

