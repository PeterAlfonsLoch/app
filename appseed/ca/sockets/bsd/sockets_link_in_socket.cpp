//InSocket.cpp
/*
Copyright (C) 2004  Anders Hedstrom

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


namespace sockets
{



   link_in_socket::link_in_socket(socket_handler_base & h) :
      ca(h.get_app()),
      socket(h),
      stream_socket(h),
      tcp_socket(h, 32000, 32000),
      m_in(NULL),
      m_out(NULL),
      m_eventFinished(h.get_app())
   {
   }


   link_in_socket::~link_in_socket()
   {
   }


   void link_in_socket::OnRead( char *buf, size_t n )
   {

      m_out->link_write(buf, n);

   }


   void link_in_socket::link_write(void * p, size_t n)
   {
      
      m_in->SendBuf((const char *) p, (int32_t) n);

   }


   void link_in_socket::server_to_link_in(httpd_socket * psocket)
   {
      socket_handler & h = dynamic_cast < socket_handler & > (psocket->Handler());
      POSITION pos = h.m_sockets.get_start_position();
      ::sockets::socket * psocket2;
      SOCKET key;
      while(pos != NULL)
      {
         h.m_sockets.get_next_assoc(pos, key, psocket2);
         if(psocket2 == psocket)
         {
            h.m_sockets.set_at(key, this);
         }
      }
      m_ssl = psocket->GetSsl();
      m_socket = psocket->m_socket;

      m_bConnecting        = psocket->m_bConnecting; ///< Flag indicating connection in progress
      m_connect_timeout    = psocket->m_connect_timeout; ///< Connection timeout (seconds)
      m_flush_before_close = psocket->m_flush_before_close; ///< Send all data before closing (default true)
      m_connection_retry   = psocket->m_connection_retry; ///< Maximum connection retries (tcp)
      m_retries            = psocket->m_retries; ///< Actual number of connection retries (tcp)
      m_call_on_connect    = psocket->m_call_on_connect; ///< OnConnect will be called next socket_handler_base cycle if true
      m_b_retry_connect    = psocket->m_b_retry_connect; ///< Try another connection attempt next socket_handler_base cycle
      m_shutdown           = psocket->m_shutdown; ///< Shutdown status

      m_bSsl               = psocket->m_bSsl;
      m_bReconnect         = psocket->m_bReconnect;
      m_bSsl               = psocket->m_bSsl;
      m_bSslServer         = psocket->m_bSslServer;
      m_bEnableSsl         = psocket->m_bEnableSsl;

   }

   link_in_socket * link_in_socket::from_server(httpd_socket * psocket)
   {
      
      link_in_socket * pinsocket = new link_in_socket(psocket->Handler());

	   pinsocket->m_in = psocket;
	
	   pinsocket->m_memfileInput.FullLoad(psocket->m_memfileInput);

      pinsocket->server_to_link_in(psocket);

      psocket->m_bEnd = true;

      return pinsocket;

   }

} // namespace sockets




