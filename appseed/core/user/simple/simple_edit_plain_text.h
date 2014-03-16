#pragma once


class CLASS_DECL_CORE simple_edit_plain_text :
   virtual public ::user::edit_plain_text
{
public:

   
   simple_edit_plain_text(sp(base_application) papp);
   virtual ~simple_edit_plain_text();


   virtual void install_message_handling(::message::dispatch * pinterface);

   
   DECL_GEN_SIGNAL(_001OnShowWindow)

   virtual bool ShowWindow(int32_t nCmdShow);

};