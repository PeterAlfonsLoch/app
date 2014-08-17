#pragma once


namespace sockets
{

   class Ajp13Socket : public AjpBaseSocket
   {
   public:
      Ajp13Socket(base_socket_handler& h);

      void OnHeader( int16_t id, int16_t len );
      void OnPacket( const char *buf, primitive::memory_size sz );

      virtual void Respond();

      void OnTransferLimit();

      virtual void OnExecute() = 0;
      virtual void OnResponseComplete();

   private:
      void ReceiveBody( const char *buf, primitive::memory_size sz );
      void ReceiveForwardRequest( const char *buf, primitive::memory_size sz );
      void ReceiveShutdown( const char *buf, primitive::memory_size sz );
      void ReceivePing( const char *buf, primitive::memory_size sz );
      void ReceiveCPing( const char *buf, primitive::memory_size sz );
      void Execute();

      primitive::memory_size m_body_size_left;
      http::request m_request;
      http::response m_response;
   };


} // namespace sockets

