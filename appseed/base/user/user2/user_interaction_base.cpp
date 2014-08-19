#include "framework.h"


/////////////////////////////////////////////////////////////////////////////
// mirroring support

//WINBUG: some mirroring stuff will be in wingdi.h someday
#ifndef LAYOUT_RTL
#define LAYOUT_LTR                               0x00000000
#define LAYOUT_RTL                         0x00000001
#define NOMIRRORBITMAP                     0x80000000
#endif

//WINBUG: some mirroring stuff will be in winuser.h someday
#ifndef WS_EX_LAYOUTRTL
#define WS_EX_LAYOUTRTL                    0x00400000L
#endif


namespace user
{


   interaction_base::interaction_base()
   {

   }


   interaction_base::interaction_base(sp(::axis::application) papp) :
      element(papp),
      command_target_interface(papp)
   {

   }


   interaction_base::~interaction_base()
   {

   }


   void interaction_base::install_message_handling(::message::dispatch * pinterface)
   {

      ::message::dispatch::install_message_handling(pinterface);

   }


   void interaction_base::TwfGetWndArray(::user::interaction_ptr_array & wndpa)
   {

      wndpa = *dynamic_cast < ::user::interaction_ptr_array * >(get_app());

   }


   void interaction_base::TwfGetWndArray(::user::oswindow_array & oswindowa)
   {

      ::user::interaction_ptr_array & wndpa = *dynamic_cast < ::user::interaction_ptr_array * >(get_app());

      oswindowa = wndpa.get_hwnda();

   }


   void interaction_base::_001RedrawWindow()
   {

      sp(::user::interaction) pui = GetWindow();

      if(pui.is_set())
      {

         GetWindow()->_001UpdateWindow();

      }

   }




   void interaction_base::RedrawOptimize(rect_array &array)
   {

      rect rect;

   Restart:

      for(int32_t i = 0; i < array.get_size(); i++)
      {
         for(int32_t j = i + 1; j < array.get_size(); j++)
         {
            if(RedrawOptimize(
               rect,
               array[i],
               array[j]))
            {
               array[i] = rect;
               array.remove_at(j);
               goto Restart;

            }

         }

      }

   }


   bool interaction_base::RedrawOptimize(LPRECT lprectOut, LPCRECT lpcrect1, LPCRECT lpcrect2)
   {

      rect rect1(lpcrect1);
      rect rect2(lpcrect2);
      rect rect3;

      int32_t iArea1 = rect1.width() * rect1.height();
      int32_t iArea2 = rect2.width() * rect2.height();
      rect3.unite(rect1, rect2);
      int32_t iArea3 = rect3.width() * rect3.height();

      if(iArea3 < (110 * (iArea1 + iArea2) / 100))
      {

         *lprectOut = rect3;

         return true;

      }
      else
      {

         return false;

      }

   }


   void interaction_base::PreSubClassWindow()
   {

      _001BaseWndInterfaceMap();

   }


   void interaction_base::_001BaseWndInterfaceMap()
   {

   }


   sp(interaction) interaction_base::GetWindow() const
   {

      return NULL;

   }


   bool interaction_base::is_window_enabled()
   {

      return true;

   }


   bool interaction_base::enable_window(bool bEnable)
   {

      UNREFERENCED_PARAMETER(bEnable);

      return true;

   }


   void interaction_base::_on_start_user_message_handler()
   {

      dispatch::_on_start_user_message_handler();

      _001BaseWndInterfaceMap();

   }


   void interaction_base::_000OnDraw(::draw2d::graphics * pdc)
   {

      _001OnDraw(pdc);

   }


   void interaction_base::UpdateWindow()
   {

      //ASSERT(::IsWindow(GetHandle()));
      //::UpdateWindow(GetHandle());

   }


   void interaction_base::Invalidate(bool bErase)
   {

      UNREFERENCED_PARAMETER(bErase);

      //ASSERT(::IsWindow(GetHandle()));
      //::InvalidateRect(GetHandle(), NULL, bErase);

   }


   bool interaction_base::Redraw(rect_array & recta)
   {

      bool bOk = true;

      for(int32_t i = 0; i < recta.get_size(); i++)
      {

         if(!GetWindow()->RedrawWindow(recta[i]))
            bOk = false;

      }

      return bOk;

   }


   bool interaction_base::Redraw(LPCRECT lprect, ::draw2d::region * prgn)
   {

      if(GetWindow() == NULL)
         return false;

      return GetWindow()->RedrawWindow(lprect, prgn, RDW_INVALIDATE);

   }


   bool interaction_base::Redraw(::draw2d::graphics * pdc)
   {

      UNREFERENCED_PARAMETER(pdc);

      if(GetWindow() == NULL)
         return false;

      return GetWindow()->RedrawWindow();

   }


   void interaction_base::ClientToScreen(LPRECT lprect)
   {

      throw interface_only_exception(get_app());

   }


   void interaction_base::ClientToScreen(LPPOINT lppoint)
   {

      throw interface_only_exception(get_app());

   }


   void interaction_base::ClientToScreen(__rect64 * lprect)
   {

      throw interface_only_exception(get_app());

   }


