#pragma once


namespace user
{


   class CLASS_DECL_BASE interaction_child :
      virtual public ::user::interaction_impl_base
   {
   public:


      // interaction_impl rectangle relative to the parent
      // this rectangle comes before in importance compared to m_rectWindow
      // m_rectWindow should be sychronized and recalculated based
      // on m_rectParentClient values of the interaction_impl and its ascendants.
      size                                m_size;
      bool                                m_bEnabled;
      bool                                m_bCreate;
      sp(::user::interaction)             m_puiMessage;
      interaction *                       m_puiOwner;


      interaction_child();
      interaction_child(::aura::application * papp);
      virtual ~interaction_child();

      ::user::interaction_child * get_user_interaction_child() override;


      using ::user::interaction_base::message_handler;
      virtual void message_handler(signal_details * pobj) override;

      using ::user::interaction_base::SetWindowPos;
      //virtual bool SetWindowPos(int_ptr z,int32_t x,int32_t y,int32_t cx,int32_t cy,UINT nFlags = SWP_SHOWWINDOW) override;


      virtual ::user::interaction * GetDescendantWindow(id id) const override;


      // Advanced: virtual AdjustWindowRect
      enum AdjustType { adjustBorder = 0,adjustOutside = 1 };
      virtual void CalcWindowRect(LPRECT lpClientRect,UINT nAdjustType = adjustBorder) override;

      virtual bool SetFocus();

      //void RepositionBars(UINT nIDFirst,UINT nIDLast,id nIDLeftOver,UINT nFlags,LPRECT lpRectParam,LPCRECT lpRectClient,bool bStretch);


      //virtual int32_t RunModalLoop(uint32_t dwFlags = 0, ::object * pliveobject = NULL);


      virtual bool DestroyWindow() override;

      virtual uint32_t GetStyle() const override;
      virtual uint32_t GetExStyle() const override;
      virtual LRESULT Default() override;

      //virtual LRESULT send_message(UINT uiMessage,WPARAM wparam = 0,lparam lparam = 0);

#ifdef LINUX

      virtual LRESULT send_message(XEvent * pevent);

#endif

      // as hosting interaction_impl
      virtual void install_message_handling(::message::dispatch * pinterface) override;
      // as virtual interaction_impl
      virtual void _002InstallMessageHandling(::message::dispatch * pinterface);


      virtual bool create_window(::user::interaction * pui, const RECT & rect, ::user::interaction * pparent, id id) override;
      virtual bool create_window(::user::interaction * pui, const char * lpszClassName, const char * lpszWindowName, uint32_t dwStyle, const RECT & rect, ::user::interaction * pParentWnd, id id, ::create * pContext = NULL) override;
      virtual bool create_window_ex(::user::interaction * pui, uint32_t dwExStyle, const char * lpszClassName, const char * lpszWindowName, uint32_t dwStyle, const RECT & rect, ::user::interaction * puiParent, id id, LPVOID lpParam = NULL) override;


      virtual bool ShowWindow(int32_t nCmdShow) override;


      virtual bool IsWindow() const override;
      virtual bool is_window_enabled() override;
      virtual bool enable_window(bool bEnable = true) override;
      virtual bool IsWindowVisible() override;

      virtual void VirtualOnSize();







      DECL_GEN_SIGNAL(_001OnDestroy);
      DECL_GEN_SIGNAL(_001OnNcDestroy);
      DECL_GEN_SIGNAL(_001OnShowWindow);

      void SendMessageToDescendants(UINT message,WPARAM wParam = 0,lparam lParam = 0,bool bDeep = true,bool bOnlyPerm = 0) override;

      virtual bool post_message(UINT uiMessage,WPARAM wparam,lparam lparam) override;

      virtual void set_viewport_org(::draw2d::graphics * pgraphics) override;


      virtual bool RedrawWindow(LPCRECT lpRectUpdate,::draw2d::region* prgnUpdate,UINT flags) override;

      virtual ::user::interaction * SetOwner(::user::interaction * pui) override;
      virtual ::user::interaction * GetOwner() const override;

      using ::user::interaction_impl_base::GetWindowRect;
      bool GetWindowRect(RECT64 * lprect) override;
      using ::user::interaction_impl_base::GetClientRect;
      bool GetClientRect(RECT64 * lprect) override;

      virtual bool ClientToScreen(LPRECT lprect) override;
      virtual bool ClientToScreen(RECT64 * lprect) override;
      virtual bool ClientToScreen(LPPOINT lppoint) override;
      virtual bool ClientToScreen(POINT64 * lppoint) override;
      virtual bool ScreenToClient(LPRECT lprect) override;
      virtual bool ScreenToClient(RECT64 * lprect) override;
      virtual bool ScreenToClient(LPPOINT lppoint) override;
      virtual bool ScreenToClient(POINT64 * lppoint) override;

      virtual bool keyboard_focus_OnKillFocus() override;


   };


} // namespace user



