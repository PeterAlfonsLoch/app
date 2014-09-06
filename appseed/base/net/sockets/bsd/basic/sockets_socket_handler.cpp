#include "base/net/net_sockets.h"


#if defined(APPLEOS)

#define bcopy(src, dest, len) memcpy(dest, src, len)

#else

#define FD_COPY(pfdsetSrc, pfdsetDst) (*(pfdsetDst)) = (*(pfdsetSrc))

#endif


namespace sockets
{


   #ifdef DEBUG
   #define DEB(x) x; fflush(stderr);
   #else
   #define DEB(x)
   #endif


   socket_handler::socket_handler(sp(::aura::application) papp, logger *plogger) :
   element(papp),
   base_socket_handler(papp, plogger),
   m_pmutex(NULL),
   m_b_use_mutex(false)
   ,m_maxsock(0)
   ,m_preverror(-1)
   ,m_errcnt(0)
   ,m_tlast(0)
   ,m_socks4_port(0)
   ,m_bTryDirect(false)
   ,m_resolv_id(0)
   ,m_resolver(NULL)
   ,m_b_enable_pool(false)
   ,m_next_trigger_id(0)
   ,m_slave(false)
   {
      ZERO(m_socks4_host);
      FD_ZERO(&m_rfds);
      FD_ZERO(&m_wfds);
      FD_ZERO(&m_efds);
   }


   socket_handler::socket_handler(sp(::aura::application) papp, mutex& mutex, logger * plogger) :
   element(papp),
   base_socket_handler(papp, plogger)
   ,m_pmutex(&mutex)
   ,m_b_use_mutex(true)
   ,m_maxsock(0)
   ,m_preverror(-1)
   ,m_errcnt(0)
   ,m_tlast(0)
   ,m_socks4_port(0)
   ,m_bTryDirect(false)
   ,m_resolv_id(0)
   ,m_resolver(NULL)
   ,m_b_enable_pool(false)
   ,m_next_trigger_id(0)
   ,m_slave(false)
   {
      ZERO(m_socks4_host);
      m_pmutex->lock();
      FD_ZERO(&m_rfds);
      FD_ZERO(&m_wfds);
      FD_ZERO(&m_efds);
   }


   socket_handler::~socket_handler()
   {
      if (m_resolver)
      {
         m_resolver -> Quit();
      }
      {
         POSITION pos = m_sockets.get_start_position();
         SOCKET s;
         while(pos != NULL)
         {
            sp(base_socket) p = NULL;
            m_sockets.get_next_assoc(pos, s, p);
            if(p)
            {
               try
               {
                  p->close();
               }
               catch(...)
               {
               }
               if(m_slave)
               {
                  try
                  {
                     p.release();
                  }
                  catch(...)
                  {
                  }
               }
            }
         }
      }
      m_sockets.remove_all();
      if (m_resolver)
      {
         delete m_resolver;
      }
      if (m_b_use_mutex)
      {
         m_pmutex->unlock();
      }
   }


   mutex& socket_handler::GetMutex() const
   {
      return *m_pmutex;
   }


   void socket_handler::SetSlave(bool x)
   {
      m_slave = x;
   }


   bool socket_handler::IsSlave()
   {
      return m_slave;
   }


   void socket_handler::add(base_socket * pbasesocket)
   {

      socket * p = dynamic_cast < socket * > (pbasesocket);

      if (p -> GetSocket() == INVALID_SOCKET)
      {
         log(p, "add", -1, "Invalid socket", ::aura::log::level_warning);
         if (p -> CloseAndDelete())
         {
            m_delete.add_tail(p);
         }
         return;
      }
      sp(base_socket) plookup;
      if (m_add.Lookup(p -> GetSocket(), plookup))
      {
         log(p, "add", (int32_t)p -> GetSocket(), "Attempt to add socket already in add queue", ::aura::log::level_info);
         //m_delete.add_tail(p);
         return;
      }
      m_add[p -> GetSocket()] = p;
      p->m_estatus = socket::status_ok;
   }


   void socket_handler::get(SOCKET s,bool& r,bool& w,bool& e)
   {
      if (s >= 0)
      {
         r = FD_ISSET(s, &m_rfds) ? true : false;
         w = FD_ISSET(s, &m_wfds) ? true : false;
         e = FD_ISSET(s, &m_efds) ? true : false;
      }
   }


   void socket_handler::set(SOCKET s,bool bRead,bool bWrite,bool bException)
   {
   //TRACE("set(%d, %s, %s, %s)\n", s, bRead ? "true" : "false", bWrite ? "true" : "false", bException ? "true" : "false");
      if (s >= 0)
      {
         if (bRead)
         {
            if (!FD_ISSET(s, &m_rfds))
            {
               FD_SET(s, &m_rfds);
            }
         }
         else
         {
            FD_CLR(s, &m_rfds);
         }
         if (bWrite)
         {
            if (!FD_ISSET(s, &m_wfds))
            {
               FD_SET(s, &m_wfds);
            }
         }
         else
         {
            FD_CLR(s, &m_wfds);
         }
         if (bException)
         {
            if (!FD_ISSET(s, &m_efds))
            {
               FD_SET(s, &m_efds);
            }
         }
         else
         {
            FD_CLR(s, &m_efds);
         }
      }
   }


