#include "StdAfx.h"
#include "front_view.h"
#include "front_document.h"


front_view::front_view(::ca::application * papp) :
   ::user::interaction(papp),
   ::userbase::view(papp),
   ::user::scroll_view(papp),
   ::userbase::scroll_view(papp),
   ::user::form(papp),
   ::userbase::form_view(papp),
   html_form(papp),
   html_view(papp)
{
   m_pkeyboardfocus = NULL;
   m_pelementMouseDown = NULL;
}

front_view::~front_view()
{
}

void front_view::install_message_handling(::user::win::message::dispatch * pinterface)
{
   html_view::install_message_handling(pinterface);

   IGUI_WIN_MSG_LINK(WM_DESTROY, pinterface, this, &front_view::_001OnDestroy);
   IGUI_WIN_MSG_LINK(WM_SIZE, pinterface, this, &front_view::_001OnSize);
   IGUI_WIN_MSG_LINK(WM_PAINT, pinterface, this, &front_view::_001OnPaint);
   IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &front_view::_001OnCreate);
   IGUI_WIN_MSG_LINK(WM_CONTEXTMENU, pinterface, this, &front_view::_001OnContextMenu);
   IGUI_WIN_MSG_LINK(WM_SETCURSOR, pinterface, this, &front_view::_001OnSetCursor);
   IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &front_view::_001OnTimer);
   IGUI_WIN_MSG_LINK(WM_USER + 101     , pinterface, this, &front_view::_001OnPost);

//   IGUI_WIN_MSG_LINK(WM_USER + 177     , this, this, &front_view::_001OnTabClick);
   IGUI_WIN_MSG_LINK(WM_APP + 119      , pinterface, this, &front_view::_001OnWavePlayerEvent);
 //  IGUI_WIN_MSG_LINK(WM_CHAR, pinterface, this, &front_view::_001OnChar);
   //IGUI_WIN_MSG_LINK(WM_SYSCHAR, pinterface, this, &front_view::_001OnSysChar);
   //connect_command(ID_FILE_PRINT, html_view::OnFilePrint)
   //connect_command(ID_FILE_PRINT_DIRECT, html_view::OnFilePrint)
   //connect_command(ID_FILE_PRINT_PREVIEW, html_view::OnFilePrintPreview)

   IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN, 
      pinterface,
      this,
      &front_view::_001OnLButtonDown);
   IGUI_WIN_MSG_LINK(WM_LBUTTONUP, 
      pinterface,
      this,
      &front_view::_001OnLButtonUp);
   IGUI_WIN_MSG_LINK(WM_MOUSEMOVE, 
      pinterface,
      this,
      &front_view::_001OnMouseMove);
   IGUI_WIN_MSG_LINK(WM_KEYDOWN, 
      pinterface,
      this,
      &front_view::_001OnKeyDown);
   IGUI_WIN_MSG_LINK(WM_KEYUP, 
      pinterface,
      this,
      &front_view::_001OnKeyUp);

}

#ifdef _DEBUG
void front_view::assert_valid() const
{
   html_view::assert_valid();
}

