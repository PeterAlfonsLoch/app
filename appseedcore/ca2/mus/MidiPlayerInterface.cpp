#include "StdAfx.h"

midi_player_interface::midi_player_interface(::ca::application * papp) :
   ca(papp),
   midi_player_callback(papp)
{
   m_pcentral = NULL;
   m_pmidiplayer = NULL;
}

midi_player_interface::~midi_player_interface()
{

}


bool midi_player_interface::Initialize(midi_central * pcentral)
{
   
   if(!initialize())
      return false;

   m_pcentral = pcentral;
   
   return true;
}


bool midi_player_interface::Finalize()
{
   
   if(!finalize())
      return false;

   return true;
}


bool midi_player_interface::OpenMidiPlayer()
{
   try
   {
      m_pmidiplayer = AfxBeginThread < midi_player >(
         get_app(),
         THREAD_PRIORITY_NORMAL,
         0,
         CREATE_SUSPENDED);
   }
   catch(memory_exception *pe)
   {
      System.simple_message_box(NULL, _T("No primitive::memory to perform this operation." ));
      pe->Delete();
      return false;        
   }

   m_pmidiplayer->SetMidiCentral(m_pcentral);
   
   m_pmidiplayer->SetCallbackWindow(&m_wnd);
   if(VMS_FAILED(m_pmidiplayer->Initialize(
      GetMidiPlayerCallbackThread())))
   {
      return false;
   }

   

   if(!OnOpenMidiPlayer())
   {
      return false;
   }
   m_pmidiplayer->ResumeThread();
   m_pmidiplayer->m_evInitialized.wait();
   return true;
}

bool midi_player_interface::OnOpenMidiPlayer()
{
   GetMidiPlayer()->SetInterface(this);
   return true;
}


// Event handling
void midi_player_interface::OnMidiPlayerNotifyEvent(::mus::midi::player::NotifyEvent * pdata)
{
   midi_player_callback::OnMidiPlayerNotifyEvent(pdata);
   switch(pdata->m_enotifyevent)
   {
   case ::mus::midi::player::NotifyEventSetSequence:
//      pdata->m_pplayer->GetSequence().m_midicallbackdata.lpThreadV1 = GetMidiPlayerCallbackThread();
      break;
   }

}

::mus::midi::sequence & midi_player_interface::GetMidiSequence()
{
   return *((::mus::midi::sequence *)NULL);
}

void midi_player_interface::MusicTempoMinus()
{
   midi_player * pplayer = GetMidiPlayer();
   ::mus::midi::sequence & sequence = GetMidiSequence();
   int iTempoShift = sequence.GetTempoShift() - 1;
   if(iTempoShift >= -10 || iTempoShift <= 10)
   {
      pplayer->SetTempoShift(iTempoShift);
      OnChangeMidiPlayerTempoShift();
   }
}

void midi_player_interface::MusicTempoReset()
{
   midi_player * pplayer = GetMidiPlayer();
   pplayer->SetTempoShift(0);
   OnChangeMidiPlayerTempoShift();
}


void midi_player_interface::MusicTransposeMinusTone()
{
    ::mus::midi::sequence & sequence = GetMidiSequence();
    int iKeyShift = sequence.GetKeyShift() - 2;
    if(iKeyShift >= -12 || iKeyShift <= 12)
    {
        sequence.SetKeyShift(iKeyShift);
      OnChangeMidiPlayerTranspose();
    }
}

void midi_player_interface::MusicUpdateTempoReset(cmd_ui *pcmdui)
{
    if(GetMidiPlayer())
    {
        ::mus::midi::sequence & sequence = GetMidiSequence();
        pcmdui->Enable(sequence.GetTempoShift() != 0);
        pcmdui->_001SetCheck(sequence.GetTempoShift() == 0 ? check::checked : check::unchecked);
    }
    else
    {
        pcmdui->Enable(false);
        pcmdui->_001SetCheck(check::unchecked);
    }
}

void midi_player_interface::MusicTempoPlus()
{
   midi_player * pplayer = GetMidiPlayer();
    ::mus::midi::sequence & sequence = GetMidiSequence();
    int iTempoShift = sequence.GetTempoShift() + 1;
    if(iTempoShift >= -10 || iTempoShift <= 10)
    {
      pplayer->SetTempoShift(iTempoShift);
      OnChangeMidiPlayerTempoShift();
    }
}

