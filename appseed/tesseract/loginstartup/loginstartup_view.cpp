#include "StdAfx.h"
#include "loginstartup_view.h"
#include "loginstartup_document.h"
#include <Psapi.h>

loginstartup_view::loginstartup_view(::ca::application * papp) :
   ::ca::ca(papp),
   user_interface(papp),
   m_dibV(papp)
{
   m_brushBkActive.CreateSolidBrush(RGB(150, 255, 130));
   m_brushBkInactive.CreateSolidBrush(RGB(128, 208, 120));
   LOGFONT lf;
   memset(&lf, 0, sizeof(lf));

   strcpy(lf.lfFaceName, "Verdana");
   lf.lfHeight = 13;
   m_font.CreateFontIndirect(&lf);

   lf.lfHeight = 15;
   lf.lfWeight = 900;

   m_iArea = 0;
   m_iItemHeight = 26;
   m_iTaskOffset = 1000;
   m_iClockOffset = 10000;
//   m_iNotificationAreaButtonOffset = 10100;
   m_iNotificationAreaOffset = 10200;
   m_iClockH = 30;
   m_iDragTask = -1;
   m_bDragTask = false;
   m_iNotificationAreaH = 30;
   m_bNotificationArea = true;
   m_iNotificationAreaColumnCount = 15;
   m_iV = 123;
   m_iVH = 49;
   m_iVW = 123;
   m_iShutDown = 60000;
   m_iShutDownW = 49;
   m_iShutDownH = 49;
   m_bShutDown = false;
}

loginstartup_view::~loginstartup_view()
{
}

void loginstartup_view::_001InstallMessageHandling(igui::win::message::Dispatch * pinterface)
{
   BaseView::_001InstallMessageHandling(pinterface);

	IGUI_WIN_MSG_LINK(WM_DESTROY, pinterface, this, &loginstartup_view::_001OnDestroy);
	IGUI_WIN_MSG_LINK(WM_SIZE, pinterface, this, &loginstartup_view::_001OnSize);
	IGUI_WIN_MSG_LINK(WM_PAINT, pinterface, this, &loginstartup_view::_001OnPaint);
	IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &loginstartup_view::_001OnCreate);
	IGUI_WIN_MSG_LINK(WM_CONTEXTMENU, pinterface, this, &loginstartup_view::_001OnContextMenu);
	IGUI_WIN_MSG_LINK(WM_SETCURSOR, pinterface, this, &loginstartup_view::_001OnSetCursor);
	IGUI_WIN_MSG_LINK(WM_ERASEBKGND, pinterface, this, &loginstartup_view::_001OnEraseBkgnd);

   //IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN, pinterface, this, &user_interface::_001OnLButtonDown);
//   IGUI_WIN_MSG_LINK(WM_LBUTTONUP, pinterface, this, &user_interface::_001OnLButtonUp);
   IGUI_WIN_MSG_LINK(WM_KEYDOWN, pinterface, this, &user_interface::_001OnKeyDown);
   IGUI_WIN_MSG_LINK(WM_KEYUP, pinterface, this, &user_interface::_001OnKeyUp);

   IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN, pinterface, this, &loginstartup_view::_001OnLButtonDown);
   IGUI_WIN_MSG_LINK(WM_LBUTTONUP, pinterface, this, &loginstartup_view::_001OnLButtonUp);
   IGUI_WIN_MSG_LINK(WM_RBUTTONUP, pinterface, this, &loginstartup_view::_001OnRButtonUp);
   IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &loginstartup_view::_001OnTimer);

   IGUI_WIN_MSG_LINK(MessageOp, pinterface, this, &loginstartup_view::_001OnOp);
   IGUI_WIN_MSG_LINK(WM_SHOWWINDOW, pinterface, this, &loginstartup_view::_001OnShowWindow);
   IGUI_WIN_MSG_LINK(WM_DESTROY, pinterface, this, &loginstartup_view::_001OnDestroy);

}
/////////////////////////////////////////////////////////////////////////////
// loginstartup_view drawing

void loginstartup_view::OnDraw(::ca::graphics * pdcScreen)
{
}

/////////////////////////////////////////////////////////////////////////////
// loginstartup_view diagnostics

#ifdef _DEBUG
void loginstartup_view::AssertValid() const
{
	BaseView::AssertValid();
}

