#include "StdAfx.h"
#include "FrameSchema.h"

namespace window_frame
{

   FrameSchema::FrameSchema(::ca::application * papp) :
      ca(papp),
      m_fontMarlett(papp),
      m_brushControlBoxBack(papp),
      m_brushControlBoxBackSel(papp),
      m_brushControlBoxBackFocus(papp),
      m_brushControlBoxBackDisabled(papp),
      m_penControlBoxBack(papp),
      m_penControlBoxBackSel(papp),
      m_penControlBoxBackFocus(papp),
      m_penControlBoxBackDisabled(papp),
      m_dibmap(papp),
      m_schema(papp)
   {
      SetControlBoxButtonId(ButtonClose      , "window_frame::ButtonClose");
      SetControlBoxButtonId(ButtonUp         , "window_frame::ButtonUp");
      SetControlBoxButtonId(ButtonDown       , "window_frame::ButtonDown");
      SetControlBoxButtonId(ButtonMinimize   , "window_frame::ButtonMinimize");
      SetControlBoxButtonId(ButtonMaximize   , "window_frame::ButtonMaximize");
      SetControlBoxButtonId(ButtonRestore    , "window_frame::ButtonRestore");
      SetControlBoxButtonId(ButtonNotifyIcon , "window_frame::ButtonNotifyIcon");
   }

   FrameSchema::~FrameSchema()
   {

   }

   EHitTest FrameSchema::_000HitTest(point pt)
   {
      UNREFERENCED_PARAMETER(pt);
      return HitTestClient;
   }

   bool FrameSchema::_000OnLButtonDown(::user::win::message::mouse * pmouse)
   {
      if(m_pworkset->GetSizingManager()->_000OnLButtonDown(pmouse))
         return true;
      
      if(m_pworkset->GetMovingManager()->_000OnLButtonDown(pmouse))
         return true;

      return false;
   }

   bool FrameSchema::_000OnLButtonUp(::user::win::message::mouse * pmouse)
   {
      if(m_pworkset->GetSizingManager()->_000OnLButtonUp(pmouse))
         return true;
      
      if(m_pworkset->GetMovingManager()->_000OnLButtonUp(pmouse))
         return true;

      return false;
   }

   bool FrameSchema::_000OnMouseMove(::user::win::message::mouse * pmouse)
   {
      if(m_pworkset->GetSizingManager()->_000OnMouseMove(pmouse))
         return true;
      
      if(m_pworkset->GetMovingManager()->_000OnMouseMove(pmouse))
         return true;

      return false;
   }

   bool FrameSchema::_000OnNcLButtonDown(::user::win::message::mouse * pmouse)
   {
      if(m_pworkset->GetSizingManager()->_000OnLButtonDown(pmouse))
         return true;
      
      if(m_pworkset->GetMovingManager()->_000OnLButtonDown(pmouse))
         return true;

      return false;
   }

   bool FrameSchema::_000OnNcLButtonUp(::user::win::message::mouse * pmouse)
   {
      if(m_pworkset->GetSizingManager()->Relay(pmouse))
         return true;
      
      if(m_pworkset->GetMovingManager()->Relay(pmouse))
         return true;

      return false;
   }

   bool FrameSchema::_000OnNcMouseMove(::user::win::message::mouse * pmouse)
   {
      if(m_pworkset->GetSizingManager()->Relay(pmouse))
         return true;
      
      if(m_pworkset->GetMovingManager()->Relay(pmouse))
         return true;

      return false;
   }

   bool FrameSchema::_000OnNcHitTest(point pt, LRESULT & nHitTest)
   {
      UNREFERENCED_PARAMETER(pt);
      UNREFERENCED_PARAMETER(nHitTest);
      return false;
   }

   bool FrameSchema::_000OnTimer(UINT nIDEvent)
   {
      UNREFERENCED_PARAMETER(nIDEvent);
      return false;
   }

   bool FrameSchema::_000OnSize(UINT nType, int cx, int cy)
   {
      UNREFERENCED_PARAMETER(nType);
      UNREFERENCED_PARAMETER(cx);
      UNREFERENCED_PARAMETER(cy);
      return false;
   }

