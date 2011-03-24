#pragma once

class CLASS_DECL_ca simple_tab_control :
   virtual public ::user::interaction,
   virtual public ::user::tab
{
public:
   simple_tab_control(::ca::application * papp);

   virtual void pre_subclass_window();

   virtual void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);

   virtual void _001OnNcDraw(::ca::graphics * pdc);
   virtual void _001OnDraw(::ca::graphics * pdc);
   virtual ~simple_tab_control();

   afx_msg BOOL OnEraseBkgnd(::ca::graphics * pgraphics);
};

