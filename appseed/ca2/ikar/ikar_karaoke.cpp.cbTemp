#include "StdAfx.h"

namespace ikar
{

   karaoke::karaoke(::ca::application * papp) :
      ca(papp)
   {

   }

   karaoke::~karaoke()
   {

   }

   void  karaoke::TimeToPosition(
      imedia::position_array & positiona,
      imedia::time_array  & timea,
      imedia::time msOffset)
   {
      if(msOffset < 0)
      {
         for(int i = 0; i < timea.get_size(); i++)
         {
            imedia::time ms = timea[i];
            imedia::time msResult = ms + msOffset;
            if(msResult < 0)
               msResult = 0;
            positiona.add(
               TimeToPosition(
                msResult));
         }
      }
      else
      {
         for(int i = 0; i < timea.get_size(); i++)
         {
            imedia::time ms = timea[i];
            imedia::time msResult = ms + msOffset;
            if(msResult < ms)
               msResult = 0x7fffffff;
            positiona.add(
               TimeToPosition(
                msResult));
         }
      }

   }

   void  karaoke::PositionToTime(
      imedia::time_array  & timea,
      imedia::position_array  & positiona,
      int tkOffset)
   {
      if(tkOffset < 0)
      {
         for(int i = 0; i < positiona.get_size(); i++)
         {
            imedia::position tk = positiona[i];
            imedia::position tkResult =  tk + tkOffset;
            if(tkResult > tk)
               tkResult = 0;

            timea.add(
               PositionToTime(tkResult));
         }
      }
      else
      {
         for(int i = 0; i < positiona.get_size(); i++)
         {
            imedia::position tk = positiona[i];
            imedia::position tkResult =  tk + tkOffset;
            if(tkResult < tk)
               tkResult = 0xFFFFFFFF;
            timea.add(
               PositionToTime(
               tkResult));
         }
      }
   }

   void karaoke::PositionToTime(
      imedia::time_2darray  & timea,
      imedia::position_2darray  & positiona,
      int tkOffset)
   {
      ASSERT(timea.get_size() == 0);
      timea.set_size(positiona.get_size());
      int i;
      for(i = 0; i < positiona.get_size(); i++)
      {
         PositionToTime(
            timea[i],
            positiona[i],
            tkOffset);
      }

   }

} // namespace ikar


