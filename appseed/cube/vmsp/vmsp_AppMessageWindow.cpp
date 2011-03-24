#include "StdAfx.h"
#include "AppMessageWindow.h"

CAppMessageWindow::CAppMessageWindow()
{
}

CAppMessageWindow::~CAppMessageWindow()
{
}


 // BEGIN_MESSAGE_MAP(CAppMessageWindow, ::ca::window)
   //{{AFX_MSG_MAP(CAppMessageWindow)
      // NOTE - the ClassWizard will add and remove mapping macros here.
   //}}AFX_MSG_MAP
// xxx   ON_MESSAGE(WM_APP, OnAppMessage)
 // END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CAppMessageWindow message handlers

afx_msg LRESULT CAppMessageWindow::OnAppMessage(WPARAM wParam, LPARAM lParam)
{
   ASSERT(FALSE);
   return 0;
}