#include "StdAfx.h"
#include "FrontView.h"
#include "FrontDoc.h"


//   // BEGIN_MESSAGE_MAP(devedgeFrontView, html_view)
   //{{AFX_MSG_MAP(devedgeFrontView)
/*
   ON_WM_DESTROY()
   ON_WM_SIZE()
   ON_WM_PAINT()
   ON_WM_CREATE()
   ON_WM_CONTEXTMENU()
   ON_WM_SETCURSOR()
   ON_WM_ERASEBKGND()
   //}}AFX_MSG_MAP
   // Standard printing commands
   ON_MESSAGE(WM_USER + 177, OnTabClick)
   ON_MESSAGE(WM_APP + 119, OnWavePlayerEvent)
   ON_COMMAND(ID_FILE_PRINT, html_view::OnFilePrint)
   ON_COMMAND(ID_FILE_PRINT_DIRECT, html_view::OnFilePrint)
   ON_COMMAND(ID_FILE_PRINT_PREVIEW, html_view::OnFilePrintPreview)
   */
// // END_MESSAGE_MAP()


devedgeFrontView::devedgeFrontView(::ca::application * papp) :
   ca(papp),
   ::user::interaction(papp),
   ::userbase::view(papp),
   ::user::scroll_view(papp),
   ::userbase::scroll_view(papp),
   ::user::form(papp),
   ::userbase::form_view(papp),
   html_form(papp),
   html_view(papp)
{
  // m_pkeyboardfocus = NULL;
//   m_pelementMouseDown = NULL;
}

devedgeFrontView::~devedgeFrontView()
{
}

void devedgeFrontView::install_message_handling(::user::win::message::dispatch * pinterface)
{
   html_view::install_message_handling(pinterface);

   IGUI_WIN_MSG_LINK(WM_DESTROY, pinterface, this, &devedgeFrontView::_001OnDestroy);
   IGUI_WIN_MSG_LINK(WM_SIZE, pinterface, this, &devedgeFrontView::_001OnSize);
   IGUI_WIN_MSG_LINK(WM_PAINT, pinterface, this, &devedgeFrontView::_001OnPaint);
   IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &devedgeFrontView::_001OnCreate);
   IGUI_WIN_MSG_LINK(WM_CONTEXTMENU, pinterface, this, &devedgeFrontView::_001OnContextMenu);
   IGUI_WIN_MSG_LINK(WM_SETCURSOR, pinterface, this, &devedgeFrontView::_001OnSetCursor);
   IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &devedgeFrontView::_001OnTimer);
   IGUI_WIN_MSG_LINK(WM_USER + 101     , this, this, &devedgeFrontView::_001OnPost);

//   IGUI_WIN_MSG_LINK(WM_USER + 177     , this, this, &devedgeFrontView::_001OnTabClick);
   IGUI_WIN_MSG_LINK(WM_APP + 119      , this, this, &devedgeFrontView::_001OnWavePlayerEvent);
 //  IGUI_WIN_MSG_LINK(WM_CHAR, pinterface, this, &devedgeFrontView::_001OnChar);
   //IGUI_WIN_MSG_LINK(WM_SYSCHAR, pinterface, this, &devedgeFrontView::_001OnSysChar);
   //connect_command(ID_FILE_PRINT, html_view::OnFilePrint)
   //connect_command(ID_FILE_PRINT_DIRECT, html_view::OnFilePrint)
   //connect_command(ID_FILE_PRINT_PREVIEW, html_view::OnFilePrintPreview)

   IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN, 
      this,
      this,
      &devedgeFrontView::_001OnLButtonDown);
   IGUI_WIN_MSG_LINK(WM_LBUTTONUP, 
      this,
      this,
      &devedgeFrontView::_001OnLButtonUp);
   IGUI_WIN_MSG_LINK(WM_MOUSEMOVE, 
      this,
      this,
      &devedgeFrontView::_001OnMouseMove);

}

#ifdef _DEBUG
void devedgeFrontView::assert_valid() const
{
   html_view::assert_valid();
}

