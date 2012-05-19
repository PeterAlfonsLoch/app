#pragma once

class SimpleMDIChildWindow;

class CLASS_DECL_ca2 SimpleMDIFrameWindow : 
   virtual public simple_frame_window
{
public:
   SimpleMDIFrameWindow(::ca::application * papp);

   void MDIActivate(::user::interaction* pWndActivate);
   SimpleMDIChildWindow* MDIGetActive(bool* pbMaximized = NULL) const;
   void MDIIconArrange();
   void MDIMaximize(::user::interaction* pWnd);
   void MDINext();
   void MDIPrev();
   void MDIRestore(::user::interaction* pWnd);
   void MDITile();
   void MDICascade();
   void MDITile(int nType);
   void MDICascade(int nType);
   SimpleMDIChildWindow* CreateNewChild(::ca::type_info pClass, const char * pszMatter,
      HMENU hMenu = NULL, HACCEL hAccel = NULL);

// Overridables
   // ca2 API 1.0 backward compatible CreateClient hook (called by OnCreateClient)
   virtual bool CreateClient(LPCREATESTRUCT lpCreateStruct, ::userbase::menu* pWindowMenu);
   // customize if using an 'Window' menu with non-standard IDs
   virtual HMENU GetWindowMenuPopup(HMENU hMenuBar);

// Implementation
public:
   ::user::interaction* m_pguieMdiClient;       // MDI Client ::ca::window handle

#ifdef _DEBUG
   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;
#endif
   virtual bool pre_create_window(CREATESTRUCT& cs);
   virtual bool LoadFrame(const char * pszMatter,
            DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE,
            ::user::interaction* pParentWnd = NULL,
            ::ca::create_context* pContext = NULL);
   virtual bool OnCreateClient(LPCREATESTRUCT lpcs, ::ca::create_context* pContext);
   virtual void pre_translate_message(gen::signal_object * pobj);
   virtual void on_update_frame_title(bool bAddToTitle);
   virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg);
      
   virtual void OnUpdateFrameMenu(HMENU hMenuAlt);
   virtual void DelayUpdateFrameMenu(HMENU hMenuAlt);

protected:
   virtual LRESULT DefWindowProc(UINT nMsg, WPARAM wParam, LPARAM lParam);
   virtual bool OnCommand(WPARAM wParam, LPARAM lParam);

   //{{__MSG(SimpleMDIFrameWindow)
   DECL_GEN_SIGNAL(_001OnDestroy)
   void OnSize(UINT nType, int cx, int cy);
   void OnUpdateMDIWindowCmd(cmd_ui * pcmdui);
   bool OnMDIWindowCmd(UINT nID);
   void OnWindowNew();
   LRESULT OnCommandHelp(WPARAM wParam, LPARAM lParam);
   void OnIdleUpdateCmdUI();
   LRESULT OnMenuChar(UINT nChar, UINT, ::userbase::menu*);
   //}}__MSG
   //()
};
