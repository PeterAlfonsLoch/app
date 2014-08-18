/** \file socket_handler.cpp
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
#include "framework.h"
//#include <stdlib.h>
//#include <errno.h>

namespace sockets
{


   socket_handler::socket_handler(::base::application * papp, logger * plogger) :
   element(papp),
   base_socket_handler(papp, plogger),
   m_mutex(m_mutex),
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
      
      memset(&m_socks4_host, 0, sizeof(m_socks4_host));

/*      FD_ZERO(&m_rfds);
      FD_ZERO(&m_wfds);
      FD_ZERO(&m_efds);*/
   }


   socket_handler::socket_handler(::base::application * papp, mutex& mutex, logger *plogger) :
   element(papp),
   base_socket_handler(papp, plogger)
   ,m_mutex(mutex)
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

      memset(&m_socks4_host, 0, sizeof(m_socks4_host));

      m_mutex.lock();

/*      FD_ZERO(&m_rfds);
      FD_ZERO(&m_wfds);
      FD_ZERO(&m_efds);*/
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
                     delete p;
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
         m_mutex.unlock();
      }
   }


   mutex& socket_handler::GetMutex() const
   {
      return m_mutex;
   }


   void socket_handler::SetSlave(bool x)
   {
      m_slave = x;
   }


   bool socket_handler::IsSlave()
   {
      return m_slave;
   }


   void socket_handler::add(base_socket * p)
   {
      if (p -> GetSocket() == INVALID_SOCKET)
      {
         log(p, "add", -1, "Invalid socket", ::core::log::level_warning);
         if (p -> CloseAndDelete())
         {
            m_delete.add_tail(p);
         }
         return;
      }
      sp(base_socket) plookup;
      if (m_add.Lookup(p -> GetSocket(), plookup))
      {
         log(p, "add", (int)p -> GetSocket(), "Attempt to add socket already in add queue", ::core::log::level_fatal);
         m_delete.add_tail(p);
         return;
      }
      m_add[p -> GetSocket()] = p;
      p->m_estatus = socket::status_ok;
   }


   void socket_handler::get(SOCKET s,bool& r,bool& w,bool& e)
   {
      if (s >= 0)
      {
/*         r = FD_ISSET(s, &m_rfds) ? true : false;
         w = FD_ISSET(s, &m_wfds) ? true : false;
         e = FD_ISSET(s, &m_efds) ? true : false;*/
      }
   }


   void socket_handler::set(SOCKET s,bool bRead,bool bWrite,bool bException)
   {
   //TRACE("Set(%d, %s, %s, %s)\n", s, bRead ? "true" : "false", bWrite ? "true" : "false", bException ? "true" : "false");
      if (s >= 0)
      {
/*         if (bRead)
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
         }*/
      }
   }


   int socket_handler::select(int32_t lSeconds, int32_t lMicroseconds)
   {
      
      struct timeval timeval;

      timeval.tv_sec    = lSeconds;
      timeval.tv_usec   = lMicroseconds;

      //return 0;

      return select(&timeval);

   }


   int socket_handler::select()
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


   int socket_handler::select(struct timeval *tsel)
   {

      POSITION pos = m_add.get_start_position();
      SOCKET s;
      sp(base_socket) psocket;
      while(pos != NULL)
      {
         s = 0;
         psocket = NULL;
         m_add.get_next_assoc(pos, s, psocket);

         if(psocket != NULL)
         {
            m_sockets.set_at(s, psocket);
            m_add.remove_key(s);
            break;
         }
      }

      pos = m_sockets.get_start_position();



      while(pos != NULL)
      {
         s = 0;
         psocket = NULL;
         m_sockets.get_next_assoc(pos, s, psocket);
         if(psocket != NULL)
         {
            psocket->m_event.wait(seconds(tsel->tv_sec));
            if(psocket->is_connecting())
            {
               psocket->m_estatus = ::sockets::socket::status_connection_timed_out;
               remove(psocket);
               break;
            }
            psocket->run();
            stream_socket * pstreamsocket = psocket.cast < stream_socket >();
            if(pstreamsocket != NULL)
            {
               if(pstreamsocket->m_posdata->m_writer != nullptr)
               {

                  auto writer = pstreamsocket->m_posdata->m_writer;
                  
                  psocket->m_event.ResetEvent();

                  writer->StoreAsync()->Completed = ref new ::Windows::Foundation::AsyncOperationCompletedHandler < unsigned int > ([=] 
                     (::Windows::Foundation::IAsyncOperation < unsigned int > ^ action, ::Windows::Foundation::AsyncStatus status)
                  {
                     writer->DetachStream();
                     psocket->m_event.SetEvent();
                  });

                  pstreamsocket->m_posdata->m_writer = nullptr;

               }
            }
            if(psocket->m_bClose)
            {
               remove(psocket);
//               delete psocket;
               break;
            }
//            psocket->step();
         }
      }
      return 0;
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

      System.net().convert(m_socks4_host, host);

   }


   void socket_handler::SetSocks4Port(port_t port)
   {

      m_socks4_port = port;

   }


   void socket_handler::SetSocks4Userid(const string & id)
   {

      m_socks4_userid = id;

   }


   int socket_handler::Resolve(base_socket * p,const string & host,port_t port)
   {
      // check cache
      resolv_socket *resolv = new resolv_socket(*this, p, host, port);
      resolv -> SetId(++m_resolv_id);
      resolv -> SetDeleteByHandler();
      ::net::address local("127.0.0.1", m_resolver_port);
      //System.net().convert(local, "127.0.0.1");
      if (!resolv -> open(local))
      {
         log(resolv, "Resolve", -1, "Can't connect to local resolve server", ::core::log::level_fatal);
      }
      add(resolv);
      m_resolve_q[p] = true;
      TRACE(" *** Resolve '%s:%d' id#%d  m_resolve_q size: %d  p: %p\n", host, port, resolv -> GetId(), m_resolve_q.get_size(), p);
      return resolv -> GetId();
   }


   int socket_handler::Resolve6(base_socket * p,const string & host,port_t port)
   {
      // check cache
      resolv_socket *resolv = new resolv_socket(*this, p, host, port, true);
      resolv -> SetId(++m_resolv_id);
      resolv -> SetDeleteByHandler();
      ::net::address local("127.0.0.1", m_resolver_port);
      if (!resolv -> open(local))
      {
         log(resolv, "Resolve", -1, "Can't connect to local resolve server", ::core::log::level_fatal);
      }
      add(resolv);
      m_resolve_q[p] = true;
      return resolv -> GetId();
   }


   int socket_handler::Resolve(base_socket * p, in_addr a)
   {
      // check cache
      resolv_socket *resolv = new resolv_socket(*this, p, a);
      resolv -> SetId(++m_resolv_id);
      resolv -> SetDeleteByHandler();
//      ipaddr_t local;
      ::net::address local("127.0.0.1", m_resolver_port);
      if (!resolv -> open(local))
      {
         log(resolv, "Resolve", -1, "Can't connect to local resolve server", ::core::log::level_fatal);
      }
      add(resolv);
      m_resolve_q[p] = true;
      return resolv -> GetId();
   }


   int socket_handler::Resolve(base_socket * p,in6_addr& a)
   {
      // check cache
      resolv_socket *resolv = new resolv_socket(*this, p, a);
      resolv -> SetId(++m_resolv_id);
      resolv -> SetDeleteByHandler();
      //ipaddr_t local;
      ::net::address local("127.0.0.1", m_resolver_port);
      if (!resolv -> open(local))
      {
         log(resolv, "Resolve", -1, "Can't connect to local resolve server", ::core::log::level_fatal);
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
         m_resolver = new resolv_server(get_app(), port);
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

   base_socket_handler::pool_socket *socket_handler::FindConnection(int type,const string & protocol, const ::net::address & ad)
   {
      socket_map::pair * ppair = m_sockets.PGetFirstAssoc();
      while(ppair != NULL)
      {
         pool_socket * pools = ppair->m_element2.cast < pool_socket > ();
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
            log(p, "remove", -1, "socket destructor called while still in use", ::core::log::level_warning);
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
            log(p, "remove", -2, "socket destructor called while still in use", ::core::log::level_warning);
            m_add.remove_key(ppair2->m_element1);
            return;
         }
         ppair2 = m_add.PGetNextAssoc(ppair2);
      }
      if(m_delete.remove(p) > 0)
      {
         log(p, "remove", -3, "socket destructor called while still in use", ::core::log::level_warning);
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
            sp(base_socket) p = m_delete.get_next(pos);
            if(p->GetSocket() == s)
            {
               found = true;
               break;
            }
         }
         if (!found)
         {
            TRACE("CheckList failed for \"%s\": fd %d\n", listname, s);
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


   int socket_handler::TriggerID(base_socket *src)
   {
      int id = m_next_trigger_id++;
      m_trigger_src[id] = src;
      return id;
   }


   bool socket_handler::Subscribe(int id, base_socket *dst)
   {
      if(m_trigger_src.PLookup(id) != NULL)
      {
         if(m_trigger_dst[id].PLookup(dst) != NULL)
         {
            m_trigger_dst[id][dst] = true;
            return true;
         }
         log(dst, "Subscribe", id, "Already subscribed", ::core::log::level_info);
         return false;
      }
      log(dst, "Subscribe", id, "Trigger id not found", ::core::log::level_info);
      return false;
   }


   bool socket_handler::Unsubscribe(int id, base_socket *dst)
   {
      if (m_trigger_src.PLookup(id) != NULL)
      {
         if(m_trigger_dst[id].PLookup(dst) != NULL)
         {
            m_trigger_dst[id].remove_key(dst);
            return true;
         }
         log(dst, "Unsubscribe", id, "Not subscribed", ::core::log::level_info);
         return false;
      }
      log(dst, "Unsubscribe", id, "Trigger id not found", ::core::log::level_info);
      return false;
   }


   void socket_handler::Trigger(int id, socket::trigger_data& data, bool erase)
   {
      if(m_trigger_src.PLookup(id) != NULL)
      {
         data.SetSource( m_trigger_src[id]);
         socket_bool::pair * ppair = m_trigger_dst[id].PGetFirstAssoc();
         while(ppair != NULL);
         {
            sp(base_socket) dst = ppair->m_element1;
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
         log(NULL, "Trigger", id, "Trigger id not found", ::core::log::level_info);
      }
   }

}

