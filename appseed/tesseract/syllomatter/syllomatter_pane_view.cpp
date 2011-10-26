#include "StdAfx.h"
#include "syllomatter_pane_view.h"
#include "html/html_view.h"
#include "html/html_document.h"

syllomatter_pane_view::syllomatter_pane_view(::ca::application * papp) :
   ca(papp),
   ::user::tab(papp),
   ::userbase::view(papp),
   ::userbase::tab_view(papp),
   ::userex::pane_tab_view(papp),
   place_holder_container(papp)
{
   m_pfilemanagerdoc = NULL;

   
   m_pviewdataOld = NULL;
   m_psvnview = NULL;

   
   m_etranslucency      = TranslucencyPresent;

   m_pviewdata              = NULL;
   m_pviewdataOld              = NULL;

   

   connect_command("commit_", &syllomatter_pane_view::_001OnCommit_);
   connect_command("update", &syllomatter_pane_view::_001OnUpdate);

}

syllomatter_pane_view::~syllomatter_pane_view()
{
}



#ifdef _DEBUG
void syllomatter_pane_view::assert_valid() const
{
   ::userbase::view::assert_valid();
}

void syllomatter_pane_view::dump(dump_context & dumpcontext) const
{
   ::userbase::view::dump(dumpcontext);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// syllomatter_pane_view message handlers

void syllomatter_pane_view::_001OnCreate(gen::signal_object * pobj) 
{

   if(pobj->previous())
      return;

   add_tab("menu", syllomatter::PaneViewContextMenu);
   add_tab("Form", syllomatter::PaneViewForm);
   add_tab("SVN", syllomatter::PaneViewSVN);
   add_tab("FileManager", syllomatter::PaneViewFileManager);

   set_cur_tab_by_id(syllomatter::PaneViewForm);

}


void syllomatter_pane_view::on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint) 
{

   UNREFERENCED_PARAMETER(pSender);
   UNREFERENCED_PARAMETER(lHint);

   if(pHint != NULL)
   {
      if(base < syllomatter::pane_view_update_hint >::bases(pHint))
      {
         syllomatter::pane_view_update_hint * puh = (syllomatter::pane_view_update_hint *) pHint;
         if(puh->is_type_of(syllomatter::pane_view_update_hint::TypeGetView))
         {
            puh->m_iId = atoi(get_cur_tab_id());
         }
         else if(puh->is_type_of(syllomatter::pane_view_update_hint::TypeSetView))
         {
            set_cur_tab_by_id(puh->m_iId);
         }
      }
   }
      if(pHint != NULL)
   {
      if(base < syllomatter::pane_view_update_hint > :: bases(pHint))
      {
         syllomatter::pane_view_update_hint * puh = (syllomatter::pane_view_update_hint * ) pHint;
         if(puh->is_type_of(syllomatter::pane_view_update_hint::TypeOnShowKaraoke))
         {
            GetTopLevelFrame()->SetActiveView(this);
         }
         else if(puh->is_type_of(syllomatter::pane_view_update_hint::TypeOnShowView))
         {
            int iTab;
//            if(puh->m_eview == PaneViewContextMenu)
  //          {
    //           m_tab._001AddSel(0);
      //      }
//            else
            {
               switch(puh->m_iId)
               {
               case syllomatter::PaneViewContextMenu:
                  iTab = 0;
                  break;
               case syllomatter::PaneViewForm:
                  iTab = 1;
                  break;
               case syllomatter::PaneViewSVN:
                  iTab = 2;
                  {
                     (dynamic_cast < syllomatter::main_frame * > (GetParentFrame()))
                        ->LoadToolBar("syllomatter_list_toolbar.xml");
                  }
                  break;
               case syllomatter::PaneViewFileManager:
                  iTab = 3;
                  break;
               }
               _001SetSel(iTab);
            }
            
         }
      }
   }

}

void syllomatter_pane_view::on_show_view()
{
   ::userex::pane_tab_view::on_show_view();
   if(m_pviewdata->m_id ==  syllomatter::PaneViewSVN)
   {
      (dynamic_cast < syllomatter::main_frame * > (GetParentFrame()))
         ->LoadToolBar("syllomatter_list_toolbar.xml");
   }
}


BOOL syllomatter_pane_view::PreCreateWindow(CREATESTRUCT& cs) 
{
   cs.dwExStyle &= ~WS_EX_CLIENTEDGE;   

   return ::userbase::view::PreCreateWindow(cs);
}


