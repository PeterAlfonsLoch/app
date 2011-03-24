#include "stdafx.h"
#include "definitionland_view.h"
#include "definitionland_document.h"


IMPLEMENT_DYNCREATE(definitionland_view, BaseView)


definitionland_view::definitionland_view()
{
   m_brushBkActive.CreateSolidBrush(RGB(150, 255, 130));
   m_brushBkInactive.CreateSolidBrush(RGB(128, 208, 120));
   LOGFONT lf;
   memset(&lf, 0, sizeof(lf));

   strcpy(lf.lfFaceName, "Verdana");
   lf.lfHeight = 13;
   m_font.CreateFontIndirect(&lf);

   m_calendar.m_font.CreateFontIndirect(&lf);
   lf.lfHeight = 15;
   lf.lfWeight = 900;
   m_calendar.m_fontYear.CreateFontIndirect(&lf);
   m_calendar.m_fontMonth.CreateFontIndirect(&lf);
   m_calendar.m_fontSpin.CreateFontIndirect(&lf);

   m_areaa.AddNew();
   m_areaa.AddNew();
   m_areaa.AddNew();
   m_areaa.AddNew();
   m_areaa[0].m_pview = this;
   m_areaa[1].m_pview = this;
   m_areaa[2].m_pview = this;
   m_areaa[3].m_pview = this;
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
   m_bShowCalendar = false;
   m_calendar.set_time(CTime::GetCurrentTime());
   m_iNotificationAreaColumnCount = 15;
   m_iV = 123;
   m_iVH = 49;
   m_iVW = 123;
   m_iShutDown = 60000;
   m_iShutDownW = 49;
   m_iShutDownH = 49;
   m_bShutDown = false;
}

definitionland_view::~definitionland_view()
{
}

void definitionland_view::_001InstallMessageHandling(igui::win::message::Dispatch * pinterface)
{
   BaseView::_001InstallMessageHandling(this);

	IGUI_WIN_MSG_LINK(WM_DESTROY      , this, this, &definitionland_view::_001OnDestroy);
	IGUI_WIN_MSG_LINK(WM_SIZE         , this, this, &definitionland_view::_001OnSize);
	IGUI_WIN_MSG_LINK(WM_PAINT        , this, this, &definitionland_view::_001OnPaint);
	IGUI_WIN_MSG_LINK(WM_CREATE       , this, this, &definitionland_view::_001OnCreate);
	IGUI_WIN_MSG_LINK(WM_CONTEXTMENU  , this, this, &definitionland_view::_001OnContextMenu);
	IGUI_WIN_MSG_LINK(WM_SETCURSOR    , this, this, &definitionland_view::_001OnSetCursor);
	IGUI_WIN_MSG_LINK(WM_ERASEBKGND   , this, this, &definitionland_view::_001OnEraseBkgnd);

   IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN  , this, this, &Ex1VirtualGuieInterface::_001OnLButtonDown);
   IGUI_WIN_MSG_LINK(WM_LBUTTONUP    , this, this, &Ex1VirtualGuieInterface::_001OnLButtonUp);
   IGUI_WIN_MSG_LINK(WM_KEYDOWN      , this, this, &Ex1VirtualGuieInterface::_001OnKeyDown);
   IGUI_WIN_MSG_LINK(WM_KEYUP        , this, this, &Ex1VirtualGuieInterface::_001OnKeyUp);
   IGUI_WIN_MSG_LINK(WM_TIMER        , this, this, &Ex1VirtualGuieInterface::_001OnTimer);

   IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN  , this, this, &definitionland_view::_001OnLButtonDown);
   IGUI_WIN_MSG_LINK(WM_LBUTTONUP    , this, this, &definitionland_view::_001OnLButtonUp);
   IGUI_WIN_MSG_LINK(WM_RBUTTONUP    , this, this, &definitionland_view::_001OnRButtonUp);
   IGUI_WIN_MSG_LINK(WM_TIMER        , this, this, &definitionland_view::_001OnTimer);

   IGUI_WIN_MSG_LINK(MessageOp       , this, this, &definitionland_view::_001OnOp);
   IGUI_WIN_MSG_LINK(WM_SHOWWINDOW   , this, this, &definitionland_view::_001OnShowWindow);
   IGUI_WIN_MSG_LINK(WM_DESTROY      , this, this, &definitionland_view::_001OnDestroy);

}
/////////////////////////////////////////////////////////////////////////////
// definitionland_view drawing

