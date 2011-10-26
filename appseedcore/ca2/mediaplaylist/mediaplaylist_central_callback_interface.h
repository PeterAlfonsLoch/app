#pragma once


namespace mediaplaylist
{

   enum e_event
   {
      event_before_open,
   };

   class document;

   class CLASS_DECL_ca central_callback_interface :
      virtual public ::radix::object
   {
   public:
      central * m_pcentral;

      virtual void OnEvent(e_event eevent);
      central_callback_interface();
      virtual ~central_callback_interface();

      virtual document * OnBeforeOpenPlaylist();

   };


} // namespace mediaplaylist


