#pragma once

namespace userex
{

class pane_view;

class CLASS_DECL_CORE pane_split_view :
   virtual public ::user::split_view
{
public:
   pane_split_view(sp(::base::application) papp);
   virtual ~pane_split_view();

   sp(pane_view) m_ppaneview;
};


} // namespace userex