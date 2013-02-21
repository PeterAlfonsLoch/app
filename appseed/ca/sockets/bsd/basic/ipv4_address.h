/**
**   \file ipv4_address.h
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
#pragma once


namespace sockets
{

   class address;

   /* Ipv4 address implementation.
   \ingroup basic */
   class CLASS_DECL_ca ipv4_address :
      virtual public ::gen::object
   {
   public:

      
      struct sockaddr_in   m_addr;
      bool                 m_bValid;


      /** create is_empty Ipv4 address structure.
      \param port Port number */
      ipv4_address(::ca::application * papp, port_t port = 0);
      /** create Ipv4 address structure.
      \param a socket address in network byte order (as returned by Utility::u2ip)
      \param port Port number in host byte order */
      //ipv4_address(::ca::application * papp, ipaddr_t a,port_t port);
      /** create Ipv4 address structure.
      \param a socket address in network byte order
      \param port Port number in host byte order */
      ipv4_address(::ca::application * papp, const in_addr& a,port_t port);
      ipv4_address(::ca::application * papp, const in_addr& a, const string & strServiceName);
      /** create Ipv4 address structure.
      \param host Hostname to be resolved
      \param port Port number in host byte order */
      ipv4_address(::ca::application * papp, const string & host,port_t port);
      ipv4_address(::ca::application * papp, const string & host, const string & strServiceName);
      ipv4_address(::ca::application * papp, const sockaddr_in&);
      ipv4_address(const ipv4_address & addr);
      ~ipv4_address();

      // ::sockets::address implementation

      //operator struct sockaddr *();
      //operator socklen_t();
      //bool operator==(address&);

      void SetPort(port_t port);
      port_t GetPort();

      void SetAddress(struct sockaddr *sa);
      int32_t GetFamily();

      bool IsValid();

      /** Convert address struct to text. */
      string Convert(bool include_port = false);
      string Reverse();


      bool is_in_net(ipv4_address & addr, ipv4_address & mask);

      /** Resolve hostname. */
      //static bool Resolve(::ca::application * papp, const string & hostname, in_addr& a);
      /** Reverse resolve (IP to hostname). */
      //static bool Reverse(::ca::application * papp, in_addr& a,string & name);
      /** Convert address struct to text. */
      //static string Convert(::ca::application * papp, in_addr& a);

      ipv4_address & operator = (const ipv4_address &);


      bool IsEqual(const ipv4_address &) const;

      string get_display_number() const;
      string get_canonical_name() const;



   };




} // namespace sockets


