//#include "framework.h" // from "base/user/user.h"
//#include "base/user/user.h"
//#include "aura/user/colorertake5/colorertake5.h"

//#define SEARCH_SCROLLING_PROFILING
//#define PROFILE_CALC_LAYOUT
CLASS_DECL_BASE void str_fill(string & str,char ch);

extern CLASS_DECL_BASE thread_int_ptr < DWORD_PTR > t_time1;

namespace user
{

   plain_edit::plain_edit() :
      m_keymessageLast(get_app())
   {

      plain_edit_common_construct();

   }


   plain_edit::plain_edit(::aura::application * papp):
      ::object(papp),
      ::user::interaction(papp),
      m_keymessageLast(papp)
   {

      plain_edit_common_construct();

   }

   plain_edit::~plain_edit()
   {

      ::aura::del(m_peditor);

      ::aura::del(m_plines);

   }

   void plain_edit::plain_edit_common_construct()
   {

      ASSERT(get_app() != NULL);

      m_peditor = new colorertake5::base_editor(get_app());
      m_plines = new colorertake5::text_lines;

      m_iLineHeight = 0;
      m_bPassword = false;
      //m_ptree              = NULL;
      m_bOwnData           = false;

      m_bMultiLine         = false;
      m_bColorerTake5      = false;
      m_bReadOnly          = false;
      m_bSendEnterKey      = false;

      m_bActionHover       = false;


      m_bCalcLayoutHintNoTextChange = false;

      m_scrolldataHorz.m_bScrollEnable = false;
      m_scrolldataVert.m_bScrollEnable = false;



      /*m_straSep.add("\n");
      m_straSep.add("\r");
      m_straSep.add("\r\n");
      */


      m_y                  = -1;
      m_iViewOffset        = 0;
      m_iViewSize          = 1000;
      m_bMouseDown         = false;
      m_dwCaretTime        = 500;
      set_cursor(::visual::cursor_text_select);

      //         m_scrolldata.m_bVScrollBarEnable = false;
      //       m_scrolldata.m_bHScrollBarEnable = false;


   }


   void plain_edit::install_message_handling(::message::dispatch * pinterface)
   {

      control::install_message_handling(pinterface);


      IGUI_WIN_MSG_LINK(WM_CREATE,pinterface,this,&plain_edit::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN,pinterface,this,&plain_edit::_001OnLButtonDown);
      IGUI_WIN_MSG_LINK(WM_LBUTTONUP,pinterface,this,&plain_edit::_001OnLButtonUp);
      IGUI_WIN_MSG_LINK(WM_RBUTTONDOWN,pinterface,this,&plain_edit::_001OnRButtonDown);
      IGUI_WIN_MSG_LINK(WM_RBUTTONUP,pinterface,this,&plain_edit::_001OnRButtonUp);
      IGUI_WIN_MSG_LINK(WM_MOUSEMOVE,pinterface,this,&plain_edit::_001OnMouseMove);
      IGUI_WIN_MSG_LINK(WM_MOUSELEAVE,pinterface,this,&plain_edit::_001OnMouseLeave);
      IGUI_WIN_MSG_LINK(WM_KEYDOWN,pinterface,this,&plain_edit::_001OnKeyDown);
      IGUI_WIN_MSG_LINK(WM_KEYUP,pinterface,this,&plain_edit::_001OnKeyUp);
      //IGUI_WIN_MSG_LINK(WM_CHAR,pinterface,this,&plain_edit::_001OnChar);

      IGUI_WIN_MSG_LINK(WM_SIZE,pinterface,this,&::user::plain_edit::_001OnSize);


      IGUI_WIN_MSG_LINK(WM_VSCROLL,pinterface,this,&::user::plain_edit::_001OnVScroll);
      IGUI_WIN_MSG_LINK(WM_HSCROLL,pinterface,this,&::user::plain_edit::_001OnHScroll);

      connect_update_cmd_ui("edit_focus_copy",&plain_edit::_001OnUpdateEditFocusCopy);
      connect_command("edit_focus_copy",&plain_edit::_001OnEditFocusCopy);
      connect_update_cmd_ui("edit_focus_paste",&plain_edit::_001OnUpdateEditFocusPaste);
      connect_command("edit_focus_paste",&plain_edit::_001OnEditFocusPaste);

   }


   void plain_edit::OnDraw(::draw2d::dib * pdib)
   {

      UNREFERENCED_PARAMETER(pdib);

   }


   void plain_edit::_001OnInitialUpdate()
   {

      _001OnUpdate(::action::source_system);

      m_bNeedCalcLayout = true;
      m_bCalcLayoutHintNoTextChange = false;

//      ThreadProcScrollSize((LPVOID) this);

   }


   void plain_edit::_001OnDestroy(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }



   void plain_edit::VirtualOnSize()
   {

      _001OnUpdate(::action::source_system);

      m_bNeedCalcLayout = true;
      m_bCalcLayoutHintNoTextChange = true;



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

   void plain_edit::_001OnPaint(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }

   void plain_edit::on_viewport_offset(::draw2d::dib * pdib)
   {
   }

   void plain_edit::_001OnDraw(::draw2d::dib * pdib)
   {

      //return;
#ifdef PROFILE_CALC_LAYOUT
      for(index i = 0; i < 1000; i++)
#else
      if(m_bNeedCalcLayout)

#endif
      {

         _001OnCalcLayout();

      }

      ::draw2d::graphics * pdc = pdib->get_graphics();

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
      if(pjob != NULL)
         pprintjob = dynamic_cast <::user::print_job *> (pjob);
      else
         pprintjob = NULL;


      rect rectClient;
      GetClientRect(rectClient);

      if(pprintjob != NULL)
      {
         TRACE("Print Job Is Printing page %d",pprintjob->m_iPrintingPage);
      }



      //rectClient.deflate(0, 0, 1, 1);

      //::draw2d::graphics * pdc = pdib->get_graphics();

      if(pprintjob == NULL)
      {

         ::user::interaction::_001OnDraw(pdib);

      }



      //color ca;
      //ca.set_rgb(RGB(227,227,210));
      //ca.hls_rate(0.0,-0.33,-0.23);
      ////      COLORREF crBorder = ca.get_rgb() | (0xff << 24);
      ////pdc->Draw3dRect(rectClient, crBorder, crBorder);

      bool bCaretOn = ((get_tick_count() - m_dwFocustStart) % (m_dwCaretTime * 2)) < m_dwCaretTime;

      if(m_ptree == NULL)
         return;

      //if(m_iLineHeight == 0)
      //{
      //   pdc->OffsetViewportOrg(-m_scrolldata.m_ptScroll.x,m_scrolldata.m_ptScroll.y);
      //}
      //else
      //{
      //   pdc->OffsetViewportOrg(-m_scrolldata.m_ptScroll.x,-(m_scrolldata.m_ptScroll.y % m_iLineHeight));
      //}

      ::draw2d::region_sp rgn(allocer());

      rectClient.deflate(2,2);

      //ClientToScreen(rectClient);
      rgn->create_rect(rectClient);

      double left = rectClient.left;

      //   pdc->SelectClipRgn(&rgn);

      if(Session.get_keyboard_focus() == this)
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

      penCaret->create_solid(1.0,ARGB(255,0,0,0));


      /*   rectClient.top = m_pt.y;
         rectClient.left = m_pt.x;
         rectClient.bottom = rectClient.top + m_size.cy;
         rectClient.right = rectClient.left + m_size.cx;*/
      //      pdc->FillSolidRect(rectClient, crBk);


      double y = rectClient.top;
      _001GetViewSel(iSelStart,iSelEnd);
      strsize iCursor = iSelEnd;
      sort::sort(iSelStart,iSelEnd);
      select_font(pdc);
      size size3;
      size3 = pdc->GetTextExtent(unitext("gGYIﾍ"));
      int32_t iLineHeight = size3.cy;
      stringa & straLines = m_plines->lines;
      stringa straLineFeed;
      string strLine;
      string str1;
      string str2;
      string str3;
      string strExtent1;
      string strExtent2;
      string strExtent3;
      index iLineStart = should_load_full_file() ? m_iLineOffset : 0;
      index iLineEnd = should_load_full_file() ?  iLineStart + m_iLineCount - 1 : straLines.get_size();
      iLineEnd = MIN(iLineEnd,straLines.get_upper_bound());
      index iLine = m_iLineOffset;
      for(index i = iLineStart; i <= iLineEnd; i++, iLine++)
      {
         straLineFeed.remove_all();
         straLineFeed.add_lines(straLines[i],false);
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
            pregion = m_peditor->getLineRegions(i);
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
               strExtent2 = strLine.Mid(x,len);
               class size size1;
               size1 = pdc->GetTextExtent(strExtent1);
               if(pregion->styled()->bback)
               {
                  pdc->FillSolidRect((int32_t)(left + size1.cx),(int32_t)y,size1.cx,size1.cy,pregion->styled()->back);
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
               pdc->TextOut(left + size1.cx,y,strExtent2);

            }
         }
         else
         {
            int iErrorBeg = -1;
            int iErrorEnd = -1;
            int iErrorA = 0;
            if(m_errora.get_size() > 0)
            {
               DWORD dwTimeout = 1284;
               DWORD dwPeriod = 84;
               if(::get_tick_count() - m_errora[0].m_dwTime > dwTimeout)
               {
                  if(::get_tick_count() - m_errora[0].m_dwTime < (dwTimeout + dwPeriod))
                  {
                     iErrorA = (::get_tick_count() - m_errora[0].m_dwTime - dwTimeout) * 255 / dwPeriod;
                  }
                  else
                  {
                     iErrorA = 255;
                  }
                  iErrorBeg = m_errora[0].m_iStart;
                  iErrorEnd = m_errora[0].m_iEnd;
                  iErrorBeg -= lim;
                  iErrorEnd -= lim;
                  iErrorBeg = MAX(0,iErrorBeg);
                  iErrorEnd = MIN(iErrorEnd,strLine.get_length());
               }
            }
            stringa stra;
            strsize i1 = iSelStart - lim;
            strsize i2 = iSelEnd - lim;
            strsize i3 = iCursor - lim;
            strsize iStart = MAX(0,i1);
            strsize iEnd = MIN(i2,strLine.get_length());
            if(m_bPassword)
            {
               str_fill(strLine,'*');
            }
            str1 = strLine.Mid(0,iStart);
            str2 = strLine.Mid(iStart,iEnd - iStart);
            str3 = strLine.Mid(iEnd);
            strExtent1 = str1;
            strExtent2 = str2;
            strExtent3 = str3;
            strExtent1.replace("\t","   ");
            strExtent2.replace("\t","   ");
            strExtent3.replace("\t","   ");
            if(m_bPassword)
            {
               str_fill(strExtent1,'*');
               str_fill(strExtent2,'*');
               str_fill(strExtent3,'*');
            }

            brushText->create_solid(cr);
            pdc->SelectObject(brushText);
            pdc->TextOut(left,y,strExtent1);


            sized size1(0.0,0.0);
            pdc->GetTextExtent(size1,strLine,(int32_t)strLine.length(),(int32_t)iStart);
            if(0 <= iErrorBeg && iErrorEnd <= strExtent1.length())
            {
               sized sizeA(0.0,0.0);
               pdc->GetTextExtent(sizeA,strLine,(int32_t)strLine.length(),(int32_t)iErrorBeg);
               sized sizeB(0.0,0.0);
               pdc->GetTextExtent(sizeB,strLine,(int32_t)strLine.length(),(int32_t)iErrorEnd);
               int y = MAX(sizeA.cy,sizeB.cy);
               ::draw2d::pen_sp p(allocer());
               p->create_solid(1.0,ARGB(iErrorA,255,0,0));
               pdc->SelectObject(p);
               pdc->DrawErrorLine(sizeA.cx,y, sizeB.cx, 1);
            }
            sized sizeb(0.0,0.0);
            pdc->GetTextExtent(sizeb,strLine,iEnd);
            sized size2(0.0,0.0);
            pdc->GetTextExtent(size2,strLine,(int32_t)strLine.length(),(int32_t)iEnd);
            size2.cx -= size1.cx;

            if(iEnd > iStart)
            {
               pdc->FillSolidRect((int32_t)(left + size1.cx),(int32_t)y,(int32_t)size2.cx,(int32_t)size2.cy,ARGB(255,120,240,180));
               brushText->create_solid(crSel);
               pdc->SelectObject(brushText);
               pdc->TextOut(left + size1.cx,y,strExtent2);
            }

            brushText->create_solid(cr);
            pdc->SelectObject(brushText);
            pdc->TextOut(left + size1.cx + size2.cx,y,strExtent3);

            //maxcy = MAX(size1.cy, size2.cy);
            //maxcy = MAX(maxcy, size3.cy);
            if(m_bFocus && bCaretOn && i3 == str1.get_length())
            {
               pdc->SelectObject(penCaret);
               pdc->MoveTo(left + size1.cx,y);
               pdc->LineTo(left + size1.cx,y + iLineHeight);
            }
            else if(m_bFocus && bCaretOn && i3 == (str1.get_length() + str2.get_length()))
            {
               pdc->SelectObject(penCaret);
               pdc->MoveTo(left + size2.cx + size1.cx,y);
               pdc->LineTo(left + size2.cx + size1.cx,y + iLineHeight);
            }
         }
         y += iLineHeight;
         lim += m_iaLineLen[iLine];
         //ASSERT(FALSE);
      }


   }

   void plain_edit::_001OnCreate(signal_details * pobj)
   {

      SCAST_PTR(::message::create,pcreate,pobj);

#if !defined(APPLE_IOS) && !defined(VSNORD)
      Session.keyboard(); // trigger keyboard creationg
#endif


      if(m_ptree == NULL)
      {

         set_root(canew(::user::plain_text_tree(get_app())),true);

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
      m_ptree->m_pfile = canew(::file::memory_buffer(get_app()));
      if(m_bColorerTake5)
      {
         m_peditor->colorertake5::base_editor::initialize(m_plines);
         m_peditor->colorertake5::base_editor::setRegionMapper("rgb","default");
      }

      //  m_peditfile = new ::file::edit_buffer(get_app());

      m_ptree->m_editfile.SetFile(m_ptree->m_pfile);

      //on_update_data(update_hint_set_file);

      m_bGetTextNeedUpdate = true;


//      SetTimer(100,100,NULL);
      m_ptree->m_iSelStart  = 0;
      m_ptree->m_iSelEnd = 0;
      _001OnSetText(::action::source_system);
      _001OnUpdate(::action::source_system);


   }

   void plain_edit::_001OnContextMenu(signal_details * pobj)
   {
      //      SCAST_PTR(::message::context_menu, pcontextmenu, pobj);
      //      point point = pcontextmenu->GetPoint();

   }

   void plain_edit::_001OnRButtonUp(signal_details * pobj)
   {
      SCAST_PTR(::message::mouse,pmouse,pobj);


            point pt = pmouse->m_pt;

         ScreenToClient(&pt);

         ::draw2d::memory_graphics pdc(allocer());

         m_ptree->m_iSelEnd = char_hit_test(pdc,pt.x,pt.y);

         m_iColumn = SelToColumn(m_ptree->m_iSelEnd);

         RedrawWindow();

         m_bMouseDown = false;

         track_popup_xml_matter_menu("ystem/edit_focus_popup.xml",0,pobj);

         pmouse->set_lresult(1);

         pmouse->m_bRet = true;


   }





   void plain_edit::_001OnSetCursor(signal_details * pobj)
   {
      //pmouse->m_ecursor = ::visual::cursor_arrow;

      pobj->previous();
   }

   void plain_edit::_001OnTimer(::timer * ptimer)
   {
      control::_001OnTimer(ptimer);
      if(ptimer->m_nIDEvent >= 100
         && ptimer->m_nIDEvent <= 200)
      {
         if(this == Session.get_keyboard_focus())
         {
            _001OnKeyboardFocusTimer(ptimer->m_nIDEvent - 100);
         }
      }
      else if(ptimer->m_nIDEvent == 500 || ptimer->m_nIDEvent == 501)
      {
         if(ptimer->m_nIDEvent == 500)
         {
            KillTimer(500);
            SetTimer(501,300,NULL);
         }
         key_to_char(&m_keymessageLast);
      }

   }


   void plain_edit::_001OnKeyDown(signal_details * pobj)
   {

      //synch_lock sl(m_pmutex);



      SCAST_PTR(::message::key,pkey,pobj);

      if(pkey->m_ekey == ::user::key_return)
      {

         if(Session.is_key_pressed(::user::key_control) && Session.is_key_pressed(::user::key_alt))
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

            if(!BaseOnControlEvent(&ev))
            {

               on_action("submit");

            }

            pobj->m_bRet      = true;

            return;

         }

      }
      else if(pkey->m_ekey == ::user::key_tab)
      {

         if(Session.is_key_pressed(::user::key_control) && Session.is_key_pressed(::user::key_alt))
         {

            pkey->m_bRet      = false;

            return;

         }

         if(!m_bMultiLine)
         {

            pkey->previous();

            //::user::control_event ev;

            //ev.m_puie         = this;

            //ev.m_eevent       = ::user::event_tab_key;

            //ev.m_actioncontext        = ::action::source_user;

            //if(!BaseOnControlEvent(&ev))
            //{

            //   sp(::user::interaction) pui = keyboard_get_next_focusable();

            //   if(pui != NULL)
            //      pui->keyboard_set_focus();

            //}

            //pkey->m_bRet      = true;

            return;

         }

      }
      else if(pkey->m_ekey == ::user::key_alt)
      {

         pkey->m_bRet = false;

         return;

      }
      else if(pkey->m_ekey == ::user::key_escape)
      {

         ::user::control_event ev;

         ev.m_puie         = this;

         ev.m_eevent       = ::user::event_escape;

         ev.m_actioncontext        = ::action::source_user;

         if(!BaseOnControlEvent(&ev))
         {

            on_action("escape");

         }

         pobj->m_bRet      = true;

         return;

      }
      else if(pkey->m_ekey == ::user::key_c)
      {

         if(Session.is_key_pressed(::user::key_control))
         {

            pkey->m_bRet      = true;

            clipboard_copy();

            return;

         }

      }
      else if(pkey->m_ekey == ::user::key_v)
      {

         if(Session.is_key_pressed(::user::key_control))
         {

            pkey->m_bRet      = true;

            clipboard_paste();

            return;

         }

      }

      m_keymessageLast = *pkey;

      m_bKeyPressed     = true;

      key_to_char(&m_keymessageLast);

      pkey->m_bRet      = true;

   }


