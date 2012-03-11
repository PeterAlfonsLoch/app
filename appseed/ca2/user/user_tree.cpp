#include "StdAfx.h"


namespace user
{


   void tree::_001DrawItem(tree_draw_item & data)
   {
      rect rect;

      tree * ptree = this;
      ex1::tree_item * pitem = data.m_pitem;

      image_list * pimagelistItem = data.m_pitem->get_image_list();
      image_list * pimagelistTree = ptree == NULL ? NULL : ptree->m_pimagelist;

      bool bSelected    = ptree->is_selected(pitem);
      bool bHover       = ptree->is_hover(pitem);

      if(ptree != NULL && pimagelistTree != NULL && data.m_pitem->m_dwState & ::ex1::tree_item_state_expandable)
      {

         _001GetItemElementRect(rect, data, tree_element_expand_box);

         int iImage;
         if(data.m_pitem->m_dwState & ::ex1::tree_item_state_expanded)
         {
            iImage = (int) ptree->m_iImageCollapse;
         }
         else
         {
            iImage = (int) ptree->m_iImageExpand;
         }
         pimagelistTree->draw(data.m_pdc, iImage, rect.top_left(), 0);
      }


//      gen::savings & savings = System.savings();
      if(bSelected) // selected
      {
         if(System.savings().is_trying_to_save(gen::resource_processing))
         {
            data.m_pdc->FillSolidRect(
               data.m_rect,
               RGB(96,96,96));
         }
         else
         {
            class rect rectUnion;
            _001GetItemElementRect(
               rect,
               data,
               tree_element_image);
            rectUnion = rect;
            _001GetItemElementRect(
               rect,
               data,
               tree_element_text);
            rectUnion.unite(rect, rectUnion);
            class imaging & imaging = System.imaging();
            COLORREF crTranslucid = RGB(0, 0, 0);
            imaging.color_blend(
                   data.m_pdc,
                   rectUnion.left, rectUnion.top,
                   rectUnion.width(), rectUnion.height(),
                   crTranslucid, 127);
         }
         if(bHover)
         {
            data.m_pdc->set_color(m_crTextSelectedHighlight);
         }
         else
         {
            data.m_pdc->set_color(m_crTextSelected);
         }
      }
      else
      {
         if(bHover)
         {
            data.m_pdc->set_color(m_crTextHighlight);
         }
         else
         {
            data.m_pdc->set_color(m_crText);
         }
      }

      if(pimagelistItem != NULL)
      {
         int iImage = (int) data.m_pitem->get_image();
         if(iImage >= 0)
         {
            _001GetItemElementRect(
               rect,
               data,
               tree_element_image);
            pimagelistItem->draw(
               data.m_pdc,
               iImage,
               rect.top_left(),
               0);
         }
      }

      string strItem = data.m_pitem->get_text();

      if(strItem.has_char() && _001GetItemElementRect(rect, data, tree_element_text))
      {
         ::ca::font_sp font(get_app());
         font->operator=(*System.font_central().GetListCtrlFont());
         font->set_bold();
         data.m_pdc->set_font(font);
         m_dcextension._DrawText(data.m_pdc, strItem, &rect, DT_LEFT | DT_BOTTOM);
      }
   }


   tree::tree(::ca::application * papp) :
      ca(papp),
      ::user::scroll_view(papp),
      ex1::tree(papp),
      m_dcextension(papp)
   {
      m_pitemFirstVisible        = NULL;
      m_iFirstVisibleItemLevel   = 0;
      m_pitemHover               = NULL;
      m_iClick                   = 0;
      m_iItemCount               = 0;
      m_crText                   = ARGB(255, 0, 0, 0);
      m_crTextSelected           = ARGB(255, 255, 255, 255);
      m_crTextHighlight          = ARGB(255, 102, 153, 255);
      m_crTextSelectedHighlight  = ARGB(255, 172, 213, 255);
   }

   tree::~tree()
   {
   }


   void tree::_001OnCreate(gen::signal_object * pobj)
   {
//      SCAST_PTR(::gen::message::create, pcreate, pobj)
      if(pobj->previous())
         return;

      if(!ex1::tree::initialize())
         throw simple_exception();

      m_pimagelist = new image_list(get_app());
      m_pimagelist->create(16, 16, 0, 10, 10);

      class rect rect;
      rect.null();

      if(IsWindowVisible())
      {
         RedrawWindow();
      }

   }

