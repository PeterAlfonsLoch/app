#pragma once

class CLASS_DECL_CORE simple_tab_control :
   virtual public ::user::interaction,
   virtual public ::user::tab
{
public:


   simple_tab_control(sp(::aura::application) papp);
   virtual ~simple_tab_control();


   virtual void pre_subclass_window();

   virtual void install_message_handling(::message::dispatch * pinterface);

   virtual void _001OnDraw(::draw2d::graphics * pdc);

};

