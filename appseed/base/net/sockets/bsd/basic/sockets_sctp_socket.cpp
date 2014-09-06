#include "base/net/net_sockets.h"


#ifdef USE_SCTP


namespace sockets
{


   SctpSocket::SctpSocket(base_socket_handler& h,int32_t type) : stream_socket(h)
   ,m_type(type)
   ,m_buf(new char[SCTP_BUFSIZE_READ])
   {
      if (type != SOCK_STREAM && type != SOCK_SEQPACKET)
      {
      }
   }


   SctpSocket::~SctpSocket()
   {
      delete[] m_buf;
   }


   int32_t SctpSocket::Bind(const string & a,port_t p)
   {
   #ifdef ENABLE_IPV6
   #ifdef IPPROTO_IPV6
      if (IsIpv6())
      {
         ipv6_address ad(a, p);
         return Bind(ad);
      }
   #endif
   #endif
      ipv4_address ad(a, p);
      return Bind(ad);
   }


   int32_t SctpSocket::Bind(const ::net::address & ad)
   {
      if (!ad.IsValid())
      {
         log("SctpSocket", -1, "invalid address", ::aura::log::level_error);
         return -1;
      }
      if (GetSocket() == INVALID_SOCKET)
      {
         attach(CreateSocket(ad.GetFamily(), m_type, "sctp"));
      }
      if (GetSocket() != INVALID_SOCKET)
      {
         int32_t n = bind(GetSocket(), ad, ad);
         if (n == -1)
         {
            log("SctpSocket", -1, "bind() failed", ::aura::log::level_error);
   #ifdef ENABLE_EXCEPTIONS
            throw Exception("bind() failed for SctpSocket, port: " + Utility::l2string(ad.GetPort()));
   #endif
         }
         return n;
      }
      return -1;
   }


   int32_t SctpSocket::AddAddress(const string & a,port_t p)
   {
   #ifdef ENABLE_IPV6
   #ifdef IPPROTO_IPV6
      if (IsIpv6())
      {
         ipv6_address ad(a, p);
         return AddAddress(ad);
      }
   #endif
   #endif
      ipv4_address ad(a, p);
      return AddAddress(ad);
   }


   int32_t SctpSocket::AddAddress(const ::net::address & ad)
   {
      if (!ad.IsValid())
      {
         log("SctpSocket", -1, "invalid address", ::aura::log::level_error);
         return -1;
      }
      if (GetSocket() == INVALID_SOCKET)
      {
         log("SctpSocket", -1, "AddAddress called with invalid file descriptor", ::aura::log::level_error);
         return -1;
      }
      int32_t n = sctp_bindx(GetSocket(), ad, ad, SCTP_BINDX_ADD_ADDR);
      if (n == -1)
      {
         log("SctpSocket", -1, "sctp_bindx() failed", ::aura::log::level_error);
      }
      return n;
   }


   int32_t SctpSocket::RemoveAddress(const string & a,port_t p)
   {
   #ifdef ENABLE_IPV6
   #ifdef IPPROTO_IPV6
      if (IsIpv6())
      {
         ipv6_address ad(a, p);
         return RemoveAddress(ad);
      }
   #endif
   #endif
      ipv4_address ad(a, p);
      return RemoveAddress(ad);
   }


   int32_t SctpSocket::RemoveAddress(const ::net::address & ad)
   {
      if (!ad.IsValid())
      {
         log("SctpSocket", -1, "invalid address", ::aura::log::level_error);
         return -1;
      }
      if (GetSocket() == INVALID_SOCKET)
      {
         log("SctpSocket", -1, "RemoveAddress called with invalid file descriptor", ::aura::log::level_error);
         return -1;
      }
      int32_t n = sctp_bindx(GetSocket(), ad, ad, SCTP_BINDX_REM_ADDR);
      if (n == -1)
      {
         log("SctpSocket", -1, "sctp_bindx() failed", ::aura::log::level_error);
      }
      return n;
   }


   int32_t SctpSocket::open(const string & a,port_t p)
   {
   #ifdef ENABLE_IPV6
   #ifdef IPPROTO_IPV6
      if (IsIpv6())
      {
         ipv6_address ad(a, p);
         return open(ad);
      }
   #endif
   #endif
      ipv4_address ad(a, p);
      return open(ad);
   }


