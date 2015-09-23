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
      virtual void message_handler(signal_details * pobj);
      //bool ShowWindow(int32_t nCmdShow);

      using ::user::interaction_base::SetWindowPos;
      virtual bool SetWindowPos(int_ptr z,int32_t x,int32_t y,int32_t cx,int32_t cy,UINT nFlags = SWP_SHOWWINDOW);


      virtual ::user::interaction * GetDescendantWindow(id id) const;


      // Advanced: virtual AdjustWindowRect
      enum AdjustType { adjustBorder = 0,adjustOutside = 1 };
      virtual void CalcWindowRect(LPRECT lpClientRect,UINT nAdjustType = adjustBorder);

      virtual ::user::interaction * SetFocus();

      //void RepositionBars(UINT nIDFirst,UINT nIDLast,id nIDLeftOver,UINT nFlags,LPRECT lpRectParam,LPCRECT lpRectClient,bool bStretch);


      //virtual int32_t RunModalLoop(uint32_t dwFlags = 0, ::object * pliveobject = NULL);


      virtual bool DestroyWindow();

      virtual uint32_t GetStyle() const;
      virtual uint32_t GetExStyle() const;
      virtual LRESULT Default();

      virtual LRESULT send_message(UINT uiMessage,WPARAM wparam = 0,lparam lparam = 0);

#ifdef LINUX

      virtual LRESULT send_message(XEvent * pevent);

#endif

      // as hosting interaction_impl
      virtual void install_message_handling(::message::dispatch * pinterface);
      // as virtual interaction_impl
      virtual void _002InstallMessageHandling(::message::dispatch * pinterface);


      virtual bool create_window(const RECT & rect, ::user::interaction *pparent,id id);
      virtual bool create_window(const char * lpszClassName,
         const char * lpszWindowName,uint32_t dwStyle,
         const RECT & rect,
         ::user::interaction * pParentWnd,id id,
         sp(::create) pContext = NULL);
      virtual bool create_window_ex(uint32_t dwExStyle,const char * lpszClassName,
         const char * lpszWindowName,uint32_t dwStyle,
         const RECT & rect,
         ::user::interaction * pParentWnd,id id,
         LPVOID lpParam = NULL);


      virtual bool ShowWindow(int32_t nCmdShow);


      virtual bool IsWindow() const;
      virtual bool is_window_enabled();
      virtual bool enable_window(bool bEnable = true);
      virtual bool IsWindowVisible();

      virtual void VirtualOnSize();







      DECL_GEN_SIGNAL(_001OnDestroy);
      DECL_GEN_SIGNAL(_001OnNcDestroy);

      void SendMessageToDescendants(UINT message,WPARAM wParam = 0,lparam lParam = 0,bool bDeep = true,bool bOnlyPerm = 0);

      virtual bool post_message(UINT uiMessage,WPARAM wparam,lparam lparam);

      virtual void set_viewport_org(::draw2d::graphics * pgraphics);


      virtual bool RedrawWindow(LPCRECT lpRectUpdate,::draw2d::region* prgnUpdate,UINT flags);

      virtual ::user::interaction * SetOwner(::user::interaction * pui);
      virtual ::user::interaction * GetOwner() const;

      using ::user::interaction_impl_base::GetWindowRect;
      void GetWindowRect(RECT64 * lprect);
      using ::user::interaction_impl_base::GetClientRect;
      void GetClientRect(RECT64 * lprect);

      virtual void ClientToScreen(LPRECT lprect);
      virtual void ClientToScreen(RECT64 * lprect);
      virtual void ClientToScreen(LPPOINT lppoint);
      virtual void ClientToScreen(POINT64 * lppoint);
      virtual void ScreenToClient(LPRECT lprect);
      virtual void ScreenToClient(RECT64 * lprect);
      virtual void ScreenToClient(LPPOINT lppoint);
      virtual void ScreenToClient(POINT64 * lppoint);


   };


} // namespace user