   //bool tree::_001DynamicGetItemData(BaseTreeItemData & itemdata, ex1::tree_path & itempath, int iValidateCount)
   //{
   /*   if(m_pdatainterface001 != NULL)
      {
         Carray < DWORD, DWORD > ida;
         Ex1TreeItemMetaData * pdata = _001StaticGetMetaData(itempath);
         if(pdata == NULL)
            return false;
         pdata->GetId001(ida);
         if(!m_pdatainterface001->_001GetItemData(itemdata, ida))
         {
            if(!_001StaticUpdateInfo(itempath, iValidateCount))
               return false;
         }
         pdata->UpdateProperExpandedUserMeta(m_pdatainterface001, iValidateCount);
      }
      else
      {
         // There is no valid data interface
         ASSERT(FALSE);
      }*/
     // return true;

      /*if(itempath.IsRoot())
         return false;
      while(!m_pdata->_001GetItemData(itemdata, itempath))
      {
         if(!_001StaticUpdateInfo(itempath, iValidateCount))
            return false;
      }
      return true;*/

   //}

   void tree::_001OnDrawBackground(::ca::graphics *pdc)
   {
      rect rectClient;
      GetClientRect(rectClient);

//      gen::savings & savings = System.savings();
      rect rectClientOffset = rectClient;

      rect rectClipBox;
      pdc->GetClipBox(rectClipBox);
      if(rectClipBox.is_null())
      {
         rectClipBox = rectClientOffset;
      }
      else
      {
         rectClipBox.intersect(rectClipBox, rectClientOffset);
      }

      class imaging & imaging = System.imaging();

      if(System.savings().is_trying_to_save(gen::resource_processing))
      {
         pdc->FillSolidRect(
            rectClipBox,
            GetSysColor(COLOR_WINDOW));
      }
      else
      {
         imaging.color_blend(
            pdc,
            rectClipBox,
            GetSysColor(COLOR_WINDOW),
            196);
      }
   }

   COLORREF tree::get_background_color()
   {
      return RGB(200, 255, 255);
   }

