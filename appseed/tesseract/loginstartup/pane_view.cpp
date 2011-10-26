#include "StdAfx.h"
#include "pane_view.h"
#include "loginstartup_application.h"
#include "loginstartup/loginstartup_frame.h"
#include "html/html_view.h"
#include "html/html_document.h"


namespace loginstartup
{


pane_view::pane_view(::ca::application * papp) :
   ::ca::ca(papp),
   ex1::tab(papp),
   BaseVirtualTab(papp),
   base_tab_view(papp),
   guiex::pane_tab_view(papp)
{
   m_pcreateview = this;

   // window_interface
   m_etranslucency      = TranslucencyPresent;

   m_pviewdata              = NULL;
   m_pviewdataOld              = NULL;

/*   BaseSingleDocumentTemplate* pdoctemplate;
	pdoctemplate = new BaseSingleDocumentTemplate(
		IDR_ALBUM,
		&typeid(MediaLibraryDoc),
		&typeid(MediaLibraryChildFrame),
		&typeid(MediaLibraryView));
   m_pdoctemplateAlbum = pdoctemplate;

	pdoctemplate = new BaseSingleDocumentTemplate(
		IDR_ALBUM,
		&typeid(OptionsDoc),
		&typeid(OptionsChildFrame),
		&typeid(OptionsView));

   
   m_pdoctemplateOptions = pdoctemplate;

	pdoctemplate = new BaseSingleDocumentTemplate(
		IDR_ALBUM,
		&typeid(GoodMixerDoc),
		&typeid(BaseChildFrame),
		&typeid(MixerMainView));

   m_pdoctemplateAudioControl = pdoctemplate;*/
   

}

pane_view::~pane_view()
{
}




#ifdef _DEBUG
void pane_view::AssertValid() const
{
	BaseView::AssertValid();
}

void pane_view::Dump(CDumpContext & dumpcontext) const
{
	BaseView::Dump(dumpcontext);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// pane_view message handlers

void pane_view::_001OnCreate(gen::signal_object * pobj) 
{
   SCAST_PTR(igui::win::message::create, pcreate, pobj)
   if(pobj->previous())
      return;

   add_tab("3-action-launch", loginstartup::PaneViewThreeActionLaunch);
   add_tab("Menu", loginstartup::PaneViewContextMenu);
   add_tab("win Action Area", loginstartup::PaneViewWinActionArea);
   add_tab("Options", loginstartup::PaneViewConfiguration);
   add_tab("FileManager", loginstartup::PaneViewFileManager);

   set_cur_tab_by_id(loginstartup::PaneViewWinActionArea);
}

void pane_view::on_update(BaseView* pSender, LPARAM lHint, base_object* pHint) 
{
   base_tab_view::on_update(pSender, lHint, pHint);
   if(lHint == 543218)
   {
      set_cur_tab_by_id(loginstartup::PaneViewWinActionArea);
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
            (dynamic_cast < BaseFrameWnd * > (GetTopLevelFrame()))->SetActiveView(this);
         }
         else if(puh->is_type_of(pane_view_update_hint::TypeOnShowView))
         {
            
            int iTab;
//            if(puh->m_eview == PaneViewContextMenu)
  //          {
    //           m_tab._001AddSel(0);
      //      }
//            else
            {
            }
            
         }
      }
   }


}


void pane_view::on_show_view() 
{
   guiex::pane_tab_view::on_show_view();
   loginstartup_frame * pframe = dynamic_cast < loginstartup_frame *> (
      dynamic_cast < ::ca::window * > (GetParentFrame()));
   if(get_view_id() == loginstartup::PaneViewFileManager)
   {
      pframe->m_bAutoHideOnOutClick = false;
   }
   else if(get_view_id() == loginstartup::PaneViewContextMenu)
   {
      FileManagerDoc * pdoc = dynamic_cast < FileManagerDoc * > (get_view_document());
      pdoc->FileManagerBrowse(Application.dir().userappdata("loginstartup\\menu"));
   }
   else
   {
      pframe->m_bAutoHideOnOutClick = true;
   }
}


