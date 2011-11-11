#include "StdAfx.h"

/*midi_player_command::midi_player_command(EMidiPlayerCommand ecommand, DWORD dwEllapse)
{
   m_ecommand = ecommand;
   m_dwEllapse = dwEllapse;
   
}
*/

midi_player_command::midi_player_command(::ca::application * papp) :
   ca(papp)
{
   m_iRefCount = 0;
   m_bReady = false;
}

EMidiPlayerCommand midi_player_command::GetCommand()
{
   return m_ecommand;
}

DWORD midi_player_command::GetEllapse()
{
   return m_dwEllapse;
}

bool midi_player_command::wait_ready()
{
   DWORD dwStart = ::GetTickCount();
   while(!m_bReady && (::GetTickCount() - dwStart) < m_dwEllapse)
   {
      Sleep(84);
   }
   return m_bReady;
}

void midi_player_command::OnFinish()
{
   m_bReady = true;
}
