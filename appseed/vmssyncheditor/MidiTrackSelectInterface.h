#pragma once

class MidiTrackSelectDDX;
class MidiSequence;

class MidiTrackSelectInterface  
{
public:
	virtual bool Initialize(MidiSequence * pmidisequence, bool bEnable);
	MidiTrackSelectInterface();
	virtual ~MidiTrackSelectInterface();

   MidiTrackSelectDDX * m_pddx;

};
