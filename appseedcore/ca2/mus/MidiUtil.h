#pragma once

class MidiEventsV1;
class stringa;
class MidiTrack;




class CLASS_DECL_ca MidiUtil : 
   virtual public ::radix::object
{
protected:


   MidiTracks           m_tracks;
   string2a      m_kar2DTokens;
   string2a      m_tune10002DTokens;
   stringa            m_straTokens;


public:


   MidiUtil(::ca::application * papp);


   bool ExtractLyrics(string & str, ::mus::midi::sequence &seq);

   MMRESULT ConvertKarToXF(stringa *      pKar1DTokens, imedia::position_array *        pKar1DTicks, MidiTrack *      pXFTrk);
   MMRESULT WorkConvertKarToXF(stringa *      pKar1DTokens, imedia::position_array *        pKar1DTicks, MidiTrack *      pXFTrk);
   MMRESULT ConvertToXF(::mus::midi::sequence &seq, int iOpenMode);
   ::mus::midi::e_file_type GetFileType(::mus::midi::sequence & seq);
   MMRESULT ConvertTune1000ToXF(::mus::midi::sequence & seq1000, ::mus::midi::sequence &seqXf, int iOpenMode);
   MMRESULT ConvertTune1000ToXF(::mus::midi::sequence & seq, int iOpenMode);
   MMRESULT ConvertKarToXF(::mus::midi::sequence &seqKar, ::mus::midi::sequence &seqXf, int iOpenMode);
   MMRESULT ConvertKarToXF(::mus::midi::sequence &seq, int iOpenMode);
   void PrepareNoteOnOffEvents(MidiEventsV1 * pNoteOnEvents, MidiEventsV1 * pNoteOffEvents, int iTrack, int iFormat, MidiEventsV1 * pNoteOnOffEvents, imedia::position_array & positiona);
   void PrepareLevel2Events(MidiEventsV1 * peventsLevel2Beg, MidiEventsV1 * peventsLevel2End, int iTrack, int iFormat, MidiEventsV1 * peventsLevel2, imedia::position_array & positiona);

};
