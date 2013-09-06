#pragma once


class CLASS_DECL_ca2 simple_edit_plain_text :
   virtual public ::user::edit_plain_text
{
public:

   simple_edit_plain_text(sp(base_application) papp);

   DECL_GEN_SIGNAL(_001OnShowWindow)

   virtual void install_message_handling(::ca2::message::dispatch * pinterface);
};