   void tree::_001OnDraw(::ca::graphics *pdc)
   {
      rect rectClient;

      GetClientRect(rectClient);

//      gen::savings & savings = System.savings();

///      ::ca::graphics * pDCBuffer = pdc;

      point ptOriginalViewportOrg = pdc->GetViewportOrg();

      rect rectClientOffset = rectClient;

      /*rect rectClipBox;
      pdc->GetClipBox(rectClipBox);
      if(rectClipBox.is_null())
      {
         rectClipBox = rectClientOffset;
      }
      else
      {
         rectClipBox.intersect(rectClipBox, rectClientOffset);
      }*/

//       class imaging & imaging = System.imaging();

      if(_001IsTranslucent())
      {
         class imaging & imaging = System.imaging();
         //_001DrawBackground(pdc, rectClipBox);
         imaging.color_blend(
            pdc,
            rectClient,
            get_background_color(),
            127);
      }
      else
      {
   //      if(m_pgdibuffer != NULL
   //         && !TwiHasTranslucency())
         {
   /*         ::ca::graphics * pdcBack = m_pgdibuffer->GetBuffer();
            if(pdcBack != NULL)
            {
               pdc->BitBlt(
                  rectClient.left,
                  rectClient.top,
                  rectClient.width(),
                  rectClient.height(),
                  pdcBack,
                  rectClient.left,
                  rectClient.top,
                  SRCCOPY);
            }*/
         }
         //else
         {
            //if(System.savings().is_trying_to_save(gen::resource_processing))
            {
               pdc->FillSolidRect(
                  rectClient,
                  get_background_color());
            }
   /*         else
            {
               imaging.color_blend(
                  pdc,
                  rectClipBox,
                  GetSysColor(COLOR_WINDOW),
                  196);
            }*/
   /*         if(m_pgdibuffer != NULL)
            {
               ::ca::graphics * pdcBack = m_pgdibuffer->GetBuffer();
               if(pdcBack != NULL)
               {
                  pdcBack->BitBlt(
                     rectClient.left,
                     rectClient.top,
                     rectClient.width(),
                     rectClient.height(),
                     pdc,
                     rectClient.left,
                     rectClient.top,
                     SRCCOPY);
               }
            }*/
         }
      }

      pdc->OffsetViewportOrg((int) -m_scrollinfo.m_ptScroll.x, (int) -(m_scrollinfo.m_ptScroll.y % _001GetItemHeight()));

   //   BaseTreeItemData itemdata;
/*      ex1::tree_path itempath;*/
      user::tree_draw_item drawitemdata;
      drawitemdata.m_pdc = pdc;
      drawitemdata.m_iIndentation = _001GetIndentation();
   //   drawitemdata.m_pdata = &itemdata;
//      drawitemdata.m_ppath = &itempath;
      drawitemdata.m_iItemHeight = 18;
      GetClientRect(drawitemdata.m_rectClient);

   //   _001OnDrawBackground(pdc);

      ::ex1::tree_item * pitem = m_pitemFirstVisible;




      index iLevel = m_iFirstVisibleItemLevel;
      index iItem = m_iFirstVisibleItemProperIndex;
      index iIndex = 0;


      for(;pitem != NULL; pitem = pitem->get_item(::ex1::TreeNavigationProperForward, &iLevel))
      {
         drawitemdata.m_pitem = pitem;
         drawitemdata.m_iItem = iItem;
         drawitemdata.m_rect = drawitemdata.m_rectClient;
         drawitemdata.m_rect.left = (LONG) (drawitemdata.m_iIndentation * iLevel);
         drawitemdata.m_rect.top += (LONG) (iIndex * drawitemdata.m_iItemHeight);
         drawitemdata.m_rect.bottom = (LONG) (drawitemdata.m_rect.top + drawitemdata.m_iItemHeight);
         drawitemdata.m_rect.right = m_iCurrentViewWidth;
         if(pitem->m_dwState & ::ex1::tree_item_state_selected)
         {
   //         drawitemdata.m_dwMetaData |= 1;
         }
         else
         {
     //       drawitemdata.m_dwMetaData &= ~1;
         }
         _001DrawItem(drawitemdata);
         iItem++;
         iIndex++;
      }
      /*int iValidateItemCount = 30;
      int iItem = 0;
      if(_001DynamicGetItemData(itemdata, m_itempathFirstVisible, iValidateItemCount))
      {
         m_iItemCount = m_pmetadataRoot->GetDescendantCount();
         itempath = m_itempathFirstVisible;
         while(true)
         {
            drawitemdata.m_iItem = iItem;
            iLevel = itempath.m_iaPath.get_size() - 1;
            drawitemdata.m_rect = drawitemdata.m_rectClient;
            drawitemdata.m_rect.left = drawitemdata.m_iIndentation * iLevel;
            drawitemdata.m_rect.top += iItem * drawitemdata.m_iItemHeight;
            drawitemdata.m_rect.bottom = drawitemdata.m_rect.top + drawitemdata.m_iItemHeight;
            Ex1TreeItemMetaData * pdata = _001StaticGetMetaData(itempath);
            if(pdata == m_pmetadataSelected)
            {
               itemdata.m_dwMetaData |= 1;
            }
            else
            {
               itemdata.m_dwMetaData &= ~1;
            }
            _001DrawItem(drawitemdata);
            iItem = _001StaticMoveNextItem(itempath, iItem);
            if(iItem < 0)
               break;
            if(!_001DynamicGetItemData(itemdata, itempath, iValidateItemCount))
               break;
            iValidateItemCount--;
         }
      }*/

   }



   index tree::_001GetIndentation()
   {
      return 24;
   }




   void tree::_001OnMouseMove(gen::signal_object * pobj)
   {
      track_mouse_leave();

      UpdateHover();
      pobj->m_bRet = true;
   }

   void tree::_001OnMouseLeave(gen::signal_object * pobj)
   {
      m_pitemHover = NULL;
      _001RedrawWindow();
      pobj->m_bRet = true;
   }

