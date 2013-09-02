#pragma once


namespace userfs
{


   class main_view;


   class CLASS_DECL_ca2 tree :
      public tree_interface
   {
   public:


      tree(sp(::application) papp);
      virtual ~tree();

      virtual void install_message_handling(::ca2::message::dispatch * pdispatch);

      virtual void _017OpenFolder(sp(::fs::item) item);
      void StartAnimation();
      void RenameFile(int32_t iLine, string & str);

      virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg); 

      virtual void on_update(sp(::user::view) pSender, LPARAM lHint, object* pHint);
      virtual bool pre_create_window(CREATESTRUCT& cs);
    
      DECL_GEN_SIGNAL(_001OnLButtonDblClk)
      DECL_GEN_SIGNAL(_001OnContextMenu)
      DECL_GEN_SIGNAL(_001OnTimer)
      DECL_GEN_SIGNAL(_001OnCreate)
      DECL_GEN_SIGNAL(_001OnShellCommand)

   #ifdef DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif


   };


} // namespace userfs



