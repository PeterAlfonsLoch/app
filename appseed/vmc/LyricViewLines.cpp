// LyricViewLines.cpp: implementation of the CLyricViewLines class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "VMSApp.h"
#include "LyricViewLines.h"

#include "LyricViewLineTemplates.h"

#include "DWArray.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLyricViewLines::CLyricViewLines()
:CBaseArray<CLyricViewLine, CLyricViewLine &>()
{
    m_iFirstVisible = -1;
    m_iLastVisible = -1;
}

CLyricViewLines::~CLyricViewLines()
{
//    CArray<CLyricViewLine, CLyricViewLine &>::~CArray<CLyricViewLine, CLyricViewLine &>();
}

int CLyricViewLines::GetTokenLine(int iToken, CLyricViewLine ** viewLine)
{
    int iLoBound = 0;
	int iHiBound = m_nSize - 1;
	int iIndex = 0;;
	while(true)
	{
		if(iLoBound > iHiBound)
		{
			return -1;
		}
		iIndex = (iHiBound + iLoBound) / 2;
		if(operator[](iIndex).ContainsToken(iToken))
			break;
		else if(iToken < operator[](iIndex).GetFirstToken())
		{
			iHiBound = iIndex - 1;
		}
		else if(iToken > operator[](iIndex).GetLastToken())
		{
			iLoBound = iIndex + 1;
		}
		else
			ASSERT(0);
	}
    if(viewLine != NULL)
    {
	    *viewLine = &operator[](iIndex);
    }
	return iIndex;
}

/*int CLyricViewLines::GetAt(CLyricViewLine * * pViewLine, CLyricViewLines &viewLines, int iIndex)
{
    int iLineIndex = viewLines.ElementAt(iIndex).m_iRelativeLineIndex;
    if(iLineIndex >= 0 &&
        iLineIndex < m_nSize)
    {
        *pViewLine = &ElementAt(iLineIndex);
        return iLineIndex;
    }
    return -1;
}*/

void CLyricViewLines::OnChildSetVisible(CLyricViewLine *lpViewLine, bool bVisible)
{
    ASSERT(lpViewLine >= m_pData);
    ASSERT(lpViewLine < (m_pData + m_nSize));

    int iLineIndex = ((LPBYTE) lpViewLine - (LPBYTE) m_pData) / sizeof(CLyricViewLine);
    int iIndex;

    ASSERT(&m_pData[iLineIndex] == lpViewLine);

    if(bVisible)
    {
        if(iLineIndex < m_iFirstVisible)
            m_iFirstVisible = iLineIndex;
        else if(iLineIndex > m_iLastVisible)
            m_iLastVisible = iLineIndex;
    }
    else
    {
        iIndex = iLineIndex;
        if(iIndex <= m_iFirstVisible)
        {
            while(!ElementAt(iIndex).GetVisible())
            {
                iIndex++;
                if(iIndex >= m_nSize)
                    break;
            }
            m_iFirstVisible = iIndex;
        }
        iIndex = iLineIndex;
        if(iIndex >= m_iLastVisible)
        {
            while(!ElementAt(iIndex).GetVisible())
            {
                iIndex--;
                if(iIndex < 0)
                    break;
            }
            m_iLastVisible = iIndex;
        }
    }

}

int CLyricViewLines::GetFirstVisibleLineIndex()
{
    return m_iFirstVisible;
}

int CLyricViewLines::GetLastVisibleLineIndex()
{
    return m_iLastVisible;
}

void CLyricViewLines::Prepare()
{
    for(int i = 0; i < m_nSize; i++)
    {
        CLyricViewLine &rline = ElementAt(i);
        rline.m_pContainer = this;
        rline.m_iLineIndex = i;
    }
    m_iLineIndex = -1;
}

void CLyricViewLines::Prepare(CLyricViewLine *lpViewLine)
{
    lpViewLine->m_pContainer = this;
}

void CLyricViewLines::SetForegroundDC(CDC *lpDC)
{
    for(int i = 0 ; i < GetSize(); i++)
    {
        ElementAt(i).SetForegroundDC(lpDC);
    }
}

void CLyricViewLines::SetBackgroundDC(CDC *lpDC)
{
    for(int i = 0 ; i < GetSize(); i++)
    {
        ElementAt(i).SetBackgroundDC(lpDC);
    }
}

void CLyricViewLines::SetEffect(int iEffect)
{
    for(int i = 0 ; i < GetSize(); i++)
    {
        ElementAt(i).SetTextEffect(iEffect);
    }

}

