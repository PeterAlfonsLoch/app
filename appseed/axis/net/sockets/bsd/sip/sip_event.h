#pragma once


namespace sockets
{


   class CLASS_DECL_AXIS sip_event :
      virtual public axis_object
   {
   public:
      enum e_event
      {
         event_invite, 
      };

      e_event     m_eevent;

      sip_event(::aura::application * papp);
   };


} // namespace sockets



