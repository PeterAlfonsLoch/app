#pragma once


namespace fs
{

   class main_view;

   class CLASS_DECL_ca tree :
      virtual public tree_interface
   {
   public:


      simple_scroll_bar             m_scrollbarVert;
      simple_scroll_bar             m_scrollbarHorz;


      tree(::ca::application * papp);
      virtual ~tree();

      virtual void _001InstallMessageHandling(::user::win::message::dispatch * pdispatch);

      virtual void _017OpenFolder(item & item);
      void StartAnimation();
      void RenameFile(int iLine, string & str);

      virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg); 

      virtual void on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint);
      virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
    
      DECL_GEN_SIGNAL(_001OnLButtonDblClk)
      DECL_GEN_SIGNAL(_001OnContextMenu)
      DECL_GEN_SIGNAL(_001OnTimer)
      DECL_GEN_SIGNAL(_001OnCreate)
      DECL_GEN_SIGNAL(_001OnShellCommand)

   #ifdef _DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif
   };


} // namespace fs


