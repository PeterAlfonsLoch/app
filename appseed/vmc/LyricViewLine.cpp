// LyricViewLine.cpp: implementation of the CLyricViewLine class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "VMSApp.h"
#include "LyricViewLine.h"

#include <math.h>


#include "LyricViewLines.h"
#include "LyricViewLineTemplate.h"

#include "LyricEventsV2.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

const int CLyricViewLine::AlignLeft = 1;
const int CLyricViewLine::AlignRight = 2;

CLyricViewLine::CLyricViewLine()
: m_rectPrevious(0, 0, 0, 0)
{
//	m_chars = NULL;
	m_iStatus = StatusEmpty;
	m_iStartTokenIndex = 0;
	m_iTokensCount = 0;
//	m_charsLength = 0;
	m_bFirstLine = FALSE;
//	m_dwEmptyTime = 0;
	m_dwNewTime = 0;
	m_lpBitmapData = NULL;
	m_bAutoSizeX = false;
	m_bAutoSizeY = false;
	m_iAlign = AlignLeft;
//	rectPlacement.left = 0;
//	rectPlacement.top = 0;
//	rectPlacement.right = 0;
//	rectPlacement.bottom = 0;
    m_iRelativeLineIndex = -1;
    m_bVisible = false;
	m_pContainer = NULL;
    m_iAnimateType = AnimateNoAnimate;
    m_iTextEffect = EffectSimple;
    m_dAnimateProgress = 0;
    m_lpForegroundDC = NULL;
    m_lpBackgroundDC = NULL;
//    m_pRenderWnd = NULL;
    m_iIndent = 0;
//    m_rgnModified.CreateRectRgn(0, 0, 0, 0);
//    m_iRedrawMode = RedrawDoRedraw;
}
CLyricViewLine::CLyricViewLine(CLyricViewLines * pContainer)
: m_rectPrevious(0, 0, 0, 0)
{
//	m_chars = NULL;
	m_iStatus = StatusEmpty;
	m_iStartTokenIndex = 0;
	m_iTokensCount = 0;
//	m_charsLength = 0;
	m_bFirstLine = FALSE;
//	m_dwEmptyTime = 0;
	m_dwNewTime = 0;
	m_lpBitmapData = NULL;
	m_bAutoSizeX = false;
    m_bAutoSizeY = false;
	m_iAlign = AlignLeft;
//	rectPlacement.left = 0;
//	rectPlacement.top = 0;
//	rectPlacement.right = 0;
//	rectPlacement.bottom = 0;
    m_iRelativeLineIndex = -1;
    m_bVisible = false;
    m_pContainer = pContainer;
    m_iAnimateType = AnimateNoAnimate;
    m_iTextEffect = EffectSimple;
    m_dAnimateProgress = 0;
    m_lpForegroundDC = NULL;
    m_lpBackgroundDC = NULL;

}

CLyricViewLine::~CLyricViewLine()
{
//	if(m_chars)
//		free(m_chars);

}

XFPLYR_LINE_RESULT CLyricViewLine::PrepareLyricLine(
	CStrArray *pTokens,
	int tokenIndex,
	int *nextTokenIndex,
	int flags,
	CTypedPtrArray <CPtrArray, CXfplayerFont *> *pFonts,
	LPRECT pRect,
	CLyricEventsV2 * pEvents)
{
	int					iTokens;
	int					iChars;
	int					iCharsFirst;
	m_iIndent;
//	char				ch;
	TCHAR				ch;
	CString				str;
	int					iStr;
	int					iStrLen;
	int					xPosition;
	BOOL			    forceInsertion = FALSE;
	XFPLYR_LINE_RESULT	result;
	
	ASSERT(tokenIndex >= 0);
	ASSERT(pTokens != NULL);
	ASSERT(m_lpForegroundDC != NULL);
//	ASSERT(m_iStatus != XFPLYR_LINE_STATUS_NEW);
//	ASSERT(m_iStatus != XFPLYR_LINE_STATUS_PLAYING);


	if(tokenIndex >= pTokens->GetSize())
	{
		//m_iStatus = XFPLYR_LINE_STATUS_NEW;
		return XFPLYR_LINE_SUCCESS_NO_LINE;
	}

	iChars = -1;
	iCharsFirst = 0;
	iStr = 0;
	iTokens = -1;
	xPosition = 0;
	m_iStartTokenIndex = tokenIndex;
    m_iIndent = 0;
    m_chars.Empty();
	//m_iStatus = XFPLYR_LINE_STATUS_NEW; // default
	//rectPlacement.left = 0;
	while(TRUE)
	{
		str = pTokens->ElementAt(tokenIndex);
		iStrLen = str.GetLength();
		if(iStr >= iStrLen)
		{
			
			tokenIndex++;
			AddToken(iCharsFirst, iChars - iCharsFirst + 1, iTokens);
			if(tokenIndex >= pTokens->GetSize())
			{
				if(iChars >= 0)
				{
					result = XFPLYR_LINE_SUCCESS_LAST_LINE;
				}
				else
				{
					result = XFPLYR_LINE_SUCCESS_NO_LINE;
				}
				break;
			}
			if(iChars >= iCharsFirst)
				iCharsFirst = iChars + 1;
			iStr = 0;
			continue;
		}
		ch = str.operator[](iStr);
		//TRACE(_T("The character: %c\n"), ch);
		if(iTokens == -1)
		{
			if(ch == '\\')
			{
				forceInsertion = TRUE;
			}
			else if(ch == '^')
			{
				AddChar(' ', iChars);
			}
			else if(ch == '/')
			{
				// This is the first token of the
				// line (iTokens == -1).
				// If the first token has other
				// characters (iStrLen != 1), then
				// the line must be wiped.
				// Otherwise, this token indicates that
				// it is the first token of this new line.
				if(iStrLen != 1)
				{
					AddToken(iCharsFirst, iChars - iCharsFirst + 1, iTokens);
					result = XFPLYR_LINE_SUCCESS;
					break;
				}
			}
			else if(ch == '%')
			{
				if(flags & XFPLYR_BREAK_LINE_FEED)
				{
				    AddToken(iCharsFirst, iChars - iCharsFirst + 1, iTokens);
					result = XFPLYR_LINE_SUCCESS;
					break;
				}
			}
			else if(ch == '<')
			{
				if(!m_bFirstLine)
				{
					m_iStatus = StatusEmpty;
					result = XFPLYR_LINE_PAGE_BREAK;
					break;
				}
			}
			else if(ch == '>')
			{
				if(iStr == 0)
					m_iIndent = m_lpForegroundDC->GetDeviceCaps(LOGPIXELSX) / 2;
			}
			else
			{
				AddChar(ch, iChars);
			}
		}
		else
		{
			if(forceInsertion)
			{
				forceInsertion = FALSE;
				AddChar(ch, iChars);
			}
			else if(ch == '\\')
			{
				forceInsertion = TRUE;
			}
			else if(ch == '^')
			{
				AddChar(' ', iChars);
			}
			else if(ch == '/')
			{
//				if(iStrLen != 1)
//				{
					AddToken(iCharsFirst, iChars - iCharsFirst + 1, iTokens);
//				}
				result = XFPLYR_LINE_SUCCESS;
				break;
			}
			else if(ch == '%')
			{
				if(flags & XFPLYR_BREAK_LINE_FEED)
				{
					AddToken(iCharsFirst, iChars - iCharsFirst + 1, iTokens);
					result = XFPLYR_LINE_SUCCESS;
					break;
				}
			}
			else if(ch == '<')
			{
				if(iStr == 0)
				{
					result = XFPLYR_LINE_SUCCESS;
					break;	
				}
			}
			else if(ch == '>')
			{
				//m_xPos = GetDeviceCaps(hDC, LOGPIXELSX) / 2;
			}
			else
			{
				AddChar(ch, iChars);
			}
		}
		iStr++;
	}

	m_iTokensCount= iTokens + 1;
	//m_charsLength = iChars + 1;
	*nextTokenIndex = m_iStartTokenIndex + m_iTokensCount;
	CalcCharsPositions(pFonts, pRect);
	CalcNotesPositions(pEvents);
	ASSERT(*nextTokenIndex >= 0);
	m_iMiddle = -1;
	SetStatus(StatusPrepared);
    m_iMiddle = 0x80000000;
    m_iLastMiddle = 0x80000000;
//	CString strTest(m_chars, m_charsLength);
//	TRACE(_T("PrepareLyricLine 3000: %s\n"), strTest);
	return result;

}

XFPLYR_LINE_RESULT CLyricViewLine::PrepareLine(
	LPCTSTR lpcsz,
	int flags,
	CTypedPtrArray <CPtrArray, CXfplayerFont *> *pFonts,
	LPRECT pRect)
{
	int					iChars;
	int					iStr;
	int					iStrLen;
	CString str(lpcsz);
	ASSERT(m_lpForegroundDC != NULL);
	iStrLen = str.GetLength();
	iChars = -1;
    m_chars.Empty();
    m_iIndent = 0;
	for(iStr = 0; iStr < iStrLen; iStr++)
	{
		AddChar(str[iStr], iChars);
	}
//	m_charsLength = iStrLen;
	CalcCharsPositions( pFonts, pRect);
	
	m_iLastMiddle = 0x80000000;
	return StatusNew;

}