   int32_t socket_handler::select(int32_t lSeconds, int32_t lMicroseconds)
   {

      struct timeval timeval;

      timeval.tv_sec    = lSeconds;
      timeval.tv_usec   = lMicroseconds;

      return select(&timeval);

   }


   int32_t socket_handler::select()
   {
      
      if (m_fds_callonconnect.get_size() ||
         (!m_slave && m_fds_detach.get_size()) ||
         m_fds_timeout.get_size() ||
         m_fds_retry.get_size() ||
         m_fds_close.get_size() ||
         m_fds_erase.get_size())
      {
         return select(0, 200000);
      }

      return select(NULL);

   }


   int32_t socket_handler::select(struct timeval *tsel)
   {

      uint32_t dw1, dw2;

      size_t ignore = 0;

      while(natural(m_add.get_size()) > ignore)
      {

         if (m_sockets.get_size() >= FD_SETSIZE)
         {
            log(NULL, "Select", (int32_t)m_sockets.get_size(), "FD_SETSIZE reached", ::aura::log::level_warning);
            break;
         }

         POSITION pos = m_add.get_start_position();
         SOCKET s;
         sp(base_socket) p;
         m_add.get_next_assoc(pos, s, p);
         //TRACE("Trying to add fd %d,  m_add.size() %d,  ignore %d\n", (int32_t)s, (int32_t)m_add.get_size(), (int32_t)ignore);
         //
         sp(base_socket) plookup;
         if (m_sockets.Lookup(p -> GetSocket(), plookup))
         {
            log(p, "add", (int32_t)p -> GetSocket(), "Attempt to add socket already in controlled queue", ::aura::log::level_fatal);
            // %! it's a dup, don't add to delete queue, just ignore it
            m_delete.add_tail(p);
            m_add.remove_key(s);
            ignore++;
            continue;
         }
         if (!p -> CloseAndDelete())
         {
            sp(stream_socket)scp = (p);
            if (scp && scp -> Connecting()) // 'open' called before adding socket
            {
               set(s,false,true);
            }
            else
            {
               sp(tcp_socket)tcp = (p);
               bool bWrite = tcp ? tcp -> GetOutputLength() != 0 : false;
               if (p -> IsDisableRead())
               {
                  set(s, false, bWrite);
               }
               else
               {
                  set(s, true, bWrite);
               }
            }
            m_maxsock = (s > m_maxsock) ? s : m_maxsock;
         }
         else
         {
            log(p, "add", (int32_t)p -> GetSocket(), "Trying to add socket with SetCloseAndDelete() true", ::aura::log::level_warning);
         }
         // only add to m_fds (process fd_set events) if
         //  slave handler and detached/detaching socket
         //  master handler and non-detached socket
         if (!(m_slave ^ p -> IsDetach()))
         {
            m_fds.add_tail(s);
         }
         m_sockets[s] = p;
         //
         m_add.remove_key(s);
      }

      fd_set rfds;
      fd_set wfds;
      fd_set efds;

      FD_COPY(&m_rfds, &rfds);
      FD_COPY(&m_wfds, &wfds);
      FD_COPY(&m_efds, &efds);

      int32_t n;
      dw1 = ::get_tick_count();
      if (m_b_use_mutex)
      {
         m_pmutex->unlock();
         n = ::select( (int32_t)(m_maxsock + 1),&rfds,&wfds,&efds,tsel);
         m_iSelectErrno = Errno;
         m_pmutex->lock();
      }
      else
      {
         n = ::select( (int32_t)(m_maxsock + 1),&rfds,&wfds,&efds,tsel);
         m_iSelectErrno = Errno;
      }
      dw2 = ::get_tick_count();
      //TRACE("socket_handler::Select select time = %d, %d, %d\n", dw1, dw2, dw2 - dw1);
      if(n == 0)
      {
         socket_map::pair * ppair = m_sockets.PGetFirstAssoc();
         while(ppair != NULL)
         {
            if(ppair->m_element2 != NULL)
            {
               //TRACE("tmout sckt(%d):\"%s\"", ppair->m_element1, ppair->m_element2->oprop("meta_info").get_string());

               SOCKET s = ppair->m_element1;

               sp(class socket) psocket = ppair->m_element2;

               TRACE("tmout sckt(%d):remote_address=\"%s\""          , s, psocket->GetRemoteAddress().get_display_number().c_str());
//               TRACE("tmout sckt(%d):remote_canonical_name=\"%s\""   , s, psocket->GetRemoteAddress().get_canonical_name());
               TRACE("tmout sckt(%d):short_desc=\"%s\""              , s, psocket->get_short_description().c_str());

               time_t tnow = time(NULL);

               if(psocket->Timeout(tnow))
               {
                  sp(stream_socket) pstreamsocket = (psocket);
                  if(pstreamsocket != NULL && pstreamsocket->Connecting())
                     psocket->OnConnectTimeout();
                  else
                     psocket->OnTimeout();
                  psocket->SetTimeout(0);
               }
//               else
  //             {
    //              psocket->OnException();
      //         }
            }
            ppair = m_sockets.PGetNextAssoc(ppair);
            n--;
         }
      }
      else if (n == -1)
      {
         /*
            EBADF  An invalid file descriptor was given in one of the sets.
            EINTR  A non blocked signal was caught.
            EINVAL n is negative. Or struct timeval contains bad time values (<0).
            ENOMEM select was unable to allocate primitive::memory for internal tables.
         */
         if (Errno != m_preverror || m_errcnt++ % 10000 == 0)
         {
            log(NULL, "select", Errno, StrError(Errno));
            int32_t iError = Errno;
#ifdef LINUX
            TRACE("m_maxsock: %d\n", m_maxsock);
            TRACE("sockets::socket_handler select error : %s (%d)", strerror(Errno), Errno);
#else
            TRACE("sockets::socket_handler select error : %s (%d)", get_system_error_message(iError).c_str(), iError);
#endif

            if(iError == 10022)
            {
               TRACE("WSEINVAL");
            }

            // test bad fd
            for (SOCKET i = 0; i <= m_maxsock; i++)
            {
               bool t = false;
               FD_ZERO(&rfds);
               FD_ZERO(&wfds);
               FD_ZERO(&efds);
               if (FD_ISSET(i, &m_rfds))
               {
                  FD_SET(i, &rfds);
                  t = true;
               }
               if (FD_ISSET(i, &m_wfds))
               {
                  FD_SET(i, &wfds);
                  t = true;
               }
               if (FD_ISSET(i, &m_efds))
               {
                  FD_SET(i, &efds);
                  t = true;
               }
               sp(base_socket) psocket;
               if (t && m_sockets.Lookup(i, psocket))
               {
                  TRACE("Bad fd in fd_set: %d\n", i);
                  TRACE("Deleting and removing socket: %d\n", i);
                  try
                  {
                     psocket.release();
                  }
                  catch(...)
                  {
                  }
                  m_sockets.remove_key(i);
               }
            }

            m_preverror = Errno;
         }

         /// \no more todo rebuild fd_set's from active sockets list (m_sockets) here
         /// done : http://jbmon.googlecode.com/svn/trunk/sockets/SocketHandler.cpp : rebuild fd_set's from active sockets list (m_sockets) here
         {

            FD_ZERO(&rfds);
		      FD_ZERO(&wfds);
		      FD_ZERO(&efds);

            SOCKET s;
            sp(base_socket) psocket;
            POSITION pos = m_sockets.get_start_position();
            while(pos != NULL)
            {

               m_sockets.get_next_assoc(pos, s, psocket);

               try
               {

			         if(s == psocket->GetSocket())
			         {
				         fd_set fds;
				         FD_ZERO(&fds);
				         FD_SET(s, &fds);
				         struct timeval tv;
				         tv.tv_sec = 0;
				         tv.tv_usec = 0;
				         int32_t n = ::select((int32_t) (s + 1), &fds, NULL, NULL, &tv);
				         if (n == -1)
				         {
					         // %! bad fd, remove
					         log(psocket, "Select", (int32_t) s, "Bad fd in fd_set (2)"); // , LOG_LEVEL_ERROR);
					         m_fds_erase.push_back(s);
				         }
				         else
				         {
                        bool bAnySet = false;
					         if(FD_ISSET(s, &m_rfds))
                        {
						         FD_SET(s, &rfds);
                           bAnySet = true;
                        }
					         if(FD_ISSET(s, &m_wfds))
                        {
						         FD_SET(s, &wfds);
                           bAnySet = true;
                        }
					         if(FD_ISSET(s, &m_efds))
                        {
						         FD_SET(s, &efds);
                           bAnySet = true;
                        }
                        if(!bAnySet)
                        {
					            // %! none set
					            log(psocket, "Select", (int32_t) s, "No fd in fd_set"); // , LOG_LEVEL_ERROR);
					            m_fds_erase.push_back(s);
                        }
				         }
			         }
			         else
			         {
				         // %! mismatch
				         log(psocket, "Select", (int32_t)s, "Bad fd in fd_set (3)"); // , LOG_LEVEL_ERROR);
				         m_fds_erase.push_back(s);
			         }

               }
               catch(...)
               {
				      // general error
				      log(psocket, "Select", (int32_t)s, "Bad fd in fd_set (3)"); // , LOG_LEVEL_ERROR);
				      m_fds_erase.push_back(s);
               }
            }
		      m_rfds = rfds;
		      m_wfds = wfds;
		      m_efds = efds;
         }
      }
      else
      if (!n)
      {
         m_preverror = -1;
      }
      else
      if (n > 0)
      {
         POSITION pos = m_fds.get_head_position();
         for(; pos != NULL && n;)
         {
            SOCKET socket = m_fds.get_next(pos);;
            if (FD_ISSET(socket, &rfds))
            {
               sp(base_socket) psocket = NULL;
               if(m_sockets.Lookup(socket, psocket)) // found
               {
                  // new SSL negotiate method
                  if(psocket->IsSSLNegotiate())
                  {
                     psocket->SSLNegotiate();
                  }
                  else
                  {
                     psocket->OnRead();
                  }
               }
               else
               {
                  log(NULL, "GetSocket/handler/1", (int32_t) socket, "Did not find expected socket using file descriptor", ::aura::log::level_warning);
               }
               n--;
            }
            if (FD_ISSET(socket, &wfds))
            {
               sp(base_socket) psocket = NULL;
               if(m_sockets.Lookup(socket, psocket)) // found
               {
                  // new SSL negotiate method
                  if(psocket->IsSSLNegotiate())
                  {
                     psocket->SSLNegotiate();
                  }
                  else
                  {
                     psocket->OnWrite();
                  }
               }
               else
               {
                  log(NULL, "GetSocket/handler/2", (int32_t) socket, "Did not find expected socket using file descriptor", ::aura::log::level_warning);
               }
               n--;
            }
            if(FD_ISSET(socket, &efds))
            {
               sp(base_socket) psocket = NULL;
               if(m_sockets.Lookup(socket, psocket)) // found
               {
                  time_t tnow = time(NULL);
                    if(psocket->Timeout(tnow))
                  {
                     sp(stream_socket) pstreamsocket = (psocket);
                     if(pstreamsocket != NULL && pstreamsocket->Connecting())
                        psocket->OnConnectTimeout();
                     else
                        psocket->OnTimeout();
                     psocket->SetTimeout(0);
                  }
                  else
                  {
                     psocket->OnException();
                  }
               }
               else
               {
                  log(NULL, "GetSocket/handler/3", (int32_t) socket, "Did not find expected socket using file descriptor", ::aura::log::level_warning);
               }
               n--;
            }
         } // m_fds loop
         m_preverror = -1;
      } // if (n > 0)

      // check CallOnConnect - EVENT
      if (m_fds_callonconnect.get_size())
      {
         socket_id_list tmp = m_fds_callonconnect;
         POSITION pos = tmp.get_head_position();
         for(; pos != NULL; )
         {
            SOCKET socket = tmp.get_next(pos);
            sp(base_socket) psocket = NULL;
            if(!m_sockets.Lookup(socket, psocket)) // not found
            {
               log(NULL, "GetSocket/handler/4", (int32_t)socket, "Did not find expected socket using file descriptor", ::aura::log::level_warning);
            }
            if(psocket != NULL)
            {
               sp(tcp_socket)tcp = (psocket);
               if(tcp != NULL)
               {
                  if (tcp -> CallOnConnect() && psocket -> Ready() )
                  {
                     psocket -> SetConnected(); // moved here from inside if (tcp) check below
                     if (psocket -> IsSSL()) // SSL Enabled socket
                        psocket -> OnSSLConnect();
                     else
                     if (psocket -> Socks4())
                        psocket -> OnSocks4Connect();
                     else
                     {

                        if (tcp)
                        {
                           if (tcp -> GetOutputLength())
                           {
                              psocket -> OnWrite();
                           }
                        }
                        if (tcp && tcp -> IsReconnect())
                           psocket -> OnReconnect();
                        else
                        {
                           log(tcp, "Calling OnConnect", 0, "Because CallOnConnect", ::aura::log::level_info);
                           psocket -> OnConnect();
                        }
                     }
                     tcp -> SetCallOnConnect( false );
                     AddList(psocket -> GetSocket(), LIST_CALLONCONNECT, false);
                  }
               }
            }
         }
      }
      bool check_max_fd = false;
      // check detach of socket if master handler - EVENT
      if (!m_slave && m_fds_detach.get_size())
      {
         // %! why not using tmp list here??!?
         POSITION pos = m_fds_detach.get_head_position();
         for(; pos != NULL; )
         {
            sp(base_socket) p = NULL;
            SOCKET socket = m_fds_detach.get_next(pos);
            if(m_sockets.Lookup(socket, p) && p != NULL)
            {
               if (p -> IsDetach())
               {
                  if(p->GetSocket() != INVALID_SOCKET)
                  {

                     set(p -> GetSocket(), false, false, false);

                     // After DetachSocket(), all calls to Handler() will return a reference
                     // to the new slave socket_handler running in the new thread.
                     try
                     {

                        p -> DetachSocket();

                     }
                     catch(...)
                     {

                     }

                  }

                  // Adding the file descriptor to m_fds_erase will now also remove the
                  // socket from the detach queue - tnx knightmad
                  //m_fds_erase.add_tail(p -> GetSocket());

                  m_fds_detach.remove(socket);
                  m_fds.remove(socket);
                  m_sockets.remove_key(socket);
                  check_max_fd = true;
               }
            }
         }
      }
      // check Connecting - connection timeout - conditional event
      if (m_fds_timeout.get_size())
      {
         time_t tnow = time(NULL);
         if (tnow != m_tlast)
         {
            socket_id_list tmp = m_fds_timeout;
            //TRACE("Checking %d socket(s) for timeout\n", tmp.get_size());
            POSITION pos = tmp.get_head_position();
            for(; pos != NULL;)
            {
               sp(base_socket) p = NULL;
               SOCKET socket = tmp.get_next(pos);
               if (!m_sockets.Lookup(socket, p)) // not found
               {
                  if(!m_add.Lookup(socket, p))
                  {
                     log(NULL, "GetSocket/handler/6", (int32_t)socket, "Did not find expected socket using file descriptor", ::aura::log::level_warning);
                  }
               }
               if (p)
               {
                  if (p -> Timeout(tnow))
                  {
                     sp(stream_socket)scp = (p);
                     if (scp && scp -> Connecting())
                        p -> OnConnectTimeout();
                     else
                        p -> OnTimeout();
                     p -> SetTimeout(0);
                  }
               }
            }
            m_tlast = tnow;
         } // tnow != tlast
      }
      // check retry client connect - EVENT
      if (m_fds_retry.get_size())
      {
         socket_id_list tmp = m_fds_retry;
         POSITION pos = tmp.get_head_position();
         for(; pos != NULL;)
         {
            SOCKET socket = tmp.get_next(pos);
            sp(base_socket) p = NULL;
            if(m_sockets.Lookup(socket, p))
            {
               log(NULL, "GetSocket/handler/7", (int32_t)socket, "Did not find expected socket using file descriptor", ::aura::log::level_warning);
            }
            if (p)
            {
               sp(tcp_socket)tcp = (p);
               if(tcp != NULL)
               {
                  if(tcp -> RetryClientConnect())
                  {

                     SOCKET nn = socket; //(*it3).m_element1;
                     tcp -> SetRetryClientConnect(false);
                     //TRACE("close() before retry client connect\n");
                     p -> close(); // removes from m_fds_retry
                     ::net::address ad = p -> GetClientRemoteAddress();
                     if(ad.is_valid())
                     {
                        tcp -> open(ad);
                     }
                     else
                     {
                        log(p, "RetryClientConnect", 0, "no address", ::aura::log::level_error);
                     }
                     add(p);
                     m_fds_erase.add_tail(nn);
                  }
               }
            }
         }
      }
      // check close and delete - conditional event
      if(m_fds_close.get_size())
      {
         socket_id_list tmp = m_fds_close;
         //TRACE("m_fds_close.size() == %d\n", (int32_t)m_fds_close.get_size());
         POSITION pos = tmp.get_head_position();
         while(pos != NULL)
         {
            SOCKET socket = tmp.get_next(pos);
            sp(base_socket) p = NULL;
            if(!m_sockets.Lookup(socket, p)) // not found
            {
               if(!m_add.Lookup(socket, p))
               {
                     log(NULL, "GetSocket/handler/8", (int32_t)socket, "Did not find expected socket using file descriptor", ::aura::log::level_warning);
               }
            }
            if (p)
            {
               if (p -> CloseAndDelete() )
               {
                  sp(tcp_socket)tcp = (p);
                  // new graceful tcp - flush and close timeout 5s
                  if (tcp && p -> IsConnected() && tcp -> GetFlushBeforeClose() &&
                     !tcp -> IsSSL() &&
                     p -> TimeSinceClose() < 5)
                  {
   //TRACE(" close(1)\n");
                     if (tcp -> GetOutputLength())
                     {
                        log(p, "Closing", (int32_t)tcp -> GetOutputLength(), "Sending all data before closing", ::aura::log::level_info);
                     }
                     else // shutdown write when output buffer is is_empty
                     if (!(tcp -> GetShutdown() & SHUT_WR))
                     {
                        if (socket != INVALID_SOCKET && shutdown(socket, SHUT_WR) == -1)
                        {
                           log(p, "graceful shutdown", Errno, StrError(Errno), ::aura::log::level_error);
                        }
                        tcp -> SetShutdown(SHUT_WR);
                     }
                  }
                  else
                  if (tcp && p -> IsConnected() && tcp -> Reconnect())
                  {
                     //SOCKET nn = *it; //(*it3).m_element1;
   //TRACE(" close(2) fd %d\n", socket);
                     p -> SetCloseAndDelete(false);
                     tcp -> SetIsReconnect();
                     p -> SetConnected(false);
                     //TRACE("close() before reconnect\n");
                     p -> close(); // dispose of old file descriptor (open creates a new)
                     p -> OnDisconnect();
                     ::net::address ad = p -> GetClientRemoteAddress();
                     if (ad.is_valid())
                     {
                        tcp -> open(ad);
                     }
                     else
                     {
                        log(p, "Reconnect", 0, "no address", ::aura::log::level_error);
                     }
                     tcp -> ResetConnectionRetries();
                     add(p);
                     m_fds_erase.add_tail(socket);
                  }
                  else
                  {
                     //TRACE(" close(3) fd %d GetSocket() %d\n", socket, p -> GetSocket());
                     if (tcp && p -> IsConnected() && tcp -> GetOutputLength())
                     {
                        log(p, "Closing", (int32_t)tcp -> GetOutputLength(), "Closing socket while data still left to send", ::aura::log::level_warning);
                     }
                     if(p -> Retain() && !p -> Lost())
                     {
                        pool_socket *p2 = new pool_socket(*this, p);
                        p2 -> SetDeleteByHandler();
                        add(p2);
                        //
                        p -> SetCloseAndDelete(false); // added - remove from m_fds_close
                     }
                     else
                     {
                        set(p -> GetSocket(),false,false,false);
                        //TRACE("close() before OnDelete\n");
                        p -> close();
                     }
                     p -> OnDelete();
                     if (p -> DeleteByHandler())
                     {
                        p -> SetErasedByHandler();
                     }

                  }
               }
            }
            m_fds_erase.add_tail(socket);
         }
      }

      // check erased sockets
      while(m_fds_erase.get_size())
      {
         SOCKET socket = m_fds_erase.remove_head();
         m_fds_detach.remove(socket);
         m_fds.remove(socket);
         sp(::sockets::socket) psocket = NULL;
         /*if(m_sockets.Lookup(socket, psocket))
         {
            if(m_slave)
            {
               if(psocket != NULL)
               {
                  try
                  {
                     delete psocket;
                  }
                  catch(...)
                  {
                  }
               }
            }*/
            m_sockets.remove_key(socket);
         //}
         check_max_fd = true;
      }

      // calculate MAX file descriptor for select() call
      if (check_max_fd)
      {
         m_maxsock = m_fds.maximum(0);
      }
      // remove add's that fizzed
      while(m_delete.get_size() > 0)
      {
         sp(socket) p = m_delete.remove_head();
         p -> OnDelete();
         if (p -> DeleteByHandler()
            && !(m_slave ^ p -> IsDetached())
            )
         {
            p -> SetErasedByHandler();
            bool again = false;
            do
            {
               again = false;
               POSITION posSrc = m_trigger_src.get_start_position();
               while(posSrc != NULL)
               {
                  SOCKET id = 0;
                  sp(base_socket) src = NULL;
                  m_trigger_src.get_next_assoc(posSrc, id, src);
                  if (src == p)
                  {
                     POSITION posDst = m_trigger_dst[id].get_start_position();
                     while(posDst != NULL)
                     {
                        base_socket * dst = NULL;
                        bool b = false;
                        m_trigger_dst[id].get_next_assoc(posDst, dst, b);
                        if (Valid(dst))
                        {
                           dst->OnCancelled(id);
                        }
                     }
                     m_trigger_src.remove_key(id);
                     m_trigger_dst.remove_key(id);
                     again = true;
                     break;
                  }
               }
            } while (again);
            p.release();
         }
      }
      return n;
   }