void definitionland_view::OnDraw(CDC* pdcScreen)
{
}

/////////////////////////////////////////////////////////////////////////////
// definitionland_view diagnostics

#ifdef _DEBUG
void definitionland_view::AssertValid() const
{
	BaseView::AssertValid();
}

void definitionland_view::Dump(CDumpContext& dc) const
{
	BaseView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// definitionland_view message handlers

// vmpLightView.cpp : implementation of the definitionland_view class
//


/////////////////////////////////////////////////////////////////////////////
// definitionland_view


BOOL definitionland_view::PreCreateWindow(CREATESTRUCT& cs)
{
   cs.lpszClass = AfxRegisterWndClass(
		CS_DBLCLKS |
		CS_OWNDC,
		0, 0, 0);
   cs.style &= ~WS_EX_CLIENTEDGE;
	return BaseView::PreCreateWindow(cs);
}
/////////////////////////////////////////////////////////////////////////////
// definitionland_view printing

BOOL definitionland_view::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void definitionland_view::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: add extra initialization before printing
}

void definitionland_view::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// OLE Server support

// The following command handler provides the standard keyboard
//  user interface to cancel an in-place editing session.  Here,
//  the server (not the container) causes the deactivation.
//void definitionland_view::OnCancelEditSrvr()
//{
//	GetscreencaptureViewData()->OnDeactivateUI(FALSE);
//}

/////////////////////////////////////////////////////////////////////////////
// definitionland_view message handlers
void definitionland_view::_001OnInitialUpdate(gen::signal_object * pobj) 
{
   BaseView::_001OnInitialUpdate(pobj);
}

base_wnd * definitionland_view::KaraokeGetWnd()
{
   return this;
}

base_wnd * definitionland_view::_001GetWnd()
{
   return this;
}

void definitionland_view::OnUpdate(BaseView* pSender, LPARAM lHint, base_object* phint) 
{
   if(lHint == 5432108)
   {
      SetTimer(5432108, 100, NULL);
   }
	
}
base_wnd * definitionland_view::BackViewGetWnd()
{
   return this;
}
void definitionland_view::_001OnDestroy(gen::signal_object * pobj) 
{
   for(int i = 0; i < m_areaa.GetSize(); i++)
   {
      for(int j = 0; j < m_areaa[i].m_hwnda.GetSize(); j++)
      {
         HWND hwnd = m_areaa[i].m_hwnda[j];
         ::ShowWindow(hwnd, SW_MINIMIZE);
      }
   }
	BaseView::OnDestroy();
}



void definitionland_view::_001OnSize(gen::signal_object * pobj) 
{
   SCAST_PTR(igui::win::message::size, psize, pobj)

   rect rectDesktop;
   HWND hwndDesktop = ::GetDesktopWindow();
   ::GetWindowRect(hwndDesktop, rectDesktop);

   m_iWScreen = rectDesktop.Width();
   m_iHScreen = rectDesktop.Height();
   rect rectClient;
   base_wnd::GetClientRect(rectClient);
   rectClient.DeflateRect(2, 2);
   int iW = rectClient.Width() / 2;
   int iH = rectClient.Height() / 2;
   iH = min(iH, 120);
   double r = (double) iW / (double) iH;
   double rScreen = (double) rectDesktop.Width() / (double) rectDesktop.Height();
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
   m_areaa[0].m_dib.Create(iW - 4, iH - 4);
   m_areaa[1].m_dib.Create(iW - 4, iH - 4);
   m_areaa[2].m_dib.Create(iW - 4, iH - 4);
   m_areaa[3].m_dib.Create(iW - 4, iH - 4);
   m_calendar.set_pos(point(1, 1 + m_iClockH), size(350, 250));
//   Snapshot();
}

