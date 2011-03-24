// XfplayerViewLines.cpp: implementation of the CXfplayerViewLines class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "VMSApp.h"
#include "XfplayerViewLines.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CXfplayerViewLines::CXfplayerViewLines()
:CArray<CXfplayerViewLine, CXfplayerViewLine &>()
{
    m_iFirstVisible = -1;
    m_iLastVisible = -1;
}

CXfplayerViewLines::~CXfplayerViewLines()
{
//    CArray<CXfplayerViewLine, CXfplayerViewLine &>::~CArray<CXfplayerViewLine, CXfplayerViewLine &>();
}



void CXfplayerViewLines::OnChildSetVisible(CXfplayerViewLine *lpViewLine, bool bVisible)
{
    ASSERT(lpViewLine >= m_pData);
    ASSERT(lpViewLine < (m_pData + m_nSize));

    int iLineIndex = ((LPBYTE) lpViewLine - (LPBYTE) m_pData) / sizeof(CXfplayerViewLine);
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
            while(!ElementAt(iIndex).IsVisible())
            {
                iIndex++;
                if(iIndex >= m_nSize)
                    break;
            }
        m_iFirstVisible = iIndex;
        iIndex = iLineIndex;
        if(iIndex <= m_iLastVisible)
            while(!ElementAt(iIndex).IsVisible())
            {
                iIndex--;
                if(iIndex < 0)
                    break;
            }
        m_iLastVisible = iIndex;
    }

}

int CXfplayerViewLines::GetFirstVisibleLineIndex()
{
    return m_iFirstVisible;
}

int CXfplayerViewLines::GetLastVisibleLineIndex()
{
    return m_iLastVisible;
}

void CXfplayerViewLines::Prepare()
{
    for(int i = 0; i < m_nSize; i++)
    {
        ElementAt(i).m_pContainer = this;
    }
}

void CXfplayerViewLines::Prepare(CXfplayerViewLine *lpViewLine)
{
    lpViewLine->m_pContainer = this;
}

/*void CXfplayerViewLines::SetForegroundDC(CDC *lpDC)
{
    for(int i = 0 ; i < GetSize(); i++)
    {
        ElementAt(i).SetForegroundDC(lpDC);
    }
}*/
void CXfplayerViewLines::SetTwi(CTransparentWndInterface *lptwi)
{
    for(int i = 0 ; i < GetSize(); i++)
    {
        ElementAt(i).SetTwi(lptwi);
    }
}


void CXfplayerViewLines::SetEffect(int iEffect)
{
    for(int i = 0 ; i < GetSize(); i++)
    {
        ElementAt(i).SetTextEffect(iEffect);
    }

}

void CXfplayerViewLines::SetRenderWindow(CWnd * pWnd)
{
  //  for(int i = 0 ; i < GetSize(); i++)
    //{
//        ElementAt(i).SetRenderWindow(pWnd);
    //}
}
