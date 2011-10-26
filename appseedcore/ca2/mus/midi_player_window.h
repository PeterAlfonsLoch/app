#pragma once


class midi_player_callback;

class CLASS_DECL_ca midi_player_window : 
   public ::user::interaction
{
public:


   midi_player_callback * m_pcallback;


   midi_player_window(::ca::application * papp);
   virtual ~midi_player_window();

   midi_player_callback * GetCallback();

   using ::user::interaction::create;
   using ::ex1::request_interface::create;
   virtual bool create();

   void SetCallback(midi_player_callback * pcallback);

   void install_message_handling(::user::win::message::dispatch * pinterface);

   DECL_GEN_SIGNAL(_001OnNotifyEvent)
   DECL_GEN_SIGNAL(_001OnMmsgDone)
   DECL_GEN_SIGNAL(_001OnUserMessage)
   DECL_GEN_SIGNAL(_001OnApp3388Message)
};

