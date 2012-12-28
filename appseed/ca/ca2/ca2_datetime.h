#pragma once


CLASS_DECL_ca int32_t SWN(int32_t y, int32_t m, int32_t d );
//where DP ("Days Passed") is given by:
//   DP( y, 1 ) = 0
//  DP( y, m+1 ) = DP( y, m ) + ML( y, m )
CLASS_DECL_ca int32_t DP(int32_t y, int32_t m);
CLASS_DECL_ca int32_t ML(int32_t y, int32_t m);
CLASS_DECL_ca int32_t LEAP(int32_t y );
CLASS_DECL_ca int32_t dayofweek(int32_t y, int32_t m, int32_t d);	/* 0 = Sunday */
CLASS_DECL_ca int32_t SDOW(int32_t y,int32_t m, int32_t d ); // ( 0 = Monday, ..., 6 = Sunday )
CLASS_DECL_ca int32_t DOW(int32_t y, int32_t m, int32_t d);
CLASS_DECL_ca int32_t getDayOfWeek(int32_t month, int32_t day, int32_t year, int32_t CalendarSystem);


namespace ca2
{

   
   class CLASS_DECL_ca datetime :
      virtual public ::radix::object
   {
   public:
      class CLASS_DECL_ca international :
         virtual public ::radix::object
      {
      public:
         international(::ca::application * papp);
         void parse_str(const char * psz, gen::property_set & set);
         string get_gmt_date_time(const ::datetime::time & time);
         string get_gmt_date_time();
         string get_local_date_time(const ::datetime::time & time);
         string get_local_date_time();
      };

      class CLASS_DECL_ca str :
         virtual public ::radix::object
      {
      public:
         str(::ca::application * papp);
         datetime * m_pdatetime;
         string get_gmt_date_time();
      };


      class ca2::datetime::international m_international;
      class ca2::datetime::str m_str;


      datetime(::ca::application * papp);

      int32_t get_month_day_count(int32_t year, int32_t month);
      int32_t get_weekday(int32_t year, int32_t month, int32_t day);
      int64_t get_timestamp(int32_t year, int32_t month, int32_t day);
      int64_t strtotime(::user::str_context * pcontext, const char * psz, time_t time, int32_t iPath, int32_t & iPathCount);
      int64_t strtotime(::user::str_context * pcontext, const char * psz, int32_t iPath, int32_t & iPathCount);

       // 1 - domingo
      string get_week_day_str(user::str_context * pcontext, int32_t iWeekDay);
       // 1 - domingo
      string get_tiny_week_day_str(user::str_context * pcontext, int32_t iWeekDay);
      string get_month_str(user::str_context * pcontext, int32_t iMonth);

      time_t mktime(int32_t iHour, int32_t iMinute, int32_t iSecond, int32_t iMonth, int32_t iDay, int32_t iYear);

      ::datetime::time from_gmt_date_time(int32_t iYear, int32_t iMonth, int32_t iDay, int32_t iHour, int32_t iMinute, int32_t iSecond);

      class international & international();
      class str & str();

      string strftime(const char * psz, time_t timeParam);
      string strftime(const char * psz);


      int32_t SWN(int32_t y, int32_t m, int32_t d );
      int32_t DP(int32_t y, int32_t m);
      int32_t ML(int32_t y, int32_t m);
      int32_t LEAP(int32_t y);
      int32_t dayofweek(int32_t y, int32_t m, int32_t d);	/* 0 = Sunday */
      int32_t SDOW(int32_t y,int32_t m, int32_t d );
      int32_t DOW(int32_t y, int32_t m, int32_t d);
      int32_t getDayOfWeek(int32_t month, int32_t day, int32_t year, int32_t CalendarSystem);
      int32_t ISO_WN(int32_t  y, int32_t m, int32_t d );


   };


} // namespace ca2