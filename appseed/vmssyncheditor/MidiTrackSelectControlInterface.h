#pragma once

class MidiTrackSelectDDX;

class MidiTrackSelectControlInterface  
{
public:
	virtual void OnSelectTrack(int iTrack);
   virtual void OnTrackSelectApply();
	MidiTrackSelectControlInterface();
	virtual ~MidiTrackSelectControlInterface();

   MidiTrackSelectDDX * m_pddx;

};
