#pragma once


class CLASS_DECL_ca FileManagerFrame :
   public simple_frame_window
{
public:
   FileManagerFrame(::ca::application * papp);

   simple_menu_bar           m_menubar;
     simple_toolbar           m_toolbar;
   bool CreateBars();
   virtual ~FileManagerFrame();

public:
   id m_idTab;

   bool DestroyBars();

   virtual void install_message_handling(::gen::message::dispatch * pinterface);

   
   DECL_GEN_SIGNAL(_001OnSetText)
   DECL_GEN_SIGNAL(_001OnCreate)

};
