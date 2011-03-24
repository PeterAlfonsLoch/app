// LyricViewLine.h: interface for the CLyricViewLine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LYRICVIEWLINE_H__C47CD06B_A337_435B_9B6A_3AD30FDFB8A5__INCLUDED_)
#define AFX_LYRICVIEWLINE_H__C47CD06B_A337_435B_9B6A_3AD30FDFB8A5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "XfplayerFont.h"
#include "xf.h"

#include "BaseRgn.h"

class CLyricViewLines;
class CLyricViewLineTemplate;
class CLyricEventsV2;

class CLyricViewLine  
{
    friend class CLyricViewLines;

public:
public:
	enum CharStates
	{
		CharStateNew = 1,
		CharStateInitial = 2,
		CharStatePlaying = 3,
		CharStatePlayed = 4
	};
    enum
    {
        StatusEmpty = 12,
        StatusPrepared = 24,
        StatusNew  = 36,
        StatusPlaying = 48,
        StatusPlayed = 60,
        StatusClean = 72
    };
    enum Animates
    {
        AnimateNoAnimate = 0,
        AnimateRHL = 1 // Rotates Horizontally Left
    };

    enum Effects
    {
        EffectSimple = 0,
        EffectEmbossed = 1
    };
//    enum RedrawModes
  //  {
    //    RedrawNoRedraw = 1,
      //  RedrawDoRedraw = 2
    //};
	CLyricViewLine();
    CLyricViewLine(CLyricViewLines * pContainer);
	virtual ~CLyricViewLine();
	LPBYTE				m_lpBitmapData;

// Attributes
private:
    CLyricViewLines * m_pContainer;
	int					m_iStatus;
protected:
    //class rect               m_rectPlacement;
public:
protected:
    int                 m_iAnimateType;
    double              m_dAnimateProgress;
    double              m_dAnimateProgressIncrement;
    int                 m_iTextEffect;
    CDC *               m_lpForegroundDC;
    CDC *               m_lpBackgroundDC;
    CPen *              m_lpPenEmboss;
    COLORREF            m_crForeground;
    CTypedPtrArray <CPtrArray, CXfplayerFont *>  m_fonts;
//    bool                m_bPendingFullUpdate;
//    bool                m_bPendingUpdate;
    //int                 m_iRedrawMode;
//    base_wnd *                m_pRenderWnd;
    //CRgn                m_rgnModified;
    CLyricViewLineTemplate * m_ptemplate;
    //CCriticalSection    m_pcsRender;
public:
	//char *				m_chars;
	//LPTSTR				m_chars;
    string             m_chars;
	//LPBYTE				m_lpbCharsStates;
    CDWordArray         m_dwaCharsStates;
	BaseArray<int, int>    m_iaCharsPositions;
	BaseArray<int, int>    m_iaTokensFirstCharIndexes;
	BaseArray<int, int>	m_iaTokensCharsLengths;
//	CDWordArray			m_notesPositions;
//	CDWordArray			m_notesDurations;
//	CDWordArray			m_tokensFirstNoteIndexes;
//	CDWordArray			m_tokensNotesLengths;
	int					m_iTokensCount;
	int					m_iStartTokenIndex;
	int					m_iNotesLength;
//	int					m_iStartNoteIndex;
//	int					m_charsLength;
//	int					m_iTop;
//	int					m_iLeft;
//	int					m_iRight;
//	int					m_iBottom;
	int					m_iIndent;
	double				m_dFillRate;
	BOOL				m_bFirstLine;
	int					m_nFont;
	int					m_iMiddle;
	int					m_iLastMiddle;
//	DWORD				m_dwEmptyTime;
    DWORD               m_dwCleanTime;
	DWORD				m_dwNewTime;
    int                 m_iLineIndex;
    int                 m_iRelativeLineIndex;
    bool                m_bPendingLayoutUpdate;
    bool                m_bVisible;
		bool		m_bAutoSizeX;
        bool		m_bAutoSizeY;
		class rect		m_rectPrevious;
		int			m_iAlign;
    class rect               m_rectClient;
public:
	bool GetTokenText(string * lpstr);
	void SetPlacement(LPRECT lprect);
	void GetPlacement(LPRECT lprect);
	CLyricViewLines * GetContainer();
	void GetTokenX(int iTokenIndex, double * pdLeft, double * pdRight);
	void SetTemplate(CLyricViewLineTemplate * pTemplate);
	CLyricViewLineTemplate * GetTemplate();
//	int SetLyricColors(COLORREF crLeft, COLORREF crRight);
//	int SetLyricPens(CPen * ppenLeft, CPen * ppenRight);
//	void SetRenderCriticalSection(CCriticalSection *pcs);
//	void SetRenderWindow(base_wnd * pWnd);
	//void SetRedrawMode(int iMode);
	void SetAnimateIncrement(double dIncrement);
	int MapToFontEffect(int iLineEffect);
    CTypedPtrArray <CPtrArray, CXfplayerFont *> * GetFonts();
	void SetForegroundColor(COLORREF cr);
	void SetEmbossPen(CPen * lpPen);
	void SetBackgroundDC(CDC * pDC);
	void SetForegroundDC(CDC * pDC);
	void SetTextEffect(int iTextEffect);
	void SetAnimateType(int iAnimateType);
	void OnTimerAnimate(CRgn * pModifiedRgn);
	bool GetVisible();
	void SetVisible(bool bVisible = true);
	void SetNewTime();
	void SetPlayingStatus(int iPlayingTokenIndex);
	void SetPendingLayoutUpdate(bool bPending = true);
	int GetLastToken();
	int GetFirstToken();
    virtual operator =(CLyricViewLine & src);
//	void GetRect(LPRECT lpRect);
//	void SetRect(LPRECT lpRect);
	void SetAlign(int iAlign);
	static const int AlignLeft;
	static const int AlignRight;

