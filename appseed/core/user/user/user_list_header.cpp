#include "framework.h"

//CLASS_DECL_CORE COLORREF BaseSession.get_default_color(uint32_t dw);

namespace user
{

   list_header::list_header(sp(::base::application) papp) :
      element(papp),
      m_font(allocer()),
      m_dcextension(papp)
   {
      m_plistctrlinterface = NULL;
      m_bTrack = false;
      m_bLButtonDown = false;
      m_bHover = false;
   }

   list_header::~list_header()
   {

   }

   void list_header::SetBaseListCtrlInterface(list *pinterface)
   {
      m_plistctrlinterface = pinterface;
   }

   void list_header::DrawItem(::draw2d::item * pdrawitem)
   {

      ::draw2d::graphics * pdc = pdrawitem->m_pgraphics;

      rect rectColumn = pdrawitem->rcItem;

      int32_t iColumn = pdrawitem->itemID;

      list * plist = m_plistctrlinterface;

      string str;

      str = System.load_string(plist->_001GetColumnTextId(ItemToColumnKey(iColumn)));

      pdc->SelectObject(m_font);

//      pdc->SetBkMode(TRANSPARENT);

      pdc->_DrawText(str, str.get_length(), rectColumn, DT_TOP | DT_LEFT | DT_END_ELLIPSIS);

   }



   index list_header::MapItemToOrder(index iItem)
   {
//#ifdef WINDOWSEX
  //    HDITEM hditem;


      //hditem.mask = HDI_ORDER| HDI_TEXT;

    //  hditem.mask = HDI_ORDER;

   //   char pszText[1024];

   //   hditem.pszText = pszText;
   //   hditem.cchTextMax = 1024;

   //   get_item(iItem, &hditem);

   //   return hditem.iOrder;
      return iItem;

//#else

      //throw todo(get_app());

//#endif

   }


   bool list_header::GetItemRect(LPRECT lprect, EElement eelement, index iItem)
   {

      if(iItem < 0)
         return false;

      list * plist = m_plistctrlinterface;
      if(iItem >= plist->_001GetColumnCount())
         return false;

      int32_t x;
      if(plist->m_bGroup && plist->m_bLateralGroup)
      {
         x = plist->m_iLateralGroupWidth;
      }
      else
      {
         x = 0;
      }
      int32_t xLast = x;
      draw_list_item item(plist);
      for(int32_t i = 0; i <= iItem; i++)
      {
         xLast = x;
         item.m_iWidthColumn = ItemToColumnKey(i);
         plist->_001GetColumnWidth(&item);
         if(item.m_bOk)
         {
            x += item.m_iColumnWidth;
         }
      }

      rect rect;

      GetClientRect(rect);
      rect.left = xLast;
      rect.right = x;

      if(eelement == ElementItem)
      {
         *lprect = rect;
         return true;
      }

      if(eelement == ElementItemBox)
      {
         rect.right -= GetDividerWidth();
         *lprect = rect;
         return true;
      }

      if(eelement == ElementDivider)
      {
         rect.left = rect.right - GetDividerWidth();
         *lprect = rect;
         return true;
      }
      return true;
   }

   bool list_header::GetItemRect(
      LPRECT lprect,
      EElement eelementLButtonDown,
      index iItemLButtonDown,
      EElement eelement,
      index iItem)
   {
      if(iItem < 0)
         return false;
      list * plist = m_plistctrlinterface;
      if(iItem >= plist->_001GetColumnCount())
         return false;


      if(eelementLButtonDown == ElementItemBox
         && eelement == ElementItemBox)
      {
         if(iItem == iItemLButtonDown)
         {
            class rect rectA;
            if(!GetItemRect(rectA, ElementItemBox, iItem - 1))
            {
               GetItemRect(rectA, ElementItemBox, iItem);
            }

            class rect rect;
            GetItemRect(rect, ElementItemBox, iItem);

            class rect rectB;
            if(!GetItemRect(rectA, ElementItemBox, iItem + 1))
            {
               GetItemRect(rectA, ElementItemBox, iItem);
            }

            rect.left = rectA.left + rectA.width() / 2;
            rect.right = rectB.left + rectB.width() / 2;
            *lprect = rect;
            return true;
         }
         else if(iItem <= iItemLButtonDown - 1)
         {
            rect rectA;
            if(!GetItemRect(rectA, ElementItemBox, iItem - 1))
            {
               GetItemRect(rectA, ElementItemBox, iItem);
            }

            rect rect;
            GetItemRect(rect, ElementItemBox, iItem);

            rect.left = rectA.left + rectA.width() / 2;
            rect.right = rect.left + rect.width() / 2;
            *lprect = rect;
            return true;
         }
         else if(iItem >= iItemLButtonDown + 1)
         {
            rect rectB;
            if(!GetItemRect(rectB, ElementItemBox, iItem + 1))
            {
               GetItemRect(rectB, ElementItemBox, iItem);
            }

            rect rect;
            GetItemRect(rect, ElementItemBox, iItem);

            rect.left = rect.left + rect.width() / 2;
            rect.right = rectB.left + rectB.width() / 2;
            *lprect = rect;
            return true;
         }
         return false;
      }
      else
      {
         return GetItemRect(lprect, eelement, iItem);
      }

   }