   bool socket_handler::Resolving(base_socket * p0)
   {
      return m_resolve_q.PLookup(p0) != NULL;
   }


   bool socket_handler::Valid(base_socket * p0)
   {
      socket_map::pair * ppair = m_sockets.PGetFirstAssoc();
      while(ppair != NULL)
      {
         if (p0 == ppair->m_element2)
            return true;
         ppair = m_sockets.PGetNextAssoc(ppair);
      }
      return false;
   }


   bool socket_handler::OkToAccept(base_socket *)
   {

      return true;

   }


   size_t socket_handler::get_count()
   {
   /*
   printf(" m_sockets : %d\n", m_sockets.size());
   printf(" m_add     : %d\n", m_add.size());
   printf(" m_delete  : %d\n", m_delete.size());
   */
      return m_sockets.get_size() + m_add.get_size() + m_delete.get_size();
   }


   void socket_handler::SetSocks4Host(in_addr a)
   {
      m_socks4_host = a;
   }


   void socket_handler::SetSocks4Host(const string & host)
   {
      Session.sockets().net().convert(m_socks4_host, host);
   }


   void socket_handler::SetSocks4Port(port_t port)
   {
      m_socks4_port = port;
   }


   void socket_handler::SetSocks4Userid(const string & id)
   {
      m_socks4_userid = id;
   }


