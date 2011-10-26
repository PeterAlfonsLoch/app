#include "StdAfx.h"

namespace user
{

   tab::data::data(::ca::application * papp) :
      ca(papp),
      ::ca::data(papp),
      m_imagelist(papp),
      m_pen(papp),
      m_font(papp),
      m_fontUnderline(papp),
      m_fontBold(papp),
      m_dcextension(papp)
   {
      
      m_bEnableCloseAll = false;

   }

   tab::data::~data()
   {
   }

   tab::pane * tab::data::get_pane_by_id(id id)
   {
      return m_panea.get_by_id(id);
   }

   count tab::data::get_visible_tab_count()
   {
      return m_panea.get_visible_count();
   }

   tab::tab(::ca::application * papp) :
      ca(papp),
      place_holder_container(papp),
      m_dcextension(papp)
   {

      m_spdata = new data(papp);
      get_data()->m_panea.set_app(papp);
      get_data()->m_iHeightAddUp = 0;
      get_data()->m_pcallback    = NULL;
      get_data()->m_bCreated     = false;
      get_data()->m_iTabHeight   = 16;
      get_data()->m_iTabWidth    = 48;
      get_data()->m_imagelist.create(16, 16, 0, 0, 0);

      get_data()->m_pen->CreatePen(PS_SOLID, 1, RGB(32, 32, 32));

      get_data()->m_iDragTab     = -1;

      m_bRestoringTabs           = true;

      m_bShowTabs                = true;

      //m_rectBorder.set(7, 1, 7, 0);

      LOGFONT                 lf;

      memset(&lf, 0, sizeof(lf));

      ::ca::graphics_sp spgraphics(get_app());
      spgraphics->CreateCompatibleDC(NULL);

      lf.lfHeight         = (int)-MulDiv(10, spgraphics->GetDeviceCaps(LOGPIXELSY), 72);
      lf.lfWeight         = FW_NORMAL;
      lf.lfCharSet        = DEFAULT_CHARSET;
      lf.lfClipPrecision  = CLIP_DEFAULT_PRECIS;
      lf.lfQuality        = PROOF_QUALITY;
      lf.lfPitchAndFamily = FF_ROMAN|DEFAULT_PITCH;
      lstrcpy(lf.lfFaceName, "Lucida Sans Unicode");

      get_data()->m_font->CreateFontIndirect(&lf);

      lf.lfWeight         = FW_BOLD;
      get_data()->m_fontBold->CreateFontIndirect(&lf);

      lf.lfWeight         = FW_NORMAL;
      lf.lfUnderline      = TRUE;
      get_data()->m_fontUnderline->CreateFontIndirect(&lf);

      _001SetVertical(false);

   }

   tab::~tab()
   {
   }

   /*bool tab::add_tab(UINT uiIdTitle, int iId)
   {
      pane pane;
      pane.m_uiId = uiIdTitle;
      pane.m_strTitleEx = L"";
      pane.m_iId = iId == -1 ? get_data()->m_panea.get_size() : iId;
   /*   if(!pane.m_wstrTitle.load_string(uiIdTitle))
      {
         return false;
      }*/
   //   pane.m_pcontainer = pcontainer;
     // pane.m_typeinfo = NULL;
     /* pane.m_iImage = -1;

      get_data()->m_panea.add(pane);
      return true;
   }*/

   bool tab::set_title(int iPane, const char * lpcsz)
   {
      get_data()->m_panea[iPane].m_strTitleEx = lpcsz;
      return true;
   }

   bool tab::SetTitleById(id id, const char * lpcsz)
   {
      get_data()->m_panea[get_tab_by_id(id)].m_strTitleEx = lpcsz;
      return true;
   }

   bool tab::set_tab(const char * lpcsz, id id, bool bVisible)
   {
      return add_tab(lpcsz, id, bVisible, true);
   }

   bool tab::add_tab(const char * lpcsz, id id, bool bVisible, bool bPermanent)
   {

      pane pane;
      pane.m_strTitleEx       = lpcsz;
      pane.m_bVisible         = bVisible;
      pane.m_bPermanent       = bPermanent;
      if(id.is_empty())
         id = get_data()->m_panea.get_size();
      pane.m_id               = id;
      pane.m_dib.destroy();
      pane.m_pholder          = NULL;
      get_data()->m_panea.add(pane);
      on_change_pane_count();
      return true;
   }

   bool tab::remove_tab_by_id(id id)
   {
      for(int i = 0; i < get_data()->m_panea.get_count(); i++)
      {
         if(get_data()->m_panea[i].m_id == id)
         {
            get_data()->m_panea.remove_at(i);
            return true;
         }
      }
      return true;
   }

   bool tab::set_image_tab(const char * lpcszTitle, const char * pszImage, id id, bool bVisible)
   {
      return add_image_tab(lpcszTitle, pszImage, id, bVisible, true);
   }

   bool tab::add_image_tab(const char * lpcszTitle, const char * pszImage, id id, bool bVisible, bool bPermanent)
   {

      pane * ppane = get_data()->m_panea.add_new();

      if(ppane == NULL)
         return false;
      ppane->m_bVisible    = bVisible;
      ppane->m_bPermanent  = bPermanent;
      ppane->m_strTitleEx  = lpcszTitle;
      if(id.is_empty())
         id = get_data()->m_panea.get_size();
      ppane->m_id          = id;
      ppane->m_pholder     = NULL;
      ppane->m_dib.create(get_app());
      ppane->m_dib.load_from_file(pszImage);
      on_change_pane_count();
      return true;
   }

