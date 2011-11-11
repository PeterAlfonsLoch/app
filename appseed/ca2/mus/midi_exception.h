#pragma once

#define MIDIPLAYERSTOPEXCEPTION 10000
#define MIDIPLAYERCLOSEEXCEPTION 10010
#define MIDIPLAYERSAVEEXCEPTION 10020

#define MIDIPLAYERPRERROLLSTREAMOPENEXCEPTION 20020
#define MIDIPLAYERPRERROLLSTREAMPROPERTYEXCEPTION 20030
#define MIDIPLAYERPRERROLLNOMEMORY1EXCEPTION 20040
#define MIDIPLAYERPRERROLLNOMEMORY2EXCEPTION 20050
#define MIDIPLAYERPRERROLLPREPAREHEADEREXCEPTION 20060
#define MIDIPLAYERPRERROLLSTREAMOUTEXCEPTION 20070
#define MIDIPLAYERPRERROLLREADEVENTSEXCEPTION 20080
#define MIDIPLAYERPRERROLLPREPAREHEADER2EXCEPTION 20090
#define MIDIPLAYERPRERROLLSTREAMOUT2EXCEPTION 20100

class CLASS_DECL_ca midi_exception : public base_exception  
{
public:

   enum e_type 
   {
      TypeUndefined,
      TypeMultimediaSystem,
      TypeMidiFile,
   };


   MMRESULT                        m_mmr;
   int                           m_iAppError;
   ::mus::midi::e_file_result    m_mfr;
   string                        m_strUser;
   e_type                        m_etype;


   midi_exception();
   midi_exception(MMRESULT mmr, int iAppError);
   midi_exception(::mus::midi::e_file_result mfr);
   virtual ~midi_exception();

   string GetUserText();
   void SetUserText(const char * lpsz);
   string GetDetailsText();
   void SetMMResult(MMRESULT mmr);


};
