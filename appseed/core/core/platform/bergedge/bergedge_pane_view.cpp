#include "framework.h"


namespace bergedge
{


   pane_view::pane_view(sp(::axis::application) papp) :
      element(papp),
      ::user::tab(papp),
      
      ::user::tab_view(papp),
      ::userex::pane_tab_view(papp),
      m_dibBk(papp),
      place_holder_container(papp)
   {

      m_iNewArea        = 0;
      m_iArea           = -1;
      m_pviewdataOld    = NULL;

      m_pviewdata       = NULL;
      m_pviewdataOld    = NULL;

      m_iDisplay        = -1;
      m_ppropform       = NULL;
      m_dataid          = "core::bergedge::pane_view";

      get_data()->m_matchanyRestore.add(new ::core::match::prefix("app:"));

   }

   pane_view::~pane_view()
   {
   }

#ifdef DEBUG
   void pane_view::assert_valid() const
   {
      ::user::impact::assert_valid();
   }

   void pane_view::dump(dump_context & dumpcontext) const
   {
      ::user::impact::dump(dumpcontext);
   }
#endif //DEBUG

   void pane_view::_001OnCreate(signal_details * pobj)
   {

      if(pobj->previous())
         return;

      sp(::bergedge::frame) pframe = (GetParentFrame());
      pframe->m_ppaneview = this;

      add_tab("application", "::bergedge::pane_view_application");
      add_tab("3-action-launch", ::bergedge::PaneViewThreeActionLaunch);
      add_tab("menu", ::bergedge::PaneViewContextMenu);
      add_tab("win desk", ::bergedge::PaneViewWinActionArea);
      add_tab("options", ::bergedge::PaneViewConfiguration);
      add_tab("Open", "file_manager");

      set_cur_tab_by_id(::bergedge::PaneViewWinActionArea);

   }

