#include "StdAfx.h"

namespace userbase
{

   tab_view::tab_view(::ca::application * papp) :
      ca(papp),
      view(papp),
      ::user::tab(papp),
      place_holder_container(papp)
   {
      get_data()->m_pcallback   = this;
      m_pdroptargetwindow           = NULL;
      m_pcreateview                 = NULL;
      m_pviewdata                   = NULL;
      m_pviewdataOld                = NULL;
      m_etranslucency               = TranslucencyPresent;
   }

   tab_view::~tab_view()
   {
   }

   #ifdef _DEBUG
   void tab_view::assert_valid() const
   {
      view::assert_valid();
   }

   void tab_view::dump(dump_context & dumpcontext) const
   {
      view::dump(dumpcontext);
   }
   #endif //_DEBUG


   void tab_view::_001OnCreate(gen::signal_object * pobj) 
   {
//      SCAST_PTR(::user::win::message::create, pcreate, pobj)
      if(pobj->previous())
         return;
   }


   void tab_view::on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint) 
   {
      if(m_pcreateview != NULL)
      {
         POSITION pos = m_pcreateview->m_viewmap.get_start_position();
         ::user::create_view::view_data * pviewdata;
         id id;
         while(pos != NULL)
         {
            m_pcreateview->m_viewmap.get_next_assoc(pos, id, pviewdata);
            if(pviewdata->m_pdoc != NULL && pviewdata->m_pdoc != get_document() && 
               (pSender == NULL || pSender->get_document() != pviewdata->m_pdoc))
            {
               pviewdata->m_pdoc->update_all_views(pSender, lHint, pHint);
            }
         }
      }

    /*  if(pHint != NULL)
      {
         if(base < tab_view_update_hint >::bases(pHint))
         {
            tab_view_update_hint * puh = (tab_view_update_hint *) pHint;
            if(puh->is_type_of(tab_view_update_hint::type_get_tab))
            {
               puh->m_id = get_cur_tab();
            }
            else if(puh->is_type_of(tab_view_update_hint::type_set_tab))
            {
               set_cur_tab(puh->m_id);
            }
         }
      }*/
         /*if(pHint != NULL)
      {
         if(base < tab_view_update_hint >::bases(pHint))
         {
            tab_view_update_hint * puh = (tab_view_update_hint * ) pHint;
            if(puh->is_type_of(tab_view_update_hint::TypeOnShowTab))
            {
               ::user::tab::set_cur_tab_by_id(puh->m_id);
            }
         }
      }*/
      view::on_update(pSender, lHint, pHint);
   }

   void tab_view::_001OnSetFocus(gen::signal_object * pobj) 
   {
      UNREFERENCED_PARAMETER(pobj);
      if(m_pcreateview != NULL)
      {
         ::user::create_view::view_data * pviewdata = m_pcreateview->get(get_cur_tab_id());
         if(pviewdata != NULL)
         {
            if(pviewdata->m_pwnd != NULL)
            {
               pviewdata->m_pwnd->SetFocus();
            }
         }
      }

   }

   BOOL tab_view::PreCreateWindow(CREATESTRUCT& cs) 
   {
      cs.dwExStyle &= ~WS_EX_CLIENTEDGE;   

      return view::PreCreateWindow(cs);
   }

   void tab_view::rotate()
   {
   /*   EPaneView eview = GetViewId();
      EPaneView eviewNew = PaneViewDevEdge;
      switch(eview)
      {
      case PaneViewDevEdge:
         eviewNew = PaneViewFileManager;
         break;
      case PaneViewFileManager:
         eviewNew = PaneViewPlaylist;
         break;
      case PaneViewPlaylist:
         eviewNew = PaneViewMediaLibrary;
         break;
      case PaneViewMediaLibrary:
         eviewNew = PaneViewAudioControl;
         break;
      case PaneViewAudioControl:
         eviewNew = PaneViewDevEdge;
         break;
      case PaneViewOptions:
         eviewNew = PaneViewDevEdge;
         break;
      default:
         ASSERT(FALSE);
         break;
      }

      ShowView(eviewNew);*/
   }

   void tab_view::_001OnMenuMessage(gen::signal_object * pobj)
   {
      SCAST_PTR(::user::win::message::base, pbase, pobj)
      if(pbase->m_wparam == 0 && pbase->m_lparam == 0)
      {
         set_cur_tab_by_id(m_pviewdataOld->m_id);
      }
   }

   void tab_view::_001InstallMessageHandling(::user::win::message::dispatch * pinterface)
   {
      view::_001InstallMessageHandling(pinterface);
      ::user::tab::_001InstallMessageHandling(pinterface);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &tab_view::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_USER + 1122  , pinterface, this, &tab_view::_001OnMenuMessage);
      IGUI_WIN_MSG_LINK(WM_SETFOCUS, pinterface, this, &tab_view::_001OnSetFocus);
   }


   void tab_view::_001OnTabClick(int iTab)
   {
      _001SetSel(iTab);
      layout();
   }


   void tab_view::_001OnDropTab(id id, e_position eposition)
   {
      ::user::interaction* pwnd1 = ensure_tab_by_id(::user::tab::get_id_by_tab(::user::tab::_001GetSel()))->m_pwnd;
      ::user::interaction* pwnd2 = ensure_tab_by_id(id)->m_pwnd;
      ::userbase::split_view * psplitview = dynamic_cast < ::userbase::split_view * > (view::create_view(typeid(::userbase::split_view), get_document(), this, 100));
      if(eposition == position_top || eposition == position_bottom)
      {
         psplitview->SetSplitOrientation(::userbase::split_layout::orientation_horizontal);
      }
      else
      {
         psplitview->SetSplitOrientation(::userbase::split_layout::orientation_vertical);
      }
      psplitview->SetPaneCount(2);
      bool bSwap;
      if(eposition == position_top || eposition == position_left)
      {
         psplitview->SetPane(0, pwnd2, false);
         psplitview->SetPane(1, pwnd1, false);
         bSwap = true;
      }
      else
      {
         psplitview->SetPane(0, pwnd1, false);
         psplitview->SetPane(1, pwnd2, false);
         bSwap = false;
      }
      //if(eposition == position_top || eposition == position_bottom)
      {
         psplitview->set_position_rate(0, 0.33);
      }
      //else
      {
        // psplitview->set_position_rate(0, ::user::tab::m_rectTabClient.width() / 2);
      }
      m_pcreateview->m_viewmap[::user::tab::get_id_by_tab(::user::tab::_001GetSel())]->m_pwnd = psplitview;
      m_pcreateview->m_viewmap[::user::tab::get_id_by_tab(::user::tab::_001GetSel())]->m_idSplit = 
         m_pcreateview->m_viewmap[::user::tab::get_id_by_tab(::user::tab::_001GetSel())]->m_id;
      m_pcreateview->m_viewmap[id]->m_idSplit = 
         m_pcreateview->m_viewmap[::user::tab::get_id_by_tab(::user::tab::_001GetSel())]->m_id;
      m_pcreateview->m_viewmap[::user::tab::get_id_by_tab(::user::tab::_001GetSel())]->m_bTabSplitSwap = 
         bSwap;
      ::user::tab::layout();
   }

   ::user::interaction * tab_view::_001GetTabWnd(int iTab)
   {
      if(m_pcreateview == NULL)
         return NULL;
      if(m_pcreateview->get(::user::tab::get_id_by_tab(iTab)) != NULL)
      {
         return m_pcreateview->get(::user::tab::get_id_by_tab(iTab))->m_pwnd;
      }
      else
      {
         return NULL;
      }
   }




   void tab_view::_001DropTargetWindowInitialize(::user::tab * pinterface)
   {
      ensure_tab_by_id(::user::tab::get_id_by_tab(pinterface->get_data()->m_iDragTab));
      m_pdroptargetwindow = new tab_drop_target_window(get_app());
      m_pdroptargetwindow->m_pinterface = pinterface;
      rect rect;
      rect = pinterface->get_data()->m_rectTabClient;
      pinterface->ClientToScreen(&rect);
      m_pdroptargetwindow->CreateEx(0, System.RegisterWndClass(NULL, 0, 0, 0), NULL, 0, rect, NULL, id());
      System.add_frame(m_pdroptargetwindow);
      m_pdroptargetwindow->ShowWindow(SW_SHOW);
   }

   void tab_view::_001DropTargetWindowRelay(::user::tab * pinterface)
   {
      UNREFERENCED_PARAMETER(pinterface);
      _001RedrawWindow();
   }

   void tab_view::_001DropTargetWindowFinalize(::user::tab * pinterface)
   {
      UNREFERENCED_PARAMETER(pinterface);
      if(m_pdroptargetwindow != NULL)
      {
         System.remove_frame(m_pdroptargetwindow);
         m_pdroptargetwindow->DestroyWindow();
         m_pdroptargetwindow = NULL;
      }
   }

   tab_drop_target_window::tab_drop_target_window(::ca::application * papp) :
      ca(papp)
   {
   }

   tab_drop_target_window::~tab_drop_target_window()
   {
   }

   void tab_drop_target_window::_001InstallMessageHandling(::user::win::message::dispatch * pinterface)
   {
      ::user::interaction::_001InstallMessageHandling(pinterface);
   }

   void tab_drop_target_window::_001OnDraw(::ca::graphics * pdc)
   {
      class imaging & imaging = System.imaging();

      COLORREF crBorder = RGB(127, 127, 80);
      COLORREF crBorderSel = RGB(40, 40, 20);
      
      point ptCursor;
      System.get_cursor_pos(&ptCursor);
      ScreenToClient(&ptCursor);
      e_position epositionDrag = m_pinterface->DragHitTest(ptCursor);
      rect rectTop;
      m_pinterface->GetDragRect(rectTop, position_top);
      COLORREF crTop;
      if(rectTop.contains(ptCursor))
      {
         crTop = RGB(255, 230, 155);
      }
      else
      {
         crTop = RGB(150, 200, 255);
      }
      rect rectBottom;
      m_pinterface->GetDragRect(rectBottom, position_bottom);
      COLORREF crBottom;
      if(rectBottom.contains(ptCursor))
      {
         crBottom = RGB(255, 230, 155);
      }
      else
      {
         crBottom = RGB(150, 200, 255);
      }
      rect rectRight;
      m_pinterface->GetDragRect(rectRight, position_right);
      COLORREF crRight;
      if(rectRight.contains(ptCursor))
      {
         crRight = RGB(255, 230, 155);
      }
      else
      {
         crRight = RGB(150, 200, 255);
      }
      rect rectLeft;
      m_pinterface->GetDragRect(rectLeft, position_left);
      COLORREF crLeft;
      if(rectLeft.contains(ptCursor))
      {
         crLeft = RGB(255, 230, 155);
      }
      else
      {
         crLeft = RGB(150, 200, 255);
      }
      imaging.color_blend(
         pdc,
         rectTop,
         crTop,
         127);
      imaging.color_blend(
         pdc,
         rectLeft,
         crLeft,
         127);
      imaging.color_blend(
         pdc,
         rectRight,
         crRight,
         127);
      imaging.color_blend(
         pdc,
         rectBottom,
         crBottom,
         127);
      pdc->Draw3dRect(rectTop, crBorder, crBorder);
      pdc->Draw3dRect(rectLeft, crBorder, crBorder);
      pdc->Draw3dRect(rectRight, crBorder, crBorder);
      pdc->Draw3dRect(rectBottom, crBorder, crBorder);
      
      if(epositionDrag != position_none)
      {
         rect rectSel;
         m_pinterface->GetDragRect(rectSel, epositionDrag);
         pdc->Draw3dRect(rectSel, crBorderSel, crBorderSel);
      }

   }


   void tab_view::on_show_view(tab * ptab)
   {
      if(ptab == this)
      {
         on_show_view();
      }
   }

   void tab_view::on_show_view()
   {

      id id = get_id_by_tab(_001GetSel());
      class id idSplit;
      ::user::create_view::view_data * pviewdata = m_pcreateview->ensure(id);
      ASSERT(pviewdata != NULL);
        
       int iTab = ::user::tab::get_tab_by_id(id);

      if(pviewdata != NULL)
      {
         
         if(iTab >= 0 && pviewdata->m_pwnd != NULL)
         {
            if(get_tab_holder(iTab) == NULL)
            {
               get_data()->m_panea[iTab].m_pholder = hold(pviewdata->m_pwnd);
            }
            else
            {
               get_data()->m_panea[iTab].m_pholder->m_uiptraHold.remove_all();
               get_data()->m_panea[iTab].m_pholder->hold(pviewdata->m_pwnd);
            }
         }
         if(pviewdata->m_strTitle.has_char())
         {
            get_data()->m_panea[_001GetSel()].m_strTitleEx = pviewdata->m_strTitle;
         }
         idSplit = pviewdata->m_idSplit;
      }
      /*
      if(idSplit.has_char())
      {
         ::userbase::split_view * psplitview = dynamic_cast < ::userbase::split_view * > 
            (m_pcreateview->m_viewmap[idSplit]->m_pwnd);
         bool bSwap = m_pcreateview->m_viewmap[idSplit]->m_bTabSplitSwap;
         if(bSwap)
         {
            m_pcreateview->m_viewmap[idSplit]->m_pwnd =
               psplitview->_001GetPane(1);
            
         }
         else
         {
            m_pcreateview->m_viewmap[idSplit]->m_pwnd =
               psplitview->_001GetPane(0);
         }
         psplitview->_001GetPane(0)->SetParent(this);
         psplitview->_001GetPane(1)->SetParent(this);
         m_pcreateview->m_viewmap[psplitview->_001GetPaneId(0)]->m_idSplit.is_empty();
         m_pcreateview->m_viewmap[psplitview->_001GetPaneId(1)]->m_idSplit.is_empty();
         psplitview->ShowWindow(SW_HIDE);
         psplitview->ModifyStyle(WS_CHILD, 0, 0);
         psplitview->SetParent(NULL);
         psplitview->DestroyWindow();
      }*/
      if(pviewdata != m_pviewdata)
      {
         m_pviewdataOld = m_pviewdata;
         m_pviewdata = pviewdata;
         if(m_pviewdataOld != NULL
            // heuristics
            && m_pviewdata->m_pwnd != NULL
            && (!m_pviewdata->m_pwnd->_001HasTranslucency()
            || m_pviewdata->m_eflag.is_signalized(::user::create_view::view_data::flag_hide_all_others_on_show)))
         {
            if(m_pviewdataOld->m_pwnd != NULL)
            {
               m_pviewdataOld->m_pwnd->ShowWindow(SW_HIDE);
            }
         }
      }
      rect rectClient;
      GetClientRect(rectClient);
      if(!rectClient.is_null())
      {
         layout();
      }
      if(m_pviewdata != NULL)
      {
         if(m_pviewdata->m_pwnd != NULL)
         {
            m_pviewdata->m_pwnd->ShowWindow(SW_SHOW);
         }
      }
      if(m_pcreateview != NULL && m_pcreateview != dynamic_cast < ::user::create_view * > (this))
      {
         m_pcreateview->on_show_view();
      }
      ::user::tab::on_show_view();
      if(m_pviewdata != NULL && m_pviewdata->m_pwnd != NULL)
      {
         m_pviewdata->m_pwnd->UpdateWindow();
         m_pviewdata->m_pwnd->SetFocus();
      }

      (dynamic_cast < userbase::frame_window * > (GetParentFrame()))->_001RedrawWindow();

      GetParentFrame()->SetActiveView(this);

   }

   ::user::create_view::view_data * tab_view::ensure_tab_by_id(id id)
   {
      ::user::create_view::view_data * pview = m_pcreateview->ensure(id);
      if(pview != NULL)
      {
         pview->m_pwnd->SetParent(this);
         pview->m_pwnd->ModifyStyle(0, WS_CHILD, NULL);
         if(get_tab_by_id(id) == -1)
         {
            ::user::tab::add_tab("", id);
         }
      }
      return pview;
   }

   id tab_view::get_view_id()
   {
      if(m_pviewdata == NULL)
         return ::ca::system::idEmpty;
      return m_pviewdata->m_id;
   }


   ::user::interaction * tab_view::get_view_uie()
   {
      if(m_pviewdata == NULL)
         return NULL;
      return m_pviewdata->m_pwnd;
   }

   ::document * tab_view::get_view_document()
   {
      if(m_pviewdata == NULL)
         return NULL;
      return m_pviewdata->m_pdoc;
   }

   ::user::create_view * tab_view::get_create_view()
   {
      return m_pcreateview;
   }

   void tab_view::set_create_view(::user::create_view * pcreateview)
   {
      m_pcreateview              = pcreateview;
      if(m_pcreateview != NULL)
      {
         m_pcreateview->m_pgetview  = this;
      }
   }


   void tab_view::_000OnDraw(::ca::graphics * pdc)
   {
      if(!m_bVisible)
         return;
      _001DrawChildren(pdc);
      _001DrawThis(pdc);
   }

   bool tab_view::_001OnCmdMsg(BaseCmdMsg * pcmdmsg)
   {
      if(!handle(pcmdmsg))
         return false;
      if(get_view_uie() != NULL)
         if(get_view_uie()->_001OnCmdMsg(pcmdmsg))
            return true;
      return view::_001OnCmdMsg(pcmdmsg);
   }

} // namespace userbase