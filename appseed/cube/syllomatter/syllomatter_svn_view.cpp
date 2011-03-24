#include "StdAfx.h"

svn_view::svn_view(::ca::application * papp) :
   ca(papp),
   ::userbase::split_layout(papp),
   ::userbase::view(papp),
   ::userbase::split_view(papp),
   place_holder_container(papp)
{
}

svn_view::~svn_view()
{
}



void svn_view::CreateViews()
{
   SetPaneCount(2);

   SetSplitOrientation(orientation_horizontal);
  
   set_position_rate(0, 0.3);

   

   create_context cc;
   cc.m_pCurrentDoc = get_document();
   cc.m_typeinfoNewView =  &typeid(::userbase::edit_plain_text_view);

   ::userbase::edit_plain_text_view * ptopview = dynamic_cast < ::userbase::edit_plain_text_view * > (create_view(typeid(::userbase::edit_plain_text_view), get_document(), this, 100));
   m_peditview = ptopview;
   if(ptopview == NULL)
   {
      System.simple_message_box(NULL, "Could not create folder tree ::view");
   }
   SetPane(0, ptopview, true);

   cc.m_pCurrentDoc = get_document();
   //cc.m_typeinfoNewView =  &c;

   
   syllomatter_list_view * plistview = dynamic_cast < syllomatter_list_view * > (create_view(typeid(syllomatter_list_view), get_document(), this, 101));
   m_plistview = plistview;
   if(m_plistview == NULL)
   {
      System.simple_message_box(NULL, "Could not create file list ::view");
   }
   m_plistview->m_psvnview = this;
   SetPane(1, m_plistview, true);
   layout();
}
