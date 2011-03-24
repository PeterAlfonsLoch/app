#pragma once

class CLASS_DECL_ca PlaylistFrame :
   public simple_frame_window
        
{
public:

   simple_toolbar              m_toolbar;

   PlaylistFrame(::ca::application * papp);
   virtual ~PlaylistFrame();

   virtual void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);

   ::view * GetParentLyricView();

   DECL_GEN_SIGNAL(_001OnCreate)
};
