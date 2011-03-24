// LyricViewLineTemplates.cpp: implementation of the CLyricViewLineTemplates class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "VMSApp.h"
#include "LyricViewLineTemplates.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLyricViewLineTemplates::CLyricViewLineTemplates()
:CBaseArray<CLyricViewLineTemplate, CLyricViewLineTemplate &>()
{
    m_iFirstVisible = -1;
    m_iLastVisible = -1;
}

CLyricViewLineTemplates::~CLyricViewLineTemplates()
{
//    CArray<CLyricViewLineTemplate, CLyricViewLineTemplate &>::~CArray<CLyricViewLineTemplate, CLyricViewLineTemplate &>();
}

/*int CLyricViewLineTemplates::GetTokenLine(int iToken, CLyricViewLineTemplate ** viewLine)
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
	*viewLine = &operator[](iIndex);
	return iIndex;
} */

/*int CLyricViewLineTemplates::GetAt(CLyricViewLineTemplate * * pViewLine, CLyricViewLineTemplates &viewLines, int iIndex)
{
    int iLineIndex = viewLines.ElementAt(iIndex).m_iRelativeLineIndex;
    if(iLineIndex >= 0 &&
        iLineIndex < m_nSize)
    {
        *pViewLine = &ElementAt(iLineIndex);
        return iLineIndex;
    }
    return -1;
} */

/*void CLyricViewLineTemplates::OnChildSetVisible(CLyricViewLineTemplate *lpViewLine, bool bVisible)
{
    ASSERT(lpViewLine >= m_pData);
    ASSERT(lpViewLine < (m_pData + m_nSize));

    int iLineIndex = ((LPBYTE) lpViewLine - (LPBYTE) m_pData) / sizeof(CLyricViewLineTemplate);
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
        if(iIndex >= m_iFirstVisible)
            while(!ElementAt(iIndex).GetVisible())
            {
                iIndex++;
                if(iIndex >= m_nSize)
                    break;
            }
        m_iFirstVisible = iIndex;
        iIndex = iLineIndex;
        if(iIndex <= m_iLastVisible)
            while(!ElementAt(iIndex).GetVisible())
            {
                iIndex--;
                if(iIndex < 0)
                    break;
            }
        m_iLastVisible = iIndex;
    }

}*/

/*int CLyricViewLineTemplates::GetFirstVisibleLineIndex()
{
    return m_iFirstVisible;
}

int CLyricViewLineTemplates::GetLastVisibleLineIndex()
{
    return m_iLastVisible;
}*/

void CLyricViewLineTemplates::Prepare()
{
    for(int i = 0; i < m_nSize; i++)
    {
        ElementAt(i).m_pContainer = this;
    }
}

void CLyricViewLineTemplates::Prepare(CLyricViewLineTemplate *lpViewLine)
{
    lpViewLine->m_pContainer = this;
}

/*void CLyricViewLineTemplates::SetForegroundDC(CDC *lpDC)
{
    for(int i = 0 ; i < GetSize(); i++)
    {
        ElementAt(i).SetForegroundDC(lpDC);
    }
}

void CLyricViewLineTemplates::SetBackgroundDC(CDC *lpDC)
{
    for(int i = 0 ; i < GetSize(); i++)
    {
        ElementAt(i).SetBackgroundDC(lpDC);
    }
}

void CLyricViewLineTemplates::SetEffect(int iEffect)
{
    for(int i = 0 ; i < GetSize(); i++)
    {
        ElementAt(i).SetTextEffect(iEffect);
    }

}

void CLyricViewLineTemplates::SetRenderWindow(CWnd * pWnd)
{
    for(int i = 0 ; i < GetSize(); i++)
    {
        ElementAt(i).SetRenderWindow(pWnd);
    }
}*/
