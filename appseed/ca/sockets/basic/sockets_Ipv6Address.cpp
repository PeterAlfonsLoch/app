/**
 **   \file ipv6_address.cpp
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


   ipv6_address::ipv6_address(::ca::application * papp, port_t port) :
      ca(papp), 
      m_valid(true)
   {
      memset(&m_addr, 0, sizeof(m_addr));
      m_addr.sin6_family = AF_INET6;
      m_addr.sin6_port = htons( port );
   }


   ipv6_address::ipv6_address(::ca::application * papp, in6_addr& a,port_t port) : 
      ca(papp),
      m_valid(true)
   {
      memset(&m_addr, 0, sizeof(m_addr));
      m_addr.sin6_family = AF_INET6;
      m_addr.sin6_port = htons( port );
      m_addr.sin6_addr = a;
   }

   ipv6_address::ipv6_address(const ipv6_address & addr) : 
      ::ca::ca(addr.get_app())
   {
      memset(&m_addr, 0, sizeof(m_addr));
      m_addr.sin6_family = AF_INET6;
      m_addr.sin6_port = htons(0);
      operator = (addr);
   }


   ipv6_address::ipv6_address(::ca::application * papp, const string & host, port_t port) : 
      ca(papp),
      m_valid(false)
   {
      memset(&m_addr, 0, sizeof(m_addr));
      m_addr.sin6_family = AF_INET6;
      m_addr.sin6_port = htons( port );
      {
         struct in6_addr a;
         if(System.net().u2ip(host, a))
         {
            m_addr.sin6_addr = a;
            m_valid = true;
         }
      }
   }


   ipv6_address::ipv6_address(::ca::application * papp, sockaddr_in6 & sa) :
      ca(papp)
   {
      m_addr = sa;
      m_valid = sa.sin6_family == AF_INET6;
   }


   ipv6_address::~ipv6_address()
   {
   }


   ipv6_address::operator struct sockaddr *()
   {
      return (struct sockaddr *)&m_addr;
   }


   ipv6_address::operator socklen_t()
   {
      return sizeof(struct sockaddr_in6);
   }


   void ipv6_address::SetPort(port_t port)
   {
      m_addr.sin6_port = htons( port );
   }


   port_t ipv6_address::GetPort()
   {
      return ntohs( m_addr.sin6_port );
   }


   bool ipv6_address::Resolve(::ca::application * papp, const string & hostname,struct in6_addr& a)
   {
      struct sockaddr_in6 sa;
      memset(&a, 0, sizeof(a));
      if(Sys(papp->m_psystem).net().isipv6(hostname))
      {
         if(!Sys(papp->m_psystem).net().u2ip(hostname, sa, AI_NUMERICHOST))
            return false;
         a = sa.sin6_addr;
         return true;
      }
      if(!Sys(papp->m_psystem).net().u2ip(hostname, sa))
         return false;
      a = sa.sin6_addr;
      return true;
   }


   bool ipv6_address::Reverse(::ca::application * papp, in6_addr& a,string & name)
   {
      struct sockaddr_in6 sa;
      memset(&sa, 0, sizeof(sa));
      sa.sin6_family = AF_INET6;
      sa.sin6_addr = a;
      return Sys(papp->m_psystem).net().reverse((struct sockaddr *)&sa, sizeof(sa), name);
   }


   string ipv6_address::Convert(bool include_port)
   {
      if (include_port)
         return Convert(get_app(), m_addr.sin6_addr) + ":" + gen::str::itoa(GetPort());
      return Convert(get_app(), m_addr.sin6_addr);
   }


   string ipv6_address::Convert(::ca::application * papp, struct in6_addr& a,bool mixed)
   {
      char slask[100]; // l2ip temporary
      *slask = 0;
      unsigned int prev = 0;
      bool skipped = false;
      bool ok_to_skip = true;
      if (mixed)
      {
         unsigned short x;
         unsigned short addr16[8];
         memcpy(addr16, &a, sizeof(addr16));
         for (size_t i = 0; i < 6; i++)
         {
            x = ntohs(addr16[i]);
            if (*slask && (x || !ok_to_skip || prev))
               strcat(slask,":");
            if (x || !ok_to_skip)
            {
               sprintf(slask + strlen(slask),"%x", x);
               if (x && skipped)
                  ok_to_skip = false;
            }
            else
            {
               skipped = true;
            }
            prev = x;
         }
         x = ntohs(addr16[6]);
         sprintf(slask + strlen(slask),":%u.%u",x / 256,x & 255);
         x = ntohs(addr16[7]);
         sprintf(slask + strlen(slask),".%u.%u",x / 256,x & 255);
      }
      else
      {
         struct sockaddr_in6 sa;
         memset(&sa, 0, sizeof(sa));
         sa.sin6_family = AF_INET6;
         sa.sin6_addr = a;
         string name;
         Sys(papp->m_psystem).net().reverse((struct sockaddr *)&sa, sizeof(sa), name, NI_NUMERICHOST);
         return name;
      }
      return slask;
   }


   void ipv6_address::SetAddress(struct sockaddr *sa)
   {
      memcpy(&m_addr, sa, sizeof(struct sockaddr_in6));
   }


   int ipv6_address::GetFamily()
   {
      return m_addr.sin6_family;
   }


   void ipv6_address::SetFlowinfo(uint32_t x)
   {
      m_addr.sin6_flowinfo = x;
   }


   uint32_t ipv6_address::GetFlowinfo()
   {
      return m_addr.sin6_flowinfo;
   }


   #ifndef _WIN32
   void ipv6_address::SetScopeId(uint32_t x)
   {
      m_addr.sin6_scope_id = x;
   }


   uint32_t ipv6_address::GetScopeId()
   {
      return m_addr.sin6_scope_id;
   }
   #endif


   bool ipv6_address::IsValid()
   {
      return m_valid;
   }


   bool ipv6_address::operator==(sockets::address& a)
   {
      if (a.GetFamily() != GetFamily())
         return false;
      if ((socklen_t)a != sizeof(m_addr))
         return false;
      struct sockaddr *sa = a;
      struct sockaddr_in6 *p = (struct sockaddr_in6 *)sa;
      if (p -> sin6_port != m_addr.sin6_port)
         return false;
      if (memcmp(&p -> sin6_addr, &m_addr.sin6_addr, sizeof(struct in6_addr)))
         return false;
      return true;
   }

   string ipv6_address::Reverse()
   {
      string tmp;
      Reverse(get_app(), m_addr.sin6_addr, tmp);
      return tmp;
   }

   ipv6_address& ipv6_address::operator=(const ipv6_address & addr)
   {
      if(&addr != this)
      {
         m_addr = addr.m_addr;
         m_valid = addr.m_valid;
         
      }
      return *this;
   }

} // namespace sockets
