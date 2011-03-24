#include "StdAfx.h"
#include "biteditor_view.h"
#include "biteditor_document.h"

biteditor_view::biteditor_view(::ca::application * papp) :
   ca(papp),
   ::user::interaction(papp),
   ::userbase::view(papp),
   ::user::scroll_view(papp),
   ::userbase::scroll_view(papp)
{
   m_iLineSize = 16;
   m_pasciibox = new biteditor::ascii_box(papp);
   m_phexbox = new biteditor::hex_box(papp);
   m_pasciibox->m_pview = this;
   m_phexbox->m_pview = this;

}

biteditor_view::~biteditor_view()
{
}

void biteditor_view::_001InstallMessageHandling(::user::win::message::dispatch * pinterface)
{
   ::userbase::scroll_view::_001InstallMessageHandling(pinterface);

   IGUI_WIN_MSG_LINK(WM_DESTROY, pinterface, this, &biteditor_view::_001OnDestroy);
   IGUI_WIN_MSG_LINK(WM_SIZE, pinterface, this, &biteditor_view::_001OnSize);
   IGUI_WIN_MSG_LINK(WM_PAINT, pinterface, this, &biteditor_view::_001OnPaint);
   IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &biteditor_view::_001OnCreate);
   IGUI_WIN_MSG_LINK(WM_CONTEXTMENU, pinterface, this, &biteditor_view::_001OnContextMenu);
   IGUI_WIN_MSG_LINK(WM_SETCURSOR, pinterface, this, &biteditor_view::_001OnSetCursor);
   IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &biteditor_view::_001OnTimer);
   IGUI_WIN_MSG_LINK(WM_HSCROLL, pinterface, this, &biteditor_view::_001OnHScroll);

   IGUI_WIN_MSG_LINK(WM_APP + 119      , this, this, &biteditor_view::_001OnWavePlayerEvent);

   IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN, 
      this,
      this,
      &biteditor_view::_001OnLButtonDown);
   IGUI_WIN_MSG_LINK(WM_LBUTTONUP, 
      this,
      this,
      &biteditor_view::_001OnLButtonUp);
   IGUI_WIN_MSG_LINK(WM_MOUSEMOVE, 
      this,
      this,
      &biteditor_view::_001OnMouseMove);
   IGUI_WIN_MSG_LINK(WM_RBUTTONUP, 
      this,
      this,
      &biteditor_view::_001OnRButtonUp);

}

#ifdef _DEBUG
void biteditor_view::assert_valid() const
{
   ::userbase::scroll_view::assert_valid();
}

