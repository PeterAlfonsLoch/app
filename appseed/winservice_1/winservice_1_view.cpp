#include "StdAfx.h"
#include <Psapi.h>

winservice_1_view::winservice_1_view(::ca::application * papp)
: uie(papp)
{
}

winservice_1_view::~winservice_1_view()
{
}

void winservice_1_view::_001InstallMessageHandling(igui::win::message::Dispatch * pinterface)
{
   BaseView::_001InstallMessageHandling(pinterface);

	IGUI_WIN_MSG_LINK(WM_DESTROY, pinterface, this, &winservice_1_view::_001OnDestroy);
	IGUI_WIN_MSG_LINK(WM_SIZE, pinterface, this, &winservice_1_view::_001OnSize);
	IGUI_WIN_MSG_LINK(WM_PAINT, pinterface, this, &winservice_1_view::_001OnPaint);
	IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &winservice_1_view::_001OnCreate);
	IGUI_WIN_MSG_LINK(WM_CONTEXTMENU, pinterface, this, &winservice_1_view::_001OnContextMenu);
	IGUI_WIN_MSG_LINK(WM_SETCURSOR, pinterface, this, &winservice_1_view::_001OnSetCursor);
	IGUI_WIN_MSG_LINK(WM_ERASEBKGND, pinterface, this, &winservice_1_view::_001OnEraseBkgnd);

//   IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN, pinterface, this, &uie::_001OnLButtonDown);
  // IGUI_WIN_MSG_LINK(WM_LBUTTONUP, pinterface, this, &uie::_001OnLButtonUp);
   IGUI_WIN_MSG_LINK(WM_KEYDOWN, pinterface, this, &uie::_001OnKeyDown);
   IGUI_WIN_MSG_LINK(WM_KEYUP, pinterface, this, &uie::_001OnKeyUp);
   IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &uie::_001OnTimer);

   IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN, pinterface, this, &winservice_1_view::_001OnLButtonDown);
   IGUI_WIN_MSG_LINK(WM_LBUTTONUP, pinterface, this, &winservice_1_view::_001OnLButtonUp);
   IGUI_WIN_MSG_LINK(WM_RBUTTONUP, pinterface, this, &winservice_1_view::_001OnRButtonUp);
   IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &winservice_1_view::_001OnTimer);

   IGUI_WIN_MSG_LINK(MessageOp, pinterface, this, &winservice_1_view::_001OnOp);
   IGUI_WIN_MSG_LINK(WM_SHOWWINDOW, pinterface, this, &winservice_1_view::_001OnShowWindow);

}
/////////////////////////////////////////////////////////////////////////////
// winservice_1_view drawing

void winservice_1_view::OnDraw(CDC* pdcScreen)
{
}

/////////////////////////////////////////////////////////////////////////////
// winservice_1_view diagnostics

#ifdef _DEBUG
void winservice_1_view::AssertValid() const
{
	BaseView::AssertValid();
}

