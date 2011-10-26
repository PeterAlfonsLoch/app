#include "StdAfx.h"
#include "hex_box.h"
#include "biteditor_view.h"
#include "biteditor_document.h"

namespace biteditor
{

   hex_box::hex_box(::ca::application * papp) :
      ca(papp),
      m_spfont(papp)
   {
      LOGFONT lf;
      memset(&lf, 0, sizeof(lf));
      lf.lfHeight = 16;
      lf.lfWeight = 400;
      strcpy(lf.lfFaceName, "Courier New");

      m_spfont->CreateFontIndirectA(&lf);

      m_bGetTextNeedUpdate = true;

      m_y = -1;      
      m_bMouseDown = false;
      m_dwCaretTime = 500;
      m_dwLastCaret = GetTickCount();
   }
   template <class T> void Sort( T & t1, T & t2)
   {
      if(t1 > t2)
      {
         T t = t2;
         t2 = t1;
         t1 = t;
      }
   }

   void hex_box::_001OnDraw(::ca::graphics * pdc)
   {
      if(System.get_keyboard_focus() == this)
      {
         m_bFocus = true;
      }
      else
      {
         m_bFocus = false;
      }

      single_lock sl(&m_pview->m_mutexData, true);


      m_pview->m_iViewOffset = (m_pview->m_scrollinfo.m_ptScroll.y * m_pview->m_iLineSize / m_pview->m_iLineHeight);

      COLORREF crBk = RGB(120, 80, 110);
      COLORREF crBkSel = RGB(120, 240, 150);
      COLORREF crSel = RGB(10, 30, 20);
      COLORREF cr = RGB(255, 255, 255);

      rect rectClient;
      GetClientRect(rectClient);
      pdc->FillSolidRect(rectClient, RGB(240, 255, 240));
   
      ::ca::rgn_sp rgn(get_app());

      rect rectClip(rectClient);

      //rect rectWindow;
      //GetWindowRect(rectWindow);
      //rectClip.offset(rectWindow.top_left());

      //rgn->CreateRectRgn(rectClip.left, rectClip.top, rectClip.width(), rectClip.height());



      //pdc->SelectClipRgn(rgn, RGN_COPY);

      string str;
      _001GetViewText(m_pview, str);
   
      file_position iSelStart;
      file_position iSelEnd;
      int lim = 0;


      cr = RGB(0, 0, 0);
      crBk = RGB(250, 248, 240);
      crBkSel = RGB(0, 0, 127);
      crSel = RGB(255, 255, 255);


      int y = rectClient.top;
      _001GetViewSel(iSelStart, iSelEnd);
      file_position iCursor = iSelEnd;
      Sort(iSelStart, iSelEnd);
      pdc->SelectObject(m_spfont);
      size size3 = pdc->GetTextExtent("gqYALÍ");
      int maxcy = size3.cy;
      int iLineStart = m_pview->m_iViewOffset / m_pview->m_iLineSize;
      int iLineEnd = (iLineStart * m_pview->m_iLineSize + m_pview->m_iViewSize) / m_pview->m_iLineSize + 1;

      iSelStart *= 3;
      iSelEnd *= 3;


      string strLine;
      string str1;
      string str2;
      string str3;
      string strExtent1;
      string strExtent2;
      string strExtent3;

      pdc->OffsetViewportOrg(0, - m_pview->m_scrollinfo.m_ptScroll.y % m_pview->m_iLineHeight);


      for(int iLine = iLineStart; iLine <= iLineEnd; iLine++)
      {
         read_line(strLine, iLine);
         stringa stra;
         int i1 = (int) (iSelStart - lim);
         int i2 = (int) (iSelEnd - lim);
         int i3 = (int) (iCursor - lim);
         int iStart = max(0, i1);
         int iEnd = max(min(i2, strLine.get_length()), iStart);
         str1 = strLine.Mid(0, iStart);
         str2 = strLine.Mid(iStart, iEnd - iStart);
         str3 = strLine.Mid(iEnd);
         strExtent1 = str1;
         strExtent2 = str2;
         strExtent3 = str3;
         pdc->SetBkMode(TRANSPARENT);
         pdc->SetTextColor(cr);
         pdc->SetBkColor(crBkSel);
         pdc->TextOut(rectClient.left, y, strExtent1);
         size size1 = pdc->GetTextExtent(strExtent1);
         pdc->SetBkMode(OPAQUE);
         pdc->SetTextColor(crSel);
         pdc->TextOut(rectClient.left + size1.cx, y, strExtent2);
         size size2 = pdc->GetTextExtent(strExtent2);
         pdc->SetTextColor(cr);
         pdc->SetBkColor(RGB(120, 240, 180));
         pdc->SetBkMode(TRANSPARENT);
         pdc->TextOut(rectClient.left + size1.cx + size2.cx, y, strExtent3);
         maxcy = max(size1.cy, size2.cy);
         maxcy = max(maxcy, size3.cy);
         if(m_bFocus && m_bCaretOn && i3 == str1.get_length())
         {
            pdc->MoveTo(rectClient.left + size1.cx, y);
            pdc->LineTo(rectClient.left + size1.cx, y + maxcy);
         }
         if(m_bFocus && m_bCaretOn && i3 == (str1.get_length() + str2.get_length()))
         {
            pdc->MoveTo(rectClient.left + size1.cx + size2.cx, y);
            pdc->LineTo(rectClient.left + size1.cx + size2.cx, y + maxcy);
         }
         y += maxcy;
         lim += m_pview->m_iLineSize;
      }
   }