XFPLYR_LINE_RESULT CLyricViewLine::PrepareLine(
	LPCTSTR lpcsz,
	int flags,
	CXfplayerFont *pFont,
	LPRECT pRect)
{
	int					iChars;
	int					iStr;
	int					iStrLen;
    m_iIndent = 0;
	CString str(lpcsz);
	ASSERT(m_lpForegroundDC != NULL);
	pFont->SetDC(m_lpForegroundDC);
    pFont->SelectFont();
//	pDC->SelectObject(pFont->GetFont());
	iStrLen = str.GetLength();
	iChars = -1;
    m_chars.Empty();
	for(iStr = 0; iStr < iStrLen; iStr++)
	{
		AddChar(str[iStr], iChars, pFont);
	}
//	m_charsLength = iStrLen;
	CalcCharsPositions(pFont, pRect);
    pFont->UnselectFont();
	pFont->ClearDC();
	m_iLastMiddle = 0x80000000;
	return StatusNew;

}

//void CLyricViewLine::InsertChar(HDC hDC, char ch, int *xOffset, int &index)
void CLyricViewLine::AddChar(
	TCHAR ch,
	int &index)
{
	index++;
	if(m_iaCharsPositions.GetSize() < index + 2)
	{
        m_iaCharsPositions.SetSize(m_iaCharsPositions.GetSize() + 10);
        m_dwaCharsStates.SetSize(m_iaCharsPositions.GetSize());
//        CString str(_T(' '), m_iaCharsPositions.GetSize() - m_chars.GetLength());
  //      m_chars += str;
//			m_iaCharsPositions.SetSize(m_iaCharsPositions.GetSize() + 10);
//			if(m_chars)
//			{
//				m_chars = (LPTSTR) realloc(m_chars, (m_iaCharsPositions.GetSize() - 1) * sizeof(TCHAR));
//				m_lpbCharsStates = (LPBYTE) realloc(m_lpbCharsStates, (m_iaCharsPositions.GetSize() - 1));
//			}
//			else
//			{
//				m_chars = (LPTSTR) malloc((m_iaCharsPositions.GetSize() - 1) * sizeof(TCHAR));
//				m_lpbCharsStates = (LPBYTE) malloc((m_iaCharsPositions.GetSize() - 1));
//			}
	}
    
	m_chars += ch;
    ASSERT(m_chars.GetLength() - 1 == index);
	m_dwaCharsStates[index] = CharStateNew;
//	xOffset = 0;
	

}

void CLyricViewLine::AddChar(
	TCHAR ch,
	int &index,
	CXfplayerFont * pFont)
{
	index++;
	if(m_iaCharsPositions.GetSize() < index + 2)
	{
        m_iaCharsPositions.SetSize(m_iaCharsPositions.GetSize() + 10);
        m_dwaCharsStates.SetSize(m_iaCharsPositions.GetSize());
//        CString str(_T(' '), m_iaCharsPositions.GetSize() - m_chars.GetLength());
//        m_chars += str;
//			m_iaCharsPositions.SetSize(m_iaCharsPositions.GetSize() + 10);
//			if(m_chars)
//			{
//				m_chars = (LPTSTR) realloc(m_chars, (m_iaCharsPositions.GetSize() - 1) * sizeof(TCHAR));
//				m_lpbCharsStates = (LPBYTE) realloc(m_lpbCharsStates, (m_iaCharsPositions.GetSize() - 1));
//			}
//			else
//			{
//				m_chars = (LPTSTR) malloc((m_iaCharsPositions.GetSize() - 1) * sizeof(TCHAR));
//				m_lpbCharsStates = (LPBYTE) malloc((m_iaCharsPositions.GetSize() - 1));
//			}
	}
	m_chars += ch;
    ASSERT(m_chars.GetLength() - 1 == index);
	m_dwaCharsStates[index] = CharStateNew;
//	xOffset = 0;
	pFont->AddGlyph(ch);

}

void CLyricViewLine::AddToken(
	int firstCharIndex,
	int charsLength,
	int &index)
{
	index++;
	while(m_iaTokensCharsLengths.GetSize() < index + 1)
	{
		int iNewSize = m_iaTokensCharsLengths.GetSize() + 10;
		m_iaTokensCharsLengths.SetSize(iNewSize);
		m_iaTokensFirstCharIndexes.SetSize(iNewSize);
//		m_tokensNotesLengths.SetSize(iNewSize);
//		m_tokensFirstNoteIndexes.SetSize(iNewSize);
	}
	m_iaTokensFirstCharIndexes[index] = firstCharIndex;
	m_iaTokensCharsLengths[index] = charsLength;

}

