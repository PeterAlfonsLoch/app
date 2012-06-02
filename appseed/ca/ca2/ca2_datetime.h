#pragma once


CLASS_DECL_ca int SWN(int y, int m, int d );
//where DP ("Days Passed") is given by:
//   DP( y, 1 ) = 0
//  DP( y, m+1 ) = DP( y, m ) + ML( y, m )
CLASS_DECL_ca int DP(int y, int m);
CLASS_DECL_ca int ML(int y, int m);
CLASS_DECL_ca int LEAP(int y );
CLASS_DECL_ca int dayofweek(int y, int m, int d);	/* 0 = Sunday */
CLASS_DECL_ca int SDOW(int y,int m, int d ); // ( 0 = Monday, ..., 6 = Sunday )
CLASS_DECL_ca int DOW(int y, int m, int d);
CLASS_DECL_ca int getDayOfWeek(int month, int day, int year, int CalendarSystem);


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

      int get_month_day_count(int year, int month);
      int get_weekday(int year, int month, int day);
      int64_t get_timestamp(int year, int month, int day);
      int64_t strtotime(::user::str_context * pcontext, const char * psz, time_t time, int iPath, int & iPathCount);
      int64_t strtotime(::user::str_context * pcontext, const char * psz, int iPath, int & iPathCount);

       // 1 - domingo
      string get_week_day_str(user::str_context * pcontext, int iWeekDay);
       // 1 - domingo
      string get_tiny_week_day_str(user::str_context * pcontext, int iWeekDay);
      string get_month_str(user::str_context * pcontext, int iMonth);

      time_t mktime(int iHour, int iMinute, int iSecond, int iMonth, int iDay, int iYear);

      ::datetime::time from_gmt_date_time(int iYear, int iMonth, int iDay, int iHour, int iMinute, int iSecond);

      class international & international();
      class str & str();

      string strftime(const char * psz, time_t timeParam);
      string strftime(const char * psz);


   };


} // namespace ca2