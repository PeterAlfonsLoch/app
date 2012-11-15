#pragma once


namespace bsd
{


   namespace sockets
   {

      class CLASS_DECL_ca http_tunnel :
         virtual public http_socket
      {
      public:
         enum estate
         {
            state_initial,
            state_connect_sent,
            state_proxy_ok,
            state_init_ssl,
         };
         http_tunnel(socket_handler_base & h);
         string      m_strProxy;
         int         m_iProxyPort;
         bool        m_bSslTunnel;
         bool        m_bOk ;
         string m_host; ///< Hostname from url_in
         port_t m_port; ///< Port from url_in
         stringa   m_straProxy;
         estate      m_estate;
         string      m_strRequest;
         primitive::memory      m_memoryBody;
         primitive::memory      m_memoryBuf;
         gen::memory_file m_fileBody;
         int         m_iContentLength;
         bool        m_bHeaders;
         bool        m_bDirect;
         string      m_strPasswordFile;
         string      m_strUserNameFile;

         virtual const string & GetUrlHost();
         /** get port from url. */
         virtual port_t GetUrlPort();


         virtual bool open(bool bConfigProxy = true);



         void OnConnect();

         void OnLine(const string & strParam);

         virtual void step();

         virtual void OnFirst();
         virtual void OnHeader(const string &, const string &);
         virtual void OnHeaderComplete();
         virtual void OnData(const char * psz, size_t size);

      };

   } // namespace sockets



} // namespace bsd