   void tab::remove_tab(int iPane, bool bVisible)
   {

      if(iPane < 0 || iPane >= get_data()->m_panea.get_size())
         return;

      if(bVisible)
      {
         for(int i = 0; iPane >= 0 && i < get_data()->m_panea.get_count(); i++)
         {
            if(get_data()->m_panea[i].m_bVisible)
            {
               if(iPane <= 0)
               {
                  get_data()->m_panea.remove_at(i);
                  on_change_pane_count();
                  break;
               }
               else
               {
                  iPane--;
               }
            }
         }
      }
      else
      {
         get_data()->m_panea.remove_at(iPane);
         on_change_pane_count();
      }
   }


   void tab::_001OnDraw(::ca::graphics * pdc)
   {

      if(!m_bShowTabs)
         return;

      if(GetParentFrame()->IsFullScreen()
     && (GetParentFrame()->GetTopLevelFrame() == NULL))
      {
         rect rectTab(get_data()->m_rectTab);
         ClientToScreen(rectTab);
         m_bShowTabs = rectTab.contains(Bergedge.m_ptCursor);
         if(!m_bShowTabs)
            return;
      }

      if(get_data()->is_in_use())
         return;

      pdc->SetBkColor(RGB(255, 255, 255));

      class rect rect;
      class rect rectBorder;
      class rect rectText;
      class rect rectClient;
      class rect rectIcon;
      class rect rectClose;

      HGDIOBJ hOldPen = pdc->SelectObject(get_data()->m_pen);

      class imaging & imaging = System.imaging();

      imaging.color_blend(
         pdc,
         get_data()->m_rectTab,
         RGB(250, 255, 255),
         127);


      int iVisiblePane = 0;

      for(int iPane = 0; iPane < get_data()->m_panea.get_size(); iPane++)
      {

         pane & pane = get_data()->m_panea[iPane];

         if(!pane.m_bVisible)
            continue;



         if(!get_element_rect(iVisiblePane, rect, element_tab))
            continue;

         if(!get_element_rect(iVisiblePane, rectBorder, element_border))
            continue;

         if(!get_element_rect(iVisiblePane, rectClient, element_client))
            continue;


         if(get_data()->m_bVertical)
         {
            if(get_element_rect(iVisiblePane, rectIcon, element_icon))
            {
               pane.m_dib->bitmap_blend(pdc, rectIcon);
            }

            if(get_data()->m_iaSel.contains(iPane))
            {
               pdc->SelectObject(get_data()->m_fontBold);
               pdc->SetTextColor(RGB(0, 0, 0));

               pdc->MoveTo(rectBorder.right, rectBorder.bottom);
               pdc->LineTo(rectBorder.left + 1, rectBorder.bottom);
               pdc->LineTo(rectBorder.left, rectBorder.top - (rectBorder.left - rectClient.left));
               pdc->LineTo(rectClient.left, rectBorder.top);
               pdc->LineTo(rectBorder.right, rectBorder.top);
            }
            else
            {
               pdc->MoveTo(rectBorder.right, rectBorder.bottom);
               pdc->LineTo(rectBorder.left + 1, rectBorder.bottom);
               pdc->LineTo(rectBorder.left, rectBorder.top - (rectBorder.left - rectClient.left));
               pdc->LineTo(rectText.left, rectBorder.top);
               pdc->LineTo(rectBorder.right, rectBorder.top);
               pdc->LineTo(rectBorder.right, rectBorder.bottom);
               if(iVisiblePane == m_iHover && m_eelementHover != element_close_tab_button)
               {
                  pdc->SelectObject(get_data()->m_fontUnderline);
                  pdc->SetTextColor(RGB(0, 127, 255));
               }
               else
               {
                  pdc->SelectObject(get_data()->m_font);
                  pdc->SetTextColor(RGB(0, 0, 0));
               }
            }


         }
         else
         {

            if(get_element_rect(iVisiblePane, rectIcon, element_icon))
            {
               pane.m_dib->bitmap_blend(pdc, rectIcon);
            }

            if(get_data()->m_iaSel.contains(iPane))
            {
               pdc->MoveTo(rectBorder.left, rectClient.bottom);
               //pdc->LineTo(rectBorder.left, rectText.bottom);
               pdc->LineTo(rectBorder.left, rectBorder.top);
               pdc->LineTo(rectClient.right, rectBorder.top);
               pdc->LineTo(rectBorder.right, rectBorder.top + (rectBorder.right - rectClient.right));
               pdc->LineTo(rectBorder.right - 1, rectClient.bottom);
               //pdc->LineTo(rect.right, rectText.bottom);
               pdc->SelectObject(get_data()->m_fontBold);
               pdc->SetTextColor(RGB(0, 0, 0));
            }
            else
            {
               //pdc->MoveTo(rect.left, rectBorder.bottom);
               //pdc->LineTo(rect.right, rectBorder.bottom);
               pdc->MoveTo(rectBorder.left, rectClient.bottom);
               pdc->LineTo(rectBorder.left, rectBorder.top);
               pdc->LineTo(rectClient.right, rectBorder.top);
               pdc->LineTo(rectBorder.right, rectBorder.top + (rectBorder.right - rectClient.right));
               pdc->LineTo(rectBorder.right - 1, rectClient.bottom);
               pdc->LineTo(rectBorder.left, rectClient.bottom);

               if(iVisiblePane == m_iHover && m_eelementHover != element_close_tab_button)
               {
                  pdc->SelectObject(get_data()->m_fontUnderline);
                  pdc->SetTextColor(RGB(0, 127, 255));
               }
               else
               {
                  pdc->SelectObject(get_data()->m_font);
                  pdc->SetTextColor(RGB(0, 0, 0));
               }
            }

         }
         if(get_element_rect(iVisiblePane, rectText, element_text))
         {
            string str;
            pane.get_title(get_app(), str);
            pdc->SetBkMode(TRANSPARENT);
            get_data()->m_dcextension._DrawText(
               pdc,
               str,
               rectText,
               DT_LEFT
               | DT_BOTTOM);
         }
         if(get_element_rect(iVisiblePane, rectClose, element_close_tab_button))
         {
            pdc->SelectObject(get_data()->m_fontBold);
            if(iVisiblePane == m_iHover && m_eelementHover == element_close_tab_button)
            {
               pdc->SetTextColor(RGB(255, 127, 0));
            }
            else
            {
               pdc->SetTextColor(RGB(0, 0, 0));
            }
            pdc->DrawText("x", rectClose, DT_CENTER | DT_VCENTER);
         }


         iVisiblePane++;

      }
      pdc->SelectObject(hOldPen);

   }


