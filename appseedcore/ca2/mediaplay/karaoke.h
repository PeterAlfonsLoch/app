#pragma once

class audWavePlayer;
class Ex1TextFile;

namespace mediaplay
{
   
   class karaoke :
      virtual public ikar::karaoke
   {
   public:


      audWavePlayer *                  m_pwaveplayer;
      stringa                        m_straToken;
      imedia::position_array           m_positionaToken;
      imedia::time_array               m_timeaDuration;


      karaoke(::ca::application * papp);
      virtual ~karaoke();


      virtual void delete_contents();


#if !core_level_1
      using ikar::karaoke::TimeToPosition;
      using ikar::karaoke::PositionToTime;
#endif
      imedia::position TimeToPosition(const char * lpcsz);
      virtual imedia::position TimeToPosition(imedia::time time);
      virtual imedia::time PositionToTime(imedia::position position);


      void ParseSSAFile(ex1::file * pfile);
      void ParseKOKFile(ex1::file * pfile);
      
      
      virtual int GetDefaultCodePage();
      


      virtual void GetPosition(imedia::position & position);
      virtual void get_time(imedia::time & position);
      virtual void GetTimeLength(imedia::time & time);
      virtual void GetPositionLength(imedia::position & position);
      virtual bool IsOpened();
      virtual void Prepare(ikar::data & data);
      virtual void Prepare(int iTrack, ikar::data & data);
      void karaoke::Prepare(
         string2a & str2a,
         imedia::position_2darray & tka2DTokensTicks,
         ikar::data & data);
      
      
      imedia::position GetQuarterNote();
      
      
   };
   
} // namespace mediaplay

