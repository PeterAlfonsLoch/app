#include "StdAfx.h"

namespace i2com
{

   im_view::im_view(::ca::application * papp) :
      ca(papp),
      ::userbase::split_layout(papp),
      ::userbase::view(papp),
      ::userbase::split_view(papp),
      place_holder_container(papp)
   {
   }

   void im_view::install_message_handling(::user::win::message::dispatch * pinterface)
   {
      ::userbase::split_view::install_message_handling(pinterface);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &im_view::_001OnCreate);
   }

   void im_view::_001OnCreate(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
//      SCAST_PTR(::user::win::message::create, pcreate, pobj)
         CreateViews();
   }

   void im_view::i2com_open(const char * pszUrl)
   {
      m_strUrl = pszUrl;
      m_strRecipient = System.url().get_server(m_strUrl);
   }


   void im_view::CreateViews()
   {
      SetPaneCount(2);

      SetSplitOrientation(orientation_horizontal);
     
      set_position_rate(0, 0.8);

      

/*      create_context cc;
      cc.m_pCurrentDoc = get_document();
      cc.m_typeinfoNewView =  ::ca::get_type_info < im_stream_view > ();
      cc.m_pCurrentFrame = this;*/

      im_stream_view * pstreamview = create_view < im_stream_view > ();
      m_pstreamview = pstreamview;
      if(pstreamview == NULL)
      {
         System.simple_message_box(NULL, "Could not create folder tree ::view");
      }
      // xxx ptopview->m_pmanager = m_pmanager;
      SetPane(0, pstreamview, false);
      pstreamview->m_pimview = this;
      
      //ptopview->CreateViews();

/*      cc.m_pCurrentDoc = get_document();
      cc.m_typeinfoNewView =  ::ca::get_type_info < im_edit_view > ();*/

      im_edit_view * peditview = create_view < im_edit_view > ();
      m_peditview = peditview;
      if(peditview == NULL)
      {
         System.simple_message_box(NULL, "Could not create edit ::view");
      }
      SetPane(1, peditview, false);
      peditview->m_pimview = this;

      layout();

   }



} // namespace i2com