void midi_player_interface::MusicUpdateTempoPlus(cmd_ui *pcmdui)
{
    if(GetMidiPlayer())
    {
        ::mus::midi::sequence & sequence = GetMidiSequence();
        int iTempoShift = sequence.GetTempoShift() + 1;
        pcmdui->Enable(iTempoShift <= 10);
    }
    else
    {
        pcmdui->Enable(false);
    }
}

void midi_player_interface::MusicUpdateTempoMinus(cmd_ui *pcmdui)
{
    if(GetMidiPlayer())
    {
        ::mus::midi::sequence & sequence = GetMidiSequence();
        int iTempoShift = sequence.GetTempoShift() - 1;
        pcmdui->Enable(iTempoShift >= -10);
    }
    else
    {
        pcmdui->Enable(false);
    }

}

void midi_player_interface::MusicTransposeMinus()
{
    ::mus::midi::sequence & sequence = GetMidiSequence();
    int iKeyShift = sequence.GetKeyShift() - 1;
    if(iKeyShift >= -12 || iKeyShift <= 12)
    {
        sequence.SetKeyShift(iKeyShift);
      OnChangeMidiPlayerTempoShift();
    }

}

void midi_player_interface::MusicTransposePlus()
{
    ::mus::midi::sequence & sequence = GetMidiSequence();
    int iKeyShift = sequence.GetKeyShift() + 1;
    if(iKeyShift >= -12 || iKeyShift <= 12)
    {
        sequence.SetKeyShift(iKeyShift);
      OnChangeMidiPlayerTranspose();
    }
}

void midi_player_interface::MusicTransposeReset()
{
    ::mus::midi::sequence & sequence = GetMidiSequence();
    sequence.SetKeyShift(0);
   OnChangeMidiPlayerTranspose();
}

void midi_player_interface::MusicTransposePlusTone()
{
    ::mus::midi::sequence & sequence = GetMidiSequence();
    int iKeyShift = sequence.GetKeyShift() + 2;
    if(iKeyShift >= -12 || iKeyShift <= 12)
    {
        sequence.SetKeyShift(iKeyShift);
      OnChangeMidiPlayerTranspose();
    }
}

void midi_player_interface::MusicUpdateTransposeMinus(cmd_ui *pcmdui)
{
    if(GetMidiPlayer())
    {
        ::mus::midi::sequence & sequence = GetMidiSequence();
        int iKeyShift = sequence.GetKeyShift() - 1;
        pcmdui->Enable(iKeyShift >= -12);
    }
    else
    {
        pcmdui->Enable(false);
    }
}

void midi_player_interface::MusicUpdateTransposePlus(cmd_ui *pcmdui)
{
    if(GetMidiPlayer())
    {
        ::mus::midi::sequence & sequence = GetMidiSequence();
        int iKeyShift = sequence.GetKeyShift() + 1;
        pcmdui->Enable(iKeyShift <= 12);
    }
    else
    {
        pcmdui->Enable(false);
    }
}

void midi_player_interface::MusicUpdateTransposeReset(cmd_ui *pcmdui)
{
    if(GetMidiPlayer())
    {
        ::mus::midi::sequence & sequence = GetMidiSequence();
        pcmdui->Enable(sequence.GetKeyShift() != 0);
        pcmdui->_001SetCheck(sequence.GetKeyShift() == 0 ? check::checked : check::unchecked);
    }
    else
    {
        pcmdui->Enable(false);
    }
}

void midi_player_interface::MusicUpdateTransposePlusTone(cmd_ui *pcmdui)
{
    if(GetMidiPlayer())
    {
        ::mus::midi::sequence & sequence = GetMidiSequence();
        int iKeyShift = sequence.GetKeyShift() + 1;
        pcmdui->Enable(iKeyShift <= 12);
    }
    else
    {
        pcmdui->Enable(false);
    }

}

void midi_player_interface::MusicUpdateTransposeMinusTone(cmd_ui *pcmdui)
{
    if(GetMidiPlayer())
    {
        ::mus::midi::sequence & sequence = GetMidiSequence();
        int iKeyShift = sequence.GetKeyShift() - 2;
        pcmdui->Enable(iKeyShift >= -12);
    }
    else
    {
        pcmdui->Enable(false);
    }
}



void midi_player_interface::OnChangeMidiPlayerTempoShift()
{

}

void midi_player_interface::OnChangeMidiPlayerTranspose()
{

}


midi_player * midi_player_interface::GetMidiPlayer()
{
   return m_pmidiplayer;
}
