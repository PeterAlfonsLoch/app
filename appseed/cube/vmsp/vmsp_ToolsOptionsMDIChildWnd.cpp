#include "StdAfx.h"
#include "ToolsOptionsMDIChildWnd.h"


CToolsOptionsMDIChildWnd::CToolsOptionsMDIChildWnd(::ca::application * papp) :
   ca(papp),
   window_frame::WorkSetClientInterface(papp),
   userbase::frame_window_interface(papp),
   userbase::frame_window(papp),
   mdi_child_window(papp),
   m_toolbar(papp)
{
//   m_pruntimeclassMainFrame = &typeid(CMainFrame);
//   m_uiIDMainFrame = IDR_MAINFRAME;

}

CToolsOptionsMDIChildWnd::~CToolsOptionsMDIChildWnd()
{
}


 // BEGIN_MESSAGE_MAP(CToolsOptionsMDIChildWnd, mdi_child_window)
   //{{AFX_MSG_MAP(CToolsOptionsMDIChildWnd)
      // NOTE - the ClassWizard will add and remove mapping macros here.
   //}}AFX_MSG_MAP
 // END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CToolsOptionsMDIChildWnd message handlers

bool CToolsOptionsMDIChildWnd::_000OnPosCreate()
{
//   mdi_child_window::_000OnPosCreate();
   if(GetParent() == NULL)
   {
      ShowWindow(SW_RESTORE);
   }
   else
   {
      MDIMaximize();
   }
   return false;
}

void CToolsOptionsMDIChildWnd::TransparentFrameWndUpdateBars()
{
//   mdi_child_window::TransparentFrameWndUpdateBars();
   bool bResult = true;
//   CRelationV001<UINT, UINT, UINT, UINT> * prel;
//   BaseMenuCentral::GetMenuCentral()->MenuV033GetImageMap(&prel);
   

/*   while(m_toolbar.GetToolBarCtrl().DeleteButton(0));
    if (!m_toolbar.LoadToolBar(m_uiIDResource))
   {
      bResult = false;
   }*/
    string str;


/*   TransparentFrameWndUpdateToolBarText(m_toolbar);
   TransparentFrameWndUpdateToolBarStyle(m_toolbar);
   TransparentFrameWndFixedReBarToolBarLayoutVR(m_toolbar, 1);
*/

/*   CReBarCtrl & rebarctrl = m_rebar.GetReBarCtrl();

   for(UINT user = 0; user < rebarctrl.GetBandCount(); user++)
   {
      rebarctrl.MaximizeBand(user);
   }*/

   layout();


}

BOOL CToolsOptionsMDIChildWnd::OnCreateClient(LPCREATESTRUCT lpcs, create_context* pContext) 
{
   if(!mdi_child_window::OnCreateClient(lpcs, pContext))
      return FALSE;

/*    if (!m_toolbar.CreateEx(
        this,
        TBSTYLE_FLAT
      | TBSTYLE_LIST
        | WS_CHILD
      | WS_VISIBLE,
        CBRS_TOOLTIPS
      | CBRS_FLYBY
      | CBRS_TOP
      | CBRS_SIZE_FIXED,
        rect(0, 0, 0, 0),
        m_uiIDResource))
   {
      TRACE0("Failed to create toolbar\n");
      return FALSE;      // fail to create
   }
    if (!m_toolbar.LoadToolBar(m_uiIDResource))
   {
      TRACE0("Failed to create toolbar\n");
      return FALSE;      // fail to create
   }*/
    
   return TRUE;   
}
