////////////////////////////////////////////////////////////////////////////////
//
// From David J. Kruglinski (Inside Visual C++).
// Modifications by Thomas Oswald (make compatible to BSD sockets) //+#
//
////////////////////////////////////////////////////////////////////////////////

// blocking_socket_exception, blocking_socket, http_blocking_socket

#include "framework.h"


namespace sockets2
{


   ///////////////////////////////////////////////////////////////////////////////////////
   //************************* Class blocking_socket_exception **************************//
   ///////////////////////////////////////////////////////////////////////////////////////

   blocking_socket_exception::blocking_socket_exception(::aura::application * papp, LPCTSTR pchMessage) :
      ::object(papp),
      ::call_stack(papp),
      ::exception::base(papp),
      m_nError(WSAGetLastError()),
      m_strMessage(pchMessage)
   {
      ASSERT(pchMessage != NULL);
   }

   bool blocking_socket_exception::GetErrorMessage(string & strError, PUINT /*pnHelpContext = NULL*/)
   {
      if (m_nError == 0)
      {
         strError.Format("%s error", m_strMessage);
      }
      else
      {
         strError.Format("%s error 0x%08x", m_strMessage, m_nError);
      }
      return true;
   }

   string blocking_socket_exception::GetErrorMessage(PUINT /*pnHelpContext = NULL*/)
   {
      string str;
      GetErrorMessage(str);
      return str;
   }

   ///////////////////////////////////////////////////////////////////////////////////////
   //******************************** Class blocking_socket ****************************//
   ///////////////////////////////////////////////////////////////////////////////////////

   iblocking_socket* blocking_socket::create_instance() const
   {
      return canew(blocking_socket(get_app()));
   }

   blocking_socket::blocking_socket(::aura::application * papp) :
      ::object(papp),
      m_hSocket(INVALID_SOCKET)
   {
#ifdef WIN32
      // Initialize the Winsock dll version 2.0
      WSADATA  wsaData = { 0 };
      VERIFY(WSAStartup(MAKEWORD(2, 0), &wsaData) == 0);
      VERIFY(LOBYTE(wsaData.wVersion) == 2 && HIBYTE(wsaData.wVersion) == 0);
#endif
   }

   blocking_socket::~blocking_socket()
   {
      cleanup();
#ifdef WIN32
      WSACleanup();
#endif
   }

   void blocking_socket::cleanup()
   {
      // doesn't throw an exception because it's called in a catch block
      if (m_hSocket == INVALID_SOCKET)
         return;

      VERIFY(closesocket(m_hSocket) != SOCKET_ERROR);

      m_hSocket = INVALID_SOCKET;
   }

   void blocking_socket::create(int nType /* = SOCK_STREAM */)
   {
      ASSERT(m_hSocket == INVALID_SOCKET);
      if ((m_hSocket = socket(AF_INET, nType, 0)) == INVALID_SOCKET)
      {
         throw blocking_socket_exception(get_app(), _T("Create"));
      }
   }

   void blocking_socket::bind(LPCSOCKADDR psa) const
   {
      ASSERT(psa != NULL);
      ASSERT(m_hSocket != INVALID_SOCKET);
      if (::bind(m_hSocket, psa, sizeof(SOCKADDR)) == SOCKET_ERROR)
      {
         throw blocking_socket_exception(get_app(), _T("Bind"));
      }
   }

   void blocking_socket::listen() const
   {
      ASSERT(m_hSocket != INVALID_SOCKET);
      if (::listen(m_hSocket, 5) == SOCKET_ERROR)
      {
         throw blocking_socket_exception(get_app(), _T("Listen"));
      }
   }