   void interaction_base::ClientToScreen(__point64 * lppoint)
   {

      throw interface_only_exception(get_app());

   }


   void interaction_base::ScreenToClient(LPRECT lprect)
   {

      throw interface_only_exception(get_app());

   }


   void interaction_base::ScreenToClient(LPPOINT lppoint)
   {

      throw interface_only_exception(get_app());

   }


   void interaction_base::ScreenToClient(__rect64 * lprect)
   {

      throw interface_only_exception(get_app());

   }


   void interaction_base::ScreenToClient(__point64 * lppoint)
   {

      throw interface_only_exception(get_app());

   }


   void interaction_base::GetWindowRect(LPRECT lprect)
   {

      throw interface_only_exception(get_app());

   }


   void interaction_base::GetClientRect(LPRECT lprect)
   {

      throw interface_only_exception(get_app());

   }


   void interaction_base::GetClientRect(__rect64 * lprect)
   {

      throw interface_only_exception(get_app());

   }


   void interaction_base::GetWindowRect(__rect64 * lprect)
   {

      throw interface_only_exception(get_app());

   }


   rect interaction_base::GetWindowRect()
   {

      rect rect;

      GetWindowRect(&rect);

      return rect;

   }


   rect64 interaction_base::GetWindowRect64()
   {

      rect64 rect;

      GetWindowRect(&rect);

      return rect;

   }


   bool interaction_base::timer_item::check(single_lock & sl)
   {

      if(::get_tick_count() >= (m_uiLastSent + m_uiElapse))
      {

         bool bWindow;

         try
         {
            // simple integrity check by calling "inoffensive" function
            // if it fails, most probably the object is damaged.
            bWindow = m_pui->IsWindow() != FALSE;
            if(bWindow)
               bWindow = m_pui != NULL;
         }
         catch(...)
         {
            return false;
         }

         if(!bWindow)
            return false;

         sl.unlock();

         try
         {
            m_pui->send_message(WM_TIMER,m_uiId);
         }
         catch(...)
         {
            return false;
         }

         sl.lock();

         m_uiLastSent = ::get_tick_count();

      }

      return true;

   }


   interaction_base::timer_array::timer_array(sp(::axis::application) papp):
      element(papp),
      m_mutex(papp)
   {
   }


   bool interaction_base::timer_array::unset(sp(interaction) pui,uint_ptr uiId)
   {


      single_lock sl(&m_mutex,TRUE);


      index i = find(pui,uiId);
      if(i >= 0)
      {
         m_timera.remove_at(i);
         if(find_from(pui,0) < 0)
         {
            remove(pui);
         }
         return true;
      }
      return false;
   }

   void interaction_base::timer_array::detach(smart_pointer_array < timer_item > & timera,sp(interaction) pui)
   {


      single_lock sl(&m_mutex,TRUE);

      timera = m_timera;
      m_timera.remove_all();

      for(int32_t i = 0; i < timera.get_count();)
      {
         if(timera[i].m_pui == pui)
         {
            i++;
         }
         else
         {
            m_timera.add(new timer_item(timera[i]));
            timera.remove_at(i);
         }
      }

   }

   void interaction_base::timer_array::transfer(::window_sp pwindow,sp(interaction) pui)
   {


      single_lock sl(&m_mutex,TRUE);

      smart_pointer_array < timer_item > timera;
      detach(timera,pui);
      pwindow->set_timer(timera);

   }

   void interaction_base::timer_array::unset(sp(interaction) pui)
   {

      retry_single_lock sl(&m_mutex,millis(177),millis(184));

      index i = 0;

      while((i = find_from(pui,i)) >= 0)
      {
         m_timera.remove_at(i);
      }

      if(find_from(pui,0) < 0)
      {
         remove(pui);
      }

   }

   index interaction_base::timer_array::find(sp(interaction) pui,uint_ptr uiId)
   {


      retry_single_lock sl(&m_mutex,millis(177),millis(184));


      for(index i = 0; i < m_timera.get_count(); i++)
      {
         if(m_timera[i].m_pui == pui && m_timera[i].m_uiId == uiId)
         {
            return i;
         }
      }

      return -1;

   }

   index interaction_base::timer_array::find_from(sp(interaction) pui,index iStart)
   {


      retry_single_lock sl(&m_mutex,millis(177),millis(184));


      for(index i = iStart; i < m_timera.get_count(); i++)
      {
         if(m_timera[i].m_pui == pui)
         {
            return i;
         }
      }

      return -1;

   }

   void interaction_base::timer_array::dump(dump_context & dc) const
   {
      UNREFERENCED_PARAMETER(dc);
   }

   void interaction_base::timer_array::assert_valid() const
   {

   }