XFPLYR_LINE_RESULT CLyricViewLine::RenderLyricLine(
	LPRECT		lpRect,
	CTypedPtrArray <CObArray, CBaseRgn *> * prgnaModified,
	int			iPlayingTokenIndex,
	int			iPlayingNoteIndex,
	int			iMode,
	int			*count,
	CTypedPtrArray <CPtrArray, CXfplayerFont *> * pFonts,
//	BOOL		bRecalcLayout,
	CLyricEventsV2 * pEvents)
    //bool bRedraw)
{
	//return XFPLYR_LINE_SUCCESS;
//    CSingleLock(&m_csRender, TRUE);
	SetPlayingStatus(iPlayingTokenIndex);
	int iTokensStart;
	int iTokensEnd;
	int	iTokens;
	int iLeft, iTop, iRight, iBottom;
	//int iMiddle_, iLastMiddle;
	int i;
    //CBaseRgn rgnModified;
    
    CRect rectPlacement;
//    m_ptemplate->GetPlacement(rectPlacement);
    GetPlacement(rectPlacement);

    CSize sizeMargin;
    m_ptemplate->GetMargin(&sizeMargin);

    CPen * ppenLeft, * ppenRight;
    m_ptemplate->GetPens(&ppenLeft, &ppenRight);

    COLORREF crLeft, crRight;
    m_ptemplate->GetColors(crLeft, crRight);

	m_lpForegroundDC->SetBkMode(TRANSPARENT);
	
	CXfplayerFont * pFont = NULL;
	if(m_nFont >= 0 &&
		m_nFont < pFonts->GetSize())
	{
		pFont = pFonts->GetAt(m_nFont);
	}
	if(count != NULL)
	{
		(*count)++;
	}
	//TRACE(_T("iPlyingTken: %05d\n"), iPlayingTokenIndex);
	TEXTMETRIC textMetric;
	if(pFont != NULL)
	{
		pFont->SetDC(m_lpForegroundDC);
		pFont->SelectFont();
	}
	m_lpForegroundDC->GetTextMetrics(&textMetric);
	if(pFont != NULL)
	{
		pFont->UnselectFont();
		pFont->ClearDC();
	}
	if(iMode == XFPLYR_LINE_RENDER_CLEAR_FULL ||
	   iMode == XFPLYR_LINE_RENDER_CLEAR)
	{
		iTokensStart = 0;
		iTokensEnd = m_iTokensCount - 1;
		m_iMiddle = 0x80000000;
        m_iLastMiddle = m_iMiddle;

        m_lpForegroundDC->BitBlt(
		   0, rectPlacement.top,
		   lpRect->right, textMetric.tmHeight + textMetric.tmInternalLeading,
		   m_lpBackgroundDC,
		   0, rectPlacement.top,
		   SRCCOPY);
//			rgnModified.CombineRgn(&rgnModified, &rgn, RGN_OR);
//			rgn.Detach();

        if(prgnaModified)
        {
			CBaseRgn * pbasergn = new CBaseRgn();
		
			pbasergn->CreateRectRgn(
				0,
				rectPlacement.top,
				lpRect->right,
				rectPlacement.top + textMetric.tmHeight + textMetric.tmInternalLeading);

			prgnaModified->Add(pbasergn);
        }
			//rgn.DeleteObject();
//            if(bRedraw)
  //          {
    //            m_pRenderWnd->RedrawWindow(NULL, &rgnModified, RDW_INVALIDATE | RDW_UPDATENOW);
      //          rgnModified.SetRectRgn(0, 0, 0, 0);
        //    }
		if(iMode == XFPLYR_LINE_RENDER_CLEAR)
        {
                    //if(m_iRedrawMode == RedrawDoRedraw)
//    if(prgnaModified)
  //          {
    //            prgnaModified->Add(rgnMod);
//                pModifiedRgn->CombineRgn(pModifiedRgn, &rgnModified, RGN_OR);
      //      }
            m_ptemplate->m_bNeedFullUpdate = true;
			return XFPLYR_LINE_SUCCESS;
        }
        else
        {
            m_ptemplate->m_bNeedFullUpdate = false;
        }
	}
	else if(iMode == XFPLYR_LINE_RENDER_UPDATE)
	{
        if(m_ptemplate->m_bNeedFullUpdate)
        {
            m_ptemplate->m_bNeedFullUpdate = false;
            SetStatus(StatusNew);
        }
		iTokens = iPlayingTokenIndex - m_iStartTokenIndex;
		if(iTokens < 0)
		{
			iTokens = 0;
		}
		if(iTokens >= m_iTokensCount)
			{
			m_iStatus = StatusPlayed;
			return XFPLYR_LINE_ERROR_OUT_OF_BOUND;
			}
//		iTokensStart = iTokens - 1;
//		if(iTokensStart < 0)
//			iTokensStart = 0;
//		iTokensEnd = iTokens + 1;
//		if(iTokensEnd >= m_iTokensLength)
//			iTokensEnd = m_iTokensLength - 1;
//		iTokensStart = iTokens;
//		iTokensEnd = iTokens;
		iTokensStart = 0;
		iTokensEnd = m_iTokensCount - 1;
	}
	else
	{
		iTokensStart = 0;
		iTokensEnd = m_iTokensCount - 1;
	}
//	if(bRecalcLayout)
    //if(m_bPendingLayoutUpdate)
    CRect clientRect = lpRect;
    if(m_rectClient != clientRect)
	{
        m_rectClient = clientRect;
		CalcCharsPositions(
			pFonts,
			lpRect);
		if(m_nFont >= 0 &&
			m_nFont < pFonts->GetSize())
		{
			pFont = pFonts->GetAt(m_nFont);
		}
        m_bPendingLayoutUpdate = false;
	}

    GetPlacement(rectPlacement);
    
    if(m_iStatus == StatusClean)
        return XFPLYR_LINE_SUCCESS;
	if(m_chars.GetLength() <= 0)
		return XFPLYR_LINE_ERROR_OUT_OF_BOUND;
    if(!m_bVisible)
        return XFPLYR_LINE_SUCCESS;
	iTop	= rectPlacement.top;
	iBottom	= rectPlacement.top + textMetric.tmHeight + textMetric.tmInternalLeading;
//    iLastMiddle = m_iMiddle;
	m_lpForegroundDC->SetTextAlign(TA_LEFT | TA_TOP);


    HRGN hrgnOld = CreateRectRgn(0, 0, 0, 0);
    GetClipRgn(m_lpForegroundDC->GetSafeHdc(), hrgnOld);
    CRect rectClipOld;
    GetRgnBox(hrgnOld, rectClipOld);
	//if(iMode == XFPLYR_LINE_RENDER_CLEAR_FULL ||
    //    iMode == XFPLYR_LINE_RENDER_FULL)
    //{
    //    rectClipOld = lpRect;
    //}

    int firstCharIndex;
	int charsLength;
	double dFillRate;
    CString str;
    int nTrimLength;

    if(iPlayingTokenIndex < m_iStartTokenIndex)
    {
///        iMiddle_ = rectPlacement.left;
        m_iMiddle = rectPlacement.left;
    }
    else if(iPlayingTokenIndex >= m_iStartTokenIndex + m_iTokensCount)
    {
        m_iMiddle = rectPlacement.right;
    }
    else
    {
	    if(m_dFillRate < 0.0)
		    dFillRate = 0.0;
	    else if(m_dFillRate > 1.0)
		    dFillRate = 1.0;
	    else
		    dFillRate = m_dFillRate;
        firstCharIndex = m_iaTokensFirstCharIndexes[iPlayingTokenIndex - m_iStartTokenIndex];
	    charsLength = m_iaTokensCharsLengths[iPlayingTokenIndex - m_iStartTokenIndex];
        //(&m_chars[firstCharIndex], charsLength );
        str = m_chars.Mid(firstCharIndex,charsLength);
	    //TRACE(_T("%s****\n"), str);
	    str.TrimRight();
	    //TRACE(_T("%s<<<<\n"), str);
 	    nTrimLength = str.GetLength();
    //	if(nTrimLength == 0)
    //		continue;
	    iLeft	= m_iaCharsPositions[firstCharIndex];
	    iRight	= m_iaCharsPositions[firstCharIndex + nTrimLength];
        double drFull, drPartial, dr;
        //			TRACE(_T("---------Playing Token\n"));
        GetNoteFillRate(
            iPlayingTokenIndex,
            iPlayingNoteIndex,
            pEvents,
            &drFull,
            &drPartial);
        //			TRACE(_T("iPlayingTokenIndex = %d iPlayingNoteIndex = %d \n"), iPlayingTokenIndex, iPlayingNoteIndex);
        //			TRACE(_T("dFillRate = %f drPartial = %f drFull = %f\n"), dFillRate, drPartial, drFull);
//        dr = dFillRate * drPartial + drFull;
   //     iMiddle_ = (int) ((iRight - iLeft) * dr)  + iLeft;
     //   m_iLastMiddle = m_iMiddle;
	   // m_iMiddle = iMiddle_;
        dr = dFillRate * drPartial + drFull;
        //iMiddle_ = ;
        m_iLastMiddle = m_iMiddle;
	    m_iMiddle = (int) ((iRight - iLeft) * dr)  + iLeft;
    }
    if(iMode == XFPLYR_LINE_RENDER_FULL ||
        iMode == XFPLYR_LINE_RENDER_CLEAR_FULL)
    {
        TRACE(_T("m_iMiddle %d"), m_iMiddle);
    }

	int iPlayingIndex;
	int iCharIndex;
	int iLength;

    for(iTokens = iTokensStart; iTokens <= iTokensEnd; iTokens++)
	{
		firstCharIndex = m_iaTokensFirstCharIndexes[iTokens];
		charsLength = m_iaTokensCharsLengths[iTokens];
        str = m_chars.Mid(firstCharIndex,charsLength);
		str.TrimRight();
        nTrimLength = str.GetLength();
		if(nTrimLength == 0)
			continue;

		iLeft	    = m_iaCharsPositions[firstCharIndex];
		iRight	    = m_iaCharsPositions[firstCharIndex + nTrimLength];
		iCharIndex	= firstCharIndex;
		iLength		= nTrimLength;

		if(iTokens + m_iStartTokenIndex < iPlayingTokenIndex)
		{
			if(iMode == XFPLYR_LINE_RENDER_UPDATE)
			{
				while(m_dwaCharsStates[iCharIndex] == CharStatePlayed)
				{
					iCharIndex++;
					iLength--;
					if(iLength <= 0)
						break;
					iLeft = m_iaCharsPositions[iCharIndex];
				}
				if(iLength <= 0)
					continue;
			}
		}
		else if(iTokens + m_iStartTokenIndex > iPlayingTokenIndex)
		{
			if(iMode == XFPLYR_LINE_RENDER_UPDATE)
			{
				while(m_dwaCharsStates[iCharIndex + iLength - 1] == CharStateInitial)
				{
					iLength--;
					if(iLength <= 0)
						break;
					iRight = m_iaCharsPositions[iCharIndex + iLength];
				}
				if(iLength <= 0)
					continue;
			}
			
		} 
		else if(iTokens + m_iStartTokenIndex == iPlayingTokenIndex)
		{
			iPlayingIndex = -1;
			for(i = iCharIndex; i < firstCharIndex + nTrimLength; i++)
			{
				if(m_iMiddle >= m_iaCharsPositions[i]&&
					m_iMiddle < m_iaCharsPositions[i + 1])
				{
					iPlayingIndex = i;
					break;
				}
			}
            if(iMode == XFPLYR_LINE_RENDER_UPDATE)
			{
				if(m_iLastMiddle == m_iMiddle)
					continue;
		
				if(iPlayingIndex >= 0)
				{
					if(iCharIndex < iPlayingIndex)
					{
						while(m_dwaCharsStates[iCharIndex] == CharStatePlayed)
						{
							iCharIndex++;
							iLength--;
							if(iCharIndex >= iPlayingIndex)
								break;
							if(iLength <= 0)
								break;
							iLeft = m_iaCharsPositions[iCharIndex];
						}
						if(iLength <= 0)
							continue;
						iLeft = m_iaCharsPositions[iCharIndex];
					}
					if(iCharIndex + iLength - 1 > iPlayingIndex)
					{
						while(m_dwaCharsStates[iCharIndex + iLength - 1] == CharStateInitial)
						{
							iLength--;
							if(iCharIndex + iLength - 1 <= iPlayingIndex)
								break;
							iRight = m_iaCharsPositions[iCharIndex + iLength];
						}
						if(iLength <= 0)
							continue;
						iRight = m_iaCharsPositions[iCharIndex + iLength];
					}
				}
			}
		}
		CString strFinal;// (&m_chars[iCharIndex], iLength);
        strFinal = m_chars.Mid(iCharIndex, iLength);
		//TRACE(_T("RenderLyricLine iPlyngIdx = %d strFinal = %s\n"), iPlayingTokenIndex,strFinal);
		//TRACE(_T("RenderLyricLine iLeft = %d iMiddle = %d iRight = %d strFinal = %s\n"), iLeft, iMiddle, iRight, strFinal);
		//TRACE(_T("RenderLyricLine iPlyngIdx = %d iLeft = %d iMiddle = %d iRight = %d strFinal = %s\n"), iPlayingIndex, iLeft, iMiddle, iRight, strFinal);

        CRect rectUpdate;
        CRect rectClip;
        CRect rectText;

		if(iMode != XFPLYR_LINE_RENDER_UPDATE ||
            m_iLastMiddle == 0x80000000 ||
            m_iMiddle > m_iLastMiddle )
		{
            
			if(iTokens + m_iStartTokenIndex <= iPlayingTokenIndex)
			{
				//Played
				if(iMode == XFPLYR_LINE_RENDER_UPDATE &&
                    m_iLastMiddle != 0x80000000)
				{
                    rectUpdate.left = iLeft > m_iLastMiddle - 1 ? iLeft : m_iLastMiddle - 1;
                    rectUpdate.top = iTop - sizeMargin.cy;
                    rectUpdate.right = m_iMiddle;// < iRight ? m_iMiddle : iRight;
                    rectUpdate.bottom = iBottom + sizeMargin.cy;
                    //TRACE(_T("RenderLyricLine iPlyngIdx = %d iLeft = %d iMiddle = %d iRight = %d iLeftMax = %d strFinal = %s \n"), iPlayingIndex, iLeft, iMiddle, iRight, i, strFinal);
				}
				else
				{
					rectUpdate.left = iLeft - sizeMargin.cy;
					rectUpdate.top = iTop - sizeMargin.cy;
					rectUpdate.right = m_iMiddle;// < iRight ? m_iMiddle : iRight;
					rectUpdate.bottom = iBottom + sizeMargin.cy;
				}
                
                if(rectUpdate.Width() < 0)
                    continue;
                rectUpdate.InflateRect(0, 0, 1, 1);
                rectClip = rectUpdate;
                rectText = rectUpdate;
                if(m_ptemplate->m_etom == m_ptemplate->tomNoClip)
                {
                    rectClip.OffsetRect(m_ptemplate->m_ptTextOffset);
                }
                rectText.OffsetRect(m_ptemplate->m_ptTextOffset);
				CRgn rgn;
                rgn.CreateRectRgnIndirect(rectClip);
                if(!rectClipOld.IsRectNull())
                {
                    rgn.CombineRgn(CRgn::FromHandle(hrgnOld), &rgn, RGN_AND);
                }
                int iClip;
					if((iClip = m_lpForegroundDC->SelectClipRgn(&rgn)) == ERROR)
                        
					{
						TRACE0("Clipping ERROR!\n");
					}
                    else if(iClip == NULLREGION)
                    {
                        	TRACE0("Clipping NULL!\n");
                    }

                m_lpForegroundDC->BitBlt(
	               rectText.left, rectText.top,
	               rectText.Width(), rectText.Height(),
	               m_lpBackgroundDC,
	               rectText.left, rectText.top,
	               SRCCOPY);

                int iL = iLeft + m_ptemplate->m_ptTextOffset.x;
                int iT = iTop + m_ptemplate->m_ptTextOffset.y;
                m_lpForegroundDC->SelectObject(ppenLeft);
				m_lpForegroundDC->SetTextColor(crLeft);
/*				pFont->EmbossedTextOut(
					m_lpForegroundDC,
					iL, iT,
					strFinal,
					m_iaCharsPositions.GetData(),
					m_iaCharsPositions.GetSize(),
					iCharIndex);	*/
//               TRACE(_T("CLyricViewLine::RenderLyricLine EmbossedTextOut Left\n"));
  //          TRACE(_T("m_iLastMiddle %d iRight %d\n"), m_iLastMiddle, iRight);
    //        TRACE(_T("strFinal %s \n"), strFinal);
                if(prgnaModified)
                {
                    prgnaModified->Add(new CBaseRgn(rgn));
                }
				//rgnModified.CombineRgn(&rgnModified, &rgn, RGN_OR);
				m_lpForegroundDC->SelectClipRgn(NULL);
				rgn.DeleteObject();

			}
        }
			//if(iMode != XFPLYR_LINE_RENDER_UPDATE)
            if(iMode != XFPLYR_LINE_RENDER_UPDATE ||
                m_iLastMiddle == 0x80000000 ||
                m_iMiddle < m_iLastMiddle)
				{
				if(iTokens + m_iStartTokenIndex >= iPlayingTokenIndex)
				{
					//About to play
//                    rectUpdate.left = iMiddle_;
  //                  rectUpdate.top = iTop - sizeMargin.cy;
    //                rectUpdate.right = iRight + sizeMargin.cx;
      //              rectUpdate.bottom = iBottom + sizeMargin.cy;
                if(iMode == XFPLYR_LINE_RENDER_UPDATE &&
                    m_iLastMiddle != 0x80000000)
				{
                    if(iTokens + m_iStartTokenIndex == iPlayingTokenIndex)
                    {
                        rectUpdate.left = m_iMiddle;
                    }
                    else
                    {
                        rectUpdate.left = iLeft;
                    }
                    rectUpdate.top = iTop - sizeMargin.cy;
                    rectUpdate.right = m_iLastMiddle + 1;
                    rectUpdate.bottom = iBottom + sizeMargin.cy;
                    //TRACE(_T("RenderLyricLine iPlyngIdx = %d iLeft = %d iMiddle = %d iRight = %d iLeftMax = %d strFinal = %s \n"), iPlayingIndex, iLeft, iMiddle, iRight, i, strFinal);
				}
				else
				{
                    if(iTokens + m_iStartTokenIndex == iPlayingTokenIndex)
                    {
                        rectUpdate.left = m_iMiddle;
                    }
                    else
                    {
                        rectUpdate.left = iLeft;
                    }
					rectUpdate.top = iTop - sizeMargin.cy;
					rectUpdate.right = iRight + sizeMargin.cx;
					rectUpdate.bottom = iBottom + sizeMargin.cy;
				}
                if(rectUpdate.Width() < 0)
                    continue;
                 
                rectUpdate.InflateRect(0, 0, 1, 1);
                rectClip = rectUpdate;
                rectText = rectUpdate;
                if(m_ptemplate->m_etom == m_ptemplate->tomNoClip)
                {
                    rectClip.OffsetRect(m_ptemplate->m_ptTextOffset);
                }
                rectText.OffsetRect(m_ptemplate->m_ptTextOffset);
				CRgn rgn;
                    rgn.CreateRectRgnIndirect(rectClip);
                    if(!rectClipOld.IsRectNull())
                    {
                        rgn.CombineRgn(CRgn::FromHandle(hrgnOld), &rgn, RGN_AND);
                    }
                    int iClip;
					if((iClip = m_lpForegroundDC->SelectClipRgn(&rgn)) == ERROR)
                        
					{
						TRACE0("Clipping ERROR!\n");
					}
                    else if(iClip == NULLREGION)
                    {
                        	TRACE0("Clipping NULL!\n");
                    }
                    m_lpForegroundDC->BitBlt(
	                   rectText.left, rectText.top,
	                   rectText.Width(), rectText.Height(),
	                   m_lpBackgroundDC,
	                   rectText.left, rectText.top,
	                   SRCCOPY);

					m_lpForegroundDC->SelectObject(ppenRight);
					m_lpForegroundDC->SetTextColor(crRight);
        
                    int iL = iLeft + m_ptemplate->m_ptTextOffset.x;
                    int iT = iTop + m_ptemplate->m_ptTextOffset.y;
/*					pFont->EmbossedTextOut(
						m_lpForegroundDC,
						iL, iT,
						strFinal,
						m_iaCharsPositions.GetData(),
						m_iaCharsPositions.GetSize(),
						iCharIndex);	*/
                    //TRACE(_T("CLyricViewLine::RenderLyricLine EmbossedTextOut right\n"));
                    //TRACE(_T("iMiddle_ %d iRight %d\n"), m_iMiddle, iRight);
                    //TRACE(_T("strFinal %s \n"), strFinal);
                if(prgnaModified)
                {
                    prgnaModified->Add(new CBaseRgn(rgn));
                }
//					rgnModified.CombineRgn(&rgnModified, &rgn, RGN_OR);
					m_lpForegroundDC->SelectClipRgn(NULL);
					rgn.DeleteObject();
				}
			}
			if(iTokens + m_iStartTokenIndex < iPlayingTokenIndex)
			{
				for(i = iCharIndex; i < firstCharIndex + charsLength; i++)
					m_dwaCharsStates[i] = CharStatePlayed;
			}
			else if(iTokens + m_iStartTokenIndex > iPlayingTokenIndex)
			{
				for(i = iCharIndex; i < firstCharIndex + charsLength ; i++)
					m_dwaCharsStates[i] = CharStateInitial;
			} 
			else if(iTokens + m_iStartTokenIndex == iPlayingTokenIndex)
			{
	//			int iPlayingIndex = -1;
				// encontra o índice do caracter sendo tocado
				// (onde está a divisão de cor)
	//			for(i = firstCharIndex; i < firstCharIndex + nTrimLength; i++)
	//			{
	//				if(m_iaCharsPositions[i] <= (DWORD) iMiddle &&
	//					m_iaCharsPositions[i + 1] > (DWORD) iMiddle)
	//				{
	//					iPlayingIndex = i;
	//					break;
	//				}
	//			}
				if(iPlayingIndex >= 0)
				{
	//				TRACE("iCharIndex %d, iPlayingIndex %d", iCharIndex, iPlayingIndex);
					for(i = iCharIndex; i < iPlayingIndex; i++)
						m_dwaCharsStates[i] = CharStatePlayed;
					for(i = iPlayingIndex + 1; i < iCharIndex + iLength ; i++)
						m_dwaCharsStates[i] = CharStateInitial;
					m_dwaCharsStates[iPlayingIndex] = CharStatePlaying;
	//				TRACE(_T("iPlayingIndex = %d\n"), iPlayingIndex);
				}
			}
        }
	/*		if(iMode == XFPLYR_LINE_RENDER_UPDATE)
			{
				if(lpModifiedRect)
				{
					if(iTokens == iTokensStart)
					{
						lpModifiedRect->top = y1;
						lpModifiedRect->left = x1;
					}
					if(iTokens == iTokensStart)
					{
						lpModifiedRect->right = x3;
						lpModifiedRect->bottom = y2;
					}
				}
			}*/
		//	}
//	}
    //if(m_iRedrawMode == RedrawDoRedraw)
//    if(bRedraw)
  //  {
//
  //      CRect rectRgn;
    //    rgnModified.GetRgnBox(rectRgn);
      //  if(rectRgn.IsRectNull())
        //{
//            TRACE(_T("CLyricViewLine.RenderLyricLine NULL rgn\n"));
        //}
        //else
        //{
//            m_pRedrawWnd->RedrawWindow(NULL, pModifiedRgn, RDW_NOERASE | RDW_INVALIDATE | RDW_UPDATENOW | RDW_INTERNALPAINT | RDW_ALLCHILDREN);
          //  m_pRenderWnd->RedrawWindow(NULL, &rgnModified, RDW_INVALIDATE | RDW_UPDATENOW);
            //rgnModified.SetRectRgn(0, 0, 0, 0);
        //}
//    }
//    if(pModifiedRgn)
  //  {
    //    pModifiedRgn->CombineRgn(pModifiedRgn, &rgnModified, RGN_OR);
    //}
    CRect rectRgnOld;
    GetRgnBox(hrgnOld, rectRgnOld);
    if(rectRgnOld.IsRectNull())
    {
        m_lpForegroundDC->SelectClipRgn(NULL);
    }
    else
    {
        m_lpForegroundDC->SelectClipRgn(CRgn::FromHandle(hrgnOld));
    }
    DeleteObject(hrgnOld);
	return XFPLYR_LINE_SUCCESS;

}


