#pragma once


namespace sockets
{

   class Ajp13Socket : public AjpBaseSocket
   {
   public:
      Ajp13Socket(base_socket_handler& h);

      void OnHeader( short id, short len );
      void OnPacket( const char *buf, size_t sz );

      virtual void Respond();

      void OnTransferLimit();

      virtual void OnExecute() = 0;
      virtual void OnResponseComplete();

   private:
      void ReceiveBody( const char *buf, size_t sz );
      void ReceiveForwardRequest( const char *buf, size_t sz );
      void ReceiveShutdown( const char *buf, size_t sz );
      void ReceivePing( const char *buf, size_t sz );
      void ReceiveCPing( const char *buf, size_t sz );
      void Execute();

      size_t m_body_size_left;
      http::request m_request;
      http::response m_response;
   };


} // namespace sockets

