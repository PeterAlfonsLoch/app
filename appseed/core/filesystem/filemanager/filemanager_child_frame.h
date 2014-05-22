#pragma once


namespace filemanager
{


   class CLASS_DECL_CORE child_frame :
      public simple_child_frame
   {
   public:


      simple_toolbar           m_toolbar;


      child_frame(sp(::base::application) papp);
      virtual ~child_frame();

      void install_message_handling(::message::dispatch * pinterface);

      void OnChangeEditSearch();

      sp(manager) GetFileManager();


      void GetSelected(::fs::item_array &itema);

      bool CreateBars();
      bool DestroyBars();
      virtual bool _001OnCmdMsg(::base::cmd_msg * pcmdmsg);

      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnAppLanguage);
      DECL_GEN_SIGNAL(_001OnShowWindow);


   };


} // namespace filemanager




