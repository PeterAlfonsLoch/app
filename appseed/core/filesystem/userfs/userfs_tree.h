#pragma once


namespace userfs
{


   class main_view;


   class CLASS_DECL_CORE tree :
      virtual public ::user::tree_data
   {
   public:

      string                        m_strPath;
      bool                          m_bCreateImageList;
      bool                          m_bCreateImageListRedraw;
      int32_t                       m_iAnimate;
      bool                          m_bTimer123;
      stringa                       m_straUpdatePtrFilter;
      int32_t                       m_iDefaultImage;
      int32_t                       m_iDefaultImageSelected;


      tree(sp(::base::application) papp);
      virtual ~tree();


      void update_list();

      void _001OnItemExpand(::data::tree_item * pitem, ::action::context actioncontext);

      sp(::userfs::document) get_document();

      virtual void _001InsertColumns();
      


      void install_message_handling(::message::dispatch * pinterface);


      virtual void _001OnOpenItem(::data::tree_item * pitem, ::action::context actioncontext);
      virtual void _001OnItemCollapse(::data::tree_item * pitem, ::action::context actioncontext);


      virtual void _017OpenFolder(sp(::fs::item) item, ::action::context actioncontext);

      virtual COLORREF get_background_color();

      void TakeAnimationSnapshot();
      virtual void StartAnimation(::user::interaction * pui);
      void GetSelectedFilePath(stringa & stra);
      virtual bool _001IsTranslucent();

      virtual void browse_sync(::action::context actioncontext);
      void _017EnsureVisible(const char * lpcsz, ::action::context actioncontext);

      sp(::data::tree_item) find_item(const char * lpcsz, ::data::tree_item * pitemStart = NULL);

      sp(::data::tree_item) find_absolute(const char * lpcsz,::data::tree_item * pitemStart = NULL);
      void clear(const char * lpcszPreserve1, const char * lpcszPreserve2);
      void arrange(::fs::e_arrange earrange);

      DECL_GEN_SIGNAL(_001OnTimer);


      void RenameFile(int32_t iLine, string & str, ::action::context actioncontext);

      virtual void on_update(sp(::user::impact) pSender, LPARAM lHint, object* pHint);
    
      DECL_GEN_SIGNAL(_001OnLButtonDblClk);
      DECL_GEN_SIGNAL(_001OnContextMenu);
      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnShellCommand);

   #ifdef DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif


   };


} // namespace userfs



