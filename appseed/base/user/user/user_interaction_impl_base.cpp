#include "framework.h"


namespace user
{


   interaction_impl_base::interaction_impl_base()
   {

      m_pui = NULL;

   }


   interaction_impl_base::~interaction_impl_base()
   {

      m_pui = NULL;

   }


   void interaction_impl_base::_001WindowMinimize()
   {

      m_pui->m_eappearance = AppearanceIconic;

      m_pui->good_iconify(NULL,true);

   }


   void interaction_impl_base::_001WindowMaximize()
   {

      m_pui->m_eappearance = AppearanceZoomed;

      m_pui->best_monitor(NULL,true);

   }


   void interaction_impl_base::_001WindowFullScreen()
   {

      m_pui->m_eappearance = ::user::AppearanceFullScreen;

      m_pui->best_monitor(NULL,true);

   }


   void interaction_impl_base::_001WindowRestore()
   {

      m_pui->m_eappearance = AppearanceNormal;

      m_pui->good_restore(NULL,true);

   }


   void interaction_impl_base::RepositionBars(UINT nIDFirst,UINT nIDLast,id nIdLeftOver, UINT nFlags,LPRECT lpRectParam,LPCRECT lpRectClient,bool bStretch)
   {
      
      UNREFERENCED_PARAMETER(nIDFirst);
      UNREFERENCED_PARAMETER(nIDLast);

      ASSERT(nFlags == 0 || (nFlags & ~reposNoPosLeftOver) == reposQuery ||
         (nFlags & ~reposNoPosLeftOver) == reposExtra);

      // walk kids in order, control bars get the resize notification
      //   which allow them to shrink the client area
      // remaining size goes to the 'nIDLeftOver' pane
      // NOTE: nIDFirst->nIDLast are usually 0->0xffff

      __SIZEPARENTPARAMS layout;
      sp(::user::interaction) oswindow_LeftOver = NULL;

      layout.bStretch = bStretch;
      layout.sizeTotal.cx = layout.sizeTotal.cy = 0;
      if(lpRectClient != NULL)
      {
         layout.rect = *lpRectClient;    // starting rect comes from parameter
      }
      else
      {
         m_pui->GetClientRect(&layout.rect);    // starting rect comes from client rect
      }

      if((nFlags & ~reposNoPosLeftOver) != reposQuery)
         layout.hDWP = ::BeginDeferWindowPos(8); // reasonable guess
      else
         layout.hDWP = NULL; // not actually doing layout

      if(m_pui != NULL)
      {
         for(sp(::user::interaction) oswindow_Child = m_pui->GetTopWindow(); oswindow_Child != NULL;
            oswindow_Child = oswindow_Child->GetNextWindow(GW_HWNDNEXT))
         {
            id id = oswindow_Child->GetDlgCtrlId();
            sp(::user::interaction) pwindow = oswindow_Child;
            if(id == (int32_t)nIdLeftOver)
               oswindow_LeftOver = oswindow_Child;
            else if(pwindow != NULL)
               oswindow_Child->send_message(WM_SIZEPARENT,0,(LPARAM)&layout);
         }
         for(sp(::user::interaction) oswindow_Child = m_pui->get_top_child(); oswindow_Child != NULL;
            oswindow_Child = oswindow_Child->under_sibling())
         {
            id id = oswindow_Child->GetDlgCtrlId();
            sp(::user::interaction) pwindow = oswindow_Child;
            if(id == nIdLeftOver)
               oswindow_LeftOver = oswindow_Child;
            else if(pwindow != NULL)
               oswindow_Child->send_message(WM_SIZEPARENT,0,(LPARAM)&layout);
         }
      }
      else
      {
         for(sp(::user::interaction) oswindow_Child = GetTopWindow(); oswindow_Child != NULL;
            oswindow_Child = oswindow_Child->GetNextWindow(GW_HWNDNEXT))
         {
            id id = oswindow_Child->GetDlgCtrlId();
            sp(::user::interaction) pwindow = oswindow_Child;
            if(id == nIdLeftOver)
               oswindow_LeftOver = oswindow_Child;
            else if(pwindow != NULL)
               oswindow_Child->send_message(WM_SIZEPARENT,0,(LPARAM)&layout);
         }
         for(sp(::user::interaction) oswindow_Child = m_pui->get_top_child(); oswindow_Child != NULL;
            oswindow_Child = oswindow_Child->under_sibling())
         {
            id id = oswindow_Child->GetDlgCtrlId();
            sp(::user::interaction) pwindow = oswindow_Child;
            if(id == nIdLeftOver)
               oswindow_LeftOver = oswindow_Child;
            else if(pwindow != NULL)
               oswindow_Child->send_message(WM_SIZEPARENT,0,(LPARAM)&layout);
         }
      }

      // if just getting the available rectangle, return it now...
      if((nFlags & ~reposNoPosLeftOver) == reposQuery)
      {
         ASSERT(lpRectParam != NULL);
         if(bStretch)
            ::CopyRect(lpRectParam,&layout.rect);
         else
         {
            lpRectParam->left = lpRectParam->top = 0;
            lpRectParam->right = layout.sizeTotal.cx;
            lpRectParam->bottom = layout.sizeTotal.cy;
         }
         return;
      }

      // the rest is the client size of the left-over pane
      if(nIdLeftOver != NULL && oswindow_LeftOver != NULL)
      {
         sp(::user::interaction) pLeftOver = oswindow_LeftOver;
         // allow extra space as specified by lpRectBorder
         if((nFlags & ~reposNoPosLeftOver) == reposExtra)
         {
            ASSERT(lpRectParam != NULL);
            layout.rect.left += lpRectParam->left;
            layout.rect.top += lpRectParam->top;
            layout.rect.right -= lpRectParam->right;
            layout.rect.bottom -= lpRectParam->bottom;
         }
         // reposition the interaction_impl
         if((nFlags & reposNoPosLeftOver) != reposNoPosLeftOver)
         {
            pLeftOver->CalcWindowRect(&layout.rect);
            __reposition_window(&layout,pLeftOver,&layout.rect);
         }
      }

      // move and resize all the windows at once!
      if(layout.hDWP == NULL || !::EndDeferWindowPos(layout.hDWP))
         TRACE(::base::trace::category_AppMsg,0,"Warning: DeferWindowPos failed - low system resources.\n");
   }