void definitionland_view::_001OnPaint(gen::signal_object * pobj) 
{
	CPaintDC dc(this); // device context for definitionlanding
   dc.TextOut(20, 20, "Carlos Gustavo Cecyn Lundgren é minha Vida Eterna, meu Coração Eterno, Todo meu tesouro eterno, meu Universo eterno, meu tudo eterno!!");
}


void definitionland_view:: _001OnDraw(CDC * pdc)
{
   rect rectClient;
   base_wnd::GetClientRect(rectClient);

   pdc->FillSolidRect(rectClient, RGB(255, 255, 255));

   rect rectArea;

   GetAreaThumbRect(rectArea, m_iV);
   m_dibV.Render(pdc, rectArea.left, rectArea.top, rectArea.Width(), rectArea.Height());


}

void definitionland_view::_001OnCreate(gen::signal_object * pobj) 
{
   if(pobj->previous())
      return;
   SetTimer(3003, 300, NULL);
   SetTimer(543218, 1000, NULL);
   CDC * pdc = base_wnd::GetDC();
   FIBITMAP * pfi = CImaging::GetImaging()->LoadImageFile(
      ca2::app(get_app()).dir().standard_square_matter("votagus_mountains_and_valleys-123.png"));
   m_dibV.From(pdc->GetSafeHdc(), pfi, true);

   
   m_notificationareainfo.Initialize();
/*   winaction_frame * pframe = dynamic_cast < winaction_frame * > (GetParentFrame());
   if(pframe != NULL)
   {
      pframe->m_pdefinitionlandview = this;
   }*/
}


void definitionland_view::_001OnContextMenu(gen::signal_object * pobj) 
{
   SCAST_PTR(igui::win::message::context_menu, pcontextmenu, pobj)
   point point = pcontextmenu->GetPoint();
}


void definitionland_view::_001OnTabClick(int iTab)
{
   if(iTab == 1)
   {
      AfxMessageBox("Playlist");
   }
}

void definitionland_view::_001OnSetCursor(gen::signal_object * pobj) 
{
   ::SetCursor(::LoadCursor(NULL, IDC_ARROW));
	
	pobj->previous();
}
void definitionland_view::_001OnEraseBkgnd(gen::signal_object * pobj) 
{
   SCAST_PTR(igui::win::message::erase_bkgnd, perasebkgnd, pobj)
   perasebkgnd->m_bRet = true;
   perasebkgnd->set_result(TRUE);
}



definitionland_document * definitionland_view::GetDocument()
{
   return dynamic_cast < definitionland_document * > (BaseView::GetDocument());
}

void definitionland_view::GetAreaThumbRect(LPRECT lprect, int iArea)
{
   rect rectClient;
   base_wnd::GetClientRect(rectClient);
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

int definitionland_view::hit_test(point pt)
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
   for(int i = 0; i < m_notificationareainfo.m_infoa.GetSize(); i++)
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
   for(int i = 0; i < m_areaa[m_iArea].m_hwnda.GetSize(); i++)
   {
      GetAreaThumbRect(rectArea, m_iTaskOffset + i);
      if(rectArea.PtInRect(pt))
      {
         return m_iTaskOffset + i;
      }
   }
   return -1;
}

