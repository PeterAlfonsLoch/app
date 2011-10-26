#pragma once

namespace i2com
{
   class comm_view;

   class CLASS_DECL_CA2_TESSERACT comm_form_view :
      public form_view
   {
   public:
      
      comm_view *  m_pcommview;

      comm_form_view(::ca::application * papp);

      virtual void install_message_handling(::user::win::message::dispatch * pdispatch);

      virtual void refresh();


      virtual void OnBeforeNavigate2(var & varFile, DWORD nFlags, const char * lpszTargetFrameName, byte_array& baPostedData, const char * lpszHeaders, BOOL* pbCancel);


      DECL_GEN_SIGNAL(_001OnCreate)

      void invite();

      bool BaseOnControlEvent(::user::control_event * pevent);

   };

} // namespace i2com