XFPLYR_LINE_RESULT CLyricViewLine::RenderLine(
	LPRECT		lpRect,
	CRgn *		pModifiedRgn,
	int			iMode,
	int			*count,
	CXfplayerFont * pFont,
	bool		bRecalcLayout,
	COLORREF	crColor,
	CPen		&pen)
{
	int iTokensStart;
	int iTokensEnd;
//	int	iTokens;
	//int iLeft, iTop, iRight, iBottom;
//	int iMiddle;
//	int i;

    CRect rectPlacement;
//    m_ptemplate->GetPlacement(rectPlacement);
    GetPlacement(rectPlacement);

	m_lpForegroundDC->SetBkMode(TRANSPARENT);
	
	CPoint iMargin;
	{
		LOGPEN logPen;
		pen.GetLogPen(&logPen);
		iMargin.x = logPen.lopnWidth.x / 2 + logPen.lopnWidth.x % 2;
		iMargin.y = logPen.lopnWidth.y / 2 + logPen.lopnWidth.y % 2;
	}
	//TRACE(_T("iPlyingTken: %05d\n"), iPlayingTokenIndex);
	CRgn rgn;
	TEXTMETRIC textMetric;
	m_lpForegroundDC->GetTextMetrics(&textMetric);
	if(iMode == XFPLYR_LINE_RENDER_CLEAR_FULL ||
	   iMode == XFPLYR_LINE_RENDER_CLEAR)
	{
		iTokensStart = 0;
		iTokensEnd = m_iTokensCount - 1;
		
		m_lpForegroundDC->BitBlt(
		   m_rectPrevious.left, m_rectPrevious.top,
		   m_rectPrevious.Width(), m_rectPrevious.Height(),
		   m_lpBackgroundDC,
		   m_rectPrevious.left, m_rectPrevious.top,
		   SRCCOPY);
		if(pModifiedRgn)
		{
			rgn.CreateRectRgn(
				m_rectPrevious.left, m_rectPrevious.top,
				m_rectPrevious.right, m_rectPrevious.bottom);
			pModifiedRgn->CombineRgn(pModifiedRgn, &rgn, RGN_OR);
//			rgn.Detach();
			rgn.DeleteObject();
		}
		if(iMode == XFPLYR_LINE_RENDER_CLEAR)
			return XFPLYR_LINE_SUCCESS;
	}
	else if(iMode == XFPLYR_LINE_RENDER_UPDATE)
	{
	}
	else
	{
	}
	if(bRecalcLayout)
	{
		CalcCharsPositions(
			pFont,
			lpRect);
		m_lpForegroundDC->SelectObject(pFont);
	}
    //m_ptemplate->GetPlacement(m_rectPrevious);
    GetPlacement(m_rectPrevious);


//	CString strFinal(m_chars, m_charsLength);
    CString strFinal;
    strFinal = m_chars;
	rgn.CreateRectRgn(
		rectPlacement.left - iMargin.x,
		rectPlacement.top - iMargin.y,
		rectPlacement.right + iMargin.x,
		rectPlacement.bottom + iMargin.y);
	if(m_lpForegroundDC->SelectClipRgn(&rgn) == ERROR)
	{
		TRACE0("Clipping ERROR!\n");
	}
	m_lpForegroundDC->SelectObject(&pen);
	m_lpForegroundDC->SetTextColor(crColor);
/*	pFont->EmbossedTextOut(
		m_lpForegroundDC,
		rectPlacement.left, rectPlacement.top,
		strFinal,
		m_iaCharsPositions.GetData(),
        m_iaCharsPositions.GetSize(),
		0);	*/
	if(pModifiedRgn)
	{
		pModifiedRgn->CombineRgn(pModifiedRgn, &rgn, RGN_OR);
		
	}
	m_lpForegroundDC->SelectClipRgn(NULL);
	rgn.DeleteObject();

	return XFPLYR_LINE_SUCCESS;

}

