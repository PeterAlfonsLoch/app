#pragma once

class CLASS_DECL_CORE BaseSplitWnd :
   virtual public ::user::split_layout
{
public:
   BaseSplitWnd(::aura::application * papp);

   virtual void _001OnDraw(::draw2d::graphics * pgraphics);

   virtual bool pre_create_window(::user::create_struct& cs);

   virtual ~BaseSplitWnd();

};

