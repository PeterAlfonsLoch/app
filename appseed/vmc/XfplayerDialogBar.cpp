// XfplayerDialogBar.cpp : implementation file
//

#include "stdafx.h"
#include "../vms/Vms.h"
#include "../vmsp/resource.h"
#include "XfplayerDialogBar.h"

CXfplayerDialogBar::CXfplayerDialogBar()
	: CDialogBar()
{
	//{{AFX_DATA_INIT(CXfplayerDialogBar)
	//}}AFX_DATA_INIT
	m_bSliderPressed = FALSE;
}


void CXfplayerDialogBar::DoDataExchange(CDataExchange* pDX)
{
	CDialogBar::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CXfplayerDialogBar)
	//}}AFX_DATA_MAP
}

/*
BEGIN_MESSAGE_MAP(CXfplayerDialogBar, CDialogBar)
	//{{AFX_MSG_MAP(CXfplayerDialogBar)
	ON_WM_HSCROLL()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/

/////////////////////////////////////////////////////////////////////////////
// CXfplayerDialogBar message handlers

/*void CXfplayerDialogBar::SetSliderPos(double rate)
{
	if(!m_bSliderPressed)
	{
		CSliderCtrl *pSlider = GetSliderCtrl();
		if(pSlider)
		{
			if(rate > 1.0)
				rate = 1.0;
			if(rate < 0.0)
				rate = 0.0;
			int iMin = pSlider->GetRangeMin();
			int iMax = pSlider->GetRangeMax();
			pSlider->SetPos((int) (((iMax - iMin) * rate) + iMin));
		}
	}
}*/

void CXfplayerDialogBar::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
/*	if(pScrollBar->GetDlgCtrlID() == IDC_SLIDER)
	{
		if(nSBCode == SB_THUMBTRACK ||
            nSBCode == SB_THUMBPOSITION)
		{
            if(nSBCode == SB_THUMBTRACK)
				m_bSliderPressed = TRUE;
            else if(nSBCode == SB_THUMBPOSITION)
                m_bSliderPressed = FALSE;
			CSliderCtrl *pSlider = GetSliderCtrl();
			if(pSlider)
			{
				int iMin = pSlider->GetRangeMin();
				int iMax = pSlider->GetRangeMax();
				int iPos = pSlider->GetPos();
				double rate = ((double) (iPos - iMin)) / (iMax - iMin);
                CVMSApp * pApp = (CVMSApp *) AfxGetApp();
				CXfplayerDoc *pDoc = pApp->GetPlayerDocument();
				if(pDoc != NULL)
					pDoc->SetApproximatePosition(rate);
			}
		}
	}

	CDialogBar::OnHScroll(nSBCode, nPos, pScrollBar);*/
}


/*CSliderCtrl * CXfplayerDialogBar::GetSliderCtrl()
{
	return (CSliderCtrl *) GetDlgItem(IDC_SLIDER);
}

double CXfplayerDialogBar::GetSliderPos()
{
	CSliderCtrl *pSlider = GetSliderCtrl();
	if(pSlider)
	{
		int iMin = pSlider->GetRangeMin();
		int iMax = pSlider->GetRangeMax();
		int iPos = pSlider->GetPos();
		return ((double) (iPos - iMin)) / (iMax - iMin);
	}
	else
		return -1.0;

}*/

void CXfplayerDialogBar::OnSize(UINT nType, int cx, int cy) 
{
	CDialogBar::OnSize(nType, cx, cy);
	
//    CEdit * pEdit = (CEdit *) GetDlgItem(IDC_EDIT_TIME);
  //  CSliderCtrl * pSlider = (CSliderCtrl *) GetDlgItem(IDC_SLIDER);
    //if(pEdit == NULL || pSlider == NULL)
      //  return;
//    class rect clientRect;
  //  class rect editRect;
    //class rect sliderRect;
    //pEdit->GetClientRect(editRect);
    //pEdit->MoveWindow(editRect);
    //GetClientRect(clientRect);
    //sliderRect.left = editRect.right;
    //sliderRect.top = 0;
    /*sliderRect.right = clientRect.right;
    sliderRect.bottom = clientRect.bottom;
    pSlider->MoveWindow(sliderRect);*/
	// TODO: Add your message handler code here
	
}
