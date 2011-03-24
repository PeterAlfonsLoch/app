// XfplayerViewLine.cpp: implementation of the CXfplayerViewLine class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "VmpApp.h"
#include "XfplayerViewLine.h"
#include "XfplayerViewLines.h"

#include "BaseRectArray.h"
#include "Imaging.h"
#include <math.h>

#include "TransparentWndInterface.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


const int CXfplayerViewLine::AlignLeft = 1;
const int CXfplayerViewLine::AlignRight = 2;

CXfplayerViewLine::CXfplayerViewLine()
{
   m_nFont = 0;
   m_lpBitmapData = NULL;
   m_bAutoSizeX = false;
   m_bAutoSizeY = false;
   m_iAlign = AlignLeft;
   m_iLeft = 0;
   m_iTop = 0;
   m_iRight = 0;
   m_iBottom = 0;
   m_bVisible = false;
   m_pContainer = NULL;
   m_iAnimateType = AnimateNoAnimate;
   m_iTextEffect = EffectSimple;
   m_dAnimateProgress = 0;
   m_ptwi_ = NULL;
   m_iIndent = 0;
}
CXfplayerViewLine::CXfplayerViewLine(CXfplayerViewLines * pContainer)
{
   m_nFont = 0;
   m_lpBitmapData = NULL;
   m_bAutoSizeX = false;
   m_bAutoSizeY = false;
   m_iAlign = AlignLeft;
   m_iLeft = 0;
   m_iTop = 0;
   m_iRight = 0;
   m_iBottom = 0;
   m_bVisible = false;
   m_pContainer = pContainer;
   m_iAnimateType = AnimateNoAnimate;
   m_iTextEffect = EffectSimple;
   m_dAnimateProgress = 0;
   m_ptwi_ = NULL;
   
}

CXfplayerViewLine::~CXfplayerViewLine()
{
}


bool CXfplayerViewLine::PrepareLine(
    CDC * pdcForeground,
	LPCWSTR lpcsz,
	int flags,
	CTypedPtrArray <CPtrArray, CVmsGdiFont *> *pFonts,
	LPRECT pRect)
{
	int					iChars;
	int					iStr;
	int					iStrLen;
	CWStr wstr(lpcsz);
	ASSERT(pdcForeground != NULL);
	iStrLen = wstr.GetLength();
	iChars = -1;
   m_wstr.Empty();
   m_iIndent = 0;
	for(iStr = 0; iStr < iStrLen; iStr++)
	{
		AddChar(wstr[iStr], iChars);
	}
	CalcCharsPositions(pdcForeground,  pFonts, pRect);
	return true;
}

bool CXfplayerViewLine::PrepareLine(
   CDC * pdcForeground,
	LPCWSTR lpcsz,
	int flags,
	CVmsGdiFont *pFont,
	LPRECT pRect)
{
	int					iChars;
	int					iStr;
	int					iStrLen;
    m_iIndent = 0;
	CWStr wstr(lpcsz);
	ASSERT(pdcForeground != NULL);
	pFont->SetDC(pdcForeground);
   pFont->SelectFont();
	iStrLen = wstr.GetLength();
	iChars = -1;
   m_wstr.Empty();
	for(iStr = 0; iStr < iStrLen; iStr++)
	{
		AddChar(wstr[iStr], iChars, pFont);
	}
	CalcCharsPositions(pdcForeground, pFont, pRect);
   pFont->UnselectFont();
	pFont->ClearDC();
	return true;
}

void CXfplayerViewLine::AddChar(
	WCHAR wch,
	int &index)
{
	index++;
	if(m_iaPosition.GetSize() < index + 2)
	{
        m_iaPosition.SetSize(m_iaPosition.GetSize() + 10);
	}
    
	m_wstr += wch;
    ASSERT(m_wstr.GetLength() - 1 == index);
	

}

void CXfplayerViewLine::AddChar(
	WCHAR wch,
	int &index,
	CVmsGdiFont * pFont)
{
	index++;
	if(m_iaPosition.GetSize() < index + 2)
	{
        m_iaPosition.SetSize(m_iaPosition.GetSize() + 10);
	}
	m_wstr += wch;
   ASSERT(m_wstr.GetLength() - 1 == index);

}