   void interaction_base::timer_array::check()
   {


      single_lock sl(&m_mutex,TRUE);

      if(m_iItem >= m_timera.get_count())
         m_iItem = m_timera.get_upper_bound();

      if(m_iItem < 0)
         m_iItem = 0;


      index iPreviousItem = m_iItem;

      for(; m_iItem < m_timera.get_count();)
      {
         try
         {
            if(!m_timera[m_iItem].check(sl))
            {
               if(m_iItem < m_timera.get_count())
               {
                  m_timera.remove_at(m_iItem);
               }
               continue;
            }
         }
         catch(...)
         {
            try
            {
               if(m_iItem < m_timera.get_count())
               {
                  m_timera.remove_at(m_iItem);
               }
               continue;
            }
            catch(...)
            {
            }
         }
         m_iItem++;
      }

      m_iItem = 0;

      for(; m_iItem < MIN(iPreviousItem,m_timera.get_count());)
      {
         try
         {
            if(!m_timera[m_iItem].check(sl))
            {
               if(m_iItem < m_timera.get_count())
               {
                  m_timera.remove_at(m_iItem);
               }
               continue;
            }
         }
         catch(...)
         {
            try
            {
               if(m_iItem < m_timera.get_count())
               {
                  m_timera.remove_at(m_iItem);
               }
               continue;
            }
            catch(...)
            {
            }
         }

         m_iItem++;
      }

   }


   uint_ptr interaction_base::timer_array::set(sp(interaction) pui,uint_ptr uiId,UINT uiElapse)
   {


      single_lock sl(&m_mutex,TRUE);


      if(pui == NULL)
         return 0xffffffff;

      add(pui);

      index i = find(pui,uiId);

      if(i >= 0)
      {

         m_timera[i].m_uiElapse = uiElapse;
         m_timera[i].m_uiLastSent = ::get_tick_count();

         return (UINT)i;

      }
      else
      {

         sp(timer_item) item(new timer_item);

         item->m_pui = pui;
         item->m_uiId = uiId;
         item->m_uiElapse = uiElapse;
         item->m_uiLastSent = ::get_tick_count();

         return (UINT)m_timera.add(item);

      }

   }





























































/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





































   bool interaction_base::IsAscendant(const interaction * puiIsAscendant) const
   {

      throw interface_only_exception(get_app());

   }


   bool interaction_base::IsParent(const interaction * puiIsParent) const
   {

      throw interface_only_exception(get_app());

   }


   bool interaction_base::IsChild(const interaction * puiIsChild) const
   {

      throw interface_only_exception(get_app());

   }


   bool interaction_base::IsDescendant(const interaction * puiIsDescendant) const
   {

      throw interface_only_exception(get_app());

   }


   sp(place_holder) interaction_base::place(sp(::user::interaction) pui)
   {

      throw interface_only_exception(get_app());

      return NULL;

   }



   void interaction_base::set_timer(smart_pointer_array < timer_item > timera)
   {

      throw interface_only_exception(get_app());

   }


   bool interaction_base::SetPlacement(const RECT & rect,UINT nFlags)
   {

      throw interface_only_exception(get_app());

   }


   bool interaction_base::RepositionWindow(const RECT & rect,UINT nFlags)
   {

      throw interface_only_exception(get_app());

   }


   bool interaction_base::RepositionWindow(int32_t x,int32_t y,int32_t cx,int32_t cy,UINT nFlags)
   {

      throw interface_only_exception(get_app());

   }


   bool interaction_base::MoveWindow(int32_t x,int32_t y,UINT nFlags)
   {

      throw interface_only_exception(get_app());

   }


   bool interaction_base::MoveWindow(POINT pt,UINT nFlags)
   {

      throw interface_only_exception(get_app());

   }


   bool interaction_base::SizeWindow(int32_t cx,int32_t cy,UINT nFlags)
   {

      throw interface_only_exception(get_app());

   }


   bool interaction_base::SizeWindow(SIZE sz,UINT nFlags)
   {

      throw interface_only_exception(get_app());

   }


   bool interaction_base::ResizeWindow(int32_t cx,int32_t cy,UINT nFlags)
   {

      throw interface_only_exception(get_app());

   }


   bool interaction_base::ResizeWindow(SIZE sz,UINT nFlags)
   {

      throw interface_only_exception(get_app());

   }


   bool interaction_base::SetWindowPos(int32_t z,const RECT & rect,UINT nFlags)
   {

      throw interface_only_exception(get_app());

   }


   bool interaction_base::defer_set_window_pos(int32_t z,int32_t x,int32_t y,int32_t cx,int32_t cy,UINT nFlags) // only set_windows_pos if get_parent()->ScreenToClient(get_window_rect) different of rect(x, y, cx, cy)
   {

      throw interface_only_exception(get_app());

      return false;

   }


   void interaction_base::_001DrawThis(::draw2d::graphics * pgraphics)
   {

      throw interface_only_exception(get_app());

   }


   void interaction_base::_001DrawChildren(::draw2d::graphics *pdc)
   {

      throw interface_only_exception(get_app());

   }


   void interaction_base::_001Print(::draw2d::graphics * pgraphics)
   {

      throw interface_only_exception(get_app());

   }


   void interaction_base::_001OnDraw(::draw2d::graphics *pdc)
   {

      throw interface_only_exception(get_app());

   }


   void interaction_base::draw_control_background(::draw2d::graphics *pdc)
   {

      throw interface_only_exception(get_app());

   }


   sp(interaction) interaction_base::_001FromPoint(point64 pt,bool bTestedIfParentVisible)
   {

      throw interface_only_exception(get_app());

   }


