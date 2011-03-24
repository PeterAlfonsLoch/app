#include "StdAfx.h"
#include "html_pane_view.h"
#include "html_application.h"
#include "html/html_view.h"
#include "html/html_document.h"

html_pane_view::html_pane_view(::ca::application * papp) :
   ::ca::ca(papp),
   Ex1TabInterface(papp),
   BaseVirtualTab(papp),
   base_tab_view(papp),
   guiex::pane_tab_view(papp)
{
   
   m_pcreateview = this;


   m_etranslucency      = TranslucencyPresent;

   m_pviewdata              = NULL;
   m_pviewdataOld              = NULL;

}

html_pane_view::~html_pane_view()
{
}



#ifdef _DEBUG
void html_pane_view::AssertValid() const
{
	BaseView::AssertValid();
}

void html_pane_view::Dump(CDumpContext& dc) const
{
	BaseView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// html_pane_view message handlers

void html_pane_view::_001OnCreate(gen::signal_object * pobj) 
{
   SCAST_PTR(igui::win::message::create, pcreate, pobj)
   if(pobj->previous())
      return;

   AddTab("Menu", html::PaneViewContextMenu);
   AddTab("html", html::PaneViewHtml);
   AddTab("html edit", html::PaneViewHtmlEdit);
   AddTab("source edit", html::PaneViewSourceEdit);
   AddTab("FileManager", html::PaneViewFileManager);

   ShowView(html::PaneViewHtml);
   Layout();
}

void html_pane_view::on_create_view(view_data * pviewdata)
{
   html_application * papp = dynamic_cast < html_application * > ((dynamic_cast < BaseFrameWnd * > (GetParentFrame()))->get_app());
   html_document * pdoc = dynamic_cast < html_document * > (papp->m_ptemplate_html->OpenDocumentFile(NULL, TRUE, this));
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
            pviewdata->m_pdoc = pdoc;
            pviewdata->m_pwnd = pframe;
         }
      }
   }

   //switch(pviewdata->m_id)
   //{
   //case html::PaneViewContextMenu:
      /*{
         devedgeFrontDoc * pdoc = (devedgeFrontDoc *) (dynamic_cast < html_application * > ((dynamic_cast < BaseFrameWnd * > (GetParentFrame()))->m_papp))->m_ptemplateFront->OpenDocumentFile("http://localhost:10011/");
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
                  pviewdata = new base_create_view::view_data();
                  pviewdata->m_eview = eview;
                  pviewdata->m_pdoc = pdoc;
                  pviewdata->m_pwnd = pframe;


               }
            }
         }
      }*/
  //       break;
      
/*         CreateContext cc;
         cc.m_pCurrentDoc = GetDocument();
         cc.m_typeinfoNewView =  &typeid(BaseWndMenuListView);

         BaseView * pview = dynamic_cast < BaseView * > (CreateView(&cc, 101, this));
         if(pview != NULL)
         {
            BaseWndMenuListView * pmenuview = (BaseWndMenuListView *) pview;
            pmenuview->m_wnd.LoadMenu(IDR_POPUP_LYRICVIEW);
            pmenuview->m_wnd.m_bAutoClose = false;
            pviewdata = new base_create_view::view_data();
            pviewdata->m_eview = eview;
            pviewdata->m_pdoc = GetDocument();
            pviewdata->m_pwnd = pview;
         }*/
/*   case html::PaneViewSourceEdit:
      {
         devedge_document * pdoc = dynamic_cast < devedge_document * > (papp->m_ptemplate_devedge->OpenDocumentFile(NULL));
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
                  pviewdata->m_pdoc = pdoc;
                  pviewdata->m_pwnd = pframe;
               }
            }
         }
      }
      break;
   case html::PaneViewHtmlEdit:
      {
         devedge_document * pdoc = dynamic_cast < devedge_document * > (papp->m_ptemplate_html_edit->OpenDocumentFile(NULL));
         if(pdoc != NULL)
         {
            POSITION pos = pdoc->GetFirstViewPosition();
            view * pview = pdoc->GetNextView(pos);
            if(pview != NULL)
            {
               html_child_frame * pframe = dynamic_cast < html_child_frame * > (pview->GetParentFrame());
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
   case html::PaneViewHtml:
      {
         devedge_document * pdoc = dynamic_cast < devedge_document * > (papp->m_ptemplate_html->OpenDocumentFile(NULL, TRUE, this));
         if(pdoc != NULL)
         {
            POSITION pos = pdoc->GetFirstViewPosition();
            view * pview = pdoc->GetNextView(pos);
            if(pview != NULL)
            {
               base_wnd * pparentframe = dynamic_cast < base_wnd *> (pview->GetParentFrame());
               html_child_frame * pframe = dynamic_cast < html_child_frame * > (pparentframe);
               if(pframe != NULL)
               {
                  string str = Application.dir().matter("html_reader\\html_toolbar.xml");
                  str = Application.file().as_string(str);
	               if (!pframe->m_toolbar.CreateEx(pframe) ||
		                !pframe->m_toolbar.LoadXmlToolBar(str))
	               {
		               TRACE0("Failed to create toolbar\n");
	               }
                  pframe->ModifyStyle(WS_CAPTION, WS_CHILD, 0);
                  pframe->SetParent(this);
                  pviewdata->m_pdoc = pdoc;
                  pviewdata->m_pwnd = pframe;
               }
            }
         }
      }
      break;
   case html::PaneViewFileManager:
      {
         FileManagerDoc * pdoc = papp->GetStdFileManagerTemplate()->OpenChild(papp, false, true, this);
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
                  pviewdata->m_pdoc    = pdoc;
                  pviewdata->m_pwnd    = pframe;

                  pdoc->Initialize(true);
               }
            }
         }
      }
      break;*/