void definitionland_view::_001OnLButtonDown(gen::signal_object * pobj)
{
   SCAST_PTR(igui::win::message::mouse, pmouse, pobj)

   int iHitArea = hit_test(pmouse->m_pt);
   if(iHitArea >= 0 && !m_bShowCalendar && !m_bShutDown)
   {
      if(iHitArea < m_areaa.GetSize())
      {
      }
      else if(iHitArea >= m_iTaskOffset && iHitArea < (m_iTaskOffset + m_areaa[m_iArea].m_hwndaPreserve.GetSize()))
      {
         m_iDragTask = iHitArea;
         SetTimer(5432180, 400, NULL); // DragTask
      }
   }

}

void definitionland_view::_001OnLButtonUp(gen::signal_object * pobj)
{
   SCAST_PTR(igui::win::message::mouse, pmouse, pobj)
   KillTimer(5432180);

   int iHitArea = hit_test(pmouse->m_pt);
   if(m_bDragTask && !m_bShowCalendar && !m_bShutDown)
   {
      m_bDragTask = false;
      if(m_iDragTask >= m_iTaskOffset
      && m_iDragTask < m_iTaskOffset + m_areaa[m_iArea].m_hwndaPreserve.GetSize()
      && iHitArea >= 0
      && iHitArea < m_areaa.GetSize())
      {
         HWND hwnd = m_areaa[m_iArea].m_hwndaPreserve[m_iDragTask - m_iTaskOffset];
         return;
      }
   }
   if(iHitArea == m_iV)
   {

   }
   else if(iHitArea == m_iShutDown)
   {
      m_bShutDown = !m_bShutDown;
      _001RedrawWindow();
   }
   else if(iHitArea == m_iClockOffset)
   {
      ToggleShowCalendar();
   }
   else if(m_bShowCalendar)
   {
      switch(m_calendar.hit_test(pmouse->m_pt))
      {
      case calendar::ElementPreviousMonth:
         m_calendar.previous_month();
         _001RedrawWindow();
         break;
      case calendar::ElementNextMonth:
         m_calendar.next_month();
         _001RedrawWindow();
         break;
      case calendar::ElementNextYear:
         m_calendar.next_year();
         _001RedrawWindow();
         break;
      case calendar::ElementPreviousYear:
         m_calendar.previous_year();
         _001RedrawWindow();
         break;
      default:
         {
            CTime time;
            if(m_calendar.time_hit_test(time, pmouse->m_pt))
            {
               m_calendar.set_time(time);
               _001RedrawWindow();
            }
         }
         break;
      }
   }
   else if(iHitArea >= 0)
   {
      {
   /*      else if(iHitArea == m_iNotificationAreaButtonOffset)
         {
            m_notificationareainfo.Refresh();
            m_bNotificationArea = true;
         }*/
         if(iHitArea >= m_iNotificationAreaOffset && iHitArea < (m_iNotificationAreaOffset + m_notificationareainfo.m_infoa.GetSize()))
         {
            m_notificationareainfo.LeftClick(iHitArea - m_iNotificationAreaOffset);
            ::Sleep(100);
         }
         else if(iHitArea >= m_iClockOffset)
         {
            ToggleShowCalendar();
         }
         else if(iHitArea < m_areaa.GetSize())
         {
            m_dw3003Time = ::GetTickCount();
            SetTimer(3003, 300, NULL);
            
         }
         else if(iHitArea >= m_iTaskOffset && iHitArea < (m_iTaskOffset + m_areaa[m_iArea].m_hwndaPreserve.GetSize()))
         {
            m_iCurrentArea = iHitArea;
            m_dwCurrentAreaTime = ::GetTickCount();
            _001RedrawWindow();
            HWND hwnd = m_areaa[m_iArea].m_hwndaPreserve[iHitArea - m_iTaskOffset];
            if(::IsIconic(hwnd))
            {
               AfxBeginThread(ThreadProcShowWindow, new show_window(hwnd, SW_RESTORE, this));
            }
            else
            {
               if(hwnd != m_areaa[m_iArea].m_hwnda[0])
               {
                  AfxBeginThread(ThreadProcShowWindow, new show_window(hwnd, -1, this));
                  
               }
               else
               {
                  AfxBeginThread(ThreadProcShowWindow, new show_window(hwnd, SW_MINIMIZE, this));
               }
            }
            _001RedrawWindow();
            ::Sleep(100);
         }
      }
   }

}

