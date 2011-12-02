#pragma once




class CLASS_DECL_ca virtual_user_interface :
   virtual public ::user::interaction
{
public:
   virtual void message_handler(gen::signal_object * pobj);
   virtual ::ax::graphics * GetDC();
   ::user::interaction * SetParent(::user::interaction * pguieParent);
   BOOL ShowWindow(int nCmdShow);
   virtual BOOL ReleaseDC(::ax::graphics *);
   virtual ::user::interaction * GetParent();

   virtual void _001WindowMaximize();
   virtual void _001WindowRestore();
   virtual bool SetWindowPos(int z, int x, int y, int cx, int cy, UINT nFlags);
   void SetWindowText(const char * psz);

   virtual_user_interface();
   virtual_user_interface(::ax::application * papp);
   virtual ~virtual_user_interface();

   virtual ::user::interaction * GetDescendantWindow(id id);

   id SetDlgCtrlId(id id);
   id GetDlgCtrlId();


   // Advanced: virtual AdjustWindowRect
   enum AdjustType { adjustBorder = 0, adjustOutside = 1 };
   virtual void CalcWindowRect(LPRECT lpClientRect, UINT nAdjustType = adjustBorder);
   virtual frame_window* GetParentFrame();

   virtual user::interaction * SetFocus();

   void RepositionBars(UINT nIDFirst, UINT nIDLast, UINT nIDLeftOver,
      UINT nFlags, LPRECT lpRectParam, LPCRECT lpRectClient, BOOL bStretch);


   //virtual int RunModalLoop(DWORD dwFlags = 0, ::ax::live_object * pliveobject = NULL);


   virtual BOOL DestroyWindow();

   virtual DWORD GetStyle();
   virtual DWORD GetExStyle();
   virtual LRESULT Default();

   virtual void SetFont(::ax::font* pFont, BOOL bRedraw = TRUE);
   virtual ::ax::font* GetFont();

   LRESULT SendMessage(UINT uiMessage, WPARAM wparam = 0, LPARAM lparam = 0);

   // as hosting ::ax::window
   virtual void install_message_handling(::gen::message::dispatch * pinterface);
   // as virtual ::ax::window
   virtual void _002InstallMessageHandling(::gen::message::dispatch * pinterface);
   size              m_size;
   string            m_strWindowText;
   bool              m_bEnabled;
   ::ax::font_sp     m_spfont;
   bool              m_bCreate;

   bool create_message_window();

// Timer Functions
   virtual UINT_PTR SetTimer(UINT_PTR nIDEvent, UINT nElapse,
      void (CALLBACK* lpfnTimer)(HWND, UINT, UINT_PTR, DWORD));
   virtual BOOL KillTimer(UINT_PTR nIDEvent);


   virtual BOOL IsWindow();
   virtual BOOL IsWindowEnabled();
   virtual BOOL IsWindowVisible();

   virtual void VirtualOnSize();
   virtual bool create(::user::interaction *pparent, id id);
   virtual BOOL create(const char * lpszClassName,
      const char * lpszWindowName, DWORD dwStyle,
      const RECT& rect,
      ::user::interaction* pParentWnd, id id,
      ::ax::create_context* pContext = NULL);
   virtual BOOL CreateEx(DWORD dwExStyle, const char * lpszClassName,
      const char * lpszWindowName, DWORD dwStyle,
      const RECT& rect,
      ::user::interaction* pParentWnd, id id,
      LPVOID lpParam = NULL);

   ph(::user::interaction)    m_pparent;

   //virtual bool _001IsPointInside(POINT & point);
   ph(::user::interaction)    m_pguieMessage;

   virtual frame_window* EnsureParentFrame();
   virtual ::user::interaction* GetTopLevelParent();
   virtual ::user::interaction* EnsureTopLevelParent();
   frame_window* GetTopLevelFrame();

   using ::user::interaction::GetWindowText;
   int GetWindowText(LPTSTR lpszStringBuf, int nMaxCount);
   void GetWindowText(string & str);


   virtual void on_delete(::ax::ax * poc);


   DECL_GEN_SIGNAL(_001OnSize)
   DECL_GEN_SIGNAL(_001OnMove)
   DECL_GEN_SIGNAL(_001OnDestroy)
   DECL_GEN_SIGNAL(_001OnNcDestroy)
   DECL_GEN_SIGNAL(_001OnClose)

   void SendMessageToDescendants(UINT message,   WPARAM wParam = 0, LPARAM lParam = 0, BOOL bDeep = true, BOOL bOnlyPerm = 0);

   virtual BOOL PostMessage(UINT uiMessage, WPARAM wparam, LPARAM lparam);
};