   void hex_box::_001GetSelText(string & str) const
   {
      file_position iEnd;
      file_position iStart;
      if(m_pview->m_iSelEnd < 0)
      {
         if(m_pview->m_iSelStart < 0)
         {
            iEnd = (file_position) m_pview->get_document()->m_peditfile->get_length();
            iStart = 0;
         }
         else
         {
            iStart = m_pview->m_iSelStart;
            iEnd = (file_position) m_pview->get_document()->m_peditfile->get_length();
         }
      }
      else
      {
         if(m_pview->m_iSelStart < 0)
         {
            iEnd = m_pview->m_iSelEnd;
            iStart = 0;
         }
         else
         {
            iEnd = m_pview->m_iSelEnd;
            iStart = m_pview->m_iSelStart;
         }
      }
      strsize iSize = (strsize) (iEnd - iStart);
      char * psz = str.GetBufferSetLength(iSize + 1);
      m_pview->get_document()->m_peditfile->seek((file_offset) iStart, ::ex1::seek_begin);
      m_pview->get_document()->m_peditfile->read(psz, iSize);
      psz[iSize] = '\0';
      str.ReleaseBuffer();
   }

   void hex_box::_001OnLButtonDown(user::elemental * pview, gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pview);
      SCAST_PTR(::user::win::message::mouse, pmouse, pobj)
      m_bMouseDown = true;
      ::ca::graphics * pdc = m_pview->GetDC();
      m_pview->m_iSelStart = char_hit_test(m_pview, pdc, pmouse->m_pt.x, pmouse->m_pt.y);
      m_pview->m_iSelEnd = m_pview->m_iSelStart;
      m_pview->ReleaseDC(pdc);
      m_pview->_001RedrawWindow();
      System.set_keyboard_focus(this);
      System.set_mouse_focus_LButtonDown(this);
   
   }
   void hex_box::_001OnLButtonUp(gen::signal_object * pobj)
   {
      SCAST_PTR(::user::win::message::mouse, pmouse, pobj)
      ::ca::graphics * pdc = m_pview->GetDC();
      m_pview->m_iSelEnd = char_hit_test(m_pview, pdc,pmouse->m_pt.x, pmouse->m_pt.y);
      m_pview->m_iColumn = SelToColumn(m_pview, m_pview->m_iSelEnd);
      m_pview->ReleaseDC(pdc);
      m_pview->_001RedrawWindow();
      m_bMouseDown = false;
      //System.simple_message_box(m_strText);
   }

   void hex_box::_001OnCalcLayoutProc(biteditor_view * pview, ::ca::graphics * pdc)
   {
      UNREFERENCED_PARAMETER(pview);
      pdc->SelectObject(m_spfont);
      int64_t y = 0;
      //int i = 1;
//      char buf[4096 + 1];
//      UINT uiRead;
//      LPTSTR lpsz;
      m_pview->get_document()->m_peditfile->seek(0, ::ex1::seek_begin);
      if(m_size.cx <= 0)
         m_size.cx = 200;
      y = m_pview->m_iLineHeight * m_pview->CalcLineCount();
      if(y <= 0)
         y = 200;
      m_size.cy = (LONG) y;
      size size3 = pdc->GetTextExtent("gqYALÍpd");
      m_size.cx = size3.cx * m_pview->m_iLineSize * 3 / 8 ;
      m_pview->UpdateScrollSizes();
   }

   void hex_box::_001OnCalcLayout(biteditor_view * pview, ::ca::graphics * pdc)
   {



      /*pdc->SelectObject(m_spfont);
      string str;
      _001GetViewText(pview, str);
      stringa & straLines = m_straLines;
      file_position iSelStart;
      file_position iSelEnd;
      _001GetViewSel(iSelStart, iSelEnd);
//      int lim = 0;
      int maxcy;
      int y = 0;
//      bool bFound = false;
      string strLine;
      size size3 = pdc->GetTextExtent("gqYALÍWM");
      size size;
      m_size.cx = 0;
      for(int i = 0; i < straLines.get_size(); i++)
      {
         strLine = straLines[i];
         strLine.replace("\t", "   ");
         size = strLine.get_length() * size3.cx / 8;
         maxcy = max(size.cy, size3.cy);
         y += maxcy;
         if(size.cx > m_size.cx)
            m_size.cx = size.cx;

      }
      m_size.cy = y;*/
   }

   int64_t hex_box::SelToLine(biteditor_view * pview, file_position iSel)
   {
      iSel -= m_pview->m_iViewOffset;
      string str;
      _001GetViewText(pview, str);
      return iSel / m_pview->m_iLineSize;
   }

   file_position hex_box::LineColumnToSel(biteditor_view * pview, int64_t iLine, int iColumn)
   {
//      int i1;
//      int i2 = 0;
      while(iLine < 0)
      {
         OneLineUp(pview);
         if(m_pview->m_iViewOffset == 0)
         {
            iLine = 0;
            break;
         }
         iLine++;
      }
      string str;
      _001GetViewText(pview, str);
      int iOffset = 0;
      for(int i = 0; i < iLine; i++)
      {
         iOffset += m_pview->m_iLineSize;
      }
            if(iColumn < 0)
         iColumn = iColumn + 1 + m_pview->m_iLineSize;
      if(iColumn > m_pview->m_iLineSize)
         iColumn = m_pview->m_iLineSize;
      return m_pview->m_iViewOffset + iOffset + iColumn;
   }


   int hex_box::SelToColumn(biteditor_view * pview, file_position iSel)
   {
      iSel -= m_pview->m_iViewOffset;
      string str;
      _001GetViewText(pview, str);
      return iSel % m_pview->m_iLineSize;
   }

   file_position hex_box::char_hit_test(biteditor_view * pview, ::ca::graphics * pdc, int px, int py)
   {
      pdc->SelectObject(m_spfont);
      py += pview->m_scrollinfo.m_ptScroll.y % m_pview->m_iLineHeight;
      string str;
      _001GetViewText(pview, str);
      file_position iSelStart;
      file_position iSelEnd;
      _001GetViewSel(iSelStart, iSelEnd);
      int lim = 0;
      int maxcy;
      rect rectClient;
      GetClientRect(rectClient);
      int y = rectClient.top;
      bool bFound = false;
      string strLine;
      string strExtent;
      size size3 = pdc->GetTextExtent("gqYALÍ");
      int iOffset = 0;
      int iLineStart = m_pview->m_iViewOffset / m_pview->m_iLineSize;
      int iLineEnd = (iLineStart * m_pview->m_iLineSize + m_pview->m_iViewSize) / m_pview->m_iLineSize + 1;

      string strExtent3;
      for(int iLine = iLineStart; iLine <= iLineEnd; iLine++)
      {
         read_line(strLine, iLine);
         strExtent = strLine;
         strExtent.replace("\t", "   ");
         size size = pdc->GetTextExtent(strExtent);
         maxcy = max(size.cy, size3.cy);
         if(py >= y && py < y + maxcy)
         {
            bFound = true;
            break;
         }
         y += maxcy;
         iOffset += m_pview->m_iLineSize;
      }
      int lim2 = 0;
      int lim1;
      for(int i = 0; i < strLine.get_length(); i++)
      {
         lim1 = lim2;
         strExtent = strLine.Mid(0, i + 1);
         strExtent.replace("\t", "   ");
         lim2 = pdc->GetTextExtent(strExtent).cx;
         lim = (lim2 + lim1) / 2;
         if(px >= lim1 && px <= lim)
         {
            return iOffset+ i + m_pview->m_iViewOffset;
         }
         else if(px >= lim && px <= lim2)
         {
            return iOffset + i + 1 + m_pview->m_iViewOffset;
         }
      }
      return iOffset + strLine.get_length() + m_pview->m_iViewOffset;
   }

   void hex_box::_001OnMouseMove(user::elemental * pview, gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pview);
      SCAST_PTR(::user::win::message::mouse, pmouse, pobj)
         ::SetCursor(::LoadCursor(NULL, IDC_IBEAM));
      
      
      if(m_bMouseDown)
      {
         ::ca::graphics * pdc = m_pview->GetDC();
         m_pview->m_iSelEnd = char_hit_test(m_pview, pdc,pmouse->m_pt.x, pmouse->m_pt.y);
         m_pview->ReleaseDC(pdc);
         m_pview->_001RedrawWindow();
      }

   }

   void hex_box::_001OnGetText(biteditor_view * pview)
   {
/*      if(m_pview->m_iLineHeight <= 0)
         return;

      //if(m_bGetTextNeedUpdate)
      {
//         int iHeight = 0;
//         char flag;
         m_iViewOffset = 0;
//         int iLineSize;
         rect rectClient;
         pview->GetClientRect(rectClient);

         m_iLineOffset = pview->m_scrollinfo.m_ptScroll.y / m_pview->m_iLineHeight;

//         int iLine = 0;
//         int iCLine = iLine / 100;
         int i;

         string str;

         m_pview->m_iViewSize = 0;
         int64_t iLineCount = m_pview->CalcLineCount();
         m_iViewOffset = m_iLineOffset * m_pview->m_iLineSize;
         m_pview->get_document()->m_peditfile->seek((file_offset) m_iViewOffset, ::ex1::seek_begin);
         int iPageLineCount = rectClient.height() / m_pview->m_iLineHeight;
         i = 0;
         int iPageLine = 0;
         for(int iLine = m_iLineOffset; i < iLineCount && iPageLine < iPageLineCount; i++, iLine++, iPageLine++)
         {
            read_line(str, iL);
            m_straLines.add(str);
         }
         m_y = pview->m_scrollinfo.m_ptScroll.y;
      }*/
   }

   void hex_box::read_line(string & str, int iLine)
   {
      str.Empty();
      m_pview->get_document()->m_peditfile->seek(iLine * m_pview->m_iLineSize, ex1::seek_begin);
      int iRead = m_pview->get_document()->m_peditfile->read(m_pchLineBuffer, m_pview->m_iLineSize);
      if(iRead <= 0)
         return;
      string strHex;
      DWORD dw = m_pchLineBuffer[0] & 0x000000ff;
      str.Format("%02x", dw);
      for(int i = 1; i < iRead; i++)
      {
         dw = m_pchLineBuffer[i] & 0x000000ff;
         strHex.Format(" %02x", dw);
         str += strHex;
      }

   }


   void hex_box::_001GetViewText(biteditor_view * pview, string & str)
   {
      UNREFERENCED_PARAMETER(str);
      _001OnGetText(pview);
      //int iSize = min(m_pview->get_document()->m_peditfile->get_length() - m_iViewOffset, m_iViewSize);
      //char * psz = str.GetBufferSetLength(iSize + 1);
      //m_pview->get_document()->m_peditfile->seek(m_iViewOffset, ::ex1::seek_begin);
   }


   void hex_box::_001GetViewSel(file_position &iSelStart, file_position &iSelEnd)
   {
      iSelStart = m_pview->m_iSelStart - m_pview->m_iViewOffset;
      iSelEnd = m_pview->m_iSelEnd - m_pview->m_iViewOffset;
   }

   void hex_box::SetFile(ex1::file * pfile)
   {
      m_pview->get_document()->m_peditfile->SetFile(pfile);
      OnFileUpdate();
   }

   void hex_box::OnFileUpdate()
   {
      m_bGetTextNeedUpdate = true;
      m_y = -1;
   }


   void hex_box::_001OnChar(biteditor_view * pview, gen::signal_object * pobj)
   {
      SCAST_PTR(::user::win::message::key, pkey, pobj)
      bool bShift = (::GetKeyState(VK_SHIFT) & 0x80000000) != 0;
   
      if(pkey->m_nChar == VK_BACK)
      {
         file_position i1 = m_pview->m_iSelStart;
         file_position i2 = m_pview->m_iSelEnd;
         if(i1 != i2)
         {
            biteditor_document * pdoc = pview->get_document();
            biteditor_document::SetSelCommand * psetsel = new biteditor_document::SetSelCommand;
            psetsel->m_iPreviousSelStart = m_pview->m_iSelStart;
            psetsel->m_iPreviousSelEnd = m_pview->m_iSelEnd;
            Sort(i1, i2);
            m_pview->get_document()->m_peditfile->seek((file_offset) i1, ::ex1::seek_begin);
            m_pview->get_document()->m_peditfile->Delete((file_size) (i2 - i1));
            IndexRegisterDelete(i1, i2 - i1);
            m_pview->m_iSelEnd = i1;
            m_pview->m_iSelStart = m_pview->m_iSelEnd;
            psetsel->m_iSelStart = m_pview->m_iSelStart;
            psetsel->m_iSelEnd = m_pview->m_iSelEnd;
            pdoc->MacroBegin();
            pdoc->MacroRecord(psetsel);
            pdoc->MacroRecord(new biteditor_document::FileCommand());
            pdoc->MacroEnd();
            on_update();
         }
         else if(m_pview->m_iSelEnd >= 0 && m_pview->get_document()->m_peditfile->get_length() > 0)
         {
            biteditor_document * pdoc = pview->get_document();
            biteditor_document::SetSelCommand * psetsel = new biteditor_document::SetSelCommand;
            psetsel->m_iPreviousSelStart = m_pview->m_iSelStart;
            psetsel->m_iPreviousSelEnd = m_pview->m_iSelEnd;
            m_pview->m_iSelEnd--;
            m_pview->get_document()->m_peditfile->seek((file_offset) m_pview->m_iSelEnd, ::ex1::seek_begin);
            m_pview->get_document()->m_peditfile->Delete((::primitive::memory_size) 1);
            IndexRegisterDelete(m_pview->m_iSelEnd, 1);
            m_pview->m_iSelStart = m_pview->m_iSelEnd;
            psetsel->m_iSelStart = m_pview->m_iSelStart;
            psetsel->m_iSelEnd = m_pview->m_iSelEnd;
            pdoc->MacroBegin();
            pdoc->MacroRecord(psetsel);
            pdoc->MacroRecord(new biteditor_document::FileCommand());
            pdoc->MacroEnd();
            on_update();
         }
      }
      else if(pkey->m_nChar == VK_UP)
      {
         int64_t iLine = SelToLine(pview, m_pview->m_iSelEnd);
         iLine--;
         m_pview->m_iSelEnd = LineColumnToSel(pview, iLine, m_pview->m_iColumn);
         if(!bShift)
         {
            m_pview->m_iSelStart = m_pview->m_iSelEnd;
         }
         pview->_001RedrawWindow();
      }
      else if(pkey->m_nChar == VK_DOWN)
      {
         int64_t iLine = SelToLine(pview, m_pview->m_iSelEnd);
         iLine++;
         m_pview->m_iSelEnd = LineColumnToSel(pview, iLine, m_pview->m_iColumn);
         if(!bShift)
         {
            m_pview->m_iSelStart = m_pview->m_iSelEnd;
         }
         pview->_001RedrawWindow();
      }
      else if(pkey->m_nChar == VK_RIGHT)
      {
         if(!bShift && m_pview->m_iSelStart > m_pview->m_iSelEnd)
         {
            m_pview->m_iSelEnd = m_pview->m_iSelStart;
         }
         else if(!bShift && m_pview->m_iSelEnd > m_pview->m_iSelStart)
         {
            m_pview->m_iSelStart = m_pview->m_iSelEnd;
         }
         else if(m_pview->m_iSelEnd < m_pview->get_document()->m_peditfile->get_length())
         {
            char buf[2];
            m_pview->get_document()->m_peditfile->seek((file_offset) m_pview->m_iSelEnd, ::ex1::seek_begin);
            UINT uiRead = m_pview->get_document()->m_peditfile->read(buf, 2);
            if(uiRead == 2 &&
               buf[0] == '\r' &&
               buf[1] == '\n')
            {
               m_pview->m_iSelEnd += 2;
            }
            else
            {
               m_pview->m_iSelEnd ++;
            }
            if(!bShift)
            {
               m_pview->m_iSelStart = m_pview->m_iSelEnd;
            }
         }
         pview->_001RedrawWindow();
      }
      else if(pkey->m_nChar == VK_LEFT)
      {
         if(!bShift && m_pview->m_iSelStart < m_pview->m_iSelEnd)
         {
            m_pview->m_iSelEnd = m_pview->m_iSelStart;
         }
         else if(!bShift && m_pview->m_iSelEnd < m_pview->m_iSelStart)
         {
            m_pview->m_iSelStart = m_pview->m_iSelEnd;
         }
         else if(m_pview->m_iSelEnd > 0)
         {
            if(m_pview->m_iSelEnd > 2)
            {
               char buf[2];
               m_pview->get_document()->m_peditfile->seek(m_pview->m_iSelEnd - 2, ::ex1::seek_begin);
               UINT uiRead = m_pview->get_document()->m_peditfile->read(buf, 2);
               if(uiRead == 2 &&
                  buf[0] == '\r' &&
                  buf[1] == '\n')
               {
                  m_pview->m_iSelEnd -= 2;
               }
               else
               {
                  m_pview->m_iSelEnd --;
               }
            }
            else
            {
               m_pview->m_iSelEnd--;
            }
            if(!bShift)
            {
               m_pview->m_iSelStart = m_pview->m_iSelEnd;
            }
         }
         pview->_001RedrawWindow();
      }
      else if(pkey->m_nChar == VK_HOME)
      {
         int64_t iLine = SelToLine(pview, m_pview->m_iSelEnd);
         m_pview->m_iSelEnd = LineColumnToSel(pview, iLine, 0);
         if(!bShift)
         {
            m_pview->m_iSelStart = m_pview->m_iSelEnd;
         }
         pview->_001RedrawWindow();
      }
      else if(pkey->m_nChar == VK_END)
      {
         int64_t iLine = SelToLine(pview, m_pview->m_iSelEnd);
         m_pview->m_iSelEnd = LineColumnToSel(pview, iLine, -1);
         if(!bShift)
         {
            m_pview->m_iSelStart = m_pview->m_iSelEnd;
         }
         pview->_001RedrawWindow();
      }
      else
      {
         if(pkey->m_nChar == VK_RETURN)
         {
            // Kill Focus => Kill Key Repeat Timer
            //System.simple_message_box("VK_RETURN reached hex_box");
         }
         biteditor_document * pdoc = pview->get_document();
         biteditor_document::SetSelCommand * psetsel = new biteditor_document::SetSelCommand;
         psetsel->m_iPreviousSelStart = m_pview->m_iSelStart;
         psetsel->m_iPreviousSelEnd = m_pview->m_iSelEnd;
         m_pview->get_document()->m_peditfile->MacroBegin();
         file_position i1 = m_pview->m_iSelStart;
         file_position i2 = m_pview->m_iSelEnd;
         Sort(i1, i2);
         m_pview->get_document()->m_peditfile->seek((file_offset) i1, ::ex1::seek_begin);
         m_pview->get_document()->m_peditfile->Delete((file_size) (i2 - i1));
         IndexRegisterDelete(i1, i2 - i1);
         m_pview->m_iSelEnd = i1;
         m_pview->get_document()->m_peditfile->seek((file_offset) m_pview->m_iSelEnd, ::ex1::seek_begin);
         m_pview->m_iSelEnd++;
         m_pview->m_iSelStart = m_pview->m_iSelEnd;
         string str;
         char ch = (char) pkey->m_nChar;
         int iChar = pkey->m_nChar;
         if(bShift)
         {
            iChar |= 0x80000000;
         }
//         int i;
         str = ch;
         m_pview->get_document()->m_peditfile->Insert(&ch, 1);
         IndexRegisterInsert(m_pview->m_iSelEnd, str);
         m_pview->get_document()->m_peditfile->MacroEnd();
         psetsel->m_iSelStart = m_pview->m_iSelStart;
         psetsel->m_iSelEnd = m_pview->m_iSelEnd;
         pdoc->MacroBegin();
         pdoc->MacroRecord(psetsel);
         pdoc->MacroRecord(new biteditor_document::FileCommand());
         pdoc->MacroEnd();
         on_update();
      }
      if(pkey->m_nChar != VK_UP
      && pkey->m_nChar != VK_DOWN)
      {
         m_pview->m_iColumn = SelToColumn(pview, m_pview->m_iSelEnd);
      }
      m_dwLastCaret = ::GetTickCount();
      m_bCaretOn = true;
      pview->_001RedrawWindow();
   }

   void hex_box::_001OnSysChar(biteditor_view * pview, gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pview);
      SCAST_PTR(::user::win::message::key, pkey, pobj)
      if(pkey->m_nChar == VK_DELETE)
      {
         file_position i1 = m_pview->m_iSelStart;
         file_position i2 = m_pview->m_iSelEnd;
         if(i1 != i2)
         {
            Sort(i1, i2);
            m_pview->get_document()->m_peditfile->seek((file_offset) i1, ::ex1::seek_begin);
            m_pview->get_document()->m_peditfile->Delete((file_size) (i2 - i1));
            m_pview->m_iSelEnd = i1;
            m_pview->m_iSelStart = m_pview->m_iSelEnd;
         }
         else if(m_pview->m_iSelEnd < m_pview->get_document()->m_peditfile->get_length())
         {
            m_pview->get_document()->m_peditfile->seek((file_offset) m_pview->m_iSelEnd, ::ex1::seek_begin);
            m_pview->get_document()->m_peditfile->Delete((::primitive::memory_size) 1);
            m_pview->m_iSelStart = m_pview->m_iSelEnd;
         }
      }
   }


   void hex_box::_001OnKeyboardFocusTimer(biteditor_view * pview, int iTimer)
   {
      if(iTimer == 0)
      {
         if(m_dwLastCaret + m_dwCaretTime < GetTickCount())
         {
            m_dwLastCaret = GetTickCount();
            m_bCaretOn = !m_bCaretOn;
            pview->_001RedrawWindow();
         }
      }
   }

   void hex_box::OneLineUp(biteditor_view * pview)
   {
      pview->m_scrollinfo.m_ptScroll.y -= m_pview->m_iLineHeight;
      if(pview->m_scrollinfo.m_ptScroll.y < 0)
         pview->m_scrollinfo.m_ptScroll.y = 0;
      int iHeight = 0;
//      char flag;
      m_pview->m_iViewOffset = 0;
      int iLineSize;
      int i = 0;
      int64_t iLineCount = m_pview->CalcLineCount();
      while(pview->m_scrollinfo.m_ptScroll.y > iHeight && i < iLineCount)
      {
         iLineSize = m_pview->m_iLineSize;
         iHeight += m_pview->m_iLineHeight;
         m_pview->m_iViewOffset += iLineSize;
         i++;
      }

   }

   void hex_box::IndexRegisterDelete(file_position iSel, file_size iCount)
   {
      UNREFERENCED_PARAMETER(iSel);
      UNREFERENCED_PARAMETER(iCount);
   }

   void hex_box::IndexRegisterInsert(file_position iSel, const char * lpcszWhat)
   {
      UNREFERENCED_PARAMETER(iSel);
      UNREFERENCED_PARAMETER(lpcszWhat);
   }

   void hex_box::on_update()
   {
      m_bGetTextNeedUpdate = 1;
      m_y = -1;
      m_pchLineBuffer = new char[m_pview->m_iLineSize];
   }


} // namespace biteditor
