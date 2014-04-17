#pragma once


class CLASS_DECL_CORE simple_button :
   virtual public ::user::button
{
public:
   
   
   bool                 m_bTransparent;
   ::draw2d::brush_sp       m_brushBkg;
   bool                 m_bFocus;


   simple_button(sp(base_application) papp);
   virtual ~simple_button();



   virtual void pre_subclass_window();
   virtual void install_message_handling(::message::dispatch * pinterface);

   virtual void _001OnDraw(::draw2d::graphics * pdc);

   virtual void ResizeToFit();

   DECL_GEN_SIGNAL(_001OnCtlColor);
   DECL_GEN_SIGNAL(_001OnSetFocus);


};