   bool blocking_socket::accept(iblocking_socket& sConnect, LPSOCKADDR psa) const
   {
      ASSERT(psa != NULL);
      ASSERT(m_hSocket != INVALID_SOCKET);
      ASSERT(sConnect.operator SOCKET() == INVALID_SOCKET);

      // ATTENTION: dynamic_cast would be better (and then checking against NULL)
      //            RTTI must be enabled to use dynamic_cast //+#
      blocking_socket* pConnect = dynamic_cast<blocking_socket*>(&sConnect);

      socklen_t nLengthAddr = sizeof(SOCKADDR);
      pConnect->m_hSocket = ::accept(m_hSocket, psa, &nLengthAddr);

      if (pConnect->operator SOCKET() == INVALID_SOCKET)
      {
         // no exception if the listen was canceled
         if (WSAGetLastError() != WSAEINTR)
         {
            throw blocking_socket_exception(get_app(), _T("Accept"));
         }
         return false;
      }
      return true;
   }

   void blocking_socket::close()
   {
      if (m_hSocket != INVALID_SOCKET && closesocket(m_hSocket) == SOCKET_ERROR)
      {
         // should be OK to close if closed already
         throw blocking_socket_exception(get_app(), _T("Close"));
      }
      m_hSocket = INVALID_SOCKET;
   }

   void blocking_socket::connect(LPCSOCKADDR psa) const
   {
      ASSERT(psa != NULL);
      ASSERT(m_hSocket != INVALID_SOCKET);
      // should timeout by itself
      if (::connect(m_hSocket, psa, sizeof(SOCKADDR)) == SOCKET_ERROR)
      {
         throw blocking_socket_exception(get_app(), _T("Connect"));
      }
   }

   int blocking_socket::write(const void* pch, int nSize, int nSecs) const
   {
      ASSERT(pch != NULL);
      int         nBytesSent = 0;
      int         nBytesThisTime = 0;
      const char* pch1 = (const char *) pch;

      do
      {
         nBytesThisTime = send(pch1, nSize - nBytesSent, nSecs);
         nBytesSent += nBytesThisTime;
         pch1 += nBytesThisTime;
      } while (nBytesSent < nSize);

      return nBytesSent;
   }

   int blocking_socket::send(const char * pch, int nSize, int nSecs) const
   {
      ASSERT(pch != NULL);
      ASSERT(m_hSocket != INVALID_SOCKET);

      // returned value will be less than nSize if client cancels the reading
      fd_set fd;
      FD_ZERO(&fd);
      FD_SET(m_hSocket, &fd);
      TIMEVAL tv = { nSecs, 0 };

      if (_select(m_hSocket + 1, NULL, &fd, NULL, &tv) == 0)
      {
         throw blocking_socket_exception(get_app(), _T("Send timeout"));
      }

      const int nBytesSent = ::send(m_hSocket, pch, nSize, 0);
      if (nBytesSent == SOCKET_ERROR)
      {
         throw blocking_socket_exception(get_app(), _T("Send"));
      }

      return nBytesSent;
   }

   bool blocking_socket::check_readability() const
   {
      ASSERT(m_hSocket != INVALID_SOCKET);

      fd_set fd;
      FD_ZERO(&fd);
      FD_SET(m_hSocket, &fd);
      TIMEVAL tv = { 0, 0 };

      // static_cast is necessary to avoid compiler warning under WIN32;
      // This is no problem because the first parameter is included only
      // for compatibility with Berkeley sockets.
      const int iRet = _select(m_hSocket + 1, &fd, NULL, NULL, &tv);

      if (iRet == SOCKET_ERROR)
      {
         throw blocking_socket_exception(get_app(), _T("Socket Error"));
      }

      return iRet == 1;
   }

   int blocking_socket::receive(void * pch, int nSize, int nSecs) const
   {
      ASSERT(pch != NULL);
      ASSERT(m_hSocket != INVALID_SOCKET);

      fd_set fd;
      FD_ZERO(&fd);
      FD_SET(m_hSocket, &fd);
      TIMEVAL tv = { nSecs, 0 };

      // static_cast is necessary to avoid compiler warning under WIN32;
      // This is no problem because the first parameter is included only
      // for compatibility with Berkeley sockets.
      if (_select(m_hSocket + 1, &fd, NULL, NULL, &tv) == 0)
      {
         throw blocking_socket_exception(get_app(), _T("Receive timeout"));
      }

      const int nBytesReceived = ::recv(m_hSocket, (char *) pch, nSize, 0);
      if (nBytesReceived == SOCKET_ERROR)
      {
         throw blocking_socket_exception(get_app(), _T("Receive"));
      }

      return nBytesReceived;
   }

