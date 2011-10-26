#pragma once

class Mixer;

class MixerWnd : 
   public ::user::interaction
{
public:
   Mixer *      m_pmixer;

   MixerWnd(::ca::application * papp);
   virtual ~MixerWnd();

   void install_message_handling(::user::win::message::dispatch * pinterface);

   DECL_GEN_SIGNAL(_001OnMixerControlChange)
   DECL_GEN_SIGNAL(_001OnMixerLineChange)
};

