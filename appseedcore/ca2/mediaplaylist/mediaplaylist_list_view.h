#pragma once


namespace mediaplaylist
{


   class document;


   class CLASS_DECL_ca list_view   :
      public simple_form_list_view
   {
   public:


      enum e_mode
      {
         mode_minimum    = 1,
         mode_normal     = 2
      };


      ::user::list_cache      m_listcache;
#ifdef WINDOWS
      HENHMETAFILE            m_enhmetafile;
      ENHMETAHEADER           m_emh;
#endif
      image_list *            m_pimagelistSubItemHover;
      image_list *            m_pimagelistItemHover;
      image_list *            m_pimagelistNormal;

      e_mode                  m_emode;
      string                  m_str;


      list_view(::ca::application * papp);


      void install_message_handling(::user::win::message::dispatch * pinterface);


      document * get_document() const;

      virtual void _001OnButtonAction(user::control * pcontrol);
      virtual void _001OnInitializeForm(user::control * pcontrol);
      virtual void _001InsertColumns();
      virtual void _001DrawBackground(::ca::graphics *pdc, LPRECT lprect);
//      PaneView * GetParentPane();
      virtual bool _001OnRemoveItem(INT_PTR iItem);
      void _001OnDraw(::ca::graphics * pdc);
      void UpdateDrawingObjects();
      virtual void _001GetItemImage(::user::list_item * pitem);
      e_mode GetMode();

      void SetMode(e_mode emode);

      virtual void _001GetItemText(::user::list_item * pitem);
      virtual count _001GetItemCount();
      DECL_GEN_VSIGNAL(_001OnInitialUpdate)
      DECL_GEN_SIGNAL(_001OnCreate)
      virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
      virtual void on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint);
      virtual ~list_view();
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

      virtual count _001GetGroupCount();
      virtual count _001GetGroupItemCount(index iGroup);

      virtual ::count _001GetGroupMetaItemCount(index iGroup);
      virtual void _001GetGroupText(::user::list_item * pitem);
      virtual void _001GetGroupImage(::user::list_item * pitem);

   };



} // namespace mediaplaylist
