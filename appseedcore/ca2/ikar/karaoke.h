#pragma once



namespace ikar
{

   class data;
   
   class CLASS_DECL_ca karaoke :
      virtual public ::radix::object
   {
   public:
      
      karaoke(::ca::application * papp);
      virtual ~karaoke();

      virtual imedia::position TimeToPosition(imedia::time time) = 0;
      virtual imedia::time PositionToTime(imedia::position position) = 0;
      virtual void get_position(imedia::position & position) = 0;
      virtual void get_time(imedia::time & position) = 0;
      virtual void GetTimeLength(imedia::time & time) = 0;
      virtual void GetPositionLength(imedia::position & position) = 0;
      virtual bool IsOpened() = 0;
      virtual void Prepare(ikar::data & data) = 0;
      virtual void Prepare(int iTrack, ikar::data & data) = 0;
      virtual imedia::position GetQuarterNote() = 0;


      virtual int GetDefaultCodePage() = 0;

      // Helpers
      virtual void TimeToPosition(
         imedia::position_array & positiona,
         imedia::time_array  & timea,
         imedia::time msOffset);

      virtual void PositionToTime(
         imedia::time_2darray  & timea,
         imedia::position_2darray  & positiona,
         int tkOffset);

      virtual void PositionToTime(
         imedia::time_array  & timea,
         imedia::position_array  & positiona,
         int tkOffset);


   };


} // namespace ikar
