// LyricViewLineTemplate.cpp: implementation of the CLyricViewLineTemplate class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "VMSApp.h"
#include "LyricViewLineTemplate.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLyricViewLineTemplate::CLyricViewLineTemplate()
: m_ptTextOffset(0, 0)
{

}

CLyricViewLineTemplate::~CLyricViewLineTemplate()
{

}

int CLyricViewLineTemplate::SetPens(CPen * ppenLeft, CPen * ppenRight)
{
    m_ppenLeft = ppenLeft;
    m_ppenRight = ppenRight;

	LOGPEN leftLogPen;
	LOGPEN rightLogPen;
	
    m_ppenLeft->GetLogPen(&leftLogPen);
    m_ppenRight->GetLogPen(&rightLogPen);
	
    int cx = max(
		leftLogPen.lopnWidth.x,
		rightLogPen.lopnWidth.x);
	
    int cy = max(
		leftLogPen.lopnWidth.y,
		rightLogPen.lopnWidth.y );
	
    cx = cx / 2 + cx % 2;
    cy = cy / 2 + cy % 2;
    
    m_sizeMargin.cx = cx;
    m_sizeMargin.cy = cy;

    return true;
}

int CLyricViewLineTemplate::SetColors(COLORREF crLeft, COLORREF crRight)
{
    m_crLeft = crLeft;
    m_crRight = crRight;
    return true;

}

void CLyricViewLineTemplate::GetPlacement_(LPRECT lpRect)
{
    *lpRect = m_rectPlacement;

}

void CLyricViewLineTemplate::GetMargin(SIZE *lpSize)
{
    *lpSize = m_sizeMargin;
}

void CLyricViewLineTemplate::GetPens(CPen **pppenLeft, CPen **pppenRight)
{
    *pppenLeft = m_ppenLeft;
    *pppenRight = m_ppenRight;
}

void CLyricViewLineTemplate::GetColors(COLORREF &crLeft, COLORREF &crRight)
{
    crLeft = m_crLeft;
    crRight = m_crRight;

}

void CLyricViewLineTemplate::SetPlacement_(LPRECT lpRect)
{
    m_rectPlacement = *lpRect;
}

CLyricViewLineTemplates * CLyricViewLineTemplate::GetContainer()
{
    return m_pContainer;
}
