#pragma once

class midi_events_v1;
class stringa;
class midi_track;




class CLASS_DECL_ca midi_util : 
   virtual public ::radix::object
{
protected:


   midi_tracks           m_tracks;
   string2a      m_kar2DTokens;
   string2a      m_tune10002DTokens;
   stringa            m_straTokens;


public:


   midi_util(::ca::application * papp);


   bool ExtractLyrics(string & str, ::mus::midi::sequence &seq);

   MMRESULT ConvertKarToXF(stringa *      pKar1DTokens, imedia::position_array *        pKar1DTicks, midi_track *      pXFTrk);
   MMRESULT WorkConvertKarToXF(stringa *      pKar1DTokens, imedia::position_array *        pKar1DTicks, midi_track *      pXFTrk);
   MMRESULT ConvertToXF(::mus::midi::sequence &seq, int iOpenMode);
   ::mus::midi::e_file_type GetFileType(::mus::midi::sequence & seq);
   MMRESULT ConvertTune1000ToXF(::mus::midi::sequence & seq1000, ::mus::midi::sequence &seqXf, int iOpenMode);
   MMRESULT ConvertTune1000ToXF(::mus::midi::sequence & seq, int iOpenMode);
   MMRESULT ConvertKarToXF(::mus::midi::sequence &seqKar, ::mus::midi::sequence &seqXf, int iOpenMode);
   MMRESULT ConvertKarToXF(::mus::midi::sequence &seq, int iOpenMode);
   void PrepareNoteOnOffEvents(midi_events_v1 * pNoteOnEvents, midi_events_v1 * pNoteOffEvents, int iTrack, int iFormat, midi_events_v1 * pNoteOnOffEvents, imedia::position_array & positiona);
   void PrepareLevel2Events(midi_events_v1 * peventsLevel2Beg, midi_events_v1 * peventsLevel2End, int iTrack, int iFormat, midi_events_v1 * peventsLevel2, imedia::position_array & positiona);

};
