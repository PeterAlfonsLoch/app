#pragma once

namespace user
{

   class CLASS_DECL_CA2_VEIEV tree_set :
      virtual public ::user::view,
      virtual public ::user::tree_set_interface
   {
   public:


      simple_list_header_control       m_headerctrl;
      simple_scroll_bar                m_scrollbarVert;
      simple_scroll_bar                m_scrollbarHorz;
      databaseuser::list_data          m_datainterface;


      tree_view(::ca::application * papp);
      virtual ~tree_view();

      virtual void _017OpenFolder(FileManagerItem & item);
      void StartAnimation();
      void RenameFile(int32_t iLine, string & str);
      virtual void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);

      virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg);

      virtual void on_update(::view * pSender, LPARAM lHint, base_object* pHint);
      virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

      // ::user::tree
      virtual void _001OnOpenItem(::ca::tree_item * pitem);
      virtual void _001OnItemExpand(::ca::tree_item * pitem);
      virtual void _001OnItemCollapse(::ca::tree_item * pitem);

      virtual bool _001GetItemText(::ca::tree_item * pitem, string & strItem);
      virtual index _001GetItemImage(::ca::tree_item * pitem, bool bSelected);



   #ifdef _DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif

      DECL_GEN_SIGNAL(_001OnLButtonDblClk)
      DECL_GEN_SIGNAL(_001OnContextMenu)
      DECL_GEN_SIGNAL(_001OnTimer)
      DECL_GEN_SIGNAL(_001OnCreate)
      DECL_GEN_SIGNAL(_001OnShellCommand)

      ::ca::tree_item * allocate_item();
      void delete_item(::ca::tree_item * pitem);

   private:
      tree_view(const tree_view & tree);
   };


} // namespace user
