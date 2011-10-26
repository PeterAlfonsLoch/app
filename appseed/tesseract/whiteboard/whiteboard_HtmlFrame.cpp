#include "StdAfx.h"

namespace whiteboard
{

   html_frame::html_frame(::ca::application * papp) :
      ca(papp),
      window_frame::WorkSetClientInterface(papp),
      userbase::frame_window_interface(papp),
      userbase::frame_window(papp),
      m_toolbarHtml(papp)
   {
   }

   html_frame::~html_frame()
   {
   }


    // BEGIN_MESSAGE_MAP(html_frame, userbase::frame_window)
      //{{AFX_MSG_MAP(html_frame)
   /*   ON_WM_CLOSE()
      ON_WM_CREATE()
      ON_COMMAND(ID_TOOLS_OPTIONS, OnToolsOptions)
      ON_WM_ACTIVATE()*/
      //}}AFX_MSG_MAP
    // END_MESSAGE_MAP()

   /////////////////////////////////////////////////////////////////////////////
   // html_frame message handlers

   void html_frame::OnClose() 
   {
      ShowWindow(SW_HIDE);
   }

   BOOL html_frame::PreCreateWindow(CREATESTRUCT& cs) 
   {
      ::ca::create_context * pContext = (::ca::create_context *) cs.lpCreateParams;
      if(pContext != NULL)
      {
         pContext->m_user->m_typeinfoNewView = ::ca::get_type_info < html_view > ();
      }
      cs.dwExStyle |= WS_EX_TOOLWINDOW;
      cs.dwExStyle &= ~WS_EX_APPWINDOW;
      return userbase::frame_window::PreCreateWindow(cs);
   }

   int html_frame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
   {
      UNREFERENCED_PARAMETER(lpCreateStruct);
   //   if (userbase::frame_window::OnCreate(lpCreateStruct) == -1)
   //      return -1;
      
   //   SetMenu(NULL);
      ModifyStyle(WS_MINIMIZEBOX | 0xc000, 0, SWP_FRAMECHANGED);
      ModifyStyleEx(WS_EX_APPWINDOW | WS_EX_CLIENTEDGE 
         | WS_EX_WINDOWEDGE, WS_EX_TOOLWINDOW, SWP_FRAMECHANGED);   

      return 0;
   }

   void html_frame::OnToolsOptions() 
   {
      GetActiveDocument()->update_all_views(NULL, 4321);
      layout();
   }

   void html_frame::OnActivate(UINT nState, ::ca::window* pWndOther, BOOL bMinimized) 
   {
      UNREFERENCED_PARAMETER(pWndOther);
      UNREFERENCED_PARAMETER(bMinimized);
   //   userbase::frame_window::OnActivate(nState, pWndOther, bMinimized);
      
      if(nState == WA_INACTIVE)
      {
         //ShowWindow(SW_HIDE);
      }
   }

} // namespace whiteboard