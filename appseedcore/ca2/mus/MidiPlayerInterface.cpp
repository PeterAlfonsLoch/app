#include "StdAfx.h"

MidiPlayerInterface::MidiPlayerInterface(::ca::application * papp) :
   ca(papp),
   MidiPlayerCallback(papp)
{
   m_pcentral = NULL;
   m_pmidiplayer = NULL;
}

MidiPlayerInterface::~MidiPlayerInterface()
{

}


bool MidiPlayerInterface::Initialize(midi_central * pcentral)
{
   
   if(!initialize())
      return false;

   m_pcentral = pcentral;
   
   return true;
}


bool MidiPlayerInterface::Finalize()
{
   
   if(!finalize())
      return false;

   return true;
}


bool MidiPlayerInterface::OpenMidiPlayer()
{
   try
   {
      m_pmidiplayer = AfxBeginThread < MidiPlayer >(
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
   m_pmidiplayer->m_evInitialized.Lock();
   return true;
}

bool MidiPlayerInterface::OnOpenMidiPlayer()
{
   GetMidiPlayer()->SetInterface(this);
   return true;
}


// Event handling
void MidiPlayerInterface::OnMidiPlayerNotifyEvent(::mus::midi::player::NotifyEvent * pdata)
{
   MidiPlayerCallback::OnMidiPlayerNotifyEvent(pdata);
   switch(pdata->m_enotifyevent)
   {
   case ::mus::midi::player::NotifyEventSetSequence:
//      pdata->m_pplayer->GetSequence().m_midicallbackdata.lpThreadV1 = GetMidiPlayerCallbackThread();
      break;
   }

}

::mus::midi::sequence & MidiPlayerInterface::GetMidiSequence()
{
   return *((::mus::midi::sequence *)NULL);
}

void MidiPlayerInterface::MusicTempoMinus()
{
   MidiPlayer * pplayer = GetMidiPlayer();
   ::mus::midi::sequence & sequence = GetMidiSequence();
   int iTempoShift = sequence.GetTempoShift() - 1;
   if(iTempoShift >= -10 || iTempoShift <= 10)
   {
      pplayer->SetTempoShift(iTempoShift);
      OnChangeMidiPlayerTempoShift();
   }
}

void MidiPlayerInterface::MusicTempoReset()
{
   MidiPlayer * pplayer = GetMidiPlayer();
   pplayer->SetTempoShift(0);
   OnChangeMidiPlayerTempoShift();
}


void MidiPlayerInterface::MusicTransposeMinusTone()
{
    ::mus::midi::sequence & sequence = GetMidiSequence();
    int iKeyShift = sequence.GetKeyShift() - 2;
    if(iKeyShift >= -12 || iKeyShift <= 12)
    {
        sequence.SetKeyShift(iKeyShift);
      OnChangeMidiPlayerTranspose();
    }
}

void MidiPlayerInterface::MusicUpdateTempoReset(cmd_ui *pcmdui)
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

void MidiPlayerInterface::MusicTempoPlus()
{
   MidiPlayer * pplayer = GetMidiPlayer();
    ::mus::midi::sequence & sequence = GetMidiSequence();
    int iTempoShift = sequence.GetTempoShift() + 1;
    if(iTempoShift >= -10 || iTempoShift <= 10)
    {
      pplayer->SetTempoShift(iTempoShift);
      OnChangeMidiPlayerTempoShift();
    }
}

void MidiPlayerInterface::MusicUpdateTempoPlus(cmd_ui *pcmdui)
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

void MidiPlayerInterface::MusicUpdateTempoMinus(cmd_ui *pcmdui)
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

void MidiPlayerInterface::MusicTransposeMinus()
{
    ::mus::midi::sequence & sequence = GetMidiSequence();
    int iKeyShift = sequence.GetKeyShift() - 1;
    if(iKeyShift >= -12 || iKeyShift <= 12)
    {
        sequence.SetKeyShift(iKeyShift);
      OnChangeMidiPlayerTempoShift();
    }

}

void MidiPlayerInterface::MusicTransposePlus()
{
    ::mus::midi::sequence & sequence = GetMidiSequence();
    int iKeyShift = sequence.GetKeyShift() + 1;
    if(iKeyShift >= -12 || iKeyShift <= 12)
    {
        sequence.SetKeyShift(iKeyShift);
      OnChangeMidiPlayerTranspose();
    }
}

void MidiPlayerInterface::MusicTransposeReset()
{
    ::mus::midi::sequence & sequence = GetMidiSequence();
    sequence.SetKeyShift(0);
   OnChangeMidiPlayerTranspose();
}

void MidiPlayerInterface::MusicTransposePlusTone()
{
    ::mus::midi::sequence & sequence = GetMidiSequence();
    int iKeyShift = sequence.GetKeyShift() + 2;
    if(iKeyShift >= -12 || iKeyShift <= 12)
    {
        sequence.SetKeyShift(iKeyShift);
      OnChangeMidiPlayerTranspose();
    }
}

void MidiPlayerInterface::MusicUpdateTransposeMinus(cmd_ui *pcmdui)
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

void MidiPlayerInterface::MusicUpdateTransposePlus(cmd_ui *pcmdui)
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

void MidiPlayerInterface::MusicUpdateTransposeReset(cmd_ui *pcmdui)
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

void MidiPlayerInterface::MusicUpdateTransposePlusTone(cmd_ui *pcmdui)
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

void MidiPlayerInterface::MusicUpdateTransposeMinusTone(cmd_ui *pcmdui)
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



void MidiPlayerInterface::OnChangeMidiPlayerTempoShift()
{

}

void MidiPlayerInterface::OnChangeMidiPlayerTranspose()
{

}


MidiPlayer * MidiPlayerInterface::GetMidiPlayer()
{
   return m_pmidiplayer;
}
