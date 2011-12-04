#include "StdAfx.h"


/////////////////////////////////////////////////////////////////////////////
// mirroring support

//WINBUG: some mirroring stuff will be in wingdi.h someday
#ifndef LAYOUT_RTL
#define LAYOUT_LTR                               0x00000000
#define LAYOUT_RTL                         0x00000001
#define NOMIRRORBITMAP                     0x80000000
#endif

//WINBUG: some mirroring stuff will be in winuser.h someday
#ifndef WS_EX_LAYOUTRTL
#define WS_EX_LAYOUTRTL                    0x00400000L
#endif

namespace user
{

   window_interface * window_interface::g_pwndLastLButtonDown = NULL;



   window_interface::window_interface() :
      m_rectParentClient(0, 0, 0, 0)
   {
      m_bVoidPaint               = false;
      m_pguie                    = NULL;
      m_etranslucency            = TranslucencyNone;
      m_bBackgroundBypass        = false;
   }

   window_interface::window_interface(::ca::application * papp) :
      ca(papp),
      command_target_interface(papp),
      m_rectParentClient(0, 0, 0, 0)
   {
      m_bVoidPaint               = false;
      m_pguie                    = NULL;
      m_etranslucency            = TranslucencyNone;
      m_bBackgroundBypass        = false;
   }


   window_interface::~window_interface()
   {
   }

   void window_interface::install_message_handling(gen::message::dispatch * pinterface)
   {
      gen::message::dispatch::install_message_handling(pinterface);

      IGUI_WIN_MSG_LINK(
         MessageBaseWndGetProperty,
         pinterface,
         this,
         &window_interface::_001OnBaseWndGetProperty);

      IGUI_WIN_MSG_LINK(
         WM_CREATE,
         pinterface,
         this,
         &window_interface::_001OnCreate);

      IGUI_WIN_MSG_LINK(
         MessageProperty,
         pinterface,
         this,
         &window_interface::_001OnBaseWndGetProperty);
   }

   // draw the background of a ::ca::window
   // can be used for trasparency
   // the rectangle must be in client coordinates.
   void window_interface::_001DrawBackground(::ca::graphics *pdc, LPRECT lprect)
   {
      UNREFERENCED_PARAMETER(pdc);
      UNREFERENCED_PARAMETER(lprect);
   //   TwfRender(pdc, GetSafeHwnd(), lprect, NULL, true);
   }


