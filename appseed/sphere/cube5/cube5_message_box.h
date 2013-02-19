#pragma once


namespace cube5 // ca8 + cube5
{


   class CLASS_DECL_ca2 message_box :
      virtual public wait_message_dialog
   {
   public:
      message_box(::ca::application * papp);

      void on_show(const char * pszMatter, gen::property_set & propertyset);
      bool on_timeout();
      void on_timer_soft_reload(uint32_t dwTimeout);


   };


} // namespace cube5 // ca8 + cube5

