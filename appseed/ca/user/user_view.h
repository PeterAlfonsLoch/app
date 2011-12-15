#pragma once


class view_update_hint;


class CLASS_DECL_ca view :
   virtual public database::user::interaction
{
public:

   sp(::ca::data)    m_spdata;
   sp(::document)    m_spdocument;

   view();
   virtual ~view() = 0;

   document * get_document() const;
   ::ca::data * get_data() const;

   virtual void install_message_handling(::gen::message::dispatch * pinterface);

   virtual BOOL IsSelected(const ::radix::object* pDocItem) const; // support for OLE

   // OLE scrolling support (used for drag/drop as well)
   virtual BOOL OnScroll(UINT nScrollCode, UINT nPos, BOOL bDoScroll = TRUE);
   virtual BOOL OnScrollBy(size sizeScroll, BOOL bDoScroll = TRUE);

   // OLE drag/drop support
/*   virtual DROPEFFECT OnDragEnter(COleDataObject* pDataObject,
      DWORD dwKeyState, point point);
   virtual DROPEFFECT OnDragOver(COleDataObject* pDataObject,
      DWORD dwKeyState, point point);
   virtual void OnDragLeave();
   virtual BOOL OnDrop(COleDataObject* pDataObject,
      DROPEFFECT dropEffect, point point);
   virtual DROPEFFECT OnDropEx(COleDataObject* pDataObject,
      DROPEFFECT dropDefault, DROPEFFECT dropList, point point);
   virtual DROPEFFECT OnDragScroll(DWORD dwKeyState, point point);*/

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



   ::user::interaction * create_view(::ca::type_info info, document * pdoc = NULL, ::user::interaction * pwndParent = NULL, id id = id(), ::user::interaction * pviewLast = NULL);
   static ::user::interaction * s_create_view(::ca::type_info info, document * pdoc, ::user::interaction * pwndParent, id id, ::user::interaction * pviewLast = NULL);
   static ::user::interaction * s_create_view(::ca::create_context * pContext, ::user::interaction * pwndParent, id id);

   template < class VIEW >
   VIEW * create_view(document * pdoc = NULL, ::user::interaction * pwndParent = NULL, id id = id(), ::user::interaction * pviewLast = NULL);


   static document * get_document(::user::interaction * pguie);

#ifdef _DEBUG
   virtual void dump(dump_context&) const;
   virtual void assert_valid() const;
#endif //_DEBUG

   // Advanced: for implementing custom print preview
/*   BOOL DoPrintPreview(UINT nIDResource, view * pPrintView,
         ::ca::type_info pPreviewViewClass, CPrintPreviewState* pState);*/

   virtual void CalcWindowRect(LPRECT lpClientRect,
      UINT nAdjustType = adjustBorder);
   virtual CScrollBar* GetScrollBarCtrl(int nBar) const;


   virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg);

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
   void OnPaint();
   //int OnMouseActivate(::ca::window* pDesktopWnd, UINT nHitTest, UINT message);
   // commands
   void OnUpdateSplitCmd(cmd_ui* pCmdUI);
   BOOL OnSplitCmd(UINT nID);
   void OnUpdateNextPaneMenu(cmd_ui* pCmdUI);
   BOOL OnNextPaneCmd(UINT nID);

   // not mapped commands - must be mapped in derived class
   void OnFilePrint();
   void OnFilePrintPreview();

   // TODO: could return a kind of - also TODO - JOB object in case of assynchronous call
   virtual void collaborate(::ca::job * pjob);
   virtual int  get_total_page_count(::ca::job * pjob);

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

   void OnPaint();

};