   void tab::GetTabClientRect(LPRECT lprect)
   {
      *lprect = get_data()->m_rectTabClient;
   }

   void tab::GetTabClientRect(__rect64 * lprect)
   {
      rect rectClient;
      GetClientRect(rectClient);
      rect64 rect64(rectClient);
      *lprect = rect64;
   }

   void tab::layout()
   {
      if(!get_data()->m_bCreated)
         return;

      if(get_data()->m_bVertical)
      {
         int iTabWidth = 16;
         int iTabHeight = 8;
         int cx;
         int cy;
         ::ca::graphics * pdc = m_pguie->GetDC();
         pdc->SelectObject(get_data()->m_fontBold);
         for(int iPane = 0; iPane < get_data()->m_panea.get_size(); iPane++)
         {
            pane & pane = get_data()->m_panea[iPane];
            if(!pane.m_bVisible)
               continue;
            string str;
            pane.get_title(get_app(), str);
            size size;
            m_dcextension.GetTextExtent(
               pdc,
               str,
               size);
            if(pane.m_dib.is_set())
            {
               size.cx += pane.m_dib->width()+ 2;
               size.cy = max(size.cy, pane.m_dib->height());
            }
            cx = size.cx + 2;

            if(!pane.m_bPermanent)
            {
               cx += 2 + 16 + 2;
            }

            if(cx > iTabWidth)
            {
               iTabWidth = cx;
            }
            cy = size.cy + 2;
            if(cy > iTabHeight)
            {
               iTabHeight = cy;
            }
         }

         // close tab button
         cy = 2 + 16 + 2;
         if(cy > iTabHeight)
         {
            iTabHeight = cy;
         }

         iTabWidth += get_data()->m_rectBorder.left + get_data()->m_rectBorder.right +
               get_data()->m_rectMargin.left + get_data()->m_rectMargin.right +
               get_data()->m_rectTextMargin.left + get_data()->m_rectTextMargin.right;

         get_data()->m_iTabWidth = iTabWidth;

         iTabHeight += get_data()->m_rectBorder.top + get_data()->m_rectBorder.bottom +
               get_data()->m_rectMargin.top + get_data()->m_rectMargin.bottom +
               get_data()->m_rectTextMargin.top + get_data()->m_rectTextMargin.bottom;

         get_data()->m_iTabHeight = iTabHeight;

         rect rectClient;
         GetClientRect(rectClient);

         get_data()->m_rectTab.left       = rectClient.left;
         get_data()->m_rectTab.top        = rectClient.top;
         get_data()->m_rectTab.right      = get_data()->m_rectTab.left + get_data()->m_iTabWidth;
         get_data()->m_rectTab.bottom     = rectClient.bottom;

   /*      m_pguie->SetWindowPos(
            ZORDER_TOP,
            m_rectTab.left,
            m_rectTab.top,
            m_rectTab.width(),
            m_rectTab.height(),
            0);*/

         get_data()->m_rectTabClient.left       = get_data()->m_rectTab.right;
         get_data()->m_rectTabClient.top        = get_data()->m_rectTab.top;
         get_data()->m_rectTabClient.right      = rectClient.right;
         get_data()->m_rectTabClient.bottom     = get_data()->m_rectTab.bottom;
         m_pguie->ReleaseDC(pdc);
      }
      else
      {
         int iTabHeight = 16;
         int cy;
         ::ca::graphics_sp graphics(get_app());
         graphics->CreateCompatibleDC(NULL);
         ::ca::graphics * pdc = graphics;
         pdc->SelectObject(get_data()->m_fontBold);
         for(int iPane = 0; iPane < get_data()->m_panea.get_size(); iPane++)
         {
            pane & pane = get_data()->m_panea[iPane];
            if(!pane.m_bVisible)
               return;
            string str;
            pane.get_title(get_app(), str);
            size size;
            m_dcextension.GetTextExtent(
               pdc,
               str,
               size);
            if(pane.m_dib.m_p != NULL)
            {
               size.cy = max(size.cy, pane.m_dib->size().cy);
            }
            cy = size.cy + 2;
            if(cy > iTabHeight)
            {
               iTabHeight = cy;
            }
         }

         // close tab button
         cy = 2 + 16 + 2;
         if(cy > iTabHeight)
         {
            iTabHeight = cy;
         }

         iTabHeight += get_data()->m_rectBorder.top + get_data()->m_rectBorder.bottom +
               get_data()->m_rectMargin.top + get_data()->m_rectMargin.bottom + get_data()->m_iHeightAddUp;

         get_data()->m_iTabHeight = iTabHeight;

         rect rectClient;
         GetClientRect(rectClient);


         get_data()->m_rectTab.left       = rectClient.left;
         get_data()->m_rectTab.top        = rectClient.top;
         get_data()->m_rectTab.right      = rectClient.right;
         get_data()->m_rectTab.bottom     = get_data()->m_rectTab.top + get_data()->m_iTabHeight;

   /*      SetWindowPos(
            ZORDER_TOP,
            m_rectTab.left,
            m_rectTab.top,
            m_rectTab.width(),
            m_rectTab.height(),
            0);*/

         get_data()->m_rectTabClient.left       = get_data()->m_rectTab.left;
         get_data()->m_rectTabClient.top        = get_data()->m_rectTab.bottom;
         get_data()->m_rectTabClient.right      = get_data()->m_rectTab.right;
         get_data()->m_rectTabClient.bottom     = rectClient.bottom;
      }

      int iSel = _001GetSel();
      if(iSel >= 0)
      {
         place_holder * pholder = get_tab_holder(iSel);
         if(pholder != NULL)
         {
            rect rectChild;
            GetTabClientRect(rectChild);
            rect rectWindow;
            pholder->GetWindowRect(rectWindow);
            ScreenToClient(rectWindow);
            pholder->SetWindowPos(ZORDER_TOP, rectChild.left, rectChild.top, rectChild.width(), rectChild.height(), SWP_SHOWWINDOW);
         }
      }

   }