   /*bool window_interface::TwfRender(
      ::ca::graphics *          pdc,
      HWND           hwndExclude,
      LPCRECT        lpcrectUpdate,
      user::HwndTree::Array & hwndtreea,
      bool           bBackground)
   {
      rect rectUpdate(*lpcrectUpdate);

      rect rectChild;

      rect rectNewUpdate;

      for(int i = hwndtreea.get_size() - 1; i >= 0; i--)
      {
         user::HwndTree & hwndtreeChild = hwndtreea[i];
         HWND hwndChild = hwndtreeChild.m_hwnd;
         if(hwndChild == hwndExclude)
         {
            if(bBackground)
               return false;
            else
               continue;
         }
         ::ca::window * pwndChild = ::ca::window::from_handle(hwndChild);
         HWND hwndParent = ::GetParent(hwndChild);
         ::GetClientRect(hwndChild, rectChild);
         ::ClientToScreen(hwndChild, &rectChild.top_left());
         ::ClientToScreen(hwndChild, &rectChild.bottom_right());
         if(rectNewUpdate.intersect(rectChild, rectUpdate))
         {
            if(!TwfRender(pdc, hwndExclude, rectNewUpdate, hwndtreeChild, bBackground))
               return false;
         }
       }
       return true;
   }


   bool window_interface::TwfRender(
      ::ca::graphics *          pdc,
      HWND           hwndExclude,
      LPCRECT        lpcrectUpdate,
      user::HwndTree & hwndtree,
      bool           bBackground)
   {

      rect rectUpdate(*lpcrectUpdate);

      DWORD dwTimeIn = GetTickCount();

      HWND hwndParam = hwndtree.m_hwnd;

      if(hwndParam == NULL)
      {
         return false;
      }

      if(hwndParam == hwndExclude)
      {
         if(bBackground)
            return false;
         else
            return true;
      }

      if(!::IsWindow(hwndParam))
      {
         return false;
      }

      if(!::IsWindowVisible(hwndParam))
      {
         return false;
      }


      ::ca::window * pwnd = ::ca::window::FromHandlePermanent(hwndParam);

      if((::GetWindowLong((hwndParam), GWL_STYLE) & WS_VISIBLE) == 0)
      {
         return true;
      }




      window_interface * pwndi = dynamic_cast<window_interface *>(pwnd);
      if(pwndi == NULL)
      {
         single_lock sl(m_papp->s_ptwf->m_csWndInterfaceMap, TRUE);
         if(m_papp->s_ptwf->m_wndinterfacemap.Lookup(hwndParam, pwndi))
         {
            if(pwndi != NULL)
            {
               pwnd = pwndi->get_guie();
            }
         }
         else
         {
            m_papp->s_ptwf->m_wndinterfacemap.set_at(hwndParam, pwndi);
            ::SendMessage(
               hwndParam,
               window_interface::MessageBaseWndGetProperty,
               window_interface::PropertyDrawBaseWndInterface,
               (LPARAM) &pwndi);
         }
         sl.unlock();
      }

   //   if(pwndi == this)
     //    return true;

      rect rectWindow;
      ::GetClientRect(hwndParam, rectWindow);
      ::ClientToScreen(hwndParam, &rectWindow.top_left());
      ::ClientToScreen(hwndParam, &rectWindow.bottom_right());
      ::ScreenToClient(GetSafeHwnd(), &rectWindow.top_left());
      ::ScreenToClient(GetSafeHwnd(), &rectWindow.bottom_right());

      pdc->SetViewportOrg(rectWindow.left, rectWindow.top);

      if(pwndi != NULL)
      {
         if(!pwndi->_001IsTransparent())
         {
            if(pwndi != NULL)
            {
               m_papp->s_ptwf->m_twrenderclienttool.FastClear();
               pwndi->TwiRenderClient(m_papp->s_ptwf->m_twrenderclienttool);
               if(m_papp->s_ptwf->m_twrenderclienttool.IsSignalizedRenderResult(
                  user::RenderDoNotProceedWithChildren))
                   return true;
            }
         }
      }
      else
      {
         BOOL bWin4 = FALSE;
      //_AfxFillPSOnStack();
         ::DefWindowProc(
            hwndParam,
            (bWin4 ? WM_PRINT : WM_PAINT),
            (WPARAM)(pdc->m_hDC),
            (LPARAM)(bWin4 ? PRF_CHILDREN | PRF_CLIENT : 0));
         //::RedrawWindow(hwndParam, NULL, rgnClient, RDW_INVALIDATE | RDW_UPDATENOW | RDW_NOCHILDREN);
      }




      DWORD dwTimeOut = GetTickCount();
   //   TRACE("// Average Window Rendering time\n");
   //   TRACE("// Window Class: %s\n", (pwnd!=NULL) ? pwnd->GetRuntimeClass()->m_lpszClassName : "(Not available)");
   //   TRACE("// TickCount: %d \n", dwTimeOut - dwTimeIn);
   //   TRACE("// \n");


      return TwfRender(
         pdc,
         hwndExclude,
         rectUpdate,
         hwndtree.m_hwndtreea,
         bBackground);

   }*/

   window_interface * window_interface::window_interface_get_parent()
   {
      return NULL;
   }


   void window_interface::TwfGetWndArray(user::LPWndArray & wndpa)
   {
      wndpa = *dynamic_cast<user::LPWndArray *>(get_app());
   }