   bool list_header::hit_test(POINT point, EElement & eelement, index & iItemParam)
   {
      list * plist = m_plistctrlinterface;
      rect rect;
      for(int32_t iItem = 0; iItem < plist->_001GetColumnCount(); iItem++)
      {
         if(GetItemRect(rect, ElementItemBox, iItem))
         {
            if(rect.contains(point))
            {
               iItemParam = iItem;
               eelement = ElementItemBox;
               return true;
            }
         }
         if(GetItemRect(rect, ElementDivider, iItem))
         {
            if(rect.contains(point))
            {
               iItemParam = iItem;
               eelement = ElementDivider;
               return true;
            }
         }
      }
      return false;
   }

   bool list_header::hit_test(POINT point, EElement eelementLButtonDown, index iItemLButtonDown, EElement & eelement, index & iItemParam)
   {
      list * plist = m_plistctrlinterface;
      rect rect;
      for(int32_t iItem = 0; iItem < plist->_001GetColumnCount(); iItem++)
      {
         if(GetItemRect(rect, eelementLButtonDown, iItemLButtonDown, ElementItemBox, iItem))
         {
            if(rect.contains(point))
            {
               iItemParam = iItem;
               eelement = ElementItemBox;
               return true;
            }
         }
         if(GetItemRect(rect, ElementDivider, iItem))
         {
            if(rect.contains(point))
            {
               iItemParam = iItem;
               eelement = ElementDivider;
               return true;
            }
         }
      }
      return false;
   }


   index list_header::ItemToColumnKey(index iItem)
   {
      list * plist = m_plistctrlinterface;
      return plist->_001MapColumnToOrder(iItem);
   }

   bool list_header::DIDDXLayout(bool bSave)
   {
      bool bFail = false;
      if(!DIDDXColumn(bSave))
         bFail = true;
      return !bFail;

   }

   bool list_header::DIDDXColumn(bool bSave)
   {

      string str;

      int_array iaWidth;

      str = "::user::list_column_width";

      draw_list_item item(m_plistctrlinterface);

      if(bSave)
      {
         for (index iColumn = 0; iColumn < m_plistctrlinterface->_001GetColumnCount(); iColumn++)
         {
            item.m_iWidthColumn = iColumn;
            m_plistctrlinterface->_001GetColumnWidth(&item);
            if (item.m_bOk)
            {
               iaWidth.add(item.m_iColumnWidth);
            }
            else
            {
               iaWidth.add(-1);
            }
         }
         if(!data_set(str, ::base::system::idEmpty, iaWidth))
            return false;
      }
      else
      {
         if(data_get(
            str,
            ::base::system::idEmpty,
            iaWidth))
         {
            for (index iColumn = 0; iColumn < m_plistctrlinterface->_001GetColumnCount(); iColumn++)
            {
               m_plistctrlinterface->_001SetColumnWidth(iColumn, max(iaWidth[iColumn], 50));
            }
         }
         else
            return false;
      }
      return true;
   }

