#include "StdAfx.h"

namespace user
{



   const UINT list::MESSAGE_ENDCOLUMNHEADERDRAG = WM_USER + 25;
   const UINT list::MESSAGE_COLUMNHEADERTRACK = WM_USER + 26;
   const UINT list::MESSAGE_ENDCOLUMNHEADERTRACK = WM_USER + 27;

   list::list(::ca::application * papp) :
   ca(papp),
   ::user::scroll_view(papp),
   m_columna(papp),
   m_font(papp),
   m_fontHover(papp),
   m_penFocused(papp),
   m_penHighlight(papp),
   m_dcextension(papp)
   {
      m_piaFilterIcon = new index_biunique();
      m_piaFilterList = new index_array();
      m_iconlayout.m_iaDisplayToStrict.set_empty_a(-1);
      m_iconlayout.m_iaDisplayToStrict.set_empty_b(-1);
      m_columna.Initialize(this);

      m_bDrag = false;

      m_eview = ViewReport;
      m_iItemFocus = -1;
      m_iItemHover = -1;
      m_iSubItemHover = -2;
      m_bSortEnable              = true;
      m_bFilter1                 = false;
      m_iWheelDelta              = 0;

      m_bSingleColumnMode        = false;
      m_bHeaderCtrl              = true;
      m_pdata           = NULL;
      m_pcache                   = NULL;
      m_pheaderctrl              = NULL;
      m_bTopText                 = false;

      m_bEmboss                  = true;
      m_bHoverSelect             = true;
      m_bMultiSelect             = true;
      m_iLateralGroupWidth       = 200;

      m_pdrawlistitem            = new draw_list_item(this);

      m_bGroup                   = false;
      m_bLateralGroup            = false;

      // Simple Filter
      m_efilterstate             = FilterStateNoFilter;

      m_iGroupMinHeight          = 0;
      m_nGroupCount              = 0;
      m_nItemCount               = 0;
      m_iTopIndex                = -1;
      m_nDisplayCount            = 0;

      m_iClick = 0;

      m_penFocused->CreatePen(PS_SOLID, 2, ARGB(255, 0, 255, 255));
      m_penHighlight->CreatePen(PS_SOLID, 2, ARGB(255, 0, 255, 255));

      m_crText = ARGB(255, 0, 0, 0);
      m_crTextSelected = ARGB(255, 255, 255, 255);
      m_crTextHighlight = ARGB(255, 55, 105, 255);
      m_crTextSelectedHighlight = ARGB(255, 102, 153, 255);

      m_bLockViewUpdate = false;


      m_iItemHeight = 0;
      m_iItemWidth = 0;

      m_iLastItemSel = 0;
      m_iLastSubItemSel = 0;
      m_iItemSel = 0;
      m_iSubItemSel = 0;
      m_iSubItemEnter = -1;
      m_iItemEnter = -1;

      //   m_iItemCount = 0;

      m_pilGroup        = NULL;
      m_pilGroupHover   = NULL;


      m_scrollinfo.m_rectMargin.left = -84;
      m_scrollinfo.m_rectMargin.top = -84;
      m_scrollinfo.m_rectMargin.bottom = -84;
      m_scrollinfo.m_rectMargin.right = -84;
      m_scrollinfo.m_ptScroll.x = -84;
      m_scrollinfo.m_ptScroll.y = -84;

   }

   list::~list()
   {
   }


   void list::install_message_handling(::gen::message::dispatch * pinterface)
   {
      ::user::scroll_view::install_message_handling(pinterface);
      IGUI_WIN_MSG_LINK(WM_SIZE,            pinterface, this, &list::_001OnSize);
      IGUI_WIN_MSG_LINK(WM_VSCROLL,         pinterface, this, &list::_001OnVScroll);
      IGUI_WIN_MSG_LINK(WM_HSCROLL,         pinterface, this, &list::_001OnHScroll);
      IGUI_WIN_MSG_LINK(WM_MOUSELEAVE,      pinterface, this, &list::_001OnMouseLeave);

      IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN,     pinterface, this, &list::_001OnLButtonDown);
      IGUI_WIN_MSG_LINK(WM_LBUTTONUP,       pinterface, this, &list::_001OnLButtonUp);
      IGUI_WIN_MSG_LINK(WM_LBUTTONDBLCLK,   pinterface, this, &list::_001OnLButtonDblClk);
      IGUI_WIN_MSG_LINK(WM_RBUTTONDOWN,     pinterface, this, &list::_001OnRButtonDown);

      IGUI_WIN_MSG_LINK(WM_MOUSEMOVE,       pinterface, this, &list::_001OnMouseMove);
      IGUI_WIN_MSG_LINK(WM_MOUSEWHEEL,      pinterface, this, &list::_001OnMouseWheel);

      IGUI_WIN_MSG_LINK(WM_KEYDOWN,         pinterface, this, &list::_001OnKeyDown);

