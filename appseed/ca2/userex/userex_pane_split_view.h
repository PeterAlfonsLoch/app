#pragma once

namespace userex
{

class pane_view;

class CLASS_DECL_ca2 pane_split_view :
   virtual public ::userbase::split_view
{
public:
   pane_split_view(::ca::applicationsp papp);
   virtual ~pane_split_view();

   pane_view * m_ppaneview;
};


} // namespace userex