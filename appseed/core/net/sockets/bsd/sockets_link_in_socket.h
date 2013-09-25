//InSocket.h
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
#pragma once


namespace sockets
{


   class link_out_socket;


   class CLASS_DECL_ca2 link_in_socket : public tcp_socket
   {
   public:

      socket *             m_in;
      link_out_socket *    m_out;
      event                m_eventFinished;


      link_in_socket(base_socket_handler& h);
      ~link_in_socket();


      void on_read(const void * pdata, ::primitive::memory_size n);
      void link_write(const void * pdata, ::primitive::memory_size size);


      static link_in_socket * from_server(httpd_socket * psocket);


      void server_to_link_in(httpd_socket * psocket);


   };

   typedef ptrptr(link_out_socket, link_in_socket) in_link_map; 


} // namespace sockets