void biteditor_view::dump(dump_context & dumpcontext) const
{
   ::userbase::scroll_view::dump(dumpcontext);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// biteditor_view message handlers

// vmpLightView.cpp : implementation of the biteditor_view class
//


/////////////////////////////////////////////////////////////////////////////
// biteditor_view


BOOL biteditor_view::PreCreateWindow(CREATESTRUCT& cs)
{
   cs.lpszClass = System.RegisterWndClass(
      CS_DBLCLKS |
      CS_OWNDC,
      0, 0, 0);
   cs.style &= ~WS_EX_CLIENTEDGE;
   return ::userbase::scroll_view::PreCreateWindow(cs);
}
void biteditor_view::_001OnInitialUpdate(gen::signal_object * pobj) 
{
   ::userbase::scroll_view::_001OnInitialUpdate(pobj);

   m_pasciibox->on_update();
   m_phexbox->on_update();

   if(m_iLineHeight <= 0)
         return;


   ::ca::graphics * pdc = GetDC();
   m_pasciibox->_001OnCalcLayout(this, pdc);
   m_phexbox->_001OnCalcLayout(this, pdc);

   size64 sizeTotal;
   sizeTotal.cx = m_pasciibox->m_size.cx + m_phexbox->m_size.cx + 200;
   sizeTotal.cy = m_iLineHeight * get_document()->m_pfile->get_length() / 16 + 200;
   size64 sizePage;
   rect rect;
   GetClientRect(rect);
   sizePage.cx = rect.width();
   sizePage.cy = rect.height() - rect.height() % m_iLineHeight - m_iLineHeight;
   size64 sizeLine;
   sizeLine.cx = sizeTotal.cx;
   sizeLine.cy = m_iLineHeight;
   m_scrollinfo.m_sizeTotal = sizeTotal;
   m_scrollinfo.m_sizePage = sizePage;
   m_scrollinfo. m_sizeLine = sizeLine;
   //SetScrollSizes(MM_TEXT, sizeTotal, sizePage, sizeLine);
   ReleaseDC(pdc);
}

void biteditor_view::on_update(::view * pSender, LPARAM lHint, ::radix::object* phint) 
{
   UNREFERENCED_PARAMETER(pSender);
   if(lHint == 1001)
   {
      _001RedrawWindow();
   }
   else if(lHint == 789231)
   {
      m_pasciibox->m_bGetTextNeedUpdate = true;
      m_phexbox->m_bGetTextNeedUpdate = true;
   }
   else if(lHint == 789231)
   {
      m_pasciibox->m_iSelStart = get_document()->m_iSelStart;
      m_pasciibox->m_iSelEnd = get_document()->m_iSelEnd;
      m_phexbox->m_iSelStart = get_document()->m_iSelStart;
      m_phexbox->m_iSelEnd = get_document()->m_iSelEnd;
      _001RedrawWindow();
   }
   if(phint != NULL)
   {
      if(base < biteditor::pane_view_update_hint> ::bases(phint))
      {
         biteditor::pane_view_update_hint * puh = (biteditor::pane_view_update_hint * ) phint;
         if(puh->is_type_of(biteditor::pane_view_update_hint::TypeOnBeforeShowView))
         {
            //get_document()->on_save_document(get_document()->get_path_name());
         }
         else if(puh->is_type_of(biteditor::pane_view_update_hint::TypeOnShowView))
         {
            get_document()->reload();
         }
      }
   }
   
}

void biteditor_view::_001OnDestroy(gen::signal_object * pobj) 
{
   ::userbase::scroll_view::_001OnDestroy(pobj);

}



void biteditor_view::_001OnSize(gen::signal_object * pobj) 
{
   UNREFERENCED_PARAMETER(pobj);
//   SCAST_PTR(::user::win::message::size, psize, pobj)

   m_pasciibox->on_update();
   m_phexbox->on_update();

//   biteditor_document * pdoc = get_document();
   ::ca::graphics * pdc = GetDC();
   pdc->SelectObject(m_pasciibox->m_spfont);
   size size3 = pdc->GetTextExtent("gqYALÍ");
   m_iLineHeight = size3.cy;
   m_pasciibox->_001OnCalcLayout(this, pdc);
   m_phexbox->_001OnCalcLayout(this, pdc);
   ReleaseDC(pdc);

   m_phexbox->SetWindowPos(ZORDER_TOP, 10, 10, m_phexbox->m_size.cx, m_phexbox->m_size.cy, SWP_SHOWWINDOW);
   m_pasciibox->SetWindowPos(ZORDER_TOP, m_phexbox->m_size.cx + 10 + 10, 10, m_pasciibox->m_size.cx, m_pasciibox->m_size.cy, SWP_SHOWWINDOW);

/*   pobj->previous();

   double d = psize->m_size.cy;
   d /= GetSystemMetrics(SM_CYSCREEN);
   SetScale(d);

   GetClientRect(m_rectKaraokeView);


   rect rectClient;
   GetClientRect(rectClient);
   rect rect = rectClient;

   rect.top = rect.bottom - 24;
   m_viewlineStatus.SetPlacement(rect);


   m_rectKaraokeView.bottom -= 16;

   LayoutTitleLines();
   LayoutLyricTemplateLines();
   LayoutLyricLines();
   LayoutKaraokeBouncingBall();*/
}

void biteditor_view::_001OnPaint(gen::signal_object * pobj) 
{
   UNREFERENCED_PARAMETER(pobj);
   //CPaintDC spgraphics(this); // device context for painting
   

   //spgraphics->TextOut(20, 20, "Carlos Gustavo Cecyn Lundgren é minha Vida Eterna, meu Coração Eterno, Todo meu tesouro eterno, meu Universo eterno, meu tudo eterno!!");
}

/*
void biteditor_view:: _001OnDraw(::ca::graphics * pdc)
{
  // biteditor_document * pdoc = get_document();
//   pdc->OffsetViewportOrg(-m_ptScroll.x, -(m_ptScroll.y % m_iLineHeight));

   ::ca::rgn rgn;

   rect rectClient;
   GetClientRect(rectClient);
   ClientToScreen(rectClient);
   rgn.CreateRectRgnIndirect(rectClient);

   pdc->SelectClipRgn(&rgn);
   
   m_pasciibox->_001OnDraw(this, pdc);
   m_phexbox->_001OnDraw(this, pdc);

}
*/

void biteditor_view::_001OnCreate(gen::signal_object * pobj) 
{
   if(pobj->previous())
      return;

   m_pasciibox->m_peditfile = get_document()->m_peditfile;   
   m_phexbox->m_peditfile = get_document()->m_peditfile;

//   biteditor_document * pdoc = get_document();


   m_pasciibox->create(this, 100);
   m_phexbox->create(this, 101);
   

   SetTimer(100, 100, NULL);


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
void biteditor_view::_001OnContextMenu(gen::signal_object * pobj) 
{
   SCAST_PTR(::user::win::message::context_menu, pcontextmenu, pobj)
   point point = pcontextmenu->GetPoint();
   
}

void biteditor_view::_001OnRButtonUp(gen::signal_object * pobj) 
{
   SCAST_PTR(::user::win::message::mouse, pmouse, pobj)
//   int iItem;
//   HRESULT hr;
   point point = pmouse->m_pt;
   class point ptClient = point;
   ClientToScreen(&point);
   //ScreenToClient(&ptClient);
   ::userbase::menu menu(get_app());
   ex1::text_file_sp spfile(get_app());

   string strModuleFolder;
   strModuleFolder = System.get_module_folder();

   if(!spfile->open(System.dir().path(strModuleFolder, "devedge_contextmenu.xml"), ::ex1::file::type_text | ::ex1::file::mode_read))
      return;

   string str;
   spfile->read_full_string(str);

   xml::node node(get_app());

   node.load(str);

   if (menu.LoadMenu( &node))
   {
      //::userbase::menu* pPopup = (::userbase::menu_item *) menu.GetSubMenu(0);
      //ASSERT(pPopup != NULL);
      userbase::frame_window * pframe = dynamic_cast < userbase::frame_window * > ( dynamic_cast < ::ca::window * > (GetParentFrame()));
      //pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,
        // point.x, point.y,
         //(::ca::window *) pframe);
      menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,
         point.x, point.y,
         pframe);
   }
}




void biteditor_view::_001OnWavePlayerEvent(gen::signal_object * pobj)
{
   UNREFERENCED_PARAMETER(pobj);
//   SCAST_PTR(::user::win::message::base, pbase, pobj)
}

void biteditor_view::_001OnUpdateViewEncoding(gen::signal_object * pobj)
{
   UNREFERENCED_PARAMETER(pobj);
//   SCAST_PTR(::user::win::message::update_cmd_ui, pupdatecmdui, pobj)
}
void biteditor_view::_001OnViewEncoding(gen::signal_object * pobj)
{
   UNREFERENCED_PARAMETER(pobj);
//   SCAST_PTR(::user::win::message::command, pcommand, pobj)
}

void biteditor_view::_001OnSetCursor(gen::signal_object * pobj) 
{
   ::SetCursor(::LoadCursor(NULL, IDC_ARROW));
   
   pobj->previous();
}

void biteditor_view::_001OnLButtonDown(gen::signal_object * pobj) 
{
   SCAST_PTR(::user::win::message::mouse, pmouse, pobj)
   point pt = pmouse->m_pt;
   //ScreenToClient(&pt);
}

void biteditor_view::_001OnLButtonUp(gen::signal_object * pobj) 
{
   SCAST_PTR(::user::win::message::mouse, pmouse, pobj)
   point pt = pmouse->m_pt;
   //ScreenToClient(&pt);
   if(System.get_mouse_focus_LButtonDown() != NULL)
   {
   System.get_mouse_focus_LButtonDown()->mouse_focus_OnLButtonUp(pobj);
   System.set_mouse_focus_LButtonDown(NULL);
   }
      
   /*biteditor::Element2D * pelement = hit_test(pt.x, pt.y);
   if(pelement != NULL)
   {
      pelement->_001OnLButtonUp(this, pobj);
   }*/
}

void biteditor_view::_001OnMouseMove(gen::signal_object * pobj) 
{
   SCAST_PTR(::user::win::message::mouse, pmouse, pobj)
   point pt = pmouse->m_pt;
   //ScreenToClient(&pt);

}

biteditor_document * biteditor_view::get_document() const
{
   return dynamic_cast < biteditor_document * > (::userbase::scroll_view::get_document());
}


void biteditor_view::_001OnTimer(gen::signal_object * pobj) 
{
   SCAST_PTR(::user::win::message::timer, ptimer, pobj)
   if(ptimer->m_nIDEvent >= 100 
      && ptimer->m_nIDEvent <= 200)
   {
      if(System.get_keyboard_focus() == m_pasciibox)
      {
         m_pasciibox->_001OnKeyboardFocusTimer(this, ptimer->m_nIDEvent - 100);
      }
      else if(System.get_keyboard_focus() == m_phexbox)
      {
         m_phexbox->_001OnKeyboardFocusTimer(this, ptimer->m_nIDEvent - 100);
      }
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

void biteditor_view::_001OnKeyDown(gen::signal_object * pobj) 
{
   SCAST_PTR(::user::win::message::key, pkey, pobj)

   if(pkey->m_nChar == VK_RETURN)
   {
      if(::GetKeyState(VK_CONTROL) & 0x80000000
         && ::GetKeyState(VK_MENU) & 0x80000000)
      {
         pkey->m_bRet = false;
         return;
      }
   }
   else if(pkey->m_nChar == VK_MENU)
   {
      pkey->m_bRet = false;
      return;
   }

   m_dwLastKeyWparam = pkey->m_wparam;
   m_dwLastKeyLparam = pkey->m_lparam;
   key_to_char(m_dwLastKeyWparam, m_dwLastKeyLparam);
   SetTimer(500, 500, NULL);
}

void biteditor_view::_001OnKeyUp(gen::signal_object * pobj) 
{
   SCAST_PTR(::user::win::message::key, pkey, pobj)
   if(pkey->m_nChar == VK_RETURN)
   {
      if(::GetKeyState(VK_CONTROL) & 0x80000000
         && ::GetKeyState(VK_MENU) & 0x80000000)
      {
         pkey->m_bRet = false;
         return;
      }
   }
   else if(pkey->m_nChar == VK_MENU)
   {
      pkey->m_bRet = false;
   }
   KillTimer(500);
   KillTimer(501);
}


void biteditor_view::_001OnChar(gen::signal_object * pobj) 
{
   SCAST_PTR(::user::win::message::key, pkey, pobj)
   if(pkey->m_nChar == 's')
   {
      if(::GetKeyState(VK_CONTROL) & 0x80000000)
      {
         return;
      }
   }
   if(System.get_keyboard_focus() == m_pasciibox)
   {
      m_pasciibox->_001OnChar(this, pobj);
   }
   else if(System.get_keyboard_focus() == m_phexbox)
   {
      m_phexbox->_001OnChar(this, pobj);
   }
}


void biteditor_view::_001OnSysChar(gen::signal_object * pobj) 
{
//   SCAST_PTR(::user::win::message::key, pkey, pobj)
   if(System.get_keyboard_focus() == m_pasciibox)
   {
      m_pasciibox->_001OnSysChar(this, pobj);
   }
   else if(System.get_keyboard_focus() == m_phexbox)
   {
      m_phexbox->_001OnSysChar(this, pobj);
   }
}

void biteditor_view::_001OnHScroll(gen::signal_object * pobj) 
{
   UNREFERENCED_PARAMETER(pobj);
   m_pasciibox->m_bGetTextNeedUpdate = true;
   m_phexbox->m_bGetTextNeedUpdate = true;
}

void biteditor_view::pre_translate_message(gen::signal_object * pobj)
{
   SCAST_PTR(user::win::message::base, pbase, pobj);
   if(pbase->m_uiMessage == WM_KEYDOWN)
   {
      SCAST_PTR(user::win::message::key, pkey, pobj);
      _001OnKeyDown(pkey);
      if(pkey->m_bRet)
         return;
   }
   else if(pbase->m_uiMessage == WM_KEYUP)
   {
      SCAST_PTR(user::win::message::key, pkey, pobj);
      _001OnKeyUp(pkey);
      if(pkey->m_bRet)
         return;
   }
   ::userbase::scroll_view::pre_translate_message(pobj);
}
void biteditor_view::key_to_char(WPARAM wparam, LPARAM lparam)
{
   UNREFERENCED_PARAMETER(lparam);
   ::user::win::message::key key(get_app());
   key.m_nChar = wparam;
   if(wparam == VK_LSHIFT || wparam == VK_RSHIFT
      || wparam == VK_LCONTROL || wparam == VK_RCONTROL
      || wparam == VK_LMENU || wparam == VK_RMENU
      || wparam == VK_SHIFT || wparam == VK_CONTROL
      || wparam == VK_MENU)
   {
      return;
   }

   if(wparam == VK_RIGHT || wparam == VK_UP
      || wparam == VK_LEFT || wparam == VK_DOWN)
   {
      _001OnChar(&key);
      return;
   }

//   LRESULT lresult;
   bool bShift = (::GetKeyState(VK_SHIFT) & 0x80000000) != 0;
   if(isalpha(key.m_nChar))
   {
      if(bShift)
      {
         key.m_nChar = toupper(key.m_nChar);  
      }
      else
      {
         key.m_nChar = tolower(key.m_nChar);  
      }
   }
   _001OnChar(&key);
}




int biteditor_view::CalcLineCount()
{
   DWORD dwLength = get_document()->m_peditfile->get_length();
   int iMod = dwLength % m_iLineSize;
   int iLineCount = dwLength / m_iLineSize;
   if(iMod == 0)
      return iLineCount;
   else 
      return iLineCount + 1;
}


int biteditor_view::UpdateScrollSizes()
{
   m_scrollinfo.m_sizeTotal.cx = 1024;
   m_scrollinfo.m_sizeTotal.cy = m_pasciibox->m_size.cy;
   return 0;
}