   void window_interface::TwfGetWndArray(user::HWNDArray & hwnda)
   {
      user::LPWndArray & wndpa = *dynamic_cast<user::LPWndArray *>(get_app());
      wndpa.get_wnda(hwnda);
   }


   void window_interface::_001RedrawWindow()
   {
      if(&System == NULL)
         return;

      // Currently does not redraw upon coercive request
      // Only prodevian or netshare redraw

      if(System.get_twf() != NULL )
      {
         if(!System.get_twf()->m_bProDevianMode)
         {
            synch_lock lock(System.get_twf());
            get_wnd()->m_pguie->RedrawWindow();
         }
      }
   }

   void window_interface::_001OnBaseWndGetProperty(gen::signal_object * pobj)
   {
      SCAST_PTR(gen::message::base, pbase, pobj)
      pbase->set_lresult(_001BaseWndGetProperty((EProperty) pbase->m_wparam, pbase->m_lparam));
   }

   LRESULT window_interface::_001BaseWndGetProperty(EProperty eprop, LPARAM lparam)
   {
      switch(eprop)
      {
      case PropertyBaseWndInterface:
      case PropertyDrawBaseWndInterface:
         {
            const window_interface ** ppinterface = (const window_interface **) lparam;
            *ppinterface = this;
         }
         return 1;
      default:
         break;
      }
      return 0;
   }



   // The first ::ca::window handle in the base_array must belong
   // to the higher z order ::ca::window.
   // The rectangle must contain all update region.
   // It must be in screen coordinates.

   // This optimization eliminates top level windows
   // that are lower z order siblings of a higher z order
   // top level ::ca::window that contains all
   // the update region in a opaque area.
   // It doesn´t eliminates from the update parent windows
   // obscured by opaque children.

   /*void window_interface::Optimize001(
      user::HwndTree::Array & hwndtreea,
      LPCRECT lpcrect)
   {
      ::ca::region rgn;

      rgn.CreateRectRgnIndirect(lpcrect);

      Optimize001(hwndtreea, rgn);
   }

   window_interface::EOptimize window_interface::Optimize001(
      user::HwndTree::Array & hwndtreea,
      HRGN hrgn)
   {
      for(int i = 0; i < hwndtreea.get_size();)
      {
         user::HwndTree & hwndtree = hwndtreea[i];
         switch(Optimize001(
            hwndtree,
            hrgn))
         {
         case OptimizeNone:
            i++;
            break;
         case OptimizeThis:
            hwndtreea.remove_at(i);
            break;
         }
      }
      return OptimizeNone;
   }



   window_interface::EOptimize window_interface::Optimize001(
      user::HwndTree & hwndtree,
      HRGN hrgn)
   {

      HWND hwnd = hwndtree.m_hwnd;

      if(!::IsWindowVisible(hwnd))
      {
         return OptimizeThis;
      }

      window_interface * pwndi = NULL;
      if(pwndi == NULL)
      {
         single_lock sl(&m_papp->s_ptwf->m_csWndInterfaceMap, TRUE);
         if(!m_papp->s_ptwf->m_wndinterfacemap.Lookup(hwnd, pwndi))
         {
            ::SendMessage(
               hwnd,
               window_interface::MessageBaseWndGetProperty,
               window_interface::PropertyDrawBaseWndInterface,
               (LPARAM) &pwndi);
            m_papp->s_ptwf->m_wndinterfacemap.set_at(hwnd, pwndi);
         }
      }

      if(pwndi != NULL && !pwndi->_001HasTranslucency())
      {
         rect rectClient;
         ::GetClientRect(hwnd, rectClient);
         ::ClientToScreen(hwnd, &rectClient.top_left());
         ::ClientToScreen(hwnd, &rectClient.bottom_right());

         ::ca::region rgn;
         rgn.CreateRectRgnIndirect(rectClient);
         int iCombine = ::CombineRgn(hrgn, hrgn, rgn, RGN_DIFF);
         if(iCombine == NULLREGION)
         {
            ASSERT(TRUE);
         }
      }

      return Optimize001(
            hwndtree.m_hwndtreea,
            hrgn);
   }
   */


