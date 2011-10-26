#include "StdAfx.h"

namespace ikar
{

   dynamic_data::dynamic_data()
   {

   }

   dynamic_data::~dynamic_data()
   {

   }

   void dynamic_data::reset()
   {
      m_iBufferOffsetTokenIndex  = -1;
      m_iBufferTokenIndex        = -1;
      m_iPlayingTokenIndex       = -1;
      m_iPlayingNoteIndex        = -1;
      m_position                 = -1;
      m_time                     = -1;
   }



   void dynamic_data::initialize_standup(int iSize)
   {
      m_daStandUp.set_size(iSize);
      m_iaStandUpLastTime.set_size(iSize);
      m_iaStandUpDeltaTime.set_size(iSize);
      __int64 time;
      __int64 count;
      __int64 freq;
      m_iLastStandUp = 0;
      if(QueryPerformanceCounter((LARGE_INTEGER *) &count)
      && QueryPerformanceFrequency((LARGE_INTEGER *) &freq))
      {
         time = count * 1000 * 1000 / freq;
      }
      else
      {
         time = ::GetTickCount() * 1000;
      }
      for(int iToken = 0; iToken < iSize; iToken++)
      {
         m_daStandUp[iToken] = 0.0;
         m_iaStandUpLastTime[iToken]  = time;
         m_iaStandUpDeltaTime[iToken]  = time;
      }
   }

   void dynamic_data::feed_standup(double dStandUp)
   {
      __int64 time;
      __int64 count;
      __int64 freq;
      if(QueryPerformanceCounter((LARGE_INTEGER *) &count)
      && QueryPerformanceFrequency((LARGE_INTEGER *) &freq))
      {
         time = (count * 1000 * 1000) / freq;
      }
      else
      {
         time = ::GetTickCount() * 1000;
      }
      if(m_iPlayingTokenIndex >= 0
      && m_iPlayingTokenIndex< m_daStandUp.get_size())
      {
         if(m_iLastStandUp > m_iPlayingTokenIndex)
         {
            m_iLastStandUp = m_iPlayingTokenIndex;
         }
         else if(m_iLastStandUp < m_iPlayingTokenIndex)
         {
            for(int iToken = m_iLastStandUp; iToken < m_iPlayingTokenIndex; iToken++)
            {
               if(m_daStandUp[iToken] == 0.0)
               {
                  double dStandUpRate = 0.67 + 0.33 * (((double) (iToken + 1)) / ((double) (m_iPlayingTokenIndex - m_iLastStandUp)));
                  __int64 iTimeDelay = 1000 * 1000 * 23 * (m_iPlayingTokenIndex - iToken);
                  __int64 iStandUpTime = time - iTimeDelay;
                  m_daStandUp[iToken] = dStandUpRate;
                  m_iaStandUpLastTime[iToken]  = iStandUpTime;
                  m_iaStandUpDeltaTime[iToken] = iStandUpTime;
               }
            }
            if(dStandUp < 0.3323)
            {
               dStandUp = 0.5;
            }
            else
            {
               m_iLastStandUp = m_iPlayingTokenIndex;
            }
         }
         m_daStandUp[m_iPlayingTokenIndex] = dStandUp;
         m_iaStandUpLastTime[m_iPlayingTokenIndex]  = time;
         m_iaStandUpDeltaTime[m_iPlayingTokenIndex] = time;
      }
      for(int iToken = 0; iToken < m_daStandUp.get_count(); iToken++)
      {
         if(iToken == m_iPlayingTokenIndex)
            continue;
         if(m_daStandUp[iToken] <= 0.0)
            continue;
         double dx = (double) (time - m_iaStandUpDeltaTime[iToken]);
         double fxderived = (double) (time - m_iaStandUpLastTime[iToken]);
         double dy = - (1.5 * dx * fxderived) / (1000.0 * 1000.0 * 1000.0 * 1000.0);
         double y = m_daStandUp[iToken];
         m_daStandUp[iToken] = y + dy;
         m_iaStandUpDeltaTime[iToken] = time;
         if(m_daStandUp[iToken] < 0.0)
         {
            m_daStandUp[iToken] = 0.0;
            if(iToken > m_iLastStandUp)
            {
               m_iLastStandUp = iToken;
            }
         }

      }
   }


} // namespace ikar