   int blocking_socket::receive_datagram(char* pch, int nSize, LPSOCKADDR psa, int nSecs) const
   {
      ASSERT(pch != NULL);
      ASSERT(psa != NULL);
      ASSERT(m_hSocket != INVALID_SOCKET);

      fd_set fd;
      FD_ZERO(&fd);
      FD_SET(m_hSocket, &fd);
      TIMEVAL tv = { nSecs, 0 };

      // static_cast is necessary to avoid compiler warning under WIN32;
      // This is no problem because the first parameter is included only
      // for compatibility with Berkeley sockets.
      if (_select(m_hSocket + 1, &fd, NULL, NULL, &tv) == 0)
      {
         throw blocking_socket_exception(get_app(), _T("Receive timeout"));
      }

      // input buffer should be big enough for the entire datagram
      socklen_t nFromSize = sizeof(SOCKADDR);
      const int nBytesReceived = recvfrom(m_hSocket, pch, nSize, 0, psa, &nFromSize);

      if (nBytesReceived == SOCKET_ERROR)
      {
         throw blocking_socket_exception(get_app(), _T("ReceiveDatagram"));
      }

      return nBytesReceived;
   }

   int blocking_socket::send_datagram(const char* pch, int nSize, LPCSOCKADDR psa, int nSecs) const
   {
      ASSERT(pch != NULL);
      ASSERT(psa != NULL);
      ASSERT(m_hSocket != INVALID_SOCKET);

      fd_set fd;
      FD_ZERO(&fd);
      FD_SET(m_hSocket, &fd);
      TIMEVAL tv = { nSecs, 0 };

      // static_cast is necessary to avoid compiler warning under WIN32;
      // This is no problem because the first parameter is included only
      // for compatibility with Berkeley sockets.
      if (_select(m_hSocket + 1, NULL, &fd, NULL, &tv) == 0)
      {
         throw blocking_socket_exception(get_app(), _T("Send timeout"));
      }

      const int nBytesSent = sendto(m_hSocket, pch, nSize, 0, psa, sizeof(SOCKADDR));
      if (nBytesSent == SOCKET_ERROR)
      {
         throw blocking_socket_exception(get_app(), _T("SendDatagram"));
      }

      return nBytesSent;
   }

   void blocking_socket::get_peer_address(LPSOCKADDR psa) const
   {
      ASSERT(psa != NULL);
      ASSERT(m_hSocket != INVALID_SOCKET);

      // gets the address of the socket at the other end
      socklen_t nLengthAddr = sizeof(SOCKADDR);
      if (getpeername(m_hSocket, psa, &nLengthAddr) == SOCKET_ERROR)
      {
         throw blocking_socket_exception(get_app(), _T("GetPeerName"));
      }
   }

   void blocking_socket::get_socket_address(LPSOCKADDR psa) const
   {
      ASSERT(psa != NULL);
      ASSERT(m_hSocket != INVALID_SOCKET);

      // gets the address of the socket at this end
      socklen_t nLengthAddr = sizeof(SOCKADDR);
      if (getsockname(m_hSocket, psa, &nLengthAddr) == SOCKET_ERROR)
      {
         throw blocking_socket_exception(get_app(), _T("GetSockName"));
      }
   }

   address blocking_socket::get_host_by_name(const char* pchName, USHORT ushPort /* = 0 */)
   {
      ASSERT(pchName != NULL);
      hostent* pHostEnt = gethostbyname(pchName);

      if (pHostEnt == NULL)
      {
         throw blocking_socket_exception(get_app(), _T("GetHostByName"));
      }

      ULONG* pulAddr = (ULONG*)pHostEnt->h_addr_list[0];
      SOCKADDR_IN sockTemp;
      sockTemp.sin_family = AF_INET;
      sockTemp.sin_port = htons(ushPort);
      sockTemp.sin_addr.s_addr = *pulAddr; // address is already in network byte order
      return sockTemp;
   }

