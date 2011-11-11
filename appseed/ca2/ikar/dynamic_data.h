#pragma once

namespace ikar
{

   ///////////////////////////////////////////////////
   // Karaoke information used in karaoke display
   // that have runtime-only-meaning
   // (that is exclusively dynamic in during execution)
   // It may contains runtime-only-use data.
   // It always changes during karaoke execution.
   ///////////////////////////////////////////////////
   class CLASS_DECL_ca dynamic_data  
   {
   public:


      int                     m_iBufferOffsetTokenIndex;
      int                     m_iBufferTokenIndex;
      int                     m_iPlayingTokenIndex;
      int                     m_iPlayingNoteIndex;
      imedia::position        m_position;
      imedia::time            m_time;
      double_array            m_daStandUp;
      int64_array             m_iaStandUpLastTime;
      int64_array             m_iaStandUpDeltaTime;
      int                     m_iLastStandUp;



      dynamic_data();
      virtual ~dynamic_data();

      void reset();

      void initialize_standup(int iSize);
      void feed_standup(double dStandUp);


   };


} // namespace ikar

