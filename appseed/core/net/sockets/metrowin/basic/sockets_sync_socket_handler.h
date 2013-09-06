#pragma once


namespace sockets
{


   class CLASS_DECL_ca2 sync_socket_handler :
      virtual public ::ca2::object,
      public socket::callback
   {
   public:


      socket *                      m_psocket;
      ::primitive::memory_file      m_file;
      socket_handler                m_handler;
      int                           m_iDefaultTimeout;

      sync_socket_handler(::ca2::application * papp, StdLog *log = NULL);
      virtual ~sync_socket_handler();



      virtual void OnRawData(socket * psocket, void * pdata, size_t len);

      void handle(socket * psocket);

      virtual void write(string & str);
      virtual void write(void * pdata, ::primitive::memory_size len);
      virtual ::primitive::memory_size read(void * pdata, ::primitive::memory_size len);
      virtual string read_line();
      virtual string read_string();


      virtual void read_payload_v1(string & strPayload, int timeout = -1);
      virtual void write_payload_v1(const char * szPayload, int timeout = -1);

   };


} // namespace sockets






