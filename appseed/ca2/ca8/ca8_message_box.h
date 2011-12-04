#pragma once


namespace ca8
{


   class CLASS_DECL_ca2 message_box :
      virtual public wait_message_dialog
   {
   public:
      message_box(::ca::application * papp);

      void on_show(const char * pszMatter, gen::property_set & propertyset);
      bool on_timeout();
      void on_timer_soft_reload(DWORD dwTimeout);


   };


} // namespace ca8

