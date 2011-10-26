#include "StdAfx.h"
#include "winshelllink_view.h"
#include "winshelllink_document.h"
#include <Psapi.h>

winshelllink_view::winshelllink_view(::ca::application * papp) :
   ca(papp),
   ::user::interaction(papp),
   ::userbase::view(papp),
   m_dibV(papp)
{
   m_brushBkActive.CreateSolidBrush(RGB(150, 255, 130));
   m_brushBkInactive.CreateSolidBrush(RGB(128, 208, 120));
   LOGFONT lf;
   memset(&lf, 0, sizeof(lf));

   strcpy(lf.lfFaceName, "Verdana");
   lf.lfHeight = 13;
   m_font.CreateFontIndirect(&lf);


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

winshelllink_view::~winshelllink_view()
{
}

void winshelllink_view::install_message_handling(::user::win::message::dispatch * pinterface)
{
   ::userbase::view::install_message_handling(pinterface);

	IGUI_WIN_MSG_LINK(WM_DESTROY, pinterface, this, &winshelllink_view::_001OnDestroy);
	IGUI_WIN_MSG_LINK(WM_SIZE, pinterface, this, &winshelllink_view::_001OnSize);
	IGUI_WIN_MSG_LINK(WM_PAINT, pinterface, this, &winshelllink_view::_001OnPaint);
	IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &winshelllink_view::_001OnCreate);
	IGUI_WIN_MSG_LINK(WM_CONTEXTMENU, pinterface, this, &winshelllink_view::_001OnContextMenu);
	IGUI_WIN_MSG_LINK(WM_SETCURSOR, pinterface, this, &winshelllink_view::_001OnSetCursor);

//   IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN, pinterface, this, &::user::interaction::_001OnLButtonDown);
  // IGUI_WIN_MSG_LINK(WM_LBUTTONUP, pinterface, this, &::user::interaction::_001OnLButtonUp);
   IGUI_WIN_MSG_LINK(WM_KEYDOWN, pinterface, this, &::user::interaction::_001OnKeyDown);
   IGUI_WIN_MSG_LINK(WM_KEYUP, pinterface, this, &::user::interaction::_001OnKeyUp);

   IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN, pinterface, this, &winshelllink_view::_001OnLButtonDown);
   IGUI_WIN_MSG_LINK(WM_LBUTTONUP, pinterface, this, &winshelllink_view::_001OnLButtonUp);
   IGUI_WIN_MSG_LINK(WM_RBUTTONUP, pinterface, this, &winshelllink_view::_001OnRButtonUp);
   IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &winshelllink_view::_001OnTimer);

   IGUI_WIN_MSG_LINK(MessageOp, pinterface, this, &winshelllink_view::_001OnOp);
   IGUI_WIN_MSG_LINK(WM_SHOWWINDOW, pinterface, this, &winshelllink_view::_001OnShowWindow);
   IGUI_WIN_MSG_LINK(WM_DESTROY, pinterface, this, &winshelllink_view::_001OnDestroy);

}
/////////////////////////////////////////////////////////////////////////////
// winshelllink_view drawing

void winshelllink_view::OnDraw(::ca::graphics * pdcScreen)
{
   UNREFERENCED_PARAMETER(pdcScreen);
}

/////////////////////////////////////////////////////////////////////////////
// winshelllink_view diagnostics

#ifdef _DEBUG
void winshelllink_view::assert_valid() const
{
	::userbase::view::assert_valid();
}

