#pragma once

class midi_event_v008;
class ::mus::midi::sequence;
class midi_track;

class Star350EventTrack;
class Star350EventV008;
class Star350File;
class primitive::memory;

class CLASS_DECL_ca KaraokeUtil : 
   virtual public ::radix::object
{
public:
    
   
   Star350File * m_pstar350file;


   KaraokeUtil(::ca::application * papp);
   virtual ~KaraokeUtil();


   VMSRESULT ConvertStar350ToXF(Star350EventV008 * pstarev, base_array<midi_event_v008, midi_event_v008&> * pmidieva);
   VMSRESULT ConvertStar350ToXF(Star350File * pstarfile, Star350EventTrack * pstartrk, midi_track * pmiditrk);
   VMSRESULT ConvertStar350ToXF(Star350File * pstarfile, ::mus::midi::sequence * pmidiseq, ::mus::midi::e_file_open_mode iOpenMode);
   
   bool IsStar350File(const char * lpcszPath);
   bool IsStar350File(primitive::memory & storage);



};
