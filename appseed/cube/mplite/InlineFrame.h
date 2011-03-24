#pragma once


class CLASS_DECL_CA2_CUBE InlineFrame :
   public simple_frame_window
{
public:
   InlineFrame(::ca::application * papp);

   DECL_GEN_SIGNAL(_001OnEraseBkgnd)

   virtual BOOL OnCreateControlBars(frame_window* pWndFrame, frame_window* pWndDoc);
   virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
   void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);
   virtual ~InlineFrame();
#ifdef _DEBUG
   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;
#endif

   //simple_toolbar    m_wndToolBar;
   //CDialogBar m_wndDlgBar;
   //CReBar m_wndReBar;
   //COleDropTarget   m_dropTarget;
   //COleResizeBar   m_wndResizeBar;

   afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};