	void SetAutoSize(bool bAutoSize);
	
    static void GetNoteFillRate(
		int iPlayingNoteIndex,
		int iNoteIndex,
		CLyricEventsV2 * pEvents,
		double * drFull,
		double * drPartial);

	bool IsNewTimedOut();
	//bool IsEmptyTimedOut();
    bool IsCleanTimedOut();
	//BOOL IsEmptyTimedOut();
	void CalcCharsPositions(
		CTypedPtrArray <CPtrArray, CXfplayerFont *> * pFonts,
		LPRECT pRect);
	void CalcCharsPositions(
		CXfplayerFont * pFont,
		LPRECT pRect);

	void CalcNotesPositions(
		CLyricEventsV2 * pEvents);
	void UpdateFillRate(double msElapsed, double msLength);
	void Reset();
	void SetStatus(int iStatus);
	int GetStatus(int iPlayingIndex);

// Operations
	XFPLYR_LINE_RESULT PrepareLyricLine(
		AStrArray *pTokens,
		int tokenIndex,
		int *nextTokenIndex,
		int flags,
		CTypedPtrArray <CPtrArray, CXfplayerFont *> * pFonts,
		LPRECT pRect,
		CLyricEventsV2 * pEvents);
	XFPLYR_LINE_RESULT PrepareLine(
		LPCTSTR lpcsz,
		int flags,
		CTypedPtrArray <CPtrArray, CXfplayerFont *> *pFonts,
		LPRECT pRect);
	XFPLYR_LINE_RESULT PrepareLine(
		LPCTSTR lpcsz,
		int flags,
		CXfplayerFont *pFont,
		LPRECT pRect);
	//void InsertChar(HDC hDC, char ch, int *xOffset, int &index);
	void AddChar(	
		TCHAR ch,
		int &index);
	void AddChar(
		TCHAR ch,
		int &index,
		CXfplayerFont * pFont);
	void AddToken(
		int firstCharIndex,
		int charsLength,
		int &index);
	XFPLYR_LINE_RESULT RenderLyricLine(
		LPRECT lpRect,
		CTypedPtrArray <CObArray, CBaseRgn *> * prgnaModified,
		int iPlayingTokenIndex,
		int iPlayingNoteIndex,
		int iMode, int *count,
		CTypedPtrArray <CPtrArray, CXfplayerFont *> * pFonts,
//		BOOL bRecalcLayout,
		CLyricEventsV2 * pEvents);
//        bool        bRedraw);
	
	XFPLYR_LINE_RESULT CLyricViewLine::RenderLine(
		LPRECT		lpRect,
		CRgn *		pModifiedRgn,
		int			iMode,
		int			*count,
		CXfplayerFont * pFont,
		bool		bRecalcLayout,
		COLORREF	crColor,
		CPen		&pen);

	XFPLYR_LINE_RESULT CLyricViewLine::RenderLine(
		LPRECT		lpRect,
		CRgn *		pModifiedRgn,
		int			iMode,
		int			*count,
		CTypedPtrArray <CPtrArray, CXfplayerFont *> * pFonts,
		bool		bRecalcLayout,
		COLORREF	crColor,
		CPen		&pen);


	BOOL ContainsToken(int iTokenIndex)
	{
		if(m_iStartTokenIndex >= 0)
		{
			int iDelta = iTokenIndex - m_iStartTokenIndex;
			return (iDelta >= 0) && (iDelta < m_iTokensCount);
		}
		else
		{
			return FALSE;
		}
	}
	void SetPlayingToken(int iIndex);
	

};

#endif // !defined(AFX_LYRICVIEWLINE_H__C47CD06B_A337_435B_9B6A_3AD30FDFB8A5__INCLUDED_)