void CXfplayerViewLine::GetPlacement(LPRECT lprect)
{
	lprect->left = m_iLeft;
	lprect->top  = m_iTop;
	lprect->right = m_iRight;
	lprect->bottom = m_iBottom;
}

bool CXfplayerViewLine::Render(
   CDC *					pdcForeground,
	CDC *					pdcBackground,
	bool					bDraw,
	LPRECT					lpRect,
	CBaseRectArray &		rectaModified,
	int	*					count,
	CVmsGdiFont *			pFont,
	bool					bRecalcLayout,
	COLORREF				crColor,
	CPen		&			pen)
{

   pdcForeground->SetBkMode(TRANSPARENT);
	
	CPoint iMargin;
	{
		LOGPEN logPen;
		pen.GetLogPen(&logPen);
		iMargin.x = logPen.lopnWidth.x / 2 + logPen.lopnWidth.x % 2;
		iMargin.y = logPen.lopnWidth.y / 2 + logPen.lopnWidth.y % 2;
	}
	//TRACE(_T("iPlyingTken: %05d\n"), iPlayingTokenIndex);
	TEXTMETRIC textMetric;
	pdcForeground->GetTextMetrics(&textMetric);
   if(!IsVisible())
   {
      CRect rect(m_rectInvalidate);
		pdcForeground->BitBlt(
		   rect.left, rect.top,
		   rect.Width(), rect.Height(),
		   pdcBackground,
		   rect.left, rect.top,
		   SRCCOPY);


		if(!rectaModified.IsThisNull())
		{
			CBaseRect baserect(rect);
         rectaModified.Add(baserect);
		}

      Validate(rect);

   	return true;
	}
	if(bRecalcLayout)
	{
		CalcCharsPositions(
            pdcForeground,
			pFont,
			lpRect);
		pdcForeground->SelectObject(pFont);
	}


//	CString strFinal(m_wstr, m_wstrLength);
    CWStr wstrFinal;
    wstrFinal = m_wstr;
	CRgn rgnOldClip;
	rgnOldClip.CreateRectRgn(0, 0, 0, 0);
	int iOldClip = ::GetClipRgn(pdcForeground->GetSafeHdc(), rgnOldClip);
	CPoint ptViewport = pdcForeground->GetViewportOrg();
	CRgn rgn;
	rgn.CreateRectRgn(
		m_iLeft - iMargin.x,
		m_iTop - iMargin.y,
		m_iRight + iMargin.x,
		m_iBottom + iMargin.y);
	rgn.OffsetRgn(ptViewport);
	if(pdcForeground->SelectClipRgn(&rgn) == ERROR)
	{
		TRACE0("Clipping ERROR!\n");
	}
	pdcForeground->SelectObject(&pen);
	pdcForeground->SetTextColor(crColor);
	CRect rectTextOut;
	GetPlacement(rectTextOut);
    pFont->TextOutEx(
        pdcForeground,
		rectTextOut,
		1.0,
		rectTextOut.Height(),
		wstrFinal,
		m_iaPosition.GetData(),
        m_iaPosition.GetSize(),
		0,
        MapToFontEffect(m_iTextEffect));
	if(!rectaModified.IsThisNull())
	{
         CBaseRect baserect;
         rgn.GetRgnBox(baserect);
        rectaModified.Add(baserect);
		//pModifiedRgn->CombineRgn(pModifiedRgn, &rgn, RGN_OR);
		
	}
	if(iOldClip == 0)
		pdcForeground->SelectClipRgn(NULL);
	else if(iOldClip == 1)
		pdcForeground->SelectClipRgn(&rgnOldClip);
	rgn.DeleteObject();
//    m_ptwi->TwiReleaseDC(pdcForeground);

	return true;

}

