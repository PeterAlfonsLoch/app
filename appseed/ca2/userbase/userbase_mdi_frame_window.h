#pragma once

namespace userbase
{

   /////////////////////////////////////////////////////////////////////////////
   // multiple document user interface support

   class CLASS_DECL_ca2 mdi_frame_window : virtual public frame_window
   {
   public:
      mdi_frame_window(::ca::application * papp);

   // Operations
      void MDIActivate(::user::interaction* pWndActivate);
      mdi_child_window* MDIGetActive(BOOL* pbMaximized = NULL) const;
      void MDIIconArrange();
      void MDIMaximize(::user::interaction* pWnd);
      void MDIPrev();
      void MDINext();
      void MDIRestore(::user::interaction* pWnd);
      ::userbase::menu* MDISetMenu(::userbase::menu* pFrameMenu, ::userbase::menu* pWindowMenu);
      void MDITile();
      void MDICascade();
      void MDITile(int nType);
      void MDICascade(int nType);
      mdi_child_window* CreateNewChild(::ca::type_info pClass, const char * pszMatter,
         HMENU hMenu = NULL, HACCEL hAccel = NULL);

   // Overridables
      // ca2 API 1.0 backward compatible CreateClient hook (called by OnCreateClient)
      virtual BOOL CreateClient(LPCREATESTRUCT lpCreateStruct, ::userbase::menu* pWindowMenu);
      // customize if using an 'Window' menu with non-standard IDs
      virtual HMENU GetWindowMenuPopup(HMENU hMenuBar);

   // Implementation
   public:
      ::user::interaction* m_pguieMdiClient;       // MDI Client ::ca::window handle

   #ifdef _DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif
      virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
      virtual BOOL LoadFrame(const char * pszMatter,
               DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE,
               ::user::interaction* pParentWnd = NULL,
               ::ca::create_context* pContext = NULL);
      virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, ::ca::create_context* pContext);
      virtual void pre_translate_message(gen::signal_object * pobj);
      virtual void on_update_frame_title(BOOL bAddToTitle);
      virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg);
         
      virtual void OnUpdateFrameMenu(HMENU hMenuAlt);
      virtual void DelayUpdateFrameMenu(HMENU hMenuAlt);
      virtual ::frame_window* GetActiveFrame();

   protected:
      virtual LRESULT DefWindowProc(UINT nMsg, WPARAM wParam, LPARAM lParam);
      virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);

      void OnDestroy();
      void OnSize(UINT nType, int cx, int cy);
      void OnUpdateMDIWindowCmd(cmd_ui * pcmdui);
      BOOL OnMDIWindowCmd(UINT nID);
      void OnWindowNew();
      LRESULT OnCommandHelp(WPARAM wParam, LPARAM lParam);
      void OnIdleUpdateCmdUI();
      LRESULT OnMenuChar(UINT nChar, UINT, ::userbase::menu*);
   };



} // namespace userbase