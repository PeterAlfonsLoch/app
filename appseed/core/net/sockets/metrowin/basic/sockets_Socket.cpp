/** \file socket.cpp
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
#ifdef _WIN32
#else
#include <errno.h>
#include <netdb.h>
#include <fcntl.h>
#endif
//#include <ctype.h>


namespace sockets
{


   #ifdef DEBUG
   #define DEB(x) x; fflush(stderr);
   #else
   #define DEB(x)
   #endif

   SOCKET socket::s_socketNextIdSeed = 1;
   socket_map socket::s_mapSocket;

   socket::socket(base_socket_handler & h) :
      element(h.get_app()),
      base_socket(h),
      m_handler(h)
   {

      m_iBindPort    = -1;
      m_dwStart      = ::get_tick_count();
      m_pcallback    = NULL;
      m_bExpectResponse = false;
      m_bExpectRequest = false;
      m_bOnConnect = false;

   }


   socket::~socket()
   {
      Handler().remove(this);
   }


   void socket::attach(Platform::Object ^ o)
   {

      synch_lock ml(&s_mutex);
      m_socket = s_socketNextIdSeed;
      s_mapSocket.set_at(m_socket, this);
      s_socket++;


   }



} // namespace sockets