XFPLYR_LINE_RESULT CLyricViewLine::RenderLine(
	LPRECT		lpRect,
	CRgn *		pModifiedRgn,
	int			iMode,
	int			*count,
	CTypedPtrArray <CPtrArray, CXfplayerFont *> * pFonts,
	bool		bRecalcLayout,
	COLORREF	crColor,
	CPen		&pen)
{
	int iTokensStart;
	int iTokensEnd;
//	int	iTokens;
	//int iLeft, iTop, iRight, iBottom;
//	int iMiddle;
//	int i;

    CRect rectPlacement;
//    m_ptemplate->GetPlacement(rectPlacement);
    GetPlacement(rectPlacement);

	m_lpForegroundDC->SetBkMode(TRANSPARENT);
	
	CPoint iMargin;
	{
		LOGPEN logPen;
		pen.GetLogPen(&logPen);
		iMargin.x = logPen.lopnWidth.x / 2 + logPen.lopnWidth.x % 2;
		iMargin.y = logPen.lopnWidth.y / 2 + logPen.lopnWidth.y % 2;
	}
	//TRACE(_T("iPlyingTken: %05d\n"), iPlayingTokenIndex);
	CXfplayerFont * pFont;
	if(m_nFont >= 0 &&
		m_nFont < pFonts->GetSize())
	{
		pFont = pFonts->GetAt(m_nFont);
	}
	CRgn rgn;
	TEXTMETRIC textMetric;
	m_lpForegroundDC->GetTextMetrics(&textMetric);
	if(iMode == XFPLYR_LINE_RENDER_CLEAR_FULL ||
	   iMode == XFPLYR_LINE_RENDER_CLEAR)
	{
		iTokensStart = 0;
		iTokensEnd = m_iTokensCount - 1;
		
		m_lpForegroundDC->BitBlt(
		   m_rectPrevious.left, m_rectPrevious.top,
		   m_rectPrevious.Width(), m_rectPrevious.Height(),
		   m_lpBackgroundDC,
		   m_rectPrevious.left, m_rectPrevious.top,
		   SRCCOPY);
		if(pModifiedRgn)
		{
			rgn.CreateRectRgn(
				m_rectPrevious.left, m_rectPrevious.top,
				m_rectPrevious.right, m_rectPrevious.bottom);
			pModifiedRgn->CombineRgn(pModifiedRgn, &rgn, RGN_OR);
//			rgn.Detach();
			rgn.DeleteObject();
		}
		if(iMode == XFPLYR_LINE_RENDER_CLEAR)
			return XFPLYR_LINE_SUCCESS;
	}
	else if(iMode == XFPLYR_LINE_RENDER_UPDATE)
	{
	}
	else
	{
	}
	if(bRecalcLayout)
	{
		CalcCharsPositions(
			pFonts,
			lpRect);
		if(m_nFont >= 0 &&
			m_nFont < pFonts->GetSize())
		{
			m_lpForegroundDC->SelectObject(pFonts->GetAt(m_nFont));
		}
	}
	m_rectPrevious.left = rectPlacement.left;
	m_rectPrevious.top = rectPlacement.top;
	m_rectPrevious.right = rectPlacement.right;
	m_rectPrevious.bottom = rectPlacement.bottom;

    switch(m_iAnimateType)
    {
    case AnimateNoAnimate:
        {
        //	CString strFinal(m_chars, m_charsLength);
            CString strFinal;
            strFinal = m_chars;
	        rgn.CreateRectRgn(
		        rectPlacement.left - iMargin.x,
		        rectPlacement.top - iMargin.y,
		        rectPlacement.right + iMargin.x,
		        rectPlacement.bottom + iMargin.y);
	        if(m_lpForegroundDC->SelectClipRgn(&rgn) == ERROR)
	        {
		        TRACE0("Clipping ERROR!\n");
	        }
	        m_lpForegroundDC->SelectObject(&pen);
	        m_lpForegroundDC->SetTextColor(crColor);
/*	        pFont->TextOutEx(
                m_lpForegroundDC,
		        rectPlacement.left, rectPlacement.top,
		        strFinal,
		        m_iaCharsPositions.GetData(),
                m_iaCharsPositions.GetSize(),
		        0,
                MapToFontEffect(m_iTextEffect));*/	
	        if(pModifiedRgn)
	        {
		        pModifiedRgn->CombineRgn(pModifiedRgn, &rgn, RGN_OR);
		        
	        }
	        m_lpForegroundDC->SelectClipRgn(NULL);
	        rgn.DeleteObject();
        }
        break;
    case AnimateRHL:
        {//	CString strFinal(m_chars, m_charsLength);
            
            int iLeft = m_iaCharsPositions.ElementAt(0);
            int iLeftDiff  = 0;
            int iLastLeftDiff = 0;
            for(int i = 0; i < m_iaCharsPositions.GetSize(); i++)
            {
                iLastLeftDiff = iLeftDiff;
                iLeftDiff = m_iaCharsPositions.ElementAt(i) - iLeft;
                if((int) m_dAnimateProgress <= iLeftDiff)
                {
                    i--;
                    break;
                }
            }
            
            CString strFinal(m_chars);
            CString strLeft = strFinal.Right(strFinal.GetLength() - i);
            int iLeftOffset;
            iLeftOffset = iLastLeftDiff - (int) m_dAnimateProgress;
	        rgn.CreateRectRgn(
		        rectPlacement.left - iMargin.x,
		        rectPlacement.top - iMargin.y,
		        rectPlacement.right + iMargin.x,
		        rectPlacement.bottom + iMargin.y);
	        if(m_lpForegroundDC->SelectClipRgn(&rgn) == ERROR)
	        {
		        TRACE0("Clipping ERROR!\n");
	        }
	        m_lpForegroundDC->SelectObject(&pen);
	        m_lpForegroundDC->SetTextColor(crColor);
	   /*     pFont->TextOutEx(
                m_lpForegroundDC,
		        rectPlacement.left + iLeftOffset, rectPlacement.top,
		        strLeft,
		        m_iaCharsPositions.GetData(),
                m_iaCharsPositions.GetSize(),
		        0,
                MapToFontEffect(m_iTextEffect));*/	
            int iMaxCounter = max((int) m_iaCharsPositions.ElementAt(m_chars.GetLength()) - m_iaCharsPositions.ElementAt(0) + 100, rectPlacement.right - rectPlacement.left);
            int iRight = iMaxCounter - (int) m_dAnimateProgress;
            if(iRight < rectPlacement.right)
            {
                int iRightEnd;
                for(int i = 0; i < m_iaCharsPositions.GetSize(); i++)
                {
                    iRightEnd = iRight + m_iaCharsPositions.ElementAt(i) - iLeft;
                    if(iRightEnd >= rectPlacement.right)
                    {
                        break;
                    }
                }
                CString strRight = strFinal.Left(i);
    	 /*       pFont->TextOutEx(
                    m_lpForegroundDC,
		            iRight, rectPlacement.top,
		            strRight,
		            m_iaCharsPositions.GetData(),
                    m_iaCharsPositions.GetSize(),
		            0,
                    MapToFontEffect(m_iTextEffect));*/	
                }
            
	        if(pModifiedRgn)
	        {
		        pModifiedRgn->CombineRgn(pModifiedRgn, &rgn, RGN_OR);
		        
	        }
	        m_lpForegroundDC->SelectClipRgn(NULL);
	        rgn.DeleteObject();
        }
        break;
    default:
        ASSERT(FALSE);
    }


	return XFPLYR_LINE_SUCCESS;

}

