/**
 **   \file Ajp13Socket.cpp
 **   \date  2007-10-05
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

   #ifdef DEBUG
   #define DEB(x) x
   #else
   #define DEB(x)
   #endif


   // --------------------------------------------------------------------------------------
   Ajp13Socket::Ajp13Socket(socket_handler_base& h) :
      socket(h),
      stream_socket(h),
      AjpBaseSocket(h),
      m_request(h.get_app()),
      m_response(h.get_app()),
      m_body_size_left(0)
   {
   }


   // --------------------------------------------------------------------------------------
   void Ajp13Socket::OnHeader( int16_t id, int16_t len )
   {
      if (id != 0x1234)
      {
         TRACE("ABORT: bad packet id: %x\n", id);
         SetCloseAndDelete();
      }
      else
      {
         TRACE("Packet size: %d bytes\n", len);
      }
   }


   // --------------------------------------------------------------------------------------
   void Ajp13Socket::ReceiveBody(const char *buf, primitive::memory_size sz)
   {
      if (sz - 2 > m_body_size_left)
      {
         TRACE("More body data received than expected\n");
         SetCloseAndDelete();
         return;
      }

      m_request.write( buf + 2, sz - 2 );
      m_body_size_left -= sz - 2;

      // request more body data
      if (m_body_size_left)
      {
         int32_t ptr = 4;
         char msg[100];
         msg[0] = 'A';
         msg[1] = 'B';

   // reply codes
   //   0x3 Send Body Chunk
   //   0x4 Send Headers
   //   0x5 End Response
   //   0x6 get Body Chunk   <------
   //   0x9 CPong Reply

         put_byte(msg, ptr, 0x06); // GET_BODY_CHUNK;
         put_integer(msg, ptr, 1000); // request 1000 bytes

         int16_t len = htons((u_short)( ptr - 4 ));
         memcpy( msg + 2, &len, 2 );

         SendBuf( msg, ptr );
         return;
      }

      // close
      m_request.CloseBody();

      // no more body data left to read - execute
      Execute();

   }


   // --------------------------------------------------------------------------------------
   void Ajp13Socket::ReceiveForwardRequest( const char *buf, primitive::memory_size sz )
   {
      UNREFERENCED_PARAMETER(sz);
      //
      int32_t ptr = 0;

      get_byte(buf, ptr); // skip first byte: prefix_code
      uchar method    = get_byte(buf, ptr);
      string    protocol      = get_string(buf, ptr);
      string    req_uri       = get_string(buf, ptr);
      string    remote_addr   = get_string(buf, ptr);
      string    remote_host   = get_string(buf, ptr);
      string    server_name   = get_string(buf, ptr);
      int16_t     server_port   = get_integer(buf, ptr);
      bool      is_ssl        = get_boolean(buf, ptr);

      string method_str = ::str::from( method );
      Application.sockets().m_pajpbasesocketinit->Method.Lookup(method, method_str);
      m_request.attr("http_method") = method_str;
      m_request.attr("http_protocol") = protocol;
      m_request.attr("request_uri") = req_uri;
      m_request.attr("remote_addr") = remote_addr;
      m_request.attr("remote_host") = remote_host;
      m_request.attr("server_name") = server_name ;
      m_request.attr("server_port") = server_port;
      m_request.attr("https") = is_ssl;

      // get Headers
      int16_t             num_headers = get_integer(buf, ptr);
      for (int32_t i = 0; i < num_headers; i++)
      {
         string key;
         switch ( (uchar)buf[ptr]) // 0xa0
         {
         case 0xa0:
            {
               uint16_t x = (uint16_t)get_integer(buf, ptr);
               if (!Application.sockets().m_pajpbasesocketinit->header.Lookup(x, key))
               {
                  TRACE("Unknown header key value: %x\n", x);
                  SetCloseAndDelete();
               }
            }
            break;

         default: // string
            key = get_string(buf, ptr);
         }
         key.make_lower();
         if (key == "cookie" ||key == "cookie2")
            m_request.add_cookie(get_string(buf, ptr));
         else
            m_request.header(key) = get_string(buf, ptr);
      } // for

      // size left to read from web server
      m_body_size_left = m_request.ContentLength();

      // get Attributes
      while ( (uchar)buf[ptr] != 0xff)
      {
         string key;
         uchar code = buf[ptr++];
         switch ( code)
         {
         case 10: // req_attribute, attribute name follow
            key = get_string(buf, ptr);
            break;
         default:
            {
               if(!Application.sockets().m_pajpbasesocketinit->Attribute.Lookup(code, key))
               {
                  TRACE("Unknown attribute key: 0x%02x\n", buf[ptr]);
                  SetCloseAndDelete();
               }
            }
         }
         key.make_lower();
         m_request.attrs()[key] = get_string(buf, ptr);
      } // while

      // execute at once if no body data
      if (!m_body_size_left)
      {
         Execute();
      }
      else
      {
         // open temporary file for body data
         m_request.InitBody( m_body_size_left );
      }
   }


   // --------------------------------------------------------------------------------------
   void Ajp13Socket::ReceiveShutdown( const char *buf, primitive::memory_size sz )
   {
      UNREFERENCED_PARAMETER(buf);
      UNREFERENCED_PARAMETER(sz);
   }


   // --------------------------------------------------------------------------------------
   void Ajp13Socket::ReceivePing( const char *buf, primitive::memory_size sz )
   {
      UNREFERENCED_PARAMETER(buf);
      UNREFERENCED_PARAMETER(sz);
   }


   // --------------------------------------------------------------------------------------
   void Ajp13Socket::ReceiveCPing( const char *buf, primitive::memory_size sz )
   {
      UNREFERENCED_PARAMETER(buf);
      UNREFERENCED_PARAMETER(sz);
   }


   // --------------------------------------------------------------------------------------
   void Ajp13Socket::Execute()
   {
      // parse form data / query_string and cookie header if available
      m_request.ParseBody();

      // prepare page
      OnExecute();

   }


   // --------------------------------------------------------------------------------------
   void Ajp13Socket::Respond()
   {
      char msg[8192];
      msg[0] = 'A';
      msg[1] = 'B';

   // reply codes
   //   0x3 Send Body Chunk
   //   0x4 Send Headers
   //   0x5 End Response
   //   0x6 get Body Chunk
   //   0x9 CPong Reply

      // check content length
      if (!m_response.ContentLength() && m_response.file().get_length())
      {
         m_response.SetContentLength((long) m_response.file().get_length() );
      }

      // Send Headers
      {
         int32_t ptr = 4;
         put_byte(msg, ptr, 0x04); // send headers
         put_integer(msg, ptr, (int16_t)(int32_t)m_response.attr("http_status_code"));
         put_string(msg, ptr, m_response.attr("http_status"));
         put_integer(msg, ptr, (int16_t)m_response.headers().m_propertya.get_size() );
         for (int32_t i = 0; i < m_response.headers().m_propertya.get_size(); i++)
         {
            string strNameLower(m_response.headers().m_propertya[i].name());
            strNameLower;
            int32_t iValue;
            if(Application.sockets().m_pajpbasesocketinit->ResponseHeader.Lookup(strNameLower, iValue))
            {
               put_integer(msg, ptr, (int16_t) iValue);
            }
            else
            {
               put_string(msg, ptr, m_response.headers().m_propertya[i].name());
            }
            put_string(msg, ptr, m_response.headers().m_propertya[i].name());
         }
         throw not_implemented(get_app());
   /*      list<string> vec = m_response.CookieNames();
         {
            for (list<string>::iterator it = vec.begin(); it != vec.end(); it++)
            {
               Utility::ncmap<int32_t>::const_iterator it2 = dynamic_cast < application_interface * >(::get_app())->m_pajpbasesocketinit->ResponseHeader.find( __id(set_cookie) );
               if (it2 != dynamic_cast < application_interface * >(::get_app())->m_pajpbasesocketinit->ResponseHeader.end())
               {
                  put_integer(msg, ptr, it2 -> second);
               }
               else
               {
                  put_string(msg, ptr, __id(set_cookie));
               }
               put_string(msg, ptr, m_response.Cookie(*it) );
            }
         }*/

         int16_t len = htons((u_short) ( ptr - 4 ));
         memcpy( msg + 2, &len, 2 );

         SendBuf( msg, ptr );
      }
      // Send Body Chunk
      OnTransferLimit();
   }


   // --------------------------------------------------------------------------------------
   void Ajp13Socket::OnTransferLimit()
   {
      char msg[8192];
      msg[0] = 'A';
      msg[1] = 'B';

      // Send Body Chunk
      size_t n = m_response.file().read(msg + 7,  8100);
      while (n > 0)
      {
         int32_t ptr = 4;
         put_byte(msg, ptr, 0x03); // send body chunk
         put_integer(msg, ptr, (int16_t)n);
         ptr += (int32_t)n;

         int16_t len = htons((u_short) ( ptr - 4 ));
         memcpy( msg + 2, &len, 2 );

         SendBuf( msg, ptr );
         if (GetOutputLength() > 1)
         {
            SetTransferLimit( 1 );
            break;
         }

         //
         n = m_response.file().read(msg + 7, 8100);
      }
      if (!GetOutputLength()) // all body data sent and no data in output buffer - send end response
      {
         // End Response
         int32_t ptr = 4;
         put_byte(msg, ptr, 0x05); // end response
         put_boolean(msg, ptr, false); // reuse
         /*
            don't reuse
            - but with m_request.Reset() and m_response.Reset() it should be possible
            - also reset any AjpBaseSocket/Ajp13Socket specific states
         */

         int16_t len = htons((u_short) ( ptr - 4 ));
         memcpy( msg + 2, &len, 2 );

         SendBuf( msg, ptr );

         OnResponseComplete();
      }
   }


   // --------------------------------------------------------------------------------------
   void Ajp13Socket::OnPacket( const char *buf, primitive::memory_size sz )
   {
      TRACE("OnPacket: %d bytes, code 0x%02x %02x %02x %02x\n", sz, *buf, buf[1], buf[2], buf[3]);

      // check body size left to read, if non-zero packet is body data
      if (m_body_size_left) // must be a body packet
      {
         ReceiveBody(buf, sz);
         return;
      }
      switch (*buf)
      {
      case 0x2: // Forward Request
         ReceiveForwardRequest(buf, sz);
         break;
      case 0x7: // Shutdown
         ReceiveShutdown(buf, sz);
         break;
      case 0x8: // Ping
         ReceivePing(buf, sz);
         break;
      case 0xa: // CPing
         ReceiveCPing(buf, sz);
         break;
      default:
         TRACE("Unknown packet type: 0x%02x\n", *buf);
         SetCloseAndDelete();
      }

   }

   void Ajp13Socket::OnResponseComplete()
   {
   }

} // namespace sockets
