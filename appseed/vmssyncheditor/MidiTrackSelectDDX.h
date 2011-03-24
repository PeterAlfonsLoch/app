#pragma once

class MidiTrackSelectInterface;
class MidiTrackSelectControlInterface;

class MidiTrackSelectDDX  
{
public:
	MidiTrackSelectDDX();
	virtual ~MidiTrackSelectDDX();

   MidiTrackSelectInterface *            m_pselect;
   MidiTrackSelectControlInterface *     m_pcontrol;

};