   void list_header::AddMessageHandling(::message::dispatch *pinterface)
   {
      IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN, pinterface, this, &list_header::_001OnLButtonDown);
      IGUI_WIN_MSG_LINK(WM_LBUTTONUP, pinterface, this, &list_header::_001OnLButtonUp);
      IGUI_WIN_MSG_LINK(WM_LBUTTONDBLCLK, pinterface, this, &list_header::_001OnLButtonDblClk);
      IGUI_WIN_MSG_LINK(WM_MOUSEMOVE, pinterface, this, &list_header::_001OnMouseMove);
   }

   void list_header::_001OnLButtonDown(signal_details * pobj)
   {
      SCAST_PTR(::message::mouse, pmouse, pobj)
      point ptCursor = pmouse->m_pt;
      ScreenToClient(&ptCursor);
      if(hit_test(ptCursor, m_eelementLButtonDown, m_iItemLButtonDown))
      {
         m_bLButtonDown = true;
      }

      pmouse->m_bRet = false;
   }

   void list_header::_001OnLButtonUp(signal_details * pobj)
   {
      SCAST_PTR(::message::mouse, pmouse, pobj)
      list * plist = m_plistctrlinterface;
      point ptCursor = pmouse->m_pt;
      ScreenToClient(&ptCursor);
      if(m_bLButtonDown)
      {
         m_bLButtonDown = false;
         EElement eelement;
         index iItem;
         if(hit_test(ptCursor, eelement, iItem))
         {
            if(m_eelementLButtonDown == ElementItemBox
               && eelement == ElementItemBox)
            {
               if(iItem == m_iItemLButtonDown)
               {
                  // This is a single click in a header item
                  plist->_001OnListHeaderItemClick(iItem);
               }
               else // iItem != m_iItemLButtonDown
               {
                  // The header item has been dragged

                  int_ptr iKeyA = plist->m_columna.OrderToKey(iItem);
                  int_ptr iKeyB = plist->m_columna.OrderToKey(iItem);
                  int_ptr iOrderA = plist->m_columna._001GetByKey(iKeyA)->m_iOrder;
                  int_ptr iOrderB = plist->m_columna._001GetByKey(iKeyB)->m_iOrder;
                  plist->m_columna._001GetByKey(iKeyA)->m_iOrder = iOrderB;
                  plist->m_columna._001GetByKey(iKeyB)->m_iOrder = iOrderA;
                  plist->_001OnColumnChange();
                  plist->DISaveOrder();
                  plist->Redraw();
                  Redraw();
               }
            }
            else if(m_eelementLButtonDown == ElementDivider)
            {
               rect rect;
               GetItemRect(rect, ElementItem, m_iItemLButtonDown);
               rect.right = ptCursor.x;
               int32_t iNewWidth = rect.width();
               plist->_001SetColumnWidth(m_iItemLButtonDown, max(0, iNewWidth));
               plist->Redraw();
               Redraw();
            }

         }
      }

      pmouse->m_bRet = false;
   }



   void list_header::_001OnMouseMove(signal_details * pobj)
   {
      SCAST_PTR(::message::mouse, pmouse, pobj)
      point ptCursor = pmouse->m_pt;
      ScreenToClient(&ptCursor);
      list * plist = m_plistctrlinterface;
      EElement eelement;
      index iItem;
      if(hit_test(ptCursor, eelement, iItem))
      {
         if(!m_bTrack)
         {
            m_bTrack = true;
            // trans SetCapture();
         }
         m_bHover = true;
         m_eelementHover = eelement;
         m_iItemHover = iItem;
      }
      else
      {
         if(m_bTrack)
         {
            m_bTrack = false;
            System.release_capture_uie();
         }
         if(m_bHover)
         {
            m_bHover = false;
         }
      }

      if(m_bLButtonDown)
      {
           if(m_eelementLButtonDown == ElementDivider)
         {
            rect rect;
            GetItemRect(rect, ElementItem, m_iItemLButtonDown);
            rect.right = ptCursor.x;
            int32_t iNewWidth = rect.width();
            plist->_001SetColumnWidth(m_iItemLButtonDown, max(0, iNewWidth));
            plist->Redraw();
            Redraw();
         }
      }


      if(m_bHover && m_eelementHover == ElementDivider)
      {
         pmouse->m_ecursor = ::visual::cursor_size_horizontal;
      }
      else
      {
         pmouse->m_ecursor = ::visual::cursor_arrow;
      }

      pmouse->m_bRet = false;
   }


   void list_header::_001OnLButtonDblClk(signal_details * pobj)
   {
      SCAST_PTR(::message::mouse, pmouse, pobj)
      point ptCursor = pmouse->m_pt;
      ScreenToClient(&ptCursor);
      list * plist = m_plistctrlinterface;
      EElement eelement;
      index iItem;
      if(hit_test(
         ptCursor,
         eelement,
         iItem)
         )
      {
         if(eelement == ElementItemBox)
         {
            plist->_001OnListHeaderItemDblClk(iItem);
         }
      }

      pmouse->m_bRet = false;
   }

   void list_header::_001OnDraw(::draw2d::graphics *pdc)
   {

      rect rectClient;

      GetClientRect(rectClient);

      rect rectUpdate(rectClient);

      rect rectClipBox;

      pdc->GetClipBox(rectClipBox);

      if(rectClipBox.is_empty())
      {
         rectClipBox = rectClient;
      }

      rectUpdate.intersect(rectUpdate, rectClipBox);

      class imaging & imaging = System.visual().imaging();

      imaging.color_blend(pdc, rectUpdate, RGB(127, 127, 117), 128);

      ::draw2d::item drawitem;
      drawitem.m_pgraphics = pdc;
      list * plist = m_plistctrlinterface;
      rect rectDivider;
      for(int32_t iItem = 0; iItem < plist->_001GetColumnCount(); iItem++)
      {
         drawitem.itemID = iItem;
         GetItemRect(&drawitem.rcItem, ElementItemBox, iItem);
         DrawItem(&drawitem);
         GetItemRect(rectDivider, ElementDivider, iItem);
         pdc->Draw3dRect(rectDivider, BaseSession.get_default_color(COLOR_BTNSHADOW), BaseSession.get_default_color(COLOR_BTNHIGHLIGHT));
      }

   }

   int32_t list_header::GetDividerWidth()
   {
      return 4;
   }

} // namespace user
