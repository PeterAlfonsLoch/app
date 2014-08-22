#include "framework.h"


string str_block(char ch,int32_t iSize);
void str_fill(string & str,char ch);


string str_block(char ch,int32_t iSize)
{
   string str;
   for(int32_t i = 0; i < iSize; i++)
   {
      str += ch;
   }
   return str;
}


void str_fill(string & str,char ch)
{
   str = str_block(ch,(int32_t)str.get_length());
}

namespace simple_ui
{




   password::password(sp(::axis::application) papp) :
      element(papp),
      ::user::interaction(papp),
      ::user::scroll_view(papp),
      ::colorertake5::base_editor(papp),
      ::data::data_listener(papp),
      ::user::edit_plain_text(papp),
      edit_box(papp)
   {
         m_bPassword = true;
   }

   password::~password()
   {
   }




   void password::_001OnDraw(::draw2d::graphics * pdc)
   {

      //return;

      pdc->set_text_rendering(::draw2d::text_rendering_anti_alias);

      COLORREF crBk;
      COLORREF crBkSel;
      COLORREF crSel;
      COLORREF cr;


      cr          = _001GetColor(::user::color_text);
      crBk        = _001GetColor(::user::color_background);
      crSel       = _001GetColor(::user::color_text_selected);
      crBkSel     = _001GetColor(::user::color_background_selected);


      ::job * pjob = pdc->m_pjob;

      ::user::print_job * pprintjob = NULL;
      if(pjob != NULL)
         pprintjob = dynamic_cast < ::user::print_job * > (pjob);
      else
         pprintjob = NULL;


      rect rectClient;
      GetClientRect(rectClient);

      if(pprintjob != NULL)
      {
         TRACE("Print Job Is Printing page %d",pprintjob->m_iPrintingPage);
      }



      //rectClient.deflate(0, 0, 1, 1);


      if(pprintjob == NULL)
      {

         ::user::interaction::_001OnDraw(pdc);

      }

      /*else if(!Session.savings().is_trying_to_save(::axis::resource_processing)
      && !Session.savings().is_trying_to_save(::axis::resource_blur_background))
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
      ::visual::fastblur *( *pfnNew )(sp(::axis::application)) = (::visual::fastblur *(*)(sp(::axis::application))) ::GetProcAddress(hmodule, "new_fastblur");*/
      /*            m_fastblur.alloc(allocer());
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
      ca.set_rgb(RGB(227,227,210));
      ca.hls_rate(0.0,-0.33,-0.23);
//      COLORREF crBorder = ca.get_rgb() | (0xff << 24);
      //pdc->Draw3dRect(rectClient,crBorder,crBorder);

      if(m_ptree == NULL)
         return;

      if(m_iLineHeight == 0)
      {
         pdc->OffsetViewportOrg(-m_scrollinfo.m_ptScroll.x,m_scrollinfo.m_ptScroll.y);
      }
      else
      {
         pdc->OffsetViewportOrg(-m_scrollinfo.m_ptScroll.x,-(m_scrollinfo.m_ptScroll.y % m_iLineHeight));
      }

      ::draw2d::region_sp rgn(allocer());

      rectClient.deflate(2,2);

      //ClientToScreen(rectClient);
      rgn->create_rect(rectClient);

      double left = rectClient.left;

      //   pdc->SelectClipRgn(&rgn);

      if(Session.user()->get_keyboard_focus() == this)
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
      iLineEnd = MIN(iLineEnd,straLines.get_upper_bound());
      for(index i = iLineStart; i <= iLineEnd; i++)
      {
         straLineFeed.remove_all();
         straLineFeed.add_smallest_tokens(straLines[i],m_straSep,FALSE,FALSE);
         if(straLineFeed.get_size() > 0)
         {
            strLine = straLineFeed[0];
         }
         else
         {
            strLine.Empty();
         }
         stringa stra;
         strsize i1 = iSelStart - lim;
         strsize i2 = iSelEnd - lim;
         strsize i3 = iCursor - lim;
         strsize iStart = MAX(0,i1);
         strsize iEnd = MIN(i2,strLine.get_length());
         str_fill(strLine,'*');
         str1 = strLine.Mid(0,iStart);
         str2 = strLine.Mid(iStart,iEnd - iStart);
         str3 = strLine.Mid(iEnd);
         strExtent1 = str1;
         strExtent2 = str2;
         strExtent3 = str3;
         strExtent1.replace("\t","   ");
         strExtent2.replace("\t","   ");
         strExtent3.replace("\t","   ");
            str_fill(strExtent1,'*');
            str_fill(strExtent2,'*');
            str_fill(strExtent3,'*');

         brushText->create_solid(cr);
         pdc->SelectObject(brushText);
         pdc->TextOut(left,y,strExtent1);

         sized size1(0.0,0.0);
         pdc->GetTextExtent(size1,strLine,(int32_t)strLine.length(),(int32_t)iStart);
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
         if(m_bFocus && m_bCaretOn && i3 == str1.get_length())
         {
            pdc->SelectObject(penCaret);
            pdc->MoveTo(left + size1.cx,y);
            pdc->LineTo(left + size1.cx,y + iLineHeight);
         }
         else if(m_bFocus && m_bCaretOn && i3 == (str1.get_length() + str2.get_length()))
         {
            pdc->SelectObject(penCaret);
            pdc->MoveTo(left + size2.cx + size1.cx,y);
            pdc->LineTo(left + size2.cx + size1.cx,y + iLineHeight);
         }
         y += iLineHeight;
         lim += straLines[i].get_length();
         //ASSERT(FALSE);
      }

   }










} // namespace simple_ui



