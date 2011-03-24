#include "StdAfx.h"

namespace bergedge
{

   pane_view::pane_view(::ca::application * papp) :
      ca(papp),
      ::user::tab(papp),
      ::userbase::view(papp),
      ::userbase::tab_view(papp),
      ::userex::pane_tab_view(papp),
      m_dibBk(papp),
      place_holder_container(papp)
   {
      m_iNewArea = 0;
      m_iArea = -1;
      m_pcreateview = this;
      m_pviewdataOld = NULL;

      m_etranslucency      = TranslucencyTotal;

      m_pviewdata              = NULL;
      m_pviewdataOld              = NULL;

      m_iDisplay = -1;
      m_ppropform = NULL;

   }

   pane_view::~pane_view()
   {
   }

   #ifdef _DEBUG
   void pane_view::assert_valid() const
   {
      ::userbase::view::assert_valid();
   }

   void pane_view::dump(dump_context & dumpcontext) const
   {
      ::userbase::view::dump(dumpcontext);
   }
   #endif //_DEBUG

   void pane_view::_001OnCreate(gen::signal_object * pobj) 
   {

      if(pobj->previous())
         return;

      ::bergedge::frame * pframe = dynamic_cast < ::bergedge::frame * > (GetParentFrame());
      pframe->m_ppaneview = this;

      add_tab("3-action-launch", ::bergedge::PaneViewThreeActionLaunch);
      add_tab("menu", ::bergedge::PaneViewContextMenu);
      add_tab("win desk", ::bergedge::PaneViewWinActionArea);
      add_tab("options", ::bergedge::PaneViewConfiguration);
      add_tab("file manager", ::bergedge::PaneViewFileManager);

      
   }

