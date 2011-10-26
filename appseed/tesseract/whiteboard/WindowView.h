#pragma once



#include "BitmapButtonEx.h"



// WindowView form view

class _declspec(dllexport) WindowView : public BaseFormView
{
	DECLARE_DYNCREATE(WindowView)

protected:
	WindowView();           // protected constructor used by dynamic creation
	virtual ~WindowView();

public:
	enum { IDD = IDD_WINDOW };
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
   CPoint         m_ptMoveStart;
   CRect          m_rectMoveStart;
   bool           m_bLButtonPressed;
   CBrush         m_brushBkNormal;
   CBrush         m_brushBkSysPressed;
   bool           m_bSysPressed;
//   CBitmapButtonEx m_buttonClose;
//   CBitmapButtonEx m_buttonExpandCollapse;
   void UpdateButtons(void);
   afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
   virtual void OnInitialUpdate();
   afx_msg void OnBnClickedExpandRetract();
   afx_msg void OnBnClickedClose();
   afx_msg void OnSetFocus(base_wnd* pOldWnd);
protected:
   virtual void OnUpdate(BaseView* /*pSender*/, LPARAM /*lHint*/, base_object* /*pHint*/);
public:
   afx_msg void OnSize(UINT nType, int cx, int cy);
   afx_msg HBRUSH OnCtlColor(CDC* pDC, base_wnd* pWnd, UINT nCtlColor);
   afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
   afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
   afx_msg void OnMouseMove(UINT nFlags, CPoint point);
   void Move();
   afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
   void ToggleExpandRetract(void);
};


