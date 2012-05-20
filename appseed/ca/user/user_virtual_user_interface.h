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
   ph(::user::interaction)    m_pparent;
   ph(::user::interaction)    m_pguieMessage;


   virtual_user_interface();
   virtual_user_interface(::ca::application * papp);
   virtual ~virtual_user_interface();

   virtual void message_handler(gen::signal_object * pobj);
   virtual ::ca::graphics * GetDC();
   ::user::interaction * SetParent(::user::interaction * pguieParent);
   bool ShowWindow(int nCmdShow);
   virtual bool ReleaseDC(::ca::graphics *);
   virtual ::user::interaction * GetParent();

   virtual void _001WindowMaximize();
   virtual void _001WindowRestore();
   virtual bool SetWindowPos(int z, int x, int y, int cx, int cy, UINT nFlags);
   void SetWindowText(const char * psz);


   virtual ::user::interaction * GetDescendantWindow(id id);

   id SetDlgCtrlId(id id);
   id GetDlgCtrlId();


   // Advanced: virtual AdjustWindowRect
   enum AdjustType { adjustBorder = 0, adjustOutside = 1 };
   virtual void CalcWindowRect(LPRECT lpClientRect, UINT nAdjustType = adjustBorder);
   virtual ::frame_window * GetParentFrame();

   virtual user::interaction * SetFocus();

   void RepositionBars(UINT nIDFirst, UINT nIDLast, id nIDLeftOver, UINT nFlags, LPRECT lpRectParam, LPCRECT lpRectClient, bool bStretch);


   //virtual int RunModalLoop(DWORD dwFlags = 0, ::ca::live_object * pliveobject = NULL);


   virtual bool DestroyWindow();

   virtual DWORD GetStyle();
   virtual DWORD GetExStyle();
   virtual LRESULT Default();

   virtual void SetFont(::ca::font* pFont, bool bRedraw = TRUE);
   virtual ::ca::font* GetFont();

   LRESULT SendMessage(UINT uiMessage, WPARAM wparam = 0, LPARAM lparam = 0);

   // as hosting ::ca::window
   virtual void install_message_handling(::gen::message::dispatch * pinterface);
   // as virtual ::ca::window
   virtual void _002InstallMessageHandling(::gen::message::dispatch * pinterface);


   bool create_message_window();

// Timer Functions
   virtual uint_ptr SetTimer(uint_ptr nIDEvent, UINT nElapse,
      void (CALLBACK* lpfnTimer)(HWND, UINT, uint_ptr, DWORD));
   virtual bool KillTimer(uint_ptr nIDEvent);


   virtual bool IsWindow();
   virtual bool IsWindowEnabled();
   virtual bool IsWindowVisible();

   virtual void VirtualOnSize();
   virtual bool create(::user::interaction *pparent, id id);
   virtual bool create(const char * lpszClassName,
      const char * lpszWindowName, DWORD dwStyle,
      const RECT& rect,
      ::user::interaction* pParentWnd, id id,
      ::ca::create_context* pContext = NULL);
   virtual bool CreateEx(DWORD dwExStyle, const char * lpszClassName,
      const char * lpszWindowName, DWORD dwStyle,
      const RECT& rect,
      ::user::interaction* pParentWnd, id id,
      LPVOID lpParam = NULL);


   virtual ::frame_window * EnsureParentFrame();
   virtual ::user::interaction * GetTopLevelParent();
   virtual ::user::interaction * EnsureTopLevelParent();
   virtual ::frame_window * GetTopLevelFrame();

   using ::user::interaction::GetWindowText;
   strsize GetWindowText(LPTSTR lpszStringBuf, int nMaxCount);
   void GetWindowText(string & str);


   virtual void on_delete(::ca::ca * poc);


   DECL_GEN_SIGNAL(_001OnSize)
   DECL_GEN_SIGNAL(_001OnMove)
   DECL_GEN_SIGNAL(_001OnDestroy)
   DECL_GEN_SIGNAL(_001OnNcDestroy)
   DECL_GEN_SIGNAL(_001OnClose)

   void SendMessageToDescendants(UINT message,   WPARAM wParam = 0, LPARAM lParam = 0, bool bDeep = true, bool bOnlyPerm = 0);

   virtual bool PostMessage(UINT uiMessage, WPARAM wparam, LPARAM lparam);


};
