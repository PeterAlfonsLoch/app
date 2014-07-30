#include "framework.h"

string str_block(char ch, int32_t iSize);
void str_fill(string & str, char ch);


   string str_block(char ch, int32_t iSize)
   {
      string str;
      for(int32_t i = 0; i < iSize; i++)
      {
         str += ch;
      }
      return str;
   }


   void str_fill(string & str, char ch)
   {
      str = str_block(ch, (int32_t) str.get_length());
   }

namespace user
{


   edit_plain_text::edit_plain_text(sp(::base::application) papp) :
      element(papp),
      ::user::interaction(papp),
      scroll_view(papp),
      colorertake5::base_editor(papp),
//      m_fastblur(allocer()),
  //    m_dibBk(allocer()),
      ::data::data_listener(papp),
      m_keymessageLast(papp)
   {

      m_ptree              = NULL;
      m_bOwnData           = false;

      m_bMultiLine         = true;
      m_bColorerTake5      = false;
      m_bReadOnly          = false;
      m_bSendEnterKey      = false;


      m_straSep.add("\n");
      m_straSep.add("\r");
      m_straSep.add("\r\n");



      m_y                  = -1;
      m_iaLineIndex.allocate(0, 100000);
      m_iaLineEndIndex.allocate(0, 100000);
      m_iaCLineIndex.allocate(0, 1000);
      m_iViewOffset        = 0;
      m_iViewSize          = 1000;
      m_bMouseDown         = false;
      m_dwCaretTime        = 500;
      m_dwLastCaret        = get_tick_count();
      set_cursor(::visual::cursor_text_select);

      m_scrollinfo.m_bVScrollBarEnable = false;
      m_scrollinfo.m_bVScrollBarEnable = false;


   }

   edit_plain_text::~edit_plain_text()
   {
      if(m_bOwnData)
      {
         delete m_ptree;
         m_ptree = NULL;
      }
   }

   void edit_plain_text::install_message_handling(::message::dispatch * pinterface)
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

      IGUI_WIN_MSG_LINK(WM_SIZE, pinterface, this, &::user::edit_plain_text::_001OnSize);

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

   void edit_plain_text::OnDraw(::draw2d::graphics * pdcScreen)
   {
      UNREFERENCED_PARAMETER(pdcScreen);
   }

   /////////////////////////////////////////////////////////////////////////////

   void edit_plain_text::_001OnInitialUpdate(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      _001OnUpdate(::action::source_system);

      ::draw2d::memory_graphics pdc(allocer());
      _001OnCalcLayout(pdc);



      ThreadProcScrollSize((LPVOID) this);


   }

   void edit_plain_text::_001OnDestroy(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }



