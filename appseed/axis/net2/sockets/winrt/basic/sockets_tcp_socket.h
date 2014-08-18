/** \file tcp_socket.h
**   \date  2004-02-13
**   \author grymse@alhem.net
**/
/*
Copyright (C) 2004-2007  Anders Hedstrom

This library is made available under the terms of the GNU GPL.

If you would like to use this library in a closed-source application,
a separate license agreement is available. For information about
the closed-source license agreement for the C++ sockets library,
please visit http://www.alhem.net/Sockets/license.html and/or
email license@alhem.net.

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/
#pragma once


#define TCP_BUFSIZE_READ 16400
#define TCP_OUTPUT_CAPACITY 1024000



   namespace sockets
   {


      /** socket implementation for TCP.
      \ingroup basic */
      class CLASS_DECL_AXIS tcp_socket :
         virtual public stream_socket
      {
      public:
#if defined(__cplusplus_winrt)


         class on_connected
         {
         public:
            ::Windows::Foundation::IAsyncAction ^ action;
            ::Windows::Foundation::AsyncStatus status;

         };
#else

         class on_connected;

#endif
         /** \defgroup internal Internal utility */
      protected:
         /** Output buffer struct.
         \ingroup internal */
         struct OUTPUT {
            OUTPUT() : _b(0), _t(0), _q(0) {}
            OUTPUT(const char *buf, size_t len) : _b(0), _t(len), _q(len) {
               memcpy(_buf, buf, len);
            }
            size_t Space() {
               return TCP_OUTPUT_CAPACITY - _t;
            }
            void add(const char *buf, size_t len) {
               memcpy(_buf + _t, buf, len);
               _t += len;
               _q += len;
            }
            size_t remove(size_t len) {
               _b += len;
               _q -= len;
               return _q;
            }
            const char *Buf() {
               return _buf + _b;
            }
            size_t Len() {
               return _q;
            }
            size_t _b;
            size_t _t;
            size_t _q;
            char _buf[TCP_OUTPUT_CAPACITY];
         };
         typedef ::list < OUTPUT *> output_list;

      public:

         //::Windows::Networking::Sockets::StreamSocket ^ m_tcpsocket;
         //
         bool m_b_input_buffer_disabled;
         uint64_t m_bytes_sent;
         uint64_t m_bytes_received;
#ifdef SOCKETS_DYNAMIC_TEMP
         char *m_buf; ///< temporary read buffer
#endif
         output_list m_obuf; ///< output buffer
         OUTPUT *m_obuf_top; ///< output buffer on top
         size_t m_transfer_limit;
         size_t m_output_length;

         //static   SSLInitializer m_ssl_init;
//         SSL_CTX *m_ssl_ctx; ///< ssl context
//         SSL *m_ssl; ///< ssl 'socket'
//         BIO *m_sbio; ///< ssl bio
         string m_password; ///< ssl password

         int m_socks4_state; ///< socks4 support
         char m_socks4_vn; ///< socks4 support, temporary var
         char m_socks4_cd; ///< socks4 support, temporary var
         unsigned short m_socks4_dstport; ///< socks4 support
         unsigned long m_socks4_dstip; ///< socks4 support

         int m_resolver_id; ///< Resolver id (if any) for current open call

         bool m_bReconnect; ///< Reconnect on lost connection flag
         bool m_bTryingReconnect; ///< Trying to reconnect
         string m_strHost;

      public:

         bool m_bCertCommonNameCheckEnabled;

//         sp(ssl_client_context)     m_spsslclientcontext;
  //       string                     m_strInitSSLClientContext;

         /** Constructor with standard values on input/output buffers. */
         tcp_socket(base_socket_handler& );
         /** Constructor with custom values for i/o buffer.
         \param h base_socket_handler reference
         \param isize Input buffer size
         \param osize Output buffer size */
         tcp_socket(base_socket_handler& h,size_t isize,size_t osize);
         ~tcp_socket();

         /** open a connection to a remote server.
         If you want your socket to connect to a server,
         always call open before add'ing a socket to the sockethandler.
         If not, the connection attempt will not be monitored by the
         socket handler...
         \param ip IP address
         \param port Port number
         \param skip_socks Do not use socks4 even if configured */
         //bool open(ipaddr_t ip,port_t port,bool skip_socks = false);
         /** open connection.
         \param ip Ipv6 address
         \param port Port number
         \param skip_socks Do not use socks4 even if configured */
         //bool open(in6_addr ip,port_t port,bool skip_socks = false);
         bool open(const ::net::address & address, bool skip_socks = false);
         bool open(const ::net::address & address, const ::net::address & bind_address, bool skip_socks = false);
         /** open connection.
         \param host Hostname
         \param port Port number */
         bool open(const string & host, port_t port);

         /** Connect timeout callback. */
         void OnConnectTimeout();
#ifdef _WIN32
         /** Connection failed reported as exception on win32 */
         void OnException();
#endif

         /** close file descriptor - internal use only.
         \sa SetCloseAndDelete */
         void close();

         /** Send a string.
         \param s string to send
         \param f Dummy flags -- not used */
         //void Send(const string &s,int f = 0);
         /** Send string using printf formatting. */
         //void Sendf(const char *format, ...);
         /** Send buffer of bytes.
         \param buf buffer pointer
         \param len Length of data
         \param f Dummy flags -- not used */
         using stream_socket::write;
      virtual void write(const void * lpBuf, ::primitive::memory_size nCount);
         /** This callback is executed after a successful read from the socket.
         \param buf Pointer to the data
         \param len Length of the data */
         virtual void OnRawData(char *buf,size_t len);

         /** Called when output buffer has been sent.
         Note: Will only be called IF the output buffer has been used.
         Send's that was successful without needing the output buffer
         will not generate a call to this method. */
         virtual void OnWriteComplete();
         /** Number of bytes in input buffer. */
         size_t GetInputLength();
         /** Number of bytes in output buffer. */
         size_t GetOutputLength();

         /** Callback fires when a socket in line protocol has read one full line.
         \param line Line read */
         void OnLine(const string & line);
         /** get counter of number of bytes received. */
         uint64_t GetBytesReceived(bool clear = false);
         /** get counter of number of bytes sent. */
         uint64_t GetBytesSent(bool clear = false);

         /** Socks4 specific callback. */
         void OnSocks4Connect();
         /** Socks4 specific callback. */
         void OnSocks4ConnectFailed();
         /** Socks4 specific callback.
         \return 'need_more' */
         bool OnSocks4Read();

         /** Callback executed when resolver thread has finished a resolve request. */
         void OnResolved(int id, const ::net::address & addr);
         //void OnResolved(int id,in6_addr& a,port_t port);
         /** Callback for 'New' ssl support - replaces SSLSocket. Internal use. */
         void OnSSLConnect();
         /** Callback for 'New' ssl support - replaces SSLSocket. Internal use. */
         void OnSSLAccept();
         /** This method must be implemented to initialize
         the ssl context for an outgoing connection. */
         virtual void InitSSLClient();
         /** This method must be implemented to initialize
         the ssl context for an incoming connection. */
         virtual void InitSSLServer();

         /** Flag that says a broken connection will try to reconnect. */
         void SetReconnect(bool = true);
         /** Check reconnect on lost connection flag status. */
         bool Reconnect();
         /** Flag to determine if a reconnect is in progress. */
         void SetIsReconnect(bool x = true);
         /** socket is reconnecting. */
         bool IsReconnect();

         void DisableInputBuffer(bool = true);

         void OnOptions(int,int,int,SOCKET);

         void SetLineProtocol(bool = true);

         // TCP options
         bool SetTcpNodelay(bool = true);

         virtual int Protocol();

         /** Trigger limit for callback OnTransferLimit. */
         void SetTransferLimit(size_t sz);
         /** This callback fires when the output buffer drops below the value
         set by SetTransferLimit. Default: 0 (disabled). */
         virtual void OnTransferLimit();

         tcp_socket(const tcp_socket& );
         void OnRead();
         virtual void on_read(const void * buf, ::primitive::memory_size n );
         void OnWrite();


//         virtual long cert_common_name_check(const char * common_name);
  //       virtual void enable_cert_common_name_check(bool bEnable = true);

         /** SSL; Initialize ssl context for a client socket.
         \param meth_in SSL method */
//         void InitializeContext(const string & context, const SSL_METHOD *meth_in = NULL);
         /** SSL; Initialize ssl context for a server socket.
         \param keyfile Combined private key/certificate file
         \param password Password for private key
         \param meth_in SSL method */
  //       void InitializeContext(const string & context, const string & keyfile, const string & password, const SSL_METHOD *meth_in = NULL);
         /** SSL; Initialize ssl context for a server socket.
         \param certfile Separate certificate file
         \param keyfile Combined private key/certificate file
         \param password Password for private key
         \param meth_in SSL method */
    //     void InitializeContext(const string & context, const string & certfile, const string & keyfile, const string & password, const SSL_METHOD *meth_in = NULL);
         /** SSL; Password callback method. */
      //   static   int SSL_password_cb(char *buf,int num,int rwflag,void *userdata);
         /** SSL; get pointer to ssl context structure. */
//         virtual SSL_CTX *GetSslContext();
         /** SSL; get pointer to ssl structure. */
  //       virtual SSL *GetSsl();
         /** ssl; still negotiating connection. */
         bool SSLNegotiate();
         /** SSL; get ssl password. */
         const string & GetPassword();


         void OnConnected(on_connected & connected);

         ::file::circular_buffer ibuf; ///< Circular input buffer
      public:

         virtual string get_url();

         string m_strUrl;

      private:
         tcp_socket& operator=(const tcp_socket& ) { return *this; }

         /** the actual send() */
         int TryWrite(const char *buf, size_t len);
         /** add data to output buffer top */
         void buffer(const char *buf, size_t len);


      };


   } // namespace sockets



