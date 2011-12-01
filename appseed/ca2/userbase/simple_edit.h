#pragma once

class CLASS_DECL_ca simple_edit :
   public ::userbase::edit_plain_text
{
public:


   simple_edit(::ca::application * papp);
   virtual ~simple_edit();


   virtual void pre_subclass_window();

   virtual void _001OnDraw(::ca::graphics * pdc);

   virtual void install_message_handling(::gen::message::dispatch * pinterface);

};
