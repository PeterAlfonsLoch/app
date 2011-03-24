// LyricViewLines.h: interface for the CLyricViewLines class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LYRICVIEWLINES_H__CB5FA9A4_6490_4567_BCF9_46336DBC9650__INCLUDED_)
#define AFX_LYRICVIEWLINES_H__CB5FA9A4_6490_4567_BCF9_46336DBC9650__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseArray.h" 
#include "LyricViewLine.h" 
#include "VMS_.H"	// Added by ClassView

//class CLyricEventsV2;


class CLyricViewLines  : public BaseArray < CLyricViewLine, CLyricViewLine &>
{
public:
	CLyricViewLines();
	virtual ~CLyricViewLines();
public:
    CXfplayerViewLines();
//    inline CXfplayerViewLine & ElementAt(int iIndex);
protected:
    int     m_iFirstVisible;
    int     m_iLastVisible;
    int     m_iLineIndex;
public:

	void GetTokenX(
        int iTokenIndex,
        double * pdLeft,
        double * pdRight);

	VMSRESULT BBArrange(int iLineIndex,
        	LPRECT		lpRect,
	CTypedPtrArray <CObArray, CBaseRgn *> * prgnaModified,
	int			iPlayingTokenIndex,
	int			iPlayingNoteIndex,
	int			*count,
	CTypedPtrArray <CPtrArray, CXfplayerFont *> * pFonts,
//	BOOL		bRecalcLayout,
	CLyricEventsV2 * pEvents,
    double dRate);

    VMSRESULT Arrange(
        	LPRECT		lpRect,
	CTypedPtrArray <CObArray, CBaseRgn *> * prgnaModified,
	int			iPlayingTokenIndex,
	int			iPlayingNoteIndex,
	int			*count,
	CTypedPtrArray <CPtrArray, CXfplayerFont *> * pFonts,
//	BOOL		bRecalcLayout,
	CLyricEventsV2 * pEvents);

	VMSRESULT UpdateFalseVisibility(
        LPRECT lprectClient,
        CTypedPtrArray <CObArray, CBaseRgn *> * lprgna,
        int iPlayingTokenIndex,
        int iPlayingNoteIndex,
        CLyricEventsV2 * pEvents,
	    CTypedPtrArray <CPtrArray, CXfplayerFont *> * pFonts);
	VMSRESULT UpdateTrueVisibility(
        LPRECT lprectClient,
        CTypedPtrArray <CObArray, CBaseRgn *> * lprgna,
        int iPlayingTokenIndex,
        int iPlayingNoteIndex,
        CLyricEventsV2 * pEvents,
	    CTypedPtrArray <CPtrArray, CXfplayerFont *> * pFonts);
	void SetRenderWindow(base_wnd * pWnd);
	void SetEffect(int iEffect);
	void SetBackgroundDC(CDC * lpDC);
	void SetForegroundDC(CDC * lpDC);
	void Prepare(CLyricViewLine * lpViewLine);
	void Prepare();
    
	int GetFirstVisibleLineIndex();
    int GetLastVisibleLineIndex();
	void OnChildSetVisible(CLyricViewLine * lpViewLine, bool bVisible);
//	int GetAt(CXfplayerViewLine ** pViewLine, CXfplayerViewLines & viewLines, int iIndex);
	int GetTokenLine(int iToken, CLyricViewLine ** viewLine);
	

};

#endif // !defined(AFX_LYRICVIEWLINES_H__CB5FA9A4_6490_4567_BCF9_46336DBC9650__INCLUDED_)
