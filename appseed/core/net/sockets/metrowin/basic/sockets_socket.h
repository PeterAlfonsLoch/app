#pragma once


namespace sockets
{


   class base_socket_handler;


   /** \defgroup basic Basic sockets */
   /** socket base class.
   \ingroup basic */
   class CLASS_DECL_ca2 socket :
      virtual public base_socket
   {
   public:



      friend class base_socket_handler;

      base_socket_handler &   m_handler; ///< Reference of base_socket_handler in control of this socket

      /** "Default" constructor */
      socket(base_socket_handler & handler);

      virtual ~socket();

   };


} // namespace sockets