   bool interaction_base::_001IsPointInside(point64 pt)
   {

      throw interface_only_exception(get_app());

   }


   sp(interaction) interaction_base::get_child_by_name(const char * pszName,int32_t iLevel)
   {

      throw interface_only_exception(get_app());

   }


   sp(interaction) interaction_base::get_child_by_id(id id,int32_t iLevel)
   {

      throw interface_only_exception(get_app());

   }


   LRESULT interaction_base::send(::message::base * pbase)
   {

      message_handler(pbase);

      return pbase->get_lresult();

   }


   // pbase object should be allocated with new in
   // base or derived object and will be delete after
   // handling
   bool interaction_base::post(::message::base * pbase)
   {

      throw interface_only_exception(get_app());

   }


   LRESULT interaction_base::send_message(UINT uiMessage,WPARAM wparam,lparam lparam)
   {

      throw interface_only_exception(get_app());

   }


#ifdef LINUX


   LRESULT interaction_base::send_message(XEvent * pevent)
   {

      throw interface_only_exception(get_app());

   }


#endif


   bool interaction_base::IsWindowVisible()
   {

      throw interface_only_exception(get_app());

   }


   bool interaction_base::ModifyStyle(uint32_t dwRemove,uint32_t dwAdd,UINT nFlags)
   {

      throw interface_only_exception(get_app());

   }


   bool interaction_base::ModifyStyleEx(uint32_t dwRemove,uint32_t dwAdd,UINT nFlags)
   {

      throw interface_only_exception(get_app());

   }


   bool interaction_base::ShowWindow(int32_t nCmdShow)
   {

      throw interface_only_exception(get_app());

   }


   sp(::user::frame_window) interaction_base::GetTopLevelFrame() const
   {

      throw interface_only_exception(get_app());

   }


   void interaction_base::SendMessageToDescendants(UINT message,WPARAM wparam,lparam lparam,bool bDeep,bool bOnlyPerm)
   {

      throw interface_only_exception(get_app());

   }


   void interaction_base::pre_translate_message(signal_details * pobj)
   {

      UNREFERENCED_PARAMETER(pobj);

   }


   oswindow interaction_base::get_handle() const
   {

      return NULL;

   }


   bool interaction_base::subclass_window(oswindow posdata)
   {

      throw interface_only_exception(get_app());

   }


   oswindow interaction_base::unsubclass_window()
   {

      throw interface_only_exception(get_app());

      return NULL;

   }


#if defined(METROWIN) || defined(APPLE_IOS)


   bool interaction_base::initialize(::user::native_window_initialize * pinitialize)
   {

      throw interface_only_exception(get_app());

      return true;

   }


#endif


   bool interaction_base::create_window(const RECT & rect,sp(interaction)pparent,id id)
   {

      throw interface_only_exception(get_app());

      return true;

   }


   bool interaction_base::create_window(const char * lpszClassName,const char * lpszWindowName,uint32_t dwStyle,const RECT & rect,sp(interaction) pParentWnd,id id,sp(::create_context) pContext)
   {

      throw interface_only_exception(get_app());

      return false;

   }


   bool interaction_base::create_window_ex(uint32_t dwExStyle,const char * lpszClassName,const char * lpszWindowName,uint32_t dwStyle,const RECT & rect,sp(interaction) pParentWnd,id id,LPVOID lpParam)
   {

      throw interface_only_exception(get_app());

      return true;

   }


   void interaction_base::BringToTop(int nCmdShow)
   {

      throw interface_only_exception(get_app());

   }


   bool interaction_base::BringWindowToTop()
   {

      throw interface_only_exception(get_app());

   }


   bool interaction_base::IsWindow() const
   {

      throw interface_only_exception(get_app());

   }


   LONG interaction_base::get_window_long(int32_t nIndex) const
   {

      throw interface_only_exception(get_app());

   }


   LONG interaction_base::set_window_long(int32_t nIndex,LONG lValue)
   {

      throw interface_only_exception(get_app());

   }


   LONG_PTR interaction_base::get_window_long_ptr(int32_t nIndex) const
   {

      throw interface_only_exception(get_app());

   }


   LONG_PTR interaction_base::set_window_long_ptr(int32_t nIndex,LONG_PTR lValue)
   {

      throw interface_only_exception(get_app());

   }


   bool interaction_base::RedrawWindow(LPCRECT lpRectUpdate, ::draw2d::region* prgnUpdate, UINT flags)
   {

      throw interface_only_exception(get_app());

   }


   sp(interaction) interaction_base::ChildWindowFromPoint(POINT point)
   {

      throw interface_only_exception(get_app());

   }


   sp(interaction) interaction_base::ChildWindowFromPoint(POINT point,UINT nFlags)
   {

      throw interface_only_exception(get_app());

   }


   sp(interaction) interaction_base::GetNextWindow(UINT nFlag)
   {

      if(nFlag == GW_HWNDNEXT)
      {

         return get_next(true, NULL);

      }
      else
      {

         throw interface_only_exception(get_app());

      }

   }


   sp(interaction) interaction_base::get_next(bool bIgnoreChildren,int32_t * piLevel)
   {

      throw interface_only_exception(get_app());

   }