   int32_t SctpSocket::open(const ::net::address & ad)
   {
      if (!ad.IsValid())
      {
         log("SctpSocket", -1, "invalid address", ::aura::log::level_error);
         return -1;
      }
      if (GetSocket() == INVALID_SOCKET)
      {
         attach(CreateSocket(ad.GetFamily(), m_type, "sctp"));
      }
      if (GetSocket() != INVALID_SOCKET)
      {
         if (!SetNonblocking(true))
         {
            return -1;
         }
         int32_t n = connect(GetSocket(), ad, ad);
         if (n == -1)
         {
            // check error code that means a connect is in progress
   #ifdef _WIN32
            if (Errno == WSAEWOULDBLOCK)
   #else
            if (Errno == EINPROGRESS)
   #endif
            {
               log("connect: connection pending", Errno, StrError(Errno), ::aura::log::level_info);
               SetConnecting( true ); // this flag will control fd_set's
            }
            else
            {
               log("SctpSocket", -1, "connect() failed", ::aura::log::level_error);
            }
         }
         return n;
      }
      return -1;
   }


   #ifndef SOLARIS
   int32_t SctpSocket::AddConnection(const string & a,port_t p)
   {
   #ifdef ENABLE_IPV6
   #ifdef IPPROTO_IPV6
      if (IsIpv6())
      {
         ipv6_address ad(a, p);
         return AddConnection(ad);
      }
   #endif
   #endif
      ipv4_address ad(a, p);
      return AddConnection(ad);
   }


   int32_t SctpSocket::AddConnection(const ::net::address & ad)
   {
      if (!ad.IsValid())
      {
         log("SctpSocket", -1, "invalid address", ::aura::log::level_error);
         return -1;
      }
      if (GetSocket() == INVALID_SOCKET)
      {
         log("SctpSocket", -1, "AddConnection called with invalid file descriptor", ::aura::log::level_error);
         return -1;
      }
      int32_t n = sctp_connectx(GetSocket(), ad, ad);
      if (n == -1)
      {
         log("SctpSocket", -1, "sctp_connectx() failed", ::aura::log::level_error);
      }
      else
      {
         SetConnecting();
      }
      return n;
   }
   #endif


   int32_t SctpSocket::getpaddrs(sctp_assoc_t id,list<string>& vec)
   {
      struct sockaddr *p = NULL;
      int32_t n = sctp_getpaddrs(GetSocket(), id, &p);
      if (!n || n == -1)
      {
         log("SctpSocket", -1, "sctp_getpaddrs failed", ::aura::log::level_warning);
         return n;
      }
      for (int32_t i = 0; i < n; i++)
      {
         vec.push_back(Utility::Sa2String(&p[i]));
      }
      sctp_freepaddrs(p);
      return n;
   }


   int32_t SctpSocket::getladdrs(sctp_assoc_t id,list<string>& vec)
   {
      struct sockaddr *p = NULL;
      int32_t n = sctp_getladdrs(GetSocket(), id, &p);
      if (!n || n == -1)
      {
         log("SctpSocket", -1, "sctp_getladdrs failed", ::aura::log::level_warning);
         return n;
      }
      for (int32_t i = 0; i < n; i++)
      {
         vec.push_back(Utility::Sa2String(&p[i]));
      }
      sctp_freeladdrs(p);
      return n;
   }


   int32_t SctpSocket::PeelOff(sctp_assoc_t id)
   {
      int32_t n = sctp_peeloff(GetSocket(), id);
      if (n == -1)
      {
         log("SctpSocket", -1, "PeelOff failed", ::aura::log::level_warning);
         return -1;
      }
      socket *p = create();
      p -> attach(n);
      p -> SetDeleteByHandler();
      Handler().add(p);
      return n;
   }


