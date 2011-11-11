#pragma once


namespace mediaplaylist
{


   class CLASS_DECL_ca frame :
      public simple_frame_window
        
   {
   public:

      simple_toolbar              m_toolbar;

      frame(::ca::application * papp);
      virtual ~frame();

      virtual void install_message_handling(::user::win::message::dispatch * pinterface);

      ::view * GetParentLyricView();

      DECL_GEN_SIGNAL(_001OnCreate)
   };



} // namespace mediaplaylist


