#pragma once


namespace sockets
{


   class sip_socket;


   class CLASS_DECL_AXIS sip_callback :
      virtual public base_object
   {
   public:

      void on_sip_event(sip_socket * psocket, sip_event * pevent);
   };


} // namespace sockets



