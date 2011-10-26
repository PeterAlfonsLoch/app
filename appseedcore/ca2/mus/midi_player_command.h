#pragma once

class midi_player_command :
   virtual public ::radix::object
{
public:

   enum eflag
   {
      flag_ticks,
      flag_dRate,
   };

   EMidiPlayerCommand   m_ecommand;
   imedia::position                m_ticks;
   double               m_dRate;
   DWORD                m_dwEllapse;
   bool                 m_bReady;
   int                  m_iRefCount;
   flags < eflag >      m_flags;

   midi_player_command(::ca::application * papp);
   //midi_player_command(EMidiPlayerCommand ecommand, DWORD dwEllapse);


   DWORD GetEllapse();
   bool wait_ready();
   void OnFinish();
   EMidiPlayerCommand GetCommand();
private:
   using ::radix::object::lock;
};