void pane_view::_001OnSize(gen::signal_object * pobj) 
{
	pobj->previous();
	
   Layout();	

}


BOOL pane_view::PreCreateWindow(CREATESTRUCT& cs) 
{
   cs.dwExStyle &= ~WS_EX_CLIENTEDGE;	

	return BaseView::PreCreateWindow(cs);
}


void pane_view::on_create_view(view_data * pviewdata)
{
   loginstartup_application * papp = dynamic_cast < loginstartup_application * > ((dynamic_cast < BaseFrameWnd * > (GetParentFrame()))->get_app());
   switch(pviewdata->m_id)
   {
   case PaneViewContextMenu:
      {
         FileManagerDoc * pdoc = papp->GetStdFileManagerTemplate()->OpenChildList(papp, false, true);
         if(pdoc != NULL)
         {
            pdoc->GetDDX().m_iIconSize = 16;
            pdoc->GetDDX().m_bListText = true;
            pdoc->GetDDX().m_bListSelection = false;
            pdoc->GetDDX().m_ptemplate->m_strFilePopup = "filemanager\\file_popup.xml";
            pdoc->GetDDX().m_strDISection = "loginstartup_menu";
            pdoc->GetDDX().m_pcallback = this;
            pdoc->Initialize(true);
            pdoc->UpdateAllViews(NULL, 1234);
            pdoc->UpdateAllViews(NULL, 123458);
            POSITION pos = pdoc->GetFirstViewPosition();
            view * pview = pdoc->GetNextView(pos);
            pdoc->FileManagerBrowse(Application.dir().userappdata("loginstartup\\menu"));
            if(pview != NULL)
            {
               BaseFrameWnd * pframe = dynamic_cast < BaseFrameWnd * > (pview->GetParentFrame());
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
   case PaneViewWinActionArea:
      {
         BaseView * pview = dynamic_cast < BaseView * > (create_view(typeid(loginstartup_view), get_document(), this, 101));
         if(pview != NULL)
         {
            pviewdata->m_pdoc = get_document();
            pviewdata->m_pwnd = pview;
         }
      }
      break;
   case PaneViewFileManager:
      {
         FileManagerDoc * pdoc = papp->GetStdFileManagerTemplate()->OpenChild(papp, false, true);
         if(pdoc != NULL)
         {
            pdoc->GetDDX().m_strDISection = "loginstartup_filemanager";
            pdoc->Initialize(true);
            pdoc->UpdateAllViews(NULL, 1234);
            pdoc->UpdateAllViews(NULL, 123458);
            POSITION pos = pdoc->GetFirstViewPosition();
            view * pview = pdoc->GetNextView(pos);
            if(pview != NULL)
            {
               BaseFrameWnd * pframe = dynamic_cast < BaseFrameWnd * > (pview->GetParentFrame());
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
         FileManagerDoc * pdoc = papp->GetStdFileManagerTemplate()->OpenChildList(papp, false, true);
         if(pdoc != NULL)
         {
            pdoc->GetDDX().m_iIconSize = 48;
            pdoc->GetDDX().m_bListText = false;
            pdoc->GetDDX().m_bListSelection = false;
            pdoc->GetDDX().m_pcallback = this;
            pdoc->GetDDX().m_strDISection = "loginstartup_3-action-launch";
            pdoc->Initialize(true);
            pdoc->UpdateAllViews(NULL, 1234);
            pdoc->UpdateAllViews(NULL, 123458);
            POSITION pos = pdoc->GetFirstViewPosition();
            view * pview = pdoc->GetNextView(pos);
            pdoc->FileManagerBrowse(Application.dir().userappdata("loginstartup\\3-action-launch"));
            if(pview != NULL)
            {
               BaseFrameWnd * pframe = dynamic_cast < BaseFrameWnd * > (pview->GetParentFrame());
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
      form_document * pdoc = Application.create_form(this, this);
      if(pdoc == NULL)
         return;
      POSITION pos = pdoc->GetFirstViewPosition();
      if(pos != NULL)
      {
         ex1::create_view::view_data * pviewdata = new ex1::create_view::view_data;
         view * pview = pdoc->GetNextView(pos);
         form_update_hint uh;
         uh.m_etype = form_update_hint::type_browse;
         uh.m_strForm = "filemanager\\replace_name_in_file_system.xhtml";
         pdoc->UpdateAllViews(NULL, 0, &uh);
         
         uh.m_etype = form_update_hint::type_get_form_view;
         pdoc->UpdateAllViews(NULL, 0, &uh);

         uh.m_etype = form_update_hint::type_after_browse;
         pdoc->UpdateAllViews(NULL, 0, &uh);


         pviewdata->m_pwnd = dynamic_cast < ::ca::window * >(pview->GetParentFrame());
         form_child_frame * pframe = dynamic_cast < form_child_frame * >(pviewdata->m_pwnd);
         //pframe->m_iTabId = iId;
         pviewdata->m_pdoc = pdoc;

      }

   }
   break;
/*   case PaneViewPlaylist:
      {
         PlaylistDoc * pdoc = ((MusicalPlayerLightApp *) &Application)->GetPlaylistCentral().GetCurrentPlaylist(true, false);
         
         if(pdoc != NULL)
         {
            MusicalPlayerLightDoc * pplayerdoc = (MusicalPlayerLightDoc *) get_document();
            if(pplayerdoc != NULL)
            {
               pplayerdoc->AttachPlaylist(pdoc);
            }
            if(pdoc != NULL)
            {
               POSITION pos = pdoc->GetFirstViewPosition();
               view * pview = pdoc->GetNextView(pos);
               if(pview != NULL)
               {
                  BaseFrameWnd * pframe = dynamic_cast < BaseFrameWnd * > (pview->GetParentFrame());
                  if(pframe != NULL)
                  {
                     pframe->ModifyStyle(WS_CAPTION, WS_CHILD, 0);
                     pframe->SetParent(this);
                     pviewdata = new ViewData();
                     pviewdata->m_eview = eview;
                     pviewdata->m_pdoc = pdoc;
                     pviewdata->m_pwnd = pframe;
                  }
               }
            }
         }
      }
      break;
   case PaneViewMediaLibrary:
      {
         MediaLibraryDoc * pdoc = (MediaLibraryDoc *) m_pdoctemplateAlbum->OpenDocumentFile(NULL, FALSE);	
         if(pdoc != NULL)
         {
            POSITION pos = pdoc->GetFirstViewPosition();
            view * pview = pdoc->GetNextView(pos);
            if(pdoc != NULL)
            {
               POSITION pos = pdoc->GetFirstViewPosition();
               view * pview = pdoc->GetNextView(pos);
               if(pview != NULL)
               {
                  BaseFrameWnd * pframe = dynamic_cast < BaseFrameWnd * > (pview->GetParentFrame());
                  if(pframe != NULL)
                  {
                     pframe->ModifyStyle(WS_CAPTION, WS_CHILD, 0);
                     pframe->ModifyStyleEx(WS_EX_CLIENTEDGE, 0);
                     pframe->SetParent(this);
                     pviewdata = new ViewData();
                     pviewdata->m_eview = eview;
                     pviewdata->m_pdoc = pdoc;
                     pviewdata->m_pwnd = pframe;
                  }
               }
            }
         }
      }
      break;
   case PaneViewAudioControl:
      {
         GoodMixerDoc * pdoc = (GoodMixerDoc *) m_pdoctemplateAudioControl->OpenDocumentFile(NULL, FALSE);	
         if(pdoc != NULL)
         {
            POSITION pos = pdoc->GetFirstViewPosition();
            view * pview = pdoc->GetNextView(pos);
            if(pdoc != NULL)
            {
               POSITION pos = pdoc->GetFirstViewPosition();
               view * pview = pdoc->GetNextView(pos);
               if(pview != NULL)
               {
                  BaseFrameWnd * pframe = dynamic_cast < BaseFrameWnd * > (pview->GetParentFrame());
                  if(pframe != NULL)
                  {
                     pframe->ModifyStyle(WS_CAPTION, WS_CHILD, 0);
                     pframe->ModifyStyleEx(WS_EX_CLIENTEDGE, 0);
                     pframe->SetParent(this);
                     pviewdata = new ViewData();
                     pviewdata->m_eview = eview;
                     pviewdata->m_pdoc = pdoc;
                     pviewdata->m_pwnd = pframe;
                  }
               }
            }
         }
      }
      break;
   case PaneViewOptions:
      {
         OptionsDoc * pdoc = (OptionsDoc *) m_pdoctemplateOptions->OpenDocumentFile(NULL, FALSE);	
         if(pdoc != NULL)
         {
            POSITION pos = pdoc->GetFirstViewPosition();
            view * pview = pdoc->GetNextView(pos);
            if(pdoc != NULL)
            {
               POSITION pos = pdoc->GetFirstViewPosition();
               view * pview = pdoc->GetNextView(pos);
               if(pview != NULL)
               {
                  BaseFrameWnd * pframe = dynamic_cast < BaseFrameWnd * > (pview->GetParentFrame());
                  if(pframe != NULL)
                  {
                     pframe->ModifyStyle(WS_CAPTION, WS_CHILD, 0);
                     pframe->ModifyStyleEx(WS_EX_CLIENTEDGE, 0);
                     pframe->SetParent(this);
                     pviewdata = new ViewData();
                     pviewdata->m_eview = eview;
                     pviewdata->m_pdoc = pdoc;
                     pviewdata->m_pwnd = pframe;
                  }
               }
            }
         }
      }
      break;*/
   default:
      ASSERT(FALSE);
      break;
   }
}


void pane_view::_001OnMenuMessage(gen::signal_object * pobj)
{
   set_cur_tab_by_id(m_pviewdata->m_id);
}

void pane_view::_001InstallMessageHandling(igui::win::message::Dispatch * pinterface)
{
   BaseView::_001InstallMessageHandling(pinterface);

	IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &pane_view::_001OnCreate);
	IGUI_WIN_MSG_LINK(WM_SIZE, pinterface, this, &pane_view::_001OnSize);
	IGUI_WIN_MSG_LINK(WM_ERASEBKGND, pinterface, this, &pane_view::_001OnEraseBkgnd);
   IGUI_WIN_MSG_LINK(WM_USER + 1122  , this, this, &pane_view::_001OnMenuMessage);

}

void pane_view::Rotate()
{
   loginstartup::EPaneView eviewNew;
   switch(get_view_id())
   {
   case loginstartup::PaneViewContextMenu:
      eviewNew = loginstartup::PaneViewWinActionArea;
      break;
   case loginstartup::PaneViewWinActionArea:
      eviewNew = loginstartup::PaneViewFileManager;
      break;
   case loginstartup::PaneViewFileManager:
      eviewNew = loginstartup::PaneViewContextMenu;
      break;
   default:
      eviewNew = loginstartup::PaneViewWinActionArea;
   }

   set_cur_tab_by_id(eviewNew);
}

void pane_view::OnFileManagerOpenFile(
      FileManagerDDX & ddx, 
      FileManagerItemArray & itema)
{
   if(itema.get_size() > 0)
   {
      int i = (int) ::ShellExecuteW(
         GetTopLevelParent()->_get_handle(), 
         NULL, 
         L"\"" + gen::international::utf8_to_unicode(itema[0].m_strPath) + L"\"",
         NULL,
         L"\"" + gen::international::utf8_to_unicode(Application.dir().name(itema[0].m_strPath)) + L"\"",
         SW_SHOWNORMAL);
      string str;
      str.Format("%d", i);
      //Application.simple_message_box(str);
      if(i == ERROR_FILE_NOT_FOUND)
      {
      }
   }
   GetParentFrame()->ShowWindow(SW_HIDE);
}

} // namespace loginstartup