   void edit_plain_text::VirtualOnSize()
   {
      _001OnUpdate(::action::source_system);

      ::draw2d::memory_graphics pdc(allocer());
      _001OnCalcLayout(pdc);



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

   void edit_plain_text::_001OnPaint(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }



   void edit_plain_text::_001OnDraw(::draw2d::graphics * pdc)
   {

      //return;

      pdc->set_text_rendering(::draw2d::text_rendering_anti_alias);

      COLORREF crBk;
      COLORREF crBkSel;
      COLORREF crSel;
      COLORREF cr;


      cr          = _001GetColor(color_text);
      crBk        = _001GetColor(color_background);
      crSel       = _001GetColor(color_text_selected);
      crBkSel     = _001GetColor(color_background_selected);
      

      ::job * pjob = pdc->m_pjob;

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


      if (pprintjob == NULL)
      {
         
         ::user::interaction::_001OnDraw(pdc);

      }

      /*else if(!session().savings().is_trying_to_save(::base::resource_processing)
      && !session().savings().is_trying_to_save(::base::resource_blur_background))
      {

         pdc->blur(true, 4, rectClient);
         //class imaging & imaging = System.visual().imaging();
         //rect rectClient;
//         GetWindowRect(rectClient);
  //       rectClient.offset(rectClient.top_left());
         if(rectClient.size() != m_dibBk->size())
         {
            m_dibBk->create(rectClient.size());
            m_dibBk->Fill(184, 184, 170);
            HMODULE hmodule = ::LoadLibrary("ca2performance.dll");
            ::visual::fastblur *( *pfnNew )(sp(::base::application)) = (::visual::fastblur *(*)(sp(::base::application))) ::GetProcAddress(hmodule, "new_fastblur");*/
/*            m_fastblur.create(allocer());
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
         class imaging & imaging = System.visual().imaging();
         //_001DrawBackground(pdc, rectClipBox);
         imaging.color_blend(
            pdc,
            rectClient,
            RGB(200, 255, 255),
            127);
      }*/

      color ca;
      ca.set_rgb(RGB(227, 227, 210));
      ca.hls_rate(0.0, -0.33, -0.23);
      COLORREF crBorder = ca.get_rgb() | (0xff << 24);
      pdc->Draw3dRect(rectClient, crBorder, crBorder);

      if(m_ptree == NULL)
         return;

      if(m_iLineHeight == 0)
      {
         pdc->OffsetViewportOrg(-m_scrollinfo.m_ptScroll.x, m_scrollinfo.m_ptScroll.y);
      }
      else
      {
         pdc->OffsetViewportOrg(-m_scrollinfo.m_ptScroll.x, -(m_scrollinfo.m_ptScroll.y % m_iLineHeight));
      }

      ::draw2d::region_sp rgn(allocer());

      rectClient.deflate(2, 2);

      //ClientToScreen(rectClient);
      rgn->create_rect(rectClient);

      double left = rectClient.left;

   //   pdc->SelectClipRgn(&rgn);

      if(session().user()->get_keyboard_focus() == this)
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

      ::draw2d::pen_sp penCaret(allocer());

      ::draw2d::brush_sp brushText(allocer());

      penCaret->create_solid(1.0, ARGB(255, 0, 0, 0));


   /*   rectClient.top = m_pt.y;
      rectClient.left = m_pt.x;
      rectClient.bottom = rectClient.top + m_size.cy;
      rectClient.right = rectClient.left + m_size.cx;*/
//      pdc->FillSolidRect(rectClient, crBk);


      double y = rectClient.top;
      _001GetViewSel(iSelStart, iSelEnd);
      strsize iCursor = iSelEnd;
      sort::sort(iSelStart, iSelEnd);
      select_font(pdc);
      size size3;
      visual::graphics_extension(get_app()).GetTextExtent(pdc, unitext("gGYIﾍ"), size3);
      int32_t iLineHeight = size3.cy;
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
               string strExtent1;
               strExtent1 = strLine.Left(x);
               string strExtent2;
               strExtent2 = strLine.Mid(x, len);
               class size size1;
               visual::graphics_extension(get_app()).GetTextExtent(pdc, strExtent1, size1);
               if(pregion->styled()->bback)
               {
                  pdc->FillSolidRect((int32_t) (left + size1.cx), (int32_t) y, size1.cx, size1.cy, pregion->styled()->back);
               }
               ::draw2d::brush_sp brushText(allocer());
               if(pregion->styled()->bfore)
               {
                  brushText->create_solid(pregion->styled()->fore);
               }
               else
               {
                  brushText->create_solid(cr);
               }
               pdc->SelectObject(brushText);
               pdc->TextOut(left + size1.cx, y, strExtent2);

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
         
            brushText->create_solid(cr);
            pdc->SelectObject(brushText);
            pdc->TextOut(left, y, strExtent1);

            sized size1(0.0, 0.0);
            pdc->GetTextExtent(size1, strLine, (int32_t) strLine.length(), (int32_t) iStart);
            sized sizeb(0.0, 0.0);
            pdc->GetTextExtent(sizeb, strLine, iEnd);
            sized size2(0.0, 0.0);
            pdc->GetTextExtent(size2, strLine, (int32_t) strLine.length(), (int32_t) iEnd);
            size2.cx -= size1.cx;
            
            if(iEnd > iStart)
            {
               pdc->FillSolidRect((int32_t) (left + size1.cx), (int32_t) y, (int32_t) size2.cx, (int32_t) size2.cy, ARGB(255, 120, 240, 180));
               brushText->create_solid(crSel);
               pdc->SelectObject(brushText);
               pdc->TextOut(left + size1.cx, y, strExtent2);
            }

            brushText->create_solid(cr);
            pdc->SelectObject(brushText);
            pdc->TextOut(left + size1.cx + size2.cx, y, strExtent3);

            //maxcy = max(size1.cy, size2.cy);
            //maxcy = max(maxcy, size3.cy);
            if(m_bFocus && m_bCaretOn && i3 == str1.get_length())
            {
               pdc->SelectObject(penCaret);
               pdc->MoveTo(left + size1.cx, y);
               pdc->LineTo(left + size1.cx, y + iLineHeight);
            }
            else if(m_bFocus && m_bCaretOn && i3 == (str1.get_length() + str2.get_length()))
            {
               pdc->SelectObject(penCaret);
               pdc->MoveTo(left + size2.cx + size1.cx, y);
               pdc->LineTo(left + size2.cx + size1.cx, y + iLineHeight);
            }
         }
         y += iLineHeight;
         lim += straLines[i].get_length();
         //ASSERT(FALSE);
      }

   }

   void edit_plain_text::_001OnCreate(signal_details * pobj)
   {

      SCAST_PTR(::message::create, pcreate, pobj);


      if(get_document() != NULL && get_typed_data < plain_text_tree >() != NULL)
      {
         set_root(get_typed_data < plain_text_tree >(), false);
      }
      else
      {
         set_root(new ::user::plain_text_tree(get_app()), true);
      }

      /*
      
      ::data::data * pdataParentLock = oprop("parent_lock_data").cast < ::data::data > ();

      if(pdataParentLock != NULL)
      {
         m_ptree->m_spdataParentLock = pdataParentLock;
      }

      */

      //m_pitem          = get_base_item();

      pcreate->previous();
      m_ptree->m_pfile = new ::file::memory_buffer(get_app());
      if(m_bColorerTake5)
      {
         colorertake5::base_editor::initialize(&m_lines);
         colorertake5::base_editor::setRegionMapper("rgb", "default");
      }
   
      //  m_peditfile = new ::file::edit_buffer(get_app());
      
      m_ptree->m_editfile.SetFile(m_ptree->m_pfile);
      
      //on_update_data(update_hint_set_file);

      m_bGetTextNeedUpdate = true;
      m_bPassword = false;


      SetTimer(100, 100, NULL);
      m_ptree->m_iSelStart  = 0;
      m_ptree->m_iSelEnd = 0;
      _001OnUpdate(::action::source_system);
      _001OnSetText(::action::source_system);


   }

   void edit_plain_text::_001OnContextMenu(signal_details * pobj)
   {
//      SCAST_PTR(::message::context_menu, pcontextmenu, pobj)
//      point point = pcontextmenu->GetPoint();

   }

   void edit_plain_text::_001OnRButtonUp(signal_details * pobj)
   {
      SCAST_PTR(::message::mouse, pmouse, pobj)
      //int32_t iItem;
      //HRESULT hr;
      class point point = pmouse->m_pt;
//      class point ptClient = point;
      ClientToScreen(&point);
      //ScreenToClient(&ptClient);
   /*   ::user::menu menu;
      Ex1TextFile file;

      sp(::base::application) papp = ::core::get_app();

      string strModuleFolder;
      strModuleFolder = papp->m_pcoreapp->get_module_folder();

      if(!spfile->open(::core::dir().path(strModuleFolder, "devedge_contextmenu.xml"), ::file::type_text | ::file::mode_read))
         return;

      string str;
      spfile->read_full_string(str);

      xml::node node(get_app());

      node.Load(str);

      if (menu.LoadMenu(get_app(), &node))
      {
         //::user::menu* pPopup = (::user::menu_item *) menu.GetSubMenu(0);
         //ASSERT(pPopup != NULL);
         sp(::user::frame_window) pframe = (sp(::user::frame_window)) (::window_sp) GetParentFrame();
         //pPopup->TrackPopupMenu(
           // point.x, point.y,
            //(::window_sp) pframe);
         menu.TrackPopupMenu(
            point.x, point.y,
            (::window_sp) pframe);
      }*/
   }





   void edit_plain_text::_001OnSetCursor(signal_details * pobj)
   {
      //pmouse->m_ecursor = ::visual::cursor_arrow;

      pobj->previous();
   }

   void edit_plain_text::_002OnTimer(signal_details * pobj)
   {
      SCAST_PTR(::message::timer, ptimer, pobj)
      if(ptimer->m_nIDEvent >= 100
         && ptimer->m_nIDEvent <= 200)
      {
         if(this == session().user()->get_keyboard_focus())
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
         key_to_char(&m_keymessageLast);
      }

   }

   void edit_plain_text::_002OnKeyDown(signal_details * pobj)
   {
      SCAST_PTR(::message::key, pkey, pobj)
      if(pkey->m_ekey == ::user::key_return)
      {
         if(session().is_key_pressed(::user::key_control) && session().is_key_pressed(::user::key_alt))
         {
            pkey->m_bRet      = false;
            return;
         }
         if((!m_bMultiLine || m_bSendEnterKey) && GetParent() != NULL)
         {
            ::user::control_event ev;
            ev.m_puie         = this;
            ev.m_eevent       = ::user::event_enter_key;
            ev.m_actioncontext        = ::action::source_user;
            BaseOnControlEvent(&ev);
            pobj->m_bRet      = true;
            return;
         }
      }
      else if(pkey->m_ekey == ::user::key_tab)
      {
         if(session().is_key_pressed(::user::key_control)
            && session().is_key_pressed(::user::key_alt))
         {
            pkey->m_bRet      = false;
            return;
         }
         if(!m_bMultiLine)
         {
            ::user::control_event ev;
            ev.m_puie         = this;
            ev.m_eevent       = ::user::event_tab_key;
            ev.m_actioncontext        = ::action::source_user;
            //GetParent()->BaseOnControlEvent(&ev);
            BaseOnControlEvent(&ev);
            pkey->m_bRet      = true;
            return;
         }
      }
      else if(pkey->m_ekey == ::user::key_alt)
      {
         pkey->m_bRet = false;
         return;
      }
      else if(pkey->m_ekey == ::user::key_c)
      {
         if(session().is_key_pressed(::user::key_control))
         {
            pkey->m_bRet      = true;
            clipboard_copy();
            return;
         }
      }
      else if(pkey->m_ekey == ::user::key_v)
      {
         if(session().is_key_pressed(::user::key_control))
         {
            pkey->m_bRet      = true;
            clipboard_paste();
            return;
         }
      }


      m_keymessageLast = *pkey;

      //m_dwLastKeyWparam = pkey->m_nChar;
      //m_dwLastKeyLparam = pkey->m_lparam;
      m_bKeyPressed     = true;
      key_to_char(&m_keymessageLast);
      pkey->m_bRet      = true;
   }

   void edit_plain_text::_002OnKeyUp(signal_details * pobj)
   {
      SCAST_PTR(::message::key, pkey, pobj)
      if(pkey->m_ekey == ::user::key_return)
      {
         if(session().is_key_pressed(::user::key_control)
         &&   session().is_key_pressed(::user::key_alt))
         {
            pkey->m_bRet = false;
            return;
         }
      }
      else if(pkey->m_ekey == ::user::key_alt)
      {
         pkey->m_bRet = false;
      }
      m_bKeyPressed = false;
   }

   void edit_plain_text::_002OnChar(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
//      SCAST_PTR(::message::key, pkey, pobj)
         if(m_bKeyPressed)
         {
               //key_to_char(&m_keymessageLast);
         }
   }





   void edit_plain_text::_001OnHScroll(signal_details * pobj)
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

   void edit_plain_text::pre_translate_message(signal_details * pobj)
   {
      SCAST_PTR(::message::base, pbase, pobj);
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
   void edit_plain_text::key_to_char(::message::key * pkey)
   {
      ::message::key & key = *pkey;
//      LRESULT lresult = 0;
      if(
         key.m_ekey == ::user::key_shift   || key.m_ekey == ::user::key_lshift   || key.m_ekey == ::user::key_rshift
      || key.m_ekey == ::user::key_control || key.m_ekey == ::user::key_lcontrol || key.m_ekey == ::user::key_rcontrol
      || key.m_ekey == ::user::key_alt     || key.m_ekey == ::user::key_lalt     || key.m_ekey == ::user::key_ralt
         )
      {
         return;
      }

      if(key.m_ekey == ::user::key_right   || key.m_ekey == ::user::key_up
      || key.m_ekey == ::user::key_left    || key.m_ekey == ::user::key_down)
      {
         _001OnChar(&key);
         return;
      }


      //LRESULT lresult;
      bool bShift = session().is_key_pressed(::user::key_shift);

      if(key.m_nChar < 256 && isalpha((int32_t) key.m_nChar))
      {

         if(bShift)
         {

            key.m_nChar = toupper((int32_t) key.m_nChar);

         }
         else
         {

            key.m_nChar = tolower((int32_t) key.m_nChar);

         }

      }

      _001OnChar(&key);

   }



   UINT edit_plain_text::ThreadProcScrollSize(LPVOID lpvoid)
   {
      edit_plain_text * pview = (edit_plain_text *) lpvoid;
      ::data::simple_lock lock(pview->m_ptree);

      ::draw2d::graphics_sp graphics(pview->allocer());
      graphics->CreateCompatibleDC(NULL);
      ::draw2d::graphics * pdc = graphics;
      pview->_001OnCalcLayoutProc(pview, pdc);

      pview->_001OnUpdate(::action::source_system);
      return 0;
   }


   void edit_plain_text::_001GetText(string & str) const
   {

      ::data::simple_lock lock(m_ptree);

      if(m_ptree == NULL)
         return;

      file_size iSize = m_ptree->m_editfile.get_length();

      char * psz = str.GetBufferSetLength((strsize)(iSize + 1));
      m_ptree->m_editfile.seek(0, ::file::seek_begin);
      m_ptree->m_editfile.read(psz, (::primitive::memory_size) iSize);
      psz[(::primitive::memory_position) iSize] = '\0';
      str.ReleaseBuffer();
  //    str.replace("\n", "\r\n");

   }


   void edit_plain_text::_001GetSelText(string & str) const
   {

      file_position iEnd;
      file_position iStart;
      if(m_ptree->m_iSelEnd < 0)
      {
         if(m_ptree->m_iSelStart < 0)
         {
            iEnd = (file_position) m_ptree->m_editfile.get_length();
            iStart = 0;
         }
         else
         {
            iStart = m_ptree->m_iSelStart;
            iEnd = (file_position) m_ptree->m_editfile.get_length();
         }
      }
      else
      {
         if(m_ptree->m_iSelStart < 0)
         {
            iEnd = m_ptree->m_iSelEnd;
            iStart = 0;
         }
         else
         {
            iEnd = m_ptree->m_iSelEnd;
            iStart = m_ptree->m_iSelStart;
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
      m_ptree->m_editfile.seek((file_offset) iStart, ::file::seek_begin);
      m_ptree->m_editfile.read(psz, (::primitive::memory_size) (iSize));
      psz[(::primitive::memory_position)iSize] = '\0';
      str.ReleaseBuffer();
      str.replace("\n", "\r\n");
   }

   void edit_plain_text::_001SetSelText(const char * psz, ::action::context actioncontext)
   {
      m_ptree->m_editfile.seek(m_ptree->m_iSelStart, ::file::seek_begin);
       m_ptree->m_editfile.Delete((primitive::memory_size) (m_ptree->m_iSelEnd - m_ptree->m_iSelStart));
      m_ptree->m_editfile.seek(m_ptree->m_iSelStart, ::file::seek_begin);
      m_ptree->m_editfile.Insert(psz, strlen(psz));
      _001OnUpdate(actioncontext);
      RedrawWindow();
   }

   void edit_plain_text::_001SetSel(strsize iSelStart, strsize iSelEnd)
   {
      m_ptree->m_iSelStart = iSelStart;
      m_ptree->m_iSelEnd = iSelEnd;
      RedrawWindow();
   }

   void edit_plain_text::_002OnLButtonDown(signal_details * pobj)
   {
      SCAST_PTR(::message::mouse, pmouse, pobj)
      point pt = pmouse->m_pt;
      ScreenToClient(&pt);
      m_bMouseDown = true;
      ::draw2d::memory_graphics pdc(allocer());
      if(pdc.is_null())
         return;
      m_ptree->m_iSelStart = char_hit_test(pdc, pt.x, pt.y);
      m_ptree->m_iSelEnd = m_ptree->m_iSelStart;

      RedrawWindow();
      session().user()->set_keyboard_focus(this);
      session().user()->set_mouse_focus_LButtonDown(this);
      pmouse->m_bRet = true;
      pmouse->set_lresult(1);
   }

   void edit_plain_text::_002OnLButtonUp(signal_details * pobj)
   {
      SCAST_PTR(::message::mouse, pmouse, pobj)
      point pt = pmouse->m_pt;
      ScreenToClient(&pt);
      ::draw2d::memory_graphics pdc(allocer());
      m_ptree->m_iSelEnd = char_hit_test(pdc, pt.x, pt.y);
      m_iColumn = SelToColumn(m_ptree->m_iSelEnd);

      RedrawWindow();
      m_bMouseDown = false;
      pmouse->m_bRet = true;
      pmouse->set_lresult(1);
      //System.simple_message_box(m_strText);
   }

   void edit_plain_text::_002OnRButtonDown(signal_details * pobj)
   {
      SCAST_PTR(::message::mouse, pmouse, pobj)
      point pt = pmouse->m_pt;
      ScreenToClient(&pt);
      m_bMouseDown = true;
      ::draw2d::memory_graphics pdc(allocer());
      m_ptree->m_iSelStart = char_hit_test(pdc, pt.x, pt.y);
      m_ptree->m_iSelEnd = m_ptree->m_iSelStart;

      RedrawWindow();
      session().user()->set_keyboard_focus(this);
      session().user()->set_mouse_focus_RButtonDown(this);
      pmouse->m_bRet = true;
      pmouse->set_lresult(1);
   }

   void edit_plain_text::_002OnRButtonUp(signal_details * pobj)
   {
      SCAST_PTR(::message::mouse, pmouse, pobj)
      point pt = pmouse->m_pt;
      ScreenToClient(&pt);
      ::draw2d::memory_graphics pdc(allocer());
      m_ptree->m_iSelEnd = char_hit_test(pdc, pt.x, pt.y);
      m_iColumn = SelToColumn(m_ptree->m_iSelEnd);

      RedrawWindow();
      m_bMouseDown = false;

      track_popup_xml_matter_menu("ystem/edit_focus_popup.xml", 0, pobj);

      pmouse->set_lresult(1);
      pmouse->m_bRet = true;
   }

   void edit_plain_text::_001OnCalcLayoutProc(::user::elemental * pview, ::draw2d::graphics * pdc)
   {
      
      ::data::simple_lock lockRoot(m_ptree);

      UNREFERENCED_PARAMETER(pview);
      
      select_font(pdc);


      int32_t y = 0;
///      int32_t i = 1;
      pdc->set_text_rendering(::draw2d::text_rendering_anti_alias_grid_fit);
      size size3 = pdc->GetTextExtent(unitext("gqYALﾍ"));

      rect rectClient;

      GetClientRect(rectClient);

      m_iLineHeight = size3.cy;
      //char buf[4096 + 1];
      //UINT uiRead;
      //LPTSTR lpsz;
      m_ptree->m_editfile.seek(0, ::file::seek_begin);
      y = (int32_t) (m_iLineHeight * m_iaLineIndex.get_size());
      if(y <= 0)
         y = 200;
   //   pview->SetScrollSizes(MM_TEXT,
     //    m_size);
   }

   void edit_plain_text::_001OnCalcLayout(::draw2d::graphics * pdc)
   {

      select_font(pdc);

      stringa & straLines = m_lines.lines;
      strsize iSelStart;
      strsize iSelEnd;
      _001GetViewSel(iSelStart, iSelEnd);
      //int32_t lim = 0;
      int32_t iLineHeight;
//      int32_t y = 0;
//      bool bFound = false;
      string strLine;
      sized size3;
      pdc->set_text_rendering(::draw2d::text_rendering_anti_alias_grid_fit);
      pdc->GetTextExtent(size3, unitext("gqYALﾍWM"));
      sized size;
      m_scrollinfo.m_sizeTotal.cx = 0;
      iLineHeight = (int32_t) size3.cy;
      for(int32_t i = 0; i < straLines.get_size(); i++)
      {
         strLine = straLines[i];
         strLine.replace("\t", "   ");
         size = (uint32_t) (strLine.get_length() * size3.cx / 8);
//         maxcy = max(size.cy, size3.cy);
         if(size.cx > m_scrollinfo.m_sizeTotal.cx)
            m_scrollinfo.m_sizeTotal.cx = (int32_t) size.cx;

      }
      m_scrollinfo.m_sizeTotal.cy = ((int32_t) m_iaLineIndex.get_count() * iLineHeight);
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

   index edit_plain_text::SelToLineX(strsize iSel, int32_t & x)
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
            ::draw2d::memory_graphics pgraphics(allocer());

            select_font(pgraphics);
            pgraphics->set_text_rendering(::draw2d::text_rendering_anti_alias_grid_fit);
            size size1 = pgraphics->GetTextExtent(straLines[i], (int32_t) straLines[i].length(), (int32_t) (iSel - i1));
            size size2 = pgraphics->GetTextExtent(straLines[i], (int32_t) iSel - i1);



            x = (size1.cx + size2.cx) / 2;

            return i;
         }
      }
      return -1;
   }


   strsize edit_plain_text::LineColumnToSel(index iLine, index iColumn)
   {
      //int32_t i1;
//      int32_t i2 = 0;
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
      for(int32_t i = 0; i < iLine; i++)
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

   strsize edit_plain_text::LineXToSel(index iLine, int32_t x)
   {

      ::draw2d::memory_graphics pgraphics(allocer());

      select_font(pgraphics);

      pgraphics->set_text_rendering(::draw2d::text_rendering_anti_alias_grid_fit);
      size size3 = pgraphics->GetTextExtent(unitext("gqYALﾍWM"));

      int32_t iLineHeight = size3.cy;

      int32_t y = (int32_t) (iLineHeight * iLine + iLineHeight / 2 - m_scrollinfo.m_ptScroll.y);

      strsize iChar = char_hit_test(pgraphics, x, y);



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
      for(int32_t i = 0; i < iLine; i++)
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

   strsize edit_plain_text::char_hit_test(::draw2d::graphics * pdc, int32_t px, int32_t py)
   {
      
      select_font(pdc);

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
      int32_t lim = 0;
      int32_t iLineHeight;
      int32_t y = 0;
      bool bFound = false;
      string strLine;
      string strExtent;
      size size3;
      visual::graphics_extension(get_app()).GetTextExtent(pdc, unitext("gqYALﾍ"), size3);

      iLineHeight = size3.cy;

      strsize iOffset = 0;
      stringa stra;
      for(int32_t i = 0; i < straLines.get_size(); i++)
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
      int32_t lim2 = 0;
      int32_t lim1;
      const char * psz = strLine;
      const char * pszEnd = psz;
      const char * pszPrevious = psz;
      for(;; )
      {
         pszPrevious = pszEnd;
         pszEnd = ::str::utf8_inc(pszEnd);
         lim1 = lim2;
         strExtent = string(psz, pszEnd - psz);
         strExtent.replace("\t", "   ");
         class size size;
         class ::size size1 = pdc->GetTextExtent(strLine, (int32_t) strLine.length(), (int32_t) strExtent.length());
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
      return (strsize) min((strsize)(iOffset + strLine.get_length() + m_iViewOffset), (strsize)m_ptree->m_editfile.get_length());
   }

   void edit_plain_text::_002OnMouseMove(signal_details * pobj)
   {
      SCAST_PTR(::message::mouse, pmouse, pobj)
      //pmouse->m_ecursor = ::visual::cursor_text_select;
      point pt = pmouse->m_pt;
      ScreenToClient(&pt);

      pmouse->m_ecursor = ::visual::cursor_text_select;

      if(m_bMouseDown)
      {
         ::draw2d::memory_graphics pdc(allocer());
         m_ptree->m_iSelEnd = char_hit_test(pdc, pt.x, pt.y);

       //  RedrawWindow();
      }

   }

   void edit_plain_text::_001GetViewSel(strsize &iSelStart, strsize &iSelEnd)
   {
      
      if (m_ptree == NULL)
      {

         iSelStart = -1;

         iSelEnd = -1;

      }
      else
      {

         iSelStart = m_ptree->m_iSelStart - m_iViewOffset;

         iSelEnd = m_ptree->m_iSelEnd - m_iViewOffset;

      }

   }

   void edit_plain_text::on_updata_data(::data::simple_data * pdata, int32_t iHint)
   {
      if(pdata == m_ptree)
      {
         if(iHint == plain_text_tree::update_hint_set_file)
         {
            OnFileUpdate();
         }
      }
   }

   void edit_plain_text::FileSave()
   {
      m_ptree->m_editfile.flush();
   }

   void edit_plain_text::OnFileUpdate()
   {
      m_bGetTextNeedUpdate = true;
      CreateLineIndex();
      m_y = -1;
   }

   void edit_plain_text::CreateLineIndex()
   {
      //int32_t y = 0;
      int32_t i = 1;
      char buf[1024 * 256 + 1];
      primitive::memory_size uiRead;
      char * lpsz;
      m_iaLineIndex.remove_all();
      m_iaLineEndIndex.remove_all();
      m_ptree->m_editfile.seek(0, ::file::seek_begin);
      if(m_scrollinfo.m_sizeTotal.cx <= 0)
         m_scrollinfo.m_sizeTotal.cx = 200;
      int32_t iLineSize = 0;
      char flags[3];
      flags[0] = 3;
      flags[1] = 1;
      flags[2] = 2;
      while((uiRead = m_ptree->m_editfile.read(buf, sizeof(buf) - 1)) > 0)
      {
         buf[uiRead] = '\0';
         lpsz = buf;
         while(*lpsz != '\0')
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

   void edit_plain_text::_001OnChar(signal_details * pobj)
   {
      
      {
      ::data::simple_lock lockRoot(m_ptree);
      

      _009OnChar(pobj);
      if(pobj->m_bRet)
         return;
      SCAST_PTR(::message::key, pkey, pobj)

      string strChar;

//      pkey->m_nChar = pkey->m_charrecv->KeyCode;

      if(pkey->m_ekey == ::user::key_s)
      {
         if(session().is_key_pressed(::user::key_control))
         {
            return;
         }
      }
      else if(pkey->m_ekey == ::user::key_z)
      {
         if(session().is_key_pressed(::user::key_control))
         {
            Undo();
            return;
         }
      }
      else if(pkey->m_ekey == ::user::key_y)
      {
         if(session().is_key_pressed(::user::key_control))
         {
            Redo();
            return;
         }
      }

      bool bShift = session().is_key_pressed(::user::key_shift);

      if(pkey->m_ekey == ::user::key_back)
      {
         if(!m_bReadOnly)
         {
            strsize i1 = m_ptree->m_iSelStart;
            strsize i2 = m_ptree->m_iSelEnd;
            if(i1 != i2)
            {
               plain_text_set_sel_command * psetsel = new plain_text_set_sel_command;
               psetsel->m_iPreviousSelStart = m_ptree->m_iSelStart;
               psetsel->m_iPreviousSelEnd = m_ptree->m_iSelEnd;
               ::sort::sort(i1, i2);
               m_ptree->m_editfile.seek(i1, ::file::seek_begin);
               m_ptree->m_editfile.Delete((primitive::memory_size)(i2 - i1));
               IndexRegisterDelete(i1, i2 - i1);
               m_ptree->m_iSelEnd = i1;
               m_ptree->m_iSelStart = m_ptree->m_iSelEnd;
               psetsel->m_iSelStart = m_ptree->m_iSelStart;
               psetsel->m_iSelEnd = m_ptree->m_iSelEnd;
               MacroBegin();
               MacroRecord(psetsel);
               MacroRecord(new plain_text_file_command());
               MacroEnd();
               _001OnUpdate(::action::source_user);
            }
            else if(m_ptree->m_iSelEnd >= 0 && m_ptree->m_editfile.get_length() > 0)
            {
               plain_text_set_sel_command * psetsel = new plain_text_set_sel_command;
               psetsel->m_iPreviousSelStart = m_ptree->m_iSelStart;
               psetsel->m_iPreviousSelEnd = m_ptree->m_iSelEnd;
               char buf[512];
               memset(buf, 0, sizeof(buf));
               strsize iBegin = max(0, m_ptree->m_iSelEnd - 256);
               strsize iCur = m_ptree->m_iSelEnd - iBegin;
               m_ptree->m_editfile.seek(iBegin, ::file::seek_begin);
               m_ptree->m_editfile.read(buf, sizeof(buf));
               const char * psz = ::str::utf8_dec(buf, &buf[iCur]);
               strsize iMultiByteUtf8DeleteCount = &buf[iCur] - psz;
               m_ptree->m_iSelEnd -= iMultiByteUtf8DeleteCount;
               m_ptree->m_editfile.seek(m_ptree->m_iSelEnd, ::file::seek_begin);
               m_ptree->m_editfile.Delete((primitive::memory_size) iMultiByteUtf8DeleteCount);
               IndexRegisterDelete(m_ptree->m_iSelEnd, iMultiByteUtf8DeleteCount);
               m_ptree->m_iSelStart = m_ptree->m_iSelEnd;
               psetsel->m_iSelStart = m_ptree->m_iSelStart;
               psetsel->m_iSelEnd = m_ptree->m_iSelEnd;
               MacroBegin();
               MacroRecord(psetsel);
               MacroRecord(new plain_text_file_command());
               MacroEnd();
               _001OnUpdate(::action::source_user);
            }
         }
      }
      else if(pkey->m_ekey == ::user::key_delete)
      {
         if(!m_bReadOnly)
         {
            strsize i1 = m_ptree->m_iSelStart;
            strsize i2 = m_ptree->m_iSelEnd;
            if(i1 != i2)
            {
               plain_text_set_sel_command * psetsel = new plain_text_set_sel_command;
               psetsel->m_iPreviousSelStart = m_ptree->m_iSelStart;
               psetsel->m_iPreviousSelEnd = m_ptree->m_iSelEnd;
               ::sort::sort(i1,i2);
               m_ptree->m_editfile.seek(i1,::file::seek_begin);
               m_ptree->m_editfile.Delete((primitive::memory_size) (i2 - i1));
               m_ptree->m_iSelEnd = i1;
               m_ptree->m_iSelStart = m_ptree->m_iSelEnd;
               psetsel->m_iSelStart = m_ptree->m_iSelStart;
               psetsel->m_iSelEnd = m_ptree->m_iSelEnd;
               MacroBegin();
               MacroRecord(psetsel);
               MacroRecord(new plain_text_file_command());
               MacroEnd();
               _001OnUpdate(::action::source_user);
            }
            else if(natural(m_ptree->m_iSelEnd) < m_ptree->m_editfile.get_length())
            {
               char buf[512];
               memset(buf,0,sizeof(buf));
               strsize iBegin = max(0,m_ptree->m_iSelEnd - 256);
               strsize iCur = m_ptree->m_iSelEnd - iBegin;
               m_ptree->m_editfile.seek(iBegin,::file::seek_begin);
               m_ptree->m_editfile.read(buf,sizeof(buf));
               const char * psz = ::str::utf8_dec(buf,&buf[iCur]);
               strsize iMultiByteUtf8DeleteCount = &buf[iCur] - psz;
               m_ptree->m_editfile.seek(m_ptree->m_iSelEnd,::file::seek_begin);
               m_ptree->m_editfile.Delete((primitive::memory_size) (iMultiByteUtf8DeleteCount));
               IndexRegisterDelete(m_ptree->m_iSelEnd,iMultiByteUtf8DeleteCount);
               m_ptree->m_iSelStart = m_ptree->m_iSelEnd;
               MacroBegin();
               MacroRecord(new plain_text_file_command());
               MacroEnd();
               _001OnUpdate(::action::source_user);
            }
         }
      }
      else if(pkey->m_ekey == ::user::key_up)
      {
         int32_t x;
         index iLine = SelToLineX(m_ptree->m_iSelEnd, x);
         iLine--;
         m_ptree->m_iSelEnd = LineXToSel(iLine, x);
         if(!bShift)
         {
            m_ptree->m_iSelStart = m_ptree->m_iSelEnd;
         }
         RedrawWindow();
      }
      else if(pkey->m_ekey == ::user::key_down)
      {
         int32_t x;
         index iLine = SelToLineX(m_ptree->m_iSelEnd, x);
         iLine++;
         m_ptree->m_iSelEnd = LineXToSel(iLine, x);
         if(!bShift)
         {
            m_ptree->m_iSelStart = m_ptree->m_iSelEnd;
         }
         RedrawWindow();
      }
      else if(pkey->m_ekey == ::user::key_right)
      {
         if(!bShift && m_ptree->m_iSelStart > m_ptree->m_iSelEnd)
         {
            m_ptree->m_iSelEnd = m_ptree->m_iSelStart;
         }
         else if(!bShift && m_ptree->m_iSelEnd > m_ptree->m_iSelStart)
         {
            m_ptree->m_iSelStart = m_ptree->m_iSelEnd;
         }
         else if(natural(m_ptree->m_iSelEnd) < m_ptree->m_editfile.get_length())
         {
            char buf[32];
            m_ptree->m_editfile.seek(m_ptree->m_iSelEnd, ::file::seek_begin);
            primitive::memory_size uiRead = m_ptree->m_editfile.read(buf, 32);
            if(uiRead == 2 &&
               buf[0] == '\r' &&
               buf[1] == '\n')
            {
               m_ptree->m_iSelEnd += 2;
            }
            else
            {
               m_ptree->m_iSelEnd += ::str::utf8_inc(buf) - buf;
            }
            if(!bShift)
            {
               m_ptree->m_iSelStart = m_ptree->m_iSelEnd;
            }
         }
         RedrawWindow();
      }
      else if(pkey->m_ekey == ::user::key_left)
      {
         if(!bShift && m_ptree->m_iSelStart < m_ptree->m_iSelEnd)
         {
            m_ptree->m_iSelEnd = m_ptree->m_iSelStart;
         }
         else if(!bShift && m_ptree->m_iSelEnd < m_ptree->m_iSelStart)
         {
            m_ptree->m_iSelStart = m_ptree->m_iSelEnd;
         }
         else if(m_ptree->m_iSelEnd > 0)
         {
            if(m_ptree->m_iSelEnd > 2)
            {
               char buf[64];
               char * psz;
               m_ptree->m_editfile.seek(max(0, m_ptree->m_iSelEnd - 32), ::file::seek_begin);
               psz = &buf[min(32, m_ptree->m_iSelEnd)];
               primitive::memory_size uiRead = m_ptree->m_editfile.read(buf, 64);
               if(uiRead == 2 &&
                  psz[0] == '\r' &&
                  psz[1] == '\n')
               {
                  m_ptree->m_iSelEnd -= 2;
               }
               else
               {
                  m_ptree->m_iSelEnd -= psz - ::str::utf8_dec(buf, psz);
               }
            }
            else
            {
               m_ptree->m_iSelEnd--;
            }
            if(!bShift)
            {
               m_ptree->m_iSelStart = m_ptree->m_iSelEnd;
            }
         }
         RedrawWindow();
      }
      else if(pkey->m_ekey == ::user::key_home)
      {
         index iLine = SelToLine(m_ptree->m_iSelEnd);
         m_ptree->m_iSelEnd = LineColumnToSel(iLine, 0);
         if(!bShift)
         {
            m_ptree->m_iSelStart = m_ptree->m_iSelEnd;
         }
         RedrawWindow();
      }
      else if(pkey->m_ekey == ::user::key_end)
      {
         index iLine = SelToLine(m_ptree->m_iSelEnd);
         m_ptree->m_iSelEnd = LineColumnToSel(iLine, -1);
         if(!bShift)
         {
            m_ptree->m_iSelStart = m_ptree->m_iSelEnd;
         }
         RedrawWindow();
      }
      else
      {
         if(!m_bReadOnly)
         {
            if(pkey->m_ekey == ::user::key_return)
            {
               // Kill Focus => Kill Key Repeat timer
               //System.simple_message_box("VK_RETURN reached edit_plain_text");
            }
            plain_text_set_sel_command * psetsel = new plain_text_set_sel_command;
            psetsel->m_iPreviousSelStart = m_ptree->m_iSelStart;
            psetsel->m_iPreviousSelEnd = m_ptree->m_iSelEnd;
            m_ptree->m_editfile.MacroBegin();
            strsize i1 = m_ptree->m_iSelStart;
            strsize i2 = m_ptree->m_iSelEnd;
            ::sort::sort(i1, i2);
            m_ptree->m_editfile.seek(i1, ::file::seek_begin);
            m_ptree->m_editfile.Delete((primitive::memory_size) (i2 - i1));
            IndexRegisterDelete(i1, i2 - i1);
            m_ptree->m_iSelEnd = i1;
            m_ptree->m_editfile.seek(m_ptree->m_iSelEnd, ::file::seek_begin);
            string str;
            char ch = (char) pkey->m_nChar;
            if(ch == '\r')
               ch = '\n';
            int32_t iChar = (int32_t) pkey->m_nChar;
            if(iChar == '\r')
               iChar = '\n';
            if(bShift)
            {
               iChar |= 0x80000000;
            }
            int32_t iCode = pkey->m_nFlags & 0xff;
            if(bShift)
            {
               iCode |= 0x80000000;
            }
            string strMap;
            str = session().user()->keyboard().process_key(pkey->m_ekey);
            m_ptree->m_iSelEnd += str.get_length();
            m_ptree->m_iSelStart = m_ptree->m_iSelEnd;
           m_ptree-> m_editfile.Insert(str, str.get_length());
            IndexRegisterInsert(m_ptree->m_iSelEnd, str);
            m_ptree->m_editfile.MacroEnd();
            psetsel->m_iSelStart = m_ptree->m_iSelStart;
            psetsel->m_iSelEnd = m_ptree->m_iSelEnd;
            MacroBegin();
            MacroRecord(psetsel);
            MacroRecord(new plain_text_file_command());
            MacroEnd();
            _001OnUpdate(::action::source_user);
            //_001OnAfterChangeText(::action::source_user);
         }
      }
      if(pkey->m_ekey != ::user::key_up
      && pkey->m_ekey != ::user::key_down)
      {
         m_iColumn = SelToColumn(m_ptree->m_iSelEnd);
      }
      m_dwLastCaret = ::get_tick_count();
      m_bCaretOn = true;
      }
      RedrawWindow();


   }





   void edit_plain_text::_001OnSysChar(signal_details * pobj)
   {
      ::data::simple_lock lockRoot(m_ptree);
      SCAST_PTR(::message::key, pkey, pobj)
      if(pkey->m_ekey == ::user::key_delete)
      {
         if(!m_bReadOnly)
         {
            strsize i1 = m_ptree->m_iSelStart;
            strsize i2 = m_ptree->m_iSelEnd;
            if(i1 != i2)
            {
               ::sort::sort(i1, i2);
               m_ptree->m_editfile.seek(i1, ::file::seek_begin);
               m_ptree->m_editfile.Delete((primitive::memory_size) (i2 - i1));
               m_ptree->m_iSelEnd = i1;
               m_ptree->m_iSelStart = m_ptree->m_iSelEnd;
            }
            else if(natural(m_ptree->m_iSelEnd) < m_ptree->m_editfile.get_length())
            {
               char buf[512];
               memset(buf, 0, sizeof(buf));
               strsize iBegin = max(0, m_ptree->m_iSelEnd - 256);
               strsize iCur = m_ptree->m_iSelEnd - iBegin;
               m_ptree->m_editfile.seek(iBegin, ::file::seek_begin);
               m_ptree->m_editfile.read(buf, sizeof(buf));
               const char * psz = ::str::utf8_dec(buf, &buf[iCur]);
               strsize iMultiByteUtf8DeleteCount = &buf[iCur] - psz;
               m_ptree->m_editfile.seek(m_ptree->m_iSelEnd, ::file::seek_begin);
               m_ptree->m_editfile.Delete((primitive::memory_size) (iMultiByteUtf8DeleteCount));
               IndexRegisterDelete(m_ptree->m_iSelEnd, iMultiByteUtf8DeleteCount);
               m_ptree->m_iSelStart = m_ptree->m_iSelEnd;
            }
         }
      }
   }


   void edit_plain_text::_001OnKeyboardFocusTimer(int32_t iTimer)
   {
      if(iTimer == 0)
      {
         if(m_dwLastCaret + m_dwCaretTime < get_tick_count())
         {
            m_dwLastCaret = get_tick_count();
            m_bCaretOn = !m_bCaretOn;
            //RedrawWindow();
            RedrawWindow();
         }
      }
   }

   void edit_plain_text::OneLineUp()
   {
      m_scrollinfo.m_ptScroll.y -= m_iLineHeight;
      if(m_scrollinfo.m_ptScroll.y < m_scrollinfo.m_rectMargin.top)
         m_scrollinfo.m_ptScroll.y = m_scrollinfo.m_rectMargin.top;
      int32_t iHeight = 0;
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
      int32_t iLineSize;
      UINT uiRead;
      int32_t iPos = 0;
      int32_t iLineStart = -1;
      int32_t iLineEnd = -1;
      int32_t iLineStartRemain = -1;
      int32_t iLineEndRemain = -1;
      int32_t iLine = 0;
      int32_t i = 0;
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
         m_editfileLineIndex.seek(5 * (iLineStart + 1), ::file::seek_begin);
         m_editfileLineIndex.Delete(5 * (iLineEnd - iLineStart));
      }
      m_editfileLineIndex.seek(5 * iLineStart, ::file::seek_begin);
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


   void edit_plain_text::_001OnUpdate(::action::context actioncontext)
   {

      string str;
      _001GetText(str);

      if(m_ptree->m_iSelStart > str.get_length())
         m_ptree->m_iSelStart = str.get_length();
      else if(m_ptree->m_iSelStart < 0)
         m_ptree->m_iSelStart = 0;

      if(m_ptree->m_iSelEnd > str.get_length())
         m_ptree->m_iSelEnd = str.get_length();
      else if(m_ptree->m_iSelEnd < 0)
         m_ptree->m_iSelEnd = 0;

      m_bGetTextNeedUpdate = 1;
      CreateLineIndex();
      m_y = -1;
      ::draw2d::graphics_sp dc(allocer());
      dc->CreateCompatibleDC(NULL);
      _001OnCalcLayout(dc);
      lineCountEvent(m_lines.lines.get_count());

      try
      {

         _001OnSetText(actioncontext);

      }
      catch(...)
      {

      }


      try
      {

         _001OnAfterChangeText(actioncontext);

      }
      catch(...)
      {

      }

   }



   void edit_plain_text::MacroBegin()
   {
      sp(::user::plain_text_group_command) pgroupcommand = new plain_text_group_command;
      pgroupcommand->m_pparent = m_ptree->m_pgroupcommand;
      m_ptree->m_pgroupcommand = pgroupcommand;
   }

   void edit_plain_text::MacroEnd()
   {
      if(m_ptree->m_pgroupcommand == NULL)
      {
         ASSERT(FALSE);
         return;
      }
      if(m_ptree->m_pgroupcommand->m_pparent == NULL)
      {
         MacroRecord(m_ptree->m_pgroupcommand);
      }
      m_ptree->m_pgroupcommand = m_ptree->m_pgroupcommand->m_pparent;
   }


   void edit_plain_text::MacroRecord(sp(plain_text_command) pcommand)
   {
      if(m_ptree->m_pgroupcommand != NULL && m_ptree->m_pgroupcommand != pcommand)
      {
         m_ptree->m_pgroupcommand->add(pcommand);
         return;
      }
      m_pitem = m_ptree->insert_item(pcommand, ::data::RelativeMacroRecord, m_pitem);
   }


   bool edit_plain_text::Undo()
   {

      if(!CanUndo())
         return false;

      sp(plain_text_command) pcommand = m_pitem->m_pitem;

      pcommand->Undo(m_ptree);

      m_pitem = m_pitem->get_previous();

      CreateLineIndex();

      m_bGetTextNeedUpdate = true;

      _001OnUpdate(::action::source_user);

      _001OnAfterChangeText(::action::source_user);

      return true;

   }


   bool edit_plain_text::Redo()
   {
      if(m_pitem == NULL)
      {
         return false;
      }
      if(m_ptree->m_iBranch < 0
         || m_ptree->m_iBranch >= GetRedoBranchCount())
      {
         return false;
      }
      sp(plain_text_command) pcommand = NULL;
      sp(::data::tree_item) ptreeitem;
      if(m_ptree->m_iBranch < m_pitem->get_expandable_children_count())
      {
         ptreeitem = m_pitem->get_expandable_child(m_ptree->m_iBranch);
      }
      else
         ptreeitem = m_pitem->get_next();
      if(ptreeitem == NULL)
         return false;
      m_pitem = ptreeitem;
      pcommand = (sp(plain_text_command)) ptreeitem->m_pitem;
      pcommand->Redo(m_ptree);
      CreateLineIndex();
      m_bGetTextNeedUpdate = true;

      _001OnUpdate(::action::source_user);
      _001OnAfterChangeText(::action::source_user);

      return true;
   }

   bool edit_plain_text::CanUndo()
   {
      return m_pitem != m_ptree->get_base_item();
   }

   bool edit_plain_text::CanRedo()
   {
      return m_ptree->m_iBranch < m_pitem->get_expandable_children_count()
         || m_pitem->get_next(false, false) != NULL;
   }

   ::count edit_plain_text::GetRedoBranchCount()
   {
      return m_pitem->get_expandable_children_count()
           + (m_pitem->next() != NULL ? 1 : 0)
           + (m_pitem->first_child() != NULL ? 1 : 0);
   }



   void edit_plain_text::_001SetText(const string & str, ::action::context actioncontext)
   {
      ::data::simple_lock lockRoot(m_ptree);
      m_ptree->m_editfile.seek(0, ::file::seek_begin);
      m_ptree->m_editfile.Delete((::primitive::memory_size)m_ptree->m_editfile.get_length());
      m_ptree->m_editfile.seek(0, ::file::seek_begin);
      m_ptree->m_editfile.Insert(str, str.get_length());
      _001OnUpdate(actioncontext);
      _001OnSetText(actioncontext);
      RedrawWindow();
   }


   void edit_plain_text::keyboard_focus_OnKeyDown(signal_details * pobj)
   {
      _002OnKeyDown(pobj);
   }

   void edit_plain_text::keyboard_focus_OnKeyUp(signal_details * pobj)
   {
      _002OnKeyUp(pobj);
   }

   void edit_plain_text::keyboard_focus_OnChar(signal_details * pobj)
   {
      _002OnChar(pobj);
   }


   void edit_plain_text::_001OnAfterChangeText(::action::context actioncontext)
   {
      ::user::control_event ev;
      ev.m_puie         = this;
      ev.m_eevent       = ::user::event_after_change_text;
      ev.m_actioncontext = actioncontext;
      BaseOnControlEvent(&ev);
   }

   void edit_plain_text::clipboard_copy()
   {
      string str;
      _001GetSelText(str);
      session().copydesk().set_plain_text(str);
   }

   void edit_plain_text::clipboard_paste()
   {

      string str;
      str = session().copydesk().get_plain_text();
      str.replace("\r\n", "\n");
      _001SetSelText(str, ::action::source::user());
      MacroBegin();
      MacroRecord(new plain_text_file_command());
      MacroEnd();

      _001OnUpdate(::action::source::user());
      _001OnAfterChangeText(::action::source::user());

   }


   void edit_plain_text::_001OnSetText(::action::context actioncontext)
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
      m_ptree->m_editfile.seek(m_iViewOffset, ::file::seek_begin);
      iLine = m_iLineOffset;
      i = 0;
      ::index iLineStart = should_load_full_file() ? 0 : m_iLineOffset;
      ::index iLineEnd = should_load_full_file() ? m_iaLineIndex.get_size() - 1 : min(m_iaLineIndex.get_size(), m_iLineCount) - 1;
      for(::index iLine = iLineStart; i <= iLineEnd && iLine < m_iaLineIndex.get_size(); i++, iLine++)
      {
         strsize iLen = m_iaLineIndex[iLine];
         char * lpsz = str.GetBufferSetLength(iLen + 1);
         m_ptree->m_editfile.read(lpsz, iLen);
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
  /*if (typeDescription != NULL){
    type = hrcParser->getFileType(typeDescription);
    if (type == NULL){
      for(int32_t idx = 0;; idx++){
        type = hrcParser->enumerateFileTypes(idx);
        if (type == NULL) break;
        if (type->getDescription() != NULL &&
            type->getDescription()->length() >= typeDescription->length() &&
            DString(type->getDescription(), 0, typeDescription->length()).equalsIgnoreCase(typeDescription))
          break;
        if (type->getName()->length() >= typeDescription->length() &&
            DString(type->getName(), 0, typeDescription->length()).equalsIgnoreCase(typeDescription))
          break;
        type = NULL;
      }
    }
  }*/
//  if (typeDescription == NULL || type == NULL){
      sp(::user::impact) pview =  (this);
   if (pview!= NULL)
   {
      sp(::user::document) pdoc = pview->get_document();
      if(type == NULL)
      {
         string textStart;
    strsize totalLength = 0;
    for(int32_t i = 0; i < 4 && i < m_lines.getLineCount(); i++){
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

   void edit_plain_text::_009OnChar(signal_details * pobj)
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
      ShowWindow(SW_HIDE);
      m_bMultiLine = pdescriptor->has_function(control::function_edit_multi_line);
      return control::create_control(pdescriptor);
   }


   bool edit_plain_text::keyboard_focus_is_focusable()
   {
      return is_window_enabled() && IsWindowVisible();
   }

   bool edit_plain_text::keyboard_focus_OnSetFocus()
   {
      m_bCaretOn = true;
      m_dwLastCaret = get_tick_count();
      SetTimer(100, 100, NULL);
      RedrawWindow();
      return true;
   }



   sp(::data::item) edit_plain_text::on_allocate_item()
   {
      return new plain_text_command;
   }


   void edit_plain_text::set_root(plain_text_tree * pdata, bool bOwnData)
   {
      ::data::simple_lock lockRoot(m_ptree);
      if(m_ptree != NULL && m_bOwnData)
      {
         delete m_ptree;
         m_ptree = NULL;
      }
      m_ptree = pdata;
      m_pitem = m_ptree->get_base_item();
      m_bOwnData = m_ptree != NULL && bOwnData;
      if(m_ptree != NULL)
      {
         listen(m_ptree);
      }
   }

   void edit_plain_text::_001OnUpdateEditFocusCopy(signal_details * pobj)
   {
      SCAST_PTR(::base::cmd_ui, pupdatecmdui, pobj)
      string str;
      _001GetSelText(str);
      pupdatecmdui->m_pcmdui->Enable(str.has_char());
   }

   void edit_plain_text::_001OnEditFocusCopy(signal_details * pobj)
   {

      UNREFERENCED_PARAMETER(pobj);

      clipboard_copy();

      pobj->m_bRet = true;

   }

   void edit_plain_text::_001OnUpdateEditFocusPaste(signal_details * pobj)
   {
      SCAST_PTR(::base::cmd_ui, pupdatecmdui, pobj)
      pupdatecmdui->m_pcmdui->Enable(session().copydesk().get_plain_text().has_char());
   }

   void edit_plain_text::_001OnEditFocusPaste(signal_details * pobj)
   {

      UNREFERENCED_PARAMETER(pobj);

      clipboard_paste();

      pobj->m_bRet = true;

   }


   void edit_plain_text::_001OnSize(signal_details * pobj)
   {

      UNREFERENCED_PARAMETER(pobj);

   }

   void edit_plain_text::layout()
   {

      scroll_view::layout();

   }

   bool edit_plain_text::ShowWindow(int32_t nCmdShow)
   {

      if (nCmdShow != SW_HIDE)
      {

         TRACE("Going to Show edit_plain_text");

      }

      return ::user::scroll_view::ShowWindow(nCmdShow);

   }




} // namespace core


