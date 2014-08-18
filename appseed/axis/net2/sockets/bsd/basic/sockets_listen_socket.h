/** \file listen_socket.h
**   \date  2004-02-13
**   \author grymse@alhem.net
**/

// xxx ref_Anders_Hedstrom_sockets_library.txt

#pragma once


namespace sockets
{

   /** Binds incoming port number to new socket class X.
   \ingroup basic */
   class CLASS_DECL_AXIS listen_socket_base :
      virtual public socket
   {
   public:


      int32_t m_depth;
      bool m_bDetach;


      /** Constructor.
      \param h base_socket_handler reference
      \param use_creator Optional use of creator (default true) */
      listen_socket_base(base_socket_handler& h);


   protected:


      listen_socket_base(const listen_socket_base& s);
      listen_socket_base& operator=(const listen_socket_base& );


   public:


      virtual ~listen_socket_base();


      virtual sp(socket) create_listen_socket();

      /** close file descriptor. */
      virtual void close();

      /** Bind and listen to any interface.
      \param port Port (0 is random)
      \param depth Listen queue depth */
      virtual int32_t Bind(port_t port,int32_t depth = 20);

      virtual int32_t Bind(const ::net::address & paddress,int32_t depth);

      /** Bind and listen to any interface, with optional protocol.
      \param port Port (0 is random)
      \param protocol Network protocol
      \param depth Listen queue depth */
      virtual int32_t Bind(port_t port,const string & protocol,int32_t depth = 20) ;

      /** Bind and listen to specific interface.
      \param intf Interface hostname
      \param port Port (0 is random)
      \param depth Listen queue depth */
      virtual int32_t Bind(const string & intf,port_t port,int32_t depth = 20);

      /** Bind and listen to specific interface.
      \param intf Interface hostname
      \param port Port (0 is random)
      \param protocol Network protocol
      \param depth Listen queue depth */
      virtual int32_t Bind(const string & intf,port_t port,const string & protocol,int32_t depth = 20);

      /** Bind and listen to ipv4 interface.
      \param a Ipv4 interface address
      \param port Port (0 is random)
      \param depth Listen queue depth */
      virtual int32_t Bind(in_addr a,port_t port,int32_t depth = 20);

      /** Bind and listen to ipv4 interface.
      \param a Ipv4 interface address
      \param port Port (0 is random)
      \param protocol Network protocol
      \param depth Listen queue depth */
      virtual int32_t Bind(in_addr a,port_t port,const string & protocol,int32_t depth);

      /** Bind and listen to ipv6 interface.
      \param a Ipv6 interface address
      \param port Port (0 is random)
      \param depth Listen queue depth */
      virtual int32_t Bind(in6_addr a,port_t port,int32_t depth = 20);


      /** Bind and listen to ipv6 interface.
      \param a Ipv6 interface address
      \param port Port (0 is random)
      \param protocol Network protocol
      \param depth Listen queue depth */
      virtual int32_t Bind(in6_addr a,port_t port,const string & protocol,int32_t depth);

      /** Bind and listen to network interface.
      \param ad Interface address
      \param protocol Network protocol
      \param depth Listen queue depth */
      virtual int32_t Bind(const ::net::address & paddress,const string & protocol,int32_t depth);

      /** Return assigned port number. */
//         port_t GetPort()
//       {
 //        return GetSockPort();
   //   }

      /** Return listen queue depth. */
      virtual int32_t GetDepth();

      /** OnRead on a listen_socket receives an incoming connection. */
      virtual void OnRead();

      /** Please don't use this method.
      "accept()" is handled automatically in the OnRead() method. */
      virtual SOCKET Accept(SOCKET socket, struct sockaddr *saptr, socklen_t *lenptr);

      virtual bool HasCreator();

      virtual void OnOptions(int32_t,int32_t,int32_t,SOCKET);



   };

   /** Binds incoming port number to new socket class X.
   \ingroup basic */
   template < class LISTENER >
   class listen_socket :
      virtual public listen_socket_base
   {
   public:


      LISTENER * m_creator;
      bool m_bHasCreate;



      /** Constructor.
      \param h base_socket_handler reference
      \param use_creator Optional use of creator (default true) */
      listen_socket(base_socket_handler& h,bool use_creator = true) :
         element(h.get_app()),
         base_socket(h),
         socket(h),
         listen_socket_base(h),
         m_bHasCreate(false),
         m_creator(NULL)
      {

         if (use_creator)
         {

            m_creator = new LISTENER(h);

            base_socket * plistener = m_creator->create();

            if(plistener != NULL)
            {

               if(dynamic_cast < LISTENER * >(plistener) != NULL)
               {

                  m_bHasCreate = true;

               }

               delete plistener;
            }

         }
      }

      virtual ~listen_socket()
      {
         if (m_creator)
         {
            delete m_creator;
         }
      }


      virtual sp(socket) create_listen_socket()
      {

         if(HasCreator())
         {

            return m_creator -> create();

         }
         else
         {

            return canew(LISTENER(Handler()));

         }

      }

      bool HasCreator()
      {
         return m_bHasCreate;
      }


   };


} // namespace sockets


