// XfplayerViewLine.h: interface for the CXfplayerViewLine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XFPLAYERVIEWLINE_H__FBA8401D_7B87_41E7_B0B8_1E66788441DC__INCLUDED_)
#define AFX_XFPLAYERVIEWLINE_H__FBA8401D_7B87_41E7_B0B8_1E66788441DC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include <afxtempl.h> 
//#include "xf.h"
#include "xfplayerfont.h"
#include "BaseRgn.h"
#include "WStr.h"

class CLyricEventsV2;
class CTransparentWndInterface;
class CXfplayerViewLines;
class CBaseRgnPtrArray;

class CXfplayerViewLine  
{
public:
   enum EAnimate
   {
      AnimateNoAnimate = 0,
      AnimateRHL = 1 // Rotates Horizontally Left
   };
   
   enum EEffect
   {
      EffectSimple = 0,
      EffectEmbossed = 1
   };
   CXfplayerViewLine();
   CXfplayerViewLine(CXfplayerViewLines * pContainer);
   virtual ~CXfplayerViewLine();
   LPBYTE				m_lpBitmapData;

// Attributes
private:
   friend class CXfplayerViewLines;
   CXfplayerViewLines * m_pContainer;
protected:
   int                  m_nFont;
   CRect                m_rectInvalidate;
   int                  m_iAnimateType;
   double               m_dAnimateProgress;
   double               m_dAnimateProgressIncrement;
   int                  m_iTextEffect;
   CTransparentWndInterface * m_ptwi_;
   CPen *               m_lpPenEmboss;
   COLORREF             m_crForeground;
   CTypedPtrArray <CPtrArray, CVmsGdiFont *>  m_fonts;
   CPen *               m_ppenLyricLeft;
   CPen *               m_ppenLyricRight;
   CSize                m_sizeLyricMargin;
   COLORREF             m_crLyricLeft;
   COLORREF             m_crLyricRight;
public:
	bool IsVisible();
	void Validate(LPCRECT lpcrect = NULL);
	void Invalidate(LPCRECT lpcrect = NULL);
	void AddVmsFont(CVmsGdiFont * pfont);
	int GetVmsFontCount();
	void SetPlacement(LPCRECT lpcrect);
	int SetLyricColors(COLORREF crLeft, COLORREF crRight);
	int SetLyricPens(CPen * ppenLeft, CPen * ppenRight);
	void SetRenderCriticalSection(CCriticalSection *pcs);
	void SetAnimateIncrement(double dIncrement);
	int MapToFontEffect(int iLineEffect);
    
	
	CTypedPtrArray <CPtrArray, CVmsGdiFont *> *
		GetFonts();

	void SetForegroundColor(COLORREF cr);
	void SetEmbossPen(CPen * lpPen);
   void SetTwi(CTransparentWndInterface * pTwi);
	void SetTextEffect(int iTextEffect);

	void SetAnimateType(int iAnimateType);

	void OnTimerAnimate(
      CDC *				pdcForeground,
      CDC *				pdcBackground,
      CBaseRectArray &	rectaModified);

	void Show(bool bShow = true);
   virtual operator =(CXfplayerViewLine & src);
	void GetRect(LPRECT lpRect);
	void SetRect(LPRECT lpRect);
	void SetAlign(int iAlign);
	static const int AlignLeft;
	static const int AlignRight;

	void SetAutoSize(bool bAutoSize);

	void CalcCharsPositions(
      CDC * pdcForeground,
      CTypedPtrArray <CPtrArray, CVmsGdiFont *> *
      pFonts,
      LPCRECT lpcrect);

	void CalcCharsPositions(
      CDC * pdcForeground,
      CVmsGdiFont * pFont,
      LPCRECT lpcrect);

   CWStr       m_wstr;
	CBaseArray<int, int>    m_iaPosition;
	int			m_iTop;
	int			m_iLeft;
	int			m_iIndent;
	int			m_iRight;
	int			m_iBottom;
   bool        m_bPendingLayoutUpdate;
   bool        m_bVisible;
   bool		   m_bAutoSizeX;
   bool		   m_bAutoSizeY;
   int			m_iAlign;

// Operations
	
	bool PrepareLine(
      CDC * pdcForeground,
      LPCWSTR lpcsz,
      int flags,
      CTypedPtrArray <CPtrArray, CVmsGdiFont *> *pFonts,
      LPRECT pRect);

	bool PrepareLine(
      CDC * pdcForeground,
      LPCWSTR lpcsz,
      int flags,
      CVmsGdiFont *pFont,
      LPRECT pRect);

	void GetPlacement(LPRECT lprect);

	void AddChar(	
		WCHAR wch,
		int &index);

	void AddChar(
		WCHAR wch,
		int &index,
		CVmsGdiFont * pFont);
	
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
		CPen		&			pen);

	bool CXfplayerViewLine::Render(
      CDC *					pdcForeground,
      CDC *					pdcBackground,
      bool					bDraw,
      LPRECT					lpRect,
      CBaseRectArray &		rectaModified,
      int	*					count,
      CTypedPtrArray <CPtrArray, CVmsGdiFont *> * pFonts,
      bool					bRecalcLayout,
      COLORREF				crColor,
      CPen		&			pen);


	

};

#endif // !defined(AFX_XFPLAYERVIEWLINE_H__FBA8401D_7B87_41E7_B0B8_1E66788441DC__INCLUDED_)
