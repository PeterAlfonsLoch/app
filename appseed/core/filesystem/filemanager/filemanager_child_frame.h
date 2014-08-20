#pragma once


namespace filemanager
{


   class CLASS_DECL_CORE child_frame :
      public simple_child_frame
   {
   public:



      child_frame(sp(::axis::application) papp);
      virtual ~child_frame();

      void install_message_handling(::message::dispatch * pinterface);

      void OnChangeEditSearch();

      sp(manager) get_filemanager_template();


      void GetSelected(::fs::item_array &itema);

      bool on_create_bars();
      bool DestroyBars();
      virtual bool _001OnCmdMsg(::axis::cmd_msg * pcmdmsg);

      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnAppLanguage);
      DECL_GEN_SIGNAL(_001OnShowWindow);


   };


} // namespace filemanager




