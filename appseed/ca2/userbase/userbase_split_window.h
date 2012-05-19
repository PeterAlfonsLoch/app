#pragma once

class CLASS_DECL_ca2 BaseSplitWnd :
   virtual public ::userbase::split_layout
{
public:
   BaseSplitWnd(::ca::application * papp);

   virtual void _001OnDraw(::ca::graphics * pdc);

   virtual bool pre_create_window(CREATESTRUCT& cs);

   virtual ~BaseSplitWnd();

};