void definitionland_view::_001OnRButtonUp(gen::signal_object * pobj)
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
   else if(iHitArea >= m_iTaskOffset 
        && iHitArea < m_iTaskOffset + m_areaa[m_iArea].m_hwndaPreserve.GetSize())
   {
      BaseWndMenu menu;
      menu.LoadMenu(::GetSystemMenu(GetParentFrame()->GetSafeHwnd(), FALSE));
      menu.set_app(get_app());
      menu.TrackPopupMenu(0, pmouse->m_pt.x, pmouse->m_pt.y, 
         m_areaa[m_iArea].m_hwndaPreserve[iHitArea - m_iTaskOffset]);
   }
   else if(iHitArea < 0)
   {
      BaseWndMenu menu;
      menu.LoadXmlMenu(get_app(), "definitionland\\popup_definitionland.xml");
      menu.set_app(get_app());
      BaseWndMenu menuPopup(menu.GetSubMenu(0));
      menuPopup.set_app(get_app());
      menuPopup.TrackPopupMenu(0, pmouse->m_pt.x, pmouse->m_pt.y, GetParentFrame()->GetSafeHwnd());
   }
   
}

void definitionland_view::_001OnOp(gen::signal_object * pobj)
{
   SCAST_PTR(igui::win::message::base, pbase, pobj)
   if(pbase->m_wparam == OpUpdateCurrentArea)
   {
   }
}


void definitionland_view::area::UpdatePreserve()
{
   bool bAutoDelete;
   for(int i = 0; i < m_hwndaPreserve.GetSize(); i++)
   {
      HWND hwnd = m_hwndaPreserve[i];
      HICON hicon16 = NULL;
      HICON hicon48 = NULL;
      HICON hicon16_1 = NULL;
      HICON hicon48_1 = NULL;
      HICON hicon_2 = NULL;
      if(!::SendMessageTimeout(hwnd, WM_GETICON, ICON_BIG, 0, SMTO_BLOCK, 10, (PDWORD_PTR) &hicon_2))
      {
         hicon48_1 = NULL;
      }
      if(!::SendMessageTimeout(hwnd, WM_GETICON, ICON_SMALL, 0, SMTO_BLOCK, 10, (PDWORD_PTR) &hicon_2))
      {
         hicon_2 = NULL;
      }
      bAutoDelete = false;
      if(hicon_2 == NULL)
      {
         hicon_2 = hicon48_1;
      }
      if(hicon_2 == NULL)
      {
         hicon_2 = (HICON)GetClassLong(hwnd, GCL_HICONSM);
      }
      if(hicon_2 == NULL)
      {
         hicon_2 = (HICON)GetClassLong(hwnd, GCL_HICON);
      }
      if(hicon_2 == NULL)
      {
         bAutoDelete = true;
         DWORD dwProcessId;
         char szFilename[1024];
         DWORD dwThreadId = ::GetWindowThreadProcessId(hwnd, &dwProcessId);
         HANDLE hprocess = (HANDLE) OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ , FALSE, dwProcessId);
         memset(szFilename, 0, sizeof(szFilename));
         ::GetModuleFileNameEx((HMODULE) hprocess, NULL, szFilename, sizeof(szFilename));
         string strFilename = szFilename;
         bool bPathCaption = strFilename.Right(13) == "\\explorer.exe";
         filemanager::_shell::ImageSet::GetIcon(m_pview->GetSafeHwnd(), szFilename, L"", filemanager::_shell::IconNormal, &hicon16, &hicon48);
         hicon_2 = hicon16;
         ::CloseHandle(hprocess);
      }
      
      gdi::Icon & icon = m_hicona[i];
      if(icon.m_bAutoDelete)
      {
         ::DestroyIcon(icon.m_hicon);
      }
      icon.m_hicon = hicon_2;
      icon.m_bAutoDelete = bAutoDelete;
      if(hicon48 != NULL)
      {
         ::DestroyIcon(hicon48);
      }
   }
