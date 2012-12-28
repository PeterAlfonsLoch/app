#pragma once


namespace filemanager
{

   class document;

   class CLASS_DECL_ca2 SimpleFolderTreeView :
      virtual public filemanager::SimpleFolderTreeInterface
   {
   public:
      SimpleFolderTreeView(::ca::application * papp);

      ContextMenu                   m_contextmenu;
      simple_list_header_control    m_headerctrl;



      virtual void _017OpenFolder(const ::fs::item & item);
      void StartAnimation();
      void RenameFile(int32_t iLine, string & str);
      virtual void install_message_handling(::gen::message::dispatch * pinterface);

      virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg); 

      virtual void on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint);
      virtual bool pre_create_window(CREATESTRUCT& cs);
    
      virtual ~SimpleFolderTreeView();
   #ifdef DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif

      DECL_GEN_SIGNAL(_001OnLButtonDblClk)
      DECL_GEN_SIGNAL(_001OnContextMenu)
      DECL_GEN_SIGNAL(_001OnTimer)
      DECL_GEN_SIGNAL(_001OnCreate)
      DECL_GEN_SIGNAL(_001OnShellCommand)
   };


} // namespace filemanager
