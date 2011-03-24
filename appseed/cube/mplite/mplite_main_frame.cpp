#include "StdAfx.h"


#include "MediaLibraryViewUpdateHint.h"
#include "mediamanager/AlbumBuild.h"


#include <gl/gl.h>



static UINT indicators[] =
{
   ID_SEPARATOR,           // status line indicator
   ID_INDICATOR_CAPS,
   ID_INDICATOR_NUM,
   ID_INDICATOR_SCRL,
};

namespace mplite
{

   main_frame::main_frame(::ca::application * papp) :
      ca(papp),
      window_frame::WorkSetClientInterface(papp),
      userbase::frame_window_interface(papp),
      userbase::frame_window(papp),
      simple_frame_window(papp),
      m_imagelist(papp)
   {
      
      m_ppaneview = NULL;

      m_iFrameData = 10;
      m_dataid = "MusicalPlayerMainFrame";
      m_iAnimateStep = 0;

      WfiEnableFullScreen();

      m_dataidWindow = "WindowData";
   //   m_iWindowDataId = vmplite::WindowDataMainFrame;


      connect_update_cmd_ui("view_full_screen", &main_frame::_001OnUpdateViewFullScreen);
      connect_command("view_full_screen", &main_frame::_001OnViewFullScreen);

      m_bblur_Background = true;
      m_bLayered = true;
      m_etranslucency = TranslucencyPresent;

      m_ptemplateCommand = new ::userbase::single_document_template(
         get_app(),
         "system/form",
         &typeid(::mplite::command_document),
         &typeid(::mplite::command_frame),
         &typeid(::mplite::command_view));

   }

   main_frame::~main_frame()
   {
   }

   void main_frame::_001OnCreate(gen::signal_object * pobj)
   {

      pobj->previous();
      if(pobj->m_bRet)
         return;

      //SetTimer(8913, 5000, 0);
      //SetTimer(4033, 100, 0);
      //ModifyStyleEx(WS_EX_OVERLAPPEDWINDOW, 0);

      //m_menuhook.Initialize(
        // BaseMenuCentral::GetMenuCentral()->MenuV033GetImageList(),
         //BaseMenuCentral::GetMenuCentral()->MenuV033GetImageListDisabled(),
         //NULL,
         //System.font_central().GetMenuFont());

      //m_menuhook.Install(this);



      //m_hMenuDefault = NULL;

   /*    if (!m_menubar.CreateEx(this))
      {
         TRACE0("Failed to create toolbar\n");
         return -1;      // fail to create
      }

      if(!m_menubar.Initialize(
         BaseMenuCentral::GetMenuCentral()->MenuV033GetImageList(),
         BaseMenuCentral::GetMenuCentral()->MenuV033GetImageListDisabled(),
         NULL,
         System.font_central().GetMenuFont()) ||
         VMS_FAILED(m_menubar.LoadMenuBar(IDR_MAINFRAME)))
      {
         TRACE0("Failed to create toolbar\n");
         return -1;      // fail to create
      }*/

      //m_imagelist.create(16, 16, 0, 10, 10);
      //m_imagelist.add_matter_icon("system/language_icon.ico");

      /*m_menubar._001SetImageList(&m_imagelist);
      m_menubar.SetItemImage(m_menubar._001GetItemCount() - 1, 0);

      if (!m_toolbar.CreateEx(this, TBSTYLE_FLAT,
         WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP | CBRS_GRIPPER | CBRS_SIZE_DYNAMIC
         | CBRS_DRAGMOVE,
         rect(0, 0, 0, 0),
         AFX_IDW_TOOLBAR) ||
         !m_toolbar.LoadToolBar(IDR_MAINFRAME))
      {
         TRACE0("Failed to create toolbar\n");
         return -1;      // fail to create
      }

      if (!m_toolbarView.CreateEx(this, TBSTYLE_FLAT,
         WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP | CBRS_GRIPPER | CBRS_SIZE_DYNAMIC
         | CBRS_DRAGMOVE,
         rect(0, 0, 0, 0),
         AFX_IDW_TOOLBAR + 1) ||
         !m_toolbarView.LoadToolBar(IDR_VIEW))
      {
         TRACE0("Failed to create toolbar\n");
         return -1;      // fail to create
      }
      
      
      if (!m_dialogbar.create(this, IDR_MAINFRAME, 
         WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP | CBRS_GRIPPER | CBRS_SIZE_DYNAMIC
         | CBRS_DRAGMOVE, AFX_IDW_DIALOGBAR))
      {
         TRACE0("Failed to create dialogbar\n");
         return -1;      // fail to create
      }*/

   /*   if (!m_wndReBar.create(this) ||
         !m_wndReBar.AddBar(&m_menubar) ||
         !m_wndReBar.AddBar(&m_wndToolBar) ||
         !m_wndReBar.AddBar(&m_toolbarView) ||
         !m_wndReBar.AddBar(&m_wndDlgBar))
      {
         TRACE0("Failed to create rebar\n");
         return -1;      // fail to create
      }*/

   /*   if (!m_statusbar.create(this) ||
         !m_statusbar.SetIndicators(indicators,
           sizeof(indicators)/sizeof(UINT)))
      {
         TRACE0("Failed to create status bar\n");
         return -1;      // fail to create
      }*/

      // TODO: remove this if you don't want tool tips
      /*m_toolbar.SetBarStyle(m_toolbar.GetBarStyle() |
         CBRS_TOOLTIPS | CBRS_FLYBY);
      m_dialogbar.SetBarStyle(m_dialogbar.GetBarStyle() |
         CBRS_TOOLTIPS | CBRS_FLYBY);

      EnableDocking(CBRS_ALIGN_ANY);

      m_toolbar.EnableDocking(CBRS_ALIGN_ANY);
      DockControlBar(&m_toolbar);

      m_toolbarView.EnableDocking(CBRS_ALIGN_ANY);
      DockControlBar(&m_toolbarView);

      m_dialogbar.EnableDocking(CBRS_ALIGN_TOP);
      m_dialogbar.EnableDocking(CBRS_ALIGN_BOTTOM);
      DockControlBar(&m_toolbar);*/

      //WindowDataLoadWindowRect();
      //WindowDataEnableSaveWindowRect(true);


      //return 0;

      if(Application.m_bClientOnly)
      {
         WindowDataEnableSaveWindowRect(false);
         WfiFullScreen(true, false);
         WindowDataEnableSaveWindowRect(true);
      }

   }

