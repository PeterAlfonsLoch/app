#pragma once


namespace sockets
{

   class Ajp13Socket : public AjpBaseSocket
   {
   public:

      memory_size_t m_body_size_left;
      http::request m_request;
      http::response m_response;


      Ajp13Socket(base_socket_handler& h);

      void OnHeader( int16_t id, int16_t len );
      void OnPacket( const char *buf, memory_size_t sz );

      virtual void Respond();

      void OnTransferLimit();

      virtual void OnExecute() = 0;
      virtual void OnResponseComplete();

      void ReceiveBody( const char *buf, memory_size_t sz );
      void ReceiveForwardRequest( const char *buf, memory_size_t sz );
      void ReceiveShutdown( const char *buf, memory_size_t sz );
      void ReceivePing( const char *buf, memory_size_t sz );
      void ReceiveCPing( const char *buf, memory_size_t sz );
      void Execute();

   };


} // namespace sockets