/*   case PaneViewPlaylist:
      {
         PlaylistDoc * pdoc = ((MusicalPlayerLightApp *) AfxGetApp())->GetPlaylistCentral().GetCurrentPlaylist(true, false);
         
         if(pdoc != NULL)
         {
            MusicalPlayerLightDoc * pplayerdoc = (MusicalPlayerLightDoc *) GetDocument();
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
                     pviewdata = new base_create_view::view_data();
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
                     pviewdata = new base_create_view::view_data();
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
                     pviewdata = new base_create_view::view_data();
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
                     pviewdata = new base_create_view::view_data();
                     pviewdata->m_eview = eview;
                     pviewdata->m_pdoc = pdoc;
                     pviewdata->m_pwnd = pframe;
                  }
               }
            }
         }
      }
      break;*/
/*  default:
      ASSERT(FALSE);
      break;
   }*/
}



void html_pane_view::Rotate()
{
   int eview = atoi(get_cur_tab());
   int eviewNew = html::PaneViewHtml;
   switch(eview)
   {
   case html::PaneViewHtml:
      eviewNew = html::PaneViewHtmlEdit;
      break;
   case html::PaneViewHtmlEdit:
      eviewNew = html::PaneViewSourceEdit;
      break;
   case html::PaneViewSourceEdit:
      eviewNew = html::PaneViewFileManager;
      break;
   case html::PaneViewFileManager:
      eviewNew = html::PaneViewHtml;
      break;
   default:
      ASSERT(FALSE);
      break;
   }

   ShowView(eviewNew);
}

void html_pane_view::_001OnMenuMessage(gen::signal_object * pobj)
{
   ShowView(m_pviewdataOld->m_id);
}

void html_pane_view::_001InstallMessageHandling(igui::win::message::Dispatch * pinterface)
{
   BaseView::_001InstallMessageHandling(pinterface);

	IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &html_pane_view::_001OnCreate);
	IGUI_WIN_MSG_LINK(WM_ERASEBKGND, pinterface, this, &html_pane_view::_001OnEraseBkgnd);
   IGUI_WIN_MSG_LINK(WM_USER + 1122  , this, this, &html_pane_view::_001OnMenuMessage);
}

/*
void html_pane_view::_001OnTabClick(int iTab)
{
   
   
   EPaneView eview = PaneViewNone;
   switch(iTab)
   {
   case 0:
      eview = PaneViewContextMenu;
      break;
   case 1:
      eview = PaneViewDevEdge;
      break;
   case 2:
      eview = PaneViewFileManager;
      break;
   default:
      ASSERT(FALSE);
      break;
   }
   ShowView(eview);
   (dynamic_cast < BaseFrameWnd * > (GetParentFrame()))->_001RedrawWindow();
   
}*/

void html_pane_view::OnViewUpdateHint(view* pSender, LPARAM lHint, view_update_hint * puh)
{
   if(puh->m_etype == view_update_hint::TypeOpenDocument)
   {
      if(!GetDocument()->GetPathName().is_empty())
      {
         html_application * papp = dynamic_cast < html_application * > (get_app());
         papp->m_ptemplate_html->OpenDocumentFile(GetDocument()->GetPathName(), true, this);
         papp->m_ptemplate_html_edit->OpenDocumentFile(GetDocument()->GetPathName(), true, this);
         papp->m_ptemplate_devedge->OpenDocumentFile(GetDocument()->GetPathName(), true, this);
      }
   }
   base_tab_view::OnViewUpdateHint(pSender, lHint, puh);
}


void html_pane_view::OnUpdate(view * pSender, LPARAM lHint, base_object * pHint)
{
   if(pHint != NULL)
   {
      if(base < html_pane_view_update_hint > ::bases(pHint))
      {
         html_pane_view_update_hint * puh = dynamic_cast < html_pane_view_update_hint * > (pHint);
      }
   }
   base_tab_view::OnUpdate(pSender, lHint, pHint);
}

html::document * html_pane_view::get_document()
{
   html_document * pdoc = get_html_document();
   if(pdoc == NULL)
      return NULL;
   return pdoc->get_document();
}

html_document * html_pane_view::get_html_document()
{
   if(m_pviewdata == NULL)
      return NULL;
   return dynamic_cast < html_document * > (m_pviewdata->m_pdoc);
}