void front_view::dump(dump_context & dumpcontext) const
{
   html_view::dump(dumpcontext);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// front_view message handlers

// vmpLightView.cpp : implementation of the front_view class
//


/////////////////////////////////////////////////////////////////////////////
// front_view


BOOL front_view::PreCreateWindow(CREATESTRUCT& cs)
{
   cs.lpszClass = System.RegisterWndClass(
      CS_DBLCLKS |
      CS_OWNDC,
      0, 0, 0);
   cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
   cs.style &= ~WS_BORDER;
   return html_view::PreCreateWindow(cs);
}
void front_view::_001OnInitialUpdate(gen::signal_object * pobj) 
{
   html_view::_001OnInitialUpdate(pobj);


   
}

void front_view::on_update(::view* pSender, LPARAM lHint, ::radix::object* phint) 
{
   UNREFERENCED_PARAMETER(pSender);
   UNREFERENCED_PARAMETER(phint);
   if(lHint == 1001)
   {
      _001RedrawWindow();
   }

   
}

void front_view::_001OnDestroy(gen::signal_object * pobj) 
{
   html_view::_001OnDestroy(pobj);

}



void front_view::_001OnSize(gen::signal_object * pobj) 
{
   UNREFERENCED_PARAMETER(pobj);
//   SCAST_PTR(::user::win::message::size, psize, pobj)
   //biteditor_document * pdoc = get_document();
}

void front_view::_001OnPaint(gen::signal_object * pobj) 
{
   UNREFERENCED_PARAMETER(pobj);
   //CPaintDC spgraphics(this); // device context for painting
   

   //spgraphics->TextOut(20, 20, "Carlos Gustavo Cecyn Lundgren ・minha Vida Eterna, meu Cora鈬o Eterno, Todo meu tesouro eterno, meu Universo eterno, meu tudo eterno!!");
}


void front_view:: _001OnDraw(::ca::graphics * pdc)
{

   pdc->OffsetViewportOrg(-2, -2);
    //CFileSpec fsDest(szDestFilename);
    //CBitmapDC destDC(srcSize.cx, srcSize.cy);

}

void front_view::_001OnCreate(gen::signal_object * pobj) 
{
   if(pobj->previous())
      return;

   SetTimer(100, 100, NULL);
   
   PostMessage(WM_USER + 101, 101, 1);



   /*biteditor_document * pdoc = get_document();
   for(int i = 0; i < pdoc->m_elementptraVisible.get_size(); i++)
   {
      IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN, 
         this,
         pdoc->m_elementptraVisible[i],
         &biteditor::Element2D::_001OnLButtonDown);
      IGUI_WIN_MSG_LINK(WM_LBUTTONUP, 
         this,
         pdoc->m_elementptraVisible[i],
         &biteditor::Element2D::_001OnLButtonUp);
   }*/

}
void front_view::_001OnContextMenu(gen::signal_object * pobj) 
{
   SCAST_PTR(::user::win::message::context_menu, pcontextmenu, pobj)
   point point = pcontextmenu->GetPoint();
   
}



void front_view::_001OnWavePlayerEvent(gen::signal_object * pobj)
{
//   SCAST_PTR(::user::win::message::base, pbase, pobj)
   UNREFERENCED_PARAMETER(pobj);
}

void front_view::_001OnUpdateViewEncoding(gen::signal_object * pobj)
{
   //SCAST_PTR(::user::win::message::update_cmd_ui, pupdatecmdui, pobj)
   UNREFERENCED_PARAMETER(pobj);
}
void front_view::_001OnViewEncoding(gen::signal_object * pobj)
{
   //SCAST_PTR(::user::win::message::command, pcommand, pobj)
   UNREFERENCED_PARAMETER(pobj);
}

void front_view::_001OnSetCursor(gen::signal_object * pobj) 
{
   ::SetCursor(::LoadCursor(NULL, IDC_ARROW));
   
   pobj->previous();
}

void front_view::_001OnLButtonDown(gen::signal_object * pobj) 
{
   SCAST_PTR(::user::win::message::mouse, pmouse, pobj)
   point pt = pmouse->m_pt;
}

void front_view::_001OnLButtonUp(gen::signal_object * pobj) 
{
   SCAST_PTR(::user::win::message::mouse, pmouse, pobj)
   point pt = pmouse->m_pt;
}

void front_view::_001OnMouseMove(gen::signal_object * pobj) 
{
   SCAST_PTR(::user::win::message::mouse, pmouse, pobj)
   point pt = pmouse->m_pt;
}

biteditor_document * front_view::get_document() const
{
   return (biteditor_document *) ::userbase::view::get_document();
}

biteditor::Element2D * front_view::hit_test(int x, int y)
{
   UNREFERENCED_PARAMETER(x);
   UNREFERENCED_PARAMETER(y);
   //biteditor_document * pdoc = get_document();
   return NULL;
}

void front_view::_001OnTimer(gen::signal_object * pobj) 
{
   SCAST_PTR(::user::win::message::timer, ptimer, pobj)
   if(ptimer->m_nIDEvent >= 100 
      && ptimer->m_nIDEvent <= 200)
   {
   }
   else if(ptimer->m_nIDEvent == 500 || ptimer->m_nIDEvent == 501 )
   {
      if(ptimer->m_nIDEvent == 500)
      {
         KillTimer(500);
         SetTimer(501, 300, NULL);
      }
      key_to_char(m_dwLastKeyWparam, m_dwLastKeyLparam);
   }

}

void front_view::_001OnKeyDown(gen::signal_object * pobj) 
{
   SCAST_PTR(::user::win::message::key, pkey, pobj)
   m_dwLastKeyWparam = pkey->m_wparam;
   m_dwLastKeyLparam = pkey->m_lparam;
   key_to_char(m_dwLastKeyWparam, m_dwLastKeyLparam);
   SetTimer(500, 500, NULL);
}

void front_view::_001OnKeyUp(gen::signal_object * pobj) 
{
//   SCAST_PTR(::user::win::message::key, pkey, pobj)
   UNREFERENCED_PARAMETER(pobj);
   KillTimer(500);
   KillTimer(501);
}


void front_view::_001OnChar(gen::signal_object * pobj) 
{
   SCAST_PTR(::user::win::message::key, pkey, pobj)
   if(pkey->m_nChar == 's')
   {
      if(::GetKeyState(VK_CONTROL) & 0x80000000)
      {
         return;
      }
   }
}


void front_view::_001OnSysChar(gen::signal_object * pobj) 
{
//   SCAST_PTR(::user::win::message::key, pkey, pobj)
   UNREFERENCED_PARAMETER(pobj);
}


/*
BOOL front_view::pre_translate_message(gen::signal_object * pobj)
{
   if(pMsg->hwnd == GetSafeHwnd())
   {
      if(pMsg->message == WM_KEYDOWN)
      {
         ::user::win::message::key key;
         LRESULT lresult;
         key.set(pMsg->message, pMsg->wParam, pMsg->lParam, lresult);
         _001OnKeyDown(&key);
         return TRUE;
      }
      else if(pMsg->message == WM_KEYUP)
      {
         ::user::win::message::key key;
         LRESULT lresult;
         key.set(pMsg->message, pMsg->wParam, pMsg->lParam, lresult);
         _001OnKeyUp(&key);
         return TRUE;
      }
   }
   return html_view::pre_translate_message(pMsg);
}
*/

void front_view::key_to_char(WPARAM wparam, LPARAM lparam)
{
   UNREFERENCED_PARAMETER(lparam);

   ::user::win::message::key key(get_app());

   if(wparam == VK_LSHIFT || wparam == VK_RSHIFT
      || wparam == VK_LCONTROL || wparam == VK_RCONTROL
      || wparam == VK_LMENU || wparam == VK_RMENU)
   {
      return;
   }

//   LRESULT lresult;
   key.m_nChar = wparam;
   bool bShift = (::GetKeyState(VK_SHIFT) & 0x80000000) != 0;
   if(bShift && isalpha(key.m_nChar))
   {
      key.m_nChar = toupper(key.m_nChar);  
   }
   else
   {
      key.m_nChar = tolower(key.m_nChar);  
   }
   _001OnChar(&key);
}

void front_view::_001OnPost(gen::signal_object * pobj)
{
   SCAST_PTR(::user::win::message::base, pbase, pobj)
   if(pbase->m_wparam == 100)
   {
      PostMessage(WM_USER + 101, 101);
      
  }
   else if (pbase->m_wparam == 101)
   {
   }
}

void front_view::OnDocumentComplete(const char * lpszURL)
{
   UNREFERENCED_PARAMETER(lpszURL);
   PostMessage(WM_USER + 101, 101);   
}