bool CXfplayerViewLine::Render(
    CDC *				pdc,
	CDC *				pdcBackground,
	bool				bDraw,
	LPRECT				lpRect,
	CBaseRectArray &	rectaModified,
	int			*		count,
	CTypedPtrArray <CPtrArray, CVmsGdiFont *> * pFonts,
	bool			bRecalcLayout,
	COLORREF		crColor,
	CPen		&	pen)
{
	CDC * pdcForeground = pdc;

	// Get clip region
	CRgn rgnClip;
	rgnClip.CreateRectRgn(0, 0, 0, 0);
	int iClip = ::GetClipRgn(pdc->GetSafeHdc(), rgnClip);

	// Get clip box in client coordinates
	CRect rectClip;
	rgnClip.GetRgnBox(rectClip);
	rectClip.OffsetRect(pdc->GetViewportOrg());

	// Get placement rectangle
	CRect rectPlacement;
	GetPlacement(rectPlacement);


	// if the placement is not in the clip region
	// do not draw anything;
	if(!rgnClip.RectInRegion(rectPlacement))
	{
		return true;
	}






   pdcForeground->SetBkMode(TRANSPARENT);
	
	CPoint iMargin;
	{
		LOGPEN logPen;
		pen.GetLogPen(&logPen);
		iMargin.x = logPen.lopnWidth.x / 2 + logPen.lopnWidth.x % 2;
		iMargin.y = logPen.lopnWidth.y / 2 + logPen.lopnWidth.y % 2;
	}
	//TRACE(_T("iPlyingTken: %05d\n"), iPlayingTokenIndex);
	CVmsGdiFont * pFont;
	if(m_nFont >= 0 &&
		m_nFont < pFonts->GetSize())
	{
		pFont = pFonts->GetAt(m_nFont);
	}
	
    CRgn rgn;
	TEXTMETRIC textMetric;
	pdcForeground->GetTextMetrics(&textMetric);
   if(!IsVisible())
   {
      CRect rect(m_rectInvalidate);
		pdcForeground->BitBlt(
		   rect.left, rect.top,
		   rect.Width(), rect.Height(),
		   pdcBackground,
		   rect.left, rect.top,
		   SRCCOPY);


		if(!rectaModified.IsThisNull())
		{
         CBaseRect baserect(rect);
         rectaModified.Add(baserect);
		}

      Validate(rect);

   	return true;
	}
	if(bRecalcLayout)
	{
		CalcCharsPositions(
            pdcForeground,
			pFonts,
			lpRect);
		if(m_nFont >= 0 &&
			m_nFont < pFonts->GetSize())
		{
			pdcForeground->SelectObject(pFonts->GetAt(m_nFont));
		}
	}
    
    CRgn rgnOld;
    rgnOld.CreateRectRgn(0, 0, 0, 0);
    GetClipRgn(pdcForeground->GetSafeHdc(), rgnOld);
    CRect rectClipOld;
    rgnOld.GetRgnBox(rectClipOld);

    CPoint ptViewport = pdcForeground->GetViewportOrg();

    switch(m_iAnimateType)
    {
    case AnimateNoAnimate:
        {
        //	CString strFinal(m_wstr, m_wstrLength);
            CWStr wstrFinal;
            wstrFinal = m_wstr;
	        CRect rectClip(
		        m_iLeft - iMargin.x,
		        m_iTop - iMargin.y,
		        m_iRight + iMargin.x,
		        m_iBottom + iMargin.y);
            rectClip.OffsetRect(ptViewport);
	        rgn.CreateRectRgnIndirect(
		        rectClip);
	        if(pdcForeground->SelectClipRgn(&rgn) == ERROR)
	        {
		        TRACE0("Clipping ERROR!\n");
	        }
	        pdcForeground->SelectObject(&pen);
	        pdcForeground->SetTextColor(crColor);
			CRect rectTextOut;
			GetPlacement(rectTextOut);
	        pFont->TextOutEx(
                pdcForeground,
		        rectTextOut,
				1.0,
				rectTextOut.Height(),
		        wstrFinal,
		        m_iaPosition.GetData(),
                m_iaPosition.GetSize(),
		        0,
                MapToFontEffect(m_iTextEffect));	
	        if(!rectaModified.IsThisNull())
	        {
              CBaseRect baserect;
              rgn.GetRgnBox(baserect);

                rectaModified.Add(baserect);
		        //pModifiedRgn->CombineRgn(pModifiedRgn, &rgn, RGN_OR);
		        
	        }
	        pdcForeground->SelectClipRgn(NULL);
	        rgn.DeleteObject();
        }
        break;
    case AnimateRHL:
        {//	CString strFinal(m_wstr, m_wstrLength);
            
            int iLeft = m_iaPosition.ElementAt(0);
            int iLeftDiff  = 0;
            int iLastLeftDiff = 0;
            for(int i = 0; i < m_iaPosition.GetSize(); i++)
            {
                iLastLeftDiff = iLeftDiff;
                iLeftDiff = m_iaPosition.ElementAt(i) - iLeft;
                if((int) m_dAnimateProgress <= iLeftDiff)
                {
                    i--;
                    break;
                }
            }
            
            CWStr wstrFinal(m_wstr);
            CWStr wstrLeft = wstrFinal.Right(wstrFinal.GetLength() - i);
            int iLeftOffset;
            iLeftOffset = iLastLeftDiff - (int) m_dAnimateProgress;
            CRect rectClip(
                m_iLeft - iMargin.x,
		        m_iTop - iMargin.y,
		        m_iRight + iMargin.x,
		        m_iBottom + iMargin.y);
            rectClip.OffsetRect(ptViewport);
	        rgn.CreateRectRgnIndirect(
		        rectClip);
                        
	        if(pdcForeground->SelectClipRgn(&rgn) == ERROR)
	        {
		        TRACE0("Clipping ERROR!\n");
	        }
	        pdcForeground->SelectObject(&pen);
	        pdcForeground->SetTextColor(crColor);
			CRect rectTextOut;
			GetPlacement(rectTextOut);
			rectTextOut.left += iLeftOffset;
	        pFont->TextOutEx(
                pdcForeground,
		        rectTextOut,
				1.0,
				rectTextOut.Height(),
		        wstrLeft,
		        m_iaPosition.GetData(),
                m_iaPosition.GetSize(),
		        0,
                MapToFontEffect(m_iTextEffect));	
            int iMaxCounter = max((int) m_iaPosition.ElementAt(m_wstr.GetLength()) - m_iaPosition.ElementAt(0) + 100, m_iRight - m_iLeft);
            int iRight = iMaxCounter - (int) m_dAnimateProgress;
            if(iRight < m_iRight)
            {
                int iRightEnd;
                for(int i = 0; i < m_iaPosition.GetSize(); i++)
                {
                    iRightEnd = iRight + m_iaPosition.ElementAt(i) - iLeft;
                    if(iRightEnd >= m_iRight)
                    {
                        break;
                    }
                }
                CWStr wstrRight = wstrFinal.Left(i);
				rectTextOut.left = iRight;
    	        pFont->TextOutEx(
                    pdcForeground,
		            rectTextOut,
					1.0,
					rectTextOut.Height(),
		            wstrRight,
		            m_iaPosition.GetData(),
                    m_iaPosition.GetSize(),
		            0,
                    MapToFontEffect(m_iTextEffect));	
                }
            
	        if(!rectaModified.IsThisNull())
	        {
				CBaseRect baserect;
				rgn.GetRgnBox(baserect);
                rectaModified.Add(baserect);
		        
	        }
	        rgn.DeleteObject();
        }
        break;
    default:
        ASSERT(FALSE);
    }
//    m_ptwi->TwiReleaseDC(pdcForeground);
    if(rectClipOld.IsRectNull())
    {
        pdcForeground->SelectClipRgn(NULL);
    }
    else
    {
        pdcForeground->SelectClipRgn(&rgnOld);
    }


	return true;

}



