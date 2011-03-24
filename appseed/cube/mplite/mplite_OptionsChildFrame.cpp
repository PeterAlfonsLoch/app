#include "StdAfx.h"
#include "OptionsChildFrame.h"
#include "MediaLibraryView.h"

#include "OptionsView.h"


namespace mplite
{

   OptionsChildFrame::OptionsChildFrame(::ca::application * papp) :
      ca(papp),
      window_frame::WorkSetClientInterface(papp),
      userbase::frame_window_interface(papp),
      userbase::frame_window(papp),
      simple_child_frame(papp),
      m_toolbar(papp),
      m_toolbar1(papp)
   {
   }

   OptionsChildFrame::~OptionsChildFrame()
   {
   }



   void OptionsChildFrame::_001OnCreate(gen::signal_object * pobj) 
   {
      SCAST_PTR(::user::win::message::create, pcreate, pobj)
      pobj->previous();
      
   //   SetMenu(NULL);

      /*if (!m_toolbar.CreateEx(this))
      {
         TRACE0("Failed to create toolbar\n");
         return -1;      // fail to create
      }*/

      if (!m_toolbar1.CreateEx(this))
      {
         pcreate->error("Failed to create toolbar\n");
         return;
      }

      /*if (!m_toolbar.LoadToolBar(IDR_MEDIALIBRARY))
      {
         TRACE0("Failed to create toolbar\n");
         return -1;      // fail to create
      }

      if (!m_dialogbar.create(this, IDR_ALBUM_DIALOGBAR, 
         CBRS_ALIGN_TOP, AFX_IDW_DIALOGBAR))
      {
         TRACE0("Failed to create dialogbar\n");
         return -1;      // fail to create
      }*/

   /*   if (!m_rebar.create(this) ||
          !m_rebar.AddBar(&m_toolbar) ||
          !m_rebar.AddBar(&m_dialogbar))
      {
         TRACE0("Failed to create rebar\n");
         return -1;      // fail to create
      }*/

      //m_menuhook.Initialize(
        // BaseMenuCentral::GetMenuCentral()->MenuV033GetImageList(),
         //BaseMenuCentral::GetMenuCentral()->MenuV033GetImageListDisabled(),
         //NULL,
         //System.font_central().GetMenuFont());

      //m_menuhook.Install(this);

   }

   void OptionsChildFrame::OnChangeEditSearch()
   {

      ::document * pdoc = GetActiveDocument();

      if(pdoc != NULL)
      {
         MediaLibraryViewUpdateHint uh;
         uh.set_type(MediaLibraryViewUpdateHint::TypeFilter);
         string str;
   /*      ::ca::window * pwnd = m_dialogbar.GetDlgItem(IDC_EDIT_SEARCH);
         pwnd->GetWindowText(str);
         gen::international::AcpToUtf8(uh.m_strFilter, str);
         pdoc->update_all_views(
            NULL,
            0,
            &uh);
   */
      }

   }

   void OptionsChildFrame::OnViewAllMedia() 
   {
      MediaLibraryViewUpdateHint uh;
      uh.set_type(MediaLibraryViewUpdateHint::TypeSetView);
      uh.m_eview = MediaLibraryViewAllMedia;
      GetMainView()->get_document()->update_all_views(NULL, 0, &uh);
   }

   void OptionsChildFrame::OnUpdateViewAllMedia(cmd_ui * pcmdui) 
   {
      pcmdui->Enable(GetViewId() != MediaLibraryViewAllMedia);
   }

   void OptionsChildFrame::OnViewMediaExplorer() 
   {
      MediaLibraryViewUpdateHint uh;
      uh.set_type(MediaLibraryViewUpdateHint::TypeSetView);
      uh.m_eview = MediaLibraryViewMediaExplorer;
      GetMainView()->get_document()->update_all_views(NULL, 0, &uh);
   }

   void OptionsChildFrame::OnUpdateViewMediaExplorer(cmd_ui * pcmdui) 
   {
      pcmdui->Enable(GetViewId() != MediaLibraryViewMediaExplorer);
   }

   MediaLibraryView * OptionsChildFrame::GetMainView()
   {
      ::user::interaction* pwnd = GetDlgItem(AFX_IDW_PANE_FIRST);
      if(base < MediaLibraryView >::bases(pwnd))
      {
         return dynamic_cast < MediaLibraryView * > (pwnd);
      }
      return NULL;
   }

   EMediaLibraryView OptionsChildFrame::GetViewId()
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

   void OptionsChildFrame::DestroyToolBar(int iToolBar)
   {
      if(iToolBar == 0)
      {
         m_toolbar1.RemoveAllTools();
      }
   }

   void OptionsChildFrame::LoadToolBar(int iToolBar, const char * pszToolBar)
   {
      if(iToolBar == 0)
      {
         m_toolbar1.LoadXmlToolBar(Application.file().as_string(System.dir().matter(pszToolBar)));
         layout();
      }
   }


   void OptionsChildFrame::_001InstallMessageHandling(::user::win::message::dispatch * pinterface)
   {
      simple_child_frame::_001InstallMessageHandling(pinterface);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &OptionsChildFrame::_001OnCreate);
   }

} // namespace mplite