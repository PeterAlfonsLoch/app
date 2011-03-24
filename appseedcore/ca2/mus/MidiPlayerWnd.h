#pragma once


class MidiPlayerCallback;

class CLASS_DECL_ca MidiPlayerWnd : 
   public ::user::interaction
{
public:
   MidiPlayerWnd(::ca::application * papp);

   MidiPlayerCallback * m_pcallback;

#if !core_level_1
   using ::user::interaction::create;
#endif
   virtual bool create();
   void SetCallback(MidiPlayerCallback * pcallback);
   MidiPlayerCallback * GetCallback();
   virtual ~MidiPlayerWnd();

   void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);

   DECL_GEN_SIGNAL(_001OnNotifyEvent)
   DECL_GEN_SIGNAL(_001OnMmsgDone)
   DECL_GEN_SIGNAL(_001OnUserMessage)
   DECL_GEN_SIGNAL(_001OnApp3388Message)
};

