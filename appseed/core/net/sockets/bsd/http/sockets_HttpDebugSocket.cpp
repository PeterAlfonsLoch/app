/** \file http_debug_socket.cpp
 **   \date  2004-10-08
**/
/*
Copyright (C) 2004-2007  Anders Hedström (grymse@alhem.net)

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

namespace sockets
{

   http_debug_socket::http_debug_socket(socket_handler_base& h) : 
      element(h.get_app()),
      socket(h),
      stream_socket(h),
      tcp_socket(h),
      http_socket(h),
      m_content_length(-1),
      m_read_ptr(0)
   {
   }


   http_debug_socket::~http_debug_socket()
   {
   }


   void http_debug_socket::Init()
   {
      if (get_parent() -> GetPort() == 443)
      {
   #ifdef HAVE_OPENSSL
         EnableSSL();
   #else
         Handler().LogError(this, "url_this", -1, "SSL not available", ::core::log::level_warning);
   #endif
      }
   }


   void http_debug_socket::OnFirst()
   {
      Send(
         "HTTP/1.1 200 OK\n"
         "Content-type: text/html\n"
         "Connection: close\n"
         "Server: http_debug_socket/1.0\n"
         "\n");
      Send(
         "<html><head><title>Echo Request</title></head>"
         "<body><h3>Request header</h3>");
      Send(   "<form method='post' action='/test_post'>"
         "<input type='text' name='text' value='test text'><br>"
         "<input type='submit' name='submit' value=' OK '></form>");
      Send(   "<pre style='background: #e0e0e0'>");
      Send(m_request.attr("http_method").get_string() + " " + m_request.attr("request_uri") + " " + m_request.attr("http_version") + "\n");
   }


   void http_debug_socket::OnHeader(id key,const string & value)
   {
      if(key == __id(content_length))
         m_content_length = atoi(value);

      Send(key + ": " + value + "\n");
   }


   void http_debug_socket::OnHeaderComplete()
   {
      if (m_content_length || m_content_length != ((size_t)(-1)) || IsChunked())
      {
         Send("</pre><h3>Request Body</h3><pre style='background: #e0e0e0'>");
      }
      else
      {
         Send("</pre><hr></body></html>");
         SetCloseAndDelete();
      }
   }


   void http_debug_socket::OnData(const char *p,size_t l)
   {
      SendBuf(p, (int32_t) l);
      m_read_ptr += (int32_t)l;
      if (m_read_ptr >= m_content_length && m_content_length && m_content_length != ((size_t)(-1)))
      {
         Send("</pre><hr></body></html>");
         SetCloseAndDelete();
      }
   }


   void http_debug_socket::OnDataComplete()
   {
      if (!CloseAndDelete())
      {
         Send("</pre><hr></body></html>");
         SetCloseAndDelete();
      }
   }


} // namespace sockets


