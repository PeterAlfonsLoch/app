#pragma once


namespace filemanager
{


   class CLASS_DECL_CORE tree :
      virtual public ::userfs::tree,
      virtual public ::filemanager::data_interface
   {
   public:


      enum e_message
      {
         MessageMainPost,
      };
      enum EMessageMainPost
      {
         MessageMainPostCreateImageListItemRedraw,
      };

      enum ETimer
      {
         TimerDelayedListUpdate = 100,
         TimerCreateImageList
      };

      context_menu                   m_contextmenu;

      critical_section        m_csBrowse;
      bool                    m_bCreateImageList;
      bool                    m_bCreateImageListRedraw;
      int32_t                     m_iAnimate;
      bool                    m_bTimer123;
      stringa                 m_straUpdatePtrFilter;
      mutex                   m_mutexMissinUpdate;
      stringa                 m_straMissingUpdate;
      bool                    m_bDelayedListUpdate;
#ifdef WINDOWSEX
      map < EFolder, EFolder, IShellFolder *, IShellFolder *> m_mapFolder;
#endif
      sp(::data::tree_item)        m_pdataitemCreateImageListStep;
      string                  m_strPath;
      //sp(image_list)            m_pimagelistFs;
      int32_t   m_iDefaultImage;
      int32_t   m_iDefaultImageSelected;


      tree(sp(base_application) papp);
      virtual ~tree();


      virtual void _001InsertColumns();
      //virtual void _001CreateImageList(CColumn & column);
      virtual void _001UpdateImageList(sp(::data::tree_item) pitem);

      DECL_GEN_VSIGNAL(_001OnTimer);


      virtual void _017Synchronize(::action::context actioncontext);
      void install_message_handling(::message::dispatch * pinterface);


      void _StartCreateImageList(::user::interaction * pui);
      void _StopCreateImageList(::user::interaction * pui);
      void _CreateImageListStep();

      // user::tree
      virtual void _001OnOpenItem(::data::tree_item * pitem, ::action::context actioncontext);
      virtual void _001OnItemExpand(::data::tree_item * pitem, ::action::context actioncontext);
      virtual void _001OnItemCollapse(::data::tree_item * pitem, ::action::context actioncontext);


      virtual void _017OpenFolder(sp(::fs::item)  item, ::action::context actioncontext);

      virtual COLORREF get_background_color();


#ifdef WINDOWSEX

      int32_t MapToCSIDL(EFolder efolder);

      IShellFolder * _001GetFolder(EFolder efolder);

#endif


      void _017PreSynchronize(::action::context actioncontext);
      void TakeAnimationSnapshot();
      virtual void StartAnimation();
      DECL_GEN_SIGNAL(_001OnMainPostMessage);
      void GetSelectedFilePath(stringa & stra);
      virtual bool _001IsTranslucent();

      void _017Browse(const char * lpcsz, ::action::context actioncontext, bool bForceUpdate = false);
      void _017UpdateList(::action::context actioncontext);
      void _017UpdateList(const char * lpcsz, int32_t iLevel, ::action::context actioncontext);
      void _017UpdateZipList(const char * lpcsz, int32_t iLevel, ::action::context actioncontext);
      void _017EnsureVisible(const char * lpcsz, ::action::context actioncontext);

      sp(::data::tree_item) find_item(const char * lpcsz, ::data::tree_item * pitemStart = NULL);





      void _StartDelayedListUpdate();
      void _StopDelayedListUpdate();
      void _DelayedListUpdate();





      void RenameFile(int32_t iLine, string & str, ::action::context actioncontext);

      virtual void on_update(sp(::user::impact) pSender, LPARAM lHint, object* pHint);

#ifdef DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
#endif

      DECL_GEN_SIGNAL(_001OnLButtonDblClk);
         DECL_GEN_SIGNAL(_001OnContextMenu);
         DECL_GEN_SIGNAL(_001OnCreate);
         DECL_GEN_SIGNAL(_001OnShellCommand);

   };


} // namespace filemanager



