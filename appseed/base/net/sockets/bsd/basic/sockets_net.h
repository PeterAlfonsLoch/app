// http://www.alhem.net/
/** from C++ Sockets Library
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
#pragma once



// 1.8.6: define FD_SETSIZE to something bigger than 64 if there are a lot of
// simultaneous connections (must be done before including winsock.h)
//#define FD_SETSIZE 1024

// windows 2000 with ipv6 preview installed:
//    http://msdn.microsoft.com/downloads/sdks/platform/tpipv6.asp
// see the FAQ on how to install
/*#define WIN32_LEAN_AND_MEAN
#include <ws2tcpip.h>
#if _MSC_VER < 1200
#ifndef __CYGWIN__
#ifdef ENABLE_IPV6
#include <tpipv6.h>  // For IPv6 Tech Preview.
#endif
#endif
#endif // _MSC_VER < 1200
*/


namespace sockets
{


   // http://www.alhem.net/
   /** from C++ Sockets Library \file Utility.h
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


   class CLASS_DECL_BASE net :
      public object
   {
   private:


      string         m_host; ///< local hostname
      in_addr        m_ip; ///< local ip address
      string         m_addr; ///< local ip address in string format
      string         m_local_addr6; ///< local ip address in string format
      in6_addr       m_local_ip6; ///< local ipv6 address
      bool           m_local_resolved; ///< ResolveLocal has been called if true



   public:

      bool           m_bInitialized;


      class CLASS_DECL_BASE dns_cache_item :
         virtual public ::file::serializable
      {
      public:


         in_addr           m_ipaddr;
         uint32_t          m_dwLastChecked;
         bool              r;


         dns_cache_item();
         dns_cache_item(const dns_cache_item & item);


         virtual void write(::file::output_stream & ostream);
         virtual void read(::file::input_stream & istream);

         dns_cache_item & operator = (const dns_cache_item & item);

      };

      class CLASS_DECL_BASE reverse_cache_item:
         virtual public ::file::serializable
      {
      public:


         in_addr           m_ipaddr;
         string            m_strReverse;
         uint32_t          m_dwLastChecked;
         bool              r;


         reverse_cache_item();
         reverse_cache_item(const reverse_cache_item & item);


         virtual void write(::file::output_stream & ostream);
         virtual void read(::file::input_stream & istream);

         reverse_cache_item & operator = (const reverse_cache_item & item);

      };

      mutex                                                                                  m_mutexCache;
      ::file::byte_serializable_map < string_map < dns_cache_item > >                        m_mapCache;
      ::file::byte_serializable_map < string_map < reverse_cache_item > >                    m_mapReverseCache;


      net(sp(::aura::application) papp);
      virtual ~net();


      virtual bool initialize();
      virtual bool finalize();

      virtual bool gudo_set();


      /*
      * Encode string per RFC1738 URL encoding rules
      * tnx rstaveley
      */
      string rfc1738_encode(const string & src);

      /*
      * Decode string per RFC1738 URL encoding rules
      * tnx rstaveley
      */
      string rfc1738_decode(const string & src);

      bool isipv4(const string & str);

      bool isipv6(const string & str);

      bool convert(struct ::in_addr& l, const string & str, int32_t ai_flags = 0);
      bool convert(struct ::in6_addr& l, const string & str, int32_t ai_flags = 0);
      bool convert(string & str, const struct ::in_addr& ip);
      bool convert(string & str, const struct ::in6_addr& ip, bool mixed = false);

      int32_t in6_addr_compare(struct ::in6_addr a, struct ::in6_addr b);

      void ResolveLocal();

      const string & GetLocalHostname();

      in_addr GetLocalIP();

      const string & GetLocalAddress();

      const struct in6_addr& GetLocalIP6();

      const string & GetLocalAddress6();

      string Sa2String(sockaddr * psa);

      //::net::address CreateAddress(sockaddr * psa, socklen_t sa_len);

      bool reverse(sockaddr * psa, socklen_t sa_len, string & hostname, int32_t flags = 0);

      bool reverse(sockaddr * psa, socklen_t sa_len, string & hostname, string & service, int32_t flags = 0);

      bool reverse(string & number, const string & hostname, int32_t flags);


      bool u2service(const string & name, int32_t& service, int32_t ai_flags);

      int32_t service_port(const string & str, int32_t flags = 0);

      string  service_name(int32_t iPort, int32_t flags = 0);


      string canonical_name(const ::net::address & address);

      string service_name(const ::net::address & address);

      string reverse_name(const ::net::address & address);

      string reverse_name(const string & address);

   };


} // namespace sockets