   int32_t socket_handler::Resolve(base_socket * p, const string & host,port_t port)
   {
      // check cache
      sp(resolv_socket) resolv = canew(resolv_socket(*this, p, host, port));
      resolv -> SetId(++m_resolv_id);
      resolv -> SetDeleteByHandler();
      in_addr local;
      Session.sockets().net().convert(local, "127.0.0.1");
      if (!resolv -> open(::net::address(local, m_resolver_port)))
      {
         log(resolv, "Resolve", -1, "Can't connect to local resolve server", ::aura::log::level_fatal);
      }
      add(resolv);
      m_resolve_q[p] = true;
      TRACE(" *** Resolve '%s:%d' id#%d  m_resolve_q size: %d  p: %p\n", host.c_str(), port, resolv -> GetId(), m_resolve_q.get_size(), p);
      return resolv -> GetId();
   }


   int32_t socket_handler::Resolve6(base_socket * p,const string & host,port_t port)
   {
      // check cache
      sp(resolv_socket) resolv = canew(resolv_socket(*this, p, host, port, true));
      resolv -> SetId(++m_resolv_id);
      resolv -> SetDeleteByHandler();
      in_addr local;
      Session.sockets().net().convert(local, "127.0.0.1");
      if (!resolv -> open(::net::address(local, m_resolver_port)))
      {
         log(resolv, "Resolve", -1, "Can't connect to local resolve server", ::aura::log::level_fatal);
      }
      add(resolv);
      m_resolve_q[p] = true;
      return resolv -> GetId();
   }


