#include "StdAfx.h"

#include "XfplayerFrame.h"

/////////////////////////////////////////////////////////////////////////////
// XfplayerFrame

// IMPLEMENT_DYNCREATE(XfplayerFrame, mdi_child_window)

 // BEGIN_MESSAGE_MAP(XfplayerFrame, mdi_child_window)
   //{{AFX_MSG_MAP(XfplayerFrame)
/* xxx   ON_WM_CLOSE()
   ON_WM_CREATE()
   ON_WM_SIZE()
   ON_WM_DESTROY() */
   //}}AFX_MSG_MAP
 // END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// XfplayerFrame construction/destruction

XfplayerFrame::XfplayerFrame(::ca::application * papp) :
   ca(papp),
   window_frame::WorkSetClientInterface(papp),
   userbase::frame_window_interface(papp),
   userbase::frame_window(papp),
   mdi_child_window(papp)
{
    m_pmenuv033 = NULL;

   // TODO: add member initialization code here
   
}

XfplayerFrame::~XfplayerFrame()
{
}

BOOL XfplayerFrame::PreCreateWindow(CREATESTRUCT& cs)
{
   // TODO: Modify the Window class or styles here by modifying
   //  the CREATESTRUCT cs

    
   if( !mdi_child_window::PreCreateWindow(cs) )
      return FALSE;

   return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// XfplayerFrame diagnostics

#ifdef _DEBUG
void XfplayerFrame::assert_valid() const
{
   mdi_child_window::assert_valid();
}

void XfplayerFrame::dump(dump_context & dumpcontext) const
{
   mdi_child_window::dump(dumpcontext);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// XfplayerFrame message handlers

void XfplayerFrame::OnClose() 
{
   // TODO: add your message handler code here and/or call default
    mdi_child_window::OnClose();
}

int XfplayerFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
   if (mdi_child_window::OnCreate(lpCreateStruct) == -1)
      return -1;
   
//    ::userbase::menu * pSystemMenu = GetSystemMenu(FALSE);

  //  pSystemMenu->EnableMenuItem(SC_CLOSE, MF_BYCOMMAND | MF_GRAYED);
    ::ca::application * pApp = (::ca::application *) &System;        

/*   DIMoveWindow(
      "PlayerWindowPlacement");*/
   // TODO: add your specialized creation code here
//   ::userbase::menu * pMenu = GetMenu();
  //  //m_menuV033.CreateMenu();
    //m_menuV033.LoadMenu(pMenu);
    //m_hMenuShared = m_menuV033.GetSafeHmenu();
    //SetMenu(&m_menuV033);
    //pMenu->DestroyMenu();

//    vmsp::application * pApp = dynamic_cast < vmsp::application * > (&System);

/*    m_pmenuv033 = new CMenuV033( BaseMenuCentral::GetMenuCentral());

   ::userbase::menu * pMenu = GetMenu();
    m_pmenuv033->CreateMenu();
    //m_pmenuv033->LoadMenu(pMenu);
    m_hMenuShared = m_pmenuv033->GetSafeHmenu();
    SetMenu(m_pmenuv033);
    pMenu->DestroyMenu();

*/
   return 0;
}

BOOL XfplayerFrame::LoadFrame(const char * pszFrame, DWORD dwDefaultStyle, ::user::interaction * pParentWnd, create_context* pContext) 
{
      // only do this once
//   ASSERT_VALID_IDR(nIDResource);
   //ASSERT(m_nIDHelp == 0 || m_nIDHelp == nIDResource);
   ASSERT(m_hMenuShared == NULL);      // only do once

   //m_nIDHelp = nIDResource;    // ID for help context (+HID_BASE_RESOURCE)

   // parent must be MDI Frame (or NULL for default)
   ASSERT(pParentWnd == NULL || base < CMDIFrameWnd >::bases(pParentWnd));
   // will be a child of MDIClient
   ASSERT(!(dwDefaultStyle & WS_POPUP));
   dwDefaultStyle |= WS_CHILD;

   // if available - get MDI child menus from doc template
   ASSERT(m_hMenuShared == NULL);      // only do once
   document_template * ptemplate;
   musctrl::single_document_template * pSingleTemplate = 
      dynamic_cast < musctrl::single_document_template * >(ptemplate);
   if (pContext != NULL &&
      (ptemplate = pContext->m_pNewDocTemplate) != NULL &&
        pSingleTemplate != NULL)
   {
      
//      ASSERT_KINDOF(XfplayerSingleDocTemplate, pSingleTemplate);
//        vmsp::application * pApp = dynamic_cast < vmsp::application * > (&System);        
      // get shared menu from doc template
//      m_hMenuShared = pSingleTemplate->m_hMenu;
  //      m_hAccelTable = pSingleTemplate->m_hAccel;
        // pApp->m_pmenuPlayerShared->m_hMenu;
//      m_hAccelTable = pApp->m_hPlayerAccelTable;
   }
   else
   {
      TRACE0("Warning: no shared menu/acceltable for MDI Child ::ca::window.\n");
         // if this happens, programmer must load these manually
   }

   string strFullString, strTitle;
   strFullString = System.matter_as_string(get_app(), pszFrame);
   if(!strFullString.is_empty())
      AfxExtractSubString(strTitle, strFullString, 0);    // first sub-string

   //ASSERT(get_handle() == NULL);
   if (!create(GetIconWndClass(dwDefaultStyle, pszFrame),
     strTitle, dwDefaultStyle, rectDefault,
     dynamic_cast < ::userbase::mdi_frame_window *> (pParentWnd), pContext))
   {
      return FALSE;   // will self destruct on failure normally
   }

   // it worked !
   return TRUE;
}

void XfplayerFrame::OnSize(UINT nType, int cx, int cy) 
{
   mdi_child_window::OnSize(nType, cx, cy);
   
   // TODO: add your message handler code here
   
}

void XfplayerFrame::OnDestroy() 
{

    mdi_child_window::OnDestroy();

   
   // TODO: add your message handler code here
   
}

BOOL XfplayerFrame::DestroyWindow() 
{
   // TODO: add your specialized code here and/or call the base class
//    vmsp::application * pApp = dynamic_cast < vmsp::application * > (&System);        
//    DISaveWindowRect();
   return mdi_child_window::DestroyWindow();
}