   bool interaction_base::is_message_only_window() const
   {

      throw interface_only_exception(get_app());

   }


   sp(interaction) interaction_base::GetTopWindow() const
   {

      throw interface_only_exception(get_app());

   }


   sp(interaction) interaction_base::GetWindow(UINT nCmd) const
   {

      throw interface_only_exception(get_app());

   }


   sp(interaction) interaction_base::GetActiveWindow()
   {

      throw interface_only_exception(get_app());

   }


   sp(interaction) interaction_base::SetFocus()
   {

      throw interface_only_exception(get_app());

   }


   sp(interaction) interaction_base::SetActiveWindow()
   {

      throw interface_only_exception(get_app());

   }


   bool interaction_base::SetForegroundWindow()
   {

      return true;

   }


   sp(interaction) interaction_base::GetLastActivePopup()
   {

      throw interface_only_exception(get_app());

   }


   void interaction_base::SetWindowText(const char * lpszString)
   {

      throw interface_only_exception(get_app());

   }


   strsize interaction_base::GetWindowText(LPTSTR lpszStringBuf,int32_t nMaxCount)
   {

      throw interface_only_exception(get_app());

   }


   string interaction_base::get_window_text()
   {

      throw interface_only_exception(get_app());

   }


   void interaction_base::GetWindowText(string & rString)
   {

      throw interface_only_exception(get_app());

   }


   strsize interaction_base::GetWindowTextLength()
   {

      throw interface_only_exception(get_app());

   }


   sp(interaction) interaction_base::EnsureTopLevel()
   {

      throw interface_only_exception(get_app());

   }


   sp(interaction) interaction_base::EnsureParentTopLevel()
   {

      throw interface_only_exception(get_app());

   }


   sp(interaction) interaction_base::GetTopLevel() const
   {

      throw interface_only_exception(get_app());

   }


   sp(interaction) interaction_base::GetParentTopLevel() const
   {

      throw interface_only_exception(get_app());

   }


   sp(frame_window) interaction_base::GetParentTopLevelFrame() const
   {

      throw interface_only_exception(get_app());

   }


   sp(::user::frame_window) interaction_base::EnsureParentFrame()
   {

      throw interface_only_exception(get_app());

   }


   LRESULT interaction_base::Default()
   {

      throw interface_only_exception(get_app());

   }


   uint32_t interaction_base::GetStyle() const
   {

      throw interface_only_exception(get_app());

   }


   uint32_t interaction_base::GetExStyle() const
   {

      throw interface_only_exception(get_app());

   }


   bool interaction_base::DestroyWindow()
   {

      throw interface_only_exception(get_app());

   }


   void interaction_base::PostNcDestroy()
   {

   }


   sp(::user::frame_window) interaction_base::GetParentFrame() const
   {

      throw interface_only_exception(get_app());

      return NULL;

   }


   void interaction_base::CalcWindowRect(LPRECT lprect,UINT nAdjustType)
   {

      throw interface_only_exception(get_app());

   }


   void interaction_base::RepositionBars(UINT nIDFirst,UINT nIDLast,id nIDLeftOver,
      UINT nFlag,LPRECT lpRectParam,
      LPCRECT lpRectClient,bool bStretch)
   {

      throw interface_only_exception(get_app());

   }


   sp(interaction) interaction_base::SetOwner(sp(interaction) pui)
   {

      throw interface_only_exception(get_app());

   }


   sp(interaction) interaction_base::SetParent(sp(interaction) pui)
   {

      throw interface_only_exception(get_app());

   }


   sp(interaction) interaction_base::GetOwner() const
   {

      throw interface_only_exception(get_app());

   }


   sp(interaction) interaction_base::GetParent() const
   {

      throw interface_only_exception(get_app());

   }


   sp(frame_window) interaction_base::GetFrame() const
   {

      throw interface_only_exception(get_app());

   }


   sp(::user::interaction) interaction_base::GetParentOwner() const
   {

      throw interface_only_exception(get_app());

   }


   sp(::user::interaction) interaction_base::GetTopLevelOwner() const
   {

      throw interface_only_exception(get_app());

   }


   sp(interaction) interaction_base::GetDescendantWindow(id iId) const
   {

      throw interface_only_exception(get_app());

   }


   void interaction_base::set_viewport_org(::draw2d::graphics * pgraphics)
   {

      throw interface_only_exception(get_app());

   }


   void interaction_base::viewport_client_to_screen(POINT * ppt)
   {

      throw interface_only_exception(get_app());

   }


   void interaction_base::viewport_screen_to_client(POINT * ppt)
   {

      throw interface_only_exception(get_app());

   }


   void interaction_base::viewport_client_to_screen(RECT * prect)
   {

      throw interface_only_exception(get_app());

   }


   void interaction_base::viewport_screen_to_client(RECT * prect)
   {

      throw interface_only_exception(get_app());

   }


   int32_t interaction_base::SetWindowRgn(HRGN hRgn,bool bRedraw)
   {

      throw interface_only_exception(get_app());

   }


   int32_t interaction_base::GetWindowRgn(HRGN hRgn)
   {

      throw interface_only_exception(get_app());

   }