void loginstartup_view::Dump(CDumpContext & dumpcontext) const
{
	BaseView::Dump(dumpcontext);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// loginstartup_view message handlers

// vmpLightView.cpp : implementation of the loginstartup_view class
//


/////////////////////////////////////////////////////////////////////////////
// loginstartup_view


BOOL loginstartup_view::PreCreateWindow(CREATESTRUCT& cs)
{
   cs.lpszClass = Application.RegisterWndClass(
		CS_DBLCLKS |
		CS_OWNDC,
		0, 0, 0);
   cs.style &= ~WS_EX_CLIENTEDGE;
	return BaseView::PreCreateWindow(cs);
}
void loginstartup_view::_001OnInitialUpdate(gen::signal_object * pobj) 
{
   BaseView::_001OnInitialUpdate(pobj);
}

::user_interface * loginstartup_view::get_guie()
{
   return this;
}

void loginstartup_view::on_update(BaseView* pSender, LPARAM lHint, base_object* phint) 
{
   if(lHint == 5432108)
   {
      SetTimer(5432108, 100, NULL);
   }
	
}

idb::user_interface * loginstartup_view::BackViewGetWnd()
{
   return this;
}

void loginstartup_view::_001OnDestroy(gen::signal_object * pobj) 
{
	BaseView::_001OnDestroy(pobj);
}



void loginstartup_view::_001OnSize(gen::signal_object * pobj) 
{
   SCAST_PTR(igui::win::message::size, psize, pobj)

   rect rectDesktop;
   HWND hwndDesktop = ::GetDesktopWindow();
   ::GetWindowRect(hwndDesktop, rectDesktop);

   m_iWScreen = rectDesktop.width();
   m_iHScreen = rectDesktop.height();
   rect rectClient;
   GetClientRect(rectClient);
   rectClient.DeflateRect(2, 2);
   int iW = rectClient.width() / 2;
   int iH = rectClient.height() / 2;
   iH = min(iH, 120);
   double r = (double) iW / (double) iH;
   double rScreen = (double) rectDesktop.width() / (double) rectDesktop.height();
   if(r < rScreen)
   {
      iH = iW / rScreen;
   }
   else if(r > rScreen)
   {
      iW = iH * rScreen;
   }
   m_iW = iW;
   m_iH = iH;
//   Snapshot();
}

void loginstartup_view::_001OnPaint(gen::signal_object * pobj) 
{
//	CPaintDC spgraphics(this); // device context for loginstartuping
//   spgraphics->TextOut(20, 20, "Carlos Gustavo Cecyn Lundgren é minha Vida Eterna, meu Coração Eterno, Todo meu tesouro eterno, meu Universo eterno, meu tudo eterno!!");
}


void loginstartup_view:: _001OnDraw(::ca::graphics * pdc)
{
   rect rectClient;
   GetClientRect(rectClient);

   pdc->FillSolidRect(rectClient, RGB(255, 255, 255));

   rect rectArea;

   GetAreaThumbRect(rectArea, m_iV);
   m_dibV->Render(pdc, rectArea.left, rectArea.top, rectArea.width(), rectArea.height());


}

void loginstartup_view::_001OnCreate(gen::signal_object * pobj) 
{
   if(pobj->previous())
      return;
   SetTimer(3003, 300, NULL);
   SetTimer(543218, 1000, NULL);
   ::ca::graphics * pdc = GetDC();
   FIBITMAP * pfi = Application.imaging().LoadImageFile(
      Application.dir().standard_square_matter("votagus_mountains_and_valleys-123.png"));
   m_dibV.From((HDC)pdc->get_os_data(), pfi, true);

   
   m_notificationareainfo.Initialize(get_app());
/*   winaction_frame * pframe = dynamic_cast < winaction_frame * > (GetParentFrame());
   if(pframe != NULL)
   {
      pframe->m_ploginstartupview = this;
   }*/
}


void loginstartup_view::_001OnContextMenu(gen::signal_object * pobj) 
{
   SCAST_PTR(igui::win::message::context_menu, pcontextmenu, pobj)
   point point = pcontextmenu->GetPoint();
}


void loginstartup_view::_001OnTabClick(int iTab)
{
   if(iTab == 1)
   {
      Application.simple_message_box("Playlist");
   }
}

void loginstartup_view::_001OnSetCursor(gen::signal_object * pobj) 
{
   ::SetCursor(::LoadCursor(NULL, IDC_ARROW));
	
	pobj->previous();
}
void loginstartup_view::_001OnEraseBkgnd(gen::signal_object * pobj) 
{
   SCAST_PTR(igui::win::message::erase_bkgnd, perasebkgnd, pobj)
   perasebkgnd->m_bRet = true;
   perasebkgnd->set_result(TRUE);
}



loginstartup_document * loginstartup_view::get_document()
{
   return dynamic_cast < loginstartup_document * > (BaseView::get_document());
}

void loginstartup_view::GetAreaThumbRect(LPRECT lprect, int iArea)
{
   rect rectClient;
   GetClientRect(rectClient);
   if(iArea == m_iV)
   {
      lprect->bottom = rectClient.bottom;
      lprect->top = lprect->bottom - m_iVH;
      lprect->left = 1;
      lprect->right = lprect->left + m_iVW;
   }
   else if(iArea == m_iShutDown)
   {
      lprect->bottom = rectClient.bottom;
      lprect->top = lprect->bottom - m_iShutDownH;
      lprect->right = rectClient.right - 1;
      lprect->left = lprect->right - m_iShutDownW;
      
   }
   else if(iArea >= m_iNotificationAreaOffset)
   {
      int iColCount = m_iNotificationAreaColumnCount;
      int iCol = (iArea - m_iNotificationAreaOffset) % iColCount;
      int iLin = (iArea - m_iNotificationAreaOffset) / iColCount;
      int cx = 20;
      lprect->left = 1 + iCol * cx;
      lprect->top = rectClient.bottom - m_iVH - m_iItemHeight * 3 + m_iItemHeight * (((iArea - m_iNotificationAreaOffset) / iColCount));
      lprect->right = lprect->left + cx;
      lprect->bottom = lprect->top + m_iItemHeight;
   }
/*   else if(iArea >= m_iNotificationAreaButtonOffset)
   {
      lprect->left = 1;
      lprect->top = 1 + m_iClockH + m_iH * 2 + 5;
      lprect->right = 350;
      lprect->bottom = lprect->top + m_iNotificationAreaH;
   }*/
   else if(iArea >= m_iClockOffset)
   {
      lprect->left = 1;
      lprect->top = 1;
      lprect->right = 350;
      lprect->bottom = lprect->top + m_iClockH;
      return;
   }
   else if(iArea >= m_iTaskOffset)
   {
      lprect->left = 1;
      //lprect->top = m_iClockH + m_iNotificationAreaH + m_iH * 2 + 5 + m_iItemHeight * ((iArea - m_iTaskOffset));
      lprect->top = m_iClockH + m_iH * 2 + 5 + m_iItemHeight * ((iArea - m_iTaskOffset));
      lprect->right = 350;
      lprect->bottom = lprect->top + m_iItemHeight;
   }
   else
   {
      switch(iArea)
      {
      case 0:
         lprect->left = 1;
         lprect->top = m_iClockH + 1;
         lprect->right = lprect->left + m_iW;
         lprect->bottom = lprect->top + m_iH;
         break;
      case 1:
         lprect->left = m_iW + 3;
         lprect->top = m_iClockH + 1;
         lprect->right = lprect->left + m_iW;
         lprect->bottom = lprect->top + m_iH;
         break;
      case 2:
         lprect->left = 1;
         lprect->top = m_iClockH + m_iH + 3;
         lprect->right = lprect->left + m_iW;
         lprect->bottom = lprect->top + m_iH;
         break;
      case 3:
         lprect->left = m_iW + 3;
         lprect->top = m_iClockH + m_iH + 3;
         lprect->right = lprect->left + m_iW;
         lprect->bottom = lprect->top + m_iH;
         break;
      }
   }
}

int loginstartup_view::hit_test(point pt)
{
   rect rectArea;
   GetAreaThumbRect(rectArea, m_iV);
   if(rectArea.PtInRect(pt))
   {
      return m_iV;
   }
   GetAreaThumbRect(rectArea, m_iShutDown);
   if(rectArea.PtInRect(pt))
   {
      return m_iShutDown;
   }
   GetAreaThumbRect(rectArea, m_iClockOffset);
   if(rectArea.PtInRect(pt))
   {
      return m_iClockOffset;
   }
/*   GetAreaThumbRect(rectArea, m_iNotificationAreaButtonOffset);
   if(rectArea.PtInRect(pt))
   {
      return m_iNotificationAreaButtonOffset;
   }*/
   for(int i = 0; i < m_notificationareainfo.m_infoa.get_size(); i++)
   {
      GetAreaThumbRect(rectArea, m_iNotificationAreaOffset + i);
      if(rectArea.PtInRect(pt))
      {
         return m_iNotificationAreaOffset + i;
      }
   }
   for(int i = 0; i < 4; i++)
   {
      GetAreaThumbRect(rectArea, i);
      if(rectArea.PtInRect(pt))
      {
         return i;
      }
   }
   return -1;
}

void loginstartup_view::_001OnLButtonDown(gen::signal_object * pobj)
{
   SCAST_PTR(igui::win::message::mouse, pmouse, pobj)

   int iHitArea = hit_test(pmouse->m_pt);
   if(iHitArea >= 0 &&  !m_bShutDown)
   {
   }

}

void loginstartup_view::_001OnLButtonUp(gen::signal_object * pobj)
{
   SCAST_PTR(igui::win::message::mouse, pmouse, pobj)
   KillTimer(5432180);

   int iHitArea = hit_test(pmouse->m_pt);
   if(m_bDragTask && !m_bShutDown)
   {
      m_bDragTask = false;
   }
   if(iHitArea == m_iV)
   {

   }
   else if(iHitArea == m_iShutDown)
   {
      m_bShutDown = !m_bShutDown;
      _001RedrawWindow();
   }
   else if(iHitArea >= 0)
   {
      {
   /*      else if(iHitArea == m_iNotificationAreaButtonOffset)
         {
            m_notificationareainfo.Refresh();
            m_bNotificationArea = true;
         }*/
         if(iHitArea >= m_iNotificationAreaOffset && iHitArea < (m_iNotificationAreaOffset + m_notificationareainfo.m_infoa.get_size()))
         {
            m_notificationareainfo.LeftClick(iHitArea - m_iNotificationAreaOffset);
            ::Sleep(100);
         }
      }
   }

}

void loginstartup_view::_001OnRButtonUp(gen::signal_object * pobj)
{
   SCAST_PTR(igui::win::message::mouse, pmouse, pobj)

   int iHitArea = hit_test(pmouse->m_pt);
   if(iHitArea >= m_iNotificationAreaOffset)
   {
      m_notificationareainfo.RightClick(iHitArea - m_iNotificationAreaOffset);
   }
   else if(iHitArea >= m_iClockOffset)
   {
   }
   else if(iHitArea < 0)
   {
      BaseWndMenu menu(get_app());
      menu.LoadXmlMenu("loginstartup\\popup_loginstartup.xml");
      BaseWndMenu menuPopup(get_app(), menu.GetSubMenu(0));
      menuPopup.TrackPopupMenu(0, pmouse->m_pt.x, pmouse->m_pt.y, GetParentFrame());
   }
   
}

void loginstartup_view::_001OnOp(gen::signal_object * pobj)
{
   SCAST_PTR(igui::win::message::base, pbase, pobj)
   if(pbase->m_wparam == OpUpdateCurrentArea)
   {
   }
}


void loginstartup_view::_001OnTimer(gen::signal_object * pobj)
{
   SCAST_PTR(igui::win::message::timer, ptimer, pobj)
   if(ptimer->m_nIDEvent == 543218)
   {
      if(IsWindowVisible())
      {
         m_notificationareainfo.Refresh();
      }
   }
   else if(ptimer->m_nIDEvent == 5432108)
   {
      KillTimer(ptimer->m_nIDEvent);
   }
   else if(ptimer->m_nIDEvent == 5432180)
   {
      KillTimer(ptimer->m_nIDEvent);
      m_bDragTask = true;
   }
   else if(ptimer->m_nIDEvent == 3003)
   {
   }
}




UINT AFX_CDECL loginstartup_view::ThreadProcShowWindow(LPVOID lpparam)
{
   show_window * pshow = (show_window *) lpparam;
   if(pshow->m_iShow == -1)
   {
      ::SetForegroundWindow(pshow->m_hwnd);
      ::SetWindowPos(pshow->m_hwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
   }
   else
   {
      if(pshow->m_iShow == SW_RESTORE)
      {
         ::SetForegroundWindow(pshow->m_hwnd);
      }
      ::ShowWindow(pshow->m_hwnd, pshow->m_iShow);
   }
   pshow->m_pview->PostMessageA(MessageOp, OpUpdateCurrentArea);
   delete pshow;
   return 0;
}

loginstartup_view::show_window::show_window(HWND hwnd, int iShow, loginstartup_view * pview)
{
   m_hwnd   = hwnd;
   m_iShow  = iShow;
   m_pview  = pview;
}



void loginstartup_view::_001OnShowWindow(gen::signal_object * pobj) 
{
   SCAST_PTR(igui::win::message::show_window, pshowwindow, pobj)
}


void loginstartup_view::ensure_apps()
{
   if(::IsWindow(m_hwndWinactionarea) &&
      ::IsWindow(m_hwndCommand) &&
      ::IsWindow(m_hwndWinutil))
      return;
   EnumWindows(GetAppsEnumWindowsProc, (LPARAM) this);
   if(!::IsWindow(m_hwndWinactionarea))
   {
      /*::ShellExecuteW(
            NULL, 
            NULL, 
            gen::international::utf8_to_unicode(m_strWinactionarea),
            NULL,
            gen::international::utf8_to_unicode(Application.dir().name(m_strWinactionarea)),
            SW_SHOW);*/
   }
   if(!::IsWindow(m_hwndCommand))
   {
      /*::ShellExecuteW(
            NULL, 
            NULL, 
            gen::international::utf8_to_unicode(m_id),
            NULL,
            gen::international::utf8_to_unicode(Application.dir().name(m_id)),
            SW_SHOW);*/
   }
}


BOOL CALLBACK loginstartup_view::GetAppsEnumWindowsProc(      
    HWND hwnd,
    LPARAM lParam)
{
   loginstartup_view * pview = (loginstartup_view *) lParam;
   DWORD dwThreadId;
   DWORD dwProcessId;
   HICON hicon16;
   HICON hicon48;
   DWORD dwptr;
   if(!::SendMessageTimeout(hwnd, WM_APP + 2000, 1, 0, SMTO_BLOCK, 10, (PDWORD_PTR) &dwptr) || dwptr != 2)
   {
      return TRUE;
   }
   if(!::SendMessageTimeout(hwnd, WM_APP + 2000, 2, 0, SMTO_BLOCK, 10, (PDWORD_PTR) &dwptr) || dwptr != 4)
   {
      return TRUE;
   }
   if(!::SendMessageTimeout(hwnd, WM_APP + 2000, 4, 0, SMTO_BLOCK, 10, (PDWORD_PTR) &dwptr) || dwptr != 5)
   {
      return TRUE;
   }
   if(!::SendMessageTimeout(hwnd, WM_APP + 2000, 5, 0, SMTO_BLOCK, 10, (PDWORD_PTR) &dwptr) || dwptr != 8)
   {
      return TRUE;
   }
   if(!::SendMessageTimeout(hwnd, WM_APP + 2000, 8, 0, SMTO_BLOCK, 10, (PDWORD_PTR) &dwptr) || dwptr != 11)
   {
      return TRUE;
   }
   if(!::SendMessageTimeout(hwnd, WM_APP + 2000, 11, 0, SMTO_BLOCK, 10, (PDWORD_PTR) &dwptr) || dwptr != 23)
   {
      return TRUE;
   }
   if(!::SendMessageTimeout(hwnd, WM_APP + 2000, 23, 0, SMTO_BLOCK, 10, (PDWORD_PTR) &dwptr) || dwptr != 33)
   {
      return TRUE;
   }
   if(::SendMessageTimeout(hwnd, WM_APP + 2000, 33, 0, SMTO_BLOCK, 10, (PDWORD_PTR) &dwptr))
   {
      if(dwptr == 1)
      {
         pview->m_hwndCommand = hwnd;
      }
      else if(dwptr == 67)
      {
         pview->m_hwndWinactionarea = hwnd;
      }
      else if(dwptr == 68)
      {
         pview->m_hwndWinutil = hwnd;
      }

   }
   return TRUE;
}


