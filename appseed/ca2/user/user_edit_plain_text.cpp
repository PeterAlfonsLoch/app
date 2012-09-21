#include "framework.h"

   string str_block(char ch, int iSize)
   {
      string str;
      for(int i = 0; i < iSize; i++)
      {
         str += ch;
      }
      return str;
   }


   void str_fill(string & str, char ch)
   {
      str = str_block(ch, (int) str.get_length());
   }

namespace user
{


   edit_plain_text::edit_plain_text(::ca::application * papp) :
      ca(papp),
      ::user::interaction(papp),
      scroll_view(papp),
      colorertake5::base_editor(papp),
      m_fastblur(papp),
      m_dibBk(papp),
      ex1::tree(papp),
      ::ca::data_listener(papp)
   {

      m_pdata              = NULL;
      m_bOwnData           = false;

      m_bMultiLine         = true;
      m_bColorerTake5      = false;
      m_bReadOnly          = false;


      m_straSep.add("\n");
      m_straSep.add("\r");
      m_straSep.add("\r\n");



      m_y                  = -1;
      m_iaLineIndex.set_size(0, 100000);
      m_iaLineEndIndex.set_size(0, 100000);
      m_iaCLineIndex.set_size(0, 1000);
      m_iViewOffset        = 0;
      m_iViewSize          = 1000;
      m_bMouseDown         = false;
      m_dwCaretTime        = 500;
      m_dwLastCaret        = GetTickCount();
      set_cursor(::visual::cursor_text_select);
   }

   edit_plain_text::~edit_plain_text()
   {
      if(m_bOwnData)
      {
         delete m_pdata;
         m_pdata = NULL;
      }
   }

   void edit_plain_text::install_message_handling(::gen::message::dispatch * pinterface)
   {
      scroll_view::install_message_handling(pinterface);
   /*   IGUI_WIN_MSG_LINK(WM_DESTROY, pinterface, this, &edit_plain_text::_001OnDestroy);
      IGUI_WIN_MSG_LINK(WM_SIZE, pinterface, this, &edit_plain_text::_001OnSize);
      IGUI_WIN_MSG_LINK(WM_PAINT, pinterface, this, &edit_plain_text::_001OnPaint);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &edit_plain_text::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_CONTEXTMENU, pinterface, this, &edit_plain_text::_001OnContextMenu);
      IGUI_WIN_MSG_LINK(WM_SETCURSOR, pinterface, this, &edit_plain_text::_001OnSetCursor);
      IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &edit_plain_text::_001OnTimer);
      IGUI_WIN_MSG_LINK(WM_HSCROLL, pinterface, this, &edit_plain_text::_001OnHScroll);*/

      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &edit_plain_text::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN, pinterface, this, &edit_plain_text::_002OnLButtonDown);
      IGUI_WIN_MSG_LINK(WM_LBUTTONUP, pinterface, this, &edit_plain_text::_002OnLButtonUp);
      IGUI_WIN_MSG_LINK(WM_RBUTTONDOWN, pinterface, this, &edit_plain_text::_002OnRButtonDown);
      IGUI_WIN_MSG_LINK(WM_RBUTTONUP, pinterface, this, &edit_plain_text::_002OnRButtonUp);
      IGUI_WIN_MSG_LINK(WM_MOUSEMOVE, pinterface, this, &edit_plain_text::_002OnMouseMove);
      IGUI_WIN_MSG_LINK(WM_KEYDOWN, pinterface, this, &edit_plain_text::_002OnKeyDown);
      IGUI_WIN_MSG_LINK(WM_KEYUP, pinterface, this, &edit_plain_text::_002OnKeyUp);
      IGUI_WIN_MSG_LINK(WM_CHAR, pinterface,   this,   &edit_plain_text::_002OnChar);

      IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &::user::edit_plain_text::_002OnTimer);

      connect_update_cmd_ui("edit_focus_copy", &edit_plain_text::_001OnUpdateEditFocusCopy);
      connect_command("edit_focus_copy", &edit_plain_text::_001OnEditFocusCopy);
      connect_update_cmd_ui("edit_focus_paste", &edit_plain_text::_001OnUpdateEditFocusPaste);
      connect_command("edit_focus_paste", &edit_plain_text::_001OnEditFocusPaste);

   /*   IGUI_WIN_MSG_LINK(WM_RBUTTONUP,
         this,
         this,
         &edit_plain_text::_002OnRButtonUp); */

   }
   /////////////////////////////////////////////////////////////////////////////
   // edit_plain_text drawing

   void edit_plain_text::OnDraw(::ca::graphics * pdcScreen)
   {
      UNREFERENCED_PARAMETER(pdcScreen);
   }

   /////////////////////////////////////////////////////////////////////////////

   void edit_plain_text::_001OnInitialUpdate(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      _001OnUpdate();

      ::ca::graphics * pdc = GetDC();
      _001OnCalcLayout(pdc);
      ReleaseDC(pdc);


      __begin_thread(get_app(), ThreadProcScrollSize, (LPVOID) this);


   }

   void edit_plain_text::_001OnDestroy(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }



   void edit_plain_text::VirtualOnSize()
   {
      _001OnUpdate();

      ::ca::graphics * pdc = GetDC();
      _001OnCalcLayout(pdc);
      ReleaseDC(pdc);


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

   void edit_plain_text::_001OnPaint(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      //CPaintDC spgraphics(this); // device context for painting


      //spgraphics->TextOut(20, 20, "Carlos Gustavo Cecyn Lundgren ・minha Vida Eterna, meu Cora鈬o Eterno, Todo meu tesouro eterno, meu Universo eterno, meu tudo eterno!!");
   }



   void edit_plain_text::_001OnDraw(::ca::graphics * pdc)
   {

      pdc->set_text_rendering(::ca::text_rendering_anti_alias);

      COLORREF crBk;
      COLORREF crBkSel;
      COLORREF crSel;
      COLORREF cr;


      cr          = ARGB(255, 23, 23, 23);
      crBk        = ARGB(255, 255, 255, 255);
      crBkSel     = ARGB(255, 0, 0, 127);
      crSel       = ARGB(255, 255, 255, 255);

      ::ca::job * pjob = pdc->m_pjob;

      ::user::print_job * pprintjob = NULL;
      if(pjob!= NULL)
         pprintjob = dynamic_cast < ::user::print_job * > (pjob);
      else
         pprintjob = NULL;


      rect rectClient;
      GetClientRect(rectClient);

      if(pprintjob != NULL)
      {
         TRACE("Print Job Is Printing page %d", pprintjob->m_iPrintingPage);
      }



      //rectClient.deflate(0, 0, 1, 1);



      if(_001IsBackgroundBypass())
      {
      }
      else if(_001IsTranslucent())
      {
         class imaging & imaging = System.imaging();
         imaging.color_blend(
            pdc,
            rectClient,
            RGB(200, 255, 255),
            127);
      }
      else
      {
         pdc->FillSolidRect(rectClient, get_background_color());
      }
      /*else if(!System.savings().is_trying_to_save(gen::resource_processing)
      && !System.savings().is_trying_to_save(gen::resource_blur_background))
      {

         pdc->blur(true, 4, rectClient);
         //class imaging & imaging = System.imaging();
         //rect rectClient;
//         GetWindowRect(rectClient);
  //       rectClient.offset(rectClient.top_left());
/*         if(rectClient.size() != m_dibBk->size())
         {
            m_dibBk->create(rectClient.size());
            m_dibBk->Fill(184, 184, 170);
/*            HMODULE hmodule = ::LoadLibrary("ca2performance.dll");
            ::visual::fastblur *( *pfnNew )(::ca::application *) = (::visual::fastblur *(*)(::ca::application *)) ::GetProcAddress(hmodule, "new_fastblur");*/
/*            m_fastblur.create(get_app());
            m_fastblur.initialize(rectClient.size(), 2);
         }
         if(m_fastblur.is_set() && m_fastblur->get_graphics() != NULL)
         {
            m_fastblur->get_graphics()->BitBlt(0, 0, rectClient.width(), rectClient.height(), pdc, 0, 0, SRCCOPY);
            m_fastblur.blur();
            imaging.bitmap_blend(
               m_fastblur->get_graphics(),
               null_point(),
               rectClient.size(),
               m_dibBk->get_graphics(),
               null_point(),
               49);
            pdc->from(rectClient.size(),
               m_fastblur->get_graphics(),
               null_point(),
               SRCCOPY);
         }*/
      /*}
      else
      {
         class imaging & imaging = System.imaging();
         //_001DrawBackground(pdc, rectClipBox);
         imaging.color_blend(
            pdc,
            rectClient,
            RGB(200, 255, 255),
            127);
      }*/

      color c;
      c.set_rgb(RGB(227, 227, 210));
      c.hls_rate(0.0, -0.33, -0.23);
      COLORREF crBorder = c.get_rgb() | (0xff << 24);
      pdc->Draw3dRect(rectClient, crBorder, crBorder);

      if(m_pdata == NULL)
         return;

      if(m_pdata->is_in_use())
      {
         return;
      }

      if(m_iLineHeight == 0)
      {
         pdc->OffsetViewportOrg(-m_scrollinfo.m_ptScroll.x, m_scrollinfo.m_ptScroll.y);
      }
      else
      {
         pdc->OffsetViewportOrg(-m_scrollinfo.m_ptScroll.x, -(m_scrollinfo.m_ptScroll.y % m_iLineHeight));
      }

      ::ca::region_sp rgn(get_app());

      rectClient.deflate(2, 2);

      //ClientToScreen(rectClient);
      rgn->CreateRectRgnIndirect(rectClient);

      double left = rectClient.left;

   //   pdc->SelectClipRgn(&rgn);

      if(Application.get_keyboard_focus() == this)
      {
         m_bFocus = keyboard_focus_is_focusable();
      }
      else
      {
         m_bFocus = false;
      }

      strsize iSelStart;
      strsize iSelEnd;
      strsize lim = 0;


   /*   rectClient.top = m_pt.y;
      rectClient.left = m_pt.x;
      rectClient.bottom = rectClient.top + m_size.cy;
      rectClient.right = rectClient.left + m_size.cx;*/
//      pdc->FillSolidRect(rectClient, crBk);


      double y = rectClient.top;
      _001GetViewSel(iSelStart, iSelEnd);
      strsize iCursor = iSelEnd;
      sort::sort(iSelStart, iSelEnd);
      pdc->SelectObject(GetFont());
      size size3;
      visual::graphics_extension(get_app()).GetTextExtent(pdc, unitext("gGYIﾍ"), size3);
      int iLineHeight = size3.cy;
      stringa & straLines = m_lines.lines;
      stringa straLineFeed;
      string strLine;
      string str1;
      string str2;
      string str3;
      string strExtent1;
      string strExtent2;
      string strExtent3;
      index iLineStart = should_load_full_file() ? m_iLineOffset : 0;
      index iLineEnd = should_load_full_file() ? m_iLineCount - 1 : straLines.get_size() - 1;
      iLineEnd = min(iLineEnd, straLines.get_upper_bound());
      for(index i = iLineStart; i <= iLineEnd; i++)
      {
         straLineFeed.remove_all();
         straLineFeed.add_smallest_tokens(straLines[i], m_straSep, FALSE, FALSE);
         if(straLineFeed.get_size() > 0)
         {
            strLine = straLineFeed[0];
         }
         else
         {
            strLine.Empty();
         }
         colorertake5::LineRegion * pregion = NULL;
         if(m_bColorerTake5)
            pregion = getLineRegions(i);
         if(pregion != NULL)
         {
            for(; pregion != NULL; pregion = pregion->next)
            {
               if(pregion->special || pregion->rdef == NULL)
                  continue;
               index end = pregion->end;
               if(end == -1)
                  end = strLine.get_length();
               strsize x = pregion->start;
               strsize len = end - pregion->start;
               if(x < 0)
               {
                  len += x;
                  x = 0;
               }
               if(len < 0)
                  continue;
               if(pregion->styled()->bfore)
               {
                  pdc->set_color(pregion->styled()->fore);
               }
               else
               {
                  pdc->set_color(cr);
               }
               if(pregion->styled()->bback)
               {
                  pdc->SetBkMode(OPAQUE);
                  pdc->SetBkColor(pregion->styled()->back);
               }
               else
               {
                  pdc->SetBkMode(TRANSPARENT);
               }
               string strExtent1;
               strExtent1 = strLine.Left(x);
               string strExtent2;
               strExtent2 = strLine.Mid(x, len);
               class size size1;
               visual::graphics_extension(get_app()).GetTextExtent(pdc, strExtent1, size1);
               pdc->TextOutA(left + size1.cx, y, strExtent2);

            }
         }
         else
         {
            stringa stra;
            strsize i1 = iSelStart - lim;
            strsize i2 = iSelEnd - lim;
            strsize i3 = iCursor - lim;
            strsize iStart = max(0, i1);
            strsize iEnd = min(i2, strLine.get_length());
            if(m_bPassword)
            {
               str_fill(strLine, '*');
            }
            str1 = strLine.Mid(0, iStart);
            str2 = strLine.Mid(iStart, iEnd - iStart);
            str3 = strLine.Mid(iEnd);
            strExtent1 = str1;
            strExtent2 = str2;
            strExtent3 = str3;
            strExtent1.replace("\t", "   ");
            strExtent2.replace("\t", "   ");
            strExtent3.replace("\t", "   ");
            if(m_bPassword)
            {
               str_fill(strExtent1, '*');
               str_fill(strExtent2, '*');
               str_fill(strExtent3, '*');
            }
            pdc->SetBkMode(TRANSPARENT);
            pdc->set_color(cr);
            pdc->SetBkColor(crBkSel);
            pdc->TextOut(left, y, strExtent1);
            sized size1(0.0, 0.0);
            pdc->GetTextExtent(size1, strLine, strLine.length(), iStart);
            pdc->SetBkMode(OPAQUE);
            sized sizeb(0.0, 0.0);
            pdc->GetTextExtent(sizeb, strLine, iEnd);
            sized size2(0.0, 0.0);
            pdc->GetTextExtent(size2, strLine, strLine.length(), iEnd);
            size2.cx -= size1.cx;
            if(iEnd > iStart)
            {
               pdc->FillSolidRect((int) (left + size1.cx), y, size2.cx, size2.cy, ARGB(255, 120, 240, 180));
               pdc->set_color(crSel);
               pdc->TextOut(left + size1.cx, y, strExtent2);
            }
            pdc->set_color(cr);
            
            pdc->SetBkMode(TRANSPARENT);
            pdc->TextOut(left + size1.cx + size2.cx, y, strExtent3);
            //maxcy = max(size1.cy, size2.cy);
            //maxcy = max(maxcy, size3.cy);
            if(m_bFocus && m_bCaretOn && i3 == str1.get_length())
            {
               pdc->MoveTo(left + size1.cx, y);
               pdc->LineTo(left + size1.cx, y + iLineHeight);
            }
            else if(m_bFocus && m_bCaretOn && i3 == (str1.get_length() + str2.get_length()))
            {
               pdc->MoveTo(left + size2.cx + size1.cx, y);
               pdc->LineTo(left + size2.cx + size1.cx, y + iLineHeight);
            }
         }
         y += iLineHeight;
         lim += straLines[i].get_length();
      }

   }

   void edit_plain_text::_001OnCreate(gen::signal_object * pobj)
   {
      SCAST_PTR(::gen::message::create, pcreate, pobj);

      if(!ex1::tree::initialize())
         throw simple_exception();



      if(get_document() != NULL
      && ::view::get_data < document > () != NULL
      && dynamic_cast < plain_text_data * > (::view::get_data < document >()) != NULL)
      {
         set_plain_text_data(dynamic_cast < plain_text_data * > (::view::get_data < document > ()), false);
      }
      else
      {
         set_plain_text_data(new user::plain_text_data(get_app()), true);
      }

      ::ca::data * pdataParentLock = oprop("parent_lock_data").ca2 < ::ca::data > ();
      if(pdataParentLock != NULL)
      {
         m_pdata->m_spdataParentLock = pdataParentLock;
      }

      if(!m_pdata->initialize_data())
         throw simple_exception();

      m_pdata->m_ptreeitem          = get_base_item();

      pcreate->previous();
      m_pdata->m_pfile = new gen::memory_file(get_app());
      if(m_bColorerTake5)
      {
         colorertake5::base_editor::initialize(&m_lines);
         colorertake5::base_editor::setRegionMapper("rgb", "default");
      }
   //  m_peditfile = new edit_file(get_app());
      m_pdata->m_editfile.SetFile(m_pdata->m_pfile);
      m_bGetTextNeedUpdate = true;
      m_bPassword = false;


      SetTimer(100, 100, NULL);
      m_iSelStart  = 0;
      m_iSelEnd = 0;
      _001OnUpdate();
      _001OnSetText();


   }

   void edit_plain_text::_001OnContextMenu(gen::signal_object * pobj)
   {
      SCAST_PTR(::gen::message::context_menu, pcontextmenu, pobj)
      point point = pcontextmenu->GetPoint();

   }

   void edit_plain_text::_001OnRButtonUp(gen::signal_object * pobj)
   {
      SCAST_PTR(::gen::message::mouse, pmouse, pobj)
      //int iItem;
      //HRESULT hr;
      class point point = pmouse->m_pt;
      class point ptClient = point;
      ClientToScreen(&point);
      //ScreenToClient(&ptClient);
   /*   ::userbase::menu menu;
      Ex1TextFile file;

      gen::application * papp = gen::get_app();

      string strModuleFolder;
      strModuleFolder = papp->get_module_folder();

      if(!spfile->open(ca2::dir().path(strModuleFolder, "devedge_contextmenu.xml"), ::ex1::file::type_text | ::ex1::file::mode_read))
         return;

      string str;
      spfile->read_full_string(str);

      xml::node node(get_app());

      node.Load(str);

      if (menu.LoadMenu(get_app(), &node))
      {
         //::userbase::menu* pPopup = (::userbase::menu_item *) menu.GetSubMenu(0);
         //ASSERT(pPopup != NULL);
         userbase::frame_window * pframe = (userbase::frame_window *) (::ca::window *) GetParentFrame();
         //pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,
           // point.x, point.y,
            //(::ca::window *) pframe);
         menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,
            point.x, point.y,
            (::ca::window *) pframe);
      }*/
   }





   void edit_plain_text::_001OnSetCursor(gen::signal_object * pobj)
   {
      //::SetCursor(::LoadCursor(NULL, IDC_ARROW));

      pobj->previous();
   }

   void edit_plain_text::_002OnTimer(gen::signal_object * pobj)
   {
      SCAST_PTR(::gen::message::timer, ptimer, pobj)
      if(ptimer->m_nIDEvent >= 100
         && ptimer->m_nIDEvent <= 200)
      {
         if(this == Application.get_keyboard_focus())
         {
            _001OnKeyboardFocusTimer(ptimer->m_nIDEvent - 100);
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

   void edit_plain_text::_002OnKeyDown(gen::signal_object * pobj)
   {
      SCAST_PTR(::gen::message::key, pkey, pobj)

      if(pkey->m_nChar == VK_RETURN)
      {
         if(::GetKeyState(VK_CONTROL) & 0x80000000
            && ::GetKeyState(VK_MENU) & 0x80000000)
         {
            pkey->m_bRet      = false;
            return;
         }
         if((!m_bMultiLine || (bool)oprop("send_enter_key")) && GetParent() != NULL)
         {
            ::user::control_event ev;
            ev.m_puie         = this;
            ev.m_eevent       = ::user::event_enter_key;
            ev.m_bUser        = true;
            BaseOnControlEvent(&ev);
            pobj->m_bRet      = true;
            return;
         }
      }
      else if(pkey->m_nChar == VK_TAB)
      {
         if(::GetKeyState(VK_CONTROL) & 0x80000000
            && ::GetKeyState(VK_MENU) & 0x80000000)
         {
            pkey->m_bRet      = false;
            return;
         }
         if(!m_bMultiLine)
         {
            ::user::control_event ev;
            ev.m_puie         = this;
            ev.m_eevent       = ::user::event_tab_key;
            ev.m_bUser        = true;
            GetParent()->BaseOnControlEvent(&ev);
            BaseOnControlEvent(&ev);
            pkey->m_bRet      = true;
            return;
         }
      }
      else if(pkey->m_nChar == VK_MENU)
      {
         pkey->m_bRet = false;
         return;
      }
      else if(pkey->m_nChar == 'C')
      {
         if(::GetKeyState(VK_CONTROL) & 0x80000000)
         {
            pkey->m_bRet      = true;
            clipboard_copy();
            return;
         }
      }
      else if(pkey->m_nChar == 'V')
      {
         if(::GetKeyState(VK_CONTROL) & 0x80000000)
         {
            pkey->m_bRet      = true;
            clipboard_paste();
            return;
         }
      }

      m_dwLastKeyWparam = pkey->m_wparam;
      m_dwLastKeyLparam = pkey->m_lparam;
      m_bKeyPressed     = true;
      key_to_char(m_dwLastKeyWparam, m_dwLastKeyLparam);
      pkey->m_bRet      = true;
   }

   void edit_plain_text::_002OnKeyUp(gen::signal_object * pobj)
   {
      SCAST_PTR(::gen::message::key, pkey, pobj)
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
      m_bKeyPressed = false;
   }

   void edit_plain_text::_002OnChar(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
//      SCAST_PTR(::gen::message::key, pkey, pobj)
         if(m_bKeyPressed)
         {
               //key_to_char(m_dwLastKeyWparam, m_dwLastKeyLparam);
         }
   }





   void edit_plain_text::_001OnHScroll(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      if(should_load_full_file())
      {
         m_bNeedScrollUpdate = true;
      }
      else
      {
         m_bGetTextNeedUpdate = true;
      }
   }

   void edit_plain_text::pre_translate_message(gen::signal_object * pobj)
   {
      SCAST_PTR(::gen::message::base, pbase, pobj);
      if(pbase->m_uiMessage == WM_KEYDOWN)
      {
         pbase->m_bRet = true;
         _001OnKeyDown(pbase);
      }
      else if(pbase->m_uiMessage == WM_KEYUP)
      {
         pbase->m_bRet = true;
         _001OnKeyUp(pbase);
      }
      else if(pbase->m_uiMessage == WM_CHAR)
      {
         pbase->m_bRet = true;
         ::user::interaction::_001OnChar(pbase);
      }
   }
   void edit_plain_text::key_to_char(WPARAM wparam, LPARAM lparam)
   {
      ::gen::message::key key(get_app());
      key.m_nChar = wparam;
      key.m_nFlags = HIWORD(lparam);
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

      //LRESULT lresult;
      bool bShift = Application.is_key_pressed(VK_SHIFT);
      if(key.m_nChar < 256 && isalpha((int) key.m_nChar))
      {
         if(bShift)
         {
            key.m_nChar = toupper((int) key.m_nChar);
         }
         else
         {
            key.m_nChar = tolower((int) key.m_nChar);
         }
      }
      _001OnChar(&key);
   }



   UINT edit_plain_text::ThreadProcScrollSize(LPVOID lpvoid)
   {
      edit_plain_text * pview = (edit_plain_text *) lpvoid;
      ::ca::data::writing writing(pview->m_pdata);

      ::ca::graphics_sp graphics(pview->get_app());
      graphics->CreateCompatibleDC(NULL);
      ::ca::graphics * pdc = graphics;
      pview->_001OnCalcLayoutProc(pview, pdc);
      //pview->ReleaseDC(pdc);
      pview->_001OnUpdate();
      return 0;
   }


   void edit_plain_text::_001GetText(string & str) const
   {
      ::ca::data::writing writing(m_pdata);
      if(m_pdata == NULL)
         return;
      file_size iSize = m_pdata->m_editfile.get_length();
      char * psz = str.GetBufferSetLength((strsize)(iSize + 1));
      m_pdata->m_editfile.seek(0, ::ex1::seek_begin);
      m_pdata->m_editfile.read(psz, (::primitive::memory_size) iSize);
      psz[(::primitive::memory_position) iSize] = '\0';
      str.ReleaseBuffer();
  //    str.replace("\n", "\r\n");
   }


   void edit_plain_text::_001GetSelText(string & str) const
   {
      file_position iEnd;
      file_position iStart;
      if(m_iSelEnd < 0)
      {
         if(m_iSelStart < 0)
         {
            iEnd = (file_position) m_pdata->m_editfile.get_length();
            iStart = 0;
         }
         else
         {
            iStart = m_iSelStart;
            iEnd = (file_position) m_pdata->m_editfile.get_length();
         }
      }
      else
      {
         if(m_iSelStart < 0)
         {
            iEnd = m_iSelEnd;
            iStart = 0;
         }
         else
         {
            iEnd = m_iSelEnd;
            iStart = m_iSelStart;
         }
      }
      if(iEnd < iStart)
      {
         file_position iSwap   = iEnd;
         iEnd        = iStart;
         iStart      = iSwap;
      }
      file_position iSize = iEnd - iStart;
      char * psz = str.GetBufferSetLength((strsize)(iSize + 1));
      m_pdata->m_editfile.seek((file_offset) iStart, ::ex1::seek_begin);
      m_pdata->m_editfile.read(psz, (::primitive::memory_size) (iSize));
      psz[(::primitive::memory_position)iSize] = '\0';
      str.ReleaseBuffer();
      str.replace("\n", "\r\n");
   }

   void edit_plain_text::_001SetSelText(const char * psz)
   {
      m_pdata->m_editfile.seek(m_iSelStart, ::ex1::seek_begin);
      m_pdata->m_editfile.Delete((file_size) (m_iSelEnd - m_iSelStart));
      m_pdata->m_editfile.seek(m_iSelStart, ::ex1::seek_begin);
      m_pdata->m_editfile.Insert(psz, strlen(psz));
      _001OnUpdate();
      _001RedrawWindow();
   }

   void edit_plain_text::_001SetSel(strsize iSelStart, strsize iSelEnd)
   {
      m_iSelStart = iSelStart;
      m_iSelEnd = iSelEnd;
      _001RedrawWindow();
   }

   void edit_plain_text::_002OnLButtonDown(gen::signal_object * pobj)
   {
      SCAST_PTR(::gen::message::mouse, pmouse, pobj)
      point pt = pmouse->m_pt;
      ScreenToClient(&pt);
      m_bMouseDown = true;
      ::ca::graphics * pdc = GetDC();
      if(pdc == NULL)
         return;
      m_iSelStart = char_hit_test(pdc, pt.x, pt.y);
      m_iSelEnd = m_iSelStart;
      ReleaseDC(pdc);
      _001RedrawWindow();
      Application.set_keyboard_focus(this);
      Application.set_mouse_focus_LButtonDown(this);
      pmouse->m_bRet = true;
      pmouse->set_lresult(1);
   }

   void edit_plain_text::_002OnLButtonUp(gen::signal_object * pobj)
   {
      SCAST_PTR(::gen::message::mouse, pmouse, pobj)
      point pt = pmouse->m_pt;
      ScreenToClient(&pt);
      ::ca::graphics * pdc = GetDC();
      m_iSelEnd = char_hit_test(pdc, pt.x, pt.y);
      m_iColumn = SelToColumn(m_iSelEnd);
      ReleaseDC(pdc);
      _001RedrawWindow();
      m_bMouseDown = false;
      pmouse->m_bRet = true;
      pmouse->set_lresult(1);
      //System.simple_message_box(m_strText);
   }

   void edit_plain_text::_002OnRButtonDown(gen::signal_object * pobj)
   {
      SCAST_PTR(::gen::message::mouse, pmouse, pobj)
      point pt = pmouse->m_pt;
      ScreenToClient(&pt);
      m_bMouseDown = true;
      ::ca::graphics * pdc = GetDC();
      m_iSelStart = char_hit_test(pdc, pt.x, pt.y);
      m_iSelEnd = m_iSelStart;
      ReleaseDC(pdc);
      _001RedrawWindow();
      Application.set_keyboard_focus(this);
      Application.set_mouse_focus_RButtonDown(this);
      pmouse->m_bRet = true;
      pmouse->set_lresult(1);
   }

   void edit_plain_text::_002OnRButtonUp(gen::signal_object * pobj)
   {
      SCAST_PTR(::gen::message::mouse, pmouse, pobj)
      point pt = pmouse->m_pt;
      ScreenToClient(&pt);
      ::ca::graphics * pdc = GetDC();
      m_iSelEnd = char_hit_test(pdc, pt.x, pt.y);
      m_iColumn = SelToColumn(m_iSelEnd);
      ReleaseDC(pdc);
      _001RedrawWindow();
      m_bMouseDown = false;

      ::userbase::menu menu(get_app());
      menu.LoadXmlMenu("system\\edit_focus_popup.xml");
      ::userbase::menu menuPopup(get_app(), menu.GetSubMenu(0));
      menuPopup.TrackPopupMenu(0, pmouse->m_pt.x, pmouse->m_pt.y, GetParentFrame());

      pmouse->set_lresult(1);
      pmouse->m_bRet = true;
   }

   void edit_plain_text::_001OnCalcLayoutProc(user::elemental * pview, ::ca::graphics * pdc)
   {
      ::ca::data::writing writing(m_pdata);

      UNREFERENCED_PARAMETER(pview);
      pdc->SelectObject(GetFont());
      int y = 0;
///      int i = 1;
      pdc->set_text_rendering(::ca::text_rendering_anti_alias_grid_fit);
      size size3 = pdc->GetTextExtent(unitext("gqYALﾍ"));

      rect rectClient;

      GetClientRect(rectClient);

      m_iLineHeight = size3.cy;
      //char buf[4096 + 1];
      //UINT uiRead;
      //LPTSTR lpsz;
      m_pdata->m_editfile.seek(0, ::ex1::seek_begin);
      y = (int) (m_iLineHeight * m_iaLineIndex.get_size());
      if(y <= 0)
         y = 200;
   //   pview->SetScrollSizes(MM_TEXT,
     //    m_size);
   }

   void edit_plain_text::_001OnCalcLayout(::ca::graphics * pdc)
   {

      pdc->SelectObject(GetFont());
      stringa & straLines = m_lines.lines;
      strsize iSelStart;
      strsize iSelEnd;
      _001GetViewSel(iSelStart, iSelEnd);
      //int lim = 0;
      int iLineHeight;
//      int y = 0;
//      bool bFound = false;
      string strLine;
      sized size3;
      pdc->set_text_rendering(::ca::text_rendering_anti_alias_grid_fit);
      pdc->GetTextExtent(size3, unitext("gqYALﾍWM"));
      sized size;
      m_scrollinfo.m_sizeTotal.cx = 0;
      iLineHeight = (int) size3.cy;
      for(int i = 0; i < straLines.get_size(); i++)
      {
         strLine = straLines[i];
         strLine.replace("\t", "   ");
         size = (DWORD) (strLine.get_length() * size3.cx / 8);
//         maxcy = max(size.cy, size3.cy);
         if(size.cx > m_scrollinfo.m_sizeTotal.cx)
            m_scrollinfo.m_sizeTotal.cx = (int) size.cx;

      }
      m_scrollinfo.m_sizeTotal.cy = (long) (m_iaLineIndex.get_count() * iLineHeight);
      rect rectClient;
      GetClientRect(rectClient);
      class size sizePage;
      sizePage.cx = rectClient.width();
      sizePage.cy = rectClient.height();
      m_scrollinfo.m_sizeTotal.cy += sizePage.cy;
      m_scrollinfo.m_sizePage = sizePage;
   }

   index edit_plain_text::SelToLine(strsize iSel)
   {
      iSel -= m_iViewOffset;
      stringa & straLines = m_lines.lines;
      strsize i1;
      strsize i2 = 0;
      for(index i = 0; i < straLines.get_size(); i++)
      {
         i1 = i2;
         i2 = i1 + straLines[i].get_length();
         if(iSel >= i1
            && iSel < i2)
         {
            return i;
         }
      }
      return -1;
   }

   index edit_plain_text::SelToLineX(strsize iSel, int & x)
   {
      iSel -= m_iViewOffset;
      stringa & straLines = m_lines.lines;
      strsize i1;
      strsize i2 = 0;
      for(index i = 0; i < straLines.get_size(); i++)
      {
         i1 = i2;
         i2 = i1 + straLines[i].get_length();
         if(iSel >= i1
            && iSel < i2)
         {
            ::ca::graphics * pgraphics = GetDC();

            pgraphics->SelectObject(GetFont());
            pgraphics->set_text_rendering(::ca::text_rendering_anti_alias_grid_fit);
            size size1 = pgraphics->GetTextExtent(straLines[i], straLines[i].length(), iSel - i1);
            size size2 = pgraphics->GetTextExtent(straLines[i], iSel - i1);

            ReleaseDC(pgraphics);

            x = (size1.cx + size2.cx) / 2;

            return i;
         }
      }
      return -1;
   }


   strsize edit_plain_text::LineColumnToSel(index iLine, index iColumn)
   {
      //int i1;
//      int i2 = 0;
      while(iLine < 0)
      {
         OneLineUp();
         if(m_iViewOffset == 0)
         {
            iLine = 0;
            break;
         }
         iLine++;
      }
      stringa & straLines = m_lines.lines;
      if(iLine >= straLines.get_size())
      {
         return 0;
      }
      strsize iOffset = 0;
      for(int i = 0; i < iLine; i++)
      {
         iOffset += straLines[i].get_length();
      }
      stringa stra;
      string strLine;
      stra.remove_all();
      stra.add_smallest_tokens(straLines[iLine], m_straSep, FALSE, FALSE);
      if(stra.get_size() > 0)
      {
         strLine = stra[0];
      }
      else
      {
         strLine.Empty();
      }
      if(iColumn < 0)
         iColumn = iColumn + 1 + strLine.get_length();
      if(iColumn > strLine.get_length())
         iColumn = strLine.get_length();
      return m_iViewOffset + iOffset + iColumn;
   }

   strsize edit_plain_text::LineXToSel(index iLine, int x)
   {
      
      ::ca::graphics * pgraphics = GetDC();

      pgraphics->SelectObject(GetFont());
      pgraphics->set_text_rendering(::ca::text_rendering_anti_alias_grid_fit);
      size size3 = pgraphics->GetTextExtent(unitext("gqYALﾍWM"));

      int iLineHeight = size3.cy;

      int y = iLineHeight * iLine + iLineHeight / 2 - m_scrollinfo.m_ptScroll.y;

      strsize iChar = char_hit_test(pgraphics, x, y); 

      ReleaseDC(pgraphics);

      return iChar;
/*      while(iLine < 0)
      {
         OneLineUp();
         if(m_iViewOffset == 0)
         {
            iLine = 0;
            break;
         }
         iLine++;
      }
      stringa & straLines = m_lines.lines;
      if(iLine >= straLines.get_size())
      {
         return 0;
      }
      strsize iOffset = 0;
      for(int i = 0; i < iLine; i++)
      {
         iOffset += straLines[i].get_length();
      }
      stringa stra;
      string strLine;
      stra.remove_all();
      stra.add_smallest_tokens(straLines[iLine], m_straSep, FALSE, FALSE);
      if(stra.get_size() > 0)
      {
         strLine = stra[0];
      }
      else
      {
         strLine.Empty();
      }
      if(iColumn < 0)
         iColumn = iColumn + 1 + strLine.get_length();
      if(iColumn > strLine.get_length())
         iColumn = strLine.get_length();
      return m_iViewOffset + iOffset + iColumn;*/
   }

   index edit_plain_text::SelToColumn(strsize iSel)
   {
      iSel -= m_iViewOffset;
      stringa & straLines = m_lines.lines;
      strsize i1;
      strsize i2 = 0;
      for(index i = 0; i < straLines.get_size(); i++)
      {
         i1 = i2;
         i2 = i1 + straLines[i].get_length();
         if(iSel >= i1
            && iSel <= i2)
         {
            return iSel - i1;
         }
      }
      return -1;
   }

   strsize edit_plain_text::char_hit_test(::ca::graphics * pdc, int px, int py)
   {
      pdc->SelectObject(GetFont());
      rect rectClient;
      GetClientRect(rectClient);
      px -= rectClient.left;
      py -= rectClient.top;
      if(m_iLineHeight == 0)
      {
         py += m_scrollinfo.m_ptScroll.y;
      }
      else
      {
         py += m_scrollinfo.m_ptScroll.y % m_iLineHeight;
      }
      stringa & straLines = m_lines.lines;
      strsize iSelStart;
      strsize iSelEnd;
      _001GetViewSel(iSelStart, iSelEnd);
      int lim = 0;
      int iLineHeight;
      int y = 0;
      bool bFound = false;
      string strLine;
      string strExtent;
      size size3;
      visual::graphics_extension(get_app()).GetTextExtent(pdc, unitext("gqYALﾍ"), size3);

      iLineHeight = size3.cy;

      strsize iOffset = 0;
      stringa stra;
      for(int i = 0; i < straLines.get_size(); i++)
      {
         stra.remove_all();
         stra.add_smallest_tokens(straLines[i], m_straSep, FALSE, FALSE);
         if(stra.get_size() > 0)
         {
            strLine = stra[0];
         }
         else
         {
            strLine.Empty();
         }
         strExtent = strLine;
         strExtent.replace("\t", "   ");
         size size;
         visual::graphics_extension(get_app()).GetTextExtent(pdc, strExtent, size);
         //iLineHeight = max(size.cy, size3.cy);
         if(py >= y && py < y + iLineHeight)
         {
            bFound = true;
            break;
         }
         y += iLineHeight;
         iOffset += straLines[i].get_length();
      }
      int lim2 = 0;
      int lim1;
      const char * psz = strLine;
      const char * pszEnd = psz;
      const char * pszPrevious = psz;
      for(;; )
      {
         pszPrevious = pszEnd;
         pszEnd = gen::str::utf8_inc(pszEnd);
         lim1 = lim2;
         strExtent = string(psz, pszEnd - psz);
         strExtent.replace("\t", "   ");
         class size size;
         class ::size size1 = pdc->GetTextExtent(strLine, strLine.length(), strExtent.length());
         class ::size size2 = pdc->GetTextExtent(strLine, strExtent.length());
         lim2 = (size1.cx + size2.cx) / 2;
         lim = lim2;
         //lim = (lim2 + lim1) / 2;
         //lim++;
         if(px >= lim1 && px <= (lim2 * 3 + lim1) / 4)
         {
            return iOffset + (pszPrevious - psz) + m_iViewOffset;
         }
         else if(px >= (lim2 * 3 + lim1) / 4 && px <= lim2)
         {
            return iOffset + (pszEnd - psz) + m_iViewOffset;
         }
         if(pszEnd[0] == '\0')
            break;
         
      }
      return (strsize) min((strsize)(iOffset + strLine.get_length() + m_iViewOffset), (strsize)m_pdata->m_editfile.get_length());
   }

   void edit_plain_text::_002OnMouseMove(gen::signal_object * pobj)
   {
      SCAST_PTR(::gen::message::mouse, pmouse, pobj)
      //::SetCursor(::LoadCursor(NULL, IDC_IBEAM));
      point pt = pmouse->m_pt;
      ScreenToClient(&pt);

      pmouse->m_ecursor = ::visual::cursor_text_select;

      if(m_bMouseDown)
      {
         ::ca::graphics * pdc = GetDC();
         m_iSelEnd = char_hit_test(pdc, pt.x, pt.y);
         ReleaseDC(pdc);
       //  _001RedrawWindow();
      }

   }

   void edit_plain_text::_001GetViewSel(strsize &iSelStart, strsize &iSelEnd)
   {
      iSelStart = m_iSelStart - m_iViewOffset;
      iSelEnd = m_iSelEnd - m_iViewOffset;
   }

   void edit_plain_text::on_updata_data(::ca::data * pdata, int iHint)
   {
      if(pdata == m_pdata)
      {
         if(iHint == plain_text_data::update_hint_set_file)
         {
            OnFileUpdate();
         }
      }
   }

   void edit_plain_text::FileSave()
   {
      m_pdata->m_editfile.Flush();
   }

   void edit_plain_text::OnFileUpdate()
   {
      m_bGetTextNeedUpdate = true;
      CreateLineIndex();
      m_y = -1;
   }

   void edit_plain_text::CreateLineIndex()
   {
      //int y = 0;
      int i = 1;
      char buf[1024 * 256 + 1];
      primitive::memory_size uiRead;
      LPTSTR lpsz;
      m_iaLineIndex.remove_all();
      m_iaLineEndIndex.remove_all();
      m_pdata->m_editfile.seek(0, ::ex1::seek_begin);
      if(m_scrollinfo.m_sizeTotal.cx <= 0)
         m_scrollinfo.m_sizeTotal.cx = 200;
      int iLineSize = 0;
      char flags[3];
      flags[0] = 3;
      flags[1] = 1;
      flags[2] = 2;
      while((uiRead = m_pdata->m_editfile.read(buf, sizeof(buf) - 1)) > 0)
      {
         buf[uiRead] = '\0';
         lpsz = buf;
         while(*lpsz != NULL)
         {
            if(*lpsz == '\r' && (*(lpsz + 1)) == '\n')
            {
               iLineSize +=2;
               m_iaLineIndex.add(iLineSize);
               m_iaLineEndIndex.add(3);
               iLineSize = 0;
               lpsz += 2;
            }
            else if(*lpsz == '\n')
            {
               iLineSize++;
               m_iaLineIndex.add(iLineSize);
               m_iaLineEndIndex.add(1);
               iLineSize = 0;
               lpsz++;
            }
            else if(*lpsz == '\r')
            {
               iLineSize++;
               m_iaLineIndex.add(iLineSize);
               m_iaLineEndIndex.add(2);
               iLineSize = 0;
               lpsz++;
            }
            else
            {
               lpsz++;
               iLineSize++;
            }
         }

         i++;
      }
      m_iaLineIndex.add(iLineSize);
      m_iaLineEndIndex.add(0);

      ::count iAcc;
      ::count iLineCount;
      i = 0;
      while(i < m_iaLineIndex.get_size())
      {
         iAcc = 0;
         iLineCount = 0;
         for(; iLineCount < 100 && i < m_iaLineIndex.get_size(); i++, iLineCount++)
         {
            iAcc += m_iaLineIndex[i];
         }
         m_iaCLineIndex.add(iAcc);
      }
   }

   void edit_plain_text::_001OnChar(gen::signal_object * pobj)
   {
      ::ca::data::writing writing(m_pdata);
      _009OnChar(pobj);
      if(pobj->m_bRet)
         return;
      SCAST_PTR(::gen::message::key, pkey, pobj)

      if(pkey->m_nChar == 's')
      {
         if(::GetKeyState(VK_CONTROL) & 0x80000000)
         {
            return;
         }
      }
      else if(pkey->m_nChar == 'z')
      {
         if(Application.is_key_pressed(VK_CONTROL))
         {
            Undo();
            return;
         }
      }
      else if(pkey->m_nChar == 'y')
      {
         if(Application.is_key_pressed(VK_CONTROL))
         {
            Redo();
            return;
         }
      }

      bool bShift = Application.is_key_pressed(VK_SHIFT);

      if(pkey->m_nChar == VK_BACK)
      {
         if(!m_bReadOnly)
         {
            strsize i1 = m_iSelStart;
            strsize i2 = m_iSelEnd;
            if(i1 != i2)
            {
               plain_text_data::SetSelCommand * psetsel = new plain_text_data::SetSelCommand;
               psetsel->m_iPreviousSelStart = m_iSelStart;
               psetsel->m_iPreviousSelEnd = m_iSelEnd;
               ::sort::sort(i1, i2);
               m_pdata->m_editfile.seek(i1, ::ex1::seek_begin);
               m_pdata->m_editfile.Delete((file_size)(i2 - i1));
               IndexRegisterDelete(i1, i2 - i1);
               m_iSelEnd = i1;
               m_iSelStart = m_iSelEnd;
               psetsel->m_iSelStart = m_iSelStart;
               psetsel->m_iSelEnd = m_iSelEnd;
               MacroBegin();
               MacroRecord(psetsel);
               MacroRecord(new plain_text_data::FileCommand());
               MacroEnd();
               _001OnUpdate();
               _001OnAfterChangeText();
            }
            else if(m_iSelEnd >= 0 && m_pdata->m_editfile.get_length() > 0)
            {
               plain_text_data::SetSelCommand * psetsel = new plain_text_data::SetSelCommand;
               psetsel->m_iPreviousSelStart = m_iSelStart;
               psetsel->m_iPreviousSelEnd = m_iSelEnd;
               char buf[512];
               memset(buf, 0, sizeof(buf));
               strsize iBegin = max(0, m_iSelEnd - 256);
               strsize iCur = m_iSelEnd - iBegin;
               m_pdata->m_editfile.seek(iBegin, ::ex1::seek_begin);
               m_pdata->m_editfile.read(buf, sizeof(buf));
               const char * psz = gen::str::utf8_dec(buf, &buf[iCur]);
               strsize iMultiByteUtf8DeleteCount = &buf[iCur] - psz;
               m_iSelEnd -= iMultiByteUtf8DeleteCount;
               m_pdata->m_editfile.seek(m_iSelEnd, ::ex1::seek_begin);
               m_pdata->m_editfile.Delete((file_size) iMultiByteUtf8DeleteCount);
               IndexRegisterDelete(m_iSelEnd, iMultiByteUtf8DeleteCount);
               m_iSelStart = m_iSelEnd;
               psetsel->m_iSelStart = m_iSelStart;
               psetsel->m_iSelEnd = m_iSelEnd;
               MacroBegin();
               MacroRecord(psetsel);
               MacroRecord(new plain_text_data::FileCommand());
               MacroEnd();
               _001OnUpdate();
               _001OnAfterChangeText();
            }
         }
      }
      else if(pkey->m_nChar == VK_UP)
      {
         int x;
         index iLine = SelToLineX(m_iSelEnd, x);
         iLine--;
         m_iSelEnd = LineXToSel(iLine, x);
         if(!bShift)
         {
            m_iSelStart = m_iSelEnd;
         }
         _001RedrawWindow();
      }
      else if(pkey->m_nChar == VK_DOWN)
      {
         int x;
         index iLine = SelToLineX(m_iSelEnd, x);
         iLine++;
         m_iSelEnd = LineXToSel(iLine, x);
         if(!bShift)
         {
            m_iSelStart = m_iSelEnd;
         }
         _001RedrawWindow();
      }
      else if(pkey->m_nChar == VK_RIGHT)
      {
         if(!bShift && m_iSelStart > m_iSelEnd)
         {
            m_iSelEnd = m_iSelStart;
         }
         else if(!bShift && m_iSelEnd > m_iSelStart)
         {
            m_iSelStart = m_iSelEnd;
         }
         else if(natural(m_iSelEnd) < m_pdata->m_editfile.get_length())
         {
            char buf[32];
            m_pdata->m_editfile.seek(m_iSelEnd, ::ex1::seek_begin);
            primitive::memory_size uiRead = m_pdata->m_editfile.read(buf, 32);
            if(uiRead == 2 &&
               buf[0] == '\r' &&
               buf[1] == '\n')
            {
               m_iSelEnd += 2;
            }
            else
            {
               m_iSelEnd += gen::str::utf8_inc(buf) - buf;
            }
            if(!bShift)
            {
               m_iSelStart = m_iSelEnd;
            }
         }
         _001RedrawWindow();
      }
      else if(pkey->m_nChar == VK_LEFT)
      {
         if(!bShift && m_iSelStart < m_iSelEnd)
         {
            m_iSelEnd = m_iSelStart;
         }
         else if(!bShift && m_iSelEnd < m_iSelStart)
         {
            m_iSelStart = m_iSelEnd;
         }
         else if(m_iSelEnd > 0)
         {
            if(m_iSelEnd > 2)
            {
               char buf[64];
               char * psz;
               m_pdata->m_editfile.seek(max(0, m_iSelEnd - 32), ::ex1::seek_begin);
               psz = &buf[min(32, m_iSelEnd)];
               primitive::memory_size uiRead = m_pdata->m_editfile.read(buf, 64);
               if(uiRead == 2 &&
                  psz[0] == '\r' &&
                  psz[1] == '\n')
               {
                  m_iSelEnd -= 2;
               }
               else
               {
                  m_iSelEnd -= psz - gen::str::utf8_dec(buf, psz);
               }
            }
            else
            {
               m_iSelEnd--;
            }
            if(!bShift)
            {
               m_iSelStart = m_iSelEnd;
            }
         }
         _001RedrawWindow();
      }
      else if(pkey->m_nChar == VK_HOME)
      {
         index iLine = SelToLine(m_iSelEnd);
         m_iSelEnd = LineColumnToSel(iLine, 0);
         if(!bShift)
         {
            m_iSelStart = m_iSelEnd;
         }
         _001RedrawWindow();
      }
      else if(pkey->m_nChar == VK_END)
      {
         index iLine = SelToLine(m_iSelEnd);
         m_iSelEnd = LineColumnToSel(iLine, -1);
         if(!bShift)
         {
            m_iSelStart = m_iSelEnd;
         }
         _001RedrawWindow();
      }
      else
      {
         if(!m_bReadOnly)
         {
            if(pkey->m_nChar == VK_RETURN)
            {
               // Kill Focus => Kill Key Repeat Timer
               //System.simple_message_box("VK_RETURN reached edit_plain_text");
            }
            plain_text_data::SetSelCommand * psetsel = new plain_text_data::SetSelCommand;
            psetsel->m_iPreviousSelStart = m_iSelStart;
            psetsel->m_iPreviousSelEnd = m_iSelEnd;
            m_pdata->m_editfile.MacroBegin();
            strsize i1 = m_iSelStart;
            strsize i2 = m_iSelEnd;
            ::sort::sort(i1, i2);
            m_pdata->m_editfile.seek(i1, ::ex1::seek_begin);
            m_pdata->m_editfile.Delete((file_size) (i2 - i1));
            IndexRegisterDelete(i1, i2 - i1);
            m_iSelEnd = i1;
            m_pdata->m_editfile.seek(m_iSelEnd, ::ex1::seek_begin);
            string str;
            char ch = (char) pkey->m_nChar;
            if(ch == '\r')
               ch = '\n';
            int iChar = (int) pkey->m_nChar;
            if(iChar == '\r')
               iChar = '\n';
            if(bShift)
            {
               iChar |= 0x80000000;
            }
            int iCode = pkey->m_nFlags & 0xff;
            if(bShift)
            {
               iCode |= 0x80000000;
            }
            string strMap;
            str = Application.keyboard().process_key(iCode, iChar, 0);
            m_iSelEnd += str.get_length();
            m_iSelStart = m_iSelEnd;
           m_pdata-> m_editfile.Insert(str, str.get_length());
            IndexRegisterInsert(m_iSelEnd, str);
            m_pdata->m_editfile.MacroEnd();
            psetsel->m_iSelStart = m_iSelStart;
            psetsel->m_iSelEnd = m_iSelEnd;
            MacroBegin();
            MacroRecord(psetsel);
            MacroRecord(new plain_text_data::FileCommand());
            MacroEnd();
            _001OnUpdate();
            _001OnAfterChangeText();
         }
      }
      if(pkey->m_nChar != VK_UP
      && pkey->m_nChar != VK_DOWN)
      {
         m_iColumn = SelToColumn(m_iSelEnd);
      }
      m_dwLastCaret = ::GetTickCount();
      m_bCaretOn = true;
      _001RedrawWindow();
   }

   void edit_plain_text::_001OnSysChar(gen::signal_object * pobj)
   {
      ::ca::data::writing writing(m_pdata);
      SCAST_PTR(::gen::message::key, pkey, pobj)
      if(pkey->m_nChar == VK_DELETE)
      {
         if(!m_bReadOnly)
         {
            strsize i1 = m_iSelStart;
            strsize i2 = m_iSelEnd;
            if(i1 != i2)
            {
               ::sort::sort(i1, i2);
               m_pdata->m_editfile.seek(i1, ::ex1::seek_begin);
               m_pdata->m_editfile.Delete((file_size) (i2 - i1));
               m_iSelEnd = i1;
               m_iSelStart = m_iSelEnd;
            }
            else if(natural(m_iSelEnd) < m_pdata->m_editfile.get_length())
            {
               char buf[512];
               memset(buf, 0, sizeof(buf));
               strsize iBegin = max(0, m_iSelEnd - 256);
               strsize iCur = m_iSelEnd - iBegin;
               m_pdata->m_editfile.seek(iBegin, ::ex1::seek_begin);
               m_pdata->m_editfile.read(buf, sizeof(buf));
               const char * psz = gen::str::utf8_dec(buf, &buf[iCur]);
               strsize iMultiByteUtf8DeleteCount = &buf[iCur] - psz;
               m_pdata->m_editfile.seek(m_iSelEnd, ::ex1::seek_begin);
               m_pdata->m_editfile.Delete((file_size) (iMultiByteUtf8DeleteCount));
               IndexRegisterDelete(m_iSelEnd, iMultiByteUtf8DeleteCount);
               m_iSelStart = m_iSelEnd;
            }
         }
      }
   }


   void edit_plain_text::_001OnKeyboardFocusTimer(int iTimer)
   {
      if(iTimer == 0)
      {
         if(m_dwLastCaret + m_dwCaretTime < GetTickCount())
         {
            m_dwLastCaret = GetTickCount();
            m_bCaretOn = !m_bCaretOn;
            //RedrawWindow();
            _001RedrawWindow();
         }
      }
   }

   void edit_plain_text::OneLineUp()
   {
      m_scrollinfo.m_ptScroll.y -= m_iLineHeight;
      if(m_scrollinfo.m_ptScroll.y < m_scrollinfo.m_rectMargin.top)
         m_scrollinfo.m_ptScroll.y = m_scrollinfo.m_rectMargin.top;
      int iHeight = 0;
      //char flag;
      m_iViewOffset = 0;
      ::count iLineSize;
      ::index i = 0;
      while(m_scrollinfo.m_ptScroll.y > iHeight && i < m_iaLineIndex.get_size())
      {
         iLineSize = m_iaLineIndex[i];
         iHeight += m_iLineHeight;
         m_iViewOffset += iLineSize;
         i++;
      }

   }

   void edit_plain_text::IndexRegisterDelete(strsize iSel, strsize iCount)
   {
      UNREFERENCED_PARAMETER(iSel);
      UNREFERENCED_PARAMETER(iCount);
      CreateLineIndex();
      modifyEvent(0);
   /*   char flag;
      m_iViewOffset = 0;
      int iLineSize;
      UINT uiRead;
      int iPos = 0;
      int iLineStart = -1;
      int iLineEnd = -1;
      int iLineStartRemain = -1;
      int iLineEndRemain = -1;
      int iLine = 0;
      int i = 0;
      while(i < m_iaLineIndex.get_size())
      {
         iLineSize = m_iaLineIndex[i];
         iLineStart = iLine;
         if(iSel < (iPos + iLineSize))
         {
            iLineStartRemain = iSel - iPos;
            break;
         }
         iPos += iLineSize;
         iLine++;
         i++;
      }
      if(iSel + iCount <= (iPos + iLineSize))
      {
         iLineEnd = iLineStart;
         iLineEndRemain = (iPos + iLineSize) - (iSel + iCount);
      }
      else
      {
         while(i < m_iaLineIndex.get_size())
         {
            iLineSize = m_iaLineIndex[i];
            iLine++;
            iLineEnd = iLine;
            m_editfileLineIndex.read(&flag, 1);
            if(iSel + iCount <= (iPos + iLineSize))
            {
               iLineEndRemain = (iPos + iLineSize) - (iSel + iCount);
               break;
            }
            iPos += iLineSize;
         }
      }

      if(iLineEnd > iLineStart)
      {
         m_editfileLineIndex.seek(5 * (iLineStart + 1), ::ex1::seek_begin);
         m_editfileLineIndex.Delete(5 * (iLineEnd - iLineStart));
      }
      m_editfileLineIndex.seek(5 * iLineStart, ::ex1::seek_begin);
      iLineSize = iLineStartRemain + iLineEndRemain;
      m_editfileLineIndex.write(&iLineSize, 4);
      m_editfileLineIndex.write(&flag, 1);
   */

   }

   void edit_plain_text::IndexRegisterInsert(strsize iSel, const char * lpcszWhat)
   {
      UNREFERENCED_PARAMETER(iSel);
      UNREFERENCED_PARAMETER(lpcszWhat);
      CreateLineIndex();
      modifyEvent(0);
   }
   void edit_plain_text::_001OnUpdate()
   {

      string str;
      _001GetText(str);

      if(m_iSelStart > str.get_length())
         m_iSelStart = str.get_length();
      else if(m_iSelStart < 0)
         m_iSelStart = 0;

      if(m_iSelEnd > str.get_length())
         m_iSelEnd = str.get_length();
      else if(m_iSelEnd < 0)
         m_iSelEnd = 0;

      m_bGetTextNeedUpdate = 1;
      CreateLineIndex();
      m_y = -1;
      ::ca::graphics_sp dc(get_app());
      dc->CreateCompatibleDC(NULL);
      _001OnCalcLayout(dc);
      lineCountEvent(m_lines.lines.get_count());

      try
      {

         _001OnSetText();

      }
      catch(...)
      {

      }


      try
      {
      
         _001OnAfterChangeText();

      }
      catch(...)
      {

      }

   }



   void edit_plain_text::MacroBegin()
   {
      plain_text_data::GroupCommand * pgroupcommand = new plain_text_data::GroupCommand;
      pgroupcommand->m_pparent = m_pdata->m_pgroupcommand;
      m_pdata->m_pgroupcommand = pgroupcommand;
   }

   void edit_plain_text::MacroEnd()
   {
      if(m_pdata->m_pgroupcommand == NULL)
      {
         ASSERT(FALSE);
         return;
      }
      if(m_pdata->m_pgroupcommand->m_pparent == NULL)
      {
         MacroRecord(m_pdata->m_pgroupcommand);
      }
      m_pdata->m_pgroupcommand = m_pdata->m_pgroupcommand->m_pparent;
   }


   void edit_plain_text::MacroRecord(plain_text_data::Command * pcommand)
   {
      if(m_pdata->m_pgroupcommand != NULL && m_pdata->m_pgroupcommand != pcommand)
      {
         m_pdata->m_pgroupcommand->add(pcommand);
         return;
      }
      if(m_pdata->m_ptreeitem->m_pnext != NULL)
      {
         ex1::tree_item * pitemNew = insert_item(pcommand, ::ex1::RelativeFirstChild, m_pdata->m_ptreeitem);
         if(pitemNew != NULL)
         {
            m_pdata->m_ptreeitem = pitemNew;
         }
      }
      else
      {
         ex1::tree_item * pitemNew = insert_item(pcommand, ::ex1::RelativeLastSibling, m_pdata->m_ptreeitem);
         if(pitemNew != NULL)
         {
            m_pdata->m_ptreeitem = pitemNew;
         }
      }
   }


   bool edit_plain_text::Undo()
   {
      if(!CanUndo())
         return false;


      plain_text_data::Command * pcommand = (plain_text_data::Command *) m_pdata->m_ptreeitem->m_pitemdata;
      pcommand->Undo(m_pdata);
      m_pdata->m_ptreeitem = m_pdata->m_ptreeitem->get_previous();
      CreateLineIndex();
      m_bGetTextNeedUpdate = true;

      _001OnUpdate();
      _001OnAfterChangeText();

      return true;
   }
   bool edit_plain_text::Redo()
   {
      if(m_pdata->m_ptreeitem == NULL)
      {
         return false;
      }
      if(m_pdata->m_iBranch < 0
         || m_pdata->m_iBranch >= GetRedoBranchCount())
      {
         return false;
      }
      plain_text_data::Command * pcommand = NULL;
      ::ex1::tree_item * ptreeitem;
      if(m_pdata->m_iBranch < m_pdata->m_ptreeitem->get_expandable_children_count())
      {
         ptreeitem = m_pdata->m_ptreeitem->get_expandable_child(m_pdata->m_iBranch);
      }
      else
         ptreeitem = m_pdata->m_ptreeitem->get_next();
      if(ptreeitem == NULL)
         return false;
      m_pdata->m_ptreeitem = ptreeitem;
      pcommand = (plain_text_data::Command *) ptreeitem->m_pitemdata;
      pcommand->Redo(m_pdata);
      CreateLineIndex();
      m_bGetTextNeedUpdate = true;

      _001OnUpdate();
      _001OnAfterChangeText();

      return true;
   }

   bool edit_plain_text::CanUndo()
   {
      return m_pdata->m_ptreeitem != get_base_item();
   }

   bool edit_plain_text::CanRedo()
   {
      return m_pdata->m_iBranch < m_pdata->m_ptreeitem->get_expandable_children_count()
         || m_pdata->m_ptreeitem->get_next(false, false) != NULL;
   }

   ::count edit_plain_text::GetRedoBranchCount()
   {
      return m_pdata->m_ptreeitem->get_expandable_children_count()
           + (m_pdata->m_ptreeitem->m_pnext != NULL ? 1 : 0)
           + (m_pdata->m_ptreeitem->m_pchild != NULL ? 1 : 0);
   }



   void edit_plain_text::_001SetText(const char * psz)
   {
      ::ca::data::writing writing(m_pdata);
      m_pdata->m_editfile.seek(0, ::ex1::seek_begin);
      m_pdata->m_editfile.Delete((::primitive::memory_size)m_pdata->m_editfile.get_length());
      m_pdata->m_editfile.seek(0, ::ex1::seek_begin);
      m_pdata->m_editfile.Insert(psz, strlen(psz));
      _001OnUpdate();
      _001OnSetText();
      _001RedrawWindow();
   }


   void edit_plain_text::keyboard_focus_OnKeyDown(gen::signal_object * pobj)
   {
      _002OnKeyDown(pobj);
   }

   void edit_plain_text::keyboard_focus_OnKeyUp(gen::signal_object * pobj)
   {
      _002OnKeyUp(pobj);
   }

   void edit_plain_text::keyboard_focus_OnChar(gen::signal_object * pobj)
   {
      _002OnChar(pobj);
   }


   void edit_plain_text::_001OnAfterChangeText()
   {
      ::user::control_event ev;
      ev.m_puie         = this;
      ev.m_eevent       = ::user::event_after_change_text;
      ev.m_bUser        = true;
      BaseOnControlEvent(&ev);
   }

   void edit_plain_text::clipboard_copy()
   {
      string str;
      _001GetSelText(str);
      System.copydesk().set_plain_text(str);
   }

   void edit_plain_text::clipboard_paste()
   {

      string str;
      str = System.copydesk().get_plain_text();
      str.replace("\r\n", "\n");
      _001SetSelText(str);
      MacroBegin();
      MacroRecord(new plain_text_data::FileCommand());
      MacroEnd();

      _001OnUpdate();
      _001OnAfterChangeText();

   }


   void edit_plain_text::_001OnSetText()
   {
      m_iViewOffset = 0;
      rect rectClient;
      GetClientRect(rectClient);

      if(m_iLineHeight == 0)
      {
         m_iLineOffset = 0;
      }
      else
      {
         m_iLineOffset = max(0, m_scrollinfo.m_ptScroll.y / m_iLineHeight);
      }

      ::index iLine = 0;
      ::count iCLine = iLine / 100;
      ::index i;

      m_iViewOffset = 0;

      for(iLine = 0, i = 0; i < iCLine; i++, iLine += 100)
      {
         m_iViewOffset += m_iaCLineIndex[i];
      }
      for(; iLine < m_iLineOffset && iLine < m_iaLineIndex.get_size(); iLine++)
      {
         m_iViewOffset += m_iaLineIndex[iLine];
      }
      m_iViewSize = 0;
      if(m_iLineHeight == 0)
      {
         m_iLineCount = 1;
      }
      else
      {
         m_iLineCount = (rectClient.height() / m_iLineHeight) + 1;
      }
      for(i = 0; i < m_iLineCount && iLine < m_iaLineIndex.get_size(); i++, iLine++)
      {
         m_iViewSize += m_iaLineIndex[iLine];
      }
      m_lines.lines.set_size(0, 100);
      string str;
      m_pdata->m_editfile.seek(m_iViewOffset, ::ex1::seek_begin);
      iLine = m_iLineOffset;
      i = 0;
      ::index iLineStart = should_load_full_file() ? 0 : m_iLineOffset;
      ::index iLineEnd = should_load_full_file() ? m_iaLineIndex.get_size() - 1 : min(m_iaLineIndex.get_size(), m_iLineCount) - 1;
      for(::index iLine = iLineStart; i <= iLineEnd && iLine < m_iaLineIndex.get_size(); i++, iLine++)
      {
         strsize iLen = m_iaLineIndex[iLine];
         LPTSTR lpsz = str.GetBufferSetLength(iLen + 1);
         m_pdata->m_editfile.read(lpsz, iLen);
         lpsz[iLen] = '\0';
         str.ReleaseBuffer();
         m_lines.lines.add(str);
      }

      m_y = m_scrollinfo.m_ptScroll.y;

      visibleTextEvent(m_iLineOffset, m_iLineCount);
      
      

   }

   bool edit_plain_text::should_load_full_file()
   {
      return m_bColorerTake5;
   }

   colorertake5::file_type *edit_plain_text::colorer_select_type()
   {
      colorertake5::file_type *type = NULL;
  /*if (typeDescription != null){
    type = hrcParser->getFileType(typeDescription);
    if (type == null){
      for(int idx = 0;; idx++){
        type = hrcParser->enumerateFileTypes(idx);
        if (type == null) break;
        if (type->getDescription() != null &&
            type->getDescription()->length() >= typeDescription->length() &&
            DString(type->getDescription(), 0, typeDescription->length()).equalsIgnoreCase(typeDescription))
          break;
        if (type->getName()->length() >= typeDescription->length() &&
            DString(type->getName(), 0, typeDescription->length()).equalsIgnoreCase(typeDescription))
          break;
        type = null;
      }
    }
  }*/
//  if (typeDescription == null || type == null){
      ::view * pview = dynamic_cast < ::view *> (this);
   if (pview!= NULL)
   {
      ::user::document_interface * pdoc = pview->get_document();
      if(type == NULL)
      {
         string textStart;
    strsize totalLength = 0;
    for(int i = 0; i < 4 && i < m_lines.getLineCount(); i++){
      string iLine = m_lines.getLine(i);
      textStart += iLine;
      textStart += "\n";
      totalLength += iLine.get_length();
      if (totalLength > 500) break;
    }
    type = System.parser_factory().getHRCParser()->chooseFileType(pdoc->get_path_name(), textStart, 0);
      }
  }
   if(type != NULL)
   {
      type->getBaseScheme();
      setFileType(type);
   }
  return type;
}

   void edit_plain_text::_009OnChar(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }


   bool edit_plain_text::create_control(class control::descriptor * pdescriptor)
   {
      ASSERT(pdescriptor->get_type() == control::type_edit_plain_text);
      if(!create(pdescriptor->m_pform, pdescriptor->m_id))
      {
         TRACE("Failed to create control");
         return false;
      }
      m_bMultiLine = pdescriptor->has_function(control::function_edit_multi_line);
      return control::create_control(pdescriptor);
   }


   bool edit_plain_text::keyboard_focus_is_focusable()
   {
      return IsWindowEnabled() && IsWindowVisible();
   }

   bool edit_plain_text::keyboard_focus_OnSetFocus()
   {
      m_bCaretOn = true;
      m_dwLastCaret = GetTickCount();
      SetTimer(100, 100, NULL);
      _001RedrawWindow();
      return true;
   }



   ex1::tree_item_data * edit_plain_text::on_allocate_item()
   {
      return new plain_text_data::Command;
   }

   void edit_plain_text::on_delete_item(ex1::tree_item_data * pitem)
   {
      delete pitem;
   }

   void edit_plain_text::set_plain_text_data(plain_text_data * pdata, bool bOwnData)
   {
      ::ca::data::writing writing(m_pdata);
      if(m_pdata != NULL && m_bOwnData)
      {
         delete m_pdata;
         m_pdata = NULL;
      }
      m_pdata = pdata;
      m_bOwnData = m_pdata != NULL && bOwnData;
      if(m_pdata != NULL)
      {
         listen(m_pdata);
      }
   }

   void edit_plain_text::_001OnUpdateEditFocusCopy(gen::signal_object * pobj)
   {
      SCAST_PTR(base_cmd_ui, pupdatecmdui, pobj)
      string str;
      _001GetSelText(str);
      pupdatecmdui->m_pcmdui->Enable(str.has_char());
   }

   void edit_plain_text::_001OnEditFocusCopy(gen::signal_object * pobj)
   {
      
      UNREFERENCED_PARAMETER(pobj);

      clipboard_copy();

      pobj->m_bRet = true;
      
   }

   void edit_plain_text::_001OnUpdateEditFocusPaste(gen::signal_object * pobj)
   {
      SCAST_PTR(base_cmd_ui, pupdatecmdui, pobj)
      pupdatecmdui->m_pcmdui->Enable(System.copydesk().get_plain_text().has_char());
   }

   void edit_plain_text::_001OnEditFocusPaste(gen::signal_object * pobj)
   {
      
      UNREFERENCED_PARAMETER(pobj);
      
      clipboard_paste();

      pobj->m_bRet = true;

   }


} // namespace ex1


