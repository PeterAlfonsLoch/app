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


#if defined(LINUX) || defined(__APPLE__)

#define SOCKADDR sockaddr

#endif


namespace sockets
{


   class CLASS_DECL_AXIS transfer_socket_exception :
      virtual public ::exception::base
   {
   public:
      // Constructor
      transfer_socket_exception(::aura::application * papp, LPCTSTR pchMessage);
      virtual ~transfer_socket_exception() {}

      virtual bool GetErrorMessage(string & strError, PUINT pnHelpContext = NULL);
      virtual string GetErrorMessage(PUINT pnHelpContext = NULL);

   private:
      int     m_nError;
      string m_strMessage;
   };

   class CLASS_DECL_AXIS transfer_socket :
      virtual public tcp_socket
   {
   public:


      memory_file                   m_file;


      transfer_socket(::sockets::base_socket_handler & handler);
      virtual ~transfer_socket();

      int  send_datagram(const char* pch, int nSize, const SOCKADDR * psa, int nSecs);
      int  receive_datagram(char* pch, int nSize, SOCKADDR * psa, int nSecs);
      bool check_readability(int nSecsPatience); // const
      bool check_writability(int nSecsPatience); // const


   };

   class CLASS_DECL_AXIS read_socket :
      virtual public transfer_socket
   {
   public:


      read_socket(::sockets::base_socket_handler & handler);
      virtual ~read_socket();



      virtual void on_read(const void * pdata, int_ptr n);



   };


   class CLASS_DECL_AXIS write_socket :
      virtual public transfer_socket
   {
   public:


      write_socket(::sockets::base_socket_handler & handler);
      virtual ~write_socket();

      virtual void OnWrite();

   };


   //class CLASS_DECL_AXIS http_transfer_socket :
   //   virtual public transfer_socket
   //{
   //public:

   //   enum { nSizeRecv = 1000 }; // max receive buffer size (> hdr line length)


   //   char*  m_pReadBuf; // read buffer
   //   int    m_nReadBuf; // number of bytes in the read buffer


   //   http_transfer_socket(base_socket_handler & handler);
   //   ~http_transfer_socket();

   //   int read_http_header_line(char* pch, int nSize, int nSecs);
   //   int read_http_response(char* pch, int nSize, int nSecs);


   //};


} // namespace sockets2