   void tree::_001OnLButtonDown(gen::signal_object * pobj)
   {
      SCAST_PTR(::gen::message::mouse, pmouse, pobj)
      /*if(System.get_focus_guie() != this)
      {
         System.set_active_guie(this);
      }*/
      pmouse->previous();
      pobj->m_bRet = true;
      pmouse->set_lresult(1);
   }

   void tree::_001OnLButtonDblClk(gen::signal_object * pobj)
   {
      SCAST_PTR(::gen::message::mouse, pmouse, pobj)
      m_iClick = 2;

      _001OnClick((UINT) pmouse->m_nFlags, pmouse->m_pt);
      ::ex1::tree_item * pitem;
      ::user::e_tree_element eelement;
      pitem = _001HitTest(pmouse->m_pt, eelement);
      if(pitem != NULL)
      {
         if(eelement == tree_element_expand_box ||
            eelement == tree_element_image ||
            eelement == tree_element_text)
         {
            _001ExpandItem(pitem, !(pitem->m_dwState & ::ex1::tree_item_state_expanded));
         }
      }


   /* trans   window_id wndidNotify = _001GetNotifyWnd();

      LRESULT lresult = 0;

      if(wndidNotify)
      {
         NMLISTVIEW nm;
         nm.hdr.idFrom = pwnd->GetDlgCtrlId();
         nm.hdr.code =   NM_DBLCLK;
         nm.hdr.hwndFrom = pwnd->GetSafeHwnd();
         lresult = ::SendMessage(
            wndidNotify,
            WM_NOTIFY,
            nm.hdr.idFrom,
            (LPARAM) &nm);


      }*/

   // trans   pobj->m_bRet = lresult != 0;
   }

   void tree::_001OnLButtonUp(gen::signal_object * pobj)
   {
      SCAST_PTR(::gen::message::mouse, pmouse, pobj)
      m_iClick++;
      m_uiLButtonUpFlags = (UINT) pmouse->m_nFlags;
      m_ptLButtonUp = pmouse->m_pt;
      SetTimer(TimerClick, 500, NULL);
      pobj->m_bRet = true;
      pmouse->set_lresult(1);
   }

   void tree::_001OnTimer(gen::signal_object * pobj)
   {
      SCAST_PTR(::gen::message::timer, ptimer, pobj)

//         return; //xxxtimer

      if(ptimer->m_nIDEvent == TimerHover)
      {
         UpdateHover();
      }
      else
      if(ptimer->m_nIDEvent == TimerClick)
      {
         KillTimer(TimerClick);
         if(m_iClick == 1)
         {
            m_iClick = 0;


            UINT nFlags = m_uiLButtonUpFlags;
            point point = m_ptLButtonUp;

            _001OnClick(nFlags, point);
   //xxx         TwiRedraw();
            ::ex1::tree_item * pitem;
            ::user::e_tree_element eelement;
            ScreenToClient(&point);
            pitem = _001HitTest(point, eelement);
            if(pitem != NULL)
            {
               if(eelement == tree_element_expand_box ||
                  eelement == tree_element_image ||
                  eelement == tree_element_text)
               {
                  _001ExpandItem(pitem, !(pitem->m_dwState & ::ex1::tree_item_state_expanded));
               }
               if(eelement == tree_element_image ||
                  eelement == tree_element_text)
               {
                  _001OnOpenItem(pitem);
               }
            }


   /* trans         window_id  wndidNotify = _001GetNotifyWnd();


            LRESULT lresult = 0;

            if(wndidNotify)
            {
               NMLISTVIEW nm;
               nm.hdr.idFrom = pwnd->GetDlgCtrlId();
               nm.hdr.code =   NM_CLICK;
               nm.hdr.hwndFrom = pwnd->GetSafeHwnd();
               lresult = ::SendMessage(
                  wndidNotify,
                  WM_NOTIFY,
                  nm.hdr.idFrom,
                  (LPARAM) &nm);


            }*/

         }
         else
         {
            m_iClick = 0;
         }


      }
   }

   /*window_id tree::_001GetNotifyWnd()
   {
      ::ca::window * pwnd = get_guie();

      window_id wndidNotify = pwnd->GetOwner()->GetSafeHwnd();
      if(wndidNotify == NULL)
         wndidNotify = pwnd->GetParent()->GetSafeHwnd();
      return wndidNotify;
   }*/

