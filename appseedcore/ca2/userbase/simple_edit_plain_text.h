#pragma once


class CLASS_DECL_ca simple_edit_plain_text :
   virtual public ::user::edit_plain_text
{
public:

   simple_edit_plain_text(::ca::application * papp);

   DECL_GEN_SIGNAL(_001OnShowWindow)

   virtual void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);
};