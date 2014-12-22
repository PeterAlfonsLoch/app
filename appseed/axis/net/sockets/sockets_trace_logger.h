#pragma once


namespace sockets
{


   class CLASS_DECL_AXIS trace_logger : 
      public logger
   {
   public:


      virtual void log(axis_socket_handler *, axis_socket * , const string & strUser, int32_t err, const string & strSystem, ::aura::log::e_level elevel = ::aura::log::level_warning);


   };


} // namespace sockets





