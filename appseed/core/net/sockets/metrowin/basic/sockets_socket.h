#pragma once


namespace sockets
{

   class base_socket_handler;

   class socket;

   typedef map < SOCKET, SOCKET, sp(socket), sp(socket) > socket_map;

   typedef ::comparable_eq_list < sp(socket) > socket_list;

   /** \defgroup basic Basic sockets */
   /** socket base class.
   \ingroup basic */
   class CLASS_DECL_ca2 socket :
      virtual public base_socket
   {
   public:



      friend class base_socket_handler;

      base_socket_handler &   m_handler; ///< Reference of base_socket_handler in control of this socket

      static SOCKET s_socketNextIdSeed;
      static socket_map s_mapSocket;
      bool                    m_bOnConnect;
      bool                    m_bExpectResponse;
      bool                    m_bExpectRequest;


      /** "Default" constructor */
      socket(base_socket_handler & handler);

      virtual ~socket();


      /** Assign this base_socket a file descriptor created
      by a call to base_socket() or otherwise. */
      void attach(::Platform::Object ^ o);

      virtual void run();


   };






} // namespace sockets




