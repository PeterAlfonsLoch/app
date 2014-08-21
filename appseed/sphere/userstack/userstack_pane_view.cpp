#include "framework.h"


namespace userstack
{

   pane_view::pane_view(sp(::axis::application) papp) :
      element(papp),
      ::user::tab(papp),
      ::user::tab_view(papp),
      ::userex::pane_tab_view(papp),
      m_dibBk(allocer()),
      place_holder_container(papp)
   {
      m_iNewArea        = 0;
      m_iArea           = -1;
      m_pviewdataOld    = NULL;

      

      m_pviewdata       = NULL;
      m_pviewdataOld    = NULL;

      m_iDisplay        = -1;
      m_ppropform       = NULL;
      m_dataid          = "ca2::bergedge::pane_view";

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

      sp(frame) pframe =  (GetParentFrame());
      pframe->m_ppaneview = this;


      Application.::userstack::application::m_ppaneview = this;



      add_tab("menu", ::userstack::PaneViewContextMenu);

      for(int32_t i = 0; i < Application.directrix()->m_varTopicQuery["app"].stra().get_count(); i++)
      {

         string strId = Application.directrix()->m_varTopicQuery["app"].stra()[i];

         if(i == 0 && strId == "app/sphere/userstack")
            continue;

         add_tab(strId, "app:" + strId);

         set_cur_tab_by_id("app:" + Application.directrix()->m_varTopicQuery["app"].stra()[i]);

      }

      for (int32_t i = 0; i < Application.directrix()->m_varTopicQuery["app/sphere/userstack"]["tab"].stra().get_count(); i++)
      {

         set_cur_tab_by_id("app:" + Application.directrix()->m_varTopicQuery["app/sphere/userstack"]["tab"].stra()[i]);

      }

   }

   void pane_view::on_update(sp(::user::impact) pSender, LPARAM lHint, ::object* pHint)
   {
      ::user::tab_view::on_update(pSender, lHint, pHint);
      if(lHint == 543218)
      {
         set_cur_tab_by_id(::bergedge::PaneViewWinActionArea);
      }
      if(pHint != NULL)
      {
         if(base_class <pane_view_update_hint >::bases(pHint))
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
         if(base_class <pane_view_update_hint >::bases(pHint))
         {
            pane_view_update_hint * puh = (pane_view_update_hint * ) pHint;
            if(puh->is_type_of(pane_view_update_hint::TypeOnShowKaraoke))
            {
               ( (GetTopLevelFrame()))->SetActiveView(this);
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
            //platform().m_pappCurrent = pappTab;
         }
/*            sp(::simple_frame_window) pframeApp = dynamic_cast < sp(::simple_frame_window) > (m_pviewdata->m_pwnd);
         if(pframeApp != NULL)
         {
            pframeApp->WfiFullScreen();
         }*/
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
         if(Session.savings().save().is_signalized(::ca2::save_display_bandwidth))
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
      /*if(m_pviewdataOld != NULL)
      {
         if(m_pviewdataOld->m_pwnd != NULL)
         {
            m_pviewdataOld->m_pwnd->ShowWindow(SW_HIDE);
         }
      }*/
   }

   bool pane_view::pre_create_window(::user::create_struct& cs)
   {
      cs.dwExStyle &= ~WS_EX_CLIENTEDGE;

      return ::user::impact::pre_create_window(cs);
   }


   void pane_view::on_create_view(::user::view_creator_data * pcreatordata)
   {

      class sp(application) papp =  (get_app());

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

            if(papp->directrix()->m_varTopicQuery.has_property(strId))
            {

               createcontext->m_spCommandLine->m_varQuery.propset().merge(papp->directrix()->m_varTopicQuery[(const char *) strId].propset());

               if(papp->directrix()->m_varTopicQuery[(const char *) strId].has_property("file"))
               {

                  createcontext->m_spCommandLine->m_varFile = papp->directrix()->m_varTopicQuery[(const char *) strId]["file"];

               }

            }

            str = ::str::from((int_ptr) createcontext->m_spApplicationBias->m_puiParent);

            createcontext->m_spCommandLine->m_eventReady.ResetEvent();

            platform().on_request(createcontext);

            createcontext->m_spCommandLine->m_eventReady.wait();

         }

         sp(::axis::application) pappCurrent = platform().m_pappCurrent;

         Application.m_mapApplication[strId] = pappCurrent;

         string strTypeId = typeid(*pappCurrent).name();

         string strIcon = sess(pappCurrent).dir().matter("mainframe/icon48.png");
         pane * ppane = (pane *) get_pane_by_id(pcreatordata->m_id);

         pappCurrent = platform().m_pappCurrent;

         if(sess(pappCurrent).file().exists(strIcon))
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
            Application.file().put_contents(System.dir().path(strDir, strApp + ".ca2"), "ca2prompt\r\n"+ strApp);
         }
      }

      //Application.file().put_contents(System.dir().path(strDir, "veriwell Musical Player.ca2"), "ca2prompt\r\nmplite");
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
      throw todo(get_app());
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
         //_001RedrawWindow();
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
#else

         throw todo(get_app());

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