   bool FrameSchema::_000OnMove(int x, int y)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      return false;
   }

   bool FrameSchema::_000OnCommand(WPARAM wparam, LPARAM lparam, LRESULT & lresult)
   {
      UNREFERENCED_PARAMETER(wparam);
      UNREFERENCED_PARAMETER(lparam);
      UNREFERENCED_PARAMETER(lresult);
      return false;
   }

   bool FrameSchema::_000OnDisplayChange(int iBitsPerPixel, size sizeScreen)
   {
      UNREFERENCED_PARAMETER(iBitsPerPixel);
      UNREFERENCED_PARAMETER(sizeScreen);
      return false;
   }

   void FrameSchema::_001OnDraw(::ca::graphics * pdc)
   {
      UNREFERENCED_PARAMETER(pdc);
   }

   void FrameSchema::OnInitializeAppearance()
   {
   }

   void FrameSchema::OnNcCalcSize(LPRECT lprect)
   {
      UNREFERENCED_PARAMETER(lprect);
   }

   void FrameSchema::OnAppearanceModeChange()
   {
   }

   appearance * FrameSchema::GetAppearance()
   {
      ASSERT(m_pworkset != NULL);
      return m_pworkset->GetAppearance();
   }

   void FrameSchema::GetWndClientRect(LPRECT lprect)
   {
      UNREFERENCED_PARAMETER(lprect);
   }

   size FrameSchema::GetMinSize()
   {
      return size(184 + 177, 184 + 177);
   }

   void FrameSchema::OnActivate()
   {

   }

   void FrameSchema::layout()
   {

   }

   void FrameSchema::_000OnBeforeMove(LPCRECT lpcrect)
   {
      UNREFERENCED_PARAMETER(lpcrect);
   }

   void FrameSchema::_000OnBeforeSize(LPCRECT lpcrect)
   {
      UNREFERENCED_PARAMETER(lpcrect);
   }

   void FrameSchema::OnAttach()
   {

   }


   void FrameSchema::SetControlBoxButtonId(EButton ebutton, id id)
   {
      m_mapButtonId[ebutton] = id;
      m_mapIdButton[id] = ebutton;
   }

   id FrameSchema::GetControlId(EButton ebutton)
   {
      return m_mapButtonId[ebutton];
   }

   FrameSchema::EButton FrameSchema::GetButtonId(id id)
   {
      return m_mapIdButton[id];
   }

   void FrameSchema::Glass(::ca::graphics * pdc, LPRECT lprect)
   {
      ::user::interaction * pwndiDraw = m_pworkset->GetDrawWindow();
      class imaging & imaging = System.imaging();
      class rect rectClient(lprect);
      class rect rectInflate;


      int iInflate = 5; // raio 2 pixels + centro 1 pixel

      rectInflate = rectClient;
      rectInflate.inflate(iInflate, iInflate);

      ::user::interaction * pwndDesktop = System.get_desktop_window();
      HDC hdcScreen = ::GetDC(NULL);
      class rect rectDesktop;
      pwndDesktop->GetWindowRect(rectDesktop);
      if(rectDesktop.width() < 800)
      {
         rectDesktop.left = 0;
         rectDesktop.right = ::GetSystemMetrics(SM_CXSCREEN);
      }
      if(rectDesktop.height() < 600)
      {
         rectDesktop.top = 0;
         rectDesktop.bottom = ::GetSystemMetrics(SM_CYSCREEN);
      }
      ::ca::dib_sp spdib(get_app());
      ::ca::dib_sp spdib2(get_app());

      spdib->create(rectClient.width()+ iInflate * 2, rectClient.height() + iInflate * 2);
      spdib2->create(rectClient.width() + iInflate * 2, rectClient.height() + iInflate * 2);
      class rect rectWindow = rectClient;
      pwndiDraw->ClientToScreen(rectWindow);
      //spdib->create(rectClient.width(), rectClient.height());
      BOOL b = spdib2->get_graphics()->BitBlt(0, 0, rectClient.width() + iInflate * 2, rectClient.height() + iInflate * 2, pdc, rectClient.left - iInflate, rectClient.top - iInflate, SRCCOPY);
      //BOOL b = ::BitBlt(dc2, 0, 0, rectClient.width() + iInflate * 2, rectClient.height() + iInflate * 2, hdcScreen, rectClient.left - iInflate, rectClient.top - iInflate, SRCCOPY);
      b = imaging.blur(spdib->get_graphics(), point(0, 0), 
         size(rectClient.width() + iInflate * 2, rectClient.height() + iInflate * 2),
         spdib2->get_graphics(), point(0, 0), 2);
      
      //spgraphics->Draw3dRect(rectClient, 127 << 24, 127 << 24);
      //rectClient.deflate(1, 1);
      //spgraphics->Draw3dRect(rectClient, 64 << 24, 64 << 24);
      /*b = imaging.bitmap_blend(pdc, lprect->left, lprect->top, 
         rectWindow.width(),
         rectWindow.height(),
         &spgraphics,
         iInflate, iInflate, 128);*/
      /*BLENDFUNCTION bf;
      bf.AlphaFormat = AC_SRC_ALPHA;
      bf.BlendOp     = AC_SRC_OVER;
      bf.BlendFlags = 0;
      bf.SourceConstantAlpha = 255;
      ::alpha_blend(pdc->get_handle1(),
         lprect->left, lprect->top, 
         rectWindow.width(),
         rectWindow.height(),
         spgraphics->get_handle1(),
         0, 0, 
         rectWindow.width(),
         rectWindow.height(),
         bf);*/
      pdc->BitBlt(rectClient.left, rectClient.top, rectClient.width(), rectClient.height(),
        spdib->get_graphics(), iInflate, iInflate, SRCCOPY);
      b = ::ReleaseDC(NULL, hdcScreen);
   }

   void FrameSchema::ColorGlass(::ca::graphics * pdc, LPRECT lprect, COLORREF cr, BYTE bAlpha)
   {
      System.imaging().color_blend(pdc, lprect, cr, bAlpha, m_dibmap[rect(lprect).size()]);
   }

   void FrameSchema::OnMove(::user::interaction * pwnd)
   {
      UNREFERENCED_PARAMETER(pwnd);
   }

   void FrameSchema::hide_button(EButton ebutton, bool bHide)
   {
      m_buttonmapPresent[ebutton] = !bHide;
   }

   bool FrameSchema::has_button(EButton ebutton)
   {
      bool bPresent;
      if(m_buttonmapPresent.Lookup(ebutton, bPresent))
         return bPresent;
      else
      {
         m_buttonmapPresent[ebutton] = true;
         return true;
      }
   }

   ControlBoxButton * FrameSchema::get_button(EButton ebutton)
   {
      ControlBoxButton * pbutton = NULL;
      m_buttonmap.Lookup(ebutton, pbutton);
      return pbutton;
   }

   bool FrameSchema::create_button(EButton ebutton)
   {
      ::user::interaction * pwnd = m_pworkset->GetDrawWindow();

      ControlBoxButton * pbutton;
      if(!m_buttonmap.Lookup(ebutton, pbutton))
      {
         m_buttonmap.set_at(ebutton, dynamic_cast < ControlBoxButton * > (System.alloc(m_typeinfoControlBoxButton)));
      }
      string strCaption;
      GetControlBoxButtonCaption(ebutton, strCaption);
      id id = GetControlId(ebutton);

      if(m_buttonmap.Lookup(ebutton, pbutton))
      {
         if(!pbutton->IsWindow()
            && !pbutton->create(pwnd, id))
            return false;
         UpdateControlBoxButton(ebutton);
      }
      else
      {
         return false;
      }
      return true;
   }


   bool FrameSchema::GetControlBoxButtonCaption(EButton ebutton, string &strCaption)
   {
      bool bOk = true;
      switch(ebutton)
      {
      case ButtonClose:
         strCaption = (CHAR) 114;
         break;
      case ButtonUp:
         strCaption = (CHAR) 53;
         break;
      case ButtonDown:
         strCaption = (CHAR) 54;
         break;
      case ButtonMinimize:
         strCaption = (CHAR) 48;
         break;
      case ButtonMaximize:
         strCaption = (CHAR) 49;
         break;
      case ButtonRestore:
         strCaption = (CHAR) 50;
         break;
      case ButtonNotifyIcon:
         strCaption = (CHAR) 0x69;
         break;

      default:
         bOk = false;
      }
      return bOk;

   }


   void FrameSchema::UpdateControlBoxButtons()
   {
      POSITION pos = m_buttonmap.get_start_position();
      EButton ebutton;
      ControlBoxButton * pbutton;
      while(pos != NULL)
      {
         m_buttonmap.get_next_assoc(pos, ebutton, pbutton);
         UpdateControlBoxButton(ebutton);
      }
   }

   void FrameSchema::UpdateControlBoxButton(EButton ebutton)
   {
      ControlBoxButton * pbutton;
      if(m_buttonmap.Lookup(ebutton, pbutton))
      {
         string strCaption;
         GetControlBoxButtonCaption(ebutton, strCaption);
         pbutton->SetParent(m_pworkset->GetDrawWindow());
         pbutton->SetWindowText(strCaption);
         pbutton->SetFont(m_fontMarlett);
         pbutton->SetEllipseBrushs(m_brushControlBoxBack, m_brushControlBoxBackSel, m_brushControlBoxBackFocus, m_brushControlBoxBackDisabled);
         pbutton->SetEllipsePens(m_penControlBoxBack, m_penControlBoxBackSel, m_penControlBoxBackFocus, m_penControlBoxBackDisabled);
         pbutton->SetTextColors(m_crControlBoxFore, m_crControlBoxForeSel, m_crControlBoxForeFocus, m_crControlBoxForeDisabled);
      }
   }


   bool FrameSchema::CreateButtons()
   {
      create_button(ButtonClose);
      create_button(ButtonUp);
      create_button(ButtonDown);
      create_button(ButtonMinimize);
      create_button(ButtonMaximize);
      create_button(ButtonRestore);
      create_button(ButtonNotifyIcon);
      return true;
   }


   int FrameSchema::UpdateControlBox()
   {
      return 0;
   }


   COLORREF FrameSchema::get_border_main_body_color()
   {
      return RGB(63, 150, 106);
   }

}











