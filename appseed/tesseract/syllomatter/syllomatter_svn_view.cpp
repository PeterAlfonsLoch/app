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

   

/*   create_context cc;
   cc.m_pCurrentDoc = get_document();
   cc.m_typeinfoNewView =  ::ca::get_type_info < ::userbase::edit_plain_text_view > ();*/

   ::userbase::edit_plain_text_view * ptopview = create_view < ::userbase::edit_plain_text_view > ();
   m_peditview = ptopview;
   if(ptopview == NULL)
   {
      System.simple_message_box(NULL, "Could not create folder tree ::view");
   }
   SetPane(0, ptopview, true);

//   cc.m_pCurrentDoc = get_document();
   //cc.m_typeinfoNewView =  &c;

   
   syllomatter_list_view * plistview = create_view < syllomatter_list_view > ();
   m_plistview = plistview;
   if(m_plistview == NULL)
   {
      System.simple_message_box(NULL, "Could not create file list ::view");
   }
   m_plistview->m_psvnview = this;
   SetPane(1, m_plistview, true);
   layout();
}