   void pane_view::on_update(sp(::user::impact) pSender, LPARAM lHint, object* pHint)
   {
      ::user::tab_view::on_update(pSender, lHint, pHint);
      if(lHint == 543218)
      {
         set_cur_tab_by_id(::bergedge::PaneViewWinActionArea);
      }
      if(pHint != NULL)
      {
         if(base_class < pane_view_update_hint >::bases(pHint))
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
         if(base_class < pane_view_update_hint >::bases(pHint))
         {
            pane_view_update_hint * puh = (pane_view_update_hint * ) pHint;
            if(puh->is_type_of(pane_view_update_hint::TypeOnShowKaraoke))
            {
               ( (GetTopLevelFrame().m_p))->SetActiveView(this);
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
//      sp(frame) pframe =  (GetParentFrame());
      string strId = get_view_id();
      if(::str::begins_eat(strId, "app:"))
      {
         sp(::axis::application) pappTab;
         if(Session.m_mapApplication.Lookup("application:" + strId, pappTab))
         {
            platform().m_pappCurrent = pappTab;
            platform().m_pappCurrent = pappTab;
         }
         sp(::simple_frame_window) pframeApp =  (m_pviewdata->m_pwnd.m_p);
         if(pframeApp != NULL)
         {
            pframeApp->WfiFullScreen();
         }
      }
      else if(strId == "::bergedge::pane_view_application")
      {
         string strDirName;
         strDirName.Format("application-%d", 0);
         string strDir = Application.dir().userappdata("bergedge", strDirName);
         sp(::filemanager::manager) pdoc =  (m_pviewdata->m_pdoc);
         pdoc->FileManagerBrowse(strDir, ::action::source::system_default());
      }
      else if(strId == "file_manager")
      {
//         pframe->m_bAutoHideOnOutClick = false;
         // pframe->ShowWindow(SW_MAXIMIZE);
      }
      else if(get_view_id() == ::bergedge::PaneViewContextMenu)
      {
         /*bergedge::menu_view * pview = dynamic_cast < bergedge::menu_view *  > (get_view());
         sp(::filemanager::manager) pdoc = (pview->get_document());
         pdoc->FileManagerBrowse(Application.dir().userappdata("bergedge\\menu"), ::action::source::system_default());*/
      }
      else if(get_view_id() == ::bergedge::PaneViewConfiguration)
      {
   /*      sp(::user::interaction) pui = m_pformOptions->ve_display_bandwidth");
         check_interface * pcheck = dynamic_cast < check_interface * > (puie);
         if(Session.savings().save().is_signalized(::core::save_display_bandwidth))
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
         if(m_iDisplay <= 0)
         {
            check_desktop_dir(strDir);
         }
         sp(::filemanager::manager) pdoc =  (m_pviewdata->m_pdoc);
         pdoc->FileManagerBrowse(strDir, ::action::source::system_default());
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

   bool pane_view::pre_create_window(::user::create_struct& cs)
   {
      cs.dwExStyle &= ~WS_EX_CLIENTEDGE;

      return ::user::impact::pre_create_window(cs);
   }


   void pane_view::on_create_view(::user::view_creator_data * pcreatordata)
   {

      string strId = pcreatordata->m_id;

      if(::str::begins_eat(strId, "app:"))
      {
         sp(::axis::application) pappTab;
         if(!Session.m_mapApplication.Lookup("application:" + strId, pappTab))
         {

            application_bias * pbiasCreate = new application_bias;
            pbiasCreate->m_puiParent = pcreatordata->m_pholder;

            sp(::create_context) createcontext(allocer());
            createcontext->m_spApplicationBias = pbiasCreate;
            createcontext->m_spCommandLine->_001ParseCommandFork(strId);

            string str;
            str = ::str::from((int_ptr) createcontext->m_spApplicationBias->m_puiParent);
            //simple_message_box(NULL, str, str, MB_ICONEXCLAMATION);
            Session.request_create(createcontext);

         }

         string strIcon = sess(platform().m_pappCurrent).dir().matter("mainframe/icon48.png");
         pane * ppane = (pane *) get_pane_by_id(pcreatordata->m_id);
         if(sess(platform().m_pappCurrent).file().exists(strIcon))
         {
            ppane->m_dib.alloc(allocer());
            ppane->m_dib.load_from_file(strIcon);
         }
         else
         {
            ppane->m_istrTitleEx = pcreatordata->m_id;
         }
         layout();
      }
      else if(strId == "::bergedge::pane_view_application")
      {
         pcreatordata->m_eflag.signalize(::user::view_creator_data::flag_hide_all_others_on_show);
         sp(::filemanager::manager) pdoc = platform().filemanager().std().open_child_list(false,true,this);
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
            sp(::user::impact) pview = pdoc->get_view();
            string strDirName;
            strDirName.Format("application-%d", 0);
            string strDir = Application.dir().userappdata("bergedge", strDirName);
            POSITION pos = System.m_mapAppLibrary.get_start_position();
            string strApp;
            string strLibrary;
            while(pos != NULL)
            {
               System.m_mapAppLibrary.get_next_assoc(pos, strApp, strLibrary);
               if(::str::begins_eat(strApp, "application:"))
               {
                  Application.file().put_contents(System.dir().path(strDir, strApp + ".core"), "ca2prompt\n" + strApp);
               }
            }
            pdoc->FileManagerBrowse(strDir, ::action::source::system_default());
            if(pview != NULL)
            {
               sp(::user::frame_window) pframe = (pview->GetParentFrame());
               if(pframe != NULL)
               {
                  pcreatordata->m_pdoc = pdoc;
                  pcreatordata->m_pwnd = pframe;


               }
            }
         }
      }
      else
      {
         switch(pcreatordata->m_id)
         {
         case PaneViewContextMenu:
            {
   /*            sp(::user::impact) pview = (create_view(System.type_info < bergedge::menu_view > (), get_document(), this, 102));
               if(pview != NULL)
               {
                  pcreatordata->m_pdoc = get_document();
                  pcreatordata->m_pwnd = pview;
               }*/
            }
            break;
         case PaneViewWinActionArea:
            {
               pcreatordata->m_eflag.signalize(::user::view_creator_data::flag_hide_all_others_on_show);
               ::filemanager::manager_template * ptemplate = &platform().filemanager().std();
               sp(::filemanager::manager) pdoc = ptemplate->open_child_list(false, true, pcreatordata->m_pholder);
               if(pdoc != NULL)
               {
                  pdoc->get_filemanager_data()->m_iIconSize = 48;
                  pdoc->get_filemanager_data()->m_bListText = true;
                  pdoc->get_filemanager_data()->m_bListSelection = false;
                  pdoc->get_filemanager_data()->m_bIconView = true;
                  pdoc->get_filemanager_data()->m_pcallback = this;
                  pdoc->get_filemanager_data()->m_strDISection.Format("bergedge.pane(%d)", m_iDisplay);
                  pdoc->get_filemanager_data()->m_bPassBk = false;
                  pdoc->Initialize(true);
                  pdoc->update_all_views(NULL, 1234);
                  pdoc->update_all_views(NULL, 1234525);
                  sp(::user::impact) pview = pdoc->get_view();
                  string strDirName;
                  strDirName.Format("desktop-%d", m_iDisplay);
                  string strDir = Application.dir().userfolder(strDirName);
                  if(m_iDisplay <= 0)
                  {
                     check_desktop_dir(strDir);
                  }
                  pdoc->FileManagerBrowse(strDir, ::action::source::system_default());
                  if(pview != NULL)
                  {
                     sp(::user::frame_window) pframe = (pview->GetParentFrame());
                     if(pframe != NULL)
                     {
                        pcreatordata->m_pdoc = pdoc;
                     }
                  }
               }
            }
            break;
         case PaneViewThreeActionLaunch:
            {
               sp(::filemanager::manager) pdoc = platform().filemanager().std().open_child_list(false, true, pcreatordata->m_pholder);
               if(pdoc != NULL)
               {
                  pdoc->get_filemanager_data()->m_iIconSize = 48;
                  pdoc->get_filemanager_data()->m_bListText = true;
                  pdoc->get_filemanager_data()->m_bListSelection = false;
                  pdoc->get_filemanager_data()->m_pcallback = &platform().filemanager();
                  pdoc->get_filemanager_data()->m_bIconView = true;
                  pdoc->get_filemanager_data()->m_strDISection = "winactionarea_3-action-launch";
                  pdoc->Initialize(true);
                  pdoc->update_all_views(NULL, 1234);
                  //pdoc->update_all_views(NULL, 123458);
                  pdoc->update_all_views(NULL, 1234525);
                  sp(::user::impact) pview = pdoc->get_view();
                  string strDir = Application.dir().userappdata("bergedge\\3-action-launch");
                  check_3click_dir(strDir);
                  pdoc->FileManagerBrowse(strDir, ::action::source::system_default());
                  if(pview != NULL)
                  {
                     sp(::user::frame_window) pframe = (pview->GetParentFrame());
                     if(pframe != NULL)
                     {
                        pcreatordata->m_pdoc = pdoc;
                     }
                  }
               }
            }
            break;
         case PaneViewConfiguration:
         {
            sp(::form_document) pdoc = System.userex()->create_form(this, this);
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




            pcreatordata->m_pwnd = m_pformOptions->GetParentFrame();
            pcreatordata->m_pdoc = pdoc;
         }
         break;
         case PaneViewFileProperties:
            {
               if(m_ppropform == NULL)
               {
                  m_ppropform = new ::filemanager::file_properties_form(get_app());
               }
               pcreatordata->m_pwnd = m_ppropform->open(this, m_itema);
               if(pcreatordata->m_pwnd == NULL)
                  return;
               pcreatordata->m_pdoc = m_ppropform->m_ptabview->get_document();

            }
            break;
         default:
            break;
         }
      }
      ::userex::pane_tab_view::on_create_view(pcreatordata);
   }



   void pane_view::_001OnMenuMessage(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      set_cur_tab_by_id(m_pviewdataOld->m_id);
   }

   void pane_view::install_message_handling(::message::dispatch * pinterface)
   {
      ::userex::pane_tab_view::install_message_handling(pinterface);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &pane_view::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_USER + 1122  , this, this, &pane_view::_001OnMenuMessage);
      IGUI_WIN_MSG_LINK(WM_RBUTTONUP, pinterface, this, &pane_view::_001OnRButtonUp);
      connect_command("properties", &pane_view::_001OnProperties);
   }