      IGUI_WIN_MSG_LINK(WM_CREATE,          pinterface, this, &list::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_TIMER,           pinterface, this, &list::_001OnTimer);
      connect_command("list_view_auto_arrange", &list::_001OnListViewAutoArrange);
      connect_update_cmd_ui("list_view_auto_arrange", &list::_001OnUpdateListViewAutoArrange);
   }

   bool list::CreateHeaderCtrl()
   {
      if(m_pheaderctrl != NULL)
      {
         if(!m_pheaderctrl->IsWindow())
         {
            return m_pheaderctrl->create(
               NULL,
               "",
               WS_CHILD
               | WS_VISIBLE
               | HDS_FULLDRAG
               | HDS_HOTTRACK
               | HDS_DRAGDROP,
               rect(0 , 0 , 0 , 0),
               get_guie(),
               1023) != 0;
         }
         else
            return true;
         return false;
      }
      return false;
   }


   void list::_001OnDraw(::ca::graphics *pdc)
   {

      if(m_bLockViewUpdate)
         return;

      rect rectClient;

      GetClientRect(rectClient);


      if(_001IsBackgroundBypass())
      {
      }
      else if(_001IsTranslucent())
      {
         class imaging & imaging = System.imaging();
         imaging.color_blend(pdc, rectClient, get_background_color() & 0xffffff, (get_background_color() >> 24) & 0xff);
      }
      else
      {
         pdc->FillSolidRect(rectClient, (255 << 24) | (get_background_color() & 0xffffff));
      }



      pdc->SetBkMode(TRANSPARENT);





      if(m_bTopText)
      {
         point ptViewportOrg = pdc->GetViewportOrg();
         pdc->set_color(m_crText);
         base_array < size > sizea;
         m_dcextension.GetTextExtent(pdc, m_strTopText, sizea);
         rect rectClient;
         GetClientRect(rectClient);
         index x = 0;
         index right = (index) rectClient.right;
         index y = m_iItemHeight;
         index iStart = 0;
         index iNewStart = 0;
         index w;
         for(index i = 0; i < sizea.get_size(); i++)
         {

            if((sizea[i].cx - x > right)
               || i == sizea.get_upper_bound())
            {
               rect rect;
               rect.top = index(y - m_scrollinfo.m_ptScroll.y);
               if(i == 0)
               {
                  w = sizea[0].cx - x      ;
                  x = sizea[0].cx;
                  y += sizea[0].cy;
                  iNewStart = 0;

               }
               else
               {
                  w = sizea[i - 1].cx - x;
                  x = sizea[i - 1].cx;
                  y += sizea[i - 1].cy;
                  iNewStart = i - 1;
               }
               rect.left = LONG(- m_scrollinfo.m_ptScroll.x);
               rect.right = rectClient.right;
               rect.bottom = LONG(y - m_scrollinfo.m_ptScroll.y);

               m_dcextension._DrawText(pdc, m_strTopText.Mid(iStart, i - iStart), rect, DT_LEFT);
               iStart = iNewStart;
            }
         }
         pdc->SetViewportOrg(ptViewportOrg);
      }



      m_pdrawlistitem->m_pgraphics              = pdc;
      m_pdrawlistitem->m_iItemRectItem          = -1;
      m_pdrawlistitem->m_iSubItemRectOrder      = -1;
      m_pdrawlistitem->m_iSubItemRectSubItem    = -1;
      m_pdrawlistitem->m_iSubItemRectItem       = -1;
      m_pdrawlistitem->m_iSubItemRectColumn     = -1;
      m_pdrawlistitem->m_pcolumnSubItemRect     = NULL;
      m_pdrawlistitem->m_pcolumnWidth           = NULL;
      m_pdrawlistitem->m_iWidthColumn           = -1;
      m_pdrawlistitem->m_iColumnWidth           = 0;

      rect rectItem;
      rect rectIntersect;
      INT_PTR iItemCount = m_nDisplayCount;
      INT_PTR iItemFirst = m_iTopIndex;
      INT_PTR iItemLast;
      if(m_eview == ViewIcon)
      {
         iItemLast = iItemCount;
      }
      else
      {
         iItemLast = min(m_nItemCount - 1, iItemFirst + m_nDisplayCount - 1);
      }

      if(iItemFirst < 0)
         return;

      _001DrawItems(m_pdrawlistitem, iItemFirst, iItemLast);

      if(m_bGroup && m_bLateralGroup)
      {

         int iGroupFirst = 0;
         int iGroupFirstTopIndex = 0;
         for(; iGroupFirst < m_nGroupCount; iGroupFirst++)
         {
            if(iItemFirst >= iGroupFirstTopIndex && iItemFirst < (iGroupFirstTopIndex + _001GetGroupItemCount(iGroupFirst)))
               break;
         }
         int iGroupLast = iGroupFirst;
         int iGroupLastTopIndex = iGroupFirstTopIndex;
         for(; iGroupLast < m_nGroupCount; iGroupLast++)
         {
            if(iItemLast >= iGroupLastTopIndex && iItemLast < (iGroupLastTopIndex + _001GetGroupItemCount(iGroupLast)))
               break;
         }

         _001DrawGroups(m_pdrawlistitem, iGroupFirst, iGroupLast, iItemFirst, iItemLast);
      }


   }



















   void list::_001DrawGroups(draw_list_item * pdrawitem, index iGroupFirst, index iGroupLast, index iItemFirst, index iItemLast)
   {

      UNREFERENCED_PARAMETER(iItemFirst);
      UNREFERENCED_PARAMETER(iItemLast);

      index iGroup;

      rect rectClient;

      rect rectIntersect;

      GetClientRect(rectClient);

      bool bHoverFont = false;
      ::ca::font  * pfont = _001GetFont();
      pdrawitem->m_pgraphics->SelectObject(pfont);

      m_pdrawlistitem->m_pfont = pfont;

      for(iGroup = iGroupFirst; iGroup <= iGroupLast; iGroup++)
      {

         m_pdrawlistitem->m_iGroup          = iGroup;

         _001GetGroupRect(m_pdrawlistitem);

         if(!m_pdrawlistitem->m_bOk)
            continue;

         if(!rectIntersect.intersect(m_pdrawlistitem->m_rectItem, rectClient))
            continue;

         if(iGroup == m_iGroupHover)
         {
            if(!bHoverFont)
            {
               m_pdrawlistitem->m_pfont = _001GetFontHover();
               pdrawitem->m_pgraphics->SelectObject(m_pdrawlistitem->m_pfont);
            }
         }
         else
         {
            if(bHoverFont)
            {
               m_pdrawlistitem->m_pfont = pfont;
               pdrawitem->m_pgraphics->SelectObject(pfont);
            }
         }

         _001DrawGroup(m_pdrawlistitem);

      }

   }



















   void list::_001DrawGroup(draw_list_item * pdrawitem)
   {

      /*if(m_bGroupCustomDraw)
      {
         pdrawitem->m_bListSubItemHover = pdrawitem->m_bListItemHover && (pdrawitem->m_iSubItem == m_iSubItemHover);
         pdrawitem->m_bFocus = false;
         return;
      }*/

      _001GetElementRect(pdrawitem, userbase::_list::ElementGroupImage);
      if(pdrawitem->m_bOk)
      {
         pdrawitem->draw_group_image();
      }

      ::count nItem = _001GetGroupMetaItemCount(pdrawitem->m_iGroup);

      for(pdrawitem->m_iItem = 0; pdrawitem->m_iItem < nItem; pdrawitem->m_iItem++)
      {
         _001GetElementRect(pdrawitem, userbase::_list::ElementGroupItemText);
         if(pdrawitem->m_bOk)
         {
            _001GetGroupText(pdrawitem);
            pdrawitem->draw_text();
         }
      }



   }
















   void list::_001DrawItems(draw_list_item * pdrawitem, index iItemFirst, index iItemLast)
   {

      rect rectClient;

      GetClientRect(rectClient);

      rect rectIntersect;

      index iItem;

      if(m_eview == ViewIcon)
      {
         m_pdrawlistitem->m_iDrawTextFlags = DT_TOP | DT_CENTER | DT_END_ELLIPSIS | DT_WORDBREAK;
      }
      else
      {
         m_pdrawlistitem->m_iDrawTextFlags = DT_TOP | DT_LEFT | DT_END_ELLIPSIS | DT_SINGLELINE;
      }

      bool bHoverFont = false;
      ::ca::font  * pfont = _001GetFont();
      pdrawitem->m_pgraphics->SelectObject(pfont);

      pdrawitem->m_pfont = pfont;

      for(iItem = iItemFirst; iItem <= iItemLast; iItem++)
      {
         if(m_eview == ViewIcon
            && (m_iconlayout.m_iaDisplayToStrict.get_b(iItem) == -1
            && iItem != m_iItemDrop))
            continue;

         m_pdrawlistitem->m_iItem           = DisplayToStrict(iItem);
         m_pdrawlistitem->m_iDisplayItem    = iItem;

         if(m_bGroup)
         {
            m_pdrawlistitem->m_iGroupTopIndex = 0;
//            int igroup;
            for(m_pdrawlistitem->m_iGroup = 0; m_pdrawlistitem->m_iGroup < m_nGroupCount; m_pdrawlistitem->m_iGroup++)
            {
               m_pdrawlistitem->m_iGroupCount = _001GetGroupItemCount(m_pdrawlistitem->m_iGroup);
               if(iItem >= m_pdrawlistitem->m_iGroupTopIndex && iItem < (m_pdrawlistitem->m_iGroupTopIndex + m_pdrawlistitem->m_iGroupCount))
                  break;
            }
         }

         _001GetItemRect(m_pdrawlistitem);

         if(!m_pdrawlistitem->m_bOk)
            continue;

         if(!rectIntersect.intersect(m_pdrawlistitem->m_rectItem, rectClient))
            continue;

         if(iItem == m_iItemHover)
         {
            if(!bHoverFont)
            {
               m_pdrawlistitem->m_pfont = _001GetFontHover();
               pdrawitem->m_pgraphics->SelectObject(m_pdrawlistitem->m_pfont);
            }
         }
         else
         {
            if(bHoverFont)
            {
               m_pdrawlistitem->m_pfont = pfont;
               pdrawitem->m_pgraphics->SelectObject(pfont);
            }
         }

         _001DrawItem(m_pdrawlistitem);

      }
   }



   void list::_001DrawItem(draw_list_item * pdrawitem)
   {

      pdrawitem->m_iState = 0;

      Range & rangeSelection = m_rangeSelection;
      Range & rangeHighlight = m_rangeHighlight;


      if(pdrawitem->m_iItem < 0)
         return;

      pdrawitem->m_bListItemHover = pdrawitem->m_iDisplayItem == m_iItemHover &&
         (m_eview != ViewIcon ||
         ((m_iconlayout.m_iaDisplayToStrict.get_a(m_iItemHover) >= 0 && m_iconlayout.m_iaDisplayToStrict.get_a(m_iItemHover) < m_nItemCount)));

      ::ca::font * pfont;
      if(pdrawitem->m_bListItemHover)
      {
         System.imaging().color_blend(pdrawitem->m_pgraphics, pdrawitem->m_rectItem, RGB(255, 255, 255), 128);
         pfont = _001GetFontHover();
      }
      else
      {
         pfont = _001GetFont();
      }
      pdrawitem->m_pgraphics->set_font(pfont);

      pdrawitem->m_bListItemSelected = (m_eview != ViewIcon || is_valid_display_item(pdrawitem->m_iItem)) && rangeSelection.HasItem(pdrawitem->m_iDisplayItem);

      if(pdrawitem->m_bListItemHover)
         pdrawitem->m_iState |= ItemStateHover;
      if(pdrawitem->m_bListItemSelected)
         pdrawitem->m_iState |= ItemStateSelected;




      if(pdrawitem->m_bListItemSelected)
      {
         if(System.savings().is_trying_to_save(gen::resource_processing))
         {
            pdrawitem->m_pgraphics->FillSolidRect(pdrawitem->m_rectItem, ARGB(255, 96,96,96));
         }
         else
         {
            COLORREF crTranslucid = RGB(0, 0, 0);
            System.imaging().color_blend(pdrawitem->m_pgraphics, pdrawitem->m_rectItem, crTranslucid, 127);
         }
      }

      pdrawitem->update_item_color();
      pdrawitem->set_text_color();

      string str;

      index iColumnCount;

      if(m_eview == ViewIcon)
      {
         iColumnCount = 1;
      }
      else
      {
         iColumnCount = _001GetColumnCount();
      }

      pdrawitem->m_iSubItemRectOrder      = -1;
      pdrawitem->m_iSubItemRectSubItem    = -1;
      pdrawitem->m_iSubItemRectColumn     = -1;
      pdrawitem->m_pcolumnSubItemRect     = NULL;

      for(pdrawitem->m_iOrder = 0; pdrawitem->m_iOrder < iColumnCount; pdrawitem->m_iOrder++)
      {


         pdrawitem->m_iColumn    = _001MapOrderToColumn(pdrawitem->m_iOrder);


         if(pdrawitem->m_iColumn < 0)
            continue;


         pdrawitem->m_pcolumn    = m_columna._001GetVisible(pdrawitem->m_iColumn);
         pdrawitem->m_iSubItem   = pdrawitem->m_pcolumn->m_iSubItem;
         pdrawitem->m_iColumnKey = pdrawitem->m_pcolumn->m_iKey;


         _001GetSubItemRect(pdrawitem);


         if(!pdrawitem->m_bOk)
            continue;


         _001DrawSubItem(pdrawitem);

      }
      if(rangeHighlight.HasItem(pdrawitem->m_iDisplayItem))
      {
         ::ca::pen_sp penHighlight(get_app());
         ::ca::pen * ppenHighlight = _001GetPenHighlight();
         class rect rectHighlight(pdrawitem->m_rectItem);
         rectHighlight.deflate(2, 2);
         pdrawitem->m_pgraphics->SelectObject(ppenHighlight);
         pdrawitem->m_pgraphics->DrawRectangle(rectHighlight);
      }



   }


   void   list::_001DrawSubItem(draw_list_item * pdrawitem)
   {

      if(pdrawitem->m_pcolumn->m_bCustomDraw)
      {
         pdrawitem->m_bListSubItemHover = pdrawitem->m_bListItemHover && (pdrawitem->m_iSubItem == m_iSubItemHover);
         pdrawitem->m_bFocus = false;
         return;
      }

      pdrawitem->m_iListItem = -1;
      _001GetElementRect(pdrawitem, userbase::_list::ElementImage);
      if(pdrawitem->m_bOk)
      {
         pdrawitem->draw_image();
      }
      pdrawitem->m_iListItem = -1;
      _001GetElementRect(pdrawitem, userbase::_list::ElementText);
      if(pdrawitem->m_bOk)
      {
         _001GetItemText(pdrawitem);
         pdrawitem->draw_text();
      }

   }




   void list::_001GetItemImage(::user::list_item * pitem)
   {
      if(m_pdata != NULL)
      {
         pitem->m_plist = this;
         return m_pdata->_001GetItemImage(pitem);
      }
      /*LVITEM lvi;
      lvi.mask = LVIF_IMAGE;
      lvi.iItem = iItem;
      lvi.iSubItem = 0;
      get_item(&lvi);
      return lvi.iImage;*/
      pitem->m_bOk = false;
   }

   void list::_001GetItemText(::user::list_item * pitem)
   {
      pitem->m_bOk = false;
      if(m_pcache != NULL)
      {
         m_pcache->_001GetItemText(pitem);
         if(pitem->m_bOk)
            return;
      }
      if(m_pdata != NULL)
      {
         m_pdata->_001GetItemText(pitem);
      }
   }

   // Purpose:
   // Provide Item Text for Search Purposes.
   void list::_001SearchGetItemText(::user::list_item * pitem)
   {
      _001GetItemText(pitem);
   }


   count list::_001GetColumnCount()
   {
      return m_columna.VisibleGetCount();
   }

   /*BOOL list::PreCreateWindow(CREATESTRUCT& cs)
   {

   //cs.style |= LVS_NOSCROLL;

   return ::ca::window::PreCreateWindow(cs);
   }*/

   /*void list::OnSize(UINT nType, index cx, index cy)
   {
   ::ca::window::OnSize(nType, cx, cy);

   layout();
   }*/

   void list::_001OnSize(gen::signal_object * pobj)
   {
      SCAST_PTR(::gen::message::size, psize, pobj);
      layout();
      psize->m_bRet = false;
   }

   void list::layout()
   {

      if(m_bTopText)
         _001LayoutTopText();

      INT_PTR iCount = m_nItemCount;
      index iMaxWidth = 0;
      index iWidth;
      if(m_bSingleColumnMode)
      {
         for(INT_PTR i = 0; i < iCount; i++)
         {
            iWidth = _001CalcItemWidth(i, 0);
            if(iWidth > iMaxWidth)
            {
               iMaxWidth = iWidth;
            }
         }
         m_iItemWidth = iMaxWidth;
         m_columna._001GetByKey(0)->m_iWidth = iMaxWidth;
      }

      m_iTopIndex       = _001CalcDisplayTopIndex();

      index iLow = 0;
      for(m_iTopGroup = 0; m_iTopGroup < m_nGroupCount; m_iTopGroup++)
      {
         if(m_iTopIndex >= iLow && m_iTopIndex < (iLow + _001GetGroupItemCount(m_iTopGroup)))
            break;
      }

      m_nDisplayCount   = _001CalcDisplayItemCount();

      SetScrollSizes();

      LayoutHeaderCtrl();

      _001LayoutScrollBars();

   }

   void list::SetScrollSizes()
   {

      rect rectTotal;

      _001GetViewRect(&rectTotal);

      size sizeTotal = rectTotal.size();

      m_scrollinfo.m_sizeTotal = sizeTotal;

      rect rectViewClient;
      _001GetViewClientRect(&rectViewClient);

      m_scrollinfo.m_sizeTotal = sizeTotal;
      m_scrollinfo.m_sizePage = rectViewClient.size();

   }


   void list::_001GetViewClientRect(LPRECT lprect)
   {
      rect rectClient;
      GetClientRect(rectClient);
      *lprect = rect(rectClient);
      if(m_bHeaderCtrl)
      {
         lprect->top += m_iItemHeight;
      }
      return;
      rect rectView;

      _001GetViewRect(&rectView);


      index iViewHeight = (index)rectView.height();

      index iViewWidth = (index)rectView.width();

      index iClientHeight = (index)rectClient.height();

      if(m_bHeaderCtrl)
      {
         iClientHeight -= m_iItemHeight;
      }

      index iClientWidth = (index)rectClient.width();

      index iScrollHeight =  iClientHeight - GetSystemMetrics(SM_CYHSCROLL);

      index iScrollWidth = iClientWidth - GetSystemMetrics(SM_CXVSCROLL);

      bool bHScroll = false;

      bool bVScroll = false;

      if(iViewWidth > iClientWidth)
      {
         bHScroll = true;
         if(iViewHeight > iScrollHeight)
         {
            bVScroll = true;
         }
      }
      else if(iViewHeight > iClientHeight)
      {
         bVScroll = true;
         if(iViewWidth > iScrollWidth)
         {
            bHScroll = true;
         }
      }

      lprect->left = 0;
      lprect->top = 0;
      if(m_bHeaderCtrl)
      {
         lprect->top += m_iItemHeight;
      }
      if(bVScroll)
         lprect->right = lprect->left + iScrollWidth;
      else
         lprect->right = lprect->left + iClientWidth;
      if(bHScroll)
         lprect->bottom = lprect->top + iScrollHeight;
      else
         lprect->bottom = lprect->top + iClientHeight;

   }

   bool list::_001OnUpdateItemCount(DWORD dwFlags)
   {
      UNREFERENCED_PARAMETER(dwFlags);

      m_nItemCount = _001GetItemCount();
      if(m_nItemCount < 0)
         return false;

      if(m_bGroup)
      {
         m_nGroupCount = _001GetGroupCount();
         if(m_nGroupCount < 0)
            return false;
      }

      if(m_eview == ViewIcon)
      {
         for(index iStrict = 0; iStrict < m_nItemCount; iStrict++)
         {
            if(m_iconlayout.m_iaDisplayToStrict.get_a(iStrict) == -1)
            {
               m_iconlayout.m_iaDisplayToStrict.set(m_iconlayout.m_iaDisplayToStrict.get_free_a(), iStrict);
            }
         }
      }
      else
      {
         index iStart = m_listlayout.m_iaDisplayToStrict.get_count();
         index iEnd = m_nItemCount - 1;
         m_listlayout.m_iaDisplayToStrict.set_size(m_nItemCount);
         for(index iStrict = iStart; iStrict <= iEnd; iStrict++)
         {
            m_listlayout.m_iaDisplayToStrict.set_at(iStrict, iStrict);
         }
      }

      if(m_bFilter1)
      {
         FilterApply();
      }

      CacheHint();
      layout();

      TRACE("list::_001OnUpdateItemCount ItemCount %d\n", m_nItemCount);
      if(m_bGroup)
      {
         TRACE("list::_001OnUpdateItemCount GroupCount %d\n", m_nGroupCount);
      }

      return true;
   }

   void list::_001GetViewRect(LPRECT lprect)
   {
      rect rect;
      if(m_eview == ViewList)
      {
         if(m_nItemCount == 0)
         {
            rect = class rect(0, 0, 0, 0);
         }
         else
         {
            class rect rectClient;

            _001GetViewClientRect(&rectClient);


            rectClient.inflate(m_scrollinfo.m_rectMargin);

            draw_list_item itemFirst(this);

            itemFirst.m_iItem          = 0;
            itemFirst.m_iDisplayItem   = 0;

            _001GetItemRect(&itemFirst);


            rect.top    = rectClient.top;
            rect.bottom = rectClient.bottom;
            rect.left   = rectClient.left;
            if(m_iItemHeight <= 0)
               rect.right = rectClient.right;
            else
               rect.right  = (LONG) min(
                  rectClient.left +
                  m_nItemCount * itemFirst.m_rectItem.width() * m_iItemHeight /
                  rectClient.height()
                  + itemFirst.m_rectItem.width(), MAXLONG);
         }
      }
      else if(m_eview == ViewReport)
      {
         if(m_nItemCount == 0)
         {
            rect = class rect(0, 0, 0, 0);
         }
         else
         {
            draw_list_item itemFirst(this);

            itemFirst.m_iItem             = 0;
            itemFirst.m_iDisplayItem      = 0;
            itemFirst.m_iGroup            = 0;
            _001GetItemRect(&itemFirst);

            draw_list_item itemLast(this);

            if(m_bFilter1)
            {
               itemLast.m_iDisplayItem       = m_piaFilterList->get_count() - 1;
               itemLast.m_iItem              = m_piaFilterList->get_count() - 1; 
            }
            else
            {
               itemLast.m_iDisplayItem       = m_nItemCount - 1;
               itemLast.m_iItem              = m_nItemCount - 1;
            }
            if(m_bGroup)
            {
               itemLast.m_iGroupTopIndex = 0;
//               int igroup;
               for(itemLast.m_iGroup = 0; itemLast.m_iGroup < m_nGroupCount; itemLast.m_iGroup++)
               {
                  itemLast.m_iGroupCount = _001GetGroupItemCount(itemLast.m_iGroup);
                  if(itemLast.m_iItem >= itemLast.m_iGroupTopIndex && itemLast.m_iItem < (itemLast.m_iGroupTopIndex + itemLast.m_iGroupCount))
                     break;
               }
            }
            _001GetItemRect(&itemLast);

            itemLast.m_rectItem.right     -= (m_scrollinfo.m_rectMargin.left + m_scrollinfo.m_rectMargin.right);
            itemLast.m_rectItem.bottom    -= (m_scrollinfo.m_rectMargin.top  + m_scrollinfo.m_rectMargin.bottom);

            rect.unite(itemFirst.m_rectItem, itemLast.m_rectItem);
         }
      }
      else if(m_eview == ViewIcon)
      {
         draw_list_item itemFirst(this);

         itemFirst.m_iItem             = 0;
         itemFirst.m_iDisplayItem      = 0;

         _001GetItemRect(&itemFirst);

         draw_list_item itemLast(this);

         itemLast.m_iDisplayItem       = m_nItemCount - 1;
         itemLast.m_iItem              = m_nItemCount - 1;

         _001GetItemRect(&itemLast);

         draw_list_item itemTopRight(this);
         if(m_flags.is_signalized(flag_auto_arrange) || m_iconlayout.m_iWidth <= 0)
         {
            class rect rectClient;

            _001GetViewClientRect(&rectClient);

            itemTopRight.m_iItem = (index)max(1, rectClient.width() / get_item_size().cx) - 1;
         }
         else
         {
            itemTopRight.m_iItem = max(1, m_iconlayout.m_iWidth) - 1;
         }
         itemTopRight.m_iDisplayItem = itemTopRight.m_iDisplayItem;
         _001GetItemRect(&itemTopRight);

         rect.unite(itemFirst.m_rectItem, itemLast.m_rectItem);
         rect.unite(rect, itemTopRight.m_rectItem);

      }
      *lprect = rect;
   }

   void list::_001OnInitialize()
   {

   }

   void list::_001AddColumn(list_column & column)
   {
      m_columna.add(column);
      _001OnColumnChange();
      column.m_bCustomDraw = false;
      column.m_iControl = (UINT) -1;
      column.m_uiSmallBitmap = (UINT) -1;
      column.m_bIcon = false;
      column.m_pil = NULL;
   }

   //
   // list_column
   //

   list_column::list_column()
   {
      m_iKey                     = -1;
      m_iKeyVisible              = -1;
      m_iKeyNonVisible           = -1;
      m_uiSmallBitmap            = (UINT) -1;
      m_iOrder                   = -1;
      m_bVisible                 = true;
      m_pil                      = NULL;
      m_iControl                 = -1;
      m_bEditOnSecondClick       = false;
      m_bCustomDraw              = false;
      m_bIcon                    = false;
      m_pil                      = NULL;
      m_pilHover                 = NULL;
   }
   list_column::list_column(const list_column & column)
   {
      operator =(column);
   }
   list_column::~list_column()
   {
   }

   bool list_column::operator ==(const list_column & column) const
   {
      return (m_iKey == column.m_iKey)
         && (m_iKeyVisible == column.m_iKeyVisible)
         && (m_iKeyNonVisible == column.m_iKeyNonVisible);

   }



   INT_PTR list_column::CompareOrderSectEndNonVisible(list_column  * pcolumna, list_column * pcolumnb)
   {
      if(pcolumna->m_bVisible && pcolumnb->m_bVisible)
         return pcolumna->m_iOrder - pcolumnb->m_iOrder;
      else if(pcolumna->m_bVisible)
         return -1;
      else if(pcolumnb->m_bVisible)
         return 1;
      else
         return 0;
   }

   INT_PTR list_column::CompareOrder(list_column * pcolumna, list_column * pcolumnb)
   {
      return pcolumna->m_iOrder - pcolumnb->m_iOrder;
   }

   INT_PTR list_column::CompareKey(list_column * pcolumna, list_column * pcolumnb)
   {
      return pcolumna->m_iKey - pcolumnb->m_iKey;
   }

   list_column & list_column::operator = (const list_column & column)
   {
      m_iKey               = column.m_iKey;
      m_iKeyVisible        = column.m_iKeyVisible;
      m_iKeyNonVisible     = column.m_iKeyNonVisible;
      m_iOrder             = column.m_iOrder;
      m_iSubItem           = column.m_iSubItem;
      m_uiText             = column.m_uiText;
      m_iWidth             = column.m_iWidth;
      m_uiSmallBitmap      = column.m_uiSmallBitmap;
      m_crSmallMask        = column.m_crSmallMask;
      m_iSmallImageWidth   = column.m_iSmallImageWidth;
      m_pil                = column.m_pil;
      m_pilHover           = column.m_pilHover;
      m_bVisible           = column.m_bVisible;
      m_iControl           = column.m_iControl;
      m_datakey            = column.m_datakey;
      m_bIcon              = column.m_bIcon;
      m_sizeIcon           = column.m_sizeIcon;
      m_bCustomDraw        = column.m_bCustomDraw;
      m_mapIcon            = column.m_mapIcon;
      m_bEditOnSecondClick = column.m_bEditOnSecondClick;

      return *this;
   }


   void list::_001OnColumnChange()
   {

      index iItemHeight = 0;
      index iItemWidth = 0;

      IMAGEINFO ii;
      index iColumnWidth;
      rect rect;

      string str;
      bool bVisible;
      INT_PTR iColumn;

      for(iColumn = 0; iColumn < m_columna.VisibleGetCount(); iColumn++)
      {
         list_column * pcolumn = m_columna._001GetVisible(iColumn);
         str.Format("SubItem[%d].Visible", pcolumn->m_iSubItem);
         if(data_get(str, ::radix::system::idEmpty, bVisible))
         {
            if(!bVisible)
            {
               m_columna.ShowSubItem(pcolumn->m_iSubItem, false);
            }
         }
      }

      for(iColumn = 0; iColumn < m_columna.NonVisibleGetCount(); iColumn++)
      {
         list_column * pcolumn = m_columna._001GetNonVisible(iColumn);
         str.Format("SubItem[%d].Visible", pcolumn->m_iSubItem);
         if(data_get(str, ::radix::system::idEmpty, bVisible))
         {
            if(bVisible)
            {
               m_columna.ShowSubItem(pcolumn->m_iSubItem, true);
            }
         }
      }





      for(iColumn = 0; iColumn < m_columna.VisibleGetCount(); iColumn++)
      {
         list_column * pcolumn = m_columna._001GetVisible(iColumn);
         iColumnWidth = pcolumn->m_iWidth;
         _001CreateImageList(pcolumn);
         if(iColumnWidth >= 0)
         {
            iItemWidth += iColumnWidth;
         }
         if(pcolumn->m_pil != NULL
            && pcolumn->m_pil->get_image_count() > 0)
         {
            pcolumn->m_pil->get_image_info(0, &ii);
            rect = ii.rcImage;
            if(rect.height() + 2 > iItemHeight)
            {
               iItemHeight = (index)rect.height() + 2;
            }
         }
         if(pcolumn->m_sizeIcon.cy + 2 > iItemHeight)
         {
            iItemHeight = pcolumn->m_sizeIcon.cy + 2;
         }
      }

      ::ca::font * pfont = _001GetFont();
      ::ca::graphics * pdc = GetDC();
      pdc->SelectObject(pfont);
      size size;
      size = pdc->GetTextExtent("Ap");
      if(size.cy + 2 > iItemHeight)
      {
         iItemHeight = size.cy + 2;
      }

      m_iItemHeight = iItemHeight;

      m_iItemWidth = iItemWidth;

      if(m_bSingleColumnMode)
      {
         m_iItemWidth = _001CalcColumnWidth(0);
      }

      if(m_pheaderctrl->IsWindow())
      {
         //      while(m_pheaderctrl->DeleteItem(0));

         HDITEM hditem;

         for(index iOrder = 0; iOrder < m_columna.VisibleGetCount(); iOrder++)
         {
            iColumn = _001MapOrderToColumn(iOrder);
            if(iColumn < 0)
               continue;
            list_column * pcolumn = m_columna._001GetVisible(iColumn);
            hditem.mask = HDI_WIDTH | HDI_TEXT | HDI_LPARAM | HDI_ORDER;
            //str.load_string(_001GetColumnTextId(iColumn));
            //hditem.pszText = (LPTSTR) (const char *) str;
            hditem.pszText = LPSTR_TEXTCALLBACK;
            //hditem.cchTextMax = str.get_length();
            hditem.cchTextMax = 0;
            hditem.cxy = pcolumn->m_iWidth;;
            hditem.lParam = iColumn;
            hditem.iOrder = iOrder;
            //         m_pheaderctrl->InsertItem(iColumn, &hditem);
         }
      }


      m_columna.VisibleToGlobalOrder();




   }

   void list::_001SetColumnWidth(index iColumn, int iWidth)
   {
      ASSERT(iColumn >= 0);
      ASSERT(iColumn < m_columna.VisibleGetCount());

      m_columna._001GetVisible(iColumn)->m_iWidth = iWidth;

      m_pheaderctrl->DIDDXColumn(true, iColumn);

      _001OnColumnChange();

   }

   void list::_001GetColumnWidth(draw_list_item * pitem)
   {
      pitem->m_pcolumnWidth   = m_columna._001GetVisible(pitem->m_iWidthColumn);
      pitem->m_iColumnWidth   = pitem->m_pcolumnWidth->m_iWidth;
      pitem->m_bOk            = true;
   }


   index list::_001MapSubItemToOrder(index iSubItem)
   {
      return _001MapColumnToOrder(_001MapSubItemToColumn(iSubItem));
   }

   index list::_001MapOrderToSubItem(index iOrder)
   {
      return _001MapColumnToSubItem(_001MapOrderToColumn(iOrder));
   }

   index list::_001MapOrderToColumn(index iOrder)
   {
      for(index iColumn = 0; iColumn < m_columna.get_size(); iColumn++)
      {
         list_column * pcolumn = m_columna.ptr_at(iColumn);
         if(pcolumn->m_bVisible && pcolumn->m_iOrder == iOrder)
            return iColumn;
      }
      return -1;
   }

   index list::_001MapColumnToOrder(index iColumn)
   {
      if(iColumn < 0)
         return -1;
      if(iColumn >= m_columna.VisibleGetCount())
         return -1;

      return m_columna._001GetVisible(iColumn)->m_iOrder;
   }

   index list::_001MapSubItemToColumn(index iSubItem)
   {
      return m_columna.VisibleMapSubItemToColumn(iSubItem);
   }

   index list::_001MapColumnToSubItem(index iColumn)
   {
      ASSERT(iColumn >= 0);
      ASSERT(iColumn < m_columna.VisibleGetCount());

      return m_columna._001GetVisible(iColumn)->m_iSubItem;
   }

   void list::_001DeleteColumn(index iColumn)
   {
      ASSERT(iColumn >= 0);
      ASSERT(iColumn < m_columna.VisibleGetCount());

      m_columna.remove(iColumn);

   }


   count list::_001GetItemCount()
   {
      if(m_pdata != NULL)
      {
         return m_pdata->_001GetItemCount();
      }
      else
         return -1;
   }


   count list::_001GetGroupCount()
   {
      if(m_pdata != NULL)
      {
         return m_pdata->_001GetGroupCount();
      }
      else
         return -1;
   }

   /////////////////////////////////////////////////////////////////
   //
   // Function: _001CalcDisplayTopIndex
   // Old Name: _001GetTopIndex
   //
   // Purpose:
   // Return the index of the first visible item in the list
   //
   // Output:
   // The index of the first visible item in the list
   //
   // Author:
   // Camilo Sasuke Tsumanuma
   //
   /////////////////////////////////////////////////////////////////
   index list::_001CalcDisplayTopIndex()
   {
      index iItem;
      if(_001DisplayHitTest(
         point(m_scrollinfo.m_ptScroll.x < 0 ? -m_scrollinfo.m_ptScroll.x : 0,
         (m_bHeaderCtrl ? m_iItemHeight : 0) + ( m_scrollinfo.m_ptScroll.y < -0 ? -m_scrollinfo.m_ptScroll.y : 0 )), iItem))
         return iItem;
      else
      {
         if(m_eview == ViewReport)
         {
            if(m_scrollinfo.m_ptScroll.y < 0)
               return 0;
         }
         return -1;
      }
   }

   count list::_001CalcDisplayItemCount()
   {
      if(m_eview == ViewIcon)
      {
         rect rectView;
         _001GetViewClientRect(&rectView);
         class size sizeItem = get_item_size();
         return max((rectView.width() / sizeItem.cx) * (rectView.height() / sizeItem.cy),
            m_iconlayout.m_iaDisplayToStrict.get_max_a() + 1);
      }
      else if(m_eview == ViewReport)
      {
         rect rectView;
         _001GetViewClientRect(&rectView);
         if(m_iItemHeight == 0)
         {
            return 0;
         }
         else
         {
            if(m_bTopText)
            {
               return (rectView.height() - m_rectTopText.height()) / m_iItemHeight;
            }
            else
            {
               return rectView.height() / m_iItemHeight;
            }
         }
      }

      INT_PTR iItemCount;
      if(m_bFilter1 && (m_eview == ViewList || m_eview == ViewReport))
      {
         iItemCount = m_piaFilterList->get_count();
      }
      else
      {
         iItemCount = m_nItemCount;
      }
      INT_PTR iItemFirst = m_iTopIndex;
      INT_PTR iItemLast = iItemFirst;
      rect rectItem;
      rect rectIntersect;
      rect rectUpdate;
      _001GetViewClientRect(&rectUpdate);
      draw_list_item item(this);
      if(iItemFirst >= 0)
      {
         iItemLast = -1;
         for(INT_PTR i = iItemFirst + 1; i < iItemCount; i++)
         {
            item.m_iItem         = i;
            item.m_iDisplayItem  = i;
            if(m_bGroup)
            {
               item.m_iGroupTopIndex = 0;
               for(item.m_iGroup = 0; item.m_iGroup < m_nGroupCount; item.m_iGroup++)
               {
                  item.m_iGroupCount = _001GetGroupItemCount(item.m_iGroup);
                  if(i >= item.m_iGroupTopIndex && i < (item.m_iGroupTopIndex + item.m_iGroupCount))
                     break;
               }
            }

            _001GetItemRect(&item);
            if(item.m_bOk)
            {
               if(!rectIntersect.intersect(item.m_rectItem, rectUpdate))
               {
                  iItemLast = i - 1;
                  break;
               }
            }
            else
            {
               iItemLast = i - 1;
               break;
            }
         }
         if(iItemLast < 0)
            iItemLast = iItemCount - 1;
         return iItemLast - iItemFirst + 1;
      }
      else
      {
         return 0;
      }

   }


   bool list::_001HitTest_(point point, index &iItem, index &iSubItem, index &iListItem, userbase::_list::EElement &eelement)
   {
      UNREFERENCED_PARAMETER(point);
      UNREFERENCED_PARAMETER(iItem);
      UNREFERENCED_PARAMETER(iSubItem);
      UNREFERENCED_PARAMETER(iListItem);
      UNREFERENCED_PARAMETER(eelement);
      return false;
   }

   bool list::_001HitTest_(point point, index &iItem, index &iSubItem)
   {
      if(!_001DisplayHitTest(point, iItem, iSubItem))
         return false;
      iItem = DisplayToStrict(iItem);
      return true;
   }

   bool list::_001HitTest_(POINT pt, index & iItem)
   {
      if(!_001DisplayHitTest(pt, iItem))
         return false;
      iItem = DisplayToStrict(iItem);
      return true;
   }

   bool list::_001DisplayHitTest(point point, index & iItem, index & iSubItem, index & iListItem, userbase::_list::EElement &eelement)
   {
      UNREFERENCED_PARAMETER(point);
      UNREFERENCED_PARAMETER(iItem);
      UNREFERENCED_PARAMETER(iSubItem);
      UNREFERENCED_PARAMETER(iListItem);
      UNREFERENCED_PARAMETER(eelement);
      return false;
   }

   bool list::_001DisplayHitTest(point point, INT_PTR &iItemParam, INT_PTR &iSubItemParam)
   {
      INT_PTR iItem;
      if(!_001DisplayHitTest(point, iItem))
      {
         return false;
      }
      if(m_eview == ViewIcon || m_eview == ViewList)
      {
         iItemParam = iItem;
         if(iItem == -1)
         {
            iSubItemParam = -1;
         }
         else
         {
            iSubItemParam = 0;
         }
         return true;
      }
      INT_PTR iColumnCount = _001GetColumnCount();
      INT_PTR iLeft =(index) m_scrollinfo.m_ptScroll.x - (m_scrollinfo.m_rectMargin.left * 2);
      if(m_bGroup && m_bLateralGroup)
         iLeft += m_iLateralGroupWidth;
      INT_PTR iRight;
      draw_list_item item(this);
      if(point.x < iLeft)
         return false;
      for(item.m_iWidthColumn = 0; item.m_iWidthColumn < iColumnCount; item.m_iWidthColumn++)
      {
         _001GetColumnWidth(&item);
         if(!item.m_bOk)
            continue;
         iRight = iLeft + item.m_iColumnWidth;
         if(iLeft <= point.x && point.x < iRight)
         {
            iItemParam = iItem;
            iSubItemParam = item.m_pcolumnWidth->m_iSubItem;
            return true;
         }
         iLeft = iRight;
      }
      return false;
   }

   bool list::_001DisplayHitTest(POINT pt, INT_PTR &iItemParam)
   {
      if(m_eview == ViewReport)
      {
         index iy = pt.y + m_scrollinfo.m_ptScroll.y;

         index iItem = -1;

         if(m_iItemHeight != 0)
            iItem = iy / m_iItemHeight;

         if(iItem < 0)
            return false;

         if(m_bHeaderCtrl)
         {
            iItem--;

            if(iItem < 0)
               return false;
         }

         if(m_bFilter1)
         {
             if(iItem >= m_piaFilterList->get_count())
                return false;
         }

         if(iItem >= m_nItemCount)
            return false;

         iItemParam = (index)iItem;

         return true;
      }
      else if(m_eview == ViewList)
      {
         if(m_iItemHeight <= 0)
            return false;

         class rect rectClient;
         _001GetViewClientRect(&rectClient);
         if(m_bTopText)
         {
            rectClient.top += m_rectTopText.height();
         }
         if(m_bHeaderCtrl)
         {
            rectClient.top += m_iItemHeight;
         }
         rectClient.inflate(m_scrollinfo.m_rectMargin);
         index iRoundHeight = (index)((rectClient.height() / m_iItemHeight) * m_iItemHeight);

         index iy = (index)((pt.y + m_scrollinfo.m_ptScroll.y) + (((pt.x + m_scrollinfo.m_ptScroll.x) / m_iItemWidth)) * iRoundHeight);

         index iItem = -1;

         if(m_iItemHeight != 0)
            iItem = iy / m_iItemHeight;

         if(iItem < 0)
            return false;

         if(m_bHeaderCtrl)
         {
            iItem--;

            if(iItem < 0)
               return false;
         }

         if(m_bFilter1)
         {
             if(iItem >= m_piaFilterList->get_count())
                return false;
         }

         if(iItem >= m_nItemCount)
            return false;

         iItemParam = iItem;

         return true;

      }
      else if(m_eview == ViewIcon)
      {
         if(m_columna.get_count() == 0)
            return false;
         class rect rectClient;
         _001GetViewClientRect(&rectClient);
         if(m_bTopText)
         {
            rectClient.top += m_rectTopText.height();
         }
         index iIconSize = max(32, m_columna[0].m_sizeIcon.cy);
         index iItemSize = iIconSize * 2;

         index ix = (index)( pt.x + m_scrollinfo.m_ptScroll.x);
         ix = (index)max(m_scrollinfo.m_ptScroll.x, ix);
         ix = (index)min(rectClient.right, ix);
         ix = (index)max(rectClient.left, ix);
         ix /= iItemSize;

         index iy = pt.y + m_scrollinfo.m_ptScroll.y;
         iy = max(m_scrollinfo.m_ptScroll.y, iy);
         iy = max(rectClient.top, iy);
         iy /= iItemSize;

         if(m_flags.is_signalized(flag_auto_arrange) || m_iconlayout.m_iWidth <= 0)
         {
            iItemParam = iy * (max(1, rectClient.width() / iItemSize) ) + ix;
         }
         else
         {
            iItemParam = iy * (max(1, m_iconlayout.m_iWidth)) + ix;
         }


         return true;
      }

      return false;
   }

   void list::_001GetGroupRect(::user::draw_list_item * pdrawitem)
   {
      if(pdrawitem->m_iGroup < 0)
         return_(pdrawitem->m_bOk, false);
      if(pdrawitem->m_iGroup >= m_nGroupCount)
         return_(pdrawitem->m_bOk, false);
      index iItemFirst = 0;
      index iItemLast = _001GetGroupItemCount(0) - 1;
      pdrawitem->m_iGroupRectGroup = 0;
      while(pdrawitem->m_iGroupRectGroup < pdrawitem->m_iGroup)
      {
         pdrawitem->m_iGroupRectGroup++;
         iItemFirst = iItemLast + 1;
         iItemLast = iItemFirst + _001GetGroupItemCount(pdrawitem->m_iGroupRectGroup) - 1;
      }

      draw_list_item itemFirst(this);

      itemFirst.m_iItem             = DisplayToStrict(iItemFirst);
      itemFirst.m_iDisplayItem      = iItemFirst;
      itemFirst.m_iGroup            = pdrawitem->m_iGroupRectGroup;

      _001GetItemRect(&itemFirst);

      draw_list_item itemLast(this);

      itemLast.m_iDisplayItem       = DisplayToStrict(iItemLast);
      itemLast.m_iItem              = iItemLast;
      itemLast.m_iGroup             = pdrawitem->m_iGroupRectGroup;

      _001GetItemRect(&itemLast);

      pdrawitem->m_rectGroup.unite(itemFirst.m_rectItem, itemLast.m_rectItem);
      pdrawitem->m_rectGroup.bottom = max(itemLast.m_rectItem.bottom, itemFirst.m_rectItem.top + m_iGroupMinHeight);
      pdrawitem->m_rectGroup.left = 0;
      pdrawitem->m_rectGroup.right = m_iLateralGroupWidth;
      pdrawitem->m_bOk = true;
   }

   void list::_001GetItemRect(::user::draw_list_item * pdrawitem)
   {

      if(pdrawitem->m_iDisplayItem == (-1 - pdrawitem->m_iItemRectItem) && pdrawitem->m_iItemRectItem >= 0)
      {
         return_(pdrawitem->m_bOk, false);
      }

      if(pdrawitem->m_iDisplayItem == pdrawitem->m_iItemRectItem)
      {
         return_(pdrawitem->m_bOk, true);
      }

      if(pdrawitem->m_iDisplayItem < 0)
      {
         pdrawitem->m_rectItem.left = 0;
         pdrawitem->m_rectItem.top = 0;
         pdrawitem->m_rectItem.right = 0;
         pdrawitem->m_rectItem.bottom = 0;
         pdrawitem->m_iItemRectItem = (-1 - pdrawitem->m_iDisplayItem);
         return_(pdrawitem->m_bOk, false);
      }
      if(m_eview == ViewIcon && pdrawitem->m_iDisplayItem >= m_nDisplayCount)
      {
         pdrawitem->m_rectItem.left = 0;
         pdrawitem->m_rectItem.top = 0;
         pdrawitem->m_rectItem.right = 0;
         pdrawitem->m_rectItem.bottom = 0;
         pdrawitem->m_iItemRectItem = (-1 - pdrawitem->m_iDisplayItem);
         return_(pdrawitem->m_bOk, false);
      }

      if(m_eview == ViewReport)
      {
         if(m_bGroup)
         {
            if(m_bLateralGroup)
            {

               if(pdrawitem->m_iItemRectItem < 0)
               {
                  pdrawitem->m_rectItem.left    = m_iLateralGroupWidth;
                  pdrawitem->m_rectItem.right   = m_iItemWidth;
                  pdrawitem->m_iItemRectItem = 0;
                  pdrawitem->m_rectItem.top  = 0;
                  if(m_bHeaderCtrl)
                  {
                     pdrawitem->m_rectItem.top += m_iItemHeight;
                  }
                  if(m_bTopText)
                  {
                     pdrawitem->m_rectItem.top += m_rectTopText.height();
                  }
                  pdrawitem->m_rectItem.bottom = pdrawitem->m_rectItem.top + m_iItemHeight;
                  pdrawitem->m_rectItem.offset(-m_scrollinfo.m_ptScroll.x, -m_scrollinfo.m_ptScroll.y);
               }

               if(pdrawitem->m_iDisplayItem > pdrawitem->m_iItemRectItem)
               {
                  int iOffset                               = (pdrawitem->m_iItemRectItem - pdrawitem->m_iGroupTopIndex) * m_iItemHeight;
                  pdrawitem->m_rectItem.top                -= iOffset;
                  pdrawitem->m_rectItem.bottom              = pdrawitem->m_rectItem.top + m_iItemHeight;
                  while(pdrawitem->m_iGroupTopIndex + pdrawitem->m_iGroupCount < pdrawitem->m_iDisplayItem)
                  {
//                     int iHeight                            = _001GetGroupHeight(pdrawitem->m_iGroup);
                     pdrawitem->m_rectItem.top             += iOffset;
                     pdrawitem->m_rectItem.bottom           = pdrawitem->m_rectItem.top + m_iItemHeight;
                     if((pdrawitem->m_iGroup + 1) >= m_nGroupCount)
                     {
                        break;
                     }
                     pdrawitem->m_iGroup++;
                     pdrawitem->m_iGroupTopIndex            += pdrawitem->m_iGroupCount;
                     pdrawitem->m_iGroupCount               = _001GetGroupItemCount(pdrawitem->m_iGroup);
                     pdrawitem->m_iItemRectItem             = pdrawitem->m_iGroupTopIndex;
                  }
               }
               else
               {
                  int iOffset                               = (pdrawitem->m_iItemRectItem - pdrawitem->m_iGroupTopIndex) * m_iItemHeight;
                  pdrawitem->m_rectItem.top                -= iOffset;
                  pdrawitem->m_rectItem.bottom              = pdrawitem->m_rectItem.top + m_iItemHeight;
                  while(pdrawitem->m_iGroupTopIndex + pdrawitem->m_iGroupCount > pdrawitem->m_iDisplayItem)
                  {
                     if((pdrawitem->m_iGroup - 1) < 0)
                     {
                        break;
                     }
                     pdrawitem->m_iGroup--;
                     int iHeight                         = _001GetGroupHeight(pdrawitem->m_iGroup);
                     pdrawitem->m_rectItem.top          -= iHeight;
                     pdrawitem->m_rectItem.bottom        = pdrawitem->m_rectItem.top + m_iItemHeight;
                     pdrawitem->m_iGroupCount            = _001GetGroupItemCount(pdrawitem->m_iGroup);
                     pdrawitem->m_iGroupTopIndex        -= pdrawitem->m_iGroupCount;
                     pdrawitem->m_iItemRectItem          = pdrawitem->m_iGroupTopIndex;
                  }
               }
               if(pdrawitem->m_iGroup < m_nGroupCount && pdrawitem->m_iGroup >= 0)
               {
                  pdrawitem->m_iItemRectItem       = pdrawitem->m_iDisplayItem;
                  pdrawitem->m_rectItem.top       += (pdrawitem->m_iItemRectItem - pdrawitem->m_iGroupTopIndex) * m_iItemHeight;
                  pdrawitem->m_rectItem.bottom     =  pdrawitem->m_rectItem.top + m_iItemHeight;
               }
            }
            else
            {
               throw not_implemented_exception();
            }
         }
         else
         {
            pdrawitem->m_rectItem.left    = 0;
            pdrawitem->m_rectItem.right   = m_iItemWidth;

            pdrawitem->m_rectItem.top = 0;
            if(m_bHeaderCtrl)
            {
               pdrawitem->m_rectItem.top += m_iItemHeight;
            }
            pdrawitem->m_rectItem.top += m_iItemHeight * pdrawitem->m_iDisplayItem;
            if(m_bTopText)
            {
               pdrawitem->m_rectItem.top += m_rectTopText.height();
            }
            pdrawitem->m_rectItem.bottom = pdrawitem->m_rectItem.top + m_iItemHeight;
            pdrawitem->m_rectItem.offset(-m_scrollinfo.m_ptScroll.x, -m_scrollinfo.m_ptScroll.y);
            pdrawitem->m_iItemRectItem   = pdrawitem->m_iDisplayItem;
         }
      }
      else if(m_eview == ViewList)
      {
         class rect rectClient;
         _001GetViewClientRect(&rectClient);
         if(m_bTopText)
         {
            rectClient.top += m_rectTopText.height();
         }
         if(m_bHeaderCtrl)
         {
            rectClient.top += m_iItemHeight;
         }
         rectClient.inflate(m_scrollinfo.m_rectMargin);
         if(m_iItemHeight <= 0)
            return_(pdrawitem->m_bOk, false);
         index iRoundHeight = (rectClient.height() / m_iItemHeight) * m_iItemHeight;
         if(iRoundHeight != 0)
         {
            pdrawitem->m_rectItem.left = ((pdrawitem->m_iItem * m_iItemHeight) / iRoundHeight) * m_iItemWidth;
            pdrawitem->m_rectItem.top = (pdrawitem->m_iItem * m_iItemHeight) % iRoundHeight;
         }
         if(m_bTopText)
         {
            pdrawitem->m_rectItem.top += m_rectTopText.height();
         }
         if(m_bHeaderCtrl)
         {
            pdrawitem->m_rectItem.top += m_iItemHeight;
         }
         pdrawitem->m_rectItem.bottom = pdrawitem->m_rectItem.top + m_iItemHeight;
         pdrawitem->m_rectItem.right = pdrawitem->m_rectItem.left + m_iItemWidth;
         pdrawitem->m_rectItem.offset(-m_scrollinfo.m_ptScroll.x, -m_scrollinfo.m_ptScroll.y);
      }
      else if(m_eview == ViewIcon)
      {
         if(m_flags.is_signalized(flag_auto_arrange) || m_iconlayout.m_iWidth <= 0)
         {
            class rect rectClient;
            _001GetViewClientRect(&rectClient);
            if(m_bTopText)
            {
               rectClient.top += m_rectTopText.height();
            }
            index iIconSize = max(32, m_columna[0].m_sizeIcon.cy);
            index iItemSize = iIconSize * 2;
            pdrawitem->m_rectItem.left = iItemSize * (pdrawitem->m_iItem % (max(1, rectClient.width() / iItemSize) ));
            pdrawitem->m_rectItem.top = iItemSize * (pdrawitem->m_iItem / (max(1, rectClient.width() / iItemSize) ));
            pdrawitem->m_rectItem.bottom = pdrawitem->m_rectItem.top + iItemSize;
            pdrawitem->m_rectItem.right = pdrawitem->m_rectItem.left + iItemSize;
         }
         else
         {
            class rect rectClient;
            _001GetViewClientRect(&rectClient);
            if(m_bTopText)
            {
               rectClient.top += m_rectTopText.height();
            }
            index iItemSize = get_item_size().cy;
            pdrawitem->m_rectItem.left = iItemSize * (pdrawitem->m_iDisplayItem % m_iconlayout.m_iWidth);
            pdrawitem->m_rectItem.top = rectClient.top + iItemSize * (pdrawitem->m_iDisplayItem / m_iconlayout.m_iWidth);
            pdrawitem->m_rectItem.bottom = pdrawitem->m_rectItem.top + iItemSize;
            pdrawitem->m_rectItem.right = pdrawitem->m_rectItem.left + iItemSize;
         }
         pdrawitem->m_rectItem.offset(-m_scrollinfo.m_ptScroll.x, -m_scrollinfo.m_ptScroll.y);
      }

      pdrawitem->m_bOk = true;

   }

   void list::_001GetSubItemRect(::user::draw_list_item * pdrawitem)
   {

      if(pdrawitem->m_iDisplayItem != pdrawitem->m_iItemRectItem)
      {
         _001GetItemRect(pdrawitem);
         if(!pdrawitem->m_bOk)
            return;
      }

      if(pdrawitem->m_iSubItemRectOrder == pdrawitem->m_iOrder)
      {
         if(pdrawitem->m_iSubItemRectItem != pdrawitem->m_iItemRectItem)
         {
            pdrawitem->m_rectSubItem.top     = pdrawitem->m_rectItem.top;
            pdrawitem->m_rectSubItem.bottom  = pdrawitem->m_rectItem.bottom;
         }
         return_(pdrawitem->m_bOk, true);
      }

      if(m_eview == ViewIcon)
      {
         pdrawitem->m_rectSubItem     = pdrawitem->m_rectItem;
         return_(pdrawitem->m_bOk, true);
         return;
         throw "subitem rectangle on icon view? why are you asking for that now?";
      }

      pdrawitem->m_bOk = false;

      pdrawitem->m_rectSubItem.top     = pdrawitem->m_rectItem.top;
      pdrawitem->m_rectSubItem.bottom  = pdrawitem->m_rectItem.bottom;

      index iLastOrder = _001GetColumnCount() - 1;

      if(iLastOrder < 0)
         return_(pdrawitem->m_bOk, false);



      if(pdrawitem->m_iSubItemRectOrder < 0 || pdrawitem->m_iOrder == 0 || pdrawitem->m_iSubItemRectOrder > pdrawitem->m_iOrder)
      {
         pdrawitem->m_iSubItemRectOrder         = 0;
         pdrawitem->m_rectSubItem.left          = pdrawitem->m_rectItem.left;
         pdrawitem->m_iSubItemRectColumn        = _001MapOrderToColumn(0);
         pdrawitem->m_iWidthColumn              = pdrawitem->m_iSubItemRectColumn;
         _001GetColumnWidth(pdrawitem);
         pdrawitem->m_rectSubItem.right         = pdrawitem->m_rectItem.left + pdrawitem->m_iColumnWidth;
         pdrawitem->m_iSubItemRectItem          = pdrawitem->m_iItemRectItem;
         pdrawitem->m_iSubItemRectSubItem       = pdrawitem->m_pcolumnWidth->m_iSubItem;
         pdrawitem->m_pcolumnSubItemRect        = pdrawitem->m_pcolumnWidth;
         if(pdrawitem->m_iOrder == 0)
         {
            pdrawitem->m_bOk = true;
            return;
         }
      }

      if(pdrawitem->m_iOrder <= iLastOrder)
      {
         while(pdrawitem->m_iSubItemRectOrder < pdrawitem->m_iOrder)
         {
            pdrawitem->m_iWidthColumn           = _001MapOrderToColumn(pdrawitem->m_iSubItemRectOrder);
            _001GetColumnWidth(pdrawitem);
            pdrawitem->m_rectSubItem.left       += pdrawitem->m_iColumnWidth;
            pdrawitem->m_iSubItemRectOrder++;
         }
         pdrawitem->m_iWidthColumn              = _001MapOrderToColumn(pdrawitem->m_iSubItemRectOrder);
         pdrawitem->m_iSubItemRectColumn        = pdrawitem->m_iWidthColumn;
         _001GetColumnWidth(pdrawitem);
         pdrawitem->m_rectSubItem.right         = pdrawitem->m_rectSubItem.left + pdrawitem->m_iColumnWidth;
         pdrawitem->m_iSubItemRectOrder         = pdrawitem->m_iOrder;
         pdrawitem->m_iSubItemRectItem          = pdrawitem->m_iItemRectItem;
         pdrawitem->m_iSubItemRectSubItem       = pdrawitem->m_pcolumnWidth->m_iSubItem;
         pdrawitem->m_pcolumnSubItemRect        = pdrawitem->m_pcolumnWidth;
         pdrawitem->m_bOk = true;
      }

   }

   void list::_001GetElementRect(::user::draw_list_item * pdrawitem, userbase::_list::EElement eelement)
   {

      if(m_bGroup && m_bLateralGroup &&
        (eelement == userbase::_list::ElementGroupImage
      || eelement == userbase::_list::ElementGroupItemText))
      {
         int x = pdrawitem->m_rectGroup.left;
         int iImageBottom = pdrawitem->m_rectGroup.top;

         if(m_pilGroup != NULL)
         {

            IMAGEINFO ii;

            _001GetGroupImage(pdrawitem);
            if(pdrawitem->m_bOk && pdrawitem->m_iImage >= 0)
            {
               m_pilGroup->get_image_info(pdrawitem->m_iImage, &ii);
               if(eelement == userbase::_list::ElementGroupImage)
               {
                  pdrawitem->m_rectImage.left      = x;
                  pdrawitem->m_rectImage.right     = x + width(&ii.rcImage);
                  pdrawitem->m_rectImage.top       = pdrawitem->m_rectGroup.top;
                  pdrawitem->m_rectImage.bottom    = pdrawitem->m_rectImage.top + height(&ii.rcImage);
                  return_(pdrawitem->m_bOk, true);
               }
               else
               {
                  x += width(&ii.rcImage);
                  x += 2;
                  iImageBottom += height(&ii.rcImage) + 2;
               }
            }
            else if(eelement == userbase::_list::ElementGroupImage)
            {
               return_(pdrawitem->m_bOk, false);
            }
         }
         else if(eelement == userbase::_list::ElementGroupImage)
         {
            return_(pdrawitem->m_bOk, false);
         }
         if(eelement == userbase::_list::ElementGroupItemText)
         {
            pdrawitem->m_rectText.top       = pdrawitem->m_rectGroup.top + m_iItemHeight * pdrawitem->m_iItem;
            if(pdrawitem->m_rectText.top >= iImageBottom)
            {
               pdrawitem->m_rectText.left      = pdrawitem->m_rectGroup.left;
            }
            else
            {
               pdrawitem->m_rectText.left      = x;
            }
            pdrawitem->m_rectText.right     = pdrawitem->m_rectGroup.right;
            pdrawitem->m_rectText.bottom    = pdrawitem->m_rectText.top + m_iItemHeight;
            return_(pdrawitem->m_bOk, true);
         }
         pdrawitem->m_bOk = false;
      }
      else
      {
         if(pdrawitem->m_iDisplayItem != pdrawitem->m_iItemRectItem)
         {
            _001GetItemRect(pdrawitem);
            if(!pdrawitem->m_bOk)
               return;
         }
         if(eelement == userbase::_list::ElementItem)
         {
            return_(pdrawitem->m_bOk, true);
         }
         if(m_eview == ViewIcon)
         {
            if(eelement == userbase::_list::ElementImage)
            {
               index iIconSize                  = m_columna[0].m_sizeIcon.cy;
               pdrawitem->m_rectImage.left      = pdrawitem->m_rectItem.left    + iIconSize / 2;
               pdrawitem->m_rectImage.top       = pdrawitem->m_rectItem.top;
               pdrawitem->m_rectImage.right     = pdrawitem->m_rectImage.left  + iIconSize;
               pdrawitem->m_rectImage.bottom    = pdrawitem->m_rectImage.top   + iIconSize;
               return_(pdrawitem->m_bOk, true);
            }
            else if(eelement == userbase::_list::ElementText)
            {
               index iIconSize               = m_columna[0].m_sizeIcon.cy;
               pdrawitem->m_rectText.left    = pdrawitem->m_rectItem.left;
               pdrawitem->m_rectText.top     = pdrawitem->m_rectItem.top + iIconSize;
               pdrawitem->m_rectText.right   = pdrawitem->m_rectText.left + iIconSize * 2;
               pdrawitem->m_rectText.bottom  = pdrawitem->m_rectText.top + iIconSize;
               return_(pdrawitem->m_bOk, true);
            }
            return_(pdrawitem->m_bOk, false);
         }

         _001GetSubItemRect(pdrawitem);

         if(!pdrawitem->m_bOk)
            return;

         int x = pdrawitem->m_rectSubItem.left;

         if(pdrawitem->m_iListItem == -1)
         {
            if(eelement == userbase::_list::ElementSubItem)
            {
               return_(pdrawitem->m_bOk, true);
            }
            if(pdrawitem->m_pcolumnSubItemRect->m_bIcon)
            {
               _001GetItemImage(pdrawitem);
               if(pdrawitem->m_bOk && pdrawitem->m_iImage >= 0)
               {
                  if(eelement == userbase::_list::ElementImage)
                  {
                     pdrawitem->m_rectImage.left      = x;
                     pdrawitem->m_rectImage.right     = x + pdrawitem->m_pcolumnSubItemRect->m_sizeIcon.cx;
                     pdrawitem->m_rectImage.bottom    = pdrawitem->m_rectSubItem.bottom;
                     pdrawitem->m_rectImage.top       = pdrawitem->m_rectImage.bottom - pdrawitem->m_pcolumnSubItemRect->m_sizeIcon.cx;
                     return_(pdrawitem->m_bOk, true);
                  }
                  else
                  {
                     x += pdrawitem->m_pcolumnSubItemRect->m_sizeIcon.cx;
                     x += 2;
                  }
               }
               else if(eelement == userbase::_list::ElementImage)
               {
                  return_(pdrawitem->m_bOk, false);
               }
            }
            else if(pdrawitem->m_pcolumnSubItemRect->m_pil != NULL)
            {

               IMAGEINFO ii;

               _001GetItemImage(pdrawitem);
               if(pdrawitem->m_bOk && pdrawitem->m_iImage >= 0)
               {
                  pdrawitem->m_pcolumnSubItemRect->m_pil->get_image_info(pdrawitem->m_iImage, &ii);
                  if(eelement == userbase::_list::ElementImage)
                  {
                     pdrawitem->m_rectImage.left      = x;
                     pdrawitem->m_rectImage.right     = x + width(&ii.rcImage);
                     pdrawitem->m_rectImage.bottom    = pdrawitem->m_rectSubItem.bottom;
                     pdrawitem->m_rectImage.top       = pdrawitem->m_rectImage.bottom - height(&ii.rcImage);
                     return_(pdrawitem->m_bOk, true);
                  }
                  else
                  {
                     x += width(&ii.rcImage);
                     x += 2;
                  }
               }
               else if(eelement == userbase::_list::ElementImage)
               {
                  return_(pdrawitem->m_bOk, false);
               }
            }
            else if(eelement == userbase::_list::ElementImage)
            {
               return_(pdrawitem->m_bOk, false);
            }
            if(eelement == userbase::_list::ElementText)
            {
               pdrawitem->m_rectText.left      = x;
               pdrawitem->m_rectText.right     = pdrawitem->m_rectSubItem.right;
               pdrawitem->m_rectText.top       = pdrawitem->m_rectSubItem.top;
               pdrawitem->m_rectText.bottom    = pdrawitem->m_rectSubItem.bottom;
               return_(pdrawitem->m_bOk, true);
            }
         }
         pdrawitem->m_bOk = false;
      }

   }


   bool list::Range::HasItem(index iItem) const
   {
      for(index i = 0; i < m_itemrangea.get_size(); i++)
      {
         const ItemRange & itemrange = m_itemrangea[i];
         if(itemrange.HasItem(iItem))
            return true;
      }
      return false;
   }

   bool list::Range::HasSubItem(INT_PTR iItem, INT_PTR iSubItem) const
   {
      for(index i = 0; i < m_itemrangea.get_size(); i++)
      {
         const ItemRange & itemrange = m_itemrangea[i];
         if(itemrange.HasItem(iItem))
            if(itemrange.HasSubItem(iSubItem))
               return true;
      }
      return false;
   }

   // remove the specified item
   bool list::Range::RemoveItem(index iItem)
   {
      for(index i = 0; i < m_itemrangea.get_size();)
      {
         ItemRange & itemrange = m_itemrangea[i];
         if(itemrange.HasItem(iItem))
         {
            if(itemrange.GetLBound() == iItem)
            {
               itemrange.SetLBound(itemrange.GetLBound() + 1);
               if(itemrange.GetLBound() > itemrange.GetUBound())
               {
                  m_itemrangea.remove_at(i);
                  continue;
               }
            }
            else if(itemrange.GetUBound() == iItem)
            {
               itemrange.SetUBound(itemrange.GetUBound() - 1);
            }
            else
            {
               // split the current range as it will be segmented
               ItemRange itemrangeL;
               ItemRange itemrangeU;
               itemrangeL = itemrange;
               itemrangeU = itemrange;
               itemrangeL.SetUBound(iItem - 1);
               itemrangeU.SetLBound(iItem + 1);
               m_itemrangea.remove_at(i);
               m_itemrangea.add(itemrangeL);
               m_itemrangea.add(itemrangeU);
               continue;
            }
         }
         i++;
      }
      return false;
   }

   // remove the specified item and offset remaining items.
   bool list::Range::OnRemoveItem(index iItem)
   {
      RemoveItem(iItem);
      // All ranges that has item "iItem + 1",
      // must have all items greater or equal "iItem + 1"
      // decremented by one
      iItem++;
      for(index i = 0; i < m_itemrangea.get_size();)
      {
         ItemRange & itemrange = m_itemrangea[i];
         if(itemrange.HasItem(iItem))
         {
            if(itemrange.GetLBound() >= iItem)
            {
               itemrange.Offset(-1);
            }
            else if(itemrange.GetUBound() >= iItem)
            {
               itemrange.SetUBound(itemrange.GetUBound() - 1);
            }
         }
         i++;
      }
      return false;
   }


   bool list::ItemRange::HasItem(index iItem) const
   {
      if(m_iLBound == -1 || m_iUBound == -1)
         return false;
      if(iItem >= m_iLBound
         && iItem <= m_iUBound)
         return true;
      else
         return false;
   }

   bool list::ItemRange::HasSubItem(index iSubItem) const
   {
      return m_subitemrange.HasSubItem(iSubItem);
   }

   void list::LayoutHeaderCtrl()
   {
      if(m_bHeaderCtrl)
      {
         rect rectClient;

         _001GetViewClientRect(&rectClient);

         m_pheaderctrl->SetWindowPos(
            ZORDER_TOP,
            0, 0,
            max(m_iItemWidth + 10, rectClient.width()),
            m_iItemHeight,
            SWP_SHOWWINDOW);
      }
      else
      {
         m_pheaderctrl->ShowWindow(SW_HIDE);
      }
   }

   void list::_001OnKeyDown(gen::signal_object * pobj)
   {
      SCAST_PTR(::gen::message::key, pkey, pobj)
         if(pkey->previous()) // give chance to child
            return;
      if(pkey->m_nChar == VK_DOWN || pkey->m_nChar == VK_UP ||
         pkey->m_nChar == VK_NEXT || pkey->m_nChar == VK_PRIOR)
      {
         if(m_nItemCount > 0)
         {
            Range range = m_rangeSelection;
            m_rangeSelection.clear();

            INT_PTR iItem = m_iItemFocus;

            if(iItem < 0)
            {
               if(pkey->m_nChar == VK_DOWN || pkey->m_nChar == VK_NEXT)
               {
                  iItem = 0;
               }
               else if(pkey->m_nChar == VK_UP || pkey->m_nChar == VK_PRIOR)
               {
                  iItem = m_nItemCount - 1;
               }
            }
            else
            {
               if(pkey->m_nChar == VK_DOWN)
               {
                  iItem++;
               }
               else if(pkey->m_nChar == VK_NEXT)
               {
                  iItem += m_nDisplayCount;
               }
               else if(pkey->m_nChar == VK_UP)
               {
                  iItem--;
               }
               else if(pkey->m_nChar == VK_PRIOR)
               {
                  iItem -= m_nDisplayCount;
               }
               else
               {
                  ASSERT(FALSE);
                  pobj->m_bRet = false;
                  return;
               }
            }

            if(iItem < 0)
            {
               iItem = m_nItemCount - 1;
            }
            else if(iItem >= m_nItemCount)
            {
               iItem = 0;
            }

            m_iShiftFirstSelection = iItem;
            m_iItemFocus = iItem;

            ItemRange itemrange;
            itemrange.Set(iItem, iItem, 0, m_columna.get_count() - 1, - 1, -1);
            m_rangeSelection.add_item(itemrange);

            _001EnsureVisible(iItem, range);

            range.add_item(itemrange);

            _001RedrawWindow();

            _001OnSelectionChange();
         }
      }

      pobj->m_bRet = false;
   }

   void list::_001OnLButtonDown(gen::signal_object * pobj)
   {
      SCAST_PTR(::gen::message::mouse, pmouse, pobj)
      pmouse->previous(); // give chance to child control and to base views
      INT_PTR iItem;
      point pt = pmouse->m_pt;
      ScreenToClient(&pt);
      if(!m_bHoverSelect)
      {
         if(m_bMultiSelect && (pmouse->m_nFlags & MK_SHIFT))
         {
            if(_001DisplayHitTest(pt, iItem))
            {
               ItemRange itemrange;
               INT_PTR iLItem = min(m_iShiftFirstSelection, iItem);
               INT_PTR iUItem = max(m_iShiftFirstSelection, iItem);
               itemrange.Set(iLItem, iUItem, 0, m_columna.get_count() - 1, - 1, -1);
               m_rangeSelection.add_item(itemrange);
               m_iShiftFirstSelection = iItem;
            }
         }
         else if(m_bMultiSelect && (pmouse->m_nFlags & MK_CONTROL))
         {
            if(_001DisplayHitTest(pt, iItem))
            {
               ItemRange itemrange;
               INT_PTR iLItem = min(m_iShiftFirstSelection, iItem);
               INT_PTR iUItem = max(m_iShiftFirstSelection, iItem);
               itemrange.Set(iLItem, iUItem, 0, m_columna.get_count() - 1, - 1, -1);
               m_rangeSelection.add_item(itemrange);
               m_iShiftFirstSelection = iItem;
            }
         }
         else
         {
            m_rangeSelection.clear();
            index iItem;
            if(_001DisplayHitTest(pt, iItem))
            {
               m_iShiftFirstSelection = iItem;
               m_iItemFocus = iItem;
               _001DisplayHitTest(pt, m_iItemDrag);
               m_iItemDrop = m_iItemDrag;
               SetTimer(12345678, 400, NULL);
               ItemRange itemrange;
               itemrange.Set(iItem, iItem, 0, m_columna.get_count() - 1, - 1, -1);
               m_rangeSelection.add_item(itemrange);
            }
         }
      }

      _001RedrawWindow();
      if(!has_focus())
      {
         SetFocus();
      }
      Application.set_keyboard_focus(this);
      System.set_mouse_focus_LButtonDown(this);
      pobj->m_bRet = true;
      pmouse->set_lresult(1);
   }

   void list::_001OnLButtonUp(gen::signal_object * pobj)
   {
      SCAST_PTR(::gen::message::mouse, pmouse, pobj)
         point pt = pmouse->m_pt;
      ScreenToClient(&pt);

      if(m_bDrag)
      {
         m_bDrag = false;
         if(_001DisplayHitTest(pt, m_iItemDrop))
         {
            if(m_eview == ViewIcon)
            {
               if(m_iItemDrop != NULL)
               {
                  defer_drop(m_iItemDrop, m_iItemDrag);
               }
            }
            else
            {
               if(m_iItemDrag != m_iItemDrop && m_iItemDrop != -1)
               {
                  // swap
                  index i = m_listlayout.m_iaDisplayToStrict[m_iItemDrag];
                  m_listlayout.m_iaDisplayToStrict[m_iItemDrag] = m_listlayout.m_iaDisplayToStrict[m_iItemDrop];
                  m_listlayout.m_iaDisplayToStrict[m_iItemDrop] = i;
                  _001OnAfterSort();
               }
            }
         }
      }
      else
      {
         m_iClick++;
         m_uiLButtonUpFlags = pmouse->m_nFlags;
         m_ptLButtonUp = pt;
         SetTimer(12345679, 500, NULL);
         KillTimer(12345678);
      }
      pobj->m_bRet = true;
      pmouse->set_lresult(1);
   }

   void list::_001OnRButtonDown(gen::signal_object * pobj)
   {
      SCAST_PTR(::gen::message::mouse, pmouse, pobj)

      pmouse->previous();
      point pt = pmouse->m_pt;
      ScreenToClient(&pt);

      if(!has_focus())
      {
         SetFocus();
      }
      if(pmouse->m_nFlags & MK_SHIFT)
      {
      }
      else if(pmouse->m_nFlags & MK_CONTROL)
      {
      }
      else
      {
         //      m_rangeSelection.clear();
         index iItem;
         if(_001DisplayHitTest(pt, iItem))
         {
            if(!m_rangeSelection.HasItem(iItem))
            {
               m_rangeSelection.clear();
               m_iShiftFirstSelection = iItem;
               ItemRange itemrange;
               itemrange.Set(iItem, iItem, 0, m_columna.get_count() - 1, - 1, -1);
               m_rangeSelection.add_item(itemrange);
               _001RedrawWindow();
            }
         }
         m_uiRButtonUpFlags = pmouse->m_nFlags;
         m_ptRButtonUp = pt;
         SetTimer(8477, 500, NULL);
      }


      pobj->m_bRet = true;
   }


   void list::_001OnClick(UINT nFlag, point point)
   {
      UNREFERENCED_PARAMETER(nFlag);
      UNREFERENCED_PARAMETER(point);
      ::user::control_event ev;
      ev.m_puie = this;
      ev.m_eevent = ::user::event_list_clicked;
      if(m_pformcallback != NULL)
      {
         m_pformcallback->BaseOnControlEvent(NULL, &ev);
      }
      else if(get_form() != NULL)
      {
         get_form()->SendMessage(
            ::gen::message_event, 0, (LPARAM) &ev);
      }
      else
      {
         GetParent()->SendMessage(
            ::gen::message_event, 0, (LPARAM) &ev);
      }

   }

   void list::_001OnRightClick(UINT nFlag, point point)
   {
      UNREFERENCED_PARAMETER(nFlag);
      UNREFERENCED_PARAMETER(point);
   }

   void list::Range::clear()
   {
      m_itemrangea.remove_all();
   }

   void list::Range::add_item(const ItemRange & itemrange)
   {
      m_itemrangea.add(itemrange);
   }

   list::ItemRange::ItemRange()
   {
      m_iLBound = -1;
      m_iUBound = -1;
   }

   index list::ItemRange::GetLBound() const
   {
      return m_iLBound;
   }

   index list::ItemRange::GetUBound() const
   {
      return m_iUBound;
   }



   list::ItemRange::ItemRange(ItemRange & itemrange)
   {
      operator =(itemrange);
   }

   list::ItemRange & list::ItemRange::operator =(const ItemRange & itemrange)
   {
      m_iLBound         = itemrange.m_iLBound;
      m_iUBound         = itemrange.m_iUBound;
      m_subitemrange    = itemrange.m_subitemrange;
      return *this;
   }



   list::CSubItemRange::CSubItemRange()
   {
      m_iLBound = -1;
      m_iUBound = -1;
   }

   list::CSubItemRange::CSubItemRange(CSubItemRange & subitemrange)
   {
      operator =(subitemrange);
   }

   list::CSubItemRange & list::CSubItemRange::operator =(const CSubItemRange & subitemrange)
   {
      m_iLBound         = subitemrange.m_iLBound;
      m_iUBound         = subitemrange.m_iUBound;
      m_listitemrange   = subitemrange.m_listitemrange;
      return *this;
   }

   bool list::CSubItemRange::HasSubItem(index iSubItem) const
   {
      if(m_iLBound == -1 || m_iUBound == -1)
         return false;
      if(iSubItem >= m_iLBound
         && iSubItem <= m_iUBound)
         return true;
      else
         return false;
   }


   list::Range & list::Range::operator = (const Range & range)
   {
      m_itemrangea.copy(range.m_itemrangea);
      return *this;
   }

   void list::_001GetSelection(Range &range)
   {
      range = m_rangeSelection;
   }

   void list::_001GetSelection(
                                           ::database::id & key,
                                           ::database::selection &selection)
   {
      if(!_001HasConfigId(key))
         return;
      INT_PTR iFilterSubItem = _001ConfigIdToColumnKey(key);
      Range & range = m_rangeSelection;
      for(index i = 0; i < range.get_item_count(); i++)
      {
         ItemRange & itemrange = range.ItemAt(i);
         if(itemrange.HasSubItem(iFilterSubItem))
         {
            for(index iLine = itemrange.GetLBound();
               iLine <= itemrange.GetUBound(); iLine++)
            {
               selection.add_item(key, iLine);
            }
         }
      }
   }


   /*index list::Range::get_item(index iItemIndex)
   {
   index iFirst = 0;
   index i = 0;
   index iItem;

   while(true)
   {
   if(i >= m_itemrangea.get_size())
   return -1;
   iItem = iItemIndex - iFirst;
   ItemRange & itemrange = m_itemrangea[i];
   if(iItem < itemrange.get_count())
   {
   return itemrange.get_item(iItem);
   }
   iFirst += itemrange.get_count();
   i++;
   }



   }*/

   /*index list::ItemRange::get_count()
   {
   return m_iItemEnd - m_iItemStart + 1;
   }*/

   /*index list::ItemRange::get_item(index iItemIndex)
   {
   return m_iItemStart + iItemIndex;
   }*/

   count list::Range::get_item_count() const
   {
      return m_itemrangea.get_size();
      /*   index iCount = 0;

      for(index i = 0; i < m_itemrangea.get_size(); i++)
      {
      ItemRange & itemrange = m_itemrangea[i];
      iCount += itemrange.get_count();
      }

      return iCount;*/
   }

   list::ItemRange & list::Range::ItemAt(index iItem)
   {
      return m_itemrangea.element_at(iItem);
   }

   count list::_001GetSelectedItemCount()
   {
      return m_rangeSelection.get_item_count();
   }

   id list::_001GetColumnTextId(index iColumn)
   {
      UNREFERENCED_PARAMETER(iColumn);
      return -1;
   }

   void list::_001OnLButtonDblClk(gen::signal_object * pobj)
   {
      SCAST_PTR(::gen::message::mouse, pmouse, pobj)
         m_iClick = 2;

      //   _001OnClick(nFlags, point);
      Redraw();


      /* trans window_id wndidNotify = pwnd->GetOwner()->GetSafeHwnd();
      if(wndidNotify == NULL)
      wndidNotify = pwnd->GetParent()->GetSafeHwnd();*/


      LRESULT lresult = 0;

      /* trans if(wndidNotify)
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

      if(lresult == 0)
      {
         pmouse->m_bRet = false;
         return;
      }
      else
      {
         pmouse->m_bRet = true;
         return;
      }
   }

   void list::HeaderCtrlLayout()
   {
      m_pheaderctrl->SetWindowPos(
         ZORDER_TOP,
         -m_scrollinfo.m_ptScroll.x,
         0,
         0, 0,
         SWP_NOSIZE
         | SWP_SHOWWINDOW);
   }

   index list::HeaderCtrlMapColumnToOrder(index iColumn)
   {
      return m_pheaderctrl->MapItemToOrder(iColumn);
      for(index iOrder = 0; iOrder < _001GetColumnCount() ; iOrder++)
      {
         //      if(m_pheaderctrl->GetItemLParam(iOrder) == iColumn)
         //         return iOrder;
      }
      ASSERT(FALSE);
      return -1;
   }

   bool list::_001OnHeaderCtrlEndDrag(WPARAM wparam, LPARAM lparam)
   {
      UNREFERENCED_PARAMETER(wparam);
      UNREFERENCED_PARAMETER(lparam);
      for(index iColumn = 0; iColumn < m_columna.VisibleGetCount(); iColumn++)
      {
         list_column * pcolumn = m_columna._001GetVisible(iColumn);
         pcolumn->m_iOrder = HeaderCtrlMapColumnToOrder(iColumn);
      }

      _001OnColumnChange();

      DISaveOrder();

      Redraw();

      return true;

   }

   /*LRESULT list::OnEndColumnHeaderDragMessage(WPARAM wparam, LPARAM lparam)
   {
   HeaderCtrlOnEndDrag();
   return 0;
   }*/

   /*LRESULT list::OnEndColumnHeaderTrackMessage(WPARAM wparam, LPARAM lparam)
   {
   HeaderCtrlOnEndTrack();
   return 0;
   }*/

   /*LRESULT list::OnColumnHeaderTrackMessage(WPARAM wparam, LPARAM lparam)
   {
   HeaderCtrlOnTrack();
   return 0;
   }*/

   bool list::_001OnHeaderCtrlEndTrack(WPARAM wparam, LPARAM lparam)
   {
      UNREFERENCED_PARAMETER(wparam);
      UNREFERENCED_PARAMETER(lparam);
      _001OnHeaderCtrlTrack(0, 0);

      string str;
      index i;
      index width;

      for(i = 0; i < m_columna.get_count(); i++)
      {
         str.Format("list_column[%d].width", i);
         width = m_columna.element_at(i).m_iWidth;
         data_set(
            str,
            ::radix::system::idEmpty,
            width);
      }

      return true;
   }

   bool list::_001OnHeaderCtrlTrack(WPARAM wparam, LPARAM lparam)
   {
      UNREFERENCED_PARAMETER(wparam);
      UNREFERENCED_PARAMETER(lparam);
  //    for(index iColumn = 0; iColumn < m_columna.VisibleGetCount(); iColumn++)
    //  {
//         list_column & column = m_columna._001GetVisible(iColumn);
         //column.m_iWidth = m_pheaderctrl->GetItemWidth(iColumn);
      //}

      _001OnColumnChange();

      Redraw();

      return true;
   }

   void list::_001ShowSubItem(index iSubItem, bool bShow)
   {
      string str;
      str.Format("SubItem[%d].Visible", iSubItem);
      data_set(
         str,
         ::radix::system::idEmpty,
         bShow ? 1 : 0);
      m_columna.ShowSubItem(iSubItem, bShow);
      _001OnColumnChange();
      Redraw();

   }

   list_column * list_column_array::_001GetByKey(index iKey)
   {

      for(index i = 0; i < this->get_size(); i++)
      {
         list_column * pcolumn = ptr_at(i);
         if(pcolumn->m_iKey == iKey)
         {
            return pcolumn;
         }
      }

      return NULL;

   }

   list_column * list_column_array::_001GetBySubItem(index iSubItem)
   {
      for(index i = 0; i < this->get_size(); i++)
      {
         list_column * pcolumn = ptr_at(i);
         if(pcolumn->m_iSubItem == iSubItem)
         {
            if(pcolumn->m_bVisible)
            {
               return pcolumn;
            }
            else
            {
               return NULL;
            }
         }
      }
      return NULL;

   }

   list_column * list_column_array::GlobalOrderGetPrevious(index iKey)
   {
      for(index i = 0; i < this->get_size(); i++)
      {
         list_column * pcolumn = ptr_at(i);
         if(pcolumn->m_iNextGlobalOrderKey == iKey)
         {
            return pcolumn;
         }
      }
      return NULL;
   }

   list_column * list_column_array::GlobalOrderGetNext(index iKey)
   {
      list_column * pcolumn = _001GetByKey(iKey);
      return _001GetByKey(pcolumn->m_iNextGlobalOrderKey);
   }

   list_column * list_column_array::_001GetVisible(index iKeyVisible)
   {
      for(index i = 0; i < this->get_size(); i++)
      {
         list_column * pcolumn = ptr_at(i);
         if(pcolumn->m_iKeyVisible == iKeyVisible)
         {
            return pcolumn;
         }
      }
      return NULL;

   }
   list_column * list_column_array::_001GetNonVisible(index iKeyNonVisible)
   {
      for(index i = 0; i < this->get_size(); i++)
      {
         list_column * pcolumn = ptr_at(i);
         if(pcolumn->m_iKeyNonVisible == iKeyNonVisible)
         {
            return pcolumn;
         }
      }
      return NULL;

   }

   index list_column_array::add(list_column &column)
   {
      column.m_iKey = this->get_size();
      column.m_iOrder = this->get_size();
      column.m_pcontainer = this;

      index index = array_ptr_alloc < list_column >::add(column);

      OnChange();

      return index;
   }

   void list_column_array::remove_all()
   {
      array_ptr_alloc < list_column >::remove_all(),
         OnChange();
   }

   count list_column_array::get_count()
   {
      return this->get_size();
   }

   list_column_array::list_column_array(::ca::application * papp) :
   ca(papp)
   {
      m_plist = NULL;
   }

   void list_column_array::Initialize(list * plist)
   {
      ASSERT(plist != NULL);
      m_plist = plist;
   }

   void list_column_array::OnChange()
   {
      sort::array::quick_sort(m_ptra, list_column::CompareKey);

      index iKeyVisible = 0;
      index iKeyNonVisible = 0;

      for(index i = 0; i < this->get_size(); i++)
      {
         list_column * pcolumn = ptr_at(i);
         if(pcolumn->m_bVisible)
         {
            pcolumn->m_iKeyVisible = iKeyVisible;
            pcolumn->m_iKeyNonVisible = -1;
            iKeyVisible++;
         }
         else
         {
            pcolumn->m_iKeyNonVisible = iKeyNonVisible;
            pcolumn->m_iKeyVisible = -1;
            iKeyNonVisible++;
         }
      }

      sort::array::quick_sort(m_ptra, list_column::CompareOrderSectEndNonVisible);

      for(index iOrder = 0; iOrder < this->get_size(); iOrder++)
      {
         list_column & column = this->element_at(iOrder);
         column.m_iOrder = iOrder;
      }



   }

   void list_column_array::remove(index iColumn)
   {
      ASSERT(iColumn >= 0);
      ASSERT(iColumn < this->get_size());

      remove_at(iColumn);

      OnChange();
   }

   count list_column_array::VisibleGetCount()
   {
      index iCount = 0;
      for(index i = 0; i < this->get_size(); i++)
      {
         list_column * pcolumn = ptr_at(i);
         if(pcolumn->m_bVisible)
            iCount++;
      }
      return iCount;
   }

   count list_column_array::NonVisibleGetCount()
   {
      index iCount = 0;
      for(index i = 0; i < this->get_size(); i++)
      {
         list_column * pcolumn = ptr_at(i);
         if(!pcolumn->m_bVisible)
            iCount++;
      }
      return iCount;
   }

   void list_column_array::ShowSubItem(index iSubItem, bool bShow)
   {
      if(bShow)
      {
         index iColumn = NonVisibleMapSubItemToColumn(iSubItem);
         if(iColumn >= 0)
         {
            list_column * pcolumn = _001GetNonVisible(iColumn);
            pcolumn->m_bVisible = true;
            OnChange();
         }
      }
      else
      {
         index iColumn = VisibleMapSubItemToColumn(iSubItem);
         if(iColumn >= 0)
         {
            list_column * pcolumn = _001GetVisible(iColumn);
            pcolumn->m_bVisible = false;
            OnChange();
         }
      }
   }

   index list_column_array::_001GetSubItemKey(index iSubItem)
   {
      list_column * pcolumn = _001GetBySubItem(iSubItem);
      if(pcolumn == NULL)
         return -1;
      return pcolumn->m_iKey;
   }

   index list_column_array::VisibleMapSubItemToColumn(index iSubItem)
   {
      int iVisible = 0;
      for(index iColumn = 0; iColumn < this->get_count(); iColumn++)
      {
         list_column * pcolumn = ptr_at(iColumn);
         if(pcolumn->m_bVisible)
         {
            if(pcolumn->m_iSubItem == iSubItem)
            {
               return iVisible;
            }
            else
            {
               iVisible++;
            }
         }
      }
      return -1;
   }

   index list_column_array::NonVisibleMapSubItemToColumn(index iSubItem)
   {
      int iNonVisible = 0;
      for(index iColumn = 0; iColumn < this->get_count(); iColumn++)
      {
         list_column * pcolumn = ptr_at(iColumn);
         if(!pcolumn->m_bVisible)
         {
            if(pcolumn->m_iSubItem == iSubItem)
            {
               return iNonVisible;
            }
            else
            {
               iNonVisible++;
            }
         }
      }
      return -1;

   }



   void list_column_array::GlobalToVisibleOrder()
   {
      INT_PTR iVisibleCount = VisibleGetCount();
      for(index iVisibleKey = 0; iVisibleKey < iVisibleCount; iVisibleKey++)
      {
         list_column * pcolumn = _001GetVisible(iVisibleKey);
         pcolumn->m_iOrder = VisibleGetOrderFromKey(pcolumn->m_iKey);
      }


   }

   void list_column_array::VisibleToGlobalOrder(index iKeyA, index iKeyB)
   {
      if(iKeyA == iKeyB)
         return;
      list_column * columnA = _001GetByKey(iKeyA);
      list_column * columnAPrevious = GlobalOrderGetPrevious(iKeyA);
      list_column * columnANext = GlobalOrderGetNext(iKeyA);
      list_column * columnB = _001GetByKey(iKeyB);
      list_column * columnBPrevious = GlobalOrderGetPrevious(iKeyB);
      list_column * columnBNext = GlobalOrderGetNext(iKeyB);

      if(columnA == NULL)
         return;

      if(columnB == NULL)
         return;

      if(columnAPrevious == NULL)
      {
         m_iFirstGlobalOrderKey = iKeyB;
      }
      else
      {
         if(columnAPrevious->m_iKey != iKeyB)
         {
            columnAPrevious->m_iNextGlobalOrderKey = iKeyB;
         }
      }


      if(columnBPrevious == NULL)
      {
         m_iFirstGlobalOrderKey = iKeyA;
      }
      else
      {
         if(columnBPrevious->m_iKey != iKeyA)
         {
            columnBPrevious->m_iNextGlobalOrderKey = iKeyA;
         }
      }

      if(columnANext == NULL)
      {
         columnB->m_iNextGlobalOrderKey = -1;
      }
      else
      {
         if(columnANext->m_iKey == columnB->m_iKey)
         {
            columnB->m_iNextGlobalOrderKey = iKeyA;
         }
         else
         {
            columnB->m_iNextGlobalOrderKey = columnANext->m_iKey;
         }
      }

      if(columnBNext == NULL)
      {
         columnA->m_iNextGlobalOrderKey = -1;
      }
      else
      {
         if(columnBNext->m_iKey == columnA->m_iKey)
         {
            columnB->m_iNextGlobalOrderKey = iKeyB;
         }
         else
         {
            columnA->m_iNextGlobalOrderKey = columnBNext->m_iKey;
         }
      }



   }

   void list_column_array::VisibleToGlobalOrder()
   {
      list * plist = m_plist;
      //detects change
      INT_PTR iVisibleCount = VisibleGetCount();
      INT_PTR iChangeCount = 0;
      INT_PTR iNew;
      INT_PTR iOld;
      for(INT_PTR iVisibleKey = 0; iVisibleKey < iVisibleCount; iVisibleKey++)
      {
         list_column * column = _001GetVisible(iVisibleKey);
         if(VisibleGetOrderFromKey(column->m_iKey) != plist->HeaderCtrlMapColumnToOrder(iVisibleKey))
         {
            iChangeCount++;
            if(iChangeCount == 1)
            {
               iNew = iVisibleKey;
            }
            else if(iChangeCount == 2)
            {
               iOld = iVisibleKey;
            }
         }
      }
      if(iChangeCount == 2)
      {
         VisibleToGlobalOrder(iNew, iOld);
      }
      else
      {
         if(this->get_size() == VisibleGetCount())
         {
            for(index iColumn = 0; iColumn < VisibleGetCount(); iColumn++)
            {
               list_column * column = _001GetVisible(iColumn);
               column->m_iOrder = plist->HeaderCtrlMapColumnToOrder(iColumn);
            }

            m_iFirstGlobalOrderKey = OrderToKey(0);
            if(m_iFirstGlobalOrderKey >= 0)
            {
               index iKey = m_iFirstGlobalOrderKey;
               index iNextKey;
               index iOrder = 1;

               while(true)
               {
                  iNextKey = OrderToKey(iOrder);
                  _001GetByKey(iKey)->m_iNextGlobalOrderKey = iNextKey;
                  if(iNextKey < 0)
                  {
                     break;
                  }
                  iOrder++;
                  iKey = iNextKey;
               }
            }
         }

      }
   }

   void list_column_array::DISaveOrder()
   {
      INT_PTR iCount = this->get_size();
      string str;
      for(index iKey = 0; iKey < iCount; iKey++)
      {
         list_column * column = _001GetByKey(iKey);
         str.Format("list_column[%d].Next", iKey);
         m_plist->data_set(
            str,
            ::radix::system::idEmpty,
            column->m_iNextGlobalOrderKey);
      }
      str.Format("list_column[-1].Next");
      m_plist->data_set(
         str,
         ::radix::system::idEmpty,
         m_iFirstGlobalOrderKey);


   }

   void list_column_array::DILoadOrder()
   {
      INT_PTR iCount = this->get_size();
      string str;
      for(index iKey = 0; iKey < iCount; iKey++)
      {
         list_column * column = _001GetByKey(iKey);
         str.Format("list_column[%d].Next", iKey);
         m_plist->data_get(
            str,
            ::radix::system::idEmpty,
            column->m_iNextGlobalOrderKey);
      }
      str.Format("list_column[-1].Next");
      m_plist->data_get(
         str,
         ::radix::system::idEmpty,
         m_iFirstGlobalOrderKey);

      GlobalToVisibleOrder();
      OnChange();

   }

   index list_column_array::VisibleGetOrderFromKey(index iKey)
   {
      index iNextKey = m_iFirstGlobalOrderKey;
      index iOrder = 0;
      while(true)
      {
         list_column * column = _001GetByKey(iNextKey);
         if(column == NULL)
            return -1;
         if(column->m_bVisible)
         {
            if(iKey == iNextKey)
               return iOrder;
            iOrder++;
         }
         else
         {
            if(iKey == iNextKey)
               return -1;
         }
         if(iOrder > VisibleGetCount())
            return -1;
         iNextKey = column->m_iNextGlobalOrderKey;
      }
      ASSERT(FALSE);
      return -1;
   }

   index list_column_array::OrderToKey(index iOrder)
   {
      for(index iKey = 0; iKey < this->get_count(); iKey++)
      {
         list_column * column = _001GetByKey(iKey);
         if(column->m_iOrder == iOrder)
            return iKey;
      }
      return -1;

      /*   index iNextKey = m_iFirstGlobalOrderKey;
      index iOrder = 0;
      while(true)
      {
      list_column & column = get(iNextKey);
      if(column.IsNull())
      return -1;
      if(column.IsVisible())
      {
      if(iOrderParam == iOrder)
      {
      return iNextKey;
      }
      iOrder++;
      }
      else
      {
      if(iOrderParam == iOrder)
      {
      return -1;
      }
      }
      if(iOrder > VisibleGetCount())
      return -1;
      iNextKey = column.m_iNextGlobalOrderKey;
      }
      ASSERT(FALSE);
      return -1;*/
   }

   void list::DISaveOrder()
   {
      m_columna.VisibleToGlobalOrder();
      m_columna.DISaveOrder();

   }

   void list::DILoadOrder()
   {
      m_columna.DILoadOrder();
      _001OnColumnChange();
   }





   /*bool list::_001WndInterfaceProc(UINT message, WPARAM wparam, LPARAM lparam, LRESULT & lresult)
   {
   if(C001TransparentWndInterface::_000WndProc(message, wparam, lparam, lresult))
   return true;

   if(message == MESSAGE_ENDCOLUMNHEADERDRAG)
   return _001OnHeaderCtrlEndDrag(wparam, lparam);
   else if(message == MESSAGE_COLUMNHEADERTRACK)
   return _001OnHeaderCtrlTrack(wparam, lparam);
   else if(message == MESSAGE_ENDCOLUMNHEADERTRACK)
   return _001OnHeaderCtrlEndTrack(wparam, lparam);

   return FALSE;
   }*/




   void list::_001UpdateColumns()
   {
      _001RemoveAllColumns();
      keeper < bool > keepLockViewUpdate(&m_bLockViewUpdate, true, false, true);
      _001InsertColumns();
      keepLockViewUpdate.KeepAway();
      DIDDXHeaderLayout(false);
      _001OnColumnChange();
      layout();
      RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE | RDW_ALLCHILDREN);
   }

   void list::_001InsertColumns()
   {


   }

   void list::_001RemoveAllColumns()
   {
      m_columna.remove_all();
      _001OnColumnChange();
   }




   bool list::TwiHasTranslucency()
   {
      return !m_scrollinfo.m_bVScroll;
   }

   void list::_001SetBackBuffer(visual::CBuffer *ptwb)
   {
      UNREFERENCED_PARAMETER(ptwb);
      //   m_pgdibuffer = ptwb;
   }


   void list::PreSubClassWindow()
   {
      //   ::user::window_interface::PreSubClassWindow();
      if(IsWindowVisible())
      {
         RedrawWindow(NULL, NULL, RDW_INVALIDATE);
      }
   }

   void list::_001OnCreate(gen::signal_object * pobj)
   {
      SCAST_PTR(::gen::message::create, pcreate, pobj)


         pobj->previous();

      
      m_font->operator=(*System.font_central().GetListCtrlFont());
      m_fontHover->operator=(*System.font_central().GetListCtrlFont());

      m_fontHover->set_underline();
      m_fontHover->set_bold();

         if(pcreate->get_lresult() == -1)
         {
            pobj->m_bRet = false;
            return;
         }

         if(m_pheaderctrl != NULL)
         {
            if(!CreateHeaderCtrl())
            {
               pcreate->set_lresult(-1);
               pobj->m_bRet = true;
               return;
            }
         }

         class rect rect;
         rect.null();


         layout();

         pcreate->set_lresult(0);

         if(IsWindowVisible())
         {
            _001RedrawWindow();
         }

         pobj->m_bRet = false;


   }

   void list::_001CreateImageList(list_column * pcolumn)
   {

      if(pcolumn == NULL)
         return;

      if(pcolumn->m_uiSmallBitmap == (UINT) -1 )
      {
         return;
      }
      if(pcolumn->m_pil == NULL)
      {
         pcolumn->m_pil = new image_list(get_app());
      }
//      image_list * pil = column.m_pil;
      //   if(pil != NULL)
      //      pil->DeleteImageList();
      throw not_implemented_exception();
      /*if(!pil->create(
         MAKEINTRESOURCE(column.m_uiSmallBitmap),
         column.m_iSmallImageWidth,
         0,
         column.m_crSmallMask))
      {
      }*/
   }


   void list::_001OnTimer(gen::signal_object * pobj)
   {
      SCAST_PTR(::gen::message::timer, ptimer, pobj);
      if(ptimer->m_nIDEvent == 12345679) // left click
      {
         KillTimer(12345679);
         if(m_iClick == 1)
         {
            m_iClick = 0;
            if(!_001IsEditing())
            {
               UINT nFlags = m_uiLButtonUpFlags;
               point point = m_ptLButtonUp;
               _001OnClick(nFlags, point);
               Redraw();


               /* trans
               window_id wndidNotify = pwnd->GetOwner()->GetSafeHwnd();
               if(wndidNotify == NULL)
               wndidNotify = pwnd->GetParent()->GetSafeHwnd(); */

//               LRESULT lresult = 0;

               /* trans            if(wndidNotify)
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
         }
         else
         {
            m_iClick = 0;
         }


      }
      else if(ptimer->m_nIDEvent == 8477) // right click
      {
         KillTimer(8477);
         //if(!_001IsEditing())
         {
            UINT nFlags = m_uiLButtonUpFlags;
            point point = m_ptLButtonUp;
            _001OnRightClick(nFlags, point);
            Redraw();


            /* trans
            window_id wndidNotify = pwnd->GetOwner()->GetSafeHwnd();
            if(wndidNotify == NULL)
            wndidNotify = pwnd->GetParent()->GetSafeHwnd(); */

//            LRESULT lresult = 0;

            /* trans            if(wndidNotify)
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
      }
      else if(ptimer->m_nIDEvent == 0xfffffffe)
      {
         if(!Filter1Step())
            KillTimer(ptimer->m_nIDEvent);
      }
      else if(ptimer->m_nIDEvent == 12345678)
      {
         KillTimer(ptimer->m_nIDEvent);
         m_bDrag = true;
      }
      else if(ptimer->m_nIDEvent == 12321)
      {
         KillTimer(ptimer->m_nIDEvent);
         index iItemSel;
         index iSubItemSel;
         point point;
         Application.get_cursor_pos(&point);
         ScreenToClient(&point);
         try
         {
            if(_001DisplayHitTest(point, iItemSel, iSubItemSel))
            {
               if(m_iSubItemEnter == iSubItemSel &&
                  m_iItemEnter == iItemSel)
               {
                  m_iSubItemEnter = -1;
                  m_iItemEnter = -1;
                  bool bLShiftKeyDown     = (GetAsyncKeyState (VK_LSHIFT)      >> ((sizeof(SHORT) * 8) - 1)) != 0;
                  bool bRShiftKeyDown     = (GetAsyncKeyState (VK_RSHIFT)      >> ((sizeof(SHORT) * 8) - 1)) != 0;
                  bool bLControlKeyDown   = (GetAsyncKeyState (VK_LCONTROL)    >> ((sizeof(SHORT) * 8) - 1)) != 0;
                  bool bRControlKeyDown   = (GetAsyncKeyState (VK_RCONTROL)    >> ((sizeof(SHORT) * 8) - 1)) != 0;
                  bool bShiftKeyDown      = bLShiftKeyDown     || bRShiftKeyDown;
                  bool bControlKeyDown    = bLControlKeyDown   || bRControlKeyDown;

                  if(m_bMultiSelect && bShiftKeyDown)
                  {
                     if(bControlKeyDown)
                     {
                        ItemRange itemrange;
                        itemrange.Set(
                           min(iItemSel, m_iItemSel),
                           max(iItemSel, m_iItemSel),
                           min(iSubItemSel, m_iSubItemSel),
                           max(iSubItemSel, m_iSubItemSel),
                           -1,
                           -1);
                        _001AddSelection(itemrange);
                     }
                     else
                     {
                        ItemRange itemrange;
                        itemrange.Set(
                           min(iItemSel, m_iItemSel),
                           max(iItemSel, m_iItemSel),
                           min(iSubItemSel, m_iSubItemSel),
                           max(iSubItemSel, m_iSubItemSel),
                           -1,
                           -1);
                        Range range;
                        range.add_item(itemrange);
                        _001SetSelection(range);
                     }
                  }
                  else if(m_bMultiSelect && bControlKeyDown)
                  {
                     m_iLastItemSel = m_iItemSel;
                     m_iLastSubItemSel = m_iSubItemSel;
                     m_iItemSel = iItemSel;
                     m_iSubItemSel = iSubItemSel;
                     ItemRange itemrange;
                     itemrange.Set(
                        m_iItemSel,
                        m_iItemSel,
                        m_iSubItemSel,
                        m_iSubItemSel,
                        -1,
                        -1);
                     _001AddSelection(itemrange);
                  }
                  else
                  {
                     m_iLastItemSel = m_iItemSel;
                     m_iLastSubItemSel = m_iSubItemSel;
                     m_iItemSel = iItemSel;
                     m_iSubItemSel = iSubItemSel;
                     ItemRange itemrange;
                     itemrange.Set(
                        m_iItemSel,
                        m_iItemSel,
                        m_iSubItemSel,
                        m_iSubItemSel,
                        -1,
                        -1);
                     Range range;
                     range.add_item(itemrange);
                     _001SetSelection(range);
                  }
               }
            }
         }
         catch(...)
         {
         }
         m_iSubItemEnter = -1;
         m_iItemEnter = -1;

      }

      ptimer->m_bRet = false;
   }

   bool list::_001IsItemVisible(index iItem)
   {
      draw_list_item item(this);
      item.m_iItem         = iItem;
      item.m_iDisplayItem  = iItem;
      _001GetItemRect(&item);
      if(!item.m_bOk)
      {
         return false;
      }
      rect rectClient;
      _001GetViewClientRect(&rectClient);
      return rectClient.intersect(rectClient, item.m_rectItem) != 0;
   }

   void list::_001ClearSelection()
   {
      m_rangeSelection.clear();
      _001OnSelectionChange();
   }

   void list::_001SetSelection(const Range &range)
   {
      m_rangeSelection = range;
      on_select();
      _001OnSelectionChange();
   }

   void list::_001AddSelection(const ItemRange & itemrange)
   {
      m_rangeSelection.add_item(itemrange);
      on_select();
      _001OnSelectionChange();
   }

   void list::_001SetHighlightRange(Range & range)
   {
      m_rangeHighlight = range;
   }

   void list::DIOnSectionSet()
   {
      string str;
      str = m_dataid.get_id();
      str += ".headerctrl";
      if(m_pheaderctrl != NULL)
      {
         m_pheaderctrl->m_dataid = str;
      }
   }

   bool list::DIDDXHeaderLayout(bool bSave)
   {
      return m_pheaderctrl->DIDDXLayout(bSave);
   }

   void list::_001SetTopText(const wchar_t * lpcwsz)
   {
      m_strTopText = lpcwsz;
      _001LayoutTopText();
   }

   void list::_001LayoutTopText()
   {
      ::ca::font * pfont = _001GetFont();
      ::ca::graphics * pdc = GetDC();
      pdc->SelectObject(pfont);
      base_array < size > sizea;
      m_dcextension.GetTextExtent(pdc, m_strTopText, sizea);
      rect rectClient;
      GetClientRect(rectClient);
      index x = 0;
      index right = rectClient.right;
      index y = 0;
      for(index i = 0; i < sizea.get_size(); i++)
      {
         if((sizea[i].cx - x > right)
            || i == sizea.get_upper_bound() )
         {
            if(i == 0)
            {
               x = sizea[0].cx;
               y += sizea[0].cy;
            }
            else
            {
               x = sizea[i - 1].cx;
               y += sizea[i - 1].cy;
            }
         }
      }

      m_rectTopText.left = 0;
      m_rectTopText.top = 0;
      m_rectTopText.right = rectClient.right;
      m_rectTopText.bottom = y;
      ReleaseDC(pdc);

   }

   void list::_001ShowTopText(bool bShow)
   {
      m_bTopText = bShow;
   }



   /*void list::InstallMessageHandling(MessageDispatch *pinterface)
   {
   /*   m_lpfnOnSize = (_001_ON_SIZE) _001OnSize;
   m_lpfnOnVScroll = (_001_ON_VSCROLL) _001OnVScroll;
   m_lpfnOnHScroll = (_001_ON_HSCROLL) _001OnHScroll;
   m_lpfnOnPaint = (_001_ON_PAINT) _001OnPaint;
   m_lpfnOnLButtonDown = (_001_ON_LBUTTONDOWN) _001OnLButtonDown;
   m_lpfnOnLButtonUp =(_001_ON_LBUTTONUP) _001OnLButtonUp;
   m_lpfnOnLButtonDblClk =(_001_ON_LBUTTONDBLCLK)_001OnLButtonDblClk;
   m_lpfnOnCreate = (_001_ON_CREATE) _001OnCreate;
   m_lpfnOnTimer = (_001_ON_TIMER) _001OnTimer;*/

   /*   VMSGEN_WINDOW_ON_SIZE_CONDITIONAL(
   pinterface,
   this,
   _001OnSize);

   VMSGEN_WINDOW_ON_VSCROLL_CONDITIONAL(
   pinterface,
   this,
   _001OnVScroll);

   VMSGEN_WINDOW_ON_HSCROLL_CONDITIONAL(
   pinterface,
   this,
   _001OnHScroll);

   VMSGEN_WINDOW_ON_LBUTTONDOWN_CONDITIONAL(
   pinterface,
   this,
   _001OnLButtonDown);

   VMSGEN_WINDOW_ON_LBUTTONUP_CONDITIONAL(
   pinterface,
   this,
   _001OnLButtonUp);

   VMSGEN_WINDOW_ON_LBUTTONDBLCLK_CONDITIONAL(
   pinterface,
   this,
   _001OnLButtonDblClk);

   VMSGEN_WINDOW_ON_CREATE_CONDITIONAL(
   pinterface,
   this,
   _001OnLButtonCreate);

   VMSGEN_WINDOW_ON_TIMER_CONDITIONAL(
   pinterface,
   this,
   _001OnLButtonTimer);
   }*/

   void list::SetCacheInterface(list_cache_interface * pinterface)
   {
      m_pcache = pinterface;
   }

   void list::CacheHint()
   {
      if(m_pcache != NULL)
      {
         INT_PTR iItemCount = m_nDisplayCount;
         INT_PTR iItemFirst = m_iTopIndex;
         m_pcache->_001CacheHint(
            this,
            iItemFirst,
            iItemCount);
      }

   }


   void list::SetDataInterface(::user::list_data *pinterface)
   {
      m_pdata = pinterface;
   }

   bool list::_001InsertColumn(list_column &column)
   {

      _001AddColumn(column);
      _001OnColumnChange();
      return true;
   }

   void list::_001SetSingleColumnMode(bool bHeaderCtrl)
   {

      m_bSingleColumnMode = true;

      m_bHeaderCtrl = bHeaderCtrl;
      _001RemoveAllColumns();

      list_column column;
      column.m_iWidth = -1;
      column.m_iSubItem = 0;
      column.m_iSmallImageWidth = 16;
      column.m_crSmallMask = ARGB(255, 255, 0, 255);


      _001InsertColumn(column);

      layout();



   }

   int list::_001CalcItemWidth(index iItem, index iSubItem)
   {
      ::ca::graphics * pdc = GetDC();
      ::ca::font * pfont = _001GetFont();
      index cx = _001CalcItemWidth(pdc, pfont, iItem, iSubItem);
      ReleaseDC(pdc);
      return cx;

   }

   int list::_001CalcItemWidth(::ca::graphics * pdc, ::ca::font * pfont, index iItem, index iSubItem)
   {
      pdc->SelectObject(pfont);
      return _001CalcItemWidth(pdc, iItem, iSubItem);
   }

   int list::_001CalcItemWidth(::ca::graphics * pdc, index iItem, index iSubItem)
   {
      IMAGEINFO ii;
      rect rect;
      size size;
      index cx = 0;
      list_column * pcolumn = m_columna._001GetByKey(iSubItem);
      draw_list_item item(this);
      item.m_iItem = iItem;
      item.m_iSubItem = iSubItem;
      item.m_iListItem = -1;
      if(pcolumn->m_pil != NULL)
      {
         _001GetItemImage(&item);
         if(item.m_bOk && item.m_iImage >= 0)
         {
            pcolumn->m_pil->get_image_info(item.m_iImage, &ii);
            rect = ii.rcImage;
            cx += rect.width();
            cx += 2;
         }
      }
      _001GetItemText(&item);
      if(item.m_bOk)
      {
         m_dcextension.GetTextExtent(pdc, item.m_strText, size);
         cx += size.cx;
      }

      return cx;
   }




   bool list::_001HasConfigId(const ::database::id & key)
   {
      return _001ConfigIdToColumnKey(key) >= 0;
   }

   index list::_001ConfigIdToSubItem(const ::database::id & key)
   {
      list_column * column = m_columna._001GetByConfigId(key);
      if(column == NULL)
         return -1;
      return column->m_iSubItem;
   }

   index list::_001ConfigIdToColumnKey(const ::database::id & key)
   {
      list_column * column = m_columna._001GetByConfigId(key);
      if(column == NULL)
         return -1;
      return column->m_iKey;
   }

   list_column * list_column_array::_001GetByConfigId(const ::database::id & key)
   {
      index iKey = MapConfigIdToKey(key);
      if(iKey >= 0)
         return ptr_at(iKey);
      else
         return NULL;

   }

   index list_column_array::MapConfigIdToKey(const ::database::id & key)
   {
      for(index iKey = 0; iKey < this->get_size(); iKey++)
      {
         if(this->element_at(iKey).m_datakey == key)
            return iKey;
      }
      return -1;
   }





   void list::ItemRange::Set(index iLBoundItem, index iUBoundItem, index iLBoundSubItem, index iUBoundSubItem, index iLBoundListItem, index iUBoundListItem)
   {

      m_iLBound = iLBoundItem;
      m_iUBound = iUBoundItem;
      m_subitemrange.Set(
         iLBoundSubItem,
         iUBoundSubItem,
         iLBoundListItem,
         iUBoundListItem);
   }

   void list::ItemRange::SetLBound(index iLBoundItem)
   {
      m_iLBound = iLBoundItem;
   }

   void list::ItemRange::SetUBound(index iUBoundItem)
   {
      m_iUBound = iUBoundItem;
   }

   void list::CSubItemRange::Set(index iLBoundSubItem, index iUBoundSubItem, index iLBoundListItem, index iUBoundListItem)
   {
      m_iLBound = iLBoundSubItem;
      m_iUBound = iUBoundSubItem;
      m_listitemrange.Set(
         iLBoundListItem,
         iUBoundListItem);
   }

   void list::CListItemRange::Set(index iLBoundListItem, index iUBoundListItem)
   {
      m_iLBound = iLBoundListItem;
      m_iUBound = iUBoundListItem;

   }


   void list::_001EnsureVisible(index iItem, bool bRedraw)
   {
      if(iItem < m_scrollinfo.m_ptScroll.y ||
         (m_iItemHeight > 0
         && iItem >= m_scrollinfo.m_ptScroll.y / m_iItemHeight + m_nDisplayCount))
      {
         m_scrollinfo.m_ptScroll.y = iItem * m_iItemHeight;
         _001UpdateScrollBars();
         if(bRedraw)
         {
            _001RedrawWindow();
         }
      }
   }

   void list::_001ItemScroll(index iItem, bool bRedraw)
   {
      if(iItem < m_nItemCount)
      {
         m_scrollinfo.m_ptScroll.y = iItem * m_iItemHeight;
         _001UpdateScrollBars();
         if(bRedraw)
         {
            _001RedrawWindow();
         }
      }
   }

   void list::_001EnsureVisible(index iItem, Range & range)
   {

      index iyScroll = m_scrollinfo.m_ptScroll.y / max(1, m_iItemHeight);
      if(iItem < iyScroll)
      {
         iyScroll = iItem - m_nDisplayCount + 1;
      }
      else if(iItem >= iyScroll + m_nDisplayCount)
      {
         iyScroll = iItem;
      }
      if(m_scrollinfo.m_ptScroll.y  / max(1, m_iItemHeight) != iyScroll)
      {
         ItemRange item;
         m_scrollinfo.m_ptScroll.y = iyScroll * m_iItemHeight;
         _001UpdateScrollBars();
         item.SetLBound(iyScroll);
         item.SetUBound(min(iyScroll + m_nDisplayCount - 1, m_nItemCount - 1));
         range.add_item(item);
      }
   }

   void list::_001Highlight(index iItem, bool bRedraw)
   {
      m_rangeHighlight.clear();
      ItemRange itemrange;
      itemrange.Set(iItem, iItem, 0, m_columna.get_count() - 1, - 1, -1);
      m_rangeHighlight.add_item(itemrange);
      if(bRedraw)
      {
         RedrawWindow();
      }
   }


   bool list::_001OnRemoveItem(index iItem)
   {
      UNREFERENCED_PARAMETER(iItem);
      return false;
   }

   bool list::_001RemoveItem(index iItem, bool bRedraw)
   {
      if(!_001OnRemoveItem(iItem))
         return false;
      m_rangeSelection.OnRemoveItem(iItem);
      if(bRedraw)
      {
         RedrawWindow();
      }
      return true;
   }

   void list::ItemRange::Offset(index iOffset)
   {
      m_iLBound += iOffset;
      m_iUBound += iOffset;
   }

   void list::_001RemoveSelection()
   {
      Range range;

      _001GetSelection(range);


      while(range.get_item_count() > 0)
      {
         index iItem = range.ItemAt(0).GetLBound();
         if(!_001RemoveItem(iItem, false))
            break;
         _001GetSelection(range);
      }

      RedrawWindow();
   }


   void list::_001Select(index iItem, index iSubItem)
   {
      m_rangeSelection.clear();
      ItemRange itemrange;
      itemrange.Set(iItem, iItem, iSubItem, iSubItem, - 1, -1);
      m_rangeSelection.add_item(itemrange);

   }

   index list::StrictToDisplay(index iStrict)
   {
      UNREFERENCED_PARAMETER(iStrict);
      return -1;
   }

   index list::DisplayToStrict(index iDisplay)
   {
      if(iDisplay < 0)
         return -1;
      if(m_bDrag)
      {
         if(m_eview == ViewIcon)
         {
            if(m_iconlayout.m_iaDisplayToStrict[m_iItemDrop] >= 0 && m_iconlayout.m_iaDisplayToStrict[m_iItemDrop] < m_nItemCount)
            {
               return m_iconlayout.m_iaDisplayToStrict[iDisplay];
            }
            else
            {
               if(iDisplay == m_iItemDrop)
               {
                  return m_iconlayout.m_iaDisplayToStrict[m_iItemDrag];
               }
               else if(iDisplay == m_iItemDrag)
               {
                  return -1;
               }
               else
               {
                  return m_iconlayout.m_iaDisplayToStrict[iDisplay];
               }
            }
         }
         else
         {
            if(iDisplay < m_iItemDrag && iDisplay < m_iItemDrop)
            {
               return m_iconlayout.m_iaDisplayToStrict[iDisplay];
            }
            else if(iDisplay > m_iItemDrag && iDisplay > m_iItemDrop)
            {
               return m_iconlayout.m_iaDisplayToStrict[iDisplay];
            }
            else
            {
               if(iDisplay == m_iItemDrop)
               {
                  return m_iconlayout.m_iaDisplayToStrict[m_iItemDrag];
               }
               else if(m_iItemDrop > m_iItemDrag)
               {
                  return m_iconlayout.m_iaDisplayToStrict[iDisplay + 1];
               }
               else if(m_iItemDrag > m_iItemDrop)
               {
                  return m_iconlayout.m_iaDisplayToStrict[iDisplay - 1];
               }
               else
               {
                  return m_iconlayout.m_iaDisplayToStrict[iDisplay];
               }
            }
         }
      }
      else if(m_eview == ViewIcon)
      {
         return m_iconlayout.m_iaDisplayToStrict[iDisplay];
      }
      else
      {
         if(iDisplay < 0)
            return -1;
         if(m_listlayout.m_iaDisplayToStrict.get_count() <= 0)
         {
            if(iDisplay < m_nItemCount)
               return iDisplay;
         }
         //if(m_listlayout.m_iaDisplayToStrict.get_count() != m_nItemCount)
           // return iDisplay;
         if(iDisplay >= m_listlayout.m_iaDisplayToStrict.get_count())
         {
            return -1;
         }
         return m_listlayout.m_iaDisplayToStrict[iDisplay];
      }
   }

   void list::FilterBegin()
   {
      m_efilterstate = FilterStateSetup;

      index iItemCount = m_nItemCount;

      if(m_eview == ViewIcon)
      {
         m_piaFilterIcon->remove_all();

         for(index i = 0; i < iItemCount; i++)
         {
            m_piaFilterIcon->add(i);
         }
      }
      else
      {
         m_piaFilterList->remove_all();

         for(index i = 0; i < iItemCount; i++)
         {
            m_piaFilterList->add(i);
         }
      }

   }

   void list::FilterApply()
   {

//      ASSERT(m_efilterstate == FilterStateSetup);

      m_iFilter1Step = 0;

      SetTimer(0xfffffffe, 50, NULL);

      m_scrollinfo.m_ptScroll.x = 0;
      m_scrollinfo.m_ptScroll.y = 0;

      m_efilterstate = FilterStateFilter;

      SetScrollSizes();

      layout();

      RedrawWindow();

   }

   void list::FilterClose()
   {
      m_bFilter1 = false;

      KillTimer(0xfffffffe);

      ASSERT(m_efilterstate == FilterStateSetup
         || m_efilterstate == FilterStateFilter);

      index iItemCount = m_nItemCount;

      if(m_eview == ViewIcon)
      {
         m_iconlayout.m_iaDisplayToStrict.remove_all();

         for(index i = 0; i < iItemCount; i++)
         {
            m_iconlayout.m_iaDisplayToStrict.add(i);
         }
      }
      else
      {
         m_listlayout.m_iaDisplayToStrict.remove_all();

         for(index i = 0; i < iItemCount; i++)
         {
            m_listlayout.m_iaDisplayToStrict.add(i);
         }
      }

      SetScrollSizes();

      layout();

      RedrawWindow();

   }

   void list::FilterExcludeAll()
   {
      if(m_eview == ViewIcon)
      {
         m_piaFilterIcon->remove_all();
      }
      else
      {
         m_piaFilterList->remove_all();
      }
   }

   void list::FilterInclude(index iItem)
   {
      ASSERT(m_efilterstate == FilterStateSetup);
      if(m_eview == ViewIcon)
      {
         m_piaFilterIcon->add_unique(iItem);
      }
      else
      {
         m_piaFilterList->add_unique(iItem);
      }
   }

   void list::FilterInclude(int_array & base_array)
   {
      ASSERT(m_efilterstate == FilterStateSetup);
      for(index i = 0; i < base_array.get_size() ; i++)
      {
         FilterInclude(base_array[i]);
      }
   }


   bool list::Filter1Step()
   {
      DWORD dwIn = GetTickCount();
      DWORD dwOut;
      TRACE("list::Filter1Step\n");
      TRACE("dwIn = %d\n", dwIn);
      if(!m_bFilter1)
         return false;

      string wstrItem;

      index iItemCount = min(m_nItemCount, m_iFilter1Step + 1000);

      index iFilter1Step;

      draw_list_item item(this);

      for(
         iFilter1Step =  m_iFilter1Step;
         iFilter1Step < iItemCount;
      iFilter1Step++)
      {
         for(index j = 0; j < m_columna.get_count(); j++)
         {
            list_column * pcolumn = m_columna._001GetByKey(j);
            item.m_strText.Empty();
            item.m_iItem = iFilter1Step;
            item.m_iSubItem = pcolumn->m_iSubItem;
            item.m_iListItem = -1;
            _001SearchGetItemText(&item);
            if(item.m_bOk)
            {
               item.m_strText.make_lower();
               item.m_strText.replace("_", " ");
               if(PcreUtil::match(item.m_strText, &m_reFilter1))
               {
                  if(m_eview == ViewIcon)
                  {
                     m_piaFilterIcon->add_unique(iFilter1Step);
                  }
                  else
                  {
                     m_piaFilterList->add_unique(iFilter1Step);
                  }
                  break;
               }
            }
         }
      }

      m_iFilter1Step = iFilter1Step;

      if(m_eview == ViewIcon)
      {
         m_iconlayout.m_iaDisplayToStrict = (*m_piaFilterIcon);
      }
      else
      {
         m_listlayout.m_iaDisplayToStrict = (*m_piaFilterList);
      }

      m_scrollinfo.m_ptScroll.x = 0;
      m_scrollinfo.m_ptScroll.y = 0;

      m_efilterstate = FilterStateFilter;

      SetScrollSizes();

      layout();

      RedrawWindow();


      dwOut = GetTickCount();
      TRACE("dwOut = %d\n", dwOut);
      TRACE("(delta) = %d\n", dwOut - dwIn);

      return m_nItemCount != iItemCount;
   }


   void list::Filter1(string & strFilter)
   {

      if(m_eview == ViewIcon)
      {
         m_piaFilterIcon->remove_all();
      }
      else
      {
         m_piaFilterList->remove_all();
      }

      stringa stra;

      stra.add_tokens(strFilter, " ", false);

      m_reFilter1.setPositionMoves(1);

      m_bFilter1 = m_reFilter1.setRE("/.*" + stra.implode(".*") + ".*/i");

      if(m_bFilter1)
      {
         FilterApply();
      }
      else
      {
         FilterClose();
      }

   }

   void list::_001OnListHeaderItemClick(index iHeaderItem)
   {
      if(!m_bSortEnable)
         return;
      _001OnSort(_001MapColumnToSubItem(iHeaderItem));
   }

   void list::_001OnListHeaderItemDblClk(index iHeaderItem)
   {
      _001MaximizeColumnWidth(iHeaderItem);
   }


   void list::_001OnSort()
   {
      if(!m_bSortEnable)
         return;
      if(m_eview != ViewIcon)
      {
         ::sort::QuickSort(m_listlayout.m_iaDisplayToStrict, this, (compare_interface::_FUNCTION_Compare) &list::_001Compare);
      }
      else
      {
      }
   }

   void list::_001OnSort(index iSubItem)
   {

      index iFound = -1;
      for(index i = 0; i < m_sortinfo.m_itema.get_size(); i++)
      {
         CSortInfoItem & item = m_sortinfo.m_itema[i];
         if(item.m_iSubItem == iSubItem)
         {
            iFound = i;
            break;
         }
      }
      if(iFound >= 0)
      {
         CSortInfoItem newItem = m_sortinfo.m_itema[iFound];
         m_sortinfo.m_itema.remove_at(iFound);
         newItem.m_bAscendent = !newItem.m_bAscendent;
         m_sortinfo.m_itema.insert_at(0, newItem);
      }
      else
      {
         CSortInfoItem newItem;
         newItem.m_iSubItem = iSubItem;
         newItem.m_bAscendent = true;
         m_sortinfo.m_itema.insert_at(0, newItem);
      }

      _001OnSort();

   }




   index list::_001Compare(index iItem1, index iItem2, index iSubItem)
   {
      draw_list_item item1(this);
      draw_list_item item2(this);

      item1.m_iItem     = iItem1;
      item2.m_iItem     = iItem2;
      item1.m_iSubItem  = iSubItem;
      item2.m_iSubItem  = iSubItem;

      _001GetItemText(&item1);
      _001GetItemText(&item2);

      if(item1.m_bOk && item2.m_bOk)
      {
         return item1.m_strText.CompareNoCase(item2.m_strText);
      }
      else
      {
         if(item1.m_bOk)
            return 1;
         else if(item2.m_bOk)
            return -1;
         else
            return 0;
      }

   }

   index list::_001Compare(index iItem1, index iItem2)
   {
      CSortInfoItem * pitem = NULL;
      index iCompare = 0;
      for(index i = 0; i < m_sortinfo.m_itema.get_size(); i++)
      {
         pitem = &m_sortinfo.m_itema[i];
         iCompare = _001Compare(iItem1, iItem2, pitem->m_iSubItem);
         if(iCompare != 0)
            break;
      }
      if(pitem == NULL)
         return 0;
      else
      {
         if(pitem->m_bAscendent)
            return iCompare;
         else
            return -iCompare;
      }
   }


   index list::_001DisplayCompare(index iDisplayItem1, index iDisplayItem2)
   {
      return _001Compare(DisplayToStrict(iDisplayItem1), DisplayToStrict(iDisplayItem2));
   }


   int list::_001CalcListWidth()
   {
      ASSERT(FALSE);
      return -1;
   }

   int list::_001CalcColumnWidth(index iColumn)
   {
      UNREFERENCED_PARAMETER(iColumn);
      ::ca::graphics * pdc = GetDC();
      ::ca::font * pfont = _001GetFont();
      pdc->SelectObject(pfont);
      index iMaxWidth = 0;
      index iCount = m_nItemCount;
      index iWidth;
      for(index i = 0; i < iCount; i++)
      {
         iWidth = _001CalcItemWidth(pdc, i, 0);
         if(iWidth > iMaxWidth)
         {
            iMaxWidth = iWidth;
         }
      }
      ReleaseDC(pdc);
      return iMaxWidth;

   }


   void list::_001MaximizeColumnWidth(index iColumn)
   {
      _001SetColumnWidth(iColumn, _001CalcColumnWidth(iColumn));
   }

   void list::_OnDraw(::ca::graphics *pdc)
   {
      UNREFERENCED_PARAMETER(pdc);
   }

   void list::_001OnMouseWheel(gen::signal_object * pobj)
   {
      SCAST_PTR(::gen::message::mouse_wheel, pmousewheel, pobj);
      m_iWheelDelta += pmousewheel->GetDelta();

      index iDelta = m_iWheelDelta / WHEEL_DELTA;

      m_iWheelDelta -= (short) (WHEEL_DELTA * iDelta);

      m_scrollinfo.m_ptScroll.y -= iDelta * 3 * m_iItemHeight;

      _001UpdateScrollBars();


      HeaderCtrlLayout();

      CacheHint();

      UpdateHover();

      Redraw();


      pmousewheel->set_lresult(0);
      pmousewheel->m_bRet = true;
   }


   ::ca::pen * list::_001GetPenHighlight()
   {
      return m_penHighlight;
   }

   ::ca::pen * list::_001GetPenFocused()
   {
      return m_penFocused;

   }

   ::ca::font * list::_001GetFont()
   {
      return m_font;
   }

   ::ca::font * list::_001GetFontHover()
   {
      return m_fontHover;
   }

   void list::_001OnMouseLeave(gen::signal_object * pobj)
   {
      m_iItemHover = -1;
      m_iSubItemHover = -1;
      _001RedrawWindow();
      pobj->m_bRet = true;
   }


   void list::_001OnMouseMove(gen::signal_object * pobj)
   {
      SCAST_PTR(::gen::message::mouse, pmouse, pobj)
         pmouse->set_lresult(1);
      point pt = pmouse->m_pt;
      ScreenToClient(&pt);

      pmouse->previous(); // give chance to child control
      if(m_bDrag)
      {
         index iItemOld = m_iItemDrop;
         if(!_001DisplayHitTest(pt, m_iItemDrop))
         {
            m_iItemDrop = m_iItemDrag;
         }
         if(iItemOld != m_iItemDrop)
         {
            _001RedrawWindow();
         }
      }

      track_mouse_leave();

      UpdateHover();
      pobj->m_bRet = true;


      index iItemEnter;
      index iSubItemEnter;
      point point;
      //Application.get_cursor_pos(&point);
      //ScreenToClient(&point);

      if(_001DisplayHitTest(pt, iItemEnter, iSubItemEnter))
      {
         if(m_bHoverSelect &&
            (m_iSubItemEnter != iSubItemEnter ||
            m_iItemEnter != iItemEnter))
         {
            m_iMouseFlagEnter = pmouse->m_nFlags;
            m_iItemEnter = iItemEnter;
            m_iSubItemEnter = iSubItemEnter;
            SetTimer(12321, 840, NULL);
         }
      }


   }

   void list::UpdateHover()
   {
      index iItemHover;
      index iSubItemHover;
      point point;
      Application.get_cursor_pos(&point);
      ScreenToClient(&point);

      if(_001DisplayHitTest(point, iItemHover, iSubItemHover))
      {
         if(m_iSubItemHover != iSubItemHover ||
            m_iItemHover != iItemHover)
         {
            m_iItemHover = iItemHover;
            m_iSubItemHover = iSubItemHover;
            _001RedrawWindow();
         }
      }

   }


   list::Range::Range()
   {

   }

   list::Range::Range(Range & range)
   {
      m_itemrangea = range.m_itemrangea;
   }


   ::user::list_data * list::GetDataInterface()
   {
      return m_pdata;
   }

   void list::_001SetView(EView eview)
   {
      m_eview = eview;

      data_get_DisplayToStrict();

      layout();
   }



   void list::data_get_DisplayToStrict()
   {
      if(m_eview == ViewIcon)
      {
         data_get(data_get_current_sort_id(), data_get_current_list_layout_id(), m_iconlayout);
      }
      else
      {
         data_get(data_get_current_sort_id(), data_get_current_list_layout_id(), m_listlayout);
      }
   }

   void list::data_set_DisplayToStrict()
   {
      if(m_eview == ViewIcon)
      {
         data_set(data_get_current_sort_id(), data_get_current_list_layout_id(), m_iconlayout);
      }
      else
      {
         data_set(data_get_current_sort_id(), data_get_current_list_layout_id(), m_listlayout);
      }
   }

   id list::data_get_current_sort_id()
   {
      return data_get_sort_id(m_eview);
   }

   id list::data_get_sort_id(EView eview)
   {
      UNREFERENCED_PARAMETER(eview);
      switch(m_eview)
      {
      case ViewReport:
         return "sort-report";
         break;
      case ViewList:
         return "sort-list";
         break;
      case ViewIcon:
         return "sort-icon";
         break;
      default:
         ASSERT(FALSE);
         return "sort";
      }
   }

   list::EView list::_001GetView()
   {
      return m_eview;
   }


   void list::_001OnAfterSort()
   {
      data_set_DisplayToStrict();
   }

   bool list::_001IsEditing()
   {
      return false;
   }

   void list::_001GetItemColor(::user::list_item * pitem)
   {
      pitem->m_bOk = false;
   }


   void list::_001OnVScroll(gen::signal_object * pobj)
   {
//      SCAST_PTR(::gen::message::scroll, pscroll, pobj);

      pobj->previous();

      m_iTopIndex = _001CalcDisplayTopIndex();
      index iLow = 0;
      for(m_iTopGroup = 0; m_iTopGroup < m_nGroupCount; m_iTopGroup++)
      {
         if(m_iTopIndex >= iLow && m_iTopIndex < (iLow + _001GetGroupItemCount(m_iTopGroup)))
            break;
      }
      m_nDisplayCount = _001CalcDisplayItemCount();

      HeaderCtrlLayout();

      CacheHint();
   }

   void list::_001OnHScroll(gen::signal_object * pobj)
   {
//      SCAST_PTR(::gen::message::scroll, pscroll, pobj);

      pobj->previous();

      m_iTopIndex = _001CalcDisplayTopIndex();
      index iLow = 0;
      for(m_iTopGroup = 0; m_iTopGroup < m_nGroupCount; m_iTopGroup++)
      {
         if(m_iTopIndex >= iLow && m_iTopIndex < (iLow + _001GetGroupItemCount(m_iTopGroup)))
            break;
      }
      m_nDisplayCount = _001CalcDisplayItemCount();

      HeaderCtrlLayout();

      CacheHint();

   }


   id list::data_get_current_list_layout_id()
   {
      return "list";
   }

   bool list::query_drop(index iDisplayDrop, index iDisplayDrag)
   {
      if(iDisplayDrag < 0)
         return false;
      if(iDisplayDrop < 0)
         return false;
      if(m_iItemDrag != m_iItemDrop)
      {
         if(m_eview == ViewIcon)
         {
            if(m_iconlayout.m_iaDisplayToStrict[m_iItemDrop] == -1 || m_iconlayout.m_iaDisplayToStrict[m_iItemDrop] >= m_nItemCount)
            {
               return true;
            }
         }
         else
         {
            if(m_listlayout.m_iaDisplayToStrict[m_iItemDrop] == -1 || m_listlayout.m_iaDisplayToStrict[m_iItemDrop] >= m_nItemCount )
            {
               return true;
            }
         }
      }
      return false;
   }


   bool list::do_drop(index iDisplayDrop, index iDisplayDrag)
   {
      UNREFERENCED_PARAMETER(iDisplayDrop);
      UNREFERENCED_PARAMETER(iDisplayDrag);
      if(m_eview == ViewIcon)
      {
         m_iconlayout.m_iaDisplayToStrict.translate_a(m_iItemDrop, m_iItemDrag);
      }
      else
      {
         index i = m_listlayout.m_iaDisplayToStrict[m_iItemDrag];
         m_listlayout.m_iaDisplayToStrict[m_iItemDrag] = m_listlayout.m_iaDisplayToStrict[m_iItemDrop];
         m_listlayout.m_iaDisplayToStrict[m_iItemDrop] = i;
      }
      _001OnAfterSort();
      return true;
   }

   bool list::defer_drop(index iDisplayDrop, index iDisplayDrag)
   {
      if(query_drop(iDisplayDrop, iDisplayDrag))
      {
         if(m_eview == ViewIcon)
         {
            if(m_iconlayout.m_iWidth <= 0)
            {
               rect rectClient;
               _001GetViewClientRect(rectClient);
               index iIconSize;
               if(m_columna.get_count() > 0)
                  iIconSize = max(32, m_columna[0].m_sizeIcon.cy);
               else
                  iIconSize = 32;
               index iItemSize = iIconSize * 2;
               m_iconlayout.m_iWidth = max(1, rectClient.width() / iItemSize);
            }
            return do_drop(iDisplayDrop, iDisplayDrag);
         }
         else
         {
            return do_drop(iDisplayDrop, iDisplayDrag);
         }
      }
      else
      {
         return false;
      }
   }

   list::list_layout::list_layout()
   {
   }

   list::list_layout::~list_layout()
   {
   }

   void list::list_layout::write(::ex1::byte_output_stream & ostream)
   {
      //ostream << m_iaDisplayToStrict;
      ostream << m_iWidth;
   }

   void list::list_layout::read(::ex1::byte_input_stream & istream)
   {
      //istream >> m_iaDisplayToStrict;
      istream >> m_iWidth;
   }

   list::icon_layout::icon_layout()
   {
   }

   list::icon_layout::~icon_layout()
   {
   }

   void list::icon_layout::write(::ex1::byte_output_stream & ostream)
   {
      ostream << m_iaDisplayToStrict;
      ostream << m_iWidth;
   }

   void list::icon_layout::read(::ex1::byte_input_stream & istream)
   {
      istream >> m_iaDisplayToStrict;
      istream >> m_iWidth;
   }

   class size list::get_item_size()
   {
      if(m_eview == ViewIcon)
      {
         if(m_columna.get_count() == 0)
         {
            return size(32, 32);
         }
         index iIconSize = max(32, m_columna[0].m_sizeIcon.cy);
         index iItemSize = iIconSize * 2;
         return size(iItemSize, iItemSize);
      }
      else
      {
         // not implemented
         ASSERT(FALSE);
         return size(0, 0);
      }
   }

   void list::auto_arrange(bool bAutoArrange)
   {
      if(bAutoArrange)
      {
         m_flags.signalize(flag_auto_arrange);
      }
      else
      {
         m_flags.unsignalize(flag_auto_arrange);
      }
      if(bAutoArrange)
      {
         index iMaxStrict = m_iconlayout.m_iaDisplayToStrict.get_max_b();
         for(index iStrict = 0; iStrict <= iMaxStrict; iStrict++)
         {
            m_iconlayout.m_iaDisplayToStrict.set(iStrict, iStrict);
         }
         layout();
      }
   }

   bool list::get_auto_arrange()
   {
      return m_flags.is_signalized(flag_auto_arrange);
   }

   void list::_001OnListViewAutoArrange(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      auto_arrange(!get_auto_arrange());
   }

   void list::_001OnUpdateListViewAutoArrange(gen::signal_object * pobj)
   {
      SCAST_PTR(base_cmd_ui, pcmdui, pobj)
      pcmdui->m_pcmdui->_001SetCheck(get_auto_arrange());
      pcmdui->m_pcmdui->Enable();
   }

   bool list::is_valid_display_item(index iDisplayItem)
   {
      if(iDisplayItem < 0)
         return false;
      if(iDisplayItem >= m_nItemCount)
         return false;
      return true;
   }

   bool list::is_valid_strict_item(index iStrictItem)
   {
      if(iStrictItem < 0)
         return false;
      if(iStrictItem >= m_nItemCount)
         return false;
      return true;

   }


   bool list::keyboard_focus_is_focusable()
   {
      return true;
   }

   void list::_001OnSelectionChange()
   {
   }

   index list::set_cur_sel(index iSel)
   {
      index iOld = get_cur_sel();
      m_rangeSelection.clear();
      if(iSel >= 0)
      {
         ItemRange itemrange;
         itemrange.SetLBound(iSel);
         itemrange.SetUBound(iSel);
         m_rangeSelection.add_item(itemrange);
      }
      return iOld;
   }

   index list::get_cur_sel()
   {
      if(m_rangeSelection.get_item_count() != 1)
         return -1;
      if(m_rangeSelection.ItemAt(0).GetLBound() == m_rangeSelection.ItemAt(0).GetUBound() && m_rangeSelection.ItemAt(0).GetLBound() >= 0)
         return m_rangeSelection.ItemAt(0).GetLBound();
      return -1;
   }


   ::count list::_001GetGroupItemCount(index iGroup)
   {
      UNREFERENCED_PARAMETER(iGroup);
      return -1;
   }

   int list::_001GetGroupHeight(index iGroup)
   {
      int iListHeight = _001GetGroupItemCount(iGroup) * m_iItemHeight;
      return max(m_iGroupMinHeight, iListHeight);
   }

   list_item::list_item(list * plist)
   {

      m_plist           = plist;
      m_iGroup          = -1;
      m_iItem           = -1;
      m_iDisplayItem    = -1;
      m_iColumn         = -1;
      m_iColumnKey      = -1;
      m_iOrder          = -1;
      m_iSubItem        = -1;
      m_iListItem       = -1;
      m_cr              = (COLORREF) -1;
      m_iState          = -1;
      m_iImage          = -1;
      m_bOk             = false;

      m_iGroupTopIndex  = -1;
      m_iGroupCount     = -1;

   }

   draw_list_item::draw_list_item(list * plist) :
      list_item(plist)
   {

      m_prectClient              = NULL;

      m_iWidthColumn             = -1;
      m_iColumnWidth             = 0;
      m_pcolumnWidth             = NULL;

      m_iItemRectItem            = -1;

      m_iSubItemRectItem         = -1;
      m_iSubItemRectSubItem      = -1;
      m_iSubItemRectOrder        = -1;
      m_iSubItemRectColumn       = -1;
      m_pcolumnSubItemRect       = NULL;

      m_iListItemRectItem        = -1;
      m_iListItemRectSubItem     = -1;
      m_iListItemRectListItem    = -1;

   }


   image_list * draw_list_item::get_image_list()
   {
      if(m_bListItemHover && m_pcolumn->m_pilHover != NULL)
      {
         return m_pcolumn->m_pilHover;
      }
      else
      {
         return m_pcolumn->m_pil;
      }
   }

   bool draw_list_item::draw_image()
   {
      if(m_pcolumn->m_bIcon)
      {
         visual::icon * picon;
         if(m_pcolumn->m_mapIcon.Lookup(m_iImage, picon))
         {
            m_pgraphics->set_alpha_mode(::ca::alpha_mode_blend);
            return m_pgraphics->DrawIcon(m_rectImage.top_left(), picon) != FALSE;
         }
      }
      else
      {
         m_pgraphics->set_alpha_mode(::ca::alpha_mode_blend);
         return get_image_list()->draw(m_pgraphics, m_iImage, m_rectImage.top_left(), m_rectImage.size(), point(0,0), 0);
      }
      return false;
   }


   bool draw_list_item::draw_group_image()
   {
      return m_plist->m_pilGroup->draw(m_pgraphics, m_iImage, m_rectImage.top_left(), m_rectImage.size(), point(0,0), 0);
   }


   void draw_list_item::update_item_color()
   {
      m_plist->_001GetItemColor(this);
      if(!m_bOk)
      {
         if(m_bListItemSelected)
         {
            if(m_bListItemHover)
            {
               m_cr = m_plist->m_crTextSelectedHighlight;
            }
            else
            {
               m_cr = m_plist->m_crTextSelected;
            }
         }
         else
         {
            if(m_bListItemHover)
            {
               m_cr = m_plist->m_crTextHighlight;
            }
            else
            {
               m_cr = m_plist->m_crText;
            }
         }
      }
   }

   void draw_list_item::set_text_color()
   {
      m_pgraphics->set_color(m_cr);
   }


   void draw_list_item::draw_text()
   {
      if(m_bOk)
      {
         if(m_plist->m_eview == list::ViewIcon && m_plist->m_bEmboss)
         {

            class size size = m_rectText.size();
            size.cx += 4;
            size.cy += 4;

            ::ca::graphics_sp dcCache(m_plist->get_app());
            dcCache->CreateCompatibleDC(NULL);
            ::ca::font * pfontOld = dcCache->SelectObject(m_pfont);

            ::ca::bitmap_sp bmpCache(m_plist->get_app());
            bmpCache->CreateCompatibleBitmap(m_pgraphics, size.cx, size.cy);
            dcCache->SelectObject(bmpCache);
            dcCache->FillSolidRect(0, 0, size.cx,size.cy, ARGB(255, 0, 0, 0));
            dcCache->SetTextColor(ARGB(255, 255, 255, 255));

            class rect rectCache;
            rectCache.left = 2;
            rectCache.top = 2;
            rectCache.right = rectCache.left + (index)m_rectText.width();
            rectCache.bottom = rectCache.top + (index)m_rectText.height();
            m_plist->m_dcextension._DrawText(dcCache, m_strText, rectCache, m_iDrawTextFlags);

            Sys(m_plist->get_app()).imaging().channel_spread(dcCache, null_point(), size, dcCache, null_point(), 0, 1);
            Sys(m_plist->get_app()).imaging().channel_gray_blur(dcCache, null_point(), size, dcCache, null_point(), 0, 1);
//            Sys(m_plist->get_app()).imaging().pre_color_blend(dcCache, dcCache, ARGB(255, 0, 0, 0));


            dcCache->SelectObject(pfontOld);

            Sys(m_plist->get_app()).imaging().color_blend(m_pgraphics, m_rectText, dcCache, point(1, 1), 0.50);


            m_pgraphics->SetTextColor(ARGB(255, 255, 255, 255));
            m_pgraphics->SelectObject(m_pfont);
            m_plist->m_dcextension._DrawText(m_pgraphics, m_strText, m_rectText, m_iDrawTextFlags);
         }
         else
         {
            m_pgraphics->set_color(m_cr);
            m_plist->m_dcextension._DrawText(m_pgraphics, m_strText, m_rectText, m_iDrawTextFlags);
         }
      }
   }

   ::count list::_001GetGroupMetaItemCount(index iGroup)
   {
      if(m_pdata != NULL)
      {
         return m_pdata->_001GetGroupMetaItemCount(iGroup);
      }
      return 0;
   }

   void list::_001GetGroupText(list_item * pitem)
   {
      pitem->m_bOk = false;
      if(m_pcache != NULL)
      {
         m_pcache->_001GetGroupText(pitem);
         if(pitem->m_bOk)
            return;
      }
      if(m_pdata != NULL)
      {
         m_pdata->_001GetGroupText(pitem);
      }
   }

   void list::_001GetGroupImage(list_item * pitem)
   {
      pitem->m_bOk = false;
      pitem->m_iImage = -1;
   }



} // namespace user