   void tree::_001OnClick(UINT uiFlags, point point)
   {
      UNREFERENCED_PARAMETER(point);
      if(uiFlags & MK_SHIFT)
      {
         if(uiFlags & MK_CONTROL)
         {
         }
      }
      else
      {

   //      Ex1TreeItemMetaData * pdata = _001HitTest(point);
   //      if(pdata != NULL)
   //      {
     //       m_pmetadataSelected = pdata;
      //   }
      }
   }

   ::ex1::tree_item * tree::_001HitTest(POINT pt, ::user::e_tree_element & eelement)
   {
      index iy = pt.y;

      index iItem = -1;

      index iItemHeight = _001GetItemHeight();

      if(iItemHeight != 0)
      {
         iItem = (int) ((iy + m_scrollinfo.m_ptScroll.y) / iItemHeight);
      }

      if(iItem < 0)
         return false;


   //   if(iItem >= _001StaticGetItemCount())
   //      return false;
      index iLevel;
      ::ex1::tree_item * pitem = get_proper_item(iItem, &iLevel);

      if(pitem == NULL)
         return NULL;

      index x = (int) (pt. x - _001GetIndentation() * iLevel + m_scrollinfo.m_ptScroll.x);
      if(x >= 0 && x < 16)
         eelement = tree_element_expand_box;
      if(x >= 18 && x < 34)
         eelement = tree_element_image;
      if(x >= 36)
         eelement = tree_element_text;

      return pitem;


   }

   int tree::_001GetItemHeight()
   {
      return 18;
   }

