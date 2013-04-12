#pragma once


class CLASS_DECL_ca virtual_user_interface :
   virtual public ::user::interaction
{
public:


   size                       m_size;
   string                     m_strWindowText;
   bool                       m_bEnabled;
   ::ca::font_sp              m_spfont;
   bool                       m_bCreate;
   sp(::user::interaction)    m_pparent;
   sp(::user::interaction)    m_pguieMessage;


   virtual_user_interface();
   virtual_user_interface(sp(::ca::application) papp);
   virtual ~virtual_user_interface();

   virtual void message_handler(::ca::signal_object * pobj);
   virtual ::ca::graphics * GetDC();
   sp(::user::interaction) set_parent(sp(::user::interaction) pguieParent);
   bool ShowWindow(int32_t nCmdShow);
   virtual bool ReleaseDC(::ca::graphics *);
   virtual sp(::user::interaction) get_parent() const;

   virtual void _001WindowMaximize();
   virtual void _001WindowRestore();
   virtual bool SetWindowPos(int32_t z, int32_t x, int32_t y, int32_t cx, int32_t cy, UINT nFlags);
   void SetWindowText(const char * psz);


   virtual sp(::user::interaction) GetDescendantWindow(id id);

   id SetDlgCtrlId(id id);
   id GetDlgCtrlId();


   // Advanced: virtual AdjustWindowRect
   enum AdjustType { adjustBorder = 0, adjustOutside = 1 };
   virtual void CalcWindowRect(LPRECT lpClientRect, UINT nAdjustType = adjustBorder);
   virtual sp(::frame_window) GetParentFrame();

   virtual sp(::user::interaction) SetFocus();

   void RepositionBars(UINT nIDFirst, UINT nIDLast, id nIDLeftOver, UINT nFlags, LPRECT lpRectParam, LPCRECT lpRectClient, bool bStretch);


   //virtual int32_t RunModalLoop(uint32_t dwFlags = 0, ::ca::live_object * pliveobject = ::null());


   virtual bool DestroyWindow();

   virtual uint32_t GetStyle();
   virtual uint32_t GetExStyle();
   virtual LRESULT Default();

   virtual void SetFont(::ca::font* pFont, bool bRedraw = TRUE);
   virtual ::ca::font* GetFont();

   virtual LRESULT send_message(UINT uiMessage, WPARAM wparam = 0, LPARAM lparam = 0);

#ifdef LINUX

   virtual LRESULT send_message(XEvent * pevent);

#endif

   // as hosting ::ca::window
   virtual void install_message_handling(::ca::message::dispatch * pinterface);
   // as virtual ::ca::window
   virtual void _002InstallMessageHandling(::ca::message::dispatch * pinterface);


   bool create_message_window();

// Timer Functions
   virtual uint_ptr SetTimer(uint_ptr nIDEvent, UINT nElapse,
      void (CALLBACK* lpfnTimer)(oswindow, UINT, uint_ptr, uint32_t));
   virtual bool KillTimer(uint_ptr nIDEvent);


   virtual bool IsWindow();
   virtual bool IsWindowEnabled();
   virtual bool IsWindowVisible();

   virtual void VirtualOnSize();
   virtual bool create(sp(::user::interaction)pparent, id id);
   virtual bool create(const char * lpszClassName,
      const char * lpszWindowName, uint32_t dwStyle,
      const RECT& rect,
      sp(::user::interaction) pParentWnd, id id,
      sp(::ca::create_context) pContext = ::null());
   virtual bool CreateEx(uint32_t dwExStyle, const char * lpszClassName,
      const char * lpszWindowName, uint32_t dwStyle,
      const RECT& rect,
      sp(::user::interaction) pParentWnd, id id,
      LPVOID lpParam = ::null());


   virtual sp(::frame_window) EnsureParentFrame();
   virtual sp(::user::interaction) GetTopLevelParent();
   virtual sp(::user::interaction) EnsureTopLevelParent();
   virtual sp(::frame_window) GetTopLevelFrame();

   using ::user::interaction::GetWindowText;
   strsize GetWindowText(LPTSTR lpszStringBuf, int32_t nMaxCount);
   void GetWindowText(string & str);




   DECL_GEN_SIGNAL(_001OnSize)
   DECL_GEN_SIGNAL(_001OnMove)
   DECL_GEN_SIGNAL(_001OnDestroy)
   DECL_GEN_SIGNAL(_001OnNcDestroy)

   void SendMessageToDescendants(UINT message,   WPARAM wParam = 0, LPARAM lParam = 0, bool bDeep = true, bool bOnlyPerm = 0);

   virtual bool PostMessage(UINT uiMessage, WPARAM wparam, LPARAM lparam);

   virtual void set_view_port_org(::ca::graphics * pgraphics);


};
