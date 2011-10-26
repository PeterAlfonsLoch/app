#pragma once

#include "Element2D.h"
#include "TextInterface.h"

namespace devedge
{

class CLASS_DECL_CA2_DEVEDGE PlainTextBox : 
	public Element2D, 
	public TextInterface
	
{
public:
	PlainTextBox();
	int			m_iSelStart;
	int			m_iSelEnd;
	int			m_iViewOffset; // in bytes
	int			m_iViewSize; // in bytes
   int         m_iLineHeight;
   int         m_iColumn;

   // Used for whatever it can make faster for large files (scroll for example)
   // keep each line size
   BaseIntArray m_iaLineIndex; 
   // Used for whatever it can make faster for large files (scroll for example)
   // keep each line end flag 3 = \r \n     1 = \n  \r = 2
   BaseIntArray m_iaLineEndIndex;
   BaseIntArray m_iaCLineIndex; 
   Ex1EditFile m_editfile;


	CFont *		m_pfont;

   BaseMap < int, int, int, int> m_imapAbnt;

	bool		m_bMouseDown;
	point		m_ptSelStart;
   bool        m_bFocus;
   bool        m_bCaretOn;
   DWORD       m_dwLastCaret;
   DWORD       m_dwCaretTime;
   int         m_iLineOffset;
   AStrArray   m_straSep;
   AStrArray   m_straLines;
   int         m_y;
   bool        m_bGetTextNeedUpdate;
   void _001OnKeyboardFocusTimer(devedgeView * pview, int iTimer);

   void OnUpdate();

	int char_hit_test(devedgeView * pview, CDC * pdc, int x, int y);

	virtual void _001OnDraw(devedgeView * pview, CDC * pdc);
	void _001GetSelText(string & str);

   void _001OnGetText(devedgeView * pview);
	void _001GetViewText(devedgeView * pview, string & str);
	void _001GetViewSel(int &iSelStart, int &iSelEnd);

	void _001OnLButtonDown(devedgeView * pview, gen::signal_object * pobj);
	void _001OnLButtonUp(devedgeView * pview, gen::signal_object * pobj);
   void _001OnCalcLayout(devedgeView * pview, CDC * pdc);
   void _001OnMouseMove(devedgeView * pview, gen::signal_object * pobj);
   void _001OnChar(devedgeView * pview, gen::signal_object * pobj);
   void _001OnSysChar(devedgeView * pview, gen::signal_object * pobj);
   void _001OnCalcLayoutProc(devedgeView * pview, CDC * pdc);

   void SetFile(Ex1File * pfile);
   void OnFileUpdate();
   void CreateLineIndex();

   int SelToColumn(devedgeView * pview, int iSel);
   int SelToLine(devedgeView * pview, int iSel);
   int LineColumnToSel(devedgeView * pview, int iLine, int iColumn);

   void OneLineUp(devedgeView * pview);

   void IndexRegisterDelete(int iSel, int iCount);
   void IndexRegisterInsert(int iSel, LPCTSTR lpcszWhat);

protected:

	
};

} // namespace devedge