void winservice_1_view::Dump(CDumpContext& dc) const
{
	BaseView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// winservice_1_view message handlers

// vmpLightView.cpp : implementation of the winservice_1_view class
//


/////////////////////////////////////////////////////////////////////////////
// winservice_1_view


BOOL winservice_1_view::PreCreateWindow(CREATESTRUCT& cs)
{
   cs.lpszClass = AfxRegisterWndClass(
		CS_DBLCLKS |
		CS_OWNDC,
		0, 0, 0);
   cs.style &= ~WS_EX_CLIENTEDGE;
	return BaseView::PreCreateWindow(cs);
}
void winservice_1_view::_001OnInitialUpdate(gen::signal_object * pobj) 
{
   BaseView::_001OnInitialUpdate(pobj);
}

uie * winservice_1_view::get_guie()
{
   return this;
}

void winservice_1_view::OnUpdate(BaseView* pSender, LPARAM lHint, base_object* phint) 
{
   if(lHint == 5432108)
   {
      SetTimer(5432108, 100, NULL);
   }
	
}

uie * winservice_1_view::BackViewGetWnd()
{
   return this;
}

void winservice_1_view::_001OnDestroy(gen::signal_object * pobj) 
{
	BaseView::_001OnDestroy(pobj);

}



void winservice_1_view::_001OnSize(gen::signal_object * pobj) 
{
   SCAST_PTR(igui::win::message::size, psize, pobj)

   rect rectDesktop;
   HWND hwndDesktop = ::GetDesktopWindow();
   ::GetWindowRect(hwndDesktop, rectDesktop);

   rect rectClient;
   GetClientRect(rectClient);
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
}

void winservice_1_view::_001OnPaint(gen::signal_object * pobj) 
{
//	CPaintDC dc(this); // device context for winactionareaing
 //  dc.TextOut(20, 20, "Carlos Gustavo Cecyn Lundgren é minha Vida Eterna, meu Coração Eterno, Todo meu tesouro eterno, meu Universo eterno, meu tudo eterno!!");
}


void winservice_1_view:: _001OnDraw(CDC * pdc)
{
}

void winservice_1_view::_001OnCreate(gen::signal_object * pobj) 
{
   if(pobj->previous())
      return;
   SetTimer(543218, 1000, NULL);
}


void winservice_1_view::_001OnContextMenu(gen::signal_object * pobj) 
{
   SCAST_PTR(igui::win::message::context_menu, pcontextmenu, pobj)
   point point = pcontextmenu->GetPoint();
}


void winservice_1_view::_001OnTabClick(int iTab)
{
   if(iTab == 1)
   {
      Application.simple_message_box("Playlist");
   }
}

void winservice_1_view::_001OnSetCursor(gen::signal_object * pobj) 
{
   ::SetCursor(::LoadCursor(NULL, IDC_ARROW));
	
	pobj->previous();
}
void winservice_1_view::_001OnEraseBkgnd(gen::signal_object * pobj) 
{
   SCAST_PTR(igui::win::message::erase_bkgnd, perasebkgnd, pobj)
   perasebkgnd->m_bRet = true;
   perasebkgnd->set_result(TRUE);
}



winservice_1_document * winservice_1_view::get_document()
{
   return dynamic_cast < winservice_1_document * > (BaseView::get_document());
}



void winservice_1_view::_001OnLButtonDown(gen::signal_object * pobj)
{
   SCAST_PTR(igui::win::message::mouse, pmouse, pobj)

}

void winservice_1_view::_001OnLButtonUp(gen::signal_object * pobj)
{
   SCAST_PTR(igui::win::message::mouse, pmouse, pobj)
   KillTimer(5432180);


}

void winservice_1_view::_001OnRButtonUp(gen::signal_object * pobj)
{
   SCAST_PTR(igui::win::message::mouse, pmouse, pobj)

}

void winservice_1_view::_001OnOp(gen::signal_object * pobj)
{
   SCAST_PTR(igui::win::message::base, pbase, pobj)
}


void winservice_1_view::_001OnTimer(gen::signal_object * pobj)
{
   SCAST_PTR(igui::win::message::timer, ptimer, pobj)
}

void winservice_1_view::GetDateTime(string & strDateTime)
{
   CTime time = CTime::GetCurrentTime();
   string strDate;
   string strWeekDay;
   string strTime;
   strDate.Format(
      "%04d-%02d-%02d",
      time.GetYear(),
      time.GetMonth(),
      time.GetDay());
   switch(time.GetDayOfWeek())
   {
   case 1:
      strWeekDay = "domingo";
      break;
   case 2:
      strWeekDay = "segunda-feira";
      break;
   case 3:
      strWeekDay = "terça-feira";
      break;
   case 4:
      strWeekDay = "quarta-feira";
      break;
   case 5:
      strWeekDay = "quinta-feira";
      break;
   case 6:
      strWeekDay = "sexta-feira";
      break;
   case 7:
      strWeekDay = "sábado";
      break;
   }
   strTime.Format("%02d:%02d:%02d",
      time.GetHour(),
      time.GetMinute(),
      time.GetSecond());
   strDateTime.Format("%s %s %s", strDate, strWeekDay, strTime);
}

void winservice_1_view::_001OnShowWindow(gen::signal_object * pobj) 
{
   SCAST_PTR(igui::win::message::show_window, pshowwindow, pobj)
}