void syllomatter_pane_view::on_create_view(::user::view_creator_data * pcreatordata)
{
   syllomatter::application * papp = dynamic_cast < syllomatter::application * > (get_app());;
   switch(pcreatordata->m_id)
   {
   case syllomatter::PaneViewContextMenu:
      /*{
         devedgeFrontDoc * pdoc = (devedgeFrontDoc *) (dynamic_cast < syllomatter::application * > (((userbase::frame_window *) GetParentFrame())->m_papp))->m_ptemplateFront->open_document_file("http://localhost:10011/");
         if(pdoc != NULL)
         {
            POSITION pos = pdoc->get_view_count();
            ::userbase::view * pview = pdoc->get_view(pos);
            if(pview != NULL)
            {
               userbase::frame_window * pframe = (userbase::frame_window *) pview->GetParentFrame();
               if(pframe != NULL)
               {
                  pcreatordata->m_pdoc = pdoc;
                  pcreatordata->m_pwnd = pframe;
               }
            }
         }
      }*/
         break;
      
/*         create_context cc;
         cc.m_pCurrentDoc = get_document();
         cc.m_typeinfoNewView =  RUNTIME_CLASS(::userbase::menu_list_view);

         ::userbase::view * pview = dynamic_cast < ::userbase::view * > (CreateView(&cc, 101, this));
         if(pview != NULL)
         {
            ::userbase::menu_list_view * pmenuview = (::userbase::menu_list_view *) pview;
            pmenuview->m_wnd.LoadMenu(IDR_POPUP_LYRICVIEW);
            pmenuview->m_wnd.m_bAutoClose = false;
            pcreatordata = new ViewData();
            pcreatordata->m_eview = eview;
            pcreatordata->m_pdoc = get_document();
            pcreatordata->m_pwnd = pview;
         }*/
   case syllomatter::PaneViewForm:
      {
         m_pdoctemplateExtractChanges = new ::userbase::single_document_template(
          get_app(),
          "syllomatter/frame",
          ::ca::get_type_info < syllomatter_document > (),
          ::ca::get_type_info < syllomatter_frame > (),
          ::ca::get_type_info < syllomatter_view > ());

         /*
       syllomatter_document * pdoc = dynamic_cast < syllomatter_document * > (
          m_pdoctemplateExtractChanges->open_document_file(
          Application.dir().matter("syllomatter_extract_changes_form.xhtml")));*/
         m_pdocForm = dynamic_cast < syllomatter_document * > (
          m_pdoctemplateExtractChanges->open_document_file(NULL, true, this));
         m_pdocForm->open_commit_message();
         syllomatter_view * pview = m_pdocForm->get_typed_view < syllomatter_view > ();
         m_pviewForm = pview;
         if(pview != NULL)
         {
            pcreatordata->m_pdoc = get_document();
            pcreatordata->m_pwnd = pview->GetParentFrame();
         }
      }
      break;
   case syllomatter::PaneViewSVN:
      {
         syllomatter_document * pdoc = dynamic_cast < syllomatter_document * > (m_pdoctemplateExtractChanges->get_document());
/*         create_context cc;
         cc.m_pCurrentDoc = pdoc;
         cc.m_typeinfoNewView = ::ca::get_type_info < svn_view > ();*/
         svn_view * pview = dynamic_cast < svn_view * > (::view::create_view(::ca::get_type_info < svn_view > (), get_document(), this, 1000));
         m_psvnview = pview;
         m_psvnview->m_ppaneview = this;
         m_psvnview->CreateViews();
         m_psvnview->m_plistview->m_ppaneview = this;
         if(pview != NULL)
         {
            pcreatordata->m_pdoc = get_document();
            pcreatordata->m_pwnd = pview;
         }
      }
      break;
   case syllomatter::PaneViewFileManager:
      {
         ::filemanager::document * pdoc = papp->GetStdFileManagerTemplate()->OpenChild(papp, false, true, this);
         m_pfilemanagerdoc = pdoc;
         if(pdoc != NULL)
         {
            ::view * pview = pdoc->get_view();
            if(pview != NULL)
            {
               frame_window * pframe = (frame_window *) pview->GetParentFrame();
               if(pframe != NULL)
               {
                  pcreatordata->m_pdoc = pdoc;
                  pcreatordata->m_pwnd = pframe;
                  pdoc->Initialize(true);
               }
            }
         }
      }
      break;
/*   case PaneViewPlaylist:
      {
         ::mediaplaylist::document * pdoc = ((MusicalPlayerLightApp *) &System)->GetPlaylistCentral().GetCurrentPlaylist(true, false);
         
         if(pdoc != NULL)
         {
            MusicalPlayerLightDoc * pplayerdoc = (MusicalPlayerLightDoc *) get_document();
            if(pplayerdoc != NULL)
            {
               pplayerdoc->AttachPlaylist(pdoc);
            }
            if(pdoc != NULL)
            {
               POSITION pos = pdoc->get_view_count();
               ::userbase::view * pview = pdoc->get_view(pos);
               if(pview != NULL)
               {
                  userbase::frame_window * pframe = (userbase::frame_window *) pview->GetParentFrame();
                  if(pframe != NULL)
                  {
                     pcreatordata->m_pdoc = pdoc;
                     pcreatordata->m_pwnd = pframe;
                  }
               }
            }
         }
      }
      break;
   case PaneViewMediaLibrary:
      {
         MediaLibraryDoc * pdoc = (MediaLibraryDoc *) m_pdoctemplateAlbum->open_document_file(NULL, FALSE);   
         if(pdoc != NULL)
         {
            POSITION pos = pdoc->get_view_count();
            ::userbase::view * pview = pdoc->get_view(pos);
            if(pdoc != NULL)
            {
               POSITION pos = pdoc->get_view_count();
               ::userbase::view * pview = pdoc->get_view(pos);
               if(pview != NULL)
               {
                  userbase::frame_window * pframe = (userbase::frame_window *) pview->GetParentFrame();
                  if(pframe != NULL)
                  {
                     pcreatordata->m_pdoc = pdoc;
                     pcreatordata->m_pwnd = pframe;
                  }
               }
            }
         }
      }
      break;
   case PaneViewAudioControl:
      {
         GoodMixerDoc * pdoc = (GoodMixerDoc *) m_pdoctemplateAudioControl->open_document_file(NULL, FALSE);   
         if(pdoc != NULL)
         {
            POSITION pos = pdoc->get_view_count();
            ::userbase::view * pview = pdoc->get_view(pos);
            if(pdoc != NULL)
            {
               POSITION pos = pdoc->get_view_count();
               ::userbase::view * pview = pdoc->get_view(pos);
               if(pview != NULL)
               {
                  userbase::frame_window * pframe = (userbase::frame_window *) pview->GetParentFrame();
                  if(pframe != NULL)
                  {
                     pcreatordata->m_pdoc = pdoc;
                     pcreatordata->m_pwnd = pframe;
                  }
               }
            }
         }
      }
      break;
   case PaneViewOptions:
      {
         OptionsDoc * pdoc = (OptionsDoc *) m_pdoctemplateOptions->open_document_file(NULL, FALSE);   
         if(pdoc != NULL)
         {
            POSITION pos = pdoc->get_view_count();
            ::userbase::view * pview = pdoc->get_view(pos);
            if(pdoc != NULL)
            {
               POSITION pos = pdoc->get_view_count();
               ::userbase::view * pview = pdoc->get_view(pos);
               if(pview != NULL)
               {
                  userbase::frame_window * pframe = (userbase::frame_window *) pview->GetParentFrame();
                  if(pframe != NULL)
                  {
                     pcreatordata->m_pdoc = pdoc;
                     pcreatordata->m_pwnd = pframe;
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




void syllomatter_pane_view::_001OnMenuMessage(gen::signal_object * pobj)
{
   UNREFERENCED_PARAMETER(pobj);
   set_cur_tab_by_id(m_pviewdataOld->m_id);
}

void syllomatter_pane_view::install_message_handling(::user::win::message::dispatch * pinterface)
{
   ::userex::pane_tab_view::install_message_handling(pinterface);
   IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &syllomatter_pane_view::_001OnCreate);
   IGUI_WIN_MSG_LINK(WM_USER + 1122  , pinterface, this, &syllomatter_pane_view::_001OnMenuMessage);
   IGUI_WIN_MSG_LINK(WM_USER + 1123  , pinterface, this, &syllomatter_pane_view::_001OnStartVerisvnwellExtract);

}

void syllomatter_pane_view::_001OnStartVerisvnwellExtract(gen::signal_object * pobj)
{
   UNREFERENCED_PARAMETER(pobj);
   set_cur_tab_by_id(syllomatter::PaneViewSVN);
}

void syllomatter_pane_view::_001OnCommit_(gen::signal_object * pobj)
{
   UNREFERENCED_PARAMETER(pobj);
   ::fs::item_array itema;
   m_pfilemanagerdoc->GetActiveViewSelection(itema);
   set_cur_tab_by_id(syllomatter::PaneViewSVN);
   m_psvnview->m_plistview->Commit_(itema);
}

void syllomatter_pane_view::_001OnUpdate(gen::signal_object * pobj)
{
   UNREFERENCED_PARAMETER(pobj);
   ::fs::item_array itema;
   m_pfilemanagerdoc->GetActiveViewSelection(itema);
   set_cur_tab_by_id(syllomatter::PaneViewSVN);
   m_psvnview->m_plistview->Update(itema);
}