restart:
   for(int i = 0; i < m_hwndaPreserve.GetSize(); i++)
   {
      if(m_hwnda.FindFirst(m_hwndaPreserve[i]) < 0)
      {
         op op;
         op.m_eop = op_delete;
         op.m_hwnd = m_hwndaPreserve[i];
         op.m_dwTime = ::GetTickCount() + 2000;
         m_opa.Add(op);
      }
   }
   for(int i = 0; i < m_hwnda.GetSize(); i++)
   {
      if(m_hwndaPreserve.FindFirst(m_hwnda[i]) < 0)
      {
         op op;
         op.m_eop = op_add;
         op.m_hwnd = m_hwnda[i];
         op.m_dwTime = ::GetTickCount() + 2000;
         m_opa.Add(op);
      }
   }
restart_cancel:
   for(int i = 0; i < m_opa.GetSize(); i++)
   {
      if(cancel_op(i, m_opa[i].m_eop, m_opa[i].m_hwnd))
      {
         goto restart_cancel;
      }
   }
restart_do:
   for(int i = 0; i < m_opa.GetSize(); i++)
   {
      if(defer_do_op(i))
         goto restart_do;
   }
}

bool definitionland_view::area::cancel_op(int iParam, e_op eop, HWND hwnd)
{
   bool bCancel = false;
   for(int i = 0; i < m_opa.GetSize(); i++)
   {
      if(i != iParam)
      {
         if(m_opa[i].m_hwnd == hwnd)
         {
            if(eop == op_delete && m_opa[i].m_eop == op_add
            || eop == op_add && m_opa[i].m_eop == op_delete)
            {
               bCancel = true;
            }
         }
      }
   }
   if(bCancel)
   {
      for(int i = 0; i < m_opa.GetSize();)
      {
         if(m_opa[i].m_hwnd == hwnd)
         {
            m_opa.RemoveAt(i);
         }
         else
         {
            i++;
         }
      }
   }
   return bCancel;
}

bool definitionland_view::area::defer_do_op(int i)
{
   if(m_opa[i].m_dwTime > ::GetTickCount())
   {
      if(m_opa[i].m_eop == op_delete)
      {
         int iRemove = m_hwndaPreserve.FindFirst(m_opa[i].m_hwnd);
         m_hwndaPreserve.RemoveAt(iRemove);
         m_hicona.RemoveAt(iRemove);
         m_opa.RemoveAt(i);
         m_baPathCaption.RemoveAt(i);
      }
      else if(m_opa[i].m_eop == op_add)
      {
         HWND hwnd = m_opa[i].m_hwnd;
         if(m_hwndaPreserve.FindFirst(hwnd) < 0)
         {
            gdi::Icon icon;
            icon.m_hicon = NULL;
            icon.m_bAutoDelete = false;
            m_hicona.Add(icon);
            m_hicona[m_hicona.GetUpperBound()].m_bAutoDelete = false;
            m_hwndaPreserve.Add(m_opa[i].m_hwnd);
            bool bPathCaption;
            {
               DWORD dwProcessId;
               char szFilename[1024];
               DWORD dwThreadId = ::GetWindowThreadProcessId(hwnd, &dwProcessId);
               HANDLE hprocess = (HANDLE) OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ , FALSE, dwProcessId);
               memset(szFilename, 0, sizeof(szFilename));
               ::GetModuleFileNameEx((HMODULE) hprocess, NULL, szFilename, sizeof(szFilename));
               string strFilename = szFilename;
               bPathCaption = strFilename.Right(13) == "\\explorer.exe";
               ::CloseHandle(hprocess);
            }
            m_baPathCaption.Add(bPathCaption);
         }
         m_opa.RemoveAt(i);
      }
      return true;
   }
   return false;
}

