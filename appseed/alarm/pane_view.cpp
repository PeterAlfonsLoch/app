#include "StdAfx.h"

namespace alarm
{

   pane_view::pane_view(::ca::application * papp) :
      ca(papp),
      user::tab(papp),
      ::userbase::view(papp),
      userbase::tab_view(papp),
      userex::pane_tab_view(papp),
      user::place_holder_container(papp)
   {
      m_pcreateview = this;
      m_etranslucency      = TranslucencyPresent;
   
   }

   pane_view::~pane_view()
   {
   }


#ifdef _DEBUG
   void pane_view::assert_valid() const
   {
	   ::userex::pane_tab_view::assert_valid();
   }

   void pane_view::dump(dump_context& dc) const
   {
	   ::userex::pane_tab_view::dump(dc);
   }
#endif //_DEBUG

   void pane_view::_001OnCreate(gen::signal_object * pobj) 
   {
      SCAST_PTR(user::win::message::create, pcreate, pobj)

      if(pobj->previous())
         return;

      add_tab("Menu", PaneViewContextMenu);
      add_tab("DevEdge", PaneViewDevEdge);
      add_tab("by weekday", PaneViewByWeekday);
      add_tab("FileManager", PaneViewFileManager);
      add_tab("Alarm Preview", PaneViewAlarmTest);

      set_cur_tab_by_id(PaneViewDevEdge);

   }


   void pane_view::on_update(::view* pviewSender, LPARAM lhint, ::radix::object* phint) 
   {
      ::userex::pane_tab_view::on_update(pviewSender, lhint, phint);

   }


   void pane_view::on_create_view(view_data * pviewdata)
   {
      switch(pviewdata->m_id)
      {
      case PaneViewContextMenu:
         /*{
            devedgeFrontDoc * pdoc = (devedgeFrontDoc *) (dynamic_cast < application * > (((BaseFrameWnd *) GetParentFrame())->m_papp))->m_ptemplateFront->OpenDocumentFile("http://localhost:10011/");
            if(pdoc != NULL)
            {
               POSITION pos = pdoc->GetFirstViewPosition();
               BaseView * pview = pdoc->GetNextView(pos);
               if(pview != NULL)
               {
                  BaseFrameWnd * pframe = (BaseFrameWnd *) pview->GetParentFrame();
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
         }*/
            break;
      
   /*         CreateContext cc;
            cc.m_pCurrentDoc = GetDocument();
            cc.m_pNewViewClass =  RUNTIME_CLASS(BaseWndMenuListView);

            BaseView * pview = dynamic_cast < BaseView * > (CreateView(&cc, 101, this));
            if(pview != NULL)
            {
               BaseWndMenuListView * pmenuview = (BaseWndMenuListView *) pview;
               pmenuview->m_wnd.LoadMenu(IDR_POPUP_LYRICVIEW);
               pmenuview->m_wnd.m_bAutoClose = false;
               pviewdata = new ViewData();
               pviewdata->m_eview = eview;
               pviewdata->m_pdoc = GetDocument();
               pviewdata->m_pwnd = pview;
            }*/
      case PaneViewDevEdge:
         {
            create_context cc;
            cc.m_pCurrentDoc = get_document();
            cc.m_typeinfoNewView =  typeid(alarm::view);

            ::userbase::view * pview = dynamic_cast < ::userbase::view * > (create_view(&cc, this, 101));
            if(pview != NULL)
            {
               pviewdata->m_pdoc = get_document();
               pviewdata->m_pwnd = pview;
            }
         }
         break;
      case PaneViewFileManager:
         {
            ::filemanager::document * pdoc = Application.GetStdFileManagerTemplate()->OpenChild(false, true);
            if(pdoc != NULL)
            {
               ::view * pview = pdoc->get_view();
               if(pview != NULL)
               {
                  userbase::frame_window * pframe = dynamic_cast < userbase::frame_window * > (pview->GetParentFrame());
                  if(pframe != NULL)
                  {
                     pviewdata->m_pdoc = pdoc;
                     pviewdata->m_pwnd = pframe;

                  }
               }
            }
         }
         break;
      case PaneViewByWeekday:
         {
            ::alatel::document * pdoc = dynamic_cast < ::alatel::document * > (Application.m_ptemplateAlatelByWeekday->open_document_file(NULL, true));
            if(pdoc != NULL)
            {
               ::alatel::week_view * pview = dynamic_cast < alatel::week_view * > (pdoc->get_view());
               if(pview != NULL)
               {
                  simple_frame_window * pframe = dynamic_cast < simple_frame_window * > (pview->GetParentFrame());
                  if(pframe != NULL)
                  {
                     pviewdata->m_pdoc = pdoc;
                     pviewdata->m_pwnd = pframe;
                  }
               }
               pview->create_views();
            }
         }
         break;

      case PaneViewAlarmTest:
         {
            ::alatel::document * pdoc = dynamic_cast < ::alatel::document * > (Application.m_ptemplateAlatel->open_document_file(NULL, true));
            if(pdoc != NULL)
            {
               ::view * pview = pdoc->get_view();
               if(pview != NULL)
               {
                  simple_frame_window * pframe = dynamic_cast < simple_frame_window * > (pview->GetParentFrame());
                  if(pframe != NULL)
                  {
                     pviewdata->m_pdoc = pdoc;
                     pviewdata->m_pwnd = pframe;
                  }
               }
            }
            pdoc = dynamic_cast < ::alatel::document * > (Application.m_ptemplateAlatel->open_document_file(NULL));
            if(pdoc != NULL)
            {
               ::view * pview = pdoc->get_view();
               if(pview != NULL)
               {
                  alatel::frame * pframe = dynamic_cast < alatel::frame * > (pview->GetParentFrame());
                  if(pframe != NULL)
                  {
                     pframe->alatel_fullscreen();

                  }
               }
            }
         }
         break;
      default:
         ASSERT(FALSE);
         break;
      }
   }


   void pane_view::_001InstallMessageHandling(user::win::message::dispatch * pinterface)
   {
      ::userex::pane_tab_view::_001InstallMessageHandling(pinterface);

      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &::alarm::pane_view::_001OnCreate);
   }

} // namespace alarm