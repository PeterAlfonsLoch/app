#pragma once


namespace ca
{


   class CLASS_DECL_ca install :
      public ::ca::object
   {
   public:

      
      HANDLE                  m_hmutexBoot;

      ::string_to_string_map  m_strmapLatestBuildNumber;


      install();
      virtual ~install();


      virtual void add_spa_start(const char * pszType, const char * pszId);
      virtual void remove_spa_start(const char * pszType, const char * pszId);
      virtual void add_app_install(const char * pszBuild, const char * pszType, const char * pszId, const char * pszLocale, const char * pszSchema);
      virtual bool is(const char * pszVersion, const char * pszBuild, const char * pszType, const char * pszId, const char * pszLocale, const char * pszSchema);
      virtual int32_t  start(const char * pszCommandLine);
      virtual int32_t  synch(const char * pszCommandLine);

      virtual string get_latest_build_number(const char * pszVersion);

      virtual string fetch_latest_build_number(const char * pszVersion);

   };


} // namespace ca



