#include "StdAfx.h"
#include "view.h"
#include "view_update_hint.h"
#include "html/html_document.h"


namespace i2com
{

   view::view(::ca::application * papp) :
      ca(papp),
      ::user::tab(papp),
      ::userbase::view(papp),
      ::userbase::tab_view(papp),
      ::userex::pane_tab_view(papp),
      m_font(papp),
      place_holder_container(papp)
   {
      m_font->CreatePointFont(84, "Geneva");
   }

   view::~view()
   {
   }

   void view::install_message_handling(::user::win::message::dispatch * pinterface)
   {
      ::userex::pane_tab_view::install_message_handling(pinterface);

      IGUI_WIN_MSG_LINK(WM_DESTROY, pinterface, this, &view::_001OnDestroy);
      IGUI_WIN_MSG_LINK(WM_SIZE, pinterface, this, &view::_001OnSize);
      IGUI_WIN_MSG_LINK(WM_PAINT, pinterface, this, &view::_001OnPaint);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &view::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_CONTEXTMENU, pinterface, this, &view::_001OnContextMenu);
      IGUI_WIN_MSG_LINK(WM_SETCURSOR, pinterface, this, &view::_001OnSetCursor);
      IGUI_WIN_MSG_LINK(WM_ERASEBKGND, pinterface, this, &view::_001OnEraseBkgnd);



   }

   void view::OnDraw(::ca::graphics * pdcScreen)
   {
      UNREFERENCED_PARAMETER(pdcScreen);
   }

   #ifdef _DEBUG
   void view::assert_valid() const
   {
      ::userbase::view::assert_valid();
   }

   void view::dump(dump_context & dumpcontext) const
   {
      ::userbase::view::dump(dumpcontext);
   }
   #endif //_DEBUG



   BOOL view::PreCreateWindow(CREATESTRUCT& cs)
   {
      cs.lpszClass = System.RegisterWndClass(
         CS_DBLCLKS |
         CS_OWNDC,
         0, 0, 0);
      cs.style &= ~WS_EX_CLIENTEDGE;
      return ::userbase::view::PreCreateWindow(cs);
   }

   void view::_001OnInitialUpdate(gen::signal_object * pobj) 
   {
      ::userbase::view::_001OnInitialUpdate(pobj);
   }

   void view::_001OnDestroy(gen::signal_object * pobj) 
   {
      ::userbase::view::_001OnDestroy(pobj);
   }

   void view::_001OnSize(gen::signal_object * pobj) 
   {
      UNREFERENCED_PARAMETER(pobj);
//      SCAST_PTR(::user::win::message::size, psize, pobj)

   /*   pobj->previous();

      double d = psize->m_size.cy;
      d /= GetSystemMetrics(SM_CYSCREEN);
      SetScale(d);

      GetClientRect(m_rectKaraokeView);


      rect rectClient;
      GetClientRect(rectClient);
      rect rect = rectClient;

      rect.top = rect.bottom - 24;
      m_viewlineStatus.SetPlacement(rect);


      m_rectKaraokeView.bottom -= 16;

      LayoutTitleLines();
      LayoutLyricTemplateLines();
      LayoutLyricLines();
      LayoutKaraokeBouncingBall();*/
   }

   void view::_001OnPaint(gen::signal_object * pobj) 
   {
      UNREFERENCED_PARAMETER(pobj);
   //   CPaintDC spgraphics(this); // device context for painting
      

   //   spgraphics->TextOut(20, 20, "Carlos Gustavo Cecyn Lundgren ・minha Vida Eterna, meu Cora鈬o Eterno, Todo meu tesouro eterno, meu Universo eterno, meu tudo eterno!!");
   }


   void view:: _001OnDraw(::ca::graphics * pdc)
   {

      /*FIBITMAP * pdib = CImaging::LoadImageFile("C:\\screenshot.jpeg");

      ::ca::bitmap bmp2;

      bmp2.Attach(CImaging::FItoHBITMAP(pdib, true));
      ::ca::graphics_sp dc2;
      dc2.CreateCompatibleDC(pdc);
      dc2.SelectObject(bmp2);

      //::SendMessage(::GetDesktopWindow(), WM_PRINT, (WPARAM)(HDC)spgraphics, PRF_CHILDREN | PRF_NONCLIENT | PRF_CLIENT);

      pdc->BitBlt(0, 0, 1280, 1024, &dc2, 0, 0, SRCCOPY);*/

      /*rect rectClient;
      GetClientRect(rectClient);
      pdc->FillSolidRect(rectClient, RGB(255, 255, 255));
      pdc->SetBkMode(TRANSPARENT);*/
      /*pdc->SelectObject(m_font);
      pdc->TextOut(20, 20, "Curitiba, 24 de fevereiro de 2008.");
      pdc->TextOut(20, 80, "Carlos Gustavo Cecyn Lundgren ・minha Vida Eterna, meu Cora鈬o Eterno, Todo meu tesouro eterno, meu Universo eterno, meu tudo eterno!!");
      pdc->TextOut(20, 110, "Assinado Camilo Sasuke Tsumanuma.");*/
   //   m_basecontrol._001OnDraw(pdc);
      ::userex::pane_tab_view::_001OnDraw(pdc);
   }

   void view::_001OnCreate(gen::signal_object * pobj) 
   {
      //SCAST_PTR(::user::win::message::create, pcreate, pobj)
      if(pobj->previous())
         return;

      add_tab("people", i2com::PaneViewContact);
      add_tab("Audio Control", "pane_view_audio_control");
      //m_tab.add_tab("cecyn1@hotmail.com", i2com::PaneViewCommunication);

      set_cur_tab_by_id(i2com::PaneViewContact);
   }
   void view::_001OnContextMenu(gen::signal_object * pobj) 
   {
      SCAST_PTR(::user::win::message::context_menu, pcontextmenu, pobj)
      point point = pcontextmenu->GetPoint();
      
   }




   void view::_001OnSetCursor(gen::signal_object * pobj) 
   {
      ::SetCursor(::LoadCursor(NULL, IDC_ARROW));
      
      pobj->previous();
   }
   void view::_001OnEraseBkgnd(gen::signal_object * pobj) 
   {
      SCAST_PTR(::user::win::message::erase_bkgnd, perasebkgnd, pobj)
      perasebkgnd->m_bRet = true;
      perasebkgnd->set_result(TRUE);
   }

   void view::pre_translate_message(gen::signal_object * pobj)
   {
      ::userbase::view::pre_translate_message(pobj);
   }



   void view::on_create_view(::user::view_creator_data * pcreatordata)
   {
      application * papp = dynamic_cast < application * > (get_app());
      if(pcreatordata->m_id.is_text())
      {
         string strId(pcreatordata->m_id);
         if(System.url().get_protocol(strId) == "i2com")
         {
            if(gen::str::begins(System.url().get_script(strId), "/im/"))
            {
               document * pdoc = dynamic_cast < document * > (papp->m_ptemplateCommunication->open_document_file(NULL, TRUE, this));
               if(pdoc != NULL)
               {
                  ::view * pview = pdoc->get_view(0);
                  if(pview != NULL)
                  {
                     pdoc->m_pcommview = dynamic_cast < i2com::comm_view * > (pview);
                     userbase::frame_window * pframe = dynamic_cast < userbase::frame_window * > (pview->GetParentFrame());
                     if(pframe != NULL)
                     {
                        pcreatordata->m_pdoc = pdoc;
                        pcreatordata->m_pwnd = pframe;
                     }
                  }
               }
            }
         }
      }
      else
      {
         switch(pcreatordata->m_id)
         {
         case i2com::PaneViewCommunication:
            {
               form_document * pdoc = (form_document *) System.create_form(this, this);
               if(pdoc != NULL)
               {
                  ::view * pview = pdoc->get_view();
                  if(pview != NULL)
                  {
                     userbase::frame_window * pframe = dynamic_cast < userbase::frame_window * > (pview->GetParentFrame());
                     if(pframe != NULL)
                     {
                        pcreatordata->m_pdoc = pdoc;
                        pcreatordata->m_pwnd = pframe;
                     }
                  }
               }
            }
            break;
         case i2com::PaneViewContact:
            {
               document * pdoc = dynamic_cast < document * > (papp->m_ptemplateContact->open_document_file(NULL, TRUE, this));
               pdoc->m_ppaneview = this;
               if(pdoc != NULL)
               {
                  i2com::contact_view * pview = pdoc->get_typed_view < i2com::contact_view > ();
                  if(pview != NULL)
                  {
                     pview->refresh();
                     userbase::frame_window * pframe = dynamic_cast < userbase::frame_window * > (pview->GetParentFrame());
                     if(pframe != NULL)
                     {
                        pcreatordata->m_pdoc = pdoc;
                        pcreatordata->m_pwnd = pframe;
                     }
                  }
               }
            }
            break;
         case i2com::PaneViewFileManager:
            {
               ::filemanager::document * pdoc = papp->GetStdFileManagerTemplate()->OpenChild(papp, false, true);
               if(pdoc != NULL)
               {
                  ::view * pview = pdoc->get_view();
                  if(pview != NULL)
                  {
                     userbase::frame_window * pframe = dynamic_cast < userbase::frame_window * > (pview->GetParentFrame());
                     if(pframe != NULL)
                     {
                        pcreatordata->m_pdoc = pdoc;
                        pcreatordata->m_pwnd = pframe;
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
                     ::view * pview = pdoc->get_view(pos);
                     if(pview != NULL)
                     {
                        userbase::frame_window * pframe = dynamic_cast < userbase::frame_window * > (pview->GetParentFrame());
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
                  ::view * pview = pdoc->get_view(pos);
                  if(pdoc != NULL)
                  {
                     POSITION pos = pdoc->get_view_count();
                     ::view * pview = pdoc->get_view(pos);
                     if(pview != NULL)
                     {
                        userbase::frame_window * pframe = dynamic_cast < userbase::frame_window * > (pview->GetParentFrame());
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
                  ::view * pview = pdoc->get_view(pos);
                  if(pdoc != NULL)
                  {
                     POSITION pos = pdoc->get_view_count();
                     ::view * pview = pdoc->get_view(pos);
                     if(pview != NULL)
                     {
                        userbase::frame_window * pframe = dynamic_cast < userbase::frame_window * > (pview->GetParentFrame());
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
                  ::view * pview = pdoc->get_view(pos);
                  if(pdoc != NULL)
                  {
                     POSITION pos = pdoc->get_view_count();
                     ::view * pview = pdoc->get_view(pos);
                     if(pview != NULL)
                     {
                        userbase::frame_window * pframe = dynamic_cast < userbase::frame_window * > (pview->GetParentFrame());
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
      ::userex::pane_tab_view::on_create_view(pcreatordata);
   }


   void view::on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint) 
   {

      application * papp = dynamic_cast < application * > (get_app());
      count count = papp->m_ptemplateHtml->get_document_count();
      for(index index = 0; index < count; index++)
      {
         ::document * pdoc = papp->m_ptemplateHtml->get_document(index);
         pdoc->update_all_views(pSender, lHint, pHint);
      }
      
      /*if(pHint != NULL)
      {
         if(base < view_update_hint >::bases(pHint))
         {
            view_update_hint * puh = (view_update_hint *) pHint;
            if(puh->is_type_of(view_update_hint::TypeGetView))
            {
               puh->m_eview = GetViewId();
            }
            else if(puh->is_type_of(view_update_hint::TypeSetView))
            {
               ShowView(puh->m_eview);
            }
         }
      }*/
        /* if(pHint != NULL)
      {
         if(base < view_update_hint >::bases(pHint))
         {
            view_update_hint * puh = (view_update_hint * ) pHint;
            if(puh->is_type_of(view_update_hint::TypeOnShowKaraoke))
            {
               (dynamic_cast < userbase::frame_window * > (GetTopLevelFrame()))->SetActiveView(this);
            }
            else if(puh->is_type_of(view_update_hint::TypeOnShowView))
            {
               int iTab;
   //            if(puh->m_eview == PaneViewContextMenu)
     //          {
       //           m_tab._001AddSel(0);
         //      }
   //            else
               {
                  switch(puh->m_eview)
                  {
                  case PaneViewPeople:
                     iTab = 0;
                     break;
                  case PaneViewPerson:
                     iTab = 1;
                     break;
                  }
                  m_tab._001SetSel(iTab);
               }
               
            }
         }
      }*/

   }


   void view::i2com_open(const char * pszUrl)
   {
      string strUrl(pszUrl);
      if(System.url().get_protocol(strUrl) == "i2com")
      {
         if(gen::str::begins(System.url().get_script(strUrl), "/im/"))
         {
            string strId;
            strId = "i2com://";
            strId += System.url().get_server(strUrl);
            strId += "/im/";
            set_cur_tab_by_id(strId);
            document * pdoc = dynamic_cast < document * > (get(strId)->m_pdoc);
            pdoc->m_pcommview->i2com_open(strUrl);
         }
      }
   }

} // namespace i2com