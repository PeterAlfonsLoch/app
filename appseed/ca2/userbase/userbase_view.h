#pragma once


namespace userbase
{
   class frame_window_interface;
}


class ::userbase::document;
class userbase::frame_window;
struct PrintPreviewState;

class CPrintDialog;     // forward reference (see afxdlgs.h)
class BasePreviewView;     // forward reference (see afxpriv.h)
class CSplitterWnd;     // forward reference (see afxext.h)
class COleServerDoc;    // forward reference (see afxole.h)

typedef DWORD DROPEFFECT;
class COleDataObject;   // forward reference (see afxole.h)

namespace userbase
{

   class CLASS_DECL_ca2 view :
      virtual public ::view
   {
   public:

      view(::ca::application * papp);

      virtual void on_select();

      ::userbase::document* get_document() const;

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



      virtual void OnActivateView(BOOL bActivate, ::view* pActivateView, ::view* pDeactiveView);
      virtual void OnActivateFrame(UINT nState, ::frame_window* pFrameWnd);

      virtual void on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint);

      virtual ~view();
#ifdef _DEBUG
      virtual void dump(dump_context&) const;
      virtual void assert_valid() const;
#endif //_DEBUG



      virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg);

      virtual BOOL pre_create_window(CREATESTRUCT& cs);

      // friend classes that call protected ::view overridables
      friend class ::userbase::document;
      friend class ::userbase::document_template;
      friend class BasePreviewView;
      friend class userbase::frame_window;
      friend class mdi_frame_window;
      friend class mdi_child_window;
      friend class CSplitterWnd;
      friend class OleServerDoc;
      friend class DocObjectServer;

      friend class userbase::frame_window_interface;

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

      virtual void install_message_handling(::gen::message::dispatch * pinterface);
   };


} // namespace userbase
