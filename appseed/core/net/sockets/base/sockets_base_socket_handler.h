/** \file base_socket_handler.h
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
#pragma once


namespace sockets
{


   typedef enum
   {
      LIST_CALLONCONNECT = 0,
#ifdef ENABLE_DETACH
      LIST_DETACH,
#endif
      LIST_TIMEOUT,
      LIST_RETRY,
      LIST_CLOSE
   } list_t;


   /** socket container class, event generator.
   \ingroup basic */
   class base_socket_handler : 
      virtual public ::object
   {
      
      friend class socket;

   public:
      /** Connection pool class for internal use by the base_socket_handler.
      \ingroup internal */
      class PoolSocket : public socket
      {
      public:
         PoolSocket(base_socket_handler& h,socket *src) : base_socket(h), socket(h) {
            CopyConnection( src );
            SetIsClient();
         }

         void OnRead() {
            Handler().LogError(this, "OnRead", 0, "data on hibernating socket", ::core::log::level_fatal);
            SetCloseAndDelete();
         }
         void OnOptions(int,int,int,SOCKET) {}

      };

   public:

      int m_iSelectErrno;


   public:
      virtual ~base_socket_handler() { }

      /** get mutex reference for threadsafe operations. */
      virtual mutex & GetMutex() const = 0;

      /** Register StdLog object for error callback.
      \param log Pointer to log class */
      virtual void RegStdLog(StdLog *log) = 0;

      /** Log error to log class for print out / storage. */
      virtual void LogError(base_socket *p,const string & user_text,int err,const string & sys_err, ::core::log::e_level elevel = ::ca_get_level_warning()) = 0;

      // -------------------------------------------------------------------------
      // socket stuff
      // -------------------------------------------------------------------------
      /** add socket instance to socket ::map. Removal is always automatic. */
      virtual void add(socket *) = 0;
   private:
      /** remove socket from socket ::map, used by socket class. */
      virtual void remove(socket *) = 0;
   public:

      /** get status of read/write/exception file descriptor set for a socket. */
      virtual void get(SOCKET s,bool& r,bool& w,bool& e) = 0;
      /** Set read/write/exception file descriptor sets (fd_set). */
      virtual void Set(SOCKET s,bool bRead,bool bWrite,bool bException = true) = 0;
      /** Wait for events, generate callbacks. */
      virtual int Select(long sec,long usec) = 0;
      /** This method will not return until an event has been detected. */
      virtual int Select() = 0;
      /** Wait for events, generate callbacks. */
      virtual int Select(struct timeval *tsel) = 0;

      /** Check that a socket really is handled by this socket handler. */
      virtual bool Valid(socket *) = 0;
      /** Return number of sockets handled by this handler.  */
      virtual size_t get_count() = 0;

      /** Override and return false to deny all incoming connections.
      \param p listen_socket class pointer (use GetPort to identify which one) */
      virtual bool OkToAccept(socket *p) = 0;

      /** Called by socket when a socket changes state. */
      virtual void AddList(SOCKET s,list_t which_one,bool add) = 0;
      // -------------------------------------------------------------------------
      // Connection pool
      // -------------------------------------------------------------------------
      /** find available open connection (used by connection pool). */
      virtual PoolSocket * FindConnection(int type,const string & protocol,::net::address_sp&) = 0;

      /** Enable connection pool (by default disabled). */
      virtual void EnablePool(bool = true) = 0;
      /** Check pool status.
      \return true if connection pool is enabled */
      virtual bool PoolEnabled() = 0;

      // -------------------------------------------------------------------------
      // Socks4
      // -------------------------------------------------------------------------
      /** Set socks4 server ip that all new tcp sockets should use. */
      virtual void SetSocks4Host(in_addr) = 0;
      /** Set socks4 server hostname that all new tcp sockets should use. */
      virtual void SetSocks4Host(const string & ) = 0;
      /** Set socks4 server port number that all new tcp sockets should use. */
      virtual void SetSocks4Port(port_t) = 0;
      /** Set optional socks4 userid. */
      virtual void SetSocks4Userid(const string & ) = 0;
      /** If connection to socks4 server fails, immediately try direct connection to final host. */
      virtual void SetSocks4TryDirect(bool = true) = 0;
      /** get socks4 server ip.
      \return socks4 server ip */
      virtual in_addr GetSocks4Host() = 0;
      /** get socks4 port number.
      \return socks4 port number */
      virtual port_t GetSocks4Port() = 0;
      /** get socks4 userid (optional).
      \return socks4 userid */
      virtual const string & GetSocks4Userid() = 0;
      /** Check status of socks4 try direct flag.
      \return true if direct connection should be tried if connection to socks4 server fails */
      virtual bool Socks4TryDirect() = 0;
      // -------------------------------------------------------------------------
      // DNS resolve server
      // -------------------------------------------------------------------------
      /** Enable asynchronous DNS.
      \param port Listen port of asynchronous dns server */
      virtual void EnableResolver(port_t = 16667) = 0;
      /** Check resolver status.
      \return true if resolver is enabled */
      virtual bool ResolverEnabled() = 0;
      /** Queue a dns request.
      \param host Hostname to be resolved
      \param port Port number will be echoed in socket::OnResolved callback */
      virtual int Resolve(socket *,const string & host,port_t port) = 0;
      virtual int Resolve6(socket *,const string & host,port_t port) = 0;
      /** Do a reverse dns lookup. */
      virtual int Resolve(socket *,in_addr a) = 0;
      virtual int Resolve(socket *,in6_addr& a) = 0;
      /** get listen port of asynchronous dns server. */
      virtual port_t GetResolverPort() = 0;
      /** Resolver thread ready for queries. */
      virtual bool ResolverReady() = 0;
      /** Returns true if socket waiting for a resolve event. */
      virtual bool Resolving(socket *) = 0;
      /** Fetch unique trigger id. */
      virtual int TriggerID(socket *src) = 0;
      /** Subscribe socket to trigger id. */
      virtual bool Subscribe(int id, socket *dst) = 0;
      /** Unsubscribe socket from trigger id. */
      virtual bool Unsubscribe(int id, socket *dst) = 0;
      /** Execute OnTrigger for subscribed sockets.
      \param id Trigger ID
      \param data Data passed from source to destination
      \param erase Empty trigger id source and destination maps if 'true',
      Leave them in place if 'false' - if a trigger should be called many times */
      virtual void Trigger(int id, socket::TriggerData& data, bool erase = true) = 0;
      /** Indicates that the handler runs under socket_thread. */
      virtual void SetSlave(bool x = true) = 0;
      /** Indicates that the handler runs under socket_thread. */
      virtual bool IsSlave() = 0;

   };


} // namespace sockets

