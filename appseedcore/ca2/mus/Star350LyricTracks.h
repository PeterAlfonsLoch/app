#pragma once

class CLASS_DECL_ca Star350LyricTracks :
   virtual public array_app_alloc < midi_lyric_track, midi_lyric_track & >
{
public:
   
   
   Star350LyricTracks(::ca::application * papp);
   virtual ~Star350LyricTracks();
    
   
   VMSRESULT GetNextEventTkPosition(imedia::position * pTkPosition, imedia::position tkMax);

   VMSRESULT GetNextEvent(midi_event_v001 * pEvent, imedia::position tkMax, BOOL bTkMaxInclusive);

   void seek_begin();

};
