#include "base/net/net_sockets.h"


#ifdef _WIN32
#else
#include <fcntl.h>
#endif
////#include <ctype.h>


#ifdef LINUX
#include <unistd.h>
#endif


namespace sockets
{

#ifdef DEBUG
#define DEB(x) x; fflush(stderr);
#else
#define DEB(x)
#endif


   // statics
#ifdef _WIN32
   WSAInitializer socket::m_winsock_init;
#endif


   socket::socket(base_socket_handler& h) :
      element(h),
      base_socket(h)
   {

      m_iBindPort    = -1;
      m_dwStart      = ::get_tick_count();
      m_pcallback    = NULL;

   }


   socket::~socket()
   {
      if(&Handler() != NULL)
      {
         Handler().remove(this);
      }
      if (m_socket != INVALID_SOCKET
#ifdef ENABLE_POOL
         && !m_bRetain
#endif
         )
      {
         close();
      }

   }


   int32_t socket::close_socket(SOCKET s)
   {

      return ::closesocket(s);

   }


   void socket::close()
   {
      if (m_socket == INVALID_SOCKET) // this could happen
      {
         if(!is_null(Handler()))
         {
            log("socket::close", 0, "file descriptor invalid", ::aura::log::level_warning);
         }
         return;
      }
      int32_t n;
      if ((n = close_socket(m_socket)) == -1)
      {
         if(!is_null(Handler()))
         {
            // failed...
            log("close", Errno, StrError(Errno), ::aura::log::level_error);
         }
      }
      if(!is_null(Handler()))
      {
         Handler().set(m_socket, false, false, false); // remove from fd_set's
         Handler().AddList(m_socket, LIST_CALLONCONNECT, false);
         Handler().AddList(m_socket, LIST_DETACH, false);
         Handler().AddList(m_socket, LIST_TIMEOUT, false);
         Handler().AddList(m_socket, LIST_RETRY, false);
         Handler().AddList(m_socket, LIST_CLOSE, false);
      }
      m_socket = INVALID_SOCKET;
      //throw n;
   }


   SOCKET socket::CreateSocket(int32_t af,int32_t iType, const string & strProtocol)
   {
      struct protoent *p = NULL;
      SOCKET s;

      m_iSocketType = iType;
      m_strSocketProtocol = strProtocol;
      if (strProtocol.get_length())
      {
         p = getprotobyname( strProtocol );
         if (!p)
         {
            log("getprotobyname", Errno, StrError(Errno), ::aura::log::level_fatal);
            SetCloseAndDelete();
            throw simple_exception(get_app(), string("getprotobyname() failed: ") + StrError(Errno));
            return INVALID_SOCKET;
         }
      }
      int32_t protno = p ? p -> p_proto : 0;

      s = ::socket(af, iType, protno);
      if (s == INVALID_SOCKET)
      {
         log("socket", Errno, StrError(Errno), ::aura::log::level_fatal);
         SetCloseAndDelete();
         throw simple_exception(get_app(), string("socket() failed: ") + StrError(Errno));
         return INVALID_SOCKET;
      }
      attach(s);
      OnOptions(af, iType, protno, s);
      attach(INVALID_SOCKET);
      return s;
   }





   void socket::set(bool bRead, bool bWrite, bool bException)
   {
      Handler().set(m_socket, bRead, bWrite, bException);
   }


   bool socket::Ready()
   {
      if (m_socket != INVALID_SOCKET && !CloseAndDelete())
         return true;
      return false;
   }

   bool socket::is_valid()
   {

      return Ready();

   }


   bool socket::SetNonblocking(bool bNb, SOCKET s)
   {
   #ifdef _WIN32
      u_long l = bNb ? 1 : 0;
      int32_t n = ioctlsocket(s, FIONBIO, &l);
      if (n != 0)
      {
         log("ioctlsocket(FIONBIO)", Errno, "");
         return false;
      }
      return true;
   #else
      if (bNb)
      {
         if (fcntl(s, F_SETFL, O_NONBLOCK) == -1)
         {
            log("fcntl(F_SETFL, O_NONBLOCK)", Errno, StrError(Errno), ::aura::log::level_error);
            return false;
         }
      }
      else
      {
         if (fcntl(s, F_SETFL, 0) == -1)
         {
            log("fcntl(F_SETFL, 0)", Errno, StrError(Errno), ::aura::log::level_error);
            return false;
         }
      }
      return true;
   #endif
   }



} // namespace sockets