int CLyricViewLine::GetStatus(int iPlayingIndex)
{
	if(//m_iStatus == XFPLYR_LINE_STATUS_NEW ||
        m_iStatus == StatusClean ||
	   m_iStatus == StatusEmpty ||
       m_iStatus == StatusPrepared )

	   return m_iStatus;
	else
	{
		int iDelta = iPlayingIndex - m_iStartTokenIndex;
		if(iDelta < 0)
			return StatusNew;
		else if(iDelta >= m_iTokensCount)
			return StatusPlayed;
		else
			return StatusPlaying;
	}
	return m_iStatus;
}

void CLyricViewLine::SetStatus(int iStatus)
{
	if(iStatus == StatusEmpty)
	{
        m_chars.Empty();
//		m_charsLength = 0;
		m_iTokensCount = 0;
		m_iStartTokenIndex = -1;
//		m_dwEmptyTime = timeGetTime();
		m_iStatus = StatusEmpty;
	}
	else if(iStatus == StatusClean)
	{
        if(m_iStatus != StatusClean)
        {
		    m_dwCleanTime = timeGetTime();
		    m_iStatus = StatusClean;
        }
	}else if(iStatus == StatusNew)
	{
        if(m_iStatus != StatusNew)
        {
            //TRACE(_T("CLyricViewLine::SetStatus(StatusNew) m_iStartTokenIndex = %d\n"), m_iStartTokenIndex);
            m_iMiddle = 0x80000000;
            m_iLastMiddle = 0x80000000;
            for(int i = 0; i < m_chars.GetLength(); i++)
            {
                m_dwaCharsStates[i] = CharStateNew;
            }
            SetNewTime();
		    m_iStatus = StatusNew;
        }
	}
	else
	{
		m_iStatus = iStatus;
	}

}

void CLyricViewLine::SetPlayingStatus(int iPlayingTokenIndex)
{
    if(iPlayingTokenIndex < m_iStartTokenIndex)
    {
        SetStatus(StatusNew);
    }
    else if (iPlayingTokenIndex >= m_iStartTokenIndex &&
        iPlayingTokenIndex < m_iStartTokenIndex + m_iTokensCount)
    {
        SetStatus(StatusPlaying);
    }
    else if (iPlayingTokenIndex >= m_iStartTokenIndex + m_iTokensCount)
    {
        if(GetStatus(iPlayingTokenIndex) != StatusClean)
        {
            SetStatus(StatusPlayed);
        }
    }

}

void CLyricViewLine::Reset()
{
	SetStatus(StatusEmpty);
}

void CLyricViewLine::UpdateFillRate(double msElapsed, double msLength)
{
	// initial filling minimum time and initial filling rate
	// is applied to facilitate karaoke text reading. When
	// the filling event is slow, initial filling rate may be
	// so small as zero rate. But to give a hint, a minimum
	// fill rate is applied. When the filling event is faster,
	// the initial filling rate must be greater so the hint
	// is more obvious..

	// minimum time where maximim fill rate is applied
	// msInitialFillingMinimumTime, msInitialFillintMinimumRate
	const double x0 = 70.0, y1 = 0.7;

	// maximumm time where minimum fill rate is applied
	// msInitialFillingMaximumTime, msInitialFillingMaximumTime
	const double x1 = 5000.0, y0 = 0.35;

	const double zr = 0.03;
	// calcula o initial rate com base numa curva 
	// ir = (y1-y0)(db^(-length+x0))+y0
	// onde a base db é calculada para ter somente zr
	// da diferença (y1 - y0) para atingir
	// o patamar y0, depois que o tempo passa x1 segundos.
	// para isso db deve ser calculado como se segue.

	double db = exp(log(zr) / (x0 - x1));
	double ir = (y1 - y0) *(pow(db, x0 - msLength)) + y0;
	m_dFillRate = ir + ((1 - ir) * msElapsed / msLength);

	
}