void CLyricViewLines::SetRenderWindow(CWnd * pWnd)
{
  //  for(int i = 0 ; i < GetSize(); i++)
    //{
//        ElementAt(i).SetRenderWindow(pWnd);
    //}
}

VMSRESULT CLyricViewLines::UpdateFalseVisibility(
        LPRECT lprectClient,
        CTypedPtrArray <CObArray, CBaseRgn *> * lprgna,
        int iPlayingTokenIndex,
        int iPlayingNoteIndex, 
        CLyricEventsV2 * pEvents,
	    CTypedPtrArray <CPtrArray, CXfplayerFont *> * pFonts)
{

        int i, iStartIndex, iEndIndex;
        int iStatus, iIndex;
        int iFirstEligibleIndex, iLastEligibleIndex;
        CDWArray dwa;
        CDWArray dwaCleared;
        CLyricViewLine * lpViewLine = NULL;

        // Calculates the first and the last line eligible for
        // true visiblity

        iFirstEligibleIndex = GetTokenLine(iPlayingTokenIndex, NULL);
        iStartIndex = iFirstEligibleIndex;
        if(iStartIndex < 0)
            iStartIndex = 0;
        iEndIndex = m_nSize - 1;
        iLastEligibleIndex = m_nSize;
        for(i = iStartIndex; i <= iEndIndex; i++)
		{
           lpViewLine = &ElementAt(i);
           if(dwa.HasItem(lpViewLine->m_iRelativeLineIndex))
           {
               iLastEligibleIndex = i - 1;
               break;
           }
           else
           {
                dwa.Add(lpViewLine->m_iRelativeLineIndex);
           }
		}

        // Calculates the first ans last visible lines

        iStartIndex = GetFirstVisibleLineIndex();
        if(iStartIndex < 0)
            iStartIndex = 0;
        if(iStartIndex >= GetSize())
            iStartIndex = GetSize() - 1;
        iEndIndex = GetLastVisibleLineIndex();
//        if(iEndIndex < iStartIndex)
  //          iEndIndex = iStartIndex;
        if(iEndIndex >= GetSize())
            iEndIndex = GetSize() - 1;

        // Clears A
        dwa.RemoveAll();
        dwaCleared.RemoveAll();
		for(i = iStartIndex; i <= iEndIndex; i++)
		{
           lpViewLine = &ElementAt(i);
           if(lpViewLine->GetVisible())
           {
			    iStatus = lpViewLine->GetStatus(iPlayingTokenIndex);
                if((i < iFirstEligibleIndex ||
                    i > iLastEligibleIndex ||
                    iStatus == CLyricViewLine::StatusPlayed ||
                    iStatus == CLyricViewLine::StatusClean) &&
                    !dwaCleared.HasItem(lpViewLine->m_iRelativeLineIndex))
			    {
                    lpViewLine->SetVisible(false);
                    lpViewLine->SetStatus(CLyricViewLine::StatusClean);
				    lpViewLine->RenderLyricLine(
					    lprectClient,
					    lprgna,
					    iPlayingTokenIndex,
					    iPlayingNoteIndex,
					    XFPLYR_LINE_RENDER_CLEAR,
					    NULL,
					    pFonts,
					    pEvents);
                    dwaCleared.Add(lpViewLine->m_iRelativeLineIndex);
    			}
           }
		}

        //TRACE(_T("m_lyricLines.GetFirstVisibleLineIndex() = %d\n"), iStartIndex);
/*        dwa.RemoveAll();
        dwaCleared.RemoveAll();
        iStartIndex = iFirstEligibleIndex;
        if(iStartIndex < 0)
            iStartIndex = 0;
        iEndIndex = iLastEligibleIndex;
        if(iEndIndex >= GetSize())
            iEndIndex = GetSize() - 1;
        bool bClear = false;
		for(i = iStartIndex; i <= iEndIndex; i++)
		{
           lpViewLine = &ElementAt(i);
           if(lpViewLine->GetVisible())
           {
                if(dwaCleared.HasItem(lpViewLine->m_iRelativeLineIndex))
			    {
                    if(dwa.HasItem(lpViewLine->m_iRelativeLineIndex))
                    {
				            lpViewLine->RenderLyricLine(
					            lprectClient,
					            lprgna,
					            iPlayingTokenIndex,
					            iPlayingNoteIndex,
					            XFPLYR_LINE_RENDER_FULL,
					            NULL,
					            pFonts,
					            pEvents);
                            break;
                        }
                    }
    			}
           } */
    return VMSR_SUCCESS;
}

