#include "StdAfx.h"

midi_central::midi_central(::ca::application * papp) :
ca(papp)
{
   m_pcontainer = NULL;
   m_uiMidiOutDevice = MIDI_MAPPER; 
}


bool midi_central::Initialize(mus::midi_central_container * pcontainer)
{
   m_pcontainer = pcontainer;


   System.factory().creatable_small < ::LyricViewLineTemplate >();

   return true;
}

midi_central::~midi_central()
{

}




void midi_central::SetMidiOutDevice(UINT uiDevice)
{
   m_uiMidiOutDevice = uiDevice;
   int iAttribute = (int) mus::MidiCentralAttributeMidiOutDevice;
   m_listenerptra.PtrCallAll(&CMidiCentralListener::OnAttributeChange, iAttribute);
}

UINT midi_central::GetMidiOutDevice()
{
   return m_uiMidiOutDevice;
}

void midi_central::AddListener(CMidiCentralListener *plistener)
{
   m_listenerptra.add_unique(plistener);
}

void midi_central::RemoveListener(CMidiCentralListener *plistener)
{
   m_listenerptra.remove(plistener);
}


bool midi_central::IsSoftKaraokeFile(const char * lpszPathName)
{
   ::mus::midi::sequence midiSeq(get_app());
   midiSeq.OpenFile(lpszPathName, ::mus::midi::OpenForParsingLevel2);
   return midiSeq.GetFile().IsSoftKaraokeFile();
}

bool midi_central::IsXFFile(const char * lpcszPathName)
{
   ::mus::midi::sequence midiSeq(get_app());
   midiSeq.OpenFile(lpcszPathName, ::mus::midi::OpenForParsing);
   return midiSeq.GetFile().IsXFFile();
}

