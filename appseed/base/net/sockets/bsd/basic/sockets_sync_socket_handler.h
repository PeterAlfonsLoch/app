#pragma once


namespace sockets
{

   
   class CLASS_DECL_BASE sync_socket_handler : 
      virtual public ::object,
      public socket::callback
   {
   public:


      socket *                m_psocket;
      ::file::memory_buffer   m_file;
      socket_handler          m_handler;
      int32_t                 m_iDefaultTimeout;

      
      sync_socket_handler(sp(::aura::application) papp, logger *log = NULL);
      virtual ~sync_socket_handler();


      using ::sockets::socket::callback::OnRawData;
      virtual void OnRawData(socket * psocket, void * pdata, size_t len);

      void handle(socket * psocket);

      virtual void write(string & str);
      virtual void write(const void * pdata, int32_t len);
      virtual int32_t read(void * pdata, int32_t len);
      virtual string read_line();
      virtual string read_string();


      virtual void read_payload_v1(string & strPayload, int32_t timeout = -1);
      virtual void write_payload_v1(const char * szPayload, int32_t timeout = -1);

   };


} // namespace sockets






