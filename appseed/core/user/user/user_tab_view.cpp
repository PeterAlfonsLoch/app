#include "framework.h"


namespace user
{


   tab_view::tab_view(sp(::base::application) papp) :
      element(papp),
      ::user::tab(papp),
      place_holder_container(papp)
   {

      get_data()->m_pcallback       = this;
      m_pdroptargetwindow           = NULL;
      m_pviewdata                   = NULL;
      m_pviewdataOld                = NULL;

   }


   tab_view::~tab_view()
   {
   }

   #ifdef DEBUG
   void tab_view::assert_valid() const
   {
      impact::assert_valid();
   }

   void tab_view::dump(dump_context & dumpcontext) const
   {
      impact::dump(dumpcontext);
   }
   #endif //DEBUG


   void tab_view::_001OnCreate(signal_details * pobj)
   {
//      SCAST_PTR(::message::create, pcreate, pobj)
      if(pobj->previous())
         return;
   }


   void tab_view::on_update(sp(::user::impact) pSender, LPARAM lHint, object* pHint)
   {

      if(m_pviewcreator != NULL)
      {

         m_pviewcreator->on_update(get_document(), pSender, lHint, pHint);

      }

      impact::on_update(pSender, lHint, pHint);

   }

   void tab_view::_001OnSetFocus(signal_details * pobj)
   {

      UNREFERENCED_PARAMETER(pobj);

      if(get_view_uie() != NULL)
      {
         get_view_uie()->SetFocus();
      }

   }

   bool tab_view::pre_create_window(CREATESTRUCT& cs)
   {
      cs.dwExStyle &= ~WS_EX_CLIENTEDGE;

      return impact::pre_create_window(cs);
   }

   void tab_view::rotate()
   {
      index iSel = _001GetSel();

      if(iSel < 0)
         iSel = 0;
      else
         iSel++;

      if(iSel >= _001GetPaneCount())
         iSel = 0;

      if(iSel >= _001GetPaneCount())
         return;

      _001SetSel(iSel);

   }

   void tab_view::_001OnMenuMessage(signal_details * pobj)
   {
      SCAST_PTR(::message::base, pbase, pobj)
      if(pbase->m_wparam == 0 && pbase->m_lparam == 0)
      {
         set_cur_tab_by_id(m_pviewdataOld->m_id);
      }
   }