void CXfplayerViewLine::CalcCharsPositions(
CDC * pdcForeground,
	CTypedPtrArray <CPtrArray, CVmsGdiFont *> * pFonts,
	LPCRECT lpcrect)
{
	//CVmsGdiFont * pFont;
//    CDC * pdcForeground = m_ptwi->TwiGetDC();
	if(m_wstr.GetLength() <= 0)
		return;
	if(pFonts->GetSize() > 0)
	{
		int i, nFont, iFontFound, iMaxExtent, iLeft;
		CSize size;
		CRect clientRect;
		nFont = 0;
		iFontFound = -1;
		for(nFont = 0; nFont < pFonts->GetSize(); nFont++)
		{
			pdcForeground->SelectObject(pFonts->GetAt(nFont)->GetFont());
			GetTextExtentPoint32W(
				pdcForeground->GetSafeHdc(),
				m_wstr,
				m_wstr.GetLength(),
				&size);
			if((m_iAlign & AlignLeft) > 0)
			{
				if(size.cx + m_iLeft <= lpcrect->right)
				{
					iFontFound = nFont;
					break;
				}
			}
			else if((m_iAlign & AlignRight) > 0)
			{
				if(m_iRight - size.cx >= 0)
				{
					iFontFound = nFont;
					break;
				}
			}
		}
		if(iFontFound < 0)
		{
			m_nFont = pFonts->GetSize() - 1;
		}
		else
		{
			m_nFont = iFontFound;
		}
		pdcForeground->SelectObject(pFonts->GetAt(m_nFont)->GetFont());
		if(m_iAlign == AlignLeft)
		{
			m_iaPosition[0] = m_iLeft + m_iIndent;
			for(i = 1; i <= m_wstr.GetLength(); i++)
			{
				GetTextExtentPoint32W(
					pdcForeground->GetSafeHdc(),
					m_wstr,
					i,
					&size);
				m_iaPosition[i] = size.cx + m_iLeft  + m_iIndent;
			}
			if(m_bAutoSizeX)
			{
				m_iRight = m_iLeft  + m_iIndent + size.cx;
            }
			if(m_bAutoSizeY)
			{
				m_iBottom = m_iTop + size.cy;
			}
		}
		else if(m_iAlign == AlignRight)
		{
			GetTextExtentPoint32W(
				pdcForeground->GetSafeHdc(),
				m_wstr,
				m_wstr.GetLength(),
				&size);
			iMaxExtent = size.cx;
			iLeft = m_iRight - iMaxExtent;
			m_iaPosition[0] = iLeft;
			for(i = 1; i <= m_wstr.GetLength(); i++)
			{
				GetTextExtentPoint32W(
					pdcForeground->GetSafeHdc(),
					m_wstr,
					i,
					&size);
				m_iaPosition[i] = size.cx + iLeft;
			}
			if(m_bAutoSizeX)
			{
				m_iLeft = m_iRight - size.cx;
            }
            if(m_bAutoSizeY)
            {
				m_iBottom = m_iTop + size.cy;
			}
		}
	
	}

	else
	{
		int i; //, width;
		CSize size;
			m_iaPosition[0] = m_iLeft;
			for(i = 1; i <= m_wstr.GetLength(); i++)
			{
				GetTextExtentPoint32W(
					pdcForeground->GetSafeHdc(),
					m_wstr,
					i ,
					&size);
				m_iaPosition[i] = m_iLeft + size.cx;
			}
		if(m_bAutoSizeX)
		{
			m_iRight = m_iLeft + size.cx;
        }
		if(m_bAutoSizeY)
		{
			m_iBottom = m_iTop + size.cy;
		}
	}
//    m_ptwi->TwiReleaseDC(pdcForeground);

}