   void tree::install_message_handling(::gen::message::dispatch * pdispatch)
   {
      ::user::window_interface::install_message_handling(pdispatch);
      ::user::scroll_view::install_message_handling(pdispatch);
      IGUI_WIN_MSG_LINK(WM_CREATE        , pdispatch, this, &tree::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_LBUTTONDBLCLK , pdispatch, this, &tree::_001OnLButtonDblClk);
      IGUI_WIN_MSG_LINK(WM_LBUTTONUP     , pdispatch, this, &tree::_001OnLButtonUp);
      IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN   , pdispatch, this, &tree::_001OnLButtonDown);
      IGUI_WIN_MSG_LINK(WM_MOUSEMOVE     , pdispatch, this, &tree::_001OnMouseMove);
      IGUI_WIN_MSG_LINK(WM_MOUSELEAVE    , pdispatch, this, &tree::_001OnMouseLeave);
      IGUI_WIN_MSG_LINK(WM_HSCROLL       , pdispatch, this, &tree::_001OnHScroll);
      IGUI_WIN_MSG_LINK(WM_VSCROLL       , pdispatch, this, &tree::_001OnVScroll);
      IGUI_WIN_MSG_LINK(WM_TIMER         , pdispatch, this, &tree::_001OnTimer);
   }

   void tree::_001GetViewRect(LPRECT lprect)
   {

      rect rectClient;
      GetClientRect(rectClient);
      lprect->left = 0;
      lprect->top = 0;
      lprect->right = m_iCurrentViewWidth;
      lprect->bottom = get_proper_item_count() * _001GetItemHeight();


   }

   bool tree::_001GetItemElementRect(
      LPRECT lprect,
      ::user::tree_draw_item &drawitem,
      ::user::e_tree_element eelement)
   {
      switch(eelement)
      {
      case tree_element_expand_box:
         {
            lprect->left   = drawitem.m_rect.left;
            lprect->right  = min(lprect->left + 16, drawitem.m_rect.right);
            lprect->top    = drawitem.m_rect.top;
            lprect->bottom = drawitem.m_rect.bottom;
         }
         break;
      case tree_element_image:
         {
            lprect->left   = drawitem.m_rect.left + 18;
            lprect->right  = min(lprect->left + 16, drawitem.m_rect.right);
            lprect->top    = drawitem.m_rect.top;
            lprect->bottom = drawitem.m_rect.bottom;
         }
         break;
      case tree_element_text:
         {
            lprect->left   = drawitem.m_rect.left + 38;
            lprect->right  = drawitem.m_rect.right;
            lprect->top    = drawitem.m_rect.top;
            lprect->bottom = drawitem.m_rect.bottom;
         }
         break;
      }
      return true;
   }

   void tree::_001SelectItem(::ex1::tree_item *pitem)
   {
      if(pitem != NULL)
      {
         pitem->set_selection();
      }
   }

   void tree::_001ExpandItem(::ex1::tree_item *pitem, bool bExpand, /* = true */ bool bRedraw, /*=true*/ bool bLayout /*=true*/)
   {
      ::ca::data::writing writing(::ca::data_container::m_spdata);
      UNREFERENCED_PARAMETER(bLayout);
      if(bExpand)
      {
         if(!(pitem->m_dwState & ::ex1::tree_item_state_expanded))
         {
            
            _001OnItemExpand(pitem);

            pitem->m_dwState |= ::ex1::tree_item_state_expanded;

            // scroll properly to show the highest possible number
            // of children while trying to preserve the old position and
            // never passing
            index iLevel = 0;
            index iParentIndex = get_proper_item_index(pitem, &iLevel);

            index iLastChildIndex = iParentIndex + pitem->get_proper_descendant_count();

            index iLastVisibleIndex = (index) (m_scrollinfo.m_ptScroll.y / _001GetItemHeight() + _001GetVisibleItemCount());

            index iObscured; // obscured proper descendants
            iObscured = iLastChildIndex  - iLastVisibleIndex;

            if(iObscured > 0)
            {
               index iNewScroll = (int) (m_scrollinfo.m_ptScroll.y + iObscured * _001GetItemHeight());
               if(iNewScroll > (iParentIndex * _001GetItemHeight()))
                  iNewScroll = (iParentIndex * _001GetItemHeight());
               m_scrollinfo.m_ptScroll.y = (LONG) max(iNewScroll, 0);
   //            _001SetYScroll(max(iNewScroll, 0), false);
               //m_pscrollbarVert->_001SetScrollPos(m_scrollinfo.m_ptScroll.y);
            }
         }
      }
      else
      {
         pitem->m_dwState &= ~::ex1::tree_item_state_expanded;
      }

      layout();
      if(bRedraw)
      {
         _001RedrawWindow();
      }

   }

   void tree::_001OnItemExpand(::ex1::tree_item * pitem)
   {
      if(pitem->get_tree() != this)
      {
         dynamic_cast < tree * > (pitem->get_tree())->_001OnItemExpand(pitem);
      }
   }

   void tree::_001OnItemCollapse(::ex1::tree_item *pitem)
   {
      if(pitem->get_tree() != this)
      {
         dynamic_cast < tree * > (pitem->get_tree())->_001OnItemCollapse(pitem);
      }
   }

   void tree::_001OnVScroll(gen::signal_object * pobj)
   {
      //SCAST_PTR(::gen::message::scroll, pscroll, pobj);
      pobj->previous();
      m_pitemFirstVisible = CalcFirstVisibleItem(
         m_iFirstVisibleItemLevel,
         m_iFirstVisibleItemProperIndex);


   }

   void tree::_001OnHScroll(gen::signal_object * pobj)
   {
      //SCAST_PTR(::gen::message::scroll, pscroll, pobj);
      pobj->previous();

   }

