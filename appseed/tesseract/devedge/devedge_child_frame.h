#pragma once

class CLASS_DECL_CA2_TESSERACT devedge_child_frame :
   public simple_child_frame
{
public:
   devedge_child_frame(::ca::application * papp);

     simple_toolbar        m_toolbar;

   FileManagerInterface * GetFileManager();

   bool CreateBars();
   bool DestroyBars();

   virtual ~devedge_child_frame();

   virtual void install_message_handling(::user::win::message::dispatch * pinterface);

   DECL_GEN_SIGNAL(_001OnCreate)
   DECL_GEN_SIGNAL(_001OnAppLanguage)
};