void CXfplayerViewLine::CalcCharsPositions(
	CDC * pdcForeground,
    CVmsGdiFont * pFont,
	LPCRECT lpcrect)
{
//    CDC * pdcForeground = m_ptwi->TwiGetDC();
	
	if(m_wstr.GetLength() <= 0)
		return;
    CFont * pfontOriginal = pdcForeground->GetCurrentFont();
	pdcForeground->SelectObject(pFont->GetFont());
	int i, iLeft, iRight, iMaxExtent;
	CSize size;
	if(m_iAlign == AlignLeft)
	{
		m_iaPosition[0] = m_iLeft + m_iIndent;
		iRight = 0;
		for(i = 1; i <= m_wstr.GetLength(); i++)
		{
			GetTextExtentPoint32W(
				pdcForeground->GetSafeHdc(),
				m_wstr,
				i,
				&size);
			m_iaPosition[i] = iRight = size.cx + m_iLeft + m_iIndent;
		}
		if(m_bAutoSizeX)
		{
			m_iRight = iRight;
        }
		if(m_bAutoSizeY)
		{
			m_iBottom = m_iTop + size.cy;
		}
	}
	else if(m_iAlign == AlignRight)
	{
		GetTextExtentPoint32W(
			pdcForeground->GetSafeHdc(),
			m_wstr,
			m_wstr.GetLength(),
			&size);
		iMaxExtent = size.cx;
		iLeft = m_iRight - iMaxExtent;
		m_iaPosition[0] = iLeft;
		for(i = 1; i <= m_wstr.GetLength(); i++)
		{
			GetTextExtentPoint32W(
				pdcForeground->GetSafeHdc(),
				m_wstr,
				i,
				&size);
			m_iaPosition[i] = size.cx + iLeft;
		}
		if(m_bAutoSizeX)
		{
			m_iLeft = iLeft;
        }
		if(m_bAutoSizeY)
		{
			m_iBottom = m_iTop + size.cy;
		}
	}
    pdcForeground->SelectObject(pfontOriginal);
//    m_ptwi->TwiReleaseDC(pdcForeground);
}

