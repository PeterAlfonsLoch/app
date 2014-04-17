#pragma once


class CLASS_DECL_CORE MetaControlBox :
   public ::user::uinteraction::frame::control_box
{
public:



   MetaControlBox(sp(base_application) papp);
   virtual ~MetaControlBox();


   virtual void _001OnDraw(::draw2d::graphics * pdc);

   virtual void install_message_handling(::message::dispatch *pinterface);


   DECL_GEN_SIGNAL(_001OnShowWindow);
   DECL_GEN_SIGNAL(_001OnLButtonDown);
   DECL_GEN_SIGNAL(_001OnLButtonUp);
   DECL_GEN_SIGNAL(_001OnTimer);


};



