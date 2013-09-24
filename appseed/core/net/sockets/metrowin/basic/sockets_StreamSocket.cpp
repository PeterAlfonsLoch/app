#include "framework.h"


namespace sockets
{

   stream_socket::stream_socket(base_socket_handler& h) : 
      element(h.get_app()),
      base_socket(h),
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
      if(m_streamsocket != nullptr)
      {
         //m_streamsocket->Close();

      }
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
      if (GetSocket() != INVALID_SOCKET && !Connecting() && !CloseAndDelete())
         return true;
      return false;
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
      Handler().AddList(GetSocket(), LIST_CALLONCONNECT, x);
      m_call_on_connect = x;
   }


   bool stream_socket::CallOnConnect()
   {
      return m_call_on_connect;
   }


   void stream_socket::SetRetryClientConnect(bool x)
   {
      Handler().AddList(GetSocket(), LIST_RETRY, x);
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


   port_t stream_socket::GetRemotePort()
   {

      return System.net().service_port(m_streamsocket->Information->RemotePort);

   }
   
   
   address stream_socket::GetRemoteAddress()
   {

      return address(get_app(), m_streamsocket->Information->RemoteAddress->CanonicalName, m_streamsocket->Information->RemotePort);

   }


   port_t stream_socket::GetLocalPort()
   {

      return System.net().service_port(m_streamsocket->Information->LocalPort);

   }
     

   address stream_socket::GetLocalAddress()
   {

      return address(get_app(), m_streamsocket->Information->LocalAddress->CanonicalName, m_streamsocket->Information->LocalPort);

   }


   bool stream_socket::is_connecting()
   {
      return m_bConnecting;
   }


} // namespace sockets

