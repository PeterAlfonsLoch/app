#include "framework.h"


namespace userstack
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
      m_iNewArea        = 0;
      m_iArea           = -1;
      m_pviewdataOld    = NULL;

      m_etranslucency   = TranslucencyTotal;

      m_pviewdata       = NULL;
      m_pviewdataOld    = NULL;

      m_iDisplay        = -1;
      m_ppropform       = NULL;
      m_dataid          = "ca2_fontopus_votagus::bergedge::pane_view";

      get_data()->m_matchanyRestore.add(new ::ex1::match::prefix("app:"));

   }

   pane_view::~pane_view()
   {
   }

#ifdef DEBUG
   void pane_view::assert_valid() const
   {
      ::userbase::view::assert_valid();
   }

   void pane_view::dump(dump_context & dumpcontext) const
   {
      ::userbase::view::dump(dumpcontext);
   }
#endif //DEBUG

   void pane_view::_001OnCreate(gen::signal_object * pobj)
   {

      if(pobj->previous())
         return;

      frame * pframe = dynamic_cast < frame * > (GetParentFrame());
      pframe->m_ppaneview = this;


      

      add_tab("menu", ::userstack::PaneViewContextMenu);

      for(int i = 0; i < Application.directrix().m_varTopicQuery["app"].get_count(); i++)
      {

         string strId = Application.directrix().m_varTopicQuery["app"].stra()[i];

         if(i == 0 && strId == "app/ca2/userstack")
            continue;

         add_tab(strId, "app:" + strId);

         set_cur_tab_by_id("app:" + Application.directrix().m_varTopicQuery["app"].stra()[i]);

      }


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
//      frame * pframe = dynamic_cast < frame *> (GetParentFrame());
      if(get_view_id().is_text())
      {
         string strId = get_view_id();
         if(gen::str::begins_eat(strId, "app:"))
         {
            ::ca::application * pappTab;
            if(Session.m_mapApplication.Lookup("application:" + strId, pappTab))
            {
               Session.m_pappCurrent = pappTab;
               //Bergedge.m_pappCurrent = pappTab;
            }
/*            ::simple_frame_window * pframeApp = dynamic_cast < ::simple_frame_window * > (m_pviewdata->m_pwnd);
            if(pframeApp != NULL)
            {
               pframeApp->WfiFullScreen(true, false);
            }*/
         }
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
         if(m_iDisplay <= 0)
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
      /*if(m_pviewdataOld != NULL)
      {
         if(m_pviewdataOld->m_pwnd != NULL)
         {
            m_pviewdataOld->m_pwnd->ShowWindow(SW_HIDE);
         }
      }*/
   }

   bool pane_view::pre_create_window(CREATESTRUCT& cs)
   {
      cs.dwExStyle &= ~WS_EX_CLIENTEDGE;

      return ::userbase::view::pre_create_window(cs);
   }


   void pane_view::on_create_view(::user::view_creator_data * pcreatordata)
   {
      
      class application * papp = dynamic_cast < class application * > (get_app());

      if(pcreatordata->m_id.is_text())
      {
         string strId = pcreatordata->m_id;

         if(gen::str::begins_eat(strId, "app:"))
         {
            ::ca::application * pappTab;
            if(!Session.m_mapApplication.Lookup("application:" + strId, pappTab))
            {
               
               ::ca::application_bias * pbiasCreate = new ::ca::application_bias;
               pbiasCreate->m_puiParent = pcreatordata->m_pholder;

               ::ca::create_context_sp createcontext(get_app());
               createcontext->m_spApplicationBias = pbiasCreate;
               createcontext->m_spCommandLine->_001ParseCommandFork(strId);
              

               string str;

               if(papp->directrix().m_varTopicQuery.has_property(strId))
               {

                  createcontext->m_spCommandLine->m_varQuery.propset().merge(papp->directrix().m_varTopicQuery[(const char *) strId].propset());

                  if(papp->directrix().m_varTopicQuery[(const char *) strId].has_property("file"))
                  {
                     
                     createcontext->m_spCommandLine->m_varFile = papp->directrix().m_varTopicQuery[(const char *) strId]["file"];

                  }

               }
   
               str = gen::str::from((int_ptr) createcontext->m_spApplicationBias->m_puiParent);

               createcontext->m_spCommandLine->m_eventReady.ResetEvent();

               Session.on_request(createcontext);

               createcontext->m_spCommandLine->m_eventReady.wait();

            }

            ::ca::application * pappCurrent = Session.m_pappCurrent;

            string strTypeId = typeid(*pappCurrent).name();

     		   string strIcon = planeApp(pappCurrent).dir().matter("mainframe/icon48.png");
            pane * ppane = (pane *) get_pane_by_id(pcreatordata->m_id);
            
            pappCurrent = Session.m_pappCurrent;

	   	   if(planeApp(pappCurrent).file().exists(strIcon))
            {
               ppane->m_dib.create(papp);
               ppane->m_dib.load_from_file(strIcon);
            }
            else
            {
               ppane->m_istrTitleEx = pcreatordata->m_id;
            }
            layout();
         }
      }
      else if(pcreatordata->m_id.is_number())
      {

      }
      ::userex::pane_tab_view::on_create_view(pcreatordata);
   }



   void pane_view::_001OnMenuMessage(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      set_cur_tab_by_id(m_pviewdataOld->m_id);
   }

   void pane_view::install_message_handling(::gen::message::dispatch * pinterface)
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
         int i = (int) ::ShellExecuteW(
            GetTopLevelParent()->get_handle(),
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
      Application.dir().rls(System.dir().commonprograms(), &straPath, NULL, &straRelative);
      for(int i = 0; i < straPath.get_size(); i++)
      {
         string str = System.dir().path(psz, straRelative[i]);
         Application.dir().mk(System.dir().name(str));
         Application.file().copy(str, straPath[i], true);
      }
      straRelative.remove_all();
      straPath.remove_all();
      Application.dir().rls(System.dir().userprograms(NULL), &straPath, NULL, &straRelative);
      for(int i = 0; i < straPath.get_size(); i++)
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
         if(gen::str::begins_eat(strApp, "application:"))
         {
            Application.file().put_contents(System.dir().path(strDir, strApp + ".ca2"), "ca2prompt\r\n"+ strApp);
         }
      }

      //Application.file().put_contents(System.dir().path(strDir, "veriwell Musical Player.ca2"), "ca2prompt\r\nmplite");
/*      stringa straPath;
      stringa straRelative;
      straPath.remove_all();
      System.dir().rls(Application.dir().userquicklaunch(), &straPath, NULL, &straRelative);
      for(int i = 0; i < straPath.get_size(); i++)
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
            for(int i = 0; i < straPath.get_size(); i++)
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
            for(int i = 0; i < straPath.get_size(); i++)
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

         ::ca::client_graphics pdc(this);

         pfi = System.imaging().LoadImageFile(strWallpaper);

         m_dibBk.From((HDC)pdc->get_os_data(), pfi, true);

         */
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
//      SCAST_PTR(::gen::message::mouse, pmouse, pobj);
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
   void pane_view::OnFileManagerOpenContextMenuFile(::filemanager::data * pdata, const ::fs::item_array & itema)
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