   int32_t socket_handler::Resolve(base_socket * p, in_addr a)
   {
      // check cache
      sp(resolv_socket) resolv = canew(resolv_socket(*this, p, a));
      resolv -> SetId(++m_resolv_id);
      resolv -> SetDeleteByHandler();
      in_addr local;
      Session.sockets().net().convert(local, "127.0.0.1");
      if (!resolv -> open(::net::address(local, m_resolver_port)))
      {
         log(resolv, "Resolve", -1, "Can't connect to local resolve server", ::aura::log::level_fatal);
      }
      add(resolv);
      m_resolve_q[p] = true;
      return resolv -> GetId();
   }


   int32_t socket_handler::Resolve(base_socket * p, in6_addr& a)
   {
      // check cache
      sp(resolv_socket) resolv = canew(resolv_socket(*this, p, a));
      resolv -> SetId(++m_resolv_id);
      resolv -> SetDeleteByHandler();
      in_addr local;
      Session.sockets().net().convert(local, "127.0.0.1");
      if (!resolv -> open(::net::address(local, m_resolver_port)))
      {
         log(resolv, "Resolve", -1, "Can't connect to local resolve server", ::aura::log::level_fatal);
      }
      add(resolv);
      m_resolve_q[p] = true;
      return resolv -> GetId();
   }


