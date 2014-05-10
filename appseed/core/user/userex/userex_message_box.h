#pragma once


namespace userex // ca8 + cube
{


   class CLASS_DECL_CORE message_box :
      virtual public wait_message_dialog
   {
   public:
      message_box(sp(::base::application) papp);

      void on_show(const char * pszMatter, property_set & propertyset);
      bool on_timeout();
      void on_timer_soft_reload(uint32_t dwTimeout);


   };


} // namespace core // ca8 + cube