   void tab_view::install_message_handling(::message::dispatch * pinterface)
   {
      impact::install_message_handling(pinterface);
      ::user::tab::install_message_handling(pinterface);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &tab_view::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_USER + 1122  , pinterface, this, &tab_view::_001OnMenuMessage);
      IGUI_WIN_MSG_LINK(WM_SETFOCUS, pinterface, this, &tab_view::_001OnSetFocus);
   }


   void tab_view::_001OnTabClick(int32_t iTab)
   {
      _001SetSel(iTab);
      layout();
   }


   void tab_view::_001OnDropTab(int32_t iPane, e_position eposition)
   {
      sp(::user::interaction) pwnd1 = ensure(::user::tab::get_id_by_tab(::user::tab::_001GetSel()))->m_pwnd;
      sp(::user::interaction) pwnd2 = ensure(::user::tab::get_id_by_tab(iPane))->m_pwnd;
      ::user::split_view * psplitview = dynamic_cast < ::user::split_view * > (impact::create_view(System.type_info < ::user::split_view > (), get_document(), this, 100).m_p);
      if(eposition == position_top || eposition == position_bottom)
      {
         psplitview->SetSplitOrientation(orientation_horizontal);
      }
      else
      {
         psplitview->SetSplitOrientation(orientation_vertical);
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
      psplitview->set_position_rate(0, 0.5);

      id id1 = ::user::tab::get_id_by_tab(::user::tab::_001GetSel());
      id id2 = ::user::tab::get_id_by_tab(iPane);

      pane * ppane1 = get_pane_by_id(id1);
      pane * ppane2 = get_pane_by_id(id2);

      string strName1 = ppane1->m_istrTitleEx;
      string strName2 = ppane2->m_istrTitleEx;

      remove_tab_by_id(id1);
      remove_tab_by_id(id2);

      id id3 = var(id1).get_string() + "-" + var(id2).get_string();

      add_tab(strName1 + "/" + strName2, id3);

      ::user::view_creator_data * pcreatordata = m_pviewcreator->allocate(id3);

      pcreatordata->m_pwnd = psplitview;

      /*m_pviewcreator->m_viewmap[::user::tab::get_id_by_tab(::user::tab::_001GetSel())]->m_pwnd            = psplitview;
      m_pviewcreator->m_viewmap[::user::tab::get_id_by_tab(::user::tab::_001GetSel())]->m_idSplit         = m_pviewcreator->m_viewmap[::user::tab::get_id_by_tab(::user::tab::_001GetSel())]->m_id;
      m_pviewcreator->m_viewmap[::user::tab::get_id_by_tab(iPane)]->m_idSplit                             = m_pviewcreator->m_viewmap[::user::tab::get_id_by_tab(::user::tab::_001GetSel())]->m_id;
      m_pviewcreator->m_viewmap[::user::tab::get_id_by_tab(::user::tab::_001GetSel())]->m_bTabSplitSwap   = bSwap;*/

      ::user::tab::layout();
      get_data()->m_iDragTab = -1;
      get_data()->m_bDrag = false;
   }

   sp(::user::interaction) tab_view::_001GetTabWnd(int32_t iTab)
   {
      if(m_pviewcreator == NULL)
         return NULL;
      if(m_pviewcreator->get(::user::tab::get_id_by_tab(iTab)) != NULL)
      {
         return m_pviewcreator->get(::user::tab::get_id_by_tab(iTab))->m_pwnd;
      }
      else
      {
         return NULL;
      }
   }




   void tab_view::_001DropTargetWindowInitialize(::user::tab * pinterface)
   {
      ensure_tab_by_id(::user::tab::get_id_by_tab(pinterface->get_data()->m_iDragTab));
      m_pdroptargetwindow = new tab_drop_target_window(this, (int32_t) pinterface->get_data()->m_iDragTab);
      rect rect;
      rect = pinterface->get_data()->m_rectTabClient;
      pinterface->ClientToScreen(&rect);
      m_pdroptargetwindow->CreateEx(0, NULL, NULL, 0, rect, NULL, id());
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
         //System.remove_frame(m_pdroptargetwindow);
         //m_pdroptargetwindow->DestroyWindow();
         //m_pdroptargetwindow = NULL;
      }
   }



   void tab_view::_001OnShowTab(tab * ptab)
   {
      if(ptab == this)
      {
         on_show_view();
      }
   }

   void tab_view::on_show_view()
   {

      id id = get_id_by_tab(_001GetSel(), false);
      class id idSplit;
      ::user::view_creator_data * pcreatordata = ensure(id);

      index iTab = ::user::tab::get_tab_by_id(id);

      if(pcreatordata != NULL)
      {
         if(iTab >= 0)
         {
            if(pcreatordata->m_pholder != NULL)
            {
               get_data()->m_panea[iTab].m_pholder = pcreatordata->m_pholder;
            }
            else if(pcreatordata->m_pwnd != NULL)
            {
               if(get_tab_holder(iTab) == NULL)
               {
                  get_data()->m_panea[iTab].m_pholder = place(pcreatordata->m_pwnd);
               }
               else
               {
                  get_data()->m_panea[iTab].m_pholder->m_uiptraHold.remove_all();
                  get_data()->m_panea[iTab].m_pholder->hold(pcreatordata->m_pwnd);
               }
            }
            else
            {
               get_data()->m_panea[iTab].m_pholder = get_new_place_holder();
            }
         }
         if(pcreatordata->m_strTitle.has_char())
         {
            get_data()->m_panea[_001GetSel()].m_istrTitleEx = pcreatordata->m_strTitle;
         }
         idSplit = pcreatordata->m_idSplit;
      }
      /*
      if(idSplit.has_char())
      {
         ::user::split_view * psplitview = dynamic_cast < ::user::split_view * >
            (m_pviewcreator->m_viewmap[idSplit]->m_pwnd);
         bool bSwap = m_pviewcreator->m_viewmap[idSplit]->m_bTabSplitSwap;
         if(bSwap)
         {
            m_pviewcreator->m_viewmap[idSplit]->m_pwnd =
               psplitview->_001GetPane(1);

         }
         else
         {
            m_pviewcreator->m_viewmap[idSplit]->m_pwnd =
               psplitview->_001GetPane(0);
         }
         psplitview->_001GetPane(0)->SetParent(this);
         psplitview->_001GetPane(1)->SetParent(this);
         m_pviewcreator->m_viewmap[psplitview->get_pane_id(0)]->m_idSplit.is_empty();
         m_pviewcreator->m_viewmap[psplitview->get_pane_id(1)]->m_idSplit.is_empty();
         psplitview->ShowWindow(SW_HIDE);
         psplitview->ModifyStyle(WS_CHILD, 0, 0);
         psplitview->SetParent(NULL);
         psplitview->DestroyWindow();
      }*/
      if(pcreatordata != m_pviewdata)
      {
         m_pviewdataOld = m_pviewdata;
         m_pviewdata = pcreatordata;
         if(m_pviewdata->m_eflag.is_signalized(::user::view_creator_data::flag_hide_all_others_on_show))
         {
            ::user::view_creator::view_map::pair * ppair = m_pviewcreator->m_viewmap.PGetFirstAssoc();
            while(ppair != NULL)
            {
               try
               {
                  if(ppair->m_element2 != m_pviewdata)
                  {
                     if(ppair->m_element2->m_pholder != NULL)
                     {
                        ppair->m_element2->m_pholder->ShowWindow(SW_HIDE);
                     }
                  }
               }
               catch(...)
               {
               }
               ppair = m_pviewcreator->m_viewmap.PGetNextAssoc(ppair);
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

      if(m_pviewcreator != NULL && m_pviewcreator != dynamic_cast < ::user::view_creator * > (this))
      {
         m_pviewcreator->on_show_view();
      }

      if(m_pviewdata != NULL && m_pviewdata->m_pwnd != NULL)
      {
         m_pviewdata->m_pwnd->UpdateWindow();
         m_pviewdata->m_pwnd->SetFocus();
      }

      ((GetParentFrame()))->_001RedrawWindow();

      GetParentFrame()->SetActiveView(this);

   }

   void tab_view::ensure_tab_by_id(id id)
   {
      ensure(id);
   }

   ::user::view_creator_data * tab_view::ensure(id id)
   {
      if(m_pviewcreator == NULL)
         return NULL;
      if(get_tab_by_id(id) == -1)
      {
         ::user::tab::add_tab("", id);
      }
      ::user::view_creator_data * pcreatordata = m_pviewcreator->::user::view_creator::ensure(id);
      if(pcreatordata != NULL)
      {
         /*if(pcreatordata->m_pwnd != NULL)
         {
            pcreatordata->m_pwnd->SetParent(this);
            pcreatordata->m_pwnd->ModifyStyle(0, WS_CHILD, NULL);
         }*/
         pane * ppane = get_pane_by_id(id);
         if(ppane != NULL)
         {
            if(pcreatordata->m_strTitle.has_char())
            {
               ppane->m_istrTitleEx = pcreatordata->m_strTitle;
            }
            if(ppane != NULL)
            {
               ppane->m_pholder = pcreatordata->m_pholder;
            }
         }
      }
      on_change_pane_count();
      return pcreatordata;
   }

   id tab_view::get_view_id()
   {
      if(m_pviewdata == NULL)
         return ::base::system::idEmpty;
      return m_pviewdata->m_id;
   }

   ::user::view_creator_data * tab_view::get_view_creator_data()
   {
      return m_pviewdata;
   }

   sp(::user::interaction) tab_view::get_view_uie()
   {
      ::user::view_creator_data * pcreatordata = get_view_creator_data();
      if(pcreatordata == NULL)
         return NULL;
      if(pcreatordata->m_pwnd != NULL)
         return pcreatordata->m_pwnd;
      if(pcreatordata->m_pholder != NULL && pcreatordata->m_pholder->m_uiptraHold.get_count() == 1)
         return pcreatordata->m_pholder->m_uiptraHold(0);
      return NULL;
   }

   sp(::user::document) tab_view::get_view_document()
   {
      if(m_pviewdata == NULL)
         return NULL;
      return m_pviewdata->m_pdoc;
   }

   void tab_view::_000OnDraw(::draw2d::graphics * pdc)
   {
      if(!m_bVisible)
         return;
      _001DrawChildren(pdc);
      _001DrawThis(pdc);
   }

   bool tab_view::_001OnCmdMsg(::base::cmd_msg * pcmdmsg)
   {
      if(!handle(pcmdmsg))
         return false;
      if(get_view_uie() != NULL)
         if(get_view_uie()->_001OnCmdMsg(pcmdmsg))
            return true;
      return impact::_001OnCmdMsg(pcmdmsg);
   }

   void tab_view::set_view_creator(::user::view_creator * pviewcreator)
   {

      m_pviewcreator = pviewcreator;

      if(m_pviewcreator != NULL)
      {
         m_pviewcreator->m_pviewcontainer = this;
      }

   }

   ::user::view_creator * tab_view::get_view_creator()
   {
      return m_pviewcreator;
   }

   tab_drop_target_window::tab_drop_target_window(::user::tab * ptab, int32_t iPane) :
      element(ptab->get_app())
   {
      m_ptab            = ptab;
      m_iPane           = iPane;
   }

   tab_drop_target_window::~tab_drop_target_window()
   {
   }

   void tab_drop_target_window::install_message_handling(::message::dispatch * pinterface)
   {
      ::user::interaction::install_message_handling(pinterface);
      IGUI_WIN_MSG_LINK(WM_LBUTTONUP, pinterface, this, &tab_drop_target_window::_001OnLButtonUp);
   }

   void tab_drop_target_window::_001OnDraw(::draw2d::graphics * pdc)
   {
      class imaging & imaging = System.visual().imaging();

      COLORREF crBorder = RGB(127, 127, 80);
      COLORREF crBorderSel = RGB(40, 40, 20);

      point ptCursor;
      session().get_cursor_pos(&ptCursor);
      ScreenToClient(&ptCursor);
      e_position epositionDrag = m_ptab->DragHitTest(ptCursor);
      rect rectTop;
      m_ptab->GetDragRect(rectTop, position_top);
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
      m_ptab->GetDragRect(rectBottom, position_bottom);
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
      m_ptab->GetDragRect(rectRight, position_right);
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
      m_ptab->GetDragRect(rectLeft, position_left);
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
         m_ptab->GetDragRect(rectSel, epositionDrag);
         pdc->Draw3dRect(rectSel, crBorderSel, crBorderSel);
      }

   }

   void tab_drop_target_window::_001OnLButtonUp(signal_details * pobj)
   {
      SCAST_PTR(::message::mouse, pmouse, pobj);

      e_position eposition = m_ptab->DragHitTest(pmouse->m_pt);

      m_ptab->_001OnDropTab(m_iPane, eposition);

      ShowWindow(SW_HIDE);

      DestroyWindow();

      delete this;

      pobj->m_bRet = true;

   }


} // namespace user
