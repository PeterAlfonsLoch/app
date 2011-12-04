#pragma once


class CLASS_DECL_ca2 simple_combo_box :
   public ::userbase::combo_box
{
public:
   simple_combo_box();


   virtual void pre_subclass_window();

   virtual void _001OnDraw(::ca::graphics * pdc);
   virtual ~simple_combo_box();

   BOOL OnEraseBkgnd(::ca::graphics * pgraphics);
};