void devedgeFrontView::dump(dump_context & dumpcontext) const
{
   html_view::dump(dumpcontext);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// devedgeFrontView message handlers

// vmpLightView.cpp : implementation of the devedgeFrontView class
//


/////////////////////////////////////////////////////////////////////////////
// devedgeFrontView


BOOL devedgeFrontView::PreCreateWindow(CREATESTRUCT& cs)
{
   cs.lpszClass = System.RegisterWndClass(
      CS_DBLCLKS |
      CS_OWNDC,
      0, 0, 0);
   cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
   cs.style &= ~WS_BORDER;
   return html_view::PreCreateWindow(cs);
}
void devedgeFrontView::_001OnInitialUpdate(gen::signal_object * pobj) 
{
   html_view::_001OnInitialUpdate(pobj);


   
}

::user::interaction* devedgeFrontView::get_guie()
{
   return this;
}

void devedgeFrontView::on_update(::view* pSender, LPARAM lHint, ::radix::object* phint) 
{
   UNREFERENCED_PARAMETER(pSender);
   UNREFERENCED_PARAMETER(phint);
   if(lHint == 1001)
   {
      _001RedrawWindow();
   }

   
}

void devedgeFrontView::_001OnDestroy(gen::signal_object * pobj) 
{
   html_view::_001OnDestroy(pobj);
}

void devedgeFrontView::_001OnSize(gen::signal_object * pobj) 
{
   UNREFERENCED_PARAMETER(pobj);
  // SCAST_PTR(::user::win::message::size, psize, pobj)
//   document * pdoc = get_document();
}

void devedgeFrontView::_001OnPaint(gen::signal_object * pobj) 
{
   UNREFERENCED_PARAMETER(pobj);
   //CPaintDC spgraphics(this); // device context for painting
   

   //spgraphics->TextOut(20, 20, "Carlos Gustavo Cecyn Lundgren ・minha Vida Eterna, meu Cora鈬o Eterno, Todo meu tesouro eterno, meu Universo eterno, meu tudo eterno!!");
}


void devedgeFrontView:: _001OnDraw(::ca::graphics * pdc)
{

   pdc->OffsetViewportOrg(-2, -2);
}

void devedgeFrontView::_001OnCreate(gen::signal_object * pobj) 
{
   if(pobj->previous())
      return;

   SetTimer(100, 100, NULL);
   
   PostMessage(WM_USER + 101, 101, 1);



   /*document * pdoc = get_document();
   for(int i = 0; i < pdoc->m_elementptraVisible.get_size(); i++)
   {
      IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN, 
         this,
         pdoc->m_elementptraVisible[i],
         &devedge::Element2D::_001OnLButtonDown);
      IGUI_WIN_MSG_LINK(WM_LBUTTONUP, 
         this,
         pdoc->m_elementptraVisible[i],
         &devedge::Element2D::_001OnLButtonUp);
   }*/

}
void devedgeFrontView::_001OnContextMenu(gen::signal_object * pobj) 
{
   SCAST_PTR(::user::win::message::context_menu, pcontextmenu, pobj)
   point point = pcontextmenu->GetPoint();
   
}



void devedgeFrontView::_001OnWavePlayerEvent(gen::signal_object * pobj)
{
   UNREFERENCED_PARAMETER(pobj);
//   SCAST_PTR(::user::win::message::base, pbase, pobj)
}

void devedgeFrontView::_001OnUpdateViewEncoding(gen::signal_object * pobj)
{
   UNREFERENCED_PARAMETER(pobj);
   //SCAST_PTR(::user::win::message::update_cmd_ui, pupdatecmdui, pobj)
}
void devedgeFrontView::_001OnViewEncoding(gen::signal_object * pobj)
{
   UNREFERENCED_PARAMETER(pobj);
   //SCAST_PTR(::user::win::message::command, pcommand, pobj)
}


void devedgeFrontView::_001OnSetCursor(gen::signal_object * pobj) 
{
   ::SetCursor(::LoadCursor(NULL, IDC_ARROW));
   
   pobj->previous();
}

void devedgeFrontView::_001OnLButtonDown(gen::signal_object * pobj) 
{
   SCAST_PTR(::user::win::message::mouse, pmouse, pobj)
   point pt = pmouse->m_pt;
}

void devedgeFrontView::_001OnLButtonUp(gen::signal_object * pobj) 
{
   SCAST_PTR(::user::win::message::mouse, pmouse, pobj)
   point pt = pmouse->m_pt;
}

void devedgeFrontView::_001OnMouseMove(gen::signal_object * pobj) 
{
   SCAST_PTR(::user::win::message::mouse, pmouse, pobj)
   point pt = pmouse->m_pt;
}

document * devedgeFrontView::get_document() const
{
   return (document *) ::userbase::view::get_document();
}

//devedge::Element2D * devedgeFrontView::hit_test(int x, int y)
//{
//   document * pdoc = get_document();
//   return NULL;
//}

void devedgeFrontView::_001OnTimer(gen::signal_object * pobj) 
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
//      key_to_char(m_dwLastKeyWparam, m_dwLastKeyLparam);
   }

}

void devedgeFrontView::_001OnKeyDown(gen::signal_object * pobj) 
{
   UNREFERENCED_PARAMETER(pobj);
//   SCAST_PTR(::user::win::message::key, pkey, pobj)
   //m_dwLastKeyWparam = pkey->m_wparam;
  // m_dwLastKeyLparam = pkey->m_lparam;
//   key_to_char(m_dwLastKeyWparam, m_dwLastKeyLparam);
   SetTimer(500, 500, NULL);
}

void devedgeFrontView::_001OnKeyUp(gen::signal_object * pobj) 
{
   UNREFERENCED_PARAMETER(pobj);
   //SCAST_PTR(::user::win::message::key, pkey, pobj)
   KillTimer(500);
   KillTimer(501);
}


void devedgeFrontView::_001OnChar(gen::signal_object * pobj) 
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


void devedgeFrontView::_001OnSysChar(gen::signal_object * pobj) 
{
   UNREFERENCED_PARAMETER(pobj);
//   SCAST_PTR(::user::win::message::key, pkey, pobj)
}

void devedgeFrontView::pre_translate_message(gen::signal_object * pobj)
{
   return html_view::pre_translate_message(pobj);
}

void devedgeFrontView::key_to_char(WPARAM wparam, LPARAM lparam)
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

void devedgeFrontView::_001OnPost(gen::signal_object * pobj)
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

void devedgeFrontView::OnDocumentComplete(const char * lpszURL)
{
   UNREFERENCED_PARAMETER(lpszURL);
   PostMessage(WM_USER + 101, 101);   
}
