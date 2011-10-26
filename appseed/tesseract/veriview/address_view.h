#pragma once

namespace veriview
{

   class CLASS_DECL_CA2_TESSERACT address_view :
      virtual public ::userbase::edit_plain_text_view,
      virtual public ::userex::autocomplete::interaction
   {
   public:

      bool                          m_bVoidSync;

      address_view(::ca::application * papp);


      virtual void install_message_handling(::user::win::message::dispatch * pinterface);

      void _017Synchronize();

      main_document * get_document();

      virtual void autocomplete_set_text(const char * pszText);

      bool BaseOnControlEvent(::user::control_event * pevent);

      void on_update(::view * pSender, LPARAM lHint, ::radix::object* phint);

      virtual void _001OnUpdate();
   };

} // namespace veriview