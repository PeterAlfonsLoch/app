////////////////////////////////////////////////////////////////////////////////
//
// From David J. Kruglinski (Inside Visual C++).
//
////////////////////////////////////////////////////////////////////////////////

// removed baseclass CObject
// removed baseclass CException
// removed all LPCTSTR LPTSTR
// _select only defined to avoid compiler warning in WIN32
// make it run on linux

#pragma once


//#ifdef WIN32
//#ifdef _WINSOCKAPI_
//#ifndef _WINSOCK2API_
//// NOTICE: In Microsoft Visual Studio you can add the header 'winsock2.h" to 
////         "Configuration --> Properties --> C/C++ --> Advanced --> Forced Include File"
//#pragma message("\nIt is recommended to include 'winsock2.h' instead of 'winsock.h'\n")
//#endif
//#else
//#include <winsock2.h>
//#endif
//#elif defined(unix)
//#include <sys/socket.h>
//#include <arpa/inet.h>   // needed for inet_ntoa and inet_addr
//#include <netdb.h>       // needed for gethostbyname and gethostbyaddr
//#include <errno.h>
//#endif

namespace sockets
{

   //#ifdef WIN32
   //   typedef int socklen_t;
   //   inline int _select(UINT_PTR /*nfds*/, fd_set* readfds, fd_set* writefds, fd_set* exceptfds, const struct timeval* timeout)
   //   {
   //      // The nfds parameter is ignored in windows (included only for 
   //      // compatibility with Berkeley sockets).
   //      return select(0, readfds, writefds, exceptfds, timeout);
   //   }
   //#elif defined(unix)
   //   typedef unsigned int SOCKET;
   //   typedef sockaddr SOCKADDR;
   //   typedef sockaddr* LPSOCKADDR;
   //   typedef sockaddr_in SOCKADDR_IN;
   //   typedef sockaddr_in* LPSOCKADDR_IN;
   //   typedef timeval TIMEVAL;
   //#define SOCKET_ERROR   (-1) 
   //#define INVALID_SOCKET (SOCKET)(~0)
   //#define closesocket close 
   //#define WSAGetLastError() errno
   //#define WSAEINTR EINTR
   //   inline int _select(int nfds, fd_set* readfds, fd_set* writefds, fd_set* exceptfds, struct timeval *__restrict timeout)
   //   {
   //      return select(nfds, readfds, writefds, exceptfds, timeout);
   //   }
   //#endif   

   typedef const struct sockaddr* LPCSOCKADDR;

   ///////////////////////////////////////////////////////////////////////////////////////
   //***************************** blocking_socket_exception  ***************************//
   ///////////////////////////////////////////////////////////////////////////////////////
   class CLASS_DECL_AXIS blocking_socket_exception :
      virtual public ::exception::base
   {
   public:
      // Constructor
      blocking_socket_exception(::aura::application * papp, LPCTSTR pchMessage);
      virtual ~blocking_socket_exception() {}

      virtual bool GetErrorMessage(string & strError, PUINT pnHelpContext = NULL);
      virtual string GetErrorMessage(PUINT pnHelpContext = NULL);

   private:
      int     m_nError;
      string m_strMessage;
   };

   /////////////////////////////////////////////////////////////////////////////////////////
   ////*********************************** address  ************************************//
   /////////////////////////////////////////////////////////////////////////////////////////
   //class CLASS_DECL_AXIS address : public sockaddr_in
   //{
   //public:
   //   // constructors
   //   address()
   //   {
   //      sin_family = AF_INET; // specifies address family
   //      sin_port = 0;       // ip port
   //      sin_addr.s_addr = 0;       // ip address
   //   }

   //   address(const SOCKADDR& sa)
   //   {
   //      memcpy(this, &sa, sizeof(SOCKADDR));
   //   }

   //   address(const SOCKADDR_IN& sin)
   //   {
   //      memcpy(this, &sin, sizeof(SOCKADDR_IN));
   //   }

   //   address(ULONG ulAddr, USHORT ushPort = 0) // parms are host byte ordered
   //   {
   //      sin_family = AF_INET;          // specifies address family
   //      sin_port = htons(ushPort);   // ip port
   //      sin_addr.s_addr = htonl(ulAddr);    // ip address
   //   }

   //   address(const char* pchIP, USHORT ushPort = 0) // dotted IP addr string
   //   {
   //      sin_family = AF_INET;               // specifies address family
   //      sin_port = htons(ushPort);          // ip port
   //      sin_addr.s_addr = inet_addr(pchIP); // ip address
   //   } // already network byte ordered

