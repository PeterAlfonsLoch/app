// ApplicationWindow.cpp : implementation file
//

#include "stdafx.h"
#include "OSZipShell.h"
#include "ApplicationWindow.h"


// ApplicationWindow

IMPLEMENT_DYNAMIC(ApplicationWindow, CWnd)

ApplicationWindow::ApplicationWindow()
{

}

ApplicationWindow::~ApplicationWindow()
{
}


BEGIN_MESSAGE_MAP(ApplicationWindow, CWnd)
END_MESSAGE_MAP()



// ApplicationWindow message handlers


bool ApplicationWindow::Create()
{
   return CWnd::CreateEx(NULL, AfxRegisterWndClass(0), "OSZipShell_ShellExtension_ApplicationWindow",
      0, 0, 0, 0, 0, NULL, NULL) != FALSE;
}