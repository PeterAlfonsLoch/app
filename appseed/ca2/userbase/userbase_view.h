#pragma once


namespace userbase
{


   class frame_window_interface;
   class document;
   class frame_window;


} // namespace userbase



struct PrintPreviewState;

class CPrintDialog;     // forward reference (see afxdlgs.h)
class BasePreviewView;     // forward reference (see afxpriv.h)
class CSplitterWnd;     // forward reference (see afxext.h)
class COleServerDoc;    // forward reference (see afxole.h)

typedef uint32_t DROPEFFECT;
class COleDataObject;   // forward reference (see afxole.h)

namespace userbase
{

   class CLASS_DECL_ca2 view :
      virtual public ::view
   {
   public:

      view(::ca::application * papp);

      virtual void on_select();

      // each view can display one or more documents but has only one document interface
      //::userbase::document* get_document() const;

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



      virtual void OnActivateView(bool bActivate, ::view* pActivateView, ::view* pDeactiveView);
      virtual void OnActivateFrame(UINT nState, ::frame_window* pFrameWnd);

      virtual void on_update(::view * pSender, LPARAM lHint, ::ca::object* pHint);

      virtual ~view();
#ifdef DEBUG
      virtual void dump(dump_context &) const;
      virtual void assert_valid() const;
#endif //DEBUG



      virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg);

      virtual bool pre_create_window(CREATESTRUCT& cs);

      // friend classes that call protected ::view overridables
      friend class ::userbase::document;
      friend class ::userbase::document_template;
      friend class BasePreviewView;
      friend class ::userbase::frame_window;
      friend class mdi_frame_window;
      friend class mdi_child_window;
      friend class CSplitterWnd;
      friend class OleServerDoc;
      friend class DocObjectServer;

      friend class ::userbase::frame_window_interface;

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


} // namespace userbase
