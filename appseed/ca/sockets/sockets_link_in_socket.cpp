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


//#include <stdio.h>


#include "StdAfx.h"


namespace sockets
{



   link_in_socket::link_in_socket(socket_handler_base & h) :
      ca(h.get_app()),
      socket(h),
      stream_socket(h),
      tcp_socket(h, 32000, 32000),
      m_in(NULL),
      m_out(NULL)
   {
   }


   link_in_socket::~link_in_socket()
   {
   }


   void link_in_socket::OnRead( char *buf, size_t n )
   {

      m_out->link_write(buf, n);

   }


   void link_in_socket::link_write(void * p, int n)
   {
      
      m_in->SendBuf((const char *) p, n);

   }




} // namespace sockets