   bool interaction_base::WfiIsZoomed()
   {

      throw interface_only_exception(get_app());

   }


   bool interaction_base::WfiIsFullScreen()
   {

      throw interface_only_exception(get_app());

   }


   bool interaction_base::WfiIsIconic()
   {

      return false;

   }


   bool interaction_base::CheckAutoCenter()
   {

      throw interface_only_exception(get_app());

   }


   void interaction_base::CenterWindow(sp(interaction) pAlternateOwner)
   {

      throw interface_only_exception(get_app());

   }


   LRESULT interaction_base::DefWindowProc(UINT uiMessage,WPARAM wparam,lparam lparam)
   {

      return 0;

   }


   void interaction_base::message_handler(signal_details * pobj)
   {

      throw interface_only_exception(get_app());

   }


   LRESULT interaction_base::message_handler(LPMESSAGE lpmessage)
   {

      throw interface_only_exception(get_app());

   }


#ifdef WINDOWSEX


   bool interaction_base::GetWindowPlacement(WINDOWPLACEMENT* lpwndpl)
   {

      throw interface_only_exception(get_app());

   }


   bool interaction_base::SetWindowPlacement(const WINDOWPLACEMENT* lpwndpl)
   {

      throw interface_only_exception(get_app());

   }


#endif


   bool interaction_base::pre_create_window(::user::create_struct& cs)
   {

      throw interface_only_exception(get_app());

   }


   bool interaction_base::IsTopParentActive()
   {

      throw interface_only_exception(get_app());

   }


   void interaction_base::ActivateTopParent()
   {

   }


   void interaction_base::UpdateDialogControls(command_target* pTarget,bool bDisableIfNoHandler)
   {

      //throw interface_only_exception(get_app());

   }


   void interaction_base::SetRedraw(bool bRedraw)
   {

      throw interface_only_exception(get_app());

   }


   bool interaction_base::GetUpdateRect(LPRECT lpRect,bool bErase)
   {

      throw interface_only_exception(get_app());

   }


   int32_t interaction_base::GetUpdateRgn(::draw2d::region* pRgn,bool bErase)
   {

      throw interface_only_exception(get_app());

   }


   void interaction_base::InvalidateRect(LPCRECT lpRect,bool bErase)
   {

      throw interface_only_exception(get_app());

   }


   void interaction_base::InvalidateRgn(::draw2d::region* pRgn,bool bErase)
   {

      throw interface_only_exception(get_app());

   }


   void interaction_base::ValidateRect(LPCRECT lpRect)
   {

      throw interface_only_exception(get_app());

   }


   void interaction_base::ValidateRgn(::draw2d::region* pRgn)
   {

      throw interface_only_exception(get_app());

   }


   void interaction_base::layout()
   {

      throw interface_only_exception(get_app());

   }


   void interaction_base::ShowOwnedPopups(bool bShow)
   {

      throw interface_only_exception(get_app());

   }


   bool interaction_base::attach(oswindow oswindow_New)
   {

      throw interface_only_exception(get_app());

   }


   oswindow interaction_base::detach()
   {

      throw interface_only_exception(get_app());

   }


   void interaction_base::pre_subclass_window()
   {

      throw interface_only_exception(get_app());

   }


   id interaction_base::run_modal_loop(::user::interaction * pui,uint32_t dwFlags,::base::live_object * pliveobject)
   {

      throw interface_only_exception(get_app());

   }


   id interaction_base::RunModalLoop(uint32_t dwFlags,::base::live_object * pliveobject)
   {

      throw interface_only_exception(get_app());

   }


   id interaction_base::_001RunModalLoop(uint32_t dwFlags,::base::live_object * pliveobject)
   {

      throw interface_only_exception(get_app());

      return id();

   }


   bool interaction_base::ContinueModal(int32_t iLevel)
   {

      throw interface_only_exception(get_app());

   }


   void interaction_base::EndModalLoop(id nResult)
   {

      throw interface_only_exception(get_app());

   }


   void interaction_base::EndAllModalLoops(id nResult)
   {

      throw interface_only_exception(get_app());

   }


   bool interaction_base::BaseOnControlEvent(control_event * pevent)
   {

      throw interface_only_exception(get_app());

   }


   bool interaction_base::post_message(UINT uiMessage,WPARAM wparam,lparam lparam)
   {

      throw interface_only_exception(get_app());

   }


   uint_ptr interaction_base::SetTimer(uint_ptr nIDEvent,UINT nElapse,void (CALLBACK* lpfnTimer)(oswindow,UINT,uint_ptr,uint32_t))
   {

      throw interface_only_exception(get_app());

   }


   bool interaction_base::KillTimer(uint_ptr nIDEvent)
   {

      throw interface_only_exception(get_app());

   }


   bool interaction_base::has_focus()
   {

      throw interface_only_exception(get_app());

   }


   sp(interaction) interaction_base::SetCapture(sp(interaction) pinterface)
   {

      throw interface_only_exception(get_app());

   }


   sp(interaction) interaction_base::GetCapture()
   {

      throw interface_only_exception(get_app());

   }


