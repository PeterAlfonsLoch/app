#include "StdAfx.h"
#include "MediaLibraryChildFrame.h"
#include "MediaLibraryView.h"

namespace mplite
{

   MediaLibraryChildFrame::MediaLibraryChildFrame(::ca::application * papp) :
      ca(papp),
      window_frame::WorkSetClientInterface(papp),
      userbase::frame_window_interface(papp),
      userbase::frame_window(papp),
      simple_child_frame(papp),
      m_toolbar(papp)
   {
      IGUI_WIN_MSG_LINK(gen::application::APPM_LANGUAGE , this, this, &MediaLibraryChildFrame::_001OnAppLanguage);
   }

   MediaLibraryChildFrame::~MediaLibraryChildFrame()
   {
   }



   int MediaLibraryChildFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
   {
      UNREFERENCED_PARAMETER(lpCreateStruct);
   // trans   if (simple_child_frame::OnCreate(lpCreateStruct) == -1)
         // return -1;
      
   //   SetMenu(NULL);


      //m_menuhook.Initialize(
        // BaseMenuCentral::GetMenuCentral()->MenuV033GetImageList(),
         //BaseMenuCentral::GetMenuCentral()->MenuV033GetImageListDisabled(),
         //NULL,
         //System.font_central().GetMenuFont());

      //m_menuhook.Install(this);



      CreateBars();

   /*   if (!m_dialogbar.create(this, IDR_ALBUM_DIALOGBAR, 
         CBRS_ALIGN_TOP, AFX_IDW_DIALOGBAR))
      {
         TRACE0("Failed to create dialogbar\n");
         return -1;      // fail to create
      }*/
      
      return 0;
   }

   void MediaLibraryChildFrame::OnChangeEditSearch()
   {

      ::document * pdoc = GetActiveDocument();

      if(pdoc != NULL)
      {
         MediaLibraryViewUpdateHint uh;
         uh.set_type(MediaLibraryViewUpdateHint::TypeFilter);
         string str;

      }

   }

   void MediaLibraryChildFrame::OnViewAllMedia() 
   {
      MediaLibraryViewUpdateHint uh;
      uh.set_type(MediaLibraryViewUpdateHint::TypeSetView);
      uh.m_eview = MediaLibraryViewAllMedia;
      GetMainView()->get_document()->update_all_views(NULL, 0, &uh);
   }

   void MediaLibraryChildFrame::OnUpdateViewAllMedia(cmd_ui * pcmdui) 
   {
      pcmdui->Enable(GetViewId() != MediaLibraryViewAllMedia);
   }

   void MediaLibraryChildFrame::OnViewMediaExplorer() 
   {
      MediaLibraryViewUpdateHint uh;
      uh.set_type(MediaLibraryViewUpdateHint::TypeSetView);
      uh.m_eview = MediaLibraryViewMediaExplorer;
      GetMainView()->get_document()->update_all_views(NULL, 0, &uh);
   }

   void MediaLibraryChildFrame::OnUpdateViewMediaExplorer(cmd_ui * pcmdui) 
   {
      pcmdui->Enable(GetViewId() != MediaLibraryViewMediaExplorer);
   }

   MediaLibraryView * MediaLibraryChildFrame::GetMainView()
   {
      ::user::interaction* pwnd = GetDlgItem(AFX_IDW_PANE_FIRST);
      if(base < MediaLibraryView >::bases(pwnd))
      {
         return dynamic_cast < MediaLibraryView *> (pwnd);
      }
      return NULL;
   }

   EMediaLibraryView MediaLibraryChildFrame::GetViewId()
   {
      if(GetMainView() != NULL)
      {
         return (EMediaLibraryView) (int) GetMainView()->get_view_id();
      }
      else
      {
         return MediaLibraryViewNone;
      }
   }
   
   void MediaLibraryChildFrame::_001OnAppLanguage(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      CreateBars();
   }

   bool MediaLibraryChildFrame::CreateBars()
   {

      DestroyBars();
      if (!m_toolbar.CreateEx(this))
      {
         TRACE0("Failed to create toolbar\n");
         return false;      // fail to create
      }

      /* xxx
      if (!m_toolbar.LoadToolBar(IDR_MEDIALIBRARY))
      {
         TRACE0("Failed to create toolbar\n");
         return false;      // fail to create
      }
      */




   /*   if (!m_rebar.create(this) ||
          !m_rebar.AddBar(&m_toolbar) ||
          !m_rebar.AddBar(&m_dialogbar))
      {
         TRACE0("Failed to create rebar\n");
         return -1;      // fail to create
      }*/

      layout();

      return true;
   }

   void MediaLibraryChildFrame::_001InitializeFormPreData(::user::form * pform)
   {
      if(pform->GetDlgCtrlId() == AFX_IDW_DIALOGBAR)
      {
         class user::control::descriptor control;

         control.m_bTransparent = true;
         control.set_type(user::control::type_static);
         control.m_typeinfo = &typeid(simple_static);
         control.m_id = "IDC_STATIC_SEARCH";
         //control.m_uiText = IDS_APP_OPTIONS_GENERAL_SYNCH_DELAY;
         //control.add_function(user::control::function_static2);
         pform->_001AddControl(control);
      }
   }


   bool MediaLibraryChildFrame::DestroyBars()
   {

      m_toolbar.DestroyWindow();
      m_toolbar.RemoveAllTools();

   //   m_dialogbar.DestroyWindow();

      return true;
   }

   void MediaLibraryChildFrame::OnViewVeriwellkaraokelibraryexplorer() 
   {
      MediaLibraryViewUpdateHint uh;
      uh.set_type(MediaLibraryViewUpdateHint::TypeSetView);
      uh.m_eview = MediaLibraryViewKaraokeLibraryExplorer;
      GetMainView()->get_document()->update_all_views(NULL, 0, &uh);
   }

   void MediaLibraryChildFrame::OnUpdateViewVeriwellkaraokelibraryexplorer(cmd_ui * pcmdui) 
   {
      pcmdui->Enable(GetViewId() != MediaLibraryViewKaraokeLibraryExplorer);
   }

} // namespace mplite