   window_interface::ETranslucency window_interface::_001GetTranslucency()
   {
      return m_etranslucency;
   }

   bool window_interface::_001IsTranslucent()
   {
      return m_etranslucency == TranslucencyPresent;
   }

   bool window_interface::_001IsBackgroundBypass()
   {
      return m_bBackgroundBypass;
   }

   bool window_interface::_001HasTranslucency()
   {
      return m_etranslucency == TranslucencyPresent
         || m_etranslucency == TranslucencyTotal;
   }

   bool window_interface::_001IsTransparent()
   {
      return m_etranslucency == TranslucencyTotal;
   }

   void window_interface::RedrawOptimize(rect_array &base_array)
   {
      rect rect;

   Restart:
      for(int i = 0; i < base_array.get_size(); i++)
      {
         for(int j = i + 1; j < base_array.get_size(); j++)
         {
            if(RedrawOptimize(
               rect,
               base_array[i],
               base_array[j]))
            {
               base_array[i] = rect;
               base_array.remove_at(j);
               goto Restart;
            }
         }
      }
   }

   bool window_interface::RedrawOptimize(LPRECT lprectOut, LPCRECT lpcrect1, LPCRECT lpcrect2)
   {
      rect rect1(lpcrect1);
      rect rect2(lpcrect2);
      rect rect3;

      int iArea1 = rect1.width() * rect1.height();
      int iArea2 = rect2.width() * rect2.height();
      rect3.unite(rect1, rect2);
      int iArea3 = rect3.width() * rect3.height();


      if(iArea3 < (110 * (iArea1 + iArea2) / 100))
      {
         *lprectOut = rect3;
         return true;
      }
      else
      {
         return false;
      }
   }



   void window_interface::_001OnCreate(gen::signal_object * pobj)
   {
      SCAST_PTR(gen::message::create, pcreate, pobj)
      if(pobj->previous())
         return;
      pcreate->set_lresult(0);
      pcreate->m_bRet = false;
      // trans PostMessageA(MessageGeneralEvent, GeneralEventPosCreate1);
   }

   void window_interface::PreSubClassWindow()
   {
      _001BaseWndInterfaceMap();
   }

   void window_interface::_001BaseWndInterfaceMap()
   {
   }

   interaction * window_interface::get_guie()
   {
      return m_pguie;
   }

   ::ca::window * window_interface::get_wnd()
   {
      return NULL;
   }

   bool window_interface::_001IsWindowEnabled()
   {
      return true;
   }

   void window_interface::_001EnableWindow(bool bEnable)
   {
      UNREFERENCED_PARAMETER(bEnable);
   }


   void window_interface::_on_start_user_message_handler()
   {
      dispatch::_on_start_user_message_handler();
      _001BaseWndInterfaceMap();
   }

   void window_interface::_000OnDraw(::ca::graphics * pdc)
   {
      _001OnDraw(pdc);
   }


   void window_interface::UpdateWindow()
   {
      //ASSERT(::IsWindow(GetHandle()));
      //::UpdateWindow(GetHandle());
   }

   inline void window_interface::Invalidate(BOOL bErase)
   {
      UNREFERENCED_PARAMETER(bErase);
      //ASSERT(::IsWindow(GetHandle()));
      //::InvalidateRect(GetHandle(), NULL, bErase);
   }

   bool window_interface::Redraw(rect_array & recta)
   {
      for(int i = 0; i < recta.get_size(); i++)
      {
         get_wnd()->RedrawWindow(recta[i]);
      }
      return true;
   }

   bool window_interface::Redraw(LPCRECT lprect, ::ca::region * prgn)
   {
      get_wnd()->RedrawWindow(lprect, prgn, RDW_INVALIDATE);
      return true;
   }

   bool window_interface::Redraw(::ca::graphics * pdc)
   {
      UNREFERENCED_PARAMETER(pdc);
      get_wnd()->RedrawWindow();
      return true;
   }