   sp(interaction) interaction_base::ReleaseCapture()
   {

      throw interface_only_exception(get_app());

   }


   void interaction_base::track_mouse_leave()
   {

      throw interface_only_exception(get_app());

   }


   void interaction_base::track_mouse_hover()
   {

      throw interface_only_exception(get_app());

   }


   void interaction_base::_001UpdateWindow()
   {

      throw interface_only_exception(get_app());

   }


   void interaction_base::_001WindowMinimize()
   {

      throw interface_only_exception(get_app());

   }


   void interaction_base::_001WindowMaximize()
   {

      throw interface_only_exception(get_app());

   }


   void interaction_base::_001WindowFullScreen()
   {

      throw interface_only_exception(get_app());

   }


   void interaction_base::_001WindowRestore()
   {

      throw interface_only_exception(get_app());

   }


   void interaction_base::GuieProc(signal_details * pobj)
   {

      throw interface_only_exception(get_app());

   }


   void interaction_base::_001DeferPaintLayeredWindowBackground(::draw2d::graphics * pdc)
   {

      throw interface_only_exception(get_app());

   }


   void interaction_base::_001OnDeferPaintLayeredWindowBackground(::draw2d::graphics * pdc)
   {

      throw interface_only_exception(get_app());

   }


   void interaction_base::OnLinkClick(const char * psz,const char * pszTarget)
   {

      throw interface_only_exception(get_app());

   }


   bool interaction_base::create_message_queue(const char * pszName)
   {

      throw interface_only_exception(get_app());

   }


   void interaction_base::WalkPreTranslateTree(signal_details * pobj)
   {

      throw interface_only_exception(get_app());

   }


   void interaction_base::WalkPreTranslateTree(sp(::user::interaction) puiStop,signal_details * pobj)
   {

      throw interface_only_exception(get_app());

   }


   void interaction_base::on_select()
   {

      throw interface_only_exception(get_app());

   }


   bool interaction_base::is_place_holder()
   {

      throw interface_only_exception(get_app());

   }


   ::visual::e_cursor interaction_base::get_cursor()
   {

      throw interface_only_exception(get_app());

   }


   void interaction_base::set_cursor(::visual::e_cursor ecursor)
   {

      throw interface_only_exception(get_app());

   }


   bool interaction_base::can_merge(sp(::user::interaction) pui)
   {

      throw interface_only_exception(get_app());

      return false;

   }


   bool interaction_base::merge(sp(::user::interaction) pui)
   {

      throw interface_only_exception(get_app());

      return false;

   }


   sp(interaction) interaction_base::get_bottom_child()
   {

      throw interface_only_exception(get_app());

   }


   sp(interaction) interaction_base::get_top_child()
   {

      throw interface_only_exception(get_app());

   }


   sp(interaction) interaction_base::under_sibling()
   {

      throw interface_only_exception(get_app());

   }


   sp(interaction) interaction_base::under_sibling(sp(interaction) pui)
   {

      throw interface_only_exception(get_app());

   }


   sp(interaction) interaction_base::above_sibling()
   {

      throw interface_only_exception(get_app());

   }


   void interaction_base::mouse_hover_add(sp(::user::interaction) pinterface)
   {

      throw interface_only_exception(get_app());

   }

   void interaction_base::mouse_hover_remove(sp(::user::interaction) pinterface)
   {

      throw interface_only_exception(get_app());

   }


   sp(interaction) interaction_base::above_sibling(sp(interaction) pui)
   {

      throw interface_only_exception(get_app());

   }


   void interaction_base::on_keyboard_focus(::user::keyboard_focus * pfocus)
   {

   }


   sp(::user::interaction) interaction_base::get_os_focus_uie()
   {

      throw interface_only_exception(get_app());

      return NULL;

   }


   int32_t interaction_base::get_descendant_level(sp(::user::interaction) pui)
   {

      throw interface_only_exception(get_app());

      return -1;

   }


   bool interaction_base::is_descendant(sp(::user::interaction) pui,bool bIncludeSelf)
   {

      throw interface_only_exception(get_app());

      return false;

   }


   sp(::user::interaction) interaction_base::get_focusable_descendant(sp(::user::interaction) pui)
   {

      throw interface_only_exception(get_app());

      return NULL;

   }


   void interaction_base::_001OnTriggerMouseInside()
   {

      throw interface_only_exception(get_app());

   }


   bool interaction_base::update_data(bool bSaveAndValidate)
   {

      throw interface_only_exception(get_app());

      return false;

   }


   string interaction_base::get_window_default_matter()
   {

      throw interface_only_exception(get_app());

      return "";

   }


   string interaction_base::get_window_icon_matter()
   {

      throw interface_only_exception(get_app());

      return get_window_default_matter();

   }


   uint32_t interaction_base::get_window_default_style()
   {

      throw interface_only_exception(get_app());

      return 0;

   }


   ::user::interaction_base::e_type interaction_base::get_window_type()
   {

      return type_window;

   }


   bool interaction_base::post_simple_command(e_simple_command ecommand,lparam lparam)
   {

      post_message(message_simple_command,(WPARAM)ecommand,lparam);

      return true;

   }