void CLyricViewLine::CalcCharsPositions(
	CTypedPtrArray <CPtrArray, CXfplayerFont *> * pFonts,
	LPRECT pRect)
{
    CRect rectPlacement;
    m_ptemplate->GetPlacement_(rectPlacement);
	//CXfplayerFont * pFont;
	if(m_chars.GetLength() <= 0)
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
			m_lpForegroundDC->SelectObject(pFonts->GetAt(nFont)->GetFont());
			GetTextExtentPoint32(
				m_lpForegroundDC->GetSafeHdc(),
				m_chars,
				m_chars.GetLength(),
				&size);
			if((m_iAlign & AlignLeft) > 0)
			{
				if(size.cx + rectPlacement.left <= pRect->right)
				{
					iFontFound = nFont;
					break;
				}
			}
			else if((m_iAlign & AlignRight) > 0)
			{
				if(rectPlacement.right - size.cx >= 0)
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
		m_lpForegroundDC->SelectObject(pFonts->GetAt(m_nFont)->GetFont());
		if(m_iAlign == AlignLeft)
		{
			m_iaCharsPositions[0] = rectPlacement.left + m_iIndent;
			for(i = 1; i <= m_chars.GetLength(); i++)
			{
				GetTextExtentPoint32(
					m_lpForegroundDC->GetSafeHdc(),
					m_chars,
					i,
					&size);
				m_iaCharsPositions[i] = size.cx + rectPlacement.left  + m_iIndent;
			}
			if(m_bAutoSizeX)
			{
				rectPlacement.right = rectPlacement.left  + m_iIndent + size.cx;
            }
			if(m_bAutoSizeY)
			{
				rectPlacement.bottom = rectPlacement.top + size.cy;
			}
		}
		else if(m_iAlign == AlignRight)
		{
			GetTextExtentPoint32(
				m_lpForegroundDC->GetSafeHdc(),
				m_chars,
				m_chars.GetLength(),
				&size);
			iMaxExtent = size.cx;
			iLeft = rectPlacement.right - iMaxExtent;
			m_iaCharsPositions[0] = iLeft;
			for(i = 1; i <= m_chars.GetLength(); i++)
			{
				GetTextExtentPoint32(
					m_lpForegroundDC->GetSafeHdc(),
					m_chars,
					i,
					&size);
				m_iaCharsPositions[i] = size.cx + iLeft;
			}
			if(m_bAutoSizeX)
			{
				rectPlacement.left = rectPlacement.right - size.cx;
            }
            if(m_bAutoSizeY)
            {
				rectPlacement.bottom = rectPlacement.top + size.cy;
			}
		}
	
	}

	else
	{
		int i; //, width;
		CSize size;
		while(TRUE)
		{
			m_iaCharsPositions[0] = rectPlacement.left;
			for(i = 1; i <= m_chars.GetLength(); i++)
			{
				GetTextExtentPoint32(
					m_lpForegroundDC->GetSafeHdc(),
					m_chars,
					i ,
					&size);
				m_iaCharsPositions[i] = rectPlacement.left + size.cx;
			}
		}
		if(m_bAutoSizeX)
		{
			rectPlacement.right = rectPlacement.left + size.cx;
        }
		if(m_bAutoSizeY)
		{
			rectPlacement.bottom = rectPlacement.top + size.cy;
		}
	}
    SetPlacement(rectPlacement);

}

void CLyricViewLine::CalcCharsPositions(
	CXfplayerFont * pFont,
	LPRECT pRect)
{
    CRect rectPlacement;
    m_ptemplate->GetPlacement_(rectPlacement);
	
	if(m_chars.GetLength() <= 0)
		return;
	m_lpForegroundDC->SelectObject(pFont);
	int i, iLeft, iRight, iMaxExtent;
	CSize size;
	if(m_iAlign == AlignLeft)
	{
		m_iaCharsPositions[0] = rectPlacement.left + m_iIndent;
		iRight = 0;
		for(i = 1; i <= m_chars.GetLength(); i++)
		{
			GetTextExtentPoint32(
				m_lpForegroundDC->GetSafeHdc(),
				m_chars,
				i,
				&size);
			m_iaCharsPositions[i] = iRight = size.cx + rectPlacement.left + m_iIndent;
		}
		if(m_bAutoSizeX)
		{
			rectPlacement.right = iRight;
        }
		if(m_bAutoSizeY)
		{
			rectPlacement.bottom = rectPlacement.top + size.cy;
		}
	}
	else if(m_iAlign == AlignRight)
	{
		GetTextExtentPoint32(
			m_lpForegroundDC->GetSafeHdc(),
			m_chars,
			m_chars.GetLength(),
			&size);
		iMaxExtent = size.cx;
		iLeft = rectPlacement.right - iMaxExtent;
		m_iaCharsPositions[0] = iLeft;
		for(i = 1; i <= m_chars.GetLength(); i++)
		{
			GetTextExtentPoint32(
				m_lpForegroundDC->GetSafeHdc(),
				m_chars,
				i,
				&size);
			m_iaCharsPositions[i] = size.cx + iLeft;
		}
		if(m_bAutoSizeX)
		{
			rectPlacement.left = iLeft;
        }
		if(m_bAutoSizeY)
		{
			rectPlacement.bottom = rectPlacement.top + size.cy;
		}
	}
    SetPlacement(rectPlacement);

}

void CLyricViewLine::CalcNotesPositions(
	CLyricEventsV2 * pEvents)
{

	//int i, iStartNote, iNotesLength;

	//for(i = 0; i < m_iTokensLength; i++)
	//{
	//	pEvents->GetTokenNotes(
	//		&iStartNote,
	//		&iNotesLength,
	//		m_iStartTokenIndex + i);
	//	m_tokensFirstNoteIndexes[i] = iStartNote;
	//	m_tokensNotesLengths[i] = iNotesLength;
	//}

}

//BOOL CLyricViewLine::IsEmptyTimedOut()
//{
//	if(m_iStatus ==	XFPLYR_LINE_STATUS_EMPTY)
//	{
//		if(m_dwEmptyTime + 2000 < timeGetTime())
//			return TRUE;
//	}
//	return FALSE;
//
//}


bool CLyricViewLine::IsNewTimedOut()
{
	//if(m_iStatus ==	XFPLYR_LINE_STATUS_NEW)
	//{
		if(m_dwNewTime + 2000 < timeGetTime())
        {
      //      TRACE(_T("CLyricViewLine::IsNewTimedOut() = true m_iStartTokenIndex = %d\n"), m_iStartTokenIndex);
			return true;
        }
	//}
//    TRACE(_T("CLyricViewLine::IsNewTimedOut() = false m_iStartTokenIndex = %d\n"), m_iStartTokenIndex);
	return false;

}

bool CLyricViewLine::IsCleanTimedOut()
{
	//if(m_iStatus ==	XFPLYR_LINE_STATUS_NEW)
	//{
		if(m_dwCleanTime + 2000 < timeGetTime())
        {
  //          TRACE(_T("CLyricViewLine::IsCleanTimedOut() = true m_iStartTokenIndex = %d\n"), m_iStartTokenIndex);
			return true;
        }
	//}
    //TRACE(_T("CLyricViewLine::IsCleanTimedOut() = false m_iStartTokenIndex = %d\n"), m_iStartTokenIndex);
	return false;

}


//bool CLyricViewLine::IsEmptyTimedOut()
//{
//	if(m_iStatus ==	XFPLYR_LINE_STATUS_NEW)
//	{
//		if(m_dwEmptyTime + 2000 < timeGetTime())
//			return TRUE;
//	}
//	return FALSE;

//}

void CLyricViewLine::GetNoteFillRate(
	int iTokenIndex,
	int iNoteIndex,
	CLyricEventsV2 * pEvents,
	double * drFull,
	double * drPartial)
{

	int i;//, iStartNote, iLastNote, iNotesCount;
	int iNotesCount;
	CArray<DWORD, DWORD> dwNotes;
    if(pEvents == NULL)
        return;
	iNotesCount = pEvents->GetTokenNotes(iTokenIndex, dwNotes) ;
	if(dwNotes.GetSize() <= 0)
	{
		*drFull = 0.0;
		*drPartial = 1.0;
		return;
	}
//	iStartNote = dwNotes.GetAt(0);
//	iLastNote = dwNotes.GetAt(dwNotes.GetSize() - 1);
//	iLastNote = iNoteIndex;
	*drFull = 0.0;
	double dDuration, dTotalDuration = 0.0;
//	for(i = iStartNote; i < iNoteIndex, i < dwNotes.GetSize(); i++)
//	{
//		*drFull += pEvents->m_msaNotesDuration[i];
//	}
	int iIndex;
	for(i = 0; i < dwNotes.GetSize(); i++)
	{
		iIndex = dwNotes.GetAt(i);
		dDuration = pEvents->m_msaNotesDuration[iIndex];
        dTotalDuration += dDuration;
		if(iIndex < iNoteIndex)
			*drFull += dDuration;
		
	}
//	*drFull = pEvents->m_msaNotesPosition[iNoteIndex] -
//		pEvents->m_msaNotesPosition[iStartNote];
	//i = iLastNote;
//	i =  iNoteIndex;
	//if(i == iLastNote)
//	if(i == iNoteIndex)
//	{
    if(iNoteIndex < 0)
        *drPartial = 0.0;
    else
	    *drPartial = pEvents->m_msaNotesDuration[iNoteIndex];
//		if(pEvents->m_msaTokensDuration[iTokenIndex] != 0)
//		{
//		for(i = iNoteIndex; i <= iLastNote, i < dwNotes.GetSize(); i++)
//		{
//			dDuration += pEvents->m_msaNotesDuration[i];
//		}
	if(dTotalDuration != 0.0)
	{
		*drFull /= dTotalDuration;
		*drPartial /= dTotalDuration;
	}
	else
	{
		*drFull = 0.0;
		*drPartial = 1.0;
	}
//	}
//	else
//	{
//		*drFull = 0.0;
//		*drPartial = 1.0;
//	}

	//int i, iFound = -1;
	//for(i = 0; i < m_iTokensLength; i++)
	//{
//		if(iNoteIndex >= m_tokensFirstNoteIndexes[i] &&
//			iNoteIndex < m_tokensFirstNoteIndexes[i] +
//			m_tokensNotesLengths[i])
//		{
//			iFound = i;
//			break;
//		}
//	}
//	if(iFound >= 0)
//	{
//		double dwDuration = 0;
//		for(i = m_tokensFirstNoteIndexes[i];
//			i <= iNoteIndex; i++)
//		{
//			dwDuration += pEvents->m_msaNotesDuration[i];
//		}
//		return dwDuration / pEvents->m_msaTokensDuration[iTokenIndex];
//	}
//	else
//	{
//		return 1.0;
//	}

}