   const char* blocking_socket::get_host_by_address(LPCSOCKADDR psa)
   {
      ASSERT(psa != NULL);
      hostent* pHostEnt = gethostbyaddr((char*) &((LPSOCKADDR_IN)psa)
         ->sin_addr.s_addr, 4, PF_INET);

      if (pHostEnt == NULL)
      {
         throw blocking_socket_exception(get_app(), _T("GetHostByAddr"));
      }

      return pHostEnt->h_name; // caller shouldn't delete this memory
   }

   ///////////////////////////////////////////////////////////////////////////////////////
   //**************************** Class http_blocking_socket ****************************//
   ///////////////////////////////////////////////////////////////////////////////////////

   http_blocking_socket::http_blocking_socket(::aura::application * papp) :
      ::object(papp),
      blocking_socket(papp)
   {
      m_pReadBuf = new char[nSizeRecv];
      m_nReadBuf = 0;
   }

   http_blocking_socket::~http_blocking_socket()
   {
      delete[] m_pReadBuf;
   }

   int http_blocking_socket::read_http_header_line(char* pch, int nSize, int nSecs)
      // reads an entire header line through CRLF (or socket close)
      // inserts zero string terminator, object maintains a buffer
   {
      int       nBytesThisTime = m_nReadBuf;
      ptrdiff_t nLineLength = 0;
      char*     pch1 = m_pReadBuf;
      char*     pch2 = NULL;

      do
      {
         // look for lf (assume preceded by cr)
         if ((pch2 = (LPSTR)memchr(pch1, '\n', nBytesThisTime)) != NULL)
         {
            ASSERT((pch2) > m_pReadBuf);
            ASSERT(*(pch2 - 1) == '\r');
            nLineLength = (pch2 - m_pReadBuf) + 1;
            if (nLineLength >= nSize)
               nLineLength = nSize - 1;
            memcpy(pch, m_pReadBuf, nLineLength); // copy the line to caller
            m_nReadBuf -= static_cast<unsigned int>(nLineLength);
            memmove(m_pReadBuf, pch2 + 1, m_nReadBuf); // shift remaining characters left
            break;
         }
         pch1 += nBytesThisTime;
         nBytesThisTime = receive(m_pReadBuf + m_nReadBuf, nSizeRecv - m_nReadBuf, nSecs);
         if (nBytesThisTime <= 0)
         { // sender closed socket or line longer than buffer
            throw blocking_socket_exception(get_app(), _T("ReadHeaderLine"));
         }
         m_nReadBuf += nBytesThisTime;
      } while (true);

      *(pch + nLineLength) = _T('\0');

      return static_cast<unsigned int>(nLineLength);
   }

   // reads remainder of a transmission through buffer full or socket close
   // (assume headers have been read already)
   int http_blocking_socket::read_http_response(char* pch, int nSize, int nSecs)
   {
      int nBytesToRead, nBytesThisTime, nBytesRead = 0;

      if (m_nReadBuf > 0)
      { // copy anything already in the recv buffer
         memcpy(pch, m_pReadBuf, m_nReadBuf);
         pch += m_nReadBuf;
         nBytesRead = m_nReadBuf;
         m_nReadBuf = 0;
      }
      do
      { // now pass the rest of the data directly to the caller
         nBytesToRead = std::min(static_cast<int>(nSizeRecv), nSize - nBytesRead);
         nBytesThisTime = receive(pch, nBytesToRead, nSecs);
         if (nBytesThisTime <= 0)
            break; // sender closed the socket
         pch += nBytesThisTime;
         nBytesRead += nBytesThisTime;
      } while (nBytesRead <= nSize);

      return nBytesRead;
   }

   sp(iblocking_socket) create_default_blocking_socket(::aura::application * papp)
   {
      return canew(blocking_socket(papp));
   }


} // namespace sockets2