   void pane_view::rotate()
   {
   }

   /*void pane_view::OnFileManagerOpenFile(
         ::filemanager::data * pdata,
         ::fs::item_array & itema)
   {
      if(itema.get_size() > 0)
      {
         int32_t i = (int32_t) ::ShellExecuteW(
            GetTopLevel()->get_handle(),
            NULL,
            L"\"" + ::str::international::utf8_to_unicode(itema[0].m_strPath) + L"\"",
            NULL,
            L"\"" + ::str::international::utf8_to_unicode(System.dir().name(itema[0].m_strPath)) + L"\"",
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
      Application.dir().rls(System.dir().commonprograms(), &straPath, NULL, &straRelative);
      for(int32_t i = 0; i < straPath.get_size(); i++)
      {
         string str = System.dir().path(psz, straRelative[i]);
         Application.dir().mk(System.dir().name(str));
         Application.file().copy(str, straPath[i], true);
      }
      straRelative.remove_all();
      straPath.remove_all();
      Application.dir().rls(System.dir().userprograms(NULL), &straPath, NULL, &straRelative);
      for(int32_t i = 0; i < straPath.get_size(); i++)
      {
         string str = System.dir().path(psz, straRelative[i]);
         Application.dir().mk(System.dir().name(str));
         Application.file().copy(str, straPath[i], true);
      }
   }

   void pane_view::check_3click_dir(const char * psz)
   {

      if(Application.dir().is(psz))
      {
         return;
      }

      Application.dir().mk(psz);
      string strDir(psz);


      POSITION pos = System.m_mapAppLibrary.get_start_position();

      string strApp;
      string strLibrary;

      while(pos != NULL)
      {
         System.m_mapAppLibrary.get_next_assoc(pos, strApp, strLibrary);
         if(::str::begins_eat(strApp, "application:"))
         {
            Application.file().put_contents(System.dir().path(strDir, strApp + ".core"), "ca2prompt\r\n"+ strApp);
         }
      }

      //Application.file().put_contents(System.dir().path(strDir, "veriwell Musical Player.core"), "ca2prompt\r\nmplite");
/*      stringa straPath;
      stringa straRelative;
      straPath.remove_all();
      System.dir().rls(Application.dir().userquicklaunch(), &straPath, NULL, &straRelative);
      for(int32_t i = 0; i < straPath.get_size(); i++)
      {
         string str = System.dir().path(psz, straRelative[i]);
         Application.dir().mk(System.dir().name(str));
         ::CopyFile(straPath[i], str, TRUE);
      }*/
   }

   void pane_view::check_desktop_dir(const char * psz)
   {
#ifdef WINDOWSEX
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
            Application.dir().rls(buf, &straPath, NULL, &straRelative);
            for(int32_t i = 0; i < straPath.get_size(); i++)
            {
               string str = System.dir().path(psz, straRelative[i]);
               Application.dir().mk(System.dir().name(str));
               Application.file().copy(str, straPath[i], true);
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
            Application.dir().rls(buf, &straPath, NULL, &straRelative);
            for(int32_t i = 0; i < straPath.get_size(); i++)
            {
               string str = System.dir().path(psz, straRelative[i]);
               Application.dir().mk(System.dir().name(str));
               ::CopyFile(straPath[i], str, TRUE);
            }
         }
      }
