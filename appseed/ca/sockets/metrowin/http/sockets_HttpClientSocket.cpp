/**
 **   \file http_client_socket.cpp
 **   \date  2006-04-20
 **   \author grymse@alhem.net
**/
/*
Copyright (C) 2007  Anders Hedstrom

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


   http_client_socket::http_client_socket(socket_handler_base& h) :
      ::ca::ca(h.get_app()),
      socket(h),
      stream_socket(h),
      tcp_socket(h),
      http_socket(h),
      http_tunnel(h),
      m_content_length((size_t)-1),
      m_content_ptr(0),
      m_b_complete(false),
      m_b_close_when_complete(false),
      m_memoryfile(h.get_app()),
      m_mutexData(h.get_app())
   {


      m_pfile           = NULL;


   }


   http_client_socket::http_client_socket(socket_handler_base & h, const string & strUrlParam) :
      ::ca::ca(h.get_app()),
      socket(h),
      stream_socket(h),
      tcp_socket(h),
      http_socket(h),
      http_tunnel(h),
      m_content_length((size_t)-1),
      m_content_ptr(0),
      m_b_complete(false),
      m_b_close_when_complete(false),
      m_memoryfile(h.get_app()),
      m_mutexData(h.get_app())
   {

      string strRequestUri;

      url_this(strUrlParam, m_protocol, m_host, m_port, strRequestUri, m_url_filename);

      m_request.attr("http_protocol")     = m_protocol;
      outheader("host")                   = m_host;
      m_request.attr("request_uri")       = strRequestUri;
      m_response.attr("request_uri")      = strRequestUri;

      m_strUrl = strUrlParam;

      m_pfile = NULL;

   }


   http_client_socket::~http_client_socket()
   {
   }


   void http_client_socket::OnFirst()
   {
      if (!IsResponse())
      {
         Handler().LogError(this, "OnFirst", 0, "Response expected but not received - aborting", ::gen::log::level::fatal);
         SetCloseAndDelete();
      }
      m_content = m_response.attr("http_version") + " " +
                  m_response.attr("http_status_code") + " " +
                  m_response.attr("http_status") + "\r\n";
   }


   void http_client_socket::OnHeader(const string & key,const string & value, const string & lowvalue)
   {
      m_content += key + ": " + value + "\r\n";
      m_response.m_propertysetHeader[key] = value;
      if (key == __str(content_length))
      {
         m_content_length = atoi(value);
      }
      else if (key == __str(content_type))
      {
         m_content_type = value;
      }
      else if (key == __str(set_cookie))
      {
         m_response.m_cookies.add(value);
      }
   }


   void http_client_socket::OnHeaderComplete()
   {

      http_tunnel::OnHeaderComplete();

      m_memoryfile.Truncate(0);

      if(m_content_length != ((size_t) (-1)))
      {
         m_memoryfile.allocate_internal(m_content_length);
      }

      m_memoryfile.seek_to_begin();

   }

   void http_client_socket::OnDataComplete()
   {
      if(oprop("noclose").is_empty() || !(bool)oprop("noclose"))
      {
         SetCloseAndDelete();
      }
   }

   void http_client_socket::OnData(const char *buf,size_t len)
   {
      OnDataArrived(buf, len);

      if(m_pfile != NULL)
      {
         m_pfile->write(buf, len);
         return;
      }
      m_memoryfile.write(buf, len);

      m_content_ptr += len;
      if (m_content_ptr == m_content_length && m_content_length && m_content_length != ((size_t) (-1)))
      {
         m_b_complete = true;
         if(outheader("Content-Encoding").compare_value_ci("gzip") == 0)
         {
            System.compress().ungz(m_memoryfile);
         }
         if(m_pfile != NULL)
         {
            m_pfile->write(m_memoryfile.get_data(), m_memoryfile.get_size());
         }
         OnContent();
         if (m_b_close_when_complete)
         {
            SetCloseAndDelete();
         }
      }
   }

   void http_client_socket::OnDataArrived(const char * buf, size_t len)
   {
      UNREFERENCED_PARAMETER(buf);
      UNREFERENCED_PARAMETER(len);
   }


   void http_client_socket::OnDelete()
   {
      if (!m_b_complete)
      {
         m_b_complete = true;
         OnContent();
      }
   }

   const string & http_client_socket::GetContent()
   {
      return m_content;
   }

   size_t http_client_socket::GetContentLength()
   {
      if(m_content_length == ((size_t)-1))
      {
         return 0;
      }
      else
      {
         return m_memoryfile.get_size();
      }
   }


   size_t http_client_socket::GetContentPtr()
   {
      return m_content_ptr;
   }

   size_t http_client_socket::GetPos()
   {
      return m_content_ptr;
   }

   bool http_client_socket::Complete()
   {
      return m_b_complete;
   }

   const unsigned char *http_client_socket::GetDataPtr() const
   {

      return m_memoryfile.get_data();

   }

   size_t http_client_socket::GetDataLength() const
   {

      return m_memoryfile.get_size();

   }


   void http_client_socket::OnContent()
   {
   }

   void http_client_socket::SetCloseOnComplete(bool x)
   {
      m_b_close_when_complete = x;
   }

   const string & http_client_socket::GetUrlProtocol()
   {
      return m_protocol;
   }

   const string & http_client_socket::GetUrlFilename()
   {
      return m_url_filename;
   }

   const string & http_client_socket::GetContentType()
   {
      return m_content_type;
   }

   void http_client_socket::Url(const string & url_in, string & host, port_t & port)
   {
      string url;
      url_this(url_in, m_protocol, m_host, m_port, url, m_url_filename);
      m_request.attr("url") = url;
      host = System.url().get_server(url);
      port = (port_t) System.url().get_port(url);
   }


   void http_client_socket::request_url(string strUrlParam)
   {
      string strRequestUri;

      url_this(strUrlParam, m_protocol, m_host, m_port, strRequestUri, m_url_filename);

      m_request.attr("http_protocol")     = m_protocol;
      outheader("host")                   = m_host;
      m_request.attr("request_uri")       = strRequestUri;
      m_response.attr("request_uri")      = strRequestUri;

      m_strUrl = strUrlParam;

      m_pfile = NULL;
   }

} // namespace sockets



