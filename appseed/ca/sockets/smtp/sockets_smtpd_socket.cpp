/**
 **   \file smtpd_socket.cpp
 **   \date  2007-05-10
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
#include "StdAfx.h"

namespace sockets
{

   smtpd_socket::smtpd_socket(socket_handler_base& h) :
      ::ca::ca(h.get_app()),
      socket(h),
      stream_socket(h),
      tcp_socket(h),
      m_hello(false),
      m_data(false),
      m_header(false)
   {
      SetLineProtocol();
   }


   void smtpd_socket::OnAccept()
   {
      Send("220 ESMTP; \r\n");
   }


   void smtpd_socket::OnLine(const string & line)
   {
      if (m_data)
      {
         if (m_header)
         {
            if (!line.get_length())
            {
               if (m_header_line.get_length())
               {
                  ::gen::parse pa(m_header_line, ":");
                  string key = pa.getword();
                  key.make_lower();
                  string value = pa.getrest();
                  string lowvalue = value;
                  lowvalue.make_lower();
                  OnHeader(key, value, lowvalue);
               }
               m_header = false;
               OnHeaderComplete();
            }
            else
            if (line[0] == ' ' || line[0] == '\t')
            {
               m_header_line += line;
            }
            else
            {
               if (m_header_line.get_length())
               {
                  ::gen::parse pa(m_header_line, ":");
                  string key = pa.getword();
                  key.make_lower();
                  string value = pa.getrest();
                  string lowvalue = value;
                  lowvalue.make_lower();
                  OnHeader(key, value, lowvalue);
               }
               m_header_line = line;
            }
         }
         else
         if (line == ".")
         {
            m_data = false;
            if (OnDataComplete())
               Send("250 OK\r\n");
            else
               Send("550 Failed\r\n");
         }
         else
         if (line.get_length() && line[0] == '.')
         {
            OnData(line.Mid(1));
         }
         else
         {
            OnData(line);
         }
         return;
      }
      ::gen::parse pa(line);
      string cmd = pa.getword();
      cmd.make_upper();
      if (cmd == "EHLO")
      {
         if (!OnHello(pa.getrest()))
         {
            Send("550 Failed\r\n");
         }
         else
         {
            m_hello = true;
            Send("250 mail.alhem.net\r\n");
         }
      }
      else
      if (cmd == "HELO")
      {
         if (!OnHello(pa.getrest()))
         {
            Send("550 Failed\r\n");
         }
         else
         {
            m_hello = true;
            Send("250 mail.alhem.net\r\n");
         }
      }
      else
      if (!m_hello)
      {
         OnAbort(SMTP_NO_HELLO);
         SetCloseAndDelete();
      }
      else
      if (cmd == "MAIL") // mail from:
      {
         ::gen::parse pa(line, ":");
         pa.getword(); // 'mail'
         pa.getword(); // 'from'
         string email = pa.getrest();
         email.make_lower();
         ::email::address addr( email );
         if (addr.get_name().get_length() > 64)
         {
            OnAbort(SMTP_NAME_TOO_LONG);
            Send("500 Name too long.\r\n");
            return;
         }
         if (addr.get_domain().get_length() > 64)
         {
            OnAbort(SMTP_DOMAIN_TOO_LONG);
            Send("500 Domain too long.\r\n");
            return;
         }

         if (!OnMailFrom( addr ))
         {
            Send("550 Failed\r\n");
         }
         else
         {
            Send("250 OK\r\n");
         }
      }
      else
      if (cmd == "RCPT") // rcpt to:
      {
         ::gen::parse pa(line, ":");
         pa.getword(); // 'rcpt'
         pa.getword(); // 'to'
         string email = pa.getrest();
         email.make_lower();
         // %! reject based on ::fontopus::user / domain?
         ::email::address addr( email );

         if (addr.get_name().get_length() > 64)
         {
            OnAbort(SMTP_NAME_TOO_LONG);
            Send("500 Name too long.\r\n");
            return;
         }
         if (addr.get_domain().get_length() > 64)
         {
            OnAbort(SMTP_DOMAIN_TOO_LONG);
            Send("500 Domain too long.\r\n");
            return;
         }

         if (!OnRcptTo( addr ))
         {
            Send("553 Failed\r\n");
         }
         else
         {
            Send("250 OK\r\n");
         }
      }
      else
      if (cmd == "DATA")
      {
         Send("354 Enter mail, end with \".\" on a line by itself\r\n");
         m_data = true;
         m_header = true;
      }
      else
      if (cmd == "RSET")
      {
         m_data = false;
         m_header = false;
         OnRset();
         Send("250 OK\r\n"); // %! ???
      }
      else
      if (cmd == "QUIT")
      {
         OnAbort(SMTP_QUIT);
         Send("221 Bye Bye\r\n");
         SetCloseAndDelete();
      }
      else
      if (cmd == "NOOP")
      {
         Send("250 OK\r\n");
      }
      else
      {
         OnNotSupported(cmd, pa.getrest());
      }
   }

} // namespace sockets