   void pane_view::on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint) 
   {
      ::userbase::tab_view::on_update(pSender, lHint, pHint);
      if(lHint == 543218)
      {
         set_cur_tab_by_id(::bergedge::PaneViewWinActionArea);
      }
      if(pHint != NULL)
      {
         if(base < pane_view_update_hint >::bases(pHint))
         {
            pane_view_update_hint * puh = (pane_view_update_hint *) pHint;
            if(puh->is_type_of(pane_view_update_hint::TypeGetView))
            {
            }
            else if(puh->is_type_of(pane_view_update_hint::TypeSetView))
            {
               set_cur_tab_by_id(puh->m_eview);
            }
         }
      }
         if(pHint != NULL)
      {
         if(base < pane_view_update_hint >::bases(pHint))
         {
            pane_view_update_hint * puh = (pane_view_update_hint * ) pHint;
            if(puh->is_type_of(pane_view_update_hint::TypeOnShowKaraoke))
            {
               (dynamic_cast < userbase::frame_window * > (GetTopLevelFrame()))->SetActiveView(this);
            }
            else if(puh->is_type_of(pane_view_update_hint::TypeOnShowView))
            {
            }
         }
      }
   }

   void pane_view::on_show_view() 
   {
      ::userex::pane_tab_view::on_show_view();
      frame * pframe = dynamic_cast < frame *> (GetParentFrame());
      if(get_view_id() == ::bergedge::PaneViewFileManager)
      {
//         pframe->m_bAutoHideOnOutClick = false;
         pframe->ShowWindow(SW_MAXIMIZE);
      }
      else if(get_view_id() == ::bergedge::PaneViewContextMenu)
      {
         /*bergedge::menu_view * pview = dynamic_cast < bergedge::menu_view *  > (get_view());
         ::filemanager::document * pdoc = dynamic_cast < ::filemanager::document * >(pview->get_document());
         pdoc->FileManagerBrowse(Application.dir().userappdata("bergedge\\menu"));*/
      }
      else if(get_view_id() == ::bergedge::PaneViewConfiguration)
      {
   /*      ::user::interaction * pui = m_pformOptions->ve_display_bandwidth");
         check_interface * pcheck = dynamic_cast < check_interface * > (puie);
         if(System.savings().save().is_signalized(gen::save_display_bandwidth))
         {
            pcheck->_001SetCheck(check::checked, false);
         }
         else
         {
            pcheck->_001SetCheck(check::unchecked, false);
         }*/
      }
      else if(get_view_id() == ::bergedge::PaneViewWinActionArea)
      {
         string strDirName;
         strDirName.Format("desktop-%d", m_iDisplay);
         string strDir = Application.dir().userfolder(strDirName);
         if(m_iDisplay == 0)
         {
            check_desktop_dir(strDir);
         }
         ::filemanager::document * pdoc = dynamic_cast < ::filemanager::document * > (m_pviewdata->m_pdoc);
         pdoc->FileManagerBrowse(strDir);
      }
      else
      {
//         pframe->m_bAutoHideOnOutClick = true;
      }
      if(m_pviewdataOld != NULL)
      {
         if(m_pviewdataOld->m_pwnd != NULL)
         {
            m_pviewdataOld->m_pwnd->ShowWindow(SW_HIDE);
         }
      }
   }

   BOOL pane_view::PreCreateWindow(CREATESTRUCT& cs) 
   {
      cs.dwExStyle &= ~WS_EX_CLIENTEDGE;   

      return ::userbase::view::PreCreateWindow(cs);
   }


   void pane_view::on_create_view(view_data * pviewdata)
   {
      class bergedge * papp = dynamic_cast < class bergedge * > (get_app());
      switch(pviewdata->m_id)
      {
      case PaneViewContextMenu:
         {
/*            ::userbase::view * pview = dynamic_cast < ::userbase::view * > (create_view(typeid(bergedge::menu_view), get_document(), this, 102));
            if(pview != NULL)
            {
               pviewdata->m_pdoc = get_document();
               pviewdata->m_pwnd = pview;
            }*/
         }
         break;
      case PaneViewWinActionArea:
         {
            ::filemanager::document * pdoc = papp->GetStdFileManagerTemplate()->OpenChildList(papp, false, true, this);
            if(pdoc != NULL)
            {
               pdoc->get_filemanager_data()->m_iIconSize = 48;
               pdoc->get_filemanager_data()->m_bListText = true;
               pdoc->get_filemanager_data()->m_bListSelection = false;
               pdoc->get_filemanager_data()->m_bIconView = true;
               pdoc->get_filemanager_data()->m_pcallback = this;
               pdoc->get_filemanager_data()->m_strDISection.Format("bergedge.pane(%d)", m_iDisplay);
               pdoc->get_filemanager_data()->m_bPassBk = true;
               pdoc->Initialize(true);
               pdoc->update_all_views(NULL, 1234);
               pdoc->update_all_views(NULL, 1234525);
               ::view * pview = pdoc->get_view();
               string strDirName;
               strDirName.Format("desktop-%d", m_iDisplay);
               string strDir = Application.dir().userfolder(strDirName);
               if(m_iDisplay == 0)
               {
                  check_desktop_dir(strDir);
               }
               pdoc->FileManagerBrowse(strDir);
               if(pview != NULL)
               {
                  userbase::frame_window * pframe = dynamic_cast < userbase::frame_window * > (pview->GetParentFrame());
                  if(pframe != NULL)
                  {
                     pframe->ModifyStyle(WS_CAPTION, WS_CHILD, 0);
                     pframe->SetParent(this);
                     pviewdata->m_pdoc = pdoc;
                     pviewdata->m_pwnd = pframe;


                  }
               }
            }
         }
         break;
      case PaneViewFileManager:
         {
            ::filemanager::document * pdoc = papp->GetStdFileManagerTemplate()->OpenChild(papp, false, true, this);
            if(pdoc != NULL)
            {
               pdoc->get_filemanager_data()->m_strDISection = "winactionarea_filemanager";
               pdoc->Initialize(true);
               pdoc->update_all_views(NULL, 1234);
               pdoc->update_all_views(NULL, 123458);
               ::view * pview = pdoc->get_view();
               if(pview != NULL)
               {
                  userbase::frame_window * pframe = dynamic_cast < userbase::frame_window * > (pview->GetParentFrame());
                  if(pframe != NULL)
                  {
                     pframe->ModifyStyle(WS_CAPTION, WS_CHILD, 0);
                     pframe->SetParent(this);
                     pviewdata->m_pdoc = pdoc;
                     pviewdata->m_pwnd = pframe;


                  }
               }
            }
         }
         break;
      case PaneViewThreeActionLaunch:
         {
            ::filemanager::document * pdoc = papp->GetStdFileManagerTemplate()->OpenChildList(papp, false, true, this);
            if(pdoc != NULL)
            {
               pdoc->get_filemanager_data()->m_iIconSize = 48;
               pdoc->get_filemanager_data()->m_bListText = false;
               pdoc->get_filemanager_data()->m_bListSelection = false;
               pdoc->get_filemanager_data()->m_pcallback = this;
               pdoc->get_filemanager_data()->m_strDISection = "winactionarea_3-action-launch";
               pdoc->Initialize(true);
               pdoc->update_all_views(NULL, 1234);
               pdoc->update_all_views(NULL, 123458);
               ::view * pview = pdoc->get_view();
               string strDir = Application.dir().userappdata("bergedge\\3-action-launch");
               check_3click_dir(strDir);
               pdoc->FileManagerBrowse(strDir);
               if(pview != NULL)
               {
                  userbase::frame_window * pframe = dynamic_cast < userbase::frame_window * > (pview->GetParentFrame());
                  if(pframe != NULL)
                  {
                     pframe->ModifyStyle(WS_CAPTION, WS_CHILD, 0);
                     pframe->SetParent(this);
                     pviewdata->m_pdoc = pdoc;
                     pviewdata->m_pwnd = pframe;


                  }
               }
            }
         }
         break;
      case PaneViewConfiguration:
      {
         form_document * pdoc = System.create_form(this, this);
         if(pdoc == NULL)
            return;
         m_pformOptions = pdoc->get_typed_view < form_view > ();
         form_update_hint uh;
         uh.m_etype = form_update_hint::type_browse;
         uh.m_strForm = "bergedge\\options.xhtml";
         pdoc->update_all_views(NULL, 0, &uh);
         
         uh.m_etype = form_update_hint::type_get_form_view;
         pdoc->update_all_views(NULL, 0, &uh);

         uh.m_etype = form_update_hint::type_after_browse;
         pdoc->update_all_views(NULL, 0, &uh);




         pviewdata->m_pwnd = dynamic_cast < ::user::interaction * >(m_pformOptions->GetParentFrame());
         pviewdata->m_pdoc = pdoc;
      }
      break;
      case PaneViewFileProperties:
         {
            if(m_ppropform == NULL)
            {
               m_ppropform = new filemanager::SimpleFilePropertiesForm(get_app());
            }
            pviewdata->m_pwnd = m_ppropform->open(this, m_itema);
            if(pviewdata->m_pwnd == NULL)
               return;
            pviewdata->m_pdoc = m_ppropform->m_ptabview->get_document();

         }
         break;
      default:
         ASSERT(FALSE);
         break;
      }
   }



   void pane_view::_001OnMenuMessage(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      set_cur_tab_by_id(m_pviewdataOld->m_id);
   }

   void pane_view::_001InstallMessageHandling(::user::win::message::dispatch * pinterface)
   {
      ::userex::pane_tab_view::_001InstallMessageHandling(pinterface);

      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &pane_view::_001OnCreate);
      //IGUI_WIN_MSG_LINK(WM_SIZE, pinterface, this, &pane_view::_001OnSize);
      IGUI_WIN_MSG_LINK(WM_USER + 1122  , this, this, &pane_view::_001OnMenuMessage);
      IGUI_WIN_MSG_LINK(WM_RBUTTONUP, pinterface, this, &pane_view::_001OnRButtonUp);
      connect_command("properties", &pane_view::_001OnProperties);
   }

   void pane_view::rotate()
   {
      ::bergedge::EPaneView eviewNew;
      switch(get_view_id())
      {
      case ::bergedge::PaneViewContextMenu:
         eviewNew = ::bergedge::PaneViewWinActionArea;
         break;
      case ::bergedge::PaneViewWinActionArea:
         eviewNew = ::bergedge::PaneViewFileManager;
         break;
      case ::bergedge::PaneViewFileManager:
         eviewNew = ::bergedge::PaneViewContextMenu;
         break;
      default:
         eviewNew = ::bergedge::PaneViewWinActionArea;
      }

      set_cur_tab_by_id(eviewNew);
   }

   /*void pane_view::OnFileManagerOpenFile(
         ::filemanager::data * pdata, 
         ::fs::item_array & itema)
   {
      if(itema.get_size() > 0)
      {
         int i = (int) ::ShellExecuteW(
            GetTopLevelParent()->_get_handle(), 
            NULL, 
            L"\"" + gen::international::utf8_to_unicode(itema[0].m_strPath) + L"\"",
            NULL,
            L"\"" + gen::international::utf8_to_unicode(System.dir().name(itema[0].m_strPath)) + L"\"",
            SW_SHOWNORMAL);
         string str;
         str.Format("%d", i);
         //System.simple_message_box(str);
         if(i == ERROR_FILE_NOT_FOUND)
         {
         }
      }
      //GetParentFrame()->ShowWindow(SW_HIDE);
   }*/

   void pane_view::check_menu_dir(const char * psz)
   {
      stringa straPath;
      stringa straRelative;
      straPath.remove_all();
      System.dir().rls(System.dir().commonprograms(), &straPath, NULL, &straRelative);
      for(int i = 0; i < straPath.get_size(); i++)
      {
         string str = System.dir().path(psz, straRelative[i]);
         System.dir().mk(System.dir().name(str));
         ::CopyFile(straPath[i], str , TRUE);
      }
      straRelative.remove_all();
      straPath.remove_all();
      System.dir().rls(Application.dir().userprograms(), &straPath, NULL, &straRelative);
      for(int i = 0; i < straPath.get_size(); i++)
      {
         string str = System.dir().path(psz, straRelative[i]);
         System.dir().mk(System.dir().name(str));
         ::CopyFile(straPath[i], str, TRUE);
      }
   }

   void pane_view::check_3click_dir(const char * psz)
   {
      stringa straPath;
      stringa straRelative;
      straPath.remove_all();
      System.dir().rls(Application.dir().userquicklaunch(), &straPath, NULL, &straRelative);
      for(int i = 0; i < straPath.get_size(); i++)
      {
         string str = System.dir().path(psz, straRelative[i]);
         System.dir().mk(System.dir().name(str));
         ::CopyFile(straPath[i], str, TRUE);
      }
   }

   void pane_view::check_desktop_dir(const char * psz)
   {
      stringa straPath;
      stringa straRelative;
      char buf[4096];
      memset(buf, 0, sizeof(buf));
      SHGetSpecialFolderPath(
         NULL,
         buf,
         CSIDL_COMMON_DESKTOPDIRECTORY,
         FALSE);
      if(strlen(buf) > 0)
      {
         if(strlen(buf) > 0)
         {
            straPath.remove_all();
            straRelative.remove_all();
            System.dir().rls(buf, &straPath, NULL, &straRelative);
            for(int i = 0; i < straPath.get_size(); i++)
            {
               string str = System.dir().path(psz, straRelative[i]);
               System.dir().mk(System.dir().name(str));
               ::CopyFile(straPath[i], str, TRUE);
            }
         }
      }
      memset(buf, 0, sizeof(buf));
      SHGetSpecialFolderPath(
         NULL,
         buf,
         CSIDL_DESKTOPDIRECTORY,
         FALSE);
      if(strlen(buf) > 0)
      {
         if(strlen(buf) > 0)
         {
            straPath.remove_all();
            straRelative.remove_all();
            System.dir().rls(buf, &straPath, NULL, &straRelative);
            for(int i = 0; i < straPath.get_size(); i++)
            {
               string str = System.dir().path(psz, straRelative[i]);
               System.dir().mk(System.dir().name(str));
               ::CopyFile(straPath[i], str, TRUE);
            }
         }
      }
   }


   void pane_view::_001OnDraw(::ca::graphics * pdc)
   {

      if(m_iNewArea != m_iArea)
      {
         m_iArea = m_iNewArea;
         //string strWallpaper;
   /*
         switch(m_iArea)
         {
         case 0:
            strWallpaper = System.dir().standard_square_matter("cgcliscstlife1_23.bmp");
            break;
         case 1:
            strWallpaper = System.dir().standard_square_matter("cgcliscstlife1_24.bmp");
            break;
         case 2:
            strWallpaper = System.dir().standard_square_matter("cgcliscstlife1_25.bmp");
            break;
         case 3:on_create_on_crea
            strWallpaper = System.dir().standard_square_matter("cgcliscstlife1_26.bmp");
            break;
         default:         
            strWallpaper = System.dir().standard_square_matter("cgcliscstlife1_23.bmp");
            break;
         }
         FIBITMAP * pfi;

         ::ca::graphics * pdc = GetDC();

         pfi = System.imaging().LoadImageFile(strWallpaper);
         
         m_dibBk.From((HDC)pdc->get_os_data(), pfi, true);

         ReleaseDC(pdc);*/
         //_001RedrawWindow();
      }
      
      //m_dibBk.to(pdc, 0, 0, rectClient.right, rectClient.bottom);
      ::userex::pane_tab_view::_001OnDraw(pdc);
   }



   void pane_view::set_display(int iDisplay)
   {
      m_iDisplay = iDisplay;
   }

   void pane_view::_001OnRButtonUp(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
//      SCAST_PTR(::user::win::message::mouse, pmouse, pobj);
      /*if(get_view_id() == ::bergedge::PaneViewWinActionArea)
      {
         ::userbase::menu menu(get_app());
         menu.LoadXmlMenu("bergedge\\popup_winactionarea.xml");
         ::userbase::menu menuPopup(get_app(), menu.GetSubMenu(0));
         GetParentFrame()->SetActiveView(this);
         menuPopup.TrackPopupMenu(0, pmouse->m_pt.x, pmouse->m_pt.y, GetParentFrame());
      }*/
   }

   void pane_view::OnFileManagerOpenContextMenu(::filemanager::data * pdata)
   {
      UNREFERENCED_PARAMETER(pdata);
      if(get_view_id() == ::bergedge::PaneViewWinActionArea)
      {
         ::userbase::menu menu(get_app());
         menu.LoadXmlMenu("bergedge\\popup_winactionarea.xml");
         ::userbase::menu menuPopup(get_app(), menu.GetSubMenu(0));
         GetParentFrame()->SetActiveView(this);
         point pt;
         System.get_cursor_pos(&pt);
         menuPopup.TrackPopupMenu(0, pt.x, pt.y, GetParentFrame());
      }
   }

   /*void pane_view::OnFileManagerOpenContextMenuFolder(::filemanager::data * pdata, ::fs::item & item)
   {
   }
*/
   void pane_view::OnFileManagerOpenContextMenuFile(::filemanager::data * pdata, ::fs::item_array & itema)
   {
      UNREFERENCED_PARAMETER(pdata);
      m_itema = itema;
      set_cur_tab_by_id(::bergedge::PaneViewFileProperties);
   }

   

   void pane_view::_001OnProperties(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      if(get_view_id() == ::bergedge::PaneViewWinActionArea)
      {
         ::ShellExecute(NULL, NULL, "control.exe", "desk.cpl", NULL, SW_SHOWNORMAL);
      }
   }


   void pane_view::_001InitializeFormPreData(::user::form * pform)
   {
      class user::control::descriptor control;

      control.m_bTransparent = true;
      control.set_type(user::control::type_check_box);
      control.m_id = "save_display_bandwidth";
      control.set_ddx_dbflags(
            "",
            "ca2_fontopus_votagus", 
            "savings",
            gen::resource_display_bandwidth);
   //   control.add_function(user::control::function_static);
      pform->_001AddControl(control);

      control.m_bTransparent = true;
      control.set_type(user::control::type_check_box);
      control.m_id = "save_processing";
      control.set_ddx_dbflags(
            "",
            "ca2_fontopus_votagus", 
            "savings",
            gen::resource_processing);
   //   control.add_function(user::control::function_static);
      pform->_001AddControl(control);

      control.m_bTransparent = true;
      control.set_type(user::control::type_check_box);
      control.m_id = "save_memory";
      control.set_ddx_dbflags(
            "",
            "ca2_fontopus_votagus", 
            "savings",
            gen::resource_memory);
   //   control.add_function(user::control::function_static);
      pform->_001AddControl(control);
      
      control.m_bTransparent = true;
      control.set_type(user::control::type_check_box);
      control.m_id = "enable_wallpaper";
      control.set_ddx_dbflags(
            "",
            "ca2_fontopus_votagus", 
            "bergedge",
            0);
   //   control.add_function(user::control::function_static);
      pform->_001AddControl(control);

   }
   bool pane_view::BaseOnControlEvent(::user::form * pview, ::user::control_event * pevent)
   {
      UNREFERENCED_PARAMETER(pview);
      UNREFERENCED_PARAMETER(pevent);
      return false;
   }

} // namespace bergedge