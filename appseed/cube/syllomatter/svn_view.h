#pragma once


class CLASS_DECL_CA2_CUBE svn_view :
   public ::userbase::split_view
{
public:
   svn_view(::ca::application * papp);
   virtual ~svn_view();

   void CreateViews();

   syllomatter_pane_view * m_ppaneview;
   ::userbase::edit_plain_text_view * m_peditview;
   syllomatter_list_view * m_plistview;

};