/*   void tree::SetScrollSizes()
   {
      rect64 rectTotal;

      _001GetViewRect(&rectTotal);

      size sizeTotal = rectTotal.size();

      m_scrollinfo.m_sizeTotal = sizeTotal;

      rect rectViewClient;
      _001GetViewClientRect(&rectViewClient);

      m_scrollinfo.m_sizeTotal = sizeTotal;
      m_scrollinfo.m_sizePage = rectViewClient.size();


      if(m_scrollinfo.m_ptScroll.y > (m_scrollinfo.m_sizeTotal.cy - m_scrollinfo.m_sizePage.cy))
      {
         m_scrollinfo.m_ptScroll.y = (m_scrollinfo.m_sizeTotal.cy - m_scrollinfo.m_sizePage.cy);
      }


   }*/

   void tree::layout()
   {
      

      SetScrollSizes();

      m_pitemFirstVisible = CalcFirstVisibleItem(m_iFirstVisibleItemLevel, m_iFirstVisibleItemProperIndex);

      m_iCurrentViewWidth = _001CalcCurrentViewWidth();

      _001LayoutScrollBars();

   }



   void tree::_001OnOpenItem(::ex1::tree_item *pitem)
   {
      if(pitem->get_tree() != this)
      {
         dynamic_cast < tree * > (pitem->get_tree())->_001OnOpenItem(pitem);
      }
   }

   void tree::UpdateHover()
   {
      point pt;
      System.get_cursor_pos(&pt);
      ScreenToClient(&pt);
      ::user::e_tree_element eelement;
      ::ex1::tree_item * pitem = _001HitTest(pt, eelement);
      if(eelement != tree_element_image &&
         eelement != tree_element_text)
      {
         pitem = NULL;
      }
      if(pitem != m_pitemHover)
      {
         m_pitemHover = pitem;
         _001RedrawWindow();
      }
      /*if(pitem != NULL)
      {
         SetTimer(TimerHover, 250, NULL);
      }
      else
      {
         KillTimer(TimerHover);
      }*/
   }

   void tree::_001SetExpandImage(HICON hicon)
   {
      m_iImageExpand = m_pimagelist->add_icon_os_data(hicon);
   }

   void tree::_001SetCollapseImage(HICON hicon)
   {
      m_iImageCollapse = m_pimagelist->add_icon_os_data(hicon);
   }

   count tree::_001GetVisibleItemCount()
   {
      if(_001GetItemHeight() == 0)
         return 0;

      rect rect;
      GetClientRect(rect);

      return rect.height() / _001GetItemHeight() - 1;
   }

   int tree::_001CalcCurrentViewWidth()
   {
      rect rectClient;
      GetClientRect(rectClient);

      count iCount = _001GetVisibleItemCount();
      int iMaxWidth = rectClient.width();
      int iWidth;
      index iLevel = m_iFirstVisibleItemLevel;
      index iIndent  = _001GetIndentation();
      ::ex1::tree_item * pitem = m_pitemFirstVisible;
      if(pitem == NULL)
         return iMaxWidth;
      for(int i = 0; i < iCount; i++)
      {
         iWidth = (int) (200 + iIndent * iLevel);
         if(iWidth > iMaxWidth)
         {
            iMaxWidth = iWidth;
         }
         pitem = pitem->get_item(::ex1::TreeNavigationProperForward, &iLevel);
         if(pitem == NULL)
            break;
      }
      return iMaxWidth;
   }

   /*
   void tree::_001SetYScroll(int y, bool bRedraw)
   {
      m_ptScroll.y = y;

      m_pitemFirstVisible = CalcFirstVisibleItem(
         m_iFirstVisibleItemLevel,
         m_iFirstVisibleItemProperIndex);

      if(bRedraw)
      {
         _001RedrawWindow();
      }
   }
   */

   ::ex1::tree_item * tree::CalcFirstVisibleItem(index & iLevel, index & iProperIndex)
   {
      index nOffset;
      if(_001GetItemHeight() == 0)
         return NULL;
      nOffset = m_scrollinfo.m_ptScroll.y / _001GetItemHeight();

      ::ex1::tree_item * pitem = get_base_item();

      iLevel = 0;
      iProperIndex = 0;

      for(;;)
      {
         pitem = pitem->get_item(::ex1::TreeNavigationProperForward, &iLevel);
         if(pitem == NULL)
            break;
         if(nOffset <= 0)
         {
            break;
         }
         nOffset--;
         iProperIndex++;
      }

      return pitem;
   }

   void tree::_001OnTreeDataChange()
   {
      layout();
   }

   image_list * tree::get_image_list()
   {
      return m_pimagelist;
   }

   bool tree::can_merge(::user::interaction * pui)
   {
      return base < tree >::bases(pui) && !m_treeptra.contains(dynamic_cast < tree * > (pui));
   }

   bool tree::merge(::user::interaction * pui)
   {
      tree * ptree = dynamic_cast < tree * > (pui);
      if(!insert_item(ptree->get_base_item(), ex1::RelativeLastChild, get_base_item()))
         return false;
      m_treeptra.add(ptree);
      return true;
   }


} // namespace ex1


