#include "StdAfx.h"

namespace i2com
{

   comm_view::comm_view(::ca::application * papp) :
      ca(papp),
      ::userbase::split_layout(papp),
      ::userbase::view(papp),
      ::userbase::split_view(papp),
      place_holder_container(papp)
   {
   }

   void comm_view::_001InstallMessageHandling(::user::win::message::dispatch * pinterface)
   {
      ::userbase::split_view::_001InstallMessageHandling(pinterface);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &comm_view::_001OnCreate);
   }

   void comm_view::_001OnCreate(gen::signal_object * pobj)
   {
      pobj->previous();
      CreateViews();
   }

   void comm_view::i2com_open(const char * pszUrl)
   {
      m_strUrl = pszUrl;
      m_strRecipient = System.url().get_server(m_strUrl);
      m_pimview->i2com_open(pszUrl);
   }


   void comm_view::CreateViews()
   {
      SetPaneCount(2);

      SetSplitOrientation(orientation_vertical);
     
      set_position_rate(0, 0.4);

      

      create_context cc;
      cc.m_pCurrentDoc = get_document();
      cc.m_typeinfoNewView =  &typeid(comm_form_view);
      cc.m_pCurrentFrame = this;

      comm_form_view * pformview = dynamic_cast < comm_form_view * > (create_view(&cc, this, 100));
      m_pformview = pformview;
      if(pformview == NULL)
      {
         System.simple_message_box(NULL, "Could not create folder tree ::view");
      }
      // xxx ptopview->m_pmanager = m_pmanager;
      SetPane(0, pformview, false);
      pformview->m_pcommview = this;
      pformview->refresh();
      
      //ptopview->CreateViews();

      cc.m_pCurrentDoc = get_document();
      cc.m_typeinfoNewView =  &typeid(im_view);

      im_view * pimview = dynamic_cast < im_view * > (create_view(&cc, this, 100));
      m_pimview = pimview;
      if(pimview == NULL)
      {
         System.simple_message_box(NULL, "Could not create edit ::view");
      }
      SetPane(1, pimview, false);
      pimview->m_pcommview = this;

      layout();

   }



} // namespace i2com