void winshelllink_view::dump(dump_context & dumpcontext) const
{
	::userbase::view::dump(dumpcontext);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// winshelllink_view message handlers

// vmpLightView.cpp : implementation of the winshelllink_view class
//


/////////////////////////////////////////////////////////////////////////////
// winshelllink_view


BOOL winshelllink_view::PreCreateWindow(CREATESTRUCT& cs)
{
   cs.lpszClass = Application.RegisterWndClass(
		CS_DBLCLKS |
		CS_OWNDC,
		0, 0, 0);
   cs.style &= ~WS_EX_CLIENTEDGE;
	return ::userbase::view::PreCreateWindow(cs);
}
void winshelllink_view::_001OnInitialUpdate(gen::signal_object * pobj) 
{
   ::userbase::view::_001OnInitialUpdate(pobj);
}


void winshelllink_view::on_update(::view* pSender, LPARAM lHint, ::radix::object* phint) 
{
   UNREFERENCED_PARAMETER(pSender);
   UNREFERENCED_PARAMETER(phint);
   if(lHint == 5432108)
   {
      SetTimer(5432108, 100, NULL);
   }
	
}

void winshelllink_view::_001OnDestroy(gen::signal_object * pobj) 
{
	::userbase::view::_001OnDestroy(pobj);
}



void winshelllink_view::_001OnSize(gen::signal_object * pobj) 
{
   UNREFERENCED_PARAMETER(pobj);
//   SCAST_PTR(::user::win::message::size, psize, pobj)

   rect rectDesktop;
   Application.get_screen_rect(rectDesktop);

   m_iWScreen = rectDesktop.width();
   m_iHScreen = rectDesktop.height();
   rect rectClient;
   GetClientRect(rectClient);
   rectClient.deflate(2, 2);
   int iW = rectClient.width() / 2;
   int iH = rectClient.height() / 2;
   iH = min(iH, 120);
   double r = (double) iW / (double) iH;
   double rScreen = (double) rectDesktop.width() / (double) rectDesktop.height();
   if(r < rScreen)
   {
      iH = (int) (iW / rScreen);
   }
   else if(r > rScreen)
   {
      iW = (int) (iH * rScreen);
   }
   m_iW = iW;
   m_iH = iH;
}

void winshelllink_view::_001OnPaint(gen::signal_object * pobj) 
{
   UNREFERENCED_PARAMETER(pobj);
	//CPaintDC spgraphics(this); // device context for winshelllinking
   //spgraphics->TextOut(20, 20, "Carlos Gustavo Cecyn Lundgren é minha Vida Eterna, meu Coração Eterno, Todo meu tesouro eterno, meu Universo eterno, meu tudo eterno!!");
}


void winshelllink_view:: _001OnDraw(::ca::graphics * pdc)
{
   UNREFERENCED_PARAMETER(pdc);
}

void winshelllink_view::_001OnCreate(gen::signal_object * pobj) 
{
   if(pobj->previous())
      return;
   SetTimer(3003, 300, NULL);
   SetTimer(543218, 1000, NULL);
   
}


void winshelllink_view::_001OnContextMenu(gen::signal_object * pobj) 
{
   SCAST_PTR(::user::win::message::context_menu, pcontextmenu, pobj)
   point point = pcontextmenu->GetPoint();
}


void winshelllink_view::_001OnTabClick(int iTab)
{
   if(iTab == 1)
   {
      Application.simple_message_box(NULL, "Playlist");
   }
}

void winshelllink_view::_001OnSetCursor(gen::signal_object * pobj) 
{
   ::SetCursor(::LoadCursor(NULL, IDC_ARROW));
	
	pobj->previous();
}

winshelllink_document * winshelllink_view::get_document()
{
   return dynamic_cast < winshelllink_document * > (::userbase::view::get_document());
}

/*
void winshelllink_view::Snapshot()
{
   int iArea = m_iArea;
   SwitchArea(0);
   SwitchArea(1);
   SwitchArea(2);
   SwitchArea(3);
   SwitchArea(iArea);
}
*/

int winshelllink_view::hit_test(point pt)
{
   UNREFERENCED_PARAMETER(pt);
/*   GetAreaThumbRect(rectArea, m_iNotificationAreaButtonOffset);
   if(rectArea.contains(pt))
   {
      return m_iNotificationAreaButtonOffset;
   }*/
   return -1;
}

void winshelllink_view::_001OnLButtonDown(gen::signal_object * pobj)
{
   UNREFERENCED_PARAMETER(pobj);
//   SCAST_PTR(::user::win::message::mouse, pmouse, pobj)


}

void winshelllink_view::_001OnLButtonUp(gen::signal_object * pobj)
{
   UNREFERENCED_PARAMETER(pobj);
   ///SCAST_PTR(::user::win::message::mouse, pmouse, pobj)
   KillTimer(5432180);


}

void winshelllink_view::_001OnRButtonUp(gen::signal_object * pobj)
{
   UNREFERENCED_PARAMETER(pobj);
   //SCAST_PTR(::user::win::message::mouse, pmouse, pobj)

   
}

void winshelllink_view::_001OnOp(gen::signal_object * pobj)
{
   UNREFERENCED_PARAMETER(pobj);
   //SCAST_PTR(::user::win::message::base, pbase, pobj)
}


void winshelllink_view::area::UpdatePreserve()
{
   bool bAutoDelete;
   for(int i = 0; i < m_hwndaPreserve.get_size(); i++)
   {
      HWND hwnd = m_hwndaPreserve[i];
      HICON hicon16 = NULL;
      HICON hicon48 = NULL;
//      HICON hicon16_1 = NULL;
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
#ifdef X86
         hicon_2 = (HICON)GetClassLong(hwnd, GCL_HICONSM);
#endif
      }
      if(hicon_2 == NULL)
      {
#ifdef X86
         hicon_2 = (HICON)GetClassLong(hwnd, GCL_HICON);
#endif
      }
      if(hicon_2 == NULL)
      {
         bAutoDelete = true;
         DWORD dwProcessId;
         char szFilename[1024];
         ::GetWindowThreadProcessId(hwnd, &dwProcessId);
         HANDLE hprocess = (HANDLE) OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ , FALSE, dwProcessId);
         memset(szFilename, 0, sizeof(szFilename));
         ::GetModuleFileNameEx((HMODULE) hprocess, NULL, szFilename, sizeof(szFilename));
         string strFilename = szFilename;
//         bool bPathCaption = strFilename.Right(13) == "\\explorer.exe";
         Application.shellimageset().GetIcon(m_pview->GetTopLevelParent()->_get_handle(), szFilename, L"", filemanager::_shell::IconNormal, &hicon16, &hicon48);
         hicon_2 = hicon16;
         ::CloseHandle(hprocess);
      }
      
      visual::icon & icon = m_hicona[i];
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
//restart:
   for(int i = 0; i < m_hwndaPreserve.get_size(); i++)
   {
      if(!m_hwnda.contains(m_hwndaPreserve[i]))
      {
         op op;
         op.m_eop = op_delete;
         op.m_hwnd = m_hwndaPreserve[i];
         op.m_dwTime = ::GetTickCount() + 2000;
         m_opa.add(op);
      }
   }
   for(int i = 0; i < m_hwnda.get_size(); i++)
   {
      if(!m_hwndaPreserve.contains(m_hwnda[i]))
      {
         op op;
         op.m_eop = op_add;
         op.m_hwnd = m_hwnda[i];
         op.m_dwTime = ::GetTickCount() + 2000;
         m_opa.add(op);
      }
   }
restart_cancel:
   for(int i = 0; i < m_opa.get_size(); i++)
   {
      if(cancel_op(i, m_opa[i].m_eop, m_opa[i].m_hwnd))
      {
         goto restart_cancel;
      }
   }
restart_do:
   for(int i = 0; i < m_opa.get_size(); i++)
   {
      if(defer_do_op(i))
         goto restart_do;
   }
}

