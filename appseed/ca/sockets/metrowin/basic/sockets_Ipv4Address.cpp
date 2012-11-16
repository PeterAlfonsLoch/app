/**
 **   \file ipv4_address.cpp
 **   \date  2006-09-21
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
#ifndef _WIN32
#include <netdb.h>
#endif


namespace sockets
{

   ipv4_address::ipv4_address(::ca::application *papp, port_t port) : ca(papp), m_valid(true)
   {
      memset(&m_addr, 0, sizeof(m_addr));
      m_addr.sin_family = AF_INET;
      m_addr.sin_port = htons( port );
   }


   ipv4_address::ipv4_address(::ca::application *papp, ipaddr_t a,port_t port) : ca(papp), m_valid(true)
   {
      memset(&m_addr, 0, sizeof(m_addr));
      m_addr.sin_family = AF_INET;
      m_addr.sin_port = htons( port );
      memcpy(&m_addr.sin_addr, &a, sizeof(struct in_addr));
   }


   ipv4_address::ipv4_address(::ca::application *papp, struct in_addr& a,port_t port) : ca(papp), m_valid(true)
   {
      memset(&m_addr, 0, sizeof(m_addr));
      m_addr.sin_family = AF_INET;
      m_addr.sin_port = htons( port );
      m_addr.sin_addr = a;
   }


   ipv4_address::ipv4_address(::ca::application *papp, const string & host,port_t port) : ca(papp), m_valid(false)
   {
      memset(&m_addr, 0, sizeof(m_addr));
      m_addr.sin_family = AF_INET;
      m_addr.sin_port = htons( port );
      {
         ipaddr_t a;
         if (System.net().u2ip(host, a))
         {
            memcpy(&m_addr.sin_addr, &a, sizeof(struct in_addr));
            m_valid = true;
         }
      }
   }


   ipv4_address::ipv4_address(::ca::application *papp, struct sockaddr_in& sa) : ca(papp)
   {
      m_addr = sa;
      m_valid = sa.sin_family == AF_INET;
   }

   ipv4_address::ipv4_address(const ipv4_address & addr) :
      ::ca::ca(addr.get_app())
   {
      memset(&m_addr, 0, sizeof(m_addr));
      m_addr.sin_family = AF_INET;
      m_addr.sin_port = htons(0);
      operator = (addr);
   }

   ipv4_address::~ipv4_address()
   {
   }


   ipv4_address::operator struct sockaddr *()
   {
      return (struct sockaddr *)&m_addr;
   }


   ipv4_address::operator socklen_t()
   {
      return sizeof(struct sockaddr_in);
   }


   void ipv4_address::SetPort(port_t port)
   {
      m_addr.sin_port = htons( port );
   }


   port_t ipv4_address::GetPort()
   {
      return ntohs( m_addr.sin_port );
   }


   bool ipv4_address::Resolve(::ca::application * papp, const string & hostname, in_addr& a)
   {
      struct sockaddr_in sa;
      memset(&a, 0, sizeof(a));
      if(Sys(papp->m_psystem).net().isipv4(hostname))
      {
         if(!Sys(papp->m_psystem).net().u2ip(hostname, sa, AI_NUMERICHOST))
            return false;
         a = sa.sin_addr;
         return true;
      }
      if(!Sys(papp->m_psystem).net().u2ip(hostname, sa))
         return false;
      a = sa.sin_addr;
      return true;
   }


   bool ipv4_address::Reverse(::ca::application * papp, in_addr& a,string & name)
   {
      struct sockaddr_in sa;
      memset(&sa, 0, sizeof(sa));
      sa.sin_family = AF_INET;
      sa.sin_addr = a;
      return Sys(papp->m_psystem).net().reverse((struct sockaddr *)&sa, sizeof(sa), name);
   }


   string ipv4_address::Convert(bool include_port)
   {
      if (include_port)
         return Convert(get_app(), m_addr.sin_addr) + ":" + gen::str::from(GetPort());
      return Convert(get_app(), m_addr.sin_addr);
   }


   string ipv4_address::Convert(::ca::application * papp, struct in_addr& a)
   {
      struct sockaddr_in sa;
      memset(&sa, 0, sizeof(sa));
      sa.sin_family = AF_INET;
      sa.sin_addr = a;
      string name;
     Sys(papp->m_psystem).net().reverse((struct sockaddr *)&sa, sizeof(sa), name, NI_NUMERICHOST | NI_NUMERICSERV);
      return name;
   }


   void ipv4_address::SetAddress(struct sockaddr *sa)
   {
      memcpy(&m_addr, sa, sizeof(struct sockaddr_in));
   }


   int ipv4_address::GetFamily()
   {
      return m_addr.sin_family;
   }


   bool ipv4_address::IsValid()
   {
      return m_valid;
   }


   bool ipv4_address::operator==(sockets::address& a)
   {
      if (a.GetFamily() != GetFamily())
         return false;
      if ((socklen_t)a != sizeof(m_addr))
         return false;
      struct sockaddr *sa = a;
      struct sockaddr_in *p = (struct sockaddr_in *)sa;
      if (p -> sin_port != m_addr.sin_port)
         return false;
      if (memcmp(&p -> sin_addr, &m_addr.sin_addr, 4))
         return false;
      return true;
   }

   string ipv4_address::Reverse()
   {
      string tmp;
      Reverse(get_app(), m_addr.sin_addr, tmp);
      return tmp;
   }

   bool ipv4_address::is_in_net(ipv4_address & addr, ipv4_address & mask)
   {
#ifdef WINDOWS
      return (addr.m_addr.sin_addr.S_un.S_addr & mask.m_addr.sin_addr.S_un.S_addr) == (m_addr.sin_addr.S_un.S_addr & mask.m_addr.sin_addr.S_un.S_addr);
#else
      return (addr.m_addr.sin_addr.s_addr & mask.m_addr.sin_addr.s_addr) == (m_addr.sin_addr.s_addr & mask.m_addr.sin_addr.s_addr);
#endif
   }

   ipv4_address & ipv4_address::operator = (const ipv4_address & addr)
   {
      if(&addr != this)
      {
         m_addr = addr.m_addr;
         m_valid = addr.m_valid;
      }
      return *this;
   }

} // namespace sockets
