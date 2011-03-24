#pragma once

class CLASS_DECL_ca simple_edit :
   public ::userbase::edit_plain_text
{
public:


   simple_edit(::ca::application * papp);
   virtual ~simple_edit();


   virtual void pre_subclass_window();

   virtual void _001OnDraw(::ca::graphics * pdc);
   virtual void _001OnNcDraw(::ca::graphics * pdc);

   virtual void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);

   afx_msg BOOL OnEraseBkgnd(::ca::graphics * pgraphics);

};
