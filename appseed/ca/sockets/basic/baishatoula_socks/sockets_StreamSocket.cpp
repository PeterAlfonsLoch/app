#include "framework.h"


namespace sockets
{


   stream_socket::stream_socket(socket_handler_base& h) : 
      ::ca::ca(h.get_app()),
      socket(h)
   ,m_bConnecting(false)
   ,m_connect_timeout(5)
   ,m_flush_before_close(true)
   ,m_connection_retry(0)
   ,m_retries(0)
   ,m_call_on_connect(false)
   ,m_b_retry_connect(false)
   ,m_shutdown(0)
   {
   }


   stream_socket::~stream_socket()
   {
   }


   SOCKET stream_socket::CreateSocket(int af, int type,const string & protocol)
   {

      m_streamsocket = ref new ::Windows::Networking::Sockets::StreamSocket;

      return m_streamsocket;

   }

   int stream_socket::close_socket()
   {

      m_streamsocket->Close();

      return 0;

   }


   void stream_socket::SetConnecting(bool x)
   {
      if (x != m_bConnecting)
      {
         m_bConnecting = x;
         if (x)
         {
            SetTimeout( GetConnectTimeout() );
         }
         else
         {
            SetTimeout( 0 );
         }
      }
   }


   bool stream_socket::Connecting()
   {
      return m_bConnecting;
   }


   bool stream_socket::Ready()
   {
#ifdef BSD_STYLE_SOCKETS
      if (GetSocket() != INVALID_SOCKET && !Connecting() && !CloseAndDelete())
         return true;
      return false;
#else
      return true;
#endif
   }


   void stream_socket::SetConnectTimeout(int x)
   {
      m_connect_timeout = x;
   }


   int stream_socket::GetConnectTimeout()
   {
      return m_connect_timeout;
   }


   void stream_socket::SetFlushBeforeClose(bool x)
   {
      m_flush_before_close = x;
   }


   bool stream_socket::GetFlushBeforeClose()
   {
      return m_flush_before_close;
   }


   int stream_socket::GetConnectionRetry()
   {
      return m_connection_retry;
   }


   void stream_socket::SetConnectionRetry(int x)
   {
      m_connection_retry = x;
   }


   int stream_socket::GetConnectionRetries()
   {
      return m_retries;
   }


   void stream_socket::IncreaseConnectionRetries()
   {
      m_retries++;
   }


   void stream_socket::ResetConnectionRetries()
   {
      m_retries = 0;
   }


   void stream_socket::SetCallOnConnect(bool x)
   {
#ifndef METROWIN
      Handler().AddList(GetSocket(), LIST_CALLONCONNECT, x);
#endif
      m_call_on_connect = x;
   }


   bool stream_socket::CallOnConnect()
   {
      return m_call_on_connect;
   }


   void stream_socket::SetRetryClientConnect(bool x)
   {
#ifndef METROWIN
      Handler().AddList(GetSocket(), LIST_RETRY, x);
#endif
      m_b_retry_connect = x;
   }


   bool stream_socket::RetryClientConnect()
   {
      return m_b_retry_connect;
   }




   void stream_socket::SetShutdown(int x)
   {
      m_shutdown = x;
   }


   int stream_socket::GetShutdown()
   {
      return m_shutdown;
   }


} // namespace sockets




