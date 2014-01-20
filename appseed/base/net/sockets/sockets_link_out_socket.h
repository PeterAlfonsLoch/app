#pragma once


namespace sockets
{


   class link_in_socket;

   class CLASS_DECL_BASE link_out_socket : public tcp_socket
   {
   public:

      link_out_socket(base_socket_handler & h);
      virtual ~link_out_socket();

      virtual void OnRead( char *buf, size_t n );
      void link_write(void * p, size_t size);


      void server_to_link_out(httpd_socket * psocket);

      link_in_socket * m_in;
      socket * m_out;
   };



} // namespace sockets