   BOOL main_frame::PreCreateWindow(CREATESTRUCT& cs)
   {
      if( !simple_frame_window::PreCreateWindow(cs) )
         return FALSE;
      cs.dwExStyle &= ~WS_EX_WINDOWEDGE;
      ::DestroyMenu(cs.hMenu);
      cs.hMenu = NULL;
      return TRUE;
   }

   /////////////////////////////////////////////////////////////////////////////
   // main_frame diagnostics

   #ifdef _DEBUG
   void main_frame::assert_valid() const
   {
      simple_frame_window::assert_valid();
   }

   void main_frame::dump(dump_context & dumpcontext) const
   {
      simple_frame_window::dump(dumpcontext);
   }


   #endif //_DEBUG

   bool main_frame::_001CanEnterScreenSaver()
   {
      if(GetPaneView() != NULL && GetPaneView()->get(PaneViewKaraoke) != NULL)
      {
         ::mplite::view * pview = dynamic_cast < mplite::view * > (GetPaneView()->get(PaneViewKaraoke)->m_pwnd);
         if(pview->_ExecuteIsEntertaining())
         {
            //MessageBox(NULL, "would start screen saver instead", "would start screen saver instead", MB_OK);
            return false;
         }
      }
      return true;
   }


   void main_frame::OnViewKaraoke() 
   {
      ShowView(PaneViewKaraoke);
   }

   void main_frame::OnUpdateViewKaraoke(cmd_ui * pcmdui) 
   {
      pcmdui->Enable(GetViewId() != PaneViewKaraoke);
      pcmdui->_001SetCheck(GetViewId() == PaneViewKaraoke);
   }

   void main_frame::OnFileOpenEx() 
   {
      ShowView(PaneViewFileManager);
   }

   void main_frame::OnUpdateFileOpenEx(cmd_ui * pcmdui) 
   {
      pcmdui->Enable(GetViewId() != PaneViewFileManager);
      pcmdui->_001SetCheck(GetViewId() == PaneViewFileManager);
   }

   void main_frame::OnViewPlaylist() 
   {
      ShowView(PaneViewPlaylist);
   }

   void main_frame::OnUpdateViewPlaylist(cmd_ui * pcmdui) 
   {
      pcmdui->Enable(GetViewId() != PaneViewPlaylist);
      pcmdui->_001SetCheck(GetViewId() == PaneViewPlaylist);
   }

