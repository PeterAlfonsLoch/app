#pragma once

class CLASS_DECL_ca BaseSplitWnd :
   virtual public ::userbase::split_layout
{
public:
   BaseSplitWnd(::ax::application * papp);

   virtual void _001OnDraw(::ax::graphics * pdc);

   virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

   virtual ~BaseSplitWnd();

};

