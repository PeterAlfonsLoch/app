#pragma once

class PlaylistDoc;
class PaneView;

class CLASS_DECL_ca PlaylistListView   :
   public simple_form_list_view
{
public:

   
   enum EMode
   {
      ModeMinimum    = 1,
      ModeNormal     = 2
   };
   
   
   ::user::list_cache         m_cache;
   HENHMETAFILE         m_enhmetafile;
   ENHMETAHEADER        m_emh;
   ::user::buffer       m_gdibuffer;
   image_list *          m_pimagelistSubItemHover;
   image_list *          m_pimagelistItemHover;
   image_list *          m_pimagelistNormal;

   EMode                  m_emode;
   string               m_str;


   PlaylistListView(::ca::application * papp);


   void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);


   PlaylistDoc * get_document() const;

   virtual void _001OnButtonAction(user::control * pcontrol);
   virtual void _001OnInitializeForm(user::control * pcontrol);
   virtual void _001InsertColumns();
   virtual void _001DrawBackground(::ca::graphics *pdc, LPRECT lprect);
   PaneView * GetParentPane();
   virtual bool _001OnRemoveItem(INT_PTR iItem);
   void _001OnDraw(::ca::graphics * pdc);
   void UpdateDrawingObjects();
   index _001GetItemImage(index iItem, index iSubItem, index iListItem);
   EMode GetMode();

   void SetMode(EMode emode);
   
   virtual bool _001GetItemText(string &str, index iItem, index iSubItem, index iListItem);
   virtual count _001GetItemCount();
   DECL_GEN_VSIGNAL(_001OnInitialUpdate)
   DECL_GEN_SIGNAL(_001OnCreate)
   virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
   virtual void on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint);
   virtual ~PlaylistListView();
#ifdef _DEBUG
   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;
#endif
   virtual bool WndFrameworkDownUpGetUpEnable();
   virtual bool WndFrameworkDownUpGetDownEnable();
   virtual bool TransparentFrameWndDownUpGetDownEnable();
   virtual bool TransparentFrameWndDownUpGetUpEnable();

   DECL_GEN_SIGNAL(_001OnLButtonDblClk)
   DECL_GEN_SIGNAL(_001OnContextMenu)
   DECL_GEN_SIGNAL(_001OnSize)
   DECL_GEN_SIGNAL(_001OnEditRemove)
   DECL_GEN_SIGNAL(_001OnUpdateEditRemove)
   DECL_GEN_SIGNAL(_001OnPlaylistExecutePlay)
   DECL_GEN_SIGNAL(_001OnUpdatePlaylistExecutePlay)
};

#ifndef _DEBUG  // debug version in xfplayer4View.cpp
inline PlaylistDoc* PlaylistListView::get_document() const
   { return dynamic_cast < PlaylistDoc * > (::view::get_document()); }
#endif
