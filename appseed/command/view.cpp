#include "StdAfx.h"


command_view::command_view(::ca::application * papp) :
   ca(papp),
   ::user::interaction(papp),
   ::userbase::view(papp)
{
}

command_view::~command_view()
{
}

void command_view::_001InstallMessageHandling(::user::win::message::dispatch * pinterface)
{
   ::userbase::view::_001InstallMessageHandling(pinterface);

	IGUI_WIN_MSG_LINK(WM_DESTROY, pinterface, this, &command_view::_001OnDestroy);
	IGUI_WIN_MSG_LINK(WM_SIZE, pinterface, this, &command_view::_001OnSize);
	IGUI_WIN_MSG_LINK(WM_PAINT, pinterface, this, &command_view::_001OnPaint);
	IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &command_view::_001OnCreate);
	IGUI_WIN_MSG_LINK(WM_CONTEXTMENU, pinterface, this, &command_view::_001OnContextMenu);
	IGUI_WIN_MSG_LINK(WM_SETCURSOR, pinterface, this, &command_view::_001OnSetCursor);

//   IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN, pinterface, this, &::user::interaction::_001OnLButtonDown);
   //IGUI_WIN_MSG_LINK(WM_LBUTTONUP, pinterface, this, &::user::interaction::_001OnLButtonUp);
   IGUI_WIN_MSG_LINK(WM_KEYDOWN, pinterface, this, &::user::interaction::_001OnKeyDown);
   IGUI_WIN_MSG_LINK(WM_KEYUP, pinterface, this, &::user::interaction::_001OnKeyUp);
   
   IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN, pinterface, this, &command_view::_001OnLButtonDown);
   IGUI_WIN_MSG_LINK(WM_LBUTTONUP, pinterface, this, &command_view::_001OnLButtonUp);
   IGUI_WIN_MSG_LINK(WM_RBUTTONUP, pinterface, this, &command_view::_001OnRButtonUp);
   IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &command_view::_001OnTimer);

   IGUI_WIN_MSG_LINK(MessageOp, pinterface, this, &command_view::_001OnOp);
   IGUI_WIN_MSG_LINK(WM_SHOWWINDOW, pinterface, this, &command_view::_001OnShowWindow);




}
/////////////////////////////////////////////////////////////////////////////
// command_view drawing

void command_view::OnDraw(::ca::graphics * pdcScreen)
{
   UNREFERENCED_PARAMETER(pdcScreen);
}

/////////////////////////////////////////////////////////////////////////////
// command_view diagnostics

#ifdef _DEBUG
void command_view::assert_valid() const
{
	::userbase::view::assert_valid();
}

void command_view::dump(dump_context & dumpcontext) const
{
	::userbase::view::dump(dumpcontext);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// command_view message handlers

// vmpLightView.cpp : implementation of the command_view class
//


/////////////////////////////////////////////////////////////////////////////
// command_view


BOOL command_view::PreCreateWindow(CREATESTRUCT& cs)
{
   cs.lpszClass = Application.RegisterWndClass(
		CS_DBLCLKS |
		CS_OWNDC,
		0, 0, 0);
   cs.style &= ~WS_EX_CLIENTEDGE;
	return ::userbase::view::PreCreateWindow(cs);
}
void command_view::_001OnInitialUpdate(gen::signal_object * pobj) 
{
   ::userbase::view::_001OnInitialUpdate(pobj);
}


void command_view::on_update(::view* pSender, LPARAM lHint, ::radix::object* phint) 
{
   UNREFERENCED_PARAMETER(pSender);
   UNREFERENCED_PARAMETER(phint);
   if(lHint == 5432108)
   {
      SetTimer(5432108, 100, NULL);
   }
	
}

void command_view::_001OnDestroy(gen::signal_object * pobj) 
{
	::userbase::view::_001OnDestroy(pobj);
}

void command_view::_001OnSize(gen::signal_object * pobj) 
{
//   SCAST_PTR(::user::win::message::size, psize, pobj)

   rect rectDesktop;
   Application.get_screen_rect(rectDesktop);

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
}

void command_view::_001OnPaint(gen::signal_object * pobj) 
{
   UNREFERENCED_PARAMETER(pobj);
//	CPaintDC spgraphics(this); // device context for winactionareaing
  // spgraphics->TextOut(20, 20, "Carlos Gustavo Cecyn Lundgren é minha Vida Eterna, meu Coração Eterno, Todo meu tesouro eterno, meu Universo eterno, meu tudo eterno!!");
}


void command_view:: _001OnDraw(::ca::graphics * pdc)
{
   UNREFERENCED_PARAMETER(pdc);
}

void command_view::_001OnCreate(gen::signal_object * pobj) 
{
   if(pobj->previous())
      return;
   SetTimer(543218, 1000, NULL);
}


void command_view::_001OnContextMenu(gen::signal_object * pobj) 
{
   SCAST_PTR(::user::win::message::context_menu, pcontextmenu, pobj)
   point point = pcontextmenu->GetPoint();


}


void command_view::_001OnTabClick(int iTab)
{
   if(iTab == 1)
   {
      Application.simple_message_box(NULL, "Playlist");
   }
}

void command_view::_001OnSetCursor(gen::signal_object * pobj) 
{
   ::SetCursor(::LoadCursor(NULL, IDC_ARROW));
	
	pobj->previous();
}

command_document * command_view::get_document()
{
   return dynamic_cast < command_document * > (::userbase::view::get_document());
}



void command_view::_001OnLButtonDown(gen::signal_object * pobj)
{
//   SCAST_PTR(::user::win::message::mouse, pmouse, pobj)
   UNREFERENCED_PARAMETER(pobj);

}

void command_view::_001OnLButtonUp(gen::signal_object * pobj)
{
   //SCAST_PTR(::user::win::message::mouse, pmouse, pobj)
   UNREFERENCED_PARAMETER(pobj);
   KillTimer(5432180);


}

void command_view::_001OnRButtonUp(gen::signal_object * pobj)
{
   //SCAST_PTR(::user::win::message::mouse, pmouse, pobj)
   UNREFERENCED_PARAMETER(pobj);

}

void command_view::_001OnOp(gen::signal_object * pobj)
{
   //SCAST_PTR(::user::win::message::base, pbase, pobj)
   UNREFERENCED_PARAMETER(pobj);
}


void command_view::_001OnTimer(gen::signal_object * pobj)
{
   //SCAST_PTR(::user::win::message::timer, ptimer, pobj)
   UNREFERENCED_PARAMETER(pobj);
}

void command_view::GetDateTime(string & strDateTime)
{
   class time time = time::get_current_time();
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

void command_view::_001OnShowWindow(gen::signal_object * pobj) 
{
//   SCAST_PTR(::user::win::message::show_window, pshowwindow, pobj)
   UNREFERENCED_PARAMETER(pobj);
}