VMSRESULT CLyricViewLines::UpdateTrueVisibility(
        LPRECT lprectClient,
        CTypedPtrArray <CObArray, CBaseRgn *> * lprgna,
        int iPlayingTokenIndex,
        int iPlayingNoteIndex, 
        CLyricEventsV2 * pEvents,
	    CTypedPtrArray <CPtrArray, CXfplayerFont *> * pFonts)
{

        int i, iStartIndex, iEndIndex;
        int iStatus, iIndex;
        int iFirstEligibleIndex, iLastEligibleIndex;
        CDWArray dwa;
        CLyricViewLine * lpViewLine = NULL;

        // Calculates the first and the last line eligible for
        // true visiblity

        iFirstEligibleIndex = GetTokenLine(iPlayingTokenIndex, NULL);

        // Calculates the first and the last line eligible for
        // true visiblity

       iFirstEligibleIndex = GetTokenLine(iPlayingTokenIndex, NULL);
       if(iFirstEligibleIndex >= 0)
       {
       lpViewLine = &ElementAt(iFirstEligibleIndex);
       if(!lpViewLine->GetVisible())
       {
			iStatus = lpViewLine->GetStatus(iPlayingTokenIndex);
            if(iStatus != CLyricViewLine::StatusPlayed &&
                iStatus != CLyricViewLine::StatusClean)
			{
                lpViewLine->SetVisible();
                lpViewLine->SetStatus(CLyricViewLine::StatusClean);
				lpViewLine->RenderLyricLine(
					lprectClient,
					lprgna,
					iPlayingTokenIndex,
					iPlayingNoteIndex,
					XFPLYR_LINE_RENDER_FULL,
					NULL,
					pFonts,
					pEvents);
    		}
       }
       }
        iStartIndex = iFirstEligibleIndex;
        if(iStartIndex < 0)
            iStartIndex = 0;
        iEndIndex = m_nSize - 1;
        iLastEligibleIndex = iEndIndex;
        for(i = iStartIndex; i <= iEndIndex; i++)
		{
           lpViewLine = &ElementAt(i);
           if(dwa.HasItem(lpViewLine->m_iRelativeLineIndex))
           {
               iLastEligibleIndex = i - 1;
               break;
           }
           else
           {
                dwa.Add(lpViewLine->m_iRelativeLineIndex);
           }
		}
        iStartIndex++;
        iEndIndex = iLastEligibleIndex;
	for(i = iStartIndex; i <= iEndIndex; i++)
	{
       lpViewLine = &ElementAt(i);
       if(lpViewLine->GetVisible())
       {
			iStatus = lpViewLine->GetStatus(iPlayingTokenIndex);
            if(lpViewLine->m_dFillRate != 0.0)
            {
                lpViewLine->m_dFillRate == 0.0;
                lpViewLine->SetStatus(CLyricViewLine::StatusNew);
				lpViewLine->RenderLyricLine(
					lprectClient,
					lprgna,
					iPlayingTokenIndex,
					iPlayingNoteIndex,
					XFPLYR_LINE_RENDER_UPDATE,
					NULL,
					pFonts,
					pEvents);
    		}
       }
	}
    return VMSR_SUCCESS;
}

VMSRESULT CLyricViewLines::Arrange(	LPRECT		lprect,
	CTypedPtrArray <CObArray, CBaseRgn *> * prgnaModified,
	int			iTokenIndex,
	int			iNoteIndex,
	int			*count,
	CTypedPtrArray <CPtrArray, CXfplayerFont *> * pFonts,
//	BOOL		bRecalcLayout,
	CLyricEventsV2 * pEvents)
{
    int iLineIndex;
    CLyricViewLine * lpviewline;
    iLineIndex = GetTokenLine(iTokenIndex, &lpviewline);

    if(iLineIndex < 0)
        iLineIndex = 0;

    if(m_iLineIndex != iLineIndex)
    {
        return BBArrange(iLineIndex,
            lprect,
				prgnaModified,
				iTokenIndex,
				iNoteIndex,
				count,
				pFonts,
				pEvents,
                0.0);
                
    }
    return VMSR_SUCCESS;

}