   void SctpSocket::OnRead()
   {
   /*
      int32_t sctp_recvmsg(int32_t sd, void * msg, size_t * len,
         struct sockaddr * from, socklen_t * fromlen,
         struct sctp_sndrcvinfo * sinfo, int32_t * msg_flags);

      DESCRIPTION
      sctp_recvmsg  is  a  wrapper library function that can be used to receive a message from a socket while using the advanced
      features of SCTP.  sd is the socket descriptor on which the message pointed to by msg of length len is received.

      If from is not NULL, the source address of the message is filled in. The argument fromlen  is  a  value-result  parameter.
      initialized  to  the  size  of the buffer associated with from , and modified on return to indicate the actual size of the
      address stored.

      sinfo is a pointer to a sctp_sndrcvinfo structure to be filled upon receipt of the message.  msg_flags is a pointer  to  a
      integer that is filled with any message flags like MESSAGE_NOTIFICATION or MESSAGE_EOR.

   */
      struct sockaddr sa;
      socklen_t sa_len = 0;
      struct sctp_sndrcvinfo sinfo;
      int32_t flags = 0;
      int32_t n = sctp_recvmsg(GetSocket(), m_buf, SCTP_BUFSIZE_READ, &sa, &sa_len, &sinfo, &flags);
      if (n == -1)
      {
         log("SctpSocket", Errno, StrError(Errno), ::aura::log::level_fatal);
         SetCloseAndDelete();
      }
      else
      {
         OnReceiveMessage(m_buf, n, &sa, sa_len, &sinfo, flags);
      }
   }


   void SctpSocket::OnReceiveMessage(const char *buf,size_t sz,struct sockaddr *sa,socklen_t sa_len,struct sctp_sndrcvinfo *sinfo,int32_t msg_flags)
   {
   }


   void SctpSocket::OnWrite()
   {
      if (Connecting())
      {
         int32_t err = SoError();

         // don't reset connecting flag on error here, we want the OnConnectFailed timeout later on
         /// \todo add to read fd_set here
         if (!err) // ok
         {
            set(!IsDisableRead(), false);
            SetConnecting(false);
            SetCallOnConnect();
            return;
         }
         log("sctp: connect failed", err, StrError(err), ::aura::log::level_fatal);
         set(false, false); // no more monitoring because connection failed

         // failed
   #ifdef ENABLE_SOCKS4
         if (Socks4())
         {
            OnSocks4ConnectFailed();
            return;
         }
   #endif
         if (GetConnectionRetry() == -1 ||
            (GetConnectionRetry() && GetConnectionRetries() < GetConnectionRetry()) )
         {
            // even though the connection failed at once, only retry after
            // the connection timeout.
            // should we even try to connect again, when CheckConnect returns
            // false it's because of a connection error - not a timeout...
            return;
         }
         SetConnecting(false);
         SetCloseAndDelete( true );
         /// \todo state reason why connect failed
         OnConnectFailed();
         return;
      }
   }


   void SctpSocket::OnConnectTimeout()
   {
      log("connect", -1, "connect timeout", ::aura::log::level_fatal);
   #ifdef ENABLE_SOCKS4
      if (Socks4())
      {
         OnSocks4ConnectFailed();
         // retry direct connection
      }
      else
   #endif
      if (GetConnectionRetry() == -1 ||
         (GetConnectionRetry() && GetConnectionRetries() < GetConnectionRetry()) )
      {
         IncreaseConnectionRetries();
         // ask socket via OnConnectRetry callback if we should continue trying
         if (OnConnectRetry())
         {
            SetRetryClientConnect();
         }
         else
         {
            SetCloseAndDelete( true );
            /// \todo state reason why connect failed
            OnConnectFailed();
         }
      }
      else
      {
         SetCloseAndDelete(true);
         /// \todo state reason why connect failed
         OnConnectFailed();
      }
      //
      SetConnecting(false);
   }


   #ifdef _WIN32
   void SctpSocket::OnException()
   {
      if (Connecting())
      {
   #ifdef ENABLE_SOCKS4
         if (Socks4())
            OnSocks4ConnectFailed();
         else
   #endif
         if (GetConnectionRetry() == -1 ||
            (GetConnectionRetry() &&
             GetConnectionRetries() < GetConnectionRetry() ))
         {
            // even though the connection failed at once, only retry after
            // the connection timeout
            // should we even try to connect again, when CheckConnect returns
            // false it's because of a connection error - not a timeout...
         }
         else
         {
            SetConnecting(false); // tnx snibbe
            SetCloseAndDelete();
            OnConnectFailed();
         }
         return;
      }
      // %! exception doesn't always mean something bad happened, this code should be reworked
      // errno valid here?
      int32_t err = SoError();
      log("exception on select", err, StrError(err), ::aura::log::level_fatal);
      SetCloseAndDelete();
   }
   #endif // _WIN32


   int32_t SctpSocket::Protocol()
   {
      return IPPROTO_SCTP;
   }


} // namespace sockets


#endif