   void main_frame::OnViewAlbum() 
   {
      ShowView(PaneViewMediaLibrary);
   }

   void main_frame::OnUpdateViewAlbum(cmd_ui * pcmdui) 
   {
      pcmdui->Enable(GetViewId() != PaneViewMediaLibrary);
      pcmdui->_001SetCheck(GetViewId() == PaneViewMediaLibrary);
   }

   void main_frame::ShowView(EPaneView eview)
   {
      pane_view * pview = GetPaneView();
      if(pview != NULL)
      {
         pview->set_cur_tab_by_id(eview);

      }
   }

   EPaneView main_frame::GetViewId()
   {
      pane_view * pview = GetPaneView();
      if(pview != NULL)
      {
         return (EPaneView) (int) pview->get_view_id();
      }
      return PaneViewNone;
   }

   pane_view * main_frame::GetPaneView()
   {
      return m_ppaneview;
   }



   void main_frame::OnTimer(UINT nIDEvent) 
   {
      static float theta;
      if(nIDEvent == 3)
      {
         //AnimateStatusBar();
      }
      else if(nIDEvent == 8913)
      {
         if(!mediamanager::get(get_app())->GetAlbumBuild().IsBuilding())
         {
            stringa stra;
            data_get("SongDirectorySet", ::ca::system::idEmpty, stra);

            mediamanager::get(get_app())->BuildAlbum(stra);
         }
         KillTimer(8913);
      }
      else if(nIDEvent == 4033)
      {
   // OpenGL animation code goes here
            
            //glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
            //glClear( GL_COLOR_BUFFER_BIT );
            
            /*glPushMatrix();
            glRotatef( theta, 0.0f, 1.0f, 1.0f );
            glBegin( GL_TRIANGLES );
            glColor3f( 1.0f, 0.0f, 0.0f ); glVertex2f( 0.0f, 1.0f );
            glColor3f( 0.0f, 1.0f, 0.0f ); glVertex2f( 0.87f, -0.5f );
            glColor3f( 0.0f, 0.0f, 1.0f ); glVertex2f( -0.87f, -0.5f );
            glEnd();
            glPopMatrix();*/
            
            //SwapBuffers( m_hdcOpenGL );
            
            theta += 2.0f;
         
      }
   // trans   simple_frame_window::OnTimer(nIDEvent);
   }

   void main_frame::SetAnimatedStatusBarText(const char * lpcsz)
   {
      m_strAnimatedStatusBarText = lpcsz;
      if(m_strAnimatedStatusBarText.is_empty())
      {
         KillTimer(3);
      }
      else
      {
         SetTimer(3, 500, NULL);
      }
   }

   void main_frame::AnimateStatusBar()
   {
      if(m_strAnimatedStatusBarText.is_empty())
         return;

      int iLen = m_strAnimatedStatusBarText.get_length();
      m_iAnimateStep++;
      if(m_iAnimateStep > iLen)
         m_iAnimateStep = 0;


   //   m_statusbar.SetPaneText(0, m_strAnimatedStatusBarText.Mid(m_iAnimateStep));
   }

   void main_frame::OnViewMediaExplorer() 
   {
      ShowView(PaneViewMediaLibrary);   
      MediaLibraryViewUpdateHint uh;
      uh.set_type(MediaLibraryViewUpdateHint::TypeSetView);
      uh.m_eview = MediaLibraryViewMediaExplorer;
      GetPaneView()->get_document()->update_all_views(NULL, 0, &uh);
   }

   void main_frame::OnViewAllMedia() 
   {
      ShowView(PaneViewMediaLibrary);
      MediaLibraryViewUpdateHint uh;
      uh.set_type(MediaLibraryViewUpdateHint::TypeSetView);
      uh.m_eview = MediaLibraryViewAllMedia;
      GetPaneView()->get_document()->update_all_views(NULL, 0, &uh);

   }

   void main_frame::ShowControlBars(bool bShow)
   {
      UINT nShow;
      if(bShow)
      {
         nShow = SW_SHOW;
      }
      else
      {
         nShow = SW_HIDE;
      }

   /*   m_toolbar.ShowWindow(nShow);
      m_toolbarView.ShowWindow(nShow);
   //   m_statusbar.ShowWindow(nShow);
      m_menubar.ShowWindow(nShow);
      m_dialogbar.ShowWindow(nShow);*/

   }

   
   LRESULT main_frame::OnVmSimple(WPARAM wparam, LPARAM lparam)
   {
      UNREFERENCED_PARAMETER(lparam);
      if(wparam == 123)
      {
         return VM_SIMPLE;
      }
      return 0;
   }

