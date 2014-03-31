#pragma once


namespace user
{


   class CLASS_DECL_BASE window_interface :
      virtual public elemental,
      virtual public command_target,
      virtual public text_interface,
      virtual public check_interface,
      virtual public draw_interface
   {
   public:

      
      enum ETranslucency
      {
         
         TranslucencyNone,
         TranslucencyPresent,
         TranslucencyTotal
         
      };

      
      enum e_message
      {
      
         MessageBaseWndGetProperty = WM_USER + 96,
         MessageProperty,
         MessageGeneralEvent
            
      };

      
      enum EProperty
      {
         
         PropertyBaseWndInterface = 0,
         PropertyDrawBaseWndInterface
            
      };

      
      enum EGeneralEvent
      {
         
         GeneralEventPosCreate1,
         GeneralEventPosCreate2,
         GeneralEventPosCreate3,
         GeneralEventPosCreate4,
         GeneralEventPosCreate5
            
      };

      
      sp(interaction)                     m_pui;
      // window rectangle relative to the parent
      // this rectangle comes before in importance compared to m_rectWindow
      // m_rectWindow should be sychronized and recalculated based
      // on m_rectParentClient values of the window and its ascendants.
      rect64                              m_rectParentClient;
      bool                                m_bVisible;
      bool                                m_bVoidPaint;
      draw_interface *                    m_pdrawinterfaceBackground;
      bool                                m_bBackgroundBypass;
      ETranslucency                       m_etranslucency;

      static window_interface *           g_pwndLastLButtonDown;



      window_interface();
      window_interface(sp(base_application) papp);
      virtual ~window_interface();


      virtual bool is_window_enabled();
      virtual bool enable_window(bool bEnable = true);
      virtual void _000OnDraw(::draw2d::graphics * pdc);

      virtual void PreSubClassWindow();


      virtual void GetClientRect(LPRECT lprect);
      virtual void GetClientRect(__rect64 * lprect);
      virtual void GetWindowRect(LPRECT lprect);
      virtual void GetWindowRect(__rect64 * lprect);
      virtual void ClientToScreen(LPRECT lprect);
      virtual void ClientToScreen(__rect64 * lprect);
      virtual void ClientToScreen(LPPOINT lppoint);
      virtual void ClientToScreen(__point64 * lppoint);
      virtual void ScreenToClient(LPRECT lprect);
      virtual void ScreenToClient(__rect64 * lprect);
      virtual void ScreenToClient(LPPOINT lppoint);
      virtual void ScreenToClient(__point64 * lppoint);


      virtual window_interface * window_interface_get_parent();


      /*oswindow GetHandle() const;
      uint32_t GetStyle() const;
      uint32_t GetExStyle() const;
      bool ModifyStyle(uint32_t dwRemove, uint32_t dwAdd, UINT uiFlags);
      bool ModifyStyleEx(uint32_t dwRemove, uint32_t dwAdd, UINT uiFlags);
      static bool ModifyStyle(oswindow oswindow, uint32_t dwRemove, uint32_t dwAdd, UINT uiFlags);
      static bool ModifyStyleEx(oswindow oswindow, uint32_t dwRemove, uint32_t dwAdd, UINT uiFlags);

      LRESULT SendMessage(UINT message, WPARAM wParam = 0, LPARAM lParam = 0);
      bool PostMessage(UINT message, WPARAM wParam = 0, LPARAM lParam = 0);*/

      // Window size and position Functions
      /*bool IsIconic() const;
      bool IsZoomed() const;

      int32_t GetWindowText(string & str) const;
      int32_t GetWindowText(wchar_t * lpsz, int32_t iLen) const;
      int32_t GetWindowTextLen() const;*/




      virtual void install_message_handling(::message::dispatch * pinterface);

      virtual void _on_start_user_message_handler();


      virtual void UpdateWindow();
      virtual void Invalidate(bool bErase = TRUE);


      virtual bool RedrawOptimize(LPRECT lprectOut, LPCRECT lpcrect1, LPCRECT lpcrect2);
      virtual void RedrawOptimize(rect_array & array);
      virtual bool _001IsBackgroundBypass();
      virtual bool _001IsTransparent();
      virtual bool _001IsTranslucent();
      virtual bool _001HasTranslucency();

      virtual ETranslucency _001GetTranslucency();






      virtual void _001RedrawWindow();
      virtual void _001DrawBackground(::draw2d::graphics * pdc, LPRECT lprect);


      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_VSIGNAL(_001OnBaseWndGetProperty);

     virtual LRESULT _001BaseWndGetProperty(EProperty eproperty, LPARAM lparam);

      virtual window * get_wnd();

      
      enum EOptimize
      {
         
         OptimizeNone,
         OptimizeThis
            
      };
      

      void Optimize008(
         ::user::oswindow_tree::Array & oswindowtreea,
         LPCRECT lpcrect);

      EOptimize Optimize008(
         ::user::oswindow_tree::Array & oswindowtreea,
         HRGN hrgn);

      EOptimize Optimize008(
         ::user::oswindow_tree & oswindowtree,
         HRGN hrgn);



      void TwfGetWndArray(::user::interaction_ptr_array & wndpa);
      void TwfGetWndArray(::user::oswindow_array & oswindowa);

      virtual bool Redraw(rect_array & recta);
      virtual bool Redraw(LPCRECT lprect = NULL, ::draw2d::region * prgn = NULL);
      virtual bool Redraw(::draw2d::graphics * pdc);

      void _001BaseWndInterfaceMap();

   };
   

} // namespace user