   bool interaction_base::OnCommand(::message::base * pbase)
   {

      throw interface_only_exception(get_app());

      return false;

   }


   bool interaction_base::OnNotify(::message::base * pbase)
   {

      throw interface_only_exception(get_app());

      return false;

   }


   bool interaction_base::OnChildNotify(::message::base * pbase)
   {

      throw interface_only_exception(get_app());

      return false;

   }


   bool interaction_base::on_simple_command(e_simple_command ecommand,lparam lparam,LRESULT & lresult)
   {

      throw interface_only_exception(get_app());

      return false;

   }


   bool interaction_base::is_selected(::data::item * pitem)
   {

      throw interface_only_exception(get_app());

      return false;

   }


   bool interaction_base::_001HasCommandHandler(id id)
   {

      throw interface_only_exception(get_app());

      return false;

   }


   bool interaction_base::track_popup_menu(sp(::user::menu_base_item) pitem,int32_t iFlags)
   {

      throw interface_only_exception(get_app());

      return false;

   }


   bool interaction_base::track_popup_menu(sp(::xml::node) lpnode,int32_t iFlags)
   {

      throw interface_only_exception(get_app());

      return false;

   }


   bool interaction_base::track_popup_xml_matter_menu(const char * pszMatter,int32_t iFlags)
   {

      throw interface_only_exception(get_app());

      return false;

   }



   bool interaction_base::track_popup_menu(sp(::user::menu_base_item) pitem,int32_t iFlags,signal_details * pobj)
   {

      throw interface_only_exception(get_app());

      return false;

   }


   bool interaction_base::track_popup_menu(sp(::xml::node) lpnode,int32_t iFlags,signal_details * pobj)
   {

      throw interface_only_exception(get_app());

      return false;

   }


   bool interaction_base::track_popup_xml_matter_menu(const char * pszMatter,int32_t iFlags,signal_details * pobj)
   {

      throw interface_only_exception(get_app());

      return false;

   }


   bool interaction_base::track_popup_menu(sp(::user::menu_base_item) pitem,int32_t iFlags,int32_t x,int32_t y)
   {

      throw interface_only_exception(get_app());

      return false;

   }

   bool interaction_base::track_popup_menu(sp(::xml::node) lpnode,int32_t iFlags,int32_t x,int32_t y)
   {

      throw interface_only_exception(get_app());

      return false;

   }


   bool interaction_base::track_popup_xml_matter_menu(const char * pszMatter,int32_t iFlags,int32_t x,int32_t y)
   {

      throw interface_only_exception(get_app());

      return false;

   }


   void interaction_base::WfiEnableFullScreen(bool bEnable)
   {

      throw interface_only_exception(get_app());

   }


   bool interaction_base::WfiIsFullScreenEnabled()
   {

      throw interface_only_exception(get_app());

      return false;

   }


   bool interaction_base::WfiClose()
   {

      throw interface_only_exception(get_app());

      return false;

   }


   bool interaction_base::WfiRestore(bool bForceNormal)
   {

      throw interface_only_exception(get_app());

      return false;

   }


   bool interaction_base::WfiMinimize()
   {

      throw interface_only_exception(get_app());

      return false;

   }


   bool interaction_base::WfiMaximize()
   {

      throw interface_only_exception(get_app());

      return false;

   }


   bool interaction_base::WfiFullScreen()
   {

      throw interface_only_exception(get_app());

      return false;

   }


   bool interaction_base::WfiUp()
   {

      throw interface_only_exception(get_app());

      return false;

   }


   bool interaction_base::WfiDown()
   {

      throw interface_only_exception(get_app());

      return false;

   }


   bool interaction_base::WfiNotifyIcon()
   {

      throw interface_only_exception(get_app());

      return false;

   }


   EAppearance interaction_base::get_appearance()
   {

      return AppearanceNone;

   }


   EAppearance interaction_base::get_appearance_before()
   {

      return AppearanceNone;

   }


   bool interaction_base::set_appearance(EAppearance eappearance)
   {

      throw interface_only_exception(get_app());

      return false;

   }


   bool interaction_base::set_appearance_before(EAppearance eappearance)
   {

      throw interface_only_exception(get_app());

      return false;

   }


   void interaction_base::show_keyboard(bool bShow)
   {

      UNREFERENCED_PARAMETER(bShow);

   }


   LRESULT interaction_base::call_message_handler(UINT message,WPARAM wparam,LPARAM lparam)
   {

      throw interface_only_exception(get_app());

      return 0;

   }


   void interaction_base::keep_alive(::base::live_object * pliveobject)
   {

      throw interface_only_exception(get_app());

   }


   bool interaction_base::SetWindowPos(int32_t z,int32_t x,int32_t y,int32_t cx,int32_t cy,UINT nFlags)
   {

      throw interface_only_exception(get_app());

      return false;

   }


   id interaction_base::GetDlgCtrlId() const
   {

      throw interface_only_exception(get_app());

   }


   id interaction_base::SetDlgCtrlId(id id)
   {

      throw interface_only_exception(get_app());

   }


   oswindow interaction_base::get_safe_handle() const
   {

      if(this == NULL)
         return NULL;

      return get_handle();

   }




} // namespace user
