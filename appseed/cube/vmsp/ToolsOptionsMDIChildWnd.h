#pragma once

class CLASS_DECL_CA2_CUBE CToolsOptionsMDIChildWnd :
   public ::userbase::mdi_child_window
{
   // // DECLARE_DYNCREATE(CToolsOptionsMDIChildWnd)
public:
   CToolsOptionsMDIChildWnd(::ca::application * papp);

// Attributes
public:
   simple_toolbar   m_toolbar;

// Operations
public:
   void TransparentFrameWndUpdateBars();

// Overrides
   virtual bool _000OnPosCreate();
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(CToolsOptionsMDIChildWnd)
   protected:
   virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, create_context* pContext);
   //}}AFX_VIRTUAL

// Implementation
protected:
   virtual ~CToolsOptionsMDIChildWnd();

   // Generated message ::collection::map functions
   //{{AFX_MSG(CToolsOptionsMDIChildWnd)
      // NOTE - the ClassWizard will add and remove member functions here.
   //}}AFX_MSG
   ()
};