   void plain_edit::_001OnKeyUp(signal_details * pobj)
   {
      SCAST_PTR(::message::key,pkey,pobj);
      if(pkey->m_ekey == ::user::key_return)
      {
         if(Session.is_key_pressed(::user::key_control)
            && Session.is_key_pressed(::user::key_alt))
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

   void plain_edit::pre_translate_message(signal_details * pobj)
   {

      SCAST_PTR(::message::base,pbase,pobj);

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


   void plain_edit::key_to_char(::message::key * pkey)
   {

      ::message::key & key = *pkey;

      if(key.m_ekey == ::user::key_shift || key.m_ekey == ::user::key_lshift || key.m_ekey == ::user::key_rshift
         || key.m_ekey == ::user::key_control || key.m_ekey == ::user::key_lcontrol || key.m_ekey == ::user::key_rcontrol
         || key.m_ekey == ::user::key_alt || key.m_ekey == ::user::key_lalt || key.m_ekey == ::user::key_ralt
         )
      {

         return;

      }

      if(key.m_ekey == ::user::key_right || key.m_ekey == ::user::key_up
         || key.m_ekey == ::user::key_left || key.m_ekey == ::user::key_down)
      {

         _001OnChar(&key);

         return;

      }

      bool bShift = Session.is_key_pressed(::user::key_shift);

      if(key.m_nChar < 256 && isalpha((int32_t)key.m_nChar))
      {

         if(bShift)
         {

            key.m_nChar = toupper((int32_t)key.m_nChar);

         }
         else
         {

            key.m_nChar = tolower((int32_t)key.m_nChar);

         }

      }

      _001OnChar(&key);

   }


   //UINT plain_edit::ThreadProcScrollSize(LPVOID lpvoid)
   //{

   //   plain_edit * pview = (plain_edit *)lpvoid;

   //   ::data::simple_lock lock(pview->m_ptree);

   //   ::draw2d::graphics_sp graphics(pview->allocer());

   //   graphics->CreateCompatibleDC(NULL);

   //   ::draw2d::graphics * pdc = graphics;

   //   pview->_001OnCalcLayoutProc(pview);

   //   pview->_001OnUpdate(::action::source_system);

   //   return 0;

   //}


   void plain_edit::_001GetText(string & str) const
   {

      if(m_ptree == NULL)
         return;

      synch_lock lock(m_ptree->m_pmutex);

      file_size_t iSize = m_ptree->m_editfile.get_length();

      char * psz = str.GetBufferSetLength((strsize)(iSize + 1));

      m_ptree->m_editfile.seek(0,::file::seek_begin);

      m_ptree->m_editfile.read(psz,(memory_size_t) iSize);

      psz[(memory_position_t) iSize] = '\0';

      str.ReleaseBuffer();

   }


   void plain_edit::_001GetSelText(string & str) const
   {

      file_position_t iEnd;

      file_position_t iStart;

      if(m_ptree->m_iSelEnd < 0)
      {

         if(m_ptree->m_iSelStart < 0)
         {

            iEnd = (file_position_t)m_ptree->m_editfile.get_length();

            iStart = 0;

         }
         else
         {

            iStart = m_ptree->m_iSelStart;

            iEnd = (file_position_t)m_ptree->m_editfile.get_length();

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

         file_position_t iSwap   = iEnd;

         iEnd        = iStart;

         iStart      = iSwap;

      }

      file_position_t iSize = iEnd - iStart;

      char * psz = str.GetBufferSetLength((strsize)(iSize + 1));

      m_ptree->m_editfile.seek((file_offset_t)iStart,::file::seek_begin);

      m_ptree->m_editfile.read(psz,(memory_size_t) (iSize));

      psz[(memory_position_t)iSize] = '\0';

      str.ReleaseBuffer();

      //str.replace("\n","\r\n");

   }


   void plain_edit::_001SetSelText(const char * psz,::action::context actioncontext)
   {

      m_ptree->m_editfile.seek(m_ptree->m_iSelStart,::file::seek_begin);

      m_ptree->m_editfile.Delete((memory_size_t) (m_ptree->m_iSelEnd - m_ptree->m_iSelStart));

      m_ptree->m_editfile.seek(m_ptree->m_iSelStart,::file::seek_begin);

      m_ptree->m_editfile.Insert(psz,strlen(psz));

      _001OnUpdate(actioncontext);

      RedrawWindow();

   }


   void plain_edit::_001SetSel(strsize iSelStart,strsize iSelEnd)
   {

      m_ptree->m_iSelStart = iSelStart;

      m_ptree->m_iSelEnd = iSelEnd;

      _001EnsureVisibleChar(iSelStart);

#ifndef      SEARCH_SCROLLING_PROFILING

      RedrawWindow();


#endif

   }


   void plain_edit::_001EnsureVisibleChar(strsize iChar)
   {

      _001EnsureVisibleLine(CharToLine(iChar));

   }


   void plain_edit::_001EnsureVisibleLine(index iLine)
   {

      //m_scrolldata.m_ptScroll.y = (MIN(MAX(0, iLine), m_iaLineLen.get_upper_bound()) - 1) * m_iLineHeight;

      set_viewport_offset_y((MIN(MAX(0,iLine),m_iaLineLen.get_upper_bound()) - 1) * m_iLineHeight);

      m_bNeedCalcLayout = true;
      m_bCalcLayoutHintNoTextChange = true;

#ifndef SEARCH_SCROLLING_PROFILING

      RedrawWindow();

#endif

   }


   void plain_edit::on_change_viewport_offset()
   {

      ::user::control::on_change_viewport_offset();

      m_bNeedCalcLayout = true;

   }


   void plain_edit::_001OnLButtonDown(signal_details * pobj)
   {

      SCAST_PTR(::message::mouse,pmouse,pobj);

         point pt = pmouse->m_pt;

      ScreenToClient(&pt);

      m_bMouseDown = true;

      ::draw2d::memory_graphics pdc(allocer());

      if(pdc.is_null())
         return;

      m_ptree->m_iSelStart = char_hit_test(pdc,pt.x,pt.y);

      m_ptree->m_iSelEnd = m_ptree->m_iSelStart;

      RedrawWindow();

      Session.set_keyboard_focus(this);

      Session.user()->set_mouse_focus_LButtonDown(this);

      pmouse->m_bRet = true;

      pmouse->set_lresult(1);

   }


   void plain_edit::_001OnLButtonUp(signal_details * pobj)
   {

      SCAST_PTR(::message::mouse,pmouse,pobj);

         point pt = pmouse->m_pt;

      ScreenToClient(&pt);

      ::draw2d::memory_graphics pdc(allocer());

      m_ptree->m_iSelEnd = char_hit_test(pdc,pt.x,pt.y);

      m_iColumn = SelToColumn(m_ptree->m_iSelEnd);

      RedrawWindow();

      m_bMouseDown = false;

      pmouse->m_bRet = true;

      pmouse->set_lresult(1);

   }


   void plain_edit::_001OnRButtonDown(signal_details * pobj)
   {

      SCAST_PTR(::message::mouse,pmouse,pobj);

         point pt = pmouse->m_pt;

      ScreenToClient(&pt);

      m_bMouseDown = true;

      ::draw2d::memory_graphics pdc(allocer());

      m_ptree->m_iSelStart = char_hit_test(pdc,pt.x,pt.y);

      m_ptree->m_iSelEnd = m_ptree->m_iSelStart;

      RedrawWindow();

      Session.set_keyboard_focus(this);

      Session.user()->set_mouse_focus_RButtonDown(this);

      pmouse->m_bRet = true;

      pmouse->set_lresult(1);

   }



   //void plain_edit::_001OnCalcLayoutProc(::user::primitive * pview)
   //{

   //   ::draw2d::memory_graphics pdc(allocer());

   //   ::data::simple_lock lockRoot(m_ptree);

   //   UNREFERENCED_PARAMETER(pview);

   //   select_font(pdc);

   //   int32_t y = 0;

   //   pdc->set_text_rendering(::draw2d::text_rendering_anti_alias_grid_fit);

   //   size size3 = pdc->GetTextExtent(unitext("gqYALﾍ"));

   //   rect rectClient;

   //   GetClientRect(rectClient);

   //   m_iLineHeight = size3.cy;

   //   m_ptree->m_editfile.seek(0,::file::seek_begin);

   //   y = (int32_t)(m_iLineHeight * m_iaLineLen.get_size());

   //   if(y <= 0)
   //   {

   //      y = 200;

   //   }

   //}

   void debug_func(const string & str)
   {

   }
   void plain_edit::_001OnCalcLayout()
   {

      synch_lock sl(m_pmutex);

      rect rectClient;

      GetClientRect(rectClient);

      if(m_ptree == NULL)
      {

         m_iLineCount = 0;

         m_iLineOffset = 0;

         m_iViewOffset = 0;

         m_iViewSize = 0;

         m_sizeTotal = rectClient.size();

         on_change_view_size();

         return;

      }

      ::index i;

      ::index iLine;

      ::draw2d::memory_graphics pdc(allocer());

      select_font(pdc);

      const int iLenUniText = 14;

      sized sizeUniText;

      pdc->set_text_rendering(::draw2d::text_rendering_anti_alias_grid_fit);

      pdc->GetTextExtent(sizeUniText,unitext("gqYALﾍWMÍÎÄÃÄÅ"));

      m_iLineHeight = sizeUniText.cy;

      if(m_iLineHeight <= 0)
      {

         m_iLineHeight = 18;

      }

      point ptOffset = get_viewport_offset();

      m_iLineCount = (rectClient.height() / m_iLineHeight) + 1;

      m_iLineOffset = MIN(MAX(0,ptOffset.y / m_iLineHeight),m_iaLineBeg.get_upper_bound());

      ::index iLineStart = should_load_full_file() ? 0 : m_iLineOffset;

      ::index iLineEnd = should_load_full_file() ? m_iaLineLen.get_size() - 1 : MIN(m_iaLineLen.get_size(),m_iLineCount + iLineStart) - 1;

      int iLineUBound = MIN(iLineEnd,m_iaLineLen.get_size() - iLineStart - 1);

      if(m_iLineOffset < 0)
      {

         return;

      }

      m_iViewOffset = m_iaLineBeg[m_iLineOffset];

      m_iViewSize = 0;

      i = 0;

      iLine = iLineStart;

      for(; i <= iLineUBound; i++,iLine++)
      {

         m_iViewSize += m_iaLineLen[iLine];

      }

      string strLine;

      memory mem;

      mem.allocate(m_iViewSize + 1);

      m_ptree->m_editfile.seek(m_iViewOffset,::file::seek_begin);

      m_ptree->m_editfile.read(mem.get_data(),m_iViewSize);

      mem.get_data()[m_iViewSize] = 0;

      int iPos = 0;

      strsize iLen;

      strsize iStrLen;

      m_plines->lines.remove_all();

      i = 0;

      iLine = iLineStart;

      for(; i <= iLineUBound; i++,iLine++)
      {

         iLen = m_iaLineLen[iLine];

         iStrLen = MAX(0,iLen - (m_iaLineEnd[iLine] & 255));

         m_plines->lines.add(string((const char *) &mem.get_data()[iPos],iStrLen));

         iPos += iLen;

      }

      m_y = ptOffset.y;

      m_peditor->visibleTextEvent(m_iLineOffset,m_iLineCount);

      select_font(pdc);

      stringa & straLines = m_plines->lines;

//      strsize iSelStart;

  //    strsize iSelEnd;

    //  _001GetViewSel(iSelStart,iSelEnd);

      m_sizeTotal.cx = 0;

      sized size;

      for(int32_t i = 0; i < straLines.get_size(); i++)
      {

         strLine = straLines[i];

         strLine.replace("\t","   ");

         size.cx = (double)strLine.get_length() * (double)sizeUniText.cx / (double)iLenUniText;

         if(size.cx > m_sizeTotal.cx)
         {

            m_sizeTotal.cx = (int32_t)size.cx;

         }

      }

      m_sizeTotal.cy = ((int32_t)m_iaLineLen.get_count() * m_iLineHeight);

      class size sizePage;

      sizePage = rectClient.size();

      if(m_bMultiLine)
      {

         m_sizeTotal.cy += sizePage.cy;

      }

      //m_scrolldata.m_sizePage = sizePage;

      //_001LayoutScrollBars();

      on_change_view_size();

      m_bNeedCalcLayout = false;

      m_bCalcLayoutHintNoTextChange = false;

   }


   //void plain_edit::on_change_view_size()
   //{
   //
   //   ::user::box::on_change_view_size();

   //}


   index plain_edit::SelToLine(strsize iSel)
   {

      synch_lock sl(m_pmutex);

      iSel -= m_iViewOffset;

      stringa & straLines = m_plines->lines;

      strsize i1;

      strsize i2 = 0;

      for(index i = 0; i < straLines.get_size(); i++)
      {

         i1 = i2;

         i2 = i1 + straLines[i].get_length();

         if(iSel >= i1 && iSel <= i2)
         {

            return i;

         }

      }

      return -1;

   }

   index plain_edit::CharToLine(strsize iChar)
   {
      //return -1;

      synch_lock sl(m_pmutex);

      for(index iLine = 0; iLine < m_iaLineBeg.get_size(); iLine++)
      {

         if(iChar >= m_iaLineBeg[iLine] && iChar < m_iaLineBeg[iLine] + m_iaLineLen[iLine])
         {

            return MAX(iLine, 0);

         }

      }

      return -1;

   }


   index plain_edit::SelToLineX(strsize iSel,int32_t & x)
   {

      synch_lock sl(m_pmutex);

      iSel -= m_iViewOffset;

      stringa & straLines = m_plines->lines;

      strsize i1;

      strsize i2 = 0;

      for(index i = 0; i < straLines.get_size(); i++)
      {

         i1 = i2;

         i2 = i1 + straLines[i].get_length();

         if(iSel >= i1 && iSel < i2)
         {

            ::draw2d::memory_graphics pgraphics(allocer());

            select_font(pgraphics);

            pgraphics->set_text_rendering(::draw2d::text_rendering_anti_alias_grid_fit);

            size size1 = pgraphics->GetTextExtent(straLines[i],(int32_t)straLines[i].length(),(int32_t)(iSel - i1));

            size size2 = pgraphics->GetTextExtent(straLines[i],(int32_t)iSel - i1);

            x = (size1.cx + size2.cx) / 2;

            return i;

         }

      }

      return -1;

   }


   strsize plain_edit::LineColumnToSel(index iLine,index iColumn)
   {

      synch_lock sl(m_pmutex);

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

      stringa & straLines = m_plines->lines;

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

      stra.add_lines(straLines[iLine],false);

      if(stra.get_size() > 0)
      {

         strLine = stra[0];

      }
      else
      {

         strLine.Empty();

      }

      if(iColumn < 0)
      {

         iColumn = iColumn + 1 + strLine.get_length();

      }

      if(iColumn > strLine.get_length())
      {

         iColumn = strLine.get_length();

      }

      return m_iViewOffset + iOffset + iColumn;

   }


   strsize plain_edit::LineXToSel(index iLine,int32_t x)
   {

      synch_lock sl(m_pmutex);

      ::draw2d::memory_graphics pgraphics(allocer());

      select_font(pgraphics);

      pgraphics->set_text_rendering(::draw2d::text_rendering_anti_alias_grid_fit);

      size size3 = pgraphics->GetTextExtent(unitext("gqYALﾍWM"));

      int32_t iLineHeight = size3.cy;

      point ptOffset = get_viewport_offset();

      int32_t y = (int32_t)(iLineHeight * iLine + iLineHeight / 2 - ptOffset.y);

      strsize iChar = char_hit_test(pgraphics,x,y);

      return iChar;

   }


   index plain_edit::SelToColumn(strsize iSel)
   {

      synch_lock sl(m_pmutex);

      iSel -= m_iViewOffset;

      stringa & straLines = m_plines->lines;

      strsize i1;

      strsize i2 = 0;

      for(index i = 0; i < straLines.get_size(); i++)
      {

         i1 = i2;

         i2 = i1 + straLines[i].get_length();

         if(iSel >= i1 && iSel <= i2)
         {

            return iSel - i1;

         }

      }

      return -1;

   }


   strsize plain_edit::char_hit_test(::draw2d::graphics * pdc,int32_t px,int32_t py)
   {

      synch_lock sl(m_pmutex);

      select_font(pdc);

      rect rectClient;

      GetClientRect(rectClient);

      px -= rectClient.left;

      py -= rectClient.top;

      point ptOffset = get_viewport_offset();

      if(m_iLineHeight == 0)
      {

         py += ptOffset.y;

      }
      else
      {

         py += ptOffset.y % m_iLineHeight;

      }

      stringa & straLines = m_plines->lines;

      strsize iSelStart;

      strsize iSelEnd;

      _001GetViewSel(iSelStart,iSelEnd);

      int32_t lim = 0;

      int32_t iLineHeight;

      int32_t y = 0;

      bool bFound = false;

      string strLine;

      string strExtent;

      size size3;

      size3 = pdc->GetTextExtent(unitext("gqYALﾍ"));

      iLineHeight = size3.cy;

      strsize iOffset = 0;

      stringa stra;

      for(int32_t i = 0; i < straLines.get_size(); i++)
      {

         stra.remove_all();

         stra.add_lines(straLines[i],false);

         if(stra.get_size() > 0)
         {

            strLine = stra[0];

         }
         else
         {

            strLine.Empty();

         }

         strExtent = strLine;

         strExtent.replace("\t","   ");

         size size;

         size = pdc->GetTextExtent(strExtent);

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

      for(;;)
      {

         pszPrevious = pszEnd;

         pszEnd = ::str::utf8_inc(pszEnd);

         if(pszEnd == NULL)
            break;

         lim1 = lim2;

         strExtent = string(psz,pszEnd - psz);

         strExtent.replace("\t","   ");

         class size size;

         class ::size size1 = pdc->GetTextExtent(strLine,(int32_t)strLine.length(),(int32_t)strExtent.length());

         class ::size size2 = pdc->GetTextExtent(strLine,strExtent.length());

         lim2 = (size1.cx + size2.cx) / 2;

         lim = lim2;

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

      return (strsize)MIN((strsize)(iOffset + strLine.get_length() + m_iViewOffset),(strsize)m_ptree->m_editfile.get_length());

   }


   void plain_edit::_001OnMouseMove(signal_details * pobj)
   {

      SCAST_PTR(::message::mouse,pmouse,pobj);

         point pt = pmouse->m_pt;

      ScreenToClient(&pt);

      if(has_text_input())
      {

         pmouse->m_ecursor = ::visual::cursor_text_select;

         if(m_bMouseDown)
         {

            ::draw2d::memory_graphics pdc(allocer());

            m_ptree->m_iSelEnd = char_hit_test(pdc,pt.x,pt.y);

         }

      }
      else
      {

         pmouse->m_ecursor = ::visual::cursor_arrow;



      }

      track_mouse_hover();

      m_bActionHover = true;

      RedrawWindow();

   }

   void plain_edit::_001OnMouseLeave(signal_details * pobj)
   {

      m_bActionHover = false;

      RedrawWindow();

   }

   void plain_edit::_001GetViewSel(strsize &iSelStart,strsize &iSelEnd)
   {

      if(m_ptree == NULL)
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


   void plain_edit::_001GetSel(strsize & iSelStart,strsize  & iSelEnd)
   {

      iSelStart   = m_ptree->m_iSelStart;

      iSelEnd     = m_ptree->m_iSelEnd;

   }


   void plain_edit::on_updata_data(::data::simple_data * pdata,int32_t iHint)
   {

      if(pdata == m_ptree)
      {

         if(iHint == plain_text_tree::update_hint_set_file)
         {

            OnFileUpdate();

         }

      }

   }


   void plain_edit::FileSave()
   {

      m_ptree->m_editfile.flush();

   }


   void plain_edit::OnFileUpdate()
   {

      m_bGetTextNeedUpdate = true;

      CreateLineIndex();

      m_y = -1;

   }


   void plain_edit::CreateLineIndex()
   {



      memory m;

      m.allocate(1024 * 1024);

      char * buf = (char *) m.get_data();

      memory_size_t uiRead;

      char * lpsz;

      m_ptree->m_editfile.seek(0,::file::seek_begin);

      if(m_sizeTotal.cx <= 0)
      {

         m_sizeTotal.cx = 200;

      }

      int32_t iLineSize = 0;

      m_iaLineLen.remove_all();

      m_iaLineEnd.remove_all();

      UINT uiPos;

      int iLastR = 0;

      while((uiRead = m_ptree->m_editfile.read(buf,m.get_size())) > 0)
      {

         uiPos = 0;

         lpsz = buf;

         while(uiPos < uiRead)
         {

            if(*lpsz == '\r')
            {

               if(iLastR)
               {

                  iLineSize++;

                  m_iaLineLen.add(iLineSize);

                  m_iaLineEnd.add(1 | 512);

                  iLineSize = 0;

                  lpsz++;

                  uiPos++;

               }

               iLastR = 1;

            }
            else if(*lpsz == '\n')
            {

               if(iLastR)
               {

                  iLineSize +=2;

                  m_iaLineLen.add(iLineSize);

                  m_iaLineEnd.add(2 | 1024);

                  iLineSize = 0;

                  lpsz += 2;

                  uiPos += 2;

               }
               else
               {

                  iLineSize++;

                  m_iaLineLen.add(iLineSize);

                  m_iaLineEnd.add(1 | 256);

                  iLineSize = 0;

                  lpsz++;

                  uiPos++;

               }

               iLastR = 0;

            }
            else
            {

               lpsz++;

               iLineSize++;

               uiPos++;

            }

         }


      }

      if(iLastR)
      {

         iLineSize++;

         m_iaLineLen.add(iLineSize);

         m_iaLineEnd.add(1 | 512);

         iLineSize = 0;

      }

      m_iaLineLen.add(iLineSize);

      m_iaLineEnd.add(0);

      ::count iAcc = 0;

      ::count iLineCount = m_iaLineLen.get_size();

      m_iaLineBeg.set_size(iLineCount);

      for(index iLine = 0; iLine < iLineCount; iLine++)
      {

         m_iaLineBeg[iLine] = iAcc;

         iAcc += m_iaLineLen[iLine];

      }

   }


   void plain_edit::_001OnChar(signal_details * pobj)
   {

      bool bUpdate = false;


      {

         _009OnChar(pobj);

         if(pobj->m_bRet)
            return;

         SCAST_PTR(::message::key,pkey,pobj);

         string strChar;

         if(Session.is_key_pressed(::user::key_control))
         {

            return;

         }

         if(pkey->m_ekey == ::user::key_s)
         {
            if(Session.is_key_pressed(::user::key_control))
            {
               return;
            }
         }
         else if(pkey->m_ekey == ::user::key_z)
         {
            if(Session.is_key_pressed(::user::key_control))
            {
               Undo();
               return;
            }
         }
         else if(pkey->m_ekey == ::user::key_y)
         {
            if(Session.is_key_pressed(::user::key_control))
            {
               Redo();
               return;
            }
         }

         {

            synch_lock sl(m_pmutex);

            synch_lock lockRoot(m_ptree == NULL ? NULL:m_ptree->m_pmutex);

            bool bShift = Session.is_key_pressed(::user::key_shift);

            if(pkey->m_ekey == ::user::key_back)
            {
               if(!m_bReadOnly)
               {
                  strsize i1 = m_ptree->m_iSelStart;
                  strsize i2 = m_ptree->m_iSelEnd;
                  if(i1 != i2)
                  {
                     plain_text_set_sel_command * psetsel = canew(plain_text_set_sel_command);
                     psetsel->m_iPreviousSelStart = m_ptree->m_iSelStart;
                     psetsel->m_iPreviousSelEnd = m_ptree->m_iSelEnd;
                     ::sort::sort(i1,i2);
                     m_ptree->m_editfile.seek(i1,::file::seek_begin);
                     m_ptree->m_editfile.Delete((memory_size_t)(i2 - i1));
                     IndexRegisterDelete(i1,i2 - i1);
                     m_ptree->m_iSelEnd = i1;
                     m_ptree->m_iSelStart = m_ptree->m_iSelEnd;
                     psetsel->m_iSelStart = m_ptree->m_iSelStart;
                     psetsel->m_iSelEnd = m_ptree->m_iSelEnd;
                     MacroBegin();
                     MacroRecord(psetsel);
                     MacroRecord(canew(plain_text_file_command()));
                     MacroEnd();
                     bUpdate = true;

                  }
                  else if(m_ptree->m_iSelEnd >= 0 && m_ptree->m_editfile.get_length() > 0)
                  {
                     plain_text_set_sel_command * psetsel = canew(plain_text_set_sel_command);
                     psetsel->m_iPreviousSelStart = m_ptree->m_iSelStart;
                     psetsel->m_iPreviousSelEnd = m_ptree->m_iSelEnd;
                     char buf[512];
                     memset(buf,0,sizeof(buf));
                     strsize iBegin = MAX(0,m_ptree->m_iSelEnd - 256);
                     strsize iCur = m_ptree->m_iSelEnd - iBegin;
                     m_ptree->m_editfile.seek(iBegin,::file::seek_begin);
                     m_ptree->m_editfile.read(buf,sizeof(buf));
                     const char * psz = ::str::utf8_dec(buf,&buf[iCur]);
                     if(psz == NULL)
                        psz = MAX(buf,&buf[iCur - 1]);
                     strsize iMultiByteUtf8DeleteCount = &buf[iCur] - psz;
                     m_ptree->m_iSelEnd -= iMultiByteUtf8DeleteCount;
                     m_ptree->m_editfile.seek(m_ptree->m_iSelEnd,::file::seek_begin);
                     m_ptree->m_editfile.Delete((memory_size_t) iMultiByteUtf8DeleteCount);
                     IndexRegisterDelete(m_ptree->m_iSelEnd,iMultiByteUtf8DeleteCount);
                     m_ptree->m_iSelStart = m_ptree->m_iSelEnd;
                     psetsel->m_iSelStart = m_ptree->m_iSelStart;
                     psetsel->m_iSelEnd = m_ptree->m_iSelEnd;
                     MacroBegin();
                     MacroRecord(psetsel);
                     MacroRecord(canew(plain_text_file_command()));
                     MacroEnd();
                     bUpdate = true;
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
                     plain_text_set_sel_command * psetsel = canew(plain_text_set_sel_command);
                     psetsel->m_iPreviousSelStart = m_ptree->m_iSelStart;
                     psetsel->m_iPreviousSelEnd = m_ptree->m_iSelEnd;
                     ::sort::sort(i1,i2);
                     m_ptree->m_editfile.seek(i1,::file::seek_begin);
                     m_ptree->m_editfile.Delete((memory_size_t) (i2 - i1));
                     m_ptree->m_iSelEnd = i1;
                     m_ptree->m_iSelStart = m_ptree->m_iSelEnd;
                     psetsel->m_iSelStart = m_ptree->m_iSelStart;
                     psetsel->m_iSelEnd = m_ptree->m_iSelEnd;
                     MacroBegin();
                     MacroRecord(psetsel);
                     MacroRecord(canew(plain_text_file_command()));
                     MacroEnd();
                     bUpdate = true;
                  }
                  else if(natural(m_ptree->m_iSelEnd) < m_ptree->m_editfile.get_length())
                  {
                     char buf[512];
                     memset(buf,0,sizeof(buf));
                     strsize iBegin = MAX(0,m_ptree->m_iSelEnd - 256);
                     strsize iCur = m_ptree->m_iSelEnd - iBegin;
                     m_ptree->m_editfile.seek(iBegin,::file::seek_begin);
                     m_ptree->m_editfile.read(buf,sizeof(buf));
                     const char * psz = ::str::utf8_dec(buf,&buf[iCur]);
                     strsize iMultiByteUtf8DeleteCount = &buf[iCur] - psz;
                     m_ptree->m_editfile.seek(m_ptree->m_iSelEnd,::file::seek_begin);
                     m_ptree->m_editfile.Delete((memory_size_t) (iMultiByteUtf8DeleteCount));
                     IndexRegisterDelete(m_ptree->m_iSelEnd,iMultiByteUtf8DeleteCount);
                     m_ptree->m_iSelStart = m_ptree->m_iSelEnd;
                     MacroBegin();
                     MacroRecord(canew(plain_text_file_command()));
                     MacroEnd();
                     bUpdate = true;
                  }
               }
            }
            else if(pkey->m_ekey == ::user::key_up)
            {
               int32_t x;
               index iLine = SelToLineX(m_ptree->m_iSelEnd,x);
               iLine--;
               m_ptree->m_iSelEnd = LineXToSel(iLine,x);
               if(!bShift)
               {
                  m_ptree->m_iSelStart = m_ptree->m_iSelEnd;
               }
            }
            else if(pkey->m_ekey == ::user::key_down)
            {
               int32_t x;
               index iLine = SelToLineX(m_ptree->m_iSelEnd,x);
               iLine++;
               m_ptree->m_iSelEnd = LineXToSel(iLine,x);
               if(!bShift)
               {
                  m_ptree->m_iSelStart = m_ptree->m_iSelEnd;
               }
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
                  m_ptree->m_editfile.seek(m_ptree->m_iSelEnd,::file::seek_begin);
                  memory_size_t uiRead = m_ptree->m_editfile.read(buf,32);
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
                     m_ptree->m_editfile.seek(MAX(0,m_ptree->m_iSelEnd - 32),::file::seek_begin);
                     psz = &buf[MIN(32,m_ptree->m_iSelEnd)];
                     memory_size_t uiRead = m_ptree->m_editfile.read(buf,64);
                     if(uiRead == 2 &&
                        psz[0] == '\r' &&
                        psz[1] == '\n')
                     {
                        m_ptree->m_iSelEnd -= 2;
                     }
                     else
                     {
                        m_ptree->m_iSelEnd -= psz - ::str::utf8_dec(buf,psz);
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
            }
            else if(pkey->m_ekey == ::user::key_home)
            {
               index iLine = SelToLine(m_ptree->m_iSelEnd);
               m_ptree->m_iSelEnd = LineColumnToSel(iLine,0);
               if(!bShift)
               {
                  m_ptree->m_iSelStart = m_ptree->m_iSelEnd;
               }
            }
            else if(pkey->m_ekey == ::user::key_end)
            {
               index iLine = SelToLine(m_ptree->m_iSelEnd);
               m_ptree->m_iSelEnd = LineColumnToSel(iLine,-1);
               if(!bShift)
               {
                  m_ptree->m_iSelStart = m_ptree->m_iSelEnd;
               }
            }
            else if(pkey->m_ekey == ::user::key_escape)
            {
            }
            else
            {
               if(!m_bReadOnly)
               {
                  if(pkey->m_ekey == ::user::key_return)
                  {
                     // Kill Focus => Kill Key Repeat timer
                     //System.simple_message_box("VK_RETURN reached plain_edit");
                  }
                  plain_text_set_sel_command * psetsel = canew(plain_text_set_sel_command);
                  psetsel->m_iPreviousSelStart = m_ptree->m_iSelStart;
                  psetsel->m_iPreviousSelEnd = m_ptree->m_iSelEnd;
                  m_ptree->m_editfile.MacroBegin();
                  strsize i1 = m_ptree->m_iSelStart;
                  strsize i2 = m_ptree->m_iSelEnd;
                  ::sort::sort(i1,i2);
                  m_ptree->m_editfile.seek(i1,::file::seek_begin);
                  m_ptree->m_editfile.Delete((memory_size_t) (i2 - i1));
                  IndexRegisterDelete(i1,i2 - i1);
                  m_ptree->m_iSelEnd = i1;
                  m_ptree->m_editfile.seek(m_ptree->m_iSelEnd,::file::seek_begin);
                  string str;
                  char ch = 0;
                  if(pkey->m_ekey == ::user::key_refer_to_text_member)
                  {
                     str = pkey->m_strText;
                  }
                  else
                  {
                     ch = (char)pkey->m_nChar;
                     if(ch == '\r')
                        ch = '\n';
                     int32_t iChar = (int32_t)pkey->m_nChar;
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
                     str = Session.keyboard().process_key(pkey);
                  }
                  string strCh(ch);
                  //               output_debug_string("thechthech");
                  //               output_debug_string(strCh);
                  //               output_debug_string(";");
                  //               output_debug_string("thekey");
                  //               output_debug_string(System.get_enum_name< ::user::e_key> (pkey->m_ekey));
                  //               output_debug_string(";");
                  //               output_debug_string("thecharthechar");
                  //               output_debug_string(str);
                  //               output_debug_string("\n");
                                 //               string strMap;
                  m_ptree->m_iSelEnd += str.get_length();
                  m_ptree->m_iSelStart = m_ptree->m_iSelEnd;
                  m_ptree-> m_editfile.Insert(str,str.get_length());
                  IndexRegisterInsert(m_ptree->m_iSelEnd,str);
                  m_ptree->m_editfile.MacroEnd();
                  psetsel->m_iSelStart = m_ptree->m_iSelStart;
                  psetsel->m_iSelEnd = m_ptree->m_iSelEnd;
                  MacroBegin();
                  MacroRecord(psetsel);
                  MacroRecord(canew(plain_text_file_command()));
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

         }

      }

      if(bUpdate)
      {

         _001OnUpdate(::action::source_user);

      }

      RedrawWindow();

   }





   void plain_edit::_001OnSysChar(signal_details * pobj)
   {

      synch_lock lockRoot(m_ptree == NULL ? NULL:m_ptree->m_pmutex);

      SCAST_PTR(::message::key,pkey,pobj);
      if(pkey->m_ekey == ::user::key_delete)
      {
         if(!m_bReadOnly)
         {
            strsize i1 = m_ptree->m_iSelStart;
            strsize i2 = m_ptree->m_iSelEnd;
            if(i1 != i2)
            {
               ::sort::sort(i1,i2);
               m_ptree->m_editfile.seek(i1,::file::seek_begin);
               m_ptree->m_editfile.Delete((memory_size_t) (i2 - i1));
               m_ptree->m_iSelEnd = i1;
               m_ptree->m_iSelStart = m_ptree->m_iSelEnd;
            }
            else if(natural(m_ptree->m_iSelEnd) < m_ptree->m_editfile.get_length())
            {
               char buf[512];
               memset(buf,0,sizeof(buf));
               strsize iBegin = MAX(0,m_ptree->m_iSelEnd - 256);
               strsize iCur = m_ptree->m_iSelEnd - iBegin;
               m_ptree->m_editfile.seek(iBegin,::file::seek_begin);
               m_ptree->m_editfile.read(buf,sizeof(buf));
               const char * psz = ::str::utf8_dec(buf,&buf[iCur]);
               strsize iMultiByteUtf8DeleteCount = &buf[iCur] - psz;
               m_ptree->m_editfile.seek(m_ptree->m_iSelEnd,::file::seek_begin);
               m_ptree->m_editfile.Delete((memory_size_t) (iMultiByteUtf8DeleteCount));
               IndexRegisterDelete(m_ptree->m_iSelEnd,iMultiByteUtf8DeleteCount);
               m_ptree->m_iSelStart = m_ptree->m_iSelEnd;
            }
         }
      }
   }


   void plain_edit::_001OnKeyboardFocusTimer(int32_t iTimer)
   {
      //if(iTimer == 0)
      //{
      //   if(m_dwLastCaret + m_dwCaretTime < get_tick_count())
      //   {
      //      m_dwLastCaret = get_tick_count();
      //      m_bCaretOn = !m_bCaretOn;
      //      //RedrawWindow();
      //      RedrawWindow();
      //   }
      //}
   }

   void plain_edit::OneLineUp()
   {

      point ptOffset = get_viewport_offset();

      set_viewport_offset_y(ptOffset.y - m_iLineHeight);

//      if(m_scrolldata.m_ptScroll.y < 0)
  //       m_scrolldata.m_ptScroll.y = 0;
      int32_t iHeight = 0;
      //char flag;
      m_iViewOffset = 0;
      ::count iLineSize;
      ::index i = 0;
      ptOffset = get_viewport_offset();
      while(ptOffset.y > iHeight && i < m_iaLineLen.get_size())
      {
         iLineSize = m_iaLineLen[i];
         iHeight += m_iLineHeight;
         m_iViewOffset += iLineSize;
         i++;
      }

   }

   void plain_edit::IndexRegisterDelete(strsize iSel,strsize iCount)
   {
      UNREFERENCED_PARAMETER(iSel);
      UNREFERENCED_PARAMETER(iCount);
      CreateLineIndex();
      m_peditor->modifyEvent(0);
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
         while(i < m_iaLineLen.get_size())
         {
         iLineSize = m_iaLineLen[i];
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
         while(i < m_iaLineLen.get_size())
         {
         iLineSize = m_iaLineLen[i];
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

   void plain_edit::IndexRegisterInsert(strsize iSel,const char * lpcszWhat)
   {
      UNREFERENCED_PARAMETER(iSel);
      UNREFERENCED_PARAMETER(lpcszWhat);
      CreateLineIndex();
      m_peditor->modifyEvent(0);
   }


   void plain_edit::_001OnUpdate(::action::context actioncontext)
   {

      {

         synch_lock sl(m_pmutex);

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

         m_bCalcLayoutHintNoTextChange = false;

         _001OnCalcLayout();

         m_peditor->lineCountEvent(m_plines->lines.get_count());

      }

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



   void plain_edit::MacroBegin()
   {
      sp(::user::plain_text_group_command) pgroupcommand = canew(plain_text_group_command);
      pgroupcommand->m_pparent = m_ptree->m_pgroupcommand;
      m_ptree->m_pgroupcommand = pgroupcommand;
   }

   void plain_edit::MacroEnd()
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


   void plain_edit::MacroRecord(sp(plain_text_command) pcommand)
   {
      if(m_ptree->m_pgroupcommand != NULL && m_ptree->m_pgroupcommand != pcommand)
      {
         m_ptree->m_pgroupcommand->add(pcommand);
         return;
      }
      m_pitem = m_ptree->insert_item(pcommand,::data::RelativeMacroRecord,m_pitem);
   }


   bool plain_edit::Undo()
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


   bool plain_edit::Redo()
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

   bool plain_edit::CanUndo()
   {
      return m_pitem != m_ptree->get_base_item();
   }

   bool plain_edit::CanRedo()
   {
      return m_ptree->m_iBranch < m_pitem->get_expandable_children_count()
         || m_pitem->get_next(false,false) != NULL;
   }

   ::count plain_edit::GetRedoBranchCount()
   {
      return m_pitem->get_expandable_children_count()
         + (m_pitem->next() != NULL ? 1 : 0)
         + (m_pitem->first_child() != NULL ? 1 : 0);
   }



   void plain_edit::_001SetText(const string & str,::action::context actioncontext)
   {
      synch_lock lockRoot(m_ptree == NULL ? NULL:m_ptree->m_pmutex);
      m_ptree->m_editfile.seek(0,::file::seek_begin);
      m_ptree->m_editfile.Delete((memory_size_t)m_ptree->m_editfile.get_length());
      m_ptree->m_editfile.seek(0,::file::seek_begin);
      m_ptree->m_editfile.Insert(str,str.get_length());
      _001OnSetText(actioncontext);
      _001OnUpdate(actioncontext);
      RedrawWindow();
   }


   void plain_edit::keyboard_focus_OnKeyDown(signal_details * pobj)
   {

      _001OnKeyDown(pobj);

   }


   void plain_edit::keyboard_focus_OnKeyUp(signal_details * pobj)
   {

      _001OnKeyUp(pobj);

   }


   void plain_edit::keyboard_focus_OnChar(signal_details * pobj)
   {

      _001OnChar(pobj);

   }


   void plain_edit::_001OnAfterChangeText(::action::context actioncontext)
   {

      ::user::control_event ev;

      ev.m_puie         = this;

      ev.m_eevent       = ::user::event_after_change_text;

      ev.m_actioncontext = actioncontext;

      BaseOnControlEvent(&ev);

   }


   void plain_edit::clipboard_copy()
   {

      if(m_bPassword)
         return;
      string str;
      _001GetSelText(str);
      Session.copydesk().set_plain_text(str);
   }

   void plain_edit::clipboard_paste()
   {

      string str;
      str = Session.copydesk().get_plain_text();
      //str.replace("\r\n","\n");
      _001SetSelText(str,::action::source::user());
      MacroBegin();
      MacroRecord(canew(plain_text_file_command()));
      MacroEnd();

      _001OnUpdate(::action::source::user());
      _001OnAfterChangeText(::action::source::user());

   }


   void plain_edit::_001OnVScroll(signal_details * pobj)
   {

      m_bCalcLayoutHintNoTextChange = true;
      m_bNeedCalcLayout = true;
      //RedrawWindow();
      pobj->m_bRet = true;
   }


   void plain_edit::_001OnHScroll(signal_details * pobj)
   {

      UNREFERENCED_PARAMETER(pobj);

      if(should_load_full_file())
      {

         m_bNeedScrollUpdate = true;
         m_bCalcLayoutHintNoTextChange = true;

      }
      else
      {

         m_bGetTextNeedUpdate = true;

      }

   }


   void plain_edit::_001OnSetText(::action::context actioncontext)
   {

      m_bNeedCalcLayout = true;
      m_bCalcLayoutHintNoTextChange = false;


   }


   bool plain_edit::should_load_full_file()
   {
      return m_bColorerTake5;
   }

   colorertake5::file_type *plain_edit::colorer_select_type()
   {

      synch_lock sl(m_pmutex);
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
      if(pview != NULL)
      {
         sp(::user::document) pdoc = pview->get_document();
         if(type == NULL)
         {
            string textStart;
            strsize totalLength = 0;
            for(int32_t i = 0; i < 4 && i < m_plines->getLineCount(); i++){
               string iLine = m_plines->getLine(i);
               textStart += iLine;
               textStart += "\n";
               totalLength += iLine.get_length();
               if(totalLength > 500) break;
            }
            type = System.parser_factory().getHRCParser()->chooseFileType(pdoc->get_file_path(),textStart,0);
         }
      }
      if(type != NULL)
      {
         type->getBaseScheme();
         m_peditor->setFileType(type);
      }
      return type;
   }

   void plain_edit::_009OnChar(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }


   bool plain_edit::create_control(class control::descriptor * pdescriptor, index iItem)
   {
      ASSERT(pdescriptor->get_type() == control_type_edit_plain_text);
      if(!create_window(pdescriptor->m_rect,pdescriptor->m_pform,pdescriptor->m_id))
      {
         TRACE("Failed to create control");
         return false;
      }
      ShowWindow(SW_HIDE);
      m_bMultiLine = pdescriptor->has_function(control::function_edit_multi_line);
      return control::create_control(pdescriptor, iItem);
   }


   bool plain_edit::keyboard_focus_is_focusable()
   {

      return is_window_enabled() && IsWindowVisible();

   }


   bool plain_edit::keyboard_focus_OnSetFocus()
   {

      if(!::user::control::keyboard_focus_OnSetFocus())
      {

         return false;

      }

      //m_bCaretOn = true;
      //m_dwLastCaret = get_tick_count();
      //SetTimer(100, 100, NULL);
      //RedrawWindow();
      return true;
   }



   sp(::data::item) plain_edit::on_allocate_item()
   {
      return canew(plain_text_command);
   }


   void plain_edit::set_root(plain_text_tree * pdata,bool bOwnData)
   {

      synch_lock lockRoot(m_ptree == NULL ? NULL:m_ptree->m_pmutex);

      if(m_ptree != NULL && m_bOwnData)
      {

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


   void plain_edit::_001OnUpdateEditFocusCopy(signal_details * pobj)
   {

      SCAST_PTR(::aura::cmd_ui,pupdatecmdui,pobj);

      string str;

      _001GetSelText(str);

      pupdatecmdui->m_pcmdui->Enable(str.has_char());

   }


   void plain_edit::_001OnEditFocusCopy(signal_details * pobj)
   {

      UNREFERENCED_PARAMETER(pobj);

      clipboard_copy();

      pobj->m_bRet = true;

   }

   void plain_edit::_001OnUpdateEditFocusPaste(signal_details * pobj)
   {
      SCAST_PTR(::aura::cmd_ui,pupdatecmdui,pobj);
         pupdatecmdui->m_pcmdui->Enable(Session.copydesk().get_plain_text().has_char());
   }

   void plain_edit::_001OnEditFocusPaste(signal_details * pobj)
   {

      UNREFERENCED_PARAMETER(pobj);

      clipboard_paste();

      pobj->m_bRet = true;

   }


   void plain_edit::_001OnSize(signal_details * pobj)
   {

      UNREFERENCED_PARAMETER(pobj);

   }


   void plain_edit::layout()
   {

      m_bNeedCalcLayout = true;
      m_bCalcLayoutHintNoTextChange = true;

   }


   bool plain_edit::ShowWindow(int32_t nCmdShow)
   {

      if(nCmdShow != SW_HIDE)
      {

         TRACE0("Going to Show plain_edit");

      }

      return ::user::control::ShowWindow(nCmdShow);

   }


   bool plain_edit::has_action_hover()
   {

      return is_window_enabled() && m_bActionHover;

   }

   bool plain_edit::has_text_input()
   {

      return is_window_enabled();

   }


   size plain_edit::get_total_size()
   {

      return m_sizeTotal;

   }


   var plain_edit::get_ex_value()
   {

      string str;

      _001GetText(str);

      return str;

   }


} // namespace core