#else
      //throw todo(get_app());
#endif
   }


   void pane_view::_001OnDraw(::draw2d::graphics * pdc)
   {

      if(m_iNewArea != m_iArea)
      {
         m_iArea = m_iNewArea;
         //string strWallpaper;
   /*
         switch(m_iArea)
         {
         case 0:
            strWallpaper = System.dir().standard_square_matter("windeskframe1_23.bmp");
            break;
         case 1:
            strWallpaper = System.dir().standard_square_matter("windeskframe1_24.bmp");
            break;
         case 2:
            strWallpaper = System.dir().standard_square_matter("windeskframe1_25.bmp");
            break;
         case 3:on_create_on_crea
            strWallpaper = System.dir().standard_square_matter("windeskframe1_26.bmp");
            break;
         default:
            strWallpaper = System.dir().standard_square_matter("windeskframe1_23.bmp");
            break;
         }
         FIBITMAP * pfi;

         ::draw2d::memory_graphics pdc(this);

         pfi = System.visual().imaging().LoadImageFile(strWallpaper);

         m_dibBk.From((HDC)pdc->get_os_data(), pfi, true);

         */
         //RedrawWindow();
      }

      //m_dibBk.to(pdc, 0, 0, rectClient.right, rectClient.bottom);
      ::userex::pane_tab_view::_001OnDraw(pdc);
   }



   void pane_view::set_display(int32_t iDisplay)
   {
      m_iDisplay = iDisplay;
   }

   void pane_view::_001OnRButtonUp(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
//      SCAST_PTR(::message::mouse, pmouse, pobj);
      /*if(get_view_id() == ::bergedge::PaneViewWinActionArea)
      {
         ::user::menu menu(get_app());
         menu.LoadXmlMenu("bergedge\\popup_winactionarea.xml");
         ::user::menu menuPopup(get_app(), menu.GetSubMenu(0));
         GetParentFrame()->SetActiveView(this);
         menuPopup.TrackPopupMenu(0, pmouse->m_pt.x, pmouse->m_pt.y, GetParentFrame());
      }*/
   }


   void pane_view::OnFileManagerOpenContextMenu(::filemanager::data * pdata)
   {

      UNREFERENCED_PARAMETER(pdata);

      if(get_view_id() == ::bergedge::PaneViewWinActionArea)
      {

         track_popup_xml_matter_menu("bergedge/popup_winactionarea.xml", 0);

      }

   }


   /*void pane_view::OnFileManagerOpenContextMenuFolder(::filemanager::data * pdata, ::fs::item & item)
   {
   }
*/
   void pane_view::OnFileManagerOpenContextMenuFile(::filemanager::data * pdata, const ::fs::item_array & itema)
   {
      UNREFERENCED_PARAMETER(pdata);
      m_itema = itema;
      set_cur_tab_by_id(::bergedge::PaneViewFileProperties);
   }



   void pane_view::_001OnProperties(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      if(get_view_id() == ::bergedge::PaneViewWinActionArea)
      {

#ifndef METROWIN

         simple_shell_launcher launcher(NULL, NULL, "control.exe", "desk.cpl", NULL, SW_SHOWNORMAL);

         launcher.execute();

#endif

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
            "ca2",
            "savings",
            ::base::resource_display_bandwidth);
   //   control.add_function(user::control::function_static);
      pform->_001AddControl(control);

      control.m_bTransparent = true;
      control.set_type(user::control::type_check_box);
      control.m_id = "save_processing";
      control.set_ddx_dbflags(
            "",
            "ca2",
            "savings",
            ::base::resource_processing);
   //   control.add_function(user::control::function_static);
      pform->_001AddControl(control);

      control.m_bTransparent = true;
      control.set_type(user::control::type_check_box);
      control.m_id = "save_memory";
      control.set_ddx_dbflags(
            "",
            "ca2",
            "savings",
            ::base::resource_memory);
   //   control.add_function(user::control::function_static);
      pform->_001AddControl(control);

      control.m_bTransparent = true;
      control.set_type(user::control::type_check_box);
      control.m_id = "enable_wallpaper";
      control.set_ddx_dbflags(
            "",
            "ca2",
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