VMSRESULT CLyricViewLines::BBArrange(
    int iLineIndex,
    LPRECT		lprect,
	CTypedPtrArray <CObArray, CBaseRgn *> * prgnaModified,
	int			iTokenIndex,
	int			iNoteIndex,
	int			*count,
	CTypedPtrArray <CPtrArray, CXfplayerFont *> * pFonts,
//	BOOL		bRecalcLayout,
	CLyricEventsV2 * pEvents,
    double dRate)
{
//    if(m_iLineIndex == iLineIndex)
  //      return VMSR_SUCCESS;

    m_iLineIndex = iLineIndex;
    
    CLyricViewLineTemplates * lpvlts = ElementAt(0).GetTemplate()->GetContainer();

    for(int i = 0; i < lpvlts->GetSize(); i++)
    {
        CLyricViewLineTemplate & lvlt = lpvlts->ElementAt(i);
        CRect rect;
        lvlt.GetPlacement_(rect);
        lvlt.m_ptTextOffset.y = - dRate * rect.Height();
        lvlt.m_etom = lvlt.m_bFirstLine ? lvlt.tomClip : lvlt.tomNoClip;
    }

/*    for(int i = 0; i < iLineIndex; i++)
    {
        CLyricViewLine & rvl = ElementAt(i);
        if(rvl.GetVisible())
        {
            rvl.SetVisible(false);
            rvl.RenderLyricLine(
                   	lprect,
					prgnaModified,
					iTokenIndex,
					iNoteIndex,
					XFPLYR_LINE_RENDER_CLEAR,
					count,
					pFonts,
					pEvents);

        }
    }
    for(i = iLineIndex + lpvlts->GetSize(); i < GetSize(); i++)
    {
        CLyricViewLine & rvl = ElementAt(i);
        if(rvl.GetVisible())
        {
            rvl.SetVisible(false);
            rvl.RenderLyricLine(
                   	lprect,
					prgnaModified,
					iTokenIndex,
					iNoteIndex,
					XFPLYR_LINE_RENDER_CLEAR,
					count,
					pFonts,
					pEvents);
        }
    }*/

    int iStartIndex;
    int iEndIndex;

    iStartIndex = GetFirstVisibleLineIndex();
    if(iStartIndex < 0)
        iStartIndex = 0;
    if(iStartIndex >= GetSize())
        iStartIndex = GetSize() - 1;
    iEndIndex = GetLastVisibleLineIndex();
//        if(iEndIndex < iStartIndex)
//          iEndIndex = iStartIndex;
    if(iEndIndex >= GetSize())
        iEndIndex = GetSize() - 1;

    for(i = iStartIndex; i <= iEndIndex; i++)
    {
        CLyricViewLine & rvl = ElementAt(i);
        if(rvl.GetVisible())
        {
            rvl.SetVisible(false);
            rvl.RenderLyricLine(
                   	lprect,
					prgnaModified,
					iTokenIndex,
					iNoteIndex,
					XFPLYR_LINE_RENDER_CLEAR,
					count,
					pFonts,
					pEvents);

        }
    }

    int iSize = lpvlts->GetSize();

    if(iLineIndex + iSize > GetSize())
        iSize = GetSize() - iLineIndex;

    for(i = 0; i < iSize; i++)
    {
//        if(iLineIndex + i
        CLyricViewLine & rvl = ElementAt(iLineIndex + i);
        rvl.SetTemplate(&lpvlts->ElementAt(i));
//        rvl.SetStatus(rvl.StatusNew);
//        if(!rvl.GetVisible())
  //      {
            rvl.SetVisible();
            rvl.RenderLyricLine(
                lprect,
				prgnaModified,
				iTokenIndex,
				iNoteIndex,
				XFPLYR_LINE_RENDER_FULL,
				count,
				pFonts,
				pEvents);
    //    }
    }
    return VMSR_SUCCESS;
}

void CLyricViewLines::GetTokenX(
    int iTokenIndex,
    double * pdLeft,
    double * pdRight)
{
    int iLineIndex;
    CLyricViewLine * lpviewline;
    while(true)
    {
        if(0 <= (iLineIndex =
            GetTokenLine(iTokenIndex, &lpviewline)))
        {
            if(lpviewline->
                m_iaTokensCharsLengths.
                ElementAt(iTokenIndex -
                lpviewline->m_iStartTokenIndex)==0)
            {
                iTokenIndex++;
            }
            else
            {
                lpviewline->GetTokenX(iTokenIndex, pdLeft, pdRight);
                return;
            }

        }
        else
        {
            break;
        }
    }
    *pdLeft = 0.0;
    *pdRight = 0.0;
    return;
}
