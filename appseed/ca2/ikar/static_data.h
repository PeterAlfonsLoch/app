#pragma once

typedef base_array<LyricEventsV1 *, LyricEventsV1 *> EventsTracksV1;

class LyricEventsV2;

namespace ikar
{
   ///////////////////////////////////////////////////
   // Karaoke information used in karaoke display
   // that does not have runtime-only-meaning
   // (that is not dynamic)
   // However, it may contain runtime-only-use data.
   // It never changes during karaoke execution.
   ///////////////////////////////////////////////////
   class CLASS_DECL_ca static_data  
   {
   public:
      EventsTracksV1         m_eventstracks;
      EventsTracksV1         m_eventstracksV002;
      EventsTracksV1       m_eventsTracksForScoring;
      EventsTracksV1         m_eventsTracksForPositionCB; 
      EventsTracksV1         m_eventsTracksForBouncingBall; 
      EventsTracksV1         m_eventsv1; 

      
      
      string2a      m_str2aRawTokens;
      int_array            m_iaTokenLine;
      stringa            m_straTitleFormat;
      string2a      m_str2aTitle;
      int                  m_LyricsDisplayOffset;
      int                  m_LyricsDisplay;
      int                  m_iGuessMelodyTrack;
      DWORD                m_dwDefaultCodePage;
      string               m_strLyrics;

   public:
      void GetLyrics(string & str);
      int GetGuessMelodyTrack();
      void SetGuessMelodyTrack(int iTrack);
      LyricEventsV2 * GetEvents();
      void delete_contents();
      static_data();
      virtual ~static_data();
   };

} // namespace ikar
