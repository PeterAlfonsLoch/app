#pragma once

class CLASS_DECL_ca2 BaseSplitWnd :
   virtual public ::userbase::split_layout
{
public:
   BaseSplitWnd(::ca::application * papp);

   virtual void _001OnDraw(::ca::graphics * pdc);

   virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

   virtual ~BaseSplitWnd();

};

