#pragma once


namespace filemanager
{


   class CLASS_DECL_CORE frame :
   public simple_frame_window
   {
   public:
       frame(sp(base_application) papp);

      simple_menu_bar           m_menubar;
      simple_toolbar           m_toolbar;
      bool CreateBars();
      virtual ~ frame();

   public:
      id m_idTab;

      bool DestroyBars();

      virtual void install_message_handling(::message::dispatch * pinterface);


      DECL_GEN_SIGNAL(_001OnSetText);
         DECL_GEN_SIGNAL(_001OnCreate);

   };


} // namespace filamanager





