#pragma once
namespace bsd
{

namespace sockets
{

   class CLASS_DECL_ca sip_event :
      virtual public base_object
   {
   public:
      enum e_event
      {
         event_invite, 
      };

      e_event     m_eevent;

      sip_event(::ca::application * papp);
   };

} // namespace sockets

} // namespace bsd