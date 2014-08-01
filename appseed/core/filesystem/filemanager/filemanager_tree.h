#pragma once


namespace filemanager
{


   class CLASS_DECL_CORE tree :
      virtual public ::userfs::tree,
      virtual public ::filemanager::impact
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

      enum e_step
      {
         step_start,
         step_image_visible,
         step_has_subdir_visible,
         step_image_hidden,
         step_has_subdir_hidden,
         step_end,
      };

      class polishing :
         virtual public ::thread
      {
      public:

         ::filemanager::tree *      m_ptree;
         ::user::tree *             m_pusertree;
         bool                       m_bLowLatency;
         ::data::tree_item *        m_pdataitem;
         e_step                     m_estep;

         polishing(sp(::base::application) papp,::filemanager::tree * ptree,::user::tree * pusertree, bool bLowLatency);

         int32_t run();
         bool step(::single_lock & sl);

      };

      context_menu            m_contextmenu;
      mutex                   m_mutexData;
      replace_thread          m_threadPolishing;
      replace_thread          m_threadPolishingLowLatency;
      

#ifdef WINDOWSEX
      map < EFolder, EFolder, IShellFolder *, IShellFolder *> m_mapFolder;
#endif


      tree(sp(::base::application) papp);
      virtual ~tree();


      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;

      virtual void _001InsertColumns();
      virtual void _polishing_step(::single_lock & sl, ::data::tree_item * pitem, bool bLowLatency, e_step estep);

      DECL_GEN_VSIGNAL(_001OnTimer);


      void install_message_handling(::message::dispatch * pinterface);

      // tree_polishing
      void _polishing_start(::user::tree * pusertree);
      UINT _polishing_run(::user::tree * pusertree, bool bLowLatency);
      bool _polishing_step(::data::tree_item * pitem, bool bLowLatency);

      // user::tree
      virtual void _001OnOpenItem(::data::tree_item * pitem, ::action::context actioncontext);
      virtual void _001OnItemExpand(::data::tree_item * pitem, ::action::context actioncontext);
      virtual void _001OnItemCollapse(::data::tree_item * pitem, ::action::context actioncontext);


      virtual void _017OpenFolder(sp(::fs::item)  item, ::action::context actioncontext);

#ifdef WINDOWSEX

      int32_t MapToCSIDL(EFolder efolder);

      IShellFolder * _001GetFolder(EFolder efolder);

#endif


      void TakeAnimationSnapshot();
      virtual void StartAnimation();
      DECL_GEN_SIGNAL(_001OnMainPostMessage);
      void GetSelectedFilePath(stringa & stra);
      virtual bool _001IsTranslucent();

      
      virtual void browse_sync(::action::context actioncontext);
      virtual void knowledge(const string & strPath,::action::context actioncontext);
      virtual void filemanager_tree_insert(const string & strPath, stringa & straPath,stringa & straTitle,int64_array & iaSize,bool_array & ba,::action::context actioncontext);
      void _017EnsureVisible(const char * lpcsz, ::action::context actioncontext);

      sp(::data::tree_item) find_item(const char * lpcsz, ::data::tree_item * pitemStart = NULL);







      void RenameFile(int32_t iLine, string & str, ::action::context actioncontext);

      virtual void on_update(sp(::user::impact) pSender, LPARAM lHint, object* pHint);


      DECL_GEN_SIGNAL(_001OnLButtonDblClk);
      DECL_GEN_SIGNAL(_001OnContextMenu);
      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnShellCommand);


      virtual void on_merge_user_tree(::user::tree * pusertree);
      virtual void on_bind_user_tree(::user::tree * pusertree);


   };


} // namespace filemanager



