// Alá Telmo Friesen Son God Document
// translucid click-through window
// applications:
//    non-intrusive alatel
//    non-intrusive notifications

#pragma once

namespace alatel
{

   class CLASS_DECL_CA2_ALARM document :
      public ::userbase::document
   {
   public:

      document(::ca::application * papp);
	   virtual ~document();
	   
      DECL_GEN_VSIGNAL(data_on_after_change);

      index create_alarm(const char * pszProfile);
      count get_alarm_count(const char * pszProfile);
      bool remove_alarm(const char * pszProfile, index iIndex);

      bool set_alarm_name(const char * pszProfile, index iIndex, const char * pszName);
      bool set_alarm_hour(const char * pszProfile, index iIndex, int iHour);
      bool set_alarm_minute(const char * pszProfile, index iIndex, int iMinute);
      bool set_alarm_second(const char * pszProfile, index iIndex, int iSecond);

      var get_alarm_name(const char * pszProfile, index iIndex);
      var get_alarm_hour(const char * pszProfile, index iIndex);
      var get_alarm_minute(const char * pszProfile, index iIndex);
      var get_alarm_second(const char * pszProfile, index iIndex);

   #ifdef _DEBUG
	   virtual void assert_valid() const;
	   virtual void dump(dump_context& dc) const;
   #endif

	   virtual BOOL on_new_document();
      bool on_open_document(var varFile);

   };

} // namespace alatel