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

      // Simple Filter
      m_efilterstate             = FilterStateNoFilter;



      m_iClick = 0;

      m_penFocused->CreatePen(PS_SOLID, 2, RGB(0, 255, 255));
      m_penHighlight->CreatePen(PS_SOLID, 2, RGB(0, 255, 255));

      m_crText = RGB(0, 0, 0);
      m_crTextSelected = RGB(255, 255, 255);
      m_crTextHighlight = RGB(55, 105, 255);
      m_crTextSelectedHighlight = RGB(102, 153, 255);

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

   }

   list::~list()
   {
   }


   void list::_001InstallMessageHandling(::user::win::message::dispatch * pinterface)
   {
      ::user::scroll_view::_001InstallMessageHandling(pinterface);
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

   COLORREF list::get_background_color()
   {
      return RGB(200, 255, 255) | (127 << 24);
   }

   void list::_001OnDraw(::ca::graphics *pdc)
   {
      if(m_bLockViewUpdate)
         return;

      ::ca::brush_sp brushNull(get_app());

      ::ca::font * pfont = _001GetFont();
      brushNull->CreateStockObject(NULL_BRUSH);


      rect rectClient;

      GetClientRect(rectClient);


//      gen::savings & savings = System.savings();

      ::ca::graphics * pDCBuffer = pdc;

      point ptOriginalViewportOrg = pdc->GetViewportOrg();

      rect rectClientOffset = rectClient;

      
      rect rectClipBox; 
      pdc->GetClipBox(&rectClipBox);
      if(rectClipBox.is_null())
      {
         rectClipBox = rectClientOffset;
      }
      else
      {
         rectClipBox.intersect(rectClipBox, rectClientOffset);
      }

      rect rectUpdate;

      rectUpdate = rectClipBox;

      ::ca::rgn_sp rgnClipOld(get_app());
      rgnClipOld->CreateRectRgn(0, 0, 0, 0);
      index iClipOld = ::GetClipRgn((HDC)pdc->get_os_data(), (HRGN)rgnClipOld->get_os_data());

      point ptOffset = ptOriginalViewportOrg;

      rect rectClipOldBox;
      rgnClipOld->GetRgnBox(&rectClipOldBox);

//      class imaging & imaging = System.imaging();

      rect rectClipBox32;

      if(_001IsBackgroundBypass())
      {
      }
      else if(_001IsTranslucent())
      {
         class imaging & imaging = System.imaging();
         //_001DrawBackground(pdc, rectClipBox);
         ::CopyRect(rectClipBox32, rectClipBox);
         imaging.color_blend(
            pdc,
            rectClipBox32,
            get_background_color() & 0xffffff,
            (get_background_color() >> 24) & 0xff);
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
               pdc->FillSolidRect(rectClipBox, get_background_color() & 0xffffff);
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



      ::ca::font * pfontOriginal = pDCBuffer->GetCurrentFont();
      pDCBuffer->SelectObject(GetFont());

//      index iBkModeOriginal = pDCBuffer->GetBkMode();
      pDCBuffer->SetBkMode(TRANSPARENT);

      bool bHover;

      ::ca::font  * pfontHover = _001GetFontHover();



      rect rectItem;
      rect rectIntersect;
      INT_PTR iItemCount = _001GetDisplayCount();
      INT_PTR iItemFirst = _001GetTopIndex();
      INT_PTR iItemLast;
      if(m_eview == ViewIcon)
      {
         iItemLast = iItemCount;
      }
      else
      {
         iItemLast = min(_001GetItemCount() - 1, iItemFirst + _001GetDisplayItemCount() - 1);
      }
      //index iItemLast = iItemFirst;
      /*for(index i = iItemFirst; i < iItemCount; i++)
      {
      if(_001GetItemRect(i, i, rectItem))
      {
      if(rectIntersect.intersect(rectItem, rectUpdate))
      {
      iItemFirst = i;
      break;
      }
      }
      }*/

      /*if(iItemFirst >= 0)
      {
      iItemLast = -1;
      for(index i = iItemFirst + 1; i < iItemCount; i++)
      {
      if(_001GetItemRect(i, i, rectItem))
      {
      if(!rectIntersect.intersect(rectItem, rectUpdate))
      {
      iItemLast = i;
      break;
      }
      }
      }
      if(iItemLast < 0)
      iItemLast = iItemCount - 1;
      }*/

      bHover = false;
      if(m_bTopText)
      {
         point ptViewportOrg = pdc->GetViewportOrg();
         pdc->SetTextColor(m_crText);
         pdc->SelectObject(pfont);
         base_array < size, size & > sizea;
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

      if(iItemFirst >= 0)
      {
         INT_PTR iItem;
         for(iItem = iItemFirst; iItem <= iItemLast; iItem++)
         {
            if(m_eview == ViewIcon 
             && (m_iconlayout.m_iaDisplayToStrict.get_b(iItem) == -1
               && iItem != m_iItemDrop))
               continue;

            rect rect;
            if(!_001GetItemRect(iItem, iItem, rect))
               continue;

            if(!rectIntersect.intersect(rect, rectClipBox))
               continue;
            //rect.offset(-m_scrollinfo.m_ptScroll);

            draw_item drawitem;
            drawitem.m_hdc       = NULL;
            drawitem.m_itemId    = iItem;
            drawitem.m_rectItem  = rect;

            if(iItem == m_iItemHover)
            {
               if(!bHover)
               {
                  pdc->SelectObject(pfontHover);
               }
            }
            else
            {
               if(bHover)
               {
                  pdc->SelectObject(pfont);
               }
            }
            //         TRACE("call _001DrawItem %d\n", iItem);
            _001DrawItem(pdc, &drawitem);
         }
      }

      if(iClipOld == 1)
      {
         pdc->SelectClipRgn(rgnClipOld);
      }
      else
      {
         pdc->SelectClipRgn(NULL);
      }

      pdc->SetViewportOrg(ptOriginalViewportOrg);
      pDCBuffer->SelectObject(pfontOriginal);


   }

   void   list::_001DrawSubItem(
                                           ::ca::graphics * pdc,
                                           draw_item * pdrawitem,
                                           LPCRECT lpcrec,
                                           index iSubItem,
                                           bool bItemHover,
                                           bool bSubItemHover,
                                           bool bFocus)
   {
      UNREFERENCED_PARAMETER(pdc);
      UNREFERENCED_PARAMETER(pdrawitem);
      UNREFERENCED_PARAMETER(lpcrec);
      UNREFERENCED_PARAMETER(iSubItem);
      UNREFERENCED_PARAMETER(bItemHover);
      UNREFERENCED_PARAMETER(bSubItemHover);
      UNREFERENCED_PARAMETER(bFocus);
   }



   void list::_001DrawItem(::ca::graphics *pdc, draw_item * pdrawitem) 
   {
//      gen::savings & savings = System.savings();

      bool bHover;


      ::ca::graphics * pDCBuffer = pdc;
      rect rectItem = pdrawitem->m_rectItem;
      rect rectClipBox = pdrawitem->m_rectItem;

      Range & rangeSelection = m_rangeSelection;
      Range & rangeHighlight = m_rangeHighlight;

      index iDisplayItem = (index) pdrawitem->m_itemId;
      index iItem = DisplayToStrict(iDisplayItem);

      bHover = iDisplayItem == m_iItemHover &&
         (m_eview != ViewIcon ||
         ((m_iconlayout.m_iaDisplayToStrict.get_a(m_iItemHover) >= 0
         &&  m_iconlayout.m_iaDisplayToStrict.get_a(m_iItemHover) < _001GetItemCount())));

      ::ca::font * pfont;
      if(bHover)
      {
         System.imaging().color_blend(pdc, rectItem, RGB(255, 255, 255), 128);
         pfont = _001GetFontHover();
      }
      else
      {
         pfont = _001GetFont();
      }

      INT_PTR iColumn = 0;

//      index iImage = -1;// = _001GetItemImage(pdrawitem->itemID);

      index iDrawTextFlags;
      if(m_eview == ViewIcon)
      {
         iDrawTextFlags = DT_TOP | DT_CENTER | DT_END_ELLIPSIS | DT_WORDBREAK;
      }
      else
      {
         iDrawTextFlags = DT_TOP | DT_LEFT | DT_END_ELLIPSIS | DT_SINGLELINE;
      }

      COLORREF crText;
      if((m_eview != ViewIcon || is_valid_display_item(iItem)) && rangeSelection.HasItem(iDisplayItem))
      {
         if(bHover)
         {
            pDCBuffer->SetTextColor(_001GetItemColor(iItem, -1, -1, ItemStateHover | ItemStateSelected));
            crText = _001GetItemColor(iItem, -1, -1, ItemStateHover | ItemStateSelected);
         }
         else
         {
            pDCBuffer->SetTextColor(_001GetItemColor(iItem, -1, -1, ItemStateSelected));
            crText = _001GetItemColor(iItem, -1, -1, ItemStateSelected);
         }
         if(System.savings().is_trying_to_save(gen::resource_processing))
         {
            pDCBuffer->FillSolidRect(
               rectClipBox,
               RGB(96,96,96));
         }
         else
         {
            imaging & imaging = System.imaging();
            //                COLORREF crTranslucid = m_crTranslucidSelect;
            COLORREF crTranslucid = RGB(0, 0, 0);
            imaging.color_blend(
               pDCBuffer,
               (index)rectClipBox.left, (index)rectClipBox.top,
               (index)rectClipBox.width(), (index)rectClipBox.height(),
               crTranslucid, 127);
         }
      }
      else
      {
         if(bHover)
         {
            pDCBuffer->SetTextColor(_001GetItemColor(iItem, -1, -1, ItemStateHover));
            crText = _001GetItemColor(iItem, -1, -1, ItemStateHover);
         }
         else
         {
            pDCBuffer->SetTextColor(_001GetItemColor(iItem, -1, -1, 0));
            crText = _001GetItemColor(iItem, -1, -1, 0);
         }
         /*        if(iEconoMode & savings::SaveProcessing)
         {
         pDCBuffer->FillSolidRect(
         rectClipBox,
         RGB(255,255,255));
         }
         else
         {
         imaging & imaging = System.imaging();
         //                COLORREF crTranslucid = m_crTranslucidSelect;
         COLORREF crTranslucid = RGB(255, 255, 255);
         imaging.color_blend(
         pDCBuffer,
         rectClipBox.left, rectClipBox.top,
         rectClipBox.width(), rectClipBox.height(),
         crTranslucid, 208);
         }*/
      }


      /*    if(iState & LVIS_FOCUSED)
      {

      rect rectFocused = pdrawitem->rcItem;
      rectFocused.deflate(2, 2);
      pDCBuffer->SelectObject(m_penFocused);
      pDCBuffer->SelectObject(m_brushNull);
      pDCBuffer->Rectangle(rectFocused);

      }*/
      /*    if(plvi.m_uiState & VMSPLVIS_PLAYING)
      {
      pDCBuffer->SetTextColor(m_crTextPlaying);
      }
      else*/
      rect rect;        
      string str;

      ::ca::font * pfontOld = pDCBuffer->SelectObject(pfont);
      ::ca::pen * ppenOld = pDCBuffer->GetCurrentPen();
      ::ca::brush * pbrushOld = pDCBuffer->GetCurrentBrush();

      index iSubItem;

      index iColumnCount;

      if(m_eview == ViewIcon)
      {
         iColumnCount = 1;
      }
      else
      {
         iColumnCount = _001GetColumnCount();
      }

      for(index iOrder = 0; iOrder < iColumnCount; iOrder++)
      {
         iColumn = _001MapOrderToColumn(iOrder);
         if(iColumn < 0)
            continue;
         Column & column = m_columna.VisibleGet(iColumn);
         iSubItem = column.m_iSubItem;
         if(column.m_bCustomDraw)
         {
            _001GetElementRect(rect, iItem, iDisplayItem, iOrder, -1, userbase::_list::ElementSubItem);
            _001DrawSubItem(
               pDCBuffer,
               pdrawitem,
               class rect(rect),
               iSubItem,
               bHover,
               bHover && (iSubItem == m_iSubItemHover),
               false);
            continue;
         }
         if(_001GetElementRect(rect, iItem, iDisplayItem, iOrder, -1, userbase::_list::ElementImage))
         {
            index iImage = _001GetItemImage(iItem, iSubItem, -1);
            if(column.m_bIcon)
            {
               HICON hicon;
               if(column.m_mapIcon.Lookup(iImage, hicon))
               {
                  DrawIconEx(
                     (HDC)pDCBuffer->get_os_data(),
                     (index)rect.left, (index)rect.top,
                     hicon,
                     (index)rect.width(), (index)rect.height(),
                     0,
                     NULL,
                     DI_NORMAL);
               }
            }
            else
            {
               image_list * pil;
               if(bHover && column.m_pilHover != NULL)
               {
                  pil = column.m_pilHover;
               }
               else
               {
                  pil = column.m_pil;
               }
               pil->draw(pDCBuffer, iImage, rect.top_left(), rect.size(), point(0,0), 0);
            }
         }
         if(_001GetElementRect(rect, iItem, iDisplayItem, iOrder, -1, userbase::_list::ElementText))
         {
            if(_001GetItemText(str, iItem, iSubItem, -1))
            {
               if(m_eview == ViewIcon && m_bEmboss)
               {
                  class size size = rect.size();
                  size.cx += 4;
                  size.cy += 4;

                  ::ca::graphics_sp dcCache(get_app());
                  dcCache->CreateCompatibleDC(NULL);
                  ::ca::font * pfontOld = dcCache->SelectObject(pfont);

                  ::ca::bitmap_sp bmpCache(get_app());
                  bmpCache->CreateCompatibleBitmap(pdc, size.cx, size.cy);
                  dcCache->SelectObject(bmpCache);
                  dcCache->FillSolidRect(0, 0, size.cx,size.cy, RGB(0, 0, 0));
                  dcCache->SetTextColor(RGB(255, 255, 255));

                  class rect rectCache;
                  rectCache.left = 2;
                  rectCache.top = 2;
                  rectCache.right = rectCache.left + (index)rect.width();
                  rectCache.bottom = rectCache.top + (index)rect.height();
                  m_dcextension._DrawText(dcCache, str, rectCache, iDrawTextFlags);
                  //string str = gen::international::utf8_to_unicode(str);
                  //::DrawTextW(dcCache, str, str.get_length(), rectCache, iDrawTextFlags);

                  System.imaging().channel_spread(dcCache, null_point(), size, dcCache, null_point(), 0, 1);
                  System.imaging().channel_gray_blur(dcCache, null_point(), size, dcCache, null_point(), 0, 1);
                  System.imaging().pre_color_blend(dcCache, dcCache, RGB(0, 0, 0));


                  dcCache->SelectObject(pfontOld);

                  System.imaging().color_blend(pDCBuffer, rect, dcCache, point(1, 1), 0.50);

                  /*               if(bHover)
                  {
                  pDCBuffer->SetTextColor(RGB(200, 200, 255));
                  }
                  else
                  {
                  pDCBuffer->SetTextColor(RGB(255, 255, 255));
                  }*/
                  pDCBuffer->SetTextColor(RGB(255, 255, 255));
                  pDCBuffer->SelectObject(pfont);
                  //::DrawTextW(*pDCBuffer, str, str.get_length(), rect, iDrawTextFlags);
                  m_dcextension._DrawText(pDCBuffer, str, class rect(rect), iDrawTextFlags);


                  /*System.imaging().AlphaTextOut(
                  pDCBuffer,
                  rect.left, rect.top,
                  gen::international::utf8_to_unicode(str), str.get_length(), 
                  crText,
                  0.25);*/
               }
               else
               {
                  m_dcextension._DrawText(pDCBuffer, str, class rect(rect), iDrawTextFlags);
               }
               //TRACE("_001DrawItem %d %S m_dcextension._DrawText\n", iItem, str);
               //TRACE("rect left-top(%d, %d) widht-height(%d, %d)\n", rect.left, rect.top, rect.width(), rect.height());
            }
         }
      }
      if(rangeHighlight.HasItem(iDisplayItem))
      {
         ::ca::pen_sp penHighlight(get_app());
         ::ca::brush_sp brushNull(get_app());
         brushNull->CreateStockObject(NULL_BRUSH);
         ::ca::pen * ppenHighlight = _001GetPenHighlight();
         class rect rectHighlight(rectItem);
         rectHighlight.deflate(2, 2);
         pDCBuffer->SelectObject(ppenHighlight);
         pDCBuffer->SelectObject(brushNull);
         pDCBuffer->Rectangle(rectHighlight);
      }

      pDCBuffer->SelectObject(pfontOld);
      pDCBuffer->SelectObject(ppenOld);
      pDCBuffer->SelectObject(pbrushOld);


   }

   index list::_001GetItemImage(index iItem, index iSubItem, index iListItem)
   {
      UNREFERENCED_PARAMETER(iItem);
      UNREFERENCED_PARAMETER(iSubItem);
      UNREFERENCED_PARAMETER(iListItem);
      /*LVITEM lvi;
      lvi.mask = LVIF_IMAGE;
      lvi.iItem = iItem;
      lvi.iSubItem = 0;
      get_item(&lvi);
      return lvi.iImage;*/
      return -1;
   }

   bool list::_001GetItemText(string & str, index iItem, index iSubItem, index iListItem)
   {
      if(m_pcache != NULL)
      {
         if(m_pcache->_001GetItemText(
            this,
            str,
            iItem,
            iSubItem,
            iListItem))
         {
            return true;
         }
      }
      if(m_pdata != NULL)
      {
         if(m_pdata->_001GetItemText(
            this,
            str,
            iItem, 
            iSubItem,
            iListItem))
         {
            return true;
         }
      }
      return false;
   }

   // Purpose:
   // Provide Item Text for Search Purposes.
   bool list::_001SearchGetItemText(
      string &str,
      index iItem,
      index iSubItem, 
      index iListItem)
   {
      return _001GetItemText(
         str, 
         iItem,
         iSubItem,
         iListItem);
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
      SCAST_PTR(::user::win::message::size, psize, pobj);
      layout();
      psize->m_bRet = false;
   }

   void list::layout()
   {

      if(m_bTopText)
         _001LayoutTopText();


      /*   scroll_info info;
      _001GetLayoutInfo(info);

      if(m_pscrollbarHorz == NULL)
      return;

      m_pscrollbarHorz->ShowWindow(info.m_bHScroll ? SW_SHOW : SW_HIDE);
      m_pscrollbarVert->ShowWindow(info.m_bVScroll ? SW_SHOW : SW_HIDE);*/

      /* trans
      pwnd->ShowScrollBar(SB_HORZ, FALSE);
      pwnd->EnableScrollBar(SB_HORZ, FALSE);
      pwnd->ShowScrollBar(SB_VERT, FALSE);
      pwnd->EnableScrollBar(SB_VERT, FALSE);
      */

      INT_PTR iCount = _001GetItemCount();
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
         m_columna.GetByKey(0).m_iWidth = iMaxWidth;
      }



      SetScrollSizes();

      LayoutHeaderCtrl();

      LayoutScrollBars();

      rect rectClient;

      GetClientRect(rectClient);

      /*   if(m_pgdibuffer != NULL)
      {
      m_pgdibuffer->UpdateBuffer(rectClient.size());
      }*/

         


   }



   /*void list::OnSettingChange(UINT uFlags, const char * lpszSection) 
   {
   ::ca::window::OnSettingChange(uFlags, lpszSection);

   //   SubclassHeaderCtrl();


   }*/

   void list::SetScrollSizes()
   {

      rect rectTotal;

      _001GetViewRect(&rectTotal);

      size sizeTotal = rectTotal.size();

      m_scrollinfo.m_sizeTotal = sizeTotal;

      rect rectViewClient;
      _001GetViewClientRect(&rectViewClient);

      ::user::scroll_info si;

      si.fMask = SIF_RANGE | SIF_PAGE;
      m_pscrollbarHorz->_001GetScrollInfo(&si);

//      index iMinPos = 0;
  //    index iMaxPos = 32767;


//      index iRange = iMaxPos - iMinPos;

      si.nMin = 0;
      si.nMax = sizeTotal.cx;
      si.nPage =  (index)rectViewClient.width();
      m_pscrollbarHorz->_001SetScrollInfo(&si);


      m_pscrollbarVert->_001GetScrollInfo(&si);

//      INT_PTR iDisplayItemCount = _001GetDisplayItemCount();
//      INT_PTR iDisplayCount = _001GetDisplayCount();

      si.nMin = 0;
      si.nMax = sizeTotal.cy;
      si.nPage = (index)rectViewClient.height();
      m_pscrollbarVert->_001SetScrollInfo(&si);



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

   /*void list::SetScrollSizes(index iMapMode)
   //{
   rect rectTotal;

   _001GetViewRect(rectTotal);

   SetScrollSizes(MM_TEXT, rectTotal.size());

   }*/

   bool list::_001OnUpdateItemCount(DWORD dwFlags)
   {
      UNREFERENCED_PARAMETER(dwFlags);
      INT_PTR iItemCount = _001GetItemCount();
      if(iItemCount < 0)
         return false;
      
      if(m_eview == ViewIcon)
      {
         for(index iStrict = 0; iStrict < iItemCount; iStrict++)
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
         index iEnd = iItemCount -1;
         m_listlayout.m_iaDisplayToStrict.set_size(iItemCount);
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

      TRACE("list::_001SetItemCountEx %d\n", iItemCount);
      _001RedrawWindow();

      return true;
   }

   void list::_001GetViewRect(LPRECT lprect)
   {
      rect rect;
      if(m_eview == ViewList)
      {
         if(_001GetItemCount() == 0)
         {
            rect = class rect(0, 0, 0, 0);
         }
         else
         {
            class rect rectClient;

            _001GetViewClientRect(&rectClient);

            class rect rectFirst;

            _001GetItemRect(0, 0, rectFirst);


            rect.top    = rectClient.top;
            rect.bottom = rectClient.bottom;
            rect.left   = rectClient.left;
            if(m_iItemHeight <= 0)
               rect.right = rectClient.right;
            else
               rect.right  = (LONG) min(
                  rectClient.left +
                  _001GetItemCount() * rectFirst.width() * m_iItemHeight / 
                  rectClient.height()
                  + rectFirst.width(), MAXLONG);
         }
      }
      else if(m_eview == ViewReport)
      {
         if(_001GetItemCount() == 0)
         {
            rect = class rect(0, 0, 0, 0);
         }
         else
         {
            class rect rectFirst;

            _001GetItemRect(0, 0, rectFirst);

            class rect rectLast;

            _001GetItemRect(_001GetItemCount() -1,_001GetItemCount() -1, rectLast);

            rect.unite(rectFirst, rectLast);
         }
      }
      else if(m_eview == ViewIcon)
      {
         class rect rectFirst;

         _001GetItemRect(0, 0, rectFirst);

         class rect rectLast;

         _001GetItemRect(_001GetItemCount() -1,_001GetItemCount() -1, rectLast);

         class rect rectTopRight;
         index iItemTopRight;
         if(m_flags.is_signalized(flag_auto_arrange) || m_iconlayout.m_iWidth <= 0)
         {
            class rect rectClient;

            _001GetViewClientRect(&rectClient);

            iItemTopRight = (index)max(1, rectClient.width() / get_item_size().cx) - 1;
         }
         else
         {
            iItemTopRight = max(1, m_iconlayout.m_iWidth) - 1;
         }
         _001GetItemRect(iItemTopRight, iItemTopRight, rectTopRight);

         rect.unite(rectFirst, rectLast);
         rect.unite(rect, rectTopRight);

      }
      *lprect = rect;
   }

   /*bool list::_001Update()
   {
   _001UpdateColumns();
   _001OnColumnChange();
   TRACE("list::_000OnPosCreate After _001OnColumnChange()\n");
   layout();

   return true;
   }*/

   /*afx_msg LRESULT list::OnPosCreateMessage(WPARAM wparam, LPARAM lparam)
   {
   m_bCreated = true;
   _001OnPosCreate();
   return 0;
   }*/


   void list::_001OnInitialize()
   {

   }

   void list::_001AddColumn(Column &column)
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
   // list::Column
   //

   const list::Column list::Column::null;

   list::Column::Column()
   {
      m_iKey                     = ColumnInvalid;
      m_iKeyVisible              = ColumnInvalid;
      m_iKeyNonVisible           = ColumnInvalid;
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
   list::Column::Column(const Column & column)
   {
      operator =(column);
   }
   list::Column::~Column()
   {
   }

   bool list::Column::operator ==(const Column & column) const
   {
      return (m_iKey == column.m_iKey)
         && (m_iKeyVisible == column.m_iKeyVisible)
         && (m_iKeyNonVisible == column.m_iKeyNonVisible);

   }

   bool list::Column::IsNull() const
   {
      return this == NULL || operator ==(null);
   }


   INT_PTR list::Column::CompareOrderSectEndNonVisible(Column &  columna, Column &  columnb)
   {
      if(columna.IsVisible() && columnb.IsVisible())
         return columna.m_iOrder - columnb.m_iOrder;
      else if(columna.IsVisible())
         return -1;
      else if(columnb.IsVisible())
         return 1;
      else
         return 0;
   }
   INT_PTR list::Column::CompareOrder(Column & columna, Column & columnb)
   {
      return columna.m_iOrder - columnb.m_iOrder;
   }

   INT_PTR list::Column::CompareKey(Column & columna, Column & columnb)
   {
      return columna.m_iKey - columnb.m_iKey;
   }

   list::Column & list::Column::operator = (const Column & column)
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
      POSITION pos = column.m_mapIcon.get_start_position();
      int iIcon;
      HICON hicon;
      m_mapIcon.remove_all();
      while (pos != NULL)
      {
         column.m_mapIcon.get_next_assoc(pos, iIcon, hicon);
         m_mapIcon.set_at(iIcon,hicon);
      }

      m_bEditOnSecondClick = column.m_bEditOnSecondClick;
      return *this;
   }

   bool list::_001GetElementRect(LPRECT lprect, index iItem, index iDisplayItem, index iOrderParam, index iListItem, userbase::_list::EElement eelement)
   {
      if(iItem < 0)
         return false;
      if(iItem >= _001GetItemCount())
         return false;
      if(iDisplayItem < 0)
         return false;
      if(m_eview == ViewIcon && iDisplayItem >= (_001GetTopIndex() + _001GetDisplayCount()))
         return false;
      if(iOrderParam < 0)
         return false;
      if(iOrderParam >= _001GetColumnCount())
         return false;

      IMAGEINFO ii;
      rect rect;
      size size;
      class rect rectItem;

      index ixSubItem;

      if(eelement == userbase::_list::ElementItem)
      {
         return _001GetItemRect(
            iDisplayItem,
            iDisplayItem,
            lprect);
      }
      if(!_001GetItemRect(
         iDisplayItem,
         iDisplayItem,
         rectItem))
      {
         return false;
      }
      if(m_eview == ViewIcon)
      {
         if(eelement == userbase::_list::ElementImage)
         {
            index iIconSize = m_columna[0].m_sizeIcon.cy;
            lprect->left = rectItem.left + iIconSize / 2;
            lprect->top = rectItem.top;
            lprect->right = lprect->left + iIconSize;
            lprect->bottom = lprect->top + iIconSize;
            return true;
         }
         else if(eelement == userbase::_list::ElementText)
         {
            index iIconSize = m_columna[0].m_sizeIcon.cy;
            lprect->left = rectItem.left;
            lprect->top = rectItem.top + iIconSize;
            lprect->right = lprect->left + iIconSize * 2;
            lprect->bottom = lprect->top + iIconSize;
            return true;
         }
         return false;
      }

      index ix = (index)rectItem.left;
      index iColumnWidth;
      INT_PTR iSubItem;
      for(index iOrder = 0; iOrder <= iOrderParam; iOrder++)
      {
         INT_PTR iColumn = _001MapOrderToColumn(iOrder);
         if(iColumn < 0)
            continue;
         Column & column = m_columna.VisibleGet(iColumn);
         iSubItem = column.m_iSubItem;
         ixSubItem = ix;
         iColumnWidth = _001GetColumnWidth(iColumn);
         if(m_bSingleColumnMode && iColumn == 0)
         {
            iColumnWidth = m_iItemWidth;
         }
         if(iOrder == iOrderParam
            && iListItem == -1
            && eelement == userbase::_list::ElementSubItem)
         {
            lprect->left = ixSubItem;
            lprect->right = ixSubItem + iColumnWidth;
            lprect->bottom = rectItem.bottom;
            lprect->top = rectItem.top;
            return true;
         }
         if(column.m_bIcon)
         {
            index iImage = _001GetItemImage(iItem, iSubItem, -1);
            if(iImage >= 0)
            {
               size = column.m_sizeIcon;
               if(iOrder == iOrderParam
                  && iListItem == -1
                  && eelement == userbase::_list::ElementImage)
               {
                  lprect->left = ix;
                  lprect->right = ix + size.cx;
                  lprect->bottom = rectItem.bottom;
                  lprect->top = rectItem.bottom - size.cy;
                  return true;
               }
               ix += size.cx;
               ix += 2;
            }
            else if(iOrder == iOrderParam
               && iListItem == -1
               && eelement == userbase::_list::ElementImage)
            {
               return false;
            }
         }
         else if(column.m_pil != NULL)
         {
            index iImage = _001GetItemImage(iItem, iSubItem, -1);
            if(iImage >= 0)
            {
               column.m_pil->get_image_info(iImage, &ii);
               rect = ii.rcImage;
               if(iOrder == iOrderParam
                  && iListItem == -1
                  && eelement == userbase::_list::ElementImage)
               {
                  lprect->left = ix;
                  lprect->right = ix + rect.width();
                  lprect->bottom = rectItem.bottom;
                  lprect->top = rectItem.bottom - rect.height();
                  return true;
               }
               ix += (index)rect.width();
               ix += 2;
            }
            else if(iOrder == iOrderParam
               && iListItem == -1
               && eelement == userbase::_list::ElementImage)
            {
               return false;
            }
         }
         else if(iOrder == iOrderParam
            && iListItem == -1
            && eelement == userbase::_list::ElementImage)
         {
            return false;
         }
         if(iOrder == iOrderParam
            && iListItem == -1
            && eelement == userbase::_list::ElementText)
         {
            lprect->left = ix;
            lprect->right = ixSubItem + iColumnWidth;
            lprect->bottom = rectItem.bottom;
            lprect->top = rectItem.top;
            return true;
         }
         ix = ixSubItem + iColumnWidth;
      }
      return false;

   }

   void list::_001OnColumnChange()
   {

      index iItemHeight = 0;
      index iItemWidth = 0;

      IMAGEINFO ii;
      index iColumnWidth;
      rect rect;

      string str;
      INT_PTR iVisible;
      INT_PTR iColumn;

      for(iColumn = 0; iColumn < m_columna.VisibleGetCount(); iColumn++)
      {
         Column & column = m_columna.VisibleGet(iColumn);
         str.Format("SubItem[%d].Visible", column.m_iSubItem);
         if(data_get(
            str,
            ::ca::system::idEmpty,
            iVisible))
         {
            if(iVisible == 0)
            {
               m_columna.ShowSubItem(column.m_iSubItem, false);
            }
         }
      }

      for(iColumn = 0; iColumn < m_columna.NonVisibleGetCount(); iColumn++)
      {
         Column & column = m_columna.NonVisibleGet(iColumn);
         str.Format("SubItem[%d].Visible", column.m_iSubItem);
         if(data_get(
            str,
            ::ca::system::idEmpty,
            iVisible))
         {
            if(iVisible != 0)
            {
               m_columna.ShowSubItem(column.m_iSubItem, true);
            }
         }
      }





      for(iColumn = 0; iColumn < m_columna.VisibleGetCount(); iColumn++)
      {
         Column & column = m_columna.VisibleGet(iColumn);
         iColumnWidth = column.m_iWidth;
         _001CreateImageList(column);
         if(iColumnWidth >= 0)
         {
            iItemWidth += iColumnWidth;
         }
         if(column.m_pil != NULL
            && column.m_pil->get_image_count() > 0)
         {
            column.m_pil->get_image_info(0, &ii);
            rect = ii.rcImage;
            if(rect.height() + 2 > iItemHeight)
            {
               iItemHeight = (index)rect.height() + 2;
            }
         }
         if(column.m_sizeIcon.cy + 2 > iItemHeight)
         {
            iItemHeight = column.m_sizeIcon.cy + 2;
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
            Column & column = m_columna.VisibleGet(iColumn);
            hditem.mask = HDI_WIDTH | HDI_TEXT | HDI_LPARAM | HDI_ORDER;
            //str.load_string(_001GetColumnTextId(iColumn));
            //hditem.pszText = (LPTSTR) (const char *) str;
            hditem.pszText = LPSTR_TEXTCALLBACK;
            //hditem.cchTextMax = str.get_length();
            hditem.cchTextMax = 0;
            hditem.cxy = column.m_iWidth;;
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

      m_columna.VisibleGet(iColumn).m_iWidth = iWidth;

      m_pheaderctrl->DIDDXColumn(true, iColumn);

      _001OnColumnChange();

   }

   int list::_001GetColumnWidth(index iColumn)
   {
      ASSERT(iColumn >= 0);
      ASSERT(iColumn < m_columna.VisibleGetCount());

      return m_columna.VisibleGet(iColumn).m_iWidth;

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
      for(index iColumn = 0; iColumn < m_columna.VisibleGetCount(); iColumn++)
      {
         Column & column = m_columna.VisibleGet(iColumn);
         if(column.m_iOrder == iOrder)
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

      return m_columna.VisibleGet(iColumn).m_iOrder;
   }

   index list::_001MapSubItemToColumn(index iSubItem)
   {
      return m_columna.VisibleMapSubItemToColumn(iSubItem);
   }

   index list::_001MapColumnToSubItem(index iColumn)
   {
      ASSERT(iColumn >= 0);
      ASSERT(iColumn < m_columna.VisibleGetCount());

      return m_columna.VisibleGet(iColumn).m_iSubItem;
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

   /////////////////////////////////////////////////////////////////
   //
   // Function: _001GetTopIndex
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
   index list::_001GetTopIndex()
   {
      index iItem;
      if(_001DisplayHitTest(point(0, m_bHeaderCtrl ? m_iItemHeight : 0), iItem))
         return iItem;
      else
         return -1;
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
      if(m_eview == ViewIcon)
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
      INT_PTR iLeft =(index) m_scrollinfo.m_ptScroll.x;
      if(m_eview == ViewList)
      {
         iLeft += point.x / m_iItemWidth * m_iItemWidth;
      }
      INT_PTR iRight;
      for(INT_PTR iColumn = 0; iColumn < iColumnCount; iColumn++)
      {
         iRight = iLeft + _001GetColumnWidth(iColumn);
         if(iLeft <= point.x &&
            point.x < iRight)
         {
            iItemParam = iItem;
            iSubItemParam = _001MapColumnToSubItem(iColumn);
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

         if(iItem >= _001GetItemCount())
            return false;

         iItemParam = (index)iItem;

         return true;
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
         index iRoundHeight = (index)((rectClient.height() / m_iItemHeight) * m_iItemHeight);

         index iy = (index)((pt.y + m_scrollinfo.m_ptScroll.y) + ((pt.x / m_iItemWidth)) * iRoundHeight);

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

         if(iItem >= _001GetItemCount())
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

   bool list::_001GetItemRect(index iItem, index iDisplayItem, LPRECT lprect)
   {
      iItem = iDisplayItem;

      if(iItem < 0)
      {
         lprect->left = 0;
         lprect->top = 0;
         lprect->right = 0;
         lprect->bottom = 0;
         return false;
      }
      if(m_eview == ViewIcon && iItem >= _001GetDisplayCount())
      {
         lprect->left = 0;
         lprect->top = 0;
         lprect->right = 0;
         lprect->bottom = 0;
         return false;
      }

      rect rect;


      if(m_eview == ViewReport)
      {
         rect.left = 0;
         rect.top = 0;
         if(m_bHeaderCtrl)
         {
            rect.top += m_iItemHeight;
         }
         rect.top += m_iItemHeight * iItem;
         if(m_bTopText)
         {
            rect.top += m_rectTopText.height();
         }
         rect.bottom = rect.top + m_iItemHeight;
         rect.right = m_iItemWidth;
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
         if(m_iItemHeight <= 0)
            return false;
         index iRoundHeight = (rectClient.height() / m_iItemHeight) * m_iItemHeight;
         if(iRoundHeight != 0)
         {
            rect.left = ((iItem * m_iItemHeight) / iRoundHeight) * m_iItemWidth;
            rect.top = (iItem * m_iItemHeight) % iRoundHeight;
         }
         if(m_bTopText)
         {
            rect.top += m_rectTopText.height();
         }
         if(m_bHeaderCtrl)
         {
            rect.top += m_iItemHeight;
         }
         rect.bottom = rect.top + m_iItemHeight;
         rect.right = rect.left + m_iItemWidth;
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
            rect.left = iItemSize * (iItem % (max(1, rectClient.width() / iItemSize) ));
            rect.top = iItemSize * (iItem / (max(1, rectClient.width() / iItemSize) ));
            rect.bottom = rect.top + iItemSize;
            rect.right = rect.left + iItemSize;
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
            rect.left = iItemSize * (iDisplayItem % m_iconlayout.m_iWidth);
            rect.top = rectClient.top + iItemSize * (iDisplayItem / m_iconlayout.m_iWidth);
            rect.bottom = rect.top + iItemSize;
            rect.right = rect.left + iItemSize;
         }
      }

      rect.offset(-m_scrollinfo.m_ptScroll.x, -m_scrollinfo.m_ptScroll.y);

      *lprect = rect;

      return true;

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
      SCAST_PTR(::user::win::message::key, pkey, pobj)
         if(pkey->previous()) // give chance to child
            return;
      if(pkey->m_nChar == VK_DOWN || pkey->m_nChar == VK_UP ||
         pkey->m_nChar == VK_NEXT || pkey->m_nChar == VK_PRIOR)
      {
         if(_001GetItemCount() > 0)
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
                  iItem = _001GetItemCount() - 1;
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
                  iItem += _001GetDisplayItemCount();
               }
               else if(pkey->m_nChar == VK_UP)
               {
                  iItem--;
               }
               else if(pkey->m_nChar == VK_PRIOR)
               {
                  iItem -= _001GetDisplayItemCount();
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
               iItem = _001GetItemCount() - 1;
            }
            else if(iItem >= _001GetItemCount())
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
      SCAST_PTR(::user::win::message::mouse, pmouse, pobj)
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
      System.set_keyboard_focus(this);
      System.set_mouse_focus_LButtonDown(this);
      pobj->m_bRet = true;
      pmouse->set_lresult(1);
   }

   void list::_001OnLButtonUp(gen::signal_object * pobj)
   {
      SCAST_PTR(::user::win::message::mouse, pmouse, pobj)
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
      SCAST_PTR(::user::win::message::mouse, pmouse, pobj)

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
            ::user::message_event, 0, (LPARAM) &ev);
      }
      else
      {
         GetParent()->SendMessage(
            ::user::message_event, 0, (LPARAM) &ev);
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
      SCAST_PTR(::user::win::message::mouse, pmouse, pobj)
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
      return ColumnInvalid;
   }

   bool list::_001OnHeaderCtrlEndDrag(WPARAM wparam, LPARAM lparam)
   {
      UNREFERENCED_PARAMETER(wparam);
      UNREFERENCED_PARAMETER(lparam);
      for(index iColumn = 0; iColumn < m_columna.VisibleGetCount(); iColumn++)
      {
         Column & column = m_columna.VisibleGet(iColumn);
         column.m_iOrder = HeaderCtrlMapColumnToOrder(iColumn);
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
         str.Format("Column[%d].width", i);
         width = _001GetColumnWidth(i);
         data_set(
            str,
            ::ca::system::idEmpty,
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
//         Column & column = m_columna.VisibleGet(iColumn);
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
         ::ca::system::idEmpty,
         bShow ? 1 : 0);
      m_columna.ShowSubItem(iSubItem, bShow);
      _001OnColumnChange();
      Redraw();

   }
   list::Column & list::ColumnArray::GetByKey(index iKey)
   {
      for(index i = 0; i < get_size(); i++)
      {
         Column & column = element_at(i);
         if(column.m_iKey == iKey)
         {
            return column;
         }
      }
      return (Column &) Column::null;

   }
   list::Column & list::ColumnArray::GetBySubItem(index iSubItem)
   {
      for(index i = 0; i < get_size(); i++)
      {
         Column & column = element_at(i);
         if(column.m_iSubItem == iSubItem)
         {
            return column;
         }
      }
      return (Column &) Column::null;

   }
   list::Column & list::ColumnArray::GlobalOrderGetPrevious(index iKey)
   {
      for(index i = 0; i < get_size(); i++)
      {
         Column & column = element_at(i);
         if(column.m_iNextGlobalOrderKey == iKey)
         {
            return column;
         }
      }
      return (Column &) Column::null;
   }
   list::Column & list::ColumnArray::GlobalOrderGetNext(index iKey)
   {
      Column & column = GetByKey(iKey);
      return GetByKey(column.m_iNextGlobalOrderKey);
   }

   list::Column & list::ColumnArray::VisibleGet(index iKeyVisible)
   {
      for(index i = 0; i < get_size(); i++)
      {
         Column & column = element_at(i);
         if(column.m_iKeyVisible == iKeyVisible)
         {
            return column;
         }
      }
      return (Column &) Column::null;

   }
   list::Column & list::ColumnArray::NonVisibleGet(index iKeyNonVisible)
   {
      for(index i = 0; i < get_size(); i++)
      {
         Column & column = element_at(i);
         if(column.m_iKeyNonVisible == iKeyNonVisible)
         {
            return column;
         }
      }
      return (Column &) Column::null;

   }

   index list::ColumnArray::add(Column &column)
   {
      column.m_iKey = get_size();
      column.m_iOrder = get_size();
      column.m_pcontainer = this;

      index index = base_array < Column, Column & >::add(column);

      OnChange();

      return index;
   }

   void list::ColumnArray::remove_all()
   {
      base_array < Column, Column & >::remove_all(),
         OnChange();
   }

   count list::ColumnArray::get_count()
   {
      return get_size();
   }

   list::ColumnArray::ColumnArray(::ca::application * papp) :
   ca(papp)
   {
      m_plist = NULL;
   }

   void list::ColumnArray::Initialize(list * plist)
   {
      ASSERT(plist != NULL);
      m_plist = plist;
   }

   void list::ColumnArray::OnChange()
   {
      sort::array::quick_sort(
         *this,
         Column::CompareKey);

      index iKeyVisible = 0;
      index iKeyNonVisible = 0;

      for(index i = 0; i < get_size(); i++)
      {
         Column & column = element_at(i);
         if(column.IsVisible())
         {
            column.m_iKeyVisible = iKeyVisible;
            column.m_iKeyNonVisible = -1;
            iKeyVisible++;
         }
         else
         {
            column.m_iKeyNonVisible = iKeyNonVisible;
            column.m_iKeyVisible = -1;
            iKeyNonVisible++;
         }
      }

      sort::array::quick_sort(
         *this,
         Column::CompareOrderSectEndNonVisible);

      for(index iOrder = 0; iOrder < get_size(); iOrder++)
      {
         Column & column = element_at(iOrder);
         column.m_iOrder = iOrder;
      }



   }

   void list::ColumnArray::remove(index iColumn)
   {
      ASSERT(iColumn >= 0);
      ASSERT(iColumn < get_size());

      remove_at(iColumn);

      OnChange();
   }

   count list::ColumnArray::VisibleGetCount()
   {
      index iCount = 0;
      for(index i = 0; i < get_size(); i++)
      {
         Column & column = element_at(i);
         if(column.IsVisible())
            iCount++;
      }
      return iCount;
   }

   count list::ColumnArray::NonVisibleGetCount()
   {
      index iCount = 0;
      for(index i = 0; i < get_size(); i++)
      {
         Column & column = element_at(i);
         if(!column.IsVisible())
            iCount++;
      }
      return iCount;
   }

   void list::ColumnArray::ShowSubItem(index iSubItem, bool bShow)
   {
      if(bShow)
      {
         index iColumn = NonVisibleMapSubItemToColumn(iSubItem);
         if(iColumn != ColumnInvalid)
         {
            Column & column = NonVisibleGet(iColumn);
            column.SetVisible(bShow);
            OnChange();
         }
      }
      else
      {
         index iColumn = VisibleMapSubItemToColumn(iSubItem);
         if(iColumn != ColumnInvalid)
         {
            Column & column = VisibleGet(iColumn);
            column.SetVisible(bShow);
            OnChange();
         }
      }
   }

   index list::ColumnArray::MapSubItemToKey(index iSubItem)
   {
      for(index iColumn = 0; iColumn < VisibleGetCount(); iColumn++)
      {
         Column & column = VisibleGet(iColumn);
         if(column.m_iSubItem == iSubItem)
            return column.m_iKey;
      }
      return ColumnInvalid;

   }

   index list::ColumnArray::VisibleMapSubItemToColumn(index iSubItem)
   {
      for(index iColumn = 0; iColumn < VisibleGetCount(); iColumn++)
      {
         Column & column = VisibleGet(iColumn);
         if(column.m_iSubItem == iSubItem)
            return iColumn;
      }
      return ColumnInvalid;

   }

   index list::ColumnArray::NonVisibleMapSubItemToColumn(index iSubItem)
   {
      for(index iColumn = 0; iColumn < NonVisibleGetCount(); iColumn++)
      {
         Column & column = NonVisibleGet(iColumn);
         if(column.m_iSubItem == iSubItem)
            return iColumn;
      }
      ASSERT(FALSE);
      return ColumnInvalid;

   }


   bool list::Column::IsVisible()
   {
      return  m_bVisible;
   }

   void list::Column::SetVisible(bool bVisible)
   {
      m_bVisible = bVisible;
   }



   void list::ColumnArray::GlobalToVisibleOrder()
   {
      INT_PTR iVisibleCount = VisibleGetCount();
      for(index iVisibleKey = 0; iVisibleKey < iVisibleCount; iVisibleKey++)
      {
         Column & column = VisibleGet(iVisibleKey);
         column.m_iOrder = VisibleGetOrderFromKey(column.m_iKey);
      }


   }

   void list::ColumnArray::VisibleToGlobalOrder(index iKeyA, index iKeyB)
   {
      if(iKeyA == iKeyB)
         return;
      Column & columnA = GetByKey(iKeyA);
      Column & columnAPrevious = GlobalOrderGetPrevious(iKeyA);
      Column & columnANext = GlobalOrderGetNext(iKeyA);
      Column & columnB = GetByKey(iKeyB);
      Column & columnBPrevious = GlobalOrderGetPrevious(iKeyB);
      Column & columnBNext = GlobalOrderGetNext(iKeyB);

      if(columnA.IsNull())
      {
         ASSERT(FALSE);
         return;
      }
      if(columnB.IsNull())
      {
         ASSERT(FALSE);
         return;
      }

      if(columnAPrevious.IsNull())
      {
         m_iFirstGlobalOrderKey = iKeyB;
      }
      else
      {
         if(columnAPrevious.m_iKey != iKeyB)
         {
            columnAPrevious.m_iNextGlobalOrderKey = iKeyB;
         }
      }


      if(columnBPrevious.IsNull())
      {
         m_iFirstGlobalOrderKey = iKeyA;
      }
      else
      {
         if(columnBPrevious.m_iKey != iKeyA)
         {
            columnBPrevious.m_iNextGlobalOrderKey = iKeyA;
         }
      }

      if(columnANext.IsNull())
      {
         columnB.m_iNextGlobalOrderKey = -1;
      }
      else
      {
         if(columnANext.m_iKey == columnB.m_iKey)
         {
            columnB.m_iNextGlobalOrderKey = iKeyA;
         }
         else
         {
            columnB.m_iNextGlobalOrderKey = columnANext.m_iKey;
         }
      }

      if(columnBNext.IsNull())
      {
         columnA.m_iNextGlobalOrderKey = -1;
      }
      else
      {
         if(columnBNext.m_iKey == columnA.m_iKey)
         {
            columnB.m_iNextGlobalOrderKey = iKeyB;
         }
         else
         {
            columnA.m_iNextGlobalOrderKey = columnBNext.m_iKey;
         }
      }



   }

   void list::ColumnArray::VisibleToGlobalOrder()
   {
      list * plist = m_plist;
      //detects change
      INT_PTR iVisibleCount = VisibleGetCount();
      INT_PTR iChangeCount = 0;
      INT_PTR iNew;
      INT_PTR iOld;
      for(INT_PTR iVisibleKey = 0; iVisibleKey < iVisibleCount; iVisibleKey++)
      {
         Column & column = VisibleGet(iVisibleKey);
         if(VisibleGetOrderFromKey(column.m_iKey) != plist->HeaderCtrlMapColumnToOrder(iVisibleKey))
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
         if(get_size() == VisibleGetCount())
         {
            for(index iColumn = 0; iColumn < VisibleGetCount(); iColumn++)
            {
               Column & column = VisibleGet(iColumn);
               column.m_iOrder = plist->HeaderCtrlMapColumnToOrder(iColumn);
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
                  GetByKey(iKey).m_iNextGlobalOrderKey = iNextKey;
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

   void list::ColumnArray::DISaveOrder()
   {
      INT_PTR iCount = get_size();
      string str;
      for(index iKey = 0; iKey < iCount; iKey++)
      {
         Column & column = GetByKey(iKey);
         str.Format("Column[%d].Next", iKey);
         m_plist->data_set(
            str,
            ::ca::system::idEmpty,
            column.m_iNextGlobalOrderKey);
      }
      str.Format("Column[-1].Next");
      m_plist->data_set(
         str,
         ::ca::system::idEmpty,
         m_iFirstGlobalOrderKey);


   }

   void list::ColumnArray::DILoadOrder()
   {
      INT_PTR iCount = get_size();
      string str;
      for(index iKey = 0; iKey < iCount; iKey++)
      {
         Column & column = GetByKey(iKey);
         str.Format("Column[%d].Next", iKey);
         m_plist->data_get(
            str,
            ::ca::system::idEmpty,
            column.m_iNextGlobalOrderKey);
      }
      str.Format("Column[-1].Next");
      m_plist->data_get(
         str,
         ::ca::system::idEmpty,
         m_iFirstGlobalOrderKey);

      GlobalToVisibleOrder();
      OnChange();

   }

   index list::ColumnArray::VisibleGetOrderFromKey(index iKey)
   {
      index iNextKey = m_iFirstGlobalOrderKey;
      index iOrder = 0;
      while(true)
      {
         Column & column = GetByKey(iNextKey);
         if(column.IsNull())
            return -1;
         if(column.IsVisible())
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
         iNextKey = column.m_iNextGlobalOrderKey;
      }
      ASSERT(FALSE);
      return -1;
   }

   index list::ColumnArray::OrderToKey(index iOrder)
   {
      for(index iKey = 0; iKey < get_count(); iKey++)
      {
         Column & column = GetByKey(iKey);
         if(column.m_iOrder == iOrder)
            return iKey;
      }
      return -1;

      /*   index iNextKey = m_iFirstGlobalOrderKey;
      index iOrder = 0;
      while(true)
      {
      Column & column = get(iNextKey);
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
      SCAST_PTR(::user::win::message::create, pcreate, pobj)


         pobj->previous();
      
      System.font_central().GetListCtrlFont()->GetLogFont(&m_logfont);
      m_font->CreateFontIndirect(&m_logfont);
      LOGFONT lf;
      lf = m_logfont;
      lf.lfUnderline = TRUE;
      //lf.lfWeight = FW_BOLD;
      m_fontHover->CreateFontIndirect(&m_logfont);

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

         if(!m_pscrollbarHorz->create(
            ::user::scroll_bar::orientation_horizontal,
            WS_CHILD 
            | WS_VISIBLE,
            rect,
            this,
            1024))
         {
            pcreate->set_lresult(-1);
            pobj->m_bRet = true;
            return;
         }

         rect.null();

         if(!m_pscrollbarVert->create(
            ::user::scroll_bar::orientation_vertical,
            WS_CHILD 
            | WS_VISIBLE,
            rect,
            this,
            1025))
         {
            pcreate->set_lresult(-1);
            pobj->m_bRet = true;
            return;
         }


         layout();

         pcreate->set_lresult(0);

         if(IsWindowVisible())
         {
            _001RedrawWindow();
         }

         pobj->m_bRet = false;


   }

   void list::TwiOnDraw(::ca::graphics *pdc)
   {
      _001OnDraw(pdc);
   }

   void list::_001CreateImageList(Column &column)
   {
      if(column.m_uiSmallBitmap == (UINT) -1 )
      {
         return;
      }
      if(column.m_pil == NULL)
      {
         column.m_pil = new image_list(get_app());
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
      SCAST_PTR(::user::win::message::timer, ptimer, pobj);
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
      rect rectItem32;
      if(!_001GetItemRect(
         iItem,
         iItem,
         rectItem32))
      {
         return false;
      }
      rect rectItem(rectItem32);
      rect rectClient;
      _001GetViewClientRect(&rectClient);
      return rectClient.intersect(rectClient, rectItem) != 0;
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
      base_array < size, size & > sizea;
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
         INT_PTR iItemCount = _001GetDisplayItemCount();
         INT_PTR iItemFirst = _001GetTopIndex();
         m_pcache->_001CacheHint(
            this,
            iItemFirst,
            iItemCount);
      }

   }

   count list::_001GetDisplayItemCount()
   {
      INT_PTR iItemCount;
      if(m_bFilter1 && (m_eview == ViewList || m_eview == ViewReport))
      {
         iItemCount = m_piaFilterList->get_count();
      }
      else
      {
         iItemCount = _001GetItemCount();
      }
      INT_PTR iItemFirst = _001GetTopIndex();
      INT_PTR iItemLast = iItemFirst;
      rect rectItem;
      rect rectIntersect;
      rect rectUpdate;
      _001GetViewClientRect(&rectUpdate);
      if(iItemFirst >= 0)
      {
         iItemLast = -1;
         for(INT_PTR i = iItemFirst + 1; i < iItemCount; i++)
         {
            if(_001GetItemRect(i, i, rectItem))
            {
               if(!rectIntersect.intersect(rectItem, rectUpdate))
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


   void list::SetDataInterface(::user::list_data *pinterface)
   {
      m_pdata = pinterface;
   }

   bool list::_001InsertColumn(Column &column)
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

      Column column;
      column.m_iWidth = -1;
      column.m_iSubItem = 0;
      column.m_iSmallImageWidth = 16;
      column.m_crSmallMask = RGB(255, 0, 255);


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
      Column & column = m_columna.GetByKey(iSubItem);
      if(column.m_pil != NULL)
      {
         index iImage = _001GetItemImage(iItem, iSubItem, -1);
         if(iImage >= 0)
         {
            column.m_pil->get_image_info(iImage, &ii);
            rect = ii.rcImage;
            cx += rect.width();
            cx += 2;
         }
      }
      string str;
      if(_001GetItemText(str, iItem, iSubItem, -1))
      {
         m_dcextension.GetTextExtent(pdc, str, size);
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
      Column & column = m_columna.GetByConfigId(key);
      if(column.IsNull())
         return -1;
      else
         return column.m_iSubItem;
   }

   index list::_001ConfigIdToColumnKey(const ::database::id & key)
   {
      Column & column = m_columna.GetByConfigId(key);
      if(column.IsNull())
         return -1;
      else
         return column.GetKey();
   }

   index list::Column::GetKey()
   {
      return m_iKey;
   }

   list::Column & list::ColumnArray::GetByConfigId(const ::database::id & key)
   {
      index iKey = MapConfigIdToKey(key);
      if(iKey >= 0)
         return element_at(iKey);
      else
         return *((Column *)NULL);

   }

   index list::ColumnArray::MapConfigIdToKey(const ::database::id & key)
   {
      for(index iKey = 0; iKey < get_size(); iKey++)
      {
         if(element_at(iKey).m_datakey == key)
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
         && iItem >= m_scrollinfo.m_ptScroll.y / m_iItemHeight + _001GetDisplayItemCount()))
      {
         m_scrollinfo.m_ptScroll.y = iItem * m_iItemHeight;
         if(m_pscrollbarVert != NULL)
         {
            ::user::scroll_info si;
            m_pscrollbarVert->_001GetScrollInfo(&si);
            si.nPos = m_scrollinfo.m_ptScroll.y; 
            m_pscrollbarVert->_001SetScrollInfo(&si, true);
         }
         if(bRedraw)
         {
            _001RedrawWindow();
         }
      }
   }

   void list::_001ItemScroll(index iItem, bool bRedraw)
   {
      if(iItem < _001GetItemCount())
      {
         m_scrollinfo.m_ptScroll.y = iItem * m_iItemHeight;
         if(m_pscrollbarVert != NULL)
         {
            ::user::scroll_info si;
            m_pscrollbarVert->_001GetScrollInfo(&si);
            si.nPos = m_scrollinfo.m_ptScroll.y; 
            m_pscrollbarVert->_001SetScrollInfo(&si, true);
         }
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
         iyScroll = iItem - _001GetDisplayItemCount() + 1;
      }
      else if(iItem >= iyScroll + _001GetDisplayItemCount())
      {
         iyScroll = iItem;
      }
      if(m_scrollinfo.m_ptScroll.y  / max(1, m_iItemHeight) != iyScroll)
      {
         ItemRange item;
         m_scrollinfo.m_ptScroll.y = iyScroll * m_iItemHeight;

         if(m_pscrollbarVert != NULL)
         {
            ::user::scroll_info si;
            m_pscrollbarVert->_001GetScrollInfo(&si);
            si.nPos = m_scrollinfo.m_ptScroll.y; 
            m_pscrollbarVert->_001SetScrollInfo(&si, true);
         }
         item.SetLBound(iyScroll);
         item.SetUBound(min(iyScroll + _001GetDisplayItemCount() - 1,
            _001GetItemCount() - 1));
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

   void list::OnDrawInterfaceDraw(::ca::graphics *pdc)
   {
      _001OnDraw(pdc);
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
            if(m_iconlayout.m_iaDisplayToStrict[m_iItemDrop] >= 0
               && m_iconlayout.m_iaDisplayToStrict[m_iItemDrop] < _001GetItemCount())
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
         if(m_listlayout.m_iaDisplayToStrict.get_count() != _001GetItemCount())
            return iDisplay;
         if(iDisplay >= m_listlayout.m_iaDisplayToStrict.get_count())
            return -1;
         return m_listlayout.m_iaDisplayToStrict[iDisplay];
      }
   }

   void list::FilterBegin()
   {
      m_efilterstate = FilterStateSetup;

      index iItemCount = _001GetItemCount();

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

      index iItemCount = _001GetItemCount();

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

   count list::_001GetDisplayCount()
   {
      if(m_eview == ViewIcon)
      {
         rect rectView;
         _001GetViewClientRect(&rectView);
         class size sizeItem = get_item_size();
         return max((rectView.width() / sizeItem.cx) * (rectView.height() / sizeItem.cy),
            m_iconlayout.m_iaDisplayToStrict.get_max_a() + 1);
      }
      else
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

      index iItemCount = min(_001GetItemCount(), m_iFilter1Step + 1000);

      index iFilter1Step;

      for(
         iFilter1Step =  m_iFilter1Step;
         iFilter1Step < iItemCount; 
      iFilter1Step++)
      {
         for(index j = 0; j < m_columna.get_count(); j++)
         {
            Column & column = m_columna.GetByKey(j);
            if(_001SearchGetItemText(
               wstrItem,
               iFilter1Step, column.m_iSubItem, -1))
            {
               //wstrItem.make_lower();
               //wstrItem.replace(L"_", L" ");
               if(PcreUtil::match(wstrItem, &m_reFilter1))
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

      return _001GetItemCount() != iItemCount;
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
      string wstr1;
      string wstr2;

      bool bOk1 = _001GetItemText(wstr1, iItem1, iSubItem, -1);
      bool bOk2 = _001GetItemText(wstr2, iItem2, iSubItem, -1);

      if(bOk1 && bOk2)
      {
         return wstr1.CompareNoCase(wstr2);
      }
      else
      {
         if(bOk1)
            return 1;
         else if(bOk2)
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
      index iCount = _001GetItemCount();
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
      SCAST_PTR(::user::win::message::mouse_wheel, pmousewheel, pobj);
      m_iWheelDelta += pmousewheel->GetDelta();

      index iDelta = m_iWheelDelta / WHEEL_DELTA;

      m_iWheelDelta -= (short) (WHEEL_DELTA * iDelta);

      m_scrollinfo.m_ptScroll.y -= iDelta * 3 * m_iItemHeight;

      if(m_scrollinfo.m_ptScroll.y < 0)
      {
         m_scrollinfo.m_ptScroll.y = 0;
      }
      else
      {
         ::user::scroll_info si;
         si.fMask = SIF_RANGE | SIF_PAGE;
         m_pscrollbarVert->_001GetScrollInfo(&si);
         index i = si.nMax - si.nPage;
         if(m_scrollinfo.m_ptScroll.y > i)
            m_scrollinfo.m_ptScroll.y = i; 
      }

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
      SCAST_PTR(::user::win::message::mouse, pmouse, pobj)
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
      Application.get_cursor_pos(&point);
      ScreenToClient(&point);

      if(_001DisplayHitTest(point, iItemEnter, iSubItemEnter))
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

   COLORREF list::_001GetItemColor(
      index iItem, 
      index iSubItem,
      index iListItem,
      int iState)
   {
      UNREFERENCED_PARAMETER(iItem);
      UNREFERENCED_PARAMETER(iSubItem);
      UNREFERENCED_PARAMETER(iListItem);
      if((iState & ItemStateSelected) != 0)
      {
         if((iState & ItemStateHover) != 0)
         {
            return m_crTextSelectedHighlight;
         }
         else
         {
            return m_crTextSelected;
         }
      }
      else
      {
         if((iState & ItemStateHover) != 0)
         {
            return m_crTextHighlight;
         }
         else
         {
            return m_crText;
         }
      }
   }


   void list::_001OnVScroll(gen::signal_object * pobj) 
   {
//      SCAST_PTR(::user::win::message::scroll, pscroll, pobj);

      pobj->previous();

      HeaderCtrlLayout();

      CacheHint();
   }

   void list::_001OnHScroll(gen::signal_object * pobj) 
   {
//      SCAST_PTR(::user::win::message::scroll, pscroll, pobj);

      pobj->previous();

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
            if(m_iconlayout.m_iaDisplayToStrict[m_iItemDrop] == -1
               || m_iconlayout.m_iaDisplayToStrict[m_iItemDrop] >= _001GetItemCount() )
            {
               return true;
            }
         }
         else
         {
            if(m_listlayout.m_iaDisplayToStrict[m_iItemDrop] == -1
               || m_listlayout.m_iaDisplayToStrict[m_iItemDrop] >= _001GetItemCount() )
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

   void list::list_layout::write(::ex1::output_stream & ostream)
   {
      //ostream << m_iaDisplayToStrict;
      ostream << m_iWidth;
   }

   void list::list_layout::read(::ex1::input_stream & istream)
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

   void list::icon_layout::write(::ex1::output_stream & ostream)
   {
      ostream << m_iaDisplayToStrict;
      ostream << m_iWidth;
   }

   void list::icon_layout::read(::ex1::input_stream & istream)
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
      if(iDisplayItem >= _001GetItemCount())
         return false;
      return true;
   }

   bool list::is_valid_strict_item(index iStrictItem)
   {
      if(iStrictItem < 0)
         return false;
      if(iStrictItem >= _001GetItemCount())
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


} // namespace user