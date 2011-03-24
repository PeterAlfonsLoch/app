#pragma once


class CLASS_DECL_CA2_CUBE XfplayerFrame :
   public ::userbase::mdi_child_window
{
public:

   CMenuV033 * m_pmenuv033;

   XfplayerFrame(::ca::application * papp);
   virtual ~XfplayerFrame();

    

   virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
   virtual BOOL LoadFrame(const char * pszMatter, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, ::user::interaction * pParentWnd = NULL, create_context* pContext = NULL);
   virtual BOOL DestroyWindow();
   
#ifdef _DEBUG
   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;
#endif

   afx_msg void OnClose();
   afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
   afx_msg void OnSize(UINT nType, int cx, int cy);
   afx_msg void OnDestroy();
};

