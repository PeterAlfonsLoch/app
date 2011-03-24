#pragma once


namespace filemanager
{

   class document;

   class CLASS_DECL_ca SimpleFolderTreeView :
      virtual public filemanager::SimpleFolderTreeInterface
   {
   public:
      SimpleFolderTreeView(::ca::application * papp);

      ContextMenu                   m_contextmenu;
      simple_list_header_control    m_headerctrl;
      simple_scroll_bar             m_scrollbarVert;
      simple_scroll_bar             m_scrollbarHorz;



      virtual void _017OpenFolder(::fs::item & item);
      void StartAnimation();
      void RenameFile(int iLine, string & str);
      virtual void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);

      virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg); 

      virtual void on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint);
      virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
    
      virtual ~SimpleFolderTreeView();
   #ifdef _DEBUG
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
