#pragma once

class CLASS_DECL_ca2 simple_button :
   public ::userbase::button
{
public:
   simple_button(::ca::application * papp);

   bool     m_bTransparent;
   ::ca::brush_sp   m_brushBkg;
   bool     m_bFocus;


protected:
   virtual void pre_subclass_window();
public:
   virtual void install_message_handling(::gen::message::dispatch * pinterface);

   virtual void _001OnDraw(::ca::graphics * pdc);
   virtual ~simple_button();

   virtual void ResizeToFit();

   // Generated message ::collection::map functions
protected:
   DECL_GEN_SIGNAL(_001OnCtlColor)
   DECL_GEN_SIGNAL(_001OnSetFocus)

   
};
