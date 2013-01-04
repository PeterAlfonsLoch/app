/** \file http_put_socket.cpp
 **   \date  2004-10-30
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

namespace sockets
{

   http_put_socket::http_put_socket(socket_handler_base& h) : 
      ::ca::ca(h.get_app()),
      socket(h),
      stream_socket(h),
      tcp_socket(h),
      http_socket(h),
      http_tunnel(h),
      http_client_socket(h)
   {
      m_content_length = -1;
   }


   http_put_socket::http_put_socket(socket_handler_base& h,const string & url_in) : 
      ::ca::ca(h.get_app()),
      socket(h),
      stream_socket(h),
      tcp_socket(h),
      http_socket(h),
      http_tunnel(h),
      http_client_socket(h, url_in)
   {
      m_content_length = -1;
   }


   http_put_socket::~http_put_socket()
   {
   }


   void http_put_socket::SetFile(const string & file)
   {
      if(Application.file().exists(file))
      {
         m_filename = file;
         m_content_length = System.file().length(file);
      }
      else
      {
         Handler().LogError(this, "SetFile", Errno, StrError(Errno), ::gen::log::level::fatal);
         SetCloseAndDelete();
      }
   }


   void http_put_socket::SetContentType(const string & type)
   {
      m_content_type = type;
   }





   void http_put_socket::step()
   {

      if(m_file.is_set())
      {
         m_content_length = (long) m_file->get_length();
      }


      m_request.attr("http_method")    = "PUT";
      m_request.attr("http_version")   = "HTTP/1.1";
      inheader("Host")                = GetUrlHost();
      if(m_content_type.has_char())
      {
         outheader("Content-type")     = m_content_type;
      }
      inheader("Content-length")      = (int64_t) m_content_length;
      inheader("User-agent")          = MyUseragent();
      inheader("Connection")          = "close";
      SendRequest();

      if(m_file.is_set())
      {
         size_t n;
         char buf[32768];
         m_file->seek_to_begin();
         while ((n = m_file->read(buf, 32768)) > 0)
         {
            SendBuf(buf, n);
         }
      }
      else
      {
         FILE *fil = fopen(m_filename, "rb");
         if (fil)
         {
            size_t n;
            char buf[32768];
            while ((n = fread(buf, 1, 32768, fil)) > 0)
            {
               SendBuf(buf, n);
            }
            fclose(fil);
         }
      }
      
   }

}


