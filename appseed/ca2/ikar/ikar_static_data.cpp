#include "StdAfx.h"

namespace ikar
{

   static_data::static_data()
   {

   }

   static_data::~static_data()
   {

   }

   void static_data::delete_contents()
   {
      int i;
      for(i = 0; i < m_eventsv1.get_size(); i++)
      {
         delete m_eventsv1[i];
      }
      m_eventsv1.remove_all();

      m_eventsTracksForBouncingBall.remove_all();
      m_eventsTracksForScoring.remove_all();
      m_eventsTracksForPositionCB.remove_all();
      m_eventstracksV002.remove_all();
      m_eventstracks.remove_all();

      m_str2aRawTokens.remove_all();
      m_iaTokenLine.remove_all();
      m_straTitleFormat.remove_all();
      m_str2aTitle.remove_all();

   }

   LyricEventsV2 * static_data::GetEvents()
   {
      if(m_eventstracksV002.get_size() <= 0)
         return NULL;
      LyricEventsV2 *pevents = (LyricEventsV2 *) m_eventstracksV002.operator [](0);
      ASSERT(pevents != NULL);
      ASSERT(pevents->GetClassOrder() == 2);
      return pevents;
   }

   void static_data::SetGuessMelodyTrack(int iTrack)
   {
      m_iGuessMelodyTrack = iTrack;
   }

   int static_data::GetGuessMelodyTrack()
   {
      return m_iGuessMelodyTrack;
   }

   void static_data::GetLyrics(string &str)
   {
      str = m_strLyrics;
   }

}