   void tab::_001OnLButtonDown(gen::signal_object * pobj)
   {
      SCAST_PTR(::user::win::message::mouse, pmouse, pobj);
      class point point = pmouse->m_pt;
      ScreenToClient(&point);

      int iPane = hit_test(point, m_eelement);

      get_data()->m_bDrag = false;
      if(iPane >= 0)
      {
         if(iPane != _001GetSel())
         {
            get_data()->m_iDragTab = iPane;
            SetTimer(5432187, 884, NULL);
            pmouse->m_bRet = true;
            pmouse->set_lresult(1);
         }
         else if(m_eelement == element_close_tab_button)
         {
            get_data()->m_iDragTab = iPane;
            pmouse->m_bRet = true;
            pmouse->set_lresult(1);
         }
      }
   }


   void tab::_001OnLButtonUp(gen::signal_object * pobj)
   {
      SCAST_PTR(::user::win::message::mouse, pmouse, pobj);
      class point point = pmouse->m_pt;
      ScreenToClient(&point);

      e_element eelement;

      int iPane = hit_test(point, eelement);

      KillTimer(5432187);
      if(iPane >= 0 && get_data()->m_iDragTab == iPane && m_eelement == eelement)
      {
         if(eelement == element_close_tab_button)
         {
            _001OnTabClose(iPane);
         }
         else
         {
            _001OnTabClick(iPane);
         }
         pmouse->m_bRet = true;
         pmouse->set_lresult(1);
      }
      else
      {
         get_data()->m_iDragTab = -1;
      }
   }

   void tab::_001OnMouseMove(gen::signal_object * pobj)
   {
      SCAST_PTR(::user::win::message::mouse, pmouse, pobj);
      class point point = pmouse->m_pt;
      ScreenToClient(&point);
      if(get_data()->m_iDragTab >= 0)
      {
         if(get_data()->m_pcallback != NULL)
         {
            get_data()->m_pcallback->_001DropTargetWindowRelay(this);
         }
      }
      if(m_iHover < 0)
      {
         track_mouse_hover();
      }

      int iHover = hit_test(point, m_eelementHover);
      if(iHover != m_iHover)
      {
         m_iHover = iHover;
         _001RedrawWindow();
      }
   }


   void tab::_001OnMouseLeave(gen::signal_object * pobj)
   {
      SCAST_PTR(::user::win::message::base, pbase, pobj);
      m_iHover = -1;
      GetParent()->_001RedrawWindow();
      pbase->set_lresult(0);
      pobj->m_bRet = true;
   }