   //     // Return the address in dotted-decimal format
   //   string DottedDecimal()
   //   {
   //      return inet_ntoa(sin_addr);
   //   }

   //   // Get port and address (even though they're public)
   //   USHORT Port() const
   //   {
   //      return ntohs(sin_port);
   //   }

   //   ULONG IPAddr() const
   //   {
   //      return ntohl(sin_addr.s_addr);
   //   }

   //   // operators added for efficiency
   //   address& operator=(const SOCKADDR& sa)
   //   {
   //      memcpy(this, &sa, sizeof(SOCKADDR));
   //      return *this;
   //   }

   //   address& operator=(const SOCKADDR_IN& sin)
   //   {
   //      memcpy(this, &sin, sizeof(SOCKADDR_IN));
   //      return *this;
   //   }

   //   operator SOCKADDR()
   //   {
   //      return *((LPSOCKADDR) this);
   //   }

   //   operator LPSOCKADDR()
   //   {
   //      return (LPSOCKADDR) this;
   //   }

   //   operator LPSOCKADDR_IN()
   //   {
   //      return (LPSOCKADDR_IN) this;
   //   }
   //};

   ///////////////////////////////////////////////////////////////////////////////////////
   //********************************* blocking_socket  ********************************//
   ///////////////////////////////////////////////////////////////////////////////////////

   //class CLASS_DECL_AXIS iblocking_socket :
   //   virtual public object
   //{
   //public:
   //   virtual ~iblocking_socket() {};
   //   virtual iblocking_socket* create_instance() const = 0;
   //   virtual void create(int nType = SOCK_STREAM) = 0;
   //   virtual void connect(LPCSOCKADDR psa) const = 0;
   //   virtual void bind(LPCSOCKADDR psa) const = 0;
   //   virtual void listen() const = 0;
   //   virtual void cleanup() = 0;
   //   virtual bool accept(::sockets2::iblocking_socket& s, LPSOCKADDR psa) const = 0;
   //   virtual void close() = 0;
   //   virtual int  write(const void * pch, int nSize, int nSecs) const = 0;
   //   virtual int  receive(void * pch, int nSize, int nSecs) const = 0;
   //   virtual void get_peer_address(LPSOCKADDR psa) const = 0;
   //   virtual void get_socket_address(LPSOCKADDR psa) const = 0;
   //   virtual operator SOCKET() const = 0;
   //   virtual bool check_readability() const = 0;
   //   virtual address   get_host_by_name(const char* pchName, USHORT ushPort = 0) = 0;
   //   virtual const char* get_host_by_address(LPCSOCKADDR psa) = 0;
   //};

   // member functions truly block and must not be used in UI threads
   // use this class as an alternative to the MFC CSocket class
   class CLASS_DECL_AXIS blocking_socket :
      virtual public ::sockets::tcp_socket
   {
   public:


      memory_file                   m_file;


      blocking_socket(::sockets::base_socket_handler & handler);
      virtual ~blocking_socket();

      virtual blocking_socket * create_instance();
      virtual listen_socket < blocking_socket > * create_listening_instance();
      //int  send(const char* pch, int nSize, int nSecs) const;
      int  write(const void* pch, int nSize, int nSecs);
      int  receive(void* pch, int nSize, int nSecs);
      int  send_datagram(const char* pch, int nSize, LPCSOCKADDR psa, int nSecs);
      int  receive_datagram(char* pch, int nSize, LPSOCKADDR psa, int nSecs);
      bool check_readability(int nSecsPatience = 0);
      bool check_writability(int nSecsPatience = 0);


      virtual void on_read(const void * pdata, int_ptr n);

      ::net::address   get_host_by_name(const char* pchName, USHORT ushPort = 0);
      string get_host_by_address(::net::address address);


   };


   sp(blocking_socket) create_default_blocking_socket(base_socket_handler & handler);


   ///////////////////////////////////////////////////////////////////////////////////////
   //******************************** http_blocking_socket ******************************//
   ///////////////////////////////////////////////////////////////////////////////////////
   class CLASS_DECL_AXIS http_blocking_socket :
      virtual public blocking_socket
   {
   public:

      enum { nSizeRecv = 1000 }; // max receive buffer size (> hdr line length)


      char*  m_pReadBuf; // read buffer
      int    m_nReadBuf; // number of bytes in the read buffer


      http_blocking_socket(base_socket_handler & handler);
      ~http_blocking_socket();

      int read_http_header_line(char* pch, int nSize, int nSecs);
      int read_http_response(char* pch, int nSize, int nSecs);


   };


} // namespace sockets2