   void socket_handler::EnableResolver(port_t port)
   {
      if (!m_resolver)
      {
         m_resolver_port = port;
         m_resolver = canew(resolv_server(get_app(), port));
      }
   }


   bool socket_handler::ResolverReady()
   {
      return m_resolver ? m_resolver -> Ready() : false;
   }

   void socket_handler::SetSocks4TryDirect(bool x)
   {
      m_bTryDirect = x;
   }


   in_addr socket_handler::GetSocks4Host()
   {
      return m_socks4_host;
   }


   port_t socket_handler::GetSocks4Port()
   {
      return m_socks4_port;
   }


   const string & socket_handler::GetSocks4Userid()
   {
      return m_socks4_userid;
   }


   bool socket_handler::Socks4TryDirect()
   {
      return m_bTryDirect;
   }

   bool socket_handler::ResolverEnabled()
   {
      return m_resolver ? true : false;
   }


   port_t socket_handler::GetResolverPort()
   {
      return m_resolver_port;
   }

   base_socket_handler::pool_socket *socket_handler::FindConnection(int32_t type, const string & protocol, const ::net::address & ad)
   {
      socket_map::pair * ppair = m_sockets.PGetFirstAssoc();
      while(ppair != NULL)
      {
         pool_socket *pools = dynamic_cast<pool_socket *>(ppair->m_element2.m_p);
         if (pools)
         {
            if (pools -> GetSocketType() == type &&
                pools -> GetSocketProtocol() == protocol &&
   // %!             pools -> GetClientRemoteAddress() &&
                pools -> GetClientRemoteAddress() == ad)
            {
               m_sockets.remove_key(ppair->m_element1);
               pools -> SetRetain(); // avoid close in socket destructor
               return pools; // Caller is responsible that this socket is deleted
            }
         }
         ppair = m_sockets.PGetNextAssoc(ppair);
      }
      return NULL;
   }