void CLyricViewLine::SetAutoSize(bool bAutoSize)
{
	m_bAutoSizeX = bAutoSize;
    m_bAutoSizeY = bAutoSize;
}

void CLyricViewLine::SetAlign(int iAlign)
{
	m_iAlign = iAlign;
}

/*void CLyricViewLine::SetRect(LPRECT lpRect)
{
    rectPlacement.left     = lpRect->left;
    rectPlacement.top      = lpRect->top;
    rectPlacement.right    = lpRect->right;
    rectPlacement.bottom   = lpRect->bottom;
}

void CLyricViewLine::GetRect(LPRECT lpRect)
{
    lpRect->left    = rectPlacement.left;
    lpRect->top     = rectPlacement.top;
    lpRect->right   = rectPlacement.right;
    lpRect->bottom  = rectPlacement.bottom;
}*/

CLyricViewLine::operator =(CLyricViewLine & src)
{
    m_bAutoSizeX = src.m_bAutoSizeX;
    m_bAutoSizeY = src.m_bAutoSizeY;
    m_bFirstLine = src.m_bFirstLine;
    m_bVisible = src.m_bVisible;
    m_chars = src.m_chars;
    m_iaCharsPositions.Copy(src.m_iaCharsPositions);
    m_dwaCharsStates.Copy(src.m_dwaCharsStates);
    m_dFillRate = src.m_dFillRate;
//    m_dwEmptyTime = src.m_dwEmptyTime;
    m_dwCleanTime = src.m_dwCleanTime;
    m_dwNewTime = src.m_dwNewTime;
    m_iAlign = src.m_iAlign;
//    rectPlacement.bottom = src.rectPlacement.bottom;
    //rectPlacement.left = src.rectPlacement.left;
    m_iLineIndex = src.m_iLineIndex;
    m_iMiddle = src.m_iMiddle;
    m_iNotesLength = src.m_iNotesLength;
//    rectPlacement.right = src.rectPlacement.right;
    m_ptemplate = src.m_ptemplate;
//    m_iStartNoteIndex = src.m_iStartNoteIndex;
    m_iStartTokenIndex = src.m_iStartTokenIndex;
    m_iStatus = src.m_iStatus;
//    m_iTokensLength = src.m_iTokensLength;
    m_iTokensCount = src.m_iTokensCount;
//    rectPlacement.top = src.rectPlacement.top;
    m_lpBitmapData  = src.m_lpBitmapData;
    m_nFont = src.m_nFont;
    m_iRelativeLineIndex = src.m_iRelativeLineIndex;
    m_iaTokensCharsLengths.Copy(src.m_iaTokensCharsLengths);
    m_iaTokensFirstCharIndexes.Copy(src.m_iaTokensFirstCharIndexes);
    m_iAnimateType = src.m_iAnimateType;
    m_iTextEffect = src.m_iTextEffect ;
    m_dAnimateProgress = src.m_dAnimateProgress;
    m_dAnimateProgressIncrement = src.m_dAnimateProgressIncrement;
    m_lpForegroundDC = src.m_lpForegroundDC ;
    m_lpBackgroundDC = src.m_lpBackgroundDC;
//    m_pRenderWnd = src.m_pRenderWnd;
//    m_iRedrawMode = src.m_iRedrawMode;

}

int CLyricViewLine::GetFirstToken()
{
    return m_iStartTokenIndex;
}

int CLyricViewLine::GetLastToken()
{
    return m_iStartTokenIndex + m_iTokensCount - 1;
}

void CLyricViewLine::SetPendingLayoutUpdate(bool bPending)
{
    m_bPendingLayoutUpdate = bPending;
}


void CLyricViewLine::SetNewTime()
{
    m_dwNewTime = timeGetTime();
}

void CLyricViewLine::SetVisible(bool bVisible)
{
    if(bVisible && !m_bVisible)
    {
        //m_bPendingFullUpdate = true;
        m_bVisible = true;
        SetStatus(StatusNew);
        m_pContainer->OnChildSetVisible(this, m_bVisible);
        
    }
    else if(!bVisible && m_bVisible)
    {
        //m_bPendingFullUpdate = true;
        m_bVisible = false;
        m_pContainer->OnChildSetVisible(this, m_bVisible);
    }
}

bool CLyricViewLine::GetVisible()
{
    return m_bVisible;
}

void CLyricViewLine::OnTimerAnimate(CRgn * pModifiedRgn)
{
    CRect rectPlacement;
    m_ptemplate->GetPlacement_(rectPlacement);

    switch(m_iAnimateType)
    {
    case AnimateNoAnimate:
        break;
    case AnimateRHL:
        {
            m_dAnimateProgress+= m_dAnimateProgressIncrement;
            if(m_iaCharsPositions.GetSize() > 0)
            {
                if((int)m_dAnimateProgress > max(m_iaCharsPositions.ElementAt(m_chars.GetLength()) - m_iaCharsPositions.ElementAt(0) + 100, rectPlacement.right - rectPlacement.left))
                    m_dAnimateProgress = 0.0;
                CRect rect;
                RenderLine(rectPlacement, pModifiedRgn, XFPLYR_LINE_RENDER_CLEAR_FULL, NULL, GetFonts(), false, m_crForeground, *m_lpPenEmboss);
            }
        }
        break;
    default:
        ASSERT(FALSE);
    }
}

void CLyricViewLine::SetAnimateType(int iAnimateType)
{
    m_iAnimateType = iAnimateType;
    m_dAnimateProgress = 0.0;

}

void CLyricViewLine::SetTextEffect(int iTextEffect)
{
    m_iTextEffect = iTextEffect;
}

void CLyricViewLine::SetForegroundDC(CDC *pDC)
{
    m_lpForegroundDC = pDC;
}

void CLyricViewLine::SetBackgroundDC(CDC *pDC)
{
    m_lpBackgroundDC = pDC;
}

void CLyricViewLine::SetEmbossPen(CPen *lpPen)
{
    m_lpPenEmboss = lpPen;

}

void CLyricViewLine::SetForegroundColor(COLORREF cr)
{
    m_crForeground = cr;
}

CTypedPtrArray <CPtrArray, CXfplayerFont *> * CLyricViewLine::GetFonts()
{
    return &m_fonts;
}

int CLyricViewLine::MapToFontEffect(int iLineEffect)
{
    switch(iLineEffect)
    {
    case EffectSimple:
        return CXfplayerFont::EffectSimple;
    case EffectEmbossed:
        return CXfplayerFont::EffectEmbossed;
    }
    ASSERT(FALSE);
    return -1;
}

void CLyricViewLine::SetAnimateIncrement(double dIncrement)
{
    m_dAnimateProgressIncrement = dIncrement;
}

//void CLyricViewLine::SetRedrawMode(int iMode)
//{
  //  m_iRedrawMode = iMode;
//}

//void CLyricViewLine::SetRenderWindow(CWnd *pWnd)
//{
  //  m_pRenderWnd = pWnd;
//}

//void CLyricViewLine::SetRenderCriticalSection(CCriticalSection *pcs)
//{
//    m_pcsRender =   pcs;
//}


CLyricViewLineTemplate * CLyricViewLine::GetTemplate()
{
    return m_ptemplate;
}

void CLyricViewLine::SetTemplate(CLyricViewLineTemplate *pTemplate)
{
    
    m_ptemplate = pTemplate;
    
//    m_ptemplate->GetPlacement_(m_rectPlacement);

}

void CLyricViewLine::GetTokenX(
    int iTokenIndex,
    double * pdLeft,
    double * pdRight)
{
//	int iLeft;
  //  int iRight;

    ASSERT(iTokenIndex >= GetFirstToken());
    ASSERT(iTokenIndex <= GetLastToken() + 1);

    if(iTokenIndex == GetLastToken() + 1)
    {
	    *pdLeft	= 0.0;
	    *pdRight = 0.0;
    }
    else
    {
        int iFirstCharIndex = m_iaTokensFirstCharIndexes[iTokenIndex - m_iStartTokenIndex];
        int iCharsLength = m_iaTokensCharsLengths[iTokenIndex - m_iStartTokenIndex];
        CString str = m_chars.Mid(iFirstCharIndex, iCharsLength);
	    //TRACE(_T("%s****\n"), str);
	    str.TrimRight();
	    //TRACE(_T("%s<<<<\n"), str);
 	    int nTrimLength = str.GetLength();
	    *pdLeft	= m_iaCharsPositions[iFirstCharIndex];
	    *pdRight = m_iaCharsPositions[iFirstCharIndex + nTrimLength];
    }
    //return ((double) iLeft + iRight) / 2.0;

}

CLyricViewLines * CLyricViewLine::GetContainer()
{
    return m_pContainer;
}

void CLyricViewLine::GetPlacement(LPRECT lprect)
{
//    *lprect = m_rectPlacement;
    m_ptemplate->GetPlacement_(lprect);
}

void CLyricViewLine::SetPlacement(LPRECT lprect)
{
    //m_rectPlacement = lprect;
    m_ptemplate->SetPlacement_(lprect);
}

bool CLyricViewLine::GetTokenText(CString *lpstr)
{
    ASSERT(FALSE);
    return false;
}