   bool tab::get_element_rect(int iTabParam, LPRECT lprect, e_element eelement)
   {
      if(iTabParam < 0 || iTabParam >= GetTabCount())
         return false;
      if(eelement == element_border)
      {
         if(!get_element_rect(iTabParam, lprect, element_tab))
            return false;
         deflate(lprect, get_data()->m_rectMargin);
         return true;
      }
      if(eelement == element_client)
      {
         if(!get_element_rect(iTabParam, lprect, element_border))
            return false;
         deflate(lprect, get_data()->m_rectBorder);
         return true;
      }
      if(eelement == element_icon)
      {
         if(get_data()->m_panea[iTabParam].m_dib.is_null())
            return false;
         if(!get_element_rect(iTabParam, lprect, element_client))
            return false;
         lprect->right = lprect->left + get_data()->m_panea[iTabParam].m_dib->width();
         lprect->bottom = lprect->top + get_data()->m_panea[iTabParam].m_dib->height();
         return true;
      }
      else if(eelement == element_text)
      {
         if(!get_element_rect(iTabParam, lprect, element_client))
            return false;
         if(get_data()->m_panea[iTabParam].m_dib.is_set())
         {
            lprect->left += get_data()->m_panea[iTabParam].m_dib->width() + 2;
         }
         if(!get_data()->m_panea[iTabParam].m_bPermanent)
         {
            lprect->right -= 2 + 16 + 2;
         }
         deflate(lprect, get_data()->m_rectTextMargin);
         return true;
      }
      else if(eelement == element_close_tab_button)
      {
         if(get_data()->m_panea[iTabParam].m_bPermanent)
            return false;
         if(get_data()->get_visible_tab_count() <= 1 && !get_data()->m_bEnableCloseAll)
            return false;
         if(!get_element_rect(iTabParam, lprect, element_client))
            return false;
         lprect->right  = lprect->right;
         lprect->left   = lprect->right - 20;
         lprect->top    = lprect->bottom - 20;
         return true;
      }
      
      if(eelement != element_tab)
         return false;

      if(get_data()->m_bVertical)
      {
         ASSERT(iTabParam >= 0);
         ASSERT(iTabParam < GetTabCount());
         ::ca::graphics * pdc = m_pguie->GetDC();
         rect rect = get_data()->m_rectTab;
         rect.bottom = rect.top;

         int iPreviousVisibleTabCount = 0;
         {
            int iPane = iTabParam;
            for(int i = 0; iPane > 0 && i < get_data()->m_panea.get_count(); i++)
            {
               if(get_data()->m_panea[i].m_bVisible)
               {
                 iPane--;
                  iPreviousVisibleTabCount++;
               }
            }
         }

         lprect->left   = rect.left;
         lprect->top    = rect.top + iPreviousVisibleTabCount * get_data()->m_iTabHeight;
         lprect->right  = rect.right;
         lprect->bottom = lprect->top + get_data()->m_iTabHeight;
         m_pguie->ReleaseDC(pdc);
      }
      else
      {
         ASSERT(iTabParam >= 0);
         ASSERT(iTabParam < GetTabCount());
         ::ca::graphics_sp graphics(get_app());
         graphics->CreateCompatibleDC(NULL);
         ::ca::graphics * pdc = graphics;
         rect rect = get_data()->m_rectTab;
         rect.right = rect.left;
         int ixAdd;
         for(int iPane = 0; iPane < iTabParam + 1; iPane++)
         {
            rect.left = rect.right;
            pane & pane = get_data()->m_panea[iPane];
            if(!pane.m_bVisible)
               continue;
            string str;
            pane.get_title(get_app(), str);
            size size;

            ixAdd = 0;
            if(pane.m_dib.is_set())
            {
               //IMAGEINFO ii;
               ixAdd += pane.m_dib->width() + 2;
            }

            if(!pane.m_bPermanent)
            {
               ixAdd += 2 + 16 + 2;
            }

            if(get_data()->m_iaSel.contains(iPane))
            {
               pdc->SelectObject(get_data()->m_fontBold);
            }
            else
            {
               pdc->SelectObject(get_data()->m_font);
            }
            m_dcextension.GetTextExtent(
               pdc,
               str,
               size);
            rect.right = rect.left + ixAdd + size.cx +
               get_data()->m_rectBorder.left + get_data()->m_rectBorder.right +
               get_data()->m_rectMargin.left + get_data()->m_rectMargin.right +
               get_data()->m_rectTextMargin.left + get_data()->m_rectTextMargin.right;

         }
         *lprect = rect;
      }
      return true;
   }

   INT_PTR tab::GetTabCount()
   {
      return get_data()->m_panea.get_size();
   }

   int tab::hit_test(point pt, e_element & eelement)
   {
      rect rect;
      for(int iPane = 0; iPane < get_data()->m_panea.get_size(); iPane++)
      {
         if(get_element_rect(iPane, rect, element_close_tab_button) && rect.contains(pt))
         {
            eelement = element_close_tab_button;
            return iPane;
         }
         if(get_element_rect(iPane, rect, element_tab) && rect.contains(pt))
         {
            eelement = element_tab;
            return iPane;
         }
      }
      return -1;
   }

   ::ca::window * tab::GetNotifyWnd()
   {
      ::ca::window * pwnd;
   //   if((pwnd = m_pguie->GetOwner()) != NULL)
     //    return pwnd;
      if((pwnd = m_pguie->GetParent()->get_wnd()) != NULL)
         return pwnd;
      return NULL;
   }

   /*
   bool tab::create(::user::interaction * pinterface, UINT uiId)
   {
      if(!m_pguie->create(
         pinterface,
         uiId))
         return false;
      m_bCreated = true;
      layout();
      return true;
   }
   */

   void tab::_001OnCreate(gen::signal_object * pobj)
   {
      SCAST_PTR(::user::win::message::base, pbase, pobj);
      if(pobj->previous())
         return;
   //  m_pimagelist = new image_list(get_app());
      get_data()->m_bCreated = true;
      pbase->set_lresult(0);
      PostMessage(WM_USER + 1342);
   }

   void tab::_011OnCreate(gen::signal_object * pobj)
   {
  UNREFERENCED_PARAMETER(pobj);
//      SCAST_PTR(::user::win::message::base, pbase, pobj);

      keeper < bool > keepRestoringTabs(&m_bRestoringTabs, true, false, true);
      if(get_data()->m_matchanyRestore.get_count() > 0)
      {
         var_array vara;
         if(data_get("restore_tab", "", vara))
         {
            open_tabs(vara);
         }
      }

   }