   void window_interface::ClientToScreen(LPRECT lprect)
   {

      lprect->left   += (LONG) m_rectParentClient.left;
      lprect->right  += (LONG) m_rectParentClient.left;
      lprect->top    += (LONG) m_rectParentClient.top;
      lprect->bottom += (LONG) m_rectParentClient.top;

      if(window_interface_get_parent() != NULL)
      {
         window_interface_get_parent()->ClientToScreen(lprect);
      }
   }

   void window_interface::ClientToScreen(LPPOINT lppoint)
   {
      lppoint->x     += (LONG) m_rectParentClient.left;
      lppoint->y     += (LONG) m_rectParentClient.top;
      if(window_interface_get_parent() != NULL)
      {
         window_interface_get_parent()->ClientToScreen(lppoint);
      }
   }


   void window_interface::ClientToScreen(__rect64 * lprect)
   {
      lprect->left   += m_rectParentClient.left;
      lprect->right  += m_rectParentClient.left;
      lprect->top    += m_rectParentClient.top;
      lprect->bottom += m_rectParentClient.top;

      if(window_interface_get_parent() != NULL)
      {
         window_interface_get_parent()->ClientToScreen(lprect);
      }
   }

   void window_interface::ClientToScreen(__point64 * lppoint)
   {
      lppoint->x     += m_rectParentClient.left;
      lppoint->y     += m_rectParentClient.top;
      if(window_interface_get_parent() != NULL)
      {
         window_interface_get_parent()->ClientToScreen(lppoint);
      }
   }


   void window_interface::ScreenToClient(LPRECT lprect)
   {
      lprect->left   -= (LONG) m_rectParentClient.left;
      lprect->right  -= (LONG) m_rectParentClient.left;
      lprect->top    -= (LONG) m_rectParentClient.top;
      lprect->bottom -= (LONG) m_rectParentClient.top;

      if(window_interface_get_parent() != NULL)
      {
         window_interface_get_parent()->ScreenToClient(lprect);
      }
   }

   void window_interface::ScreenToClient(LPPOINT lppoint)
   {
      lppoint->x     -= (LONG) m_rectParentClient.left;
      lppoint->y     -= (LONG) m_rectParentClient.top;
      if(window_interface_get_parent() != NULL)
      {
         window_interface_get_parent()->ScreenToClient(lppoint);
      }
   }


   void window_interface::ScreenToClient(__rect64 * lprect)
   {
      lprect->left   -= m_rectParentClient.left;
      lprect->right  -= m_rectParentClient.left;
      lprect->top    -= m_rectParentClient.top;
      lprect->bottom -= m_rectParentClient.top;

      if(window_interface_get_parent() != NULL)
      {
         window_interface_get_parent()->ScreenToClient(lprect);
      }
   }

   void window_interface::ScreenToClient(__point64 * lppoint)
   {
      lppoint->x     -= m_rectParentClient.left;
      lppoint->y     -= m_rectParentClient.top;
      if(window_interface_get_parent() != NULL)
      {
         window_interface_get_parent()->ScreenToClient(lppoint);
      }
   }


   void window_interface::GetWindowRect(LPRECT lprect)
   {
      rect64 rect;
      GetWindowRect(rect);
      ::copy(lprect, rect);
   }

   void window_interface::GetClientRect(LPRECT lprect)
   {
      rect64 rect;
      GetClientRect(rect);
      ::copy(lprect, rect);
   }

   void window_interface::GetClientRect(__rect64 * lprect)
   {
      *lprect = m_rectParentClient;
      lprect->right -= lprect->left;
      lprect->bottom -= lprect->top;
      lprect->left = 0;
      lprect->top = 0;
   }

   void window_interface::GetWindowRect(__rect64 * lprect)
   {
      *lprect = m_rectParentClient;
      if(window_interface_get_parent() != NULL)
      {
         window_interface_get_parent()->ClientToScreen(lprect);
      }
   }


} // namespace user