   void socket_handler::EnablePool(bool x)
   {
      m_b_enable_pool = x;
   }


   bool socket_handler::PoolEnabled()
   {
      return m_b_enable_pool;
   }


   void socket_handler::remove(base_socket * p)
   {
      bool b;
      if(m_resolve_q.Lookup(p, b))
         m_resolve_q.remove_key(p);
      if(p -> ErasedByHandler())
      {
         return;
      }
      socket_map::pair * ppair = m_sockets.PGetFirstAssoc();
      while(ppair != NULL)
      {
         if(ppair->m_element2 == p)
         {
            log(p, "remove", -1, "socket destructor called while still in use", ::aura::log::level_warning);
            m_sockets.remove_key(ppair->m_element1);
            return;
         }
         ppair = m_sockets.PGetNextAssoc(ppair);
      }
      socket_map::pair * ppair2 = m_add.PGetFirstAssoc();
      while(ppair2 != NULL)
      {
         if (ppair2->m_element2 == p)
         {
            log(p, "remove", -2, "socket destructor called while still in use", ::aura::log::level_warning);
            m_add.remove_key(ppair2->m_element1);
            return;
         }
         ppair2 = m_add.PGetNextAssoc(ppair2);
      }
      if(m_delete.remove(p) > 0)
      {
         log(p, "remove", -3, "socket destructor called while still in use", ::aura::log::level_warning);
         return;
      }
   }


