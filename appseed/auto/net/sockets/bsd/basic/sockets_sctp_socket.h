/**
 **   \file SctpSocket.h
 **   \date  2006-09-04
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

#ifdef USE_SCTP

#include <netinet/sctp.h>


namespace sockets
{

   #define SCTP_BUFSIZE_READ 16400


   class SctpSocket : public stream_socket
   {
   public:
      /** SctpSocket constructor.
         \param h Owner
         \param type SCTP_STREAM or SCTP_SEQPACKET */
      SctpSocket(base_socket_handler& h,int32_t type);
      ~SctpSocket();

      /** bind() */
      int32_t Bind(const string &,port_t);
      int32_t Bind(const ::net::address & address);
      /** sctp_bindx() */
      int32_t AddAddress(const string &,port_t);
      int32_t AddAddress(const ::net::address & address);
      /** sctp_bindx() */
      int32_t RemoveAddress(const string &,port_t);
      int32_t RemoveAddress(const ::net::address & address);

      /** connect() */
      int32_t open(const string &,port_t);
      int32_t open(const ::net::address & address);

      /** Connect timeout callback. */
      void OnConnectTimeout();
   #ifdef _WIN32
      /** Connection failed reported as exception on win32 */
      void OnException();
   #endif

   #ifndef SOLARIS
      /** sctp_connectx() */
      int32_t AddConnection(const string &,port_t);
      int32_t AddConnection(const ::net::address & address);
   #endif

      /** get peer addresses of an association. */
      int32_t getpaddrs(sctp_assoc_t id,list<string>&);
      /** get all bound addresses of an association. */
      int32_t getladdrs(sctp_assoc_t id,list<string>&);

      /** sctp_peeloff */
      int32_t PeelOff(sctp_assoc_t id);

      /** recvmsg callback */
      virtual void OnReceiveMessage(const char *buf,size_t sz,struct sockaddr *sa,socklen_t sa_len,struct sctp_sndrcvinfo *sinfo,int32_t msg_flags) = 0;

      void OnOptions(int32_t,int32_t,int32_t,SOCKET) {}

      virtual int32_t Protocol();

   protected:
      SctpSocket(const SctpSocket& s) : stream_socket(s) {}
      void OnRead();
      void OnWrite();

   private:
      SctpSocket& operator=(const SctpSocket& s) { return *this; }
      int32_t m_type; ///< SCTP_STREAM or SCTP_SEQPACKET
      char *m_buf; ///< Temporary receive buffer
   };

} // namespace sockets

 

#endif // USE_SCTP

