#pragma once


namespace sockets
{


   class CLASS_DECL_AXIS trace_logger : 
      public logger
   {
   public:


      virtual void log(base_socket_handler *, base_socket * , const string & strUser, int32_t err, const string & strSystem, ::axis::log::e_level elevel = ::axis::log::level_warning);


   };


} // namespace sockets