void CXfplayerViewLine::SetAutoSize(bool bAutoSize)
{
	m_bAutoSizeX = bAutoSize;
    m_bAutoSizeY = bAutoSize;
}

void CXfplayerViewLine::SetAlign(int iAlign)
{
	m_iAlign = iAlign;
}

void CXfplayerViewLine::SetRect(LPRECT lpRect)
{
    m_iLeft     = lpRect->left;
    m_iTop      = lpRect->top;
    m_iRight    = lpRect->right;
    m_iBottom   = lpRect->bottom;
}

void CXfplayerViewLine::GetRect(LPRECT lpRect)
{
    lpRect->left    = m_iLeft;
    lpRect->top     = m_iTop;
    lpRect->right   = m_iRight;
    lpRect->bottom  = m_iBottom;
}

CXfplayerViewLine::operator =(CXfplayerViewLine & src)
{
    m_bAutoSizeX = src.m_bAutoSizeX;
    m_bAutoSizeY = src.m_bAutoSizeY;
    m_wstr = src.m_wstr;
    m_iaPosition.Copy(src.m_iaPosition);
    m_iAlign = src.m_iAlign;
    m_iBottom = src.m_iBottom;
    m_iLeft = src.m_iLeft;
    m_iRight = src.m_iRight;
    m_iTop = src.m_iTop;
    m_lpBitmapData  = src.m_lpBitmapData;
    m_nFont = src.m_nFont;
    m_iAnimateType = src.m_iAnimateType;
    m_iTextEffect = src.m_iTextEffect ;
    m_dAnimateProgress = src.m_dAnimateProgress;
    m_dAnimateProgressIncrement = src.m_dAnimateProgressIncrement;
    m_ptwi_ = src.m_ptwi_;
}

void CXfplayerViewLine::Show(bool bShow)
{
    if(bShow && !m_bVisible)
    {
        m_bVisible = true;
        Invalidate();
        if(m_pContainer != NULL)
        {
            m_pContainer->OnChildSetVisible(this, m_bVisible);
        }
        
    }
    else if(!bShow && m_bVisible)
    {
        m_bVisible = false;
        Invalidate();
        if(m_pContainer != NULL)
        {
            m_pContainer->OnChildSetVisible(this, m_bVisible);
        }
    }
}


void CXfplayerViewLine::OnTimerAnimate(
    CDC *					pdcForeground,
	CDC *					pdcBackground,
    CBaseRectArray &		rectaModified)
{
    if(IsVisible())
    {
        switch(m_iAnimateType)
        {
        case AnimateNoAnimate:
            break;
        case AnimateRHL:
            {
                m_dAnimateProgress+= m_dAnimateProgressIncrement;
                if(m_iaPosition.GetSize() > 0)
                {
                    if((int)m_dAnimateProgress > max(m_iaPosition.ElementAt(m_wstr.GetLength()) - m_iaPosition.ElementAt(0) + 100, m_iRight - m_iLeft))
                        m_dAnimateProgress = 0.0;
                    CRect rect;
                    GetRect(rect);
                    Invalidate();
                    Render(
                        pdcForeground,
						      pdcBackground,
						      true,
                        rect, rectaModified, 
                        NULL, 
                        GetFonts(), false, m_crForeground, *m_lpPenEmboss);
                }
            }
            break;
        default:
            ASSERT(FALSE);
        }
    }
}

