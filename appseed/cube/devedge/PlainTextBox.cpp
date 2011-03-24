#include "StdAfx.h"
#include "PlainTextBox.h"
#include "devedgeView.h"
#include "devedgeDoc.h"




namespace devedge
{

	PlainTextBox::PlainTextBox()
	{
      m_bGetTextNeedUpdate = true;

	   m_straSep.Add("\n");
	   m_straSep.Add("\r");
	   m_straSep.Add("\r\n");

      m_imapAbnt.SetAt(188, ',');
      m_imapAbnt.SetAt(190, '.');
      m_imapAbnt.SetAt(190 | 0x80000000, '>');
      m_imapAbnt.SetAt(189, '-');
      m_imapAbnt.SetAt(189 | 0x80000000, '_');
      m_imapAbnt.SetAt('1' | 0x80000000, '!');
      m_imapAbnt.SetAt('2' | 0x80000000, '@');
      m_imapAbnt.SetAt('3' | 0x80000000, '#');
      m_imapAbnt.SetAt('4' | 0x80000000, '$');
      m_imapAbnt.SetAt('5' | 0x80000000, '%');
      m_imapAbnt.SetAt('6' | 0x80000000, '¨');
      m_imapAbnt.SetAt('7' | 0x80000000, '&');
      m_imapAbnt.SetAt('8' | 0x80000000, '*');
      m_imapAbnt.SetAt('9' | 0x80000000, '(');
      m_imapAbnt.SetAt('0' | 0x80000000, ')');

      m_y = -1;      
      m_iaLineIndex.SetSize(0, 100000);
      m_iaLineEndIndex.SetSize(0, 100000);
      m_iaCLineIndex.SetSize(0, 1000);
		m_iViewOffset = 0;
		m_iViewSize = 1000;
		m_bMouseDown = false;
		m_pfont = NULL;
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

void PlainTextBox::_001OnDraw(devedgeView * pview, CDC * pdc)
{
   if(pview->m_pkeyboardfocus == (KeyboardFocus *) this)
   {
      m_bFocus = true;
   }
   else
   {
      m_bFocus = false;
   }
	string str;
	_001GetViewText(pview, str);
	
	int iSelStart;
	int iSelEnd;
	int lim = 0;

   COLORREF crBk = RGB(120, 80, 110);
   COLORREF crBkSel = RGB(120, 240, 150);
   COLORREF crSel = RGB(10, 30, 20);
   COLORREF cr = RGB(255, 255, 255);

   cr = RGB(0, 0, 0);
   crBk = RGB(250, 248, 240);
   crBkSel = RGB(0, 0, 127);
   crSel = RGB(255, 255, 255);

   BaseRect rectClient;

   rectClient.top = m_pt.y;
   rectClient.left = m_pt.x;
   rectClient.bottom = rectClient.top + m_size.cy;
   rectClient.right = rectClient.left + m_size.cx;
   pdc->FillSolidRect(rectClient, crBk);

	
	int y = m_pt.y;
	_001GetViewSel(iSelStart, iSelEnd);
   int iCursor = iSelEnd;
	Sort(iSelStart, iSelEnd);
	if(m_pfont != NULL)
	{
		pdc->SelectObject(m_pfont);
	}
	size size3 = pdc->GetTextExtent("gqYALÍ");
	int maxcy = size3.cy;
   AStrArray & straLines = m_straLines;
   AStrArray straLineFeed;
   string strLine;
   string str1;
   string str2;
   string str3;
   string strExtent1;
   string strExtent2;
   string strExtent3;
	for(int i = 0; i < straLines.GetSize(); i++)
	{
      straLineFeed.RemoveAll();
      straLineFeed.AddSmallestTokens(straLines[i], m_straSep, FALSE, FALSE);
      if(straLineFeed.GetSize() > 0)
      {
		   strLine = straLineFeed[0];
      }
      else
      {
         strLine.Empty();
      }
		AStrArray stra;
		int i1 = iSelStart - lim;
		int i2 = iSelEnd - lim;
      int i3 = iCursor - lim;
		int iStart = max(0, i1);
		int iEnd = min(i2, strLine.GetLength());
		str1 = strLine.Mid(0, iStart);
		str2 = strLine.Mid(iStart, iEnd - iStart);
		str3 = strLine.Mid(iEnd);
      strExtent1 = str1;
      strExtent2 = str2;
      strExtent3 = str3;
      strExtent1.Replace("\t", "   ");
      strExtent2.Replace("\t", "   ");
      strExtent3.Replace("\t", "   ");
		pdc->SetBkMode(TRANSPARENT);
      pdc->SetTextColor(cr);
      pdc->SetBkColor(crBkSel);
		pdc->TextOut(m_pt.x, y, strExtent1);
		size size1 = pdc->GetTextExtent(strExtent1);
		pdc->SetBkMode(OPAQUE);
      pdc->SetTextColor(crSel);
		pdc->TextOut(m_pt.x + size1.cx, y, strExtent2);
		size size2 = pdc->GetTextExtent(strExtent2);
      pdc->SetTextColor(cr);
      pdc->SetBkColor(RGB(120, 240, 180));
		pdc->SetBkMode(TRANSPARENT);
		pdc->TextOut(m_pt.x + size1.cx + size2.cx, y, strExtent3);
		maxcy = max(size1.cy, size2.cy);
		maxcy = max(maxcy, size3.cy);
      if(m_bFocus && m_bCaretOn && i3 == str1.GetLength())
      {
         pdc->MoveTo(m_pt.x + size1.cx, y);
         pdc->LineTo(m_pt.x + size1.cx, y + maxcy);
      }
      if(m_bFocus && m_bCaretOn && i3 == (str1.GetLength() + str2.GetLength()))
      {
         pdc->MoveTo(m_pt.x + size1.cx + size2.cx, y);
         pdc->LineTo(m_pt.x + size1.cx + size2.cx, y + maxcy);
      }
		y += maxcy;
		lim += straLines[i].GetLength();
	}
}

void PlainTextBox::_001GetSelText(string & str)
{
	int iEnd;
	int iStart;
	if(m_iSelEnd < 0)
	{
		if(m_iSelStart < 0)
		{
			iEnd = m_editfile.GetLength();
			iStart = 0;
		}
		else
		{
			iStart = m_iSelStart;
			iEnd = m_editfile.GetLength();
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
	int iSize = iEnd - iStart;
	char * psz = str.GetBufferSetLength(iSize + 1);
	m_editfile.Seek(iStart, Ex1File::SeekBegin);
	m_editfile.Read(psz, iSize);
	psz[iSize] = '\0';
	str.ReleaseBuffer();
}

void PlainTextBox::_001OnLButtonDown(devedgeView * pview, gen::signal_object * pobj)
{
	SCAST_PTR(igui::win::message::mouse, pmouse, pobj)
	m_bMouseDown = true;
	CDC * pdc = pview->GetDC();
	m_iSelStart = char_hit_test(pview, pdc, pmouse->m_pt.x, pmouse->m_pt.y);
	m_iSelEnd = m_iSelStart;
	pview->ReleaseDC(pdc);
	pview->_001RedrawWindow();
	pview->m_pelementMouseDown = this;
	
}
void PlainTextBox::_001OnLButtonUp(devedgeView * pview, gen::signal_object * pobj)
{
	SCAST_PTR(igui::win::message::mouse, pmouse, pobj)
	CDC * pdc = pview->GetDC();
	m_iSelEnd = char_hit_test(pview, pdc,pmouse->m_pt.x, pmouse->m_pt.y);
   m_iColumn = SelToColumn(pview, m_iSelEnd);
	pview->ReleaseDC(pdc);
	pview->_001RedrawWindow();
	m_bMouseDown = false;
	//AfxMessageBox(m_strText);
}

void PlainTextBox::_001OnCalcLayoutProc(devedgeView * pview, CDC * pdc)
{
   if(m_pfont != NULL)
	{
		pdc->SelectObject(m_pfont);
	}
   int y = 0;
   int i = 1;
	size size3 = pdc->GetTextExtent("gqYALÍ");

   m_iLineHeight = size3.cy;
   char buf[4096 + 1];
   UINT uiRead;
   LPTSTR lpsz;
   m_editfile.Seek(0, Ex1File::SeekBegin);
   if(m_size.cx <= 0)
      m_size.cx = 200;
   y = m_iLineHeight * m_iaLineIndex.GetSize();
   if(y <= 0)
      y = 200;
	m_size.cy = y;
   pview->SetScrollSizes(MM_TEXT, 
      m_size);
}

void PlainTextBox::_001OnCalcLayout(devedgeView * pview, CDC * pdc)
{
if(m_pfont != NULL)
	{
		pdc->SelectObject(m_pfont);
	}
	string str;
	_001GetViewText(pview, str);
   AStrArray & straLines = m_straLines;
	int iSelStart;
	int iSelEnd;
	_001GetViewSel(iSelStart, iSelEnd);
	int lim = 0;
	int maxcy;
	int y = 0;
	bool bFound = false;
	string strLine;
	size size3 = pdc->GetTextExtent("gqYALÍWM");
	size size;
	m_size.cx = 0;
	for(int i = 0; i < straLines.GetSize(); i++)
	{
		strLine = straLines[i];
      strLine.Replace("\t", "   ");
		size = strLine.GetLength() * size3.cx / 8;
		maxcy = max(size.cy, size3.cy);
		y += maxcy;
		if(size.cx > m_size.cx)
			m_size.cx = size.cx;

	}
	m_size.cy = y;
}

int PlainTextBox::SelToLine(devedgeView * pview, int iSel)
{
   iSel -= m_iViewOffset;
	string str;
	_001GetViewText(pview, str);
	AStrArray & straLines = m_straLines;
   int i1;
   int i2 = 0;
   for(int i = 0; i < straLines.GetSize(); i++)
   {
      i1 = i2;
      i2 = i1 + straLines[i].GetLength();
      if(iSel >= i1
         && iSel < i2)
      {
         return i;
      }
   }
   return -1;
}

int PlainTextBox::LineColumnToSel(devedgeView * pview, int iLine, int iColumn)
{
   int i1;
   int i2 = 0;
   while(iLine < 0)
   {
      OneLineUp(pview);
      if(m_iViewOffset == 0)
      {
         iLine = 0;
         break;
      }
      iLine++;
   }
	string str;
	_001GetViewText(pview, str);
	AStrArray & straLines = m_straLines;
   if(iLine >= straLines.GetSize())
   {
      return 0;
   }
   int iOffset = 0;
   for(int i = 0; i < iLine; i++)
   {
      iOffset += straLines[i].GetLength();
   }
   AStrArray stra;
   string strLine;
   stra.RemoveAll();
   stra.AddSmallestTokens(straLines[iLine], m_straSep, FALSE, FALSE);
   if(stra.GetSize() > 0)
   {
	   strLine = stra[0];
   }
   else
   {
      strLine.Empty();
   }
   if(iColumn < 0)
      iColumn = iColumn + 1 + strLine.GetLength();
   if(iColumn > strLine.GetLength())
      iColumn = strLine.GetLength();
   return m_iViewOffset + iOffset + iColumn;
}


int PlainTextBox::SelToColumn(devedgeView * pview, int iSel)
{
   iSel -= m_iViewOffset;
	string str;
	_001GetViewText(pview, str);
	AStrArray & straLines = m_straLines;
   int i1;
   int i2 = 0;
   for(int i = 0; i < straLines.GetSize(); i++)
   {
      i1 = i2;
      i2 = i1 + straLines[i].GetLength();
      if(iSel >= i1
         && iSel <= i2)
      {
         return iSel - i1;
      }
   }
   return -1;
}

int PlainTextBox::char_hit_test(devedgeView * pview, CDC * pdc, int px, int py)
{
   if(m_pfont != NULL)
	{
		pdc->SelectObject(m_pfont);
	}
   py += pview->m_ptScroll.y % m_iLineHeight;
	string str;
	_001GetViewText(pview, str);
	AStrArray & straLines = m_straLines;
	int iSelStart;
	int iSelEnd;
	_001GetViewSel(iSelStart, iSelEnd);
	int lim = 0;
	int maxcy;
	int y = m_pt.y;
	bool bFound = false;
	string strLine;
   string strExtent;
	size size3 = pdc->GetTextExtent("gqYALÍ");
	int iOffset = 0;
   AStrArray stra;
	for(int i = 0; i < straLines.GetSize(); i++)
	{
      stra.RemoveAll();
      stra.AddSmallestTokens(straLines[i], m_straSep, FALSE, FALSE);
      if(stra.GetSize() > 0)
      {
		   strLine = stra[0];
      }
      else
      {
         strLine.Empty();
      }
      strExtent = strLine;
      strExtent.Replace("\t", "   ");
		size size = pdc->GetTextExtent(strExtent);
		maxcy = max(size.cy, size3.cy);
		if(py >= y && py < y + maxcy)
		{
			bFound = true;
			break;
		}
		y += maxcy;
		iOffset += straLines[i].GetLength();
	}
	int lim2 = 0;
	int lim1;
	for(int i = 0; i < strLine.GetLength(); i++)
	{
		lim1 = lim2;
      strExtent = strLine.Mid(0, i + 1);
      strExtent.Replace("\t", "   ");
		lim2 = pdc->GetTextExtent(strExtent).cx;
		lim = (lim2 + lim1) / 2;
		if(px >= lim1 && px <= lim)
		{
			return iOffset+ i + m_iViewOffset;
		}
		else if(px >= lim && px <= lim2)
		{
			return iOffset + i + 1 + m_iViewOffset;
		}
	}
	return iOffset + strLine.GetLength() + m_iViewOffset;
}

void PlainTextBox::_001OnMouseMove(devedgeView * pview, gen::signal_object * pobj)
{
	SCAST_PTR(igui::win::message::mouse, pmouse, pobj)
      ::SetCursor(::LoadCursor(NULL, IDC_IBEAM));
      
      
		if(m_bMouseDown)
		{
		CDC * pdc = pview->GetDC();
		m_iSelEnd = char_hit_test(pview, pdc,pmouse->m_pt.x, pmouse->m_pt.y);
		pview->ReleaseDC(pdc);
		pview->_001RedrawWindow();
		}

}

void PlainTextBox::_001OnGetText(devedgeView * pview)
{
   //if(m_bGetTextNeedUpdate)
   {
      int iHeight = 0;
      char flag;
      m_iViewOffset = 0;
      int iLineSize;
      rect rectClient;
      pview->GetClientRect(rectClient);

      m_iLineOffset = pview->m_ptScroll.y / m_iLineHeight;

      int iLine = 0;
      int iCLine = iLine / 100;
      int i;

      m_iViewOffset = 0;

      for(iLine = 0, i = 0; i < iCLine; i++, iLine += 100)
      {
         m_iViewOffset += m_iaCLineIndex[i];
      }
      for(; iLine < m_iLineOffset && iLine < m_iaLineIndex.GetSize(); iLine++)
      {
         m_iViewOffset += m_iaLineIndex[iLine];
      }
      m_iViewSize = 0;
      int iLineCount = (rectClient.Height() / m_iLineHeight) + 1;
      for(i = 0; i < iLineCount && iLine < m_iaLineIndex.GetSize(); i++, iLine++)
      {
         m_iViewSize += m_iaLineIndex[iLine];
      }
      m_straLines.SetSize(0, 100);
      string str;
      m_editfile.Seek(m_iViewOffset, Ex1File::SeekBegin);
      iLine = m_iLineOffset;
      i = 0;
      for(int iLine = m_iLineOffset; i < iLineCount && iLine < m_iaLineIndex.GetSize(); i++, iLine++)
      {
         int iLen = m_iaLineIndex[iLine];
         LPTSTR lpsz = str.GetBufferSetLength(iLen + 1);
         m_editfile.Read(lpsz, iLen);
         lpsz[iLen] = '\0';
         str.ReleaseBuffer();
	      m_straLines.Add(str);
      }
      m_y = pview->m_ptScroll.y;
   }
}


void PlainTextBox::_001GetViewText(devedgeView * pview, string & str)
{
   _001OnGetText(pview);
   //int iSize = min(m_editfile.GetLength() - m_iViewOffset, m_iViewSize);
   //char * psz = str.GetBufferSetLength(iSize + 1);
   //m_editfile.Seek(m_iViewOffset, Ex1File::SeekBegin);
}


void PlainTextBox::_001GetViewSel(int &iSelStart, int &iSelEnd)
{
	iSelStart = m_iSelStart - m_iViewOffset;
	iSelEnd = m_iSelEnd - m_iViewOffset;
}

void PlainTextBox::SetFile(Ex1File * pfile)
{
   m_editfile.SetFile(pfile);
   OnFileUpdate();
}

void PlainTextBox::OnFileUpdate()
{
   m_bGetTextNeedUpdate = true;
   CreateLineIndex();
   m_y = -1;
}

void PlainTextBox::CreateLineIndex()
{
   int y = 0;
   int i = 1;
   char buf[1024 * 256 + 1];
   UINT uiRead;
   LPTSTR lpsz;
   m_iaLineIndex.RemoveAll();
   m_iaLineEndIndex.RemoveAll();
   m_editfile.Seek(0, Ex1File::SeekBegin);
   if(m_size.cx <= 0)
      m_size.cx = 200;
   int iLineSize = 0;
   char flags[3];
   flags[0] = 3;
   flags[1] = 1;
   flags[2] = 2;
	while((uiRead = m_editfile.Read(buf, sizeof(buf) - 1)) > 0)
	{
      buf[uiRead] = '\0';
      lpsz = buf;
      while(*lpsz != NULL)
      {
         if(*lpsz == '\r' && (*(lpsz + 1)) == '\n')
         {
            iLineSize +=2;
            m_iaLineIndex.Add(iLineSize);
            m_iaLineEndIndex.Add(3);
            iLineSize = 0;
            lpsz += 2;
         }
         else if(*lpsz == '\n')
         {
            iLineSize++;
            m_iaLineIndex.Add(iLineSize);
            m_iaLineEndIndex.Add(1);
            iLineSize = 0;
            lpsz++;
         }
         else if(*lpsz == '\r')
         {
            iLineSize++;
            m_iaLineIndex.Add(iLineSize);
            m_iaLineEndIndex.Add(2);
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
   if(iLineSize > 0)
   {
      m_iaLineIndex.Add(iLineSize);
      m_iaLineEndIndex.Add(0);
   }

   int iAcc;
   int iLineCount;
   i = 0;
   while(i < m_iaLineIndex.GetSize())
   {
      iAcc = 0;
      iLineCount = 0;
      for(; iLineCount < 100 && i < m_iaLineIndex.GetSize(); i++, iLineCount++)
      {
         iAcc += m_iaLineIndex[i];
      }
      m_iaCLineIndex.Add(iAcc);
   }
}

void PlainTextBox::_001OnChar(devedgeView * pview, gen::signal_object * pobj)
{
   SCAST_PTR(igui::win::message::key, pkey, pobj)
   bool bShift = ::GetKeyState(VK_SHIFT) & 0x80000000;
   
   if(pkey->m_nChar == VK_BACK)
   {
      int i1 = m_iSelStart;
      int i2 = m_iSelEnd;
      if(i1 != i2)
      {
         devedgeDoc * pdoc = pview->GetDocument();
         devedgeDoc::SetSelCommand * psetsel = new devedgeDoc::SetSelCommand;
         psetsel->m_iPreviousSelStart = m_iSelStart;
         psetsel->m_iPreviousSelEnd = m_iSelEnd;
         Sort(i1, i2);
         m_editfile.Seek(i1, Ex1File::SeekBegin);
         m_editfile.Delete(i2 - i1);
         IndexRegisterDelete(i1, i2 - i1);
         m_iSelEnd = i1;
         m_iSelStart = m_iSelEnd;
         psetsel->m_iSelStart = m_iSelStart;
         psetsel->m_iSelEnd = m_iSelEnd;
         pdoc->MacroBegin();
         pdoc->MacroRecord(psetsel);
         pdoc->MacroRecord(new devedgeDoc::FileCommand());
         pdoc->MacroEnd();
         OnUpdate();
      }
      else if(m_iSelEnd >= 0 && m_editfile.GetLength() > 0)
      {
         devedgeDoc * pdoc = pview->GetDocument();
         devedgeDoc::SetSelCommand * psetsel = new devedgeDoc::SetSelCommand;
         psetsel->m_iPreviousSelStart = m_iSelStart;
         psetsel->m_iPreviousSelEnd = m_iSelEnd;
         m_iSelEnd--;
         m_editfile.Seek(m_iSelEnd, Ex1File::SeekBegin);
         m_editfile.Delete(1);
         IndexRegisterDelete(m_iSelEnd, 1);
         m_iSelStart = m_iSelEnd;
         psetsel->m_iSelStart = m_iSelStart;
         psetsel->m_iSelEnd = m_iSelEnd;
         pdoc->MacroBegin();
         pdoc->MacroRecord(psetsel);
         pdoc->MacroRecord(new devedgeDoc::FileCommand());
         pdoc->MacroEnd();
         OnUpdate();
      }
   }
   else if(pkey->m_nChar == VK_UP)
   {
      int iLine = SelToLine(pview, m_iSelEnd);
      iLine--;
      m_iSelEnd = LineColumnToSel(pview, iLine, m_iColumn);
      if(!bShift)
      {
         m_iSelStart = m_iSelEnd;
      }
      pview->_001RedrawWindow();
   }
   else if(pkey->m_nChar == VK_DOWN)
   {
      int iLine = SelToLine(pview, m_iSelEnd);
      iLine++;
      m_iSelEnd = LineColumnToSel(pview, iLine, m_iColumn);
      if(!bShift)
      {
         m_iSelStart = m_iSelEnd;
      }
      pview->_001RedrawWindow();
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
      else if(m_iSelEnd < m_editfile.GetLength())
      {
         char buf[2];
         m_editfile.Seek(m_iSelEnd, Ex1File::SeekBegin);
         UINT uiRead = m_editfile.Read(buf, 2);
         if(uiRead == 2 &&
            buf[0] == '\r' &&
            buf[1] == '\n')
         {
            m_iSelEnd += 2;
         }
         else
         {
            m_iSelEnd ++;
         }
         if(!bShift)
         {
            m_iSelStart = m_iSelEnd;
         }
      }
      pview->_001RedrawWindow();
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
            char buf[2];
            m_editfile.Seek(m_iSelEnd - 2, Ex1File::SeekBegin);
            UINT uiRead = m_editfile.Read(buf, 2);
            if(uiRead == 2 &&
               buf[0] == '\r' &&
               buf[1] == '\n')
            {
               m_iSelEnd -= 2;
            }
            else
            {
               m_iSelEnd --;
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
      pview->_001RedrawWindow();
   }
   else if(pkey->m_nChar == VK_HOME)
   {
      int iLine = SelToLine(pview, m_iSelEnd);
      m_iSelEnd = LineColumnToSel(pview, iLine, 0);
      if(!bShift)
      {
         m_iSelStart = m_iSelEnd;
      }
      pview->_001RedrawWindow();
   }
   else if(pkey->m_nChar == VK_END)
   {
      int iLine = SelToLine(pview, m_iSelEnd);
      m_iSelEnd = LineColumnToSel(pview, iLine, -1);
      if(!bShift)
      {
         m_iSelStart = m_iSelEnd;
      }
      pview->_001RedrawWindow();
   }
   else
   {
      if(pkey->m_nChar == VK_RETURN)
      {
         // Kill Focus => Kill Key Repeat Timer
         //AfxMessageBox("VK_RETURN reached PlainTextBox");
      }
      devedgeDoc * pdoc = pview->GetDocument();
      devedgeDoc::SetSelCommand * psetsel = new devedgeDoc::SetSelCommand;
      psetsel->m_iPreviousSelStart = m_iSelStart;
      psetsel->m_iPreviousSelEnd = m_iSelEnd;
      m_editfile.MacroBegin();
      int i1 = m_iSelStart;
      int i2 = m_iSelEnd;
      Sort(i1, i2);
      m_editfile.Seek(i1, Ex1File::SeekBegin);
      m_editfile.Delete(i2 - i1);
      IndexRegisterDelete(i1, i2 - i1);
      m_iSelEnd = i1;
      m_editfile.Seek(m_iSelEnd, Ex1File::SeekBegin);
      m_iSelEnd++;
      m_iSelStart = m_iSelEnd;
      string str;
      char ch = pkey->m_nChar;
      int iChar = pkey->m_nChar;
      if(bShift)
      {
         iChar |= 0x80000000;
      }
      int i;
      if(m_imapAbnt.Lookup(iChar, i))
      {
         ch = i;
      }
      str = ch;
      m_editfile.Insert(&ch, 1);
      IndexRegisterInsert(m_iSelEnd, str);
      m_editfile.MacroEnd();
      psetsel->m_iSelStart = m_iSelStart;
      psetsel->m_iSelEnd = m_iSelEnd;
      pdoc->MacroBegin();
      pdoc->MacroRecord(psetsel);
      pdoc->MacroRecord(new devedgeDoc::FileCommand());
      pdoc->MacroEnd();
      OnUpdate();
   }
   if(pkey->m_nChar != VK_UP
   && pkey->m_nChar != VK_DOWN)
   {
      m_iColumn = SelToColumn(pview, m_iSelEnd);
   }
   m_dwLastCaret = ::GetTickCount();
   m_bCaretOn = true;
   pview->_001RedrawWindow();
}

void PlainTextBox::_001OnSysChar(devedgeView * pview, gen::signal_object * pobj)
{
   SCAST_PTR(igui::win::message::key, pkey, pobj)
   if(pkey->m_nChar == VK_DELETE)
   {
      int i1 = m_iSelStart;
      int i2 = m_iSelEnd;
      if(i1 != i2)
      {
         Sort(i1, i2);
         m_editfile.Seek(i1, Ex1File::SeekBegin);
         m_editfile.Delete(i2 - i1);
         m_iSelEnd = i1;
         m_iSelStart = m_iSelEnd;
      }
      else if(m_iSelEnd < m_editfile.GetLength())
      {
         m_editfile.Seek(m_iSelEnd, Ex1File::SeekBegin);
         m_editfile.Delete(1);
         m_iSelStart = m_iSelEnd;
      }
   }
}


void PlainTextBox::_001OnKeyboardFocusTimer(devedgeView * pview, int iTimer)
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

void PlainTextBox::OneLineUp(devedgeView * pview)
{
   pview->m_ptScroll.y -= m_iLineHeight;
   if(pview->m_ptScroll.y < 0)
      pview->m_ptScroll.y = 0;
   int iHeight = 0;
   char flag;
   m_iViewOffset = 0;
   int iLineSize;
   int i = 0;
   while(pview->m_ptScroll.y > iHeight && i < m_iaLineIndex.GetSize())
   {
      iLineSize = m_iaLineIndex[i];
      iHeight += m_iLineHeight;
      m_iViewOffset += iLineSize;
      i++;
   }

}

void PlainTextBox::IndexRegisterDelete(int iSel, int iCount)
{
   CreateLineIndex();
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
   while(i < m_iaLineIndex.GetSize())
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
      while(i < m_iaLineIndex.GetSize())
      {
         iLineSize = m_iaLineIndex[i];
         iLine++;
         iLineEnd = iLine;
         m_editfileLineIndex.Read(&flag, 1);
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
      m_editfileLineIndex.Seek(5 * (iLineStart + 1), Ex1File::SeekBegin);
      m_editfileLineIndex.Delete(5 * (iLineEnd - iLineStart));
   }
   m_editfileLineIndex.Seek(5 * iLineStart, Ex1File::SeekBegin);
   iLineSize = iLineStartRemain + iLineEndRemain;
   m_editfileLineIndex.Write(&iLineSize, 4);
   m_editfileLineIndex.Write(&flag, 1);
*/

}

void PlainTextBox::IndexRegisterInsert(int iSel, LPCTSTR lpcszWhat)
{
   CreateLineIndex();
}
void PlainTextBox::OnUpdate()
{
   m_bGetTextNeedUpdate = 1;
   CreateLineIndex();
   m_y = -1;
}

} // namespace devedge