   void interaction_impl_base::ClientToScreen(LPRECT lprect)
   {

      m_pui->ClientToScreen(lprect);

   }


   void interaction_impl_base::ClientToScreen(LPPOINT lppoint)
   {

      m_pui->ClientToScreen(lppoint);

   }


   void interaction_impl_base::ClientToScreen(__rect64 * lprect)
   {

      m_pui->ClientToScreen(lprect);

   }


   void interaction_impl_base::ClientToScreen(__point64 * lppoint)
   {

      m_pui->ClientToScreen(lppoint);

   }


   void interaction_impl_base::ScreenToClient(LPRECT lprect)
   {

      m_pui->ScreenToClient(lprect);

   }


   void interaction_impl_base::ScreenToClient(LPPOINT lppoint)
   {

      m_pui->ScreenToClient(lppoint);

   }


   void interaction_impl_base::ScreenToClient(__rect64 * lprect)
   {

      m_pui->ScreenToClient(lprect);

   }


   void interaction_impl_base::ScreenToClient(__point64 * lppoint)
   {

      m_pui->ScreenToClient(lppoint);

   }


   void interaction_impl_base::GetWindowRect(LPRECT lprect)
   {

      m_pui->GetWindowRect(lprect);

   }


   void interaction_impl_base::GetClientRect(LPRECT lprect)
   {

      m_pui->GetClientRect(lprect);

   }


   void interaction_impl_base::GetClientRect(__rect64 * lprect)
   {

      m_pui->GetClientRect(lprect);

   }


   void interaction_impl_base::GetWindowRect(__rect64 * lprect)
   {

      m_pui->GetWindowRect(lprect);

   }


   rect interaction_impl_base::GetWindowRect()
   {

      return m_pui->GetWindowRect();

   }


   rect64 interaction_impl_base::GetWindowRect64()
   {

      return m_pui->GetWindowRect64();

   }


   bool interaction_impl_base::SetPlacement(LPCRECT lpcrect,UINT nFlags)
   {

      return m_pui->SetPlacement(lpcrect, nFlags);

   }


   bool interaction_impl_base::RepositionWindow(LPCRECT lpcrect,UINT nFlags)
   {

      return m_pui->RepositionWindow(lpcrect, nFlags);

   }