void definitionland_view::_001OnTimer(gen::signal_object * pobj)
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
      point pt;
      ::GetCursorPos(&pt);
      HWND hwnd = ::WindowFromPoint(pt);
      if(GetParentFrame()->GetSafeHwnd() != hwnd
         && !igui::WndUtil::IsAscendant(GetParentFrame()->GetSafeHwnd(), hwnd))
      {
      }
   }
}



BOOL CALLBACK definitionland_view::UpdateCurrentAreaEnumWindowsProc(      
    HWND hwnd,
    LPARAM lParam)
{
   definitionland_view * pview = (definitionland_view *) lParam;
   DWORD dwThreadId;
   DWORD dwProcessId;
   HICON hicon16;
   HICON hicon48;
   base_wnd * pwnd = base_wnd::FromHandle(hwnd);
   if(pwnd == NULL)
      return TRUE;
   //HICON hicon = pwnd->GetIcon(FALSE);
   //if(hicon == NULL)
   //{
      //hicon = pwnd->GetIcon(TRUE);
   //}
   int iStyle = pwnd->GetStyle();
   int iStyleEx = pwnd->GetExStyle();
   if(pwnd->GetSafeHwnd() != pview->GetParentFrame()->GetSafeHwnd()
     && (iStyle & WS_VISIBLE)
     && !(iStyleEx & WS_EX_TOOLWINDOW)
     &&((iStyleEx & WS_EX_APPWINDOW)
     || (!(iStyle & WS_CHILD)
     && pwnd->GetOwner() == NULL)))
   {
      if(!pview->m_areaa.Contains(pwnd->GetSafeHwnd(), pview->m_iArea))
         pview->m_areaa[pview->m_iArea].m_hwnda.Add(pwnd->GetSafeHwnd());
   }
   return TRUE;
}

UINT AFX_CDECL definitionland_view::ThreadProcShowWindow(LPVOID lpparam)
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

definitionland_view::show_window::show_window(HWND hwnd, int iShow, definitionland_view * pview)
{
   m_hwnd   = hwnd;
   m_iShow  = iShow;
   m_pview  = pview;
}



void definitionland_view::_001OnShowWindow(gen::signal_object * pobj) 
{
   SCAST_PTR(igui::win::message::show_window, pshowwindow, pobj)
}


bool definitionland_view::ShowCalendar(bool bShow)
{
   m_bShowCalendar = bShow;
   _001RedrawWindow();
   return m_bShowCalendar;
}

bool definitionland_view::ToggleShowCalendar()
{
   return ShowCalendar(!m_bShowCalendar);
}


bool definitionland_view::area_array::Contains(HWND hwnd, int iExcludeArea)
{
   for(int iArea = 0; iArea < GetSize(); iArea++)
   {
      if(iArea != iExcludeArea)
      {
         if(ElementAt(iArea).m_hwnda.FindFirst(hwnd) >= 0)
            return true;
      }
   }
   return false;
}



void definitionland_view::ensure_apps()
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
            International::Utf8ToUnicode(m_strWinactionarea),
            NULL,
            International::Utf8ToUnicode(ca2::app().dir().name(m_strWinactionarea)),
            SW_SHOW);*/
   }
   if(!::IsWindow(m_hwndCommand))
   {
      /*::ShellExecuteW(
            NULL, 
            NULL, 
            International::Utf8ToUnicode(m_strCommand),
            NULL,
            International::Utf8ToUnicode(ca2::app().dir().name(m_strCommand)),
            SW_SHOW);*/
   }
}


BOOL CALLBACK definitionland_view::GetAppsEnumWindowsProc(      
    HWND hwnd,
    LPARAM lParam)
{
   definitionland_view * pview = (definitionland_view *) lParam;
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


