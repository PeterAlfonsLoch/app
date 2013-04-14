#pragma once


namespace user
{


   class view_creator_data;


} // namespace user


class view_update_hint;



class CLASS_DECL_ca2 view :
   virtual public database::user::interaction
{
public:


   enum e_hint
   {
      
      hint_begin = 1984,
      hint_set_edit_file = hint_begin,
      hint_add_location,
      hint_end,

   };



   sp(::user::document_interface)    m_spdocument;

   view();
   virtual ~view() = 0;

   sp(::user::document_interface) get_document() const;

   template < class DOCUMENT >
   ::ca::data * get_data();

   template < class DOCUMENT >
   DOCUMENT * get_typed_document();


   virtual void install_message_handling(::ca::message::dispatch * pinterface);

   virtual bool IsSelected(const ::ca::object* pDocItem) const; // support for OLE

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

   virtual void OnPrepareDC(::ca::graphics * pgraphics, CPrintInfo* pInfo = ::null());

   //virtual void OnInitialUpdate(); // called first time after construct
   DECL_GEN_VSIGNAL(_001OnInitialUpdate) // called first time after construct


   // Activation
   virtual void OnActivateView(bool bActivate, sp(view) pActivateView,
               sp(view) pDeactiveView);
   virtual void OnActivateFrame(UINT nState, sp(frame_window) pFrameWnd);

   // General drawing/updating
   virtual void on_update(sp(view) pSender, LPARAM lHint, ::ca::object* pHint);
   virtual void _001OnDraw(::ca::graphics * pgraphics);
   virtual void OnViewUpdateHint(sp(view) pSender, LPARAM lHint, view_update_hint * pHint);



    sp(::user::interaction) create_view(::ca::type_info * info, sp(::user::document_interface) pdoc = ::null(), sp(::user::interaction) pwndParent = ::null(), ::id id = ::id(), sp(::user::interaction) pviewLast = ::null());
   static sp(::user::interaction) s_create_view(::ca::type_info * info, sp(::user::document_interface) pdoc, sp(::user::interaction) pwndParent, id id, sp(::user::interaction) pviewLast = ::null());
   static sp(::user::interaction) s_create_view(::ca::create_context * pContext, sp(::user::interaction) pwndParent, id id);

   template < class VIEW >
   sp(VIEW) create_view(::user::document_interface * pdoc = ::null(), sp(::user::interaction) pwndParent = ::null(), ::id id = ::id(), sp(::user::interaction) pviewLast = ::null());

   template < class VIEW >
   sp(VIEW) create_view(::user::interaction * pwndParent, ::id id = ::id(), sp(::user::interaction) pviewLast = ::null());

   template < class VIEW >
   sp(VIEW) create_view(::user::view_creator_data * pcreatordata, sp(::user::interaction) pviewLast = ::null());


   static sp(::user::document_interface) get_document(sp(::user::interaction) pguie);

   virtual void dump(dump_context &) const;
   virtual void assert_valid() const;

   // Advanced: for implementing custom print preview
/*   bool DoPrintPreview(UINT nIDResource, sp(view) pPrintView,
         sp(::ca::type_info) pPreviewViewClass, CPrintPreviewState* pState);*/

   virtual void CalcWindowRect(LPRECT lpClientRect,
      UINT nAdjustType = adjustBorder);
   virtual CScrollBar* GetScrollBarCtrl(int32_t nBar) const;


   virtual void on_draw_view_nc(::ca::graphics * pdc);
   virtual void on_draw_view(::ca::graphics * pdc, spa(::ca::data) spadata);
   virtual void defer_draw_view(::ca::graphics * pdc);

   virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg);

   virtual bool pre_create_window(CREATESTRUCT& cs);
   virtual void PostNcDestroy();

   // friend classes that call protected view overridables
   friend class user::document_interface;