   void tab::install_message_handling(::user::win::message::dispatch *pinterface)
   {
      ::user::window_interface::install_message_handling(pinterface);
      IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN , pinterface, this, &tab::_001OnLButtonDown);
      IGUI_WIN_MSG_LINK(WM_LBUTTONUP   , pinterface, this, &tab::_001OnLButtonUp);
      IGUI_WIN_MSG_LINK(WM_MOUSEMOVE   , pinterface, this, &tab::_001OnMouseMove);
      IGUI_WIN_MSG_LINK(WM_MOUSELEAVE  , pinterface, this, &tab::_001OnMouseLeave);
      IGUI_WIN_MSG_LINK(WM_CREATE      , pinterface, this, &tab::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_USER + 1342 , pinterface, this, &tab::_011OnCreate);
      IGUI_WIN_MSG_LINK(gen::application::APPM_LANGUAGE, pinterface, this, &tab::_001OnAppLanguage);
      IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &tab::_001OnTimer);
   }

   void tab::_001SetSel(int iSel)
   {
      ::ca::data::writing writing(get_data());
      get_data()->m_iaSel.remove_all();
      get_data()->m_iaSel.add(iSel);
      on_change_pane_count();
      on_show_view();
   }

   void tab::_001AddSel(int iSel)
   {
      ::ca::data::writing writing(get_data());
      get_data()->m_iaSel.add(iSel);
      on_change_pane_count();
   }

   tab::pane::pane()
   {
      m_bVisible     = true;
      m_bPermanent   = false;
      m_pholder      = NULL;
   }

   bool tab::pane::get_title(::ca::application * papp, string &str)
   {
    //  if(!m_strTitleEx.is_empty())
      //{
      try
      {
         str = App(papp).load_string(m_strTitleEx);
      }
      catch(...)
      {
         try
         {
            str.Empty();
         }
         catch(...)
         {

         }
      }
      //}
      //else
      //{
        // return str.load_string(m_uiId) != 0;
      //}
      return true;
   }


   tab::pane * tab::pane_array::get_by_id(id id)
   {
      for(int i = 0; i < this->get_count(); i++)
      {
         if(this->element_at(i).m_id == id)
         {
            return ptr_at(i);
         }
      }
      return NULL;
   }

   count tab::pane_array::get_visible_count()
   {
      
      count count = 0;

      for(int i = 0; i < this->get_count(); i++)
      {
         if(this->element_at(i).m_bVisible)
         {
            count++;
         }
      }

      return count;
   }

   void tab::_001OnAppLanguage(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      layout();
   }



   void tab::_001SetTabCallback(tab_callback * pcallback)
   {
      if(get_data()->m_pcallback != NULL)
      {
         delete get_data()->m_pcallback;
      }
      get_data()->m_pcallback = pcallback;;

   }

   int tab::_001GetSel()
   {
      if(get_data()->m_iaSel.get_size() == 1)
      {
         return get_data()->m_iaSel[0];
      }
      else
      {
         return -1;
      }
   }

   int tab::_001GetPaneCount()
   {
      return get_data()->m_panea.get_count();
   }


   bool tab::_001IsAddTab(int iPane)
   {
      if(get_data()->m_pcallback != NULL)
      {
         return get_data()->m_pcallback->_001IsAddTab(iPane);
      }
      else
      {
         return false;
      }
   }

   void tab::_001OnTabClick(int iPane)
   {
      if(get_data()->m_pcallback != NULL)
      {
         get_data()->m_pcallback->_001OnTabClick(iPane);
      }
      else
      {
         _001SelectTab(iPane);
      }
   }

   void tab::_001OnTabClose(int iPane)
   {
      if(get_data()->m_pcallback != NULL)
      {
         get_data()->m_pcallback->_001OnTabClose(iPane);
      }
      else
      {
         _001CloseTab(iPane);
      }
   }

   bool tab::show_tab_by_id(id id, bool bShow)
   {
      pane * ppane = get_pane_by_id(id);
      if(ppane == NULL)
         return false;

      ppane->m_bVisible = bShow;

      layout();
      return true;
   }

   bool tab::show_tab(int iTab, bool bShow)
   {
      pane * ppane = get_pane(iTab, !bShow);
      if(ppane == NULL)
         return !bShow;

      ppane->m_bVisible = bShow;

      layout();

      return bShow;
   }


   ::user::interaction * tab::get_tab_window(int iPane, bool bVisible)
   {
      place_holder * pholder = get_tab_holder(iPane, bVisible);
      if(pholder == NULL)
         return NULL;
      return pholder->get_ui();
   }

   ::user::place_holder * tab::get_tab_holder(int iPane, bool bVisible)
   {
      pane * ppane = get_pane(iPane, bVisible);
      if(ppane == NULL)
         return NULL;
      return ppane->m_pholder;
   }

   tab::pane * tab::get_pane(int iPane, bool bVisible)
   {
      if(iPane < 0 || iPane >= get_data()->m_panea.get_count())
         return NULL;
      if(bVisible)
      {
         for(int i = 0; iPane >= 0 && i < get_data()->m_panea.get_count(); i++)
         {
            if(get_data()->m_panea[i].m_bVisible)
            {
               if(iPane <= 0)
               {
                  return get_data()->m_panea.ptr_at(i);
               }
               else
               {
                  iPane--;
               }
            }
         }
         return NULL;
      }
      else
      {
         return get_data()->m_panea.ptr_at(iPane);
      }
   }


   void tab::_001SelectTab(int iPane)
   {
      if(get_tab_holder(_001GetSel()) != NULL)
      {
         get_tab_holder(_001GetSel())->ShowWindow(SW_HIDE);
      }
      _001SetSel(iPane);
      if(get_tab_holder(_001GetSel()) != NULL)
      {
         get_tab_holder(_001GetSel())->ShowWindow(SW_SHOW);
      }
      layout();
   }

   void tab::on_show_view()
   {
      if(get_data()->m_pcallback != NULL && dynamic_cast < ::user::tab * > (get_data()->m_pcallback) != this)
      {
         get_data()->m_pcallback->_001OnShowTab(this);
      }
   }

   void tab:: _001SetVertical(bool bVertical)
   {
      get_data()->m_bVertical = bVertical;

      if(get_data()->m_bVertical)
      {
         get_data()->m_rectMargin.set(2, 3, 1, 0);
         get_data()->m_rectBorder.set(11, 1, 6, 0);
         get_data()->m_rectTextMargin.set(3, 0, 1, 0);

         get_data()->m_iTabHeight += get_data()->m_rectBorder.top + get_data()->m_rectBorder.bottom +
               get_data()->m_rectMargin.top + get_data()->m_rectMargin.bottom;

         get_data()->m_iTabWidth += get_data()->m_rectBorder.left + get_data()->m_rectBorder.right +
               get_data()->m_rectMargin.left + get_data()->m_rectMargin.right;
      }
      else
      {
         get_data()->m_rectMargin.set(3, 2, 0, 1);
         get_data()->m_rectBorder.set(0, 1, 11, 6);
         get_data()->m_rectTextMargin.set(3, 0, 1, 0);

         get_data()->m_iTabHeight += get_data()->m_rectBorder.top + get_data()->m_rectBorder.bottom +
               get_data()->m_rectMargin.top + get_data()->m_rectMargin.bottom;

         get_data()->m_iTabWidth += get_data()->m_rectBorder.left + get_data()->m_rectBorder.right +
               get_data()->m_rectMargin.left + get_data()->m_rectMargin.right;
      }
   }

   void tab::_001ConnectParent(::user::win::message::dispatch * pinterface)
   {
      UNREFERENCED_PARAMETER(pinterface);
   }

   id tab::get_cur_tab_id()
   {
      return get_id_by_tab(_001GetSel());
   }


   int tab::get_tab_by_id(id id)
   {
      for(int i = 0; i < get_data()->m_panea.get_size(); i++)
      {
         if(get_data()->m_panea[i].m_id == id)
            return i;
      }
      return -1;
   }


   id tab::get_id_by_tab(int iPane, bool bVisible)
   {
      if(bVisible)
      {
         for(int i = 0; iPane >= 0 && i < get_data()->m_panea.get_count(); i++)
         {
            if(get_data()->m_panea[i].m_bVisible)
            {
               if(iPane <= 0)
               {
                  return get_data()->m_panea[i].m_id;
               }
               else
               {
                  iPane--;
               }
            }
         }
         return id();
      }
      else
      {
         if(iPane >= 0 && iPane < get_data()->m_panea.get_size())
            return get_data()->m_panea[iPane].m_id;
         else
            return id();
      }
   }

   void tab::set_cur_tab_by_id(id id)
   {
      int iPane = get_tab_by_id(id);
      if(iPane == -1)
      {
         add_tab("", id);
         iPane = get_tab_by_id(id);
         if(iPane == -1)
            return;
      }
      _001SetSel(iPane);
   }



   e_position tab::DragHitTest(point pt)
   {
      rect rect;
      GetDragRect(rect, position_top);
      if(rect.contains(pt))
      {
         return position_top;
      }
      GetDragRect(rect, position_bottom);
      if(rect.contains(pt))
      {
         return position_bottom;
      }
      GetDragRect(rect, position_left);
      if(rect.contains(pt))
      {
         return position_left;
      }
      GetDragRect(rect, position_right);
      if(rect.contains(pt))
      {
         return position_right;
      }
      return position_none;
   }

   void tab::GetDragRect(LPRECT lprect, e_position eposition)
   {
      switch(eposition)
      {
      case position_top:
         {
            lprect->top = get_data()->m_rectTabClient.top;
            lprect->left = get_data()->m_rectTabClient.left + get_data()->m_rectTabClient.width() / 3;
            lprect->right = lprect->left + get_data()->m_rectTabClient.width() / 3;
            lprect->bottom = lprect->top + get_data()->m_rectTabClient.height() / 3;
         }
         break;
      case position_left:
         {
            lprect->top = get_data()->m_rectTabClient.top + get_data()->m_rectTabClient.height() / 3;
            lprect->left = get_data()->m_rectTabClient.left;
            lprect->right = lprect->left + get_data()->m_rectTabClient.width() / 3;
            lprect->bottom = lprect->top + get_data()->m_rectTabClient.height() / 3;
         }
         break;
      case position_right:
         {
            lprect->top = get_data()->m_rectTabClient.top + get_data()->m_rectTabClient.height() / 3;
            lprect->left = get_data()->m_rectTabClient.left + get_data()->m_rectTabClient.width() * 2 / 3;
            lprect->right = lprect->left + get_data()->m_rectTabClient.width() / 3;
            lprect->bottom = lprect->top + get_data()->m_rectTabClient.height() / 3;
         }
         break;
      case position_bottom:
         {
            lprect->top = get_data()->m_rectTabClient.top + get_data()->m_rectTabClient.height() * 2 / 3;
            lprect->left = get_data()->m_rectTabClient.left + get_data()->m_rectTabClient.width() / 3;
            lprect->right = lprect->left + get_data()->m_rectTabClient.width() / 3;
            lprect->bottom = lprect->top + get_data()->m_rectTabClient.height() / 3;
         }
         break;
      }
   }



   void tab::_001OnDropTab(int iPane, e_position eposition)
   {
      if(get_data()->m_pcallback != NULL)
      {
         get_data()->m_pcallback->_001OnDropTab(iPane, eposition);
      }
   }


   ::user::interaction * tab::get_view_uie()
   {
      return NULL;
   }


   id tab::get_current_id()
   {
      return get_cur_tab_id();
   }

   void tab::_001OnTimer(gen::signal_object * pobj)
   {
      SCAST_PTR(::user::win::message::timer, ptimer, pobj);
      if(ptimer->m_nIDEvent == 5432187)
      {
         get_data()->m_bDrag = true;
         if(get_data()->m_pcallback != NULL)
         {
            get_data()->m_pcallback->_001DropTargetWindowInitialize(this);
         }
         KillTimer(5432187);
      }
   }

   void tab::_000OnMouse(::user::win::message::mouse * pmouse)
   {
      if(m_bShowTabs)
      {
         // these try catchs are needed for multi threading supporting: multi threaded windows: an endeavour
         // Now I understand why Microsoft (TM) Windows (R) windows are single threaded.
         // to debug, enable catch exceptions in debugger
         try
         {
            (m_pimpl->*m_pimpl->m_pfnDispatchWindowProc)(dynamic_cast < gen::signal_object * > (pmouse));
            if(pmouse->get_lresult() != 0)
               return;
         }
         catch(...)
         {
         }
      }
      else if(pmouse->m_uiMessage == WM_MOUSEMOVE)
      {
         try
         {
            rect rectWindow;

            GetWindowRect(rectWindow);

            if(pmouse->m_pt.y <= rectWindow.top)
            {
               if(GetParentFrame()->IsFullScreen())
               {
                  m_bShowTabs = true;
               }
            }
         }
         catch(...)
         {
         }
      }
      user::interaction * pui = get_top_child();
//      int iSize;
      try
      {
         while(pui != NULL)
         {
            try
            {
               if(pui->IsWindowVisible() && pui->_001IsPointInside(pmouse->m_pt))
               {
                  try
                  {
                     pui->_000OnMouse(pmouse);
                     if(pmouse->m_bRet)
                        return;
                  }
                  catch(...)
                  {
                  }
               }
               pui = pui->under_sibling();
            }
            catch(...)
            {
            }
         }
      }
      catch(...)
      {
      }
   }

   tab::data * tab::get_data()
   {
      return dynamic_cast < data * > (m_spdata.m_p);
   }

   tab::pane * tab::get_pane_by_id(id id)
   {
      return get_data()->get_pane_by_id(id);
   }

   tab::pane * tab::ensure_pane_by_id(id id)
   {
      ensure_tab_by_id(id);
      return get_data()->get_pane_by_id(id);
   }

   void tab::ensure_tab_by_id(id id)
   {
      UNREFERENCED_PARAMETER(id);
      throw not_implemented_exception();
   }

   void tab::on_change_pane_count()
   {
      if(m_bRestoringTabs)
         return;

      if(get_data()->m_matchanyRestore.get_count() > 0)
      {
         var_array vara;
         get_restore_tab(vara);
         data_set("restore_tab", "", vara);
      }
   }

   void tab::get_text_id(stringa & stra)
   {
      get_presuffixed_ci_id(stra, NULL, NULL);
   }

   void tab::get_prefixed_ci_id(stringa & stra, const char * pszPrefix)
   {
      get_presuffixed_ci_id(stra, pszPrefix, NULL);
   }

   void tab::get_suffixed_ci_id(stringa & stra, const char * pszSuffix)
   {
      get_presuffixed_ci_id(stra, NULL, pszSuffix);
   }

   void tab::get_presuffixed_ci_id(stringa & stra, const char * pszPrefix, const char * pszSuffix)
   {
      string strPrefix(pszPrefix);
      string strSuffix(pszSuffix);
      string strPath;
      pane_array & panea = get_data()->m_panea;
      for(int i = 0; i < panea.get_count(); i++)
      {
         pane & pane = panea[i];
         if(pane.m_id.is_text())
         {
            strPath = pane.m_id;
            if(strPrefix.is_empty() || gen::str::begins_ci(strPath, strPrefix))
            {
               if(strSuffix.is_empty() || gen::str::ends_ci(strPath, strSuffix))
               {
                  stra.add(strPath);
               }
            }
         }
      }
   }

   void tab::get_begins_ci_eat_id(stringa & stra, const char * pszPrefix)
   {
      get_begins_ends_ci_eat_id(stra, pszPrefix, NULL);
   }

   void tab::get_ends_ci_eat_id(stringa & stra, const char * pszSuffix)
   {
      get_begins_ends_ci_eat_id(stra, NULL, pszSuffix);
   }

   void tab::get_begins_ends_ci_eat_id(stringa & stra, const char * pszPrefix, const char * pszSuffix)
   {
      string strPrefix(pszPrefix);
      string strSuffix(pszSuffix);
      string strPath;
      pane_array & panea = get_data()->m_panea;
      for(int i = 0; i < panea.get_count(); i++)
      {
         pane & pane = panea[i];
         if(pane.m_id.is_text())
         {
            strPath = pane.m_id;
            if(strPrefix.is_empty() || gen::str::begins_ci(strPath, strPrefix))
            {
               if(strSuffix.is_empty() || gen::str::ends_ci(strPath, strSuffix))
               {
                  stra.add(strPath);
               }
            }
         }
      }
   }

   void tab::get_restore_tab(var_array & vara)
   {
      ::ex1::match::any  & matchany = get_data()->m_matchanyRestore;
      if(matchany.get_count() == 0)
         return;
      var varId;
      pane_array & panea = get_data()->m_panea;
      for(int i = 0; i < panea.get_count(); i++)
      {
         varId = panea[i].m_id;
         if(matchany.matches(varId))
         {
            vara.add(varId);
         }
      }
   }

   bool tab::has_restore_tab()
   {
      ::ex1::match::any  & matchany = get_data()->m_matchanyRestore;
      if(matchany.get_count() == 0)
         return false;
      var varId;
      pane_array & panea = get_data()->m_panea;
      for(int i = 0; i < panea.get_count(); i++)
      {
         varId = panea[i].m_id;
         if(matchany.matches(varId))
         {
            return true;
         }
      }
      return false;
   }

   void tab::open_tabs(const var_array & vara)
   {
      for(int i = 0; i < vara.get_count(); i++)
      {
         // ODOW : TODO : should create bergedgewrapper to open bergedge inside a window.
         if(vara[i].get_type() == var::type_string && vara[i].get_string() == "app:bergedge")
            continue;
         if(vara[i].get_type() == var::type_string && vara[i].get_string() == "app:")
            continue;
         ensure_tab_by_id(vara[i]);
      }
   }

   void tab::_001CloseTab(int iTab)
   {
      UNREFERENCED_PARAMETER(iTab);
   }

} // namespace ex1


