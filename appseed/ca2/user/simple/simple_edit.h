#pragma once

class CLASS_DECL_ca2 simple_edit :
   public ::user::edit_plain_text
{
public:


   simple_edit(sp(::ca::application) papp);
   virtual ~simple_edit();


   virtual void pre_subclass_window();

   virtual void _001OnDraw(::ca::graphics * pdc);

   virtual void install_message_handling(::ca::message::dispatch * pinterface);

};
