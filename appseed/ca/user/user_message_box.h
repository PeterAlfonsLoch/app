#pragma once

class CLASS_DECL_ca message_box :
   virtual public wait_message_dialog
{
public:
   message_box(sp(::ca::application) papp);

   void on_show(const char * pszMatter, ::ca::property_set & propertyset);
   bool on_timeout();
   void on_timer_soft_reload(uint32_t dwTimeout);


};
