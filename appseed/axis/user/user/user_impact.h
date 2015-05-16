#pragma once


#define WM_VIEW (WM_USER + 1023)



namespace user
{


   class view_creator_data;


   class view_update_hint;


   class frame_window;



   struct PrintPreviewState;

   class CPrintDialog;     // forward reference (see afxdlgs.h)
   class BasePreviewView;     // forward reference (see afxpriv.h)
   class CSplitterWnd;     // forward reference (see afxext.h)
   class COleServerDoc;    // forward reference (see afxole.h)

   typedef uint32_t DROPEFFECT;
   class COleDataObject;   // forward reference (see afxole.h)

} // namespace user

namespace aura
{

   class CLASS_DECL_AXIS impact :
      virtual public ::database::user::interaction
   {
   public:


      enum e_hint
      {

         hint_begin = 1984,
         hint_set_edit_file = hint_begin,
         hint_add_location,
         hint_save_to_ostream,
         hint_end

      };



      ::aura::document *      m_pdocument;



      impact();
      virtual ~impact();

      ::aura::document * get_document() const;

      template < class DATA >
      DATA * get_typed_data();

      template < class DOCUMENT >
      DOCUMENT * get_typed_document();

      template < class DOCUMENT >
      ::data::data * get_typed_document_data();

      virtual void install_message_handling(::message::dispatch * pinterface);

      virtual bool IsSelected(const object* pDocItem) const; // support for OLE

      // OLE scrolling support (used for drag/drop as well)
      virtual bool OnScroll(UINT nScrollCode, UINT nPos, bool bDoScroll = TRUE);
      virtual bool OnScrollBy(size sizeScroll, bool bDoScroll = TRUE);

      // OLE drag/drop support
      /*   virtual DROPEFFECT OnDragEnter(COleDataObject* pDataObject,
      uint32_t dwKeyState, point point);
      virtual DROPEFFECT OnDragOver(COleDataObject* pDataObject,
      uint32_t dwKeyState, point point);
      virtual void OnDragLeave();
      virtual bool OnDrop(COleDataObject* pDataObject,
      DROPEFFECT dropEffect, point point);
      virtual DROPEFFECT OnDropEx(COleDataObject* pDataObject,
      DROPEFFECT dropDefault, DROPEFFECT dropList, point point);
      virtual DROPEFFECT OnDragScroll(uint32_t dwKeyState, point point);*/

      virtual void OnPrepareDC(::draw2d::graphics * pgraphics, CPrintInfo* pInfo = NULL);

      //virtual void OnInitialUpdate(); // called first time after construct
      DECL_GEN_SIGNAL(_001OnInitialUpdate); // called first time after construct


         // Activation
         virtual void OnActivateView(bool bActivate, sp(impact) pActivateView, sp(impact) pDeactiveView);
      virtual void OnActivateFrame(UINT nState, sp(::user::frame_window) pFrameWnd);

      // General drawing/updating
      virtual void on_update(::aura::impact * pSender, LPARAM lHint, ::object* pHint);
      //virtual void _001OnDraw(::draw2d::graphics * pgraphics);
      virtual void OnViewUpdateHint(sp(impact) pSender, LPARAM lHint, ::user::view_update_hint * pHint);



      ::user::interaction * create_view(type * info, ::aura::document * pdoc = NULL, const RECT & rect = ::null_rect(), ::user::interaction * pwndParent = NULL, ::id id = ::id(), ::user::interaction * pviewLast = NULL);
      static ::user::interaction * s_create_view(type * info, ::aura::document * pdoc,const RECT & rect, ::user::interaction * pwndParent,id id,::user::interaction * pviewLast = NULL);
      static ::user::interaction * s_create_view(::create * pContext,const RECT & rect,::user::interaction * pwndParent,id id);

      template < class VIEW >
      VIEW * create_view(::aura::document * pdoc = NULL,const RECT & rect = ::null_rect(),::user::interaction * pwndParent = NULL,::id id = ::id(),::user::interaction * pviewLast = NULL);

      template < class VIEW >
      VIEW * create_view(const RECT & rect, ::user::interaction * pwndParent,::id id = ::id(),::user::interaction * pviewLast = NULL);

      template < class VIEW >
      VIEW * create_view(::user::view_creator_data * pcreatordata, ::user::interaction * pviewLast = NULL);


      static ::aura::document * get_document(::user::interaction * pui);

      virtual void dump(dump_context &) const;
      virtual void assert_valid() const;

      // Advanced: for implementing custom print preview
      /*   bool DoPrintPreview(UINT nIDResource, sp(view) pPrintView,
      sp(type) pPreviewViewClass, CPrintPreviewState* pState);*/

      virtual void CalcWindowRect(LPRECT lpClientRect,
         UINT nAdjustType = adjustBorder);
//      virtual CScrollBar* GetScrollBarCtrl(int32_t nBar) const;


      //virtual void on_draw_view_nc(::draw2d::graphics * pdc);
      //virtual void on_draw_view(::draw2d::graphics * pdc, spa(::data::data) spadata);
      //virtual void defer_draw_view(::draw2d::graphics * pdc);

      virtual bool _001OnCmdMsg(::aura::cmd_msg * pcmdmsg);

      virtual bool pre_create_window(::user::create_struct& cs);
      virtual void PostNcDestroy();


      DECL_GEN_SIGNAL(_001OnCreate);
         DECL_GEN_SIGNAL(_001OnDestroy);
         void OnPaint();
      //int32_t OnMouseActivate(::window_sp pDesktopWnd, UINT nHitTest, UINT message);
      // commands
      void OnUpdateSplitCmd(cmd_ui* pCmdUI);
      bool OnSplitCmd(UINT nID);
      void OnUpdateNextPaneMenu(cmd_ui* pCmdUI);
      bool OnNextPaneCmd(UINT nID);

      // not mapped commands - must be mapped in derived class
      void OnFilePrint();
      void OnFilePrintPreview();

      // TODO: could return a kind of - also TODO - JOB object in case of assynchronous call
      virtual void collaborate(::job * pjob);
      virtual int32_t  get_total_page_count(::job * pjob);

      DECL_GEN_SIGNAL(_001OnView);
         DECL_GEN_SIGNAL(_001OnLButtonDown);
         DECL_GEN_SIGNAL(_001OnLButtonUp);
         DECL_GEN_SIGNAL(_001OnMouseMove);

         virtual ::user::interaction::e_type get_window_type();

      virtual void on_simple_view_update_hint(sp(::aura::impact) pviewSender, e_hint ehint, object * phint);



      virtual void on_select();

      // each view can display one or more documents but has only one document interface
      //::aura::document * get_document() const;

      //      virtual bool IsSelected(const object* pDocItem) const; // support for OLE

      // OLE scrolling support (used for drag/drop as well)
      //      virtual bool OnScroll(UINT nScrollCode, UINT nPos, bool bDoScroll = TRUE);
      //    virtual bool OnScrollBy(size sizeScroll, bool bDoScroll = TRUE);

      // OLE drag/drop support
#ifndef ANDROID
      //virtual DROPEFFECT OnDragEnter(COleDataObject* pDataObject,
      //   uint32_t dwKeyState, point point);
      //virtual DROPEFFECT OnDragOver(COleDataObject* pDataObject,
      //   uint32_t dwKeyState, point point);
      //virtual void OnDragLeave();
      //virtual bool OnDrop(COleDataObject* pDataObject,
      //   DROPEFFECT dropEffect, point point);
      //virtual DROPEFFECT OnDropEx(COleDataObject* pDataObject,
      //   DROPEFFECT dropDefault, DROPEFFECT dropList, point point);
      //virtual DROPEFFECT OnDragScroll(uint32_t dwKeyState, point point);
#endif


      //virtual void OnActivateView(bool bActivate, sp(::aura::impact) pActivateView, sp(::aura::impact) pDeactiveView);
      //virtual void OnActivateFrame(UINT nState, sp(::user::frame_window) pFrameWnd);

      //virtual void on_update(::aura::impact * pSender, LPARAM lHint, object* pHint);

      //      virtual void dump(dump_context &) const;
      //    virtual void assert_valid() const;



      //      virtual bool _001OnCmdMsg(::aura::cmd_msg * pcmdmsg);

      //      virtual bool pre_create_window(::user::create_struct& cs);

      DECL_GEN_SIGNAL(_001OnMouseActivate);
         DECL_GEN_SIGNAL(_001OnUpdateSplitCmd);
         DECL_GEN_SIGNAL(_001OnSplitCmd);
         DECL_GEN_SIGNAL(_001OnUpdateNextPaneMenu);
         DECL_GEN_SIGNAL(_001OnNextPaneCmd);

         DECL_GEN_SIGNAL(_001OnFilePrint);
         DECL_GEN_SIGNAL(_001OnFilePrintPreview);


         DECL_GEN_SIGNAL(_001OnRButtonDown);
         //         DECL_GEN_SIGNAL(_001OnLButtonDown);
         DECL_GEN_SIGNAL(_001OnMButtonDown);

         //         virtual void install_message_handling(::message::dispatch * pinterface);

         virtual bool _001HasCommandHandler(id id);

         virtual void walk_pre_translate_tree(signal_details * pobj,sp(::user::interaction) puiStop);


         virtual string calc_data_id();

   };


} // namespace user



