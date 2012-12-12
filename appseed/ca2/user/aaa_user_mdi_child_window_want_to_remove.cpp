#include "StdAfx.h"

void CMDIChildWnd::MDIDestroy()
   {  GetParent()->SendMessage(WM_MDIDESTROY, (WPARAM)this, 0L); }
 void CMDIChildWnd::MDIActivate()
   {  GetParent()->SendMessage( WM_MDIACTIVATE, (WPARAM)this, 0L); }
 void CMDIChildWnd::MDIMaximize()
   {  GetParent()->SendMessage( WM_MDIMAXIMIZE, (WPARAM)this, 0L); }
 void CMDIChildWnd::MDIRestore()
   {  GetParent()->SendMessage( WM_MDIRESTORE, (WPARAM)this, 0L); }

 
 