void CXfplayerViewLine::SetAnimateType(int iAnimateType)
{
    m_iAnimateType = iAnimateType;
    m_dAnimateProgress = 0.0;

}

void CXfplayerViewLine::SetTextEffect(int iTextEffect)
{
    m_iTextEffect = iTextEffect;
}

//void CXfplayerViewLine::SetForegroundDC(CDC *pDC)
//{
  //  pdcForeground = pDC;
//}
void CXfplayerViewLine::SetTwi(CTransparentWndInterface *ptwi)
{
    m_ptwi_ = ptwi;
}


void CXfplayerViewLine::SetEmbossPen(CPen *lpPen)
{
    m_lpPenEmboss = lpPen;

}

void CXfplayerViewLine::SetForegroundColor(COLORREF cr)
{
    m_crForeground = cr;
}

CTypedPtrArray <CPtrArray, CVmsGdiFont *> * CXfplayerViewLine::GetFonts()
{
    return &m_fonts;
}

int CXfplayerViewLine::MapToFontEffect(int iLineEffect)
{
    switch(iLineEffect)
    {
    case EffectSimple:
        return CVmsGdiFont::EffectSimple;
    case EffectEmbossed:
        return CVmsGdiFont::EffectEmbossed;
    }
    ASSERT(FALSE);
    return -1;
}

void CXfplayerViewLine::SetAnimateIncrement(double dIncrement)
{
    m_dAnimateProgressIncrement = dIncrement;
}

//void CXfplayerViewLine::SetRedrawMode(int iMode)
//{
  //  m_iRedrawMode = iMode;
//}

//void CXfplayerViewLine::SetRenderWindow(CWnd *pWnd)
//{
  //  m_pRenderWnd = pWnd;
//}

void CXfplayerViewLine::SetRenderCriticalSection(CCriticalSection *pcs)
{
//    m_pcsRender =   pcs;
}

int CXfplayerViewLine::SetLyricPens(CPen * ppenLeft, CPen * ppenRight)
{
    m_ppenLyricLeft = ppenLeft;
    m_ppenLyricRight = ppenRight;
    return true;
}

int CXfplayerViewLine::SetLyricColors(COLORREF crLeft, COLORREF crRight)
{
    m_crLyricLeft = crLeft;
    m_crLyricRight = crRight;
    return true;

}

void CXfplayerViewLine::SetPlacement(LPCRECT lpcrect)
{
	m_iLeft = lpcrect->left;
	m_iTop = lpcrect->top;
	m_iRight = lpcrect->right;
	m_iBottom = lpcrect->bottom;
}

int CXfplayerViewLine::GetVmsFontCount()
{
	return m_fonts.GetSize();
}

void CXfplayerViewLine::AddVmsFont(CVmsGdiFont * pfont)
{
	m_fonts.Add(pfont);
}

void CXfplayerViewLine::Invalidate(LPCRECT lpcrect)
{
   CRect rectPlacement;
   GetPlacement(rectPlacement);
   CRect rect;
   if(lpcrect == NULL)
   {
      rect = rectPlacement;
   }
   else
   {
      rect = *lpcrect;
   }
   m_rectInvalidate.UnionRect(m_rectInvalidate, rect);
   m_rectInvalidate.IntersectRect(m_rectInvalidate, rectPlacement);

}

void CXfplayerViewLine::Validate(LPCRECT lpcrect)
{
   CRect rectPlacement;
   GetPlacement(rectPlacement);
   CRect rect;
   if(lpcrect == NULL)
   {
      rect = rectPlacement;
   }
   else
   {
      rect = *lpcrect;
   }
   m_rectInvalidate -= rect;
   m_rectInvalidate.IntersectRect(m_rectInvalidate, rectPlacement);

}

bool CXfplayerViewLine::IsVisible()
{
   return m_bVisible;
}
