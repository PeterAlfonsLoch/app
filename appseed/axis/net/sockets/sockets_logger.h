#pragma once


namespace sockets
{


   class axis_socket_handler;
   class axis_socket;


   class CLASS_DECL_AXIS logger :
      virtual public ::object
   {
   public:


      virtual void log(axis_socket_handler *, axis_socket * , const string & strUser, int32_t err, const string & strSystem, ::aura::log::e_level elevel = ::aura::log::level_warning) = 0;


   };


} // namespace sockets




