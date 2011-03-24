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
   }

   tab::data::~data()
   {
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

   bool tab::add_tab(const char * lpcsz, id id)
   {
      
      pane pane;
      pane.m_strTitleEx = lpcsz;
      if(id.is_empty())
         id = get_data()->m_panea.get_size();
      pane.m_id = id;
      pane.m_dib.destroy();
      pane.m_pholder = NULL;
      get_data()->m_panea.add(pane);
      return true;
   }

   bool tab::remove_tab(id id)
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

   bool tab::add_image_tab(const char * lpcszTitle, const char * pszImage, id id)
   {

      pane * ppane = get_data()->m_panea.add_new();

      if(ppane == NULL)
         return false;

      ppane->m_strTitleEx = lpcszTitle;
      if(id.is_empty())
         id = get_data()->m_panea.get_size();
      ppane->m_id = id;
      ppane->m_pholder = NULL;
      ppane->m_dib.create(get_app());
      ppane->m_dib.load_from_file(pszImage);

      return true;
   }

   void tab::RemoveTab(int iPane)
   {
      
      if(iPane < 0 || iPane >= get_data()->m_panea.get_size())
         return;

      get_data()->m_panea.remove_at(iPane);
   }


   void tab::_001OnDraw(::ca::graphics * pdc) 
   {

      if(get_data()->is_in_use())
         return;
      
      pdc->SetBkColor(RGB(255, 255, 255));
      
      class rect rect;
      class rect rectBorder;
      class rect rectText;
      
      HGDIOBJ hOldPen = pdc->SelectObject(get_data()->m_pen);

      class imaging & imaging = System.imaging();

      imaging.color_blend(
         pdc,
         get_data()->m_rectTab,
         RGB(250, 255, 255),
         127);

      for(int iPane = 0; iPane < get_data()->m_panea.get_size(); iPane++)
      {
         pane & pane = get_data()->m_panea[iPane];
         
         GetTabRect(iPane, rect);


         if(get_data()->m_bVertical)
         {
            rectBorder = rect;
            rectBorder.deflate(get_data()->m_rectMargin);

            rectText = rectBorder;
            rectText.deflate(get_data()->m_rectBorder);
            if(pane.m_dib.is_set())
            {
               class rect rectIcon;
               rectIcon = rectText;
               rectIcon.right = rectIcon.left + pane.m_dib->width();
               rectIcon.bottom = rectIcon.top + pane.m_dib->height();
               pane.m_dib->bitmap_blend(pdc, rectIcon);
               rectText.left += pane.m_dib->width() + 2;
            }



            if(get_data()->m_iaSel.contains(iPane))
            {
               pdc->SelectObject(get_data()->m_fontBold);
               pdc->SetTextColor(RGB(0, 0, 0));
               
               pdc->MoveTo(rectBorder.right, rectBorder.bottom);
               pdc->LineTo(rectBorder.left + 1, rectBorder.bottom);
               pdc->LineTo(rectBorder.left, rectBorder.top - (rectBorder.left - rectText.left));
               pdc->LineTo(rectText.left, rectBorder.top);
               pdc->LineTo(rectBorder.right, rectBorder.top);
            }
            else
            {
               pdc->MoveTo(rectBorder.right, rectBorder.bottom);
               pdc->LineTo(rectBorder.left + 1, rectBorder.bottom);
               pdc->LineTo(rectBorder.left, rectBorder.top - (rectBorder.left - rectText.left));
               pdc->LineTo(rectText.left, rectBorder.top);
               pdc->LineTo(rectBorder.right, rectBorder.top);
               pdc->LineTo(rectBorder.right, rectBorder.bottom);
               if(iPane == m_iHover)
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

            rectText.deflate(get_data()->m_rectTextMargin);

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
         else
         {
            rectBorder = rect;
            rectBorder.deflate(get_data()->m_rectMargin);

            rectText = rectBorder;
            rectText.deflate(get_data()->m_rectBorder);
            if(pane.m_dib.is_set())
            {
               class rect rectIcon;
               rectIcon = rectText;
               rectIcon.right = rectIcon.left + pane.m_dib->width();
               rectIcon.bottom = rectIcon.top + pane.m_dib->height();
               pane.m_dib->bitmap_blend(pdc, rectIcon);
               rectText.left += pane.m_dib->width() + 2;
            }



            if(get_data()->m_iaSel.contains(iPane))
            {
               pdc->MoveTo(rectBorder.left, rectText.bottom);
               //pdc->LineTo(rectBorder.left, rectText.bottom);
               pdc->LineTo(rectBorder.left, rectBorder.top);
               pdc->LineTo(rectText.right, rectBorder.top);
               pdc->LineTo(rectBorder.right, rectBorder.top + (rectBorder.right - rectText.right));
               pdc->LineTo(rectBorder.right - 1, rectText.bottom);
               //pdc->LineTo(rect.right, rectText.bottom);
               pdc->SelectObject(get_data()->m_fontBold);
               pdc->SetTextColor(RGB(0, 0, 0));
            }
            else
            {
               //pdc->MoveTo(rect.left, rectBorder.bottom);
               //pdc->LineTo(rect.right, rectBorder.bottom);
               pdc->MoveTo(rectBorder.left, rectText.bottom);
               pdc->LineTo(rectBorder.left, rectBorder.top);
               pdc->LineTo(rectText.right, rectBorder.top);
               pdc->LineTo(rectBorder.right, rectBorder.top + (rectBorder.right - rectText.right));
               pdc->LineTo(rectBorder.right - 1, rectText.bottom);
               pdc->LineTo(rectBorder.left, rectText.bottom);

               if(iPane == m_iHover)
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

            rectText.deflate(get_data()->m_rectTextMargin);

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
         pdc->SelectObject(get_data()->m_font);
         for(int iPane = 0; iPane < get_data()->m_panea.get_size(); iPane++)
         {
            pane & pane = get_data()->m_panea[iPane];
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
         pdc->SelectObject(get_data()->m_font);
         for(int iPane = 0; iPane < get_data()->m_panea.get_size(); iPane++)
         {
            pane & pane = get_data()->m_panea[iPane];
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
            pholder->SetWindowPos(ZORDER_TOP, rectChild.left, rectChild.top,
               rectChild.width(), rectChild.height(), SWP_SHOWWINDOW);
         }
      }

   }

   void tab::_001OnLButtonDown(gen::signal_object * pobj) 
   {
      SCAST_PTR(::user::win::message::mouse, pmouse, pobj);
      class point point = pmouse->m_pt;
      ScreenToClient(&point);

      int iPane = hit_test(point);

      get_data()->m_bDrag = false;
      if(iPane >= 0 && iPane != _001GetSel())
      {
         get_data()->m_iDragTab = iPane;
         SetTimer(5432187, 884, NULL);
         pmouse->m_bRet = true;
         pmouse->set_lresult(1);
      }
   }


   void tab::_001OnLButtonUp(gen::signal_object * pobj) 
   {
      SCAST_PTR(::user::win::message::mouse, pmouse, pobj);
      class point point = pmouse->m_pt;
      ScreenToClient(&point);
      int iPane = hit_test(point);

      KillTimer(5432187);
      if(iPane >= 0 && get_data()->m_iDragTab == iPane)
      {
         _001OnTabClick(iPane);
         pmouse->m_bRet = true;
         pmouse->set_lresult(1);
      }
      else if(get_data()->m_bDrag && get_data()->m_iDragTab >= 0)
      {
         e_position eposition = DragHitTest(point);
         if(eposition != position_none)
         {
            _001OnDropTab(get_data()->m_iDragTab, eposition);
         }
         if(get_data()->m_pcallback != NULL)
         {
            get_data()->m_pcallback->_001DropTargetWindowFinalize(this);         
         }
         get_data()->m_iDragTab = -1;
         System.release_capture_uie();
      }
      get_data()->m_bDrag = false;
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
      int iHover = hit_test(point);
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

   void tab::GetTabRect(int iTabParam, LPRECT lprect)
   {
      
      if(iTabParam < 0 || iTabParam >= GetTabCount())
         return;
      if(get_data()->m_bVertical)
      {
         ASSERT(iTabParam >= 0);
         ASSERT(iTabParam < GetTabCount());
         ::ca::graphics * pdc = m_pguie->GetDC();
         rect rect = get_data()->m_rectTab;
         rect.bottom = rect.top;
        lprect->left   = rect.left;
         lprect->top    = rect.top + iTabParam * get_data()->m_iTabHeight;
         lprect->right  = rect.right;
         lprect->bottom = lprect->top + get_data()->m_iTabHeight;
   /*      for(int iPane = 0; iPane < iTabParam + 1; iPane++)
         {
            rect.top = rect.bottom;
            pane & pane = get_data()->m_panea[iPane];
            string str;
            pane.get_title(str);
            size size;

            iyAdd = 0;
            if(pane.m_iImage >= 0)
            {
               IMAGEINFO ii;
               m_imagelist.get_image_info(pane.m_iImage, &ii);
               iyAdd += ii.rcImage.bottom - ii.rcImage.top + 2;
            }

            if(m_iaSel.contains(iPane))
            {
               pdc->SelectObject(m_fontBold);
            }
            else
            {
               pdc->SelectObject(m_font);
            }
            ::GetTextExtentPoint32W(
               (HDC)pdc->get_os_data(),
               str,
               str.get_length(),
               &size);
            rect.bottom = rect.top + iyAdd + size.cy + 
               m_rectBorder.top + m_rectBorder.bottom +
               m_rectMargin.top + m_rectMargin.bottom +
               m_rectTextMargin.top + m_rectTextMargin.bottom;

         }*/
         //*lprect = rect;
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
            string str;
            pane.get_title(get_app(), str);
            size size;

            ixAdd = 0;
            if(pane.m_dib.is_set())
            {
               //IMAGEINFO ii;
               ixAdd += pane.m_dib->width() + 2;
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
         //ReleaseDC(pdc);
      }
   }

   INT_PTR tab::GetTabCount()
   {
      return get_data()->m_panea.get_size();
   }

   int tab::hit_test(point pt)
   {
      rect rect;
      for(int iPane = 0; iPane < get_data()->m_panea.get_size(); iPane++)
      {
         GetTabRect(iPane, rect);
         if(rect.contains(pt))
         {
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
   }

   void tab::_001InstallMessageHandling(::user::win::message::dispatch *pinterface)
   {
      ::user::window_interface::_001InstallMessageHandling(pinterface);
      IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN , pinterface, this, &tab::_001OnLButtonDown);
      IGUI_WIN_MSG_LINK(WM_LBUTTONUP   , pinterface, this, &tab::_001OnLButtonUp);
      IGUI_WIN_MSG_LINK(WM_MOUSEMOVE   , pinterface, this, &tab::_001OnMouseMove);
      IGUI_WIN_MSG_LINK(WM_MOUSELEAVE  , pinterface, this, &tab::_001OnMouseLeave);
      IGUI_WIN_MSG_LINK(WM_CREATE      , pinterface, this, &tab::_001OnCreate);
      IGUI_WIN_MSG_LINK(gen::application::APPM_LANGUAGE, pinterface, this, &tab::_001OnAppLanguage);
      IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &tab::_001OnTimer);
   }

   void tab::_001SetSel(int iSel)
   {
      ::ca::data::writing writing(get_data());
      get_data()->m_iaSel.remove_all();
      get_data()->m_iaSel.add(iSel);
      on_show_view();
   }

   void tab::_001AddSel(int iSel)
   {
      ::ca::data::writing writing(get_data());
      get_data()->m_iaSel.add(iSel);
   }

   bool tab::pane::get_title(::ca::application * papp, string &str)
   {
    //  if(!m_strTitleEx.is_empty())
      //{
      str = App(papp).load_string(m_strTitleEx);
      //}
      //else
      //{
        // return str.load_string(m_uiId) != 0;
      //}
      return true;
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


   ::user::interaction * tab::get_tab_window(int iPane)
   {
      place_holder * pholder = get_tab_holder(iPane);
      if(pholder == NULL)
         return NULL;
      return pholder->get_ui();
   }

   place_holder * tab::get_tab_holder(int iPane)
   {
      if(iPane < 0 || iPane >= get_data()->m_panea.get_count())
         return NULL;
      return get_data()->m_panea[iPane].m_pholder;
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
         get_data()->m_pcallback->on_show_view(this);
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


   id tab::get_id_by_tab(int iPane)
   {
      if(iPane >= 0 && iPane < get_data()->m_panea.get_size())
         return get_data()->m_panea[iPane].m_id;
      else 
         return id();
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
         GetParent()->set_capture();
         if(get_data()->m_pcallback != NULL)
         {
            get_data()->m_pcallback->_001DropTargetWindowInitialize(this);         
         }
         KillTimer(5432187);
      }
   }

   void tab::_000OnMouse(::user::win::message::mouse * pmouse)
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
      user::interaction * pui = get_top_child();
      int iSize;
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

} // namespace ex1