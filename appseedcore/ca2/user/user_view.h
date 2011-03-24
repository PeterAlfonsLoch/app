#pragma once

class view_update_hint;

class CLASS_DECL_ca view :
   virtual public database::user::interaction
{
public:

   sp(::ca::data)    m_spdata;
   sp(::document)    m_spdocument;

   view();

   document * get_document() const;
   ::ca::data * get_data() const;

   virtual void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);

   virtual BOOL IsSelected(const ::radix::object* pDocItem) const; // support for OLE

   // OLE scrolling support (used for drag/drop as well)
   virtual BOOL OnScroll(UINT nScrollCode, UINT nPos, BOOL bDoScroll = TRUE);
   virtual BOOL OnScrollBy(size sizeScroll, BOOL bDoScroll = TRUE);

   // OLE drag/drop support
   virtual DROPEFFECT OnDragEnter(COleDataObject* pDataObject,
      DWORD dwKeyState, point point);
   virtual DROPEFFECT OnDragOver(COleDataObject* pDataObject,
      DWORD dwKeyState, point point);
   virtual void OnDragLeave();
   virtual BOOL OnDrop(COleDataObject* pDataObject,
      DROPEFFECT dropEffect, point point);
   virtual DROPEFFECT OnDropEx(COleDataObject* pDataObject,
      DROPEFFECT dropDefault, DROPEFFECT dropList, point point);
   virtual DROPEFFECT OnDragScroll(DWORD dwKeyState, point point);

   virtual void OnPrepareDC(::ca::graphics * pgraphics, CPrintInfo* pInfo = NULL);

   //virtual void OnInitialUpdate(); // called first time after construct
   DECL_GEN_VSIGNAL(_001OnInitialUpdate) // called first time after construct


   // Activation
   virtual void OnActivateView(BOOL bActivate, view * pActivateView,
               view * pDeactiveView);
   virtual void OnActivateFrame(UINT nState, frame_window* pFrameWnd);

   // General drawing/updating
   virtual void on_update(view * pSender, LPARAM lHint, ::radix::object* pHint);
   virtual void OnDraw(::ca::graphics * pgraphics);
   virtual void OnViewUpdateHint(view * pSender, LPARAM lHint, view_update_hint * pHint);


   static ::user::interaction * create_view(::ca::type_info info, document * pdoc, ::user::interaction * pwndParent, id id, ::user::interaction * pviewLast = NULL);
   static ::user::interaction * create_view(create_context * pContext, ::user::interaction * pwndParent, id id);

   static document * get_document(::user::interaction * pguie);

// Implementation
public:
   virtual ~view() = 0;
#ifdef _DEBUG
   virtual void dump(dump_context&) const;
   virtual void assert_valid() const;
#endif //_DEBUG

   // Advanced: for implementing custom print preview
   BOOL DoPrintPreview(UINT nIDResource, view * pPrintView,
         ::ca::type_info pPreviewViewClass, CPrintPreviewState* pState);

   virtual void CalcWindowRect(LPRECT lpClientRect,
      UINT nAdjustType = adjustBorder);
   virtual CScrollBar* GetScrollBarCtrl(int nBar) const;


public:
   virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg);
      
protected:
   virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
   virtual void PostNcDestroy();

   // friend classes that call protected view overridables
   friend class document;
   friend class document_template;
   friend class CPreviewView;
   friend class frame_window;
   friend class CMDIFrameWnd;
   friend class CMDIChildWnd;
   friend class CSplitterWnd;
   friend class COleServerDoc;
   friend class CDocObjectServer;
   friend class SimpleMDIFrameWindow;
   friend class SimpleMDIChildWindow;

   DECL_GEN_SIGNAL(_001OnCreate)
   DECL_GEN_SIGNAL(_001OnDestroy)
   afx_msg void OnPaint();
   //afx_msg int OnMouseActivate(::ca::window* pDesktopWnd, UINT nHitTest, UINT message);
   // commands
   afx_msg void OnUpdateSplitCmd(cmd_ui* pCmdUI);
   afx_msg BOOL OnSplitCmd(UINT nID);
   afx_msg void OnUpdateNextPaneMenu(cmd_ui* pCmdUI);
   afx_msg BOOL OnNextPaneCmd(UINT nID);

   // not mapped commands - must be mapped in derived class
   afx_msg void OnFilePrint();
   afx_msg void OnFilePrintPreview();

   DECL_GEN_SIGNAL(_001OnView)
   DECL_GEN_SIGNAL(_001OnLButtonDown)
   DECL_GEN_SIGNAL(_001OnLButtonUp)
   DECL_GEN_SIGNAL(_001OnMouseMove)
};

class view_update_hint :
   virtual public ::radix::object
{
public:
   enum etype
   {
      TypeOpenDocument,
   };
public:
   view_update_hint(::ca::application * papp);
   etype m_etype;
};


/////////////////////////////////////////////////////////////////////////////
// class CCtrlView allows almost any control to be a view

class CLASS_DECL_ca AFX_NOVTABLE CCtrlView : public view
{
   // // DECLARE_DYNCREATE(CCtrlView)

public:
   CCtrlView(const char * lpszClass, DWORD dwStyle);

// Attributes
protected:
   string m_strClass;
   DWORD m_dwDefaultStyle;

// Overrides
   virtual void OnDraw(::ca::graphics * pgraphics);
   virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
   ~CCtrlView() = 0;
#ifdef _DEBUG
   virtual void dump(dump_context&) const;
   virtual void assert_valid() const;
#endif //_DEBUG

   afx_msg void OnPaint();
};

