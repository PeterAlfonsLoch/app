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


   void interaction_impl_base::_001UpdateWindow()
   {


   }


   void interaction_impl_base::_001WindowMinimize()
   {

      m_pui->m_eappearance = AppearanceIconic;

      rect rectNormal;

      m_pui->get_rect_normal(rectNormal);

      m_pui->good_iconify(NULL,rectNormal,true);

   }


   void interaction_impl_base::_001WindowMaximize()
   {

      m_pui->m_eappearance = AppearanceZoomed;

      rect rectNormal;

      m_pui->get_rect_normal(rectNormal);

      m_pui->best_wkspace(NULL, rectNormal,true);

   }


   void interaction_impl_base::_001WindowFullScreen()
   {

      m_pui->m_eappearance = ::user::AppearanceFullScreen;

      rect rectNormal;

      m_pui->get_rect_normal(rectNormal);

      m_pui->best_monitor(NULL,rectNormal,true);

   }


   void interaction_impl_base::_001WindowRestore()
   {

      m_pui->m_eappearance = AppearanceNormal;

      rect rectNormal;

      m_pui->get_rect_normal(rectNormal);

      m_pui->good_restore(NULL,rectNormal,true);

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

      return m_pui->GetWindow();

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


   bool interaction_impl_base::RedrawWindow(LPCRECT lpRectUpdate,::draw2d::region* prgnUpdate,UINT flags)
   {

      return m_pui->RedrawWindow(lpRectUpdate,prgnUpdate,flags);

   }



   void interaction_impl_base::SetFont(::draw2d::font* pFont,bool bRedraw)
   {

      m_pui->SetFont(pFont,bRedraw);

   }


   ::draw2d::font* interaction_impl_base::GetFont()
   {

      return m_pui->GetFont();

   }


   uint32_t interaction_impl_base::GetStyle() const
   {
      
      return get_window_long(GWL_STYLE);

   }
   
   
   uint32_t interaction_impl_base::GetExStyle() const
   {

      return get_window_long(GWL_EXSTYLE);

   }


   bool interaction_impl_base::ModifyStyle(uint32_t dwRemove,uint32_t dwAdd,UINT nFlags)
   {

      set_window_long(GWL_STYLE,(GetStyle() | dwAdd) & ~dwRemove);

      return true;

   }


   bool interaction_impl_base::ModifyStyleEx(uint32_t dwRemove,uint32_t dwAdd,UINT nFlags)
   {

      set_window_long(GWL_EXSTYLE,(GetExStyle() | dwAdd) & ~dwRemove);

      return true;

   }


   LONG interaction_impl_base::get_window_long(int32_t nIndex) const
   {

      return (LONG)get_window_long_ptr(nIndex);

   }


   LONG interaction_impl_base::set_window_long(int32_t nIndex,LONG lValue)
   {

      return (LONG)set_window_long_ptr(nIndex, lValue);

   }


   LONG_PTR interaction_impl_base::get_window_long_ptr(int32_t nIndex) const
   {

      return oprop("window_long:" + ::str::from(nIndex));

   }


   LONG_PTR interaction_impl_base::set_window_long_ptr(int32_t nIndex,LONG_PTR lValue)
   {

      return oprop("window_long:" + ::str::from(nIndex)) = lValue;

   }


   id interaction_impl_base::GetDlgCtrlId() const
   {

      return m_pui->GetDlgCtrlId();

   }


   id interaction_impl_base::SetDlgCtrlId(id id)
   {

      return m_pui->SetDlgCtrlId(id);

   }


   sp(interaction) interaction_impl_base::get_bottom_child()
   {

      return m_pui->get_bottom_child();

   }


   sp(interaction) interaction_impl_base::get_top_child()
   {

      return m_pui->get_bottom_child();

   }


   sp(interaction) interaction_impl_base::under_sibling()
   {

      return m_pui->under_sibling();

   }


   sp(interaction) interaction_impl_base::above_sibling()
   {

      return m_pui->above_sibling();

   }


   sp(interaction) interaction_impl_base::above_sibling(sp(interaction) pui)
   {

      return m_pui->above_sibling(pui);

   }


   sp(interaction) interaction_impl_base::under_sibling(sp(interaction) pui)
   {

      return m_pui->under_sibling(pui);

   }


   UINT interaction_impl_base::ArrangeIconicWindows()
   {

//      return m_pui->ArrangeIconicWindows();
      return 0;

   }


   void interaction_impl_base::BringToTop(int nCmdShow)
   {

      //return m_pui->BringToTop(nCmdShow);

   }


   bool interaction_impl_base::BringWindowToTop()
   {

      return m_pui->BringWindowToTop();

   }


   bool interaction_impl_base::IsAscendant(const interaction * puiIsAscendant) const
   {

      if(puiIsAscendant == NULL)
         return false;

      return puiIsAscendant->IsDescendant(m_pui);

   }


   bool interaction_impl_base::IsParent(const interaction * puiIsParent) const
   {

      if(puiIsParent == NULL)
         return false;

      return puiIsParent->IsChild(m_pui);

   }


   bool interaction_impl_base::IsChild(const interaction * puiIsChild) const
   {

      interaction * puiProbe = puiIsChild->GetParent();

      return puiProbe == m_pui;

   }


   bool interaction_impl_base::IsDescendant(const interaction * puiIsDescendant) const
   {

      interaction * puiProbe = puiIsDescendant->GetParent();

      if(puiProbe == NULL)
         return false;

      do
      {

         if(puiProbe == m_pui)
            return true;

         puiProbe = puiProbe->GetParent();

      } while(puiProbe != NULL);

      return false;

   }

   sp(::user::interaction) interaction_impl_base::GetWindow() const
   {

      return m_pui->GetWindow();

   }


   sp(interaction) interaction_impl_base::GetWindow(UINT nCmd) const
   {

      return m_pui->GetWindow(nCmd);

   }


   sp(::user::interaction) interaction_impl_base::GetTopWindow() const
   {

      sp(interaction) pui = GetWindow();

      if(pui.is_null())
         return NULL;

      return pui->GetTopWindow();

   }


   sp(interaction) interaction_impl_base::GetParent() const
   {

      return m_pui->GetParent();

   }


   sp(interaction) interaction_impl_base::GetOwner() const
   {

      return m_pui->GetOwner();

   }


   sp(frame_window) interaction_impl_base::GetFrame() const
   {

      return m_pui->GetFrame();

   }


   sp(frame_window) interaction_impl_base::GetParentFrame() const
   {

      return m_pui->GetParentFrame();

   }


   sp(::user::interaction) interaction_impl_base::GetParentOwner() const
   {

      return m_pui->GetParentOwner();

   }


   sp(::user::interaction) interaction_impl_base::GetTopLevelOwner() const
   {

      return m_pui->GetTopLevelOwner();

   }


   sp(::user::frame_window) interaction_impl_base::GetTopLevelFrame() const
   {

      return m_pui->GetTopLevelFrame();

   }

   sp(::user::frame_window) interaction_impl_base::EnsureParentFrame()
   {

      return m_pui->EnsureParentFrame();

   }


   sp(interaction) interaction_impl_base::GetTopLevel() const
   {

      return m_pui->GetTopLevel();

   }


   sp(interaction) interaction_impl_base::GetParentTopLevel() const
   {

      return m_pui->GetParentTopLevel();

   }


   sp(frame_window) interaction_impl_base::GetParentTopLevelFrame() const
   {

      return m_pui->GetParentTopLevelFrame();

   }


   sp(interaction) interaction_impl_base::EnsureTopLevel()
   {

      return m_pui->EnsureTopLevel();

   }


   sp(interaction) interaction_impl_base::EnsureParentTopLevel()
   {

      return m_pui->EnsureParentTopLevel();

   }


   void interaction_impl_base::SendMessageToDescendants(UINT message,WPARAM wparam,lparam lparam,bool bDeep,bool bOnlyPerm)
   {

      return m_pui->SendMessageToDescendants(message, wparam, lparam, bDeep, bOnlyPerm);

   }


   void interaction_impl_base::pre_translate_message(signal_details * pobj)
   {

      m_pui->pre_translate_message(pobj);

   }


   sp(interaction) interaction_impl_base::SetCapture(sp(interaction) pinterface)
   {

      return GetWindow()->SetCapture(pinterface);

   }


   sp(interaction) interaction_impl_base::GetCapture()
   {

      return GetWindow()->GetCapture();

   }


   sp(interaction) interaction_impl_base::ReleaseCapture()
   {

      return GetWindow()->ReleaseCapture();

   }


   sp(::user::interaction) interaction_impl_base::SetFocus()
   {

      return m_pui->SetFocus();

   }


   bool interaction_impl_base::get_rect_normal(LPRECT lprect)
   {

      GetWindowRect(lprect);

      return true;

   }



} // namespace user












