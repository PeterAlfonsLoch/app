#include "StdAfx.h"


namespace winactionarea
{


   menu_view::menu_view(::ca::application * papp) :
      ca(papp),
      ::userbase::split_layout(papp),
      ::userbase::view(papp),
      ::userbase::split_view(papp),
      ::userex::split_view(papp),
      place_holder_container(papp)
   {
      m_pdocStartMenu = NULL;
      m_etranslucency      = TranslucencyPresent;


   }

   menu_view::~menu_view()
   {
   }




   #ifdef _DEBUG
   void menu_view::assert_valid() const
   {
	   ::userbase::view::assert_valid();
   }

   void menu_view::dump(dump_context & dumpcontext) const
   {
	   ::userbase::view::dump(dumpcontext);
   }
   #endif //_DEBUG

   /////////////////////////////////////////////////////////////////////////////
   // menu_view message handlers

   void menu_view::_001OnCreate(gen::signal_object * pobj) 
   {
      if(pobj->previous())
         return;

        SetPaneCount(2);

      SetSplitOrientation(orientation_vertical);
  
      set_position_rate(0, 0.2);

      SetPane(0, ::user::view_creator::create(MenuViewLeft)->m_pwnd, false);
      SetPane(1, ::user::view_creator::create(MenuViewRight)->m_pwnd, false);

   }

   void menu_view::on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint) 
   {
      ::userbase::split_view::on_update(pSender, lHint, pHint);

   }


   BOOL menu_view::PreCreateWindow(CREATESTRUCT& cs) 
   {
      cs.dwExStyle &= ~WS_EX_CLIENTEDGE;	

	   return ::userbase::view::PreCreateWindow(cs);
   }


   void menu_view::on_create_view(::user::view_creator_data * pcreatordata)
   {
      filemanager::application * pfilemanagerapp = dynamic_cast < filemanager::application * > (get_app());
      switch(pcreatordata->m_id)
      {
      case MenuViewLeft:
         {
            ::filemanager::document * pdoc = pfilemanagerapp->GetStdFileManagerTemplate()->OpenChildList(this, false, true, this);
            if(pdoc != NULL)
            {
               m_pdocStartMenu = pdoc;
               pdoc->get_filemanager_data()->m_iIconSize = 16;
               pdoc->get_filemanager_data()->m_bListText = true;
               pdoc->get_filemanager_data()->m_bListSelection = false;
               pdoc->get_filemanager_data()->m_ptemplate->m_strFilePopup = "filemanager\\file_popup.xml";
               pdoc->get_filemanager_data()->m_strDISection = "winactionarea_menu";
               pdoc->get_filemanager_data()->m_pcallback = this;
               pdoc->Initialize(true);
               pdoc->update_all_views(NULL, 1234);
               pdoc->update_all_views(NULL, 1234511); // ::view Report
               ::view * pview = pdoc->get_view();
               userbase::frame_window * pframe = dynamic_cast < userbase::frame_window * > (pview->GetParentFrame());
               if(pframe != NULL)
               {
                  pframe->ModifyStyle(WS_CAPTION, WS_CHILD, 0);
                  pframe->SetParent(this);
                  pcreatordata->m_pdoc = pdoc;
                  pcreatordata->m_pwnd = pframe;


               }
            }
         }
         break;
      case MenuViewRight:
         {
/*            create_context cc;
            cc.m_pCurrentDoc = get_document();
            cc.m_typeinfoNewView =  ::ca::get_type_info < menu_right_view > ();*/

            ::userbase::view * pview = dynamic_cast < ::userbase::view * > (view::create_view(::ca::get_type_info < menu_right_view > (), get_document(), this, 101));
            if(pview != NULL)
            {
               pcreatordata->m_pdoc = get_document();
               pcreatordata->m_pwnd = pview;
            }
         }
         break;
      default:
         ASSERT(FALSE);
         break;
      }


   }

   void menu_view::_001OnMenuMessage(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }

   void menu_view::install_message_handling(::user::win::message::dispatch * pinterface)
   {
      ::userbase::split_view::install_message_handling(pinterface);
	   IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &menu_view::_001OnCreate);
	   IGUI_WIN_MSG_LINK(WM_SIZE, pinterface, this, &menu_view::_001OnSize);
      IGUI_WIN_MSG_LINK(WM_USER + 1122  , pinterface, this, &menu_view::_001OnMenuMessage);
   }


   void menu_view::OnFileManagerOpenFile(::filemanager::data * pdata, ::fs::item_array & itema)
   {
      UNREFERENCED_PARAMETER(pdata);
      if(itema.get_size() > 0)
      {
         int i = (int) ::ShellExecuteW(
            GetTopLevelParent()->_get_handle(), 
            NULL, 
            gen::international::utf8_to_unicode("\"" + itema[0].m_strPath + "\""),
            NULL,
            gen::international::utf8_to_unicode("\"" + System.dir().name(itema[0].m_strPath) + "\""),
            SW_SHOWNORMAL);
         string str;
         str.Format("%d", i);
         //System.simple_message_box(str);
         if(i == ERROR_FILE_NOT_FOUND)
         {
         }
      }
      GetParentFrame()->ShowWindow(SW_HIDE);
   }



   void menu_view::on_show()
   {
      if(m_pdocStartMenu != NULL)
      {
         string strDir = Application.dir().userappdata("winactionarea\\menu");
         m_pdocStartMenu->FileManagerBrowse(strDir);
      }
   }


} // namespace winactionarea