   void socket_handler::CheckSanity()
   {
      CheckList(m_fds, "active sockets"); // active sockets
      CheckList(m_fds_erase, "sockets to be erased"); // should always be is_empty anyway
      CheckList(m_fds_callonconnect, "checklist CallOnConnect");
      CheckList(m_fds_detach, "checklist detach");
      CheckList(m_fds_timeout, "checklist Timeout");
      CheckList(m_fds_retry, "checklist retry client connect");
      CheckList(m_fds_close, "checklist close and delete");
   }


   void socket_handler::CheckList(socket_id_list& ref,const string & listname)
   {
      POSITION pos = ref.get_head_position();
      while(pos != NULL)
      {
         SOCKET s = ref.get_next(pos);
         if(m_sockets.PLookup(s) != NULL)
            continue;
         if(m_add.PLookup(s) != NULL)
            continue;
         bool found = false;
         POSITION pos = m_delete.get_head_position();
         while(pos != NULL)
         {
            sp(socket) p = m_delete.get_next(pos);
            if(p->GetSocket() == s)
            {
               found = true;
               break;
            }
         }
         if (!found)
         {
            TRACE("CheckList failed for \"%s\": fd %d\n", listname.c_str(), s);
         }
      }
   }


   void socket_handler::AddList(SOCKET s,list_t which_one,bool add)
   {
      if (s == INVALID_SOCKET)
      {
         TRACE("AddList:  invalid_socket\n");
         return;
      }
      socket_id_list& ref =
         (which_one == LIST_CALLONCONNECT) ? m_fds_callonconnect :
         (which_one == LIST_DETACH) ? m_fds_detach :
         (which_one == LIST_TIMEOUT) ? m_fds_timeout :
         (which_one == LIST_RETRY) ? m_fds_retry :
         (which_one == LIST_CLOSE) ? m_fds_close : m_fds_close;
      if (add)
      {
/*         TRACE("AddList;  %5d: %s: %s\n", s, (which_one == LIST_CALLONCONNECT) ? "CallOnConnect" :
            (which_one == LIST_DETACH) ? "detach" :
            (which_one == LIST_TIMEOUT) ? "Timeout" :
            (which_one == LIST_RETRY) ? "Retry" :
            (which_one == LIST_CLOSE) ? "close" : "<undef>",
            add ? "add" : "remove");*/
      }
      if (add)
      {
         ref.add_tail_unique(s);
         return;
      }
      // remove
      ref.remove(s);
      //TRACE("/AddList\n");
   }


   int32_t socket_handler::TriggerID(base_socket * src)
   {
      int32_t id = m_next_trigger_id++;
      m_trigger_src[id] = src;
      return id;
   }


   bool socket_handler::Subscribe(int32_t id, base_socket * dst)
   {
      if(m_trigger_src.PLookup(id) != NULL)
      {
         if(m_trigger_dst[id].PLookup(dst) != NULL)
         {
            m_trigger_dst[id][dst] = true;
            return true;
         }
         log(dst, "Subscribe", id, "Already subscribed", ::aura::log::level_info);
         return false;
      }
      log(dst, "Subscribe", id, "Trigger id not found", ::aura::log::level_info);
      return false;
   }


   bool socket_handler::Unsubscribe(int32_t id, base_socket * dst)
   {
      if (m_trigger_src.PLookup(id) != NULL)
      {
         if(m_trigger_dst[id].PLookup(dst) != NULL)
         {
            m_trigger_dst[id].remove_key(dst);
            return true;
         }
         log(dst, "Unsubscribe", id, "Not subscribed", ::aura::log::level_info);
         return false;
      }
      log(dst, "Unsubscribe", id, "Trigger id not found", ::aura::log::level_info);
      return false;
   }


   void socket_handler::Trigger(int32_t id, socket::trigger_data& data, bool erase)
   {
      if(m_trigger_src.PLookup(id) != NULL)
      {
         data.SetSource( m_trigger_src[id]);
         socket_bool::pair * ppair = m_trigger_dst[id].PGetFirstAssoc();
         while(ppair != NULL);
         {
            sp(socket) dst = ppair->m_element1;
            if (Valid(dst))
            {
               dst->OnTrigger(id, data);
            }
            ppair = m_trigger_dst[id].PGetNextAssoc(ppair);
         }
         if (erase)
         {
            m_trigger_src.remove_key(id);
            m_trigger_dst.remove_key(id);
         }
      }
      else
      {
         log(NULL, "Trigger", id, "Trigger id not found", ::aura::log::level_info);
      }
   }


}