bool winshelllink_view::area::cancel_op(int iParam, e_op eop, HWND hwnd)
{
   bool bCancel = false;
   for(int i = 0; i < m_opa.get_size(); i++)
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
      for(int i = 0; i < m_opa.get_size();)
      {
         if(m_opa[i].m_hwnd == hwnd)
         {
            m_opa.remove_at(i);
         }
         else
         {
            i++;
         }
      }
   }
   return bCancel;
}

bool winshelllink_view::area::defer_do_op(int i)
{
   if(m_opa[i].m_dwTime > ::GetTickCount())
   {
      if(m_opa[i].m_eop == op_delete)
      {
         int iRemove = m_hwndaPreserve.find_first(m_opa[i].m_hwnd);
         m_hwndaPreserve.remove_at(iRemove);
         m_hicona.remove_at(iRemove);
         m_opa.remove_at(i);
         m_baPathCaption.remove_at(i);
      }
      else if(m_opa[i].m_eop == op_add)
      {
         HWND hwnd = m_opa[i].m_hwnd;
         if(!m_hwndaPreserve.contains(hwnd))
         {
            visual::icon icon;
            icon.m_hicon = NULL;
            icon.m_bAutoDelete = false;
            m_hicona.add(icon);
            m_hicona[m_hicona.get_upper_bound()].m_bAutoDelete = false;
            m_hwndaPreserve.add(m_opa[i].m_hwnd);
            bool bPathCaption;
            {
               DWORD dwProcessId;
               char szFilename[1024];
               ::GetWindowThreadProcessId(hwnd, &dwProcessId);
               HANDLE hprocess = (HANDLE) OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ , FALSE, dwProcessId);
               memset(szFilename, 0, sizeof(szFilename));
               ::GetModuleFileNameEx((HMODULE) hprocess, NULL, szFilename, sizeof(szFilename));
               string strFilename = szFilename;
               bPathCaption = strFilename.Right(13) == "\\explorer.exe";
               ::CloseHandle(hprocess);
            }
            m_baPathCaption.add(bPathCaption);
         }
         m_opa.remove_at(i);
      }
      return true;
   }
   return false;
}

void winshelllink_view::_001OnTimer(gen::signal_object * pobj)
{
   SCAST_PTR(::user::win::message::timer, ptimer, pobj)
   if(ptimer->m_nIDEvent == 543218)
   {
      if(IsWindowVisible())
      {
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
      Application.get_cursor_pos(&pt);
//      HWND hwnd = ::WindowFromPoint(pt);
   }
}


UINT AFX_CDECL winshelllink_view::ThreadProcShowWindow(LPVOID lpparam)
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

winshelllink_view::show_window::show_window(HWND hwnd, int iShow, winshelllink_view * pview)
{
   m_hwnd   = hwnd;
   m_iShow  = iShow;
   m_pview  = pview;
}



void winshelllink_view::_001OnShowWindow(gen::signal_object * pobj) 
{
   UNREFERENCED_PARAMETER(pobj);
//   SCAST_PTR(::user::win::message::show_window, pshowwindow, pobj)
}