   bool interaction_impl_base::RepositionWindow(int32_t x,int32_t y,int32_t cx,int32_t cy,UINT nFlags)
   {

      return m_pui->RepositionWindow(x, y, cx, cy, nFlags);

   }


   bool interaction_impl_base::MoveWindow(int32_t x,int32_t y,UINT nFlags)
   {

      return m_pui->MoveWindow(x, y, nFlags);

   }


   bool interaction_impl_base::MoveWindow(POINT pt,UINT nFlags)
   {

      return m_pui->MoveWindow(pt, nFlags);

   }


   bool interaction_impl_base::SizeWindow(int32_t cx,int32_t cy,UINT nFlags)
   {

      return m_pui->SizeWindow(cx, cy, nFlags);

   }


   bool interaction_impl_base::SizeWindow(SIZE sz,UINT nFlags)
   {

      return m_pui->SizeWindow(sz, nFlags);

   }


   bool interaction_impl_base::ResizeWindow(int32_t cx,int32_t cy,UINT nFlags)
   {

      return m_pui->ResizeWindow(cx, cy, nFlags);

   }


   bool interaction_impl_base::ResizeWindow(SIZE sz,UINT nFlags)
   {

      return m_pui->ResizeWindow(sz, nFlags);

   }


   bool interaction_impl_base::SetWindowPos(int32_t z,LPCRECT lpcrect,UINT nFlags)
   {

      return m_pui->SetWindowPos(z, lpcrect, nFlags);

   }


   bool interaction_impl_base::SetWindowPos(int32_t z,int32_t x,int32_t y,int32_t cx,int32_t cy,UINT nFlags)
   {

      return m_pui->SetWindowPos(z,x,y,cx,cy,nFlags);

   }


   bool interaction_impl_base::defer_set_window_pos(int32_t z,int32_t x,int32_t y,int32_t cx,int32_t cy,UINT nFlags) // only set_windows_pos if get_parent()->ScreenToClient(get_window_rect) different of rect(x, y, cx, cy)
   {

      return m_pui->defer_set_window_pos(z, x, y, cx, cy, nFlags);

   }


   void interaction_impl_base::_001Print(::draw2d::graphics * pdc)
   {

      m_pui->_001Print(pdc);

   }


   void interaction_impl_base::_000OnDraw(::draw2d::graphics *pdc)
   {

      m_pui->_000OnDraw(pdc);

   }


   void interaction_impl_base::_001DrawThis(::draw2d::graphics *pdc)
   {

      m_pui->_001DrawThis(pdc);

   }


   void interaction_impl_base::_001DrawChildren(::draw2d::graphics *pdc)
   {

      m_pui->_001DrawChildren(pdc);

   }


   void interaction_impl_base::_001OnDraw(::draw2d::graphics *pdc)
   {

      m_pui->_001OnDraw(pdc);

   }


   void interaction_impl_base::draw_control_background(::draw2d::graphics *pdc)
   {

      m_pui->draw_control_background(pdc);

   }

   
   interaction * interaction_impl_base::get_wnd() const
   {

      return m_pui->get_wnd();

   }



   void interaction_impl_base::set_viewport_org(::draw2d::graphics * pgraphics)
   {

      throw interface_only_exception(get_app());

   }


   void interaction_impl_base::viewport_client_to_screen(POINT * ppt)
   {

      ClientToScreen(ppt);

   }


   void interaction_impl_base::viewport_screen_to_client(POINT * ppt)
   {

      ScreenToClient(ppt);

   }


   void interaction_impl_base::viewport_client_to_screen(RECT * prect)
   {

      viewport_client_to_screen((POINT *)&prect->left);
      viewport_client_to_screen((POINT *)&prect->right);

   }


   void interaction_impl_base::viewport_screen_to_client(RECT * prect)
   {

      viewport_screen_to_client((POINT *)&prect->left);
      viewport_screen_to_client((POINT *)&prect->right);

   }


   void interaction_impl_base::SetFont(::draw2d::font* pFont,bool bRedraw)
   {

      m_pui->SetFont(pFont,bRedraw);

   }


   ::draw2d::font* interaction_impl_base::GetFont()
   {

      return m_pui->GetFont();

   }



} // namespace user