//   friend class document_template;
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
   //int32_t OnMouseActivate(sp(::ca::window) pDesktopWnd, UINT nHitTest, UINT message);
   // commands
   void OnUpdateSplitCmd(cmd_ui* pCmdUI);
   bool OnSplitCmd(UINT nID);
   void OnUpdateNextPaneMenu(cmd_ui* pCmdUI);
   bool OnNextPaneCmd(UINT nID);

   // not mapped commands - must be mapped in derived class
   void OnFilePrint();
   void OnFilePrintPreview();

   // TODO: could return a kind of - also TODO - JOB object in case of assynchronous call
   virtual void collaborate(::ca::job * pjob);
   virtual int32_t  get_total_page_count(::ca::job * pjob);

   DECL_GEN_SIGNAL(_001OnView)
   DECL_GEN_SIGNAL(_001OnLButtonDown)
   DECL_GEN_SIGNAL(_001OnLButtonUp)
   DECL_GEN_SIGNAL(_001OnMouseMove)

   virtual ::user::interaction::e_type get_window_type();

   virtual void on_simple_view_update_hint(sp(::view) pviewSender, e_hint ehint, ::ca::object * phint);

};

class view_update_hint :
   virtual public ::ca::object
{
public:
   enum etype
   {
      TypeOpenDocument,
   };
public:
   view_update_hint(sp(::ca::application) papp);
   etype m_etype;
};




#pragma once


namespace user
{


   class frame_window_interface;
   class document;
   class frame_window;


} // namespace user



struct PrintPreviewState;

class CPrintDialog;     // forward reference (see afxdlgs.h)
class BasePreviewView;     // forward reference (see afxpriv.h)
class CSplitterWnd;     // forward reference (see afxext.h)
class COleServerDoc;    // forward reference (see afxole.h)

typedef uint32_t DROPEFFECT;
class COleDataObject;   // forward reference (see afxole.h)

namespace user
{

   class CLASS_DECL_ca2 view :
      virtual public ::view
   {
   public:

      view(sp(::ca::application) papp);
      virtual ~view();

      virtual void on_select();

      // each view can display one or more documents but has only one document interface
      //sp(::user::document) get_document() const;

      virtual bool IsSelected(const ::ca::object* pDocItem) const; // support for OLE

      // OLE scrolling support (used for drag/drop as well)
      virtual bool OnScroll(UINT nScrollCode, UINT nPos, bool bDoScroll = TRUE);
      virtual bool OnScrollBy(size sizeScroll, bool bDoScroll = TRUE);

      // OLE drag/drop support
      virtual DROPEFFECT OnDragEnter(COleDataObject* pDataObject,
         uint32_t dwKeyState, point point);
      virtual DROPEFFECT OnDragOver(COleDataObject* pDataObject,
         uint32_t dwKeyState, point point);
      virtual void OnDragLeave();
      virtual bool OnDrop(COleDataObject* pDataObject,
         DROPEFFECT dropEffect, point point);
      virtual DROPEFFECT OnDropEx(COleDataObject* pDataObject,
         DROPEFFECT dropDefault, DROPEFFECT dropList, point point);
      virtual DROPEFFECT OnDragScroll(uint32_t dwKeyState, point point);



      virtual void OnActivateView(bool bActivate, sp(::view) pActivateView, sp(::view) pDeactiveView);
      virtual void OnActivateFrame(UINT nState, sp(frame_window) pFrameWnd);

      virtual void on_update(sp(::view) pSender, LPARAM lHint, ::ca::object* pHint);

      virtual void dump(dump_context &) const;
      virtual void assert_valid() const;



      virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg);

      virtual bool pre_create_window(CREATESTRUCT& cs);

      DECL_GEN_SIGNAL(_001OnMouseActivate)
      DECL_GEN_SIGNAL(_001OnUpdateSplitCmd)
      DECL_GEN_SIGNAL(_001OnSplitCmd)
      DECL_GEN_SIGNAL(_001OnUpdateNextPaneMenu)
      DECL_GEN_SIGNAL(_001OnNextPaneCmd)

      DECL_GEN_SIGNAL(_001OnFilePrint)
      DECL_GEN_SIGNAL(_001OnFilePrintPreview)


      DECL_GEN_SIGNAL(_001OnRButtonDown)
      DECL_GEN_SIGNAL(_001OnLButtonDown)
      DECL_GEN_SIGNAL(_001OnMButtonDown)

      virtual void install_message_handling(::ca::message::dispatch * pinterface);
   };


} // namespace user