   /*BOOL main_frame::OnCopyData(::ca::window * pwnd, COPYDATASTRUCT* pcds)
   {
      if(pcds->dwData == 123)
      {
         string str((wchar_t *) pcds->lpData);
         application * papp = dynamic_cast < application * > (&System);
         papp->ProcessCommandLine(str);
         return TRUE;
      }

      return FALSE;
   }*/

   void main_frame::OnViewOptions() 
   {
      ShowView(PaneViewOptions);
      
   }

   void main_frame::OnUpdateViewOptions(cmd_ui * pcmdui) 
   {
      pcmdui->Enable(GetViewId() != PaneViewOptions);
      pcmdui->_001SetCheck(GetViewId() == PaneViewOptions);
   }

   void main_frame::OnViewNextPane() 
   {
      GetPaneView()->rotate();
      
   }



   void main_frame::_001InstallMessageHandling(::user::win::message::dispatch * pinterface)
   {
      simple_frame_window::_001InstallMessageHandling(pinterface);
      IGUI_WIN_MSG_LINK(WM_KEYDOWN, pinterface, this, &main_frame::_001OnKeyDown);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &main_frame::_001OnCreate);
   }

   void main_frame::pre_translate_message(gen::signal_object * pobj)
   {
      user::win::message::key * pkey = dynamic_cast < user::win::message::key * > (pobj);
      if(pkey != NULL && pkey->m_uiMessage == WM_KEYDOWN)
      {
         _001OnKeyDown(pobj);
      }
      simple_frame_window::pre_translate_message(pobj);
   }

   void main_frame::_001OnKeyDown(gen::signal_object * pobj)
   {
      
      SCAST_PTR(::user::win::message::key, pkey, pobj)

      if(::GetKeyState(VK_CONTROL) & 0x80000000)
      {
         if(pkey->m_nChar == VK_CONTROL)
         {
            pkey->m_bRet      = true;
            return;
         }
         else if(pkey->m_nChar == 'V')
         {
            pkey->m_bRet      = true;
            string strFilter1 = System.copydesk().get_plain_text();
            strFilter1.trim();
            if(gen::str::begins_ci(strFilter1, "http:")
            || gen::str::begins_ci(strFilter1, "https:"))
            {
               PlaylistCentral & playlistcentral = PlaylistCentralContainer::AppGetPlaylistCentral(get_app());
               PlaylistDoc * pdoc = playlistcentral.GetCurrentPlaylist(true);
               {
                  string strScript = System.url().url_decode(System.url().get_script(strFilter1));
                  strFilter1 = System.url().set_script(strFilter1, strScript);
               }
               pdoc->AddSong(strFilter1, PlaylistDoc::AddSongAndPlayIfNotPlaying, true, true);
               return;
            }
         }
      }



      if(m_ptemplateCommand->get_document(0) == NULL)
      {
         m_ptemplateCommand->open_document_file(System.dir().matter("mplite/command.xhtml"), true, System.m_puiInitialPlaceHolderContainer);
      }
      
      ::mplite::command_document * pdoc = dynamic_cast < ::mplite::command_document * > (m_ptemplateCommand->get_document(0));

      if(pdoc != NULL)
      {
         ::mplite::command_view * pview = pdoc->get_typed_view < ::mplite::command_view > ();
         if(pview != NULL)
         {
            pview->m_pmainframe = this;
            ::mplite::command_frame * pframe = pview->GetTypedParent < ::mplite::command_frame > ();
            if(pframe != NULL)
            {
               class rect rectWindow;
               GetWindowRect(rectWindow);
               if(System.m_puiInitialPlaceHolderContainer != NULL)
               {
                  System.m_puiInitialPlaceHolderContainer->ScreenToClient(rectWindow);
               }
               pframe->SetWindowPos(ZORDER_TOPMOST, 33, rectWindow.bottom - 100, 800, 33, SWP_SHOWWINDOW);
               pview->on_key(dynamic_cast < ::user::win::message::key * > (pobj));
            }
         }
      }

   }

} // namespace mplite