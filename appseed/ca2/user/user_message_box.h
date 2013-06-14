#pragma once

class CLASS_DECL_ca2 message_box :
   virtual public wait_message_dialog
{
public:
   message_box(sp(::ca2::application) papp);

   void on_show(const char * pszMatter, ::ca2::property_set & propertyset);
   bool on_timeout();
   void on_timer_soft_reload(uint32_t dwTimeout);


};
